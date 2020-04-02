/*===========================================================================
 *
 * File:		Aboutdlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __ABOUTDLG_H
#define __ABOUTDLG_H


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
 * Begin Class CAboutDlg Definition
 *
 *=========================================================================*/
class CAboutDlg : public CDialog {

public:
  CAboutDlg();

  void AddBullet (const TCHAR* pString, ...);
  void AddText   (const TCHAR* pString, ...);

	/* Dialog Data */
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  CRichEditCtrl	m_Credits;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

	/* Implementation */
protected:
  //{{AFX_MSG(CAboutDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnLink (NMHDR *pNotify, LRESULT *pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

public:
};
/*===========================================================================
 *		End of Class CAboutDlg Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Aboutdlg.H
 *=========================================================================*/
