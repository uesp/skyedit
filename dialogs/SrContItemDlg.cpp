/*===========================================================================
 *
 * File:		SrContItemDlg.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "SrContItemDlg.h"
#include "sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrContItemDlg, CDialog)
	ON_BN_CLICKED(ID_DELETE_BUTTON, OnDeleteButton)
	ON_EN_CHANGE(IDC_EDITORID, OnChangeEditorid)
	ON_EN_KILLFOCUS(IDC_EDITORID, OnKillfocusEditorid)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RECORDLIST, OnItemchangedRecordlist)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnActivateList)
	ON_BN_CLICKED(IDC_EDIT_FACTION, &CSrContItemDlg::OnBnClickedEditFaction)
	ON_BN_CLICKED(IDC_SELECT_FACTION, &CSrContItemDlg::OnBnClickedSelectFaction)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Record List Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_ContListInit[] = 
{
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		60,		LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	75,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
};
/*===========================================================================
 *		End of Record List Data
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Constructor
 *
 *=========================================================================*/
CSrContItemDlg::CSrContItemDlg(CWnd* pParent) : CDialog(CSrContItemDlg::IDD, pParent) 
{
	m_TitleValue      = _T("Edit Container Item Object");
	m_pListInfo       = NULL;
	m_pRecordHandler  = NULL;
	m_EditorIDCheck   = SR_CHECKRESULT_NOCHANGE;
	m_pRecordTypes    = NULL;
	m_ParentFormID    = SR_FORMID_NULL;

	m_UpdateListOnChange = false;
}
/*===========================================================================
 *		End of Class CSrContItemDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - void DoDataExchange ( pDX);
 *
 *=========================================================================*/
void CSrContItemDlg::DoDataExchange(CDataExchange* pDX) 
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_OBJECT_FORMID, m_FormID);
	DDX_Control(pDX, IDC_COUNT, m_Count);
	DDX_Control(pDX, IDC_EDITORID, m_ObjectID);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
	DDX_Control(pDX, IDC_FACTION, m_Faction);
	DDX_Control(pDX, IDC_MINRANK, m_MinRank);
	DDX_Control(pDX, IDC_CONDITION, m_Condition);
}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - void AddListColumns (void);
 *
 *=========================================================================*/
void CSrContItemDlg::AddListColumns (void) 
{
	m_RecordList.DeleteAllColumns();    
	m_RecordList.SetupList(SR_NAME_NULL, s_ContListInit, NULL);
}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::AddListColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - void FillRecordList (void);
 *
 *=========================================================================*/
void CSrContItemDlg::FillRecordList (void) 
{
	dword		 Index;

		/* Clear the current content */
	m_RecordList.DeleteAllItems();

		/* Add all matching records */
	for (Index = 0; m_pRecordTypes[Index] != SR_NAME_NULL; ++Index) 
	{
		FillRecordList(m_pRecordTypes[Index]);
	}

}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - void FillRecordList (RecordType);
 *
 *=========================================================================*/
void CSrContItemDlg::FillRecordList (const srrectype_t RecordType) 
{
	CSrTypeGroup*  pGroup;
	CSrBaseRecord* pBaseRecord;
	CSrRecord*	 pRecord;
	dword          Index;

  		/* Get the type group for the given record type */
	pGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(RecordType);
	if (pGroup == NULL) return;

		/* Add all matching records in the group */
	for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) 
	{
		pBaseRecord = pGroup->GetRecord(Index);
		pRecord     = SrCastRecord(pBaseRecord);
		if (pRecord == NULL) continue;
		if (pRecord->GetFormID() == m_ParentFormID) continue;

		m_RecordList.AddRecord(pRecord);
	}

}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrContItemDlg::GetControlData (void) 
{
	CString		Buffer;
	CSrRecord*  pRecord;
	int		    MinRank;
	float		Condition;
	word		Value;
	bool		Result;

	if (m_pListInfo == NULL) return;

	m_Count.GetWindowText(Buffer);
	Result = SrFieldConvertWord(Buffer, Value);
	if (Result) m_pListInfo->SetCount(Value);
  
	m_pListInfo->SetFormID(m_ObjectFormID);

	m_Faction.GetWindowTextA(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pRecordHandler->FindEditorID(Buffer);

	m_Condition.GetWindowTextA(Buffer);
	Condition = (float) atof(Buffer);

	m_MinRank.GetWindowTextA(Buffer);
	MinRank = strtol(Buffer, NULL, 0);

	m_pListInfo->SetCoedData(pRecord ? pRecord->GetFormID() : 0, MinRank, Condition);
}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CSrContItemDlg::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_ObjectID) 
	{
		switch (m_EditorIDCheck) 
		{
		case SR_CHECKRESULT_NOCHANGE:
			hBrush = CreateSolidBrush(RGB(255,255,255));
			pDC->SetBkColor(RGB(255,255,255));
			break;
		case SR_CHECKRESULT_OK:
			hBrush = CreateSolidBrush(RGB(204,255,204));
			pDC->SetBkColor(RGB(204,255,204));
			break;
		case SR_CHECKRESULT_ERROR:
			hBrush = CreateSolidBrush(RGB(255,204,204));
			pDC->SetBkColor(RGB(255,204,204));
			break;
		}
	}

	return (hBrush);
}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - void OnDeleteButton ();
 *
 *=========================================================================*/
