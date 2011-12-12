/*===========================================================================
 *
 * File:		SrMgefView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRMGEFVIEW_H
#define __SRMGEFVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	//#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrMgefView Definition
 *
 *=========================================================================*/
class CSrMgefView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrMgefView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrMgefView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrMgefView)
  enum { IDD = IDD_MGEF_VIEW };
  CEdit		m_EditorID;
  CEdit		m_ItemName;
  CEdit		m_DName;
  CEdit		m_FormID;
  CListBox  m_Keywords;
  CComboBox m_SchoolList;
  CComboBox m_TypeList;
  CButton   m_Conditions;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrMgefView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrMgefView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrMgefView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:
	
	
};
/*===========================================================================
 *		End of Class CSrMgefView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrMgefView.H
 *=========================================================================*/
