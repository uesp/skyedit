/*===========================================================================
 *
 * File:		Srlvlnview.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srLvlnView.h"
#include "dialogs/sreditdlghandler.h"
#include "SrLvlEditDlg.h"


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

  IMPLEMENT_DYNCREATE(CSrLvlnView, CSrRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrLvlnView, CSrRecordDialog)
	//{{AFX_MSG_MAP(CSrLvlnView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LVLLIST_EDIT, OnLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDIT, OnUpdateLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_DELETE, OnUpdateLvllistDelete)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDITRECORD, OnUpdateLvllistEdit)
	ON_COMMAND(ID_LVLLIST_ADD, OnLvllistAdd)
	ON_COMMAND(ID_LVLLIST_DELETE, OnLvllistDelete)
	ON_COMMAND(ID_MINUS_COUNT, OnMinusCount)
	ON_COMMAND(ID_ADD_COUNT, OnAddCount)
	ON_COMMAND(ID_MINUS_LEVEL, OnMinusLevel)
	ON_COMMAND(ID_ADD_LEVEL, OnAddLevel)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_SRRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_COMMAND(ID_DELETE_ITEM, OnLvllistDelete)
	ON_COMMAND(ID_LVLLIST_EDITRECORD, OnLvlEditrecord)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_KEYDOWN, IDC_ITEM_LIST, OnKeydownItemList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrLvlnView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID2,		16,		IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_CALCULATEEACH,	IDC_CALCULATEEACH,	0,		IDS_TT_CALCEACH)
	ADD_SRRECUIFIELDS( SR_FIELD_CALCULATEALL,	IDC_CALCULATEALL,	0,		IDS_TT_CALCALL)
	ADD_SRRECUIFIELDS( SR_FIELD_USEALL,			IDC_USEALL,			0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CHANCENONE,		IDC_CHANCENONE,		16,		IDS_TT_CHANCENONE)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,			200,	IDS_TT_MODEL)
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
	CSrLvloSubrecord* pItem1 = SrCastClass(CSrLvloSubrecord, pCustomData1->pSubrecords[0]);
	CSrLvloSubrecord* pItem2 = SrCastClass(CSrLvloSubrecord, pCustomData2->pSubrecords[0]);

	if (pItem1 == NULL || pItem2 == NULL) return (0);
  
	if (pSortData->Reverse) return -((int)pItem1->GetCount() - (int)pItem2->GetCount());
	return ((int)pItem1->GetCount() - (int)pItem2->GetCount());
}


static int CALLBACK s_ItemLevelRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrLvloSubrecord* pItem1 = SrCastClass(CSrLvloSubrecord, pCustomData1->pSubrecords[0]);
	CSrLvloSubrecord* pItem2 = SrCastClass(CSrLvloSubrecord, pCustomData2->pSubrecords[0]);
  
	if (pItem1 == NULL || pItem2 == NULL) return (0);

	if (pSortData->Reverse) return -((int)pItem1->GetLevel() - (int)pItem2->GetLevel());
	return ((int)pItem1->GetLevel() - (int)pItem2->GetLevel());
}


static int CALLBACK s_ItemFormIDRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrLvloSubrecord* pItem1 = SrCastClass(CSrLvloSubrecord, pCustomData1->pSubrecords[0]);
	CSrLvloSubrecord* pItem2 = SrCastClass(CSrLvloSubrecord, pCustomData2->pSubrecords[0]);
  
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
static srreclistcolinit_t s_LevelListInit[] = {
	{ SR_FIELD_EDITORID,	150,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		5,		LVCFMT_LEFT,  s_ItemFormIDRecListSort},
	{ SR_FIELD_FLAGS,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LEVEL,		40,		LVCFMT_CENTER, s_ItemLevelRecListSort},
	{ SR_FIELD_ITEMCOUNT,	40,		LVCFMT_CENTER, s_ItemCountRecListSort},
	{ SR_FIELD_ITEMNAME,	190,	LVCFMT_LEFT },
	{ SR_FIELD_RECORDTYPE,	40,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_LevelListFields[] = {
	{ "Item Name",	SR_FIELD_ITEMNAME,  0, NULL },
	{ "Count",	SR_FIELD_ITEMCOUNT, 0, NULL },
	{ "Level",	SR_FIELD_LEVEL,     0, NULL },
	{ NULL,		SR_FIELD_NONE,      0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Constructor
 *
 *=========================================================================*/
