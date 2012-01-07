/*===========================================================================
 *
 * File:		SrSnctView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSNCTVIEW_H
#define __SRSNCTVIEW_H


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
 * Begin Class CSrSnctView Definition
 *
 *=========================================================================*/
class CSrSnctView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrSnctView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrSnctView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_SNCT_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
  
protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrSnctView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();
  
public:

	afx_msg void OnDropSoundParent (NMHDR* pNotifyStruct, LRESULT* pResult);
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	
	afx_msg void OnBnClickedEditSoundParent();
	afx_msg void OnBnClickedSelectSoundParent();
		
	CEdit m_ItemName;
	CEdit m_SoundFlags;
	CEdit m_SoundParent;
};
/*===========================================================================
 *		End of Class CSrSnctView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrSnctView.H
 *=========================================================================*/
