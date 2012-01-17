/*===========================================================================
 *
 * File:		Errorbar.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implements the dockable error control bar in the main frame.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "errorbar.h"


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
 * Begin CSrErrorBar Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrErrorBar, CSizingControlBarG)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ERRORBAR_COPY, OnErrorbarCopy)
	ON_UPDATE_COMMAND_UI(ID_ERRORBAR_COPY, OnUpdateErrorbarCopy)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrErrorBar Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorBar Constructor
 *
 *=========================================================================*/
CSrErrorBar::CSrErrorBar() {

  m_BoldFormat.cbSize    = sizeof(this);
  m_BoldFormat.dwMask    = CFM_BOLD;
  m_BoldFormat.dwEffects = CFE_BOLD;

}
/*===========================================================================
 *		End of Class CSrErrorBar Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorBar Destructor
 *
 *=========================================================================*/
CSrErrorBar::~CSrErrorBar() {
}
/*===========================================================================
 *		End of Class CSrErrorBar Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorBar Method - void AddText (pString);
 *
 * Add a line of text to the end of the error log.
 *
 *=========================================================================*/
void CSrErrorBar::AddText (const TCHAR* pString) {
  int Length;

  if (pString == NULL) return;
  Length = m_wndChild.GetWindowTextLength();

  if (Length > 60000) {
    m_wndChild.SetSel(0, 10000);
    m_wndChild.ReplaceSel(_T(""), FALSE); 
    Length = m_wndChild.GetWindowTextLength();
  }

  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(pString, FALSE);

  Length = m_wndChild.GetWindowTextLength();
  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(_T("\r\n"), FALSE);

}
/*===========================================================================
 *		End of Class Method CSrErrorBar::AddText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorBar Method - void AddBoldText (pString);
 *
 * Add a line of bolded text to the end of the error log.
 *
 *=========================================================================*/
void CSrErrorBar::AddBoldText (const TCHAR* pString) {
  int Length;

  if (pString == NULL) return;
  Length = m_wndChild.GetWindowTextLength();

  if (Length > 60000) {
    m_wndChild.SetSel(0, 10000);
    m_wndChild.ReplaceSel(_T(""), FALSE); 
    Length = m_wndChild.GetWindowTextLength();
  }

  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(pString, FALSE);

  m_wndChild.SetSel(Length, Length + strlen(pString));
  m_wndChild.SetSelectionCharFormat(m_BoldFormat);

  Length = m_wndChild.GetWindowTextLength();
  m_wndChild.SetSel(Length, Length);
  m_wndChild.ReplaceSel(_T("\r\n"), FALSE);
  m_wndChild.SetSel(Length, Length+2);
  m_wndChild.SetSelectionCharFormat(m_DefaultFormat);

}
/*===========================================================================
 *		End of Class Method CSrErrorBar::AddBoldText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrErrorBar Event - int OnCreate (lpCreateStruct);
 *
 *=========================================================================*/
int CSrErrorBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1) return -1;
  SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

  if (!m_wndChild.Create(WS_CHILD|WS_VISIBLE|
			ES_MULTILINE|ES_WANTRETURN|ES_AUTOHSCROLL|ES_READONLY|WS_VSCROLL,
			CRect(0,0,0,0), this, 123)) {
    return -1;
  }

  m_wndChild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

  if (!m_font.CreateStockObject(DEFAULT_GUI_FONT)) {
    if (!m_font.CreatePointFont(80, "MS Sans Serif")) {
      return -1;
    }
  }

  m_wndChild.SetBackgroundColor(FALSE, RGB(212,208,200));
  m_wndChild.GetDefaultCharFormat(m_DefaultFormat);
  m_wndChild.SetFont(&m_font);

  return 0;
}
/*===========================================================================
 *		End of Class Event CSrErrorBar::OnCreate()
 *=========================================================================*/


void CSrErrorBar::OnContextMenu(CWnd* pWnd, CPoint Point)
{
 	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;

	Result = Menu.LoadMenu(IDR_ERRORBAR_MENU);
	if (!Result) return;

	pSubMenu = Menu.GetSubMenu(0);
	if (pSubMenu == NULL) return;

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
}


 void CSrErrorBar::OnErrorbarCopy()
 {
	 m_wndChild.Copy();
 }


 void CSrErrorBar::OnUpdateErrorbarCopy(CCmdUI *pCmdUI)
 {
	 pCmdUI->Enable(!m_wndChild.GetSelText().IsEmpty());
 }
