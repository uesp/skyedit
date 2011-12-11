/*===========================================================================
 *
 * File:		ChildFrm.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implementation of the CChildFrame class
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "ChildFrm.h"


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

  IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
  //{{AFX_MSG_MAP(CChildFrame)
  ON_WM_SIZE()
  ON_WM_WINDOWPOSCHANGING()
  ON_WM_SYSCOMMAND()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CChildFrame Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Constructor
 *
 *=========================================================================*/
CChildFrame::CChildFrame() {
  m_IsFakeMaximized = false;
}
/*===========================================================================
 *		End of Class CChildFrame Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Destructor
 *
 *=========================================================================*/
CChildFrame::~CChildFrame() {
}
/*===========================================================================
 *		End of Class CChildFrame Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CChildFrame::PreCreateWindow (CREATESTRUCT& cs) {
  cs.style &= ~WS_MAXIMIZE;
  if( !CMDIChildWnd::PreCreateWindow(cs) ) return FALSE;

  return TRUE;
 }
/*===========================================================================
 *		End of Class Method CChildFrame::PreCreateWindow()
 *=========================================================================*/


#ifdef _DEBUG
/*===========================================================================
 *
 * CChildFrame Diagnostics
 *
 *=========================================================================*/
void CChildFrame::AssertValid() const {
  CMDIChildWnd::AssertValid();
 }

void CChildFrame::Dump(CDumpContext& dc) const {
  CMDIChildWnd::Dump(dc);
 }
/*===========================================================================
 *		End of CChildFrame Diagnostics
 *=========================================================================*/
#endif


/*===========================================================================
 *
 * Class CChildFrame Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CChildFrame::OnSize (UINT nType, int cx, int cy) {
  CMDIChildWnd::OnSize(nType, cx, cy);
  m_IsFakeMaximized = false;
}
/*===========================================================================
 *		End of Class Event CChildFrame::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Method - BOOL PreTranslateMessage (pMsg);
 *
 *=========================================================================*/
BOOL CChildFrame::PreTranslateMessage(MSG* pMsg) {
  return CMDIChildWnd::PreTranslateMessage(pMsg);
}
/*===========================================================================
 *		End of Class Method CChildFrame::PreTranslateMessage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Event - void OnWindowPosChanging (pPos);
 *
 *=========================================================================*/
void CChildFrame::OnWindowPosChanging (WINDOWPOS* pPos) {
  CMDIChildWnd::OnWindowPosChanging(pPos);
}
/*===========================================================================
 *		End of Class Event CChildFrame::OnWindowPosChanging()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Method - void FakeMaximize (void);
 *
 *=========================================================================*/
void CChildFrame::FakeMaximize (void) {
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
 *		End of Class Method CChildFrame::FakeMaximize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrame Event - void OnSysCommand (nID, Param);
 *
 *=========================================================================*/
void CChildFrame::OnSysCommand (UINT nID, LPARAM Param) {

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
 *		End of Class Event CChildFrame::OnSysCommand()
 *=========================================================================*/
