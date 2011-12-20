/*===========================================================================
 *
 * File:		SrLighview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	18 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRLIGHVIEW_H
#define __SRLIGHVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/srrecorddialog.h"
  #include "colorstatic.h"
#include "afxwin.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrLighView Definition
 *
 *=========================================================================*/
class CSrLighView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrLighView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	bool	m_Initialized;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrLighView();

	void EnableCarried (const bool Enable);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_LIGH_VIEW };
	CEdit			m_Falloff;
	CEdit			m_Radius;
	CEdit			m_FOV;
	CSpinButtonCtrl	m_BlueSpin;
	CSpinButtonCtrl	m_GreenSpin;
	CSpinButtonCtrl	m_RedSpin;
	CComboBox		m_FlickerType;
	CColorStatic	m_ColorBox;
	CEdit			m_Fade;
	CEdit			m_BlueColor;
	CEdit			m_GreenColor;
	CEdit			m_RedColor;
	CEdit			m_Sound;
	CEdit			m_Time;
	CEdit			m_Icon;
	CEdit			m_Model;
	CEdit			m_Value;
	CEdit			m_Weight;
    CEdit			m_Name;
	CEdit			m_EditorID;
	CEdit			m_FormID;
	CButton			m_QuestItem;

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual ~CSrLighView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnCarried();
	afx_msg void OnColor();
	afx_msg void OnChangeColor();
	afx_msg void OnDropSound(NMHDR* pNotifyStruct, LRESULT* pResult);

	DECLARE_MESSAGE_MAP();

public:
	CButton m_Dynamic;
	CButton m_Carried;
	CButton m_SpotShadow;
	CButton m_UnknownFlag1;
	CButton m_UnknownFlag2;
	CButton m_UnknownFlag3;
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown4;
	afx_msg void OnBnClickedEditSound();
	afx_msg void OnBnClickedSelectsoundButton();
};
/*===========================================================================
 *		End of Class CSrLighView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrLighview.H
 *=========================================================================*/
