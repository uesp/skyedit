/*===========================================================================
 *
 * File:		SrRaceView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srraceview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrRaceView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrRaceView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrRaceView, CSrRecordDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrRaceView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrRaceView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_ITEMNAME,		128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,	IDC_DESCRIPTION,	256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MALEHEIGHT,		IDC_MALEHEIGHT,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_FEMALEHEIGHT,	IDC_FEMALEHEIGHT,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE1,	IDC_ACTORVALUE1,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE2,	IDC_ACTORVALUE2,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE3,	IDC_ACTORVALUE3,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE4,	IDC_ACTORVALUE4,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE5,	IDC_ACTORVALUE5,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE6,	IDC_ACTORVALUE6,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE7,	IDC_ACTORVALUE7,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ACTORVALUE7,	IDC_ACTORVALUE7,	64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL1,			IDC_ACTORSKILL1,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL2,			IDC_ACTORSKILL2,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL3,			IDC_ACTORSKILL3,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL4,			IDC_ACTORSKILL4,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL5,			IDC_ACTORSKILL5,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL6,			IDC_ACTORSKILL6,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SKILL7,			IDC_ACTORSKILL7,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_BODYPARTS,		IDC_BODYDATA,		64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_RACEUNKNOWN1,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_RACEUNKNOWN2,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_RACEFLAGS,		64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,		IDC_RACEUNKNOWN4,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN5,		IDC_RACEUNKNOWN5,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN6,		IDC_RACEUNKNOWN6,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN7,		IDC_RACEUNKNOWN7,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN8,		IDC_RACEUNKNOWN8,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN9,		IDC_RACEUNKNOWN9,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN10,		IDC_RACEUNKNOWN10,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN11,		IDC_RACEUNKNOWN11,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN12,		IDC_RACEUNKNOWN12,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN13,		IDC_RACEUNKNOWN13,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN14,		IDC_RACEUNKNOWN14,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN15,		IDC_RACEUNKNOWN15,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN16,		IDC_RACEUNKNOWN16,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN17,		IDC_RACEUNKNOWN17,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN18,		IDC_RACEUNKNOWN18,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN19,		IDC_RACEUNKNOWN19,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN20,		IDC_RACEUNKNOWN20,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN21,		IDC_RACEUNKNOWN21,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN22,		IDC_RACEUNKNOWN22,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN23,		IDC_RACEUNKNOWN23,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN24,		IDC_RACEUNKNOWN24,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN25,		IDC_RACEUNKNOWN25,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN26,		IDC_RACEUNKNOWN26,	16,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRaceView Constructor
 *
 *=========================================================================*/
CSrRaceView::CSrRaceView() : CSrRecordDialog(CSrRaceView::IDD), m_BasicPage(m_RaceInfo), m_ModelPage(m_RaceInfo), 
	m_MovePage(m_RaceInfo), m_UnknownPage(m_RaceInfo), m_AttackPage(m_RaceInfo), m_FacePage(m_RaceInfo),
	m_MaleHead1Page(m_RaceInfo, true), m_FemaleHead1Page(m_RaceInfo, false),
	m_MaleTintPage(m_RaceInfo, true), m_FemaleTintPage(m_RaceInfo, false)
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrRaceView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRaceView Destructor
 *
 *=========================================================================*/
