/*===========================================================================
 *
 * File:		SrContView.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srcontview.h"
#include "dialogs/sreditdlghandler.h"
#include "SrContItemDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

  IMPLEMENT_DYNCREATE(CSrContView, CSrRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrContView, CSrRecordDialog)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LVLLIST_EDIT, OnLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDIT, OnUpdateLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_DELETE, OnUpdateLvllistDelete)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDITRECORD, OnUpdateLvllistEdit)
	ON_COMMAND(ID_LVLLIST_ADD, OnLvllistAdd)
	ON_COMMAND(ID_LVLLIST_DELETE, OnLvllistDelete)
	ON_COMMAND(ID_MINUS_COUNT, OnMinusCount)
	ON_COMMAND(ID_ADD_COUNT, OnAddCount)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_SRRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_COMMAND(ID_DELETE_ITEM, OnLvllistDelete)
	ON_COMMAND(ID_LVLLIST_EDITRECORD, OnLvlEditrecord)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_KEYDOWN, IDC_ITEM_LIST, OnKeydownItemList)
	ON_BN_CLICKED(IDC_EDIT_OPENSOUND, &CSrContView::OnBnClickedEditOpensound)
	ON_BN_CLICKED(IDC_SELECT_OPENSOUND, &CSrContView::OnBnClickedSelectOpensound)
	ON_BN_CLICKED(IDC_EDIT_CLOSESOUND, &CSrContView::OnBnClickedEditClosesound)
	ON_BN_CLICKED(IDC_SELECT_CLOSESOUND, &CSrContView::OnBnClickedSelectClosesound)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrContView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			16,		IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,			200,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPE,			IDC_TYPE,			16,		IDS_TT_TYPE)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_OPENSOUND,		IDC_OPENSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_CLOSESOUND,		IDC_CLOSESOUND,		128,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Special callback functions for list sorting.
 *
 *=========================================================================*/
static int CALLBACK s_ItemCountRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrCntoSubrecord* pItem1 = SrCastClass(CSrCntoSubrecord, pCustomData1->pSubrecords[0]);
	CSrCntoSubrecord* pItem2 = SrCastClass(CSrCntoSubrecord, pCustomData2->pSubrecords[0]);

	if (pItem1 == NULL || pItem2 == NULL) return (0);
  
	if (pSortData->Reverse) return -((int)pItem1->GetCount() - (int)pItem2->GetCount());
	return ((int)pItem1->GetCount() - (int)pItem2->GetCount());
}


