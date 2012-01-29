/*===========================================================================
 *
 * File:		ChildFrmScript.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	28 January 2012
 *
 * Definition of the CChildFrameScript class.
 *
 *=========================================================================*/
#ifndef __CHILDFRAMESCRIPT_H
#define __CHILDFRAMESCRIPT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

		/* Forward class definitions */
	class CSrScriptView;
	class CSrScriptErrorView;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CChildFrameScript Definition
 *
 *=========================================================================*/
class CChildFrameScript : public CMDIChildWnd 
{
	DECLARE_DYNCREATE(CChildFrameScript)

  /*---------- Begin Protected Class Members --------------------*/
protected:
	bool				m_IsFakeMaximized;
	bool				m_IsInitialized;
	CRect				m_RestoreRect;

	CSplitterWndEx		m_Splitter;

	CSrScriptView*		m_pScriptView;
	CSrScriptErrorView*	m_pErrorView;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

		/* Class constructor/destructor */
	CChildFrameScript();
	virtual ~CChildFrameScript();

		/* Get class members */
	CSrScriptView*        GetScriptView (void) { return (m_pScriptView); }
	CSrScriptErrorView*	GetErrorView  (void) { return (m_pErrorView); }

	void FakeMaximize (void);
	
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	/* Diagnostics routines */
#ifdef _DEBUG
	virtual void AssertValid () const;
	virtual void Dump (CDumpContext& dc) const;
#endif

public:
	virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
  

  /*---------- Generated message map functions ------------------*/
protected:
	afx_msg void OnSize (UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging (WINDOWPOS* pPos);
	afx_msg void OnSysCommand (UINT nID, LPARAM Param);

	DECLARE_MESSAGE_MAP()

};
/*===========================================================================
 *		End of Class CChildFrameScript Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ChildFrmScript.H
 *=========================================================================*/
