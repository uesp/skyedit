/*===========================================================================
 *
 * File:	Oblvleditdlg.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 2, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLVLEDITDLG_H
#define __OBLVLEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/obrecordvirtuallistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Return results */
  #define OB_LVLEDITDLG_RESULT_OK	IDOK
  #define OB_LVLEDITDLG_RESULT_CANCEL	IDCANCEL
  #define OB_LVLEDITDLG_RESULT_DELETE	201

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLvlEditDlg Definition
 *
 *=========================================================================*/
class CObLvlEditDlg : public CDialog {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CObLvloSubrecord*	m_pSubrecord;	/* Item being edited */
  CString		m_TitleValue;
  
  CObRecordHandler*	m_pRecordHandler;

  const obrectype_t*	m_pRecordTypes;

  bool			m_UpdateListOnChange;

  int			m_EditorIDCheck;
  obformid_t		m_ObjectFormID;
  obformid_t		m_ParentFormID;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:

	/* Helper initialize methods */
  void AddListColumns (void);
  void FillRecordList (void);
  void FillRecordList (const obrectype_t RecordType);
  int  UpdateEditorID (void);
  

  /*---------- Begin Public Class Methods -----------------------------*/
public:

	/* Constructor */
  CObLvlEditDlg(CWnd* pParent = NULL);

	/* Get class members */
  CObLvloSubrecord* GetSubrecord (void) { return (m_pSubrecord); }

	/* Set class members */
  void SetSubrecord       (CObLvloSubrecord* pSubrecord) { m_pSubrecord      = pSubrecord; }
  void SetTitleValue      (const TCHAR*         pString) { m_TitleValue      = pString; }
  void SetRecordHandler   (CObRecordHandler*   pHandler) { m_pRecordHandler  = pHandler; }
  void SetRecordTypes     ( const obrectype_t*   pTypes) { m_pRecordTypes    = pTypes; }
  void SetParentFormID    (const obformid_t      FormID) { m_ParentFormID    = FormID; }

	/* Set/get control data */
  void GetControlData (void);
  void SetControlData (void);
  

  //{{AFX_DATA(CObLvlEditDlg)
  enum { IDD = IDD_LVLEDIT_DLG };
  CEdit				m_FormID;
  CEdit				m_Level;
  CEdit				m_Count;
  CEdit				m_ObjectID;
  CObRecordVirtualListCtrl	m_RecordList;
	//}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObLvlEditDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObLvlEditDlg)
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
 *		End of Class CObLvlEditDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  int ObEditLvlItemDlg     (CObLvloSubrecord* pSubrecord, CObRecordHandler* pHandler, const obformid_t ParentFormID);
  int ObEditLvlSpellDlg    (CObLvloSubrecord* pSubrecord, CObRecordHandler* pHandler, const obformid_t ParentFormID);
  int ObEditLvlCreatureDlg (CObLvloSubrecord* pSubrecord, CObRecordHandler* pHandler, const obformid_t ParentFormID);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/



//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Oblvleditdlg.H
 *=========================================================================*/