CSrRaceView::~CSrRaceView() 
{
}
/*===========================================================================
 *		End of Class CSrRaceView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRaceView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrRaceView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_TAB_CTRL, m_TabControl);
}
/*===========================================================================
 *		End of Class Method CSrRaceView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrRaceView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrRaceView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrRaceView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrRaceView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRaceView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrRaceView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();
	
	m_ModelPage.m_pDlgHandler = m_pDlgHandler;
	m_AttackPage.m_pDlgHandler = m_pDlgHandler;
	m_MovePage.m_pDlgHandler = m_pDlgHandler;
	m_BasicPage.m_pDlgHandler = m_pDlgHandler;
	m_UnknownPage.m_pDlgHandler = m_pDlgHandler;
	m_FacePage.m_pDlgHandler = m_pDlgHandler;
	m_MaleHead1Page.m_pDlgHandler = m_pDlgHandler;
	m_FemaleHead1Page.m_pDlgHandler = m_pDlgHandler;
	m_MaleTintPage.m_pDlgHandler = m_pDlgHandler;
	m_FemaleTintPage.m_pDlgHandler = m_pDlgHandler;
	m_ModelPage.m_pParent = this;
	m_AttackPage.m_pParent = this;
	m_MovePage.m_pParent = this;
	m_BasicPage.m_pParent = this;
	m_UnknownPage.m_pParent = this;
	m_FacePage.m_pParent = this;
	m_MaleHead1Page.m_pParent = this;
	m_FemaleHead1Page.m_pParent = this;
	m_MaleTintPage.m_pParent = this;
	m_FemaleTintPage.m_pParent = this;

	m_BasicPage.Create(IDD_RACE_BASICPAGE, &m_TabControl);
	m_MovePage.Create(IDD_RACE_MOVEPAGE, &m_TabControl);
	m_AttackPage.Create(IDD_RACE_ATTACKPAGE, &m_TabControl);
	m_ModelPage.Create(IDD_RACE_MODELPAGE, &m_TabControl);
	m_UnknownPage.Create(IDD_RACE_UNKNOWNPAGE, &m_TabControl);
	m_FacePage.Create(IDD_RACE_FACEPAGE, &m_TabControl);
	m_MaleHead1Page.Create(IDD_RACE_HEADPAGE1, &m_TabControl);
	m_FemaleHead1Page.Create(IDD_RACE_HEADPAGE1, &m_TabControl);
	m_MaleTintPage.Create(IDD_RACE_TINTPAGE, &m_TabControl);
	m_FemaleTintPage.Create(IDD_RACE_TINTPAGE, &m_TabControl);
  
	m_TabControl.AddTab("Basic Data", &m_BasicPage);
	m_TabControl.AddTab("Model", &m_ModelPage);
	m_TabControl.AddTab("Attack", &m_AttackPage);
	m_TabControl.AddTab("Movement", &m_MovePage);
	m_TabControl.AddTab("Face", &m_FacePage);
	m_TabControl.AddTab("Male Head", &m_MaleHead1Page);
	m_TabControl.AddTab("Female Head", &m_FemaleHead1Page);
	m_TabControl.AddTab("Male Tint", &m_MaleTintPage);
	m_TabControl.AddTab("Female Tint", &m_FemaleTintPage);
	m_TabControl.AddTab("Unknown", &m_UnknownPage);
	m_TabControl.SetPage(0);

	AddTabControl(m_TabControl);

	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrRaceView::OnInitialUpdate()
 *=========================================================================*/


void CSrRaceView::GetControlData (void)
{
	CSrRecordDialog::GetControlData();

	m_ModelPage.GetControlData();
	m_BasicPage.GetControlData();
	m_AttackPage.GetControlData();
	m_MovePage.GetControlData();
	m_UnknownPage.GetControlData();
	m_FacePage.GetControlData();
	m_MaleHead1Page.GetControlData();
	m_FemaleHead1Page.GetControlData();
	m_MaleTintPage.GetControlData();
	m_FemaleTintPage.GetControlData();

	CSrRaceRecord* pRace = SrCastClass(CSrRaceRecord, GetOutputRecord());

	m_RaceInfo.CheckMaleHeadMarker();
	m_RaceInfo.CheckFemaleHeadMarker();

	if (pRace) pRace->CreateFromRaceInfo(m_RaceInfo);
}


void CSrRaceView::SetControlData (void)
{
	CSrRaceRecord* pRace = SrCastClass(CSrRaceRecord, GetInputRecord());

	if (pRace)
	{
		m_RaceInfo.Destroy();
		pRace->CreateRaceInfo(m_RaceInfo);
		m_RaceInfo.CheckNew();
	}

	CSrRecordDialog::SetControlData();

	m_ModelPage.SetControlData();
	m_BasicPage.SetControlData();
	m_AttackPage.SetControlData();
	m_MovePage.SetControlData();
	m_UnknownPage.SetControlData();
	m_FacePage.SetControlData();
	m_MaleHead1Page.SetControlData();
	m_FemaleHead1Page.SetControlData();
	m_MaleTintPage.SetControlData();
	m_FemaleTintPage.SetControlData();
}


CWnd* CSrRaceView::GetNextControl (const bool Previous)
{
	CWnd* pWnd = GetFocus();
	if (pWnd == NULL) return NULL;

	CWnd* pParent = pWnd->GetParent();
	if (pParent == NULL) return NULL;

	CWnd* pParent1 = pParent->GetParent();
	if (pParent1 == NULL) return NULL;

	if (pParent1 == &m_TabControl)
	{
		if (m_TabControl.GetCurrentPage() == NULL) return NULL;
		return m_TabControl.GetCurrentPage()->GetNextDlgTabItem(pWnd, Previous);
	}
	else
	{
		return GetNextDlgTabItem(pWnd, Previous);
	}

	return NULL;
}


BOOL CSrRaceView::PreTranslateMessage(MSG* pMsg)
{

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
	{
		CWnd* pWnd = GetNextControl(GetKeyState(VK_SHIFT) != 0);

		if (pWnd)
		{
			pWnd->SetFocus();
			return TRUE;
		}
	}

	return CSrRecordDialog::PreTranslateMessage(pMsg);
}
