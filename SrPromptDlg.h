/*===========================================================================
 *
 * File:	Obpromptdlg.H
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	September 26, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBPROMPTDLG_H
#define __OBPROMPTDLG_H


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
 * Begin Class CSrPromptDlg Definition
 *
 *=========================================================================*/
class CSrPromptDlg : public CDialog {

  /*---------- Begin Protected Class Members -------------------------*/
protected:
  CString	m_Label;
  CString	m_Title;
  CString	m_Button1Text;
  CString	m_Button2Text;
  CString	m_Button3Text;

  int		m_SelectedButton;



  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Constructor */
  CSrPromptDlg(CWnd* pParent = NULL);

	/* Get class members */
  int GetSelectedButton (void) { return (m_SelectedButton); }

	/* Set class members */
  void SetLabel   (const TCHAR* pString) { m_Label       = pString; }
  void SetTitle   (const TCHAR* pString) { m_Title       = pString; }
  void SetButton1 (const TCHAR* pString) { m_Button1Text = pString; }
  void SetButton2 (const TCHAR* pString) { m_Button2Text = pString; }
  void SetButton3 (const TCHAR* pString) { m_Button3Text = pString; }

	/* Dialog Data */
  //{{AFX_DATA(CSrPromptDlg)
  enum { IDD = IDD_PROMPT_DLG };
  CStatic	m_PromptLabel;
  CButton	m_Button3;
  CButton	m_Button2;
  CButton	m_Button1;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrPromptDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrPromptDlg)
  afx_msg void OnButton1();
  afx_msg void OnButton2();
  afx_msg void OnButton3();
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrPromptDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int  ShowObPromptDlg   (const TCHAR* pTitle, const TCHAR* pLabel, const TCHAR* pButton1, const TCHAR* pButton2 = "", const TCHAR* pButton3 = "");
  void ShowObOkDlg       (const TCHAR* pTitle, const TCHAR* pLabel);
  bool ShowObYesNoDlg    (const TCHAR* pTitle, const TCHAR* pLabel);
  bool ShowObOkCancelDlg (const TCHAR* pTitle, const TCHAR* pLabel);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/



//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obpromptdlg.H
 *=========================================================================*/
