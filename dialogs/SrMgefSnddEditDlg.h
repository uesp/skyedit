/*===========================================================================
 *
 * File:		SrMgefSndddEditdlg.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	21 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRMGEFSNDDEDITDLG_H
#define __SRMGEFSNDDEDITDLG_H


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
  #define SR_MGEFSNDDEDITDLG_RESULT_OK		IDOK
  #define SR_MGEFSNDDEDITDLG_RESULT_CANCEL	IDCANCEL
  #define SR_MGEFSNDDEDITDLG_RESULT_DELETE	201

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrMgefSnddEditDlg Definition
 *
 *=========================================================================*/
class CSrMgefSnddEditDlg : public CDialog {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  srmgefsndddata_t*		m_pSoundData;
  CString				m_TitleValue;
  
  CSrRecordHandler*		m_pRecordHandler;

  const srrectype_t*	m_pRecordTypes;

  bool					m_UpdateListOnChange;

  int					m_EditorIDCheck;
  srformid_t			m_ObjectFormID;
  srformid_t			m_ParentFormID;


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
  CSrMgefSnddEditDlg(CWnd* pParent = NULL);

	/* Get class members */
  srmgefsndddata_t* GetSoundData (void) { return (m_pSoundData); }

	/* Set class members */
  void SetSoundData       (srmgefsndddata_t*      pData) { m_pSoundData      = pData; }
  void SetTitleValue      (const char*          pString) { m_TitleValue      = pString; }
  void SetRecordHandler   (CSrRecordHandler*   pHandler) { m_pRecordHandler  = pHandler; }
  void SetRecordTypes     (const srrectype_t*    pTypes) { m_pRecordTypes    = pTypes; }
  void SetParentFormID    (const srformid_t      FormID) { m_ParentFormID    = FormID; }

	/* Set/get control data */
  void GetControlData (void);
  void SetControlData (void);
  
  enum { IDD = IDD_MGEFSNDDEDIT_DLG };
  CEdit				m_FormID;
  CEdit				m_Value;
  CEdit				m_ObjectID;
  CSrRecordVirtualListCtrl	m_RecordList;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();

  afx_msg void OnDeleteButton();
  virtual BOOL OnInitDialog();
  afx_msg void OnChangeEditorid();
  afx_msg void OnKillfocusEditorid();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnItemchangedRecordlist(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnActivateList (WPARAM wParam, LPARAM lParam);

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrMgefSnddEditDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int SrEditMgefSnddDlg (srmgefsndddata_t* pData, CSrRecordHandler* pHandler, const srformid_t ParentFormID);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrMgefSnddEditdlg.H
 *=========================================================================*/
