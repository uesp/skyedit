/*===========================================================================
 *
 * File:		SrKywdView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRKYWDVIEW_H
#define __SRKYWDVIEW_H


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
 * Begin Class CSrKywdView Definition
 *
 *=========================================================================*/
class CSrKywdView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrKywdView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrKywdView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrKywdView)
  enum { IDD = IDD_KEYWORD_VIEW };
  CEdit		m_CName;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrKywdView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrKywdView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrKywdView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrKywdView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrKywdView.H
 *=========================================================================*/
