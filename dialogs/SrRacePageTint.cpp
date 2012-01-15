#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageTint.h"
#include "afxdialogex.h"
#include <vector>


IMPLEMENT_DYNAMIC(CSrRacePageTint, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageTint, CPropertyPage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_TINTLIST, &CSrRacePageTint::OnLvnItemchangedTintlist)
	ON_BN_CLICKED(IDC_ADD_TINT, &CSrRacePageTint::OnBnClickedAddTint)
	ON_BN_CLICKED(IDC_DELETE_TINT, &CSrRacePageTint::OnBnClickedDeleteTint)
	ON_BN_CLICKED(IDC_SELECT_TINTMASK, &CSrRacePageTint::OnBnClickedSelectTintmask)
	ON_BN_CLICKED(IDC_EDIT_TINDCOLOR, &CSrRacePageTint::OnBnClickedEditTindcolor)
	ON_BN_CLICKED(IDC_SELECT_TINDCOLOR, &CSrRacePageTint::OnBnClickedSelectTindcolor)
	ON_BN_CLICKED(IDC_ADD_TINTDATA, &CSrRacePageTint::OnBnClickedAddTintdata)
	ON_BN_CLICKED(IDC_DELETE_TINTDATA, &CSrRacePageTint::OnBnClickedDeleteTintdata)
	ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_TINTMASK, OnDropMaskFile)
	ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_TINTMASK, OnDropMaskFile)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_TINDCOLOR, OnDropTindColor)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_TINDCOLOR, OnDropTindColor)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_TINTLIST, OnDropTintList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_TINTLIST, OnDropTintList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_TINTDATALIST, OnDropTintDataList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_TINTDATALIST, OnDropTintDataList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DATATINC, OnDropDataColor)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DATATINC, OnDropDataColor)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_TINTDATALIST, &CSrRacePageTint::OnLvnItemchangedTintdatalist)
	ON_BN_CLICKED(IDC_EDIT_DATATINC, &CSrRacePageTint::OnBnClickedEditDatatinc)
	ON_BN_CLICKED(IDC_SELECT_DATATINC, &CSrRacePageTint::OnBnClickedSelectDatatinc)
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_RaceTintListInit[] = 
{
	{ SR_FIELD_LISTUNKNOWN1,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN2,		220,	LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN3,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN4,		150,	LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN5,		70,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
};

static srrecfield_t s_RaceTintListFields[] = 
{
	{ "Index",			SR_FIELD_LISTUNKNOWN1,			0, NULL },
	{ "MaskFile",		SR_FIELD_LISTUNKNOWN2,			0, NULL },
	{ "Tinp",			SR_FIELD_LISTUNKNOWN3,			0, NULL },
	{ "Tind Color",		SR_FIELD_LISTUNKNOWN4,			0, NULL },
	{ "DataCount",		SR_FIELD_LISTUNKNOWN5,			0, NULL },
	{ NULL,				SR_FIELD_NONE,					0, NULL }
};


static srreclistcolinit_t s_RaceTintDataListInit[] = 
{
	{ SR_FIELD_LISTUNKNOWN1,		150,	LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN2,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN3,		40,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
};

static srrecfield_t s_RaceTintDataListFields[] = 
{
	{ "Color",		SR_FIELD_LISTUNKNOWN1,			0, NULL },
	{ "Value",		SR_FIELD_LISTUNKNOWN2,			0, NULL },
	{ "Short",		SR_FIELD_LISTUNKNOWN3,			0, NULL },
	{ NULL,			SR_FIELD_NONE,					0, NULL }
};
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


CSrRacePageTint::CSrRacePageTint(srraceinfo_t& RaceInfo, const bool IsMale)
	: CPropertyPage(CSrRacePageTint::IDD), m_RaceInfo(RaceInfo), m_IsMale(IsMale), m_HeadInfo(IsMale ? RaceInfo.MaleHead : RaceInfo.FemaleHead)
{
	m_IsInitialized = false;
	m_pParent = NULL;
	m_pDlgHandler = NULL;
	m_pCurrentTint = NULL;
	m_pCurrentTintData = NULL;
}


CSrRacePageTint::~CSrRacePageTint()
{
}


void CSrRacePageTint::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TINTINDEX, m_Index);
	DDX_Control(pDX, IDC_TINTMASK, m_MaskFile);
	DDX_Control(pDX, IDC_TINDCOLOR, m_TindColor);
	DDX_Control(pDX, IDC_SELECT_TINTMASK, m_SelectMaskFile);
	DDX_Control(pDX, IDC_EDIT_TINDCOLOR, m_EditTind);
	DDX_Control(pDX, IDC_SELECT_TINDCOLOR, m_SelectTind);
	DDX_Control(pDX, IDC_TINTTINP, m_Tinp);
	DDX_Control(pDX, IDC_TINTDATALIST, m_TintDataList);
	DDX_Control(pDX, IDC_TINTLIST, m_TintList);
	DDX_Control(pDX, IDC_ADD_TINTDATA, m_AddTintData);
	DDX_Control(pDX, IDC_DELETE_TINTDATA, m_DeleteTintData);
	DDX_Control(pDX, IDC_DELETE_TINT, m_DeleteTint);
	DDX_Control(pDX, IDC_DATATINC, m_DataTinc);
	DDX_Control(pDX, IDC_DATATINV, m_DataTinv);
	DDX_Control(pDX, IDC_DATATIRS, m_DataTirs);
	DDX_Control(pDX, IDC_EDIT_DATATINC, m_EditDataTinc);
	DDX_Control(pDX, IDC_SELECT_DATATINC, m_SelectDataTinc);
}


