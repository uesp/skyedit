/*===========================================================================
 *
 * File:		Srerrordlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srErrorDlg.h"


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
 * Begin CSrErrorDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrErrorDlg, CDialog)
  //{{AFX_MSG_MAP(CSrErrorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrErrorDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Constructor
 *
 *=========================================================================*/
CSrErrorDlg::CSrErrorDlg(CWnd* pParent)	: CDialog(CSrErrorDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CSrErrorDlg)
  //}}AFX_DATA_INIT

  m_Flags       = 0;
  m_OutputCount = 0;
}
/*===========================================================================
 *		End of Class CSrErrorDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Method - void AddErrorInfo (pError, ErrorIndex);
 *
 *=========================================================================*/
void CSrErrorDlg::AddErrorInfo (CSrError* pError, const int ErrorIndex) {
  CString Buffer;
  CString IndexBuffer;
  int     Length;

  if (ErrorIndex >= 0) IndexBuffer.Format(_T("%d) "), ErrorIndex);

	/* Check for no error information */
  if (pError == NULL) {
    Buffer.Format(_T("%sNo Error!\r\n"), ErrorIndex >= 0 ? IndexBuffer : _T(""));
  }
	/* Fill in error information */
  else {
    CSString ErrorString = pError->GetErrorString();

    Buffer.Format(_T("%s%s\r\n%s%s%s"), ErrorIndex >= 0 ? IndexBuffer : _T(""), pError->GetErrorMessage(), 
	ErrorString.IsEmpty() ? _T("") : _T("\t"),
	ErrorString.c_str(), ErrorString.IsEmpty() ? _T("") : _T("\r\n"));

    ++m_OutputCount;
  }

  Length = m_ErrorDetails.GetWindowTextLength();
  m_ErrorDetails.SetSel(Length, Length, TRUE);
  m_ErrorDetails.ReplaceSel(Buffer, FALSE);
}
/*===========================================================================
 *		End of Class Method CSrErrorDlg::AddErrorInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Method - void AddLastError (void);
 *
 *=========================================================================*/
void CSrErrorDlg::AddLastError (void) {
  CSrError* pError;

  pError = SrErrorHandler->GetLastError();
  if (pError != NULL) pError->SetTag(1);
  AddErrorInfo(pError, -1);

}
/*===========================================================================
 *		End of Class Method CSrErrorDlg::AddLastError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Method - void AddAllErrors (void);
 *
 *=========================================================================*/
void CSrErrorDlg::AddAllErrors (void) {
  CSrError* pError;
  dword     Index;

  for (Index = 0; Index < SrErrorHandler->GetNumErrors(); ++Index) {
    pError = SrErrorHandler->GetError(Index);
    pError->SetTag(1);
    AddErrorInfo(pError, Index + 1);
  }

}
/*===========================================================================
 *		End of Class Method CSrErrorDlg::AddAllErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Method - void AddAllUntaggedErrors (void);
 *
 *=========================================================================*/
void CSrErrorDlg::AddAllUntaggedErrors (void) {
  CSrError* pError;
  dword     Index;
  dword     Count = 0;

  for (Index = 0; Index < SrErrorHandler->GetNumErrors(); ++Index) {
    pError = SrErrorHandler->GetError(Index);
    if (pError->GetTag() > 0) continue;
    pError->SetTag(1);
    ++Count;
    AddErrorInfo(pError, Count);
  }

}
/*===========================================================================
 *		End of Class Method CSrErrorDlg::AddAllUntaggedErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrErrorDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CSrErrorDlg)
  DDX_Control(pDX, IDC_DETAILS, m_ErrorDetails);
  DDX_Control(pDX, IDC_MESSAGE, m_ErrorMessage);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrErrorDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrErrorDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  if (m_Title.IsEmpty()) m_Title = _T("SkyEdit Error");
  SetWindowText(m_Title);
  m_ErrorMessage.SetWindowText(m_Message);

  if ((m_Flags & OBERRDLG_SHOWALLERRORS) != 0) {
    AddAllErrors();
  }
  else if ((m_Flags & OBERRDLG_SHOWUNTAGGEDERRORS) != 0) {
    AddAllUntaggedErrors();
  }
  else {
    AddLastError();
  }
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrErrorDlg::OnInitDialog()
 *=========================================================================*/
