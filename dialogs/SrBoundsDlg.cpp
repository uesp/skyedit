/*===========================================================================
 *
 * File:		SrBoundsDlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "dialogs\SrBoundsDlg.h"
#include "afxdialogex.h"



/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNAMIC(CSrBoundsDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSounView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrBoundsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSrBoundsDlg::OnBnClickedOk)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSounView Message Map
 *=========================================================================*/
 

CSrBoundsDlg::CSrBoundsDlg(CWnd* pParent) : CDialogEx(CSrBoundsDlg::IDD, pParent)
{

}


CSrBoundsDlg::~CSrBoundsDlg()
{
}


void CSrBoundsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_X1, m_X1);
	DDX_Control(pDX, IDC_Y1, m_Y1);
	DDX_Control(pDX, IDC_Z1, m_Z1);
	DDX_Control(pDX, IDC_X2, m_X2);
	DDX_Control(pDX, IDC_Y2, m_Y2);
	DDX_Control(pDX, IDC_Z2, m_Z2);
}


void CSrBoundsDlg::SetControlData (void)
{
	CString Buffer;

	Buffer.Format("%hd", m_BoundsData.X1);
	m_X1.SetWindowText(Buffer);

	Buffer.Format("%hd", m_BoundsData.Y1);
	m_Y1.SetWindowText(Buffer);

	Buffer.Format("%hd", m_BoundsData.Z1);
	m_Z1.SetWindowText(Buffer);

	Buffer.Format("%hd", m_BoundsData.X2);
	m_X2.SetWindowText(Buffer);

	Buffer.Format("%hd", m_BoundsData.Y2);
	m_Y2.SetWindowText(Buffer);

	Buffer.Format("%hd", m_BoundsData.Z2);
	m_Z2.SetWindowText(Buffer);
}


void CSrBoundsDlg::GetControlData (void)
{
	CString Buffer;

	m_X1.GetWindowText(Buffer);
	SrFieldConvertShort(Buffer, m_BoundsData.X1);

	m_Y1.GetWindowText(Buffer);
	SrFieldConvertShort(Buffer, m_BoundsData.Y1);

	m_Z1.GetWindowText(Buffer);
	SrFieldConvertShort(Buffer, m_BoundsData.Z1);

	m_X2.GetWindowText(Buffer);
	SrFieldConvertShort(Buffer, m_BoundsData.X2);

	m_Y2.GetWindowText(Buffer);
	SrFieldConvertShort(Buffer, m_BoundsData.Y2);

	m_Z2.GetWindowText(Buffer);
	SrFieldConvertShort(Buffer, m_BoundsData.Z2);
}


void CSrBoundsDlg::OnBnClickedOk()
{
	GetControlData();
	CDialogEx::OnOK();
}


BOOL CSrBoundsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetControlData();

	m_X1.SetFocus();
	return FALSE;
}


bool SrEditBoundsDlg (srboundsdata_t& Data)
{
	CSrBoundsDlg Dlg;

	Dlg.m_BoundsData = Data;

	if (Dlg.DoModal() != IDOK) return false;

	Data = Dlg.m_BoundsData;
	return true;
}
