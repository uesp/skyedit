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
#include "SrConditionDlg.h"


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
  //{{AFX_MSG_MAP(CSrMgefView)
  //}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONDITION_BUTTON, &CSrMgefView::OnBnClickedConditionButton)
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
	ADD_SRRECUIFIELDS( SR_FIELD_CONDITIONCOUNT,		IDC_CONDITION_BUTTON,	64,		IDS_TT_EFFECTTYPE)
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


void CSrMgefView::OnBnClickedConditionButton()
{
	CSrConditionDlg ConditionDlg;
	int Result = ConditionDlg.DoModal(GetInputRecord(), &m_ConditionsCopy);
	if (Result == IDOK) m_ConditionsChanged = true;

	CString Buffer;
	Buffer.Format("%d", m_ConditionsCopy.GetSize());
	m_Conditions.SetWindowText(Buffer);
}

