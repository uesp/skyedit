#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageHead1.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CSrRacePageHead1, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageHead1, CPropertyPage)
	ON_BN_CLICKED(IDC_ADD_RACEPRESET, &CSrRacePageHead1::OnBnClickedAddRacepreset)
	ON_BN_CLICKED(IDC_EDIT_RACEPRESET, &CSrRacePageHead1::OnBnClickedEditRacepreset)
	ON_BN_CLICKED(IDC_DEL_RACEPRESET, &CSrRacePageHead1::OnBnClickedDelRacepreset)
	ON_BN_CLICKED(IDC_ADD_HAIRCOLOR, &CSrRacePageHead1::OnBnClickedAddHaircolor)
	ON_BN_CLICKED(IDC_EDIT_HAIRCOLOR, &CSrRacePageHead1::OnBnClickedEditHaircolor)
	ON_BN_CLICKED(IDC_DEL_HAIRCOLOR, &CSrRacePageHead1::OnBnClickedDelHaircolor)
	ON_BN_CLICKED(IDC_ADD_FEATURESET, &CSrRacePageHead1::OnBnClickedAddFeatureset)
	ON_BN_CLICKED(IDC_EDIT_FEATURESET, &CSrRacePageHead1::OnBnClickedEditFeatureset)
	ON_BN_CLICKED(IDC_DEL_FEATURESET, &CSrRacePageHead1::OnBnClickedDelFeatureset)
	ON_BN_CLICKED(IDC_EDIT_HEADFEATURE, &CSrRacePageHead1::OnBnClickedEditHeadfeature)
	ON_BN_CLICKED(IDC_SELECT_HEADFEATURE, &CSrRacePageHead1::OnBnClickedSelectHeadfeature)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RACEPRESETS, OnDropRacePresets)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RACEPRESETS, OnDropRacePresets)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_HAIRCOLORS, OnDropHairColors)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_HAIRCOLORS, OnDropHairColors)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FEATURESETS, OnDropFeatureSets)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FEATURESETS, OnDropFeatureSets)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_HEADFEATURE, OnDropHeadFeature)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_HEADFEATURE, OnDropHeadFeature)
	ON_LBN_DBLCLK(IDC_RACEPRESETS, &CSrRacePageHead1::OnLbnDblclkRacepresets)
	ON_LBN_DBLCLK(IDC_HAIRCOLORS, &CSrRacePageHead1::OnLbnDblclkHaircolors)
	ON_LBN_DBLCLK(IDC_FEATURESETS, &CSrRacePageHead1::OnLbnDblclkFeaturesets)
END_MESSAGE_MAP()


CSrRacePageHead1::CSrRacePageHead1(srraceinfo_t& RaceInfo, const bool IsMale)
	: CPropertyPage(), m_RaceInfo(RaceInfo), m_IsMale(IsMale), m_HeadInfo(IsMale ? RaceInfo.MaleHead : RaceInfo.FemaleHead)
{

}


CSrRacePageHead1::~CSrRacePageHead1()
{
}


void CSrRacePageHead1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RACEPRESETS, m_RacePresets);
	DDX_Control(pDX, IDC_HAIRCOLORS, m_HairColors);
	DDX_Control(pDX, IDC_FEATURESETS, m_FeatureSets);
	DDX_Control(pDX, IDC_HEADFEATURE, m_HeadFeature);
}


void CSrRacePageHead1::GetControlData (void)
{
	CString    Buffer;
	CSrRecord* pRecord;

	m_HeadFeature.GetWindowTextA(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord =  m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_HeadInfo.SetHeadFeature(pRecord ? pRecord->GetFormID() : 0);

	m_HeadInfo.RacialPresets.Destroy();
	m_HeadInfo.HairColors.Destroy();
	m_HeadInfo.FeatureSets.Destroy();

	for (int i = 0; i < m_RacePresets.GetCount(); ++i)
	{
		m_RacePresets.GetText(i, Buffer);
		pRecord =  m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddRacePreset(pRecord->GetFormID());
	}

	for (int i = 0; i < m_HairColors.GetCount(); ++i)
	{
		m_HairColors.GetText(i, Buffer);
		pRecord =  m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddHairColor(pRecord->GetFormID());
	}

	for (int i = 0; i < m_FeatureSets.GetCount(); ++i)
	{
		m_FeatureSets.GetText(i, Buffer);
		pRecord =  m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddFeatureSet(pRecord->GetFormID());
	}

}


void CSrRacePageHead1::SetControlData (void)
{
	m_HeadFeature.SetWindowTextA(m_HeadInfo.pHeadFeature ? m_pParent->m_pRecordHandler->GetEditorID(m_HeadInfo.pHeadFeature->GetValue()) : "");

	m_RacePresets.ResetContent();
	m_HairColors.ResetContent();
	m_FeatureSets.ResetContent();

	for (dword i = 0; i < m_HeadInfo.RacialPresets.GetSize(); ++i)
	{
		const char* pString = m_pParent->m_pRecordHandler->GetEditorID(m_HeadInfo.RacialPresets[i]->GetValue());
		if (pString) m_RacePresets.AddString(pString);
	}

	for (dword i = 0; i < m_HeadInfo.HairColors.GetSize(); ++i)
	{
		const char* pString = m_pParent->m_pRecordHandler->GetEditorID(m_HeadInfo.HairColors[i]->GetValue());
		if (pString) m_HairColors.AddString(pString);
	}

	for (dword i = 0; i < m_HeadInfo.FeatureSets.GetSize(); ++i)
	{
		const char* pString = m_pParent->m_pRecordHandler->GetEditorID(m_HeadInfo.FeatureSets[i]->GetValue());
		if (pString) m_FeatureSets.AddString(pString);
	}
}


BOOL CSrRacePageHead1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	return TRUE;
}


