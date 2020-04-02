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
#include "SrInputDialog.h"


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
	ON_BN_CLICKED(IDC_EDIT_SECTPERK, &CSrAvifView::OnBnClickedEditSectperk)
	ON_BN_CLICKED(IDC_SELECT_SECTPERK, &CSrAvifView::OnBnClickedSelectSectperk)
	ON_BN_CLICKED(IDC_EDIT_SECTSNAM, &CSrAvifView::OnBnClickedEditSectsnam)
	ON_BN_CLICKED(IDC_SELECT_SECTSNAM, &CSrAvifView::OnBnClickedSelectSectsnam)
	ON_BN_CLICKED(ID_ADD_SECTCNAM, &CSrAvifView::OnBnClickedAddSectcnam)
	ON_BN_CLICKED(ID_EDIT_SECTCNAM, &CSrAvifView::OnBnClickedEditSectcnam)
	ON_BN_CLICKED(ID_DELETE_SECTCNAM, &CSrAvifView::OnBnClickedDeleteSectcnam)
	ON_BN_CLICKED(ID_ADD_AVIFSECTION, &CSrAvifView::OnBnClickedAddAvifsection)
	ON_BN_CLICKED(ID_DELETE_AVIFSECTION, &CSrAvifView::OnBnClickedDeleteAvifsection)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_AVIFDATA_LIST, &CSrAvifView::OnLvnItemchangedAvifdataList)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SECTPERK, OnDropSectPName)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SECTPERK, OnDropSectPName)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SECTSNAM, OnDropSectSName)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SECTSNAM, OnDropSectSName)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_AVIFDATA_LIST, OnDropSectionList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_AVIFDATA_LIST, OnDropSectionList)
	ON_LBN_DBLCLK(IDC_SECTCNAM, &CSrAvifView::OnLbnDblclkSectcnam)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrAvifView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_SectionListInit[] = 
{
	{ SR_FIELD_PNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_INAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_FNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_XNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_YNAME,	50,		LVCFMT_CENTER },
	{ SR_FIELD_HNAME,	60,		LVCFMT_CENTER },
	{ SR_FIELD_VNAME,	60,		LVCFMT_CENTER },
	{ SR_FIELD_SNAME,	100,	LVCFMT_CENTER },
	{ SR_FIELD_CNAME,	50,		LVCFMT_CENTER },	
	{ SR_FIELD_NONE, 0, 0 }
};

static srrecfield_t s_SectionFields[] = 
{
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
	DDX_Control(pDX, IDC_SECTINAM, m_SectIName);
	DDX_Control(pDX, IDC_SECTFNAM, m_SectFName);
	DDX_Control(pDX, IDC_SECTPERK, m_SectPName);
	DDX_Control(pDX, IDC_EDIT_SECTPERK, m_SectEditPName);
	DDX_Control(pDX, IDC_SELECT_SECTPERK, m_SectSelectPName);
	DDX_Control(pDX, IDC_SECTSNAM, m_SectSName);
	DDX_Control(pDX, IDC_EDIT_SECTSNAM, m_SectEditSName);
	DDX_Control(pDX, IDC_SELECT_SECTSNAM, m_SectSelectSName);
	DDX_Control(pDX, IDC_SECTXNAM, m_SectXName);
	DDX_Control(pDX, IDC_SECTHNAM, m_SectHName);
	DDX_Control(pDX, IDC_SECTYNAM, m_SectYName);
	DDX_Control(pDX, IDC_SECTVNAM, m_SectVName);
	DDX_Control(pDX, IDC_SECTCNAM, m_SectCNames);
	DDX_Control(pDX, ID_ADD_SECTCNAM, m_SectAddCName);
	DDX_Control(pDX, ID_DELETE_SECTCNAM, m_SectDeleteCName);
	DDX_Control(pDX, ID_EDIT_SECTCNAM, m_SectEditCName);
	DDX_Control(pDX, ID_ADD_AVIFSECTION, m_SectAdd);
	DDX_Control(pDX, ID_DELETE_AVIFSECTION, m_SectDelete);
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
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pCurrentSection == NULL) return;

	m_SectPName.GetWindowTextA(Buffer);
	pRecord = m_pRecordHandler->FindEditorID(Buffer);
	m_pCurrentSection->PName.SetValue(pRecord ? pRecord->GetFormID() : 0);

	m_SectSName.GetWindowTextA(Buffer);
	pRecord = m_pRecordHandler->FindEditorID(Buffer);
	m_pCurrentSection->SName.SetValue(pRecord ? pRecord->GetFormID() : 0);

	m_SectIName.GetWindowTextA(Buffer);
	m_pCurrentSection->IName.SetValue(strtoul(Buffer, NULL, 0));

	m_SectFName.GetWindowTextA(Buffer);
	m_pCurrentSection->FName.SetValue(strtoul(Buffer, NULL, 0));

	m_SectXName.GetWindowTextA(Buffer);
	m_pCurrentSection->XName.SetValue(strtoul(Buffer, NULL, 0));

	m_SectYName.GetWindowTextA(Buffer);
	m_pCurrentSection->YName.SetValue(strtoul(Buffer, NULL, 0));

	m_SectHName.GetWindowTextA(Buffer);
	m_pCurrentSection->HName.SetValue((float) atof(Buffer));

	m_SectVName.GetWindowTextA(Buffer);
	m_pCurrentSection->VName.SetValue((float) atof(Buffer));

	m_pCurrentSection->CNames.Destroy();

	for (int i = 0; i < m_SectCNames.GetCount(); ++i)
	{
		m_SectCNames.GetText(i, Buffer);
		m_pCurrentSection->AddCName(strtoul(Buffer, NULL, 0));
	}

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

	Buffer.Format("%d", m_pCurrentSection->IName.GetValue());
	m_SectIName.SetWindowTextA(Buffer);

	Buffer.Format("%d", m_pCurrentSection->FName.GetValue());
	m_SectFName.SetWindowTextA(Buffer);

	Buffer.Format("%d", m_pCurrentSection->XName.GetValue());
	m_SectXName.SetWindowTextA(Buffer);

	Buffer.Format("%d", m_pCurrentSection->YName.GetValue());
	m_SectYName.SetWindowTextA(Buffer);

	Buffer.Format("%g", m_pCurrentSection->HName.GetValue());
	m_SectHName.SetWindowTextA(Buffer);

	Buffer.Format("%g", m_pCurrentSection->VName.GetValue());
	m_SectVName.SetWindowTextA(Buffer);

	m_SectPName.SetWindowTextA(m_pRecordHandler->GetEditorID(m_pCurrentSection->PName.GetValue()));
	m_SectSName.SetWindowTextA(m_pRecordHandler->GetEditorID(m_pCurrentSection->SName.GetValue()));	

	m_SectCNames.ResetContent();

	for (dword i = 0; i < m_pCurrentSection->CNames.GetSize(); ++i)
	{
		Buffer.Format("%d", m_pCurrentSection->CNames[i]->GetValue());
		m_SectCNames.AddString(Buffer);
	}
	
	m_IsUpdating = false;
}


