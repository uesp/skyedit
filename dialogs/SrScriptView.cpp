#include "stdafx.h"
#include "resource.h"
#include "sredit.h"
#include "dialogs\SrScriptView.h"
#include "common\srutils.h"
#include "SrProgressDlg.h"
#include "SrScriptPropertyDlg.h"


srscriptoptions_t CSrScriptView::s_ScriptOptions = { "-f=TESV_Papyrus_Flags.flg", "Consolas", 90, 5 };


IMPLEMENT_DYNCREATE(CSrScriptView, CFormView)


BEGIN_MESSAGE_MAP(CSrScriptView, CFormView)
	ON_WM_INITMENUPOPUP()
	ON_LBN_SELCHANGE(IDC_SCRIPT_LIST, &CSrScriptView::OnLbnSelchangeScriptList)
	ON_WM_SIZE()
	ON_COMMAND(ID_SCRIPT_NEW, &CSrScriptView::OnScriptNew)
	ON_COMMAND(ID_SCRIPT_LOAD, &CSrScriptView::OnScriptLoad)
	ON_COMMAND(ID_SCRIPT_REMOVE, &CSrScriptView::OnScriptRemove)
	ON_COMMAND(ID_SCRIPT_SAVE, &CSrScriptView::OnScriptSave)
	ON_COMMAND(ID_SCRIPT_SAVEAS, &CSrScriptView::OnScriptSaveAs)
	ON_COMMAND(ID_SCRIPT_COMPILE, &CSrScriptView::OnScriptCompile)
	ON_UPDATE_COMMAND_UI(ID_SCRIPT_DELETE, &CSrScriptView::OnUpdateScriptExists)
	ON_UPDATE_COMMAND_UI(ID_SCRIPT_COMPILE, &CSrScriptView::OnUpdateScriptExists)
	ON_BN_CLICKED(IDC_LOADSCRIPT, &CSrScriptView::OnBnClickedLoadscript)
	ON_BN_CLICKED(IDC_NEWSCRIPT, &CSrScriptView::OnBnClickedNewscript)
	ON_BN_CLICKED(IDC_COMPILESCRIPT, &CSrScriptView::OnBnClickedCompilescript)
	ON_BN_CLICKED(IDC_SAVESCRIPT, &CSrScriptView::OnBnClickedSavescript)
	ON_BN_CLICKED(IDC_SAVEASSCRIPT, &CSrScriptView::OnBnClickedSaveasscript)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_SCRIPTTEXTMENU_UNDO, &CSrScriptView::OnScripttextmenuUndo)
	ON_COMMAND(ID_SCRIPTTEXTMENU_CUT, &CSrScriptView::OnScripttextmenuCut)
	ON_COMMAND(ID_SCRIPTTEXTMENU_COPY, &CSrScriptView::OnScripttextmenuCopy)
	ON_COMMAND(ID_SCRIPTTEXTMENU_PASTE, &CSrScriptView::OnScripttextmenuPaste)
	ON_UPDATE_COMMAND_UI(ID_SCRIPTTEXTMENU_UNDO, &CSrScriptView::OnUpdateScriptTextUndo)
	ON_UPDATE_COMMAND_UI(ID_SCRIPTTEXTMENU_CUT, &CSrScriptView::OnUpdateScriptTextCut)
	ON_UPDATE_COMMAND_UI(ID_SCRIPTTEXTMENU_COPY, &CSrScriptView::OnUpdateScriptTextCopy)
	ON_UPDATE_COMMAND_UI(ID_SCRIPTTEXTMENU_PASTE, &CSrScriptView::OnUpdateScriptTextPaste)
	ON_COMMAND(ID_SCRIPTTEXTACC_UNDO, &CSrScriptView::OnScripttextaccUndo)
	ON_COMMAND(ID_SCRIPTTEXTACC_CUT, &CSrScriptView::OnScripttextaccCut)
	ON_COMMAND(ID_SCRIPTTEXTACC_COPY, &CSrScriptView::OnScripttextaccCopy)
	ON_COMMAND(ID_SCRIPTTEXTACC_PASTE, &CSrScriptView::OnScripttextaccPaste)
	ON_WM_GETDLGCODE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SCRIPTLISTMENU_TESTTOKENS, &CSrScriptView::OnScriptlistmenuTesttokens)
	ON_COMMAND(ID_SCRIPTLISTMENU_TESTPROPERTIES, &CSrScriptView::OnScriptlistmenuTestproperties)