void CSrRacePageTint::GetControlData (void)
{
	GetTintControlData();
}


void CSrRacePageTint::SetControlData (void)
{
	m_TintList.DeleteAllItems();

	for (dword i = 0; i < m_HeadInfo.Tints.GetSize(); ++i)
	{
		AddTintList(m_HeadInfo.Tints[i]);
	}

	m_TintList.SelectRecord(0);
	SetCurrentTint(m_HeadInfo.Tints[0]);
}


void CSrRacePageTint::CreateTintCustomData (srrlcustomdata_t& CustomData, srraceheadtintinfo_t* pTint)
{
	CustomData.Destroy();

	CustomData.pRecord = m_pParent->GetInputRecord();
	CustomData.Subrecords.Add(&pTint->Index);
	if (pTint->pMaskFile) CustomData.Subrecords.Add(pTint->pMaskFile);
	if (pTint->pTinp) CustomData.Subrecords.Add(pTint->pTinp);
	if (pTint->pColor) CustomData.Subrecords.Add(pTint->pColor);

	for (dword i = 0; i < pTint->Tints.GetSize(); ++i)
	{
		CustomData.Subrecords.Add(&pTint->Tints[i]->Tinc);
		CustomData.Subrecords.Add(&pTint->Tints[i]->Tinv);
		CustomData.Subrecords.Add(&pTint->Tints[i]->Tirs);
	}

}


int CSrRacePageTint::AddTintList (srraceheadtintinfo_t* pTint)
{
	srrlcustomdata_t CustomData;
	int			     ListIndex;

	CreateTintCustomData(CustomData, pTint);

	ListIndex = m_TintList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return -1;

	UpdateTintList(ListIndex, true);
	return ListIndex;
}


