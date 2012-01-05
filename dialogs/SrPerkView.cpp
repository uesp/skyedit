*===========================================================================
 *
 * File:		SrPerkView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srperkview.h"
#include "dialogs/sreditdlghandler.h"
#include "../SrConditionDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrPerkView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrPerkView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrPerkView, CSrRecordDialog)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_NEXTPERK, OnDropNextPerk)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_NEXTPERK, OnDropNextPerk)
	ON_BN_CLICKED(IDC_EDIT_NEXTPERK, &CSrPerkView::OnBnClickedEditNextperk)
	ON_BN_CLICKED(IDC_SELECT_NEXTPERK, &CSrPerkView::OnBnClickedSelectNextperk)
	ON_BN_CLICKED(ID_ADDPERK_BUTTON, &CSrPerkView::OnBnClickedAddperkButton)
	ON_BN_CLICKED(ID_DELETEPERK_BUTTON, &CSrPerkView::OnBnClickedDeleteperkButton)
	ON_BN_CLICKED(IDC_SECTION_CONDITIONS, &CSrPerkView::OnBnClickedSectionConditions)
	ON_BN_CLICKED(IDC_EDIT_SECTIONEDITORID, &CSrPerkView::OnBnClickedEditSectioneditorid)
	ON_BN_CLICKED(IDC_SELECT_SECTIONEDITORID, &CSrPerkView::OnBnClickedSelectSectioneditorid)
	ON_CBN_SELCHANGE(IDC_SECTIONTYPE, &CSrPerkView::OnCbnSelchangeSectiontype)
	ON_CBN_SELCHANGE(IDC_SECTIONAPPLYTYPE, &CSrPerkView::OnCbnSelchangeSectionapplytype)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PERKDATA_LIST, &CSrPerkView::OnLvnItemchangedPerkdataList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_PERKDATA_LIST, OnDropSectionList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_PERKDATA_LIST, OnDropSectionList)	
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrPerkView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_SectionListInit[] = {
	{ SR_FIELD_PERKSECTYPE,		50,		LVCFMT_CENTER },
	{ SR_FIELD_PERKINDEX,		40,		LVCFMT_CENTER },
	{ SR_FIELD_PERKEFFTYPE,		100,	LVCFMT_CENTER },
	{ SR_FIELD_PERKAPPLYTYPE,	80,		LVCFMT_CENTER },
	{ SR_FIELD_UNKNOWN1,		40,		LVCFMT_CENTER },
	{ SR_FIELD_PERKSEFFDATA,	150,	LVCFMT_CENTER },
	{ SR_FIELD_CONDITIONCOUNT,	60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_SectionFields[] = {
	{ "Type",			SR_FIELD_PERKSECTYPE,			0, NULL },
	{ "Index",			SR_FIELD_PERKINDEX,				0, NULL },
	{ "Conditions",		SR_FIELD_CONDITIONCOUNT,		0, NULL },
	{ "EffectType",		SR_FIELD_PERKEFFTYPE,			0, NULL },
	{ "ApplyType",		SR_FIELD_PERKAPPLYTYPE,			0, NULL },
	{ "UnknownType",	SR_FIELD_UNKNOWN1,				0, NULL },
	{ "EffectData",		SR_FIELD_PERKSEFFDATA,			0, NULL },
	{ NULL,				SR_FIELD_NONE,					0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrPerkView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,		IDC_DESCRIPTION,		256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_NEXTPERK,			IDC_NEXTPERK,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,			IDC_UNKNOWN1,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,			IDC_UNKNOWN2,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,			IDC_UNKNOWN3,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CONDITIONCOUNT,		IDC_CONDITION_BUTTON,	8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPerkView Constructor
 *
 *=========================================================================*/
CSrPerkView::CSrPerkView() : CSrRecordDialog(CSrPerkView::IDD) 
{
	m_InitialSetData = false;
	m_IsInitialized = false;
	m_IsUpdating = false;
	m_pCurrentSection = NULL;
}
/*===========================================================================
 *		End of Class CSrPerkView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPerkView Destructor
 *
 *=========================================================================*/
CSrPerkView::~CSrPerkView() 
{
}
/*===========================================================================
 *		End of Class CSrPerkView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPerkView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrPerkView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_NEXTPERK, m_NextPerk);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_CONDITION_BUTTON, m_Conditions);
	DDX_Control(pDX, IDC_PERKDATA_LIST, m_SectionList);
	DDX_Control(pDX, IDC_SECTIONTYPE, m_SectionType);
	DDX_Control(pDX, IDC_SECTIONINDEX, m_SectionIndex);
	DDX_Control(pDX, IDC_SECTION_CONDITIONS, m_SectionConditions);
	DDX_Control(pDX, IDC_SECTION_EDITORIDLABEL, m_SectionEditorIDLabel);
	DDX_Control(pDX, IDC_SECTION_EDITORID, m_SectionEditorID);
	DDX_Control(pDX, IDC_EDIT_SECTIONEDITORID, m_EditEditorIDButton);
	DDX_Control(pDX, IDC_SELECT_SECTIONEDITORID, m_SelectEditorIDButton);
	DDX_Control(pDX, IDC_SECTION_ACTORVALUE, m_SectionActorValue);
	DDX_Control(pDX, IDC_SECTIONVALUE, m_SectionValue);
	DDX_Control(pDX, IDC_SECTION_VALUELABEL1, m_SectionValueLabel);
	DDX_Control(pDX, IDC_SECTIONEFFECTTYPE, m_SectionEffectType);
	DDX_Control(pDX, IDC_SECTIONAPPLYTYPE, m_SectionApplyType);
	DDX_Control(pDX, IDC_SECTIONUNKNOWNTYPE, m_SectionUnknownType);
}
/*===========================================================================
 *		End of Class Method CSrPerkView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrPerkView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrPerkView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrPerkView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrPerkView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPerkView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrPerkView::OnInitialUpdate (void) 
{
	m_IsInitialized = false;
	CSrRecordDialog::OnInitialUpdate();

	m_SectionList.SetListName("PerkSectionList");
	m_SectionList.SetDragEnable(true);
	m_SectionList.DefaultSettings();
	m_SectionList.SetupCustomList(s_SectionListInit, NULL, s_SectionFields);
	m_SectionList.SetOwner(this);
	m_SectionList.SetColorEnable(false);
	m_SectionList.SetDragType(SR_RLDRAG_CUSTOM);
	m_SectionList.SetSortEnable(false);
	//m_SectionList.SetActivateType(SR_RLACTIVATE_NONE);
	
	SrFillComboList(m_Unknown1, s_SrPerkDataUnknown1Types, 0);
	SrFillComboList(m_Unknown2, s_SrPerkDataUnknown2Types, 0);
	SrFillComboList(m_Unknown3, s_SrPerkDataUnknown3Types, 0);

	SrFillComboList(m_SectionType, s_SrPerkDataTypes, 0);
	SrFillComboList(m_SectionEffectType, s_SrPerkDataEffectTypes, 0);
	SrFillComboList(m_SectionApplyType, s_SrPerkDataApplyTypes, 0);
	SrFillComboList(m_SectionUnknownType, s_SrPerkDataUnknownTypes, 0);
	SrFillComboList(m_SectionActorValue, s_SrActorValues, 0);

	CopyPerkSections();
	
	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrPerkView::OnInitialUpdate()
 *=========================================================================*/


void CSrPerkView::CopyPerkSections (void)
{
	m_Sections.Destroy();

	for (dword i = 0; i < GetInputRecord()->GetNumSubrecords(); ++i)
	{
		CSrSubrecord* pSubrecord = GetInputRecord()->GetSubrecord(i);

		if (pSubrecord->GetRecordType() == SR_NAME_PRKE)
		{
			m_Sections.AddNew()->CopyFrom(GetInputRecord(), i);
		}
	}

}


void CSrPerkView::SetPerkSectionList (void)
{
	m_SectionList.DeleteAllItems();
	
	for (dword i = 0; i < m_Sections.GetSize(); ++i) 
	{
		AddPerkSectionList(m_Sections[i]);
	}

	m_SectionList.SelectRecord(0);
	SetCurrentSection(m_Sections[0]);
}


void CSrPerkView::SetSectionCustomData(srrlcustomdata_t& CustomData, srperk_section_t* pSection)
{
	memset(CustomData.pSubrecords, 0, sizeof(CustomData.pSubrecords));

	CustomData.UserCount = pSection->Subsections.GetSize();
	CustomData.pRecord = GetInputRecord();
	CustomData.pSubrecords[0] = &pSection->Prke;
	CustomData.pSubrecords[1] = &pSection->Data;
  
	for (dword i = 0, j = 2; i < pSection->Subsections.GetSize() && j < SR_RLMAX_SUBRECORDS; ++i)
	{
		srperk_subsection_t* pSubsection = pSection->Subsections[i];
		CustomData.pSubrecords[j++] = &pSubsection->Prkc;

		for (dword k = 0; k < pSubsection->Conditions.GetSize() && j+3 < SR_RLMAX_SUBRECORDS; ++k)
		{
			srconditioninfo_t* pCondInfo = pSubsection->Conditions[k];
			CustomData.pSubrecords[j++] = &pCondInfo->Condition;
			if (pCondInfo->pParam1) CustomData.pSubrecords[j++] = pCondInfo->pParam1;
			if (pCondInfo->pParam2) CustomData.pSubrecords[j++] = pCondInfo->pParam2;
		}

		if (j < SR_RLMAX_SUBRECORDS && pSection->pEpft) CustomData.pSubrecords[j++] = pSection->pEpft;
		if (j < SR_RLMAX_SUBRECORDS && pSection->pEpf2) CustomData.pSubrecords[j++] = pSection->pEpf2;
		if (j < SR_RLMAX_SUBRECORDS && pSection->pEpf3) CustomData.pSubrecords[j++] = pSection->pEpf3;
		if (j < SR_RLMAX_SUBRECORDS && pSection->pEpfd) CustomData.pSubrecords[j++] = pSection->pEpfd;
		if (j < SR_RLMAX_SUBRECORDS) CustomData.pSubrecords[j++] = &pSection->Prkf;
	}
}


int CSrPerkView::AddPerkSectionList (srperk_section_t* pSection)
{
	srrlcustomdata_t  CustomData = { 0 };
	CString           Buffer;
	int		          ListIndex;

	SetSectionCustomData(CustomData, pSection);	
  
	ListIndex = m_SectionList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdatePerkSectionList(ListIndex, false);
	return (ListIndex);
}


srperk_section_t* CSrPerkView::FindPerkSection(CSrPrkeSubrecord* pPrke)
{
	for (dword i = 0; i < m_Sections.GetSize(); ++i)
	{
		if (pPrke == &m_Sections[i]->Prke) return m_Sections[i];
	}

	return NULL;
}


void CSrPerkView::UpdatePerkSectionList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t*	pCustomData;
	srperk_section_t*	pSection;
	CSrPrkeSubrecord*	pPrke;
	CString				Buffer;

	if (GetInputRecord() == NULL) return;

	pCustomData = m_SectionList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	if (Update) m_SectionList.UpdateRecord(ListIndex);

	pPrke = SrCastClassNull(CSrPrkeSubrecord, pCustomData->pSubrecords[0]);
	if (pPrke == NULL) return;

	pSection = FindPerkSection(pPrke);
	if (pSection == NULL) return;

	Buffer.Format("%s", (int) GetSrPerkDataTypeString(pSection->Prke.GetPrkeData().Type));
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKSECTYPE, Buffer);

	Buffer.Format("%d", (int) pSection->Prke.GetPrkeData().Index);
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKINDEX, Buffer);

	Buffer.Format("%d", (int) pSection->Subsections.GetSize());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_CONDITIONCOUNT, Buffer);
		
	if (pSection->Data.GetPerkDataType() == SR_PERKDATA_TYPE02)
	{
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKEFFTYPE, GetSrPerkDataEffectTypeString(pSection->Data.GetPerkData02().Effect));
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKAPPLYTYPE, GetSrPerkDataApplyTypeString(pSection->Data.GetPerkData02().ModType));
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_UNKNOWN1, GetSrPerkDataUnknownTypeString(pSection->Data.GetPerkData02().Unknown));
	}
	else
	{
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKEFFTYPE, "");
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKAPPLYTYPE, "");
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_UNKNOWN1, "");
	}

	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKSEFFDATA, GetPerkSectionDataString(*pSection));	
}