END_MESSAGE_MAP()


CSrScriptView::CSrScriptView()
	: CFormView(CSrScriptView::IDD)
{
	m_pCurrentScript = NULL;
	m_pErrorView     = NULL;

	m_hCompileStdInWrite = NULL;
	m_hCompileStdOutWrite = NULL;
	m_hCompileStdInRead = NULL;
	m_hCompileStdOutRead = NULL;

	m_ScriptFont.CreatePointFont(s_ScriptOptions.FontSize, s_ScriptOptions.FontName);
	m_hAccelerator = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_SCRIPTTEXT_ACCEL));
}


CSrScriptView::~CSrScriptView()
{
}


void CSrScriptView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCRIPT_TEXT, m_ScriptText);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_ScriptList);
}


#ifdef _DEBUG
	void CSrScriptView::AssertValid() const { CFormView::AssertValid(); }
	void CSrScriptView::Dump(CDumpContext& dc) const { CFormView::Dump(dc); }
#endif


bool CSrScriptView::AddScript (const char* pFilename)
{
	CSString Filename;

	if (pFilename == NULL) return false;

	GetSrInstallPath(Filename);
	Filename += "data\\scripts\\source\\";
	Filename += pFilename;

	return AddScriptAbsPath(Filename);
}


bool CSrScriptView::AddScriptAbsPath (const char* pFilename)
{
	CSrScriptFile* pInfo;
	bool           Result;

	pInfo = FindScript(pFilename);

	if (pInfo != NULL)
	{
		SetCurrentScript(pInfo);
		return true;
	}

	CSrScriptFile* pNewScript = m_Scripts.AddNew();

	Result = pNewScript->Load(pFilename);
	if (!Result) return SrEditShowError("Failed to load script file '%s'!", pFilename);
	
	SetCurrentScript(pNewScript);
	FillScriptList();
	return true;
}


bool CSrScriptView::AddScriptFromData (const char* pFilename)
{
	CSString Filename;

	if (pFilename == NULL) return false;

	GetSrInstallPath(Filename);
	Filename += "data\\";
	Filename += pFilename;

	return AddScriptAbsPath(Filename);
}


void CSrScriptView::SetCurrentScript (CSrScriptFile* pScript)
{
	GetControlData();

	m_pCurrentScript = pScript;

	SetControlData();
}


CSrScriptFile* CSrScriptView::FindScript (const char* pFilename)
{
	if (pFilename == NULL) return NULL;

	for (dword i = 0; i < m_Scripts.GetSize(); ++i)
	{
		if (m_Scripts[i]->IsFilename(pFilename)) return m_Scripts[i];
	}

	return NULL;
}


CSrScriptFile* CSrScriptView::FindScriptName (const char* pScriptName)
{
	if (pScriptName == NULL) return NULL;

	for (dword i = 0; i < m_Scripts.GetSize(); ++i)
	{
		if (m_Scripts[i]->IsScriptName(pScriptName)) return m_Scripts[i];
	}

	return NULL;
}


void CSrScriptView::FillScriptList (void)
{
	int ListIndex;

	m_ScriptList.SetRedraw(false);
	m_ScriptList.ResetContent();

	for (dword i = 0; i < m_Scripts.GetSize(); ++i)
	{
		ListIndex = AddScriptList(m_Scripts[i]);
		
		if (m_pCurrentScript == m_Scripts[i]) m_ScriptList.SetCurSel(ListIndex);
	}

	m_ScriptList.SetRedraw(true);	
}


