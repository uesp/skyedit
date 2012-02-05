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
#include "dialogs/SrMgefSnddEditDlg.h"


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
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_SoundListInit[] = {
	{ SR_FIELD_SOUND,		180,	LVCFMT_CENTER },
	{ SR_FIELD_VALUE,		50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_SoundFields[] = {
	{ "Sound",		SR_FIELD_SOUND,		0, NULL },
	{ "Value",		SR_FIELD_VALUE,		0, NULL },	
	{ NULL,			SR_FIELD_NONE,		0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrMgefView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrMgefView, CSrRecordDialog)
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditSoundMsg)
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

	ON_BN_CLICKED(IDC_DELETESOUND, &CSrMgefView::OnBnClickedDeletesound)
	ON_COMMAND(ID_SNDDLIST_DELETE, &CSrMgefView::OnBnClickedDeletesound)

	ON_BN_CLICKED(IDC_ADDSOUND, &CSrMgefView::OnBnClickedAddsound)
	ON_COMMAND(ID_SNDDLIST_ADD, &CSrMgefView::OnBnClickedAddsound)
	ON_COMMAND(ID_SNDDLIST_EDITRECORD, &CSrMgefView::OnSnddlistEditrecord)
	ON_COMMAND(ID_SNDDLIST_EDIT, &CSrMgefView::OnSnddlistEdit)
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
	DDX_Control(pDX, IDC_SOUND_LIST,		m_Sounds);
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
	m_IsInitialized = false;
	CSrRecordDialog::OnInitialUpdate();

	SrFillComboList(m_SchoolList,	s_SrMagicSchools,		0);
	SrFillComboList(m_TypeList,		s_SrMagicTypes,			0);
	SrFillComboList(m_CastType,		s_SrEffectCastTypes,	0);
	SrFillComboList(m_ActorValue,	s_SrActorValues,		0);
	SrFillComboList(m_Unknown7,		s_SrEffectLinkTypes,	0);

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetInputRecord());
	if (pMgef != NULL && pMgef->GetSoundArray()) m_SoundCopy = *pMgef->GetSoundArray();

	m_Sounds.SetListName("EffectSoundList");
	m_Sounds.SetDragEnable(true);
	m_Sounds.DefaultSettings();
	m_Sounds.SetupCustomList(s_SoundListInit, NULL, s_SoundFields);
	m_Sounds.SetOwner(this);
	m_Sounds.SetColorEnable(false);
	m_Sounds.SetDragType(SR_RLDRAG_CUSTOM);
	m_Sounds.SetSortEnable(false);
	m_Sounds.SetActivateType(SR_RLACTIVATE_RECORD);
	
	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrMgefView::OnInitialUpdate()
 *=========================================================================*/


void CSrMgefView::GetControlData (void)
{
	CSrRecordDialog::GetControlData();

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetOutputRecord());
	if (pMgef == NULL) return;

	pMgef->SetSounds(m_SoundCopy);
	
}


void CSrMgefView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetInputRecord());
	if (pMgef == NULL) return;	

	SetSoundList();
}


void CSrMgefView::SetSoundList (void)
{
	m_Sounds.DeleteAllItems();
	
	for (dword i = 0; i < m_SoundCopy.GetSize(); ++i) 
	{
		AddSoundList(&m_SoundCopy[i]);
	}

	m_Sounds.SelectRecord(0);
}


/*===========================================================================
 *
 * Class CSrMgefView Method - int AddSoundList (pSoundData);
 *
 *=========================================================================*/
int CSrMgefView::AddSoundList (srmgefsndddata_t* pSoundData) 
{
	srrlcustomdata_t CustomData;
	CString          Buffer;
	int				 ListIndex;
	
	CustomData.pRecord   = GetInputRecord();
	CustomData.pUserData = (void *) pSoundData;
	    
	ListIndex = m_Sounds.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);
	
	UpdateSoundList(ListIndex, false);
	return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrMgefView::AddSoundList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefView Method - void UpdateSoundList (ListIndex, Update);
 *
 *=========================================================================*/
void CSrMgefView::UpdateSoundList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t* pCustomData;
	srmgefsndddata_t* pSoundData;
	CString		      Buffer;

	if (GetInputRecord() == NULL) return;

	pCustomData = m_Sounds.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;
	if (Update) m_Sounds.UpdateRecord(ListIndex);

	pSoundData = (srmgefsndddata_t *) pCustomData->pUserData;
	if (pSoundData == NULL) return;

	m_Sounds.SetCustomField(ListIndex, SR_FIELD_SOUND,  GetInputRecord()->GetParent()->GetEditorID(pSoundData->SoundID));
		
	Buffer.Format("%d", pSoundData->Value);
	m_Sounds.SetCustomField(ListIndex, SR_FIELD_VALUE, Buffer);  
}
/*===========================================================================
 *		End of Class Method CSrMgefView::UpdateSoundList()
 *=========================================================================*/


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
	CString Buffer;
	int     Unknown7 = 0;

	if (m_pDlgHandler == NULL) return;

	m_Unknown7.GetWindowText(Buffer);
	GetSrEffectLinkTypeValue(Unknown7, Buffer);

	srrectype_t RecType = CSrMgefRecord::GetSecondRecordType(Unknown7);
	m_pDlgHandler->EditRecordHelper(&m_SecondSpell, RecType);
}