CString CSrPerkView::GetPerkSectionDataString (srperk_section_t& Section)
{
	CString Result;

	if (Section.Data.GetPerkDataType() == SR_PERKDATA_TYPE00)
	{
		Result.Format("%s::%d", GetInputRecord()->GetParent()->GetEditorID(Section.Data.GetPerkData00().QuestID), Section.Data.GetPerkData00().Stage);
	}
	else if (Section.Data.GetPerkDataType() == SR_PERKDATA_TYPE01)
	{
		Result.Format("%s", GetInputRecord()->GetParent()->GetEditorID(Section.Data.GetPerkData01().RecordID));
	}
	else if (Section.Data.GetPerkDataType() == SR_PERKDATA_TYPE02)
	{
		switch (Section.Data.GetPerkData02().ModType)
		{
		case 0x01:
		case 0x02:
		case 0x03:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 1) Result.Format("%g", Section.pEpfd->GetEpfdData01().Value);
			break;
		case 0x09:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 4) Result.Format("%s  ", GetInputRecord()->GetParent()->GetEditorID(Section.pEpfd->GetEpfdData04().FormID));
			if (Section.pEpf2) Result += Section.pEpf2->GetString().c_str();
			break;
		case 0x0A:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 5) Result.Format("%s", GetInputRecord()->GetParent()->GetEditorID(Section.pEpfd->GetEpfdData05().FormID));
			break;
		case 0x0B:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 6) Result.Format("%s", Section.pEpfd->GetEpfdData06().String.c_str());
			break;
		case 0x0E:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 2) Result.Format("%s * %g", GetSrActorValueString((int)Section.pEpfd->GetEpfdData02().ActorValue), Section.pEpfd->GetEpfdData02().Factor);
			break;
		case 0x0F:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 7) Result.Format("%s", Section.pEpfd->GetEpfdData07().String.c_str());
			break;
		}	
	}

	return Result;
}


