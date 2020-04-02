/*===========================================================================
 *
 * File:		SrFlstView.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	9 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srFlstView.h"
#include "dialogs/sreditdlghandler.h"
#include "SrLvlEditDlg.h"
#include <vector>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrFlstView, CSrRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrFlstView, CSrRecordDialog)
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_SRRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_COMMAND(ID_FLSTLIST_ADD, &CSrFlstView::OnFlstlistAdd)
	ON_COMMAND(ID_FLSTLIST_EDIT, &CSrFlstView::OnFlstlistEdit)
	ON_COMMAND(ID_FLSTLIST_DELETE, &CSrFlstView::OnFlstlistDelete)
	ON_COMMAND(ID_FLSTTLIST_EDITBASE, &CSrFlstView::OnFlsttlistEditbase)
	ON_UPDATE_COMMAND_UI(ID_FLSTLIST_EDIT, &CSrFlstView::OnUpdateFlstlistEdit)
	ON_UPDATE_COMMAND_UI(ID_FLSTLIST_DELETE, &CSrFlstView::OnUpdateFlstlistEdit)
	ON_UPDATE_COMMAND_UI(ID_FLSTTLIST_EDITBASE, &CSrFlstView::OnUpdateFlstlistEdit)
	ON_BN_CLICKED(ID_ADD_BUTTON, &CSrFlstView::OnBnClickedAddButton)
	ON_BN_CLICKED(ID_EDIT_BUTTON, &CSrFlstView::OnBnClickedEditButton)
	ON_BN_CLICKED(ID_DELETE_BUTTON4, &CSrFlstView::OnBnClickedDeleteButton4)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrFlstView)
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
static srreclistcolinit_t s_FlstListInit[] = 
{
	{ SR_FIELD_EDITORID,	150,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		5,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		40,		LVCFMT_CENTER },
	{ SR_FIELD_ITEMNAME,	190,	LVCFMT_LEFT },
	{ SR_FIELD_RECORDTYPE,	60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_FlstListFields[] = 
{
	{ "Item Name",	SR_FIELD_ITEMNAME,  0, NULL },
	{ "EditorID",	SR_FIELD_EDITORID,  0, NULL },
	{ NULL,			SR_FIELD_NONE,      0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Constructor
 *
 *=========================================================================*/