int CSrScriptView::AddScriptList (CSrScriptFile* pScript)
{
	CString Buffer;
	int     ListIndex;

	Buffer = MakeScriptName(pScript);	

	ListIndex = m_ScriptList.AddString(Buffer);
	if (ListIndex >= 0) m_ScriptList.SetItemDataPtr(ListIndex, pScript);

	return ListIndex;
}


CString CSrScriptView::MakeScriptName (CSrScriptFile* pScript)
{
	CString Buffer;

	if (pScript == NULL) return Buffer;

	if (pScript->HasScriptName())
	{
		Buffer.Format("%s%s", pScript->IsModified() ? "*" : "", pScript->GetScriptName());
	}
	else
	{
		Buffer.Format("%s<newscript>", pScript->IsModified() ? "*" : "");		
	}

	return Buffer;
}


void CSrScriptView::UpdateScriptList (const int ListIndex, CSrScriptFile* pScript)
{
	CString Buffer;
	int     SelIndex = m_ScriptList.GetCurSel();
	if (ListIndex < 0 || pScript == NULL) return;

	Buffer = MakeScriptName(pScript);

	m_ScriptList.DeleteString(ListIndex);
	m_ScriptList.InsertString(ListIndex, Buffer);
	m_ScriptList.SetItemDataPtr(ListIndex, pScript);
	if (SelIndex == ListIndex) m_ScriptList.SetCurSel(SelIndex);
}


void CSrScriptView::UpdateScriptList (CSrScriptFile* pUpdateScript)
{
	if (m_pCurrentScript == NULL) return;
	
	for (int i = 0; i < m_ScriptList.GetCount(); ++i)
	{
		CSrScriptFile* pScript = (CSrScriptFile *) m_ScriptList.GetItemDataPtr(i);

		if (pScript == pUpdateScript)
		{
			UpdateScriptList(i, m_pCurrentScript);
			break;
		}
	}
	
}


void CSrScriptView::UpdateCurrentScriptList (void)
{
	if (m_pCurrentScript == NULL) return;
	
	for (int i = 0; i < m_ScriptList.GetCount(); ++i)
	{
		CSrScriptFile* pScript = (CSrScriptFile *) m_ScriptList.GetItemDataPtr(i);

		if (pScript == m_pCurrentScript)
		{
			UpdateScriptList(i, m_pCurrentScript);
			break;
		}
	}
	
}


void CSrScriptView::GetControlData (void)
{
	CString Buffer;

	if (m_pCurrentScript == NULL) return;

	m_ScriptText.GetWindowTextA(Buffer);
	m_pCurrentScript->SetScriptText(Buffer);
	if (!m_pCurrentScript->IsModified()) m_pCurrentScript->SetIsModified(m_ScriptText.GetModify() != FALSE);

	m_ScriptText.SetModify(false);

	UpdateCurrentScriptList();
}


void CSrScriptView::SetControlData (void)
{
	if (m_pCurrentScript == NULL) 
	{
		m_ScriptText.SetWindowTextA("");
		m_ScriptText.EnableWindow(false);
		m_ScriptText.SetModify(false);
		return;
	}

	m_ScriptText.EnableWindow(true);

	m_ScriptText.SetWindowTextA(m_pCurrentScript->GetScriptText());
	m_ScriptText.SetModify(false);
}


void CSrScriptView::OnLbnSelchangeScriptList()
{
	int ListIndex = m_ScriptList.GetCurSel();
	if (ListIndex < 0) return;

	CSrScriptFile* pScript = (CSrScriptFile *) m_ScriptList.GetItemDataPtr(ListIndex);
	if (pScript == NULL) return;

	SetCurrentScript(pScript);
}


