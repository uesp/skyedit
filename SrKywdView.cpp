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
#include "srkywdview.h"
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

  IMPLEMENT_DYNCREATE(CSrKywdView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrKywdView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrKywdView, CSrRecordDialog)
  //{{AFX_MSG_MAP(CSrKywdView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrKywdView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrKywdView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,	IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,		IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_CNAM,       IDC_CNAME,		256,	IDS_TT_CNAME)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrKywdView Constructor
 *
 *=========================================================================*/
CSrKywdView::CSrKywdView() : CSrRecordDialog(CSrKywdView::IDD) 
{
	m_EnchantType = 0;
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrKywdView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrKywdView Destructor
 *
 *=========================================================================*/
CSrKywdView::~CSrKywdView() 
{

}
/*===========================================================================
 *		End of Class CSrKywdView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrKywdView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrKywdView::DoDataExchange (CDataExchange* pDX) {
  CSrRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrKywdView)
	DDX_Control(pDX, IDC_CNAME, m_CName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrKywdView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrKywdView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrKywdView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrKywdView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrKywdView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrKywdView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrKywdView::OnInitialUpdate (void) {
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrKywdView::OnInitialUpdate()
 *=========================================================================*/
