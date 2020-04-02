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
#include "afxwin.h"
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
  CString		m_TextData;
  byte*			m_pBinaryData;
  dword			m_BinarySize;
  srformid_t	m_FindFormID;

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

  enum { IDD = IDD_FIND_DLG };
  CStatic	m_FindLabel;
  CButton	m_CaseSensitiveCheck;
  CButton			m_BinaryCheck;
  CComboBox			m_SearchCombo;
  CSrRecordVirtualListCtrl	m_FindList;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();

protected:
  afx_msg void OnFindButton();

  DECLARE_MESSAGE_MAP();

public:
	CButton m_FormIDCheck;
	CButton m_FindInScripts;
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
