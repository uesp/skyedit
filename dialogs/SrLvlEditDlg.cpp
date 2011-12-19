/*===========================================================================
 *
 * File:		Srlvleditdlg.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "SrLvlEditDlg.h"


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
BEGIN_MESSAGE_MAP(CSrLvlEditDlg, CDialog)
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
static srreclistcolinit_t s_LvlListInit[] = {
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
 * Class CSrLvlEditDlg Constructor
 *
 *=========================================================================*/
CSrLvlEditDlg::CSrLvlEditDlg(CWnd* pParent) : CDialog(CSrLvlEditDlg::IDD, pParent) 
{
  m_TitleValue      = _T("Edit Leveled Object");
  m_pSubrecord      = NULL;
  m_pRecordHandler  = NULL;
  m_EditorIDCheck   = SR_CHECKRESULT_NOCHANGE;
  m_pRecordTypes    = NULL;
  m_ParentFormID    = SR_FORMID_NULL;

  m_UpdateListOnChange = false;
}
/*===========================================================================
 *		End of Class CSrLvlEditDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - void DoDataExchange ( pDX);
 *
 *=========================================================================*/
void CSrLvlEditDlg::DoDataExchange(CDataExchange* pDX) 
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_OBJECT_FORMID, m_FormID);
	DDX_Control(pDX, IDC_LEVEL, m_Level);
	DDX_Control(pDX, IDC_COUNT, m_Count);
	DDX_Control(pDX, IDC_EDITORID, m_ObjectID);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
}
/*===========================================================================
 *		End of Class Method CSrLvlEditDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - void AddListColumns (void);
 *
 *=========================================================================*/
void CSrLvlEditDlg::AddListColumns (void) 
{
  m_RecordList.DeleteAllColumns();    
  m_RecordList.SetupList(SR_NAME_NULL, s_LvlListInit, NULL);
}
/*===========================================================================
 *		End of Class Method CSrLvlEditDlg::AddListColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - void FillRecordList (void);
 *
 *=========================================================================*/
