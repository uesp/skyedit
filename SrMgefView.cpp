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
IMPLEMENT_DYNCREATE(CSrMgefView, CSrRecordDialog);

const srmgeftypedlginfo_t g_EffectTypeDlgInfos[] =
{
	{ SR_NAME_NULL, 1, -1 }, //0
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 1, -1 },
	{ SR_NAME_NULL, 2, -1 },
	{ SR_NAME_NULL, 0,  0 },	//Agression
	{ SR_NAME_NULL, 0,  1 },	//Confidence
	{ SR_NAME_NULL, 0,  0 },	//Agression
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 }, //10
	{ SR_NAME_NULL, 0, 54 },	//Invisibility
	{ SR_NAME_LIGH, 0, -1 },
	{ SR_NAME_NULL, 0, -1 }, //Unused
	{ SR_NAME_NULL, 0, -1 }, //Unused
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_WEAP, 0, -1 },
	{ SR_NAME_NPC_, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 }, //20
	{ SR_NAME_NULL, 0, 53 },	//Paralysis
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0,  1 },	//Confidence
	{ SR_NAME_HAZD, 0, -1 },	
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 }, //30
	{ SR_NAME_NULL, 1, -1 },
	{ SR_NAME_NULL, 1, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_KYWD, 1, -1 }, //No weight?
	{ SR_NAME_SPEL, 0, -1 },
	{ SR_NAME_RACE, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0,  1 },	//Confidence
	{ SR_NAME_ENCH, 0, -1 },
	{ SR_NAME_HAZD, 0, -1 }, //40
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0,  1 },	//Confidence
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 },
	{ SR_NAME_NULL, 0, -1 }
};
		
