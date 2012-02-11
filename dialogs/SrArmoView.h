/*===========================================================================
 *
 * File:		SrArmoview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRARMOVIEW_H
#define __SRARMOVIEW_H


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
 * Begin Class CSrArmoView Definition
 *
 *=========================================================================*/
class CSrArmoView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrArmoView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
  CSrArmoView();

  virtual void GetControlData (void);
  virtual void SetControlData (void);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_ARMO_VIEW };
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
	CListBox	m_Keywords;
	CEdit		m_EquipSlot;
	CButton		m_Playable;
	CComboBox	m_ArmorType;
	CEdit		m_Description;
	CEdit		m_PickupSound;
	CEdit		m_DropSound;
	CEdit		m_Template;
	CEdit		m_Race;
	CEdit		m_Material;
	CEdit		m_ImpactData;
	CEdit		m_Rating;
	CButton		m_BodyParts;
	CEdit		m_ArmModel;
	CListBox	m_ArmaModels;
	CListBox	m_ScriptList;

public:

	/* ClassWizard generated virtual function overrides */
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);

protected:
  virtual ~CSrArmoView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	afx_msg void OnBnClickedEditEquipslot();
	afx_msg void OnBnClickedSelectequipslotButton();
	afx_msg void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedEditMaterial();
	afx_msg void OnBnClickedSelectMaterial();
	afx_msg void OnDropMaterial (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedEditRace();
	afx_msg void OnBnClickedSelectRace();
	afx_msg void OnDropRace (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedEditTemplate();
	afx_msg void OnBnClickedSelectTemplate();
	afx_msg void OnDropTemplate (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedEditImpactData();
	afx_msg void OnBnClickedSelectImpactData();
	afx_msg void OnDropImpactData (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropArmaModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedBodyparts();
	afx_msg void OnBnClickedAddArmamodel();
	afx_msg void OnBnClickedEditArmamodel();
	afx_msg void OnBnClickedDelArmamodel();
	afx_msg void OnLbnDblclkArmamodels();
	afx_msg void OnLbnDblclkKeywords();
	
	afx_msg void OnArmamenuAdd();
	afx_msg void OnArmamenuEdit();
	afx_msg void OnArmamenuEditBase();
	afx_msg void OnArmamenuDelete();
	afx_msg void OnUpdateArmamenuEdit(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);
	afx_msg void OnBnClickedBounds();
	CButton	m_Bounds;
};
/*===========================================================================
 *		End of Class CSrArmoView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrArmoview.H
 *=========================================================================*/
