/*===========================================================================
 *
 * File:		SrAvifView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRAVIFVIEW_H
#define __SRAVIFVIEW_H


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
 * Begin Class CSrAvifView Definition
 *
 *=========================================================================*/
class CSrAvifView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrAvifView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrAvifSectionArray		m_Sections;
	sravifsection_t*		m_pCurrentSection;
	bool					m_IsInitialized;
	bool					m_IsUpdating;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrAvifView();

	void CopyAvifSections      (void);
	void SetAvifSectionList    (void);
	int  AddAvifSectionList    (sravifsection_t* pSection);
	void UpdateAvifSectionList (const int ListIndex, const bool Update);
	void UpdateSectionList     (sravifsection_t* pSection);

	void SetCurrentSection (sravifsection_t* pSection);
	void SetSectionCustomData (srrlcustomdata_t& CustomData, sravifsection_t* pSection);

	void EnableSectionControls (void);

	void GetSectionData (void);
	void SetSectionData (void);

	sravifsection_t* FindAvifSection(CSrFormidSubrecord* pPName);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_AVIF_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;
	CEdit		m_Unknown1;
	CEdit		m_Unknown2;
	CEdit		m_Unknown3;
	CEdit		m_Unknown4;
	CEdit		m_CName;

	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);
	virtual int   OnPreSaveRecord  (void);

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrAvifView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:
	CEdit m_Description;
	CSrRecordListCtrl m_SectionList;
	CEdit m_AName;
	CEdit m_SectIName;
	CEdit m_SectFName;
	CEdit m_SectPName;
	CButton m_SectEditPName;
	CButton m_SectSelectPName;
	CEdit m_SectSName;
	CButton m_SectEditSName;
	CButton m_SectSelectSName;
	CEdit m_SectXName;
	CEdit m_SectHName;
	CEdit m_SectYName;
	CEdit m_SectVName;
	CListBox m_SectCNames;
	CButton m_SectAddCName;
	CButton m_SectDeleteCName;
	CButton m_SectEditCName;
	CButton m_SectAdd;
	CButton m_SectDelete;
	afx_msg void OnBnClickedEditSectperk();
	afx_msg void OnBnClickedSelectSectperk();
	afx_msg void OnBnClickedEditSectsnam();
	afx_msg void OnBnClickedSelectSectsnam();
	afx_msg void OnBnClickedAddSectcnam();
	afx_msg void OnBnClickedEditSectcnam();
	afx_msg void OnBnClickedDeleteSectcnam();
	afx_msg void OnBnClickedAddAvifsection();
	afx_msg void OnBnClickedDeleteAvifsection();
	afx_msg void OnLvnItemchangedAvifdataList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropSectionList (NMHDR* pNotifyStruct, LRESULT* pResult);
	int OnDropCustomSectionData (srrldroprecords_t& DropItems);
	afx_msg void OnDropSectPName (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSectSName (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnLbnDblclkSectcnam();
};
/*===========================================================================
 *		End of Class CSrAvifView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrAvifView.H
 *=========================================================================*/
