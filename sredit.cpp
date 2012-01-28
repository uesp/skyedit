/*===========================================================================
 *
 * File:		Sredit.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Defines the class behaviors for the application.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "sreditDoc.h"
#include "sreditView.h"
#include "srloaddlg.h"
#include "stdarg.h"
#include "aboutdlg.h"
#include "shlwapi.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Debug definitions */
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

		/* Main application object */
	CSrEditApp theApp;

		/* Global clipboard objects */
	CSrConditionArray g_GlobClipConditions;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrEditApp Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEditApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrEditApp Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Constructor
 *
 *=========================================================================*/
CSrEditApp::CSrEditApp() 
{
	m_pCurrentLoadInfo     = NULL;
	m_pCurrentProgressDlg  = NULL;
	m_pCurrentLoadCallback = NULL;
	m_NewFileIndex         = 1;
	m_InitResourceHandler  = false;
	m_pMainFrame           = NULL;
}
/*===========================================================================
 *		End of Class CSrEditApp Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Destructor
 *
 *=========================================================================*/
CSrEditApp::~CSrEditApp() 
{
}
/*===========================================================================
 *		End of Class CSrEditApp Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - BOOL InitInstance ();
 *
 *=========================================================================*/
BOOL CSrEditApp::InitInstance() {
  TCHAR    Buffer[_MAX_PATH + 8];
  CSString PathBuffer;
  bool     Result;

  SystemLog.Open("skyedit.log");

  AfxEnableControlContainer();
  AfxInitRichEdit2();

#ifdef _AFXDLL
  Enable3dControls();
#else
  Enable3dControlsStatic();
#endif

	/* Register custom window classes */
  WNDCLASSEX ClassInfo;
  ClassInfo.cbSize = sizeof(ClassInfo);
  ClassInfo.style = 0;
  ClassInfo.lpfnWndProc = DefWindowProc;
  ClassInfo.cbClsExtra = 0;
  ClassInfo.cbWndExtra = 0;
  ClassInfo.hInstance = m_hInstance;
  ClassInfo.hIcon = NULL;
  ClassInfo.hCursor = NULL;
  ClassInfo.hbrBackground = NULL;
  ClassInfo.hIconSm = NULL;
  ClassInfo.lpszMenuName = NULL;
  ClassInfo.lpszClassName = "PreviewImageClass";
  RegisterClassEx(&ClassInfo);

	/* Initialize the image library */
  ilInit();
  iluInit();
  ilutInit();

	/* Load the standard display filters file */
  GetCurrentDirectory(_MAX_PATH, Buffer);
  m_AppPath = Buffer;
  TerminatePathString(m_AppPath);

	/* Change the registry key under which our settings are stored. */
  SetRegistryKey(_T("UESP"));

	/* Load standard INI file options (including MRU) */
  LoadStdProfileSettings(); 

	/* Register document templates */
  CMultiDocTemplate* pDocTemplate;
  pDocTemplate = new CMultiDocTemplate(IDR_SREDITTYPE,
		RUNTIME_CLASS(CSrEditDoc),
		RUNTIME_CLASS(CChildFrame), /* Custom MDI child frame */
		RUNTIME_CLASS(CSrEditView));
  AddDocTemplate(pDocTemplate);

	/* Create main MDI Frame window */
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME)) return FALSE;
  m_pMainWnd   = pMainFrame;
  m_pMainFrame = pMainFrame;

  	/* Load the default config file */
  LoadOptions(SREDIT_OPTIONS_FILE);

	/* Change to the data file path */ /*
  Result = GetSrInstallPath(PathBuffer);

  if (Result) {
    PathBuffer += "data\\";
    SetCurrentDirectory(PathBuffer);
  } //*/

	/* Parse command line for standard shell commands, DDE, file open */
  CCommandLineInfo cmdInfo;
  cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
  ParseCommandLine(cmdInfo);

	/* Dispatch commands specified on the command line */
  if (!ProcessShellCommand(cmdInfo)) return FALSE;

	/* The main window has been initialized, so show and update it. */
  pMainFrame->ShowWindow(m_nCmdShow);
  pMainFrame->UpdateWindow();

	/* Display the about box initially if required */
  m_ConfigFile.GetBoolean(Result, "DisplayAboutOnLoad", true);
  if (Result) OnAppAbout();

  //SrLoadScriptFunctions("functions.dat");
  //SystemLog.Printf("Loaded %u functions...", Functions.GetNumFunctions());
  
	/* Resource handler and view initialization */
  //InitResourceHandler();
  //OpenResourceView();

  return TRUE;
}
/*===========================================================================
 *		End of Class Method CSrEditApp::InitInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - int ExitInstance ();
 *
 *=========================================================================*/