static int CALLBACK s_ItemFormIDRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrCntoSubrecord* pItem1 = SrCastClass(CSrCntoSubrecord, pCustomData1->pSubrecords[0]);
	CSrCntoSubrecord* pItem2 = SrCastClass(CSrCntoSubrecord, pCustomData2->pSubrecords[0]);
  
	if (pItem1 == NULL || pItem2 == NULL) return (0);

	if (pSortData->Reverse) return -(int)(pItem1->GetFormID() - pItem2->GetFormID());
	return (int)(pItem1->GetFormID() - pItem2->GetFormID());
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_ContainerListInit[] = {
	{ SR_FIELD_EDITORID,	190,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		5,		LVCFMT_LEFT,  s_ItemFormIDRecListSort},
	{ SR_FIELD_FLAGS,		40,		LVCFMT_CENTER },
	{ SR_FIELD_ITEMCOUNT,	50,		LVCFMT_CENTER, s_ItemCountRecListSort},
	{ SR_FIELD_ITEMNAME,	190,	LVCFMT_LEFT },
	{ SR_FIELD_RECORDTYPE,	40,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_ContainerListFields[] = {
	{ "Item Name",	SR_FIELD_ITEMNAME,  0, NULL },
	{ "Count",		SR_FIELD_ITEMCOUNT, 0, NULL },
	{ NULL,	SR_FIELD_NONE, 0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Constructor
 *
 *=========================================================================*/
CSrContView::CSrContView() : CSrRecordDialog(CSrContView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrContView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Destructor
 *
 *=========================================================================*/
CSrContView::~CSrContView() 
{
	if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CSrContView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrContView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
	DDX_Control(pDX, IDC_NAME, m_ItemName);
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_OPENSOUND, m_OpenSound);
	DDX_Control(pDX, IDC_CLOSESOUND, m_CloseSound);
}
/*===========================================================================
 *		End of Class Method CSrContView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrContView::GetControlData (void) 
{
  CSrContRecord*    pContainer;
  CSrCntoSubrecord* pItem;
  int               ItemPos;

  CSrRecordDialog::GetControlData();
  if (m_EditInfo.pNewRecord == NULL) return;

  pContainer = SrCastClass(CSrContRecord, m_EditInfo.pNewRecord);
  if (pContainer == NULL) return;

		/* Copy all subrecords into the new record */
  pContainer->DeleteSubrecords(SR_NAME_CNTO);

  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) 
  {
		pContainer->AddItem(pItem->GetFormID(), pItem->GetCount());
  }

  pContainer->UpdateItemCount();
}
/*===========================================================================
 *		End of Class Method CSrContView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrContView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrContView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrContView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrContView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrContView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	SrFillComboList(m_Type, s_SrContainerTypes, 0);

		/* Setup the list */
	m_ItemList.SetListName("ContainerList");
	m_ItemList.DefaultSettings();
	m_ItemList.SetupCustomList(s_ContainerListInit, &CSrContRecord::s_FieldMap, s_ContainerListFields);
	m_ItemList.SetOwner(this);
	m_ItemList.SetDragType(SR_RLDRAG_CUSTOM | SR_RLDRAG_RECORD);

	m_pRecordHandler->GetEventHandler().AddListener(this);

	SaveSubrecords();
	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrContView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void SaveSubrecords (void);
 *
 *=========================================================================*/
void CSrContView::SaveSubrecords (void) 
{
	m_CopyRecord.Destroy();
	m_CopyRecord.Copy(m_EditInfo.pOldRecord);
}
/*===========================================================================
 *		End of Class Method CSrContView::SaveSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrContView::SetControlData (void) 
{
	CSrRecordDialog::SetControlData();

	FillItemList();
}
/*===========================================================================
 *		End of Class Method CSrContView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CSrContView::FillItemList (void) {
  CSrCntoSubrecord* pItem;
  int               ItemPos;

  m_ItemList.DeleteAllItems();
  
  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) 
  {
		AddItemList(pItem);
  }

}
/*===========================================================================
 *		End of Class Method CSrContView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - int AddItemList (pItem);
 *
 *=========================================================================*/
int CSrContView::AddItemList (CSrCntoSubrecord* pItem) 
{
  CSrBaseRecord*    pBaseRecord;
  CSrIdRecord*	    pIdRecord;
  srrlcustomdata_t  CustomData = { 0 };
  int               ListIndex;

  pBaseRecord = m_pRecordHandler->FindFormID(pItem->GetFormID());
  pIdRecord   = NULL;
  if (pBaseRecord != NULL) pIdRecord = SrCastClass(CSrIdRecord, pBaseRecord);

  CustomData.pRecord        = pIdRecord;
  CustomData.pSubrecords[0] = pItem;

  ListIndex = m_ItemList.AddCustomRecord(CustomData);
  if (ListIndex < 0) return (-1);

  UpdateItem(ListIndex, pItem);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrContView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void UpdateItem (ListIndex, pItem);
 *
 *=========================================================================*/
void CSrContView::UpdateItem (const int ListIndex, CSrCntoSubrecord* pItem) 
{
  CSrBaseRecord*    pBaseRecord;
  CSrIdRecord*	    pRecord = NULL;
  CString           Buffer;

  m_ItemList.UpdateRecord(ListIndex);

  pBaseRecord = m_pRecordHandler->FindFormID(pItem->GetFormID());
  if (pBaseRecord != NULL) pRecord = SrCastClass(CSrIdRecord, pBaseRecord);
  
  if (pRecord == NULL) {
    Buffer.Format("0x%08X", pItem->GetFormID());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_FORMID, Buffer);

    m_ItemList.SetCustomField(ListIndex, SR_FIELD_EDITORID, "");
  }

		/* Set custom fields */
  Buffer.Format("%u", (dword) pItem->GetCount());
  m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
}
/*===========================================================================
 *		End of Class Method CSrContView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrContView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) {
    Result = Menu.LoadMenu(IDR_CONTAINERLIST_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }
  else {  
    CSrRecordDialog::OnContextMenu(pWnd, Point);
  }
    
}
/*===========================================================================
 *		End of Class Event CSrContView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CSrContView::OnLvllistEdit() 
{
  CSrCntoSubrecord* pSubrecord;
  srrlcustomdata_t* pCustomData;
  int		    ListIndex;
  int		    Result;

  ListIndex = m_ItemList.GetSelectedItem();
  if (ListIndex < 0) return;

  pCustomData = m_ItemList.GetCustomData(ListIndex);
  if (pCustomData == NULL) return;

  pSubrecord = SrCastClass(CSrCntoSubrecord, pCustomData->pSubrecords[0]);
  if (pSubrecord == NULL) return;

  Result = SrEditContItemDlg(pSubrecord, m_pRecordHandler, m_CopyRecord.GetFormID());
  if (Result == SR_CONTITEMDLG_RESULT_CANCEL) return;

  if (Result == SR_CONTITEMDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pSubrecord);
    m_ItemList.RemoveItem(ListIndex);
    return;
  }
  
  pCustomData->pRecord = m_pRecordHandler->FindFormID(pSubrecord->GetFormID());
  UpdateItem(ListIndex, pSubrecord); 
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrContView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) 
{
  OnLvllistEdit();
  return (0);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvllistAdd ();
 *
 *=========================================================================*/
void CSrContView::OnLvllistAdd() 
{
  CSrCntoSubrecord* pItem;
  int		    Result;

  pItem = m_CopyRecord.AddItem(0, 1);
  Result = SrEditContItemDlg(pItem, m_pRecordHandler, m_CopyRecord.GetFormID());

  if (Result == SR_CONTITEMDLG_RESULT_CANCEL || Result == SR_CONTITEMDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pItem);
    return;
  }

  AddItemList(pItem);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvllistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvllistDelete ();
 *
 *=========================================================================*/
void CSrContView::OnLvllistDelete() 
{
  srrlcustomdata_t*	pCustomData;
  CSrCntoSubrecord*	pItem;
  POSITION		ListPos;
  int			ListIndex;

	/* Delete all items in the record first */
  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) 
  {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);

    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem != NULL) m_CopyRecord.DeleteItem(pItem);
  }

	/* Redraw the list */
  FillItemList();
  m_ItemList.SelectRecord(0);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnUpdateLvllistDelete (pCmdUI);
 *
 *=========================================================================*/
