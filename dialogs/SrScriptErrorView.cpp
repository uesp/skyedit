
#include "stdafx.h"
#include "sredit.h"
#include "SrScriptErrorView.h"
#include "SrScriptView.h"


#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSrScriptErrorView, CFormView)


BEGIN_MESSAGE_MAP(CSrScriptErrorView, CFormView)
	ON_WM_INITMENUPOPUP()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_ERRORTEXT, OnDblclkErrortext)
	ON_NOTIFY(EN_MSGFILTER, IDC_ERRORTEXT, OnMsgfilterErrortext)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ERRORBAR_COPY, OnErrorbarCopy)
	ON_UPDATE_COMMAND_UI(ID_ERRORBAR_COPY, OnUpdateErrorbarCopy)
	ON_COMMAND(ID_ERROR_COPY, OnErrorbarCopy)
END_MESSAGE_MAP()


CSrScriptErrorView::CSrScriptErrorView() : CFormView(CSrScriptErrorView::IDD) 
{
	m_pScriptView = NULL;
	m_HasDblClick = false;
	m_hAccelerator = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ERRORBAR_ACCEL));
}


CSrScriptErrorView::~CSrScriptErrorView() 
{
}


void CSrScriptErrorView::DoDataExchange(CDataExchange* pDX) 
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ERRORTEXT, m_ErrorText);
}


#ifdef _DEBUG
	void CSrScriptErrorView::AssertValid() const { CFormView::AssertValid(); }
	void CSrScriptErrorView::Dump(CDumpContext& dc) const {	CFormView::Dump(dc); }
#endif


void CSrScriptErrorView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if (IsWindow(m_ErrorText.m_hWnd)) 
	{
		m_ErrorText.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE);
	}
	
}


void CSrScriptErrorView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(0,0));

	m_ErrorText.SetEventMask(ENM_MOUSEEVENTS);

	m_ErrorText.SetWindowText("Compiler output text:");
}


void CSrScriptErrorView::ClearErrors (void) 
{
	m_ErrorText.SetWindowText("");
}


void CSrScriptErrorView::AddErrors (CSrScriptErrorArray& Errors) 
{
	dword Index;

	for (Index = 0; Index < Errors.GetSize(); ++Index) 
	{
		AddError(Errors.GetAt(Index));
	}

}


void CSrScriptErrorView::AddError (CSrScriptError* pError) 
{
	CString Buffer;
	int     Length;
	int     LineNumber;

		/* Ignore invalid input */
	if (pError == NULL) return;

	Length     = m_ErrorText.GetWindowTextLength();
	LineNumber = m_ErrorText.LineFromChar(Length);
	pError->SetUserData(LineNumber);

	Buffer = pError->MakeErrorString();
	Buffer += "\r\n";
 
	m_ErrorText.SetSel(Length, Length);
	m_ErrorText.ReplaceSel(Buffer);
}


void CSrScriptErrorView::AddMessage (const char* pString, ...) 
{
	CString Buffer;
	va_list Args;
	int     Length;

	va_start(Args, pString);
	Buffer.FormatV(pString, Args);
	Buffer += "\r\n";
	va_end(Args);

	Length = m_ErrorText.GetWindowTextLength();
	m_ErrorText.SetSel(Length, Length);
	m_ErrorText.ReplaceSel(Buffer);
}


CSrScriptError* CSrScriptErrorView::FindErrorFromLine (const int Line) 
{
	//CSrScriptError* pError;
	//dword           Index;

	if (m_pScriptView == NULL) return (NULL);

	/*
	for (Index = 0; Index < m_pScriptView->GetCompiler().GetErrors().GetSize(); ++Index) 
	{
		pError = m_pScriptView->GetCompiler().GetErrors().GetAt(Index);
		if (pError->GetUserData() == Line) return (pError);
	} //*/

	return (NULL);
}


void CSrScriptErrorView::OnDblclkErrortext(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CSrScriptError* pError;
	long            StartSel;
	long            EndSel;
	int             LineNumber;

	*pResult = 0;

	m_ErrorText.GetSel(StartSel, EndSel);
	if (StartSel < 0) return;
	if (m_pScriptView == NULL) return;

	LineNumber = m_ErrorText.LineFromChar(StartSel);
    
	pError = FindErrorFromLine(LineNumber);
	if (pError == NULL) return;

	//m_pScriptView->SelectFromError(pError);
}


void CSrScriptErrorView::OnMsgfilterErrortext(NMHDR* pNMHDR, LRESULT* pResult) 
{
	MSGFILTER *pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);

	switch (pMsgFilter->msg) 
	{
    case WM_LBUTTONDOWN:
		m_HasDblClick = false;
		break;
    case WM_LBUTTONUP:
		if (m_HasDblClick) 
		{
			m_HasDblClick = false;
		OnDblclkErrortext(pNMHDR, pResult);
		}
		break;
    case WM_LBUTTONDBLCLK:
		m_HasDblClick = true;
		break;
	}

	*pResult = 0;
}


void CSrScriptErrorView::SetErrorText (const char* pString)
{
	m_ErrorText.SetWindowTextA(pString);
}


void CSrScriptErrorView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;
	
	if (pWnd->GetDlgCtrlID() == IDC_ERRORTEXT) 
	{
		Result = Menu.LoadMenu(IDR_ERRORBAR_MENU);
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


void CSrScriptErrorView::OnErrorbarCopy()
{
	m_ErrorText.Copy();
}


void CSrScriptErrorView::OnUpdateErrorbarCopy(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_ErrorText.GetSelText().IsEmpty());
}


BOOL CSrScriptErrorView::PreTranslateMessage(MSG* pMsg)
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


void CSrScriptErrorView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFormView::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	OnInitMenuPopupHelper(this, pPopupMenu, nIndex, bSysMenu);
}