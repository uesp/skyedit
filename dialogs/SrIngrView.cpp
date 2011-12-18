/*===========================================================================
 *
 * File:		SrIngrView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	14 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "sringrview.h"
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

  IMPLEMENT_DYNCREATE(CSrIngrView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrIngrView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrIngrView, CSrRecordDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EFFECT_LIST, &CSrIngrView::OnLvnItemchangedEffectList)
	ON_BN_CLICKED(IDC_CONDITION_BUTTON, &CSrIngrView::OnBnClickedConditionButton)
	ON_BN_CLICKED(IDC_EDIT_EFFECT, &CSrIngrView::OnBnClickedEditEffect)
	ON_BN_CLICKED(IDC_SELECTEFFECT_BUTTON, &CSrIngrView::OnBnClickedSelecteffectButton)
	ON_BN_CLICKED(ID_ADD_BUTTON, &CSrIngrView::OnBnClickedAddButton)
	ON_BN_CLICKED(ID_DELETE_BUTTON2, &CSrIngrView::OnBnClickedDeleteButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECT_LIST, OnDropEffectList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECTNAME, OnDropEffect)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECTNAME, OnDropEffect)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrIngrView Message Map
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
BEGIN_SRRECUIFIELDS(CSrIngrView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_PICKUPSOUND,		IDC_PICKUPSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DROPSOUND,			IDC_DROPSOUND,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,				IDC_VALUE,				32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,			IDC_UNKNOWN,			32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,				IDC_WEIGHT,				32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,			IDC_KEYWORDS,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,				IDC_MODEL,				128,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrIngrView Constructor
 *
 *=========================================================================*/
CSrIngrView::CSrIngrView() : CSrRecordDialog(CSrIngrView::IDD) 
{
	m_InitialSetData = false;
	m_IsInitialized = false;
	m_pCurrentEffect = NULL;
}
/*===========================================================================
 *		End of Class CSrIngrView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrIngrView Destructor
 *
 *=========================================================================*/
CSrIngrView::~CSrIngrView() 
{
}
/*===========================================================================
 *		End of Class CSrIngrView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrIngrView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrIngrView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_EFFECT_LIST, m_EffectList);
	DDX_Control(pDX, IDC_EFFECTNAME, m_EffectName);
	DDX_Control(pDX, IDC_EDIT_EFFECT, m_EditEffectButton);
	DDX_Control(pDX, IDC_SELECTEFFECT_BUTTON, m_SelectEffectButton);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_EffectConditions);
	DDX_Control(pDX, IDC_MAGNITUDE, m_Magnitude);
	DDX_Control(pDX, IDC_AREA, m_Area);
	DDX_Control(pDX, IDC_DURATION, m_Duration);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_PICKUPSOUND, m_PickupSound);
	DDX_Control(pDX, IDC_DROPSOUND, m_DropSound);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_UNKNOWN, m_Unknown);
}
/*===========================================================================
 *		End of Class Method CSrIngrView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrIngrView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrIngrView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrIngrView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrIngrView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrIngrView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrIngrView::OnInitialUpdate (void) 
{
	m_IsInitialized = false;
	CSrRecordDialog::OnInitialUpdate();

	m_EffectList.SetListName("PotionEffectList");
	m_EffectList.SetDragEnable(true);
	m_EffectList.DefaultSettings();
	m_EffectList.SetupCustomList(s_EffectListInit, NULL, s_EffectFields);
	m_EffectList.SetOwner(this);
	m_EffectList.SetColorEnable(false);
	m_EffectList.SetDragType(SR_RLDRAG_CUSTOM);
	m_EffectList.SetSortEnable(false);
	m_EffectList.SetActivateType(SR_RLACTIVATE_NONE);
	
	CreateEffectArray();

	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrIngrView::OnInitialUpdate()
 *=========================================================================*/


void CSrIngrView::GetControlData (void)
{
	CSrSubrecord* pNewEffect;
	CSrSubrecord* pNewEffectData;
	CSrSubrecord* pNewCondition;
	
	CSrRecordDialog::GetControlData();
	GetCurrentEffect();

	CSrIngrRecord* pIngredient = SrCastClassNull(CSrIngrRecord, GetOutputRecord());
	if (pIngredient == NULL) return;

	pIngredient->DeleteSubrecords(SR_NAME_EFID);
	pIngredient->DeleteSubrecords(SR_NAME_EFIT);
	pIngredient->DeleteSubrecords(SR_NAME_CTDA);	

	for (dword i = 0; i < m_Effects.GetSize(); ++i)
	{
		sringr_effectdata_t* pEffect = m_Effects[i];
		if (pEffect == NULL || pEffect->pEffect == NULL || pEffect->pEffectData == NULL) continue;
				
		pNewEffect = pIngredient->AddNewSubrecord(SR_NAME_EFID);
		if (pNewEffect) pNewEffect->Copy(pEffect->pEffect);

		pNewEffectData = pIngredient->AddNewSubrecord(SR_NAME_EFIT);
		if (pNewEffectData) pNewEffectData->Copy(pEffect->pEffectData);

		for (dword j = 0; j < pEffect->Conditions.GetSize(); ++j)
		{
			CSrCtdaSubrecord* pCondition = pEffect->Conditions[j];
			if (pCondition == NULL) continue;

			pNewCondition = pIngredient->AddNewSubrecord(SR_NAME_CTDA);
			if (pNewCondition) pNewCondition->Copy(pCondition);
		}

	}
}


void CSrIngrView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	SetEffectList();
}


