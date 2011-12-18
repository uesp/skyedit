/*===========================================================================
 *
 * File:		SrBookView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	17 Decemberr 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRBOOKVIEW_H
#define __SRBOOKVIEW_H


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
 * Begin Class CSrBookView Definition
 *
 *=========================================================================*/
class CSrBookView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrBookView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrBookView();
  
	void EnableSpellSkillControls (void);

  /*---------- Begin Public Class Methods ------------------------*/
public:
	enum { IDD = IDD_BOOK_VIEW };
	CButton		m_QuestItem;
	CEdit		m_Value;
	CEdit		m_Weight;
	CEdit		m_Name;
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_Model;
	CListBox	m_Keywords;
	CEdit		m_PickupSound;
	CEdit		m_CName;
	CEdit		m_Description;
	CButton		m_SkillBook;
	CButton		m_NoteType;
	CButton		m_SpellTome;
	CComboBox	m_Skill;
	CEdit		m_StaticModel;
	CEdit		m_Spell;
	CButton		m_EditSpellButton;
	CButton		m_SelectSpellButton;

protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual ~CSrBookView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	afx_msg void OnBnClickedEditStaticmodel();
	afx_msg void OnBnClickedSelectstaticmodelButton();
	afx_msg void OnDropStaticModel (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnBnClickedSkillbook();
	afx_msg void OnBnClickedSpelltome();
	
	afx_msg void OnBnClickedEditSpell();
	afx_msg void OnBnClickedSelectspellButton();
	afx_msg void OnDropSpell (NMHDR* pNotifyStruct, LRESULT* pResult);
	
};
/*===========================================================================
 *		End of Class CSrBookView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrWeapview.H
 *=========================================================================*/
