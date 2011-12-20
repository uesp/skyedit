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

	ON_BN_CLICKED(IDC_EDIT_LIGHT, OnBnClickedEditLight)
	ON_BN_CLICKED(IDC_SELECT_LIGHT, OnBnClickedSelectLight)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_LIGHT, OnDropLight)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_LIGHT, OnDropLight)

	ON_BN_CLICKED(IDC_EDIT_PROJECTILE, OnBnClickedEditProjectile)
	ON_BN_CLICKED(IDC_SELECT_PROJECTILE, OnBnClickedSelectProjectile)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_PROJECTILE, OnDropProjectile)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_PROJECTILE, OnDropProjectile)

	ON_BN_CLICKED(IDC_EDIT_PERK, OnBnClickedEditPerk)
	ON_BN_CLICKED(IDC_SELECT_PERK, OnBnClickedSelectPerk)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_PERK, OnDropPerk)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_PERK, OnDropPerk)

	ON_BN_CLICKED(IDC_EDIT_DUALCAST, OnBnClickedEditDualCast)
	ON_BN_CLICKED(IDC_SELECT_DUALCAST, OnBnClickedSelectDualCast)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DUALCAST, OnDropDualCast)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DUALCAST, OnDropDualCast)

	ON_BN_CLICKED(IDC_EDIT_SECONDSPELL, OnBnClickedEditSecondSpell)
	ON_BN_CLICKED(IDC_SELECT_SECONDSPELL, OnBnClickedSelectSecondSpell)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SECONDSPELL, OnDropSecondSpell)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SECONDSPELL, OnDropSecondSpell)

	ON_BN_CLICKED(IDC_EDIT_EXPLOSION, OnBnClickedEditExplosion)
	ON_BN_CLICKED(IDC_SELECT_EXPLOSION, OnBnClickedSelectExplosion)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EXPLOSION, OnDropExplosion)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EXPLOSION, OnDropExplosion)

	ON_BN_CLICKED(IDC_EDIT_ART1, OnBnClickedEditArt1)
	ON_BN_CLICKED(IDC_SELECT_ART1, OnBnClickedSelectArt1)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ART1, OnDropArt1)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ART1, OnDropArt1)

	ON_BN_CLICKED(IDC_EDIT_ART2, OnBnClickedEditArt2)
	ON_BN_CLICKED(IDC_SELECT_ART2, OnBnClickedSelectArt2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ART2, OnDropArt2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ART2, OnDropArt2)

	ON_BN_CLICKED(IDC_EDIT_ART3, OnBnClickedEditArt3)
	ON_BN_CLICKED(IDC_SELECT_ART3, OnBnClickedSelectArt3)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ART3, OnDropArt3)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ART3, OnDropArt3)

	ON_BN_CLICKED(IDC_EDIT_ART4, OnBnClickedEditArt4)
	ON_BN_CLICKED(IDC_SELECT_ART4, OnBnClickedSelectArt4)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ART4, OnDropArt4)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ART4, OnDropArt4)

	ON_BN_CLICKED(IDC_EDIT_SHADER1, OnBnClickedEditShader1)
	ON_BN_CLICKED(IDC_SELECT_SHADER1, OnBnClickedSelectShader1)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SHADER1, OnDropShader1)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SHADER1, OnDropShader1)

	ON_BN_CLICKED(IDC_EDIT_SHADER2, OnBnClickedEditShader2)
	ON_BN_CLICKED(IDC_SELECT_SHADER2, OnBnClickedSelectShader2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SHADER2, OnDropShader2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SHADER2, OnDropShader2)

	ON_BN_CLICKED(IDC_EDIT_IMPACTSET1, OnBnClickedEditImpactSet1)
	ON_BN_CLICKED(IDC_SELECT_IMPACTSET1, OnBnClickedSelectImpactSet1)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMPACTSET1, OnDropImpactSet1)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMPACTSET1, OnDropImpactSet1)

	ON_BN_CLICKED(IDC_EDIT_IMPACTSET2, OnBnClickedEditImpactSet2)
	ON_BN_CLICKED(IDC_SELECT_IMPACTSET2, OnBnClickedSelectImpactSet2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMPACTSET2, OnDropImpactSet2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMPACTSET2, OnDropImpactSet2)

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

	ADD_SRRECUIFIELDS( SR_FIELD_EFFECTPLAYRATE,		IDC_EFFECTPLAYRATE,		10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE,			IDC_ACTORVALUE,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTTYPE,			IDC_CASTTYPE,			10,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,			IDC_UNKNOWN1,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,			IDC_UNKNOWN2,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,			IDC_UNKNOWN3,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,			IDC_UNKNOWN4,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN5,			IDC_UNKNOWN5,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN6,			IDC_UNKNOWN6,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN7,			IDC_UNKNOWN7,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN8,			IDC_UNKNOWN8,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN9,			IDC_UNKNOWN9,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN10,			IDC_UNKNOWN10,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN13,			IDC_UNKNOWN13,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN14,			IDC_UNKNOWN14,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN15,			IDC_UNKNOWN15,			10,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_LIGHT,				IDC_LIGHT,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SHADER1,			IDC_SHADER1,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SHADER2,			IDC_SHADER2,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ART1,				IDC_ART1,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ART2,				IDC_ART2,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ART3,				IDC_ART3,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ART4,				IDC_ART4,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IMPACTSET1,			IDC_IMPACTSET1,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IMPACTSET2,			IDC_IMPACTSET2,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PERK,				IDC_PERK,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_EXPLOSION,			IDC_EXPLOSION,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DUALCAST,			IDC_DUALCAST,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SECONDSPELL,		IDC_SECONDSPELL,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PROJECTILE,			IDC_PROJECTILE,			200,	0)

	ADD_SRRECUIFIELDS( SR_FIELD_HOSTILE,			IDC_HOSTILECHECK,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_RECOVER,			IDC_RECOVERCHECK,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_DETRIMENTAL,		IDC_DETRIMENTALCHECK,	0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_PERCENTMAG,			IDC_PERCENTMAGCHECK,	0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_NOAREA,				IDC_NOAREACHECK,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SELFONLY,			IDC_SELFONLYCHECK,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_FXPERSIST,			IDC_FXPERSISTCHECK,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_BOUND,				IDC_BOUNDCHECK,			0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_WARD,				IDC_WARDCHECK,			0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG1,		IDC_UNKNOWNCHECK1,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG2,		IDC_UNKNOWNCHECK2,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG3,		IDC_UNKNOWNCHECK3,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG4,		IDC_UNKNOWNCHECK4,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG5,		IDC_UNKNOWNCHECK5,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG6,		IDC_UNKNOWNCHECK6,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG7,		IDC_UNKNOWNCHECK7,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG8,		IDC_UNKNOWNCHECK8,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG9,		IDC_UNKNOWNCHECK9,		0,		0)
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

	DDX_Control(pDX, IDC_DNAME, m_DName);
	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
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

	DDX_Control(pDX, IDC_EFFECTPLAYRATE,	m_EffectPlayRate);
	DDX_Control(pDX, IDC_ACTORVALUE,		m_ActorValue);
	DDX_Control(pDX, IDC_CASTTYPE,			m_CastType);
	
	DDX_Control(pDX, IDC_UNKNOWN1,			m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2,			m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3,			m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4,			m_Unknown4);
	DDX_Control(pDX, IDC_UNKNOWN5,			m_Unknown5);
	DDX_Control(pDX, IDC_UNKNOWN6,			m_Unknown6);
	DDX_Control(pDX, IDC_UNKNOWN7,			m_Unknown7);
	DDX_Control(pDX, IDC_UNKNOWN8,			m_Unknown8);
	DDX_Control(pDX, IDC_UNKNOWN9,			m_Unknown9);
	DDX_Control(pDX, IDC_UNKNOWN10,			m_Unknown10);
	DDX_Control(pDX, IDC_UNKNOWN13,			m_Unknown13);
	DDX_Control(pDX, IDC_UNKNOWN14,			m_Unknown14);
	DDX_Control(pDX, IDC_UNKNOWN15,			m_Unknown15);
	
	DDX_Control(pDX, IDC_LIGHT,				m_Light);
	DDX_Control(pDX, IDC_SHADER1,			m_Shader1);
	DDX_Control(pDX, IDC_SHADER2,			m_Shader2);
	DDX_Control(pDX, IDC_ART1,				m_Art1);
	DDX_Control(pDX, IDC_ART2,				m_Art2);
	DDX_Control(pDX, IDC_ART3,				m_Art3);
	DDX_Control(pDX, IDC_ART4,				m_Art4);
	DDX_Control(pDX, IDC_IMPACTSET1,		m_ImpactSet1);
	DDX_Control(pDX, IDC_IMPACTSET2,		m_ImpactSet2);
	DDX_Control(pDX, IDC_PERK,				m_Perk);
	DDX_Control(pDX, IDC_EXPLOSION,			m_Explosion);
	DDX_Control(pDX, IDC_DUALCAST,			m_DualCast);
	DDX_Control(pDX, IDC_SECONDSPELL,		m_SecondSpell);
	DDX_Control(pDX, IDC_PROJECTILE,		m_Projectile);
	
	DDX_Control(pDX, IDC_WARDCHECK,			m_WardCheck);
	DDX_Control(pDX, IDC_NOAREACHECK,		m_NoAreaCheck);
	DDX_Control(pDX, IDC_UNKNOWNCHECK1,		m_UnknownCheck1);
	DDX_Control(pDX, IDC_UNKNOWNCHECK2,		m_UnknownCheck2);
	DDX_Control(pDX, IDC_UNKNOWNCHECK3,		m_UnknownCheck3);
	DDX_Control(pDX, IDC_UNKNOWNCHECK4,		m_UnknownCheck4);
	DDX_Control(pDX, IDC_UNKNOWNCHECK5,		m_UnknownCheck5);
	DDX_Control(pDX, IDC_UNKNOWNCHECK6,		m_UnknownCheck6);
	DDX_Control(pDX, IDC_UNKNOWNCHECK7,		m_UnknownCheck7);
	DDX_Control(pDX, IDC_UNKNOWNCHECK8,		m_UnknownCheck8);
	DDX_Control(pDX, IDC_UNKNOWNCHECK9,		m_UnknownCheck9);
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

  SrFillComboList(m_SchoolList,	s_SrMagicSchools,		0);
  SrFillComboList(m_TypeList,	s_SrMagicTypes,			0);
  SrFillComboList(m_CastType,	s_SrEffectCastTypes,	0);
  SrFillComboList(m_ActorValue,	s_SrActorValues,		0);
  
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

	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_HOSTILE,		m_HostileCheck.GetCheck() != 0);
	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_RECOVER,		m_RecoverCheck.GetCheck() != 0);
	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_DETRIMENTAL,	m_DetrimentalCheck.GetCheck() != 0);
	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_PERCENTMAG,	m_PercentMagCheck.GetCheck() != 0);
	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_SELF,		m_SelfCheck.GetCheck() != 0);
	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_FXPERSIST,	m_FXPersistCheck.GetCheck() != 0);
	//FlipFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_BOUND,		m_BoundCheck.GetCheck() != 0);
}


