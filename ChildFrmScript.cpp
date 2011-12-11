/*===========================================================================
 *
 * File:		ChildFrmScript.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implementation of the CChildFrameScriptScript class
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "ChildFrmScript.h"
#include "srScptView.h"
#include "srScriptErrorView.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Debug defines */
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  IMPLEMENT_DYNCREATE(CChildFrameScript, CMDIChildWnd)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CChildFrameScript, CMDIChildWnd)
  //{{AFX_MSG_MAP(CChildFrameScript)
  ON_WM_SIZE()
  ON_WM_WINDOWPOSCHANGING()
  ON_WM_SYSCOMMAND()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CChildFrameScript Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Constructor
 *
 *=========================================================================*/
CChildFrameScript::CChildFrameScript() {
  m_IsFakeMaximized = false;
  m_pErrorView      = NULL;
  m_pScriptView     = NULL;
}
/*===========================================================================
 *		End of Class CChildFrameScript Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Destructor
 *
 *=========================================================================*/
CChildFrameScript::~CChildFrameScript() {
}
/*===========================================================================
 *		End of Class CChildFrameScript Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Method - BOOL OnCreateClient (lpcs, pContext);
 *
 *=========================================================================*/
BOOL CChildFrameScript::OnCreateClient (LPCREATESTRUCT lpcs, CCreateContext* pContext) {
  BOOL  bCreateSpltr = m_Splitter.CreateStatic(this, 2, 1);
  CWnd* pWnd;

  m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CSrScptView),        CSize(0,300), pContext);
  m_Splitter.CreateView(1, 0, RUNTIME_CLASS(CSrScriptErrorView), CSize(0,75),  pContext);
  
  //m_Splitter.SetRowInfo(0, 1000, 50);
  //m_Splitter.SetRowInfo(1, 75, 50);

  pWnd = m_Splitter.GetPane(0, 0);
  if (pWnd->IsKindOf(RUNTIME_CLASS(CSrScptView))) m_pScriptView = (CSrScptView* ) pWnd;

  pWnd = m_Splitter.GetPane(1, 0);
  if (pWnd->IsKindOf(RUNTIME_CLASS(CSrScriptErrorView))) m_pErrorView = (CSrScriptErrorView* ) pWnd;

  if (m_pScriptView != NULL) m_pScriptView->SetErrorView(m_pErrorView);
  if (m_pErrorView  != NULL) m_pErrorView->SetScriptView(m_pScriptView);

  return (bCreateSpltr);
}
/*===========================================================================
 *		End of Class Method CChildFrameScript::OnCreateClient()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CChildFrameScript::PreCreateWindow (CREATESTRUCT& cs) {
  cs.style &= ~WS_MAXIMIZE;
  if( !CMDIChildWnd::PreCreateWindow(cs) ) return FALSE;

  return TRUE;
}
/*===========================================================================
 *		End of Class Method CChildFrameScript::PreCreateWindow()
 *=========================================================================*/


#ifdef _DEBUG
/*===========================================================================
 *
 * CChildFrameScript Diagnostics
 *
 *=========================================================================*/
void CChildFrameScript::AssertValid() const {
  CMDIChildWnd::AssertValid();
}

void CChildFrameScript::Dump(CDumpContext& dc) const {
  CMDIChildWnd::Dump(dc);
}
/*===========================================================================
 *		End of CChildFrameScript Diagnostics
 *=========================================================================*/
#endif


/*===========================================================================
 *
 * Class CChildFrameScript Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CChildFrameScript::OnSize (UINT nType, int cx, int cy) {
  CMDIChildWnd::OnSize(nType, cx, cy);
  m_IsFakeMaximized = false;
}
/*===========================================================================
 *		End of Class Event CChildFrameScript::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Method - BOOL PreTranslateMessage (pMsg);
 *
 *=========================================================================*/
BOOL CChildFrameScript::PreTranslateMessage(MSG* pMsg) {
  return CMDIChildWnd::PreTranslateMessage(pMsg);
}
/*===========================================================================
 *		End of Class Method CChildFrameScript::PreTranslateMessage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Event - void OnWindowPosChanging (pPos);
 *
 *=========================================================================*/
void CChildFrameScript::OnWindowPosChanging (WINDOWPOS* pPos) {
  CMDIChildWnd::OnWindowPosChanging(pPos);
}
/*===========================================================================
 *		End of Class Event CChildFrameScript::OnWindowPosChanging()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Method - void FakeMaximize (void);
 *
 *=========================================================================*/
void CChildFrameScript::FakeMaximize (void) {
  CRect ClientRect;
  CRect RestoreRect;

  if (m_IsFakeMaximized) {
    SetWindowPos(NULL, m_RestoreRect.left, m_RestoreRect.top, m_RestoreRect.Width(), m_RestoreRect.Height(), SWP_NOZORDER);
    m_IsFakeMaximized = false;
  }
  else {
    if (IsIconic()) {
      ShowWindow(SW_RESTORE);
    }

    GetWindowRect(&RestoreRect);
    GetParent()->ScreenToClient(&RestoreRect);

    GetParent()->GetClientRect(&ClientRect);
    SetWindowPos(NULL, 0, 0, ClientRect.Width(), ClientRect.Height(), SWP_NOZORDER);

    m_IsFakeMaximized = true;
    m_RestoreRect = RestoreRect;
  }

}
/*===========================================================================
 *		End of Class Method CChildFrameScript::FakeMaximize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Event - void OnSysCommand (nID, Param);
 *
 *=========================================================================*/
void CChildFrameScript::OnSysCommand (UINT nID, LPARAM Param) {

  if ((nID & 0xFFF0) == SC_MAXIMIZE) {
    FakeMaximize();
    return;
  }
  else if ((nID & 0xFFF0) == SC_MINIMIZE) {
    m_IsFakeMaximized = false;
  }

  CMDIChildWnd::OnSysCommand(nID, Param);
}
/*===========================================================================
 *		End of Class Event CChildFrameScript::OnSysCommand()
 *=========================================================================*/
