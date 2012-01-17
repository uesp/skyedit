/*===========================================================================
 *
 * File:	Oberrordlg.H
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	July 31, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBERRORDLG_H
#define __OBERRORDLG_H


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
 * Begin Definitions
 *
 *=========================================================================*/

	/* Error dialog flags */
  #define OBERRDLG_SHOWALLERRORS	1
  #define OBERRDLG_SHOWUNTAGGEDERRORS	2

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/

     
/*===========================================================================
 *
 * Begin Class CSrErrorDlg Definition
 *
 *=========================================================================*/
class CSrErrorDlg : public CDialog {


  /*---------- Protected Class Members -------------------------------*/
protected:
  CString	m_Title;
  CString	m_Message;
  dword		m_Flags;
  dword		m_OutputCount;


  /*---------- Protected Class Members -------------------------------*/
protected:

	/* Add error information to the dialog */
  void AddLastError            (void);
  void AddAllErrors            (void);
  void AddAllUntaggedErrors    (void);
  void AddErrorInfo            (CSrError* pError, const int ErrorIndex);


  /*---------- Public Class Methods ---------------------------------*/
public:

	/* Constructor */
  CSrErrorDlg(CWnd* pParent = NULL);


	/* Set class members */
  void SetTitle   (const TCHAR* pString) { m_Title   = pString; }
  void SetMessage (const TCHAR* pString) { m_Message = pString; }
  void SetFlags   (const dword    Flags) { m_Flags   = Flags; }

	/* Dialog Data */
  //{{AFX_DATA(CSrErrorDlg)
  enum { IDD = IDD_SRERROR_DLG };
  CEdit	m_ErrorDetails;
  CEdit	m_ErrorMessage;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrErrorDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrErrorDlg)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
/*===========================================================================
 *		End of Class CSrErrorDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Oberrordlg.H
 *=========================================================================*/