void CSrScriptView::OnSize(UINT nType, int cx, int cy)
{
	static const int LISTWIDTH = 180;
	static const int TOPMARGIN = 25;

	CFormView::OnSize(nType, cx, cy);

	CRect ClientRect;
	GetClientRect(&ClientRect);

	cx = ClientRect.Width();
	cy = ClientRect.Height();

	if (IsWindow(m_ScriptList.m_hWnd)) 
	{
		m_ScriptList.SetWindowPos(NULL, -2, TOPMARGIN, LISTWIDTH, cy - TOPMARGIN + 2, SWP_NOZORDER);
	}

	if (IsWindow(m_ScriptText.m_hWnd)) 
	{
		m_ScriptText.SetWindowPos(NULL, LISTWIDTH, TOPMARGIN, cx - LISTWIDTH + 2, cy - TOPMARGIN + 2, SWP_NOZORDER);
	}
}


void CSrScriptView::SetupScriptTabs (void)
{
	m_ScriptText.SetSel(0, -1);

	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);
	pf.dwMask = PFM_TABSTOPS;
	pf.cTabCount = MAX_TAB_STOPS;
	
	for (int i = 0; i < pf.cTabCount; i++)
	{
		pf.rgxTabs[i] = (i + 1) * 100 * s_ScriptOptions.TabSize;
	}

	m_ScriptText.SetParaFormat(pf);
}


void CSrScriptView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0,0));

	m_ScriptText.LimitText(10000000);
	m_ScriptText.SetEventMask(m_ScriptText.GetEventMask() | ENM_SELCHANGE | ENM_CHANGE);
	m_ScriptText.SetFont(&m_ScriptFont);
	m_ScriptText.SetFocus();
	SetupScriptTabs();
	
	m_CompileSecurityAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	m_CompileSecurityAttr.bInheritHandle = TRUE; 
	m_CompileSecurityAttr.lpSecurityDescriptor = NULL; 

	SetControlData();
}


void CSrScriptView::OnScriptNew()
{
	CSrScriptFile* pNewScript = m_Scripts.AddNew();
	pNewScript->SetIsModified(true);
	
	SetCurrentScript(pNewScript);
	m_ScriptList.SetCurSel(AddScriptList(pNewScript));
}


void CSrScriptView::OnScriptLoad()
{
	CFileDialog Dlg(TRUE, ".psc", "", OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, SR_SCRIPTFILE_FILTER, this);

	int Result = Dlg.DoModal();
	if (Result != IDOK) return;

	CString Filename = Dlg.GetPathName();

	CSrScriptFile* pNewScript = new CSrScriptFile;
	
	bool fResult = pNewScript->Load(Filename);

	if (!fResult)
	{
		delete pNewScript;
		SrEditShowError("Failed to load script file '%s'!", Filename);
		return;
	}

	pNewScript->SetIsModified(false);
	m_Scripts.Add(pNewScript);

	SetCurrentScript(pNewScript);
	m_ScriptList.SetCurSel(AddScriptList(pNewScript));
}


bool CSrScriptView::SaveScript (CSrScriptFile* pScript)
{
	CString Filename;
	bool    Result;

	if (pScript == NULL) return false;

	if (!pScript->HasScriptName())
	{
		CFileDialog Dlg(FALSE, ".psc", pScript->GetFilename(), OFN_OVERWRITEPROMPT, SR_SCRIPTFILE_FILTER, this);
		if (Dlg.DoModal() != IDOK) return false;

		Filename = Dlg.GetPathName();
		Result = pScript->Save(Filename);
	}
	else
	{
		Filename = pScript->GetFilename();
		Result = pScript->Save();
	}

	if (!Result) 
	{
		SrEditShowError("Failed to save script file '%s'!", Filename);
		return false;
	}

	pScript->SetIsModified(false);
	UpdateScriptList(pScript);
	return true;
}


bool CSrScriptView::SaveCurrentScript (void)
{
	GetControlData();
	return SaveScript(m_pCurrentScript);
}


void CSrScriptView::OnScriptSave()
{
	SaveCurrentScript();
}


void CSrScriptView::OnScriptSaveAs()
{
	CFileDialog Dlg(FALSE, ".psc", m_pCurrentScript->GetFilename(), OFN_OVERWRITEPROMPT, SR_SCRIPTFILE_FILTER, this);
	if (Dlg.DoModal() != IDOK) return;

	bool Result = m_pCurrentScript->Save(Dlg.GetPathName());
	if (!Result) SrEditShowError("Failed to save script file '%s'!", Dlg.GetPathName());
}