int CSrEditApp::ExitInstance() {
	extern long g_StringAllocations;
	SystemLog.Printf("TotalStringAllocations = %d", g_StringAllocations);

  CSrMultiRecordHandler::m_SkyrimMaster.Destroy();

  m_ResourceHandler.Destroy();
  m_BsaFiles.Destroy();

  return CWinApp::ExitInstance();
}
/*===========================================================================
 *		End of Class Method CSrEditApp::ExitInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Event - void OnAppAbout ();
 *
 * Application command to run the about dialog.
 *
 *=========================================================================*/
void CSrEditApp::OnAppAbout() {
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}
/*===========================================================================
 *		End of Class Event CSrEditApp::OnAppAbout()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Event - void OnFileOpen (void);
 *
 *=========================================================================*/
void CSrEditApp::OnFileOpen (void) 
{
  CSrProgressDlg*     pProgressDlg;
  CSrCallback	      LoadCallback;
  CDocument*	      pDocument;
  CSrLoadDlg          LoadDlg;
  srfileloadinfo_t*   pLoadInfo;
  CString	      Buffer;
  bool		      NotActive;
  int                 Result;
	
	/* Prompt the user to select the files */
  Result = LoadDlg.DoModal();
  if (Result != IDOK) return;

  pLoadInfo = &LoadDlg.GetLoadInfo();
  
	/* Initialize the progress dialog */
  pProgressDlg = ShowSrProgressDlg(_T("Loading Plugin"), _T("Loading..."));
  //pProgressDlg->SetCancelMsg(_T("Are you sure you wish to abort loading this plugin?"));
  LoadCallback.SetCallbackInterval(10000);
  LoadCallback.SetFunction(SrEditDefaultProgressCallback);
  LoadCallback.SetUserPtr((void *) pProgressDlg);
  LoadCallback.Reset();
	
  Buffer    = pLoadInfo->m_ActiveFilename;
  NotActive = Buffer.IsEmpty() != 0;
  if (NotActive) Buffer.Format(_T("noname%u"), m_NewFileIndex++);

	/* Load the file */
  m_pCurrentLoadInfo     = pLoadInfo;
  m_pCurrentProgressDlg  = pProgressDlg;
  m_pCurrentLoadCallback = &LoadCallback;

  pDocument = OpenDocumentFile(Buffer);

  m_pCurrentLoadInfo     = NULL;
  m_pCurrentProgressDlg  = NULL;
  m_pCurrentLoadCallback = NULL;

  DestroySrProgressDlg(pProgressDlg);

  if (pDocument == NULL) SrEditShowLastError(_T("Failed to load the requested plugin(s)!"));
}
/*===========================================================================
 *		End of Class Event CSrEditApp::OnFileOpen()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - CDocument* OpenDocumentFile (lpszFileName);
 *
 *=========================================================================*/
