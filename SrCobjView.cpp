/*===========================================================================
 *
 * File:		SrCobjView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srcobjview.h"
#include "dialogs/sreditdlghandler.h"
#include "SrConditionDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrCobjView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrCobjView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrCobjView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_RESULTITEM, &CSrCobjView::OnBnClickedEditResultitem)
	ON_BN_CLICKED(IDC_SELECTRESULTITEM_BUTTON, &CSrCobjView::OnBnClickedSelectresultitemButton)
	ON_BN_CLICKED(IDC_EDIT_CRAFTSTATION, &CSrCobjView::OnBnClickedEditCraftstation)
	ON_BN_CLICKED(IDC_SELECTCRAFTSTATION_BUTTON, &CSrCobjView::OnBnClickedSelectcraftstationButton)
	ON_EN_CHANGE(IDC_RESULTITEM, &CSrCobjView::OnEnChangeResultItem)
	ON_WM_CTLCOLOR()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_COMPONENT_EDIT, &CSrCobjView::OnComponentEdit)
	ON_COMMAND(ID_COMPONENT_DELETE, &CSrCobjView::OnComponentDelete)
	ON_COMMAND(ID_COMPONENT_ADD, &CSrCobjView::OnComponentAdd)
	ON_BN_CLICKED(IDC_EDIT_COMPONENT, &CSrCobjView::OnBnClickedEditComponent)
	ON_BN_CLICKED(IDC_SELECTCOMPONENT_BUTTON, &CSrCobjView::OnBnClickedSelectcomponentButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_COMPONENT_LIST, &CSrCobjView::OnLvnItemchangedComponentList)
	ON_EN_CHANGE(IDC_COMPONENT, &CSrCobjView::OnEnChangeComponent)
	ON_BN_CLICKED(ID_ADD_BUTTON, &CSrCobjView::OnBnClickedAddButton)
	ON_BN_CLICKED(ID_DELETE_BUTTON2, &CSrCobjView::OnBnClickedDeleteButton2)
	ON_COMMAND(ID_COMPONENT_DECREASE, &CSrCobjView::OnComponentDecrease)
	ON_COMMAND(ID_COMPONENT_INCREASE, &CSrCobjView::OnComponentIncrease)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_CRAFTSTATION, OnDropCraftStation)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_CRAFTSTATION, OnDropCraftStation)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RESULTITEM, OnDropResultItem)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RESULTITEM, OnDropResultItem)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_COMPONENT, OnDropComponent)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_COMPONENT, OnDropComponent)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_COMPONENT_LIST, OnDropComponentList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_COMPONENT_LIST, OnDropComponentList)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrCobjView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrCobjView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_RESULTITEM,			IDC_RESULTITEM,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_RESULTCOUNT,		IDC_RESULTCOUNT,		 8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CONDITIONCOUNT,		IDC_CONDITION_BUTTON,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_STATION,			IDC_CRAFTSTATION,		128,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_ComponentListInit[] = {
	{ SR_FIELD_COMPONENT,		150,		LVCFMT_CENTER },
	{ SR_FIELD_COMPFORMID,		5,			LVCFMT_CENTER },
	{ SR_FIELD_COMPITEMNAME,	150,		LVCFMT_CENTER },
	{ SR_FIELD_COMPCOUNT,		50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_ComponentFields[] = {
	{ "Component",	SR_FIELD_COMPONENT,		0, NULL },
	{ "FormID",		SR_FIELD_COMPFORMID,	0, NULL },
	{ "Item Name",	SR_FIELD_COMPITEMNAME,	0, NULL },
	{ "Count",		SR_FIELD_COMPCOUNT,		0, NULL },	
	{ NULL,			SR_FIELD_NONE,			0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Constructor
 *
 *=========================================================================*/
CSrCobjView::CSrCobjView() : CSrRecordDialog(CSrCobjView::IDD) 
{
  m_ResultItemIDCheck = SR_CHECKRESULT_NOCHANGE;
  m_ComponentIDCheck  = SR_CHECKRESULT_NOCHANGE;
  m_InitialSetData = false;

  m_AcceleratorID = IDR_COMPONENT_ACCEL;
}
/*===========================================================================
 *		End of Class CSrCobjView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Destructor
 *
 *=========================================================================*/
