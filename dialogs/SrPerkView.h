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


struct srperk_subsection_t
{
	CSrByteSubrecord	Prkc;
	CSrConditionArray	Conditions;

	srperk_subsection_t()
	{
		Prkc.Initialize(SR_NAME_PRKC, 1);
		Prkc.InitializeNew();
	}

	~srperk_subsection_t()
	{
	}

};

typedef CSrPtrArray<srperk_subsection_t> CSrPerkSubsectionArray;


struct srperk_section_t
{
	CSrPrkeSubrecord		Prke;
	CSrPerkDataSubrecord	Data;
	CSrPerkSubsectionArray	Subsections;	
	CSrByteSubrecord*		pEpft;
	CSrLStringSubrecord*	pEpf2;
	CSrDwordSubrecord*		pEpf3;
	CSrEpfdSubrecord*		pEpfd;
	CSrDataSubrecord		Prkf;

	srperk_section_t()
	{
		InitializeNew();
	}

	srperk_section_t(CSrRecord* pRecord, const dword Index)
	{
		InitializeNew();
		CopyFrom(pRecord, Index);
	}

	dword CountSubsections (void)
	{
		dword Count = 0;

		for (dword i = 0; i < Subsections.GetSize(); ++i)
		{
			Count += Subsections[i]->Conditions.GetSize();
		}

		return Count;
	}

	void InitializeNew (void)
	{
		pEpft = NULL;
		pEpf2 = NULL;
		pEpf3 = NULL;
		pEpfd = NULL;

		Prke.Initialize(SR_NAME_PRKE, 3);
		Prke.InitializeNew();

		Data.Initialize(SR_NAME_DATA, 4);
		Data.SetDataType(SR_PERKDATA_TYPE01);
		Data.InitializeNew();

		//Epft.Initialize(SR_NAME_EPFT, 1);
		//Epft.InitializeNew();
		//Epft.SetValue(SP_EPFDTYPE_FLOAT);

		//Epfd.Initialize(SR_NAME_EPFD, 4);
		//Epfd.InitializeNew();
		//Epfd.SetDataType(SP_EPFDTYPE_FLOAT);

		Prkf.Initialize(SR_NAME_PRKF, 0);
		Prkf.InitializeNew();
	}
		
	~srperk_section_t()
	{
		delete pEpft;
		delete pEpf2;
		delete pEpf3;
		delete pEpfd;
	}

	void CreateNewEpft (void)
	{
		if (pEpft) delete pEpft;
		pEpft = new CSrByteSubrecord;

		pEpft->Initialize(SR_NAME_EPFT, 1);
		pEpft->InitializeNew();
		pEpft->SetValue(SP_EPFDTYPE_FLOAT);
	}

	void CreateNewEpf2 (void)
	{
		if (pEpf2) delete pEpf2;
		pEpf2 = new CSrLStringSubrecord;

		pEpf2->Initialize(SR_NAME_EPF2, 0);
		pEpf2->InitializeNew();
	}

	void CreateNewEpf3 (void)
	{
		if (pEpf3) delete pEpf3;
		pEpf3 = new CSrDwordSubrecord;

		pEpf3->Initialize(SR_NAME_EPF3, 4);
		pEpf3->InitializeNew();
	}

	void CreateNewEpfd (void)
	{
		if (pEpfd) delete pEpft;
		pEpfd = new CSrEpfdSubrecord;

		pEpfd->Initialize(SR_NAME_EPFD, 4);
		pEpfd->InitializeNew();
		pEpfd->SetDataType(SP_EPFDTYPE_FLOAT);
	}


