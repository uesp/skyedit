/*===========================================================================
 *
 * File:		Srfinddlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srFindDlg.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
IMPLEMENT_DYNCREATE(CSrFindDlg, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrFindDlg, CSrRecordDialog)
	ON_BN_CLICKED(ID_FIND_BUTTON, OnFindButton)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Columns
 *
 *=========================================================================*/
static srreclistcolinit_t s_FindListInit[] = 
{
	{ SR_FIELD_EDITORID,	150,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,	85,	LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	75,	LVCFMT_CENTER },
	{ SR_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };
/*===========================================================================
 *		End of List Columns
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Constructor
 *
 *=========================================================================*/
CSrFindDlg::CSrFindDlg (CWnd* pParent) : CSrRecordDialog(CSrFindDlg::IDD) 
{
  m_BinarySize  = 0;
  m_pBinaryData = NULL;

  m_FindData.Flags     = SR_FIND_COMPARETEXT | SR_FIND_ADDRECORDS | SR_FIND_NOHEADER;
  m_FindData.pData     = NULL;
  m_FindData.DataSize  = 0;

  m_FindData.pFindRecords = m_FindList.GetRecords();
}
/*===========================================================================
 *		End of Class CSrFindDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Destructor
 *
 *=========================================================================*/
CSrFindDlg::~CSrFindDlg () {

  if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);

  if (m_pBinaryData != NULL) {
    delete[] m_pBinaryData;
    m_pBinaryData = NULL;
  }

}
/*===========================================================================
 *		End of Class CSrFindDlg Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrFindDlg::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FIND_LABEL, m_FindLabel);
	DDX_Control(pDX, IDC_CASESENSITIVE_CHECK, m_CaseSensitiveCheck);
	DDX_Control(pDX, IDC_BINARY_CHECK, m_BinaryCheck);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_SearchCombo);
	DDX_Control(pDX, IDC_FIND_LIST, m_FindList);
	DDX_Control(pDX, IDC_FORMID_CHECK, m_FormIDCheck);
	DDX_Control(pDX, IDC_FINDSCRIPTS_CHECK, m_FindInScripts);
 }
/*===========================================================================
 *		End of Class Method CSrFindDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CSrFindDlg::ClearControlData (void) 
{

}
/*===========================================================================
 *		End of Class Method CSrFindDlg::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Method - void ConvertBinaryData (void);
 *
 *=========================================================================*/
bool CSrFindDlg::ConvertBinaryData (void) {
  CSString Buffer(m_TextData);
  int      Index;

  Buffer.RemoveCharsToMatch(isxdigit);
  m_TextData = Buffer;
  if (Buffer.IsEmpty()) return (false);

  if (m_pBinaryData != NULL) delete[] m_pBinaryData;
  m_BinarySize  = (Buffer.GetLength() + 1)/2;
  m_pBinaryData = new byte[m_BinarySize + 4];

  for (Index = 0; Index < Buffer.GetLength(); Index += 2) {
    m_pBinaryData[Index/2] = ConvertFromHexChar(Buffer[Index]) << 4;
    if (Index + 1 < Buffer.GetLength()) m_pBinaryData[Index/2] |= ConvertFromHexChar(Buffer[Index + 1]);
  }

  Buffer.Empty();

  for (Index = 0; Index < (int)m_BinarySize; ++Index) {
    Buffer += ConvertByteToHexChar(m_pBinaryData[Index]);
  }

  m_TextData = Buffer; 
  //SystemLog.Printf("Searching for binary data '%s' (%.*s)...", Buffer, m_BinarySize, m_pBinaryData);

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrFindDlg::ConvertBinaryData()
 *=========================================================================*/

  
/*===========================================================================
 *
 * Class CSrFindDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrFindDlg::GetControlData (void) {
  CString Buffer;
  bool    Result;

	/* Set the find flags */
  m_FindData.Flags = SR_FIND_ADDRECORDS | SR_FIND_NOHEADER;
  if (!m_BinaryCheck.GetCheck())       m_FindData.Flags |= SR_FIND_COMPARETEXT;
  if (m_CaseSensitiveCheck.GetCheck()) m_FindData.Flags |= SR_FIND_CASESENSITIVE;
  if (m_FormIDCheck.GetCheck())        m_FindData.Flags |= SR_FIND_FORMID;
  if (m_FindInScripts.GetCheck())      m_FindData.Flags |= SR_FIND_INCLUDESCRIPTS;

	/* Update the search text */
  m_SearchCombo.GetWindowText(m_TextData);

	/* Set the binary data as required */
  if (m_BinaryCheck.GetCheck()) 
  {
    Result = ConvertBinaryData();

    if (!Result) {
      m_FindLabel.SetWindowText("Invalid hexadecimal binary data specified!");
      m_FindData.DataSize = 0;
      m_FindData.pData    = NULL;
      return;
    }

    m_FindData.DataSize = m_BinarySize;
    m_FindData.pData    = m_pBinaryData;
    m_SearchCombo.SetWindowText(m_TextData);
  }
  else if (m_FindData.Flags & SR_FIND_FORMID)
  {
	m_FindData.DataSize = 4;
	m_FindData.pData    = (const byte *) &m_FindFormID;
	m_FindFormID = strtol(m_TextData, NULL, 0);
  }
  else
  {
    m_FindData.DataSize = m_TextData.GetLength();
    m_FindData.pData    = (const byte *) (const TCHAR *) m_TextData;
    if (m_FindData.DataSize == 0) m_FindLabel.SetWindowText("Nothing to find!");
  }
  
}
/*===========================================================================
 *		End of Class Method CSrFindDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Method - bool IsEditRecord (pRecord);
 *
 *=========================================================================*/
