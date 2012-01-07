/*===========================================================================
 *
 * File:		SrCamsView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srcamsview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrCamsView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrCamsView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrCamsView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_IMAGESPACE, &CSrCamsView::OnBnClickedEditImagespace)
	ON_BN_CLICKED(IDC_SELECT_IMAGESPACE, &CSrCamsView::OnBnClickedSelectImagespace)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMAGESPACE, OnDropImageSpace)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMAGESPACE, OnDropImageSpace)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrCamsView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrCamsView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_IMAGESPACE,		IDC_IMAGESPACE,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_X1,				IDC_X1,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_Y1,				IDC_Y1,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_Z1,				IDC_Z1,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_X2,				IDC_X2,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_Y2,				IDC_Y2,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_Z2,				IDC_Z2,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3a,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,		IDC_UNKNOWN4,		8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCamsView Constructor
 *
 *=========================================================================*/
CSrCamsView::CSrCamsView() : CSrRecordDialog(CSrCamsView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrCamsView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCamsView Destructor
 *
 *=========================================================================*/
CSrCamsView::~CSrCamsView() 
{
}
/*===========================================================================
 *		End of Class CSrCamsView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCamsView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrCamsView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_IMAGESPACE, m_ImageSpace);
	DDX_Control(pDX, IDC_X1, m_X1);
	DDX_Control(pDX, IDC_Y1, m_Y1);
	DDX_Control(pDX, IDC_Z1, m_Z1);
	DDX_Control(pDX, IDC_X2, m_X2);
	DDX_Control(pDX, IDC_Y2, m_Y2);
	DDX_Control(pDX, IDC_Z2, m_Z2);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3a, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Unknown4);
}
/*===========================================================================
 *		End of Class Method CSrCamsView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrCamsView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrCamsView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrCamsView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrCamsView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrCamsView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrCamsView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrCamsView::OnInitialUpdate()
 *=========================================================================*/



void CSrCamsView::OnBnClickedEditImagespace()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImageSpace, SR_NAME_IMAD);
}


void CSrCamsView::OnBnClickedSelectImagespace()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImageSpace, SR_NAME_IMAD, &CSrImadRecord::s_FieldMap);
}


void CSrCamsView::OnDropImageSpace (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  *pResult = DropRecordHelper(pDropItems, &m_ImageSpace, SR_NAME_IMAD, 1);
}