void CSrPerkView::SetCurrentSection (srperk_section_t* pSection)
{
	GetSectionData();

	m_pCurrentSection = pSection;

	EnableSectionControls();
	UpdateSectionLabels();

	SetSectionData();
}


void CSrPerkView::GetSectionData (void)
{
	CString      Buffer;
	CSrIdRecord* pRecord;
	int          ListIndex;

	if (m_pCurrentSection == NULL) return;
	
	ListIndex = m_SectionType.GetCurSel();
	if (ListIndex >= 0)	m_pCurrentSection->Prke.GetPrkeData().Type = (word) m_SectionType.GetItemData(ListIndex);

	m_SectionIndex.GetWindowText(Buffer);
	m_pCurrentSection->Prke.GetPrkeData().Index = (byte) atoi(Buffer);
	
	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		m_pCurrentSection->Data.SetDataType(SR_PERKDATA_TYPE00);
		m_SectionEditorID.GetWindowText(Buffer);
		Buffer.Trim(" \t\n\r");

		pRecord = m_pRecordHandler->FindEditorID(Buffer);
		m_pCurrentSection->Data.GetPerkData00().QuestID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;
		
		m_SectionValue.GetWindowText(Buffer);
		m_pCurrentSection->Data.GetPerkData00().Stage = atoi(Buffer);
		
		m_pCurrentSection->Subsections.Destroy();
		delete m_pCurrentSection->pEpft;
		delete m_pCurrentSection->pEpf2;
		delete m_pCurrentSection->pEpf3;
		delete m_pCurrentSection->pEpfd;
		m_pCurrentSection->pEpft = NULL;
		m_pCurrentSection->pEpf2 = NULL;
		m_pCurrentSection->pEpf3 = NULL;
		m_pCurrentSection->pEpfd = NULL;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		m_pCurrentSection->Data.SetDataType(SR_PERKDATA_TYPE01);
		m_SectionEditorID.GetWindowText(Buffer);
		Buffer.Trim(" \t\n\r");

		pRecord = m_pRecordHandler->FindEditorID(Buffer);
		m_pCurrentSection->Data.GetPerkData01().RecordID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;

		m_pCurrentSection->Subsections.Destroy();
		delete m_pCurrentSection->pEpft;
		delete m_pCurrentSection->pEpf2;
		delete m_pCurrentSection->pEpf3;
		delete m_pCurrentSection->pEpfd;
		m_pCurrentSection->pEpft = NULL;
		m_pCurrentSection->pEpf2 = NULL;
		m_pCurrentSection->pEpf3 = NULL;
		m_pCurrentSection->pEpfd = NULL;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		m_pCurrentSection->Data.SetDataType(SR_PERKDATA_TYPE02);

		ListIndex = m_SectionEffectType.GetCurSel();
		if (ListIndex >= 0)	m_pCurrentSection->Data.GetPerkData02().Effect = (byte) m_SectionEffectType.GetItemData(ListIndex);

		ListIndex = m_SectionApplyType.GetCurSel();
		if (ListIndex >= 0) m_pCurrentSection->Data.GetPerkData02().ModType = (byte) m_SectionApplyType.GetItemData(ListIndex);
		
		ListIndex = m_SectionUnknownType.GetCurSel();
		if (ListIndex >= 0)	m_pCurrentSection->Data.GetPerkData02().Unknown = (byte) m_SectionUnknownType.GetItemData(ListIndex);

		if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
						
		switch (m_pCurrentSection->Data.GetPerkData02().ModType)
		{
		case 0x01:
		case 0x02:
		case 0x03:
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x01);
			m_pCurrentSection->pEpfd->SetDataType(0x01);

			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData01().Value = (float) atof(Buffer);
			break;
		case 0x09:
			if (m_pCurrentSection->pEpf3 == NULL) m_pCurrentSection->CreateNewEpf3();
			m_pCurrentSection->pEpft->SetValue(0x04);			

			m_SectionValue.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");
			
			if (Buffer.IsEmpty())
			{
				delete m_pCurrentSection->pEpf2;
				m_pCurrentSection->pEpf2 = NULL;		
			}
			else
			{
				if (m_pCurrentSection->pEpf2 == NULL) m_pCurrentSection->CreateNewEpf2();
				m_pCurrentSection->pEpf2->SetString(Buffer);
			}

			m_SectionEditorID.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");
			pRecord = m_pRecordHandler->FindEditorID(Buffer);

			if (pRecord)
			{
				if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
				m_pCurrentSection->pEpfd->SetDataType(0x04);
				m_pCurrentSection->pEpfd->GetEpfdData04().FormID = pRecord->GetFormID();
				m_pCurrentSection->pEpf3->SetValue(3);
			}
			else
			{
				delete m_pCurrentSection->pEpfd;
				m_pCurrentSection->pEpfd = NULL;
				m_pCurrentSection->pEpf3->SetValue(0);
			}			

			break;
		case 0x0A:
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x05);
			m_pCurrentSection->pEpfd->SetDataType(0x05);

			m_SectionEditorID.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");

			pRecord = m_pRecordHandler->FindEditorID(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData05().FormID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;
			break;
		case 0x0B:
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x06);
			m_pCurrentSection->pEpfd->SetDataType(0x06);

			m_SectionEditorID.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");
			m_pCurrentSection->pEpfd->GetEpfdData06().String = Buffer;
			break;
		case 0x0E:
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x02);
			m_pCurrentSection->pEpfd->SetDataType(0x02);

			ListIndex = m_SectionActorValue.GetCurSel();
			if (ListIndex >= 0)	m_pCurrentSection->pEpfd->GetEpfdData02().ActorValue = (float) m_SectionActorValue.GetItemData(ListIndex);
			
			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData02().Factor = (float) atof(Buffer);
			break;
		case 0x0F:
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x07);
			m_pCurrentSection->pEpfd->SetDataType(0x07);

			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData07().String = Buffer;
			break;
		}	
	}

	UpdateSectionList(m_pCurrentSection);
}


