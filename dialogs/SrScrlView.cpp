/*===========================================================================
 *
 * File:		SrScrlView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srscrlview.h"
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

  IMPLEMENT_DYNCREATE(CSrScrlView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrScrlView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrScrlView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_EQUIPSLOT, &CSrScrlView::OnBnClickedEditEquipSlot)
	ON_BN_CLICKED(IDC_SELECTEQUIPSLO_BUTTON, &CSrScrlView::OnBnClickedSelectequipslotButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EFFECT_LIST, &CSrScrlView::OnLvnItemchangedEffectList)
	ON_BN_CLICKED(IDC_CONDITION_BUTTON, &CSrScrlView::OnBnClickedConditionButton)
	ON_BN_CLICKED(IDC_EDIT_EFFECT, &CSrScrlView::OnBnClickedEditEffect)
	ON_BN_CLICKED(IDC_SELECTEFFECT_BUTTON, &CSrScrlView::OnBnClickedSelecteffectButton)
	ON_BN_CLICKED(ID_ADD_BUTTON, &CSrScrlView::OnBnClickedAddButton)
	ON_BN_CLICKED(ID_DELETE_BUTTON2, &CSrScrlView::OnBnClickedDeleteButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EQUIPSLOT, OnDropEquipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EQUIPSLOT, OnDropEquipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECTNAME, OnDropEffect)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECTNAME, OnDropEffect)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrScrlView Message Map
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
BEGIN_SRRECUIFIELDS(CSrScrlView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_EQUIPSLOT,			IDC_EQUIPSLOT,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_COST,				IDC_COST,				8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,		IDC_DESCRIPTION,		256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTTIME,			IDC_CASTTIME,			32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTTYPE,			IDC_CASTTYPE,			32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTANIM,			IDC_CASTANIM,			32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,				IDC_VALUE,				32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,				IDC_WEIGHT,				32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,			IDC_KEYWORDS,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,				IDC_MODEL,				200,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrScrlView Constructor
 *
 *=========================================================================*/
CSrScrlView::CSrScrlView() : CSrRecordDialog(CSrScrlView::IDD) 
{
	m_InitialSetData = false;
	m_IsInitialized = false;
	m_pCurrentEffect = NULL;
}
/*===========================================================================
 *		End of Class CSrScrlView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrScrlView Destructor
 *
 *=========================================================================*/
CSrScrlView::~CSrScrlView() 
{
}
/*===========================================================================
 *		End of Class CSrScrlView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrScrlView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrScrlView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_EQUIPSLOT, m_EquipSlot);
	DDX_Control(pDX, IDC_EFFECT_LIST, m_EffectList);
	DDX_Control(pDX, IDC_EFFECTNAME, m_EffectName);
	DDX_Control(pDX, IDC_EDIT_EFFECT, m_EditEffectButton);
	DDX_Control(pDX, IDC_SELECTEFFECT_BUTTON, m_SelectEffectButton);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_EffectConditions);
	DDX_Control(pDX, IDC_MAGNITUDE, m_Magnitude);
	DDX_Control(pDX, IDC_AREA, m_Area);
	DDX_Control(pDX, IDC_DURATION, m_Duration);
	DDX_Control(pDX, IDC_COST, m_Cost);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_CASTTYPE, m_CastType);
	DDX_Control(pDX, IDC_CASTANIM, m_CastAnim);
	DDX_Control(pDX, IDC_CASTTIME, m_CastTime);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_MODEL, m_Model);
}
/*===========================================================================
 *		End of Class Method CSrScrlView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrScrlView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrScrlView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrScrlView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrScrlView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrScrlView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrScrlView::OnInitialUpdate (void) 
{
	m_IsInitialized = false;
	m_IgnoreConditions = true;

	CSrRecordDialog::OnInitialUpdate();

	m_EffectList.SetListName("SpellEffectList");
	m_EffectList.SetDragEnable(true);
	m_EffectList.DefaultSettings();
	m_EffectList.SetupCustomList(s_EffectListInit, NULL, s_EffectFields);
	m_EffectList.SetOwner(this);
	m_EffectList.SetColorEnable(false);
	m_EffectList.SetDragType(SR_RLDRAG_CUSTOM);
	m_EffectList.SetSortEnable(false);
	m_EffectList.SetActivateType(SR_RLACTIVATE_NONE);
	
	CreateEffectArray();

	::SrFillComboList(m_CastType, s_SrSpellCastTypes, 0);
	::SrFillComboList(m_CastAnim, s_SrSpellCastAnims, 0);
  
	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrScrlView::OnInitialUpdate()
 *=========================================================================*/


