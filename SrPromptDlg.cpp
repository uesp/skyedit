/*===========================================================================
 *
 * File:		Srpromptdlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srPromptDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrPromptDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrPromptDlg, CDialog)
	ON_BN_CLICKED(ID_BUTTON1, OnButton1)
	ON_BN_CLICKED(ID_BUTTON2, OnButton2)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrPromptDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Constructor
 *
 *=========================================================================*/
CSrPromptDlg::CSrPromptDlg(CWnd* pParent) : CDialog(CSrPromptDlg::IDD, pParent) 
{
	m_SelectedButton = 0;
}
/*===========================================================================
 *		End of Class CSrPromptDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrPromptDlg::DoDataExchange(CDataExchange* pDX) 
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL, m_PromptLabel);
	DDX_Control(pDX, ID_BUTTON3, m_Button3);
	DDX_Control(pDX, ID_BUTTON2, m_Button2);
	DDX_Control(pDX, ID_BUTTON1, m_Button1);
}
/*===========================================================================
 *		End of Class Method CSrPromptDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Event - void OnButton1 ();
 *
 *=========================================================================*/
void CSrPromptDlg::OnButton1() 
{
  m_SelectedButton = 1;
  EndDialog(IDOK);
}
/*===========================================================================
 *		End of Class Event CSrPromptDlg::OnButton1()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Event - void OnButton2 ();
 *
 *=========================================================================*/
void CSrPromptDlg::OnButton2() 
{
  m_SelectedButton = 2;
  EndDialog(IDOK);
}
/*===========================================================================
 *		End of Class Event CSrPromptDlg::OnButton2()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Event - void OnButton3 ();
 *
 *=========================================================================*/
void CSrPromptDlg::OnButton3() 
{
  m_SelectedButton = 3;
  EndDialog(IDOK);
}
/*===========================================================================
 *		End of Class Event CSrPromptDlg::OnButton3()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrPromptDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();

  SetWindowText(m_Title);
  m_PromptLabel.SetWindowText(m_Label);

  m_Button1.SetWindowText(m_Button1Text);
  m_Button2.SetWindowText(m_Button2Text);
  m_Button3.SetWindowText(m_Button3Text);

  m_Button1.ShowWindow(m_Button1Text.IsEmpty() ? SW_HIDE : SW_SHOW);
  m_Button2.ShowWindow(m_Button2Text.IsEmpty() ? SW_HIDE : SW_SHOW);
  m_Button3.ShowWindow(m_Button3Text.IsEmpty() ? SW_HIDE : SW_SHOW);
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrPromptDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrPromptDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CSrPromptDlg::OnOK (void) 
{
  m_SelectedButton = 1;
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrPromptDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ShowSrOkDlg (pTitle, pLabel);
 *
 *=========================================================================*/
void ShowSrOkDlg (const TCHAR* pTitle, const TCHAR* pLabel) 
{
  ShowSrPromptDlg(pTitle, pLabel, "Ok");
}
/*===========================================================================
 *		End of Function ShowSrOkDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ShowSrYesNoDlg (pTitle, pLabel);
 *
 *=========================================================================*/
bool ShowSrYesNoDlg (const TCHAR* pTitle, const TCHAR* pLabel) 
{
  return ShowSrPromptDlg(pTitle, pLabel, "Yes", "No") == 1;
}
/*===========================================================================
 *		End of Function ShowSrYesNoDlg()
 *=========================================================================*/


int ShowSrYesNoCancelDlg (const TCHAR* pTitle, const TCHAR* pLabel) 
{
  return ShowSrPromptDlg(pTitle, pLabel, "Yes", "No", "Cancel");
}


/*===========================================================================
 *
 * Function - bool ShowSrOkCancelDlg (pTitle, pLabel);
 *
 *=========================================================================*/
bool ShowSrOkCancelDlg (const TCHAR* pTitle, const TCHAR* pLabel) 
{
  return ShowSrPromptDlg(pTitle, pLabel, "Ok", "Cancel") == 1;
}
/*===========================================================================
 *		End of Function ShowSrOkCancelDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ShowSrPromptDlg (pTitle, pLabel, pButton1, pButton2, pButton3);
 *
 *=========================================================================*/
int ShowSrPromptDlg (const TCHAR* pTitle, const TCHAR* pLabel, const TCHAR* pButton1, const TCHAR* pButton2, const TCHAR* pButton3) 
{
  CSrPromptDlg	Dlg;
  int		    Result;

  Dlg.SetTitle(pTitle);
  Dlg.SetLabel(pLabel);
  Dlg.SetButton1(pButton1);
  Dlg.SetButton2(pButton2);
  Dlg.SetButton3(pButton3);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (0);

  return Dlg.GetSelectedButton();
}
/*===========================================================================
 *		End of Function ShowSrPromptDlg()
 *=========================================================================*/