void CSrRacePageTint::UpdateTintList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t*    pCustomData = m_TintList.GetCustomData(ListIndex);
	CString			     Buffer;
	CSrStringSubrecord*  pMaskfile = NULL;
	CSrWordSubrecord*    pTinp = NULL;
	CSrFormidSubrecord*  pColor = NULL;
	dword                DataCount = 0;

	if (Update) m_TintList.UpdateRecord(ListIndex);
	if (pCustomData == NULL) return;

	CSrWordSubrecord* pIndex = SrCastClassNull(CSrWordSubrecord, pCustomData->Subrecords[0]);
	if (pIndex == NULL) return;

		/* Gather data from all the subrecords */
	for (dword i = 1; i < pCustomData->Subrecords.GetSize(); ++i)
	{
		CSrSubrecord* pSubrecord = pCustomData->Subrecords[i];

		if (pSubrecord->GetRecordType() == SR_NAME_TINT)
		{
			pMaskfile = SrCastClass(CSrStringSubrecord, pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TINP)
		{
			pTinp = SrCastClass(CSrWordSubrecord, pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TIND)
		{
			pColor = SrCastClass(CSrFormidSubrecord, pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TINC)
		{
			++DataCount;
		}
	}

	Buffer.Format("%hd", pIndex->GetValue());
	m_TintList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN1, Buffer);

	m_TintList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN2, pMaskfile ? pMaskfile->GetString().c_str() : "");

	Buffer.Empty();
	if (pTinp != NULL) Buffer.Format("%hd", pTinp->GetValue());
	m_TintList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN3, Buffer);

	Buffer.Empty();
	if (pColor != NULL) Buffer = m_pParent->m_pRecordHandler->GetEditorID(pColor->GetValue());
	m_TintList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN4, Buffer);

	Buffer.Format("%d", DataCount);
	m_TintList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN5, Buffer);
}


void CSrRacePageTint::SetCurrentTint (srraceheadtintinfo_t* pTint)
{
	GetTintControlData();
	
	m_pCurrentTintData = NULL;
	m_pCurrentTint = pTint;
	EnableTintControls();

	SetTintControlData();
}


void CSrRacePageTint::EnableTintControls (void)
{
	bool Enable = m_pCurrentTint != NULL;

	m_DeleteTint.EnableWindow(Enable);
	m_Index.EnableWindow(Enable);
	m_MaskFile.EnableWindow(Enable);
	m_SelectMaskFile.EnableWindow(Enable);
	m_Tinp.EnableWindow(Enable);
	m_TindColor.EnableWindow(Enable);
	m_EditTind.EnableWindow(Enable);
	m_SelectTind.EnableWindow(Enable);
	m_TintDataList.EnableWindow(Enable);
	m_AddTintData.EnableWindow(Enable);
	m_DeleteTintData.EnableWindow(Enable);
}


void CSrRacePageTint::GetTintControlData (void)
{
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pCurrentTint == NULL)	return;
	GetTintDataControlData();

	m_Index.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	m_pCurrentTint->Index.SetValue((word) strtoul(Buffer, NULL, 0));

	m_MaskFile.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	m_pCurrentTint->SetMaskFile(Buffer);

	m_Tinp.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	m_pCurrentTint->SetTinp(Buffer);

	m_TindColor.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_pCurrentTint->SetColor(pRecord ? pRecord->GetFormID() : 0);
	
	for (int i = 0; i < m_TintList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_TintList.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != &m_pCurrentTint->Index) continue;

		CreateTintCustomData(*pCustomData, m_pCurrentTint);

		UpdateTintList(i, true);
		break;
	}

}


void CSrRacePageTint::SetTintControlData (void)
{
	CString Buffer;

	if (m_pCurrentTint == NULL)
	{
		m_TintDataList.DeleteAllItems();
		m_Index.SetWindowTextA("");
		m_Tinp.SetWindowTextA("");
		m_TindColor.SetWindowTextA("");
		m_MaskFile.SetWindowTextA("");
		return;
	}

	Buffer.Format("%hd", m_pCurrentTint->Index.GetValue());
	m_Index.SetWindowText(Buffer);

	m_MaskFile.SetWindowText(m_pCurrentTint->pMaskFile ? m_pCurrentTint->pMaskFile->GetString().c_str() : "");

	Buffer.Empty();
	if (m_pCurrentTint->pTinp) Buffer.Format("%hd", m_pCurrentTint->pTinp->GetValue());
	m_Tinp.SetWindowText(Buffer);

	Buffer.Empty();
	if (m_pCurrentTint->pColor) Buffer = m_pParent->m_pRecordHandler->GetEditorID(m_pCurrentTint->pColor->GetValue());
	m_TindColor.SetWindowText(Buffer);

	m_TintDataList.DeleteAllItems();

	for (dword i = 0; i < m_pCurrentTint->Tints.GetSize(); ++i)
	{
		AddTintDataList(m_pCurrentTint->Tints[i]);
	}

	m_TintDataList.SelectRecord(0);
	SetCurrentTintData(m_pCurrentTint->Tints[0]);	
}


