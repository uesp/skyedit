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
  CFont			m_font;
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

  CRichEditCtrl& GetRichEdit (void) { return m_wndChild; }

protected:
  
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateErrorbarCopy(CCmdUI *pCmdUI);
	afx_msg void OnErrorbarCopy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrErrorBar Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Errorbar.H
 *=========================================================================*/
