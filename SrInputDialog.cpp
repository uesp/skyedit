/*===========================================================================
 *
 * File:		Srinputdialog.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srInputDialog.h"


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
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrInputDialog, CDialog)
	//{{AFX_MSG_MAP(CSrInputDialog)
	//ON_EN_CHANGE(IDC_INPUTTEXT, OnChangeInputText)
	ON_EN_UPDATE(IDC_INPUTTEXT, OnChangeInputText)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrInputDialog Constructor
 *
 *=========================================================================*/
CSrInputDialog::CSrInputDialog(CWnd* pParent) : CDialog(CSrInputDialog::IDD, pParent) {
	//{{AFX_DATA_INIT(CSrInputDialog)
	//}}AFX_DATA_INIT

	m_CheckFunction = NULL;
	m_ValidCharFunc = NULL;
	m_CheckUserData = 0;
	m_CheckCode     = SR_INPUTDLG_CHECK_NOCHANGE;

	m_TitleValue = _T("Input");
	m_LabelValue = _T("Enter value below:");
}
/*===========================================================================
 *		End of Class CSrInputDialog Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrInputDialog Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrInputDialog::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrInputDialog)
	DDX_Control(pDX, IDC_LABEL, m_Label);
	DDX_Control(pDX, IDC_INPUTTEXT, m_InputText);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrInputDialog::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrInputDialog Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrInputDialog::OnInitDialog() {
  CDialog::OnInitDialog();

  SetWindowText(m_TitleValue);
  m_Label.SetWindowText(m_LabelValue);
  m_InputText.SetWindowText(m_TextValue);
  m_OrigTextValue = m_TextValue;
	
  m_InputText.SetFocus();
  return (FALSE);
}
/*===========================================================================
 *		End of Class Event CSrInputDialog::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrInputDialog Event - void OnOK ();
 *
 *=========================================================================*/
void CSrInputDialog::OnOK() {
  m_InputText.GetWindowText(m_TextValue);

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrInputDialog::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrInputDialog Event - void OnChangeInputText (void);
 *
 *=========================================================================*/
void CSrInputDialog::OnChangeInputText (void) {
  CString  Buffer;
  CSString ValidBuffer;
  int      CheckCode;
  int      ChangeCount;

  m_InputText.GetWindowText(Buffer);

  if (m_ValidCharFunc != NULL) {
    ValidBuffer = Buffer;
    ChangeCount = ValidBuffer.RemoveCharsToMatch(m_ValidCharFunc);

    if (ChangeCount > 0) {
      Buffer = ValidBuffer;
      DWORD SelStart = m_InputText.GetSel();
      m_InputText.SetWindowText(Buffer);
      m_InputText.SetSel(SelStart, SelStart);
    }
  }

  if (m_CheckFunction == NULL) return;
    
  CheckCode = m_CheckFunction(Buffer, m_OrigTextValue, m_CheckUserData);

  if (CheckCode == m_CheckCode) return;
  m_CheckCode = CheckCode;

  RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CSrInputDialog::OnChangeInputText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrInputDialog Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CSrInputDialog::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
  HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_InputText) {

    switch (m_CheckCode) {
      case SR_INPUTDLG_CHECK_NOCHANGE:
        hBrush = CreateSolidBrush(SR_INPUTDLG_NOCHANGECOLOR);
        pDC->SetBkColor(SR_INPUTDLG_NOCHANGECOLOR);
	break;
      case SR_INPUTDLG_CHECK_OK:
        hBrush = CreateSolidBrush(SR_INPUTDLG_OKCOLOR);
        pDC->SetBkColor(SR_INPUTDLG_OKCOLOR);
	break;
      case SR_INPUTDLG_CHECK_ERROR:
        hBrush = CreateSolidBrush(SR_INPUTDLG_ERRORCOLOR);
        pDC->SetBkColor(SR_INPUTDLG_ERRORCOLOR);
	break;
    }
  }

  return (hBrush);
}
/*===========================================================================
 *		End of Class Event CSrInputDialog::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObInputDialog (Buffer, pTitle, pLabel);
 *
 *=========================================================================*/
bool ObInputDialog (CString& Buffer, const TCHAR* pTitle, const TCHAR* pLabel) {
  CSrInputDialog Dlg;
  int            Result;

  Dlg.SetTextValue(Buffer);
  Dlg.SetTitleValue(pTitle);
  Dlg.SetLabelValue(pLabel);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  Buffer = Dlg.GetTextValue();
  return (true);
}
/*===========================================================================
 *		End of Function ObInputDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrInputDialogValidate (Buffer, pTitle, pLabel, CheckFunc, UserData, ValidFunc);
 *
 *=========================================================================*/
bool SrInputDialogValidate (CString& Buffer, const TCHAR* pTitle, const TCHAR* pLabel, INPUTDLGCHECKFUNC CheckFunc, const long UserData, ISCHARFUNC ValidFunc) {
  CSrInputDialog Dlg;
  int            Result;

  Dlg.SetTextValue(Buffer);
  Dlg.SetTitleValue(pTitle);
  Dlg.SetLabelValue(pLabel);
  Dlg.SetCheckFunction(CheckFunc, UserData);
  Dlg.SetValidCharFunc(ValidFunc);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  Buffer = Dlg.GetTextValue();
  return (true);
}
/*===========================================================================
 *		End of Function SrInputDialogValidate()
 *=========================================================================*/
