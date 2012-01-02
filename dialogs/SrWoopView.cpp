/*===========================================================================
 *
 * File:		SrWoopView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srwoopview.h"
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

  IMPLEMENT_DYNCREATE(CSrWoopView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrWoopView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrWoopView, CSrRecordDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrWoopView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrWoopView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,	 IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,		 IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,    IDC_ITEMNAME,		256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_TRANSLATION, IDC_TRANSLATION,	256,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWoopView Constructor
 *
 *=========================================================================*/
CSrWoopView::CSrWoopView() : CSrRecordDialog(CSrWoopView::IDD) 
{
}
/*===========================================================================
 *		End of Class CSrWoopView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWoopView Destructor
 *
 *=========================================================================*/
CSrWoopView::~CSrWoopView() 
{
}
/*===========================================================================
 *		End of Class CSrWoopView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWoopView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrWoopView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_TRANSLATION, m_Translation);
}
/*===========================================================================
 *		End of Class Method CSrWoopView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrWoopView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrWoopView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrWoopView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrWoopView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWoopView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrWoopView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrWoopView::OnInitialUpdate()
 *=========================================================================*/

