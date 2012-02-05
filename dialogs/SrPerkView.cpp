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
#include <vector>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrPerkView, CSrRecordDialog);

	srperkeffectinfo_t CSrPerkView::s_EffectInfoQuest = { 0xff, 0, 0, { 0, 0, 0 } };
	srperkeffectinfo_t CSrPerkView::s_EffectInfoSpell = { 0xff, 0, 0, { 0, 0, 0 } };
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
	ON_BN_CLICKED(IDC_SECTION_CONDITIONS1, &CSrPerkView::OnBnClickedSectionConditions1)
	ON_BN_CLICKED(IDC_SECTION_CONDITIONS2, &CSrPerkView::OnBnClickedSectionConditions2)
	ON_BN_CLICKED(IDC_SECTION_CONDITIONS3, &CSrPerkView::OnBnClickedSectionConditions3)
	ON_BN_CLICKED(IDC_EDIT_SECTIONEDITORID, &CSrPerkView::OnBnClickedEditSectioneditorid)
	ON_BN_CLICKED(IDC_SELECT_SECTIONEDITORID, &CSrPerkView::OnBnClickedSelectSectioneditorid)
	ON_CBN_SELCHANGE(IDC_SECTIONEFFECTTYPE, &CSrPerkView::OnCbnSelchangeSectionEffectType)
	ON_CBN_SELCHANGE(IDC_SECTIONFUNCTIONTYPE, &CSrPerkView::OnCbnSelchangeSectionFunctionType)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PERKDATA_LIST, &CSrPerkView::OnLvnItemchangedPerkdataList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_PERKDATA_LIST, OnDropSectionList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_PERKDATA_LIST, OnDropSectionList)	
	ON_COMMAND(ID_PERKSECTION_ADD, &CSrPerkView::OnPerksectionAdd)
	ON_COMMAND(ID_PERKSECTION_DELETE, &CSrPerkView::OnPerksectionDelete)
	ON_COMMAND(ID_PERKSECTION_DUPLICATE, &CSrPerkView::OnPerksectionDuplicate)
	ON_UPDATE_COMMAND_UI(ID_PERKSECTION_DELETE, &CSrPerkView::OnUpdatePerksectionEdit)
	ON_UPDATE_COMMAND_UI(ID_PERKSECTION_DUPLICATE, &CSrPerkView::OnUpdatePerksectionEdit)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_CONDITIONRECORD_COPY, OnConditionrecordCopy)
	ON_COMMAND(ID_CONDITIONRECORD_PASTE, OnConditionrecordPaste)
	ON_COMMAND(ID_CONDITIONRECORD_DELETEALL, OnConditionrecordDeleteAll)
	ON_UPDATE_COMMAND_UI(ID_CONDITIONRECORD_COPY, OnUpdateConditionrecordCopy)
	ON_UPDATE_COMMAND_UI(ID_CONDITIONRECORD_PASTE, OnUpdateConditionrecordPaste)
	ON_UPDATE_COMMAND_UI(ID_CONDITIONRECORD_DELETEALL, OnUpdateConditionrecordDeleteAll)
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
	{ SR_FIELD_PERKRANK,			40,		LVCFMT_CENTER },
	{ SR_FIELD_PERKPRIORITY,		40,		LVCFMT_CENTER },
	{ SR_FIELD_PERKEFFECTTYPE,		100,	LVCFMT_CENTER },
	{ SR_FIELD_PERKFUNCTIONTYPE,	80,		LVCFMT_CENTER },
	{ SR_FIELD_PERKSEFFDATA,		150,	LVCFMT_CENTER },
	{ SR_FIELD_CONDITIONCOUNT,		60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_SectionFields[] = {
	{ "Rank",			SR_FIELD_PERKRANK,				0, NULL },
	{ "Priority",		SR_FIELD_PERKPRIORITY,			0, NULL },
	{ "EffectType",		SR_FIELD_PERKEFFECTTYPE,		0, NULL },
	{ "Function",		SR_FIELD_PERKFUNCTIONTYPE,		0, NULL },
	{ "EffectData",		SR_FIELD_PERKSEFFDATA,			0, NULL },
	{ "Conditions",		SR_FIELD_CONDITIONCOUNT,		0, NULL },
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
	m_pScriptList = &m_Scripts;
	m_InitialSetData = false;
	m_IsInitialized = false;
	m_IsUpdating = false;
	m_pCurrentSection = NULL;
	m_ContextConditionIndex = -1;
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
	DDX_Control(pDX, IDC_SECTIONINDEX, m_SectionPriority);
	DDX_Control(pDX, IDC_SECTIONRANK, m_SectionRank);
	DDX_Control(pDX, IDC_SECTION_CONDITIONS1, m_SectionConditions[0]);
	DDX_Control(pDX, IDC_SECTION_CONDITIONS2, m_SectionConditions[1]);
	DDX_Control(pDX, IDC_SECTION_CONDITIONS3, m_SectionConditions[2]);
	DDX_Control(pDX, IDC_SECTION_EDITORIDLABEL, m_SectionEditorIDLabel);
	DDX_Control(pDX, IDC_SECTION_EDITORID, m_SectionEditorID);
	DDX_Control(pDX, IDC_EDIT_SECTIONEDITORID, m_EditEditorIDButton);
	DDX_Control(pDX, IDC_SELECT_SECTIONEDITORID, m_SelectEditorIDButton);
	DDX_Control(pDX, IDC_SECTION_ACTORVALUE, m_SectionActorValue);
	DDX_Control(pDX, IDC_SECTIONVALUE, m_SectionValue);
	DDX_Control(pDX, IDC_SECTION_VALUELABEL1, m_SectionValueLabel);
	DDX_Control(pDX, IDC_SECTIONEFFECTTYPE, m_SectionEffectType);
	DDX_Control(pDX, IDC_SECTIONFUNCTIONTYPE, m_SectionFunctionType);
	DDX_Control(pDX, IDC_SECTION_VALUELABEL2, m_SectionValueLabel2);
	DDX_Control(pDX, IDC_SECTIONVALUE2, m_SectionValue2);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_Scripts);
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
	void CSrPerkView::AssertValid() const { CSrRecordDialog::AssertValid(); }
	void CSrPerkView::Dump(CDumpContext& dc) const { CSrRecordDialog::Dump(dc); }
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

	FillPerkEffectList();
	FillPerkFunctionList();	
	SrFillComboList(m_SectionActorValue, s_SrActorValues, 0);
	m_SectionActorValue.SetCurSel(0);

	CopyPerkSections();
	
	SetControlData();
	m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrPerkView::OnInitialUpdate()
 *=========================================================================*/


void CSrPerkView::FillPerkEffectList (void)
{
	int ListIndex; 

	m_SectionEffectType.ResetContent();

		/* Fill standard effects */
	SrFillComboList(m_SectionEffectType, s_SrPerkEffectTypes, 0);

		/* Add custom "quest" type */
	ListIndex = m_SectionEffectType.AddString("Quest");
	if (ListIndex >= 0) m_SectionEffectType.SetItemData(ListIndex, SRPERK_EFFECTTYPE_CUSTOMQUEST);

		/* Add custom "spell" type */
	ListIndex = m_SectionEffectType.AddString("Spell");
	if (ListIndex >= 0) m_SectionEffectType.SetItemData(ListIndex, SRPERK_EFFECTTYPE_CUSTOMSPELL);
}


void CSrPerkView::FillPerkFunctionList (void)
{
	CString            CurrentSelString;
	srperkeffectinfo_t EffectInfo;
	
	m_SectionFunctionType.GetWindowText(CurrentSelString);	
	m_SectionFunctionType.ResetContent();

	int ListIndex = m_SectionEffectType.GetCurSel();
	if (ListIndex < 0) return;
	int EffectType = m_SectionEffectType.GetItemData(ListIndex);

	if (EffectType == SRPERK_EFFECTTYPE_CUSTOMQUEST) 
	{
		EffectInfo = s_EffectInfoQuest;
	}
	else if (EffectType == SRPERK_EFFECTTYPE_CUSTOMSPELL) 
	{
		EffectInfo = s_EffectInfoSpell;
	}
	else
	{
		EffectInfo = GetSrPerkEffectInfo(m_SectionEffectType.GetItemData(ListIndex));
		if (EffectInfo.EffectType == 0xff) return;
	}

	for (dword i = 1; i <= SRPERK_EFFECT_FUNCTION_MAX; ++i)
	{
		if (EffectInfo.IsFunctionType(i))
		{
			CString Buffer(GetSrPerkFunctionTypeString(i));
			ListIndex = m_SectionFunctionType.AddString(Buffer);
			if (ListIndex >= 0) m_SectionFunctionType.SetItemData(ListIndex, i);
		}
	}

	if (CurrentSelString.IsEmpty())
		m_SectionFunctionType.SetCurSel(0);
	else
	{
		int Result = m_SectionFunctionType.SelectString(-1, CurrentSelString);
		if (Result < 0) m_SectionFunctionType.SetCurSel(0);
	}
}


void CSrPerkView::CopyPerkSections (void)
{
	CSrPerkRecord* pPerk = SrCastClass(CSrPerkRecord, GetInputRecord());
	if (pPerk) pPerk->CreateInfo(m_Sections);
}


void CSrPerkView::FillPerkSectionList (void)
{
	m_SectionList.DeleteAllItems();
	
	for (dword i = 0; i < m_Sections.GetSize(); ++i) 
	{
		AddPerkSectionList(m_Sections[i]);
	}

	m_SectionList.SelectRecord(0);
	SetCurrentSection(m_Sections[0]);
}


void CSrPerkView::SetSectionCustomData (srrlcustomdata_t& CustomData, srperksectioninfo_t* pSection)
{
	CustomData.Subrecords.Destroy();

	CustomData.pRecord = GetInputRecord();
	CustomData.Subrecords.Add(&pSection->Prke);
	CustomData.Subrecords.Add(&pSection->Data);
  
	for (dword k = 0; k < pSection->Conditions.GetSize(); ++k)
	{
		srconditioninfo_t* pCondInfo = pSection->Conditions[k];
		CustomData.Subrecords.Add(&pCondInfo->Condition);
		if (pCondInfo->pParam1) CustomData.Subrecords.Add(pCondInfo->pParam1);
		if (pCondInfo->pParam2) CustomData.Subrecords.Add(pCondInfo->pParam2);
	}

	if (pSection->pEpft) CustomData.Subrecords.Add(pSection->pEpft);
	if (pSection->pEpf2) CustomData.Subrecords.Add(pSection->pEpf2);
	if (pSection->pEpf3) CustomData.Subrecords.Add(pSection->pEpf3);
	if (pSection->pEpfd) CustomData.Subrecords.Add(pSection->pEpfd);
	CustomData.Subrecords.Add(&pSection->Prkf);
}


int CSrPerkView::AddPerkSectionList (srperksectioninfo_t* pSection)
{
	srrlcustomdata_t  CustomData;
	CString           Buffer;
	int		          ListIndex;

	SetSectionCustomData(CustomData, pSection);	
  
	ListIndex = m_SectionList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdatePerkSectionList(ListIndex, false);
	return (ListIndex);
}


srperksectioninfo_t* CSrPerkView::FindPerkSection(CSrPrkeSubrecord* pPrke)
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
	srperksectioninfo_t*	pSection;
	CSrPrkeSubrecord*	pPrke;
	CString				Buffer;

	if (GetInputRecord() == NULL) return;

	pCustomData = m_SectionList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	if (Update) m_SectionList.UpdateRecord(ListIndex);

	pPrke = SrCastClassNull(CSrPrkeSubrecord, pCustomData->Subrecords[0]);
	if (pPrke == NULL) return;

	pSection = FindPerkSection(pPrke);
	if (pSection == NULL) return;

	Buffer.Format("%d", (int) pSection->Prke.GetPrkeData().Rank);
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKRANK, Buffer);

	Buffer.Format("%d", (int) pSection->Prke.GetPrkeData().Priority);
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKPRIORITY, Buffer);

	Buffer.Format("%d", (int) pSection->CountConditions());
	m_SectionList.SetCustomField(ListIndex, SR_FIELD_CONDITIONCOUNT, Buffer);
		
	if (pSection->Data.GetPerkDataType() == SR_PERKDATA_TYPE02)
	{
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKEFFECTTYPE, GetSrPerkEffectTypeString(pSection->Data.GetPerkData02().EffectType));
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKFUNCTIONTYPE, GetSrPerkFunctionTypeString(pSection->Data.GetPerkData02().FunctionType));
	}
	else if (pSection->Data.GetPerkDataType() == SR_PERKDATA_TYPE01)
	{
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKEFFECTTYPE, "Spell");
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKFUNCTIONTYPE, "");
	}
	else if (pSection->Data.GetPerkDataType() == SR_PERKDATA_TYPE00)
	{
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKEFFECTTYPE, "Quest");
		m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKFUNCTIONTYPE, "");
	}

	m_SectionList.SetCustomField(ListIndex, SR_FIELD_PERKSEFFDATA, GetPerkSectionDataString(*pSection));	
}


