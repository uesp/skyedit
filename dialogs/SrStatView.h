/*===========================================================================
 *
 * File:		SrStatView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSTATVIEW_H
#define __SRSTATVIEW_H


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
 * Begin Class CSrStatView Definition
 *
 *=========================================================================*/
class CSrStatView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrStatView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrStatView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_STAT_VIEW };
	CEdit		m_Scale;
	CEdit		m_EditorID;
	CEdit		m_FormID;
 	CEdit		m_Material;
	CEdit		m_Model;


protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrStatView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	void OnBnClickedEditMaterial();
	void OnBnClickedSelectMaterial();
};
/*===========================================================================
 *		End of Class CSrStatView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrStatView.H
 *=========================================================================*/
