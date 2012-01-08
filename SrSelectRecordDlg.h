/*===========================================================================
 *
 * File:		Srselectrecorddlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSELECTRECORDDLG_H
#define __SRSELECTRECORDDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/srespfile.h"
  #include "windows/srrecordlistctrl.h"
  #include "modfile/srmultirecordhandler.h"
#include "afxwin.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Optional callback function type */
  typedef bool (*SRRECSELDLGCALLBACK) (CSrRecord* pRecord, long UserData);

	/* Used to define a selection record dialog */
  struct srselrecdlginfo_t 
  {
	const srrectype_t*		pRecordType;		/* Type of record to display */
	const srrectype_t**		ppRecordArray;
	const TCHAR*			pTitle;

	srreclistcolinit_t*		pListColumns;
	const srrecfieldmap_t*  pFieldMap;

	srrecfieldid_t			SortField;

	SRRECSELDLGCALLBACK		pCheckFunc;
	long					UserData;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrSelectRecordDlg Definition
 *
 *=========================================================================*/
class CSrSelectRecordDlg : public CDialog {

  /*---------- Begin Protected Class Members ---------------------------*/
protected:
  srselrecdlginfo_t	m_DlgInfo;

  srformid_t		m_InitialFormID;
  CString			m_InitialEditorID;
  srformid_t		m_CurrentFormID;
  CString			m_CurrentEditorID;

  CSrRecord*		m_pPrevRecord;
  CSrRecord*		m_pCurrentRecord;

  bool				m_AllowNullRecord;		/* Allow a null record to be selected */
  bool				m_IsInitialized;

  CSrRecordHandler*	m_pRecordHandler;

  int				m_EditorIDCheck;
  bool				m_UpdateListOnChange;

  srrectype_t		m_CurrentTypeFilter;


  /*---------- Begin Protected Class Methods ---------------------------*/
protected:

	/* Get/set control data */
  void GetControlData      (void);
  void SetControlData      (void);
  void FillRecordList      (void);
  void FillRecordList      (const srrectype_t RecordType);
  void AddListColumns      (void);
  void UpdateCurrentRecord (void);
  int  UpdateEditorID      (void);
  void FillFilterList	   (void);


  /*---------- Begin Public Class Methods ------------------------------*/
public:
	/* Construction */
  CSrSelectRecordDlg(CWnd* pParent = NULL);

	/* Get class members */
  CSrRecord*   GetCurrentRecord   (void) { return (m_pCurrentRecord); }
  CSrRecord*   GetPrevRecord      (void) { return (m_pPrevRecord); }
  srformid_t   GetCurrentFormID   (void) { return (m_CurrentFormID); }
  const TCHAR* GetCurrentEditorID (void) { return (m_CurrentEditorID); }
  
	/* Set class members */
  void SetInitialFormID   (const srformid_t   FormID)   { m_InitialFormID   = FormID; }
  void SetInitialEditorID (const TCHAR*      pString)   { m_InitialEditorID = pString; }
  void SetPrevRecord      (CSrRecord*         pRecord)  { m_pPrevRecord     = pRecord; }
  void SetCurrentRecord   (CSrRecord*         pRecord)  { m_pCurrentRecord  = pRecord; }
  void SetRecordHandler   (CSrRecordHandler*  pHandler) { m_pRecordHandler  = pHandler; }
  void SetDlgInfo         (srselrecdlginfo_t& DlgInfo)  { m_DlgInfo         = DlgInfo; }
  void SetAllowNull       (const bool         Value)    { m_AllowNullRecord = Value; }

  enum { IDD = IDD_SELECTRECORD_DLG };
  CEdit			m_CurrentFormIDText;
  CEdit			m_PreviousFormIDText;
  CButton		m_ClearButton;
  CEdit			m_CurrentText;
  CEdit			m_PreviousText;
  CSrRecordListCtrl	m_RecordList;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);

protected:
  virtual BOOL OnInitDialog();
  afx_msg void OnClearButton();
  virtual void OnOK();
  afx_msg void OnItemchangedRecordlist(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnEditRecord (WPARAM lParam, LPARAM wParam);
  afx_msg void OnChangeCurrentText();
  afx_msg HBRUSH OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor);

  DECLARE_MESSAGE_MAP();

public:
	CStatic m_TypeFilterLabel;
	CComboBox m_TypeFilterList;
	afx_msg void OnCbnSelchangeTypefilterList();
};
/*===========================================================================
 *		End of Class CSrSelectRecordDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  bool SrSelectItemScript     (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectActor          (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectApparelEnchant (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectIngrediant     (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectScrollEnchant  (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectSound          (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectStaffEnchant   (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectWeaponEnchant  (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectKeyword        (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectKeyword        (CString& EditorID, CSrRecordHandler* pRecordHandler, const char* pFilter);
  bool SrSelectComponent      (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectEquipSlot      (CString& EditorID, CSrRecordHandler* pRecordHandler);
  bool SrSelectRecord         (CString& EditorID, CSrRecordHandler* pRecordHandler, const srrectype_t Type, const srrecfieldmap_t* pFieldMap);
  bool SrSelectOutfitItem     (CString& EditorID, CSrRecordHandler* pRecordHandler);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Srselectrecorddlg.H
 *=========================================================================*/
