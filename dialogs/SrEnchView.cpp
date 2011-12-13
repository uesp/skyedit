/*===========================================================================
 *
 * File:		SrEnchView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srenchview.h"
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

  IMPLEMENT_DYNCREATE(CSrEnchView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEnchView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEnchView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_BASEENCHANT, &CSrEnchView::OnBnClickedEditBaseenchant)
	ON_BN_CLICKED(IDC_SELECTBASEENCHANT_BUTTON, &CSrEnchView::OnBnClickedSelectbaseenchantButton)
	ON_BN_CLICKED(IDC_EDIT_ITEMTYPES, &CSrEnchView::OnBnClickedEditItemtypes)
	ON_BN_CLICKED(IDC_SELECTITEMTYPES_BUTTON, &CSrEnchView::OnBnClickedSelectitemtypesButton)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrEnchView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrEnchView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_BASEENCHANT,		IDC_BASEENCHANTMENT,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMTYPES,			IDC_ITEMTYPES,			128,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Constructor
 *
 *=========================================================================*/
CSrEnchView::CSrEnchView() : CSrRecordDialog(CSrEnchView::IDD) 
{
  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrEnchView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Destructor
 *
 *=========================================================================*/
CSrEnchView::~CSrEnchView() 
{
}
/*===========================================================================
 *		End of Class CSrEnchView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrEnchView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_BASEENCHANTMENT, m_BaseEnchantment);
	DDX_Control(pDX, IDC_ITEMTYPES, m_ItemTypes);
}
/*===========================================================================
 *		End of Class Method CSrEnchView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEnchView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrEnchView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrEnchView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrEnchView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEnchView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrEnchView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();
  
  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrEnchView::OnInitialUpdate()
 *=========================================================================*/


void CSrEnchView::GetControlData (void)
{
	CSrRecordDialog::GetControlData();
}


void CSrEnchView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
}


void CSrEnchView::OnBnClickedEditBaseenchant()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_BaseEnchantment, SR_NAME_ENCH);
}


void CSrEnchView::OnBnClickedSelectbaseenchantButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_BaseEnchantment.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_ENCH, &CSrEnchRecord::s_FieldMap);
	if (!Result) return;

	m_BaseEnchantment.SetWindowText(Buffer);
}


void CSrEnchView::OnBnClickedEditItemtypes()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ItemTypes, SR_NAME_FLST);
}


void CSrEnchView::OnBnClickedSelectitemtypesButton()
{
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_ItemTypes.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_FLST, &CSrFlstRecord::s_FieldMap);
	if (!Result) return;

	m_ItemTypes.SetWindowText(Buffer);
}
