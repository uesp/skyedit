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
#include "afxwin.h"
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

  void OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult);
  

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

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

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
	
	
	CEdit m_BaseCost;
	CEdit m_SkillLevel;
	CButton m_HostileCheck;
	CButton m_RecoverCheck;
	CButton m_DetrimentalCheck;
	CButton m_PercentMagCheck;
	CButton m_SelfCheck;
	CButton m_FXPersistCheck;
	CButton m_BoundCheck;
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