	bool CopyFrom (CSrRecord* pRecord, const dword Index)
	{
		CSrPrkeSubrecord*    pSrcPrke;
		CSrSubrecord*        pSubrecord;
		srperk_subsection_t* pCurrentSubsection = NULL;
		srconditioninfo_t*   pCurrentCondInfo = NULL;

		if (pRecord == NULL) return false;
		pSrcPrke = SrCastClassNull(CSrPrkeSubrecord, pRecord->GetSubrecord(Index));
		if (pSrcPrke == NULL) return false;

		Prke.Copy(pSrcPrke);

		for (dword i = Index + 1; i < pRecord->GetNumSubrecords(); ++i)
		{
			 pSubrecord = pRecord->GetSubrecord(i);

			 if (pSubrecord->GetRecordType() == SR_NAME_DATA)
			 {
				 Data.Copy(pSubrecord);
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_PRKC)
			 {
				 pCurrentSubsection = Subsections.AddNew();
				 pCurrentSubsection->Prkc.Copy(pSubrecord);
				 pCurrentCondInfo = NULL;
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_CTDA && pCurrentSubsection != NULL)
			 {
				pCurrentCondInfo = pCurrentSubsection->Conditions.AddNew();
				pCurrentCondInfo->Condition.Copy(pSubrecord);
				pCurrentCondInfo->Condition.SetPrkc(pCurrentSubsection->Prkc.GetValue());
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_CIS1 && pCurrentCondInfo != NULL)
			 {
				 pCurrentCondInfo->CopyParam1(pSubrecord);
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_CIS2 && pCurrentCondInfo != NULL)
			 {
				 pCurrentCondInfo->CopyParam2(pSubrecord);
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_EPFT)
			 {
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pEpft = SrCastClass(CSrByteSubrecord, pTmp);
				 if (pEpft == NULL) delete pTmp;
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_EPF2)
			 {
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pEpf2 = SrCastClass(CSrLStringSubrecord, pTmp);
				 if (pEpf2 == NULL) delete pTmp;
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_EPF3)
			 {
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pEpf3 = SrCastClass(CSrDwordSubrecord, pTmp);
				 if (pEpf3 == NULL) delete pTmp;
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_EPFD)
			 {
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 CSrSubrecord* pTmp = pSubrecord->CreateCopy();
				 pEpfd = SrCastClass(CSrEpfdSubrecord, pTmp);
				 if (pEpfd == NULL) delete pTmp;
			 }
			 else if (pSubrecord->GetRecordType() == SR_NAME_PRKF)
			 {
				 pCurrentSubsection = NULL;
				 pCurrentCondInfo   = NULL;

				 Prkf.Copy(pSubrecord);
				 break;
			 }

		}		

		return true;
	}


};

typedef CSrPtrArray<srperk_section_t> CSrPerkSectionArray;


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
	srperk_section_t*		m_pCurrentSection;
	bool					m_IsInitialized;
	bool					m_IsUpdating;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrPerkView();

	virtual void CopyConditions (void);

	void CopyPerkSections      (void);
	void SetPerkSectionList    (void);
	int  AddPerkSectionList    (srperk_section_t* pSection);
	void UpdatePerkSectionList (const int ListIndex, const bool Update);
	void UpdateSectionList     (srperk_section_t* pSection);

	void SetCurrentSection (srperk_section_t* pSection);
	void SetSectionCustomData(srrlcustomdata_t& CustomData, srperk_section_t* pSection);

	void EnableSectionControls (void);
	void UpdateSectionLabels (void);

	void GetSectionData (void);
	void SetSectionData (void);

	CString GetPerkSectionDataString (srperk_section_t& Section);

	srperk_section_t* FindPerkSection(CSrPrkeSubrecord* pPrke);
  

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
	afx_msg void OnBnClickedEditNextperk();
	afx_msg void OnBnClickedSelectNextperk();
	CComboBox m_Unknown1;
	CComboBox m_Unknown2;
	CComboBox m_Unknown3;
	CButton m_Conditions;
	afx_msg void OnBnClickedAddperkButton();
	afx_msg void OnBnClickedDeleteperkButton();
	CSrRecordListCtrl m_SectionList;
	afx_msg void OnDropNextPerk (NMHDR* pNotifyStruct, LRESULT* pResult);

	CComboBox m_SectionType;
	CEdit m_SectionIndex;
	CButton m_SectionConditions;
	afx_msg void OnBnClickedSectionConditions();
	CStatic m_SectionEditorIDLabel;
	CEdit m_SectionEditorID;
	afx_msg void OnBnClickedEditSectioneditorid();
	afx_msg void OnBnClickedSelectSectioneditorid();
	CButton m_EditEditorIDButton;
	CButton m_SelectEditorIDButton;
	CComboBox m_SectionActorValue;
	CEdit m_SectionValue;
	CStatic m_SectionValueLabel;
	CComboBox m_SectionEffectType;
	CComboBox m_SectionApplyType;
	CComboBox m_SectionUnknownType;
	afx_msg void OnCbnSelchangeSectiontype();
	afx_msg void OnCbnSelchangeSectionapplytype();
	afx_msg void OnLvnItemchangedPerkdataList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropSectionList (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg int OnDropCustomSectionData (srrldroprecords_t& DropItems);
	afx_msg void OnPerksectionAdd();
	afx_msg void OnPerksectionDelete();
	afx_msg void OnPerksectionDuplicate();
	afx_msg void OnUpdatePerksectionEdit(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
/*===========================================================================
 *		End of Class CSrPerkView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrPerkView.H
 *=========================================================================*/
