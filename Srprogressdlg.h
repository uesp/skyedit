/*===========================================================================
 *
 * File:		Srprogressdlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRPROGRESSDLG_H
#define __SRPROGRESSDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "common/srcallback.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrProgressDlg Definition
 *
 *=========================================================================*/
class CSrProgressDlg : public CDialog {

  /*---------- Protected Class Members --------------------------------*/
protected:
  CString		m_Title;
  CString       m_CancelMsg;
  CString		m_Label;

  bool			m_AllowCancel;
  bool			m_PromptCancel;
  bool			m_RunAsModal;
  bool			m_IsCancelled;


  /*---------- Protected Class Methods --------------------------------*/
protected:


  /*---------- Public Class Methods -----------------------------------*/
public:

	/* Constructor */
  CSrProgressDlg (const TCHAR* pTitle, const TCHAR* pLabel);

	/* Get class members */
  bool GetIsCancelled (void) { return (m_IsCancelled); }

	/* Pump messages in the dialog's queue */
  BOOL Pump (void);

	/* Update progress */
  void SetProgress (const float Progress);

	/* Set class members */
  void SetTitle        (const TCHAR* pString) { m_Title        = pString; }
  void SetLabel        (const TCHAR* pString) { m_Label        = pString; }
  void SetCancelMsg    (const TCHAR* pString) { m_CancelMsg    = pString; }
  void SetAllowCancel  (const bool   Value)   { m_AllowCancel  = Value; }
  void SetPromptCancel (const bool   Value)   { m_PromptCancel = Value; }

	/* Update the control contents using the current data */
  void UpdateControls (void);
  void UpdateLabel    (const TCHAR* pString);
  void UpdateTitle    (const TCHAR* pString);

	/* Main update method */
  void Update (const float Percent);

	/* Dialog Data */
  //{{AFX_DATA(CSrProgressDlg)
  enum { IDD = IDD_PROGRESS_DLG };
  CStatic	m_PercentLabel;
  CProgressCtrl	m_ProgressCtrl;
  CStatic	m_LabelText;
  CButton	m_CancelButton;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrProgressDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnCancel ();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrProgressDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnDestroy (void);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrProgressDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Create and display a modeless progress dialog */
  CSrProgressDlg* ShowSrProgressDlg (const TCHAR* pTitle, const TCHAR* pLabel, ...);

	/* Destroy a previously created progress dialog */
  void DestroySrProgressDlg (CSrProgressDlg* pProgressDlg);

	/* Default progress callback function */
  int SrEditDefaultProgressCallback (CSrCallback* pCallback);
  
/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obprogressdlg.H
 *=========================================================================*/