CString CSrPerkView::GetPerkSectionDataString (srperksectioninfo_t& Section)
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
		switch (Section.Data.GetPerkData02().FunctionType)
		{
		case 0x01:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 1) Result.Format("=%g", Section.pEpfd->GetEpfdData01().Value);
			break;
		case 0x02:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 1) Result.Format("+%g", Section.pEpfd->GetEpfdData01().Value);
			break;
		case 0x03:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 1) Result.Format("*%g", Section.pEpfd->GetEpfdData01().Value);
			break;
		case 0x04:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 2) Result.Format("+random(%g, %g)", Section.pEpfd->GetEpfdData02().Value1, Section.pEpfd->GetEpfdData02().Value2);
			break;
		case 0x05:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 2) Result.Format("+%s * %g", ::GetSrActorValueString((int)Section.pEpfd->GetEpfdData02().Value1), Section.pEpfd->GetEpfdData02().Value2);
			break;
		case 0x06:
			Result.Format("=abs()");
			break;
		case 0x07:
			Result.Format("=-abs()");
			break;
		case 0x08:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 3) Result.Format("%s", GetInputRecord()->GetParent()->GetEditorID(Section.pEpfd->GetEpfdData03().FormID));
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
		case 0x0C:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 2) Result.Format("=%s * %g", GetSrActorValueString((int)Section.pEpfd->GetEpfdData02().Value1), Section.pEpfd->GetEpfdData02().Value2);
			break;
		case 0x0D:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 2) Result.Format("*%s * %g", GetSrActorValueString((int)Section.pEpfd->GetEpfdData02().Value1), Section.pEpfd->GetEpfdData02().Value2);
			break;
		case 0x0E:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 2) Result.Format("*(1+%s * %g)", GetSrActorValueString((int)Section.pEpfd->GetEpfdData02().Value1), Section.pEpfd->GetEpfdData02().Value2);
			break;
		case 0x0F:
			if (Section.pEpfd && Section.pEpfd->GetDataType() == 7) Result.Format("%s", Section.pEpfd->GetEpfdData07().String.c_str());
			break;
		}	
	}

	return Result;
}


