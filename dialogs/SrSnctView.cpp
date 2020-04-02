/*===========================================================================
 *
 * File:		SrSnctView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srsnctview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrSnctView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSnctView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSnctView, CSrRecordDialog)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDPARENT, OnDropSoundParent)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDPARENT, OnDropSoundParent)
	ON_BN_CLICKED(IDC_EDIT_SOUNDPARENT, &CSrSnctView::OnBnClickedEditSoundParent)
	ON_BN_CLICKED(IDC_SELECT_SOUNDPARENT, &CSrSnctView::OnBnClickedSelectSoundParent)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSnctView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrSnctView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_ITEMNAME,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUNDFLAGS,		IDC_SOUNDFLAGS,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_PARENT,			IDC_SOUNDPARENT,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2,		8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSnctView Constructor
 *
 *=========================================================================*/
CSrSnctView::CSrSnctView() : CSrRecordDialog(CSrSnctView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrSnctView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSnctView Destructor
 *
 *=========================================================================*/
CSrSnctView::~CSrSnctView() 
{
}
/*===========================================================================
 *		End of Class CSrSnctView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSnctView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrSnctView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_SOUNDFLAGS, m_SoundFlags);
	DDX_Control(pDX, IDC_SOUNDPARENT, m_SoundParent);
}
/*===========================================================================
 *		End of Class Method CSrSnctView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSnctView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrSnctView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrSnctView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrSnctView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSnctView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrSnctView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrSnctView::OnInitialUpdate()
 *=========================================================================*/


void CSrSnctView::OnDropSoundParent (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SoundParent, SR_NAME_SNCT, 1);
}


void CSrSnctView::OnBnClickedEditSoundParent()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_SoundParent, SR_NAME_SNCT);
}


void CSrSnctView::OnBnClickedSelectSoundParent()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_SoundParent, SR_NAME_SNCT, &CSrSnctRecord::s_FieldMap);
}