void CSrMgefView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetInputRecord());
	if (pMgef == NULL) return;

	//m_HostileCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_HOSTILE));
	//m_RecoverCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_RECOVER));
	//m_DetrimentalCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_DETRIMENTAL));
	//m_PercentMagCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_PERCENTMAG));
	//m_SelfCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_SELF));
	//m_FXPersistCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_FXPERSIST));
	//m_BoundCheck.SetCheck(CheckFlagBits(pMgef->GetEffectData().Flags, SR_MGEFFLAG_BOUND));
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



void CSrMgefView::OnBnClickedEditPerk()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Perk, SR_NAME_PERK);
}


void CSrMgefView::OnBnClickedSelectPerk()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Perk, SR_NAME_PERK, &CSrPerkRecord::s_FieldMap);
}


void CSrMgefView::OnDropPerk (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Perk, SR_NAME_PERK, 1);
}


void CSrMgefView::OnBnClickedEditLight()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Light, SR_NAME_PROJ);
}


void CSrMgefView::OnBnClickedSelectLight()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Light, SR_NAME_LIGH, &CSrLighRecord::s_FieldMap);
}


void CSrMgefView::OnDropLight (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Light, SR_NAME_LIGH, 1);
}


void CSrMgefView::OnBnClickedEditProjectile()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Projectile, SR_NAME_PROJ);
}


