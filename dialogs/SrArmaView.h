/*===========================================================================
 *
 * File:		SrArmaView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRARMAVIEW_H
#define __SRARMAVIEW_H


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
 * Begin Class CSrArmaView Definition
 *
 *=========================================================================*/
class CSrArmaView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrArmaView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
  CSrArmaView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_ARMA_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;

public:

	/* ClassWizard generated virtual function overrides */
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);

  virtual void GetControlData (void);
  virtual void SetControlData (void);
  void FillRaceList (void);

protected:
  virtual ~CSrArmaView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	afx_msg void OnBnClickedEditEquipslot();
	afx_msg void OnBnClickedSelectequipslotButton();
	afx_msg void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);

	CButton m_BodyParts;
	afx_msg void OnBnClickedBodyparts();
		
	CEdit m_Unknown1;
	CEdit m_Unknown3;
	CEdit m_Unknown2;
	CEdit m_Race;
	afx_msg void OnBnClickedEditRace();
	afx_msg void OnBnClickedSelectRace();
	CListBox m_RaceList;
	afx_msg void OnBnClickedAddraceList();
	afx_msg void OnBnClickedEditraceList();
	afx_msg void OnBnClickedDelraceList();
	CEdit m_MaleTexture;
	afx_msg void OnBnClickedEditMaletexture();
	afx_msg void OnBnClickedSelectMaletexture();
	CEdit m_FemaleTexture;
	afx_msg void OnBnClickedEditFemaletexture();
	afx_msg void OnBnClickedSelectFemaletexture();
	CEdit m_Male1stTexture;
	afx_msg void OnBnClickedEditMale1sttexture();
	afx_msg void OnBnClickedSelectMale1sttexture();
	CEdit m_Female1stTexture;
	afx_msg void OnBnClickedEditFemale1sttexture();
	afx_msg void OnBnClickedSelectFemale1sttexture();
	afx_msg void OnBnClickedEditFootsteps();
	afx_msg void OnBnClickedSelectFootsteps();
	CEdit m_Footsteps;
	CEdit m_MaleModel;
	afx_msg void OnBnClickedSelectMalemodel();
	CEdit m_FemaleModel;
	afx_msg void OnBnClickedSelectFemalemodel();
	CEdit m_Male1stModel;
	afx_msg void OnBnClickedSelectMale1stmodel();
	CEdit m_Female1stModel;
	afx_msg void OnBnClickedSelectFemale1stmodel();

	afx_msg void OnDropFootsteps (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropRace (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropRaceList (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnDropMaleTexture (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropMale1stTexture (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropFemaleTexture (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropFemale1stTexture (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropMaleModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropFemaleModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropMale1stModel (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropFemale1stModel (NMHDR* pNotifyStruct, LRESULT* pResult);
};
/*===========================================================================
 *		End of Class CSrArmaView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrArmaView.H
 *=========================================================================*/
