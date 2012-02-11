#pragma once


#include "modfile/srmoddefs.h"
#include "scripts/srscriptfile.h"
#include "srscripterrorview.h"
#include "SrScriptTextCtrl.h"
#include "afxcmn.h"
#include "afxwin.h"


#define SR_SCRIPTFILE_FILTER  "Script Files (*.psc)|*.psc|All Files (*.*)|*.*||"


struct srscriptoptions_t
{
	CSString CompilerCmdOptions;
	CSString FontName;
	int      FontSize;
	int		 TabSize;
};


class CSrScriptView : public CFormView
{
	DECLARE_DYNCREATE(CSrScriptView)

protected:
	CSrScriptFileArray		m_Scripts;
	CSrScriptFile*			m_pCurrentScript;

	CSrScriptErrorView*		m_pErrorView;

	CFont					m_ScriptFont;
	HACCEL					m_hAccelerator;

	
	HANDLE					m_hCompileStdOutRead;
	HANDLE					m_hCompileStdOutWrite;
	HANDLE					m_hCompileStdInRead;
	HANDLE					m_hCompileStdInWrite;
	SECURITY_ATTRIBUTES		m_CompileSecurityAttr; 
	PROCESS_INFORMATION		m_piProcInfo; 
	STARTUPINFO				m_siStartInfo;

public:
	static srscriptoptions_t	s_ScriptOptions;


protected:
	void GetControlData (void);
	void SetControlData (void);

	void SetCurrentScript (CSrScriptFile* pScript);

	void FillScriptList (void);
	int AddScriptList (CSrScriptFile* pScript);
	void UpdateScriptList (const int ListIndex, CSrScriptFile* pScript);
	void UpdateCurrentScriptList (void);
	CString MakeScriptName (CSrScriptFile* pScript);

	void UpdateScriptList (CSrScriptFile* pScript);
	bool SaveScript (CSrScriptFile* pScript);
	bool SaveCurrentScript (void);
	bool SaveExistingScript (void);

	CString CreateCompilerCommand (CSrScriptFile* pScript);
	bool CreateCompilerPipes (void);

	bool CompileCurrentScript (void);
	bool CompileScript (CSrScriptFile* pScript);
	bool CompileScript (const char* pFilename);

	void SetupScriptTabs (void);

	

	CSrScriptView();
	virtual ~CSrScriptView();

public:
	enum { IDD = IDD_SCRIPT_VIEW };

	bool AddScript         (const char* pFilename);
	bool AddScriptFromData (const char* pFilename);
	bool AddScriptAbsPath  (const char* pFilename);

	bool CheckCanClose (void);

	CSrScriptFile* FindScript     (const char* pFilename);
	CSrScriptFile* FindScriptName (const char* pScriptName);

	void SetErrorView (CSrScriptErrorView* pView) { m_pErrorView = pView; }

	bool UpdateScript (const char* pScriptName);
	bool UpdateScriptView (const char* pScriptName);
	

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CSrScriptTextCtrl m_ScriptText;
	CListBox m_ScriptList;
	afx_msg void OnLbnSelchangeScriptList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnScriptNew();
	afx_msg void OnScriptLoad();
	afx_msg void OnScriptSave();
	afx_msg void OnScriptSaveAs();
	afx_msg void OnScriptRemove();
	afx_msg void OnScriptCompile();
	afx_msg void OnUpdateScriptExists(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedLoadscript();
	afx_msg void OnBnClickedNewscript();
	afx_msg void OnBnClickedCompilescript();
	afx_msg void OnBnClickedSavescript();
	afx_msg void OnBnClickedSaveasscript();
	afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
	afx_msg void OnScripttextmenuUndo();
	afx_msg void OnScripttextmenuCut();
	afx_msg void OnScripttextmenuCopy();
	afx_msg void OnScripttextmenuPaste();
	afx_msg void OnUpdateScriptTextUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScriptTextCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScriptTextCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScriptTextPaste(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnScripttextaccUndo();
	afx_msg void OnScripttextaccCut();
	afx_msg void OnScripttextaccCopy();
	afx_msg void OnScripttextaccPaste();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnDestroy();
	afx_msg void OnScriptlistmenuTesttokens();
	afx_msg void OnScriptlistmenuTestproperties();
};