void CSrPerkView::SetCurrentSection (srperksectioninfo_t* pSection)
{
	GetSectionData();

	m_pCurrentSection = pSection;
	
	SetSectionData();
}


void CSrPerkView::GetSectionData (void)
{
	CString      Buffer;
	CSrIdRecord* pRecord;
	dword        EffectType;
	int          ListIndex;
	int			 Value;

	if (m_pCurrentSection == NULL) return;
	
	m_SectionPriority.GetWindowText(Buffer);
	Value = strtol(Buffer, 0, NULL);
	if (Value < 0) Value = 0;
	if (Value > 255) Value = 255;
	m_pCurrentSection->Prke.GetPrkeData().Priority = Value;

	m_SectionRank.GetWindowText(Buffer);
	Value = strtol(Buffer, 0, NULL);
	if (Value < 0) Value = 0;
	if (Value > 255) Value = 255;
	m_pCurrentSection->Prke.GetPrkeData().Rank = Value;

	ListIndex = m_SectionEffectType.GetCurSel();
	EffectType = m_SectionEffectType.GetItemData(ListIndex);

	delete m_pCurrentSection->pEpft;
	delete m_pCurrentSection->pEpf2;
	delete m_pCurrentSection->pEpf3;
	delete m_pCurrentSection->pEpfd;
	m_pCurrentSection->pEpft = NULL;
	m_pCurrentSection->pEpf2 = NULL;
	m_pCurrentSection->pEpf3 = NULL;
	m_pCurrentSection->pEpfd = NULL;
	
	if (EffectType == SRPERK_EFFECTTYPE_CUSTOMQUEST)
	{
		m_pCurrentSection->Prke.GetPrkeData().Type = SR_PERKDATA_TYPE00;
		m_pCurrentSection->Data.SetDataType(SR_PERKDATA_TYPE00);
		m_SectionEditorID.GetWindowText(Buffer);
		Buffer.Trim(" \t\n\r");

		pRecord = m_pRecordHandler->FindEditorID(Buffer);
		m_pCurrentSection->Data.GetPerkData00().QuestID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;
		
		m_SectionValue.GetWindowText(Buffer);
		m_pCurrentSection->Data.GetPerkData00().Stage = atoi(Buffer);
	}
	else if (EffectType == SRPERK_EFFECTTYPE_CUSTOMSPELL)
	{
		m_pCurrentSection->Prke.GetPrkeData().Type = SR_PERKDATA_TYPE01;
		m_pCurrentSection->Data.SetDataType(SR_PERKDATA_TYPE01);
		m_SectionEditorID.GetWindowText(Buffer);
		Buffer.Trim(" \t\n\r");

		pRecord = m_pRecordHandler->FindEditorID(Buffer);
		m_pCurrentSection->Data.GetPerkData01().RecordID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;

	}
	else if (EffectType >= 0 && EffectType <= SRPERK_EFFECT_TYPE_MAX)
	{
		m_pCurrentSection->Prke.GetPrkeData().Type = SR_PERKDATA_TYPE02;
		m_pCurrentSection->Data.SetDataType(SR_PERKDATA_TYPE02);
		m_pCurrentSection->Data.GetPerkData02().EffectType = (byte) (EffectType & 0xFF);

		const srperkeffectinfo_t EffectInfo = GetSrPerkEffectInfo(EffectType & 0xFF);
		m_pCurrentSection->Data.GetPerkData02().CondTypeCount = EffectInfo.ConditionTypeCounts;

		ListIndex = m_SectionFunctionType.GetCurSel();
		if (ListIndex >= 0) m_pCurrentSection->Data.GetPerkData02().FunctionType = (byte) m_SectionFunctionType.GetItemData(ListIndex);
						
		switch (m_pCurrentSection->Data.GetPerkData02().FunctionType)
		{
		case 0x01:
		case 0x02:
		case 0x03:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x01);
			m_pCurrentSection->pEpfd->SetDataType(0x01);

			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData01().Value = (float) atof(Buffer);
			break;
		case 0x06:
		case 0x07:
			break;
		case 0x08:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x03);
			m_pCurrentSection->pEpfd->SetDataType(0x03);

			m_SectionEditorID.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");

			pRecord = m_pRecordHandler->FindEditorID(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData03().FormID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;
			break;
		case 0x09:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
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
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x05);
			m_pCurrentSection->pEpfd->SetDataType(0x05);

			m_SectionEditorID.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");

			pRecord = m_pRecordHandler->FindEditorID(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData05().FormID = pRecord ? pRecord->GetFormID() : SR_FORMID_NULL;
			break;
		case 0x0B:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x06);
			m_pCurrentSection->pEpfd->SetDataType(0x06);

			m_SectionEditorID.GetWindowText(Buffer);
			Buffer.Trim(" \t\n\r");
			m_pCurrentSection->pEpfd->GetEpfdData06().String = Buffer;
			break;
		case 0x04:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x02);
			m_pCurrentSection->pEpfd->SetDataType(0x02);

			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData02().Value1 = (float) atof(Buffer);
			m_SectionValue2.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData02().Value2 = (float) atof(Buffer);
			break;
		case 0x05:
		case 0x0C:
		case 0x0D:
		case 0x0E:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x02);
			m_pCurrentSection->pEpfd->SetDataType(0x02);

			ListIndex = m_SectionActorValue.GetCurSel();
			if (ListIndex >= 0)	m_pCurrentSection->pEpfd->GetEpfdData02().Value1 = (float) m_SectionActorValue.GetItemData(ListIndex);
			
			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData02().Value2 = (float) atof(Buffer);
			break;
		case 0x0F:
			if (m_pCurrentSection->pEpft == NULL) m_pCurrentSection->CreateNewEpft();
			if (m_pCurrentSection->pEpfd == NULL) m_pCurrentSection->CreateNewEpfd();
			m_pCurrentSection->pEpft->SetValue(0x07);
			m_pCurrentSection->pEpfd->SetDataType(0x07);

			m_SectionValue.GetWindowText(Buffer);
			m_pCurrentSection->pEpfd->GetEpfdData07().String = Buffer;
			break;
		}	
	}
	else
	{
		SystemLog.Printf("PerkDialog: Unknown effect type 0x%08X!", EffectType);
	}

	UpdateSectionList(m_pCurrentSection);
}


