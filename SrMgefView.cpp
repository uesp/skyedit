/*===========================================================================
 *
 * File:		SrMgefView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srmgefview.h"
#include "dialogs/sreditdlghandler.h"


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

  IMPLEMENT_DYNCREATE(CSrMgefView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrMgefView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrMgefView, CSrRecordDialog)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropKeywords)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropKeywords)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrMgefView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrMgefView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,		IDC_DNAME,				256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,			IDC_KEYWORDS,			0,		IDS_TT_KEYWORDS)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			256,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_SCHOOL,				IDC_SCHOOLLIST,			64,		IDS_TT_SCHOOL)
	ADD_SRRECUIFIELDS( SR_FIELD_EFFECTTYPE,			IDC_TYPELIST,			64,		IDS_TT_EFFECTTYPE)
	ADD_SRRECUIFIELDS( SR_FIELD_CONDITIONCOUNT,		IDC_CONDITION_BUTTON,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILLLEVEL,			IDC_SKILLLEVEL,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_BASECOST,			IDC_BASECOST,			10,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefView Constructor
 *
 *=========================================================================*/
CSrMgefView::CSrMgefView() : CSrRecordDialog(CSrMgefView::IDD) 
{
  //{{AFX_DATA_INIT(CSrMgefView)
  //}}AFX_DATA_INIT

  m_ScriptType  = 0;
  m_EnchantType = 0;

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrMgefView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefView Destructor
 *
 *=========================================================================*/
CSrMgefView::~CSrMgefView() 
{

}
/*===========================================================================
 *		End of Class CSrMgefView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrMgefView::DoDataExchange (CDataExchange* pDX) {
	CSrRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrMgefView)
	DDX_Control(pDX, IDC_DNAME, m_DName);
	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_SCHOOLLIST, m_SchoolList);
	DDX_Control(pDX, IDC_TYPELIST, m_TypeList);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_Conditions);
	DDX_Control(pDX, IDC_BASECOST, m_BaseCost);
	DDX_Control(pDX, IDC_SKILLLEVEL, m_SkillLevel);
	DDX_Control(pDX, IDC_HOSTILECHECK, m_HostileCheck);
	DDX_Control(pDX, IDC_RECOVERCHECK, m_RecoverCheck);
	DDX_Control(pDX, IDC_DETRIMENTALCHECK, m_DetrimentalCheck);
	DDX_Control(pDX, IDC_PERCENTMAGCHECK, m_PercentMagCheck);
	DDX_Control(pDX, IDC_SELFONLYCHECK, m_SelfCheck);
	DDX_Control(pDX, IDC_FXPERSISTCHECK, m_FXPersistCheck);
	DDX_Control(pDX, IDC_BOUNDCHECK, m_BoundCheck);
}
/*===========================================================================
 *		End of Class Method CSrMgefView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrMgefView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrMgefView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrMgefView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrMgefView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrMgefView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SrFillComboList(m_SchoolList,	s_SrMagicSchools,	0);
  SrFillComboList(m_TypeList,	s_SrMagicTypes,		0);
  
  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrMgefView::OnInitialUpdate()
 *=========================================================================*/


void CSrMgefView::GetControlData (void)
{
	CSrRecordDialog::GetControlData();

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetOutputRecord());
	if (pMgef == NULL) return;

	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_HOSTILE,		m_HostileCheck.GetCheck() != 0);
	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_RECOVER,		m_RecoverCheck.GetCheck() != 0);
	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_DETRIMENTAL,	m_DetrimentalCheck.GetCheck() != 0);
	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_PERCENTMAG,	m_PercentMagCheck.GetCheck() != 0);
	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_SELF,		m_SelfCheck.GetCheck() != 0);
	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_FXPERSIST,	m_FXPersistCheck.GetCheck() != 0);
	FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_BOUND,		m_BoundCheck.GetCheck() != 0);
}


void CSrMgefView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetInputRecord());
	if (pMgef == NULL) return;

	m_HostileCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_HOSTILE));
	m_RecoverCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_RECOVER));
	m_DetrimentalCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_DETRIMENTAL));
	m_PercentMagCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_PERCENTMAG));
	m_SelfCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_SELF));
	m_FXPersistCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_FXPERSIST));
	m_BoundCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_BOUND));
}


/*===========================================================================
 *
 * Class CSrMgefView Event - void OnDropKeywords (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrMgefView::OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrKywdRecord*     pKeyword;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;

  for (dword i = 0; i < pDropItems->pRecords->GetSize(); ++i)
  {
	pRecord = pDropItems->pRecords->GetAt(i);

	if (pRecord->GetRecordType() != SR_NAME_KYWD) return;
    pKeyword = SrCastClass(CSrKywdRecord, pRecord);
    if (pKeyword == NULL) return;

    if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
    {
      m_Keywords.AddString(pKeyword->GetEditorID());
    }
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrMgefView::OnDropKeywords()
 *=========================================================================*/