CDocument* CSrEditApp::OpenDocumentFile (LPCTSTR lpszFileName) 
{
  return CWinApp::OpenDocumentFile(lpszFileName, FALSE);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::OpenDocumentFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - bool LoadOptions (pFilename);
 *
 *=========================================================================*/
bool CSrEditApp::LoadOptions (const TCHAR* pFilename) 
{
  bool Result;

  Result = m_ConfigFile.Load(pFilename);
  if (!Result) return (false);

	/* Update all settings */
  UpdateOptions(false);
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::LoadOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - bool SaveOptions (pFilename);
 *
 *=========================================================================*/
bool CSrEditApp::SaveOptions (const TCHAR* pFilename) 
{
  bool Result;

  	/* Update all settings */
  UpdateOptions(false);

  Result = m_ConfigFile.Save(pFilename);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::SaveOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - void UpdateOptions (SetConfigFile);
 *
 * If Set is true the configfile values are updated from the option
 * data.
 *
 *=========================================================================*/
void CSrEditApp::UpdateOptions (const bool Set) 
{

	/* Record list options */
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableColors",		CSrRecordListCtrl::GetOptions().EnableColors);
  m_ConfigFile.UpdateBoolean(Set, "RecordListSaveState",		CSrRecordListCtrl::GetOptions().SaveState);

  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableActiveColor",	CSrRecordListCtrl::GetOptions().ActiveColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableDeletedColor",	CSrRecordListCtrl::GetOptions().DeletedColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableIgnoredColor",	CSrRecordListCtrl::GetOptions().IgnoredColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableDangerousColor",	CSrRecordListCtrl::GetOptions().DangerousColor.Enable);
  m_ConfigFile.UpdateBoolean(Set, "RecordListEnableQuestColor",		CSrRecordListCtrl::GetOptions().QuestColor.Enable);

  m_ConfigFile.UpdateInteger(Set, "RecordListActiveColorOrder",		CSrRecordListCtrl::GetOptions().ActiveColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListDeletedColorOrder",	CSrRecordListCtrl::GetOptions().DeletedColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListIgnoredColorOrder",	CSrRecordListCtrl::GetOptions().IgnoredColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListDangerousColorOrder",	CSrRecordListCtrl::GetOptions().DangerousColor.Order);
  m_ConfigFile.UpdateInteger(Set, "RecordListQuestColorOrder",		CSrRecordListCtrl::GetOptions().QuestColor.Order);

  m_ConfigFile.UpdateDword(Set, "RecordListActiveColor",		CSrRecordListCtrl::GetOptions().ActiveColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListDeletedColor",		CSrRecordListCtrl::GetOptions().DeletedColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListIgnoredColor",		CSrRecordListCtrl::GetOptions().IgnoredColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListDangerousColor",		CSrRecordListCtrl::GetOptions().DangerousColor.Color);
  m_ConfigFile.UpdateDword(Set, "RecordListQuestColor",			CSrRecordListCtrl::GetOptions().QuestColor.Color);

	/* Record tree options */
  m_ConfigFile.UpdateBoolean(Set, "RecordTreeEnableCounts", CSrRecordTreeCtrl::GetOptions().EnableCounts);
  m_ConfigFile.UpdateString (Set, "RecordTreeFilterFile",   CSrRecordTreeCtrl::GetOptions().FilterFile);
    
  	/* Undo options */
  m_ConfigFile.UpdateBoolean(Set, "EnableUndo", CSrMultiRecordHandler::GetOptions().Undo.EnableUndo);
  m_ConfigFile.UpdateDword  (Set, "UndoLimit",  CSrMultiRecordHandler::GetOptions().Undo.UndoLimit);

  	/* Backup options */
  m_ConfigFile.UpdateBoolean(Set, "EnableBackup",       CSrMultiRecordHandler::GetOptions().EnableBackup);
  m_ConfigFile.UpdateBoolean(Set, "EnableBackupOnSave", CSrMultiRecordHandler::GetOptions().EnableBackupOnSave);
  m_ConfigFile.UpdateInteger(Set, "MaximumBackupSize",  CSrMultiRecordHandler::GetOptions().MaxBackupSize);
  m_ConfigFile.UpdateInteger(Set, "MaximumBackupCount", CSrMultiRecordHandler::GetOptions().MaxBackupCount);
  m_ConfigFile.UpdateString (Set, "BackupPath",         CSrMultiRecordHandler::GetOptions().BackupPath);
  m_ConfigFile.UpdateBoolean(Set, "EnableAutoBackup",   CSrMultiRecordHandler::GetOptions().EnableAutoBackup);
  m_ConfigFile.UpdateInteger(Set, "AutoBackupTime",     CSrMultiRecordHandler::GetOptions().AutoBackupTime);

	/* Performance settings */
  m_ConfigFile.UpdateBoolean(Set, "EnableCaching",     CSrMultiRecordHandler::GetOptions().EnableCaching);

	/* Dialog options */
  m_ConfigFile.UpdateBoolean(Set, "EnableWebHelp",   CSrEditDlgHandler::GetOptions().EnableWebHelp);
  m_ConfigFile.UpdateBoolean(Set, "UseUESPWikiHelp", CSrEditDlgHandler::GetOptions().UseUESPWikiHelp);
  m_ConfigFile.UpdateString(Set,  "CSWikiPrefix",    CSrEditDlgHandler::GetOptions().CSWikiPrefix);
  m_ConfigFile.UpdateString(Set,  "UESPWikiPrefix",  CSrEditDlgHandler::GetOptions().UESPWikiPrefix);
  m_ConfigFile.UpdateString(Set,  "DefaultCSPage",   CSrEditDlgHandler::GetOptions().DefaultCSPage);
  m_ConfigFile.UpdateString(Set,  "DefaultUESPPage", CSrEditDlgHandler::GetOptions().DefaultUESPPage);

  m_ConfigFile.UpdateString (Set, "SkyrimInstallPath",  g_SrManualInstallPath);
  g_SrManualInstallPath.Trim();

		/* Language/string file options */
  m_ConfigFile.UpdateString(Set, "StringFileLanguage", g_SrLanguage);

		/* File/path options */
  CSString Value;
  int      Position;

  if (!Set)
  {
	  bool Result = m_ConfigFile.FindFirst(Value, "ExtraLoadPath", Position);
	  CSrLoadDlg::s_ExtraFilePaths.RemoveAll();

	  while (Result)
	  {
		  CSrLoadDlg::s_ExtraFilePaths.Add(Value.c_str());
		  Result = m_ConfigFile.FindNext(Value, "ExtraLoadPath", Position);
	  }
  }

		/* Script options */
  //m_ConfigFile.UpdateString (Set, "ScriptFontName", CSrScptView::m_Options.FontName);
  //m_ConfigFile.UpdateInteger(Set, "ScriptFontSize", CSrScptView::m_Options.FontSize);
  //m_ConfigFile.UpdateDword  (Set, "ScriptForeColor[]", CSrScptView::m_Options.DefaultForeColor);
  //m_ConfigFile.UpdateDword  (Set, "ScriptBackColor[]", CSrScptView::m_Options.DefaultBackColor);
  //m_ConfigFile.UpdateInteger(Set, "ScriptTabSize", CSrScptView::m_Options.TabSize);
  //UpdateScriptErrorOptions(Set);

	/* Force a redraw */
  if (!Set) 
  {
    ResolveOptionPaths();

    CWnd* pWnd = AfxGetMainWnd();
    if (pWnd != NULL) pWnd->RedrawWindow();
  }

}
/*===========================================================================
 *		End of Class Method CSrEditApp::UpdateOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - void UpdateScriptColorOptions (Compiler, Set);
 *
 *=========================================================================*/
/*
void CSrEditApp::UpdateScriptColorOptions (CCustomCompiler& Compiler, const bool Set) {
  CTokenTypeArray* pTokens = &Compiler.GetTokenTypes();
  CSString         Buffer;
  CTokenType*      pToken;
  dword            Index;
  bool             Result;

  for (Index = 0; Index < pTokens->GetNumRecords(); ++Index) {
    pToken = pTokens->GetRecord(Index);

    Buffer.Format("ScriptForeColor[%s]", pToken->GetName());
    Result = m_ConfigFile.UpdateDword(Set, Buffer, pToken->GetForeColorRef());
    if (!Result && Set) pToken->GetForeColorRef() = CSrScptView::m_Options.DefaultForeColor;

    Buffer.Format("ScriptBackColor[%s]", pToken->GetName());
    Result = m_ConfigFile.UpdateDword(Set, Buffer, pToken->GetBackColorRef());
    if (!Result && Set) pToken->GetBackColorRef() = CSrScptView::m_Options.DefaultBackColor;
  }

} */
/*===========================================================================
 *		End of Class Method CSrEditApp::UpdateScriptColorOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - void UpdateScriptErrorOptions (Set);
 *
 *=========================================================================*/
/*
void CSrEditApp::UpdateScriptErrorOptions (const bool Set) {
  CString Buffer;
  dword   Index;

  for (Index = 0; g_ObScriptErrorDefs[Index].pName != NULL; ++Index) {
    Buffer.Format("ScriptError[%s]", g_ObScriptErrorDefs[Index].pName);
    m_ConfigFile.UpdateInteger(Set, Buffer, g_ObScriptErrorDefs[Index].Level);
  }

}*/
/*===========================================================================
 *		End of Class Method CSrEditApp::UpdateScriptErrorOptions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - void ResolveOptionPaths (void);
 *
 *=========================================================================*/
void CSrEditApp::ResolveOptionPaths (void) {
  char  Buffer[_MAX_PATH + 8];
  dword Result;
  bool  HasPath = false;

  if (CSrMultiRecordHandler::GetOptions().BackupPath[0] != '\\' &&
      CSrMultiRecordHandler::GetOptions().BackupPath[1] != ':') {

    Result = GetSrInstallPath(CSrMultiRecordHandler::GetOptions().FullBackupPath);

    if (Result) {
      CSrMultiRecordHandler::GetOptions().FullBackupPath += "data\\";
      CSrMultiRecordHandler::GetOptions().FullBackupPath += CSrMultiRecordHandler::GetOptions().BackupPath;
      TerminatePathString(CSrMultiRecordHandler::GetOptions().FullBackupPath);
      HasPath = true;
    }
  }

  if (!HasPath) {
    Result = GetFullPathName(CSrMultiRecordHandler::GetOptions().BackupPath, _MAX_PATH, Buffer, NULL);

    if (Result)
      CSrMultiRecordHandler::GetOptions().FullBackupPath = Buffer;
    else
      CSrMultiRecordHandler::GetOptions().FullBackupPath = CSrMultiRecordHandler::GetOptions().BackupPath;
  }

	/* Create the fulll display filter path */
  CSrRecordTreeCtrl::GetOptions().FullFilterFile  = m_AppPath;
  CSrRecordTreeCtrl::GetOptions().FullFilterFile += CSrRecordTreeCtrl::GetOptions().FilterFile;

  SystemLog.Printf("Full backup path: %s", CSrMultiRecordHandler::GetOptions().FullBackupPath.c_str());
}
/*===========================================================================
 *		End of Class Method CSrEditApp::ResolveOptionPaths()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Event - bool OpenWebHelp (pPage);
 *
 *=========================================================================*/
bool CSrEditApp::OpenWebHelp (const char* pPage)
{
  CSString	 Buffer;

	/* Ignore if web help is disabled */
  if (!CSrEditDlgHandler::GetOptions().EnableWebHelp) return (false);
  
  if (CSrEditDlgHandler::GetOptions().UseUESPWikiHelp) {
    Buffer = CSrEditDlgHandler::GetOptions().UESPWikiPrefix;
    if (pPage == NULL) pPage = CSrEditDlgHandler::GetOptions().DefaultUESPPage;
   }
  else {
    Buffer = CSrEditDlgHandler::GetOptions().CSWikiPrefix;
    if (pPage == NULL) pPage = CSrEditDlgHandler::GetOptions().DefaultCSPage;
  }
 
  if (pPage != NULL) Buffer += pPage;
  OpenWebPage(Buffer);
  return (true);
}


bool CSrEditApp::OpenWebHelp (const char* pUESPPage, const char* pCSPage)
{
	CSString	 Buffer;

	if (!CSrEditDlgHandler::GetOptions().EnableWebHelp) return (false);

	if (CSrEditDlgHandler::GetOptions().UseUESPWikiHelp) 
	{
		Buffer = CSrEditDlgHandler::GetOptions().UESPWikiPrefix;
		if (pUESPPage == NULL) pUESPPage = CSrEditDlgHandler::GetOptions().DefaultUESPPage;
		if (pUESPPage != NULL) Buffer += pUESPPage;
	}
	else 
	{
		Buffer = CSrEditDlgHandler::GetOptions().CSWikiPrefix;
		if (pCSPage == NULL) pCSPage = CSrEditDlgHandler::GetOptions().DefaultCSPage;
		if (pCSPage != NULL) Buffer += pCSPage;
	}
 
	OpenWebPage(Buffer);
	return true;
}

/*===========================================================================
 *		End of Class Event CSrEditApp::OpenWebHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - CFrameWnd* FindResourceView (void);
 *
 *=========================================================================*/
CFrameWnd* CSrEditApp::FindResourceView (void) {
  CWnd* pWnd;
  CWnd* pWnd1;
  HWND  hWnd;

  hWnd = GetWindow(m_pMainFrame->m_hWndMDIClient, GW_CHILD);

  while (hWnd != NULL) {
    pWnd = CWnd::FromHandle(hWnd);

    if (pWnd != NULL) {
      pWnd1 = pWnd->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);

      if (pWnd1 != NULL && pWnd1->IsKindOf(RUNTIME_CLASS(CSrResourceView))) {
        if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) return (CFrameWnd *) pWnd;
      }
    }
   
    hWnd = GetWindow(hWnd, GW_HWNDNEXT);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::FindResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - void OpenResourceView (pResource);
 *
 *=========================================================================*/
void CSrEditApp::OpenResourceView (const char* pResource) {
  CSrResourceView* pView;
  
  pView = OpenResourceView();
  if (pView == NULL) return;

  pView->SelectResource(pResource);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::OpenResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - CSrResourceView* CreateResourceView (void);
 *
 *=========================================================================*/
CSrResourceView* CSrEditApp::CreateResourceView (void) {
  CSrResourceView* pView;
  CCreateContext   Context;
  CFrameWnd*       pFrame;
  CWnd*			   pWnd;

  if (m_pCurrentProgressDlg == NULL) {
    m_pCurrentProgressDlg = ShowSrProgressDlg(_T("Resource Viewer"), _T("Initializing Resources..."));
    m_pCurrentProgressDlg->Update(50);
  }

	/* Initialize the context structure */
  Context.m_pCurrentDoc     = NULL;
  Context.m_pCurrentFrame   = NULL;
  Context.m_pNewDocTemplate = NULL;
  Context.m_pLastView       = NULL;
  Context.m_pNewViewClass   = RUNTIME_CLASS(CSrResourceView);

	/* Create the dialog parent frame */  
  pFrame = (CFrameWnd *) RUNTIME_CLASS(CChildFrame)->CreateObject();
  ASSERT_KINDOF(CFrameWnd, pFrame);

	/* Create new form view from resource */
  pFrame->LoadFrame(IDD_RESOURCE_VIEW, WS_OVERLAPPEDWINDOW, m_pMainWnd, &Context);

  	/* Attempt to initialize the new view */
  pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);

  if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CSrResourceView))) {
    pView = (CSrResourceView *) pWnd;
    pView->SetResourceHandler(&m_ResourceHandler);
    pView->SetBsaFileArray(&m_BsaFiles);
  }
  
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(75);

  pFrame->InitialUpdateFrame(NULL, TRUE);
  pFrame->ActivateFrame(SW_SHOWNORMAL);
  pFrame->SetWindowText(_T("Resource Viewer"));

  return (pView);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::CreateResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - CSrResourceView* OpenResourceView (void);
 *
 *=========================================================================*/
CSrResourceView* CSrEditApp::OpenResourceView (void) {
  CSrResourceView* pView = NULL;
  CFrameWnd*       pFrame;
  CWnd*            pWnd;
  
	/* Force the initialization of the resource handler if required */
  if (!m_InitResourceHandler) {
    m_pCurrentProgressDlg = ShowSrProgressDlg(_T("Resource Viewer"), _T("Initializing Resources..."));
    m_pCurrentProgressDlg->Update(0);
    
    InitResourceHandler();
  }

	/* Find an already open view */
  pFrame = FindResourceView();

  if (pFrame != NULL) {
    pFrame->ActivateFrame(SW_RESTORE);

    pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
    if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CSrResourceView))) pView = (CSrResourceView *) pWnd;
  }
  else {
    pView = CreateResourceView();
  }

  if (m_pCurrentProgressDlg) {
    DestroySrProgressDlg(m_pCurrentProgressDlg);
    m_pCurrentProgressDlg = NULL;
  }

  return (pView);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::OpenResourceView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - bool InitResourceHandler (void);
 *
 *=========================================================================*/
