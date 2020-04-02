/*===========================================================================
 *
 * File:		SrGmstView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srgmstview.h"
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

  IMPLEMENT_DYNCREATE(CSrGmstView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrGmstView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrGmstView, CSrRecordDialog)
  //{{AFX_MSG_MAP(CSrGmstView)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrGmstView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrGmstView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,	IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,		IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,      IDC_VALUE,		256,	IDS_TT_VALUE)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGmstView Constructor
 *
 *=========================================================================*/
CSrGmstView::CSrGmstView() : CSrRecordDialog(CSrGmstView::IDD) 
{
  //{{AFX_DATA_INIT(CSrGmstView)
  //}}AFX_DATA_INIT
	  
  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrGmstView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGmstView Destructor
 *
 *=========================================================================*/
CSrGmstView::~CSrGmstView() 
{

}
/*===========================================================================
 *		End of Class CSrGmstView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGmstView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrGmstView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrGmstView)
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrGmstView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrGmstView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrGmstView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrGmstView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrGmstView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrGmstView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrGmstView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrGmstView::OnInitialUpdate()
 *=========================================================================*/


int CSrGmstView::OnPreSaveRecord (void)
{
	CString Buffer;

	if (m_pRecordHandler == NULL) return SR_RESULT_ERROR;
	m_EditorID.GetWindowText(Buffer);
	Buffer.Trim();

	if (!Buffer.IsEmpty()) 
	{
		char Type = tolower(Buffer[0]);

		switch (Type)
		{
		case 's':
		case 'i':
		case 'f':
		case 'b':
			break;
		default:
			AddSrGeneralError("A Game Setting editor ID should start with one of i/f/s/b!");
			return SR_RESULT_ERROR;
		}	
	}

	return CSrRecordDialog::OnPreSaveRecord();
}