const dword g_EffectTypeDlgInfoCount = sizeof(g_EffectTypeDlgInfos) / sizeof(g_EffectTypeDlgInfos[0]);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrMgefView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrMgefView, CSrRecordDialog)
	ON_WM_CONTEXTMENU()

	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropKeywords)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropKeywords)

	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_COUNTEREFFECTS, OnDropCounterEffects)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_COUNTEREFFECTS, OnDropCounterEffects)

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

	ON_BN_CLICKED(IDC_EDIT_EFFECTOBJECT, OnBnClickedEditEffectObject)
	ON_BN_CLICKED(IDC_SELECT_EFFECTOBJECT, OnBnClickedSelectEffectObject)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EFFECTOBJECT, OnDropEffectObject)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EFFECTOBJECT, OnDropEffectObject)

	ON_BN_CLICKED(IDC_EDIT_EXPLOSION, OnBnClickedEditExplosion)
	ON_BN_CLICKED(IDC_SELECT_EXPLOSION, OnBnClickedSelectExplosion)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EXPLOSION, OnDropExplosion)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EXPLOSION, OnDropExplosion)

	ON_BN_CLICKED(IDC_EDIT_HITEFFECTART, OnBnClickedEditHitEffectArt)
	ON_BN_CLICKED(IDC_SELECT_HITEFFECTART, OnBnClickedSelectHitEffectArt)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_HITEFFECTART, OnDropHitEffectArt)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_HITEFFECTART, OnDropHitEffectArt)

	ON_BN_CLICKED(IDC_EDIT_CASTINGART, OnBnClickedEditCastingArt)
	ON_BN_CLICKED(IDC_SELECT_CASTINGART, OnBnClickedSelectCastingArt)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_CASTINGART, OnDropCastingArt)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_CASTINGART, OnDropCastingArt)

	ON_BN_CLICKED(IDC_EDIT_ENCHANTART, OnBnClickedEditEnchantArt)
	ON_BN_CLICKED(IDC_SELECT_ENCHANTART, OnBnClickedSelectEnchantArt)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ENCHANTART, OnDropEnchantArt)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ENCHANTART, OnDropEnchantArt)

	ON_BN_CLICKED(IDC_EDIT_EQUIPABILITY, OnBnClickedEditEquipAbility)
	ON_BN_CLICKED(IDC_SELECT_EQUIPABILITY, OnBnClickedSelectEquipAbility)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EQUIPABILITY, OnDropEquipAbility)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EQUIPABILITY, OnDropEquipAbility)

	ON_BN_CLICKED(IDC_EDIT_HITSHADER, OnBnClickedEditHitShader)
	ON_BN_CLICKED(IDC_SELECT_HITSHADER, OnBnClickedSelectHitShader)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_HITSHADER, OnDropHitShader)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_HITSHADER, OnDropHitShader)

	ON_BN_CLICKED(IDC_EDIT_ENCHANTSHADER, OnBnClickedEditEnchantShader)
	ON_BN_CLICKED(IDC_SELECT_ENCHANTSHADER, OnBnClickedSelectEnchantShader)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ENCHANTSHADER, OnDropEnchantShader)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ENCHANTSHADER, OnDropEnchantShader)

	ON_BN_CLICKED(IDC_EDIT_IMPACTSET, OnBnClickedEditImpactSet)
	ON_BN_CLICKED(IDC_SELECT_IMPACTSET, OnBnClickedSelectImpactSet)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMPACTSET, OnDropImpactSet)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMPACTSET, OnDropImpactSet)

	ON_BN_CLICKED(IDC_EDIT_IMAGESPACEMOD, OnBnClickedEditImageSpaceMod)
	ON_BN_CLICKED(IDC_SELECT_IMAGESPACEMOD, OnBnClickedSelectImageSpaceMod)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMAGESPACEMOD, OnDropImageSpaceMod)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMAGESPACEMOD, OnDropImageSpaceMod)

	ON_BN_CLICKED(IDC_EDIT_MENU, OnBnClickedEditMenu)
	ON_BN_CLICKED(IDC_SELECT_MENU, OnBnClickedSelectMenu)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MENU, OnDropMenu)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MENU, OnDropMenu)

	ON_BN_CLICKED(IDC_EDIT_SOUNDDRAW, OnBnClickedEditDrawSound)
	ON_BN_CLICKED(IDC_SELECT_SOUNDDRAW, OnBnClickedSelectDrawSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDDRAW, OnDropDrawSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDDRAW, OnDropDrawSound)

	ON_BN_CLICKED(IDC_EDIT_SOUNDCHARGE, OnBnClickedEditChargeSound)
	ON_BN_CLICKED(IDC_SELECT_SOUNDCHARGE, OnBnClickedSelectChargeSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDCHARGE, OnDropChargeSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDCHARGE, OnDropChargeSound)

	ON_BN_CLICKED(IDC_EDIT_SOUNDREADY, OnBnClickedEditReadySound)
	ON_BN_CLICKED(IDC_SELECT_SOUNDREADY, OnBnClickedSelectReadySound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDREADY, OnDropReadySound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDREADY, OnDropReadySound)

	ON_BN_CLICKED(IDC_EDIT_SOUNDRELEASE, OnBnClickedEditReleaseSound)
	ON_BN_CLICKED(IDC_SELECT_SOUNDRELEASE, OnBnClickedSelectReleaseSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDRELEASE, OnDropReleaseSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDRELEASE, OnDropReleaseSound)

	ON_BN_CLICKED(IDC_EDIT_SOUNDCASTLOOP, OnBnClickedEditCastLoopSound)
	ON_BN_CLICKED(IDC_SELECT_SOUNDCASTLOOP, OnBnClickedSelectCastLoopSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDCASTLOOP, OnDropCastLoopSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDCASTLOOP, OnDropCastLoopSound)

	ON_BN_CLICKED(IDC_EDIT_SOUNDONHIT, OnBnClickedEditOnHitSound)
	ON_BN_CLICKED(IDC_SELECT_SOUNDONHIT, OnBnClickedSelectOnHitSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDONHIT, OnDropOnHitSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDONHIT, OnDropOnHitSound)

	ON_BN_CLICKED(IDC_ADD_COUNTEREFFECTS, &CSrMgefView::OnBnClickedAddCountereffects)
	ON_BN_CLICKED(IDC_EDIT_COUNTEREFFECTS, &CSrMgefView::OnBnClickedEditCountereffects)
	ON_BN_CLICKED(IDC_DEL_COUNTEREFFECTS, &CSrMgefView::OnBnClickedDelCountereffects)
	ON_CBN_SELCHANGE(IDC_EFFECTTYPE, &CSrMgefView::OnCbnSelchangeEffecttype)
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
	ADD_SRRECUIFIELDS( SR_FIELD_CONDITIONCOUNT,		IDC_CONDITION_BUTTON,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILLLEVEL,			IDC_SKILLLEVEL,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_BASECOST,			IDC_BASECOST,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTINGDELAY,		IDC_CASTINGDELAY,		10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_AREA,				IDC_AREA,				10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_DUALCASTSCALE,		IDC_DUALCASTSCALE,		10,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_SKILLUSAGEMULT,		IDC_SKILLUSAGEMULT,		10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE,			IDC_ACTORVALUE,			64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE2,		IDC_ACTORVALUE2,		64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SECONDAVWEIGHT,		IDC_SECONDAVWEIGHT,		10,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_SCHOOL,				IDC_SCHOOLLIST,			64,		IDS_TT_SCHOOL)
	ADD_SRRECUIFIELDS( SR_FIELD_RESISTTYPE,			IDC_RESISTLIST,			64,		IDS_TT_EFFECTTYPE)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTTYPE,			IDC_CASTTYPE,			64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_DELIVERYTYPE,		IDC_DELIVERYTYPE,		64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_EFFECTTYPE,			IDC_EFFECTTYPE,			64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUNDVOLUME,		IDC_SOUNDVOLUME,		64,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_TAPERCURVE,			IDC_TAPERCURVE,			10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TAPERDURATION,		IDC_TAPERDURATION,		10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TAPERWEIGHT,		IDC_TAPERWEIGHT,		10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SCRIPTAIDATASCORE,	IDC_SCRIPTAIDATASCORE,	10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SCRIPTAIDATADELAY,	IDC_SCRIPTAIDATADELAY,	10,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_DISPELEFFECTS,		IDC_DISPELEFFECTS,		10,		0)

	ADD_SRRECUIFIELDS( SR_FIELD_LIGHT,				IDC_LIGHT,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_HITSHADER,			IDC_HITSHADER,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTSHADER,		IDC_ENCHANTSHADER,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_CASTINGART,			IDC_CASTINGART,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_HITEFFECTART,		IDC_HITEFFECTART,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTART,			IDC_ENCHANTART,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_EQUIPABILITY,		IDC_EQUIPABILITY,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IMPACTSET,			IDC_IMPACTSET,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IMAGESPACEMOD,		IDC_IMAGESPACEMOD,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PERK,				IDC_PERK,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_EXPLOSION,			IDC_EXPLOSION,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DUALCAST,			IDC_DUALCAST,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_EFFECTOBJECT,		IDC_EFFECTOBJECT,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PROJECTILE,			IDC_PROJECTILE,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MENU,				IDC_MENU,				200,	0)

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
	m_pScriptList = &m_Scripts;
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

	DDX_Control(pDX, IDC_DNAME, m_Description);
	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);

	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_Conditions);
	DDX_Control(pDX, IDC_BASECOST, m_BaseCost);
	DDX_Control(pDX, IDC_SKILLLEVEL, m_SkillLevel);

	DDX_Control(pDX, IDC_SKILLUSAGEMULT,	m_SkillUsageMult);
	DDX_Control(pDX, IDC_ACTORVALUE,		m_ActorValue);
	DDX_Control(pDX, IDC_ACTORVALUE2,		m_ActorValue2);
	DDX_Control(pDX, IDC_SECONDAVWEIGHT,	m_SecondAVWeight);

	DDX_Control(pDX, IDC_SCHOOLLIST,	m_SchoolList);
	DDX_Control(pDX, IDC_RESISTLIST,	m_ResistList);
	DDX_Control(pDX, IDC_CASTTYPE,		m_CastType);
	DDX_Control(pDX, IDC_DELIVERYTYPE,	m_DeliveryType);
	DDX_Control(pDX, IDC_EFFECTTYPE,	m_EffectType);
	DDX_Control(pDX, IDC_SOUNDVOLUME,	m_SoundVolume);
	DDX_Control(pDX, IDC_DUALCASTSCALE,	m_DualCastScale);
	DDX_Control(pDX, IDC_CASTINGDELAY,	m_CastingDelay);
	DDX_Control(pDX, IDC_AREA,	m_Area);

	DDX_Control(pDX, IDC_TAPERCURVE,			m_TaperCurve);
	DDX_Control(pDX, IDC_TAPERDURATION,			m_TaperDuration);
	DDX_Control(pDX, IDC_TAPERWEIGHT,			m_TaperWeight);
	DDX_Control(pDX, IDC_SCRIPTAIDATASCORE,		m_ScriptAIDataScore);
	DDX_Control(pDX, IDC_SCRIPTAIDATADELAY,		m_ScriptAIDataDelay);

	DDX_Control(pDX, IDC_LIGHT,				m_Light);
	DDX_Control(pDX, IDC_HITSHADER,			m_HitShader);
	DDX_Control(pDX, IDC_ENCHANTSHADER,		m_EnchantShader);
	DDX_Control(pDX, IDC_CASTINGART,		m_CastingArt);
	DDX_Control(pDX, IDC_HITEFFECTART,		m_HitEffectArt);
	DDX_Control(pDX, IDC_ENCHANTART,		m_EnchantArt);
	DDX_Control(pDX, IDC_EQUIPABILITY,		m_EquipAbility);
	DDX_Control(pDX, IDC_IMPACTSET,			m_ImpactSet);
	DDX_Control(pDX, IDC_IMAGESPACEMOD,		m_ImageSpaceMod);
	DDX_Control(pDX, IDC_PERK,				m_Perk);
	DDX_Control(pDX, IDC_EXPLOSION,			m_Explosion);
	DDX_Control(pDX, IDC_DUALCAST,			m_DualCast);
	DDX_Control(pDX, IDC_EFFECTOBJECT,		m_EffectObject);
	DDX_Control(pDX, IDC_MENU,				m_Menu);
	DDX_Control(pDX, IDC_PROJECTILE,		m_Projectile);

	DDX_Control(pDX, IDC_SCRIPT_LIST, m_Scripts);
	DDX_Control(pDX, IDC_DELIVERYTYPE, m_DeliveryType);
	DDX_Control(pDX, IDC_MAGICFLAGS, m_MagicFlags);
	DDX_Control(pDX, IDC_COUNTEREFFECTS, m_CounterEffects);
	DDX_Control(pDX, IDC_DISPELEFFECTS, m_DispelEffectsCheck);
	DDX_Control(pDX, IDC_SOUNDDRAW, m_DrawSound);
	DDX_Control(pDX, IDC_SOUNDCHARGE, m_ChargeSound);
	DDX_Control(pDX, IDC_SOUNDREADY, m_ReadySound);
	DDX_Control(pDX, IDC_SOUNDRELEASE, m_ReleaseSound);
	DDX_Control(pDX, IDC_SOUNDCASTLOOP, m_CastLoopSound);
	DDX_Control(pDX, IDC_SOUNDONHIT, m_OnHitSound);
	DDX_Control(pDX, IDC_EDIT_EFFECTOBJECT, m_EditEffectObject);
	DDX_Control(pDX, IDC_SELECT_EFFECTOBJECT, m_SelectEffectObject);
	DDX_Control(pDX, IDC_EFFECTOBJECTLABEL, m_EffectObjectLabel);
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
	void CSrMgefView::AssertValid() const { CSrRecordDialog::AssertValid(); }
	void CSrMgefView::Dump(CDumpContext& dc) const { CSrRecordDialog::Dump(dc); }
