/*===========================================================================
 *
 * File:		SrWeapview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRWEAPVIEW_H
#define __SRWEAPVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "dialogs/srrecorddialog.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrWeapView Definition
 *
 *=========================================================================*/
class CSrWeapView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrWeapView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrWeapView();
  

  /*---------- Begin Public Class Methods ------------------------*/
public:


  //{{AFX_DATA(CSrWeapView)
  enum { IDD = IDD_WEAP_VIEW };
  CButton	m_QuestItem;
  CEdit		m_Value;
  CEdit		m_Weight;
  CEdit		m_Enchantment;
  CEdit		m_Name;
  CEdit		m_EditorID;
  CEdit		m_FormID;
  CEdit		m_Model;
  CEdit		m_Damage;
  CEdit		m_EnchantPoints;
  CListBox  m_Keywords;
  //}}AFX_DATA

public:

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrWeapView)
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:
  virtual ~CSrWeapView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

		/* Generated message map functions */
	//{{AFX_MSG(CSrWeapView)
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

public:

};
/*===========================================================================
 *		End of Class CSrWeapView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrWeapview.H
 *=========================================================================*/
