/*===========================================================================
 *
 * File:		SrEnchView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srenchview.h"
#include "dialogs/sreditdlghandler.h"
#include "../SrConditionDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrEnchView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEnchView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEnchView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_BASEENCHANT, &CSrEnchView::OnBnClickedEditBaseenchant)
	ON_BN_CLICKED(IDC_SELECTBASEENCHANT_BUTTON, &CSrEnchView::OnBnClickedSelectbaseenchantButton)
	ON_BN_CLICKED(IDC_EDIT_ITEMTYPES, &CSrEnchView::OnBnClickedEditItemtypes)
	ON_BN_CLICKED(IDC_SELECTITEMTYPES_BUTTON, &CSrEnchView::OnBnClickedSelectitemtypesButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EFFECT_LIST, &CSrEnchView::OnLvnItemchangedEffectList)
	ON_BN_CLICKED(IDC_CONDITION_BUTTON, &CSrEnchView::OnBnClickedConditionButton)
	ON_BN_CLICKED(IDC_EDIT_EFFECT, &CSrEnchView::OnBnClickedEditEffect)
	ON_BN_CLICKED(IDC_SELECTEFFECT_BUTTON, &CSrEnchView::OnBnClickedSelecteffectButton)
	ON_BN_CLICKED(ID_ADD_BUTTON, &CSrEnchView::OnBnClickedAddButton)
	ON_BN_CLICKED(ID_DELETE_BUTTON2, &CSrEnchView::OnBnClickedDeleteButton2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECTNAME, OnDropEffect)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECTNAME, OnDropEffect)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ITEMTYPES, OnDropItemTypes)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ITEMTYPES, OnDropItemTypes)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_BASEENCHANTMENT, OnDropBaseEnchant)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_BASEENCHANTMENT, OnDropBaseEnchant)
	ON_COMMAND(ID_CONDITIONRECORD_COPY, OnConditionrecordCopy)
	ON_COMMAND(ID_CONDITIONRECORD_PASTE, OnConditionrecordPaste)
	ON_COMMAND(ID_CONDITIONRECORD_DELETEALL, OnConditionrecordDeleteAll)
	ON_UPDATE_COMMAND_UI(ID_CONDITIONRECORD_COPY, OnUpdateConditionrecordCopy)
	ON_UPDATE_COMMAND_UI(ID_CONDITIONRECORD_PASTE, OnUpdateConditionrecordPaste)
	ON_UPDATE_COMMAND_UI(ID_CONDITIONRECORD_DELETEALL, OnUpdateConditionrecordDeleteAll)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrEnchView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_EffectListInit[] = {
	{ SR_FIELD_EFFECTNAME,		180,	LVCFMT_CENTER },
	{ SR_FIELD_EFFECTID,		5,		LVCFMT_CENTER },
	{ SR_FIELD_MAGNITUDE,		50,		LVCFMT_CENTER },
	{ SR_FIELD_AREA,			50,		LVCFMT_CENTER },
	{ SR_FIELD_DURATION,		50,		LVCFMT_CENTER },
	{ SR_FIELD_CONDITIONCOUNT,	50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_EffectFields[] = {
	{ "Effect",		SR_FIELD_EFFECTNAME,		0, NULL },
	{ "FormID",		SR_FIELD_EFFECTID,			0, NULL },
	{ "Magnitude",	SR_FIELD_MAGNITUDE,			0, NULL },
	{ "Area",		SR_FIELD_AREA,				0, NULL },	
	{ "Duration",	SR_FIELD_DURATION,			0, NULL },	
	{ "Conditions",	SR_FIELD_CONDITIONCOUNT,	0, NULL },	
	{ NULL,			SR_FIELD_NONE,				0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrEnchView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_BASEENCHANT,		IDC_BASEENCHANTMENT,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMTYPES,			IDC_ITEMTYPES,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTCOST,		IDC_COST,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CHARGE,				IDC_CHARGE,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPEA,				IDC_TYPEA,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPEB,				IDC_TYPEB,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPEC,				IDC_TYPEC,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPED,				IDC_TYPED,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_STAFFMOD,			IDC_STAFFMOD,			8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Constructor
 *
 *=========================================================================*/
