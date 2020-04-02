/*===========================================================================
 *
 * File:		SrShouView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSHOUVIEW_H
#define __SRSHOUVIEW_H


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
 * Begin Class CSrShouView Definition
 *
 *=========================================================================*/
class CSrShouView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrShouView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	CSrShouView();
	virtual void GetControlData (void);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
  enum { IDD = IDD_SHOU_VIEW };
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrShouView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();
  
public:

	CEdit m_Description;
	CEdit m_StaticModel;
	afx_msg void OnBnClickedEditStaticmodel();
	afx_msg void OnBnClickedSelectStaticmodel();
	afx_msg void OnBnClickedEditPowerword1();
	afx_msg void OnBnClickedSelectPowerword1();
	afx_msg void OnBnClickedEditSpell1();
	afx_msg void OnBnClickedSelectSpell1();
	afx_msg void OnBnClickedEditPowerword2();
	afx_msg void OnBnClickedSelectPowerword2();
	afx_msg void OnBnClickedEditSpell2();
	afx_msg void OnBnClickedSelectSpell2();
	afx_msg void OnBnClickedEditPowerword3();
	afx_msg void OnBnClickedSelectPowerword3();
	afx_msg void OnBnClickedEditSpell3();
	afx_msg void OnBnClickedSelectSpell3();
	CEdit m_PowerWord1;
	CEdit m_Spell1;
	CEdit m_Recharge1;
	CEdit m_PowerWord2;
	CEdit m_Spell2;
	CEdit m_Recharge2;
	CEdit m_PowerWord3;
	CEdit m_Spell3;
	CEdit m_Recharge3;
	afx_msg void OnDropStaticModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSpell1 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSpell2 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSpell3 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropPowerWord1 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropPowerWord2 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropPowerWord3 (NMHDR* pNotifyStruct, LRESULT* pResult);
};
/*===========================================================================
 *		End of Class CSrShouView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrShouView.H
 *=========================================================================*/
