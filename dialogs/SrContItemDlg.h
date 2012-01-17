/*===========================================================================
 *
 * File:		SrContItemdlg.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRCONTITEMDLG_H
#define __SRCONTITEMDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "windows/srrecordvirtuallistctrl.h"
	#include "srlvllistinfo.h"
	#include "afxwin.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

		/* Return results */
	#define SR_CONTITEMDLG_RESULT_OK		IDOK
	#define SR_CONTITEMDLG_RESULT_CANCEL	IDCANCEL
	#define SR_CONTITEMDLG_RESULT_DELETE	201

		/* Forward class declaration */
	class CSrEditDlgHandler;

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrContItemDlg Definition
 *
 *=========================================================================*/
class CSrContItemDlg : public CDialog {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
	srlvllistinfo_t*		m_pListInfo;	/* Item being edited */
	CString					m_TitleValue;
  
	CSrRecordHandler*		m_pRecordHandler;
	CSrEditDlgHandler*		m_pDlgHandler;

	const srrectype_t*		m_pRecordTypes;

	bool					m_UpdateListOnChange;

	int						m_EditorIDCheck;
	srformid_t				m_ObjectFormID;
	srformid_t				m_ParentFormID;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:

		/* Helper initialize methods */
	void AddListColumns (void);
	void FillRecordList (void);
	void FillRecordList (const srrectype_t RecordType);
	int  UpdateEditorID (void);
  

  /*---------- Begin Public Class Methods -----------------------------*/
public:

	/* Constructor */
  CSrContItemDlg(CWnd* pParent = NULL);

	/* Get class members */
  srlvllistinfo_t* GetLvlListInfo (void) { return m_pListInfo; }

	/* Set class members */
  void SetLvlListInfo     (srlvllistinfo_t*   pListInfo) { m_pListInfo       = pListInfo; }
  void SetTitleValue      (const char*          pString) { m_TitleValue      = pString; }
  void SetRecordHandler   (CSrRecordHandler*   pHandler) { m_pRecordHandler  = pHandler; }
  void SetDlgHandler      (CSrEditDlgHandler*  pHandler) { m_pDlgHandler     = pHandler; }
  void SetRecordTypes     (const srrectype_t*    pTypes) { m_pRecordTypes    = pTypes; }
  void SetParentFormID    (const srformid_t      FormID) { m_ParentFormID    = FormID; }

	/* Set/get control data */
  void GetControlData (void);
  void SetControlData (void);

  enum { IDD = IDD_CONTITEMEDIT_DLG };
  CEdit				m_FormID;
  CEdit				m_Count;
  CEdit				m_ObjectID;
  CSrRecordVirtualListCtrl	m_RecordList;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();

protected:
	afx_msg void OnDeleteButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditorid();
	afx_msg void OnKillfocusEditorid();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnActivateList (WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnNMDblclkRecordlist(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_Faction;
	CEdit m_MinRank;
	CEdit m_Condition;
	afx_msg void OnBnClickedEditFaction();
	afx_msg void OnBnClickedSelectFaction();
};
/*===========================================================================
 *		End of Class CSrContItemDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int SrEditContItemDlg(srlvllistinfo_t* pListInfo, CSrEditDlgHandler* pHandler, const srformid_t ParentFormID);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrContItemDlg.H
 *=========================================================================*/