void CSrRacePageHead1::OnBnClickedAddRacepreset()
{
	CString Buffer;
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_NPC_, &CSrNpc_Record::s_FieldMap)) return;
	m_RacePresets.AddString(Buffer);
}


void CSrRacePageHead1::OnBnClickedEditRacepreset()
{
	CString Buffer;
	int     ListIndex = m_RacePresets.GetCurSel();

	if (ListIndex < 0) return;
	m_RacePresets.GetText(ListIndex, Buffer);

	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_NPC_, &CSrNpc_Record::s_FieldMap)) return;

	m_RacePresets.DeleteString(ListIndex);
	m_RacePresets.InsertString(ListIndex, Buffer);
}


void CSrRacePageHead1::OnBnClickedDelRacepreset()
{
	int ListIndex = m_RacePresets.GetCurSel();
	if (ListIndex < 0) return;

	m_RacePresets.DeleteString(ListIndex);

	if (ListIndex > 0) m_RacePresets.SetCurSel(ListIndex - 1);
	else m_RacePresets.SetCurSel(0);
}


void CSrRacePageHead1::OnBnClickedAddHaircolor()
{
	CString Buffer;
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_CLFM, &CSrClfmRecord::s_FieldMap)) return;
	m_HairColors.AddString(Buffer);
}


void CSrRacePageHead1::OnBnClickedEditHaircolor()
{
	CString Buffer;
	int     ListIndex = m_HairColors.GetCurSel();

	if (ListIndex < 0) return;
	m_HairColors.GetText(ListIndex, Buffer);

	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_CLFM, &CSrClfmRecord::s_FieldMap)) return;

	m_HairColors.DeleteString(ListIndex);
	m_HairColors.InsertString(ListIndex, Buffer);
}


void CSrRacePageHead1::OnBnClickedDelHaircolor()
{
	int ListIndex = m_HairColors.GetCurSel();
	if (ListIndex < 0) return;

	m_HairColors.DeleteString(ListIndex);

	if (ListIndex > 0) m_HairColors.SetCurSel(ListIndex - 1);
	else m_HairColors.SetCurSel(0);
}


void CSrRacePageHead1::OnBnClickedAddFeatureset()
{
	CString Buffer;
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap)) return;
	m_FeatureSets.AddString(Buffer);
}


void CSrRacePageHead1::OnBnClickedEditFeatureset()
{
	CString Buffer;
	int     ListIndex = m_FeatureSets.GetCurSel();

	if (ListIndex < 0) return;
	m_FeatureSets.GetText(ListIndex, Buffer);

	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap)) return;

	m_FeatureSets.DeleteString(ListIndex);
	m_FeatureSets.InsertString(ListIndex, Buffer);
}


void CSrRacePageHead1::OnBnClickedDelFeatureset()
{
	int ListIndex = m_FeatureSets.GetCurSel();
	if (ListIndex < 0) return;

	m_FeatureSets.DeleteString(ListIndex);

	if (ListIndex > 0) m_FeatureSets.SetCurSel(ListIndex - 1);
	else m_FeatureSets.SetCurSel(0);
}


void CSrRacePageHead1::OnBnClickedEditHeadfeature()
{
	m_pDlgHandler->EditRecordHelper(&m_HeadFeature, SR_NAME_TXST);
}


void CSrRacePageHead1::OnBnClickedSelectHeadfeature()
{
	m_pDlgHandler->SelectRecordHelper(&m_HeadFeature, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap);
}


void CSrRacePageHead1::OnDropRacePresets (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_RacePresets, SR_NAME_NPC_, false);
}


void CSrRacePageHead1::OnDropHairColors (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_HairColors, SR_NAME_CLFM, false);
}


void CSrRacePageHead1::OnDropFeatureSets (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_FeatureSets, SR_NAME_TXST, false);
}


void CSrRacePageHead1::OnDropHeadFeature (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_HeadFeature, SR_NAME_TXST, 1);
}


void CSrRacePageHead1::OnLbnDblclkRacepresets()
{
	OnBnClickedEditRacepreset();
}


void CSrRacePageHead1::OnLbnDblclkHaircolors()
{
	OnBnClickedEditHaircolor();
}


void CSrRacePageHead1::OnLbnDblclkFeaturesets()
{
	OnBnClickedEditFeatureset();
}
