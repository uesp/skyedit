/*===========================================================================
 *
 * File:		SrScrlView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSCRLVIEW_H
#define __SRSCRLVIEW_H


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


struct srscrl_effectdata_t
{
	CSrFormidSubrecord*	pEffect;
	CSrEfitSubrecord*	pEffectData;
	CSrConditionArray	Conditions;

	srscrl_effectdata_t()
	{
		pEffect = NULL;
		pEffectData = NULL;
	}

	~srscrl_effectdata_t()
	{
		delete pEffect;
		delete pEffectData;
	}
};

typedef CSrPtrArray<srscrl_effectdata_t> CSrScrlEffectArray;


/*===========================================================================
 *
 * Begin Class CSrScrlView Definition
 *
 *=========================================================================*/
class  CSrScrlView: public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrScrlView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrScrlEffectArray		m_Effects;
	srscrl_effectdata_t*	m_pCurrentEffect;
	bool					m_IsInitialized;
	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrScrlView();

	void CreateEffectArray (void);

	void SetEffectList    (void);
	int  AddEffectList    (srscrl_effectdata_t* pEffectData);
	void UpdateEffectList (const int ListIndex, const bool Update);

	void GetCurrentEffect (void);
	void SetCurrentEffect (srscrl_effectdata_t* pEffectData);
	void EnableEffectControls (const bool Enable);
		
	void OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult);
	int  OnDropCustomEffectData (srrldroprecords_t& DropItems);  

	void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropPerk (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_SCRL_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;
	CEdit		m_EquipSlot;
	CEdit		m_EffectName;
	CButton		m_SelectEffectButton;
	CButton		m_EditEffectButton;
	CButton		m_EffectConditions;
	CEdit		m_Magnitude;
	CEdit		m_Area;
	CEdit		m_Duration;
	CEdit		m_Cost;
	CEdit		m_Description;
	CComboBox	m_CastType;
	CEdit		m_ChargeTime;
	CSrRecordListCtrl m_EffectList;  

public:

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);
	virtual int  OnPreSaveRecord   (void);

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual ~CSrScrlView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();

public:
	CEdit m_CastDuration;
	CEdit m_Range;
	CButton m_DestructData;
	CButton m_AutoCalc;
	CButton m_AreaIgnoresLOS;
	CButton m_ScriptAlwaysApplies;
	CButton m_NoAbsorbReflect;
	CButton m_ForceExplode;
	CEdit m_Value;
	CEdit m_Weight;
	CListBox m_Keywords;
	CEdit m_Model;
	CComboBox m_DeliveryType;
	CEdit m_InventoryModel;
	
	afx_msg void OnBnClickedEditEquipSlot();
	afx_msg void OnBnClickedSelectequipslotButton();
	afx_msg void OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedConditionButton();
	afx_msg void OnBnClickedEditEffect();
	afx_msg void OnBnClickedSelecteffectButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnConditionrecordCopy();
	afx_msg void OnConditionrecordPaste();
	afx_msg void OnConditionrecordDeleteAll();
	afx_msg void OnUpdateConditionrecordCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);	
	afx_msg void OnBnClickedEditInventorymodel();
	afx_msg void OnBnClickedSelectInventorymodel();
	afx_msg LRESULT OnEditEffectMsg (WPARAM wParam, LPARAM lParam);
	afx_msg void OnDropInventoryModel (NMHDR* pNotifyStruct, LRESULT* pResult);
};
/*===========================================================================
 *		End of Class CSrScrlView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrScrlView.H
 *=========================================================================*/