CSrCobjView::~CSrCobjView() 
{

}
/*===========================================================================
 *		End of Class CSrCobjView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrCobjView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_Conditions);
	DDX_Control(pDX, IDC_RESULTITEM, m_ResultItem);
	DDX_Control(pDX, IDC_RESULTCOUNT, m_ResultCount);
	DDX_Control(pDX, IDC_COMPONENT_LIST, m_ComponentList);
	DDX_Control(pDX, IDC_CRAFTSTATION, m_CraftStation);
	DDX_Control(pDX, IDC_COMPONENT, m_Component);
	DDX_Control(pDX, IDC_COMPONENTCOUNT, m_ComponentCount);
	DDX_Control(pDX, IDC_EDIT_COMPONENT, m_EditComponentButton);
	DDX_Control(pDX, IDC_SELECTCOMPONENT_BUTTON, m_SelectComponentButton);
	DDX_Control(pDX, ID_DELETE_BUTTON2, m_DeleteButton);
	DDX_Control(pDX, ID_ADD_BUTTON, m_AddButton);
}
/*===========================================================================
 *		End of Class Method CSrCobjView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrCobjView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrCobjView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrCobjView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrCobjView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrCobjView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	m_IsInitialized = false;
	m_pCurrentComponent = NULL;

	m_ResultItemIDCheck = SR_CHECKRESULT_NOCHANGE;
	m_ComponentIDCheck  = SR_CHECKRESULT_NOCHANGE;

	if (GetInputRecord() != NULL) GetInputRecord()->GetField(m_OrigResultItem, SR_FIELD_RESULTITEM);

		/* Setup the list */
	m_ComponentList.SetListName("ComponentList");
	m_ComponentList.SetDragEnable(true);
	m_ComponentList.DefaultSettings();
	m_ComponentList.SetupCustomList(s_ComponentListInit, NULL, s_ComponentFields);
	m_ComponentList.SetOwner(this);
	m_ComponentList.SetColorEnable(false);
	m_ComponentList.SetDragType(SR_RLDRAG_CUSTOM);
	m_ComponentList.SetSortEnable(false);
	m_ComponentList.SetActivateType(SR_RLACTIVATE_NONE);

	m_ComponentsChanged = false;
	 
	CopyComponents();
	EnableComponentControls(false);
	SetControlData();

	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnInitialUpdate()
 *=========================================================================*/


void CSrCobjView::CopyComponents (void)
{
	CSrSubrecord*		pSubrecord;
	CSrCntoSubrecord*	pComponent;
	int					Position;
		
	m_Components.Destroy();
	if (GetInputRecord() == NULL) return;

	pSubrecord = GetInputRecord()->FindFirstSubrecord(SR_NAME_CNTO, Position);

	while (pSubrecord != NULL)
	{
		pComponent = SrCastClass(CSrCntoSubrecord, pSubrecord);

		if (pComponent != NULL)
		{
			CSrCntoSubrecord* pNewComp = new CSrCntoSubrecord;
			pNewComp->Copy(pComponent);
			m_Components.Add(pNewComp);
		}

		pSubrecord = GetInputRecord()->FindNextSubrecord(SR_NAME_CNTO, Position);
	}

}


void CSrCobjView::GetControlData (void)
{
	GetCurrentComponent();

	if (m_ComponentsChanged) 
	{
		CSrRecord* pRecord = GetOutputRecord();
		CSrCobjRecord* pRecipe = SrCastClassNull(CSrCobjRecord, pRecord);
		if (pRecipe == NULL) return;

		pRecipe->DeleteSubrecords(SR_NAME_CNTO);
	
		for (dword i = 0; i < m_Components.GetSize(); ++i)
		{
			CSrCntoSubrecord* pComponent = m_Components[i];
			CSrSubrecord* pNewComp = pRecipe->AddNewSubrecord(SR_NAME_CNTO);
			pNewComp->Copy(pComponent); 
		}

		pRecipe->UpdateComponentCount();		
	}


	CSrRecordDialog::GetControlData();
}


void CSrCobjView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	SetComponentList();
}


void CSrCobjView::SetComponentList (void)
{
	CSrCntoSubrecord*     pComponent;

	m_ComponentList.DeleteAllItems();
	
	for (dword i = 0; i < m_Components.GetSize(); ++i) 
	{
		pComponent = m_Components[i];
		AddComponentList(pComponent);
	}

	m_ComponentList.SelectRecord(0);
}

