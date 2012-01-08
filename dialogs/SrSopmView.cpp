/*===========================================================================
 *
 * File:		SrSopmView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srsopmview.h"
#include "sreditdlghandler.h"
#include "SrSopmEditDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrSopmView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSopmView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSopmView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_ANAMDATA_BUTTON, &CSrSopmView::OnBnClickedAnamdataButton)
	ON_BN_CLICKED(IDC_ONAMDATA_BUTTON, &CSrSopmView::OnBnClickedOnamdataButton)
	ON_BN_CLICKED(IDC_SNAMDATA_BUTTON, &CSrSopmView::OnBnClickedSnamdataButton)
	ON_CBN_SELCHANGE(IDC_CONTENTTYPE, &CSrSopmView::OnCbnSelchangeContenttype)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSopmView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrSopmView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SOUNDFLAGS,		IDC_SOUNDFLAGS,		16,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSopmView Constructor
 *
 *=========================================================================*/
CSrSopmView::CSrSopmView() : CSrRecordDialog(CSrSopmView::IDD) 
{
	m_InitialSetData = false;

	memset(&m_AnamData, 0, sizeof(m_AnamData));
	memset(&m_OnamData, 0, sizeof(m_OnamData));
	memset(&m_SnamData, 0, sizeof(m_SnamData));
}
/*===========================================================================
 *		End of Class CSrSopmView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSopmView Destructor
 *
 *=========================================================================*/
CSrSopmView::~CSrSopmView() 
{
}
/*===========================================================================
 *		End of Class CSrSopmView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSopmView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrSopmView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_SOUNDFLAGS, m_SoundFlags);
	DDX_Control(pDX, IDC_CONTENTTYPE, m_ContentType);
	DDX_Control(pDX, IDC_ANAMDATA_BUTTON, m_AnamButton);
	DDX_Control(pDX, IDC_ONAMDATA_BUTTON, m_OnamButton);
	DDX_Control(pDX, IDC_SNAMDATA_BUTTON, m_SnamButton);
}
/*===========================================================================
 *		End of Class Method CSrSopmView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSopmView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrSopmView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrSopmView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrSopmView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSopmView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrSopmView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	SrFillComboList(m_ContentType, s_SrSopmContentTypes, 0);

	CopyNameData();
	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrSopmView::OnInitialUpdate()
 *=========================================================================*/


void CSrSopmView::CopyNameData (void)
{
	CSrSopmRecord* pMarker = SrCastClass(CSrSopmRecord, GetInputRecord());
	if (pMarker == NULL) return;

	if (pMarker->GetAnamData()) m_AnamData = *pMarker->GetAnamData();
	if (pMarker->GetOnamData()) m_OnamData = *pMarker->GetOnamData();
	if (pMarker->GetSnamData()) m_SnamData = *pMarker->GetSnamData();
}


void CSrSopmView::GetControlData (void)
{
	int ContentType = SR_SOPMCONTENTTYPE_UNKNOWN;
	int ListIndex;

	CSrRecordDialog::GetControlData();

	CSrSopmRecord* pMarker = SrCastClass(CSrSopmRecord, GetOutputRecord());
	if (pMarker == NULL) return;

	ListIndex = m_ContentType.GetCurSel();
	if (ListIndex >= 0) ContentType = m_ContentType.GetItemData(ListIndex);

	pMarker->SetContentType(ContentType);

	pMarker->SetAnamData(m_AnamData);
	pMarker->SetOnamData(m_OnamData);
	pMarker->SetSnamData(m_SnamData);	

	pMarker->MoveToEnd(SR_NAME_ONAM);
	pMarker->MoveToEnd(SR_NAME_SNAM);
	pMarker->MoveToEnd(SR_NAME_ANAM);
}


void CSrSopmView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();

	CSrSopmRecord* pMarker = SrCastClass(CSrSopmRecord, GetInputRecord());
	if (pMarker == NULL) return;
		
	FindComboBoxItemData(m_ContentType, pMarker->GetContentType(), true);

	UpdateEnableControls();

	SetAnamControlData();
	SetOnamControlData();
	SetSnamControlData();
}