void CSrScrlView::GetControlData (void)
{
	CSrSubrecord* pNewEffect;
	CSrSubrecord* pNewEffectData;
	CSrSubrecord* pNewCondition;
	
	CSrRecordDialog::GetControlData();
	GetCurrentEffect();

	CSrScrlRecord* pScroll = SrCastClassNull(CSrScrlRecord, GetOutputRecord());
	if (pScroll == NULL) return;

	pScroll->DeleteSubrecords(SR_NAME_EFID);
	pScroll->DeleteSubrecords(SR_NAME_EFIT);
	pScroll->DeleteSubrecords(SR_NAME_CTDA);	
	pScroll->DeleteSubrecords(SR_NAME_CIS1);
	pScroll->DeleteSubrecords(SR_NAME_CIS2);

	for (dword i = 0; i < m_Effects.GetSize(); ++i)
	{
		srscrl_effectdata_t* pEffect = m_Effects[i];
		if (pEffect == NULL || pEffect->pEffect == NULL || pEffect->pEffectData == NULL) continue;
				
		pNewEffect = pScroll->AddNewSubrecord(SR_NAME_EFID);
		if (pNewEffect) pNewEffect->Copy(pEffect->pEffect);

		pNewEffectData = pScroll->AddNewSubrecord(SR_NAME_EFIT);
		if (pNewEffectData) pNewEffectData->Copy(pEffect->pEffectData);

		for (dword j = 0; j < pEffect->Conditions.GetSize(); ++j)
		{
			srconditioninfo_t* pCondInfo = pEffect->Conditions[j];
			CSrCtdaSubrecord* pCondition = &pCondInfo->Condition;
			if (pCondition == NULL) continue;

			pNewCondition = pScroll->AddNewSubrecord(SR_NAME_CTDA);
			if (pNewCondition) pNewCondition->Copy(pCondition);

			if (pCondInfo->pParam1)
			{
				CSrSubrecord* pNewParam = pScroll->AddNewSubrecord(SR_NAME_CIS1);
				if (pNewParam) pNewParam->Copy(pCondInfo->pParam1);
			}

			if (pCondInfo->pParam2)
			{
				CSrSubrecord* pNewParam = pScroll->AddNewSubrecord(SR_NAME_CIS2);
				if (pNewParam) pNewParam->Copy(pCondInfo->pParam2);
			}
		}

	}
}


void CSrScrlView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	SetEffectList();
}


void CSrScrlView::OnBnClickedEditEquipSlot()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EquipSlot, SR_NAME_EQUP);
}


void CSrScrlView::OnBnClickedSelectequipslotButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_EquipSlot.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_EQUP, &CSrFlstRecord::s_FieldMap);
	if (!Result) return;

	m_EquipSlot.SetWindowText(Buffer);
}


void CSrScrlView::SetEffectList (void)
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
 * Class CSrScrlView Method - int AddEffectList (pEffectData);
 *
 *=========================================================================*/
int CSrScrlView::AddEffectList (srscrl_effectdata_t* pEffectData) 
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
	  CustomData.pSubrecords[i+2] = &pEffectData->Conditions[i]->Condition;
  }
  
  ListIndex = m_EffectList.AddCustomRecord(CustomData);
  if (ListIndex < 0) return (-1);

  UpdateEffectList(ListIndex, false);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrScrlView::AddEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrScrlView Method - void UpdateEffectList (ListIndex, Update);
 *
 *=========================================================================*/
void CSrScrlView::UpdateEffectList (const int ListIndex, const bool Update)
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
 *		End of Class Method CSrScrlView::UpdateEffectList()
 *=========================================================================*/


