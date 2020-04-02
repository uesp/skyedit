/*===========================================================================
 *
 * File:		Srbatcheditdlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRBATCHEDITDLG_H
#define __SRBATCHEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/srrecorddialog.h"
  #include "srbatchlistctrl.h"
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

  typedef CSrPtrArray<srbatchfieldinfo_t> CSrBatchFieldInfoArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrBatchEditDlg Definition
 *
 *=========================================================================*/
class CSrBatchEditDlg : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrBatchEditDlg);

  /*---------- Begin Protected Class Members -----------------------*/
protected:
  CSrRefRecordArray			m_Records;

  int						m_CurrentEditItem;

  bool						m_Initialized;
  bool						m_IsChanging;
  
  CSrBatchFieldInfoArray	m_Fields;
  dword						m_SavedFieldCount;


  /*---------- Begin Protected Class Methods -----------------------*/
protected:

	/* Creates the field array */
  void AddFields           (CSrRecord* pRecord);
  void RemoveMissingFields (CSrRecord* pRecord);
  void CreateFieldArray    (void);
  void FillFieldList       (void);

	/* Helper update methods */
  CSrRecord* PrepareRecord (CSrRecord* pRecord);
  bool       UpdateFields  (CSrRecord* pRecord);

	/* Update the edit control */
  void UpdateEditCtrl (const int NewIndex);


  /*---------- Begin Public Class Methods --------------------------*/
public:

	/* Construction */
  CSrBatchEditDlg(CWnd* pParent = NULL);

  	/* Set records to the edited */
  void AddEditRecords (CSrRefRecordArray& Records);
  void AddEditRecords (CSrRecordArray&    Records);

	/* Get class members */
  CSrRefRecordArray& GetRecords    (void) { return (m_Records); }
  dword              GetNumRecords (void) { return (m_Records.GetSize()); }

	/* Check if the dialog is editing the given record */
  virtual bool IsEditRecord (CSrRecord* pRecord);

	/* Set and get control data */
  virtual void  ClearControlData (void);
  virtual void  GetControlData   (void);
  virtual void  SetControlData   (void);
  virtual void  SetTitle         (const SSCHAR* pEditorID);
  virtual void  UpdateSaveFields (void);

	/* Events */
  virtual void OnApply  (void);
  virtual void OnSave	(void);
  virtual void OnCancel	(void);


  //{{AFX_DATA(CSrBatchEditDlg)
  enum { IDD = IDD_BATCHEDIT_DLG };
  CSrBatchListCtrl	m_FieldList;
  CEdit			m_EditCtrl;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrBatchEditDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrBatchEditDlg)
	afx_msg void OnItemchangedFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusBatchEdit(void);
	afx_msg void OnSetfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditCtrl (void);
	afx_msg void OnUncheckAll (void);
	afx_msg void OnCheckAll (void);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClickFieldList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnEditUpdate (WPARAM mParam, LPARAM lParam);
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP()

};
/*===========================================================================
 *		End of Class CSrBatchEditDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Srbatcheditdlg.H
 *=========================================================================*/
