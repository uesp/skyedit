/*
 * File:		SrConditiondlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 Decemberr 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "sredit.h"
#include "SrFunctionDlg.h"
#include "afxdialogex.h"
#include "modfile/srfunctions.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNAMIC(CSrFunctionDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/
 
 
/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrFunctionDlg, CDialogEx)
	ON_COMMAND(ID_HELP, &CSrFunctionDlg::OnHelp)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_FUNCTION_LIST, &CSrFunctionDlg::OnLvnItemchangingFunctionList)
	ON_NOTIFY(NM_DBLCLK, IDC_FUNCTION_LIST, OnDblclk)
	ON_EN_CHANGE(IDC_FILTER_TEXT, &CSrFunctionDlg::OnEnChangeFilterText)
	ON_BN_CLICKED(ID_CLEAR_FILTER, &CSrFunctionDlg::OnBnClickedClearFilter)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/



int CALLBACK l_fnSortFunctionList(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	srfunction_t* pFunc1 = (srfunction_t *) lParam1;
	srfunction_t* pFunc2 = (srfunction_t *) lParam2;

	if (pFunc1 == NULL || pFunc2 == NULL) return 0;

	switch (lParamSort)
	{
	case SR_FUNCDLG_SORTNAME:
		return stricmp(pFunc1->Name, pFunc2->Name);
		break;
	}

	return 0;
}


CSrFunctionDlg::CSrFunctionDlg(CWnd* pParent)
	: CDialogEx(CSrFunctionDlg::IDD, pParent)
{
	m_FunctionMask = 0;
}

CSrFunctionDlg::~CSrFunctionDlg()
{
}


void CSrFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREVIOUS_TEXT, m_PreviousValue);
	DDX_Control(pDX, IDC_CURRENT_TEXT, m_CurrentValue);
	DDX_Control(pDX, IDC_FUNCTION_LIST, m_FunctionList);
	DDX_Control(pDX, IDC_FILTER_TEXT, m_Filter);
}


void CSrFunctionDlg::FillFunctionList (void)
{
	CString Buffer;
	int Index;
	int SelIndex = -1;

	m_FunctionList.SetRedraw(FALSE);
	m_FunctionList.DeleteAllItems();

	for (dword i = 0; i < g_SrFunctionCount; ++i)
	{
		srfunction_t* pFunc = &g_SrFunctions[i];
		if ((pFunc->Flags & m_FunctionMask) != m_FunctionMask) continue;
		if (CheckFlagBits(pFunc->Flags, SR_FUNCTION_FLAG_IGNORE)) continue;		

		if (!m_FilterString.IsEmpty())
		{
			if (stristr(pFunc->Name, m_FilterString) == NULL) continue;
		}

		Index = m_FunctionList.InsertItem(i, pFunc->Name);

		if (Index >= 0) 
		{
			Buffer = "";
			if (CheckFlagBits(pFunc->Flags, SR_FUNCTION_FLAG_BLOCK)) Buffer = "Block";
			else if (CheckFlagBits(pFunc->Flags, SR_FUNCTION_FLAG_CONSOLE)) Buffer = "Console";
			else if (CheckFlagBits(pFunc->Flags, SR_FUNCTION_FLAG_SCRIPT)) Buffer = "Script";

			m_FunctionList.SetItemText(Index, SR_FUNCDLG_SUBITEM_TYPE, Buffer);
			m_FunctionList.SetItemData(Index, (DWORD) pFunc);

			if (pFunc->NumParams >= 1)
			{
				m_FunctionList.SetItemText(Index, SR_FUNCDLG_SUBITEM_PARAM1, GetSrFunctionParamTypeString(pFunc->Params[0].Type));
			}

			if (pFunc->NumParams >= 2)
			{
				m_FunctionList.SetItemText(Index, SR_FUNCDLG_SUBITEM_PARAM2, GetSrFunctionParamTypeString(pFunc->Params[1].Type));
			}

			if (pFunc->NumParams >= 3)
			{
				m_FunctionList.SetItemText(Index, SR_FUNCDLG_SUBITEM_PARAM3, GetSrFunctionParamTypeString(pFunc->Params[2].Type));
			}
			
		}
	}

	m_FunctionList.SortItems(l_fnSortFunctionList, SR_FUNCDLG_SORTNAME);
	m_FunctionList.SetRedraw(TRUE);

	LVFINDINFO FindInfo;
	FindInfo.flags = LVFI_STRING;
	FindInfo.psz = m_OrigFunction;
	
	SelIndex = m_FunctionList.FindItem(&FindInfo);
	if (SelIndex < 0) SelIndex = 0;

	m_FunctionList.SetItemState(SelIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_FunctionList.EnsureVisible(SelIndex, FALSE);
}


void CSrFunctionDlg::SetupFunctionList (void)
{
	m_FunctionList.InsertColumn(SR_FUNCDLG_SUBITEM_NAME,	"Function",		LVCFMT_CENTER, 180, SR_FUNCDLG_SUBITEM_NAME);
	m_FunctionList.InsertColumn(SR_FUNCDLG_SUBITEM_PARAM1,	"Param1",		LVCFMT_CENTER, 100,	SR_FUNCDLG_SUBITEM_PARAM1);
	m_FunctionList.InsertColumn(SR_FUNCDLG_SUBITEM_PARAM2,	"Param2",		LVCFMT_CENTER, 100,	SR_FUNCDLG_SUBITEM_PARAM2);
	m_FunctionList.InsertColumn(SR_FUNCDLG_SUBITEM_PARAM3,	"Param3",		LVCFMT_CENTER, 100,	SR_FUNCDLG_SUBITEM_PARAM3);
	m_FunctionList.InsertColumn(SR_FUNCDLG_SUBITEM_TYPE,	"Type",			LVCFMT_CENTER, 60,	SR_FUNCDLG_SUBITEM_TYPE);
}


BOOL CSrFunctionDlg::OnInitDialog()
{
	LVFINDINFO FindInfo;

	CDialogEx::OnInitDialog();
	
	m_FunctionList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	SetupFunctionList();
	FillFunctionList();

	m_CurrentFunction = m_OrigFunction;
	m_PreviousValue.SetWindowText(m_OrigFunction);
	m_CurrentValue.SetWindowText(m_OrigFunction);

	FindInfo.flags = LVFI_STRING;
	FindInfo.psz = m_OrigFunction;
	int Index = m_FunctionList.FindItem(&FindInfo);
	if (Index >= 0) m_FunctionList.SetItemState(Index, LVIS_SELECTED, LVIF_STATE);

	m_Filter.SetFocus();
	return FALSE;
}


void CSrFunctionDlg::OnOK()
{
	CWnd* pWnd = GetFocus();

	if (pWnd == &m_Filter)
	{
		CString Buffer;
		m_Filter.GetWindowText(Buffer);
		Buffer.Trim(" \n\t\r");

		srfunction_t* pFunc = GetSrFunction(Buffer);

		if (pFunc == NULL) 
		{
			if (m_FunctionList.GetItemCount() > 1) return;
			if (m_FunctionList.GetItemCount() < 1) return;

			m_CurrentFunction = m_FunctionList.GetItemText(0, SR_FUNCDLG_SUBITEM_NAME);
		}
		else
		{
			m_CurrentFunction = Buffer;
		}
	}
	else if (pWnd == &m_CurrentValue)
	{
		m_CurrentValue.GetWindowText(m_CurrentFunction);
		m_CurrentFunction.Trim(" \n\t\r");

		srfunction_t* pFunc = GetSrFunction(m_CurrentFunction);

		if (pFunc == NULL) 
		{
			if (m_FunctionList.GetItemCount() > 1) return;
			if (m_FunctionList.GetItemCount() < 1) return;

			m_CurrentFunction = m_FunctionList.GetItemText(0, SR_FUNCDLG_SUBITEM_NAME);
		}
	}

	CDialogEx::OnOK();
}


bool CSrFunctionDlg::DoModal (CString& Function, const dword Mask)
{
	m_OrigFunction = Function;
	m_FunctionMask = Mask;

	int Result = CDialogEx::DoModal();
	if (Result != IDOK) return false;

	Function = m_CurrentFunction;
	return true;
}


void CSrFunctionDlg::OnLvnItemchangingFunctionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	srfunction_t* pFunc = (srfunction_t *) m_FunctionList.GetItemData(pNMLV->iItem);
	if (pFunc == NULL) return;

	m_CurrentFunction = pFunc->Name;
	m_CurrentValue.SetWindowText(pFunc->Name);
}


/*===========================================================================
 *
 * Class CSrFunctionDlg Event - void OnDblclk (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrFunctionDlg::OnDblclk (NMHDR* pNMHDR, LRESULT* pResult) 
{
  *pResult = 0;

  OnOK();
  EndModalLoop(IDOK);
}
/*===========================================================================
 *		End of Class Event CSrFunctionDlg::OnDblclk()
 *=========================================================================*/


void CSrFunctionDlg::OnEnChangeFilterText()
{
	m_Filter.GetWindowText(m_FilterString);
	FillFunctionList();
}


void CSrFunctionDlg::OnBnClickedClearFilter()
{
	m_Filter.SetWindowText("");
	m_FilterString.Empty();
	FillFunctionList();	
}


bool SrSelectFunctionScript (CString& Function)
{
	CSrFunctionDlg FuncDlg;

	return FuncDlg.DoModal(Function, SR_FUNCTION_FLAG_SCRIPT);
}


bool SrSelectFunctionCondition (CString& Function)
{
	CSrFunctionDlg FuncDlg;

	return FuncDlg.DoModal(Function, SR_FUNCTION_FLAG_SCRIPT | SR_FUNCTION_FLAG_CONDITION);
}


/*===========================================================================
 *
 * Class CSrFunctionDlg Event - void OnHelp (void);
 *
 *=========================================================================*/
void CSrFunctionDlg::OnHelp (void) 
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Functions", "Functions");
}
/*===========================================================================
 *		End of Class Event CSrFunctionDlg::OnHelp()
 *=========================================================================*/


BOOL CSrFunctionDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Functions", "Functions");
	return true;
}