void CSrAvifView::EnableSectionControls (void)
{
	bool Enable = m_pCurrentSection != NULL;

	m_SectIName.EnableWindow(Enable);
	m_SectPName.EnableWindow(Enable);
	m_SectFName.EnableWindow(Enable);
	m_SectSName.EnableWindow(Enable);
	m_SectXName.EnableWindow(Enable);
	m_SectYName.EnableWindow(Enable);
	m_SectHName.EnableWindow(Enable);
	m_SectVName.EnableWindow(Enable);
	m_SectCNames.EnableWindow(Enable);
	m_SectAddCName.EnableWindow(Enable);
	m_SectEditCName.EnableWindow(Enable);
	m_SectDeleteCName.EnableWindow(Enable);
	m_SectDelete.EnableWindow(Enable);
	m_SectEditPName.EnableWindow(Enable);
	m_SectSelectPName.EnableWindow(Enable);
	m_SectEditSName.EnableWindow(Enable);
	m_SectSelectSName.EnableWindow(Enable);
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


void CSrAvifView::OnBnClickedEditSectperk()
{
	m_pDlgHandler->EditRecordHelper(m_SectPName, SR_NAME_PERK);
}


void CSrAvifView::OnBnClickedSelectSectperk()
{
	m_pDlgHandler->SelectRecordHelper(&m_SectPName, SR_NAME_PERK, &CSrPerkRecord::s_FieldMap);
}


void CSrAvifView::OnBnClickedEditSectsnam()
{
	m_pDlgHandler->EditRecordHelper(m_SectSName, SR_NAME_AVIF);
}


void CSrAvifView::OnBnClickedSelectSectsnam()
{
	m_pDlgHandler->SelectRecordHelper(&m_SectSName, SR_NAME_AVIF, &CSrAvifRecord::s_FieldMap);
}


void CSrAvifView::OnBnClickedAddSectcnam()
{
	if (m_pCurrentSection == NULL) return;
	CString Buffer("0");

	if (!SrInputDialog(Buffer, "Add CName", "Enter New CName Value Below:")) return;

	dword Value = strtoul(Buffer, NULL, 0);
	m_pCurrentSection->AddCName(Value);
	m_SectCNames.AddString(Buffer);
	m_SectCNames.SetCurSel(m_SectCNames.GetCount() - 1);
}


void CSrAvifView::OnBnClickedEditSectcnam()
{
	if (m_pCurrentSection == NULL) return;

	CString Buffer;
	int ListIndex = m_SectCNames.GetCurSel();
	if (ListIndex < 0) return;
	m_SectCNames.GetText(ListIndex, Buffer);

	if (!SrInputDialog(Buffer, "Edit CName", "Enter CName Value Below:")) return;

	m_SectCNames.DeleteString(ListIndex);
	m_SectCNames.InsertString(ListIndex, Buffer);
}

void CSrAvifView::OnLbnDblclkSectcnam()
{
	OnBnClickedEditSectcnam();
}


void CSrAvifView::OnBnClickedDeleteSectcnam()
{
	if (m_pCurrentSection == NULL) return;

	int ListIndex = m_SectCNames.GetCurSel();
	if (ListIndex < 0) return;

	m_SectCNames.DeleteString(ListIndex);
	m_pCurrentSection->CNames.Delete(ListIndex);

	if (ListIndex < m_SectCNames.GetCount())
		m_SectCNames.SetCurSel(ListIndex);
	else
		m_SectCNames.SetCurSel(ListIndex - 1);
}


void CSrAvifView::OnBnClickedAddAvifsection()
{
	sravifsection_t* pSection = m_Sections.AddNew();
	pSection->InitializeNew();

	AddAvifSectionList(pSection);

	SetCurrentSection(pSection);
	m_SectionList.SelectRecord(m_SectionList.GetItemCount() - 1);
}


void CSrAvifView::OnBnClickedDeleteAvifsection()
{
	std::vector<int> ListIndices;
	POSITION Pos;
	int      ListIndex;

	Pos = m_SectionList.GetFirstSelectedItemPosition();

	while (Pos)
	{
		ListIndex = m_SectionList.GetNextSelectedItem(Pos);
		ListIndices.push_back(ListIndex);
	}

	GetSectionData();
	m_pCurrentSection = NULL;

	while (ListIndices.size() > 0)
	{
		ListIndex = ListIndices.back();
		ListIndices.pop_back();

		m_SectionList.DeleteItem(ListIndex);
		m_Sections.Delete(ListIndex);
	}

	if (ListIndex < m_SectionList.GetItemCount())
	{
		m_SectionList.SelectRecord(ListIndex);
		SetCurrentSection(m_Sections[ListIndex]);
	}
	else
	{
		m_SectionList.SelectRecord(0);
		SetCurrentSection(m_Sections[0]);
	}
}


void CSrAvifView::OnLvnItemchangedAvifdataList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	
	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	SetCurrentSection(m_Sections[pNMLV->iItem]);
}