int CSrRacePageTint::AddTintDataList(srraceheadtintdata_t *pTintData)
{
	srrlcustomdata_t CustomData;
	int			     ListIndex;

	CreateTintDataCustomData(CustomData, pTintData);

	ListIndex = m_TintDataList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return -1;

	UpdateTintDataList(ListIndex, true);
	return ListIndex;
}


void CSrRacePageTint::EnableTintDataControls (void)
{
	bool Enable = m_pCurrentTintData != NULL;

	m_DeleteTintData.EnableWindow(Enable);
	m_DataTinc.EnableWindow(Enable);
	m_DataTinv.EnableWindow(Enable);
	m_DataTirs.EnableWindow(Enable);
	m_EditDataTinc.EnableWindow(Enable);
	m_SelectDataTinc.EnableWindow(Enable);
}


void CSrRacePageTint::SetCurrentTintData (srraceheadtintdata_t* pTintData)
{

	if (m_pCurrentTint == NULL)
	{
		m_pCurrentTintData = NULL;
		return;
	}

	GetTintDataControlData();

	m_pCurrentTintData = pTintData;
	EnableTintDataControls();

	SetTintDataControlData();
}


void CSrRacePageTint::GetTintDataControlData (void)
{
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pCurrentTint == NULL) return;
	if (m_pCurrentTintData == NULL) return;

	m_DataTinc.GetWindowTextA(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_pCurrentTintData->Tinc.SetValue(pRecord ? pRecord->GetFormID() : 0);

	m_DataTinv.GetWindowTextA(Buffer);
	m_pCurrentTintData->Tinv.SetValue((float) atof(Buffer));

	m_DataTirs.GetWindowTextA(Buffer);
	m_pCurrentTintData->Tirs.SetValue((word) strtoul(Buffer, NULL, 0));

	for (int i = 0; i < m_TintDataList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_TintDataList.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != &m_pCurrentTintData->Tinc) continue;

		UpdateTintDataList(i, true);
		break;
	}

}


void CSrRacePageTint::SetTintDataControlData (void)
{
	CString Buffer;

	if (m_pCurrentTintData == NULL)
	{
		m_DataTinc.SetWindowTextA("");
		m_DataTinv.SetWindowTextA("");
		m_DataTirs.SetWindowTextA("");
		return;
	}

	m_DataTinc.SetWindowTextA(m_pParent->m_pRecordHandler->GetEditorID(m_pCurrentTintData->Tinc.GetValue()));

	Buffer.Format("%g", m_pCurrentTintData->Tinv.GetValue());
	m_DataTinv.SetWindowTextA(Buffer);

	Buffer.Format("%hd", m_pCurrentTintData->Tirs.GetValue());
	m_DataTirs.SetWindowTextA(Buffer);
}