void CSrPerkView::UpdateSectionList (srperksectioninfo_t* pSection)
{
	for (int i = 0; i < m_SectionList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pData = m_SectionList.GetCustomData(i);
		if (pData == NULL) continue;

		if (pData->Subrecords[0] == &pSection->Prke)
		{
			SetSectionCustomData(*pData, pSection);
			UpdatePerkSectionList(i, true);
			return;
		}
	}
}


void CSrPerkView::UpdateSectionConditionLabels (void)
{
	CString Buffer;
	int ListIndex = m_SectionEffectType.GetCurSel();
	const srperkeffectinfo_t EffectInfo = GetSrPerkEffectInfo(ListIndex >= 0 ? m_SectionEffectType.GetItemData(ListIndex) : SRPERK_EFFECT_TYPE_MAX);

	for (dword i = 0; i < SRPERK_EFFECT_MAXCONDTYPES; ++i)
	{
		if (i >= EffectInfo.ConditionTypeCounts)
		{
			m_SectionConditions[i].SetWindowText("");
			m_SectionConditions[i].EnableWindow(false);
		}
		else
		{
			const char* pString = GetSrPerkConditionTypeString(EffectInfo.ConditionTypes[i]);

			if (pString == NULL || *pString == '\0')
			{
				m_SectionConditions[i].SetWindowText("");
				m_SectionConditions[i].EnableWindow(false);
			}
			else
			{
				Buffer.Format("%d %s", m_pCurrentSection->CountSubsections(i), pString);
				m_SectionConditions[i].SetWindowText(Buffer);
				m_SectionConditions[i].EnableWindow(true);
			}
		}
	}

}


