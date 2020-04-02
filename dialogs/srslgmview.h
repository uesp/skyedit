/*===========================================================================
 *
 * File:		SrSlgmView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSLGMVIEW_H
#define __SRSLGMVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrSlgmView Definition
 *
 *=========================================================================*/
class CSrSlgmView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrSlgmView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrSlgmView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
  enum { IDD = IDD_SLGM_VIEW };
  CButton	m_QuestItem;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_Model;
  CListBox  m_Keywords;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrSlgmView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:
	CComboBox m_Capacity;
	CComboBox m_CurrentSoul;
	CEdit m_FilledGem;
	CButton m_Dangerous;
	afx_msg void OnBnClickedEditFilledgem();
	afx_msg void OnBnClickedSelectFilledgem();
	afx_msg void OnDropFilledGem (NMHDR* pNotifyStruct, LRESULT* pResult);
};
/*===========================================================================
 *		End of Class CSrSlgmView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrMiscView.H
 *=========================================================================*/