void CSrRacePageTint::UpdateTintDataList (const int ListIndex, const bool Update)
{
	srrlcustomdata_t* pCustomData = m_TintDataList.GetCustomData(ListIndex);
	CString           Buffer;

	if (Update) m_TintDataList.UpdateRecord(ListIndex);
	if (pCustomData == NULL) return;

	CSrFormidSubrecord* pTinc = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
	CSrFloatSubrecord*  pTinv = SrCastClassNull(CSrFloatSubrecord, pCustomData->Subrecords[1]);
	CSrWordSubrecord*   pTirs = SrCastClassNull(CSrWordSubrecord, pCustomData->Subrecords[2]);
	if (pTinc == NULL || pTinv == NULL || pTirs == NULL) return;

	m_TintDataList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN1, m_pParent->m_pRecordHandler->GetEditorID(pTinc->GetValue()));

	Buffer.Format("%g", pTinv->GetValue());
	m_TintDataList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN2, Buffer);

	Buffer.Format("%hd", pTirs->GetValue());
	m_TintDataList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN3, Buffer);
}


void CSrRacePageTint::CreateTintDataCustomData (srrlcustomdata_t& CustomData, srraceheadtintdata_t* pTintData)
{
	CustomData.Destroy();

	CustomData.pRecord = m_pParent->GetInputRecord();
	CustomData.Subrecords.Add(&pTintData->Tinc);
	CustomData.Subrecords.Add(&pTintData->Tinv);
	CustomData.Subrecords.Add(&pTintData->Tirs);
}


BOOL CSrRacePageTint::OnInitDialog()
{
	m_IsInitialized = false;
	CPropertyPage::OnInitDialog();

	m_TintList.SetListName("RaceTintList");
	m_TintList.SetDragEnable(true);
	m_TintList.DefaultSettings();
	m_TintList.SetupCustomList(s_RaceTintListInit, NULL, s_RaceTintListFields);
	m_TintList.SetOwner(this);
	m_TintList.SetColorEnable(false);
	m_TintList.SetDragType(SR_RLDRAG_CUSTOM);
	m_TintList.SetSortEnable(false);
	//m_TintList.SetActivateType(SR_RLACTIVATE_NONE);

	m_TintDataList.SetListName("RaceTintDataList");
	m_TintDataList.SetDragEnable(true);
	m_TintDataList.DefaultSettings();
	m_TintDataList.SetupCustomList(s_RaceTintDataListInit, NULL, s_RaceTintDataListFields);
	m_TintDataList.SetOwner(this);
	m_TintDataList.SetColorEnable(false);
	m_TintDataList.SetDragType(SR_RLDRAG_CUSTOM);
	m_TintDataList.SetSortEnable(false);
	//m_TintDataList.SetActivateType(SR_RLACTIVATE_NONE);

	m_IsInitialized = true;

	EnableTintControls();

	return TRUE;
}


void CSrRacePageTint::OnLvnItemchangedTintlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	SetCurrentTint(m_HeadInfo.Tints[pNMLV->iItem]);
}


void CSrRacePageTint::OnBnClickedAddTint()
{
	GetTintControlData();

	srraceheadtintinfo_t* pNewTint = m_HeadInfo.Tints.AddNew();
	pNewTint->InitializeNew();

	int ListIndex = AddTintList(pNewTint);
	m_TintList.SelectRecord(ListIndex);
	SetCurrentTint(pNewTint);
}


void CSrRacePageTint::OnBnClickedDeleteTint()
{
	std::vector<int> IndexList;
	POSITION		 Pos;
	int				 ListIndex;

	GetTintControlData();

	Pos = m_TintList.GetFirstSelectedItemPosition();

	while (Pos)
	{
		ListIndex = m_TintList.GetNextSelectedItem(Pos);
		IndexList.push_back(ListIndex);
	}

	if (IndexList.size() <= 0) return;

	while (IndexList.size())
	{
		ListIndex = IndexList.back();

		m_TintList.DeleteItem(ListIndex);
		m_HeadInfo.Tints.Delete(ListIndex);

		IndexList.pop_back();
	}

	m_pCurrentTint = NULL;
	m_pCurrentTintData = NULL;

	if (ListIndex < (int) m_HeadInfo.Tints.GetSize())
	{
		SetCurrentTint(m_HeadInfo.Tints[ListIndex]);
		m_TintList.SelectRecord(ListIndex);
	}
	else
	{
		SetCurrentTint(m_HeadInfo.Tints[ListIndex - 1]);
		m_TintList.SelectRecord(ListIndex - 1);
	}
}