void CSrPerkView::SetSectionData (void)
{
	CString Buffer;

	m_IsUpdating = true;

	m_SectionEffectType.SetCurSel(-1);
	m_SectionFunctionType.SetCurSel(-1);
	m_SectionActorValue.SetCurSel(0);
	m_SectionPriority.SetWindowText("");
	m_SectionRank.SetWindowText("");
	m_SectionEditorID.SetWindowText("");
	m_SectionValue.SetWindowText("");
	m_SectionValue2.SetWindowText("");
	m_SectionConditions[0].SetWindowText("");
	m_SectionConditions[1].SetWindowText("");
	m_SectionConditions[2].SetWindowText("");

	if (m_pCurrentSection == NULL) 
	{
		EnableSectionControls();
		m_IsUpdating = false;
		return;	
	}

	Buffer.Format("%u", (dword) m_pCurrentSection->Prke.GetPrkeData().Priority);
	m_SectionPriority.SetWindowText(Buffer);

	Buffer.Format("%u", (dword) m_pCurrentSection->Prke.GetPrkeData().Rank);
	m_SectionRank.SetWindowText(Buffer);

	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		FindComboBoxItemData(m_SectionEffectType, SRPERK_EFFECTTYPE_CUSTOMQUEST, true);
		m_SectionEditorID.SetWindowText(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->Data.GetPerkData00().QuestID));

		Buffer.Format("%d", (int) m_pCurrentSection->Data.GetPerkData00().Stage);
		m_SectionValue.SetWindowText(Buffer);

		FillPerkFunctionList();
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		FindComboBoxItemData(m_SectionEffectType, SRPERK_EFFECTTYPE_CUSTOMSPELL, true);
		m_SectionEditorID.SetWindowText(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->Data.GetPerkData01().RecordID));

		FillPerkFunctionList();
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		FindComboBoxItemData(m_SectionEffectType,    m_pCurrentSection->Data.GetPerkData02().EffectType,  true);
		FillPerkFunctionList();
		FindComboBoxItemData(m_SectionFunctionType,  m_pCurrentSection->Data.GetPerkData02().FunctionType, true);

		switch (m_pCurrentSection->Data.GetPerkData02().FunctionType)
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
		case 0x06:
		case 0x07:
				//No Data
			break;
		case 0x08:
			if (m_pCurrentSection->pEpfd != NULL) m_SectionEditorID.SetWindowTextA(GetInputRecord()->GetParent()->GetEditorID(m_pCurrentSection->pEpfd->GetEpfdData03().FormID));
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
		case 0x04:
			if (m_pCurrentSection->pEpfd != NULL)
			{
				Buffer.Format("%g", m_pCurrentSection->pEpfd->GetEpfdData02().Value1);
				m_SectionValue.SetWindowText(Buffer);

				Buffer.Format("%g", m_pCurrentSection->pEpfd->GetEpfdData02().Value2);
				m_SectionValue2.SetWindowText(Buffer);
			}
			break;
			break;
		case 0x05:
		case 0x0C:
		case 0x0D:
		case 0x0E:
			if (m_pCurrentSection->pEpfd != NULL)
			{
				int Result = FindComboBoxItemData(m_SectionActorValue, (dword) m_pCurrentSection->pEpfd->GetEpfdData02().Value1, true);
				if (Result < 0) m_SectionActorValue.SetCurSel(0);
				Buffer.Format("%g",  m_pCurrentSection->pEpfd->GetEpfdData02().Value2);
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

	EnableSectionControls();
	UpdateSectionLabels();
	
	UpdateSectionConditionLabels();
	m_IsUpdating = false;
}


