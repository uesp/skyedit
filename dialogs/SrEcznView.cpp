/*===========================================================================
 *
 * File:		SrMiscView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srecznview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrEcznView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEcznView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEcznView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_FACTION, &CSrEcznView::OnBnClickedEditFaction)
	ON_BN_CLICKED(IDC_SELECT_FACTION, &CSrEcznView::OnBnClickedSelectFaction)
	ON_BN_CLICKED(IDC_EDIT_LOCATION, &CSrEcznView::OnBnClickedEditLocation)
	ON_BN_CLICKED(IDC_SELECT_LOCATION, &CSrEcznView::OnBnClickedSelectLocation)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_LOCATION, OnDropLocation)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_LOCATION, OnDropLocation)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FACTION, OnDropFaction)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FACTION, OnDropFaction)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrEcznView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrEcznView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_FACTION,		IDC_FACTION,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_LOCATION,		IDC_LOCATION,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_RANK,			IDC_RANK,			4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_MINLEVEL,		IDC_MINLEVEL,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_RESET,			IDC_ZONERESET,		4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_ZONEUNKNOWN1,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_ZONEUNKNOWN2,	4,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,		4,		0)	
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEcznView Constructor
 *
 *=========================================================================*/
CSrEcznView::CSrEcznView() : CSrRecordDialog(CSrEcznView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrEcznView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEcznView Destructor
 *
 *=========================================================================*/
CSrEcznView::~CSrEcznView() 
{
}
/*===========================================================================
 *		End of Class CSrEcznView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEcznView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrEcznView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_RANK, m_Rank);
	DDX_Control(pDX, IDC_MINLEVEL, m_MinLevel);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_FACTION, m_Faction);
	DDX_Control(pDX, IDC_LOCATION, m_Location);
	DDX_Control(pDX, IDC_ZONERESET, m_ZoneReset);
	DDX_Control(pDX, IDC_ZONEUNKNOWN1, m_ZoneUnknown1);
	DDX_Control(pDX, IDC_ZONEUNKNOWN2, m_ZoneUnknown2);
}
/*===========================================================================
 *		End of Class Method CSrEcznView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEcznView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrEcznView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrEcznView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrEcznView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEcznView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrEcznView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrEcznView::OnInitialUpdate()
 *=========================================================================*/



void CSrEcznView::OnBnClickedEditFaction()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Faction, SR_NAME_FACT);
}


void CSrEcznView::OnBnClickedSelectFaction()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Faction, SR_NAME_FACT, &CSrFactRecord::s_FieldMap);
}


void CSrEcznView::OnBnClickedEditLocation()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Location, SR_NAME_LCTN);
}


void CSrEcznView::OnBnClickedSelectLocation()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Location, SR_NAME_LCTN, &CSrLctnRecord::s_FieldMap);
}


void CSrEcznView::OnDropLocation (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Location, SR_NAME_LCTN, 1);
}


void CSrEcznView::OnDropFaction (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Faction, SR_NAME_FACT, 1);
}