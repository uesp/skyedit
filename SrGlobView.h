/*===========================================================================
 *
 * File:		SrGlobView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRGLOBVIEW_H
#define __SRGLOBVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/srrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrGlobView Definition
 *
 *=========================================================================*/
class CSrGlobView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrGlobView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrGlobView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrGlobView)
  enum { IDD = IDD_GLOB_VIEW };
  CEdit		m_Value;
  CComboBox	m_Type;  
  CEdit		m_EditorID;
  CEdit		m_FormID;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrGlobView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrGlobView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrGlobView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrGlobView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrGlobView.H
 *=========================================================================*/
