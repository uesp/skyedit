/*===========================================================================
 *
 * File:		Srlvleditdlg.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRLVLEDITDLG_H
#define __SrLVLEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/srrecordvirtuallistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Return results */
  #define SR_LVLEDITDLG_RESULT_OK		IDOK
  #define SR_LVLEDITDLG_RESULT_CANCEL	IDCANCEL
  #define SR_LVLEDITDLG_RESULT_DELETE	201

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrLvlEditDlg Definition
 *
 *=========================================================================*/
class CSrLvlEditDlg : public CDialog {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CSrLvloSubrecord*	m_pSubrecord;	/* Item being edited */
  CString			m_TitleValue;
  
  CSrRecordHandler*	m_pRecordHandler;

  const srrectype_t*	m_pRecordTypes;

  bool				m_UpdateListOnChange;

  int				m_EditorIDCheck;
  srformid_t		m_ObjectFormID;
  srformid_t		m_ParentFormID;


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
  CSrLvlEditDlg(CWnd* pParent = NULL);

	/* Get class members */
  CSrLvloSubrecord* GetSubrecord (void) { return (m_pSubrecord); }

	/* Set class members */
  void SetSubrecord       (CSrLvloSubrecord* pSubrecord) { m_pSubrecord      = pSubrecord; }
  void SetTitleValue      (const char*          pString) { m_TitleValue      = pString; }
  void SetRecordHandler   (CSrRecordHandler*   pHandler) { m_pRecordHandler  = pHandler; }
  void SetRecordTypes     (const srrectype_t*    pTypes) { m_pRecordTypes    = pTypes; }
  void SetParentFormID    (const srformid_t      FormID) { m_ParentFormID    = FormID; }

	/* Set/get control data */
  void GetControlData (void);
  void SetControlData (void);
  

  //{{AFX_DATA(CSrLvlEditDlg)
  enum { IDD = IDD_LVLEDIT_DLG };
  CEdit				m_FormID;
  CEdit				m_Level;
  CEdit				m_Count;
  CEdit				m_ObjectID;
  CSrRecordVirtualListCtrl	m_RecordList;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrLvlEditDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrLvlEditDlg)
  afx_msg void OnDeleteButton();
  virtual BOOL OnInitDialog();
  afx_msg void OnChangeEditorid();
  afx_msg void OnKillfocusEditorid();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnItemchangedRecordlist(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrLvlEditDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int SrEditLvlItemDlg     (CSrLvloSubrecord* pSubrecord, CSrRecordHandler* pHandler, const srformid_t ParentFormID);
  int SrEditLvlSpellDlg    (CSrLvloSubrecord* pSubrecord, CSrRecordHandler* pHandler, const srformid_t ParentFormID);
  int SrEditLvlCreatureDlg (CSrLvloSubrecord* pSubrecord, CSrRecordHandler* pHandler, const srformid_t ParentFormID);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Srlvleditdlg.H
 *=========================================================================*/
