/*===========================================================================
 *
 * File:		SrSelectScriptDlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	7 February 2012
 *
 * Implements the CSrSelectScriptDlg class
 *
 *=========================================================================*/
#include "stdafx.h"
#include "sredit.h"
#include "dialogs\SrSelectScriptDlg.h"
#include "afxdialogex.h"
#include "common/srutils.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
IMPLEMENT_DYNAMIC(CSrSelectScriptDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrScriptTextCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSelectScriptDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SCRIPTLIST, &CSrSelectScriptDlg::OnLvnItemchangedScriptlist)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_SCRIPTLIST, &CSrSelectScriptDlg::OnLvnItemActivateScriptlist)
	ON_EN_CHANGE(IDC_SCRIPTFILTER, &CSrSelectScriptDlg::OnEnChangeScriptfilter)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_SCRIPTLIST, &CSrSelectScriptDlg::OnLvnGetdispinfoScriptlist)
	ON_EN_CHANGE(IDC_CURRENT_TEXT, &CSrSelectScriptDlg::OnEnChangeCurrentText)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrScriptTextCtrl Message Map
 *=========================================================================*/


int CALLBACK l_SortByName(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pList = (CListCtrl *) lParamSort;
	if (pList == NULL) return 0;

	return 0;
}


CSrSelectScriptDlg::CSrSelectScriptDlg(CWnd* pParent)
	: CDialogEx(CSrSelectScriptDlg::IDD, pParent)
{
}


CSrSelectScriptDlg::~CSrSelectScriptDlg()
{
}


void CSrSelectScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CURRENT_TEXT, m_CurrentValue);
	DDX_Control(pDX, IDC_SCRIPTLIST, m_ScriptList);
	DDX_Control(pDX, IDC_SCRIPTFILTER, m_Filter);
}


void CSrSelectScriptDlg::FillScriptNames (void)
{
	CString  ScriptPath;
	CSString InstallPath;
	CSString Filename;

	m_ScriptFiles.RemoveAll();

	GetSrInstallPath(InstallPath);
	ScriptPath = InstallPath;
	ScriptPath += "data\\scripts\\source\\*.psc";

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFileA(ScriptPath, &FindFileData);
	BOOL   Result;

	if (hFind == INVALID_HANDLE_VALUE)
	{
		AddSrWindowsError("Failed to find script files matching '%s'!", ScriptPath);
		return;
	}

	do
	{
		Filename = FindFileData.cFileName;
		Filename.TruncateAtR('.');

		if (!Filename.IsEmpty())
		{
			m_ScriptFiles.Add(Filename);
		}

		Result = FindNextFileA(hFind, &FindFileData);
	} while (Result);

}


void CSrSelectScriptDlg::FillScriptList (void)
{
	int ListIndex;

	m_ScriptList.SetRedraw(false);
	m_ScriptList.DeleteAllItems();

	for (int i = 0; i < m_ScriptFiles.GetCount(); ++i)
	{
		if (!m_CurrentFilter.IsEmpty() && m_ScriptFiles[i].Find(m_CurrentFilter) < 0) continue;
		ListIndex = m_ScriptList.InsertItem(m_ScriptList.GetItemCount(), m_ScriptFiles[i]);
		m_IndexMap[ListIndex] = i;
	}

	m_ScriptList.SetRedraw(true);
}


BOOL CSrSelectScriptDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ScriptList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ScriptList.InsertColumn(0, "Script", LVCFMT_LEFT, 300, 0);

	FillScriptNames();
	FillScriptList();	

	m_ScriptList.SetFocus();
	return FALSE;
}


void CSrSelectScriptDlg::OnOK()
{
	CDialogEx::OnOK();
}


int CSrSelectScriptDlg::DoModal (CString& ScriptName)
{
	int Result = CDialogEx::DoModal();
	if (Result != IDOK) return Result;

	ScriptName = m_CurrentScriptName;
	return IDOK;
}


void CSrSelectScriptDlg::OnLvnItemchangedScriptlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	CString Buffer = m_ScriptList.GetItemText(pNMLV->iItem, 0);
	m_CurrentValue.SetWindowText(Buffer);
	m_CurrentScriptName = Buffer;
}


void CSrSelectScriptDlg::OnLvnItemActivateScriptlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	CString Buffer = m_ScriptList.GetItemText(pNMIA->iItem, 0);
	m_CurrentValue.SetWindowText(Buffer);
	m_CurrentScriptName = Buffer;

	EndDialog(IDOK);
}


void CSrSelectScriptDlg::OnEnChangeScriptfilter()
{
	CString Buffer;

	m_Filter.GetWindowTextA(Buffer);
	Buffer.Trim(" ");
	if (Buffer.CompareNoCase(m_CurrentFilter) == 0) return;

	m_CurrentFilter = Buffer;
	FillScriptList();
}


void CSrSelectScriptDlg::OnLvnGetdispinfoScriptlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	*pResult = 0;

	if (pDispInfo->item.mask & LVIF_TEXT) 
	{
		int i = m_IndexMap[pDispInfo->item.iItem];
		if (i >= 0 && i < m_ScriptFiles.GetCount()) lstrcpyn(pDispInfo->item.pszText, m_ScriptFiles[i], pDispInfo->item.cchTextMax);
	}

}


void CSrSelectScriptDlg::OnEnChangeCurrentText()
{
	m_CurrentValue.GetWindowText(m_CurrentScriptName);
	m_CurrentScriptName.Trim(" ");
}
