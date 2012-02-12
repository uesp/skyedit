/*===========================================================================
 *
 * File:		Srprogressdlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "common/srerrorhandler.h"
#include "resource.h"
#include "SrProgressDlg.h"
#include "common/srlogfile.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrProgressDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CSrProgressDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrProgressDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int SrEditDefaultProgressCallback (pData);
 *
 * Default progress update callback.
 *
 *=========================================================================*/
int SrEditDefaultProgressCallback (CSrCallback* pCallback) {
  CSrProgressDlg* pProgressView;

  if (pCallback == NULL) return (SRCALLBACK_INVALIDINPUT);

  pProgressView = (CSrProgressDlg *) pCallback->GetUserPtr();
  if (pProgressView == NULL) return (SRCALLBACK_INVALIDINPUT);
    

  if (pCallback->GetUpdateTitle()) {
    pProgressView->UpdateTitle(pCallback->GetTitle());  
    pCallback->SetUpdateTitle(false);
  }

  if (pCallback->GetUpdateLabel()) {
    pProgressView->UpdateLabel(pCallback->GetLabel());  
    pCallback->SetUpdateLabel(false);
  }

  pProgressView->Update(pCallback->GetPercentDone());

  if (pProgressView->GetIsCancelled()) {
    return (SRCALLBACK_USERABORT);
  }

  return (SRCALLBACK_OK);
}
/*===========================================================================
 *		End of Function SrEditDefaultProgressCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Constructor
 *
 *=========================================================================*/
CSrProgressDlg::CSrProgressDlg (const TCHAR* pTitle, const TCHAR* pLabel) : CDialog(CSrProgressDlg::IDD, NULL) {
  //{{AFX_DATA_INIT(CSrProgressDlg)
  //}}AFX_DATA_INIT

  m_Title        = pTitle;
  m_CancelMsg    = _T("Are you sure you wish to abort?");
  m_Label        = pLabel;

  m_AllowCancel  = true;
  m_PromptCancel = false;
  m_RunAsModal   = true;
  m_IsCancelled  = false;

  	/* Disable the application window if required */
  if (m_RunAsModal) AfxGetMainWnd()->EnableWindow(FALSE);
    
  Create(CSrProgressDlg::IDD, NULL);
  ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class CSrProgressDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrProgressDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CSrProgressDlg)
  DDX_Control(pDX, IDC_FILE_PERCENT, m_PercentLabel);
  DDX_Control(pDX, IDC_FILE_PROGRESS, m_ProgressCtrl);
  DDX_Control(pDX, IDC_FILE_LABEL, m_LabelText);
  DDX_Control(pDX, IDCANCEL, m_CancelButton);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Event - void OnCancel (void);
 *
 *=========================================================================*/
void CSrProgressDlg::OnCancel (void) {
  int Result;

  if (!m_AllowCancel) return;

  if (m_PromptCancel) {
    Result = MessageBox(m_CancelMsg, _T("Cancel Operation"), MB_YESNO | MB_ICONEXCLAMATION);
    if (Result != IDYES) return;
  }

  AddSrGeneralError("Action aborted by user!");
  m_IsCancelled = true;
  //CDialog::OnCancel();
}
/*===========================================================================
 *		End of Class Event CSrProgressDlg::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Event - void OnDestroy (void);
 *
 *=========================================================================*/
void CSrProgressDlg::OnDestroy (void) {

	/* Enable the application window if required */
  if (m_RunAsModal) AfxGetMainWnd()->EnableWindow(FALSE);

  CDialog::OnDestroy();
}
/*===========================================================================
 *		End of Class Event CSrProgressDlg::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrProgressDlg::OnInitDialog() {

	/* Call the base class event */
  CDialog::OnInitDialog();

	/* Initialize the controls */
  m_ProgressCtrl.SetRange(0, 100);
  m_ProgressCtrl.SetPos(0);
  m_CancelButton.ShowWindow(m_AllowCancel ? SW_SHOW : SW_HIDE);

  UpdateControls();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrProgressDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - BOOL Pump (void);
 *
 *=========================================================================*/
BOOL CSrProgressDlg::Pump (void) {
  MSG msg;

  while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) {
    if (!AfxGetApp()->PumpMessage()) {
      ::PostQuitMessage(0);
      return FALSE;
    }
  }

	/* Simulate the framework's idle processing mechanism */
  LONG lIdle = 0;

  while (AfxGetApp()->OnIdle(lIdle++));

  return TRUE;
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::Pump()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - void SetProgress (Progress);
 *
 *=========================================================================*/
void CSrProgressDlg::SetProgress (const float Progress) {
  CString Buffer;

  m_ProgressCtrl.SetPos((int)Progress);

  Buffer.Format(_T("%d%%"), (int)Progress);
  m_PercentLabel.SetWindowText(Buffer);

  m_ProgressCtrl.UpdateWindow();
  m_PercentLabel.UpdateWindow();

  m_CancelButton.ShowWindow(m_AllowCancel ? SW_SHOW : SW_HIDE);
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::SetProgress()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - void UpdateControls (void);
 *
 *=========================================================================*/
void CSrProgressDlg::UpdateControls (void) 
{
  SetWindowText(m_Title);
  m_LabelText.SetWindowText(m_Label);
  m_CancelButton.ShowWindow(m_AllowCancel ? SW_SHOW : SW_HIDE);
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::UpdateControls()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - void UpdateLabel (pString);
 *
 *=========================================================================*/
void CSrProgressDlg::UpdateLabel (const TCHAR* pString) {
  m_LabelText.SetWindowText(pString);
  m_LabelText.RedrawWindow();
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::UpdateLabel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - void UpdateTitle (pString);
 *
 *=========================================================================*/
void CSrProgressDlg::UpdateTitle (const TCHAR* pString) {
  SetWindowText(pString);
  RedrawWindow();
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::UpdateTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrProgressDlg Method - void Update (Percent);
 *
 * Main progress update callback. Updates the progress and pumps any
 * waiting messages.
 *
 *=========================================================================*/
void CSrProgressDlg::Update (const float Percent) 
{
  SetProgress(Percent);
  m_CancelButton.ShowWindow(m_AllowCancel ? SW_SHOW : SW_HIDE);

  Pump();
}
/*===========================================================================
 *		End of Class Method CSrProgressDlg::Update()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CSrProgressDlg* ShowSrProgressDlg (pTitle, pLabel, ...);
 *
 * Creates and displays a new progress dialog. Ensure to destroy the
 * dialog using the DestroySrProgressDlg() function.
 *
 *=========================================================================*/
CSrProgressDlg* ShowSrProgressDlg (const TCHAR* pTitle, const TCHAR* pLabel, ...) {
  CSrProgressDlg* pProgressDlg;
  CString	  Buffer;
  va_list	  Args;
  
  va_start(Args, pLabel);
  Buffer.FormatV(pLabel, Args);
  va_end(Args);

  pProgressDlg = new CSrProgressDlg(pTitle, Buffer);

  return (pProgressDlg);
}
/*===========================================================================
 *		End of Function ShowSrProgressDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void DestroySrProgressDlg (pProgressDlg);
 *
 * Closes and destroys a progress dialog created by ShowSrProgressDlg().
 *
 *=========================================================================*/
void DestroySrProgressDlg (CSrProgressDlg* pProgressDlg) {

  if (pProgressDlg != NULL) {
    pProgressDlg->EndDialog(IDOK);
    delete pProgressDlg;
  }

}
/*===========================================================================
 *		End of Function DestroySrProgressDlg()
 *=========================================================================*/
