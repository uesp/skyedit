/*===========================================================================
 *
 * File:		SrBatchlistctrl.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 *
 *
 *=========================================================================*/
#ifndef __SrBATCHLISTCTRL_H
#define __SRBATCHLISTCTRL_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/srespfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
		
	/* Column subitems */
  #define SR_BATCHEDIT_SUBITEM_FIELD	0
  #define SR_BATCHEDIT_SUBITEM_VALUE	1
  
	/* Custom messages */
  #define ID_BATCHEDIT_MSG_UPDATE	(WM_APP + 118)

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Holds information on each field being edited */
  struct srbatchfieldinfo_t 
  {
	srrecfieldid_t	FieldID;
	bool			Save;
	CSString		Value;
	CSString		Title;

	srbatchfieldinfo_t() {
		FieldID = 0;
		Save    = false;
	}
  };

  struct srbatchlistsort_t 
  {
	int  iSubItem;
	bool Reverse;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin class CSrBatchListCtrl
 *
 *=========================================================================*/
class CSrBatchListCtrl : public CListCtrl 
{

  /*---------- Begin Protected Class Members -------------------------*/
protected:
  int	m_SortSubItem;
  bool  m_SortReverse;


  /*---------- Begin Protected Class Methods -------------------------*/
protected:


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Constructor/Destructor */
  CSrBatchListCtrl();
  virtual ~CSrBatchListCtrl();

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrBatchListCtrl)
protected:
  //}}AFX_VIRTUAL

	/* Generated message map functions */
protected:
  //{{AFX_MSG(CSrBatchListCtrl)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnLButtonDown( UINT, CPoint );
  afx_msg void OnClick (NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of class CSrBatchListCtrl
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrBatchlistctrl.H
 *=========================================================================*/