CSrEnchView::CSrEnchView() : CSrRecordDialog(CSrEnchView::IDD) 
{
  m_InitialSetData = false;
  m_IsInitialized = false;
  m_pCurrentEffect = NULL;
}
/*===========================================================================
 *		End of Class CSrEnchView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Destructor
 *
 *=========================================================================*/
CSrEnchView::~CSrEnchView() 
{
}
/*===========================================================================
 *		End of Class CSrEnchView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrEnchView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_BASEENCHANTMENT, m_BaseEnchantment);
	DDX_Control(pDX, IDC_ITEMTYPES, m_ItemTypes);
	DDX_Control(pDX, IDC_EFFECT_LIST, m_EffectList);
	DDX_Control(pDX, IDC_EFFECTNAME, m_EffectName);
	DDX_Control(pDX, IDC_EDIT_EFFECT, m_EditEffectButton);
	DDX_Control(pDX, IDC_SELECTEFFECT_BUTTON, m_SelectEffectButton);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_EffectConditions);
	DDX_Control(pDX, IDC_MAGNITUDE, m_Magnitude);
	DDX_Control(pDX, IDC_AREA, m_Area);
	DDX_Control(pDX, IDC_DURATION, m_Duration);
	DDX_Control(pDX, IDC_CHARGE, m_Charge);
	DDX_Control(pDX, IDC_COST, m_Cost);
	DDX_Control(pDX, IDC_STAFFMOD, m_StaffMod);
	DDX_Control(pDX, IDC_TYPEA, m_TypeA);
	DDX_Control(pDX, IDC_TYPEB, m_TypeB);
	DDX_Control(pDX, IDC_TYPEC, m_TypeC);
	DDX_Control(pDX, IDC_TYPED, m_TypeD);
 }
/*===========================================================================
 *		End of Class Method CSrEnchView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEnchView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrEnchView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrEnchView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrEnchView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrEnchView::OnInitialUpdate (void) 
{
	m_IsInitialized = false;
	m_IgnoreConditions = true;

	CSrRecordDialog::OnInitialUpdate();

	m_EffectList.SetListName("EffectList");
	m_EffectList.SetDragEnable(true);
	m_EffectList.DefaultSettings();
	m_EffectList.SetupCustomList(s_EffectListInit, NULL, s_EffectFields);
	m_EffectList.SetOwner(this);
	m_EffectList.SetColorEnable(false);
	m_EffectList.SetDragType(SR_RLDRAG_CUSTOM);
	m_EffectList.SetSortEnable(false);
	//m_ComponentList.SetActivateType(SR_RLACTIVATE_NONE);
	
	CreateEffectArray();

	SrFillComboList(m_TypeA, s_SrEnchantTypeA, 0);
	SrFillComboList(m_TypeB, s_SrEnchantTypeB, 0);
	SrFillComboList(m_TypeC, s_SrEnchantTypeC, 0);
	SrFillComboList(m_TypeD, s_SrEnchantTypeD, 0);
  
	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnInitialUpdate()
 *=========================================================================*/


