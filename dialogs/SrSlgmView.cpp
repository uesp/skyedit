/*===========================================================================
 *
 * File:		SrSlgmView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srslgmview.h"
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

  IMPLEMENT_DYNCREATE(CSrSlgmView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSlgmView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSlgmView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_FILLEDGEM, &CSrSlgmView::OnBnClickedEditFilledgem)
	ON_BN_CLICKED(IDC_SELECT_FILLEDGEM, &CSrSlgmView::OnBnClickedSelectFilledgem)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FILLEDGEM, OnDropFilledGem)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FILLEDGEM, OnDropFilledGem)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSlgmView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrSlgmView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,			IDC_WEIGHT,			16,		IDS_TT_WEIGHT)
	ADD_SRRECUIFIELDS( SR_FIELD_FILLEDGEM,		IDC_FILLEDGEM,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_CAPACITY,		IDC_CAPACITY,	    16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CURRENTSOUL,	IDC_CURRENTSOUL,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_DANGEROUS,		IDC_DANGEROUS,		0,		IDS_TT_DANGEROUS)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSlgmView Constructor
 *
 *=========================================================================*/
CSrSlgmView::CSrSlgmView() : CSrRecordDialog(CSrSlgmView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrSlgmView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSlgmView Destructor
 *
 *=========================================================================*/
CSrSlgmView::~CSrSlgmView() 
{
}
/*===========================================================================
 *		End of Class CSrSlgmView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSlgmView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrSlgmView::DoDataExchange (CDataExchange* pDX) 
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
	DDX_Control(pDX, IDC_CAPACITY, m_Capacity);
	DDX_Control(pDX, IDC_CURRENTSOUL, m_CurrentSoul);
	DDX_Control(pDX, IDC_FILLEDGEM, m_FilledGem);
	DDX_Control(pDX, IDC_DANGEROUS, m_Dangerous);
}
/*===========================================================================
 *		End of Class Method CSrSlgmView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSlgmView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrSlgmView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrSlgmView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrSlgmView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSlgmView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrSlgmView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SrFillComboList(m_Capacity,    s_SrSoulGemTypes, 0);
  SrFillComboList(m_CurrentSoul, s_SrSoulGemTypes, 0);

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrSlgmView::OnInitialUpdate()
 *=========================================================================*/



void CSrSlgmView::OnBnClickedEditFilledgem()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_FilledGem, SR_NAME_SLGM);
}


void CSrSlgmView::OnBnClickedSelectFilledgem()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_FilledGem, SR_NAME_SLGM, &CSrSlgmRecord::s_FieldMap);
}


void CSrSlgmView::OnDropFilledGem (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_FilledGem, SR_NAME_SLGM, 1);
}