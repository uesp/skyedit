/*===========================================================================
 *
 * File:		Srlvliview.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRLVLIVIEW_H
#define __SRLVLIVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "windows/srrecordlistctrl.h"
	#include "afxwin.h"
	#include "srlvllistinfo.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrLvliView Definition
 *
 *=========================================================================*/
class CSrLvliView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrLvliView)
	DECLARE_SRRECUIFIELDS()

  /*---------- Begin Protected Class Members ----------------------------*/
protected:
	CSrLvlListInfoArray		m_LvlListInfo;


  /*---------- Begin Protected Class Methods ----------------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrLvliView();         
	virtual ~CSrLvliView();

		/* Helper update methods */
	void FillItemList   (void);
	void SaveSubrecords (void);
	int  AddItemList    (srlvllistinfo_t* pInfo);
	void UpdateItem     (const int ListIndex, srlvllistinfo_t* pInfo);

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

	enum { IDD = IDD_LVLI_VIEW };
	CButton		m_CalculateEach;
	CButton		m_CalculateAll;
	CEdit			m_ChanceNone;
	CEdit			m_EditorID;
	CEdit			m_FormID;
	CSrRecordListCtrl	m_ItemList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
  

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void OnInitialUpdate (void);
	afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
	afx_msg void OnLvllistEdit();
	afx_msg void OnUpdateLvllistEdit(CCmdUI* pCmdUI);
	afx_msg void OnLvllistAdd();
	afx_msg void OnLvllistDelete();
	afx_msg void OnUpdateLvllistDelete(CCmdUI* pCmdUI);
	afx_msg void OnMinusCount();
	afx_msg void OnAddCount();
	afx_msg void OnMinusLevel();
	afx_msg void OnAddLevel();
	afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam);
	afx_msg void OnLvlEditrecord();
	afx_msg void OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult);
	  
	DECLARE_MESSAGE_MAP();

public:
	CButton m_UseAll;
	CEdit m_Global;
	afx_msg void OnBnClickedEditGlobal();
	afx_msg void OnBnClickedSelectGlobal();
};
/*===========================================================================
 *		End of Class CSrLvliView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Srlvliview.H
 *=========================================================================*/