void CSrEnchView::GetControlData (void)
{
	CSrSubrecord* pNewEffect;
	CSrSubrecord* pNewEffectData;
	CSrSubrecord* pNewCondition;
	
	CSrRecordDialog::GetControlData();
	GetCurrentEffect();

	CSrEnchRecord* pEnchant = SrCastClassNull(CSrEnchRecord, GetOutputRecord());
	if (pEnchant == NULL) return;

	pEnchant->DeleteSubrecords(SR_NAME_EFID);
	pEnchant->DeleteSubrecords(SR_NAME_EFIT);
	pEnchant->DeleteSubrecords(SR_NAME_CTDA);	
	pEnchant->DeleteSubrecords(SR_NAME_CIS1);
	pEnchant->DeleteSubrecords(SR_NAME_CIS2);

	for (dword i = 0; i < m_Effects.GetSize(); ++i)
	{
		srench_effectdata_t* pEffect = m_Effects[i];
		if (pEffect == NULL || pEffect->pEffect == NULL || pEffect->pEffectData == NULL) continue;
				
		pNewEffect = pEnchant->AddNewSubrecord(SR_NAME_EFID);
		if (pNewEffect) pNewEffect->Copy(pEffect->pEffect);

		pNewEffectData = pEnchant->AddNewSubrecord(SR_NAME_EFIT);
		if (pNewEffectData) pNewEffectData->Copy(pEffect->pEffectData);

		for (dword j = 0; j < pEffect->Conditions.GetSize(); ++j)
		{
			srconditioninfo_t* pCondInfo = pEffect->Conditions[j];
			CSrCtdaSubrecord* pCondition = &pCondInfo->Condition;
			if (pCondition == NULL) continue;

			pNewCondition = pEnchant->AddNewSubrecord(SR_NAME_CTDA);
			if (pNewCondition) pNewCondition->Copy(pCondition);

			if (pCondInfo->pParam1)
			{
				CSrSubrecord* pNewParam = pEnchant->AddNewSubrecord(SR_NAME_CIS1);
				if (pNewParam) pNewParam->Copy(pCondInfo->pParam1);
			}

			if (pCondInfo->pParam2)
			{
				CSrSubrecord* pNewParam = pEnchant->AddNewSubrecord(SR_NAME_CIS2);
				if (pNewParam) pNewParam->Copy(pCondInfo->pParam2);
			}
		}

	}
}


void CSrEnchView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	SetEffectList();
}


void CSrEnchView::OnBnClickedEditBaseenchant()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_BaseEnchantment, SR_NAME_ENCH);
}


void CSrEnchView::OnBnClickedSelectbaseenchantButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_BaseEnchantment.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_ENCH, &CSrEnchRecord::s_FieldMap);
	if (!Result) return;

	m_BaseEnchantment.SetWindowText(Buffer);
}


void CSrEnchView::OnBnClickedEditItemtypes()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ItemTypes, SR_NAME_FLST);
}


void CSrEnchView::OnBnClickedSelectitemtypesButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_ItemTypes.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_FLST, &CSrFlstRecord::s_FieldMap);
	if (!Result) return;

	m_ItemTypes.SetWindowText(Buffer);
}


void CSrEnchView::SetEffectList (void)
{
	m_EffectList.DeleteAllItems();
	
	for (dword i = 0; i < m_Effects.GetSize(); ++i) 
	{
		AddEffectList(m_Effects[i]);
	}

	m_EffectList.SelectRecord(0);
	SetCurrentEffect(m_Effects[0]);
}


/*===========================================================================
 *
 * Class CSrEnchView Method - int AddEffectList (pEffectData);
 *
 *=========================================================================*/