void CSrContView::OnUpdateLvllistDelete (CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnUpdateLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnUpdateLvllistEdit (pCmdUI);
 *
 *=========================================================================*/
void CSrContView::OnUpdateLvllistEdit (CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnUpdateLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnAddCount ();
 *
 *=========================================================================*/
void CSrContView::OnAddCount() 
{
  srrlcustomdata_t*	pCustomData;
  CSrCntoSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() >= 32768) continue;
    pItem->SetCount(pItem->GetCount() + 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnAddCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnMinusCount ();
 *
 *=========================================================================*/
void CSrContView::OnMinusCount() {
  srrlcustomdata_t*	pCustomData;
  CSrCntoSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() == 0) continue;
    pItem->SetCount(pItem->GetCount() - 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
  }

}
/*===========================================================================
 *		End of Class Event CSrContView::OnMinusCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrContView::OnListenCleanRecord (CSrListenEvent* pEvent) 
{
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrContView::OnListenUpdateRecord (CSrListenEvent* pEvent) 
{
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvlEditrecord ();
 *
 *=========================================================================*/
void CSrContView::OnLvlEditrecord() 
{
  CSrRecord* pRecord;
  CWnd*      pWnd;

  pRecord = m_ItemList.GetSelectedRecord();
  if (pRecord == NULL) return;
  
  pWnd = GetOwner();

  if (pWnd != NULL) {
    m_pDlgHandler->EditRecord(pRecord);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvlEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrContView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) 
{
  OnLvlEditrecord();
  return (0);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrContView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;

  *pResult = SRRL_DROPCHECK_ERROR;
  
	/* Check for custom data */
  if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) 
  {
    *pResult = OnDropCustomData(*pDropItems);
  }	/* Check for records */
  else if (pDropItems->pRecords != NULL) 
  {
    *pResult = OnDropRecords(*pDropItems);
  } 

}
/*===========================================================================
 *		End of Class Event CSrContView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CSrContView::OnDropCustomData (srrldroprecords_t& DropItems) 
{
  CSrCntoSubrecord*  pItem;
  srrlcustomdata_t*  pCustomData;
  dword				 Index;

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
  {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (SRRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords    == NULL) return (SRRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords[0] == NULL) return (SRRL_DROPCHECK_ERROR);

		/* Check for dragging another lvlo record */
    if (!SrIsValidContainerRecord(pCustomData->pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);
    pItem = SrCastClass(CSrCntoSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) return (SRRL_DROPCHECK_ERROR);
    
		/* If we're just checking */
    if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pItem->GetFormID(), pItem->GetCount());
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnDropCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CSrContView::OnDropRecords (srrldroprecords_t& DropItems) 
{
  CSrCntoSubrecord*  pItem;
  CSrRecord*	     pRecord;
  dword		     Index;

  for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) 
  {
    pRecord = DropItems.pRecords->GetAt(Index);
    
		/* Don't drag onto ourself */
    if (pRecord == m_EditInfo.pOldRecord) return (SRRL_DROPCHECK_ERROR);
    if (pRecord->GetFormID() == m_EditInfo.pOldRecord->GetFormID()) return (SRRL_DROPCHECK_ERROR);

		/* Ignore any invalid record types */
    if (!SrIsValidContainerRecord(pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);

		/* If we're just checking */
    if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pRecord->GetFormID(), 1);
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnDropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnKeydownItemList (pHdr, lResult);
 *
 *=========================================================================*/
void CSrContView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) 
{
  srrlkeydown_t* pNotify = (srrlkeydown_t *) pHdr;
  *lResult = 0;
	
  if (pNotify->KeyDown.nVKey == VK_DELETE || pNotify->KeyDown.nVKey == VK_BACK) 
  {
    if (!pNotify->Ctrl && !pNotify->Alt) OnLvllistDelete();
  }
  else if (pNotify->KeyDown.nVKey == VK_ADD) 
  {
      OnAddCount();
  }
  else if (pNotify->KeyDown.nVKey == VK_SUBTRACT) 
  {
      OnMinusCount();
  }

}
/*===========================================================================
 *		End of Class Event CSrContView::OnKeydownItemList()
 *=========================================================================*/



void CSrContView::OnBnClickedEditOpensound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_OpenSound, SR_NAME_SNDR);
}


void CSrContView::OnBnClickedSelectOpensound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_OpenSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrContView::OnBnClickedEditClosesound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_CloseSound, SR_NAME_SNDR);
}


void CSrContView::OnBnClickedSelectClosesound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_CloseSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}
