/*===========================================================================
 *
 * File:		SrGmstView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRGMSTVIEW_H
#define __SRGMSTVIEW_H


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
 * Begin Class CSrGmstView Definition
 *
 *=========================================================================*/
class CSrGmstView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrGmstView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrGmstView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrGmstView)
  enum { IDD = IDD_GMST_VIEW };
  CEdit		m_Value;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  //}}AFX_DATA

  int OnPreSaveRecord (void);

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrGmstView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrGmstView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrGmstView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrGmstView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrGmstView.H
 *=========================================================================*/
