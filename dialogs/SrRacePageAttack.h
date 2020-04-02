#pragma once
#include "afxcmn.h"
#include "afxwin.h"


class CSrRacePageAttack : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageAttack)

	srraceinfo_t&		m_RaceInfo;
	bool				m_IsInitialized;
	srraceattackinfo_t*	m_pCurrentAttack;

	int  AddAttack (srraceattackinfo_t* pAttack);
	void EnableAttackControls (void);
	void SetCurrentAttack (srraceattackinfo_t* pAttack);
	void GetAttackControlData (void);
	void SetAttackControlData (void);
	void SetAttackCustomData(srrlcustomdata_t& CustomData, srraceattackinfo_t* pAttack);
	void UpdateAttackList(const int ListIndex, const bool Update);

public:
	CSrRacePageAttack(srraceinfo_t& RaceInfo);
	virtual ~CSrRacePageAttack();

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

	void GetControlData (void);
	void SetControlData (void);

	enum { IDD = IDD_RACE_ATTACKPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CSrRecordListCtrl m_AttackList;
	CEdit m_AttackKeyword;
	afx_msg void OnBnClickedEditAttackkeyword();
	afx_msg void OnBnClickedSelectAttackkeyword();
	CEdit m_AttackUnknown1;
	CEdit m_AttackUnknown2;
	CEdit m_AttackUnknown3;
	CEdit m_AttackUnknown4;
	CEdit m_AttackUnknown5;
	CEdit m_AttackUnknown6;
	CEdit m_AttackUnknown7;
	CEdit m_AttackUnknown8;
	CEdit m_AttackUnknown9;
	CEdit m_AttackUnknown10;
	CButton m_EditKeyword;
	CButton m_SelectKeyword;
	virtual BOOL OnInitDialog();
	CEdit m_AttackEvent;
	CButton m_DeleteAttack;
	afx_msg void OnLvnItemchangedAttacklist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddAttack();
	afx_msg void OnBnClickedDeleteAttack();
	afx_msg void OnDropKeyword (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropAttackList (NMHDR* pNotifyStruct, LRESULT* pResult);
};