void CSrScriptView::OnScriptRemove()
{
	int ListIndex = m_ScriptList.GetCurSel();
	if (ListIndex < 0) return;

	GetControlData();
	
	if (m_pCurrentScript->IsModified())
	{
		CString Buffer;
		Buffer.Format("Script '%s' has not been saved. Do you wish to save now?", m_pCurrentScript->GetScriptName());

		int Result = AfxMessageBox(Buffer, MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (Result == IDCANCEL) return;

		if (Result == IDYES)
		{
			if (!SaveCurrentScript()) return;
		}
	}

	m_pCurrentScript = NULL;
	m_ScriptList.DeleteString(ListIndex);
	m_Scripts.Delete(ListIndex);

	if (ListIndex > 0)
		m_ScriptList.SetCurSel(ListIndex - 1);
	else
		m_ScriptList.SetCurSel(0);

	ListIndex = m_ScriptList.GetCurSel();

	if (ListIndex < 0) 
	{
		SetCurrentScript(NULL);
		return;
	}

	SetCurrentScript((CSrScriptFile *) m_ScriptList.GetItemDataPtr(ListIndex));
}


bool CSrScriptView::SaveExistingScript (void)
{

	if (m_pCurrentScript->HasScriptName())
	{
		if (!m_pCurrentScript->IsModified()) return true;
		return SaveCurrentScript();
	}	
	
	AddSrGeneralError("No script file to compile!");
	SrEditShowError("Scripts must be saved before compiling!");
	return false;
}


CString CSrScriptView::CreateCompilerCommand (CSrScriptFile* pScript)
{
	CString  Cmd;
	CSString InstallPath;

	if (pScript == NULL) return Cmd;

	GetSrInstallPath(InstallPath);

	Cmd = InstallPath;
	Cmd += "Papyrus Compiler\\PapyrusCompiler.exe ";
	Cmd += pScript->GetFilename();
	Cmd += " -i=";
	Cmd += InstallPath;
	Cmd += "data\\scripts\\source\\ ";
	Cmd += s_ScriptOptions.CompilerCmdOptions;
	Cmd += " -o=";
	Cmd += InstallPath;
	Cmd += "data\\scripts\\";

	return Cmd;
}


bool CSrScriptView::CreateCompilerPipes (void)
{
	BOOL Result;

	CloseHandle(m_hCompileStdInWrite);
	CloseHandle(m_hCompileStdOutWrite);
	CloseHandle(m_hCompileStdInRead);
	CloseHandle(m_hCompileStdOutRead);

	Result = CreatePipe(&m_hCompileStdOutRead, &m_hCompileStdOutWrite, &m_CompileSecurityAttr, 0);
	if (!Result) return AddSrWindowsError("Failed to create the compiler's output pipes!");

	Result = SetHandleInformation(m_hCompileStdOutRead, HANDLE_FLAG_INHERIT, 0);
	if (!Result) return AddSrWindowsError("Failed to change the compiler's output-read pipe!");

	Result = CreatePipe(&m_hCompileStdInRead, &m_hCompileStdInWrite, &m_CompileSecurityAttr, 0);
	if (!Result) return AddSrWindowsError("Failed to create the compiler's input pipes!");

	Result = SetHandleInformation(m_hCompileStdInWrite, HANDLE_FLAG_INHERIT, 0);
	if (!Result) return AddSrWindowsError("Failed to change the compiler's input-write pipe!");
	
	ZeroMemory( &m_piProcInfo, sizeof(PROCESS_INFORMATION) );

	ZeroMemory( &m_siStartInfo, sizeof(STARTUPINFO) );
	m_siStartInfo.cb = sizeof(STARTUPINFO); 
	m_siStartInfo.hStdError = m_hCompileStdOutWrite;
	m_siStartInfo.hStdOutput = m_hCompileStdOutWrite;
	m_siStartInfo.hStdInput = m_hCompileStdInRead;
	m_siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	return true;
}
    

bool CSrScriptView::CompileCurrentScript (void)
{
	bool Result;

	if (m_pCurrentScript == NULL) return false;
	GetControlData();

	Result = SaveExistingScript();
	if (!Result) return false;

	return CompileScript(m_pCurrentScript);
}


bool CSrScriptView::CompileScript (CSrScriptFile* pScript)
{
	CString  Cmd;
	bool     Result;

	if (pScript == NULL) return false;

	Cmd = CreateCompilerCommand(pScript);
	if (Cmd.IsEmpty()) return AddSrGeneralError("Failed to create the command for launching the compiler!");
	
	CSrProgressDlg* pProgressDlg = ShowSrProgressDlg("Compiling Script",  "Attempting to compile '%s'...", pScript->GetScriptName());
	pProgressDlg->SetAllowCancel(false);

	Result = CreateCompilerPipes();
	if (!Result) return false;
	
	BOOL bSuccess = CreateProcessA(NULL, (char *)Cmd.GetBuffer(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &m_siStartInfo, &m_piProcInfo);
	if (!bSuccess) return AddSrWindowsError("Failed to create the compiler process!");

	CloseHandle(m_hCompileStdInWrite);
	CloseHandle(m_hCompileStdOutWrite);
	m_hCompileStdInWrite = NULL;
	m_hCompileStdOutWrite = NULL;

	DWORD dwRead;
	const int BUFSIZE = 4096;
	CHAR chBuf[BUFSIZE+32]; 
	bSuccess = FALSE;
	CString Output;
	int TotalSize = 0;
	int Counter = 0;

	Output = "Compiler Command: ";
	Output += Cmd;
	Output += "\r\n";

	for (;;) 
	{ 
		bSuccess = ReadFile( m_hCompileStdOutRead, chBuf, BUFSIZE, &dwRead, NULL);
		if ( !bSuccess || dwRead == 0) break;

		chBuf[dwRead] = 0;
		Output += chBuf;

		TotalSize += dwRead;
		++Counter;

		pProgressDlg->Update(TotalSize / (float)(TotalSize + 100.0f) * 100.0f);
	}

	DestroySrProgressDlg(pProgressDlg);

	if (m_pErrorView != NULL)
	{
		m_pErrorView->SetErrorText(Output);
	}

	return true;
}


bool CSrScriptView::CompileScript (const char* pFilename)
{
	CSrScriptFile TmpScript;
	bool          Result;

	Result = TmpScript.Load(pFilename);
	if (!Result) return AddSrGeneralError("Failed to compile the script '%s'!", pFilename);

	return CompileScript(&TmpScript);
}


void CSrScriptView::OnScriptCompile()
{
	if (!CompileCurrentScript()) SrEditShowError("Internal error compiling script!");
}


void CSrScriptView::OnUpdateScriptExists(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pCurrentScript != NULL);
}


void CSrScriptView::OnBnClickedLoadscript()
{
	OnScriptLoad();
}


void CSrScriptView::OnBnClickedNewscript()
{
	OnScriptNew();
}


void CSrScriptView::OnBnClickedCompilescript()
{
	OnScriptCompile();
}


void CSrScriptView::OnBnClickedSavescript()
{
	OnScriptSave();
}


void CSrScriptView::OnBnClickedSaveasscript()
{
	OnScriptSaveAs();
}


void CSrScriptView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;
	
	if (pWnd->GetDlgCtrlID() == IDC_SCRIPT_LIST) 
	{
		Result = Menu.LoadMenu(IDR_SCRIPTLIST_MENU);
		if (!Result) return;
		
		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;
		
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_SCRIPT_TEXT) 
	{
		Result = Menu.LoadMenu(IDR_SCRIPTTEXT_MENU);
		if (!Result) return;
		
		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;
		
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
	else 
	{
		CFormView::OnContextMenu(pWnd, Point);
	}
		
}


void CSrScriptView::OnScripttextmenuUndo()
{
	m_ScriptText.Undo();
}


void CSrScriptView::OnScripttextmenuCut()
{
	m_ScriptText.Cut();
}


void CSrScriptView::OnScripttextmenuCopy()
{
	m_ScriptText.Copy();
}


void CSrScriptView::OnScripttextmenuPaste()
{
	m_ScriptText.Paste();
}


void CSrScriptView::OnUpdateScriptTextUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pCurrentScript != NULL && m_ScriptText.CanUndo());
}


