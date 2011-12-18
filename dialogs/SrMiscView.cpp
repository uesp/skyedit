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
#include "srmiscview.h"
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

  IMPLEMENT_DYNCREATE(CSrMiscView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrMiscView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrMiscView, CSrRecordDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrMiscView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrMiscView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,			IDC_WEIGHT,			16,		IDS_TT_WEIGHT)
	ADD_SRRECUIFIELDS( SR_FIELD_PICKUPSOUND,	IDC_PICKUPSOUND,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DROPSOUND,		IDC_DROPSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMiscView Constructor
 *
 *=========================================================================*/
CSrMiscView::CSrMiscView() : CSrRecordDialog(CSrMiscView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrMiscView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMiscView Destructor
 *
 *=========================================================================*/
CSrMiscView::~CSrMiscView() 
{
}
/*===========================================================================
 *		End of Class CSrMiscView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMiscView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrMiscView::DoDataExchange (CDataExchange* pDX) 
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
	DDX_Control(pDX, IDC_PICKUPSOUND, m_PickupSound);
	DDX_Control(pDX, IDC_DROPSOUND, m_DropSound);
 }
/*===========================================================================
 *		End of Class Method CSrMiscView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrMiscView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrMiscView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrMiscView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrMiscView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMiscView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrMiscView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrMiscView::OnInitialUpdate()
 *=========================================================================*/