CSrLvlnView::CSrLvlnView() : CSrRecordDialog(CSrLvlnView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrLvlnView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Destructor
 *
 *=========================================================================*/
CSrLvlnView::~CSrLvlnView() 
{
	if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CSrLvlnView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrLvlnView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CALCULATEEACH, m_CalculateEach);
	DDX_Control(pDX, IDC_CALCULATEALL, m_CalculateAll);
	DDX_Control(pDX, IDC_CHANCENONE, m_ChanceNone);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID2, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
	DDX_Control(pDX, IDC_USEALL, m_UseAll);
	DDX_Control(pDX, IDC_MODEL, m_Model);
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::DoDataExchange()
 *=========================================================================*/


static int __stdcall l_SortLevelRecords (long lParam1, long lParam2, long lParamSort)
{
	CSrLvloSubrecord* pRecord1 = (CSrLvloSubrecord *) lParam1;
	CSrLvloSubrecord* pRecord2 = (CSrLvloSubrecord *) lParam2;

	if (pRecord1 == NULL || pRecord2 == NULL) return 0;

	if (pRecord1->GetLevel() == pRecord2->GetLevel()) return 0;
	if (pRecord1->GetLevel() >  pRecord2->GetLevel()) return 1;
	return -1;
}


/*===========================================================================
 *
 * Class CSrLvlnView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrLvlnView::GetControlData (void) 
{
  CSrLvlnRecord*		pLevelItem;
  CSrLvloSubrecord*		pItem;
  CSrRefSubrecordArray	SortLevelRecords;
  int					ItemPos;
  
  CSrRecordDialog::GetControlData();

  if (m_EditInfo.pNewRecord == NULL) return;

  pLevelItem = SrCastClass(CSrLvlnRecord, m_EditInfo.pNewRecord);
  if (pLevelItem == NULL) return;

		/* Ensure the count subreecord is created in the correct place */
  pLevelItem->DeleteSubrecords(SR_NAME_LLCT);
  pLevelItem->DeleteSubrecords(SR_NAME_LVLO);
  pLevelItem->UpdateListCount();

		/* Copy all subrecords into the new record */
  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) 
  {
	  SortLevelRecords.Add(pItem);
  }

  SortLevelRecords.Sort(l_SortLevelRecords, 0);

  for (dword i = 0; i < SortLevelRecords.GetSize(); ++i)
  {
	  pItem = SrCastClass(CSrLvloSubrecord, SortLevelRecords[i]);
	  if (pItem == NULL) continue;
	  pLevelItem->AddItem(pItem->GetFormID(), pItem->GetLevel(), pItem->GetCount());
  }  

  pLevelItem->UpdateListCount();
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrLvlnView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrLvlnView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrLvlnView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrLvlnView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrLvlnView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

	/* Setup the list */
  m_ItemList.SetListName("LvlnList");
  m_ItemList.DefaultSettings();
  m_ItemList.SetupCustomList(s_LevelListInit, &CSrLvlnRecord::s_FieldMap, s_LevelListFields);
  m_ItemList.SetOwner(this);
  m_ItemList.SetDragType(SR_RLDRAG_CUSTOM | SR_RLDRAG_RECORD);

  m_pRecordHandler->GetEventHandler().AddListener(this);

  SaveSubrecords();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - void SaveSubrecords (void);
 *
 *=========================================================================*/
