/*===========================================================================
 *
 * File:		SrActiView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 January 2021
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRACTIVIEW_H
#define __SRACTIVIEW_H


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
 * Begin Class CSrActiView Definition
 *
 *=========================================================================*/
class  CSrActiView: public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrActiView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrActiView();

	

  /*---------- Begin Public Class Methods ------------------------*/
public:

	enum { IDD = IDD_ACTI_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;
	CEdit		m_Model;

public:

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
  virtual ~CSrActiView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:


	CEdit m_Verb;
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown4;
	CEdit m_Keyword;
	CEdit m_AmbientSound;
	CEdit m_UseSound;
	CEdit m_Water;
	CEdit m_DestroyModel;
	afx_msg void OnBnClickedSelectDestroymodel();
	afx_msg void OnBnClickedEditKeyword();
	afx_msg void OnBnClickedSelectKeyword();
	afx_msg void OnBnClickedEditAmbientsound();
	afx_msg void OnBnClickedSelectAmbientsound();
	afx_msg void OnBnClickedEditUsesound();
	afx_msg void OnBnClickedSelectusesoundButton();
	afx_msg void OnBnClickedEditWater();
	afx_msg void OnBnClickedSelectWater();
	afx_msg void OnDropAmbientSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropUseSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropWater (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropKeyword (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropDestroyModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnSelectDestroyModel (void);
	CListBox m_Scripts;
};
/*===========================================================================
 *		End of Class CSrActiView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrActiView.H
 *=========================================================================*/
