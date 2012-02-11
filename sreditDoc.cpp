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
#include "common/srbackup.h"


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
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CSrEditDoc Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Constructor
 *
 *=========================================================================*/
CSrEditDoc::CSrEditDoc() 
{
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

  SrDoSavePluginBackup(lpszPathName, GetActiveFile().IsLoadLocalString());

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
