/*===========================================================================
 *
 * File:		SrEcznView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	9 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRECZNVIEW_H
#define __SRECZNVIEW_H


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
 * Begin Class CSrEcznView Definition
 *
 *=========================================================================*/
class CSrEcznView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrEcznView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrEcznView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
  enum { IDD = IDD_ECZN_VIEW };
  CEdit		m_EditorID;
  CEdit		m_FormID;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrEcznView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();
  
public:

	CEdit m_Rank;
	CEdit m_MinLevel;
	CEdit m_Unknown3;
	CEdit m_Faction;
	CEdit m_Location;
	CButton m_ZoneReset;
	CButton m_ZoneUnknown1;
	CButton m_ZoneUnknown2;
	afx_msg void OnBnClickedEditFaction();
	afx_msg void OnBnClickedSelectFaction();
	afx_msg void OnBnClickedEditLocation();
	afx_msg void OnBnClickedSelectLocation();
	afx_msg void OnDropFaction (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropLocation (NMHDR* pNotifyStruct, LRESULT* pResult);
};
/*===========================================================================
 *		End of Class CSrEcznView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrEcznView.H
 *=========================================================================*/
