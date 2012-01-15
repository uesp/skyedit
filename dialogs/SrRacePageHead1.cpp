#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageHead1.h"
#include "afxdialogex.h"
#include <vector>


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
	ON_BN_CLICKED(IDC_ADD_HEADPART, &CSrRacePageHead1::OnBnClickedAddHeadpart)
	ON_BN_CLICKED(IDC_EDIT_HEADPART, &CSrRacePageHead1::OnBnClickedEditHeadpart)
	ON_BN_CLICKED(IDC_DEL_HEADPART, &CSrRacePageHead1::OnBnClickedDelHeadpart)
	ON_LBN_DBLCLK(IDC_HEADPARTS, &CSrRacePageHead1::OnLbnDblclkHeadparts)
	ON_BN_CLICKED(IDC_ADD_MPA, &CSrRacePageHead1::OnBnClickedAddMpa)
	ON_BN_CLICKED(IDC_DELETE_MPA, &CSrRacePageHead1::OnBnClickedDeleteMpa)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MPALIST, &CSrRacePageHead1::OnLvnItemchangedMpalist)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MPALIST, OnDropMpaList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MPALIST, OnDropMpaList)
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_RaceMpaListInit[] = {
	{ SR_FIELD_LISTUNKNOWN1,		30,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN2,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN3,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN4,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN5,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN6,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN7,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN8,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN9,		70,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_RaceMpaListFields[] = {
	{ "Idx",			SR_FIELD_LISTUNKNOWN1,			0, NULL },
	{ "U1",				SR_FIELD_LISTUNKNOWN2,			0, NULL },
	{ "U2",				SR_FIELD_LISTUNKNOWN3,			0, NULL },
	{ "U3",				SR_FIELD_LISTUNKNOWN4,			0, NULL },
	{ "U4",				SR_FIELD_LISTUNKNOWN5,			0, NULL },
	{ "U5",				SR_FIELD_LISTUNKNOWN6,			0, NULL },
	{ "U6",				SR_FIELD_LISTUNKNOWN7,			0, NULL },
	{ "U7",				SR_FIELD_LISTUNKNOWN8,			0, NULL },
	{ "U8",				SR_FIELD_LISTUNKNOWN9,			0, NULL },
	{ "U9",				SR_FIELD_LISTUNKNOWN10,			0, NULL },
	{ NULL,				SR_FIELD_NONE,					0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


CSrRacePageHead1::CSrRacePageHead1(srraceinfo_t& RaceInfo, const bool IsMale)
	: CPropertyPage(), m_RaceInfo(RaceInfo), m_IsMale(IsMale), m_HeadInfo(IsMale ? RaceInfo.MaleHead : RaceInfo.FemaleHead)
{
	m_pCurrentMpa = NULL;
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
	DDX_Control(pDX, IDC_HEADPARTS, m_HeadParts);
	DDX_Control(pDX, IDC_MPALIST, m_MpaList);
	DDX_Control(pDX, IDC_UNKNOWN1, m_MpaData[0]);
	DDX_Control(pDX, IDC_UNKNOWN2, m_MpaData[1]);
	DDX_Control(pDX, IDC_UNKNOWN3, m_MpaData[2]);
	DDX_Control(pDX, IDC_UNKNOWN4, m_MpaData[3]);
	DDX_Control(pDX, IDC_UNKNOWN5, m_MpaData[4]);
	DDX_Control(pDX, IDC_UNKNOWN6, m_MpaData[5]);
	DDX_Control(pDX, IDC_UNKNOWN7, m_MpaData[6]);
	DDX_Control(pDX, IDC_UNKNOWN8, m_MpaData[7]);
	DDX_Control(pDX, IDC_DELETE_MPA, m_DeleteMpa);
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
	m_HeadInfo.HeadData.Destroy();

	for (int i = 0; i < m_RacePresets.GetCount(); ++i)
	{
		m_RacePresets.GetText(i, Buffer);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddRacePreset(pRecord->GetFormID());
	}

	for (int i = 0; i < m_HairColors.GetCount(); ++i)
	{
		m_HairColors.GetText(i, Buffer);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddHairColor(pRecord->GetFormID());
	}

	for (int i = 0; i < m_FeatureSets.GetCount(); ++i)
	{
		m_FeatureSets.GetText(i, Buffer);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddFeatureSet(pRecord->GetFormID());
	}

	for (int i = 0; i < m_HeadParts.GetCount(); ++i)
	{
		m_HeadParts.GetText(i, Buffer);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord == NULL) continue;
		m_HeadInfo.AddHeadData(i, pRecord->GetFormID());
	}

	GetMpaControlData();

		/* Update the MPA indexes */
	for (dword i = 0; i < m_HeadInfo.MPAData.GetSize(); ++i)
	{
		m_HeadInfo.MPAData[i]->Index.SetValue(i);
	}
}


void CSrRacePageHead1::SetControlData (void)
{
	m_HeadFeature.SetWindowTextA(m_HeadInfo.pHeadFeature ? m_pParent->m_pRecordHandler->GetEditorID(m_HeadInfo.pHeadFeature->GetValue()) : "");

	m_RacePresets.ResetContent();
	m_HairColors.ResetContent();
	m_FeatureSets.ResetContent();
	m_HeadParts.ResetContent();

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

	for (dword i = 0; i < m_HeadInfo.HeadData.GetSize(); ++i)
	{
		srraceheaddata_t* pHeadData = m_HeadInfo.HeadData[i];
		const char* pString = m_pParent->m_pRecordHandler->GetEditorID(pHeadData->Data.GetValue());
		if (pString) m_HeadParts.AddString(pString);
	}

	m_MpaList.DeleteAllItems();

	for (dword i = 0; i < m_HeadInfo.MPAData.GetSize(); ++i)
	{
		AddMpaList(m_HeadInfo.MPAData[i]);
	}
}


BOOL CSrRacePageHead1::OnInitDialog()
{
	m_IsInitialized = false;
	CPropertyPage::OnInitDialog();

	m_MpaList.SetListName("RaceMpaList");
	m_MpaList.SetDragEnable(true);
	m_MpaList.DefaultSettings();
	m_MpaList.SetupCustomList(s_RaceMpaListInit, NULL, s_RaceMpaListFields);
	m_MpaList.SetOwner(this);
	m_MpaList.SetColorEnable(false);
	m_MpaList.SetDragType(SR_RLDRAG_CUSTOM);
	m_MpaList.SetSortEnable(false);
	//m_MpaList.SetActivateType(SR_RLACTIVATE_NONE);

	EnableMpaControls();

	m_IsInitialized = true;

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

	if (ListIndex < m_RacePresets.GetCount()) m_RacePresets.SetCurSel(ListIndex);
	else m_RacePresets.SetCurSel(ListIndex - 1);
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

	if (ListIndex < m_HairColors.GetCount()) m_HairColors.SetCurSel(ListIndex);
	else m_HairColors.SetCurSel(ListIndex - 1);
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

	if (ListIndex < m_FeatureSets.GetCount()) m_FeatureSets.SetCurSel(ListIndex);
	else m_FeatureSets.SetCurSel(ListIndex - 1);
}


void CSrRacePageHead1::OnBnClickedAddHeadpart()
{
	CString Buffer;
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_HDPT, &CSrHdptRecord::s_FieldMap)) return;
	m_HeadParts.AddString(Buffer);
}


void CSrRacePageHead1::OnBnClickedEditHeadpart()
{
	CString Buffer;
	int     ListIndex = m_HeadParts.GetCurSel();

	if (ListIndex < 0) return;
	m_HeadParts.GetText(ListIndex, Buffer);

	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_HDPT, &CSrHdptRecord::s_FieldMap)) return;

	m_HeadParts.DeleteString(ListIndex);
	m_HeadParts.InsertString(ListIndex, Buffer);
}


