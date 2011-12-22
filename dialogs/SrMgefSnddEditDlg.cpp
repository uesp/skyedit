/*===========================================================================
 *
 * File:		SrMgefSnddEditDlg.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	21 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "SrMgefSnddEditDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrMgefSnddEditDlg, CDialog)
	ON_BN_CLICKED(ID_DELETE_BUTTON, OnDeleteButton)
	ON_EN_CHANGE(IDC_EDITORID, OnChangeEditorid)
	ON_EN_KILLFOCUS(IDC_EDITORID, OnKillfocusEditorid)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RECORDLIST, OnItemchangedRecordlist)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnActivateList)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Record List Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_MgefSnddListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		60,		LVCFMT_CENTER },
	{ SR_FIELD_TYPE,		75,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };
/*===========================================================================
 *		End of Record List Data
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Constructor
 *
 *=========================================================================*/
CSrMgefSnddEditDlg::CSrMgefSnddEditDlg(CWnd* pParent) : CDialog(CSrMgefSnddEditDlg::IDD, pParent) 
{
	m_TitleValue      = _T("Edit Effect Sound");
	m_pSoundData      = NULL;
	m_pRecordHandler  = NULL;
	m_EditorIDCheck   = SR_CHECKRESULT_NOCHANGE;
	m_pRecordTypes    = NULL;
	m_ParentFormID    = SR_FORMID_NULL;

	m_UpdateListOnChange = false;
}
/*===========================================================================
 *		End of Class CSrMgefSnddEditDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - void DoDataExchange ( pDX);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::DoDataExchange(CDataExchange* pDX) 
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_OBJECT_FORMID, m_FormID);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_EDITORID, m_ObjectID);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
}
/*===========================================================================
 *		End of Class Method CSrMgefSnddEditDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - void AddListColumns (void);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::AddListColumns (void) 
{
  m_RecordList.DeleteAllColumns();    
  m_RecordList.SetupList(SR_NAME_NULL, s_MgefSnddListInit, NULL);
}
/*===========================================================================
 *		End of Class Method CSrMgefSnddEditDlg::AddListColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - void FillRecordList (void);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::FillRecordList (void) 
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
 *		End of Class Method CSrMgefSnddEditDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - void FillRecordList (RecordType);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::FillRecordList (const srrectype_t RecordType) 
{
  CSrTypeGroup*  pGroup;
  CSrBaseRecord* pBaseRecord;
  CSrRecord*	 pRecord;
  dword          Index;

  	/* Get the type group for the given record type */
  pGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(RecordType);
  if (pGroup == NULL) return;

	/* Add all matching records in the group */
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pRecord     = SrCastRecord(pBaseRecord);
    if (pRecord == NULL) continue;
    if (pRecord->GetFormID() == m_ParentFormID) continue;

		/* Add the record */
    m_RecordList.AddRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Method CSrMgefSnddEditDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::GetControlData (void) 
{
  CString	Buffer;
  int		Value;
  bool		Result;

  if (m_pSoundData == NULL) return;

  m_Value.GetWindowText(Buffer);
  Result = SrFieldConvertInt(Buffer, Value);
  if (Result) m_pSoundData->Value = Value;
  
  m_pSoundData->SoundID = m_ObjectFormID;
}
/*===========================================================================
 *		End of Class Method CSrMgefSnddEditDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CSrMgefSnddEditDlg::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
  HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_ObjectID) {
    switch (m_EditorIDCheck) {
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
 *		End of Class Event CSrMgefSnddEditDlg::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - void OnDeleteButton ();
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::OnDeleteButton() 
{
  EndDialog(SR_MGEFSNDDEDITDLG_RESULT_DELETE);
}
/*===========================================================================
 *		End of Class Event CSrMgefSnddEditDlg::OnDeleteButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrMgefSnddEditDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();

  assert(m_pRecordHandler != NULL);
  m_UpdateListOnChange = false;

  SetWindowText(m_TitleValue);

  	/* Initialize the record list */
  m_RecordList.SetListName("MgefSnddEditList");
  m_RecordList.DefaultSettings();
  AddListColumns();
  FillRecordList();
  m_RecordList.SortList(SR_FIELD_EDITORID);

  m_Value.SetLimitText(8);
  m_ObjectID.SetLimitText(128);

  SetControlData();

  m_UpdateListOnChange = true;
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrMgefSnddEditDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::OnOK() 
{
  GetControlData();
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrMgefSnddEditDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - void OnChangeEditorid ();
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::OnChangeEditorid() 
{
  CString   Buffer;
  int		Result;
  int		ListIndex;
  
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
 *		End of Class Event CSrMgefSnddEditDlg::OnChangeEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - void OnKillfocusEditorid ();
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::OnKillfocusEditorid() 
{

}
/*===========================================================================
 *		End of Class Event CSrMgefSnddEditDlg::OnKillfocusEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::SetControlData (void) 
{
  CString Buffer;

  if (m_pSoundData == NULL) return;

  Buffer.Format(_T("%u"), (dword) m_pSoundData->Value);
  m_Value.SetWindowText(Buffer);

  m_ObjectFormID = m_pSoundData->SoundID;
  Buffer.Format(_T("0x%08X"), m_ObjectFormID);
  m_FormID.SetWindowText(Buffer);

  Buffer = m_pRecordHandler->GetEditorID(m_ObjectFormID);  
  m_ObjectID.SetWindowText(Buffer);

  m_RecordList.SelectRecord(m_pRecordHandler->FindFormID(m_ObjectFormID));
}
/*===========================================================================
 *		End of Class Method CSrMgefSnddEditDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CSrMgefSnddEditDlg::UpdateEditorID (void) 
{
  CString		Buffer;
  CSString		EditorID;
  CSrIdRecord*	pIdRecord;
  bool			Result;
  int			ListIndex;

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
  if (m_ObjectFormID == m_pSoundData->SoundID) return (SR_CHECKRESULT_NOCHANGE);

  Buffer.Format(_T("0x%08X"), m_ObjectFormID);
  m_FormID.SetWindowText(Buffer);

  return (SR_CHECKRESULT_OK);
}
/*===========================================================================
 *		End of Class Method CSrMgefSnddEditDlg::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrMgefSnddEditDlg Event - void OnItemchangedRecordlist (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrMgefSnddEditDlg::OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult)
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
 *		End of Class Event CSrMgefSnddEditDlg::OnItemchangedRecordlist()
 *=========================================================================*/


LRESULT CSrMgefSnddEditDlg::OnActivateList (WPARAM wParam, LPARAM lParam) 
{
	CSrRecord*   pRecord = (CSrRecord *) wParam;
	CSString	 Buffer;

	if (pRecord == NULL) return 0;
	pRecord->GetField(Buffer, SR_FIELD_EDITORID);
		
	OnOK();
	EndDialog(IDOK);
	return (0);
}


/*===========================================================================
 *
 * Function - int SrEditMgefSnddDlg (pSoundData, pHandler, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled item.
 *
 *=========================================================================*/
int SrEditMgefSnddDlg (srmgefsndddata_t* pSoundData, CSrRecordHandler* pHandler, const srformid_t ParentFormID) 
{
  static const srrectype_t s_MgefSnddRecordTypes[] = { SR_NAME_SNDR, SR_NAME_NULL };

  CSrMgefSnddEditDlg Dlg;
  int				 Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSoundData(pSoundData);
  Dlg.SetTitleValue(_T("Edit Effect Sound"));
  Dlg.SetRecordTypes(s_MgefSnddRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function SrEditMgefSnddDlg()
 *=========================================================================*/