void CSrScrlView::CreateEffectArray (void)
{
	CSrScrlRecord*			pScroll;
	CSrSubrecord*			pSubrecord;
	CSrSubrecord*			pNewSubrecord;
	CSrFormidSubrecord*		pEffectID;
	srscrl_effectdata_t*	pEffectData;
	int Position;
	int EfitCount;

	m_Effects.Empty();
	pScroll = SrCastClassNull(CSrScrlRecord, GetInputRecord());
	if (pScroll == NULL) return;

	pSubrecord = pScroll->FindFirstSubrecord(SR_NAME_EFID, Position);

	while (pSubrecord)
	{
		pEffectID = SrCastClass(CSrFormidSubrecord, pSubrecord);
		if (pEffectID == NULL) goto CreateEffectArray_EndLoop;

		pEffectData = new srscrl_effectdata_t;
		m_Effects.Add(pEffectData);

		pSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFID);
		pEffectData->pEffect = SrCastClassNull(CSrFormidSubrecord, pSubrecord);
		if (pEffectData->pEffect == NULL) goto CreateEffectArray_EndLoop;
		pEffectData->pEffect->InitializeNew();
		pEffectData->pEffect->Copy(pEffectID);
		EfitCount = 0;

		for (int i = Position + 1; i < (int) pScroll->GetNumSubrecords(); ++i)
		{
			pSubrecord = pScroll->GetSubrecord(i);
			if (pSubrecord == NULL) continue;
			if (pSubrecord->GetRecordType() == SR_NAME_EFID) break;

			if (pSubrecord->GetRecordType() == SR_NAME_CTDA)
			{
				srconditioninfo_t* pNewCond = new srconditioninfo_t;
				pNewCond->Condition.Copy(pSubrecord);
				pEffectData->Conditions.Add(pNewCond);

				pSubrecord = pScroll->GetSubrecord(i+1);
				if (pSubrecord == NULL) goto CreateEffectArray_EndLoop;

				if (pSubrecord->GetRecordType() == SR_NAME_CIS1)
					pNewCond->CopyParam1(pSubrecord);
				else if (pSubrecord->GetRecordType() == SR_NAME_CIS2)
					pNewCond->CopyParam2(pSubrecord);

				pSubrecord = pScroll->GetSubrecord(i+2);
				if (pSubrecord == NULL) goto CreateEffectArray_EndLoop;

				if (pSubrecord->GetRecordType() == SR_NAME_CIS2 && pNewCond->pParam2 == NULL)
					pNewCond->CopyParam2(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EFIT)
			{
				++EfitCount;
				if (EfitCount > 1) SystemLog.Printf("WARNING: More than one EFIT per EFID found in SCRL 0x%08X!", pScroll->GetFormID());

				pNewSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFIT);
				pEffectData->pEffectData = SrCastClassNull(CSrEfitSubrecord, pNewSubrecord);
				if (pEffectData->pEffectData == NULL) goto CreateEffectArray_EndLoop;
				pEffectData->pEffectData->InitializeNew();
				pEffectData->pEffectData->Copy(pSubrecord);
			}
			else
			{
				SystemLog.Printf("WARNING: Unknown subrecord type %4.4s found in SCRL effects!", pSubrecord->GetRecordType().Name);
			}
		}		

CreateEffectArray_EndLoop:
		pSubrecord = pScroll->FindNextSubrecord(SR_NAME_EFID, Position);
	}
	
}


void CSrScrlView::OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetCurrentEffect();
	SetCurrentEffect(m_Effects[pNMLV->iItem]);
}


void CSrScrlView::GetCurrentEffect (void)
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

		int CDIndex = 2;

		for (int j = 0; CDIndex < SR_RLMAX_SUBRECORDS && j < (int) m_pCurrentEffect->Conditions.GetSize(); ++j)
		{
			srconditioninfo_t* pCondInfo = m_pCurrentEffect->Conditions[j];
			pCustomData->pSubrecords[CDIndex] = &pCondInfo->Condition;
			++CDIndex;

			if (pCondInfo->pParam1 != NULL && CDIndex < SR_RLMAX_SUBRECORDS)
			{
				pCustomData->pSubrecords[CDIndex] = pCondInfo->pParam1;
				++CDIndex;
			}

			if (pCondInfo->pParam2 != NULL && CDIndex < SR_RLMAX_SUBRECORDS)
			{
				pCustomData->pSubrecords[CDIndex] = pCondInfo->pParam2;
				++CDIndex;
			}
		}

		UpdateEffectList(i, true);
		break;
	}
	
}


void CSrScrlView::SetCurrentEffect (srscrl_effectdata_t* pEffectData)
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


void CSrScrlView::EnableEffectControls (const bool Enable)
{
	m_EffectConditions.EnableWindow(Enable);
	m_Magnitude.EnableWindow(Enable);
	m_Area.EnableWindow(Enable);
	m_Duration.EnableWindow(Enable);
	m_EffectName.EnableWindow(Enable);
	m_SelectEffectButton.EnableWindow(Enable);
	m_EditEffectButton.EnableWindow(Enable);
}