void CSrPerkView::EnableSectionControls (void)
{
	bool Enable = m_pCurrentSection != NULL;
	bool EnableActorValue = false;
	bool EnableEditorID = false;
	bool EnableValue = false;
	bool EnableValue2 = false;

	m_SectionPriority.EnableWindow(Enable);
	m_SectionRank.EnableWindow(Enable);
	m_SectionEffectType.EnableWindow(Enable);
	m_SectionFunctionType.EnableWindow(Enable);
	m_SectionEditorID.EnableWindow(Enable);
	m_EditEditorIDButton.EnableWindow(Enable);
	m_SelectEditorIDButton.EnableWindow(Enable);
	m_SectionActorValue.EnableWindow(Enable);
	m_SectionValue.EnableWindow(Enable);	
	m_SectionValue2.EnableWindow(Enable);	
	m_SectionConditions[0].EnableWindow(Enable);
	m_SectionConditions[1].EnableWindow(Enable);
	m_SectionConditions[2].EnableWindow(Enable);

	if (!Enable || m_pCurrentSection == NULL) return;

	m_SectionEffectType.EnableWindow(true);
	m_SectionFunctionType.EnableWindow(true);

	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		m_SectionConditions[0].EnableWindow(false);
		m_SectionConditions[1].EnableWindow(false);
		m_SectionConditions[2].EnableWindow(false);
		m_SectionActorValue.EnableWindow(false);

		EnableEditorID = true;
		EnableValue = true;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		m_SectionConditions[0].EnableWindow(false);
		m_SectionConditions[1].EnableWindow(false);
		m_SectionConditions[2].EnableWindow(false);
		m_SectionActorValue.EnableWindow(false);

		EnableEditorID = true;
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		switch (m_pCurrentSection->Data.GetPerkData02().FunctionType)
		{
			case 0x01:
			case 0x02:
			case 0x03:
				EnableValue = true;
				break;
			case 0x08:
				EnableValue = false;
				EnableEditorID = true;
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
			case 0x04:
				EnableValue = true;
				EnableValue2 = true;
				EnableActorValue = false;
				break;
			case 0x05:
			case 0x0C:
			case 0x0D:
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
	m_SectionValue2.EnableWindow(EnableValue2);
}


void CSrPerkView::UpdateSectionLabels (void)
{
	if (m_pCurrentSection == NULL) 
	{
		m_SectionValueLabel.SetWindowText("None");
		m_SectionValueLabel2.SetWindowText("None");
		m_SectionEditorIDLabel.SetWindowText("None");
		return;
	}
	
	if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00)
	{
		m_SectionValueLabel.SetWindowText("Stage");
		m_SectionValueLabel2.SetWindowText("None");
		m_SectionEditorIDLabel.SetWindowText("Quest");
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01)
	{
		m_SectionEditorIDLabel.SetWindowText("Spell");
		m_SectionValueLabel2.SetWindowText("None");
		m_SectionValueLabel.SetWindowText("None");
	}
	else if (m_pCurrentSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE02)
	{
		switch (m_pCurrentSection->Data.GetPerkData02().FunctionType)
		{
			case 0x01:
			case 0x02:
			case 0x03:
				m_SectionEditorIDLabel.SetWindowText("None");
				m_SectionValueLabel2.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Value");
				break;
			case 0x06:
			case 0x07:
				m_SectionValueLabel.SetWindowText("None");
				m_SectionValueLabel2.SetWindowText("None");
				m_SectionEditorIDLabel.SetWindowText("None");
				break;
			case 0x08:
				m_SectionEditorIDLabel.SetWindowText("LevelList");
				m_SectionValueLabel2.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("None");
				break;
			case 0x09:
				m_SectionEditorIDLabel.SetWindowText("Spell");
				m_SectionValueLabel2.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Activate");
				break;
			case 0x0A:
				m_SectionEditorIDLabel.SetWindowText("Spell");
				m_SectionValueLabel2.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("None");
				break;
			case 0x0B:
				m_SectionEditorIDLabel.SetWindowText("Game Setting");
				m_SectionValueLabel2.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("None");
				break;
			case 0x04:
				m_SectionValueLabel.SetWindowText("Min");
				m_SectionValueLabel2.SetWindowText("Max");				
				break;
			case 0x05:
			case 0x0C:
			case 0x0D:
			case 0x0E:
				m_SectionEditorIDLabel.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Skill Adjust");
				m_SectionValueLabel2.SetWindowText("None");
				break;
			case 0x0F:
				m_SectionEditorIDLabel.SetWindowText("None");
				m_SectionValueLabel.SetWindowText("Text");
				m_SectionValueLabel2.SetWindowText("None");
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

		/* Always save base conditions in PERKs */
	m_ConditionsChanged = true;
}


void CSrPerkView::GetControlData (void)
{
	byte MaxPrkc = 0;

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
		srperksectioninfo_t* pSection = m_Sections[i];

		GetOutputRecord()->GetSubrecordArray().Add(pSection->Prke.CreateCopy());
		GetOutputRecord()->GetSubrecordArray().Add(pSection->Data.CreateCopy());
		byte LastPrkc = -1;

				/* Ignore conditions if required */
		if (pSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE00 || pSection->Prke.GetPrkeData().Type == SR_PERKDATA_TYPE01) 
		{
			MaxPrkc = 0;
		}
		else
		{
			const srperkeffectinfo_t EffectInfo = GetSrPerkEffectInfo(pSection->Data.GetPerkData02().EffectType);
			MaxPrkc = EffectInfo.ConditionTypeCounts;
		}

		for (dword k = 0; k < pSection->Conditions.GetSize(); ++k)
		{
			srconditioninfo_t* pCondInfo = pSection->Conditions[k];

			if (pCondInfo->Condition.GetPrkc() != LastPrkc)
			{
				LastPrkc = pCondInfo->Condition.GetPrkc();
				if (LastPrkc >= MaxPrkc) break;

				CSrSubrecord* pSubrecord = GetOutputRecord()->AddInitNewSubrecord(SR_NAME_PRKC);
				CSrByteSubrecord* pPrkc = SrCastClassNull(CSrByteSubrecord, pSubrecord);
				if (pPrkc) pPrkc->SetValue(LastPrkc);				
			}

			GetOutputRecord()->GetSubrecordArray().Add(pCondInfo->Condition.CreateCopy());
			if (pCondInfo->pParam1) GetOutputRecord()->GetSubrecordArray().Add(pCondInfo->pParam1->CreateCopy());
			if (pCondInfo->pParam2) GetOutputRecord()->GetSubrecordArray().Add(pCondInfo->pParam2->CreateCopy());
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
	FillPerkSectionList();
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
	GetSectionData();
	m_pCurrentSection = NULL;

	srperksectioninfo_t* pSection = m_Sections.AddNew();
	pSection->InitializeNew();

	int ListIndex = AddPerkSectionList(pSection);
	m_SectionList.ClearSelections();
	m_SectionList.SelectRecord(ListIndex);
}


void CSrPerkView::OnBnClickedDeleteperkButton()
{
	GetSectionData();
	m_pCurrentSection = NULL;

	int ListIndex = m_SectionList.GetSelectedItem();
	if (ListIndex < 0) return;

	m_SectionList.DeleteItem(ListIndex);
	m_Sections.Delete(ListIndex);
	m_SectionList.ClearSelections();
	
	if (m_SectionList.GetItemCount() == 0)
		SetCurrentSection(NULL);
	else if (ListIndex == 0)
		m_SectionList.SelectRecord(ListIndex);
	else
		m_SectionList.SelectRecord(ListIndex-1);

}


void CSrPerkView::OnBnClickedSectionConditions1()
{
	OnEditSectionConditions(0);
}


void CSrPerkView::OnBnClickedSectionConditions2()
{
	OnEditSectionConditions(1);
}


void CSrPerkView::OnBnClickedSectionConditions3()
{
	OnEditSectionConditions(2);
}


void CSrPerkView::OnEditSectionConditions(const dword Index)
{
	CSrConditionArray Conditions;

	if (m_pCurrentSection == NULL) return;
	if (Index >= 3) return;	

		/* Copy conditions to edit */
	for (dword j = 0; j < m_pCurrentSection->Conditions.GetSize(); ++j)
	{
		srconditioninfo_t* pCond = m_pCurrentSection->Conditions[j];

		if (pCond->Condition.GetPrkc() == Index)
		{
			srconditioninfo_t* pNewCond = Conditions.AddNew();
			pNewCond->Copy(*pCond);
		}
	}

	CSrConditionDlg ConditionDlg;
	int Result = ConditionDlg.DoModal(GetInputRecord(), &Conditions);
	if (Result != IDOK) return;
	m_ConditionsChanged = true;

		/* Delete "old" conditions */
	for (int i = (int)m_pCurrentSection->Conditions.GetSize() - 1; i >= 0; --i)
	{
		srconditioninfo_t* pCond = m_pCurrentSection->Conditions[i];
		if (pCond->Condition.GetPrkc() == Index) m_pCurrentSection->Conditions.Delete(i);
	}

		/* Recreate the conditions data just edited/deleted */
	for (dword i = 0; i < Conditions.GetSize(); ++i)
	{
		srconditioninfo_t* pCond = Conditions[i];
		srconditioninfo_t* pNewCond = m_pCurrentSection->Conditions.AddNew();
		pNewCond->Copy(*pCond);
		pNewCond->Condition.SetPrkc(Index);
	}

	UpdateSectionConditionLabels();
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
		if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x09) 
			RecordType = SR_NAME_SPEL;
		else if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x0A) 
			RecordType = SR_NAME_SPEL;
		else if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x0B) 
			RecordType = SR_NAME_GMST;
		else if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x08) 
			RecordType = SR_NAME_LVLI;
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
		if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x09) 
		{
			RecordType = SR_NAME_SPEL;
			pFieldMap = &CSrSpelRecord::s_FieldMap;
		}
		else if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x08)
		{
			RecordType = SR_NAME_LVLI;
			pFieldMap = &CSrLvliRecord::s_FieldMap;
		}
		else if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x0A) 
		{
			RecordType = SR_NAME_SPEL;
			pFieldMap = &CSrSpelRecord::s_FieldMap;
		}
		else if (m_pCurrentSection->Data.GetPerkData02().FunctionType == 0x0B) 
		{
			RecordType = SR_NAME_GMST;
			pFieldMap = &CSrGmstRecord::s_FieldMap;
		}
	}

	if (RecordType != SR_NAME_NULL && pFieldMap != NULL) m_pDlgHandler->SelectRecordHelper(&m_SectionEditorID, RecordType, pFieldMap);
}


