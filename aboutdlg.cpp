/*===========================================================================
 *
 * File:		Aboutdlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "aboutdlg.h"


/*===========================================================================
 *
 * Begin Class CAboutDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_NOTIFY(EN_LINK, IDC_CREDITS, OnLink)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CAboutDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CAboutDlg Constructor
 *
 *=========================================================================*/
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}
/*===========================================================================
 *		End of Class CAboutDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CAboutDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_CREDITS, m_Credits);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CAboutDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CAboutDlg Method - void AddBullet (pString, ...);
 *
 *=========================================================================*/
void CAboutDlg::AddBullet (const TCHAR* pString, ...) {
  PARAFORMAT ParaFormat;
  PARAFORMAT OldFormat;
  CString    Buffer;
  va_list    Args;
  int        Length;

  ParaFormat.cbSize        = sizeof(ParaFormat);
  ParaFormat.dwMask        = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
  ParaFormat.wNumbering    = PFN_BULLET;
  ParaFormat.dxStartIndent = 150;
  ParaFormat.dxOffset      = 150;

  m_Credits.GetParaFormat(OldFormat);
  
  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);
  
  Length = m_Credits.GetWindowTextLength();
  m_Credits.SetSel(Length, Length);

  m_Credits.SetParaFormat(ParaFormat);
  m_Credits.ReplaceSel(Buffer, FALSE);

  Length = m_Credits.GetWindowTextLength();
  m_Credits.SetSel(Length, Length);
  
  AddText("");
  m_Credits.SetParaFormat(OldFormat);
  
}
/*===========================================================================
 *		End of Class Method CAboutDlg::AddBullet()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CAboutDlg Method - void AddText (pString, ...);
 *
 *=========================================================================*/
void CAboutDlg::AddText (const TCHAR* pString, ...) {
  CString Buffer;
  va_list Args;
  int     Length;

  va_start(Args, pString);
  Buffer.FormatV(pString, Args);
  va_end(Args);
  Buffer += "\r\n";

  Length = m_Credits.GetWindowTextLength();
  m_Credits.SetSel(Length, Length);

  m_Credits.ReplaceSel(Buffer, FALSE);

  Length = m_Credits.GetWindowTextLength();
  m_Credits.SetSel(Length, Length);
  
}
/*===========================================================================
 *		End of Class Method CAboutDlg::AddText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CAboutDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CAboutDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  m_Credits.SetBackgroundColor(FALSE, SREDIT_COLOR_GRAY);
  m_Credits.SetTargetDevice(NULL, 0);
  m_Credits.SendMessage(EM_AUTOURLDETECT, 1, 0);
  m_Credits.SetEventMask(m_Credits.GetEventMask() | ENM_LINK);
  
  AddText("Note: SkyEdit is a work in progress and likely contains bugs. Not all features are complete or implemented yet. Please use caution and keep backups of all plugins and save games.");
  AddText("");
  AddText("The latest version along with documentation and help can be found at:");
  AddText("     http://www.uesp.net/wiki/Tes5Mod:SkyEdit");
  AddText("     http://github.com/uesp/skyedit");
  AddText("");
  AddText("Credits:");
  AddBullet("Devil (http://openil.sourceforge.net/) for loading images.");
  AddBullet("zLib (http://www.zlib.net/) for loading/saving compressed data.");
  AddBullet("Resizable Control Bars (http://www.datamekanix.com/) for the nice dockable error/undo control bars in the main view.");
  AddBullet("Tes5Lib (http://github.com/uesp/tes5lib) for loading and manipulating Skyrim data files. ");
  AddText("");
  AddText("Note: This notice can be turned off in SkyEdit.ini by changing 'DisplayAboutOnLoad' to false.");
  	
  return TRUE;
}
/*===========================================================================
 *		End of Class Event CAboutDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CAboutDlg Event - void OnLink (pNotify, pResult);
 *
 *=========================================================================*/
void CAboutDlg::OnLink (NMHDR *pNotify, LRESULT *pResult) {
  ENLINK*   pEnlink = (ENLINK *) pNotify;
  CString   Buffer;
  CHARRANGE OldSel;
  *pResult = 0;

  if (pEnlink->msg != WM_LBUTTONDOWN) return;

  m_Credits.GetSel(OldSel);
  m_Credits.HideSelection(TRUE, FALSE);
  m_Credits.SetSel(pEnlink->chrg);

  Buffer = m_Credits.GetSelText();
  OpenWebPage(Buffer);

  m_Credits.SetSel(OldSel);
  m_Credits.HideSelection(FALSE, FALSE);
}
/*===========================================================================
 *		End of Class Event CAboutDlg::OnLink()
 *=========================================================================*/

