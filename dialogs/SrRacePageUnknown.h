#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSrRacePageUnknown dialog

class CSrRacePageUnknown : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageUnknown)

	srraceinfo_t& m_RaceInfo;

public:
	CSrRacePageUnknown(srraceinfo_t& RaceInfo);
	virtual ~CSrRacePageUnknown();

	void GetControlData (void);
	void SetControlData (void);


	enum { IDD = IDD_RACE_UNKNOWNPAGE };

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	CEdit m_Unknown[26];

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Tinl;
	CEdit m_PName;
	CEdit m_UName;
	CEdit m_VName;
	CListCtrl m_BodyNameList;
	afx_msg void OnLvnItemActivateBodynamelist(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
