/*===========================================================================
 *
 * File:		SrSndrView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSNDRVIEW_H
#define __SRSNDRVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrSndrView Definition
 *
 *=========================================================================*/
class CSrSndrView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrSndrView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrSndrView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_SNDR_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
  
protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrSndrView();

	virtual void GetControlData (void);
	virtual void SetControlData (void);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();
  
public:

	afx_msg void OnDropSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropCategory (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropOutputMarker (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSoundFileList (NMHDR* pNotifyStruct, LRESULT* pResult);

	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_FName;
	CEdit m_CName;
	CEdit m_SoundFlags;
	CEdit m_Category;
	CEdit m_Sound;
	CEdit m_OutputMarker;
	CButton m_Conditions;
	CListBox m_SoundFileList;

	afx_msg void OnBnClickedEditSound();
	afx_msg void OnBnClickedSelectSound();
	afx_msg void OnBnClickedEditCategory();
	afx_msg void OnBnClickedSelectCategory();
	afx_msg void OnBnClickedEditOutputmarker();
	afx_msg void OnBnClickedSelectOutputmarker();
	afx_msg void OnBnClickedAddSoundfilelist();
	afx_msg void OnBnClickedSelectSoundfilelist();
	afx_msg void OnBnClickedDeleteSoundfilelist();
	afx_msg void OnLbnDblclkSoundfileList();
	afx_msg void OnBnClickedEditSoundfile();
};
/*===========================================================================
 *		End of Class CSrSndrView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrSndrView.H
 *=========================================================================*/