int CSrEnchView::AddEffectList (srench_effectdata_t* pEffectData) 
{
  srrlcustomdata_t	CustomData;
  CString           Buffer;
  int		        ListIndex;

  CustomData.UserCount = pEffectData->Conditions.GetSize();
  CustomData.pRecord = GetInputRecord();
  CustomData.Subrecords.Add(pEffectData->pEffect);
  CustomData.Subrecords.Add(pEffectData->pEffectData);
  
  for (int i = 0; i < (int) pEffectData->Conditions.GetSize(); ++i)
  {
	  CustomData.Subrecords.Add(&pEffectData->Conditions[i]->Condition);
  }
  
  ListIndex = m_EffectList.AddCustomRecord(CustomData);
  if (ListIndex < 0) return (-1);

  UpdateEffectList(ListIndex, false);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrEnchView::AddEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Method - void UpdateEffectList (ListIndex, Update);
 *
 *=========================================================================*/
void CSrEnchView::UpdateEffectList (const int ListIndex, const bool Update)
{
	CSrFormidSubrecord*	pEffectID;
	srrlcustomdata_t*	pCustomData;
	srformid_t			FormID;
	CString				Buffer;

	if (GetInputRecord() == NULL) return;

	pCustomData = m_EffectList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	if (Update) m_EffectList.UpdateRecord(ListIndex);

	pEffectID = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
	if (pEffectID == NULL) return;
		
	FormID = pEffectID->GetValue();
	Buffer.Format("0x%08X", FormID);
	m_EffectList.SetCustomField(ListIndex, SR_FIELD_EFFECTID, Buffer);

	CSrRecord* pRecord = GetInputRecord()->GetParent()->FindFormID(FormID);
	CSrIdRecord* pIdRecord = SrCastClassNull(CSrIdRecord, pRecord);
	if (pIdRecord != NULL) m_EffectList.SetCustomField(ListIndex, SR_FIELD_EFFECTNAME, pIdRecord->GetEditorID());
	
	Buffer.Format("%d", pCustomData->UserCount);
	m_EffectList.SetCustomField(ListIndex, SR_FIELD_CONDITIONCOUNT, Buffer);  
}
/*===========================================================================
 *		End of Class Method CSrEnchView::UpdateEffectList()
 *=========================================================================*/


void CSrEnchView::CreateEffectArray (void)
{
	CSrEnchRecord*			pEnchant;
	CSrSubrecord*			pSubrecord;
	CSrSubrecord*			pNewSubrecord;
	CSrFormidSubrecord*		pEffectID;
	srench_effectdata_t*	pEffectData;
	int Position;
	int EfitCount;

	m_Effects.Empty();
	pEnchant = SrCastClassNull(CSrEnchRecord, GetInputRecord());
	if (pEnchant == NULL) return;

	pSubrecord = pEnchant->FindFirstSubrecord(SR_NAME_EFID, Position);

	while (pSubrecord)
	{
		pEffectID = SrCastClass(CSrFormidSubrecord, pSubrecord);
		if (pEffectID == NULL) goto CreateEffectArray_EndLoop;

		pEffectData = new srench_effectdata_t;
		m_Effects.Add(pEffectData);

		pSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFID);
		pEffectData->pEffect = SrCastClassNull(CSrFormidSubrecord, pSubrecord);
		if (pEffectData->pEffect == NULL) goto CreateEffectArray_EndLoop;
		pEffectData->pEffect->InitializeNew();
		pEffectData->pEffect->Copy(pEffectID);
		EfitCount = 0;

		for (int i = Position + 1; i < (int) pEnchant->GetNumSubrecords(); ++i)
		{
			pSubrecord = pEnchant->GetSubrecord(i);
			if (pSubrecord == NULL) continue;
			if (pSubrecord->GetRecordType() == SR_NAME_EFID) break;

			if (pSubrecord->GetRecordType() == SR_NAME_CTDA)
			{
				srconditioninfo_t* pNewCond = new srconditioninfo_t;
				pNewCond->Condition.Copy(pSubrecord);
				pEffectData->Conditions.Add(pNewCond);

				pSubrecord = pEnchant->GetSubrecord(i+1);
				if (pSubrecord == NULL) continue;

				if (pSubrecord->GetRecordType() == SR_NAME_CIS1)
					pNewCond->CopyParam1(pSubrecord);
				else if (pSubrecord->GetRecordType() == SR_NAME_CIS2)
					pNewCond->CopyParam2(pSubrecord);

				pSubrecord = pEnchant->GetSubrecord(i+2);
				if (pSubrecord == NULL) continue;

				if (pSubrecord->GetRecordType() == SR_NAME_CIS2 && pNewCond->pParam2 == NULL)
					pNewCond->CopyParam2(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EFIT)
			{
				++EfitCount;
				if (EfitCount > 1) SystemLog.Printf("WARNING: More than one EFIT per EFID found in ENCH 0x%08X!", pEnchant->GetFormID());

				pNewSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFIT);
				pEffectData->pEffectData = SrCastClassNull(CSrEfitSubrecord, pNewSubrecord);
				if (pEffectData->pEffectData == NULL) continue;
				pEffectData->pEffectData->InitializeNew();
				pEffectData->pEffectData->Copy(pSubrecord);
			}
			else
			{
				SystemLog.Printf("WARNING: Unknown subrecord type %4.4s found in ENCH effects!", pSubrecord->GetRecordType().Name);
			}
		}		

CreateEffectArray_EndLoop:
		pSubrecord = pEnchant->FindNextSubrecord(SR_NAME_EFID, Position);
	}
	
}


