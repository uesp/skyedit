/*===========================================================================
 *
 * File:		Srclfmview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	8 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRCLFMVIEW_H
#define __SRCLFMVIEW_H


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
 * Begin Class CSrClfmView Definition
 *
 *=========================================================================*/
class CSrClfmView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrClfmView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrClfmView();

	void EnableCarried (const bool Enable);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_CLFM_VIEW };
	CSpinButtonCtrl	m_BlueSpin;
	CSpinButtonCtrl	m_GreenSpin;
	CSpinButtonCtrl	m_RedSpin;
	CColorStatic	m_ColorBox;
	CEdit			m_BlueColor;
	CEdit			m_GreenColor;
	CEdit			m_RedColor;
    CEdit			m_Name;
	CEdit			m_EditorID;
	CEdit			m_FormID;

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual ~CSrClfmView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnColor();
	afx_msg void OnChangeColor();

	DECLARE_MESSAGE_MAP();

public:
	CEdit m_Unknown1;
	
};
/*===========================================================================
 *		End of Class CSrClfmView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrClfmView.H
 *=========================================================================*/
