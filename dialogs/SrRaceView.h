/*===========================================================================
 *
 * File:		SrRaceView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	12 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRRACEVIEW_H
#define __SRRACEVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "afxwin.h"
	#include "afxcmn.h"
	#include "windows/tabctrlsheet.h"
	#include "SrRacePageBasic.h"
	#include "SrRacePageMove.h"
	#include "SrRacePageAttack.h"
	#include "SrRacePageModel.h"
	#include "SrRacePageUnknown.h"
	#include "SrRacePageFace.h"
	#include "SrRacePageHead1.h"
	#include "SrRacePageTint.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrRaceView Definition
 *
 *=========================================================================*/
class CSrRaceView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrRaceView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrRacePageBasic	m_BasicPage;
	CSrRacePageMove		m_MovePage;
	CSrRacePageAttack	m_AttackPage;
	CSrRacePageModel	m_ModelPage;
	CSrRacePageUnknown	m_UnknownPage;
	CSrRacePageFace		m_FacePage;
	CSrRacePageHead1	m_MaleHead1Page;
	CSrRacePageHead1	m_FemaleHead1Page;
	CSrRacePageTint		m_MaleTintPage;
	CSrRacePageTint		m_FemaleTintPage;

	srraceinfo_t		m_RaceInfo;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrRaceView();

	virtual void GetControlData (void);
	virtual void SetControlData (void);

	CWnd* GetNextControl (const bool Previous);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_RACE_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual ~CSrRaceView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP();
  
public:

	CTabCtrlSheet m_TabControl;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
/*===========================================================================
 *		End of Class CSrRaceView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrRaceView.H
 *=========================================================================*/
