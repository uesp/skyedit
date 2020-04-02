/*===========================================================================
 *
 * File:		SrSndrView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srsndrview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrSndrView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSndrView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSndrView, CSrRecordDialog)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUND, OnDropSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUND, OnDropSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_CATEGORY, OnDropCategory)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_CATEGORY, OnDropCategory)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_OUTPUTMARKER, OnDropOutputMarker)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_OUTPUTMARKER, OnDropOutputMarker)
	ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_SOUNDFILE_LIST, OnDropSoundFileList)
	ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_SOUNDFILE_LIST, OnDropSoundFileList)
	ON_BN_CLICKED(IDC_EDIT_SOUND, &CSrSndrView::OnBnClickedEditSound)
	ON_BN_CLICKED(IDC_SELECT_SOUND, &CSrSndrView::OnBnClickedSelectSound)
	ON_BN_CLICKED(IDC_EDIT_CATEGORY, &CSrSndrView::OnBnClickedEditCategory)
	ON_BN_CLICKED(IDC_SELECT_CATEGORY, &CSrSndrView::OnBnClickedSelectCategory)
	ON_BN_CLICKED(IDC_EDIT_OUTPUTMARKER, &CSrSndrView::OnBnClickedEditOutputmarker)
	ON_BN_CLICKED(IDC_SELECT_OUTPUTMARKER, &CSrSndrView::OnBnClickedSelectOutputmarker)
	ON_BN_CLICKED(ID_ADD_SOUNDFILE, &CSrSndrView::OnBnClickedAddSoundfilelist)
	ON_BN_CLICKED(ID_SELECT_SOUNDFILE, &CSrSndrView::OnBnClickedSelectSoundfilelist)
	ON_BN_CLICKED(ID_DELETE_SOUNDFILE, &CSrSndrView::OnBnClickedDeleteSoundfilelist)
	ON_LBN_DBLCLK(IDC_SOUNDFILE_LIST, &CSrSndrView::OnLbnDblclkSoundfileList)
	ON_BN_CLICKED(ID_EDIT_SOUNDFILE, &CSrSndrView::OnBnClickedEditSoundfile)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSndrView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrSndrView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_CATEGORY,		IDC_CATEGORY,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUND,			IDC_SOUND,				128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_OUTPUTMARKER,	IDC_OUTPUTMARKER,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_CONDITIONCOUNT,	IDC_CONDITION_BUTTON,	8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_FNAME,			IDC_FNAME,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CNAME,			IDC_CNAME,				16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUNDFLAGS,		IDC_SOUNDFLAGS,			16,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSndrView Constructor
 *
 *=========================================================================*/
CSrSndrView::CSrSndrView() : CSrRecordDialog(CSrSndrView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrSndrView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSndrView Destructor
 *
 *=========================================================================*/
CSrSndrView::~CSrSndrView() 
{
}
/*===========================================================================
 *		End of Class CSrSndrView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSndrView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrSndrView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_FNAME, m_FName);
	DDX_Control(pDX, IDC_CNAME, m_CName);
	DDX_Control(pDX, IDC_SOUNDFLAGS, m_SoundFlags);
	DDX_Control(pDX, IDC_OUTPUTMARKER, m_OutputMarker);
	DDX_Control(pDX, IDC_SOUND, m_Sound);
	DDX_Control(pDX, IDC_CATEGORY, m_Category);
	DDX_Control(pDX, IDC_SOUNDFILE_LIST, m_SoundFileList);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_Conditions);
}
/*===========================================================================
 *		End of Class Method CSrSndrView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSndrView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrSndrView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrSndrView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrSndrView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSndrView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrSndrView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrSndrView::OnInitialUpdate()
 *=========================================================================*/


void CSrSndrView::GetControlData (void)
{
	CString Buffer;

	GetOutputRecord()->DeleteSubrecords(SR_NAME_ANAM);

	CSrRecordDialog::GetControlData();

	CSrSndrRecord* pSound = SrCastClass(CSrSndrRecord, GetOutputRecord());
	if (pSound == NULL) return;

	for (int i = 0; i < m_SoundFileList.GetCount(); ++i)
	{
		Buffer.Empty();
		m_SoundFileList.GetText(i, Buffer);
		Buffer.Trim(" \t\r\n");

		pSound->AddSoundFile(Buffer);
	}

}


void CSrSndrView::SetControlData (void)
{
	CSrSubrecord* pSubrecord;
	int           Position;

	CSrRecordDialog::SetControlData();

	m_SoundFileList.ResetContent();
	pSubrecord = GetInputRecord()->FindFirstSubrecord(SR_NAME_ANAM, Position);

	while (pSubrecord != NULL)
	{
		CSrStringSubrecord* pString = SrCastClass(CSrStringSubrecord, pSubrecord);
		if (pString != NULL) m_SoundFileList.AddString(pString->GetString());

		pSubrecord = GetInputRecord()->FindNextSubrecord(SR_NAME_ANAM, Position);
	}
	
}



void CSrSndrView::OnDropSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Sound, SR_NAME_SNDR, 1);
}