#endif
/*===========================================================================
 *		End of CSrMgefView Diagnostics
 *=========================================================================*/


void CSrMgefView::FillMagicFlagList (void)
{	
	m_MagicFlags.ResetContent();

	SrAddListBoxItem(m_MagicFlags, "Hostile",					SR_MGEFFLAG_HOSTILE);
	SrAddListBoxItem(m_MagicFlags, "Recover",					SR_MGEFFLAG_RECOVER);
	SrAddListBoxItem(m_MagicFlags, "Detrimental",				SR_MGEFFLAG_DETRIMENTAL);
	SrAddListBoxItem(m_MagicFlags, "Snap To Navmesh",			SR_MGEFFLAG_SNAPTONAVMESH);
	SrAddListBoxItem(m_MagicFlags, "No Hit Event",				SR_MGEFFLAG_NOHITEVENT);
	SrAddListBoxItem(m_MagicFlags, "No Duration",				SR_MGEFFLAG_NODURATION);
	SrAddListBoxItem(m_MagicFlags, "No Magnitude",				SR_MGEFFLAG_NOMAGNITUDE);
	SrAddListBoxItem(m_MagicFlags, "No Area",					SR_MGEFFLAG_NOAREA);
	SrAddListBoxItem(m_MagicFlags, "Effects Persist",			SR_MGEFFLAG_FXPERSIST);
	SrAddListBoxItem(m_MagicFlags, "No Recast",					SR_MGEFFLAG_NORECAST);
	SrAddListBoxItem(m_MagicFlags, "Gory Visual",				SR_MGEFFLAG_GORYVISUAL);
	SrAddListBoxItem(m_MagicFlags, "Hide In Interface",			SR_MGEFFLAG_HIDEINUI);
	SrAddListBoxItem(m_MagicFlags, "Power Affects Magnitude",	SR_MGEFFLAG_POWERMAGNITUDE);
	SrAddListBoxItem(m_MagicFlags, "Power Affects Duration",	SR_MGEFFLAG_POWERDURATION);
	SrAddListBoxItem(m_MagicFlags, "Painless",					SR_MGEFFLAG_PAINLESS);
	SrAddListBoxItem(m_MagicFlags, "No Hit Effect",				SR_MGEFFLAG_NOHITEFFECT);
	SrAddListBoxItem(m_MagicFlags, "No Death Dispell",			SR_MGEFFLAG_NODEATHDISPELL);
	SrAddListBoxItem(m_MagicFlags, "0x40000000",				SR_MGEFFLAG_WARD);
	SrAddListBoxItem(m_MagicFlags, "0x80000000",				SR_MGEFFLAG_80000000);
}


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
	SrFillComboList(m_ResistList,	s_SrMagicResistTypes,	0);
	SrFillComboList(m_CastType,		s_SrEffectCastTypes,	0);
	SrFillComboList(m_ActorValue,	s_SrActorValues,		0);
	SrFillComboList(m_ActorValue2,	s_SrActorValues,		0);
	SrFillComboList(m_EffectType,	s_SrMagicEffectTypes,	0);
	SrFillComboList(m_DeliveryType,	s_SrMagicDeliveryTypes,	0);
	SrFillComboList(m_SoundVolume,	s_SrSoundVolumes,		0);

	FillMagicFlagList();
	
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

	pMgef->GetEffectData().Flags = GetMagicFlags();
	GetCounterEffects(pMgef);
	GetEffectSounds(pMgef);
}


