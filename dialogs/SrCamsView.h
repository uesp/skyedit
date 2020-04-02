/*===========================================================================
 *
 * File:		SrCamsView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRCAMSVIEW_H
#define __SRCAMSVIEW_H


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
 * Begin Class CSrCamsView Definition
 *
 *=========================================================================*/
class CSrCamsView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrCamsView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrCamsView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
  enum { IDD = IDD_CAMS_VIEW };
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_Model;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrCamsView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();
  
public:

	CEdit m_ImageSpace;
	afx_msg void OnBnClickedEditImagespace();
	afx_msg void OnBnClickedSelectImagespace();
	afx_msg void OnDropImageSpace (NMHDR* pNotifyStruct, LRESULT* pResult);
	CEdit m_X1;
	CEdit m_Y1;
	CEdit m_Z1;
	CEdit m_X2;
	CEdit m_Y2;
	CEdit m_Z2;
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown4;
};
/*===========================================================================
 *		End of Class CSrCamsView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrCamsView.H
 *=========================================================================*/
