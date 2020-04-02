/*===========================================================================
 *
 * File:		SrNewScriptPropertyDlg.cpp
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 February 2012
 *
 *=========================================================================*/
#include "stdafx.h"
#include "sredit.h"
#include "dialogs\SrNewScriptPropertyDlg.h"
#include "afxdialogex.h"
#include "scripts/SrScriptFile.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNAMIC(CSrNewScriptPropertyDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrNewScriptPropertyDlg, CDialogEx)
END_MESSAGE_MAP()
/*===========================================================================
 *		End Message Map
 *=========================================================================*/


CSrNewScriptPropertyDlg::CSrNewScriptPropertyDlg(CWnd* pParent)
	: CDialogEx(CSrNewScriptPropertyDlg::IDD, pParent)
{

}

CSrNewScriptPropertyDlg::~CSrNewScriptPropertyDlg()
{
}

void CSrNewScriptPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ARRAYCHECK, m_ArrayCheck);
	DDX_Control(pDX, IDC_HIDDENCHECK, m_HiddenCheck);
	DDX_Control(pDX, IDC_PROPERTYTYPES, m_TypeList);
	DDX_Control(pDX, IDC_PROPERTYNAME, m_Name);
	DDX_Control(pDX, IDC_PROPERTYVALUE, m_Value);
	DDX_Control(pDX, IDC_PROPERTYDOC, m_Document);
}


void CSrNewScriptPropertyDlg::FillTypeList (void)
{
	int ListIndex;

	m_TypeList.ResetContent();

		//Note: Skip first array element on purpose
	for (dword i = 1; g_SrScriptRefTypes[i].pName != NULL; ++i) 
	{
		ListIndex = m_TypeList.AddString(g_SrScriptRefTypes[i].pName);
	}

		/* Add predefined property types */
	m_TypeList.AddString("bool");
	m_TypeList.AddString("int");
	m_TypeList.AddString("float");
	m_TypeList.AddString("string");

	m_TypeList.SetCurSel(0);
}


BOOL CSrNewScriptPropertyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	FillTypeList();

	return TRUE;
}


void CSrNewScriptPropertyDlg::GetControlData (void)
{
	CString Buffer;

	m_TypeList.GetWindowTextA(Buffer);
	m_NewProperty.Type = Buffer;
	m_Name.GetWindowTextA(Buffer);
	m_NewProperty.Name = Buffer;
	m_Value.GetWindowTextA(Buffer);
	m_NewProperty.Value = Buffer;
	m_Document.GetWindowTextA(Buffer);
	m_NewProperty.Document = Buffer;

	m_NewProperty.Name.RemoveCharsToMatch(iscsym);
	m_NewProperty.Name.Trim();
	m_NewProperty.Value.Trim();

	m_NewProperty.Hidden = m_HiddenCheck.GetCheck() != 0;
	m_NewProperty.Array  = m_ArrayCheck.GetCheck() != 0;
}


void CSrNewScriptPropertyDlg::OnOK (void)
{
	GetControlData();
	CDialogEx::OnOK();
}


bool CSrNewScriptPropertyDlg::DoModal (srnewscriptpropertyinfo_t& Property)
{
	int Result;

	Result = CDialogEx::DoModal();
	if (Result != IDOK) return false;

	Property = m_NewProperty;
	return true;
}