void CSrMgefView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	UpdateEffectTypeControls();

	CSrMgefRecord* pMgef = SrCastClassNull(CSrMgefRecord, GetInputRecord());
	if (pMgef == NULL) return;

	SetMagicFlags(pMgef->GetEffectData().Flags);
	SetCounterEffects(pMgef);
	SetEffectSounds(pMgef);
}


void CSrMgefView::SetMagicFlags (const dword Flags)
{
	dword FlagValue;

	for (int i = 0; i < m_MagicFlags.GetCount(); ++i)
	{
		FlagValue = m_MagicFlags.GetItemData(i);
		m_MagicFlags.SetSel(i, ((Flags & FlagValue) != 0));
	}

}


void CSrMgefView::GetCounterEffects (CSrMgefRecord* pEffect)
{
	CSrSubrecord*		pSubrecord;
	CSrFormidSubrecord* pFormid;
	CString				Buffer;
	srformid_t			FormID;

	if (pEffect == NULL) return;

	pEffect->DeleteSubrecords(SR_NAME_ESCE);

	for (int i = 0; i < m_CounterEffects.GetCount(); ++i)
	{
		m_CounterEffects.GetText(i, Buffer);

		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		if (FormID == 0) continue;

		pSubrecord = pEffect->AddInitNewSubrecord(SR_NAME_ESCE);
		pFormid = SrCastClassNull(CSrFormidSubrecord, pSubrecord);
		if (pFormid) pFormid->SetValue(FormID);
	}

}


