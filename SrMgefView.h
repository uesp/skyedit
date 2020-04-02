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
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


struct srmgeftypedlginfo_t
{
	srrectype_t	RecordType;
	int			NumAV;
	int			ForceAV1;
};


/*===========================================================================
 *
 * Begin Class CSrMgefView Definition
 *
 *=========================================================================*/
class CSrMgefView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrMgefView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	bool				m_IsInitialized;
	

  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrMgefView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_MGEF_VIEW };
	CEdit		m_EditorID;
	CEdit		m_ItemName;
	CEdit		m_Description;
	CEdit		m_FormID;
	CListBox	m_Keywords;
	CComboBox	m_SchoolList;
	CComboBox	m_ResistList;
	CButton		m_Conditions;

public:
	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

	void FillMagicFlagList (void);
	void SetMagicFlags (const dword Flags);
	dword GetMagicFlags (void);

	void GetCounterEffects (CSrMgefRecord* pEffect);
	void SetCounterEffects (CSrMgefRecord* pEffect);

	void GetEffectSounds (CSrMgefRecord* pEffect);
	void SetEffectSounds (CSrMgefRecord* pEffect);

	void UpdateEffectTypeControls (void);

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrMgefView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	DECLARE_MESSAGE_MAP();

public:	
	CEdit m_BaseCost;
	CEdit m_SkillLevel;
	CEdit m_SkillUsageMult;
	CComboBox m_ActorValue;
	CComboBox m_ActorValue2;
	CEdit m_SecondAVWeight;
	CComboBox m_CastType;
	CComboBox m_EffectType;
	CComboBox m_ResistType;
	CComboBox m_DeliveryType;
	CComboBox m_School;
	CComboBox m_SoundVolume;

	CEdit m_Area;
	CEdit m_DualCastScale;
	CEdit m_CastingDelay;

	CEdit m_TaperCurve;
	CEdit m_TaperWeight;
	CEdit m_TaperDuration;
	CEdit m_ScriptAIDataScore;
	CEdit m_ScriptAIDataDelay;
	
	CEdit m_Light;
	CEdit m_HitShader;
	CEdit m_EnchantShader;
	CEdit m_CastingArt;
	CEdit m_HitEffectArt;
	CEdit m_EnchantArt;
	CEdit m_EquipAbility;
	CEdit m_ImpactSet;
	CEdit m_ImageSpaceMod;
	CEdit m_Perk;
	CEdit m_Explosion;
	CEdit m_DualCast;
	CEdit m_EffectObject;
	CEdit m_Projectile;
	CEdit m_Menu;

	CListBox m_Scripts;
	CListBox m_MagicFlags;
	CListBox m_CounterEffects;
	CButton m_DispelEffectsCheck;

	void OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropCounterEffects (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditPerk();
	afx_msg void OnBnClickedSelectPerk();
	afx_msg void OnDropPerk (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditDualCast();
	afx_msg void OnBnClickedSelectDualCast();
	afx_msg void OnDropDualCast (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditLight();
	afx_msg void OnBnClickedSelectLight();
	afx_msg void OnDropLight (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditEffectObject();
	afx_msg void OnBnClickedSelectEffectObject();
	afx_msg void OnDropEffectObject (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditExplosion();
	afx_msg void OnBnClickedSelectExplosion();
	afx_msg void OnDropExplosion (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditProjectile();
	afx_msg void OnBnClickedSelectProjectile();
	afx_msg void OnDropProjectile (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditCastingArt();
	afx_msg void OnBnClickedSelectCastingArt();
	afx_msg void OnDropCastingArt (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditHitEffectArt();
	afx_msg void OnBnClickedSelectHitEffectArt();
	afx_msg void OnDropHitEffectArt (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditEnchantArt();
	afx_msg void OnBnClickedSelectEnchantArt();
	afx_msg void OnDropEnchantArt (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditEquipAbility();
	afx_msg void OnBnClickedSelectEquipAbility();
	afx_msg void OnDropEquipAbility (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditImpactSet();
	afx_msg void OnBnClickedSelectImpactSet();
	afx_msg void OnDropImpactSet(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditImageSpaceMod();
	afx_msg void OnBnClickedSelectImageSpaceMod();
	afx_msg void OnDropImageSpaceMod(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditHitShader();
	afx_msg void OnBnClickedSelectHitShader();
	afx_msg void OnDropHitShader(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditEnchantShader();
	afx_msg void OnBnClickedSelectEnchantShader();
	afx_msg void OnDropEnchantShader(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditMenu();
	afx_msg void OnBnClickedSelectMenu();
	afx_msg void OnDropMenu(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditDrawSound();
	afx_msg void OnBnClickedSelectDrawSound();
	afx_msg void OnDropDrawSound(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditReadySound();
	afx_msg void OnBnClickedSelectReadySound();
	afx_msg void OnDropReadySound(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditChargeSound();
	afx_msg void OnBnClickedSelectChargeSound();
	afx_msg void OnDropChargeSound(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditReleaseSound();
	afx_msg void OnBnClickedSelectReleaseSound();
	afx_msg void OnDropReleaseSound(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditCastLoopSound();
	afx_msg void OnBnClickedSelectCastLoopSound();
	afx_msg void OnDropCastLoopSound(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedEditOnHitSound();
	afx_msg void OnBnClickedSelectOnHitSound();
	afx_msg void OnDropOnHitSound(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
	
	afx_msg void OnBnClickedAddCountereffects();
	afx_msg void OnBnClickedEditCountereffects();
	afx_msg void OnBnClickedDelCountereffects();
	
	afx_msg void OnCbnSelchangeEffecttype();
	CEdit m_DrawSound;
	CEdit m_ChargeSound;
	CEdit m_ReadySound;
	CEdit m_ReleaseSound;
	CEdit m_CastLoopSound;
	CEdit m_OnHitSound;
	CButton m_EditEffectObject;
	CButton m_SelectEffectObject;
	CStatic m_EffectObjectLabel;
};
/*===========================================================================
 *		End of Class CSrMgefView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrMgefView.H
 *=========================================================================*/