bool CSrEditApp::InitResourceHandler (void) {
  CSString        Buffer;
  CSString        Buffer1;
  CSString        Filename;
  srtimer_t       Timer;
  bool            Result;

	/* Clear any current content */
  m_BsaFiles.Destroy();
  m_ResourceHandler.Destroy();
  m_InitResourceHandler = false;

	/* Get the current Oblivion path */
  Result = GetSrInstallPath(Buffer);
  if (!Result) return AddSrGeneralError("Failed to find the Skyrim install path!");

  Buffer += "data\\";
  m_ResourceHandler.SetBasePath(Buffer);

	/* Add files in the data file path */  
  SrStartTimer(Timer);
 
  m_ResourceHandler.AddPathContents(Buffer, false);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(10);
  
  SrEndTimer(Timer, "Added resource \\data path contents in ");

		/* Add known BSA files for now */
  Filename = Buffer + "Skyrim - Animations.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(20);

  Filename = Buffer + "Skyrim - Interfaces.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(30);
    
  Filename = Buffer + "Skyrim - Misc.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(40);

  Filename = Buffer + "Skyrim - Meshes.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(50);

  Filename = Buffer + "Skyrim - Sounds.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(60);

  Filename = Buffer + "Skyrim - Shaders.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(70);

  Filename = Buffer + "Skyrim - Textures.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(80);

  Filename = Buffer + "Skyrim - Voices.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(90);

  Filename = Buffer + "Skyrim - VoicesExtra.bsa";
  AddBsaFile(Filename);
  if (m_pCurrentProgressDlg) m_pCurrentProgressDlg->Update(95);
  
  m_InitResourceHandler = true;
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::InitResourceHandler()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - bool AddBsaFile (pFilename);
 *
 *=========================================================================*/
bool CSrEditApp::AddBsaFile (const char* pFilename) {
  CSrBsaFile* pBsaFile;
  bool        Result;
  srtimer_t   Timer;

  pBsaFile = new CSrBsaFile;
  m_BsaFiles.Add(pBsaFile);

  SrStartTimer(Timer);
  Result = pBsaFile->Load(pFilename);
  SrEndTimer(Timer, "Loaded BSA file in ");

  if (!Result) {
    m_BsaFiles.Delete(pBsaFile);
    return (false);
  }

  SrStartTimer(Timer);
  m_ResourceHandler.AddBsaFile(pBsaFile);
  SrEndTimer(Timer, "Added BSA records in ");
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditApp::AddBsaFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditApp Method - void ResetListState (void);
 *
 *=========================================================================*/
void CSrEditApp::ResetListState (void) {
  CString Section;
  dword   Result;

  Result = MessageBox(NULL, "This action will delete the state and restore all lists in SkyEdit to their default settings.\r\nAre you sure you wish to proceed?", "Reset List State", MB_YESNO | MB_ICONQUESTION);
  if (Result != IDYES) return;

	/* The registry section to delete */
  Section.Format("%s%s\\", SREDIT_REGISTRY_BASE, SRRL_REGKEY_ROOT);

  Result = SHDeleteKey(HKEY_CURRENT_USER, Section);

  if (Result != ERROR_SUCCESS) {
    AddSrWindowsError("Failed to delete the registry section '%s' and all its sub-keys!", Section);
  }
	
}
/*===========================================================================
 *		End of Class Method CSrEditApp::ResetListState()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CSrEditApp& GetSrEditApp (void);
 *
 *=========================================================================*/
CSrEditApp& GetSrEditApp (void) {
  return theApp;
}


CSrConfigFile& GetSrEditConfigFile (void) {
  return theApp.GetConfigFile();
}
/*===========================================================================
 *		End of Function GetSrEditApp()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrEditShowError (Flags, pTitle, pString, ...);
 *
 * Displays a modal error dialog showing error message. Returns false.
 *
 *=========================================================================*/
bool SrEditShowError (const dword Flags, const TCHAR* pTitle, const TCHAR* pString, ...) {
  CSrErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(Flags);
  ErrorDlg.SetTitle(pTitle);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}


bool SrEditShowError (const TCHAR* pTitle, const TCHAR* pString, ...) {
  CSrErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(OBERRDLG_SHOWUNTAGGEDERRORS);
  ErrorDlg.SetTitle(pTitle);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}


bool SrEditShowError (const TCHAR* pString, ...) {
  CSrErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(OBERRDLG_SHOWUNTAGGEDERRORS);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}


bool SrEditShowLastError (const TCHAR* pString, ...) {
  CSrErrorDlg ErrorDlg;
  CString     Buffer;
  va_list     Args;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);

  ErrorDlg.SetFlags(0);
  ErrorDlg.SetMessage(Buffer);

  ErrorDlg.DoModal();

  return (false);
}
/*===========================================================================
 *		End of Function SrEditShowError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void WINAPI SetInternalWindowText (hwnd, lpText);
 *
 *=========================================================================*/
void WINAPI SetInternalWindowText(HWND hwnd, LPCTSTR lpText) {

	/* Turn off WS_VISIBLE if necessary to avoid painting */
  DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
  if (dwStyle & WS_VISIBLE) ::SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_VISIBLE);
    
	/* Call DefWindowProc directly to set internal window text */
  DefWindowProc(hwnd, WM_SETTEXT, 0, (LPARAM)lpText);

	/* Restore parent visible state */
  if (dwStyle & WS_VISIBLE) ::SetWindowLong(hwnd, GWL_STYLE, dwStyle);
 }
