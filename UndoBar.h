/*===========================================================================
 *
 * File:		UndoBar.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __UNDOBAR_H
#define __UNDOBAR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/srundoitem.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrUndoBar Definition
 *
 *=========================================================================*/
class CSrUndoBar : public CSizingControlBarCF {

  /*---------- Protected Class Members -----------------------*/
protected:
  CListBox			m_wndChild;
  CFont				m_font;

  CSrUndoItemArray*	m_pLastUndoArray;
  

  /*---------- Public Class Members --------------------------*/
public:

	/* Constructor/Destructor */
  CSrUndoBar();
  virtual ~CSrUndoBar();

	/* Access the currently selected item */
  CSrUndoItem* GetCurrentUndoItem (void);
  int GetCurrentUndoItemCount (void);

	/* Prevent updates from being displayed immediately */
  void LockUpdates (const bool Lock);

	/* Update the list from an array of undo items */
  void UpdateList (CSrUndoItemArray* pUndoItems);


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrUndoBar)
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CSrUndoBar)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDblclkUndoList (void);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrUndoBar Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File UndoBar.H
 *=========================================================================*/
