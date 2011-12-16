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
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

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
			CSrCtdaSubrecord* pCondition = pEffect->Conditions[j];
			if (pCondition == NULL) continue;

			pNewCondition = pEnchant->AddNewSubrecord(SR_NAME_CTDA);
			if (pNewCondition) pNewCondition->Copy(pCondition);
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
  srrlcustomdata_t	CustomData = { 0 };
  CString           Buffer;
  int		        ListIndex;

  CustomData.UserCount = pEffectData->Conditions.GetSize();
  CustomData.pRecord = GetInputRecord();
  CustomData.pSubrecords[0] = pEffectData->pEffect;
  CustomData.pSubrecords[1] = pEffectData->pEffectData;
  
  for (int i = 0; i < SR_RLMAX_SUBRECORDS-3 && i < (int) pEffectData->Conditions.GetSize(); ++i)
  {
	  CustomData.pSubrecords[i+2] = pEffectData->Conditions[i];
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

	pEffectID = SrCastClassNull(CSrFormidSubrecord, pCustomData->pSubrecords[0]);
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
				pNewSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_CTDA);
				CSrCtdaSubrecord* pNewCond = SrCastClassNull(CSrCtdaSubrecord, pNewSubrecord);
				if (pNewCond == NULL) goto CreateEffectArray_EndLoop;
				pNewCond->InitializeNew();
				pNewCond->Copy(pSubrecord);
				pEffectData->Conditions.Add(pNewCond);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EFIT)
			{
				++EfitCount;
				if (EfitCount > 1) SystemLog.Printf("WARNING: More than one EFIT per EFID found in ENCH 0x%08X!", pEnchant->GetFormID());

				pNewSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFIT);
				pEffectData->pEffectData = SrCastClassNull(CSrEfitSubrecord, pNewSubrecord);
				if (pEffectData->pEffectData == NULL) goto CreateEffectArray_EndLoop;
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

		CSrFormidSubrecord* pEffect = SrCastClassNull(CSrFormidSubrecord, pCustomData->pSubrecords[0]);
		if (pEffect == NULL) continue;
		if (pEffect != m_pCurrentEffect->pEffect) continue;

		pCustomData->UserCount = m_pCurrentEffect->Conditions.GetSize();
		memset(pCustomData->pSubrecords + 2, 0, sizeof(pCustomData->pSubrecords) - 2*sizeof(pCustomData->pSubrecords[0]));

		for (int j = 0; j < SR_RLMAX_SUBRECORDS-3 && j < (int) m_pCurrentEffect->Conditions.GetSize(); ++j)
		{
			pCustomData->pSubrecords[j+2] = m_pCurrentEffect->Conditions[j];
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