void CSrPerkView::UpdateSectionList (srperk_section_t* pSection)
{
	for (int i = 0; i < m_SectionList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pData = m_SectionList.GetCustomData(i);
		if (pData == NULL) continue;

		if (pData->pSubrecords[0] == &pSection->Prke)
		{
			SetSectionCustomData(*pData, pSection);
			UpdatePerkSectionList(i, true);
			return;
		}
	}
}


void CSrPerkView::SetSectionData (void)
{
	CString Buffer;

	m_IsUpdating = true;

	m_SectionType.SetCurSel(-1);
	m_SectionEffectType.SetCurSel(-1);
	m_SectionApplyType.SetCurSel(-1);
	m_SectionUnknownType.SetCurSel(-1);
	m_SectionActorValue.SetCurSel(-1);
	m_SectionIndex.SetWindowText("");
	m_SectionEditorID.SetWindowText("");
	m_SectionValue.SetWindowText("");
	m_SectionConditions.SetWindowText("");

	if (m_pCurrentSection == NULL) 
	{
		m_IsUpdating = false;
		return;	
	}

	FindComboBoxItemData(m_SectionType, m_pCurrentSection->Prke.GetPrkeData().Type, true);

	Buffer.Format("%u", (dword) m_pCurrentSection->Prke.GetPrkeData().Index);
	m_SectionIndex.SetWindowText(Buffer);

	Buffer.Format("%u", m_pCurrentSection->Subsections.GetSize());
	m_SectionConditions.SetWindowText(Buffer);
	
	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		m_SectionEditorID.SetWindowText(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->Data.GetPerkData00().QuestID));

		Buffer.Format("%d", (int) m_pCurrentSection->Data.GetPerkData00().Stage);
		m_SectionValue.SetWindowText(Buffer);
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		m_SectionEditorID.SetWindowText(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->Data.GetPerkData01().RecordID));
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		FindComboBoxItemData(m_SectionEffectType,  m_pCurrentSection->Data.GetPerkData02().Effect,  true);
		FindComboBoxItemData(m_SectionApplyType,   m_pCurrentSection->Data.GetPerkData02().ModType, true);
		FindComboBoxItemData(m_SectionUnknownType, m_pCurrentSection->Data.GetPerkData02().Unknown, true);

		switch (m_pCurrentSection->Data.GetPerkData02().ModType)
		{
		case 0x01:
		case 0x02:
		case 0x03:
			if (m_pCurrentSection->pEpfd != NULL)
			{
				Buffer.Format("%g", m_pCurrentSection->pEpfd->GetEpfdData01().Value);
				m_SectionValue.SetWindowText(Buffer);
			}
			break;
		case 0x09:
			if (m_pCurrentSection->pEpfd != NULL)
			{
				m_SectionEditorID.SetWindowTextA(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->pEpfd->GetEpfdData04().FormID));
			}
			if (m_pCurrentSection->pEpf2) m_SectionValue.SetWindowText(m_pCurrentSection->pEpf2->GetString().c_str());
			break;
		case 0x0A:
			if (m_pCurrentSection->pEpfd != NULL) m_SectionEditorID.SetWindowTextA(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->pEpfd->GetEpfdData05().FormID));
			break;
		case 0x0B:
			if (m_pCurrentSection->pEpfd != NULL)m_SectionEditorID.SetWindowTextA(m_pCurrentSection->pEpfd->GetEpfdData06().String.c_str());
			break;
		case 0x0E:
			if (m_pCurrentSection->pEpfd != NULL)
			{
				FindComboBoxItemData(m_SectionActorValue, (dword) m_pCurrentSection->pEpfd->GetEpfdData02().ActorValue, true);
				Buffer.Format("%g",  m_pCurrentSection->pEpfd->GetEpfdData02().Factor);
				m_SectionValue.SetWindowText(Buffer);
			}
			break;
		case 0x0F:
			if (m_pCurrentSection->pEpfd != NULL)
			{
				m_SectionValue.SetWindowText(m_pCurrentSection->pEpfd->GetEpfdData07().String.c_str());
			}
			break;
		}	
	}
	
	m_IsUpdating = false;
}