void CSrRacePageHead1::OnBnClickedDelHeadpart()
{
	int ListIndex = m_HeadParts.GetCurSel();
	if (ListIndex < 0) return;

	m_HeadParts.DeleteString(ListIndex);

	if (ListIndex < m_HeadParts.GetCount()) m_HeadParts.SetCurSel(ListIndex);
	else m_HeadParts.SetCurSel(ListIndex - 1);
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
	if (GetAsyncKeyState(VK_CONTROL))
		m_pDlgHandler->EditRecordHelper(m_RacePresets, SR_NAME_NPC_);
	else
		OnBnClickedEditRacepreset();
}


void CSrRacePageHead1::OnLbnDblclkHaircolors()
{
	if (GetAsyncKeyState(VK_CONTROL))
		m_pDlgHandler->EditRecordHelper(m_HairColors, SR_NAME_CLFM);
	else
		OnBnClickedEditHaircolor();
}


void CSrRacePageHead1::OnLbnDblclkFeaturesets()
{
	if (GetAsyncKeyState(VK_CONTROL))
		m_pDlgHandler->EditRecordHelper(m_FeatureSets, SR_NAME_TXST);
	else
		OnBnClickedEditFeatureset();
}


void CSrRacePageHead1::OnLbnDblclkHeadparts()
{
	if (GetAsyncKeyState(VK_CONTROL))
		m_pDlgHandler->EditRecordHelper(m_HeadParts, SR_NAME_HDPT);
	else
		OnBnClickedEditHeadpart();
}


void CSrRacePageHead1::SetCurrentMpa (srraceheadmpadata_t* pMpa)
{
	GetMpaControlData();

	m_pCurrentMpa = pMpa;
	EnableMpaControls();

	SetMpaControlData();
}


int CSrRacePageHead1::AddMpaList (srraceheadmpadata_t* pMpa)
{
	srrlcustomdata_t CustomData;

	CustomData.pRecord = m_pParent->GetInputRecord();
	CustomData.Subrecords.Add(&pMpa->Index);
	CustomData.Subrecords.Add(&pMpa->Data);

	int ListIndex = m_MpaList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return -1;

	UpdateMpaList(ListIndex, true);
	return ListIndex;
}


