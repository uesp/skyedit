/*===========================================================================
 *
 * File:		SrPerkView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRPERKVIEW_H
#define __SRPERKVIEW_H


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
 * Begin Definitions
 *
 *=========================================================================*/
	#define SRPERK_EFFECTTYPE_CUSTOMQUEST 0x10000
	#define SRPERK_EFFECTTYPE_CUSTOMSPELL 0x20000
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrPerkView Definition
 *
 *=========================================================================*/
class CSrPerkView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrPerkView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrPerkSectionArray		m_Sections;
	srperksectioninfo_t*	m_pCurrentSection;
	bool					m_IsInitialized;
	bool					m_IsUpdating;

	static srperkeffectinfo_t s_EffectInfoQuest;
	static srperkeffectinfo_t s_EffectInfoSpell;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrPerkView();

	virtual void CopyConditions (void);

	void CopyPerkSections      (void);
	void FillPerkSectionList   (void);
	int  AddPerkSectionList    (srperksectioninfo_t* pSection);
	void UpdatePerkSectionList (const int ListIndex, const bool Update);
	void UpdateSectionList     (srperksectioninfo_t* pSection);
	void FillPerkEffectList    (void);
	void FillPerkFunctionList  (void);

	void SetCurrentSection (srperksectioninfo_t* pSection);
	void SetSectionCustomData(srrlcustomdata_t& CustomData, srperksectioninfo_t* pSection);

	void EnableSectionControls (void);
	void UpdateSectionLabels (void);
	void UpdateSectionConditionLabels (void);

	void GetSectionData (void);
	void SetSectionData (void);

	CString GetPerkSectionDataString (srperksectioninfo_t& Section);

	void OnEditSectionConditions(const dword Index);

	srperksectioninfo_t* FindPerkSection(CSrPrkeSubrecord* pPrke);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_PERK_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);
	virtual int   OnPreSaveRecord  (void);

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrPerkView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:
	CEdit m_Description;
	CEdit m_NextPerk;
	CComboBox m_Unknown1;
	CComboBox m_Unknown2;
	CComboBox m_Unknown3;
	CButton m_Conditions;

	CSrRecordListCtrl m_SectionList;
	CEdit m_SectionPriority;
	CEdit m_SectionRank;
	CStatic m_SectionEditorIDLabel;
	CEdit m_SectionEditorID;
	CButton m_SectionConditions[SRPERK_EFFECT_MAXCONDTYPES];
	CButton m_EditEditorIDButton;
	CButton m_SelectEditorIDButton;
	CComboBox m_SectionActorValue;
	CEdit m_SectionValue;
	CStatic m_SectionValueLabel;
	CComboBox m_SectionEffectType;
	CComboBox m_SectionFunctionType;

	afx_msg void OnBnClickedEditNextperk();
	afx_msg void OnBnClickedSelectNextperk();	
	afx_msg void OnBnClickedAddperkButton();
	afx_msg void OnBnClickedDeleteperkButton();	
	afx_msg void OnDropNextPerk (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedSectionConditions1();
	afx_msg void OnBnClickedSectionConditions2();
	afx_msg void OnBnClickedSectionConditions3();
	afx_msg void OnBnClickedEditSectioneditorid();
	afx_msg void OnBnClickedSelectSectioneditorid();
	afx_msg void OnCbnSelchangeSectiontype();
	afx_msg void OnCbnSelchangeSectionFunctionType();
	afx_msg void OnLvnItemchangedPerkdataList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropSectionList (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg int OnDropCustomSectionData (srrldroprecords_t& DropItems);
	afx_msg void OnPerksectionAdd();
	afx_msg void OnPerksectionDelete();
	afx_msg void OnPerksectionDuplicate();
	afx_msg void OnUpdatePerksectionEdit(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);
	afx_msg void OnCbnSelchangeSectionEffectType();
	CStatic m_SectionValueLabel2;
	CEdit m_SectionValue2;
	CListBox m_Scripts;


	int m_ContextConditionIndex;
	afx_msg void OnConditionrecordCopy();
	afx_msg void OnConditionrecordPaste();
	afx_msg void OnConditionrecordDeleteAll();
	afx_msg void OnUpdateConditionrecordCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI);	

};
/*===========================================================================
 *		End of Class CSrPerkView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrPerkView.H
 *=========================================================================*/