void CSrPerkView::EnableSectionControls (void)
{
	bool Enable = m_pCurrentSection != NULL;
	bool EnableActorValue = false;
	bool EnableEditorID = false;
	bool EnableValue = false;

	m_SectionType.EnableWindow(Enable);
	m_SectionIndex.EnableWindow(Enable);
	m_SectionEffectType.EnableWindow(Enable);
	m_SectionApplyType.EnableWindow(Enable);
	m_SectionUnknownType.EnableWindow(Enable);
	m_SectionEditorID.EnableWindow(Enable);
	m_EditEditorIDButton.EnableWindow(Enable);
	m_SelectEditorIDButton.EnableWindow(Enable);
	m_SectionActorValue.EnableWindow(Enable);
	m_SectionValue.EnableWindow(Enable);	
	m_SectionConditions.EnableWindow(Enable);

	if (!Enable || m_pCurrentSection == NULL) return;

	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		m_SectionEffectType.EnableWindow(false);
		m_SectionApplyType.EnableWindow(false);
		m_SectionUnknownType.EnableWindow(false);
		m_SectionConditions.EnableWindow(false);
		m_SectionActorValue.EnableWindow(false);

		EnableEditorID = true;
		EnableValue = true;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		m_SectionEffectType.EnableWindow(false);
		m_SectionApplyType.EnableWindow(false);
		m_SectionUnknownType.EnableWindow(false);
		m_SectionConditions.EnableWindow(false);
		m_SectionActorValue.EnableWindow(false);

		EnableEditorID = true;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		m_SectionEffectType.EnableWindow(true);
		m_SectionApplyType.EnableWindow(true);
		m_SectionUnknownType.EnableWindow(true);
		m_SectionConditions.EnableWindow(true);

		switch (m_pCurrentSection->Data.GetPerkData02().ModType)
		{
			case 0x01:
			case 0x02:
			case 0x03:
				EnableValue = true;
				break;
			case 0x09:
				EnableValue = true;
				EnableEditorID = true;
				break;
			case 0x0A:
				EnableEditorID = true;
				break;
			case 0x0B:
				EnableEditorID = true;
				break;
			case 0x0E:
				EnableValue = true;
				EnableActorValue = true;
				break;
			case 0x0F:
				EnableValue = true;
				break;
		}
	}

	m_SectionActorValue.EnableWindow(EnableActorValue);
	m_SectionEditorID.EnableWindow(EnableEditorID);
	m_EditEditorIDButton.EnableWindow(EnableEditorID);
	m_SelectEditorIDButton.EnableWindow(EnableEditorID);
	m_SectionValue.EnableWindow(EnableValue);
}