void CSrSndrView::OnDropCategory (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Category, SR_NAME_SNCT, 1);
}


void CSrSndrView::OnDropOutputMarker (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_OutputMarker, SR_NAME_SOPM, 1);
}



void CSrSndrView::OnDropSoundFileList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;
	
	*pResult = SRRESOURCE_DROPCHECK_ERROR;
	
	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_SOUND) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_SOUNDS)) return;
	
	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_SoundFileList.AddString(pDropInfo->pResourceFile->GetCSName());    
	}
	
	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrSndrView::OnBnClickedEditSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Sound, SR_NAME_SNDR);
}


void CSrSndrView::OnBnClickedSelectSound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Sound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrSndrView::OnBnClickedEditCategory()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Category, SR_NAME_SNCT);
}


void CSrSndrView::OnBnClickedSelectCategory()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Category, SR_NAME_SNCT, &CSrSnctRecord::s_FieldMap);
}


void CSrSndrView::OnBnClickedEditOutputmarker()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_OutputMarker, SR_NAME_SOPM);
}


void CSrSndrView::OnBnClickedSelectOutputmarker()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_OutputMarker, SR_NAME_SOPM, &CSrSopmRecord::s_FieldMap);
}


void CSrSndrView::OnBnClickedAddSoundfilelist()
{
	CString Buffer;
	if (!SrInputDialog(Buffer, "Add Sound", "Enter Sound Filename Below:")) return;
	m_SoundFileList.AddString(Buffer);
}


void CSrSndrView::OnBnClickedSelectSoundfilelist()
{
	CString Buffer;
	int ListIndex = m_SoundFileList.GetCurSel();
	if (ListIndex >= 0) m_SoundFileList.GetText(ListIndex, Buffer);
	if (m_pDlgHandler) m_pDlgHandler->SelectSoundFile(Buffer);
}


void CSrSndrView::OnBnClickedDeleteSoundfilelist()
{
	int ListIndex = m_SoundFileList.GetCurSel();

	if (ListIndex >= 0) 
	{
		m_SoundFileList.DeleteString(ListIndex);

		if (ListIndex > 0)
			m_SoundFileList.SetCurSel(ListIndex - 1);
		else
			m_SoundFileList.SetCurSel(ListIndex);
	}

}


void CSrSndrView::OnLbnDblclkSoundfileList()
{
	CString Buffer;

	int ListIndex = m_SoundFileList.GetCurSel();
	if (ListIndex < 0) return;
	m_SoundFileList.GetText(ListIndex, Buffer);

	if (!SrInputDialog(Buffer, "Edit Sound", "Edit Sound Filename Below:")) return;

	m_SoundFileList.DeleteString(ListIndex);
	m_SoundFileList.InsertString(ListIndex, Buffer);
	m_SoundFileList.SetCurSel(ListIndex);
}


void CSrSndrView::OnBnClickedEditSoundfile()
{
	OnLbnDblclkSoundfileList();
}
