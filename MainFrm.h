/*===========================================================================
 *
 * File:		MainFrm.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Defines the interface of the CMainFrame class.
 *
 *=========================================================================*/
#ifndef __MainFrm_H
#define __MainFrm_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "errorbar.h"
  #include "undobar.h"
  #include "sreditdoc.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Custom messages */
  #define SRE_MSG_UPDATEUNDO (WM_APP + 209)
  #define SRE_MSG_UNDOITEMS  (WM_APP + 210)
  #define SRE_MSG_LOCKUNDO   (WM_APP + 211)

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CMainFrame Definition
 *
 *=========================================================================*/
class CMainFrame : public CMDIFrameWnd {
  DECLARE_DYNAMIC(CMainFrame)
public:
  CMainFrame();

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  CStatusBar		m_wndStatusBar;
  CToolBar			m_wndToolBar;
  CSrErrorBar		m_wndErrorBar;
  CSrUndoBar		m_wndUndoBar;


  /*---------- Begin Public Class Methods ------------------------*/
public:

	/* Destructor */
  virtual ~CMainFrame();

  CView*      GetActiveMainView  (void);
  CSrEditDoc* GetActiveSrEditDoc (void);


	/* Diagnostics */
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  afx_msg void OnViewErrorBar();
  afx_msg void OnUpdateViewErrorBar(CCmdUI* pCmdUI);
  afx_msg void OnViewUndobar();
  afx_msg void OnUpdateViewUndobar(CCmdUI* pCmdUI);
  afx_msg LRESULT OnUpdateUndo (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnUndoItems (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnUndoLock (WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnMdiMaximize (WPARAM wParam, LPARAM lParam);
  afx_msg void OnHelp (void);
  afx_msg void OnViewResourceviewer();
  afx_msg void OnHelpUespwiki();
  afx_msg void OnHelpCswiki();
	afx_msg void OnViewResetlists();
	afx_msg void OnViewScripts();

  DECLARE_MESSAGE_MAP();

public:

};
/*===========================================================================
 *		End of Class CMainFrame Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File MainFrm.H
 *=========================================================================*/