void CSrContItemDlg::OnDeleteButton() 
{
	EndDialog(SR_CONTITEMDLG_RESULT_DELETE);
}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnDeleteButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrContItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	assert(m_pRecordHandler != NULL);
	m_UpdateListOnChange = false;

	SetWindowText(m_TitleValue);

  		/* Initialize the record list */
	m_RecordList.SetListName("ContItemList");
	m_RecordList.DefaultSettings();
	m_RecordList.SetActivateType(SR_RLACTIVATE_RECORD);
	
	AddListColumns();
	FillRecordList();
	m_RecordList.SortList(SR_FIELD_EDITORID);

	m_Count.SetLimitText(8);
	m_ObjectID.SetLimitText(128);
	m_Faction.SetLimitText(128);
	m_Condition.SetLimitText(10);
	m_MinRank.SetLimitText(10);

	SetControlData();

	m_UpdateListOnChange = true;
	return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CSrContItemDlg::OnOK() 
{
	GetControlData();
	CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - void OnChangeEditorid ();
 *
 *=========================================================================*/
void CSrContItemDlg::OnChangeEditorid() 
{
	CString		Buffer;
	int			Result;
	int			ListIndex;
  
	Result = UpdateEditorID();

	if (Result != m_EditorIDCheck) 
	{
		m_EditorIDCheck = Result;
		m_ObjectID.RedrawWindow();
	}

	if (m_UpdateListOnChange) 
	{
		m_UpdateListOnChange = false;
		m_ObjectID.GetWindowText(Buffer);
    
		ListIndex = m_RecordList.FindEditorID(Buffer);
	
		if (ListIndex >= 0) m_RecordList.SelectRecord(ListIndex);
		m_UpdateListOnChange = true;
	}

}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnChangeEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - void OnKillfocusEditorid ();
 *
 *=========================================================================*/
void CSrContItemDlg::OnKillfocusEditorid() 
{

}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnKillfocusEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrContItemDlg::SetControlData (void) 
{
	CString Buffer;

	if (m_pListInfo == NULL) return;

	Buffer.Format(_T("%u"), (dword) m_pListInfo->GetCount());
	m_Count.SetWindowText(Buffer);

	m_ObjectFormID = m_pListInfo->GetFormID();
	Buffer.Format(_T("0x%08X"), m_ObjectFormID);
	m_FormID.SetWindowText(Buffer);

	Buffer = m_pRecordHandler->GetEditorID(m_ObjectFormID);  
	m_ObjectID.SetWindowText(Buffer);

	m_RecordList.SelectRecord(m_pRecordHandler->FindFormID(m_ObjectFormID));

	if (m_pListInfo->pCoed != NULL)
	{
		m_Faction.SetWindowTextA(m_pRecordHandler->GetEditorID(m_pListInfo->pCoed->GetCoedData().FactionID));

		Buffer.Format("%g", m_pListInfo->pCoed->GetCoedData().Condition);
		m_Condition.SetWindowTextA(Buffer);

		Buffer.Format("%d", (int) m_pListInfo->pCoed->GetCoedData().MinRank);
		m_MinRank.SetWindowTextA(Buffer);
	}
	else
	{
		m_Faction.SetWindowTextA("");
		m_Condition.SetWindowTextA("");
		m_MinRank.SetWindowTextA("");
	}
}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CSrContItemDlg::UpdateEditorID (void) 
{
	CString			Buffer;
	CSString		EditorID;
	CSrIdRecord*	pIdRecord;
	bool			Result;
	int				ListIndex;

	m_ObjectID.GetWindowText(Buffer);
	EditorID = Buffer;

	Result = SrPrepareEditorID(EditorID);
	if (!Result) return (SR_CHECKRESULT_ERROR);

	pIdRecord = m_pRecordHandler->FindEditorID(EditorID);
	if (pIdRecord == NULL) return (SR_CHECKRESULT_ERROR);
	if (pIdRecord->GetFormID() == m_ParentFormID) return (SR_CHECKRESULT_ERROR);

	ListIndex = m_RecordList.FindRecord(pIdRecord);
	if (ListIndex < 0) return (SR_CHECKRESULT_ERROR);

	m_ObjectFormID = pIdRecord->GetFormID();
	if (m_ObjectFormID == m_pListInfo->GetFormID()) return (SR_CHECKRESULT_NOCHANGE);

	Buffer.Format(_T("0x%08X"), m_ObjectFormID);
	m_FormID.SetWindowText(Buffer);

	return (SR_CHECKRESULT_OK);
}
/*===========================================================================
 *		End of Class Method CSrContItemDlg::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContItemDlg Event - void OnItemchangedRecordlist (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrContItemDlg::OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW *) pNMHDR;
	CSrRecord*   pRecord;
	CSString     Buffer;
	*pResult = 0;

	if (!m_UpdateListOnChange) return;

	pRecord = m_RecordList.GetSelectedRecord();
	if (pRecord == NULL) return;

	m_UpdateListOnChange = false;
	pRecord->GetField(Buffer, SR_FIELD_EDITORID);
	m_ObjectID.SetWindowText(Buffer);
	m_UpdateListOnChange = true;
}
/*===========================================================================
 *		End of Class Event CSrContItemDlg::OnItemchangedRecordlist()
 *=========================================================================*/


LRESULT CSrContItemDlg::OnActivateList (WPARAM wParam, LPARAM lParam) 
{
	CSrRecord*   pRecord = (CSrRecord *) wParam;
	CSString	 Buffer;

	if (pRecord == NULL) return 0;
	pRecord->GetField(Buffer, SR_FIELD_EDITORID);
		
	OnOK();
	EndDialog(IDOK);
	return (0);
}


void CSrContItemDlg::OnBnClickedEditFaction()
{
	m_pDlgHandler->EditRecordHelper(m_Faction, SR_NAME_FACT);
}


void CSrContItemDlg::OnBnClickedSelectFaction()
{
	m_pDlgHandler->SelectRecordHelper(&m_Faction, SR_NAME_FACT, &CSrFactRecord::s_FieldMap);
}


/*===========================================================================
 *
 * Function - int SrEditContItemDlg (pListInfo, ParentFormID);
 *
 *=========================================================================*/
int SrEditContItemDlg (srlvllistinfo_t* pListInfo, CSrEditDlgHandler* pHandler, const srformid_t ParentFormID) 
{
	static const srrectype_t s_ContRecordTypes[] = 
	{
		SR_NAME_ALCH,	SR_NAME_AMMO,	SR_NAME_APPA,	SR_NAME_ARMO,	SR_NAME_BOOK,	
		SR_NAME_INGR,	SR_NAME_KEYM,	SR_NAME_LVLI,	SR_NAME_MISC,	SR_NAME_SLGM,
		SR_NAME_WEAP,	SR_NAME_NULL 
	};

	CSrContItemDlg Dlg;
	int		Result;

	if (pHandler == NULL || pListInfo == NULL) return SR_CONTITEMDLG_RESULT_CANCEL;

	Dlg.SetDlgHandler(pHandler);
	Dlg.SetRecordHandler(&pHandler->GetDocument()->GetRecordHandler());
	Dlg.SetLvlListInfo(pListInfo);
	Dlg.SetTitleValue(_T("Edit Container Item Entry"));
	Dlg.SetRecordTypes(s_ContRecordTypes);
	Dlg.SetParentFormID(ParentFormID);

	Result = Dlg.DoModal();
	return (Result);
}
/*===========================================================================
 *		End of Function SrEditContItemDlg()
 *=========================================================================*/

