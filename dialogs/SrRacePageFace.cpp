
#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageFace.h"
#include "afxdialogex.h"
#include "SrInputDialog.h"
#include <vector>


IMPLEMENT_DYNAMIC(CSrRacePageFace, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageFace, CPropertyPage)
	ON_BN_CLICKED(IDC_ADD_FACEKEY, &CSrRacePageFace::OnBnClickedAddFacekey)
	ON_BN_CLICKED(IDC_EDIT_FACEKEY, &CSrRacePageFace::OnBnClickedEditFacekey)
	ON_BN_CLICKED(IDC_DEL_FACEKEY, &CSrRacePageFace::OnBnClickedDelFacekey)
	ON_LBN_SELCHANGE(IDC_FACEKEYS, &CSrRacePageFace::OnLbnSelchangeFacekeys)
	ON_LBN_DBLCLK(IDC_FACEKEYS, &CSrRacePageFace::OnLbnDblclkFacekeys)
	ON_BN_CLICKED(IDC_ADD_FACEWEIGHT, &CSrRacePageFace::OnBnClickedAddFaceweight)
	ON_BN_CLICKED(IDC_DELETE_FACEWEIGHT, &CSrRacePageFace::OnBnClickedDeleteFaceweight)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FACEWEIGHTS, OnDropFaceWeights)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FACEWEIGHTS, OnDropFaceWeights)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FACEWEIGHTS, &CSrRacePageFace::OnLvnItemchangedFaceweights)
END_MESSAGE_MAP()




/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_RaceFaceWeightListInit[] = {
	{ SR_FIELD_LISTUNKNOWN1,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN2,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN3,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN4,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN5,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN6,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN7,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN8,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN9,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN10,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN11,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN12,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN13,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN14,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN15,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN16,		50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_RaceFaceWeightListFields[] = {
	{ "U1",				SR_FIELD_LISTUNKNOWN1,			0, NULL },
	{ "U2",				SR_FIELD_LISTUNKNOWN2,			0, NULL },
	{ "U3",				SR_FIELD_LISTUNKNOWN3,			0, NULL },
	{ "U4",				SR_FIELD_LISTUNKNOWN4,			0, NULL },
	{ "U5",				SR_FIELD_LISTUNKNOWN5,			0, NULL },
	{ "U6",				SR_FIELD_LISTUNKNOWN6,			0, NULL },
	{ "U7",				SR_FIELD_LISTUNKNOWN7,			0, NULL },
	{ "U8",				SR_FIELD_LISTUNKNOWN8,			0, NULL },
	{ "U9",				SR_FIELD_LISTUNKNOWN9,			0, NULL },
	{ "U10",			SR_FIELD_LISTUNKNOWN10,			0, NULL },
	{ "U11",			SR_FIELD_LISTUNKNOWN11,			0, NULL },
	{ "U12",			SR_FIELD_LISTUNKNOWN12,			0, NULL },	
	{ "U13",			SR_FIELD_LISTUNKNOWN13,			0, NULL },	
	{ "U14",			SR_FIELD_LISTUNKNOWN14,			0, NULL },	
	{ "U15",			SR_FIELD_LISTUNKNOWN15,			0, NULL },	
	{ "U16",			SR_FIELD_LISTUNKNOWN16,			0, NULL },	
	{ NULL,				SR_FIELD_NONE,					0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


CSrRacePageFace::CSrRacePageFace(srraceinfo_t& RaceInfo)
	: CPropertyPage(CSrRacePageFace::IDD), m_RaceInfo(RaceInfo)
{
	m_pParent     = NULL;
	m_pDlgHandler = NULL;
	m_IsInitialized = false;
	m_pCurrentWeight = NULL;
}


CSrRacePageFace::~CSrRacePageFace()
{
}


void CSrRacePageFace::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FACEKEYS, m_FaceKeys);
	DDX_Control(pDX, IDC_FACEWEIGHTS, m_FaceWeights);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Weight[0]);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Weight[1]);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Weight[2]);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Weight[3]);
	DDX_Control(pDX, IDC_UNKNOWN5, m_Weight[4]);
	DDX_Control(pDX, IDC_UNKNOWN6, m_Weight[5]);
	DDX_Control(pDX, IDC_UNKNOWN7, m_Weight[6]);
	DDX_Control(pDX, IDC_UNKNOWN8, m_Weight[7]);
	DDX_Control(pDX, IDC_UNKNOWN9, m_Weight[8]);
	DDX_Control(pDX, IDC_UNKNOWN10, m_Weight[9]);
	DDX_Control(pDX, IDC_UNKNOWN11, m_Weight[10]);
	DDX_Control(pDX, IDC_UNKNOWN12, m_Weight[11]);
	DDX_Control(pDX, IDC_UNKNOWN13, m_Weight[12]);
	DDX_Control(pDX, IDC_UNKNOWN14, m_Weight[13]);
	DDX_Control(pDX, IDC_UNKNOWN15, m_Weight[14]);
	DDX_Control(pDX, IDC_UNKNOWN16, m_Weight[15]);
	DDX_Control(pDX, IDC_ADD_FACEWEIGHT, m_AddFaceWeight);
}