/*===========================================================================
 *
 * Class CSrCobjView Method - int AddComponentList (pCondition);
 *
 *=========================================================================*/
int CSrCobjView::AddComponentList (CSrCntoSubrecord* pComponent) 
{
  srrlcustomdata_t	CustomData;
  CString           Buffer;
  int		        ListIndex;

  CustomData.pRecord = GetInputRecord();

		/* Setup the custom data structure for the list */
  CustomData.Subrecords.Add(pComponent);
  
	/* Add the custom record to the list */
  ListIndex = m_ComponentList.AddCustomRecord(CustomData);
  if (ListIndex < 0) return (-1);

  UpdateComponentList(ListIndex, false);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrCobjView::AddComponentList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Method - void UpdateComponentList (ListIndex, Update);
 *
 *=========================================================================*/
void CSrCobjView::UpdateComponentList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t*	pCustomData;
	srformid_t			FormID;
	CString				Buffer;

	if (GetInputRecord() == NULL) return;

	pCustomData = m_ComponentList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	if (Update) m_ComponentList.UpdateRecord(ListIndex);

	CSrCntoSubrecord* pCondition = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
	if (pCondition == NULL) return;

	FormID = pCondition->GetFormID();
	CSrRecord* pRecord = GetInputRecord()->GetParent()->FindFormID(FormID);
	CSrIdRecord* pIdRecord = SrCastClassNull(CSrIdRecord, pRecord);

	if (pIdRecord != NULL) 
	{		
		m_ComponentList.SetCustomField(ListIndex, SR_FIELD_COMPONENT, pIdRecord->GetEditorID());
		CSrItem1Record* pItem1Record = SrCastClassNull(CSrItem1Record, pRecord);
		if (pItem1Record != NULL) m_ComponentList.SetCustomField(ListIndex, SR_FIELD_COMPITEMNAME, pItem1Record->GetItemName());
	}
  
}
/*===========================================================================
 *		End of Class Method CSrCobjView::UpdateComponentList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CSrCobjView::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CSrRecordDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT && (pWnd == &m_ResultItem || pWnd == &m_Component)) 
	{
		int CheckValue = (pWnd == &m_ResultItem) ? m_ResultItemIDCheck : m_ComponentIDCheck;

		switch (CheckValue) {
		case SR_CHECKRESULT_NOCHANGE:
			hBrush = CreateSolidBrush(RGB(255,255,255));
			pDC->SetBkColor(RGB(255,255,255));
			break;
		case SR_CHECKRESULT_OK:
			hBrush = CreateSolidBrush(RGB(204,255,204));
			pDC->SetBkColor(RGB(204,255,204));
			break;
		case SR_CHECKRESULT_ERROR:
			hBrush = CreateSolidBrush(RGB(255,204,204));
			pDC->SetBkColor(RGB(255,204,204));
			break;
		}
	}

	return (hBrush);
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnCtlColor()
 *=========================================================================*/


void CSrCobjView::OnBnClickedEditResultitem()
{
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pDlgHandler == NULL) return;
	m_ResultItem.GetWindowText(Buffer);

	if (Buffer.IsEmpty()) 
	{
		//Do what?
	}
	else 
	{
		pRecord = m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
	}
}


void CSrCobjView::OnBnClickedSelectresultitemButton()
{
	CString Buffer;
	bool    Result;

	m_ResultItem.GetWindowText(Buffer);
	
	Result = m_pDlgHandler->SelectComponent(Buffer);
	if (!Result) return;

	m_ResultItem.SetWindowText(Buffer);
}


void CSrCobjView::OnBnClickedEditCraftstation()
{
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pDlgHandler == NULL) return;
	m_CraftStation.GetWindowText(Buffer);

	if (Buffer.IsEmpty()) 
	{
		m_pDlgHandler->EditNewRecord(SR_NAME_KYWD);
	}
	else 
	{
		pRecord = m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
	}
}


void CSrCobjView::OnBnClickedSelectcraftstationButton()
{
	CString Buffer;
	bool    Result;

	m_CraftStation.GetWindowText(Buffer);
	
	Result = m_pDlgHandler->SelectKeyword(Buffer, "Crafting");
	if (!Result) return;

	m_CraftStation.SetWindowText(Buffer);
}