void CSrEnchView::OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetCurrentEffect();
	SetCurrentEffect(m_Effects[pNMLV->iItem]);
}


void CSrEnchView::GetCurrentEffect (void)
{	
	CString Buffer;

	if (m_pCurrentEffect == NULL) return;

	if (m_pCurrentEffect->pEffectData) 
	{
		m_Magnitude.GetWindowText(Buffer);
		m_pCurrentEffect->pEffectData->SetMagnitude((float) atof(Buffer));
		m_Area.GetWindowText(Buffer);
		m_pCurrentEffect->pEffectData->SetArea(atoi(Buffer));
		m_Duration.GetWindowText(Buffer);
		m_pCurrentEffect->pEffectData->SetDuration(atoi(Buffer));
	}

	if (m_pCurrentEffect->pEffect)
	{
		m_EffectName.GetWindowText(Buffer);
		Buffer.Trim();

		if (Buffer.IsEmpty())
		{
			m_pCurrentEffect->pEffect->SetValue(0);
		}
		else
		{
			CSrIdRecord* pRecord = GetInputRecord()->GetParent()->FindEditorID(Buffer);
			if (pRecord) m_pCurrentEffect->pEffect->SetValue(pRecord->GetFormID());
		}
	}

	for (dword i = 0; i < m_Effects.GetSize(); ++i)
	{
		srrlcustomdata_t* pCustomData = (srrlcustomdata_t *) m_EffectList.GetItemData(i);
		if (pCustomData == NULL) continue;

		CSrFormidSubrecord* pEffect = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
		if (pEffect == NULL) continue;
		if (pEffect != m_pCurrentEffect->pEffect) continue;

		pCustomData->UserCount = m_pCurrentEffect->Conditions.GetSize();
		pCustomData->Subrecords.Truncate(2);

		for (dword j = 0; j < m_pCurrentEffect->Conditions.GetSize(); ++j)
		{
			srconditioninfo_t* pCondInfo = m_pCurrentEffect->Conditions[j];
			pCustomData->Subrecords.Add(&pCondInfo->Condition);
			if (pCondInfo->pParam1 != NULL)	pCustomData->Subrecords.Add(pCondInfo->pParam1);
			if (pCondInfo->pParam2 != NULL)	pCustomData->Subrecords.Add(pCondInfo->pParam2);
		}

		UpdateEffectList(i, true);
		break;
	}
	
}


