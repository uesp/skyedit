/*===========================================================================
 *
 * File:		Srfinddlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRFINDDLG_H
#define __SRFINDDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/srrecorddialog.h"
  #include "windows/srrecordvirtuallistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrFindDlg Definition
 *
 *=========================================================================*/
class CSrFindDlg : public CSrRecordDialog 
{
  DECLARE_DYNCREATE(CSrFindDlg);

  /*---------- Begin Protected Class Members -------------------------*/
protected:
  CString	m_TextData;
  byte*		m_pBinaryData;
  dword		m_BinarySize;

  srfinddata_t	m_FindData;

  CSrCallback	m_Callback;


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Constructor */
  CSrFindDlg(CWnd* pParent = NULL);
  virtual ~CSrFindDlg();

  	/* Set and get control data */
  virtual void  ClearControlData (void);
  virtual void  GetControlData   (void);
  virtual void  SetControlData   (void);
  virtual void  SetTitle         (const SSCHAR* pEditorID);

  	/* Check if the dialog is editing the given record */
  virtual bool IsEditRecord (CSrRecord* pRecord);

	/* Events */
  virtual void OnApply  (void);
  virtual void OnSave	(void);
  virtual void OnCancel	(void);

	/* Listener events */
  virtual int OnListenAddRecord       (CSrListenEvent* pEvent);
  virtual int OnListenCleanRecord     (CSrListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CSrListenEvent* pEvent);
  virtual int GetListenEvents         (void)                   { return (SR_EVENT_ADDRECORD | SR_EVENT_CLEANRECORD | SR_EVENT_UPDATERECORD); }

	/* Conver the current text data to binary */
  bool ConvertBinaryData (void);

  //{{AFX_DATA(CSrFindDlg)
  enum { IDD = IDD_FIND_DLG };
  CStatic	m_FindLabel;
  CButton	m_CaseSensitiveCheck;
  CButton			m_BinaryCheck;
  CComboBox			m_SearchCombo;
  CSrRecordVirtualListCtrl	m_FindList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrFindDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrFindDlg)
  afx_msg void OnFindButton();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrFindDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Srfinddlg.H
 *=========================================================================*/
