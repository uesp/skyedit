/*===========================================================================
 *
 * File:		SrStatView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srstatview.h"
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

  IMPLEMENT_DYNCREATE(CSrStatView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrStatView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrStatView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_MATERIAL, OnBnClickedEditMaterial)
	ON_BN_CLICKED(IDC_SELECT_MATERIAL, OnBnClickedSelectMaterial)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrStatView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrStatView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,	IDC_EDITORID,	128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,		IDC_FORMID,		128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_SCALE,      IDC_SCALE,		12,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,      IDC_MODEL,		200,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_MATERIAL,   IDC_MATERIAL,	200,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrStatView Constructor
 *
 *=========================================================================*/
CSrStatView::CSrStatView() : CSrRecordDialog(CSrStatView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrStatView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrStatView Destructor
 *
 *=========================================================================*/
CSrStatView::~CSrStatView() 
{
}
/*===========================================================================
 *		End of Class CSrStatView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrStatView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrStatView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SCALE, m_Scale);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_MATERIAL, m_Material);
	DDX_Control(pDX, IDC_MODEL, m_Model);
}
/*===========================================================================
 *		End of Class Method CSrStatView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrStatView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrStatView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrStatView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrStatView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrStatView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrStatView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrStatView::OnInitialUpdate()
 *=========================================================================*/


void CSrStatView::OnBnClickedEditMaterial()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Material, SR_NAME_MATO);
 }


 void CSrStatView::OnBnClickedSelectMaterial()
 {
 	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Material, SR_NAME_MATO, &CSrMatoRecord::s_FieldMap);
 }