#pragma once
#include "afxwin.h"


class CSrRacePageBasic : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageBasic)

	srraceinfo_t& m_RaceInfo;

public:
	CSrRacePageBasic(srraceinfo_t& RaceInfo);
	virtual ~CSrRacePageBasic();

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

	void GetControlData (void);
	void SetControlData (void);


	enum { IDD = IDD_RACE_BASICPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ItemName;
	CEdit m_Description;
	CComboBox m_ActorValue[7];
	CEdit m_ActorSkill[7];
	virtual BOOL OnInitDialog();
	CButton m_RaceFlags;
	afx_msg void OnBnClickedRaceflags();
	CListBox m_SpellList;
	CListBox m_Keywords;
	afx_msg void OnBnClickedAddSpell();
	afx_msg void OnBnClickedEditSpell();
	afx_msg void OnBnClickedDelSpell();
	afx_msg void OnLbnDblclkSpells();
	afx_msg void OnBnClickedAddkeywordButton();
	afx_msg void OnBnClickedEditkeywordButton();
	afx_msg void OnBnClickedDelkeywordButton();
	afx_msg void OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSpells (NMHDR* pNotifyStruct, LRESULT* pResult);
	CListBox m_EquipSlots;
	afx_msg void OnBnClickedAddEquipslot();
	afx_msg void OnBnClickedEditEquipslot();
	afx_msg void OnBnClickedDelEquipslot();
	afx_msg void OnDropEquipSlots (NMHDR* pNotifyStruct, LRESULT* pResult);
	CEdit m_UnequipSlot;
	afx_msg void OnBnClickedEditUnequipslot();
	afx_msg void OnBnClickedSelectUnequipslot();
	afx_msg void OnDropUnequipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnLbnDblclkEquipslots();
};
