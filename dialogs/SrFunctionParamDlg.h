/*===========================================================================
 *
 * File:		SrFunctionParamDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRFUNCTIONPARAMDLG_H
#define __SRFUNCTIONPARAMDLG_H


#include "afxwin.h"
#include "afxcmn.h"
#include "modfile/srmoddefs.h"


	#define SR_FUNCPARAMDLG_SUBITEM_NAME		0
	#define SR_FUNCPARAMDLG_SUBITEM_TYPE		1

struct srfuncparasortdata_t
{
	CListCtrl&	List;
	int			SubItem;
	bool		SortReverse;	
	bool		IsRecordType;
};


/*===========================================================================
 *
 * Begin Class CSrFunctionParamDlg Definition
 *
 *=========================================================================*/
class CSrFunctionParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrFunctionParamDlg)

protected:
	CString					m_OrigParamValue;
	CString					m_CurrentParamValue;
	CString					m_FilterString;
	CSrRecordHandler*		m_pRecordHandler;
	int						m_ParamType;

	bool					m_IsRecordType;
	const stringvalue_t*	m_pStringValues;
	const srrectype_t*		m_pRecordType;
	const CSrRecTypeArray*  m_pRecordTypeArray;

	bool					m_IsUpdating;
	bool					m_LastSortOrder;
	int						m_LastSortSubItem;
	int						m_CurrentValueCheck;

	CEdit		m_Filter;
	CEdit		m_PreviousValue;
	CEdit		m_CurrentValue;
	CListCtrl	m_ParamList;
	

protected:

	bool SetupListType  (void);
	void FillParamList  (void);
	void SetupParamList (void);
	void FillParamRecordList (void);
	void FillParamRecordArrayList (void);
	void FillParamStringValueList (void);
	void FillParamList (const srrectype_t RecordType);

public:
	CSrFunctionParamDlg(CWnd* pParent = NULL); 
	virtual ~CSrFunctionParamDlg();

	bool DoModal (CString& ParamValue, const int ParamType, CSrRecordHandler&  RecordHandler);

	enum { IDD = IDD_FUNCTIONPARAM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnLvnItemchangingParamList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclk (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeFilterText();
	afx_msg void OnBnClickedClearFilter();
	afx_msg void OnHelp (void);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnLvnColumnclickParamList(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_FilterLabel;
	CButton m_FilterReset;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeCurrentText();
};
/*===========================================================================
 *		End of Class CSrFunctionParamDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Declarations
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Function Declarations
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrFunctionParamDlg.H
 *=========================================================================*/

