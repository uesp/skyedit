/*===========================================================================
 *
 * File:		SrOtftView.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	8 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SROTFTVIEW_H
#define __SROTFTVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "windows/srrecordlistctrl.h"
	#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrOtftView Definition
 *
 *=========================================================================*/
class CSrOtftView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrOtftView)
	DECLARE_SRRECUIFIELDS()

  /*---------- Begin Protected Class Members ----------------------------*/
protected:
  

  /*---------- Begin Protected Class Methods ----------------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrOtftView();         
	virtual ~CSrOtftView();

		/* Helper update methods */
	void FillItemList   (void);
	void SaveSubrecords (void);
	int  AddItemList    (const srformid_t FormID);
	void UpdateItem     (const int ListIndex, CSrIdRecord* pRecord);

		/* Drag/drop helpers */
	int OnDropCustomData (srrldroprecords_t& DropItems);
	int OnDropRecords    (srrldroprecords_t& DropItems);


  /*---------- Begin Public Class Methods -------------------------------*/
public:

		/* Get and set data */
	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

  		/* Listener events */
	virtual int OnListenCleanRecord     (CSrListenEvent* pEvent);
	virtual int OnListenUpdateRecord    (CSrListenEvent* pEvent);
	virtual int GetListenEvents         (void) { return (SR_EVENT_CLEANRECORD | SR_EVENT_UPDATERECORD); }

	enum { IDD = IDD_OTFT_VIEW };
	CEdit				m_EditorID;
	CEdit				m_FormID;
	CSrRecordListCtrl	m_ItemList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
  

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
	LRESULT OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam);
	virtual void OnInitialUpdate (void);
	afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
	afx_msg void OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult);
  
	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnOutfitlistAdd();
	afx_msg void OnOutfitlistDelete();
	afx_msg void OnOutfitlistEdit();
	afx_msg void OnOutfitlistEditBase();
	afx_msg void OnUpdateOutfitlistMenu(CCmdUI *pCmdUI);
};
/*===========================================================================
 *		End of Class CSrOtftView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrOtftView.H
 *=========================================================================*/
