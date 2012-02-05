/*===========================================================================
 *
 * File:		SrBookView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srbookview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
IMPLEMENT_DYNCREATE(CSrBookView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrBookView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrBookView, CSrRecordDialog)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_STATICMODEL, OnDropStaticModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_STATICMODEL, OnDropStaticModel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SPELL, OnDropSpell)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SPELL, OnDropSpell)
	ON_BN_CLICKED(IDC_EDIT_STATICMODEL, &CSrBookView::OnBnClickedEditStaticmodel)
	ON_BN_CLICKED(IDC_SELECTSTATICMODEL_BUTTON, &CSrBookView::OnBnClickedSelectstaticmodelButton)
	ON_BN_CLICKED(IDC_SKILLBOOK, &CSrBookView::OnBnClickedSkillbook)
	ON_BN_CLICKED(IDC_SPELLTOME, &CSrBookView::OnBnClickedSpelltome)
	ON_BN_CLICKED(IDC_EDIT_SPELL, &CSrBookView::OnBnClickedEditSpell)
	ON_BN_CLICKED(IDC_SELECTSPELL_BUTTON, &CSrBookView::OnBnClickedSelectspellButton)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrBookView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrBookView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,			IDC_WEIGHT,			16,		IDS_TT_WEIGHT)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
	ADD_SRRECUIFIELDS( SR_FIELD_SPELLTOME,		IDC_SPELLTOME,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILLBOOK,		IDC_SKILLBOOK,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SCROLL,			IDC_NOTETYPE,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CNAM,			IDC_CNAME,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,	IDC_DESCRIPTION,	32000,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PICKUPSOUND,	IDC_PICKUPSOUND,	200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_STATIC,			IDC_STATICMODEL,	200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL,			IDC_SKILL,			0,		0) // Skill/Spell should be last
	ADD_SRRECUIFIELDS( SR_FIELD_SPELL,			IDC_SPELL,			200,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBookView Constructor
 *
 *=========================================================================*/
CSrBookView::CSrBookView() : CSrRecordDialog(CSrBookView::IDD) 
{
	m_pScriptList = &m_Scripts;
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrBookView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBookView Destructor
 *
 *=========================================================================*/
CSrBookView::~CSrBookView() 
{
}
/*===========================================================================
 *		End of Class CSrBookView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBookView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrBookView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_SKILL, m_Skill);
	DDX_Control(pDX, IDC_STATICMODEL, m_StaticModel);
	DDX_Control(pDX, IDC_PICKUPSOUND, m_PickupSound);
	DDX_Control(pDX, IDC_CNAME, m_CName);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_SKILLBOOK, m_SkillBook);
	DDX_Control(pDX, IDC_NOTETYPE, m_NoteType);
	DDX_Control(pDX, IDC_SPELLTOME, m_SpellTome);
	DDX_Control(pDX, IDC_SPELL, m_Spell);
	DDX_Control(pDX, IDC_EDIT_SPELL, m_EditSpellButton);
	DDX_Control(pDX, IDC_SELECTSPELL_BUTTON, m_SelectSpellButton);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_Scripts);
}
/*===========================================================================
 *		End of Class Method CSrBookView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrBookView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrBookView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrBookView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrBookView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBookView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrBookView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  ::SrFillComboList(m_Skill, s_SrSkillTypes, SRE_FILLCOMBO_INCLUDENULL);

  SetControlData();
  EnableSpellSkillControls();
}
/*===========================================================================
 *		End of Class Event CSrBookView::OnInitialUpdate()
 *=========================================================================*/


void CSrBookView::OnBnClickedEditStaticmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_StaticModel, SR_NAME_STAT);
}


void CSrBookView::OnBnClickedSelectstaticmodelButton()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_StaticModel, SR_NAME_STAT, &CSrStatRecord::s_FieldMap);
}


void CSrBookView::OnDropStaticModel (NMHDR* pNotifyStruct, LRESULT* pResult)
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_StaticModel, SR_NAME_STAT, 1);
}


void CSrBookView::OnBnClickedSkillbook()
{
	if (m_SkillBook.GetCheck()) m_SpellTome.SetCheck(0);
	EnableSpellSkillControls();
}


void CSrBookView::OnBnClickedSpelltome()
{
	if (m_SpellTome.GetCheck()) m_SkillBook.SetCheck(0);
	EnableSpellSkillControls();
}


void CSrBookView::EnableSpellSkillControls (void)
{
	bool SkillEnable = m_SkillBook.GetCheck() != 0;
	bool SpellEnable = m_SpellTome.GetCheck() != 0;

	m_Skill.EnableWindow(SkillEnable);

	m_Spell.EnableWindow(SpellEnable);
	m_EditSpellButton.EnableWindow(SpellEnable);
	m_SelectSpellButton.EnableWindow(SpellEnable);
}


void CSrBookView::OnBnClickedEditSpell()
{
	if (m_SpellTome.GetCheck() && m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Spell, SR_NAME_SPEL);
}


void CSrBookView::OnBnClickedSelectspellButton()
{
	if (m_SpellTome.GetCheck() && m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Spell, SR_NAME_SPEL, &CSrSpelRecord::s_FieldMap);
}


void CSrBookView::OnDropSpell (NMHDR* pNotifyStruct, LRESULT* pResult)
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;

	if (m_SpellTome.GetCheck())
		*pResult = DropRecordHelper(pDropItems, &m_Spell, SR_NAME_SPEL, 1);
	else
		*pResult = SRRL_DROPCHECK_ERROR;
}