void CSrRacePageTint::OnBnClickedSelectTintmask()
{
	if (m_pCurrentTint == NULL) return;
	m_pDlgHandler->SelectResourceHelper(&m_MaskFile, "textures\\");
}


void CSrRacePageTint::OnBnClickedEditTindcolor()
{
	m_pDlgHandler->EditRecordHelper(m_TindColor, SR_NAME_CLFM);
}


void CSrRacePageTint::OnBnClickedSelectTindcolor()
{
	m_pDlgHandler->SelectRecordHelper(&m_TindColor, SR_NAME_CLFM, &CSrClfmRecord::s_FieldMap);
}


void CSrRacePageTint::OnBnClickedAddTintdata()
{
	if (m_pCurrentTint == NULL) return;
	GetTintDataControlData();

	srraceheadtintdata_t* pNewTintData = m_pCurrentTint->Tints.AddNew();
	pNewTintData->InitializeNew();

	int ListIndex = AddTintDataList(pNewTintData);
	m_TintDataList.SelectRecord(ListIndex);
	SetCurrentTintData(pNewTintData);

	UpdateTintCustomData();
}


void CSrRacePageTint::UpdateTintCustomData (void)
{
	if (m_pCurrentTint == NULL) return;

	for (int i = 0; i < m_TintList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_TintList.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != &m_pCurrentTint->Index) continue;

		CreateTintCustomData(*pCustomData, m_pCurrentTint);
		break;
	}
}


void CSrRacePageTint::OnBnClickedDeleteTintdata()
{
	std::vector<int> IndexList;
	POSITION		 Pos;
	int				 ListIndex;

	if (m_pCurrentTint == NULL) return;
	GetTintDataControlData();

	Pos = m_TintDataList.GetFirstSelectedItemPosition();

	while (Pos)
	{
		ListIndex = m_TintDataList.GetNextSelectedItem(Pos);
		IndexList.push_back(ListIndex);
	}

	if (IndexList.size() <= 0) return;

	while (IndexList.size())
	{
		ListIndex = IndexList.back();

		m_TintDataList.DeleteItem(ListIndex);
		m_pCurrentTint->Tints.Delete(ListIndex);

		IndexList.pop_back();
	}

	m_pCurrentTintData = NULL;

	if (ListIndex < (int) m_pCurrentTint->Tints.GetSize())
	{
		SetCurrentTintData(m_pCurrentTint->Tints[ListIndex]);
		m_TintDataList.SelectRecord(ListIndex);
	}
	else
	{
		SetCurrentTintData(m_pCurrentTint->Tints[ListIndex - 1]);
		m_TintDataList.SelectRecord(ListIndex - 1);
	}

	UpdateTintCustomData();
}


void CSrRacePageTint::OnDropMaskFile (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;
	*pResult = SRRESOURCE_DROPCHECK_ERROR;

	if (m_pCurrentTint == NULL) return;
	if (pDropInfo->pResourceFile == NULL) return;

	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_IMAGE) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_TEXTURES)) return;

	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_MaskFile.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}

	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrRacePageTint::OnDropTindColor (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	*pResult = SRRESOURCE_DROPCHECK_ERROR;
	if (m_pCurrentTint == NULL) return;

	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_TindColor, SR_NAME_CLFM, 1);
}


void CSrRacePageTint::OnDropDataColor (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	*pResult = SRRESOURCE_DROPCHECK_ERROR;
	if (m_pCurrentTintData == NULL) return;

	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DataTinc, SR_NAME_CLFM, 1);
}


