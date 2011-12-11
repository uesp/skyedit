/*===========================================================================
 *
 * File:		SrFunctionDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRFUNCTIONDLG_H
#define __SRFUNCTIONDLG_H


#include "afxwin.h"
#include "afxcmn.h"
#include "modfile/srmoddefs.h"


#define SR_FUNCDLG_SORTNAME		0x01
#define SR_FUNCDLG_SORTTYPE		0x02
#define SR_FUNCDLG_SORTPARAMS	0x03


/*===========================================================================
 *
 * Begin Class CSrFunctionDlg Definition
 *
 *=========================================================================*/
class CSrFunctionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrFunctionDlg)

protected:
	CString		m_OrigFunction;
	CString		m_CurrentFunction;
	CString		m_FilterString;
	dword		m_FunctionMask;


protected:
	void FillFunctionList (void);
	void SetupFunctionList (void);

public:
	CSrFunctionDlg(CWnd* pParent = NULL); 
	virtual ~CSrFunctionDlg();

	bool DoModal (CString& Function, const dword Mask);


	enum { IDD = IDD_FUNCTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_PreviousValue;
	CEdit m_CurrentValue;
	CListCtrl m_FunctionList;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLvnItemchangingFunctionList(NMHDR *pNMHDR, LRESULT *pResult);
	void OnDblclk (NMHDR* pNMHDR, LRESULT* pResult);
	CEdit m_Filter;
	afx_msg void OnEnChangeFilterText();
	afx_msg void OnBnClickedClearFilter();
	afx_msg void OnHelp (void);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};
/*===========================================================================
 *		End of Class CSrFunctionDlg Definition
 *=========================================================================*/


  bool SrSelectFunctionScript (CString& Function);


#endif
/*===========================================================================
 *		End of File SrFunctionDlg.H
 *=========================================================================*/