void CSrLvlEditDlg::FillRecordList (void) 
{
  dword		 Index;

	/* Clear the current content */
  m_RecordList.DeleteAllItems();

	/* Add all matching records */
  for (Index = 0; m_pRecordTypes[Index] != SR_NAME_NULL; ++Index) {
    FillRecordList(m_pRecordTypes[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CSrLvlEditDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - void FillRecordList (RecordType);
 *
 *=========================================================================*/
void CSrLvlEditDlg::FillRecordList (const srrectype_t RecordType) 
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
 *		End of Class Method CSrLvlEditDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrLvlEditDlg::GetControlData (void) 
{
  CString	Buffer;
  word		Value;
  bool		Result;

  if (m_pSubrecord == NULL) return;

  m_Count.GetWindowText(Buffer);
  Result = SrFieldConvertWord(Buffer, Value);
  if (Result) m_pSubrecord->SetCount(Value);

  m_Level.GetWindowText(Buffer);
  Result = SrFieldConvertWord(Buffer, Value);
  if (Result) m_pSubrecord->SetLevel(Value);
  
  m_pSubrecord->SetFormID(m_ObjectFormID);
}
/*===========================================================================
 *		End of Class Method CSrLvlEditDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CSrLvlEditDlg::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
 *		End of Class Event CSrLvlEditDlg::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - void OnDeleteButton ();
 *
 *=========================================================================*/
void CSrLvlEditDlg::OnDeleteButton() 
{
  EndDialog(SR_LVLEDITDLG_RESULT_DELETE);
}
/*===========================================================================
 *		End of Class Event CSrLvlEditDlg::OnDeleteButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrLvlEditDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();

  assert(m_pRecordHandler != NULL);
  m_UpdateListOnChange = false;

  SetWindowText(m_TitleValue);

  	/* Initialize the record list */
  m_RecordList.SetListName("LvlEditList");
  m_RecordList.DefaultSettings();
  AddListColumns();
  FillRecordList();
  m_RecordList.SortList(SR_FIELD_EDITORID);

  m_Count.SetLimitText(8);
  m_Level.SetLimitText(8);
  m_ObjectID.SetLimitText(128);

  SetControlData();

  m_UpdateListOnChange = true;
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrLvlEditDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CSrLvlEditDlg::OnOK() 
{
  GetControlData();
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrLvlEditDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - void OnChangeEditorid ();
 *
 *=========================================================================*/
void CSrLvlEditDlg::OnChangeEditorid() 
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
 *		End of Class Event CSrLvlEditDlg::OnChangeEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - void OnKillfocusEditorid ();
 *
 *=========================================================================*/
void CSrLvlEditDlg::OnKillfocusEditorid() 
{

}
/*===========================================================================
 *		End of Class Event CSrLvlEditDlg::OnKillfocusEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrLvlEditDlg::SetControlData (void) 
{
  CString Buffer;

  if (m_pSubrecord == NULL) return;

  Buffer.Format(_T("%u"), (dword) m_pSubrecord->GetCount());
  m_Count.SetWindowText(Buffer);

  Buffer.Format(_T("%u"), (dword) m_pSubrecord->GetLevel());
  m_Level.SetWindowText(Buffer);

  m_ObjectFormID = m_pSubrecord->GetFormID();
  Buffer.Format(_T("0x%08X"), m_ObjectFormID);
  m_FormID.SetWindowText(Buffer);

  Buffer = m_pRecordHandler->GetEditorID(m_ObjectFormID);  
  m_ObjectID.SetWindowText(Buffer);

  m_RecordList.SelectRecord(m_pRecordHandler->FindFormID(m_ObjectFormID));
}
/*===========================================================================
 *		End of Class Method CSrLvlEditDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CSrLvlEditDlg::UpdateEditorID (void) 
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
  if (m_ObjectFormID == m_pSubrecord->GetFormID()) return (SR_CHECKRESULT_NOCHANGE);

  Buffer.Format(_T("0x%08X"), m_ObjectFormID);
  m_FormID.SetWindowText(Buffer);

  return (SR_CHECKRESULT_OK);
}
/*===========================================================================
 *		End of Class Method CSrLvlEditDlg::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLvlEditDlg Event - void OnItemchangedRecordlist (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrLvlEditDlg::OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult)
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
 *		End of Class Event CSrLvlEditDlg::OnItemchangedRecordlist()
 *=========================================================================*/


LRESULT CSrLvlEditDlg::OnActivateList (WPARAM wParam, LPARAM lParam) 
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
 * Function - int SrEditLvlItemDlg (pSubrecord, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled item.
 *
 *=========================================================================*/
int SrEditLvlItemDlg (CSrLvloSubrecord* pSubrecord, CSrRecordHandler* pHandler, const srformid_t ParentFormID) 
{
  static const srrectype_t s_LvliRecordTypes[] = {
	SR_NAME_ALCH,	SR_NAME_AMMO,	SR_NAME_APPA,	SR_NAME_ARMO,	SR_NAME_BOOK,	
	SR_NAME_INGR,	SR_NAME_KEYM,	SR_NAME_LVLI,	SR_NAME_MISC,	SR_NAME_SLGM,
	SR_NAME_WEAP,	SR_NAME_NULL };

  CSrLvlEditDlg Dlg;
  int		Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSubrecord(pSubrecord);
  Dlg.SetTitleValue(_T("Edit Leveled Item Entry"));
  Dlg.SetRecordTypes(s_LvliRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function SrEditLvlItemDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int SrEditLvlSpellDlg (pSubrecord, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled spell.
 *
 *=========================================================================*/
int SrEditLvlSpellDlg (CSrLvloSubrecord* pSubrecord, CSrRecordHandler* pHandler, const srformid_t ParentFormID) 
{
  static const srrectype_t s_LvspRecordTypes[] = { SR_NAME_LVSP, SR_NAME_SPEL, SR_NAME_NULL };
  CSrLvlEditDlg Dlg;
  int		Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSubrecord(pSubrecord);
  Dlg.SetTitleValue(_T("Edit Leveled Spell Entry"));
  Dlg.SetRecordTypes(s_LvspRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function SrEditLvlSpellDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int SrEditLvlActorDlg (pSubrecord, ParentFormID);
 *
 * Displays a modal edit lvlo edit dialog for a leveled creature.
 *
 *=========================================================================*/
int SrEditLvlActorDlg (CSrLvloSubrecord* pSubrecord, CSrRecordHandler* pHandler, const srformid_t ParentFormID) 
{
  static const srrectype_t s_LvlnRecordTypes[] = { SR_NAME_LVLN, SR_NAME_NPC_, SR_NAME_NULL };
  CSrLvlEditDlg Dlg;
  int		Result;

  Dlg.SetRecordHandler(pHandler);
  Dlg.SetSubrecord(pSubrecord);
  Dlg.SetTitleValue(_T("Edit Leveled Actor Entry"));
  Dlg.SetRecordTypes(s_LvlnRecordTypes);
  Dlg.SetParentFormID(ParentFormID);

  Result = Dlg.DoModal();
  return (Result);
}
/*===========================================================================
 *		End of Function SrEditLvlActorDlg()
 *=========================================================================*/


