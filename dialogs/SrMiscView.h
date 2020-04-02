/*===========================================================================
 *
 * File:		SrMiscView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRMISCVIEW_H
#define __SRMISCVIEW_H


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
 * Begin Class CSrMiscView Definition
 *
 *=========================================================================*/
class CSrMiscView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrMiscView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrMiscView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
  enum { IDD = IDD_MISC_VIEW };
  CButton	m_QuestItem;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_Model;
  CEdit		m_PickupSound;
  CEdit		m_DropSound;
  CListBox  m_Keywords;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrMiscView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();
  
public:

	CListBox m_Scripts;
};
/*===========================================================================
 *		End of Class CSrMiscView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrMiscView.H
 *=========================================================================*/
