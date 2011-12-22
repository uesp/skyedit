/*===========================================================================
 *
 * File:		SrMgefView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRMGEFVIEW_H
#define __SRMGEFVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
#include "afxwin.h"
#include "afxcmn.h"
 //#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrMgefView Definition
 *
 *=========================================================================*/
class CSrMgefView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrMgefView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrMgefSnddArray	m_SoundCopy;
	bool				m_IsInitialized;
	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrMgefView();

  void OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrMgefView)
  enum { IDD = IDD_MGEF_VIEW };
  CEdit		m_EditorID;
  CEdit		m_ItemName;
  CEdit		m_DName;
  CEdit		m_FormID;
  CListBox  m_Keywords;
  CComboBox m_SchoolList;
  CComboBox m_TypeList;
  CButton   m_Conditions;
  //}}AFX_DATA

public:

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);
	void SetSoundList (void);
	int AddSoundList (srmgefsndddata_t* pSoundData);
	void UpdateSoundList (const int ListIndex, const bool Update);

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrMgefView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrMgefView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* Generated message map functions */
  //{{AFX_MSG(CSrMgefView)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:
	
	
	CEdit m_BaseCost;
	CEdit m_SkillLevel;
	CButton m_HostileCheck;
	CButton m_RecoverCheck;
	CButton m_DetrimentalCheck;
	CButton m_PercentMagCheck;
	CButton m_SelfCheck;
	CButton m_NoAreaCheck;
	CButton m_FXPersistCheck;
	CButton m_BoundCheck;
	CEdit m_EffectPlayRate;
	CComboBox m_ActorValue;
	CComboBox m_CastType;
	
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown4;
	CEdit m_Unknown5;
	CEdit m_Unknown6;
	CEdit m_Unknown7;
	CEdit m_Unknown8;
	CEdit m_Unknown9;
	CEdit m_Unknown10;
	CEdit m_Unknown13;
	CEdit m_Unknown14;
	CEdit m_Unknown15;
	
	CEdit m_Light;
	CEdit m_Shader1;
	CEdit m_Shader2;
	CEdit m_Art1;
	CEdit m_Art2;
	CEdit m_Art3;
	CEdit m_Art4;
	CEdit m_ImpactSet1;
	CEdit m_ImpactSet2;
	CEdit m_Perk;
	CEdit m_Explosion;
	CEdit m_DualCast;
	CEdit m_SecondSpell;
	CEdit m_Projectile;
	
	CButton m_WardCheck;
	CButton	m_UnknownCheck1;
	CButton m_UnknownCheck2;
	CButton m_UnknownCheck3;
	CButton m_UnknownCheck4;
	CButton m_UnknownCheck5;
	CButton m_UnknownCheck6;
	CButton m_UnknownCheck7;
	CButton m_UnknownCheck8;
	CButton m_UnknownCheck9;

	afx_msg void OnBnClickedEditPerk();
	afx_msg void OnBnClickedSelectPerk();
	afx_msg void OnDropPerk (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditDualCast();
	afx_msg void OnBnClickedSelectDualCast();
	afx_msg void OnDropDualCast (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditLight();
	afx_msg void OnBnClickedSelectLight();
	afx_msg void OnDropLight (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditSecondSpell();
	afx_msg void OnBnClickedSelectSecondSpell();
	afx_msg void OnDropSecondSpell (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditExplosion();
	afx_msg void OnBnClickedSelectExplosion();
	afx_msg void OnDropExplosion (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditProjectile();
	afx_msg void OnBnClickedSelectProjectile();
	afx_msg void OnDropProjectile (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditArt1();
	afx_msg void OnBnClickedSelectArt1();
	afx_msg void OnDropArt1 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditArt2();
	afx_msg void OnBnClickedSelectArt2();
	afx_msg void OnDropArt2 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditArt3();
	afx_msg void OnBnClickedSelectArt3();
	afx_msg void OnDropArt3 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditArt4();
	afx_msg void OnBnClickedSelectArt4();
	afx_msg void OnDropArt4 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditImpactSet1();
	afx_msg void OnBnClickedSelectImpactSet1();
	afx_msg void OnDropImpactSet1 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditImpactSet2();
	afx_msg void OnBnClickedSelectImpactSet2();
	afx_msg void OnDropImpactSet2 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditShader1();
	afx_msg void OnBnClickedSelectShader1();
	afx_msg void OnDropShader1 (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditShader2();
	afx_msg void OnBnClickedSelectShader2();
	afx_msg void OnDropShader2 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedSoundButton();

	afx_msg LRESULT OnEditSoundMsg (WPARAM wParam, LPARAM lParam);

	CButton m_SoundButton;
	afx_msg void OnCbnSelchangeCasttype();
	CSrRecordListCtrl m_Sounds;
	afx_msg void OnBnClickedDeletesound();
	afx_msg void OnBnClickedAddsound();
};
/*===========================================================================
 *		End of Class CSrMgefView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrMgefView.H
 *=========================================================================*/
