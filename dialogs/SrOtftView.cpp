/*===========================================================================
 *
 * File:		SrOtftView.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	8 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srOtftView.h"
#include "dialogs/sreditdlghandler.h"
#include "SrLvlEditDlg.h"
#include <vector>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrOtftView, CSrRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrOtftView, CSrRecordDialog)
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_SRRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_COMMAND(ID_OUTFITLIST_ADD, &CSrOtftView::OnOutfitlistAdd)
	ON_COMMAND(ID_OUTFITLIST_DELETE, &CSrOtftView::OnOutfitlistDelete)
	ON_COMMAND(ID_OUTFITLIST_EDIT, &CSrOtftView::OnOutfitlistEdit)
	ON_COMMAND(ID_OUTFITLIST_EDITBASE, &CSrOtftView::OnOutfitlistEditBase)
	ON_UPDATE_COMMAND_UI(ID_OUTFITLIST_DELETE, &CSrOtftView::OnUpdateOutfitlistMenu)
	ON_UPDATE_COMMAND_UI(ID_OUTFITLIST_EDIT, &CSrOtftView::OnUpdateOutfitlistMenu)
	ON_UPDATE_COMMAND_UI(ID_OUTFITLIST_EDITBASE, &CSrOtftView::OnUpdateOutfitlistMenu)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrOtftView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			16,		IDS_TT_FORMID)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_OutfitListInit[] = {
	{ SR_FIELD_EDITORID,	150,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		5,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		40,		LVCFMT_CENTER },
	{ SR_FIELD_ITEMNAME,	190,	LVCFMT_LEFT },
	{ SR_FIELD_RECORDTYPE,	60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_OutfitListFields[] = {
	{ "FormID",		SR_FIELD_FORMID,		0, NULL },
	{ "EditorID",	SR_FIELD_EDITORID,		0, NULL },
	{ "Flags",		SR_FIELD_FLAGS,			0, NULL },
	{ "Item Name",	SR_FIELD_ITEMNAME,		0, NULL },
	{ "RecType",	SR_FIELD_RECORDTYPE,	0, NULL },
	{ NULL,			SR_FIELD_NONE,			0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Constructor
 *
 *=========================================================================*/
CSrOtftView::CSrOtftView() : CSrRecordDialog(CSrOtftView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrOtftView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Destructor
 *
 *=========================================================================*/
CSrOtftView::~CSrOtftView() 
{
	if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CSrOtftView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrOtftView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);	
}
/*===========================================================================
 *		End of Class Method CSrOtftView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrOtftView::GetControlData (void) 
{
	CSrRecordDialog::GetControlData();
	CSrOtftRecord* pOutfit = SrCastClass(CSrOtftRecord, GetOutputRecord());
	if (pOutfit == NULL) return;

	CSrFormidArray* pArray = pOutfit->GetItemArray();
	if (pArray == NULL) return;
	pArray->Destroy();

	for (int i = 0; i < m_ItemList.GetItemCount(); ++i)
	{
		CSrRecord* pRecord = m_ItemList.GetRecord(i);
		if (pRecord == NULL) continue;
		pArray->Add(pRecord->GetFormID());
	}
 
}
/*===========================================================================
 *		End of Class Method CSrOtftView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrOtftView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrOtftView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrOtftView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrOtftView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrOtftView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

		/* Setup the list */
	m_ItemList.SetListName("OutfitList");
	m_ItemList.DefaultSettings();
	m_ItemList.SetupCustomList(s_OutfitListInit, &CSrOtftRecord::s_FieldMap, s_OutfitListFields);
	m_ItemList.SetOwner(this);
	m_ItemList.SetDragType(SR_RLDRAG_RECORD);
	m_ItemList.SetSortEnable(false);

	m_pRecordHandler->GetEventHandler().AddListener(this);

	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrOtftView::SetControlData (void) 
{
	CSrRecordDialog::SetControlData();
	FillItemList();
}
/*===========================================================================
 *		End of Class Method CSrOtftView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CSrOtftView::FillItemList (void) {
	CSrFormidArray* pArray;
	CSrOtftRecord*  pOutfit = SrCastClass(CSrOtftRecord, GetInputRecord());

	m_ItemList.DeleteAllItems();
	if (pOutfit == NULL) return;
	pArray = pOutfit->GetItemArray();

	for (dword i = 0; i < pArray->GetSize(); ++i) 
	{
		AddItemList((*pArray)[i]);
	}

}
/*===========================================================================
 *		End of Class Method CSrOtftView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Method - int AddItemList (FormID);
 *
 *=========================================================================*/