void CSrMgefView::OnBnClickedSelectProjectile()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Projectile, SR_NAME_PROJ, &CSrProjRecord::s_FieldMap);
}


void CSrMgefView::OnDropProjectile (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Projectile, SR_NAME_PROJ, 1);
}


void CSrMgefView::OnBnClickedEditExplosion()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Explosion, SR_NAME_EXPL);
}


void CSrMgefView::OnBnClickedSelectExplosion()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Explosion, SR_NAME_EXPL, &CSrExplRecord::s_FieldMap);
}


void CSrMgefView::OnDropExplosion (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Explosion, SR_NAME_EXPL, 1);
}


void CSrMgefView::OnBnClickedEditSecondSpell()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_SecondSpell, SR_NAME_SPEL);
}


void CSrMgefView::OnBnClickedSelectSecondSpell()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, SR_NAME_SPEL, &CSrSpelRecord::s_FieldMap);
}


void CSrMgefView::OnDropSecondSpell (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_SecondSpell, SR_NAME_SPEL, 1);
}


void CSrMgefView::OnBnClickedEditDualCast()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_DualCast, SR_NAME_DUAL);
}


void CSrMgefView::OnBnClickedSelectDualCast()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_DualCast, SR_NAME_DUAL, &CSrDualRecord::s_FieldMap);
}