bool CSrFindDlg::IsEditRecord (CSrRecord* pRecord) 
{
  return (false);
}
/*===========================================================================
 *		End of Class Method CSrFindDlg::IsEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrFindDlg::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();
  
  m_FindList.SetListName("FindList");
  m_FindList.DefaultSettings();
  m_FindList.SetupList(SR_NAME_NULL, s_FindListInit, NULL);

  m_FindList.SortList(SR_FIELD_EDITORID);

  m_pRecordHandler->GetEventHandler().AddListener(this);

  SetTitle("");
  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - void OnSave (void);
 *
 *=========================================================================*/
void CSrFindDlg::OnSave (void) {
  Close();
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - void OnCancel (void);
 *
 *=========================================================================*/
void CSrFindDlg::OnCancel (void) {
  Close();
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - void OnApply ();
 *
 *=========================================================================*/
void CSrFindDlg::OnApply() {
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - void OnFindButton ();
 *
 *=========================================================================*/
void CSrFindDlg::OnFindButton() {
  CSrProgressDlg* pProgressDlg = NULL;
  CSrCallback*    pCallback    = NULL;
  CString	  Buffer;
  dword		  ResultCount;
  srtimer_t	  Timer;
  double	  DeltaTime;
  int		  ListIndex;

  GetControlData();
  m_FindList.DeleteAllItems();

  if (m_FindData.DataSize == 0) return;
  
	/* TODO: Proper history */
  ListIndex = m_SearchCombo.FindStringExact(-1, m_TextData);

  if (ListIndex < 0) {
    m_SearchCombo.InsertString(0, m_TextData);
  }
  else if (ListIndex > 0) {
    m_SearchCombo.DeleteString(ListIndex);   
    m_SearchCombo.InsertString(0, m_TextData);
  }

	/* Clear the current find data */
  m_FindData.FileCount       = 0;
  m_FindData.FoundRecords    = 0;
  m_FindData.FoundSubrecords = 0;
  m_FindData.GroupCount      = 0;
  m_FindData.RecordCount     = 0;
  m_FindData.SubrecordCount  = 0;
  m_FindData.ScriptCount     = 0;
  m_FindData.FoundScripts    = 0;
  m_FindData.pExcludeRecords = NULL;  

		/* Create a progress dialog */
  if (m_pRecordHandler->GetNumRecords() > 1000 || (m_FindData.Flags & SR_FIND_INCLUDESCRIPTS) != 0) 
  {
    pProgressDlg = ShowSrProgressDlg(_T("Finding..."), _T("Finding data..."));

    m_Callback.SetEnable(true);
    m_Callback.SetFunction(SrEditDefaultProgressCallback);
    m_Callback.SetUserPtr(pProgressDlg);
    m_Callback.Reset();

    pCallback = &m_Callback;
  }
 
	/* Perform the find */
  SrStartTimer(Timer);
  ResultCount = m_pRecordHandler->Search(m_FindData, pCallback);
  
  if ((m_FindData.Flags & SR_FIND_INCLUDESCRIPTS) != 0)
  {
	  ResultCount += GetSrEditApp().FindInScripts(m_FindData, pCallback);
  }
  
  DestroySrProgressDlg(pProgressDlg);
  DeltaTime = SrEndTimer(Timer);

	/* Update the find label */
  if ((m_FindData.Flags & SR_FIND_INCLUDESCRIPTS) != 0)
  {
	  Buffer.Format("Found %u matches in %u records/scripts (%.3f seconds).", ResultCount, m_FindData.RecordCount + m_FindData.ScriptCount, DeltaTime);
	  //m_FindList.SetItemCountEx(m_FindData.pFindRecords->GetSize() + m_FindData.FindScripts.GetSize());
	  m_FindList.SetItemCountEx(m_FindData.pFindRecords->GetSize());
  }
  else
  {
	  Buffer.Format("Found %u matches in %u records (%.3f seconds).", ResultCount, m_FindData.RecordCount, DeltaTime);
	  m_FindList.SetItemCountEx(m_FindData.pFindRecords->GetSize());
  }  

  m_FindList.RedrawWindow();
  m_FindLabel.SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnFindButton()
 *=========================================================================*/


/*======================================= ====================================
 *
 * Class CSrFindDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrFindDlg::SetControlData (void) { 
  m_FindList.RedrawWindow();
}
/*===========================================================================
 *		End of Class Method CSrFindDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Method - void SetTitle (pEditorID);
 *
 *=========================================================================*/
void CSrFindDlg::SetTitle (const SSCHAR* pEditorID) {
  CString Buffer;

  Buffer.Format("%s -- Find", m_pDlgHandler->GetTitle());
  SetWindowText(Buffer);
  SetInternalWindowText(GetParentFrame()->m_hWnd, Buffer);
}
/*===========================================================================
 *		End of Class Method CSrFindDlg::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - int OnListenAddRecord (pEvent);
 *
 *=========================================================================*/
int CSrFindDlg::OnListenAddRecord (CSrListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_FindList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_FindList.UpdateRecord(NULL, pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnListenAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrFindDlg::OnListenCleanRecord (CSrListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_FindList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_FindList.UpdateRecord(NULL, pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindDlg Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrFindDlg::OnListenUpdateRecord (CSrListenEvent* pEvent) {
  int ListIndex;

  ListIndex = m_FindList.FindRecord(pEvent->GetOldRecord());
  if (ListIndex >= 0) m_FindList.UpdateRecord(NULL, pEvent->GetOldRecord());

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrFindDlg::OnListenUpdateRecord()
 *=========================================================================*/