void CSrCobjView::OnEnChangeResultItem()
{
	CString Buffer;
	int     CurrentCheck = m_ResultItemIDCheck;

	if (m_pRecordHandler == NULL) return;
	m_ResultItem.GetWindowText(Buffer);

	CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);

	if (Buffer.Compare(m_OrigResultItem) == 0)
		m_ResultItemIDCheck = SR_CHECKRESULT_NOCHANGE;
	else if (pRecord == NULL)
		m_ResultItemIDCheck = SR_CHECKRESULT_ERROR;
	else
		m_ResultItemIDCheck = SR_CHECKRESULT_OK;

	if (CurrentCheck != m_ResultItemIDCheck) m_ResultItem.RedrawWindow();
}


int CSrCobjView::OnPreSaveRecord (void)
{
	CString Buffer;

	if (m_pRecordHandler == NULL) return SR_RESULT_ERROR;
	m_ResultItem.GetWindowText(Buffer);
	Buffer.Trim();

	if (!Buffer.IsEmpty()) 
	{
		CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);

		if (pRecord == NULL)
		{
			AddSrGeneralError("Unknown editor ID '%s'!", Buffer);
			return SR_RESULT_ERROR;
		}
	}

	if (m_pCurrentComponent != NULL)
	{
		m_Component.GetWindowText(Buffer);
		CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);

		if (pRecord == NULL)
		{
			AddSrGeneralError("Unknown editor ID '%s'!", Buffer);
			return SR_RESULT_ERROR;
		}
	}

	return CSrRecordDialog::OnPreSaveRecord();
}


void CSrCobjView::OnContextMenu(CWnd* pWnd, CPoint Point)
{
	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;

	if (pWnd->GetDlgCtrlID() == IDC_COMPONENT_LIST) 
	{
		Result = Menu.LoadMenu(IDR_COMPONENT_MENU);
		if (!Result) return;

		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;

		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
		
}


CSrCntoSubrecord* CSrCobjView::GetSelectedComponent (void)
{
	int SelIndex = m_ComponentList.GetSelectedItem();
	if (SelIndex < 0) return NULL;
		
	srrlcustomdata_t* pCustomData = m_ComponentList.GetCustomData(SelIndex);
	if (pCustomData == NULL) return NULL;

	CSrCntoSubrecord* pComponent = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
	return pComponent;
}


void CSrCobjView::OnComponentEdit()
{
	CSrCntoSubrecord* pComponent = GetSelectedComponent();
	if (pComponent == NULL) return;
}


void CSrCobjView::OnComponentDelete()
{
	CSrCntoSubrecord* pComponent = GetSelectedComponent();
	if (pComponent == NULL) return;

	GetCurrentComponent();
	m_pCurrentComponent = NULL;

	int ListIndex = m_ComponentList.GetSelectedItem();
	if (ListIndex < 0) return;
	m_Components.Delete(ListIndex);

	SetComponentList();
	m_ComponentList.SelectRecord(ListIndex);
}


void CSrCobjView::OnComponentAdd()
{
	CSrCntoSubrecord* pComponent = GetSelectedComponent();

	GetCurrentComponent();

	CSrCntoSubrecord* pNewComp = new CSrCntoSubrecord;
	m_Components.Add(pNewComp);
	pNewComp->InitializeNew();

	SetComponentList();
	m_ComponentList.SelectRecord(m_ComponentList.GetItemCount() - 1);
}


void CSrCobjView::OnBnClickedEditComponent()
{
	CString Buffer;

	if (m_pDlgHandler == NULL) return;
	m_Component.GetWindowText(Buffer);

	CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);
	if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
}


void CSrCobjView::OnBnClickedSelectcomponentButton()
{
	CString Buffer;

	m_Component.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectComponent(Buffer);
	if (!Result) return;

	m_Component.SetWindowText(Buffer);
}


void CSrCobjView::OnLvnItemchangedComponentList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetCurrentComponent();

	srrlcustomdata_t* pCustomData = (srrlcustomdata_t *) m_ComponentList.GetItemData(pNMLV->iItem);

	if (pCustomData == NULL)
	{
		SetCurrentComponent(NULL);
	}
	else
	{
		CSrCntoSubrecord* pComponent = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
		SetCurrentComponent(pComponent);
	}
}