CSrFlstView::CSrFlstView() : CSrRecordDialog(CSrFlstView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrFlstView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Destructor
 *
 *=========================================================================*/
CSrFlstView::~CSrFlstView() 
{
	if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CSrFlstView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrFlstView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
}
/*===========================================================================
 *		End of Class Method CSrFlstView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrFlstView::GetControlData (void) 
{
	CSrFlstRecord*		pFormList;

	GetOutputRecord()->DeleteSubrecords(SR_NAME_LNAM);
	
	CSrRecordDialog::GetControlData();
	if (m_EditInfo.pNewRecord == NULL) return;
	
	pFormList = SrCastClass(CSrFlstRecord, GetOutputRecord());
	if (pFormList == NULL) return;

	for (int i = 0; i < m_ItemList.GetItemCount(); ++i)
	{
		CSrRecord* pRecord = m_ItemList.GetRecord(i);
		if (pRecord == NULL) continue;

		pFormList->AddItem(pRecord->GetFormID());
	}

}
/*===========================================================================
 *		End of Class Method CSrFlstView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrFlstView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrFlstView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrFlstView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrFlstView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrFlstView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();
	
		/* Setup the list */
	m_ItemList.SetListName("FormItemList");
	m_ItemList.DefaultSettings();
	m_ItemList.SetupCustomList(s_FlstListInit, &CSrRecord::s_FieldMap, s_FlstListFields);
	m_ItemList.SetOwner(this);
	m_ItemList.SetDragType(SR_RLDRAG_RECORD);
	
	m_pRecordHandler->GetEventHandler().AddListener(this);
	
	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrFlstView::SetControlData (void) 
{
	CSrRecordDialog::SetControlData();

	FillItemList();
}
/*===========================================================================
 *		End of Class Method CSrFlstView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CSrFlstView::FillItemList (void) 
{
	CSrSubrecord* pSubrecord;
	int		 	  Pos;
			
	m_ItemList.DeleteAllItems();

	pSubrecord = GetInputRecord()->FindFirstSubrecord(SR_NAME_LNAM, Pos);	

	while (pSubrecord)
	{
		CSrFormidSubrecord* pFormid = SrCastClass(CSrFormidSubrecord, pSubrecord);

		if (pFormid != NULL)
		{
			AddItemList(pFormid->GetValue());
		}

		pSubrecord = GetInputRecord()->FindNextSubrecord(SR_NAME_LNAM, Pos);
	}

}
/*===========================================================================
 *		End of Class Method CSrFlstView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Method - int AddItemList (FormID);
 *
 *=========================================================================*/
int CSrFlstView::AddItemList (const srformid_t FormID) 
{
	CSrRecord*	pRecord;
	int         ListIndex;
	
	pRecord = m_pRecordHandler->FindFormID(FormID);
	if (pRecord == NULL) return -1;

	ListIndex = m_ItemList.AddRecord(pRecord);
	if (ListIndex < 0) return -1;
	
	return ListIndex;
}
/*===========================================================================
 *		End of Class Method CSrFlstView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrFlstView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;
	
	if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) 
	{
		Result = Menu.LoadMenu(IDR_FLSTLIST_MENU);
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
 *		End of Class Event CSrFlstView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrFlstView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) 
{
	srformid_t FormID;
	if (m_pDlgHandler == NULL) return -1;
	
	int ListIndex = m_ItemList.GetSelectedItem();
	CSrRecord* pRecord = m_ItemList.GetSelectedRecord();
	if (pRecord == NULL) return -1;
	FormID = pRecord->GetFormID();
		
	if (!SrSelectFormListItem(FormID, m_pRecordHandler)) return -1;

	pRecord = m_pRecordHandler->FindFormID(FormID);
	if (pRecord == NULL) return -1;
		
	m_ItemList.UpdateRecord(ListIndex, pRecord);
	return 0;
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrFlstView::OnListenCleanRecord (CSrListenEvent* pEvent) 
{
	int ListIndex;

	ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
	if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

	return SR_EVENT_RESULT_OK;
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrFlstView::OnListenUpdateRecord (CSrListenEvent* pEvent) 
{
	int ListIndex;

	ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
	if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

	return SR_EVENT_RESULT_OK;
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrFlstView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) 
{
	CSrRecord* pRecord = m_ItemList.GetSelectedRecord();
	if (pRecord == NULL) return -1;
	m_pDlgHandler->EditRecord(pRecord);
	return 0;
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrFlstView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = SRRL_DROPCHECK_ERROR;
  	if (pDropItems->pRecords != NULL) *pResult = OnDropRecords(*pDropItems);
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFlstView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CSrFlstView::OnDropRecords (srrldroprecords_t& DropItems) 
{
	CSrRecord*	     pRecord;
	dword		     Index;
	
	for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) 
	{
		pRecord = DropItems.pRecords->GetAt(Index);
		
			/* Don't drag onto ourself */
		if (pRecord ==  GetInputRecord()) return SRRL_DROPCHECK_ERROR;
		if (pRecord->GetFormID() == GetInputRecord()->GetFormID()) return SRRL_DROPCHECK_ERROR;
		
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;
		
		m_ItemList.AddRecord(pRecord);
	}
	
	return SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrFlstView::OnDropRecords()
 *=========================================================================*/


void CSrFlstView::OnFlstlistAdd()
{
	srformid_t FormID;
	if (!SrSelectFormListItem(FormID, m_pRecordHandler)) return;
	AddItemList(FormID);	
}


void CSrFlstView::OnFlstlistEdit()
{
	OnEditRecordMsg(0, 0);
}


void CSrFlstView::OnFlstlistDelete()
{
	std::vector<int> Indices;
	POSITION Pos = m_ItemList.GetFirstSelectedItemPosition();
	int SelIndex = m_ItemList.GetSelectedItem();
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

	m_ItemList.SelectRecord(SelIndex);
}


void CSrFlstView::OnFlsttlistEditbase()
{
	OnEditBaseRecordMsg(0, 0);
}


void CSrFlstView::OnUpdateFlstlistEdit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_ItemList.GetSelectedRecord() != NULL);
}


void CSrFlstView::OnBnClickedAddButton()
{
	OnFlstlistAdd();
}


void CSrFlstView::OnBnClickedEditButton()
{
	OnEditRecordMsg(0, 0);
}


void CSrFlstView::OnBnClickedDeleteButton4()
{
	OnFlstlistDelete();
}
