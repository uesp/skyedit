/*===========================================================================
 *
 * File:		ChildFrmFix.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implementation of the CChildFrameFixFix class
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "ChildFrmFix.h"


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

  IMPLEMENT_DYNCREATE(CChildFrameFix, CMDIChildWnd)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameFix Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CChildFrameFix, CMDIChildWnd)
  //{{AFX_MSG_MAP(CChildFrameFix)
  ON_WM_SIZE()
  ON_WM_CLOSE()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CChildFrameFix Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameFix Constructor
 *
 *=========================================================================*/
CChildFrameFix::CChildFrameFix() {
}
/*===========================================================================
 *		End of Class CChildFrameFix Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameFix Destructor
 *
 *=========================================================================*/
CChildFrameFix::~CChildFrameFix() {
}
/*===========================================================================
 *		End of Class CChildFrameFix Destructor
 *=========================================================================*/


/*===========================================================================
 *		End of Class Event CChildFrameFix::OnCreateClient()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameFix Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CChildFrameFix::PreCreateWindow (CREATESTRUCT& cs) {
  cs.style &= ~WS_THICKFRAME;
  cs.style &= ~WS_MAXIMIZEBOX;
  cs.style &= ~WS_MAXIMIZE;
  //cs.style &= ~WS_MINIMIZEBOX;
  //cs.dwExStyle |= WS_EX_CONTEXTHELP;
  if( !CMDIChildWnd::PreCreateWindow(cs) ) return FALSE;

  return TRUE;
}
/*===========================================================================
 *		End of Class Method CChildFrameFix::PreCreateWindow()
 *=========================================================================*/


#ifdef _DEBUG
/*===========================================================================
 *
 * CChildFrameFix Diagnostics
 *
 *=========================================================================*/
void CChildFrameFix::AssertValid() const {
  CMDIChildWnd::AssertValid();
}

void CChildFrameFix::Dump(CDumpContext& dc) const {
  CMDIChildWnd::Dump(dc);
}
/*===========================================================================
 *		End of CChildFrameFix Diagnostics
 *=========================================================================*/
#endif


/*===========================================================================
 *
 * Class CChildFrameFix Event - void OnClose (void);
 *
 *=========================================================================*/
void CChildFrameFix::OnClose (void) {
  DestroyWindow();
}
/*===========================================================================
 *		End of Class Event CChildFrameFix::OnClose()
 *=========================================================================*/
  

/*===========================================================================
 *
 * Class CChildFrameFix Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CChildFrameFix::OnSize(UINT nType, int cx, int cy) {

	/* Cannot maximize this type of frame */
  if (nType == SIZE_MAXIMIZED) {
    CMDIChildWnd::OnSize(SIZE_RESTORED, 200, 200);
  }
  else {
    CMDIChildWnd::OnSize(nType, cx, cy);
  }

}
/*===========================================================================
 *		End of Class Event CChildFrameFix::OnSize()
 *=========================================================================*/