void CSrSopmView::SetAnamControlData (void)
{
	CString Buffer;
	Buffer.Format("0x%08X %g %g 0x%08X 0x%08X", m_AnamData.Unknown1, m_AnamData.Unknown2, m_AnamData.Unknown3, m_AnamData.Unknown4, m_AnamData.Unknown5);
	m_AnamButton.SetWindowText(Buffer);
}


void CSrSopmView::SetOnamControlData (void)
{
	CString Buffer;
	CString Tmp;

	for (dword i = 0; i < 24; ++i)
	{
		Tmp.Format("%d ", (int) m_OnamData.Unknown[i]);
		Buffer += Tmp;
	}

	m_OnamButton.SetWindowText(Buffer);
}


void CSrSopmView::SetSnamControlData (void)
{
	CString Buffer;
	CString Tmp;

	for (dword i = 0; i < 16; ++i)
	{
		Tmp.Format("%d ", (int) m_SnamData.Unknown[i]);
		Buffer += Tmp;
	}

	m_SnamButton.SetWindowText(Buffer);
}


void CSrSopmView::UpdateEnableControls (void)
{
	int ListIndex;
	int ContentType = SR_SOPMCONTENTTYPE_UNKNOWN;

	ListIndex = m_ContentType.GetCurSel();
	if (ListIndex >= 0) ContentType = m_ContentType.GetItemData(ListIndex);

	switch (ContentType)
	{
	case SR_SOPMCONTENTTYPE_FNAM:
		m_AnamButton.EnableWindow(true);
		m_OnamButton.EnableWindow(false);
		m_SnamButton.EnableWindow(true);
		m_SoundFlags.EnableWindow(true);
		m_Unknown1.EnableWindow(false);
		m_Unknown2.EnableWindow(false);
		m_Unknown2.SetWindowText("0");
		m_Unknown3.EnableWindow(true);		
		break;
	case SR_SOPMCONTENTTYPE_ANAM:
		m_AnamButton.EnableWindow(true);
		m_OnamButton.EnableWindow(false);
		m_SnamButton.EnableWindow(false);
		m_SoundFlags.EnableWindow(false);
		m_Unknown1.EnableWindow(true);
		m_Unknown2.EnableWindow(false);
		m_Unknown2.SetWindowText("0");
		m_Unknown3.EnableWindow(false);
		break;
	case SR_SOPMCONTENTTYPE_ONAM:
		m_AnamButton.EnableWindow(false);
		m_OnamButton.EnableWindow(true);
		m_SnamButton.EnableWindow(false);
		m_SoundFlags.EnableWindow(false);
		m_Unknown1.EnableWindow(true);
		m_Unknown2.EnableWindow(false);
		m_Unknown2.SetWindowText("1");
		m_Unknown3.EnableWindow(false);
		break;
	case SR_SOPMCONTENTTYPE_ANAMONAM:
		m_AnamButton.EnableWindow(true);
		m_OnamButton.EnableWindow(true);
		m_SnamButton.EnableWindow(false);
		m_SoundFlags.EnableWindow(false);
		m_Unknown1.EnableWindow(true);
		m_Unknown2.EnableWindow(false);
		m_Unknown2.SetWindowText("1");
		m_Unknown3.EnableWindow(false);
		break;
	default:
		m_AnamButton.EnableWindow(false);
		m_OnamButton.EnableWindow(false);
		m_SnamButton.EnableWindow(false);
		m_SoundFlags.EnableWindow(false);
		m_Unknown1.EnableWindow(false);
		m_Unknown2.EnableWindow(false);
		m_Unknown3.EnableWindow(false);
		break;
	}

}

void CSrSopmView::OnBnClickedAnamdataButton()
{
	srsopmeditinfo_t EditInfo = { &m_AnamData, NULL, NULL };
	if (SrSopmEditDlg(EditInfo)) SetAnamControlData();
}


void CSrSopmView::OnBnClickedOnamdataButton()
{
	srsopmeditinfo_t EditInfo = { NULL, &m_OnamData, NULL };
	if (SrSopmEditDlg(EditInfo)) SetOnamControlData();
}


void CSrSopmView::OnBnClickedSnamdataButton()
{
	srsopmeditinfo_t EditInfo = { NULL, NULL, &m_SnamData };
	if (SrSopmEditDlg(EditInfo)) SetSnamControlData();
}


void CSrSopmView::OnCbnSelchangeContenttype()
{
	UpdateEnableControls();
}
