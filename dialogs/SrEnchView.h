/*===========================================================================
 *
 * File:		SrEnchView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRENCHVIEW_H
#define __SRENCHVIEW_H


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
 * Begin Class CSrEnchView Definition
 *
 *=========================================================================*/
class CSrEnchView : public CSrRecordDialog 
{
  DECLARE_DYNCREATE(CSrEnchView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrEnchView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:

  //{{AFX_DATA(CSrEnchView)
  enum { IDD = IDD_ENCH_VIEW };
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_ItemName;
  //}}AFX_DATA

public:

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrEnchView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrEnchView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrEnchView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:
	
		
	CEdit m_BaseEnchantment;
	CEdit m_ItemTypes;
	afx_msg void OnBnClickedEditBaseenchant();
	afx_msg void OnBnClickedSelectbaseenchantButton();
	afx_msg void OnBnClickedEditItemtypes();
	afx_msg void OnBnClickedSelectitemtypesButton();
};
/*===========================================================================
 *		End of Class CSrEnchView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrEnchView.H
 *=========================================================================*/
