/*===========================================================================
 *
 * File:		SrArmoView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srarmoview.h"
#include "dialogs/sreditdlghandler.h"
#include "srbodypartslistdlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrArmoView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrArmoView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrArmoView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_EQUIPSLOT, &CSrArmoView::OnBnClickedEditEquipslot)
	ON_BN_CLICKED(IDC_SELECTEQUIPSLOT_BUTTON, &CSrArmoView::OnBnClickedSelectequipslotButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EQUIPSLOT, OnDropEquipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EQUIPSLOT, OnDropEquipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EQUIPSLOT, OnDropEquipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EQUIPSLOT, OnDropEquipSlot)

	ON_BN_CLICKED(IDC_EDIT_MATERIAL, &CSrArmoView::OnBnClickedEditMaterial)
	ON_BN_CLICKED(IDC_SELECTMATERIAL_BUTTON, &CSrArmoView::OnBnClickedSelectMaterial)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MATERIAL, OnDropMaterial)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EQUIPSLOT, OnDropMaterial)

	ON_BN_CLICKED(IDC_EDIT_TEMPLATE, &CSrArmoView::OnBnClickedEditTemplate)
	ON_BN_CLICKED(IDC_SELECTTEMPLATE_BUTTON, &CSrArmoView::OnBnClickedSelectTemplate)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_TEMPLATE, OnDropTemplate)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_TEMPLATE, OnDropTemplate)

	ON_BN_CLICKED(IDC_EDIT_RACE, &CSrArmoView::OnBnClickedEditRace)
	ON_BN_CLICKED(IDC_SELECTRACE_BUTTON, &CSrArmoView::OnBnClickedSelectRace)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RACE, OnDropRace)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RACE, OnDropRace)

	ON_BN_CLICKED(IDC_EDIT_IMPACTDATA, &CSrArmoView::OnBnClickedEditImpactData)
	ON_BN_CLICKED(IDC_SELECTIMPACTDATA_BUTTON, &CSrArmoView::OnBnClickedSelectImpactData)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMPACTDATA, OnDropImpactData)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMPACTDATA, OnDropImpactData)

	ON_BN_CLICKED(IDC_BODYPARTS, &CSrArmoView::OnBnClickedBodyparts)

	ON_BN_CLICKED(IDC_ADD_ARMAMODEL, &CSrArmoView::OnBnClickedAddArmamodel)
	ON_BN_CLICKED(IDC_EDIT_ARMAMODEL, &CSrArmoView::OnBnClickedEditArmamodel)
	ON_BN_CLICKED(IDC_DEL_ARMAMODEL, &CSrArmoView::OnBnClickedDelArmamodel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ARMAMODELS, OnDropArmaModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ARMAMODELS, OnDropArmaModel)
	ON_LBN_DBLCLK(IDC_ARMAMODELS, &CSrArmoView::OnLbnDblclkArmamodels)

	ON_COMMAND(ID_ARMAMENU_ADD, &CSrArmoView::OnArmamenuAdd)
	ON_COMMAND(ID_ARMAMENU_EDIT, &CSrArmoView::OnArmamenuEdit)
	ON_COMMAND(ID_ARMAMENU_EDITBASE, &CSrArmoView::OnArmamenuEditBase)
	ON_COMMAND(ID_ARMAMENU_DELETE, &CSrArmoView::OnArmamenuDelete)
	ON_UPDATE_COMMAND_UI(ID_ARMAMENU_EDIT, &CSrArmoView::OnUpdateArmamenuEdit)
	ON_UPDATE_COMMAND_UI(ID_ARMAMENU_EDITBASE, &CSrArmoView::OnUpdateArmamenuEdit)
	ON_UPDATE_COMMAND_UI(ID_ARMAMENU_DELETE, &CSrArmoView::OnUpdateArmamenuEdit)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrArmoView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrArmoView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,	IDC_DESCRIPTION,	256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,			IDC_WEIGHT,			16,		IDS_TT_WEIGHT)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTMENT,	IDC_ENCHANTMENT,	128,	IDS_TT_ENCHANTMENT)
	ADD_SRRECUIFIELDS( SR_FIELD_RATING,			IDC_RATING,	        8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPE,			IDC_ARMORTYPE,	    32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
	ADD_SRRECUIFIELDS( SR_FIELD_EQUIPSLOT,		IDC_EQUIPSLOT,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MATERIAL,		IDC_MATERIAL,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_TEMPLATE,		IDC_TEMPLATE,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DROPSOUND,		IDC_DROPSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PICKUPSOUND,	IDC_PICKUPSOUND,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_RACE,			IDC_RACE,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PLAYABLE,		IDC_PLAYABLE,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IMPACTDATA,		IDC_IMPACTDATA,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_BODYPARTS,		IDC_BODYPARTS,		256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_BOUNDS,			IDC_BOUNDS,			256,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrArmoView Constructor
 *
 *=========================================================================*/