void CSrPerkView::UpdateSectionLabels (void)
{
	if (m_pCurrentSection == NULL) 
	{
		m_SectionValueLabel.SetWindowText("None");
		m_SectionEditorIDLabel.SetWindowText("None");
		return;
	}
	
	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		m_SectionValueLabel.SetWindowText("Stage");
		m_SectionEditorIDLabel.SetWindowText("Quest");
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		m_SectionEditorIDLabel.SetWindowText("Spell");
		m_SectionValueLabel.SetWindowText("None");
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		switch (m_pCurrentSection->Data.GetPerkData02().ModType)
		{
			case 0x01:
			case 0x02:
			case 0x03:
				m_SectionEditorIDLabel.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Value");
				break;
			case 0x09:
				m_SectionEditorIDLabel.SetWindowText("Spell?");
				m_SectionValueLabel.SetWindowText("Verb String?");
				break;
			case 0x0A:
				m_SectionEditorIDLabel.SetWindowText("Spell");
				m_SectionValueLabel.SetWindowText("None");
				break;
			case 0x0B:
				m_SectionEditorIDLabel.SetWindowText("Game Setting");
				m_SectionValueLabel.SetWindowText("None");
				break;
			case 0x0E:
				m_SectionEditorIDLabel.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Skill Adjust");
				break;
			case 0x0F:
				m_SectionEditorIDLabel.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Verb String?");
				break;
		}
	}

}


void CSrPerkView::CopyConditions (void) 
{
	if (GetInputRecord() == NULL) return;
	if (m_IgnoreConditions) return;

	for (dword i = 0; i < GetInputRecord()->GetNumSubrecords(); ++i)
	{
		CSrSubrecord* pSubrecord = GetInputRecord()->GetSubrecord(i);
		if (pSubrecord->GetRecordType() == SR_NAME_PRKE) break;
		if (pSubrecord->GetRecordType() != SR_NAME_CTDA) continue;		

		CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pSubrecord);
		if (pCondition != NULL) CreateConditionInfo(pCondition, GetInputRecord(), i);
	}

		/* Always save conditions in PERKs */
	m_ConditionsChanged = true;
}


void CSrPerkView::GetControlData (void)
{
	GetSectionData();

		/* Force delete of subrecords to ensure proper order */
	GetOutputRecord()->DeleteSubrecords(SR_NAME_DATA);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_PRKE);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_PRKC);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_CTDA);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_CIS1);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_CIS2);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_EPFT);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_EPFD);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_EPF2);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_EPF3);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_PRKF);

		/* Recreate the base DATA */
	GetOutputRecord()->AddNewSubrecord(SR_NAME_DATA);

		/* Save the basic perk data */
	CSrRecordDialog::GetControlData();

		/* Save all the perk section data */
	for (dword i = 0; i < m_Sections.GetSize(); ++i)
	{
		srperk_section_t* pSection = m_Sections[i];

		GetOutputRecord()->GetSubrecordArray().Add(pSection->Prke.CreateCopy());
		GetOutputRecord()->GetSubrecordArray().Add(pSection->Data.CreateCopy());

		for (dword j = 0; j < pSection->Subsections.GetSize(); ++j)
		{
			srperk_subsection_t* pSubsection = pSection->Subsections[j];
			GetOutputRecord()->GetSubrecordArray().Add(pSubsection->Prkc.CreateCopy());

			for (dword k = 0; k < pSubsection->Conditions.GetSize(); ++k)
			{
				srconditioninfo_t* pCondInfo = pSubsection->Conditions[k];
				GetOutputRecord()->GetSubrecordArray().Add(pCondInfo->Condition.CreateCopy());
				if (pCondInfo->pParam1) GetOutputRecord()->GetSubrecordArray().Add(pCondInfo->pParam1->CreateCopy());
				if (pCondInfo->pParam2) GetOutputRecord()->GetSubrecordArray().Add(pCondInfo->pParam2->CreateCopy());
			}			
		}

		if (pSection->pEpft) GetOutputRecord()->GetSubrecordArray().Add(pSection->pEpft->CreateCopy());
		if (pSection->pEpf2) GetOutputRecord()->GetSubrecordArray().Add(pSection->pEpf2->CreateCopy());
		if (pSection->pEpf3) GetOutputRecord()->GetSubrecordArray().Add(pSection->pEpf3->CreateCopy());
		if (pSection->pEpfd) GetOutputRecord()->GetSubrecordArray().Add(pSection->pEpfd->CreateCopy());
		GetOutputRecord()->GetSubrecordArray().Add(pSection->Prkf.CreateCopy());
	}
}


