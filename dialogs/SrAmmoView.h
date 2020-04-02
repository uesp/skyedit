/*===========================================================================
 *
 * File:		SrAmmoview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRAMMOVIEW_H
#define __SRAMMOVIEW_H


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
 * Begin Class CSrAmmoView Definition
 *
 *=========================================================================*/
class CSrAmmoView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrAmmoView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrAmmoView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:

  enum { IDD = IDD_AMMO_VIEW };
  CEdit		m_Value;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_Model;
  CEdit		m_Damage;
  CListBox  m_Keywords;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);


protected:
  virtual ~CSrAmmoView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif


  DECLARE_MESSAGE_MAP();

public:

	CButton m_IgnoreResist;
	CButton m_Vanish;
	CEdit m_DropSound;
	CEdit m_PickupSound;
	CEdit m_Projectile;
	afx_msg void OnBnClickedEditProjectile();
	afx_msg void OnBnClickedSelectprojectileButton();
	afx_msg void OnDropProjectile (NMHDR* pNotifyStruct, LRESULT* pResult);
};
/*===========================================================================
 *		End of Class CSrAmmoView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrAmmoView.H
 *=========================================================================*/