void CSrEnchView::SetCurrentEffect (srench_effectdata_t* pEffectData)
{
	CString Buffer;

	EnableEffectControls(pEffectData != NULL);

	m_pCurrentEffect = pEffectData;

	if (pEffectData == NULL)
	{
		m_Magnitude.SetWindowText("");
		m_Area.SetWindowText("");
		m_Duration.SetWindowText("");
		m_EffectName.SetWindowText("");
		m_EffectConditions.SetWindowText("");
		return;
	}

	if (m_pCurrentEffect->pEffectData) 
	{
		Buffer.Format("%g", m_pCurrentEffect->pEffectData->GetMagnitude());
		m_Magnitude.SetWindowText(Buffer);
		Buffer.Format("%u", m_pCurrentEffect->pEffectData->GetArea());
		m_Area.SetWindowText(Buffer);
		Buffer.Format("%u", m_pCurrentEffect->pEffectData->GetDuration());
		m_Duration.SetWindowText(Buffer);
	}
	else
	{
		m_Magnitude.SetWindowText("");
		m_Area.SetWindowText("");
		m_Duration.SetWindowText("");
	}

	if (m_pCurrentEffect->pEffect)
	{
		m_EffectName.SetWindowText(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentEffect->pEffect->GetValue()));
	}
	else
	{
		m_EffectName.SetWindowTextA("");
	}

	Buffer.Format("%u", m_pCurrentEffect->Conditions.GetSize());
	m_EffectConditions.SetWindowText(Buffer);
}


void CSrEnchView::EnableEffectControls (const bool Enable)
{
	m_EffectConditions.EnableWindow(Enable);
	m_Magnitude.EnableWindow(Enable);
	m_Area.EnableWindow(Enable);
	m_Duration.EnableWindow(Enable);
	m_EffectName.EnableWindow(Enable);
	m_SelectEffectButton.EnableWindow(Enable);
	m_EditEffectButton.EnableWindow(Enable);
}


void CSrEnchView::OnBnClickedConditionButton()
{
	if (m_pCurrentEffect == NULL) return;

	CSrConditionDlg ConditionDlg;
	int Result = ConditionDlg.DoModal(GetInputRecord(), &m_pCurrentEffect->Conditions);
	if (Result != IDOK) return;
	
	CString Buffer;
	Buffer.Format("%d", m_pCurrentEffect->Conditions.GetSize());
	m_EffectConditions.SetWindowText(Buffer);
		
	GetCurrentEffect();
}


void CSrEnchView::OnBnClickedEditEffect()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EffectName, SR_NAME_MGEF);
}


void CSrEnchView::OnBnClickedSelecteffectButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_EffectName.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_MGEF, &CSrMgefRecord::s_FieldMap);
	if (!Result) return;

	m_EffectName.SetWindowText(Buffer);
	GetCurrentEffect();
}


int CSrEnchView::OnPreSaveRecord (void)
{
	GetCurrentEffect();
	return CSrRecordDialog::OnPreSaveRecord();
}


void CSrEnchView::OnBnClickedAddButton()
{
	srench_effectdata_t* pNewEffect = new srench_effectdata_t;
	CSrSubrecord* pSubrecord;

	pSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFID);
	pNewEffect->pEffect     = SrCastClassNull(CSrFormidSubrecord, pSubrecord);
	pSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFIT);
	pNewEffect->pEffectData = SrCastClassNull(CSrEfitSubrecord,   pSubrecord);

	if (pNewEffect->pEffect == NULL || pNewEffect->pEffectData == NULL) 
	{
		delete pNewEffect;
		return;
	}

	pNewEffect->pEffect->InitializeNew();
	pNewEffect->pEffectData->InitializeNew();
	
	GetCurrentEffect();

	m_Effects.Add(pNewEffect);
	AddEffectList(pNewEffect);

	m_EffectList.SelectRecord(m_Effects.GetSize() - 1);
	SetCurrentEffect(m_Effects[m_Effects.GetSize() - 1]);	
}


void CSrEnchView::OnBnClickedDeleteButton2()
{
	if (m_pCurrentEffect == NULL) return;
	GetCurrentEffect();
	m_pCurrentEffect = NULL;

	int Index = m_EffectList.GetSelectedItem();
	m_Effects.Delete(Index);
	m_EffectList.DeleteItem(Index);

	if (Index >= (int) m_Effects.GetSize())
	{
		int i = Index - 1;
		m_EffectList.SelectRecord(i);
		SetCurrentEffect(m_Effects[i]);	
	}
	else
	{
		m_EffectList.SelectRecord(Index);
		SetCurrentEffect(m_Effects[Index]);	
	}
}