void CSrIngrView::SetEffectList (void)
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
 * Class CSrIngrView Method - int AddEffectList (pEffectData);
 *
 *=========================================================================*/
int CSrIngrView::AddEffectList (sringr_effectdata_t* pEffectData) 
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
 *		End of Class Method CSrIngrView::AddEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrIngrView Method - void UpdateEffectList (ListIndex, Update);
 *
 *=========================================================================*/
void CSrIngrView::UpdateEffectList (const int ListIndex, const bool Update)
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
 *		End of Class Method CSrIngrView::UpdateEffectList()
 *=========================================================================*/


void CSrIngrView::CreateEffectArray (void)
{
	CSrIngrRecord*			pIngredient;
	CSrSubrecord*			pSubrecord;
	CSrSubrecord*			pNewSubrecord;
	CSrFormidSubrecord*		pEffectID;
	sringr_effectdata_t*	pEffectData;
	int Position;
	int EfitCount;

	m_Effects.Empty();
	pIngredient = SrCastClassNull(CSrIngrRecord, GetInputRecord());
	if (pIngredient == NULL) return;

	pSubrecord = pIngredient->FindFirstSubrecord(SR_NAME_EFID, Position);

	while (pSubrecord)
	{
		pEffectID = SrCastClass(CSrFormidSubrecord, pSubrecord);
		if (pEffectID == NULL) goto CreateEffectArray_EndLoop;

		pEffectData = new sringr_effectdata_t;
		m_Effects.Add(pEffectData);

		pSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFID);
		pEffectData->pEffect = SrCastClassNull(CSrFormidSubrecord, pSubrecord);
		if (pEffectData->pEffect == NULL) goto CreateEffectArray_EndLoop;
		pEffectData->pEffect->InitializeNew();
		pEffectData->pEffect->Copy(pEffectID);
		EfitCount = 0;

		for (int i = Position + 1; i < (int) pIngredient->GetNumSubrecords(); ++i)
		{
			pSubrecord = pIngredient->GetSubrecord(i);
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
				if (EfitCount > 1) SystemLog.Printf("WARNING: More than one EFIT per EFID found in INGR 0x%08X!", pIngredient->GetFormID());

				pNewSubrecord = GetInputRecord()->CreateSubrecord(SR_NAME_EFIT);
				pEffectData->pEffectData = SrCastClassNull(CSrEfitSubrecord, pNewSubrecord);
				if (pEffectData->pEffectData == NULL) goto CreateEffectArray_EndLoop;
				pEffectData->pEffectData->InitializeNew();
				pEffectData->pEffectData->Copy(pSubrecord);
			}
			else
			{
				SystemLog.Printf("WARNING: Unknown subrecord type %4.4s found in INGR effects!", pSubrecord->GetRecordType().Name);
			}
		}		

CreateEffectArray_EndLoop:
		pSubrecord = pIngredient->FindNextSubrecord(SR_NAME_EFID, Position);
	}
	
}


void CSrIngrView::OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetCurrentEffect();
	SetCurrentEffect(m_Effects[pNMLV->iItem]);
}


void CSrIngrView::GetCurrentEffect (void)
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


void CSrIngrView::SetCurrentEffect (sringr_effectdata_t* pEffectData)
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


void CSrIngrView::EnableEffectControls (const bool Enable)
{
	m_EffectConditions.EnableWindow(Enable);
	m_Magnitude.EnableWindow(Enable);
	m_Area.EnableWindow(Enable);
	m_Duration.EnableWindow(Enable);
	m_EffectName.EnableWindow(Enable);
	m_SelectEffectButton.EnableWindow(Enable);
	m_EditEffectButton.EnableWindow(Enable);
}


void CSrIngrView::OnBnClickedConditionButton()
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


void CSrIngrView::OnBnClickedEditEffect()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EffectName, SR_NAME_MGEF);
}


void CSrIngrView::OnBnClickedSelecteffectButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_EffectName.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_MGEF, &CSrMgefRecord::s_FieldMap);
	if (!Result) return;

	m_EffectName.SetWindowText(Buffer);
	GetCurrentEffect();
}


int CSrIngrView::OnPreSaveRecord (void)
{
	GetCurrentEffect();
	return CSrRecordDialog::OnPreSaveRecord();
}


void CSrIngrView::OnBnClickedAddButton()
{
	sringr_effectdata_t* pNewEffect = new sringr_effectdata_t;
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


void CSrIngrView::OnBnClickedDeleteButton()
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
 * Class CSrIngrView Event - int OnDropCustomEffectData (DropItems);
 *
 *=========================================================================*/
int CSrIngrView::OnDropCustomEffectData (srrldroprecords_t& DropItems) 
{
  CSrFormidSubrecord*   pEffect;
  CSrEfitSubrecord*     pEffectData;
  srrlcustomdata_t*     pCustomData;
  sringr_effectdata_t*  pEffectInfo;
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

		CSrCtdaSubrecord* pNewCond = pEffectInfo->Conditions.AddNew();
		pNewCond->Copy(pCustomData->pSubrecords[i]);
	}
    
    AddEffectList(pEffectInfo);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrIngrView::OnDropCustomData()
 *=========================================================================*/


 /*===========================================================================
 *
 * Class CSrIngrView Event - void OnDropEffectList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrIngrView::OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult) 
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
 *		End of Class Event CSrIngrView::OnDropEffectList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrIngrView Event - void OnDropEffect (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrIngrView::OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult) {
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
 *		End of Class Event CSrIngrView::OnDropEffect()
 *=========================================================================*/

