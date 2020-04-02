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
#include <vector>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
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
	CSrLvloSubrecord* pItem1 = SrCastClassNull(CSrLvloSubrecord, pCustomData1->Subrecords[0]);
	CSrLvloSubrecord* pItem2 = SrCastClassNull(CSrLvloSubrecord, pCustomData2->Subrecords[0]);

	if (pItem1 == NULL || pItem2 == NULL) return (0);
  
	if (pSortData->Reverse) return -((int)pItem1->GetCount() - (int)pItem2->GetCount());
	return ((int)pItem1->GetCount() - (int)pItem2->GetCount());
}


static int CALLBACK s_ItemLevelRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrLvloSubrecord* pItem1 = SrCastClassNull(CSrLvloSubrecord, pCustomData1->Subrecords[0]);
	CSrLvloSubrecord* pItem2 = SrCastClassNull(CSrLvloSubrecord, pCustomData2->Subrecords[0]);
  
	if (pItem1 == NULL || pItem2 == NULL) return (0);

	if (pSortData->Reverse) return -((int)pItem1->GetLevel() - (int)pItem2->GetLevel());
	return ((int)pItem1->GetLevel() - (int)pItem2->GetLevel());
}


static int CALLBACK s_ItemFormIDRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrLvloSubrecord* pItem1 = SrCastClass(CSrLvloSubrecord, pCustomData1->Subrecords[0]);
	CSrLvloSubrecord* pItem2 = SrCastClass(CSrLvloSubrecord, pCustomData2->Subrecords[0]);
  
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
static srreclistcolinit_t s_LevelListInit[] = 
{
	{ SR_FIELD_EDITORID,		150,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,			5,		LVCFMT_LEFT,  s_ItemFormIDRecListSort},
	{ SR_FIELD_FLAGS,			40,		LVCFMT_CENTER },
	{ SR_FIELD_LEVEL,			40,		LVCFMT_CENTER, s_ItemLevelRecListSort},
	{ SR_FIELD_ITEMCOUNT,		40,		LVCFMT_CENTER, s_ItemCountRecListSort},
	{ SR_FIELD_RECORDTYPE,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTFACTION,		100,	LVCFMT_CENTER },
	{ SR_FIELD_LISTMINRANK,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTCONDITION,	50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_LevelListFields[] = 
{
	{ "Item Name",	SR_FIELD_ITEMNAME,		0, NULL },
	{ "Count",		SR_FIELD_ITEMCOUNT,		0, NULL },
	{ "Level",		SR_FIELD_LEVEL,			0, NULL },
	{ "Faction",	SR_FIELD_LISTFACTION,	0, NULL },
	{ "MinRank",	SR_FIELD_LISTMINRANK,	0, NULL },
	{ "Condition",	SR_FIELD_LISTCONDITION, 0, NULL },
	{ NULL,	SR_FIELD_NONE, 0, NULL }
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
	srlvllistinfo_t* pRecord1 = (srlvllistinfo_t *) lParam1;
	srlvllistinfo_t* pRecord2 = (srlvllistinfo_t *) lParam2;

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
	CSrLvlnRecord*			pLevelItem;
	CSrRefSubrecordArray	SortLevelRecords;
	
	CSrRecordDialog::GetControlData();
	
	if (m_EditInfo.pNewRecord == NULL) return;
	
	pLevelItem = SrCastClass(CSrLvlnRecord, GetOutputRecord());
	if (pLevelItem == NULL) return;

	m_LvlListInfo.Sort(l_SortLevelRecords, 0);
	SrSaveLvlListInfo(m_LvlListInfo, *pLevelItem);

		/* Update item list due to change in listinfo order*/
	FillItemList();
	
	pLevelItem->MoveToEnd(SR_NAME_MODL);
	pLevelItem->MoveToEnd(SR_NAME_MODT);
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
	void CSrLvlnView::AssertValid() const { CSrRecordDialog::AssertValid(); }
	void CSrLvlnView::Dump(CDumpContext& dc) const { CSrRecordDialog::Dump(dc); }
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
	m_ItemList.SetSortEnable(false);

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
	SrCreateLvlListInfo(m_LvlListInfo, GetInputRecord());
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
void CSrLvlnView::FillItemList (void) 
{
	m_ItemList.DeleteAllItems();
  
	for (dword i = 0; i < m_LvlListInfo.GetSize(); ++i)
	{
		AddItemList(m_LvlListInfo[i]);
	}
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - int AddItemList (pInfo);
 *
 *=========================================================================*/
int CSrLvlnView::AddItemList (srlvllistinfo_t* pInfo) 
{
	srrlcustomdata_t  CustomData;
	int               ListIndex;

	if (pInfo->pLvlo == NULL) return -1;
	SrCreateLvlListInfoCustomData(CustomData, *pInfo, m_pRecordHandler);

	ListIndex = m_ItemList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdateItem(ListIndex, pInfo);
	return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrLvlnView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Method - void UpdateItem (ListIndex, pInfo);
 *
 *=========================================================================*/
void CSrLvlnView::UpdateItem (const int ListIndex, srlvllistinfo_t* pInfo) 
{
	CSrBaseRecord*    pBaseRecord;
	CSrIdRecord*	  pRecord;
	CString           Buffer;

	m_ItemList.UpdateRecord(ListIndex);

	pBaseRecord = m_pRecordHandler->FindFormID(pInfo->GetFormID());
	pRecord = SrCastClassNull(CSrIdRecord, pBaseRecord);
  
	if (pRecord == NULL) 
	{
		Buffer.Format("0x%08X", pInfo->GetFormID());
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_FORMID, Buffer);
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_EDITORID, "");
	}

		/* Set custom fields */
	Buffer.Format("%u", (dword) pInfo->GetLevel());
	m_ItemList.SetCustomField(ListIndex, SR_FIELD_LEVEL, Buffer);

	Buffer.Format("%u", (dword) pInfo->GetCount());
	m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);

	if (pInfo->pCoed != NULL)
	{
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTFACTION, m_pRecordHandler->GetEditorID(pInfo->pCoed->GetCoedData().FactionID));

		Buffer.Format("%d", (int) pInfo->pCoed->GetCoedData().MinRank);
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTMINRANK, Buffer);

		Buffer.Format("%g", pInfo->pCoed->GetCoedData().Condition);
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTCONDITION, Buffer);
	}
	else
	{
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTFACTION, "");
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTMINRANK, "");
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTCONDITION, "");
	}
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

	if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) 
	{
		Result = Menu.LoadMenu(IDR_LVLITEMLIST_MENU);
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
 *		End of Class Event CSrLvlnView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlnView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CSrLvlnView::OnLvllistEdit() 
{
	CSrLvloSubrecord*	pSubrecord;
	srlvllistinfo_t*	pListInfo;
	srrlcustomdata_t*	pCustomData;
	int					ListIndex;
	int					Result;

	ListIndex = m_ItemList.GetSelectedItem();
	if (ListIndex < 0) return;

	pCustomData = m_ItemList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	pSubrecord = SrCastClassNull(CSrLvloSubrecord, pCustomData->Subrecords[0]);
	if (pSubrecord == NULL) return;

	pListInfo = SrFindLvlListInfo(m_LvlListInfo, pSubrecord);
	if (pListInfo == NULL) return;

	Result = SrEditLvlActorDlg (pListInfo, m_pDlgHandler, GetInputRecord()->GetFormID());
	if (Result == SR_LVLEDITDLG_RESULT_CANCEL) return;

	if (Result == SR_LVLEDITDLG_RESULT_DELETE) 
	{
		m_LvlListInfo.Delete(pListInfo);
		m_ItemList.RemoveItem(ListIndex);
		return;
	}
  
	SrCreateLvlListInfoCustomData(*pCustomData, *pListInfo, m_pRecordHandler);
	UpdateItem(ListIndex, pListInfo); 
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
	srlvllistinfo_t*  pNewInfo;
	int				  Result;

	pNewInfo = m_LvlListInfo.AddNew();
	pNewInfo->InitializeNew(SR_NAME_LVLN);
	Result = SrEditLvlActorDlg(pNewInfo, m_pDlgHandler, GetInputRecord()->GetFormID());

	if (Result == SR_LVLEDITDLG_RESULT_CANCEL || Result == SR_LVLEDITDLG_RESULT_DELETE) 
	{
		m_LvlListInfo.Delete(pNewInfo);
		return;
	}

	AddItemList(pNewInfo);
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
	std::vector<int> IndexList;
	POSITION         ListPos;
	int				 ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
		IndexList.push_back(ListIndex);
	}

	while (IndexList.size() > 0)
	{
		ListIndex = IndexList.back();
		IndexList.pop_back();

		m_ItemList.DeleteItem(ListIndex);
		m_LvlListInfo.Delete(ListIndex);
	}

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
	POSITION			ListPos;
	CString				Buffer;
	int					ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
		pCustomData = m_ItemList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		pItem = SrCastClassNull(CSrLvloSubrecord, pCustomData->Subrecords[0]);
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
	POSITION			ListPos;
	CString				Buffer;
	int					ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
		pCustomData = m_ItemList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		pItem = SrCastClassNull(CSrLvloSubrecord, pCustomData->Subrecords[0]);
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
	POSITION			ListPos;
	CString				Buffer;
	int					ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
	    pCustomData = m_ItemList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		pItem = SrCastClassNull(CSrLvloSubrecord, pCustomData->Subrecords[0]);
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
	POSITION			ListPos;
	CString				Buffer;
	int					ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
		pCustomData = m_ItemList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		pItem = SrCastClassNull(CSrLvloSubrecord, pCustomData->Subrecords[0]);
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

	if (pWnd != NULL) m_pDlgHandler->EditRecord(pRecord);
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
	return 0;
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
  
	if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) 
	{
		*pResult = OnDropCustomData(*pDropItems);
	}
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
	CSrLvloSubrecord*	pItem;
	srrlcustomdata_t*	pCustomData;
	srlvllistinfo_t*	pInfo;
	dword				Index;

		/* Check all custom data dropped */
	for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
	{
		pCustomData = DropItems.pCustomDatas->GetAt(Index);

		if (pCustomData->pRecord == NULL) return (SRRL_DROPCHECK_ERROR);

			/* Check for dragging another lvlo record */
		if (!SrIsValidLvlnRecord(pCustomData->pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);
		pItem = SrCastClassNull(CSrLvloSubrecord, pCustomData->Subrecords[0]);
	    if (pItem == NULL) return (SRRL_DROPCHECK_ERROR);
    
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

		pInfo = m_LvlListInfo.AddNew();
		pInfo->CopyFrom(pCustomData->Subrecords);
		AddItemList(pInfo);
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
	srlvllistinfo_t*	pInfo;
	CSrRecord*			pRecord;
	dword				Index;

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

		pInfo = m_LvlListInfo.AddNew();
		pInfo->InitializeNew(SR_NAME_LVLN);
		pInfo->SetFormID(pRecord->GetFormID());
		AddItemList(pInfo);
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
void CSrLvlnView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) 
{
	srrlkeydown_t* pNotify = (srrlkeydown_t *) pHdr;
	*lResult = 0;
	
	if (pNotify->KeyDown.nVKey == VK_DELETE || pNotify->KeyDown.nVKey == VK_BACK) 
	{
		if (!pNotify->Ctrl && !pNotify->Alt) OnLvllistDelete();
	}
	else if (pNotify->KeyDown.nVKey == VK_ADD) 
	{
		if (pNotify->Shift) 
			OnAddCount();
		else
			OnAddLevel();
	}
	else if (pNotify->KeyDown.nVKey == VK_SUBTRACT) 
	{
		if (pNotify->Shift) 
			OnMinusCount();
		else
			OnMinusLevel();
	}

}
/*===========================================================================
 *		End of Class Event CSrLvlnView::OnKeydownItemList()
 *=========================================================================*/