void CSrMgefView::SetCounterEffects (CSrMgefRecord* pEffect)
{
	CSrSubrecord*		pSubrecord;
	CSrFormidSubrecord* pFormid;
	CString				Buffer;
	int					Position;

	if (pEffect == NULL)
	{
		m_CounterEffects.ResetContent();
		return;
	}

	pSubrecord = pEffect->FindFirstSubrecord(SR_NAME_ESCE, Position);

	while (pSubrecord)
	{
		pFormid = SrCastClass(CSrFormidSubrecord, pSubrecord);

		if (pFormid)
		{
			const char* pString = m_pRecordHandler->GetEditorID(pFormid->GetValue());

			if (pString) 
			{
				SrAddListBoxItem(m_CounterEffects, pString, pFormid->GetValue());
			}
			else
			{
				Buffer.Format("0x%08X", pFormid->GetValue());
				SrAddListBoxItem(m_CounterEffects, Buffer, pFormid->GetValue());
			}
		}

		pSubrecord = pEffect->FindNextSubrecord(SR_NAME_ESCE, Position);
	}

}


void CSrMgefView::GetEffectSounds (CSrMgefRecord* pEffect)
{
	CSrMgefSnddArray Sounds;
	srmgefsndddata_t Data;
	CString          Buffer;
	srformid_t		 FormID;

	if (pEffect == NULL) return;

	m_DrawSound.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!Buffer.IsEmpty())
	{
		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		Data.SoundID = FormID;
		Data.Type    = SR_MAGICSOUND_SHEATH;
		if (FormID != 0) Sounds.Add(Data);
	}

	m_ChargeSound.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!Buffer.IsEmpty())
	{
		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		Data.SoundID = FormID;
		Data.Type    = SR_MAGICSOUND_CHARGE;
		if (FormID != 0) Sounds.Add(Data);
	}

	m_ReadySound.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!Buffer.IsEmpty())
	{
		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		Data.SoundID = FormID;
		Data.Type    = SR_MAGICSOUND_READY;
		if (FormID != 0) Sounds.Add(Data);
	}

	m_ReleaseSound.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!Buffer.IsEmpty())
	{
		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		Data.SoundID = FormID;
		Data.Type    = SR_MAGICSOUND_RELEASE;
		if (FormID != 0) Sounds.Add(Data);
	}

	m_CastLoopSound.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!Buffer.IsEmpty())
	{
		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		Data.SoundID = FormID;
		Data.Type    = SR_MAGICSOUND_CASTLOOP;
		if (FormID != 0) Sounds.Add(Data);
	}

	m_OnHitSound.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!Buffer.IsEmpty())
	{
		FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
		Data.SoundID = FormID;
		Data.Type    = SR_MAGICSOUND_ONHIT;
		if (FormID != 0) Sounds.Add(Data);
	}

	pEffect->SetSounds(Sounds);
}


