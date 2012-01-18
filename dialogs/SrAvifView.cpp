/*===========================================================================
 *
 * File:		SrAvifView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "sravifview.h"
#include "dialogs/sreditdlghandler.h"
#include "../SrConditionDlg.h"
#include <vector>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrAvifView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrAvifView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrAvifView, CSrRecordDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrAvifView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_SectionListInit[] = {
	{ SR_FIELD_PNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_FNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_XNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_YNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_HNAME,	60,		LVCFMT_CENTER },
	{ SR_FIELD_VNAME,	60,		LVCFMT_CENTER },
	{ SR_FIELD_SNAME,	100,	LVCFMT_CENTER },
	{ SR_FIELD_CNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_INAME,	40,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_SectionFields[] = {
	{ "Perk",		SR_FIELD_PNAME,		0, NULL },
	{ "FName",		SR_FIELD_FNAME,		0, NULL },
	{ "XName",		SR_FIELD_XNAME,		0, NULL },
	{ "YName",		SR_FIELD_YNAME,		0, NULL },
	{ "HName",		SR_FIELD_HNAME,		0, NULL },
	{ "VName",		SR_FIELD_VNAME,		0, NULL },
	{ "SName",		SR_FIELD_SNAME,		0, NULL },
	{ "CName",		SR_FIELD_CNAME,		0, NULL },
	{ "IName",		SR_FIELD_INAME,		0, NULL },
	{ NULL,			SR_FIELD_NONE,		0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrAvifView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,		IDC_DESCRIPTION,		256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,			IDC_UNKNOWN1,			12,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,			IDC_UNKNOWN2,			12,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,			IDC_UNKNOWN3,			12,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,			IDC_UNKNOWN4,			12,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CNAME,				IDC_CNAME,				10,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_ANAME,				IDC_ANAME,				10,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAvifView Constructor
 *
 *=========================================================================*/
CSrAvifView::CSrAvifView() : CSrRecordDialog(CSrAvifView::IDD) 
{
	m_InitialSetData = false;
	m_IsInitialized = false;
	m_IsUpdating = false;
	m_pCurrentSection = NULL;
}
/*===========================================================================
 *		End of Class CSrAvifView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAvifView Destructor
 *
 *=========================================================================*/
CSrAvifView::~CSrAvifView() 
{
}
/*===========================================================================
 *		End of Class CSrAvifView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAvifView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrAvifView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Unknown4);
	DDX_Control(pDX, IDC_CNAME, m_CName);
	DDX_Control(pDX, IDC_AVIFDATA_LIST, m_SectionList);
	DDX_Control(pDX, IDC_ANAME, m_AName);
}
/*===========================================================================
 *		End of Class Method CSrAvifView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrAvifView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG
	void CSrAvifView::AssertValid() const { CSrRecordDialog::AssertValid(); }
	void CSrAvifView::Dump(CDumpContext& dc) const { CSrRecordDialog::Dump(dc); }
#endif
/*===========================================================================
 *		End of CSrAvifView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAvifView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrAvifView::OnInitialUpdate (void) 
{
	m_IsInitialized = false;
	CSrRecordDialog::OnInitialUpdate();

	m_SectionList.SetListName("AvifSectionList");
	m_SectionList.SetDragEnable(true);
	m_SectionList.DefaultSettings();
	m_SectionList.SetupCustomList(s_SectionListInit, NULL, s_SectionFields);
	m_SectionList.SetOwner(this);
	m_SectionList.SetColorEnable(false);
	m_SectionList.SetDragType(SR_RLDRAG_CUSTOM);
	m_SectionList.SetSortEnable(false);
	//m_SectionList.SetActivateType(SR_RLACTIVATE_NONE);
	
	CopyAvifSections();
	
	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrAvifView::OnInitialUpdate()
 *=========================================================================*/


void CSrAvifView::CopyAvifSections (void)
{
	CSrAvifRecord* pAvif = SrCastClass(CSrAvifRecord, GetInputRecord());
	if (pAvif) pAvif->CreateSectionInfo(m_Sections);
}


void CSrAvifView::SetAvifSectionList (void)
{
	m_SectionList.DeleteAllItems();
	
	for (dword i = 0; i < m_Sections.GetSize(); ++i) 
	{
		AddAvifSectionList(m_Sections[i]);
	}

	m_SectionList.SelectRecord(0);
	SetCurrentSection(m_Sections[0]);
}


