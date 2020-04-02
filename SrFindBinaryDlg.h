/*===========================================================================
 *
 * File:	Obfindbinarydlg.H
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	August 29, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFINDBINARYDLG_H
#define __OBFINDBINARYDLG_H


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
 * Begin Class CSrFindBinaryDlg Definition
 *
 *=========================================================================*/
class CSrFindBinaryDlg : public CDialog {

  /*---------- Begin Protected Class Members -----------------------------*/
protected:
  CString	m_BinaryData;


  /*---------- Public Class Methods --------------------------------------*/
public:

	/* Constructor */
  CSrFindBinaryDlg(CWnd* pParent = NULL);

	/* Get class members */
  const TCHAR* GetBinaryData (void) { return (m_BinaryData); }

	/* Dialog Data */
  //{{AFX_DATA(CSrFindBinaryDlg)
  enum { IDD = IDD_FINDBINARY_DLG };
  CEdit		m_BinaryDataText;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrFindBinaryDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrFindBinaryDlg)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrFindBinaryDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obfindbinarydlg.H
 *=========================================================================*/
