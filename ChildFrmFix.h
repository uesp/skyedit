/*===========================================================================
 *
 * File:		ChildFrmFix.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Definition of the CChildFrameFix class.
 *
 *=========================================================================*/
#ifndef __ChildFrmFix_H
#define __ChildFrmFix_H


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
 * Class CChildFrameFix Definition
 *
 *=========================================================================*/
class CChildFrameFix : public CMDIChildWnd {
  DECLARE_DYNCREATE(CChildFrameFix)


  /*---------- Begin Private Class Members ----------------------*/
private:

  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class constructor/destructor */
  CChildFrameFix();
  virtual ~CChildFrameFix();

	/* Diagnostics routines */
#ifdef _DEBUG
  virtual void AssertValid () const;
  virtual void Dump (CDumpContext& dc) const;
#endif


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CChildFrameFix)
  virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
  //}}AFX_VIRTUAL


  /*---------- Generated message map functions ------------------*/
protected:
  //{{AFX_MSG(CChildFrameFix)
  afx_msg void OnClose (void);
  afx_msg void OnSize (UINT nType, int cx, int cy);
  //}}AFX_MSG


  DECLARE_MESSAGE_MAP()

 };
/*===========================================================================
 *		End of Class CSrEditView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File ChildFrmFix.H
 *=========================================================================*/
