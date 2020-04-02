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
	srfunction_t*		m_pCurrentFunction;

	CStatic		m_Param1Label;
	CStatic		m_Param2Label;
	CStatic		m_Param3Label;
	CEdit		m_Param1;
	CEdit		m_Param2;
	CEdit		m_Param3;
	CButton		m_Param1Button;
	CButton		m_Param2Button;	
	CButton		m_Param3Button;	
	CEdit		m_Value;
	CStatic		m_ValueLabel;
	CComboBox	m_Operator;
	CButton		m_FlagOr;
	CButton		m_FlagUseGlobal;
	CEdit		m_Reference;
	CStatic		m_ReferenceLabel;
	CEdit		m_Function;
	CStatic		m_FunctionLabel;
	CButton		m_FunctionButton;
	CButton		m_ReferenceButton;
	int			m_FunctionIDCheck;

	const static COLORREF s_UnchangedColor = RGB(255,255,255);
	const static COLORREF s_OkColor        = RGB(204,255,204);
	const static COLORREF s_ErrorColor     = RGB(255,204,204);


	/*---------- Begin Protected Class Methods -----------------------*/
protected:
	BOOL PreTranslateMessage( MSG* pMsg );

	void SetControlData (void);
	void SetConditionList (void);
	int AddConditionList (srconditioninfo_t* pCondition);
	void UpdateConditionList (const int ListIndex, const bool Update);

	void GetConditionParamControlData (CEdit& ParamEdit, const dword ParamIndex, int& ParamValue);
	void GetConditionControlData (void);
	void SetCurrentCondition (srconditioninfo_t* pCondition);
	void SetConditionControlData (void);

	bool CheckCurrentCondition (void);
	void CopyConditions(void);

	void UpdateReferenceStatus (void);
	void UpdateFunctionStatus  (void);
	void UpdateValueStatus     (void);
	void UpdateParamsStatus    (void);
	void UpdateParam1Status    (void);
	void UpdateParam2Status    (void);
	void UpdateParam3Status    (void);

	void EnableConditionControls (void);

	void FillRunOnList (void);

	void SelectCondition (const int Index);
	srconditioninfo_t* FindConditionInfo(CSrCtdaSubrecord* pCondition);

	int IsValidParam (CEdit& ParamEdit, const dword ParamIndex);
	int IsValidParam1 (void) { return IsValidParam(m_Param1, 0); }
	int IsValidParam2 (void) { return IsValidParam(m_Param2, 1); }
	int IsValidParam3 (void) { return IsValidParam(m_Param3, 2); }

	int IsValidValue      (void);
	int IsValidReference  (void);
	int IsValidRecordType (CString& Value, const srrectype_t Type);
	bool IsFunctionParamSelectable (const int ParamType);


	/*---------- Begin Public Class Methods --------------------------*/
public:
	CSrConditionDlg(CWnd* pParent = NULL); 
	virtual ~CSrConditionDlg();

	bool DoModal (CSrRecord* pRecord, CSrConditionArray* pConditions);
	
	enum { IDD = IDD_CONDITION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	srconditioninfo_t* GetSelectedCondition();

	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnLvnItemchangedConditionList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelectreferenceButton();
	afx_msg void OnBnClickedSelectfunctionButton();	
	afx_msg void OnBnClickedSelectparam1Button();
	afx_msg void OnBnClickedSelectparam2Button();
	afx_msg void OnBnClickedSelectparam3Button();
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeFunctionText();
	afx_msg void OnLvnItemchangingConditionList(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_FlagPackData;
	CButton m_FlagQuestAlias;
	CButton m_FlagSwapSubject;
	CComboBox m_RunOnList;
	afx_msg void OnCbnSelchangeRunonList();
	CButton m_ValueButton;
	afx_msg void OnBnClickedSelectvalueButton();
	afx_msg void OnBnClickedUseglobalCheck();
	afx_msg void OnEnChangeValueText();
	afx_msg void OnEnChangeReferenceText();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeParam1Text();
	afx_msg void OnEnChangeParam2Text();
	afx_msg void OnEnChangeParam3Text();
	afx_msg void OnDblClkParam1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnConditionPastecondition();
	afx_msg void OnUpdateConditionPastecondition(CCmdUI *pCmdUI);
	afx_msg void OnConditionDuplicate();
	afx_msg void OnUpdateConditionDuplicate(CCmdUI *pCmdUI);
	CButton m_MoveUpButton;
	CButton m_MoveDownButton;
};
/*===========================================================================
 *		End of Class CSrConditionDlg Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrConditionDlg.H
 *=========================================================================*/
