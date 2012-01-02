/*===========================================================================
 *
 * File:		SrClasView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srclasview.h"
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

  IMPLEMENT_DYNCREATE(CSrClasView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrClasView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrClasView, CSrRecordDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrClasView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrClasView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,	IDC_DESCRIPTION,	256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,		IDC_UNKNOWN4,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN5,		IDC_UNKNOWN5,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN6,		IDC_UNKNOWN6,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN7,		IDC_UNKNOWN7,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN8,		IDC_UNKNOWN8,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ONEHAND	,		IDC_ONEHAND	,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TWOHAND,		IDC_TWOHAND,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_MARKSMAN,		IDC_MARKSMAN,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_BLOCK,			IDC_BLOCK,			4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SMITHING,		IDC_SMITHING,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_HEAVYARMOR,		IDC_HEAVYARMOR,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_LIGHTARMOR,		IDC_LIGHTARMOR,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_PICKPOCKET,		IDC_PICKPOCKETING,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_LOCKPICKING,	IDC_LOCKPICKING,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SNEAK,			IDC_SNEAK,			4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ALCHEMY,		IDC_ALCHEMY,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SPEECHCRAFT,	IDC_SPEECHCRAFT,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ALTERATION,		IDC_ALTERATION,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CONJURATION,	IDC_CONJURATION,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_DESTRUCTION,	IDC_DESTRUCTION,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ILLUSION,		IDC_ILLUSION,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_RESTORATION,	IDC_RESTORATION,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTING,		IDC_ENCHANTING,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TRAINERSKILL,	IDC_TRAINERSKILL,	32,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TRAINERLEVEL,	IDC_TRAINERLEVEL,	8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClasView Constructor
 *
 *=========================================================================*/
CSrClasView::CSrClasView() : CSrRecordDialog(CSrClasView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrClasView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClasView Destructor
 *
 *=========================================================================*/
CSrClasView::~CSrClasView() 
{
}
/*===========================================================================
 *		End of Class CSrClasView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClasView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrClasView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Unknown4);
	DDX_Control(pDX, IDC_UNKNOWN5, m_Unknown5);
	DDX_Control(pDX, IDC_UNKNOWN6, m_Unknown6);
	DDX_Control(pDX, IDC_UNKNOWN7, m_Unknown7);
	DDX_Control(pDX, IDC_UNKNOWN8, m_Unknown8);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_TRAINERSKILL, m_TrainerSkill);
	DDX_Control(pDX, IDC_TRAINERLEVEL, m_TrainerLevel);
	DDX_Control(pDX, IDC_ONEHAND, m_OneHand);
	DDX_Control(pDX, IDC_TWOHAND, m_TwoHand);
	DDX_Control(pDX, IDC_MARKSMAN, m_Marksman);
	DDX_Control(pDX, IDC_BLOCK, m_Block);
	DDX_Control(pDX, IDC_SMITHING, m_Smithing);
	DDX_Control(pDX, IDC_HEAVYARMOR, m_HeavyArmor);
	DDX_Control(pDX, IDC_LIGHTARMOR, m_LightArmor);
	DDX_Control(pDX, IDC_PICKPOCKETING, m_Pickpocketing);
	DDX_Control(pDX, IDC_LOCKPICKING, m_Lockpicking);
	DDX_Control(pDX, IDC_SNEAK, m_Sneak);
	DDX_Control(pDX, IDC_ALCHEMY, m_Alchemy);
	DDX_Control(pDX, IDC_SPEECHCRAFT, m_Speechcraft);
	DDX_Control(pDX, IDC_ALTERATION, m_Alteration);
	DDX_Control(pDX, IDC_CONJURATION, m_Conjuration);
	DDX_Control(pDX, IDC_DESTRUCTION, m_Destruction);
	DDX_Control(pDX, IDC_ILLUSION, m_Illusion);
	DDX_Control(pDX, IDC_RESTORATION, m_Restoration);
	DDX_Control(pDX, IDC_ENCHANTING, m_Enchanting);
}
/*===========================================================================
 *		End of Class Method CSrClasView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrClasView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrClasView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrClasView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrClasView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClasView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrClasView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SrFillComboList(m_TrainerSkill, s_SrSkillTypes, 0, -SR_SKILL_ONEHAND);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrClasView::OnInitialUpdate()
 *=========================================================================*/
