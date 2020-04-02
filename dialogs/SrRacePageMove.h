#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CSrRacePageMove : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageMove)

	bool				m_IsInitialized;
	srraceinfo_t&		m_RaceInfo;
	srracemoveinfo_t*	m_pCurrentMoveType;

	void SetMoveTypeList (void);
	int AddMoveTypeList (srracemoveinfo_t* pMoveType);
	void SetMoveTypeCustomData(srrlcustomdata_t& CustomData, srracemoveinfo_t* pMoveType);
	void UpdateMoveTypeList(const int ListIndex, const bool Update);

	void SetCurrentMoveType (srracemoveinfo_t* pMoveType);
	void EnableMoveControls (void);
	void GetMoveTypeControlData (void);
	void SetMoveTypeControlData (void);

public:
	CSrRacePageMove(srraceinfo_t& RaceInfo); 
	virtual ~CSrRacePageMove();

	void GetControlData (void);
	void SetControlData (void);

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

	enum { IDD = IDD_RACE_MOVEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_MoveNames;
	virtual BOOL OnInitDialog();
	CEdit m_WalkMove;
	CEdit m_RunMove;
	CEdit m_SwimMove;
	CEdit m_FlyMove;
	CEdit m_SneakMove;
	afx_msg void OnBnClickedEditWalkmove();
	afx_msg void OnBnClickedSelectWalkmove();
	afx_msg void OnBnClickedEditRunmove();
	afx_msg void OnBnClickedSelectRunmove();
	afx_msg void OnBnClickedEditSwimmove();
	afx_msg void OnBnClickedSelectSwimmove();
	afx_msg void OnBnClickedEditFlymove();
	afx_msg void OnBnClickedSelectFlymove();
	afx_msg void OnBnClickedEditSneakmove();
	afx_msg void OnBnClickedSelectSneakmove();
	afx_msg void OnDropWalkMove (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropRunMove (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSwimMove (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropFlyMove (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSneakMove (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropMoveType (NMHDR* pNotifyStruct, LRESULT* pResult);

	CSrRecordListCtrl m_MoveTypeList;
	CEdit m_MoveType;
	afx_msg void OnBnClickedEditMovetype();
	afx_msg void OnBnClickedSelectMovetype();
	CButton m_SelectMoveType;
	CButton m_EditMoveType;
	CEdit m_MoveUnknown[11];
	CButton m_AddMoveType;
	CButton m_DeleteMoveType;
	afx_msg void OnBnClickedAddMovetype();
	afx_msg void OnBnClickedDeleteMovetype();
	afx_msg void OnLvnItemchangedMovetypelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropMoveTypeList (NMHDR* pNotifyStruct, LRESULT* pResult);
};
