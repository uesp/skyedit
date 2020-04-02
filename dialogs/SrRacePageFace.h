#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CSrRacePageFace : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageFace)

	bool				m_IsInitialized;
	srraceinfo_t&		m_RaceInfo;
	CSrPhwtSubrecord*	m_pCurrentWeight;

	int  AddWeightList (CSrPhwtSubrecord* pWeight);
	void EnableWeightControls (void);
	void SetCurrentWeight (CSrPhwtSubrecord* pWeight);
	void GetWeightControlData (void);
	void SetWeightControlData (void);
	void UpdateWeightList(const int ListIndex, const bool Update);

public:
	CSrRacePageFace(srraceinfo_t& RaceInfo);
	virtual ~CSrRacePageFace();

	void GetControlData (void);
	void SetControlData (void);

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

	enum { IDD = IDD_RACE_FACEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_FaceKeys;
	afx_msg void OnBnClickedAddFacekey();
	afx_msg void OnBnClickedEditFacekey();
	afx_msg void OnBnClickedDelFacekey();
	afx_msg void OnLbnSelchangeFacekeys();
	afx_msg void OnLbnDblclkFacekeys();
	CSrRecordListCtrl m_FaceWeights;
	CEdit m_Weight[16];
	CButton m_AddFaceWeight;
	afx_msg void OnBnClickedAddFaceweight();
	afx_msg void OnBnClickedDeleteFaceweight();
	afx_msg void OnDropFaceWeights (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnLvnItemchangedFaceweights(NMHDR *pNMHDR, LRESULT *pResult);
};