void CSrMgefView::SetEffectSounds (CSrMgefRecord* pEffect)
{
	const char* pString;
	CString     Buffer;

	if (pEffect == NULL || pEffect->GetSoundArray() == NULL)  
	{
		m_DrawSound.SetWindowTextA("");
		m_ChargeSound.SetWindowTextA("");
		m_ReadySound.SetWindowTextA("");
		m_ReleaseSound.SetWindowTextA("");
		m_CastLoopSound.SetWindowTextA("");		
		m_OnHitSound.SetWindowTextA("");
		return;
	}

	CSrMgefSnddArray* pSounds = pEffect->GetSoundArray();
	
	for (dword i = 0; i < pSounds->GetSize(); ++i)
	{
		pString = m_pRecordHandler->GetEditorID((*pSounds)[i].SoundID);

		if (pString == NULL)
		{
			Buffer.Format("0x%08X", (*pSounds)[i].SoundID);
			pString = Buffer;
		}

		switch ((*pSounds)[i].Type)
		{
			case SR_MAGICSOUND_SHEATH:
				m_DrawSound.SetWindowTextA(pString);
				break;
			case SR_MAGICSOUND_CHARGE:	
				m_ChargeSound.SetWindowTextA(pString);
				break;
			case SR_MAGICSOUND_READY:
				m_ReadySound.SetWindowTextA(pString);
				break;
			case SR_MAGICSOUND_RELEASE:
				m_ReleaseSound.SetWindowTextA(pString);
				break;
			case SR_MAGICSOUND_CASTLOOP:
				m_CastLoopSound.SetWindowTextA(pString);
				break;
			case SR_MAGICSOUND_ONHIT:
				m_OnHitSound.SetWindowTextA(pString);
				break;
		}
	}

	 
}


dword CSrMgefView::GetMagicFlags (void)
{
	dword Flags = 0;

	if (m_DispelEffectsCheck.GetCheck()) Flags = SR_MGEFFLAG_DISPELLEFFECTS;

	for (int i = 0; i < m_MagicFlags.GetCount(); ++i)
	{
		if (m_MagicFlags.GetSel(i)) Flags |= m_MagicFlags.GetItemData(i);
	}

	return Flags;
}


void CSrMgefView::OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
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


void CSrMgefView::OnBnClickedEditEffectObject()
{
	int     ListIndex = m_EffectType.GetCurSel();
	int     EffectType = 0;

	if (m_pDlgHandler == NULL) return;

	if (ListIndex >= 0) EffectType = m_EffectType.GetItemData(ListIndex);
	if (EffectType < 0 || EffectType >= g_EffectTypeDlgInfoCount) return;

	srrectype_t RecType = CSrMgefRecord::GetEffectObjectRecordType(EffectType);
	m_pDlgHandler->EditRecordHelper(&m_EffectObject, RecType);
}


void CSrMgefView::OnBnClickedSelectEffectObject()
{
	int     ListIndex = m_EffectType.GetCurSel();
	int     EffectType = 0;

	if (m_pDlgHandler == NULL) return;

	if (ListIndex >= 0) EffectType = m_EffectType.GetItemData(ListIndex);
	if (EffectType < 0 || EffectType >= g_EffectTypeDlgInfoCount) return;

	srrectype_t RecType = CSrMgefRecord::GetEffectObjectRecordType(EffectType);

	switch (EffectType)
	{
		case 12: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrLighRecord::s_FieldMap); break;
		case 17: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrWeapRecord::s_FieldMap); break;
		case 18: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrNpc_Record::s_FieldMap); break;
		case 25: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrHazdRecord::s_FieldMap); break;
		case 34: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrKywdRecord::s_FieldMap); break;
		case 35: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrSpelRecord::s_FieldMap); break;
		case 36: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrRaceRecord::s_FieldMap); break;
		case 39: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrEnchRecord::s_FieldMap); break;
		case 40: m_pDlgHandler->SelectRecordHelper(&m_EffectObject, RecType, &CSrHazdRecord::s_FieldMap); break;
		default:
			break;
	}
	

}