void CSrRacePageHead1::UpdateMpaList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t* pCustomData = m_MpaList.GetCustomData(ListIndex);
	CString           Buffer;

	if (Update) m_MpaList.UpdateRecord(ListIndex);
	if (pCustomData == NULL) return;

	CSrDwordSubrecord* pIndex = SrCastClassNull(CSrDwordSubrecord, pCustomData->Subrecords[0]);
	CSrMpavSubrecord* pData = SrCastClassNull(CSrMpavSubrecord, pCustomData->Subrecords[1]);
	if (pIndex == NULL || pData == NULL) return;

	Buffer.Format("%d", pIndex->GetValue());
	m_MpaList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN1, Buffer);

	for (dword i = 0; i < 8; ++i)
	{
		Buffer.Format("%08X", pData->GetMpavData().Unknown[i]);
		m_MpaList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN2 + i, Buffer);
	}

}


void CSrRacePageHead1::EnableMpaControls (void)
{
	bool Enable = m_pCurrentMpa != NULL;

	m_DeleteMpa.EnableWindow(Enable);

	for (dword i = 0; i < 8; ++i) m_MpaData[i].EnableWindow(Enable);
}


void CSrRacePageHead1::GetMpaControlData (void)
{
	CString Buffer;

	if (m_pCurrentMpa == NULL) return;

	for (dword i = 0; i < 8; ++i)
	{
		m_MpaData[i].GetWindowTextA(Buffer);
		m_pCurrentMpa->Data.GetMpavData().Unknown[i] = strtoul(Buffer, NULL, 0);	
	}

	for (int i = 0; i < m_MpaList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_MpaList.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != &m_pCurrentMpa->Index) continue;

		UpdateMpaList(i, true);
		break;
	}

}


void CSrRacePageHead1::SetMpaControlData (void)
{
	CString Buffer;

	if (m_pCurrentMpa == NULL) 
	{
		for (dword i = 0; i < 8; ++i) m_MpaData[i].SetWindowTextA("");
		return;
	}

	for (dword i = 0; i < 8; ++i)
	{
		Buffer.Format("0x%08X", m_pCurrentMpa->Data.GetMpavData().Unknown[i]);
		m_MpaData[i].SetWindowTextA(Buffer);
	}

}


void CSrRacePageHead1::OnBnClickedAddMpa()
{
	GetMpaControlData();
	srraceheadmpadata_t* pMpa = m_HeadInfo.CreateMpa();
	
	pMpa->Index.SetValue(m_MpaList.GetItemCount());

	int ListIndex = AddMpaList(pMpa);
	m_MpaList.SelectRecord(ListIndex);
	SetCurrentMpa(pMpa);
}


void CSrRacePageHead1::OnBnClickedDeleteMpa()
{
	std::vector<int> IndexList;
	POSITION		 Pos;
	int				 ListIndex;

	GetMpaControlData();

	Pos = m_MpaList.GetFirstSelectedItemPosition();

	while (Pos)
	{
		ListIndex = m_MpaList.GetNextSelectedItem(Pos);
		IndexList.push_back(ListIndex);
	}

	if (IndexList.size() <= 0) return;

	while (IndexList.size())
	{
		ListIndex = IndexList.back();

		m_MpaList.DeleteItem(ListIndex);
		m_HeadInfo.MPAData.Delete(ListIndex);

		IndexList.pop_back();
	}

	m_pCurrentMpa = NULL;

	if (ListIndex < (int) m_HeadInfo.MPAData.GetSize())
	{
		SetCurrentMpa(m_HeadInfo.MPAData[ListIndex]);
		m_MpaList.SelectRecord(ListIndex);
	}
	else
	{
		SetCurrentMpa(m_HeadInfo.MPAData[ListIndex - 1]);
		m_MpaList.SelectRecord(ListIndex - 1);
	}
}


void CSrRacePageHead1::OnLvnItemchangedMpalist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetMpaControlData();
	SetCurrentMpa(m_HeadInfo.MPAData[pNMLV->iItem]);
}


void CSrRacePageHead1::OnDropMpaList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	srrlcustomdata_t*  pCustomData;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pCustomDatas == NULL) return;
	
	for (dword i = 0; i < pDropItems->pCustomDatas->GetSize(); ++i)
	{
		pCustomData = pDropItems->pCustomDatas->GetAt(i);
		if (pCustomData == NULL) continue;

		CSrDwordSubrecord* pIndex = SrCastClassNull(CSrDwordSubrecord, pCustomData->Subrecords[0]);
		CSrMpavSubrecord*   pData = SrCastClassNull(CSrMpavSubrecord,  pCustomData->Subrecords[1]);
		if (pIndex == NULL || pData == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			srraceheadmpadata_t* pMpa = m_HeadInfo.MPAData.AddNew();
			pMpa->Index.CopyFull(pIndex);
			pMpa->Data.CopyFull(pData);
			pMpa->Index.SetValue(m_MpaList.GetItemCount());
			AddMpaList(pMpa);
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;
}