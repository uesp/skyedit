/*===========================================================================
 *
 * File:		UndoBar.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implements the dockable undo control bar in the main frame.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "undobar.h"
#include "mainfrm.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrUndoBar Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrUndoBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CSrUndoBar)
	ON_WM_CREATE()
	ON_LBN_DBLCLK(12345, OnDblclkUndoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrUndoBar Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Constructor
 *
 *=========================================================================*/
CSrUndoBar::CSrUndoBar() {

  m_pLastUndoArray = NULL;

}
/*===========================================================================
 *		End of Class CSrUndoBar Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Destructor
 *
 *=========================================================================*/
CSrUndoBar::~CSrUndoBar() {
}
/*===========================================================================
 *		End of Class CSrUndoBar Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Event - int OnCreate (lpCreateStruct);
 *
 *=========================================================================*/
int CSrUndoBar::OnCreate (LPCREATESTRUCT lpCreateStruct) {
  if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1) return -1;
  SetSCBStyle(GetSCBStyle() | SCBS_SIZECHILD);

  if (!m_wndChild.Create(WS_CHILD|WS_VISIBLE| LBS_HASSTRINGS | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
			CRect(0,0,0,0), this, 12345)) {
    return -1;
  }

  m_wndChild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

  if (!m_font.CreateStockObject(DEFAULT_GUI_FONT)) {
    if (!m_font.CreatePointFont(80, "MS Sans Serif")) {
      return -1;
    }
  }

  m_wndChild.SetFont(&m_font);
  return 0;
}
/*===========================================================================
 *		End of Class Event CSrUndoBar::OnCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Method - void UpdateList (pUndoItems);
 *
 *=========================================================================*/
void CSrUndoBar::UpdateList (CSrUndoItemArray* pUndoItems) {
  CSrUndoItem* pItem;
  CSString     Buffer;
  int          Index;
  int          ListIndex;

  m_pLastUndoArray = pUndoItems;

	/* Clear the current content */
  m_wndChild.ResetContent();
  if (pUndoItems == NULL) return;

  for (Index = (int)pUndoItems->GetSize() - 1; Index >= 0; --Index) {
    pItem = pUndoItems->GetAt(Index);

    ListIndex = m_wndChild.AddString(pItem->MakeString(Buffer));
    if (ListIndex >= 0) m_wndChild.SetItemData(ListIndex, (DWORD) pItem);
  }

  //int ID = m_wndChild.GetDlgCtrlID();
}
/*===========================================================================
 *		End of Class Method CSrUndoBar::UpdateList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Method - CSrUndoItem* GetCurrentUndoItem (void);
 *
 *=========================================================================*/
CSrUndoItem* CSrUndoBar::GetCurrentUndoItem (void) {
  CSrUndoItem* pItem;
  int          ListIndex;

  ListIndex = m_wndChild.GetCurSel();
  if (ListIndex < 0) return (NULL);

  pItem = (CSrUndoItem *) m_wndChild.GetItemData(ListIndex);
  return (pItem);
}
/*===========================================================================
 *		End of Class Method CSrUndoBar::GetCurrentUndoItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Method - void LockUpdates (Lock);
 *
 *=========================================================================*/
void CSrUndoBar::LockUpdates (const bool Lock) {

  if (Lock) {
    m_wndChild.SetRedraw(FALSE);
  }
  else {
    m_wndChild.SetRedraw(TRUE);
    m_wndChild.RedrawWindow();
  }

}
/*===========================================================================
 *		End of Class Method CSrUndoBar::LockUpdates()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrUndoBar Event - void OnDblclkUndoList (void);
 *
 *=========================================================================*/
void CSrUndoBar::OnDblclkUndoList (void) {
  AfxGetMainWnd()->SendMessage(SRE_MSG_UNDOITEMS, 0, 0);
}
/*===========================================================================
 *		End of Class Event CSrUndoBar::OnDblclkUndoList()
 *=========================================================================*/