void CSrMgefView::OnDropEffectObject (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	int     ListIndex = m_EffectType.GetCurSel();
	int     EffectType = 0;

	if (m_pDlgHandler == NULL) return;

	if (ListIndex >= 0) EffectType = m_EffectType.GetItemData(ListIndex);
	if (EffectType < 0 || EffectType >= g_EffectTypeDlgInfoCount) return;
		
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_EffectObject, CSrMgefRecord::GetEffectObjectRecordType(EffectType), 1);
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


void CSrMgefView::OnBnClickedEditCastingArt()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_CastingArt, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectCastingArt()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_CastingArt, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropCastingArt (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_CastingArt, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditHitEffectArt()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_HitEffectArt, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectHitEffectArt()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_HitEffectArt, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropHitEffectArt (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_HitEffectArt, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditEnchantArt()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EnchantArt, SR_NAME_ARTO);
}


void CSrMgefView::OnBnClickedSelectEnchantArt()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_EnchantArt, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrMgefView::OnDropEnchantArt (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_EnchantArt, SR_NAME_ARTO, 1);
}


void CSrMgefView::OnBnClickedEditEquipAbility()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EquipAbility, SR_NAME_SPEL);
}


void CSrMgefView::OnBnClickedSelectEquipAbility()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_EquipAbility, SR_NAME_SPEL, &CSrSpelRecord::s_FieldMap);
}


void CSrMgefView::OnDropEquipAbility (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_EquipAbility, SR_NAME_SPEL, 1);
}


void CSrMgefView::OnBnClickedEditImpactSet()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImpactSet, SR_NAME_IPDS);
}


void CSrMgefView::OnBnClickedSelectImpactSet()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImpactSet, SR_NAME_IPDS, &CSrIpdsRecord::s_FieldMap);
}


void CSrMgefView::OnDropImpactSet (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ImpactSet, SR_NAME_IPDS, 1);
}


void CSrMgefView::OnBnClickedEditImageSpaceMod()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImageSpaceMod, SR_NAME_IMAD);
}


void CSrMgefView::OnBnClickedSelectImageSpaceMod()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImageSpaceMod, SR_NAME_IMAD, &CSrImadRecord::s_FieldMap);
}


void CSrMgefView::OnDropImageSpaceMod (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ImageSpaceMod, SR_NAME_IMAD, 1);
}


void CSrMgefView::OnBnClickedEditHitShader()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_HitShader, SR_NAME_EFSH);
}


void CSrMgefView::OnBnClickedSelectHitShader()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_HitShader, SR_NAME_EFSH, &CSrEfshRecord::s_FieldMap);
}


void CSrMgefView::OnDropHitShader (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_HitShader, SR_NAME_EFSH, 1);
}


void CSrMgefView::OnBnClickedEditEnchantShader()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EnchantShader, SR_NAME_EFSH);
}


void CSrMgefView::OnBnClickedSelectEnchantShader()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_EnchantShader, SR_NAME_EFSH, &CSrEfshRecord::s_FieldMap);
}


void CSrMgefView::OnDropEnchantShader (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_EnchantShader, SR_NAME_EFSH, 1);
}


void CSrMgefView::OnBnClickedEditMenu()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Menu, SR_NAME_STAT);
}


void CSrMgefView::OnBnClickedSelectMenu()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Menu, SR_NAME_STAT, &CSrStatRecord::s_FieldMap);
}


void CSrMgefView::OnDropMenu (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_Menu, SR_NAME_STAT, 1);
}


void CSrMgefView::OnDropCounterEffects (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_CounterEffects, SR_NAME_MGEF, 1);
}


void CSrMgefView::OnBnClickedEditDrawSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_DrawSound, SR_NAME_SNDR);
}


void CSrMgefView::OnBnClickedSelectDrawSound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_DrawSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrMgefView::OnDropDrawSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_DrawSound, SR_NAME_SNDR, 1);
}


void CSrMgefView::OnBnClickedEditChargeSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ChargeSound, SR_NAME_SNDR);
}


void CSrMgefView::OnBnClickedSelectChargeSound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ChargeSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrMgefView::OnDropChargeSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ChargeSound, SR_NAME_SNDR, 1);
}


void CSrMgefView::OnBnClickedEditReadySound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ReadySound, SR_NAME_SNDR);
}


void CSrMgefView::OnBnClickedSelectReadySound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ReadySound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrMgefView::OnDropReadySound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ReadySound, SR_NAME_SNDR, 1);
}


