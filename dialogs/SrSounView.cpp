/*===========================================================================
 *
 * File:		SrSounView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srsounview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrSounView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSounView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSounView, CSrRecordDialog)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUNDREF, OnDropSoundRef)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUNDREF, OnDropSoundRef)
	ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_SOUNDFILE, OnDropSoundFile)
	ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_SOUNDFILE, OnDropSoundFile)
	ON_BN_CLICKED(IDC_SELECT_SOUNDFILE, &CSrSounView::OnBnClickedSelectSoundfile)
	ON_BN_CLICKED(IDC_EDIT_SOUNDREF, &CSrSounView::OnBnClickedEditSoundref)
	ON_BN_CLICKED(IDC_SELECT_SOUNDREF, &CSrSounView::OnBnClickedSelectSoundref)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSounView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrSounView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_IMAGESPACE,		IDC_IMAGESPACE,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_BOUNDS,			IDC_BOUNDS,			64,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUNDFILE,		IDC_SOUNDFILE,		256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUNDREF,		IDC_SOUNDREF,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,		IDC_UNKNOWN4,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN5,		IDC_UNKNOWN5,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN6,		IDC_UNKNOWN6,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN7,		IDC_UNKNOWN7,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN8,		IDC_UNKNOWN8,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN9,		IDC_UNKNOWN9,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN10,		IDC_UNKNOWN10,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN11,		IDC_UNKNOWN11,		8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN12,		IDC_UNKNOWN12,		8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSounView Constructor
 *
 *=========================================================================*/
CSrSounView::CSrSounView() : CSrRecordDialog(CSrSounView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrSounView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSounView Destructor
 *
 *=========================================================================*/
CSrSounView::~CSrSounView() 
{
}
/*===========================================================================
 *		End of Class CSrSounView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSounView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrSounView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Unknown4);
	DDX_Control(pDX, IDC_UNKNOWN5, m_Unknown5);
	DDX_Control(pDX, IDC_UNKNOWN6, m_Unknown6);
	DDX_Control(pDX, IDC_UNKNOWN7, m_Unknown7);
	DDX_Control(pDX, IDC_UNKNOWN8, m_Unknown8);
	DDX_Control(pDX, IDC_UNKNOWN9, m_Unknown9);
	DDX_Control(pDX, IDC_UNKNOWN10, m_Unknown10);
	DDX_Control(pDX, IDC_UNKNOWN11, m_Unknown11);
	DDX_Control(pDX, IDC_UNKNOWN12, m_Unknown12);
	DDX_Control(pDX, IDC_SOUNDFILE, m_SoundFile);
	DDX_Control(pDX, IDC_SOUNDREF, m_SoundRef);
	DDX_Control(pDX, IDC_BOUNDS, m_Bounds);
}
/*===========================================================================
 *		End of Class Method CSrSounView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSounView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrSounView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrSounView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrSounView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSounView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrSounView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrSounView::OnInitialUpdate()
 *=========================================================================*/



void CSrSounView::OnDropSoundRef (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SoundRef, SR_NAME_SNDR, 1);
}


void CSrSounView::OnDropSoundFile (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;
	
	*pResult = SRRESOURCE_DROPCHECK_ERROR;
	
	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_SOUND) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_SOUNDS)) return;
	
	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
	  m_SoundFile.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}
	
	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrSounView::OnBnClickedSelectSoundfile()
{
	CString Buffer;

	m_SoundFile.GetWindowText(Buffer);
	m_pDlgHandler->SelectSoundFile(Buffer);
}


void CSrSounView::OnBnClickedEditSoundref()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_SoundRef, SR_NAME_SNDR);
}


void CSrSounView::OnBnClickedSelectSoundref()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_SoundRef, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