/*===========================================================================
 *
 * Class CSrEnchView Event - int OnDropCustomEffectData (DropItems);
 *
 *=========================================================================*/
int CSrEnchView::OnDropCustomEffectData (srrldroprecords_t& DropItems) 
{
  CSrFormidSubrecord*   pEffect;
  CSrEfitSubrecord*     pEffectData;
  srrlcustomdata_t*     pCustomData;
  srench_effectdata_t*  pEffectInfo;
  dword					Index;

  GetCurrentEffect();

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
  {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (SRRL_DROPCHECK_ERROR);

		/* Check for dragging another effect record */
    pEffect = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
    if (pEffect == NULL) return (SRRL_DROPCHECK_ERROR);
    pEffectData = SrCastClassNull(CSrEfitSubrecord, pCustomData->Subrecords[1]);
    if (pEffectData == NULL) return (SRRL_DROPCHECK_ERROR);
        
		/* If we're just checking */
    if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

	pEffectInfo = m_Effects.AddNew();
	if (pEffectInfo == NULL) continue;

	CSrSubrecord* pNewSubrecord = pCustomData->pRecord->CreateSubrecord(SR_NAME_EFID);
	pEffectInfo->pEffect = SrCastClassNull(CSrFormidSubrecord, pNewSubrecord);

	pNewSubrecord = pCustomData->pRecord->CreateSubrecord(SR_NAME_EFIT);
	pEffectInfo->pEffectData = SrCastClassNull(CSrEfitSubrecord, pNewSubrecord);

	if (pEffectInfo->pEffect == NULL || pEffectInfo->pEffectData == NULL)
	{
		m_Effects.Delete(pEffectInfo);
		continue;
	}

	pEffectInfo->pEffect->Copy(pEffect);
	pEffectInfo->pEffectData->Copy(pEffectData);

	for (dword i = 2; i < pCustomData->Subrecords.GetSize(); ++i)
	{
		if (pCustomData->Subrecords[i] == NULL) continue;
		if (pCustomData->Subrecords[i]->GetRecordType() != SR_NAME_CTDA) continue;

		srconditioninfo_t* pNewCond = pEffectInfo->Conditions.AddNew();
		pNewCond->Condition.Copy(pCustomData->Subrecords[i]);

		if (pCustomData->Subrecords[i+1] == NULL) continue;

		if (pCustomData->Subrecords[i+1]->GetRecordType() == SR_NAME_CIS1)
			pNewCond->CopyParam1(pCustomData->Subrecords[i+1]);
		else if (pCustomData->Subrecords[i+1]->GetRecordType() == SR_NAME_CIS2)
			pNewCond->CopyParam2(pCustomData->Subrecords[i+1]);
	
		if (pCustomData->Subrecords[i+2] == NULL) continue;

		if (pCustomData->Subrecords[i+2]->GetRecordType() == SR_NAME_CIS2 && pNewCond->pParam2 == NULL)
			pNewCond->CopyParam2(pCustomData->Subrecords[i+1]);
	}
    
    AddEffectList(pEffectInfo);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnDropCustomData()
 *=========================================================================*/


 /*===========================================================================
 *
 * Class CSrEnchView Event - void OnDropEffectList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrEnchView::OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;

  *pResult = SRRL_DROPCHECK_ERROR;
  
  if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) 
  {
    *pResult = OnDropCustomEffectData(*pDropItems);
  }
  else if (pDropItems->pRecords != NULL) 
  {
    *pResult = SRRL_DROPCHECK_ERROR;
  } 

}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnDropEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Event - void OnDropEffect (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrEnchView::OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrMgefRecord*     pMgef;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  if (m_pCurrentEffect == NULL) return;

  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_PERK) return;
  pMgef = SrCastClass(CSrMgefRecord, pRecord);
  if (pMgef == NULL) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_EffectName.SetWindowText(pMgef->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnDropEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Event - void OnDropBaseEnchant (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrEnchView::OnDropBaseEnchant (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrEnchRecord*     pEnch;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  
  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_PERK) return;
  pEnch = SrCastClass(CSrEnchRecord, pRecord);
  if (pEnch == NULL) return;
  if (pEnch == GetInputRecord()) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_BaseEnchantment.SetWindowText(pEnch->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnDropBaseEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Event - void OnDropItemTypes (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrEnchView::OnDropItemTypes (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrFlstRecord*     pFlst;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  
  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_FLST) return;
  pFlst = SrCastClass(CSrFlstRecord, pRecord);
  if (pFlst == NULL) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_ItemTypes.SetWindowText(pFlst->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnDropItemTypes()
 *=========================================================================*/


void CSrEnchView::OnConditionrecordCopy()
{
	if (m_pCurrentEffect == NULL) return;
	if (m_pCurrentEffect->Conditions.GetSize() == 0) return;

	SrGlobClipClearConditions();

	for (dword i = 0; i < m_pCurrentEffect->Conditions.GetSize(); ++i)
	{
		SrGlobClipAddCondition(m_pCurrentEffect->Conditions[i]);
	}

}


void CSrEnchView::OnConditionrecordPaste()
{
	if (m_pCurrentEffect == NULL) return;
	if (SrGlobClipGetConditions().GetSize() == 0) return;
	m_ConditionsChanged = true;

	for (dword i = 0; i < SrGlobClipGetConditions().GetSize(); ++i)
	{
		m_pCurrentEffect->Conditions.AddNew()->Copy(*SrGlobClipGetConditions()[i]);
	}

	CString Buffer;
	Buffer.Format("%d", m_pCurrentEffect->Conditions.GetSize());
	m_EffectConditions.SetWindowTextA(Buffer);

	GetCurrentEffect();
}


void CSrEnchView::OnConditionrecordDeleteAll()
{
	if (m_pCurrentEffect == NULL) return;
	if (m_pCurrentEffect->Conditions.GetSize() > 0) m_ConditionsChanged = true;
	m_pCurrentEffect->Conditions.Destroy();	
	m_EffectConditions.SetWindowText("0");

	GetCurrentEffect();
}


void CSrEnchView::OnUpdateConditionrecordCopy(CCmdUI *pCmdUI)
{
	if (m_pCurrentEffect == NULL)
	{
		pCmdUI->Enable(false);
		return;
	}

	CString Buffer;
	Buffer.Format("Copy %d Condition(s)", m_pCurrentEffect->Conditions.GetSize());
	pCmdUI->SetText(Buffer);
	pCmdUI->Enable(m_pCurrentEffect->Conditions.GetSize() > 0);
}


void CSrEnchView::OnUpdateConditionrecordPaste(CCmdUI *pCmdUI)
{
	if (m_pCurrentEffect == NULL)
	{
		pCmdUI->Enable(false);
		return;
	}

	CString Buffer;
	Buffer.Format("Paste %d Condition(s)", SrGlobClipGetConditions().GetSize());
	pCmdUI->SetText(Buffer);
	pCmdUI->Enable(SrGlobClipGetConditions().GetSize() > 0);
}


void CSrEnchView::OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI)
{
	if (m_pCurrentEffect == NULL)
	{
		pCmdUI->Enable(false);
		return;
	}

	pCmdUI->Enable(m_pCurrentEffect->Conditions.GetSize() > 0);
}


void CSrEnchView::OnContextMenu(CWnd* pWnd, CPoint Point)
{
	if (pWnd == &m_EffectConditions)
	{
		CMenu Menu;
		int Result = Menu.LoadMenu(IDR_CONDITIONRECORD_MENU);
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