void CSrScrlView::OnBnClickedConditionButton()
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


void CSrScrlView::OnBnClickedEditEffect()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EffectName, SR_NAME_MGEF);
}


void CSrScrlView::OnBnClickedSelecteffectButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_EffectName.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_MGEF, &CSrMgefRecord::s_FieldMap);
	if (!Result) return;

	m_EffectName.SetWindowText(Buffer);
	GetCurrentEffect();
}


int CSrScrlView::OnPreSaveRecord (void)
{
	GetCurrentEffect();
	return CSrRecordDialog::OnPreSaveRecord();
}


void CSrScrlView::OnBnClickedAddButton()
{
	srscrl_effectdata_t* pNewEffect = new srscrl_effectdata_t;
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


void CSrScrlView::OnBnClickedDeleteButton()
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
 * Class CSrScrlView Event - int OnDropCustomEffectData (DropItems);
 *
 *=========================================================================*/
int CSrScrlView::OnDropCustomEffectData (srrldroprecords_t& DropItems) 
{
  CSrFormidSubrecord*   pEffect;
  CSrEfitSubrecord*     pEffectData;
  srrlcustomdata_t*     pCustomData;
  srscrl_effectdata_t*  pEffectInfo;
  dword					Index;

  GetCurrentEffect();

	/* Check all custom data dropped */
  for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
  {
    pCustomData = DropItems.pCustomDatas->GetAt(Index);

    if (pCustomData->pRecord        == NULL) return (SRRL_DROPCHECK_ERROR);
    if (pCustomData->pSubrecords    == NULL) return (SRRL_DROPCHECK_ERROR);

		/* Check for dragging another effect record */
    pEffect = SrCastClassNull(CSrFormidSubrecord, pCustomData->pSubrecords[0]);
    if (pEffect == NULL) return (SRRL_DROPCHECK_ERROR);
    pEffectData = SrCastClassNull(CSrEfitSubrecord, pCustomData->pSubrecords[1]);
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

	for (int i = 2; i < SR_RLMAX_SUBRECORDS; ++i)
	{
		if (pCustomData->pSubrecords[i] == NULL) continue;
		if (pCustomData->pSubrecords[i]->GetRecordType() != SR_NAME_CTDA) continue;

		srconditioninfo_t* pNewCond = pEffectInfo->Conditions.AddNew();
		pNewCond->Condition.Copy(pCustomData->pSubrecords[i]);

		if (pCustomData->pSubrecords[i+1] == NULL) continue;

		if (pCustomData->pSubrecords[i+1]->GetRecordType() == SR_NAME_CIS1)
			pNewCond->CopyParam1(pCustomData->pSubrecords[i+1]);
		else if (pCustomData->pSubrecords[i+1]->GetRecordType() == SR_NAME_CIS2)
			pNewCond->CopyParam2(pCustomData->pSubrecords[i+1]);
	
		if (pCustomData->pSubrecords[i+2] == NULL) continue;

		if (pCustomData->pSubrecords[i+2]->GetRecordType() == SR_NAME_CIS2 && pNewCond->pParam2 == NULL)
			pNewCond->CopyParam2(pCustomData->pSubrecords[i+1]);
	}
    
    AddEffectList(pEffectInfo);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrScrlView::OnDropCustomData()
 *=========================================================================*/


 /*===========================================================================
 *
 * Class CSrScrlView Event - void OnDropEffectList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrScrlView::OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult) 
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
 *		End of Class Event CSrScrlView::OnDropEffectList()
 *=========================================================================*/


 /*===========================================================================
 *
 * Class CSrScrlView Event - void OnDropEquipSlot (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrScrlView::OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrEqupRecord*     pEquipSlot;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_EQUP) return;
  pEquipSlot = SrCastClass(CSrEqupRecord, pRecord);
  if (pEquipSlot == NULL) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_EquipSlot.SetWindowText(pEquipSlot->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrScrlView::OnDropEquipSlot()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrScrlView Event - void OnDropEffect (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrScrlView::OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrMgefRecord*     pMgef;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;
  if (m_pCurrentEffect == NULL) return;

  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_MGEF) return;
  pMgef = SrCastClass(CSrMgefRecord, pRecord);
  if (pMgef == NULL) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_EffectName.SetWindowText(pMgef->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrScrlView::OnDropEffect()
 *=========================================================================*/