void CSrAvifView::OnDropSectPName (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	*pResult = SRRL_DROPCHECK_ERROR;
	if (m_pCurrentSection == NULL) return;
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SectPName, SR_NAME_PERK, 1);
}


void CSrAvifView::OnDropSectSName (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	*pResult = SRRL_DROPCHECK_ERROR;
	if (m_pCurrentSection == NULL) return;
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SectSName, SR_NAME_AVIF, 1);
}


int CSrAvifView::OnDropCustomSectionData (srrldroprecords_t& DropItems) 
{
	CSrFormidSubrecord*		pPName;
	srrlcustomdata_t*		pCustomData;
	sravifsection_t*   		pSection;
	dword					Index;
	CSrSubrecord*			pSubrecord;

	GetSectionData();

		/* Check all custom data dropped */
	for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
	{
		pCustomData = DropItems.pCustomDatas->GetAt(Index);

			/* Check for dragging another effect record */
		pPName = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
		if (pPName == NULL) return SRRL_DROPCHECK_ERROR;
		if (pPName->GetRecordType() != SR_NAME_PNAM) return SRRL_DROPCHECK_ERROR;
				    
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

		pSection = m_Sections.AddNew();
		if (pSection == NULL) continue;		
		pSection->InitializeNew();

		pSection->PName.Copy(pPName);

		for (dword i = 1; i < pCustomData->Subrecords.GetSize(); ++i)
		{
			pSubrecord = pCustomData->Subrecords[i];
			if (pSubrecord == NULL) continue;			

			if (pSubrecord->GetRecordType() == SR_NAME_FNAM)
			{
				pSection->FName.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_XNAM)
			{
				pSection->XName.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_YNAM)
			{
				pSection->YName.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_HNAM)
			{
				pSection->HName.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_VNAM)
			{
				pSection->VName.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_SNAM)
			{
				pSection->SName.Copy(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_CNAM)
			{
				pSection->CNames.AddNew()->CopyFull(pSubrecord);
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_INAM)
			{
				pSection->IName.Copy(pSubrecord);
			}
			
		}		

		AddAvifSectionList(pSection);
	}

	return SRRL_DROPCHECK_OK;
}


void CSrAvifView::OnDropSectionList (NMHDR* pNotifyStruct, LRESULT* pResult) 
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