void CSrMgefView::OnBnClickedEditReleaseSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ReleaseSound, SR_NAME_SNDR);
}


void CSrMgefView::OnBnClickedSelectReleaseSound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ReleaseSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrMgefView::OnDropReleaseSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ReleaseSound, SR_NAME_SNDR, 1);
}


void CSrMgefView::OnBnClickedEditCastLoopSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_CastLoopSound, SR_NAME_SNDR);
}


void CSrMgefView::OnBnClickedSelectCastLoopSound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_CastLoopSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrMgefView::OnDropCastLoopSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_CastLoopSound, SR_NAME_SNDR, 1);
}


void CSrMgefView::OnBnClickedEditOnHitSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_OnHitSound, SR_NAME_SNDR);
}


void CSrMgefView::OnBnClickedSelectOnHitSound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_OnHitSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrMgefView::OnDropOnHitSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_OnHitSound, SR_NAME_SNDR, 1);
}


/*===========================================================================
 *
 * Class CSrMgefView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrMgefView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
    CSrRecordDialog::OnContextMenu(pWnd, Point);
}
/*===========================================================================
 *		End of Class Event CSrMgefView::OnContextMenu()
 *=========================================================================*/


void CSrMgefView::OnBnClickedAddCountereffects()
{
	CString    Buffer;
	bool		Result;
	 
	Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_MGEF, &CSrMgefRecord::s_FieldMap);
	if (!Result) return;

	CSrRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);
	SrAddListBoxItem(m_CounterEffects, Buffer, pRecord ? pRecord->GetFormID() : 0);
}


void CSrMgefView::OnBnClickedEditCountereffects()
{
	CString		Buffer;
	int			ListIndex = m_CounterEffects.GetCurSel();
	bool		Result;

	if (ListIndex >= 0) m_CounterEffects.GetText(ListIndex, Buffer);
	 
	Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_MGEF, &CSrMgefRecord::s_FieldMap);
	if (!Result) return;

	CSrRecord* pRecord = m_pRecordHandler->FindEditorID(Buffer);

	if (ListIndex < 0)
	{
		SrAddListBoxItem(m_CounterEffects, Buffer, pRecord ? pRecord->GetFormID() : 0);
	}
	else
	{
		m_CounterEffects.DeleteString(ListIndex);
		ListIndex = m_CounterEffects.InsertString(ListIndex, Buffer);
		m_CounterEffects.SetItemData(ListIndex, pRecord ? pRecord->GetFormID() : 0);	
	}

}


void CSrMgefView::OnBnClickedDelCountereffects()
{
	int	ListIndex = m_CounterEffects.GetCurSel();
	if (ListIndex < 0) return; 

	m_CounterEffects.DeleteString(ListIndex);

	if (ListIndex > 0)
		m_CounterEffects.SetCurSel(ListIndex - 1);
	else
		m_CounterEffects.SetCurSel(0);
}


void CSrMgefView::OnCbnSelchangeEffecttype()
{
	UpdateEffectTypeControls();
}


void CSrMgefView::UpdateEffectTypeControls (void)
{
	int ListIndex = m_EffectType.GetCurSel();
	if (ListIndex < 0) return;

	int EffectType = m_EffectType.GetItemData(ListIndex);
	if (EffectType < 0 || EffectType >= g_EffectTypeDlgInfoCount) return;

	if (g_EffectTypeDlgInfos[EffectType].RecordType != SR_NAME_NULL)
	{
		m_EffectObject.EnableWindow(true);
		m_EditEffectObject.EnableWindow(true);
		m_SelectEffectObject.EnableWindow(true);
		m_EffectObjectLabel.SetWindowTextA(GetSrRecTypeName(g_EffectTypeDlgInfos[EffectType].RecordType));
	}
	else
	{
		m_EffectObject.EnableWindow(false);
		m_EditEffectObject.EnableWindow(false);
		m_SelectEffectObject.EnableWindow(false);
		m_EffectObjectLabel.SetWindowTextA("<none>");
	}

	bool EnableAV1 = g_EffectTypeDlgInfos[EffectType].NumAV > 0;
	bool EnableAV2 = g_EffectTypeDlgInfos[EffectType].NumAV > 1;

	m_ActorValue.EnableWindow(EnableAV1);
	m_ActorValue2.EnableWindow(EnableAV2);
	m_SecondAVWeight.EnableWindow(EnableAV2);

	if (g_EffectTypeDlgInfos[EffectType].ForceAV1 >= 0)
	{
		FindComboBoxItemData(m_ActorValue, g_EffectTypeDlgInfos[EffectType].ForceAV1, true);
	}
}