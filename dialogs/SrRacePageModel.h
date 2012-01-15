#pragma once
#include "afxwin.h"


class CSrRacePageModel : public CPropertyPage
{
	DECLARE_DYNAMIC(CSrRacePageModel)

	srraceinfo_t& m_RaceInfo;

public:
	CSrRacePageModel(srraceinfo_t& RaceInfo);
	virtual ~CSrRacePageModel();

	void GetControlData (void);
	void SetControlData (void);

	enum { IDD = IDD_RACE_MODELPAGE };

	CSrEditDlgHandler*	m_pDlgHandler;
	CSrRecordDialog*	m_pParent;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_MaleHeight;
	CEdit m_FemaleHeight;
	CEdit m_MaleModel;
	CEdit m_FemaleModel;
	CButton m_BodyParts;
	afx_msg void OnBnClickedSelectMalemodel();
	afx_msg void OnBnClickedSelectFemalemodel();
	CEdit m_MaleEgtModel;
	CEdit m_MaleHavokModel;
	CEdit m_FemaleEgtModel;
	CEdit m_FemaleHavokModel;
	afx_msg void OnBnClickedSelectMaleegtmodel();
	afx_msg void OnBnClickedSelectMalehavokmodel();
	afx_msg void OnBnClickedSelectFemaleegtmodel();
	afx_msg void OnBnClickedSelectFemalehavokmodel();
	afx_msg void OnBnClickedBodydata();
	CEdit m_DefaultVoice;
	afx_msg void OnBnClickedEditDefaultvoice();
	afx_msg void OnBnClickedSelectDefaultvoice();
	CEdit m_DefaultHairColor;
	afx_msg void OnBnClickedEditDefaulthaircolor();
	afx_msg void OnBnClickedSelectDefaulthaircolor();
	CEdit m_DecapitatedHead;
	afx_msg void OnBnClickedEditDecapitatedhead();
	afx_msg void OnBnClickedSelectDecapitatedhead();
	CEdit m_Material;
	afx_msg void OnBnClickedEditMaterial();
	afx_msg void OnBnClickedSelectMaterial();
	CEdit m_ImpactSet;
	afx_msg void OnBnClickedEditImpactset();
	afx_msg void OnBnClickedSelectImpactset();
	CEdit m_BloodFX;
	afx_msg void OnBnClickedEditBloodfx();
	afx_msg void OnBnClickedSelectBloodfx();
	CEdit m_OpenSound;
	afx_msg void OnBnClickedEditOpensound();
	afx_msg void OnBnClickedSelectOpensound();
	CEdit m_CloseSound;
	afx_msg void OnBnClickedEditClosesound();
	afx_msg void OnBnClickedSelectClosesound();
	CEdit m_Name8;
	afx_msg void OnBnClickedEditName8();
	afx_msg void OnBnClickedSelectName8();
	CEdit m_RName;
	afx_msg void OnBnClickedEditRname();
	afx_msg void OnBnClickedSelectRname();

	afx_msg void OnDropDefaultVoice (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDefaultHairColor (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDecapitatedHead (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDefaultVoice2 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDefaultHairColor2 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDecapitatedHead2 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropMaterial (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropImpactSet (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropBloodFX (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropOpenSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropCloseSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropName8 (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropRName (NMHDR* pNotifyStruct, LRESULT* pResult);
	CEdit m_DefaultVoice2;
	CEdit m_DefaultHairColor2;
	CEdit m_DecapitatedHead2;
	afx_msg void OnBnClickedEditDecapitatedhead2();
	afx_msg void OnBnClickedSelectDecapitatedhead2();
	afx_msg void OnBnClickedEditDefaulthaircolor2();
	afx_msg void OnBnClickedSelectDefaulthaircolor2();
	afx_msg void OnBnClickedEditDefaultvoice2();
	afx_msg void OnBnClickedSelectDefaultvoice2();
};