void CSrPerkView::OnCbnSelchangeSectionEffectType()
{
	if (m_IsUpdating) return;
	m_IsUpdating = true;

	GetSectionData();

	FillPerkFunctionList();
	UpdateSectionConditionLabels();
	EnableSectionControls();
	UpdateSectionLabels();

	m_IsUpdating = false;
}


void CSrPerkView::OnCbnSelchangeSectionFunctionType()
{
	if (m_IsUpdating) return;

	GetSectionData();

	UpdateSectionLabels();
	EnableSectionControls();
}


void CSrPerkView::OnLvnItemchangedPerkdataList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	SetCurrentSection(m_Sections[pNMLV->iItem]);
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
	srperksectioninfo_t*   	pSection;
	dword					Index;
	CSrPrkeSubrecord*		pSrcPrke;
	CSrSubrecord*			pSubrecord;
	srconditioninfo_t*		pCurrentCondInfo = NULL;

	GetSectionData();

		/* Check all custom data dropped */
	for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
	{
		pCustomData = DropItems.pCustomDatas->GetAt(Index);

			/* Check for dragging another effect record */
		pPrke = SrCastClassNull(CSrPrkeSubrecord, pCustomData->Subrecords[0]);
		if (pPrke == NULL) return SRRL_DROPCHECK_ERROR;

		pSrcPrke = SrCastClassNull(CSrPrkeSubrecord, pPrke);
		if (pSrcPrke == NULL) return SRRL_DROPCHECK_ERROR;
	        
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

		pSection = m_Sections.AddNew();
		if (pSection == NULL) continue;		

		pSection->Prke.Copy(pSrcPrke);

		for (dword i = 1; i < pCustomData->Subrecords.GetSize(); ++i)
		{
			if (pCustomData->Subrecords[i] == NULL) continue;
			pSubrecord = pCustomData->Subrecords[i];

			if (pSubrecord->GetRecordType() == SR_NAME_DATA)
			{
				pSection->Data.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_CTDA)
			{
				pCurrentCondInfo = pSection->Conditions.AddNew();
				pCurrentCondInfo->Condition.Copy(pSubrecord);
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
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpft = SrCastClass(CSrByteSubrecord, pTmp);
				 if (pSection->pEpft == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPF2)
			{
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpf2 = SrCastClass(CSrLStringSubrecord, pTmp);
				 if (pSection->pEpf2 == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPF3)
			{
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpf3 = SrCastClass(CSrDwordSubrecord, pTmp);
				 if (pSection->pEpf3 == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPFD)
			{
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpfd = SrCastClass(CSrEpfdSubrecord, pTmp);
				 if (pSection->pEpfd == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_PRKF)
			{
				 pCurrentCondInfo   = NULL;

				 pSection->Prkf.Copy(pSubrecord);
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


 void CSrPerkView::OnPerksectionAdd()
 {
	 OnBnClickedAddperkButton();
 }

 
 void CSrPerkView::OnPerksectionDelete()
 {
	 OnBnClickedDeleteperkButton();
 }


 void CSrPerkView::OnPerksectionDuplicate()
 {
	 std::vector<srperksectioninfo_t*> NewSections;
	 POSITION Pos;
	 int      ListIndex;
	
	 GetSectionData();
	 
	 Pos = m_SectionList.GetFirstSelectedItemPosition();

	 while (Pos)
	 {
		ListIndex = m_SectionList.GetNextSelectedItem(Pos);
		srrlcustomdata_t* pCustomData = m_SectionList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		srconditioninfo_t*		pCurrentCondInfo = NULL;
		srperksectioninfo_t*   	pSection;
		CSrSubrecord*			pSubrecord;

		pSection = m_Sections.AddNew();
		if (pSection == NULL) continue;	

		for (dword i = 0; i < pCustomData->Subrecords.GetSize(); ++i)
		{
			if (pCustomData->Subrecords[i] == NULL) continue;
			pSubrecord = pCustomData->Subrecords[i];

			if (pSubrecord->GetRecordType() == SR_NAME_PRKE)
			{
				pSection->Prke.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_DATA)
			{
				pSection->Data.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_CTDA)
			{
				pCurrentCondInfo = pSection->Conditions.AddNew();
				pCurrentCondInfo->Condition.Copy(pSubrecord);
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
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpft = SrCastClass(CSrByteSubrecord, pTmp);
				 if (pSection->pEpft == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPF2)
			{
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpf2 = SrCastClass(CSrLStringSubrecord, pTmp);
				 if (pSection->pEpf2 == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPF3)
			{
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpf3 = SrCastClass(CSrDwordSubrecord, pTmp);
				 if (pSection->pEpf3 == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPFD)
			{
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pSection->pEpfd = SrCastClass(CSrEpfdSubrecord, pTmp);
				 if (pSection->pEpfd == NULL) delete pTmp;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_PRKF)
			{
				 pCurrentCondInfo   = NULL;

				 pSection->Prkf.Copy(pSubrecord);
			}
		}

		NewSections.push_back(pSection);
	 }
	 
	 for (auto i = NewSections.begin(); i != NewSections.end(); ++i)
	 {
		AddPerkSectionList(*i);
	 }

 }


 void CSrPerkView::OnUpdatePerksectionEdit(CCmdUI *pCmdUI)
 {
	pCmdUI->Enable(m_pCurrentSection != NULL);
 }


 void CSrPerkView::OnContextMenu(CWnd* pWnd, CPoint Point)
 {
 	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;
	
	if (pWnd->GetDlgCtrlID() == IDC_PERKDATA_LIST) 
	{
		Result = Menu.LoadMenu(IDR_PERKSECTION_MENU);
		if (!Result) return;
		
		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;
		
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_SECTION_CONDITIONS1 ||
		     pWnd->GetDlgCtrlID() == IDC_SECTION_CONDITIONS2 ||
			 pWnd->GetDlgCtrlID() == IDC_SECTION_CONDITIONS3) 
	{
		if (pWnd->GetDlgCtrlID() == IDC_SECTION_CONDITIONS1)
			m_ContextConditionIndex = 0;
		else if (pWnd->GetDlgCtrlID() == IDC_SECTION_CONDITIONS2)
			m_ContextConditionIndex = 1;
		else if (pWnd->GetDlgCtrlID() == IDC_SECTION_CONDITIONS3)
			m_ContextConditionIndex = 2;
		else
			m_ContextConditionIndex = -1;

		Result = Menu.LoadMenu(IDR_CONDITIONRECORD_MENU);
		if (!Result) return;
		
		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;
		
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
	else 
	{
		CSrRecordDialog::OnContextMenu(pWnd, Point);
	}
	  
 }

 
void CSrPerkView::OnConditionrecordCopy()
{
	if (m_pCurrentSection == NULL || m_ContextConditionIndex < 0 || m_ContextConditionIndex >= SRPERK_EFFECT_MAXCONDTYPES) return;
	if (m_pCurrentSection->CountSubsections(m_ContextConditionIndex) == 0) return;

	SrGlobClipClearConditions();

	for (dword i = 0; i < m_pCurrentSection->Conditions.GetSize(); ++i)
	{
		if (m_pCurrentSection->Conditions[i]->Condition.GetPrkc() != m_ContextConditionIndex) continue;
		SrGlobClipAddCondition(m_pCurrentSection->Conditions[i]);
	}

}


void CSrPerkView::OnConditionrecordPaste()
{
	if (m_pCurrentSection == NULL || m_ContextConditionIndex < 0 || m_ContextConditionIndex >= SRPERK_EFFECT_MAXCONDTYPES) return;
	if (SrGlobClipGetConditions().GetSize() == 0) return;

	for (dword i = 0; i < SrGlobClipGetConditions().GetSize(); ++i)
	{
		srconditioninfo_t* pNewCond = m_pCurrentSection->Conditions.AddNew();
		pNewCond->Copy(*SrGlobClipGetConditions()[i]);
		pNewCond->Condition.SetPrkc(m_ContextConditionIndex);
	}

	CString Buffer;
	Buffer.Format("%d", m_pCurrentSection->CountSubsections(m_ContextConditionIndex));
	m_SectionConditions[m_ContextConditionIndex].SetWindowText(Buffer);

	GetSectionData();
	SetSectionData();
}


void CSrPerkView::OnConditionrecordDeleteAll()
{
	if (m_pCurrentSection == NULL || m_ContextConditionIndex < 0 || m_ContextConditionIndex >= SRPERK_EFFECT_MAXCONDTYPES) return;
	
		/* Delete all conditions with the given index */
	for (int i = m_pCurrentSection->Conditions.GetSize() - 1; i >= 0 ; --i)
	{
		if (m_pCurrentSection->Conditions[i]->Condition.GetPrkc() == m_ContextConditionIndex)
		{
			m_pCurrentSection->Conditions.Delete(i);
		}
	}		
		
	m_SectionConditions[m_ContextConditionIndex].SetWindowText("0");
	GetSectionData();
	SetSectionData();
}


void CSrPerkView::OnUpdateConditionrecordCopy(CCmdUI *pCmdUI)
{
	if (m_pCurrentSection == NULL || m_ContextConditionIndex < 0 || m_ContextConditionIndex >= SRPERK_EFFECT_MAXCONDTYPES)
	{
		pCmdUI->Enable(false);
		return;
}

	CString Buffer;
	dword   Count = m_pCurrentSection->CountSubsections(m_ContextConditionIndex);
	Buffer.Format("Copy %d Condition(s)", Count);
	pCmdUI->SetText(Buffer);
	pCmdUI->Enable(Count > 0);
}


void CSrPerkView::OnUpdateConditionrecordPaste(CCmdUI *pCmdUI)
{
	if (m_pCurrentSection == NULL || m_ContextConditionIndex < 0 || m_ContextConditionIndex >= SRPERK_EFFECT_MAXCONDTYPES)
	{
		pCmdUI->Enable(false);
		return;
	}

	CString Buffer;
	dword Count = SrGlobClipGetConditions().GetSize();
	Buffer.Format("Paste %d Condition(s)", Count);
	pCmdUI->SetText(Buffer);
	pCmdUI->Enable(Count > 0);
}


void CSrPerkView::OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI)
{
	if (m_pCurrentSection == NULL || m_ContextConditionIndex < 0 || m_ContextConditionIndex >= SRPERK_EFFECT_MAXCONDTYPES)
	{
		pCmdUI->Enable(false);
		return;
	}

	pCmdUI->Enable(m_pCurrentSection->CountSubsections(m_ContextConditionIndex) > 0);
}