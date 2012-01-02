/*===========================================================================
 *
 * File:		SrClasview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRCLASVIEW_H
#define __SRCLASVIEW_H


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
 * Begin Class CSrClasView Definition
 *
 *=========================================================================*/
class CSrClasView : public CSrRecordDialog {
	DECLARE_DYNCREATE(CSrClasView);
	DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	CSrClasView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_CLAS_VIEW };
	CEdit		m_Name;
	CEdit		m_EditorID;
	CEdit		m_FormID;
  

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);

protected:
  virtual ~CSrClasView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	
	CEdit m_Unknown1;
	CEdit m_Unknown2;
	CEdit m_Unknown3;
	CEdit m_Unknown4;
	CEdit m_Unknown5;
	CEdit m_Unknown6;
	CEdit m_Unknown7;
	CEdit m_Unknown8;
	CEdit m_Description;
	
	CComboBox m_TrainerSkill;
	CEdit m_TrainerLevel;
	CEdit m_OneHand;
	CEdit m_TwoHand;
	CEdit m_Marksman;
	CEdit m_Block;
	CEdit m_Smithing;
	CEdit m_HeavyArmor;
	CEdit m_LightArmor;
	CEdit m_Pickpocketing;
	CEdit m_Lockpicking;
	CEdit m_Sneak;
	CEdit m_Alchemy;
	CEdit m_Speechcraft;
	CEdit m_Alteration;
	CEdit m_Conjuration;
	CEdit m_Destruction;
	CEdit m_Illusion;
	CEdit m_Restoration;
	CEdit m_Enchanting;
};
/*===========================================================================
 *		End of Class CSrClasView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrClasView.H
 *=========================================================================*/
