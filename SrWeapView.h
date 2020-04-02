/*===========================================================================
 *
 * File:		SrWeapview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRWEAPVIEW_H
#define __SRWEAPVIEW_H


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
 * Begin Class CSrWeapView Definition
 *
 *=========================================================================*/
class CSrWeapView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrWeapView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrWeapView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrWeapView)
  enum { IDD = IDD_WEAP_VIEW };
  CButton	m_QuestItem;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Enchantment;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_Model;
  CEdit		m_Damage;
  CEdit		m_EnchantPoints;
  CListBox  m_Keywords;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrWeapView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrWeapView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

		/* Generated message map functions */
	//{{AFX_MSG(CSrWeapView)
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:

	CEdit m_EquipSlot;
	afx_msg void OnBnClickedEditEquipslot();
	afx_msg void OnBnClickedSelectequipslotButton();
	afx_msg void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropImpactSet (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropStaticModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDrawSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSheathSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSwingSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropBoundSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropTrapSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropBaseWeapon (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedEditImpactset();
	afx_msg void OnBnClickedSelectImpactset();
	afx_msg void OnBnClickedEditStaticmodel();
	afx_msg void OnBnClickedSelectStaticmodel();
	afx_msg void OnBnClickedEditDrawsound();
	afx_msg void OnBnClickedSelectDrawsound();
	afx_msg void OnBnClickedEditSheathsound();
	afx_msg void OnBnClickedSelectSheathsound();
	afx_msg void OnBnClickedEditSwingsound();
	afx_msg void OnBnClickedSelectSwingsound();
	afx_msg void OnBnClickedEditBoundsound();
	afx_msg void OnBnClickedSelectBoundsound();
	afx_msg void OnBnClickedEditTrapsound();
	afx_msg void OnBnClickedSelectTrapsound();
	CEdit m_ImpactSet;
	CEdit m_StaticModel;
	CEdit m_DrawSound;
	CEdit m_SheathSound;
	CEdit m_SwingSound;
	CEdit m_BoundSound;
	CEdit m_TrapSound;
	CEdit m_BaseWeapon;
	afx_msg void OnBnClickedEditBaseweapon();
	afx_msg void OnBnClickedSelectBaseweapon();
	CEdit m_NName;
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown5;
	CEdit m_Unknown6;
	CEdit m_Unknown7;
	CEdit m_Unknown8;
	CEdit m_Unknown9;
	CEdit m_Unknown10;
	CEdit m_Unknown11;
	CEdit m_Unknown12;
	CEdit m_Unknown13;
	CEdit m_Unknown14;
	CEdit m_Unknown15;
	CEdit m_Unknown16;
	CEdit m_UnknownFlags1;
	CEdit m_Description;
	CComboBox m_Type;
	CListBox m_Scripts;
};
/*===========================================================================
 *		End of Class CSrWeapView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrWeapview.H
 *=========================================================================*/