void CSrScriptView::OnUpdateScriptTextCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pCurrentScript != NULL && m_ScriptText.GetSelectionType() != SEL_EMPTY);
}


void CSrScriptView::OnUpdateScriptTextCopy(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pCurrentScript != NULL && m_ScriptText.GetSelectionType() != SEL_EMPTY);
}


void CSrScriptView::OnUpdateScriptTextPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pCurrentScript != NULL && m_ScriptText.CanPaste());
}


BOOL CSrScriptView::PreTranslateMessage(MSG* pMsg)
{

	if (m_hAccelerator != NULL) 
	{
		if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST && m_hAccelerator != NULL) 
		{
			BOOL Result = TranslateAccelerator(m_hWnd, m_hAccelerator, pMsg);
			if (Result != 0) return Result;
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}


void CSrScriptView::OnScripttextaccUndo()
{
	if (GetFocus() == &m_ScriptText) OnScripttextmenuUndo();
}


void CSrScriptView::OnScripttextaccCopy()
{
	if (GetFocus() == &m_ScriptText) OnScripttextmenuCopy();
}


void CSrScriptView::OnScripttextaccCut()
{
	if (GetFocus() == &m_ScriptText) OnScripttextmenuCut();
}


void CSrScriptView::OnScripttextaccPaste()
{
	if (GetFocus() == &m_ScriptText) OnScripttextmenuPaste();
}


void CSrScriptView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFormView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	OnInitMenuPopupHelper(this, pPopupMenu, nIndex, bSysMenu);
}