void CSrCobjView::EnableComponentControls (const bool Enable)
{
	m_Component.EnableWindow(Enable);
	m_ComponentCount.EnableWindow(Enable);
	m_EditComponentButton.EnableWindow(Enable);
	m_SelectComponentButton.EnableWindow(Enable);
	m_DeleteButton.EnableWindow(Enable);
}


void CSrCobjView::SetCurrentComponent (CSrCntoSubrecord* pComponent)
{
	CString Buffer;

	EnableComponentControls(pComponent != NULL);

	if (pComponent == NULL)
	{
		m_Component.SetWindowText("");
		m_ComponentCount.SetWindowText("");
		m_pCurrentComponent = NULL;
		return;
	}

	m_pCurrentComponent = pComponent;

	m_OrigComponent = m_pRecordHandler->GetEditorID(pComponent->GetFormID());
	m_ComponentIDCheck = SR_CHECKRESULT_NOCHANGE;
	m_Component.SetWindowText(m_OrigComponent);

	Buffer.Format("%d", pComponent->GetCount());
	m_ComponentCount.SetWindowText(Buffer);
}


void CSrCobjView::GetCurrentComponent (void)
{
	CString Buffer;

	if (m_pCurrentComponent == NULL) return;
	m_ComponentsChanged = true;

	m_Component.GetWindowText(Buffer);
	CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);

	if (pRecord != NULL)
	{
		m_pCurrentComponent->SetFormID(pRecord->GetFormID());
	}
	else
	{
		m_pCurrentComponent->SetFormID(0);
	}

	m_ComponentCount.GetWindowText(Buffer);
	m_pCurrentComponent->SetCount(atoi(Buffer));

	for (int i = 0; i < m_ComponentList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = (srrlcustomdata_t *) m_ComponentList.GetItemData(i);
		if (pCustomData == NULL) continue;

		CSrCntoSubrecord* pComponent = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
		if (pComponent == NULL) continue;
		if (pComponent != m_pCurrentComponent) continue;

		UpdateComponentList(i, true);
		break;
	 }

}


void CSrCobjView::OnEnChangeComponent()
{
	CString Buffer;
	int     CurrentCheck = m_ComponentIDCheck;

	if (m_pRecordHandler == NULL) return;
	m_Component.GetWindowText(Buffer);

	CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);

	if (Buffer.Compare(m_OrigComponent) == 0)
		m_ComponentIDCheck = SR_CHECKRESULT_NOCHANGE;
	else if (pRecord == NULL)
		m_ComponentIDCheck = SR_CHECKRESULT_ERROR;
	else
		m_ComponentIDCheck = SR_CHECKRESULT_OK;

	if (CurrentCheck != m_ComponentIDCheck) m_Component.RedrawWindow();
}


void CSrCobjView::OnBnClickedAddButton()
{
	OnComponentAdd();
}


void CSrCobjView::OnBnClickedDeleteButton2()
{
	OnComponentDelete();
}


void CSrCobjView::OnComponentDecrease()
{
	CWnd* pWnd = GetFocus();
	if (pWnd != &m_ComponentList && pWnd != &m_Component && pWnd != &m_ComponentCount) return;

	CSrCntoSubrecord* pComp = GetSelectedComponent();
	if (pComp == NULL) return;
	int ListIndex = m_ComponentList.GetSelectedItem();

	GetCurrentComponent();

	int NewCount = pComp->GetCount() - 1;
	if (NewCount >= 0) pComp->SetCount(NewCount);
	UpdateComponentList(ListIndex, true);
	SetCurrentComponent(pComp);
}


void CSrCobjView::OnComponentIncrease()
{
	CWnd* pWnd = GetFocus();
	if (pWnd != &m_ComponentList && pWnd != &m_Component && pWnd != &m_ComponentCount) return;

	CSrCntoSubrecord* pComp = GetSelectedComponent();
	if (pComp == NULL) return;
	int ListIndex = m_ComponentList.GetSelectedItem();

	GetCurrentComponent();

	pComp->SetCount(pComp->GetCount() + 1);
	UpdateComponentList(ListIndex, true);
	SetCurrentComponent(pComp);
}


