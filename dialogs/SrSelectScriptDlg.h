/*=========================================================================== 
 *
 * File:		SrSelectScriptDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 February 2012
 *
 *=========================================================================*/
#ifndef __SRSELECTSCRIPTDLG_H
#define __SRSELECTSCRIPTDLG_H


#include "afxwin.h"
#include "afxcmn.h"
#include <unordered_map>


class CSrSelectScriptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrSelectScriptDlg)

	CStringArray	m_ScriptFiles;
	CString			m_CurrentScriptName;
	CString			m_CurrentFilter;
	std::unordered_map<int, int> m_IndexMap;

public:
	CSrSelectScriptDlg(CWnd* pParent = NULL);
	virtual ~CSrSelectScriptDlg();

	enum { IDD = IDD_SELECTSCRIPT_DLG };

	int DoModal (CString& ScriptName);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	void FillScriptNames (void);
	void FillScriptList  (void);

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_CurrentValue;
	CListCtrl m_ScriptList;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLvnItemchangedScriptlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateScriptlist(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_Filter;
	afx_msg void OnEnChangeScriptfilter();
	afx_msg void OnLvnGetdispinfoScriptlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeCurrentText();
};


#endif
/*===========================================================================
 *		End of File SrScriptTextCtrl.H
 *=========================================================================*/