void CSrLvlnView::SaveSubrecords (void) 
{
	m_CopyRecord.Destroy();
	m_CopyRecord.Copy(m_EditInfo.pOldRecord);
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::SaveSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrLvlnView::SetControlData (void) 
{
	CSrRecordDialog::SetControlData();

	FillItemList();
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CSrLvlnView::FillItemList (void) {
  CSrLvloSubrecord* pItem;
  int               ItemPos;

  m_ItemList.DeleteAllItems();
  
  for (pItem = m_CopyRecord.GetFirstItem(ItemPos); pItem != NULL; pItem = m_CopyRecord.GetNextItem(ItemPos)) 
  {
		AddItemList(pItem);
  }

}
/*===========================================================================
 *		End of Class Method CSrLvlnView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - int AddItemList (pItem);
 *
 *=========================================================================*/
int CSrLvlnView::AddItemList (CSrLvloSubrecord* pItem) 
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
 *		End of Class Method CSrLvlnView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - void UpdateItem (ListIndex, pItem);
 *
 *=========================================================================*/
void CSrLvlnView::UpdateItem (const int ListIndex, CSrLvloSubrecord* pItem) 
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
  Buffer.Format("%u", (dword) pItem->GetLevel());
  m_ItemList.SetCustomField(ListIndex, SR_FIELD_LEVEL, Buffer);

  Buffer.Format("%u", (dword) pItem->GetCount());
  m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrLvlnView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) {
    Result = Menu.LoadMenu(IDR_LVLITEMLIST_MENU);
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
 *		End of Class Event CSrLvlnView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CSrLvlnView::OnLvllistEdit() 
{
  CSrLvloSubrecord* pSubrecord;
  srrlcustomdata_t* pCustomData;
  int		    ListIndex;
  int		    Result;

  ListIndex = m_ItemList.GetSelectedItem();
  if (ListIndex < 0) return;

  pCustomData = m_ItemList.GetCustomData(ListIndex);
  if (pCustomData == NULL) return;

  pSubrecord = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
  if (pSubrecord == NULL) return;

  Result = SrEditLvlActorDlg (pSubrecord, m_pRecordHandler, m_CopyRecord.GetFormID());
  if (Result == SR_LVLEDITDLG_RESULT_CANCEL) return;

  if (Result == SR_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pSubrecord);
    m_ItemList.RemoveItem(ListIndex);
    return;
  }
  
  pCustomData->pRecord = m_pRecordHandler->FindFormID(pSubrecord->GetFormID());
  UpdateItem(ListIndex, pSubrecord); 
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrLvlnView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) 
{
  OnLvllistEdit();
  return (0);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnLvllistAdd ();
 *
 *=========================================================================*/
void CSrLvlnView::OnLvllistAdd() 
{
  CSrLvloSubrecord* pItem;
  int		    Result;

  pItem = m_CopyRecord.AddItem(0, 1, 1);
  Result = SrEditLvlActorDlg(pItem, m_pRecordHandler, m_CopyRecord.GetFormID());

  if (Result == SR_LVLEDITDLG_RESULT_CANCEL || Result == SR_LVLEDITDLG_RESULT_DELETE) {
    m_CopyRecord.DeleteItem(pItem);
    return;
  }

  AddItemList(pItem);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnLvllistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnLvllistDelete ();
 *
 *=========================================================================*/
void CSrLvlnView::OnLvllistDelete() 
{
  srrlcustomdata_t*	pCustomData;
  CSrLvloSubrecord*	pItem;
  POSITION		ListPos;
  int			ListIndex;

	/* Delete all items in the record first */
  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);

    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem != NULL) m_CopyRecord.DeleteItem(pItem);
  }

	/* Redraw the list */
  FillItemList();
  m_ItemList.SelectRecord(0);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnUpdateLvllistDelete (pCmdUI);
 *
 *=========================================================================*/
void CSrLvlnView::OnUpdateLvllistDelete (CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnUpdateLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnUpdateLvllistEdit (pCmdUI);
 *
 *=========================================================================*/
void CSrLvlnView::OnUpdateLvllistEdit (CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnUpdateLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnAddCount ();
 *
 *=========================================================================*/
void CSrLvlnView::OnAddCount() 
{
  srrlcustomdata_t*	pCustomData;
  CSrLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() >= 32768) continue;
    pItem->SetCount(pItem->GetCount() + 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnAddCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnMinusCount ();
 *
 *=========================================================================*/
void CSrLvlnView::OnMinusCount() 
{
  srrlcustomdata_t*	pCustomData;
  CSrLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) 
  {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetCount() == 0) continue;
    pItem->SetCount(pItem->GetCount() - 1);

    Buffer.Format("%u", (dword) pItem->GetCount());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
  }

}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnMinusCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnAddLevel ();
 *
 *=========================================================================*/
void CSrLvlnView::OnAddLevel() 
{
  srrlcustomdata_t*	pCustomData;
  CSrLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) 
  {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetLevel() >= 32768) continue;
    pItem->SetLevel(pItem->GetLevel() + 1);

    Buffer.Format("%u", (dword) pItem->GetLevel());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_LEVEL, Buffer);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnAddLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnMinusLevel ();
 *
 *=========================================================================*/
void CSrLvlnView::OnMinusLevel() 
{
  srrlcustomdata_t*	pCustomData;
  CSrLvloSubrecord*	pItem;
  POSITION		ListPos;
  CString		Buffer;
  int			ListIndex;

  ListPos = m_ItemList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) 
  {
    ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
    pCustomData = m_ItemList.GetCustomData(ListIndex);
    if (pCustomData == NULL) continue;

    pItem = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) continue; 

    if (pItem->GetLevel() == 0) continue;
    pItem->SetLevel(pItem->GetLevel() - 1);

    Buffer.Format("%u", (dword) pItem->GetLevel());
    m_ItemList.SetCustomField(ListIndex, SR_FIELD_LEVEL, Buffer);
  }

}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnMinusLevel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrLvlnView::OnListenCleanRecord (CSrListenEvent* pEvent) 
{
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrLvlnView::OnListenUpdateRecord (CSrListenEvent* pEvent) 
{
  int ListIndex;

  ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnLvlEditrecord ();
 *
 *=========================================================================*/
void CSrLvlnView::OnLvlEditrecord() 
{
  CSrRecord* pRecord;
  CWnd*      pWnd;

  pRecord = m_ItemList.GetSelectedRecord();
  if (pRecord == NULL) return;
  
  pWnd = GetOwner();

  if (pWnd != NULL) 
  {
    m_pDlgHandler->EditRecord(pRecord);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnLvlEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrLvlnView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) 
{
  OnLvlEditrecord();
  return (0);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrLvlnView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult)
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
 *		End of Class Event CSrLvlnView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CSrLvlnView::OnDropCustomData (srrldroprecords_t& DropItems) 
{
  CSrLvloSubrecord*  pItem;
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
	if (!SrIsValidLvlnRecord(pCustomData->pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);
    pItem = SrCastClass(CSrLvloSubrecord, pCustomData->pSubrecords[0]);
    if (pItem == NULL) return (SRRL_DROPCHECK_ERROR);
    
		/* If we're just checking */
    if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pItem->GetFormID(), pItem->GetLevel(), pItem->GetCount());
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnDropCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CSrLvlnView::OnDropRecords (srrldroprecords_t& DropItems) 
{
  CSrLvloSubrecord*  pItem;
  CSrRecord*	     pRecord;
  dword		     Index;

  for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) 
  {
    pRecord = DropItems.pRecords->GetAt(Index);
    
		/* Don't drag onto ourself */
    if (pRecord == m_EditInfo.pOldRecord) return (SRRL_DROPCHECK_ERROR);
    if (pRecord->GetFormID() == m_EditInfo.pOldRecord->GetFormID()) return (SRRL_DROPCHECK_ERROR);

		/* Ignore any invalid record types */
    if (!SrIsValidLvlnRecord(pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);

		/* If we're just checking */
    if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

    pItem = m_CopyRecord.AddItem(pRecord->GetFormID(), 1, 1);
    if (pItem == NULL) continue;

    AddItemList(pItem);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnDropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnKeydownItemList (pHdr, lResult);
 *
 *=========================================================================*/
void CSrLvlnView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) {
  srrlkeydown_t* pNotify = (srrlkeydown_t *) pHdr;
  *lResult = 0;
	
  if (pNotify->KeyDown.nVKey == VK_DELETE || pNotify->KeyDown.nVKey == VK_BACK) {
    if (!pNotify->Ctrl && !pNotify->Alt) OnLvllistDelete();
  }
  else if (pNotify->KeyDown.nVKey == VK_ADD) {
    if (pNotify->Shift) 
      OnAddCount();
    else
      OnAddLevel();
  }
  else if (pNotify->KeyDown.nVKey == VK_SUBTRACT) {
    if (pNotify->Shift) 
      OnMinusCount();
    else
      OnMinusLevel();
  }

}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnKeydownItemList()
 *=========================================================================*/
