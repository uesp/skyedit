/*===========================================================================
 *
 * File:		SrEnchView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRENCHVIEW_H
#define __SRENCHVIEW_H


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


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
struct srench_effectdata_t
{
	CSrFormidSubrecord*	pEffect;
	CSrEfitSubrecord*	pEffectData;
	CSrConditionArray	Conditions;

	srench_effectdata_t()
	{
		pEffect = NULL;
		pEffectData = NULL;
	}

	~srench_effectdata_t()
	{
		delete pEffect;
		delete pEffectData;
	}
};

typedef CSrPtrArray<srench_effectdata_t> CSrEnchEffectArray;
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrEnchView Definition
 *
 *=========================================================================*/
class CSrEnchView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrEnchView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrEnchEffectArray		m_Effects;
	srench_effectdata_t*	m_pCurrentEffect;
	bool					m_IsInitialized;	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrEnchView();

	void CreateEffectArray (void);

	void SetEffectList    (void);
	int  AddEffectList    (srench_effectdata_t* pEffectData);
	void UpdateEffectList (const int ListIndex, const bool Update);

	void GetCurrentEffect (void);
	void SetCurrentEffect (srench_effectdata_t* pEffectData);
	void EnableEffectControls (const bool Enable);

	void OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult);
	int  OnDropCustomEffectData (srrldroprecords_t& DropItems);
	void OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropBaseEnchant (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropItemTypes (NMHDR* pNotifyStruct, LRESULT* pResult);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_ENCH_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;
  
public:

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

	virtual int  OnPreSaveRecord   (void);

	void UpdateAutoCalcControls();
	void ComputeAutoCost();

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrEnchView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();

public:
	CEdit m_BaseEnchantment;
	CEdit m_ItemTypes;
	CEdit m_EffectName;
	CButton m_SelectEffectButton;
	CButton m_EditEffectButton;
	CButton m_EffectConditions;
	CEdit m_Magnitude;
	CEdit m_Area;
	CEdit m_Duration;
	CEdit m_Charge;
	CEdit m_Cost;
	CEdit m_ChargeTime;
	CComboBox m_CastType;
	CComboBox m_EnchantType;
	CComboBox m_DeliveryType;	
	CButton m_AutoCalc;
	CButton m_ExtendDuration;
	CSrRecordListCtrl m_EffectList;

	afx_msg void OnBnClickedEditBaseenchant();
	afx_msg void OnBnClickedSelectbaseenchantButton();
	afx_msg void OnBnClickedEditItemtypes();
	afx_msg void OnBnClickedSelectitemtypesButton();
	afx_msg void OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedConditionButton();
	afx_msg void OnBnClickedEditEffect();
	afx_msg void OnBnClickedSelecteffectButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton2();
	afx_msg void OnConditionrecordCopy();
	afx_msg void OnConditionrecordPaste();
	afx_msg void OnConditionrecordDeleteAll();
	afx_msg void OnUpdateConditionrecordCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);
	afx_msg void OnBnClickedAutocalc();
	afx_msg LRESULT OnEditEffectMsg (WPARAM wParam, LPARAM lParam);
};
/*===========================================================================
 *		End of Class CSrEnchView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrEnchView.H
 *=========================================================================*/
