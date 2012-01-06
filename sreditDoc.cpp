/*===========================================================================
 *
 * File:		SreditDoc.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implementation of the CSrEditDoc document class.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "sreditDoc.h"
#include "modfile/records/srcheckrecord.h"
#include "modfile/srexport.h"
#include "modfile/srimport.h"
#include "common/srutils.h"


/*===========================================================================
 *
 * Begin Location Definitions
 *
 *=========================================================================*/

	/* Debug definitions */
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  IMPLEMENT_DYNCREATE(CSrEditDoc, CDocument)

/*===========================================================================
 *		End of Location Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrEditDoc Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEditDoc, CDocument)
  //{{AFX_MSG_MAP(CSrEditDoc)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CSrEditDoc Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Constructor
 *
 *=========================================================================*/
CSrEditDoc::CSrEditDoc() {
  m_HasActiveContent = false;
}
/*===========================================================================
 *		End of Class CSrEditDoc Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Destructor
 *
 *=========================================================================*/
CSrEditDoc::~CSrEditDoc() {
  m_RecordHandler.Destroy();
}
/*===========================================================================
 *		End of Class CSrEditDoc Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - void DeleteContents ();
 *
 *=========================================================================*/
void CSrEditDoc::DeleteContents() {
  m_RecordHandler.Destroy();
  CDocument::DeleteContents();
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::DeleteContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Event - BOOL OnNewDocument ();
 *
 *=========================================================================*/
BOOL CSrEditDoc::OnNewDocument() {
  if (!CDocument::OnNewDocument()) return FALSE;
  m_HasActiveContent = false;

  m_RecordHandler.NewFile();
  return (TRUE);
 }
/*===========================================================================
 *		End of Class Event CSrEditDoc::OnNewDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Event - BOOL OnOpenDocument (lpszPathName);
 *
 *=========================================================================*/
BOOL CSrEditDoc::OnOpenDocument (LPCTSTR lpszPathName) {
  srfileloadinfo_t* pLoadInfo    = ((CSrEditApp *) AfxGetApp())->GetCurrentLoadInfo();
  CSrProgressDlg*   pProgressDlg = ((CSrEditApp *) AfxGetApp())->GetCurrentProgressDlg();
  CSrCallback*      pCallback    = ((CSrEditApp *) AfxGetApp())->GetCurrentLoadCallback();
  bool		    Result;

  if (pLoadInfo == NULL) {
    AddSrGeneralError("Invalid load information received!");
    return (FALSE);
  }

  SetModifiedFlag();

  m_HasActiveContent = !pLoadInfo->m_ActiveFilename.IsEmpty();
  
  Result = m_RecordHandler.Load(*pLoadInfo, pCallback);

  if (!Result) {
    DeleteContents();
    return (FALSE); 
   }

  SetModifiedFlag(FALSE);
  //SetTitle(m_RecordHandler.GetActiveFile().GetShortFilename());
  //UpdateAllViews(NULL, SREDIT_DOC_HINT_UPDATEALL, NULL);
  return (TRUE);
 }
/*===========================================================================
 *		End of Class Event CSrEditDoc::OnOpenDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - BOOL DoFileSave ();
 *
 *=========================================================================*/
BOOL CSrEditDoc::DoFileSave() {

  if (!m_HasActiveContent) {
    CSString InstallPath;

    GetSrInstallPath(InstallPath);
    m_strPathName  = InstallPath;
    m_strPathName += "data\\";
    m_strPathName += m_strTitle;
    m_strPathName += ".esp";
    return DoSave(NULL);
  }

  return CDocument::DoFileSave();
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::DoFileSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - bool DoSaveBackup (pFilename);
 *
 *=========================================================================*/
bool CSrEditDoc::DoSaveBackup (const TCHAR* pFilename) {
	bool Result;

		/* Are backups enabled? */
	if (!CSrMultiRecordHandler::GetOptions().EnableBackup)       return (true);
	if (!CSrMultiRecordHandler::GetOptions().EnableBackupOnSave) return (true);

		/* Main plugin backup */
	Result = DoBackup(pFilename);
	if (!Result) return false;

		/* Do string file backup only if required */
	if (!GetActiveFile().IsLoadLocalString()) return true;

	Result  = DoBackup(CreateSrStringFilename(pFilename, "ILSTRINGS"));
	Result &= DoBackup(CreateSrStringFilename(pFilename, "DLSTRINGS"));
	Result &= DoBackup(CreateSrStringFilename(pFilename, "STRINGS"));
	return Result;
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::DoBackup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - bool CheckBackups (OldestFile, BackupCount, const int64 BackupSize);
 *
 *=========================================================================*/
bool CSrEditDoc::CheckBackups (const char* OldestFile, const dword BackupCount, const int64 BackupSize) {
  BOOL Result;
  bool Delete = false;
  
  if (CSrMultiRecordHandler::GetOptions().MaxBackupCount > 0 && (int)BackupCount > CSrMultiRecordHandler::GetOptions().MaxBackupCount) {
    Delete = true;
  }
  else if (CSrMultiRecordHandler::GetOptions().MaxBackupSize > 0 && BackupSize/1000000 > CSrMultiRecordHandler::GetOptions().MaxBackupSize) {
    Delete = true;
  }

  if (Delete) {
    Result = DeleteFile(OldestFile);
    if (!Result) return AddSrWindowsError("Failed to delete the old backup file '%s'!", OldestFile);
    SystemLog.Printf("Deleted old backup file '%s'.", OldestFile);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::CheckBackups()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - bool MakeBackupFile (OutputFile, InputFile);
 *
 * TODO: Cleanup, better backup cleanup needed
 *
 *=========================================================================*/
bool CSrEditDoc::MakeBackupFile (CString& OutputFile, CString& InputFile) {
  WIN32_FIND_DATA FindData;
  CString	  OldestFile;
  FILETIME	  OldestTime;
  CString	  Filename;
  HANDLE	  hFind;
  int		  CharIndex;
  BOOL		  Result;
  int		  MaxBackupIndex = 0;
  int		  BackupIndex;
  dword		  BackupCount = 0;
  int64		  BackupSize  = 0;
  
  Filename = InputFile;
  CharIndex = Filename.ReverseFind('\\'); 
  if (CharIndex >= 0) Filename.Delete(0, CharIndex + 1);

  OutputFile  = CSrMultiRecordHandler::GetOptions().FullBackupPath;
  OutputFile += Filename;
  Filename    = OutputFile + ".*";

	/* Find the maximum existing backup index of the current backup file */
  hFind  = FindFirstFile(Filename, &FindData);
  Result = TRUE;
  
  while (hFind != INVALID_HANDLE_VALUE && Result) {
    Filename = FindData.cFileName;

    CharIndex = Filename.ReverseFind('.'); 
    if (CharIndex >= 0) Filename.Delete(0, CharIndex + 1);
    
    BackupIndex = atoi(Filename);
    if (BackupIndex > MaxBackupIndex) MaxBackupIndex = BackupIndex;

    if (OldestFile.IsEmpty() || CompareFileTime(&OldestTime, &FindData.ftLastWriteTime) > 0) {
      OldestFile = FindData.cFileName;
      OldestTime = FindData.ftLastWriteTime;
    }

    ++BackupCount;
    BackupSize += (int64) FindData.nFileSizeLow;
    BackupSize += ((int64) FindData.nFileSizeHigh) << 32;
    Result = FindNextFile(hFind, &FindData);
  }

	/* See if we need to delete the oldest backup file */
  if (!OldestFile.IsEmpty()) {
    Filename  = CSrMultiRecordHandler::GetOptions().FullBackupPath;
    Filename += OldestFile;
    CheckBackups(Filename, BackupCount, BackupSize);
  }
  
	/* Create the output filename */
  ++MaxBackupIndex;
  Filename.Format(".%03d", MaxBackupIndex);
  OutputFile += Filename;

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::MakeBackupFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - bool CreateBackupPath (void);
 *
 *=========================================================================*/
bool CSrEditDoc::CreateBackupPath (void) {
  bool Result;
  
  Result = MakePathEx(CSrMultiRecordHandler::GetOptions().FullBackupPath);

  if (!Result) {
    AddSrGeneralError("Failed to create the backup directory '%s'!", CSrMultiRecordHandler::GetOptions().FullBackupPath);
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::CreateBackupPath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - bool DoBackup (pFilename);
 *
 *=========================================================================*/
bool CSrEditDoc::DoBackup (const TCHAR* pFilename) 
{
	CString InputFile;
	CString OutputFile;
	bool    Result;
	BOOL    CopyResult;

		/* Ignore if the file doesn't yet exist */
	InputFile = pFilename;
	if (!FileExists(InputFile)) return true;

	Result = MakeBackupFile(OutputFile, InputFile);
	if (!Result) return false;

	Result = CreateBackupPath();
	if (!Result) return false;

	CopyResult = CopyFile(InputFile, OutputFile, FALSE);
	if (!CopyResult) return AddSrWindowsError("Failed to backup '%s' to '%s'!", InputFile, OutputFile);

	SystemLog.Printf("Successfully backed up '%s' to '%s'", InputFile, OutputFile);
	return true;
}
/*===========================================================================
 *		End of Class Method CSrEditDoc::DoBackup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Event - BOOL OnSaveDocument (lpszPathName);
 *
 *=========================================================================*/
BOOL CSrEditDoc::OnSaveDocument (LPCTSTR lpszPathName) {
  CSrProgressDlg* pProgressDlg;
  CSrCallback     SaveCallback;
  CString	  Filename(lpszPathName);
  int		  CharIndex;
  bool		  Result;

  UpdateAllViews(NULL, SREDIT_DOC_HINT_GETDATA, NULL);

  DoSaveBackup(lpszPathName);

  CharIndex = Filename.ReverseFind('\\'); 
  if (CharIndex >= 0) Filename.Delete(0, CharIndex + 1);

  pProgressDlg = ShowSrProgressDlg(_T("Saving File"), _T("Saving File..."));
  //pProgressDlg->SetCancelMsg(_T("Are you sure you wish to abort this save?"));
  SaveCallback.SetCallbackInterval(100);
  SaveCallback.SetUserPtr((void *) pProgressDlg);
  SaveCallback.SetFunction(SrEditDefaultProgressCallback);
  
  Result = GetActiveFile().Save(lpszPathName, &SaveCallback);

  DestroySrProgressDlg(pProgressDlg);

  if (!Result) {
    ReportSaveLoadException(lpszPathName, NULL, TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
    return (FALSE); 
   }

  m_HasActiveContent = true;
  SetModifiedFlag(FALSE);
  return (TRUE);
 }
/*===========================================================================
 *		End of Class Event CSrEditDoc::OnSaveDocument()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Method - void Serialize (ar);
 *
 *=========================================================================*/
void CSrEditDoc::Serialize (CArchive& ar) {
  assert(false);
 }
/*===========================================================================
 *		End of Class Method CSrEditDoc::Serialize()
 *=========================================================================*/


#ifdef _DEBUG
/*===========================================================================
*
 * Class CSrEditDoc Diagnostics
 * 
 *=========================================================================*/
void CSrEditDoc::AssertValid() const {
  CDocument::AssertValid();
 }

void CSrEditDoc::Dump(CDumpContext& dc) const {
  CDocument::Dump(dc);
 }
/*===========================================================================
 *		End of Class CSrEditDoc Diagnostics
 *=========================================================================*/
#endif
