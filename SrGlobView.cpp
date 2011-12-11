/*===========================================================================
 *
 * File:		SrKywdView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srglobview.h"
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

  IMPLEMENT_DYNCREATE(CSrGlobView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrGlobView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrGlobView, CSrRecordDialog)
  //{{AFX_MSG_MAP(CSrGlobView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrGlobView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrGlobView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,	IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,		IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,      IDC_VALUE,		32,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPE,       IDC_TYPELIST,	32,		IDS_TT_TYPE)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGlobView Constructor
 *
 *=========================================================================*/
CSrGlobView::CSrGlobView() : CSrRecordDialog(CSrGlobView::IDD) 
{
  //{{AFX_DATA_INIT(CSrGlobView)
  //}}AFX_DATA_INIT
	  
  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrGlobView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGlobView Destructor
 *
 *=========================================================================*/
CSrGlobView::~CSrGlobView() 
{

}
/*===========================================================================
 *		End of Class CSrGlobView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGlobView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrGlobView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrGlobView)
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_TYPELIST, m_Type);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrGlobView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrGlobView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrGlobView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrGlobView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrGlobView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGlobView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrGlobView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  m_Type.AddString("long");
  m_Type.AddString("float");
  m_Type.AddString("short");  

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrGlobView::OnInitialUpdate()
 *=========================================================================*/