/*===========================================================================
 *		End of Function WINAPI SetInternalWindowText()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool OpenWebPage (pAddress);
 *
 *=========================================================================*/
bool OpenWebPage (const char* pAddress) {
  BOOL		   Result;
  SHELLEXECUTEINFO ShellInfo;

	/* Initialize the shellinfo structure */
  ShellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
  ShellInfo.fMask  = SEE_MASK_NOCLOSEPROCESS;
  ShellInfo.hwnd   = NULL;
  ShellInfo.lpFile = pAddress;
  ShellInfo.lpVerb = _T("open");
  ShellInfo.lpClass      = NULL;
  ShellInfo.lpDirectory  = NULL;
  ShellInfo.lpIDList     = NULL;
  ShellInfo.lpParameters = NULL;
  ShellInfo.nShow        = SW_SHOWNORMAL;

	/* Attempt to open the file/page */
  Result = ShellExecuteEx(&ShellInfo);
  if (!Result) return (false);
    
  //hResult = ShellExecute (NULL, _T("open"), pSiteAddress, NULL, NULL, SW_SHOWNORMAL); 
  return (true);
}
/*===========================================================================
 *		End of Function OpenWebPage()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void SrLockUndoUpdates (Lock);
 *
 *=========================================================================*/
void SrLockUndoUpdates (const bool Lock) {
  theApp.GetMainWnd()->SendMessage(SRE_MSG_LOCKUNDO, (int)Lock, 0);
}
/*===========================================================================
 *		End of Function SrLockUndoUpdates()
 *=========================================================================*/


void SrGlobClipAddCondition (srconditioninfo_t* pCondition, const bool Clear)
{
	if (Clear) g_GlobClipConditions.Destroy();
	if (pCondition == NULL) return;
	g_GlobClipConditions.AddNew()->Copy(*pCondition);
}


void SrGlobClipClearConditions (void)
{
	g_GlobClipConditions.Destroy();
}


CSrConditionArray& SrGlobClipGetConditions (void)
{
	return g_GlobClipConditions;
}