BOOL CSrRacePageFace::OnInitDialog()
{
	m_IsInitialized = false;

	CPropertyPage::OnInitDialog();

	m_FaceWeights.SetListName("RaceFaceWeightList");
	m_FaceWeights.SetDragEnable(true);
	m_FaceWeights.DefaultSettings();
	m_FaceWeights.SetupCustomList(s_RaceFaceWeightListInit, NULL, s_RaceFaceWeightListFields);
	m_FaceWeights.SetOwner(this);
	m_FaceWeights.SetColorEnable(false);
	m_FaceWeights.SetDragType(SR_RLDRAG_CUSTOM);
	m_FaceWeights.SetSortEnable(false);
	//m_FaceWeights.SetActivateType(SR_RLACTIVATE_NONE);

	EnableWeightControls();
	m_IsInitialized = true;

	return TRUE;
}


void CSrRacePageFace::GetControlData (void)
{
	CString Buffer;

	GetWeightControlData();

	m_RaceInfo.FacialKeys.Destroy();

	for (int i = 0; i < m_FaceKeys.GetCount(); ++i)
	{
		m_FaceKeys.GetText(i, Buffer);
		CSrStringSubrecord* pString = m_RaceInfo.FacialKeys.AddNew();
		pString->Initialize(SR_NAME_PHTN, 0);
		pString->InitializeNew();
		pString->SetString(Buffer);
	}

}


void CSrRacePageFace::SetControlData (void)
{

	m_FaceKeys.ResetContent();

	for (dword i = 0; i < m_RaceInfo.FacialKeys.GetSize(); ++i)
	{
		m_FaceKeys.AddString(m_RaceInfo.FacialKeys[i]->GetString().c_str());
	}

	for (dword i = 0; i < m_RaceInfo.FacialWeights.GetSize(); ++i)
	{
		AddWeightList(m_RaceInfo.FacialWeights[i]);
	}
}


void CSrRacePageFace::GetWeightControlData (void)
{
	CString Buffer;

	if (m_pCurrentWeight == NULL) return;

	for (dword i = 0; i < 16; ++i) 
	{
		m_Weight[i].GetWindowTextA(Buffer);
		m_pCurrentWeight->GetPhwtData().Unknown[i] = (float) atof(Buffer);		
	}

	for (int i = 0; i < m_FaceWeights.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_FaceWeights.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != m_pCurrentWeight) continue;

		UpdateWeightList(i, true);
		break;
	}
}


void CSrRacePageFace::SetWeightControlData (void)
{
	CString Buffer;

	if (m_pCurrentWeight == NULL)
	{
		for (dword i = 0; i < 16; ++i) m_Weight[i].SetWindowTextA("");
		return;
	}

	for (dword i = 0; i < 16; ++i) 
	{
		Buffer.Format("%g", m_pCurrentWeight->GetPhwtData().Unknown[i]);
		m_Weight[i].SetWindowTextA(Buffer);
	}
}


int CSrRacePageFace::AddWeightList (CSrPhwtSubrecord* pWeight)
{
	srrlcustomdata_t  CustomData;
	CString           Buffer;
	int		          ListIndex;

	CustomData.pRecord = m_pParent->GetInputRecord();
	CustomData.Subrecords.Add(pWeight);
  
	ListIndex = m_FaceWeights.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdateWeightList(ListIndex, false);
	return (ListIndex);
}


void CSrRacePageFace::UpdateWeightList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t*   pCustomData = m_FaceWeights.GetCustomData(ListIndex);
	CSrPhwtSubrecord*   pWeight; 
	CString				Buffer;

	if (Update) m_FaceWeights.UpdateRecord(ListIndex);
	if (pCustomData == NULL) return;

	pWeight = SrCastClassNull(CSrPhwtSubrecord, pCustomData->Subrecords[0]);
	if (pWeight == NULL) return;

	for (dword i = 0; i < 16; ++i)
	{
		Buffer.Format("%g", pWeight->GetPhwtData().Unknown[i]);
		m_FaceWeights.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN1 + i, Buffer);
	}
	
}