CSrArmoView::CSrArmoView() : CSrRecordDialog(CSrArmoView::IDD) 
{
	m_InitialSetData = false;
	m_pScriptList = &m_ScriptList;
}
/*===========================================================================
 *		End of Class CSrArmoView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrArmoView Destructor
 *
 *=========================================================================*/
CSrArmoView::~CSrArmoView() 
{
}
/*===========================================================================
 *		End of Class CSrArmoView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrArmoView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrArmoView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_ENCHANTMENT, m_Enchantment);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_EQUIPSLOT, m_EquipSlot);
	DDX_Control(pDX, IDC_PLAYABLE, m_Playable);
	DDX_Control(pDX, IDC_ARMORTYPE, m_ArmorType);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_PICKUPSOUND, m_PickupSound);
	DDX_Control(pDX, IDC_DROPSOUND, m_DropSound);
	DDX_Control(pDX, IDC_TEMPLATE, m_Template);
	DDX_Control(pDX, IDC_RACE, m_Race);
	DDX_Control(pDX, IDC_MATERIAL, m_Material);
	DDX_Control(pDX, IDC_IMPACTDATA, m_ImpactData);
	DDX_Control(pDX, IDC_RATING, m_Rating);
	DDX_Control(pDX, IDC_BODYPARTS, m_BodyParts);
	DDX_Control(pDX, IDC_ARMAMODELS, m_ArmaModels);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_ScriptList);
	DDX_Control(pDX, IDC_BOUNDS, m_Bounds);
}
/*===========================================================================
 *		End of Class Method CSrArmoView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrArmoView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrArmoView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrArmoView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrArmoView Diagnostics
 *=========================================================================*/


void CSrArmoView::GetControlData (void) 
{
	CString			Buffer;
	CSrRecord*		pRecord = GetOutputRecord();
	CSrArmoRecord*	pArmor = SrCastClassNull(CSrArmoRecord, pRecord);

	if (pArmor != NULL)
	{
		m_BodyParts.GetWindowText(Buffer);
		pArmor->SetBodyParts(Buffer);
	}

	CSrRecordDialog::GetControlData();

	GetOutputRecord()->DeleteSubrecords(SR_NAME_MODL);

	for (int i = 0; i < m_ArmaModels.GetCount(); ++i)
	{
		m_ArmaModels.GetText(i, Buffer);
		CSrIdRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;

		CSrSubrecord* pSubrecord = GetOutputRecord()->AddInitNewSubrecord(SR_NAME_MODL);
		CSrFormidSubrecord* pFormid = SrCastClassNull(CSrFormidSubrecord, pSubrecord);
		if (pFormid != NULL) pFormid->SetValue(pRecord->GetFormID());
	}
}


/*===========================================================================
 *
 * Class CSrArmoView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrArmoView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	::SrFillComboList(m_ArmorType, s_SrArmorTypes, 0);

	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrArmoView::OnInitialUpdate()
 *=========================================================================*/


void CSrArmoView::SetControlData (void)
{
	CSrSubrecord* pSubrecord;
	int           Position;

	CSrRecordDialog::SetControlData();

	m_ArmaModels.ResetContent();
	pSubrecord = GetInputRecord()->FindFirstSubrecord(SR_NAME_MODL, Position);

	while (pSubrecord)
	{
		CSrFormidSubrecord* pFormid = SrCastClass(CSrFormidSubrecord, pSubrecord);

		if (pFormid != NULL)
		{
			const SSCHAR* pString = m_pRecordHandler->GetEditorID(pFormid->GetValue());
			if (pString) m_ArmaModels.AddString(pString);
		}

		pSubrecord = GetInputRecord()->FindNextSubrecord(SR_NAME_MODL, Position);
	}

}


 void CSrArmoView::OnBnClickedEditEquipslot()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EquipSlot, SR_NAME_EQUP);
 }


 void CSrArmoView::OnBnClickedSelectequipslotButton()
 {
 	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_EquipSlot, SR_NAME_EQUP, &CSrEqupRecord::s_FieldMap);
 }
 

void CSrArmoView::OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_EquipSlot, SR_NAME_EQUP, 1);
}


void CSrArmoView::OnBnClickedEditMaterial()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Material, SR_NAME_MATT);
 }


 void CSrArmoView::OnBnClickedSelectMaterial()
 {
 	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Material, SR_NAME_MATT, &CSrMattRecord::s_FieldMap);
 }
 

