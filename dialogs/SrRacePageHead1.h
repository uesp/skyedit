#pragma once
#include "afxwin.h"


class CSrRacePageHead1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageHead1)

	bool				m_IsInitialized;
	srraceinfo_t&		m_RaceInfo;
	srraceheadinfo_t&	m_HeadInfo;
	bool				m_IsMale;
		

public:
	CSrRacePageHead1(srraceinfo_t& RaceInfo, const bool IsMale);
	virtual ~CSrRacePageHead1();

	void GetControlData (void);
	void SetControlData (void);

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

	enum { IDD = IDD_RACE_HEADPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_RacePresets;
	CListBox m_HairColors;
	CListBox m_FeatureSets;
	CEdit m_HeadFeature;
	afx_msg void OnBnClickedAddRacepreset();
	afx_msg void OnBnClickedEditRacepreset();
	afx_msg void OnBnClickedDelRacepreset();
	afx_msg void OnBnClickedAddHaircolor();
	afx_msg void OnBnClickedEditHaircolor();
	afx_msg void OnBnClickedDelHaircolor();
	afx_msg void OnBnClickedAddFeatureset();
	afx_msg void OnBnClickedEditFeatureset();
	afx_msg void OnBnClickedDelFeatureset();
	afx_msg void OnBnClickedEditHeadfeature();
	afx_msg void OnBnClickedSelectHeadfeature();
	afx_msg void OnDropRacePresets (NMHDR* pNotifyStruct, LRESULT* pResult); 
	afx_msg void OnDropHairColors (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropFeatureSets (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropHeadFeature (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnLbnDblclkRacepresets();
	afx_msg void OnLbnDblclkHaircolors();
	afx_msg void OnLbnDblclkFeaturesets();
};