void CSrPerkView::SetControlData (void)
{
	CSrRecordDialog::SetControlData();
	SetPerkSectionList();
}


int CSrPerkView::OnPreSaveRecord (void)
{
	return CSrRecordDialog::OnPreSaveRecord();
}


void CSrPerkView::OnDropNextPerk (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_NextPerk, SR_NAME_PERK, 1);
}


void CSrPerkView::OnBnClickedEditNextperk()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_NextPerk, SR_NAME_PERK);
}


void CSrPerkView::OnBnClickedSelectNextperk()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_NextPerk, SR_NAME_PERK, &CSrPerkRecord::s_FieldMap);
}


void CSrPerkView::OnBnClickedAddperkButton()
{
	// TODO: Add your control notification handler code here
}


void CSrPerkView::OnBnClickedDeleteperkButton()
{
	// TODO: Add your control notification handler code here
}


void CSrPerkView::OnBnClickedSectionConditions()
{
	if (m_pCurrentSection == NULL) return;
	CSrConditionArray Conditions;

	for (dword i = 0; i < m_pCurrentSection->Subsections.GetSize(); ++i)
	{
		srperk_subsection_t* pSubsection = m_pCurrentSection->Subsections[i];

		for (dword j = 0; j < pSubsection->Conditions.GetSize(); ++j)
		{
			srconditioninfo_t* pCond = pSubsection->Conditions[j];
			pCond->Condition.SetPrkc(pSubsection->Prkc.GetValue());

			srconditioninfo_t* pNewCond = Conditions.AddNew();
			pNewCond->Copy(*pCond);
		}
	}

	CSrConditionDlg ConditionDlg;
	int Result = ConditionDlg.DoModal(GetInputRecord(), &Conditions, true);
	if (Result != IDOK) return;
	m_ConditionsChanged = true;

	CString Buffer;
	Buffer.Format("%d", m_pCurrentSection->Subsections.GetSize());
	m_SectionConditions.SetWindowText(Buffer);

			/* Recreate the subsection structure */
	m_pCurrentSection->Subsections.Destroy();
	byte CurrentPrkc = 0xff;

	srperk_subsection_t* pCurrentSubsection = NULL;

	for (dword i = 0; i < Conditions.GetSize(); ++i)
	{
		srconditioninfo_t* pCond = Conditions[i];

		if (pCond->Condition.GetPrkc() != CurrentPrkc || pCurrentSubsection == NULL)
		{
			pCurrentSubsection = m_pCurrentSection->Subsections.AddNew();
			CurrentPrkc = pCond->Condition.GetPrkc();

			pCurrentSubsection->Prkc.Initialize(SR_NAME_PRKC, 1);
			pCurrentSubsection->Prkc.InitializeNew();
			pCurrentSubsection->Prkc.SetValue(pCond->Condition.GetPrkc());
		}

		srconditioninfo_t* pNewCond = pCurrentSubsection->Conditions.AddNew();
		pNewCond->Copy(*pCond);
	}

	Buffer.Format("%d", m_pCurrentSection->Subsections.GetSize());
	m_SectionConditions.SetWindowText(Buffer);

	GetSectionData();
}


void CSrPerkView::OnBnClickedEditSectioneditorid()
{
	srrectype_t RecordType = SR_NAME_NULL;

	if (m_pCurrentSection == NULL || m_pDlgHandler == NULL) return;

	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		RecordType = SR_NAME_QUST;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		RecordType = SR_NAME_SPEL;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		if (m_pCurrentSection->Data.GetPerkData02().ModType == 0x09) 
			RecordType = SR_NAME_SPEL;
		else if (m_pCurrentSection->Data.GetPerkData02().ModType == 0x0A) 
			RecordType = SR_NAME_SPEL;
		else if (m_pCurrentSection->Data.GetPerkData02().ModType == 0x0B) 
			RecordType = SR_NAME_GMST;
	}

	if (RecordType != SR_NAME_NULL) m_pDlgHandler->EditRecordHelper(&m_SectionEditorID, RecordType);
}