void CSrMgefView::OnDropDualCast (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_DualCast, SR_NAME_DUAL, 1);
}


void CSrMgefView::OnBnClickedEditArt1()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Art1, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectArt1()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Art1, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropArt1 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Art1, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditArt2()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Art2, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectArt2()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Art2, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropArt2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Art2, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditArt3()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Art3, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectArt3()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Art3, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropArt3 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Art3, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditArt4()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Art4, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectArt4()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Art4, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropArt4 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Art4, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditImpactSet1()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImpactSet1, SR_NAME_IPDS);
}


void CSrMgefView::OnBnClickedSelectImpactSet1()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImpactSet1, SR_NAME_IPDS, &CSrIpdsRecord::s_FieldMap);
}


void CSrMgefView::OnDropImpactSet1 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ImpactSet1, SR_NAME_IPDS, 1);
}


void CSrMgefView::OnBnClickedEditImpactSet2()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImpactSet2, SR_NAME_IPDS);
}


void CSrMgefView::OnBnClickedSelectImpactSet2()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImpactSet2, SR_NAME_IPDS, &CSrIpdsRecord::s_FieldMap);
}


void CSrMgefView::OnDropImpactSet2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ImpactSet2, SR_NAME_IPDS, 1);
}


void CSrMgefView::OnBnClickedEditShader1()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Shader1, SR_NAME_EFSH);
}


void CSrMgefView::OnBnClickedSelectShader1()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Shader1, SR_NAME_EFSH, &CSrEfshRecord::s_FieldMap);
}


void CSrMgefView::OnDropShader1 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Shader1, SR_NAME_EFSH, 1);
}


void CSrMgefView::OnBnClickedEditShader2()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Shader2, SR_NAME_EFSH);
}


void CSrMgefView::OnBnClickedSelectShader2()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Shader2, SR_NAME_EFSH, &CSrEfshRecord::s_FieldMap);
}


void CSrMgefView::OnDropShader2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Shader2, SR_NAME_EFSH, 1);
}