void CSrRacePageTint::DropListCreateTint (CSrRefSubrecordArray& Subrecords) 
{
	srraceheadtintinfo_t* pTint = m_HeadInfo.Tints.AddNew();
	srraceheadtintdata_t* pCurrentData = NULL;

	pTint->InitializeNew();
	
	for (dword i = 0; i < Subrecords.GetSize(); ++i)
	{
		CSrSubrecord* pSubrecord = Subrecords[i];

		if (pSubrecord->GetRecordType() == SR_NAME_TINI)
		{
			pTint->Index.CopyFull(pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TINT)
		{
			pTint->pMaskFile = new CSrStringSubrecord;
			pTint->pMaskFile->CopyFull(pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TIND)
		{
			pTint->pColor = new CSrFormidSubrecord;
			pTint->pColor->CopyFull(pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TINP)
		{
			pTint->pTinp = new CSrWordSubrecord;
			pTint->pTinp->CopyFull(pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TINC)
		{
			pCurrentData = pTint->Tints.AddNew();
			pCurrentData->InitializeNew();
			pCurrentData->Tinc.CopyFull(pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TINV && pCurrentData != NULL)
		{
			pCurrentData->Tinv.CopyFull(pSubrecord);
		}
		else if (pSubrecord->GetRecordType() == SR_NAME_TIRS && pCurrentData != NULL)
		{
			pCurrentData->Tirs.CopyFull(pSubrecord);
			pCurrentData = NULL;
		}
		else
		{
			SystemLog.Printf("Warning: Unknown subrecord type %4.4s dropped onto TintList!", pSubrecord->GetRecordType().Name);
		}

	}

	AddTintList(pTint);
}


void CSrRacePageTint::OnDropTintList (NMHDR* pNotifyStruct, LRESULT* pResult) 
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

		CSrWordSubrecord* pIndex = SrCastClassNull(CSrWordSubrecord, pCustomData->Subrecords[0]);
		if (pIndex == NULL) return;
		if (pIndex->GetRecordType() != SR_NAME_TINI) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			DropListCreateTint(pCustomData->Subrecords);
		}
	}
	
	if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
	{
		UpdateTintCustomData();
	}

	*pResult = SRRL_DROPCHECK_OK;
}


void CSrRacePageTint::OnDropTintDataList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	srrlcustomdata_t*  pCustomData;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pCustomDatas == NULL) return;
	if (m_pCurrentTint == NULL) return;
	
	for (dword i = 0; i < pDropItems->pCustomDatas->GetSize(); ++i)
	{
		pCustomData = pDropItems->pCustomDatas->GetAt(i);
		if (pCustomData == NULL) continue;

		CSrFormidSubrecord* pTinc = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
		CSrFloatSubrecord*  pTinv = SrCastClassNull(CSrFloatSubrecord, pCustomData->Subrecords[1]);
		CSrWordSubrecord*   pTirs = SrCastClassNull(CSrWordSubrecord, pCustomData->Subrecords[2]);
		if (pTinc == NULL || pTinv == NULL || pTirs == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			srraceheadtintdata_t* pTintData = m_pCurrentTint->Tints.AddNew();
			pTintData->Tinc.CopyFull(pTinc);
			pTintData->Tinv.CopyFull(pTinv);
			pTintData->Tirs.CopyFull(pTirs);
			AddTintDataList(pTintData);
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;
}


void CSrRacePageTint::OnLvnItemchangedTintdatalist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;
	if (m_pCurrentTint == NULL) return;

	SetCurrentTintData(m_pCurrentTint->Tints[pNMLV->iItem]);
}


void CSrRacePageTint::OnBnClickedEditDatatinc()
{
	if (m_pCurrentTintData == NULL) return;
	m_pDlgHandler->EditRecordHelper(m_DataTinc, SR_NAME_CLFM);
}


void CSrRacePageTint::OnBnClickedSelectDatatinc()
{
	if (m_pCurrentTintData == NULL) return;
	m_pDlgHandler->SelectRecordHelper(&m_DataTinc, SR_NAME_CLFM, &CSrClfmRecord::s_FieldMap);
}