void CSrAvifView::SetSectionCustomData(srrlcustomdata_t& CustomData, sravifsection_t* pSection)
{
	CustomData.Subrecords.Destroy();

	CustomData.pRecord = GetInputRecord();
	CustomData.Subrecords.Add(&pSection->PName);
	CustomData.Subrecords.Add(&pSection->FName);
	CustomData.Subrecords.Add(&pSection->XName);
	CustomData.Subrecords.Add(&pSection->YName);
	CustomData.Subrecords.Add(&pSection->HName);
	CustomData.Subrecords.Add(&pSection->VName);
	CustomData.Subrecords.Add(&pSection->SName);
  
	for (dword i = 0; i < pSection->CNames.GetSize(); ++i)
	{
		CustomData.Subrecords.Add(pSection->CNames[i]);
	}

	CustomData.Subrecords.Add(&pSection->IName);
}


int CSrAvifView::AddAvifSectionList (sravifsection_t* pSection)
{
	srrlcustomdata_t  CustomData;
	CString           Buffer;
	int		          ListIndex;

	SetSectionCustomData(CustomData, pSection);	
  
	ListIndex = m_SectionList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdateAvifSectionList(ListIndex, false);
	return (ListIndex);
}


sravifsection_t* CSrAvifView::FindAvifSection(CSrFormidSubrecord* pPName)
{
	for (dword i = 0; i < m_Sections.GetSize(); ++i)
	{
		if (pPName == &m_Sections[i]->PName) return m_Sections[i];
	}

	return NULL;
}


void CSrAvifView::UpdateAvifSectionList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t*	pCustomData;
	sravifsection_t*	pSection;
	CSrFormidSubrecord*	pPName;
	CString				Buffer;

	if (GetInputRecord() == NULL) return;

	pCustomData = m_SectionList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	if (Update) m_SectionList.UpdateRecord(ListIndex);

	pPName = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
	if (pPName == NULL) return;

	pSection = FindAvifSection(pPName);
	if (pSection == NULL) return;


	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PNAME, m_pRecordHandler->GetEditorID(pSection->PName.GetValue()));

	Buffer.Format("%d", pSection->FName.GetValue());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_FNAME, Buffer);

	Buffer.Format("%d", pSection->XName.GetValue());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_XNAME, Buffer);

	Buffer.Format("%d", pSection->YName.GetValue());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_YNAME, Buffer);

	Buffer.Format("%g", pSection->HName.GetValue());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_HNAME, Buffer);

	Buffer.Format("%g", pSection->VName.GetValue());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_VNAME, Buffer);

	m_SectionList.SetCustomField(ListIndex, SR_FIELD_SNAME, m_pRecordHandler->GetEditorID(pSection->SName.GetValue()));

	Buffer.Format("%d", pSection->CNames.GetSize());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_CNAME, Buffer);

	Buffer.Format("%d", pSection->IName.GetValue());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_INAME, Buffer);
}


void CSrAvifView::SetCurrentSection (sravifsection_t* pSection)
{
	GetSectionData();

	m_pCurrentSection = pSection;
	EnableSectionControls();

	SetSectionData();
}


void CSrAvifView::GetSectionData (void)
{
	if (m_pCurrentSection == NULL) return;

	UpdateSectionList(m_pCurrentSection);
}


void CSrAvifView::UpdateSectionList (sravifsection_t* pSection)
{
	for (int i = 0; i < m_SectionList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pData = m_SectionList.GetCustomData(i);
		if (pData == NULL) continue;

		if (pData->Subrecords[0] == &pSection->PName)
		{
			SetSectionCustomData(*pData, pSection);
			UpdateAvifSectionList(i, true);
			return;
		}
	}
}


void CSrAvifView::SetSectionData (void)
{
	CString Buffer;

	m_IsUpdating = true;

	if (m_pCurrentSection == NULL) 
	{
		m_IsUpdating = false;
		return;	
	}

	
	
	m_IsUpdating = false;
}


void CSrAvifView::EnableSectionControls (void)
{
	bool Enable = m_pCurrentSection != NULL;

	if (!Enable || m_pCurrentSection == NULL) return;

}


void CSrAvifView::GetControlData (void)
{
	GetSectionData();

	CSrRecordDialog::GetControlData();

	CSrAvifRecord* pAvif = SrCastClass(CSrAvifRecord, GetOutputRecord());
	if (pAvif) pAvif->CreateFromSectionInfo(m_Sections);
}


void CSrAvifView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	SetAvifSectionList();
}


int CSrAvifView::OnPreSaveRecord (void)
{
	return CSrRecordDialog::OnPreSaveRecord();
}


