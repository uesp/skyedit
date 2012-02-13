/*===========================================================================
 *
 * File:		SrSpelView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	14 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSPELVIEW_H
#define __SRSPELVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "windows/srrecordlistctrl.h"
	#include "afxwin.h"
	#include "afxcmn.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


struct srspel_effectdata_t
{
	CSrFormidSubrecord*	pEffect;
	CSrEfitSubrecord*	pEffectData;
	CSrConditionArray	Conditions;

	srspel_effectdata_t()
	{
		pEffect = NULL;
		pEffectData = NULL;
	}

	~srspel_effectdata_t()
	{
		delete pEffect;
		delete pEffectData;
	}
};

typedef CSrPtrArray<srspel_effectdata_t> CSrSpelEffectArray;


/*===========================================================================
 *
 * Begin Class CSrSpelView Definition
 *
 *=========================================================================*/
class  CSrSpelView: public CSrRecordDialog 
{
  DECLARE_DYNCREATE(CSrSpelView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrSpelEffectArray		m_Effects;
	srspel_effectdata_t*	m_pCurrentEffect;
	bool					m_IsInitialized;
	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrSpelView();

	void CreateEffectArray (void);

	void SetEffectList    (void);
	int  AddEffectList    (srspel_effectdata_t* pEffectData);
	void UpdateEffectList (const int ListIndex, const bool Update);

	void GetCurrentEffect (void);
	void SetCurrentEffect (srspel_effectdata_t* pEffectData);
	void EnableEffectControls (const bool Enable);
		
	void OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult);
	int  OnDropCustomEffectData (srrldroprecords_t& DropItems);  

	void OnDropInventoryModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropPerk (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_SPEL_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;

public:
	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);
	virtual int  OnPreSaveRecord   (void);

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual ~CSrSpelView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();

public:	
	CEdit m_EquipSlot;
	CSrRecordListCtrl m_EffectList;
	CEdit m_EffectName;
	CButton m_SelectEffectButton;
	CButton m_EditEffectButton;
	CButton m_EffectConditions;
	CEdit m_Magnitude;
	CEdit m_Area;
	CEdit m_Duration;
	CEdit m_Charge;
	CEdit m_Cost;
	CEdit m_Description;
	CEdit m_Perk;
	CEdit m_SpellFlags;
	CEdit m_Range;
	CEdit m_ChargeTime;
	CEdit m_CastDuration;
	CComboBox m_SpellType;
	CComboBox m_CastType;
	CComboBox m_DeliveryType;
	CButton m_AutoCalc;
	CButton m_PCStartSpell;
	CButton m_AreaIgnoresLOS;
	CButton m_IgnoreResistance;
	CButton m_NoAbsorbReflect;
	CButton m_NoDualCastMods;
	CComboBox m_TargetType;
	CEdit m_InventoryModel;

	afx_msg void OnBnClickedEditEquipSlot();
	afx_msg void OnBnClickedSelectequipslotButton();
	afx_msg void OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEditPerk();
	afx_msg void OnBnClickedSelectperkButton();
	afx_msg void OnConditionrecordCopy();
	afx_msg void OnConditionrecordPaste();
	afx_msg void OnConditionrecordDeleteAll();
	afx_msg void OnUpdateConditionrecordCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);	
	afx_msg void OnBnClickedEditInventorymodel();
	afx_msg void OnBnClickedSelectInventorymodel();
	afx_msg void OnBnClickedConditionButton();
	afx_msg void OnBnClickedEditEffect();
	afx_msg void OnBnClickedSelecteffectButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg LRESULT OnEditEffectMsg (WPARAM wParam, LPARAM lParam);
	
};
/*===========================================================================
 *		End of Class CSrSpelView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrSpelView.H
 *=========================================================================*/
