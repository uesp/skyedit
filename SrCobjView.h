/*===========================================================================
 *
 * File:		SrCobjView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRCOBJVIEW_H
#define __SRCOBJVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "windows/srrecordlistctrl.h"
#include "afxwin.h"
//#include "afxcmn.h"
	//#include "afxwin.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrCobjView Definition
 *
 *=========================================================================*/
class CSrCobjView : public CSrRecordDialog {
  DECLARE_DYNCREATE(CSrCobjView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	int			m_ResultItemIDCheck;
	int			m_ComponentIDCheck;
	CSString	m_OrigResultItem;
	CSString	m_OrigComponent;
	bool		m_ComponentsChanged;
	bool		m_IsInitialized;

	 CSrPtrArray<CSrCntoSubrecord> m_Components;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

	/* Protected constructor used by dynamic creation */
  CSrCobjView();
  void CopyComponents (void);

  CSrCntoSubrecord* GetSelectedComponent (void);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:

  enum { IDD = IDD_COBJ_VIEW };
  CEdit				m_ResultItem;
  CEdit				m_EditorID;
  CEdit				m_FormID;
  CButton			m_Conditions;
  CEdit				m_ResultCount;
  CSrRecordListCtrl m_ComponentList;
  CEdit				m_CraftStation;

  CSrCntoSubrecord*	m_pCurrentComponent;

public:

	virtual void GetControlData   (void);
	virtual void SetControlData   (void);
	virtual void SetComponentList (void);
	void UpdateComponentList(const int ListIndex, const bool Update);
	int  AddComponentList (CSrCntoSubrecord* pComponent) ;
	void EnableComponentControls (const bool Enable);
	void SetCurrentComponent (CSrCntoSubrecord* pComponent);
	void GetCurrentComponent (void);

	void OnDropCraftStation (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropResultItem (NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnDropComponent (NMHDR* pNotifyStruct, LRESULT* pResult);
	int  OnDropCustomComponentData (srrldroprecords_t& DropItems);
	int  OnDropRecordComponentData (srrldroprecords_t& DropItems);
	void OnDropComponentList (NMHDR* pNotifyStruct, LRESULT* pResult);

	/* ClassWizard generated virtual function overrides */
protected:
  virtual void OnInitialUpdate();
  virtual void DoDataExchange(CDataExchange* pDX);

protected:
  virtual ~CSrCobjView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:

	virtual int  OnPreSaveRecord    (void);
	afx_msg	HBRUSH OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedEditResultitem();
	afx_msg void OnBnClickedSelectresultitemButton();
	afx_msg void OnBnClickedEditCraftstation();
	afx_msg void OnBnClickedSelectcraftstationButton();
	afx_msg void OnEnChangeResultItem();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnComponentEdit();
	afx_msg void OnComponentDelete();
	afx_msg void OnComponentAdd();
	afx_msg void OnBnClickedEditComponent();
	afx_msg void OnBnClickedSelectcomponentButton();
	CEdit m_Component;
	CEdit m_ComponentCount;
	afx_msg void OnLvnItemchangedComponentList(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_EditComponentButton;
	CButton m_SelectComponentButton;
	afx_msg void OnEnChangeComponent();
	CButton m_DeleteButton;
	CButton m_AddButton;
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton2();
	afx_msg void OnComponentDecrease();
	afx_msg void OnComponentIncrease();
};
/*===========================================================================
 *		End of Class CSrCobjView Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrMgefView.H
 *=========================================================================*/
