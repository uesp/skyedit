/*===========================================================================
 *
 * File:	Errorbar.H
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	September 10, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ERRORBAR_H
#define __ERRORBAR_H


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
 * Begin Class CSrErrorBar Definition
 *
 *=========================================================================*/
class CSrErrorBar : public CSizingControlBarCF {

  /*---------- Protected Class Members -----------------------*/
protected:
  CRichEditCtrl m_wndChild;
  CFont		m_font;
  CHARFORMAT	m_BoldFormat;
  CHARFORMAT	m_DefaultFormat;


  /*---------- Public Class Members --------------------------*/
public:

	/* Constructor/Destructor */
  CSrErrorBar();
 virtual ~CSrErrorBar();

	/* Add a line of text to the end of the error bar */
  void AddText     (const TCHAR* pString);
  void AddBoldText (const TCHAR* pString);


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrErrorBar)
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CSrErrorBar)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrErrorBar Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Errorbar.H
 *=========================================================================*/