void CSrRacePageFace::SetCurrentWeight (CSrPhwtSubrecord* pWeight)
{
	GetWeightControlData();

	m_pCurrentWeight = pWeight;
	EnableWeightControls();

	SetWeightControlData();
}


void CSrRacePageFace::EnableWeightControls (void)
{
	bool Enable = m_pCurrentWeight != NULL;

	m_AddFaceWeight.EnableWindow(Enable);

	for (dword i = 0; i < 16; ++i)
	{
		m_Weight[i].EnableWindow(Enable);
	}
}


void CSrRacePageFace::OnBnClickedAddFacekey()
{
	CString Buffer;
	if (!::SrInputDialog(Buffer, "Face Key", "Enter Face Key String:")) return;
	m_FaceKeys.AddString(Buffer);
}


void CSrRacePageFace::OnBnClickedEditFacekey()
{
	CString Buffer;
	int     ListIndex = m_FaceKeys.GetCurSel();

	if (ListIndex < 0) return;
	m_FaceKeys.GetText(ListIndex, Buffer);

	if (!::SrInputDialog(Buffer, "Face Key", "Enter Face Key String:")) return;

	m_FaceKeys.DeleteString(ListIndex);
	m_FaceKeys.InsertString(ListIndex, Buffer);
}


void CSrRacePageFace::OnBnClickedDelFacekey()
{
	int ListIndex = m_FaceKeys.GetCurSel();
	if (ListIndex < 0) return;
	m_FaceKeys.DeleteString(ListIndex);

	if (ListIndex > 0)
		m_FaceKeys.SetCurSel(ListIndex - 1);
	else
		m_FaceKeys.SetCurSel(0);
}


void CSrRacePageFace::OnLbnSelchangeFacekeys()
{
}


void CSrRacePageFace::OnLbnDblclkFacekeys()
{
	OnBnClickedEditFacekey();
}


void CSrRacePageFace::OnBnClickedAddFaceweight()
{
	CSrPhwtSubrecord* pWeight = m_RaceInfo.FacialWeights.AddNew();
	pWeight->Initialize(SR_NAME_PHWT, SR_PHWT_SUBRECORD_SIZE);
	pWeight->InitializeNew();
	AddWeightList(pWeight);
}


void CSrRacePageFace::OnBnClickedDeleteFaceweight()
{
	std::vector<int> IndexList;
	POSITION		 Pos;
	int				 ListIndex;

	GetWeightControlData();

	Pos = m_FaceWeights.GetFirstSelectedItemPosition();

	while (Pos)
	{
		ListIndex = m_FaceWeights.GetNextSelectedItem(Pos);
		IndexList.push_back(ListIndex);
	}

	if (IndexList.size() <= 0) return;

	while (IndexList.size())
	{
		ListIndex = IndexList.back();

		m_FaceWeights.DeleteItem(ListIndex);
		m_RaceInfo.FacialWeights.Delete(ListIndex);

		IndexList.pop_back();
	}

	m_pCurrentWeight = NULL;

	if (ListIndex > 0)
	{
		SetCurrentWeight(m_RaceInfo.FacialWeights[ListIndex - 1]);
		m_FaceWeights.SelectRecord(ListIndex - 1);
	}
	else
	{
		SetCurrentWeight(m_RaceInfo.FacialWeights[0]);
		m_FaceWeights.SelectRecord(0);
	}
}


void CSrRacePageFace::OnDropFaceWeights (NMHDR* pNotifyStruct, LRESULT* pResult) 
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

		CSrPhwtSubrecord* pWeight = SrCastClassNull(CSrPhwtSubrecord, pCustomData->Subrecords[0]);
		if (pWeight == NULL) return;
				
			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			CSrPhwtSubrecord* pNewWeight = m_RaceInfo.FacialWeights.AddNew();			
			pNewWeight->CopyFull(pWeight);
			AddWeightList(pNewWeight);
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;	
}


void CSrRacePageFace::OnLvnItemchangedFaceweights(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetWeightControlData();
	SetCurrentWeight(m_RaceInfo.FacialWeights[pNMLV->iItem]);
	SetWeightControlData();
}
