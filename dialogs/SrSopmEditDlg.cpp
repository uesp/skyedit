/*===========================================================================
 *
 * File:		SrSopmEditDlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	8 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "afxdialogex.h"
#include "sredit.h"
#include "SrSopmEditDlg.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
IMPLEMENT_DYNAMIC(CSrSopmEditDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSopmView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSopmEditDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSrSopmEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSopmView Message Map
 *=========================================================================*/


CSrSopmEditDlg::CSrSopmEditDlg(CWnd* pParent)
	: CDialogEx(CSrSopmEditDlg::IDD, pParent)
{

}


CSrSopmEditDlg::~CSrSopmEditDlg()
{
}


void CSrSopmEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATA1, m_Data[0]);
	DDX_Control(pDX, IDC_DATA2, m_Data[1]);
	DDX_Control(pDX, IDC_DATA3, m_Data[2]);
	DDX_Control(pDX, IDC_DATA4, m_Data[3]);
	DDX_Control(pDX, IDC_DATA5, m_Data[4]);
	DDX_Control(pDX, IDC_DATA6, m_Data[5]);
	DDX_Control(pDX, IDC_DATA7, m_Data[6]);
	DDX_Control(pDX, IDC_DATA8, m_Data[7]);
	DDX_Control(pDX, IDC_DATA9, m_Data[8]);
	DDX_Control(pDX, IDC_DATA10, m_Data[9]);
	DDX_Control(pDX, IDC_DATA11, m_Data[10]);
	DDX_Control(pDX, IDC_DATA12, m_Data[11]);
	DDX_Control(pDX, IDC_DATA13, m_Data[12]);
	DDX_Control(pDX, IDC_DATA14, m_Data[13]);
	DDX_Control(pDX, IDC_DATA15, m_Data[14]);
	DDX_Control(pDX, IDC_DATA16, m_Data[15]);
	DDX_Control(pDX, IDC_DATA17, m_Data[16]);
	DDX_Control(pDX, IDC_DATA18, m_Data[17]);
	DDX_Control(pDX, IDC_DATA19, m_Data[18]);
	DDX_Control(pDX, IDC_DATA20, m_Data[19]);
	DDX_Control(pDX, IDC_DATA21, m_Data[20]);
	DDX_Control(pDX, IDC_DATA22, m_Data[21]);
	DDX_Control(pDX, IDC_DATA23, m_Data[22]);
	DDX_Control(pDX, IDC_DATA24, m_Data[23]);

	DDX_Control(pDX, IDC_DATALABEL1, m_DataLabel[0]);
	DDX_Control(pDX, IDC_DATALABEL2, m_DataLabel[1]);
	DDX_Control(pDX, IDC_DATALABEL3, m_DataLabel[2]);
	DDX_Control(pDX, IDC_DATALABEL4, m_DataLabel[3]);
	DDX_Control(pDX, IDC_DATALABEL5, m_DataLabel[4]);
	DDX_Control(pDX, IDC_DATALABEL6, m_DataLabel[5]);
	DDX_Control(pDX, IDC_DATALABEL7, m_DataLabel[6]);
	DDX_Control(pDX, IDC_DATALABEL8, m_DataLabel[7]);
}


BOOL CSrSopmEditDlg::OnInitDialog (void) 
{
	CDialogEx::OnInitDialog();

	EnableControls();
	SetControlData();

	m_Data[0].SetFocus();
	return FALSE;
}


void CSrSopmEditDlg::OnBnClickedOk()
{
	GetControlData();
	CDialogEx::OnOK();
}


void CSrSopmEditDlg::EnableControls (void)
{
	int LastValidIndex = 0;

	if (m_EditInfo.pOnamData != NULL)
		LastValidIndex = 23;
	else if (m_EditInfo.pAnamData != NULL)
		LastValidIndex = 4;
	else if (m_EditInfo.pSnamData != NULL)
		LastValidIndex = 15;
	else
		LastValidIndex = -1;

	for (int i = LastValidIndex + 1; i < 24; ++i)
	{
		m_Data[i].ShowWindow(SW_HIDE);
	}

	for (int i = (LastValidIndex + 1)/3; i < 8; ++i)
	{
		m_DataLabel[i].ShowWindow(SW_HIDE);
	}

}


void CSrSopmEditDlg::GetControlData (void)
{
	CString Buffer;
	
	if (m_EditInfo.pOnamData != NULL)
	{
		for (dword i = 0; i < 24; ++i)
		{
			m_Data[i].GetWindowText(Buffer);
			m_EditInfo.pOnamData->Unknown[i] = (byte) strtoul(Buffer, NULL, 0);
		}
	
	}
	else if (m_EditInfo.pAnamData != NULL)
	{
		m_Data[0].GetWindowText(Buffer);
		m_EditInfo.pAnamData->Unknown1 = strtoul(Buffer, NULL, 0);
				
		m_Data[1].GetWindowText(Buffer);
		m_EditInfo.pAnamData->Unknown2 = (float) atof(Buffer);
		
		m_Data[2].GetWindowText(Buffer);
		m_EditInfo.pAnamData->Unknown3 = (float) atof(Buffer);
		
		m_Data[3].GetWindowText(Buffer);
		m_EditInfo.pAnamData->Unknown4 = strtoul(Buffer, NULL, 0);
		
		m_Data[4].GetWindowText(Buffer);
		m_EditInfo.pAnamData->Unknown5 = strtoul(Buffer, NULL, 0);
	}
	else if (m_EditInfo.pSnamData != NULL)
	{
		for (dword i = 0; i < 16; ++i)
		{
			m_Data[i].GetWindowText(Buffer);
			m_EditInfo.pSnamData->Unknown[i] = (byte) strtoul(Buffer, NULL, 0);
		}
	}
	
}


void CSrSopmEditDlg::SetControlData (void)
{
	CString Buffer;
	
	if (m_EditInfo.pOnamData != NULL)
	{
		for (dword i = 0; i < 24; ++i)
		{
			Buffer.Format("%d", (int) m_EditInfo.pOnamData->Unknown[i]);
			m_Data[i].SetWindowText(Buffer);
		}
	
	}
	else if (m_EditInfo.pAnamData != NULL)
	{
		Buffer.Format("0x%08X", m_EditInfo.pAnamData->Unknown1);
		m_Data[0].SetWindowText(Buffer);
		Buffer.Format("%g", m_EditInfo.pAnamData->Unknown2);
		m_Data[1].SetWindowText(Buffer);
		Buffer.Format("%g", m_EditInfo.pAnamData->Unknown3);
		m_Data[2].SetWindowText(Buffer);
		Buffer.Format("0x%08X", m_EditInfo.pAnamData->Unknown4);
		m_Data[3].SetWindowText(Buffer);
		Buffer.Format("0x%08X", m_EditInfo.pAnamData->Unknown5);
		m_Data[4].SetWindowText(Buffer);
	}
	else if (m_EditInfo.pSnamData != NULL)
	{
		for (dword i = 0; i < 16; ++i)
		{
			Buffer.Format("%d", (int) m_EditInfo.pSnamData->Unknown[i]);
			m_Data[i].SetWindowText(Buffer);
		}
	}
}


bool SrSopmEditDlg (srsopmeditinfo_t EditInfo)
{
	CSrSopmEditDlg Dlg;

	if (EditInfo.pOnamData == NULL && EditInfo.pAnamData == NULL && EditInfo.pSnamData == NULL) return false;

	Dlg.m_EditInfo = EditInfo;
	return (Dlg.DoModal() == IDOK);
}