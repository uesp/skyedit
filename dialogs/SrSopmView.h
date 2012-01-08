/*===========================================================================
 *
 * File:		SrSopmView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSOPMVIEW_H
#define __SRSOPMVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "afxwin.h"
	#include "afxcmn.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrSopmView Definition
 *
 *=========================================================================*/
class CSrSopmView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrSopmView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	srsopmonamdata_t	m_OnamData;
	srsopmanamdata_t	m_AnamData;
	srsopmsnamdata_t	m_SnamData;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrSopmView();

	virtual void GetControlData (void);
	virtual void SetControlData (void);

	void SetAnamControlData (void);
	void SetOnamControlData (void);
	void SetSnamControlData (void);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_SOPM_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
  
protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrSopmView();

	void CopyNameData (void);
	void UpdateEnableControls (void);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();
  
public:
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;	
	CEdit m_SoundFlags;
	CComboBox m_ContentType;
	afx_msg void OnBnClickedAnamdataButton();
	afx_msg void OnBnClickedOnamdataButton();
	afx_msg void OnBnClickedSnamdataButton();
	CButton m_AnamButton;
	CButton m_OnamButton;
	CButton m_SnamButton;
	afx_msg void OnCbnSelchangeContenttype();
};
/*===========================================================================
 *		End of Class CSrSopmView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrSopmView.H
 *=========================================================================*/
