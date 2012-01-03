/*===========================================================================
 *
 * File:		SrConditiondlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRCONDITIONDLG_H
#define __SRCONDITIONDLG_H


#include "afxcmn.h"
#include "dialogs/sreditdlghandler.h"
#include "windows/srrecordlistctrl.h"
#include "dialogs/srrecorddialog.h"
#include "afxwin.h"


/*===========================================================================
 *
 * Begin Class CSrConditionDlg Definition
 *
 *=========================================================================*/
class CSrConditionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrConditionDlg)

	/*---------- Begin Protected Class Members -----------------------*/
protected:
	CSrRecordListCtrl	m_ConditionList;
	CSrConditionArray*	m_pOrigConditions;
	CSrConditionArray	m_Conditions;
	CSrRecord*			m_pRecord;
	bool				m_IsInitialized;

	srconditioninfo_t*	m_pCurrentCondition;

	CStatic		m_Param1Label;
	CStatic		m_Param2Label;
	CEdit		m_Param2;
	CEdit		m_Value;
	CStatic		m_ValueLabel;
	CComboBox	m_Operator;
	CButton		m_FlagOr;
	CButton		m_FlagRunOnTarget;
	CButton		m_FlagUseGlobal;

	int			m_FunctionIDCheck;


	/*---------- Begin Protected Class Methods -----------------------*/
protected:
	void SetControlData (void);
	void SetConditionList (void);
	int AddConditionList (srconditioninfo_t* pCondition);
	void UpdateConditionList (const int ListIndex, const bool Update);

	void GetCurrentCondition (void);
	void SetCurrentCondition (srconditioninfo_t* pCondition);

	bool CheckCurrentCondition (void);
	void CopyConditions(void);

	void SelectCondition (const int Index);
	srconditioninfo_t* FindConditionInfo(CSrCtdaSubrecord* pCondition);


	/*---------- Begin Public Class Methods --------------------------*/
public:
	CSrConditionDlg(CWnd* pParent = NULL); 
	virtual ~CSrConditionDlg();
	
	enum { IDD = IDD_CONDITION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	srconditioninfo_t* GetSelectedCondition();


	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnItemchangedConditionList(NMHDR *pNMHDR, LRESULT *pResult);
	
	virtual BOOL OnInitDialog();

	bool DoModal (CSrRecord* pRecord, CSrConditionArray* pConditions);
	afx_msg void OnBnClickedSelectreferenceButton();
	CEdit m_Reference;
	CStatic m_ReferenceLabel;
	afx_msg void OnBnClickedSelectfunctionButton();
	CEdit m_Function;
	CStatic m_FunctionLabel;
	CEdit m_Param1;
	afx_msg void OnBnClickedSelectparam1Button();
	afx_msg void OnBnClickedSelectparam2Button();

	virtual void OnOK();
	afx_msg void OnCondInsertBefore();
	afx_msg void OnCondInsertAfter();
	afx_msg void OnCondMoveUp();
	afx_msg void OnCondMoveDown();
	afx_msg void OnCondDelete();
	afx_msg void OnCondCopyCondition();
	afx_msg void OnUpdateCondMenu(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedMoveupButton();
	afx_msg void OnBnClickedMovedownButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnHelp (void);

	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	CButton m_FunctionButton;
	CButton m_ReferenceButton;
	CButton m_Param1Button;
	CButton m_Param2Button;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeFunctionText();
	afx_msg void OnLvnItemchangingConditionList(NMHDR *pNMHDR, LRESULT *pResult);
};
/*===========================================================================
 *		End of Class CSrConditionDlg Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File SrConditiondlg.H
 *=========================================================================*/
