/*===========================================================================
 *
 * File:		SrSounView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSOUNVIEW_H
#define __SRSOUNVIEW_H


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
 * Begin Class CSrSounView Definition
 *
 *=========================================================================*/
class CSrSounView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrSounView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrSounView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_SOUN_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
  
protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrSounView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();
  
public:

	afx_msg void OnDropSoundRef (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropSoundFile (NMHDR* pNotifyStruct, LRESULT* pResult);
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown4;
	CEdit m_Unknown5;
	CEdit m_Unknown6;
	CEdit m_Unknown7;
	CEdit m_Unknown8;
	CEdit m_Unknown9;
	CEdit m_Unknown10;
	CEdit m_Unknown11;
	CEdit m_Unknown12;
	CEdit m_SoundFile;
	CEdit m_SoundRef;
	afx_msg void OnBnClickedSelectSoundfile();
	afx_msg void OnBnClickedEditSoundref();
	afx_msg void OnBnClickedSelectSoundref();
	CButton m_Bounds;
	
};
/*===========================================================================
 *		End of Class CSrSounView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrSounView.H
 *=========================================================================*/