void CSrPerkView::OnBnClickedSelectSectioneditorid()
{
	srrectype_t RecordType = SR_NAME_NULL;
	const srrecfieldmap_t* pFieldMap = NULL;

	if (m_pCurrentSection == NULL || m_pDlgHandler == NULL) return;

	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		RecordType = SR_NAME_QUST;
		pFieldMap = &CSrQustRecord::s_FieldMap;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		RecordType = SR_NAME_SPEL;
		pFieldMap = &CSrSpelRecord::s_FieldMap;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		if (m_pCurrentSection->Data.GetPerkData02().ModType == 0x09) 
		{
			RecordType = SR_NAME_SPEL;
			pFieldMap = &CSrSpelRecord::s_FieldMap;
		}
		else if (m_pCurrentSection->Data.GetPerkData02().ModType == 0x0A) 
		{
			RecordType = SR_NAME_SPEL;
			pFieldMap = &CSrSpelRecord::s_FieldMap;
		}
		else if (m_pCurrentSection->Data.GetPerkData02().ModType == 0x0B) 
		{
			RecordType = SR_NAME_GMST;
			pFieldMap = &CSrGmstRecord::s_FieldMap;
		}
	}

	if (RecordType != SR_NAME_NULL && pFieldMap != NULL) m_pDlgHandler->SelectRecordHelper(&m_SectionEditorID, RecordType, pFieldMap);
}


void CSrPerkView::OnCbnSelchangeSectiontype()
{
	if (m_IsUpdating) return;
	GetSectionData();
	EnableSectionControls();
	UpdateSectionLabels();
}


void CSrPerkView::OnCbnSelchangeSectionapplytype()
{
	if (m_IsUpdating) return;
	GetSectionData();
	EnableSectionControls();
	UpdateSectionLabels();
}


void CSrPerkView::OnLvnItemchangedPerkdataList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetSectionData();
	SetCurrentSection(m_Sections[pNMLV->iItem]);
	SetSectionData();
}


/*===========================================================================
 *
 * Class CSrPerkView Event - int OnDropCustomSectionData (DropItems);
 *
 *=========================================================================*/
int CSrPerkView::OnDropCustomSectionData (srrldroprecords_t& DropItems) 
{
	CSrPrkeSubrecord*		pPrke;
	srrlcustomdata_t*		pCustomData;
	srperk_section_t*   	pSection;
	dword					Index;
	CSrPrkeSubrecord*		pSrcPrke;
	CSrSubrecord*			pSubrecord;
	srperk_subsection_t*	pCurrentSubsection = NULL;
	srconditioninfo_t*		pCurrentCondInfo = NULL;

	GetSectionData();

		/* Check all custom data dropped */
	for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
	{
		pCustomData = DropItems.pCustomDatas->GetAt(Index);

		if (pCustomData->pSubrecords    == NULL) return SRRL_DROPCHECK_ERROR;
		if (pCustomData->pSubrecords[0] == NULL) return SRRL_DROPCHECK_ERROR;

			/* Check for dragging another effect record */
		pPrke = SrCastClassNull(CSrPrkeSubrecord, pCustomData->pSubrecords[0]);
		if (pPrke == NULL) return SRRL_DROPCHECK_ERROR;

		pSrcPrke = SrCastClassNull(CSrPrkeSubrecord, pPrke);
		if (pSrcPrke == NULL) return SRRL_DROPCHECK_ERROR;
	        
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

		pSection = m_Sections.AddNew();
		if (pSection == NULL) continue;		

		pSection->Prke.Copy(pSrcPrke);

		for (dword i = 1; i < SR_RLMAX_SUBRECORDS; ++i)
		{
			if (pCustomData->pSubrecords[i] == NULL) break;
			pSubrecord = pCustomData->pSubrecords[i];

			if (pSubrecord->GetRecordType() == SR_NAME_DATA)
			{
				pSection->Data.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_PRKC)
			{
				 pCurrentSubsection = pSection->Subsections.AddNew();
				 pCurrentSubsection->Prkc.Copy(pSubrecord);
				 pCurrentCondInfo = NULL;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_CTDA && pCurrentSubsection != NULL)
			{
				pCurrentCondInfo = pCurrentSubsection->Conditions.AddNew();
				pCurrentCondInfo->Condition.Copy(pSubrecord);
				pCurrentCondInfo->Condition.SetPrkc(pCurrentSubsection->Prkc.GetValue());
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_CIS1 && pCurrentCondInfo != NULL)
			{
				 pCurrentCondInfo->CopyParam1(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_CIS2 && pCurrentCondInfo != NULL)
			{
				 pCurrentCondInfo->CopyParam2(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPFT)
			{
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpft = SrCastClass(CSrByteSubrecord, pTmp);
				 if (pSection->pEpft == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPF2)
			{
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpf2 = SrCastClass(CSrLStringSubrecord, pTmp);
				 if (pSection->pEpf2 == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPF3)
			{
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpf3 = SrCastClass(CSrDwordSubrecord, pTmp);
				 if (pSection->pEpf3 == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPFD)
			{
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpfd = SrCastClass(CSrEpfdSubrecord, pTmp);
				 if (pSection->pEpfd == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_PRKF)
			{
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 pSection->Prkf.Copy(pSubrecord);
				 break;
			}
		}		

		AddPerkSectionList(pSection);
	}

	return SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrPerkView::OnDropCustomSectionData()
 *=========================================================================*/


 /*===========================================================================
 *
 * Class CSrPerkView Event - void OnDropSectionList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrPerkView::OnDropSectionList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = SRRL_DROPCHECK_ERROR;
	
	if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) 
	{
	  *pResult = OnDropCustomSectionData(*pDropItems);
	}
	else if (pDropItems->pRecords != NULL) 
	{
	} 
	
}
/*===========================================================================
 *		End of Class Event CSrPerkView::OnDropSectionList()
 *=========================================================================*/
