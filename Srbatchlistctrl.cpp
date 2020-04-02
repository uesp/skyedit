/*===========================================================================
 *
 * File:		SrBatchlistctrl.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implements the CSrBatchListCtrl class
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "SrBatchListCtrl.h"


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
 * Begin CSrBatchListCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrBatchListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSrBatchListCtrl)
	ON_NOTIFY_REFLECT(HDN_ITEMCLICK, OnItemclick)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//ON_NOTIFY_REFLECT(NM_RCLICK, OnClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrBatchListCtrl Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int CALLBACK s_DefaultBatchListSort (lParam1, lParam2, lParamSort);
 *
 * Default callback function for batch list sorting.
 *
 *=========================================================================*/
int CALLBACK s_DefaultBatchListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  srbatchfieldinfo_t* pInfo1 = (srbatchfieldinfo_t *) lParam1;
  srbatchfieldinfo_t* pInfo2 = (srbatchfieldinfo_t *) lParam2;
  srbatchlistsort_t*  pSort  = (srbatchlistsort_t  *) lParamSort;
  long		      Result;

  switch (pSort->iSubItem) {
    case SR_BATCHEDIT_SUBITEM_FIELD:
        Result = stricmp(pInfo1->Title, pInfo2->Title);
	break;
    case SR_BATCHEDIT_SUBITEM_VALUE:
        Result = stricmp(pInfo1->Value, pInfo2->Value);
	break;
    default:
	Result = 0;
	break;
  }
  
  if (pSort->Reverse) return (-Result);
  return (Result);
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultBatchListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Constructor
 *
 *=========================================================================*/
CSrBatchListCtrl::CSrBatchListCtrl() {
  m_SortSubItem = -1;
  m_SortReverse = 0;
}
/*===========================================================================
 *		End of Class CSrBatchListCtrl Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Destructor
 *
 *=========================================================================*/
CSrBatchListCtrl::~CSrBatchListCtrl() {
}
/*===========================================================================
 *		End of Class CSrBatchListCtrl Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnColumnclick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnColumnclick (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW*       pNMListView = (NM_LISTVIEW*)pNMHDR;
  srbatchlistsort_t  SortData;
  int	             SubItem;

  *pResult = 0;
  SubItem  = pNMListView->iSubItem;

  if (SubItem == m_SortSubItem) {
    m_SortReverse = !m_SortReverse;
  }
  else {
    m_SortReverse = false;
    m_SortSubItem = SubItem;
  }

  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);

  SortData.iSubItem = m_SortSubItem;
  SortData.Reverse  = m_SortReverse;
  SortItems(s_DefaultBatchListSort, (DWORD) &SortData);
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnColumnclick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnDblclk (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnDblclk (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnDblclk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnClick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnClick (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnClick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnLButtonDown (nFlags, Point);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnLButtonDown (UINT nFlags, CPoint Point) {
  LVHITTESTINFO HitTest;
  int		Result;

  CListCtrl::OnLButtonDown(nFlags, Point);

  HitTest.pt    = Point;
  HitTest.flags = 0;
  HitTest.iItem = -1;

  Result = SubItemHitTest(&HitTest);

  if (Result < 0) {
    GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);
    return;
  }
  
  SetItem(Result, 0, LVIF_STATE, "", 0, LVIS_SELECTED, LVIS_SELECTED, 0);
  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, Result, 0);
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnLButtonDown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnItemclick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnItemclick (NMHDR* pNMHDR, LRESULT* pResult) {
  HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnItemclick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnSize (UINT nType, int cx, int cy) {
  CListCtrl::OnSize(nType, cx, cy);
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnVScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);

  CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnVScroll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchListCtrl Event - void OnHScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CSrBatchListCtrl::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  GetParent()->SendMessage(ID_BATCHEDIT_MSG_UPDATE, -1, 0);

  CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}
/*===========================================================================
 *		End of Class Event CSrBatchListCtrl::OnHScroll()
 *=========================================================================*/