/*===========================================================================
 *
 * Class CSrCobjView Event - void OnDropCraftStation (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrCobjView::OnDropCraftStation (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrKywdRecord*     pKeyword;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  
  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_KYWD) return;
  pKeyword = SrCastClass(CSrKywdRecord, pRecord);
  if (pKeyword == NULL) return;
  if (strnicmp(pKeyword->GetEditorID(), "Crafting", 8) == 0) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_CraftStation.SetWindowText(pKeyword->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnDropCraftStation()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - void OnDropResultItem (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrCobjView::OnDropResultItem (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrIdRecord*		 pIdRecord;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  
  pRecord = pDropItems->pRecords->GetAt(0);
    
  pIdRecord = SrCastClass(CSrIdRecord, pRecord);
  if (pIdRecord == NULL) return;
  if (!SrIsRecipeResult(pIdRecord->GetRecordType())) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_ResultItem.SetWindowText(pIdRecord->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnDropResultItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - void OnDropComponent (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrCobjView::OnDropComponent (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrIdRecord*		 pIdRecord;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  if (m_pCurrentComponent == NULL) return;

  pRecord = pDropItems->pRecords->GetAt(0);
    
  pIdRecord = SrCastClass(CSrIdRecord, pRecord);
  if (pIdRecord == NULL) return;
  if (!SrIsRecipeComponent(pIdRecord->GetRecordType())) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_Component.SetWindowText(pIdRecord->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnDropComponent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - int OnDropCustomComponentData (DropItems);
 *
 *=========================================================================*/
int CSrCobjView::OnDropCustomComponentData (srrldroprecords_t& DropItems) 
{
  CSrCntoSubrecord*		pComponent;
  CSrCntoSubrecord*		pNewComponent;
  srrlcustomdata_t*		pCustomData;
  CSrSubrecord*			pNewSubrecord; 
  dword					Index;

  GetCurrentComponent();

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
  {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (SRRL_DROPCHECK_ERROR);

		/* Check for dragging another component subrecord */
    pComponent = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
    if (pComponent == NULL) return SRRL_DROPCHECK_ERROR;

		/* If we're just checking */
    if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

	pNewSubrecord = pCustomData->pRecord->CreateSubrecord(SR_NAME_CNTO);
	pNewComponent = SrCastClassNull(CSrCntoSubrecord, pNewSubrecord);

	if (pNewComponent == NULL) 
	{
		delete pNewComponent;
		continue;
	}

	m_Components.Add(pNewComponent);
	pNewComponent->Copy(pComponent);
    AddComponentList(pNewComponent);
	m_ComponentsChanged = true;
  }

  return SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnDropCustomComponentData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - int OnDropRecordComponentData (DropItems);
 *
 *=========================================================================*/
int CSrCobjView::OnDropRecordComponentData (srrldroprecords_t& DropItems) 
{
  CSrCntoSubrecord*		pNewComponent;
  CSrRecord*			pRecord;
  CSrSubrecord*			pNewSubrecord; 
  dword					Index;

  GetCurrentComponent();

	/* Check all record data dropped */
  for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) 
  {
	pRecord = DropItems.pRecords->GetAt(Index);
    if (pRecord == NULL) continue;

	if (!SrIsRecipeComponent(pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);

	if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

	pNewSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_CNTO);
	pNewComponent = SrCastClassNull(CSrCntoSubrecord, pNewSubrecord);

	if (pNewComponent == NULL) 
	{
		delete pNewComponent;
		continue;
	}		

	pNewComponent->InitializeNew();
	pNewComponent->SetCount(1);
	pNewComponent->SetFormID(pRecord->GetFormID());
	m_Components.Add(pNewComponent);
	
	m_ComponentsChanged = true;
	AddComponentList(pNewComponent);
  }

  return SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnDropRecordComponentData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCobjView Event - void OnDropComponentList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrCobjView::OnDropComponentList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;

  *pResult = SRRL_DROPCHECK_ERROR;
  
  if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) 
  {
    *pResult = OnDropCustomComponentData(*pDropItems);
  }
  else if (pDropItems->pRecords != NULL) 
  {
    *pResult =  OnDropRecordComponentData(*pDropItems);
  } 

}
/*===========================================================================
 *		End of Class Event CSrCobjView::OnDropEffectList()
 *=========================================================================*/