UINT CSrScriptView::OnGetDlgCode()
{
	return CFormView::OnGetDlgCode();
}


void CSrScriptView::OnDestroy()
{
	CFormView::OnDestroy();
}


bool CSrScriptView::CheckCanClose (void)
{
	CString Buffer;
	bool	fResult;
	int     Result;

	GetControlData();

	for (dword i = 0; i < m_Scripts.GetSize(); ++i)
	{
		if (!m_Scripts[i]->IsModified()) continue;
		
		Buffer.Format("Script '%s' has not been saved. Do you wish to save now?", m_Scripts[i]->GetScriptName());

		Result = AfxMessageBox(Buffer, MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (Result == IDCANCEL) return false;

		if (Result == IDYES)
		{
			fResult = SaveScript(m_Scripts[i]);
			if (!fResult) return false;
		}
	}

	return true;
}


void CSrScriptView::OnScriptlistmenuTesttokens()
{
	if (m_pCurrentScript == NULL) return;
	m_pCurrentScript->Tokenize();
	m_pCurrentScript->DumpTokens();
}


void CSrScriptView::OnScriptlistmenuTestproperties()
{
	if (m_pCurrentScript == NULL) return;
	CSrScriptPropertyDlg Dlg;

	GetControlData();

	srvmadscript_t Script;
	Script.Name = m_pCurrentScript->GetScriptName();

	Dlg.DoModal(Script, NULL);
}


bool CSrScriptView::UpdateScript (const char* pScriptName)
{
	CSrScriptFile* pScriptFile = FindScriptName(pScriptName);
	if (pScriptFile == NULL) return false;

	if (m_pCurrentScript == pScriptFile) 
	{
		GetControlData();
		return true;
	}

	return false;
}


bool CSrScriptView::UpdateScriptView (const char* pScriptName)
{
	CSrScriptFile* pScriptFile = FindScriptName(pScriptName);
	if (pScriptFile == NULL) return false;

	if (m_pCurrentScript == pScriptFile) 
	{
		SetControlData();
		return true;
	}

	return false;
}

