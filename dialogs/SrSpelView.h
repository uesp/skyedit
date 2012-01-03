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

	void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropPerk (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:

  //{{AFX_DATA(CSrSpelView)
  enum { IDD = IDD_SPEL_VIEW };
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_ItemName;
  //}}AFX_DATA

public:

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

	virtual int  OnPreSaveRecord   (void);

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrSpelView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrSpelView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrSpelView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:
	
		
	CEdit m_EquipSlot;
	afx_msg void OnBnClickedEditEquipSlot();
	afx_msg void OnBnClickedSelectequipslotButton();
	CSrRecordListCtrl m_EffectList;
	afx_msg void OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_EffectName;
	CButton m_SelectEffectButton;
	CButton m_EditEffectButton;
	CButton m_EffectConditions;
	CEdit m_Magnitude;
	CEdit m_Area;
	CEdit m_Duration;
	afx_msg void OnBnClickedConditionButton();
	afx_msg void OnBnClickedEditEffect();
	afx_msg void OnBnClickedSelecteffectButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	CEdit m_Charge;
	CEdit m_Cost;
	CEdit m_Description;
	CEdit m_Perk;
	afx_msg void OnBnClickedEditPerk();
	afx_msg void OnBnClickedSelectperkButton();
	CEdit m_SpellFlags;
	CComboBox m_SpellType;
	CComboBox m_CastType;
	CComboBox m_CastAnim;
	CEdit m_CastTime;
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CButton m_AutoCalc;
};
/*===========================================================================
 *		End of Class CSrSpelView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrSpelView.H
 *=========================================================================*/
