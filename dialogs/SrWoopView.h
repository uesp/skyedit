/*===========================================================================
 *
 * File:		SrWoopView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRWOOPVIEW_H
#define __SRWOOPVIEW_H


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
 * Begin Class CSrWoopView Definition
 *
 *=========================================================================*/
class CSrWoopView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrWoopView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrWoopView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_WOOP_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrWoopView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	CEdit m_ItemName;
	CEdit m_Translation;
};
/*===========================================================================
 *		End of Class CSrWoopView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrWoopView.H
 *=========================================================================*/
