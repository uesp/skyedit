#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CSrRacePageTint : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageTint)

	bool				m_IsInitialized;
	srraceinfo_t&		m_RaceInfo;
	srraceheadinfo_t&	m_HeadInfo;
	bool				m_IsMale;

	srraceheadtintinfo_t*	m_pCurrentTint;
	srraceheadtintdata_t*	m_pCurrentTintData;

	void SetCurrentTint (srraceheadtintinfo_t* pTint);
	void EnableTintControls (void);
	void GetTintControlData (void);
	void SetTintControlData (void);
	int AddTintList (srraceheadtintinfo_t* pTint);
	void CreateTintCustomData (srrlcustomdata_t& CustomData, srraceheadtintinfo_t* pTint);
	void UpdateTintList (const int ListIndex, const bool Update);

	int AddTintDataList(srraceheadtintdata_t *pTintData);
	void UpdateTintDataList (const int ListIndex, const bool Update);
	void CreateTintDataCustomData (srrlcustomdata_t& CustomData, srraceheadtintdata_t* pTintData);
	void EnableTintDataControls (void);
	void SetCurrentTintData (srraceheadtintdata_t* pTintData);
	void GetTintDataControlData (void);
	void SetTintDataControlData (void);
	void UpdateTintCustomData (void);

	void DropListCreateTint (CSrRefSubrecordArray& Subrecords);

public:
	CSrRacePageTint(srraceinfo_t& RaceInfo, const bool IsMale);
	virtual ~CSrRacePageTint();

	void GetControlData (void);
	void SetControlData (void);

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;

	enum { IDD = IDD_RACE_TINTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Index;
	CEdit m_MaskFile;
	CEdit m_TindColor;
	CButton m_SelectMaskFile;
	CButton m_EditTind;
	CButton m_SelectTind;
	CEdit m_Tinp;
	CSrRecordListCtrl m_TintDataList;
	CSrRecordListCtrl m_TintList;
	CButton m_AddTintData;
	CButton m_DeleteTintData;
	CButton m_DeleteTint;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedTintlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddTint();
	afx_msg void OnBnClickedDeleteTint();
	afx_msg void OnBnClickedSelectTintmask();
	afx_msg void OnBnClickedEditTindcolor();
	afx_msg void OnBnClickedSelectTindcolor();
	afx_msg void OnBnClickedAddTintdata();
	afx_msg void OnBnClickedDeleteTintdata();
	afx_msg void OnDropMaskFile (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropTintList (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropTintDataList (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropTindColor (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDataColor (NMHDR* pNotifyStruct, LRESULT* pResult);
	CEdit m_DataTinc;
	CEdit m_DataTinv;
	CEdit m_DataTirs;
	CButton m_EditDataTinc;
	CButton m_SelectDataTinc;
	afx_msg void OnLvnItemchangedTintdatalist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEditDatatinc();
	afx_msg void OnBnClickedSelectDatatinc();
};