void CSrMgefView::OnBnClickedSelectSecondSpell()
{
	CString Buffer;
	int     Unknown7 = 0;

	if (m_pDlgHandler == NULL) return;

	m_Unknown7.GetWindowText(Buffer);
	GetSrEffectLinkTypeValue(Unknown7, Buffer);

	srrectype_t RecType = CSrMgefRecord::GetSecondRecordType(Unknown7);

	if (RecType == SR_NAME_NULL)
	{
		Buffer.Format("A value of LinkRecType=%d doesn't have an associated record type to select!", Unknown7);
		MessageBox(Buffer, "Warning", MB_OK);
		return;
	}

	switch (Unknown7)
	{
		case 12: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrLighRecord::s_FieldMap); break;
		case 17: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrWeapRecord::s_FieldMap); break;
		case 18: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrNpc_Record::s_FieldMap); break;
		case 25: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrHazdRecord::s_FieldMap); break;
		case 34: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrKywdRecord::s_FieldMap); break;
		case 35: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrSpelRecord::s_FieldMap); break;
		case 36: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrRaceRecord::s_FieldMap); break;
		case 39: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrEnchRecord::s_FieldMap); break;
		case 40: m_pDlgHandler->SelectRecordHelper(&m_SecondSpell, RecType, &CSrHazdRecord::s_FieldMap); break;
		default:
			break;
	}
	

}


void CSrMgefView::OnDropSecondSpell (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	CString Buffer;
	int     Unknown7 = 0;

	if (m_pDlgHandler == NULL) return;

	m_Unknown7.GetWindowText(Buffer);
	GetSrEffectLinkTypeValue(Unknown7, Buffer);

	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SecondSpell, CSrMgefRecord::GetSecondRecordType(Unknown7), 1);
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


void CSrMgefView::OnBnClickedDeletesound()
{
	int ListIndex = m_Sounds.GetSelectedItem();

	if (ListIndex < 0) return;

	m_SoundCopy.Delete(ListIndex);
	m_Sounds.DeleteItem(ListIndex);
	m_Sounds.SelectRecord(ListIndex - 1);
}


void CSrMgefView::OnBnClickedAddsound()
{
	srmgefsndddata_t NewData = { 0, 0 };
	m_SoundCopy.Add(NewData);
	AddSoundList(&m_SoundCopy[m_SoundCopy.GetSize() - 1]);
}


LRESULT CSrMgefView::OnEditSoundMsg (WPARAM wParam, LPARAM lParam) 
{
	srmgefsndddata_t*	pSoundData;
	srrlcustomdata_t*	pCustomData;
	int					ListIndex;
	int					Result;

	ListIndex = m_Sounds.GetSelectedItem();
	if (ListIndex < 0) return -1;

	pCustomData = m_Sounds.GetCustomData(ListIndex);
	if (pCustomData == NULL) return -1;

	pSoundData = (srmgefsndddata_t *) pCustomData->pUserData;
	if (pSoundData == NULL) return -1;
	
	Result = SrEditMgefSnddDlg (pSoundData, m_pRecordHandler, GetInputRecord()->GetFormID());
	if (Result == SR_MGEFSNDDEDITDLG_RESULT_CANCEL) return -1;

	if (Result == SR_MGEFSNDDEDITDLG_RESULT_DELETE) 
	{
		m_SoundCopy.Delete(ListIndex);
		m_Sounds.RemoveItem(ListIndex);
		return -1;
	}
  
	UpdateSoundList(ListIndex, true);
	return (0);
}


void CSrMgefView::OnSnddlistEditrecord()
{
	srmgefsndddata_t*	pSoundData;
	srrlcustomdata_t*	pCustomData;
	int					ListIndex;

	if (m_pDlgHandler == NULL || GetInputRecord()->GetParent() == NULL) return;

	ListIndex = m_Sounds.GetSelectedItem();
	if (ListIndex < 0) return;

	pCustomData = m_Sounds.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	pSoundData = (srmgefsndddata_t *) pCustomData->pUserData;
	if (pSoundData == NULL) return;
	
	CSrRecord* pRecord = GetInputRecord()->GetParent()->FindFormID(pSoundData->SoundID);
	if (pRecord == NULL) return;

	m_pDlgHandler->EditRecord(pRecord);
}


void CSrMgefView::OnSnddlistEdit()
{
	OnEditSoundMsg(0, 0);
}


/*===========================================================================
 *
 * Class CSrMgefView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrMgefView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_SOUND_LIST) 
  {
    Result = Menu.LoadMenu(IDR_MGEFSOUNDLIST_MENU);
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
 *		End of Class Event CSrMgefView::OnContextMenu()
 *=========================================================================*/