void CSrArmoView::OnDropMaterial (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Material, SR_NAME_MATT, 1);
}


void CSrArmoView::OnBnClickedEditRace()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Race, SR_NAME_RACE);
 }


 void CSrArmoView::OnBnClickedSelectRace()
 {
 	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Race, SR_NAME_RACE, &CSrRaceRecord::s_FieldMap);
 }
 

void CSrArmoView::OnDropRace (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Race, SR_NAME_RACE, 1);
}


void CSrArmoView::OnBnClickedEditImpactData()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImpactData, SR_NAME_IPDS);
 }


 void CSrArmoView::OnBnClickedSelectImpactData()
 {
 	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImpactData, SR_NAME_IPDS, &CSrIpdsRecord::s_FieldMap);
 }
 

void CSrArmoView::OnDropImpactData (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_ImpactData, SR_NAME_IPDS, 1);
}


void CSrArmoView::OnDropArmaModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_ImpactData, SR_NAME_ARMA, true);
}


void CSrArmoView::OnBnClickedEditTemplate()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Template, SR_NAME_ARMO);
 }


 void CSrArmoView::OnBnClickedSelectTemplate()
 {
 	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Template, SR_NAME_ARMO, &CSrArmoRecord::s_FieldMap);
 }
 

void CSrArmoView::OnDropTemplate (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Template, SR_NAME_ARMO, 1);
}


void CSrArmoView::OnBnClickedBodyparts()
{
	CString Buffer;
	dword   PartsValue;

	m_BodyParts.GetWindowText(Buffer);
	GetSrBodyPartFlagValue(PartsValue, Buffer);

	if (!SrEditBodyPartsDlg(PartsValue)) return;

	m_BodyParts.SetWindowText(GetSrBodyPartFlagString(PartsValue));
}


void CSrArmoView::OnBnClickedAddArmamodel()
{
	CString Buffer;

	if (m_pDlgHandler == NULL) return;

	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_ARMA, &CSrArmaRecord::s_FieldMap)) return;
	m_ArmaModels.AddString(Buffer);
}


void CSrArmoView::OnBnClickedEditArmamodel()
{
	CString Buffer;

	if (m_pDlgHandler == NULL) return;

	int ListIndex = m_ArmaModels.GetCurSel();
	if (ListIndex < 0) return;

	m_ArmaModels.GetText(ListIndex, Buffer);

	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_ARMA, &CSrArmaRecord::s_FieldMap)) return;

	m_ArmaModels.DeleteString(ListIndex);
	m_ArmaModels.InsertString(ListIndex, Buffer);
}


void CSrArmoView::OnBnClickedDelArmamodel()
{
	int ListIndex = m_ArmaModels.GetCurSel();
	if (ListIndex >= 0) m_ArmaModels.DeleteString(ListIndex);
}


void CSrArmoView::OnLbnDblclkArmamodels()
{
	if ((GetKeyState(VK_CONTROL) & 0x8000) == 0)
	{
		OnBnClickedEditArmamodel();
	}
	else
	{
		OnArmamenuEditBase();
	}
}


void CSrArmoView::OnArmamenuAdd()
{
	OnBnClickedAddArmamodel();
}


void CSrArmoView::OnArmamenuEdit()
{
	OnBnClickedEditArmamodel();
}


void CSrArmoView::OnArmamenuEditBase()
{
	CString Buffer;

	if (m_pDlgHandler == NULL) return;
	m_pDlgHandler->EditRecordHelper(m_ArmaModels, SR_NAME_ARMA);
}


void CSrArmoView::OnArmamenuDelete()
{
	OnBnClickedDelArmamodel();
}


void CSrArmoView::OnUpdateArmamenuEdit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_ArmaModels.GetCurSel() >= 0);
}


void CSrArmoView::OnContextMenu(CWnd* pWnd, CPoint Point)
{
	if (pWnd == &m_ArmaModels)
	{
			/* Force select item on right-click */
		BOOL Outside;
		CPoint ClientPt(Point);
		m_ArmaModels.ScreenToClient(&ClientPt);
		UINT ListIndex = m_ArmaModels.ItemFromPoint(ClientPt, Outside);
		if (!Outside) m_ArmaModels.SetCurSel(ListIndex);

		CMenu Menu;
		BOOL Result = Menu.LoadMenu(IDR_ARMORARMA_MENU);
		if (!Result) return;
		
		CMenu* pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;
		
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
	else
	{
		CSrRecordDialog::OnContextMenu(pWnd, Point);
	}
}