int CSrOtftView::AddItemList (const srformid_t FormID) 
{
	CSrBaseRecord*    pBaseRecord;
	CSrIdRecord*	  pIdRecord = NULL;
	int               ListIndex;

	pBaseRecord = m_pRecordHandler->FindFormID(FormID);
	if (pBaseRecord != NULL) pIdRecord = SrCastClass(CSrIdRecord, pBaseRecord);
	if (pIdRecord == NULL) return -1;

	ListIndex = m_ItemList.AddRecord(pIdRecord);
	if (ListIndex < 0) return -1;

	return ListIndex;
}
/*===========================================================================
 *		End of Class Method CSrOtftView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Method - void UpdateItem (ListIndex, pItem);
 *
 *=========================================================================*/
void CSrOtftView::UpdateItem (const int ListIndex, CSrIdRecord* pItem) 
{

}
/*===========================================================================
 *		End of Class Method CSrOtftView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrOtftView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
	CMenu	Menu;
	CMenu*	pSubMenu;
	int		Result;

	if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) 
	{
		Result = Menu.LoadMenu(IDR_OUTFITLIST_MENU);
		if (!Result) return;

		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;

		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
	else 
	{  
		CSrRecordDialog::OnContextMenu(pWnd, Point);
	}
    
}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrOtftView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) 
{
	CString Buffer;
	if (m_pDlgHandler == NULL) return -1;
	
	int ListIndex = m_ItemList.GetSelectedItem();
	CSrRecord* pRecord = m_ItemList.GetSelectedRecord();
	CSrIdRecord* pIdRecord = SrCastClassNull(CSrIdRecord, pRecord);
	if (pIdRecord == NULL) return -1;
	Buffer = pIdRecord->GetEditorID();
		
	if (!SrSelectOutfitItem(Buffer, m_pRecordHandler)) return -1;

	pIdRecord = m_pRecordHandler->FindEditorID(Buffer);
	if (pRecord == NULL) return -1;

	m_ItemList.SetItemData(ListIndex, pRecord);
	return 0;
}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnEditRecordMsg()
 *=========================================================================*/


LRESULT CSrOtftView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) 
{
	if (m_pDlgHandler == NULL) return -1;
	
	CSrRecord* pRecord = m_ItemList.GetSelectedRecord();
	if (pRecord == NULL) return -1;

	m_pDlgHandler->EditRecord(pRecord);

	return 0;
}


/*===========================================================================
 *
 * Class CSrOtftView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrOtftView::OnListenCleanRecord (CSrListenEvent* pEvent) 
{
	int ListIndex;

	ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
	if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

	return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrOtftView::OnListenUpdateRecord (CSrListenEvent* pEvent) 
{
	int ListIndex;

	ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
	if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

	return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrOtftView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	
	*pResult = SRRL_DROPCHECK_ERROR;
	
	if (pDropItems->pRecords != NULL) 
	{
		*pResult = OnDropRecords(*pDropItems);
	} 

}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrOtftView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CSrOtftView::OnDropRecords (srrldroprecords_t& DropItems) 
{
	CSrRecord*			pRecord;
	dword				Index;
	
	for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) 
	{
		pRecord = DropItems.pRecords->GetAt(Index);
		
			/* Don't drag onto ourself */
		if (pRecord == m_EditInfo.pOldRecord) return (SRRL_DROPCHECK_ERROR);
		if (pRecord->GetFormID() == m_EditInfo.pOldRecord->GetFormID()) return SRRL_DROPCHECK_ERROR;
		
			/* Ignore any invalid record types */
		if (pRecord->GetRecordType() != SR_NAME_ARMO && pRecord->GetRecordType() != SR_NAME_LVLI) return SRRL_DROPCHECK_ERROR;
		
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;
		
		AddItemList(pRecord->GetFormID());
	}
	
	return SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrOtftView::OnDropRecords()
 *=========================================================================*/


void CSrOtftView::OnOutfitlistAdd()
{
	CString Buffer;

	if (!SrSelectOutfitItem(Buffer, m_pRecordHandler)) return;

	CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);
	if (pRecord == NULL) return;
	AddItemList(pRecord->GetFormID());
}


void CSrOtftView::OnOutfitlistDelete()
{
	std::vector<int> Indices;
	POSITION Pos = m_ItemList.GetFirstSelectedItemPosition();
	int ListIndex;
	
	while (Pos)
	{
		ListIndex = m_ItemList.GetNextSelectedItem(Pos);
		Indices.push_back(ListIndex);
	}

	for (auto i = Indices.rbegin(); i != Indices.rend(); ++i)
	{
		m_ItemList.DeleteItem(*i);
	}

}


void CSrOtftView::OnOutfitlistEdit()
{
	CSrRecord* pRecord = m_ItemList.GetSelectedRecord();

	if (pRecord == NULL) return;
	if (m_pDlgHandler) m_pDlgHandler->EditRecord(pRecord);
}


void CSrOtftView::OnOutfitlistEditBase()
{
	OnEditBaseRecordMsg(0,0);
}


void CSrOtftView::OnUpdateOutfitlistMenu(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_ItemList.GetSelectedRecord() != NULL);
}
