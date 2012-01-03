/*===========================================================================
 *
 * File:		SrRawDataDlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/

#include "stdafx.h"
#include "resource.h"
#include "SrRawDataDlg.h"
#include "afxdialogex.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
IMPLEMENT_DYNAMIC(CSrRawDataDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrPromptDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrRawDataDlg, CDialogEx)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrPromptDlg Message Map
 *=========================================================================*/


CSrRawDataDlg::CSrRawDataDlg(CWnd* pParent)
	: CDialogEx(CSrRawDataDlg::IDD, pParent)
{
	m_pRecord = NULL;

	m_HexFmt1.cbSize = sizeof(m_HexFmt1);
	m_HexFmt2.cbSize = sizeof(m_HexFmt2);
	m_StringFmt.cbSize = sizeof(m_StringFmt);
	m_DefaultFmt.cbSize = sizeof(m_DefaultFmt);

	memset(&m_HexFmt1, 0, sizeof(m_HexFmt1));
	memset(&m_HexFmt2, 0, sizeof(m_HexFmt2));
	memset(&m_StringFmt, 0, sizeof(m_StringFmt));
	memset(&m_DefaultFmt, 0, sizeof(m_DefaultFmt));

	m_HexFmt1.dwMask = CFM_COLOR;
	m_HexFmt2.dwMask = CFM_COLOR;
	m_StringFmt.dwMask = CFM_COLOR;
	m_DefaultFmt.dwMask = CFM_COLOR;

	m_DefaultFmt.crTextColor = RGB(0,0,0);
	m_HexFmt1.crTextColor = RGB(0,128,128);
	m_HexFmt2.crTextColor = RGB(0,0,255);
	m_StringFmt.crTextColor = RGB(128,0,0);

	m_pCurrentFmt = &m_DefaultFmt;
}


CSrRawDataDlg::~CSrRawDataDlg()
{
}


void CSrRawDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXTCONTROL, m_Text);
}


void CSrRawDataDlg::AddText (const char* pString, ...)
{
	CString Buffer;
	va_list Args;
	long    TextLength;

	va_start(Args, pString);
	Buffer.FormatV(pString, Args);
	va_end(Args);

	TextLength = m_Text.GetTextLength();
	m_Text.SetSel(TextLength, TextLength);
	m_Text.ReplaceSel(Buffer);

	if (m_pCurrentFmt)
	{
		//m_Text.SetSel(TextLength, m_Text.GetTextLengthEx(GTL_USECRLF | GTL_NUMCHARS) - 1);
		//m_Text.SetSelectionCharFormat(*m_pCurrentFmt);
		//m_Text.SetSel(0, 0);
	}
}


int CSrRawDataDlg::DoModal (CSrRecord* pRecord)
{
	if (pRecord == NULL) return -1;
	m_pRecord = pRecord;

	return CDialogEx::DoModal();
}


BOOL CSrRawDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TextFont.CreatePointFont(11, "FixedSys");
	m_Text.SetFont(&m_TextFont);

	SetControlData();

	m_Text.SetFocus();
	return FALSE; 
}


void CSrRawDataDlg::SetControlData (void)
{
	m_pCurrentFmt = &m_DefaultFmt;

	AddText("Record Information\r\n");
	AddText("\tFormID: 0x%08X\r\n", m_pRecord->GetFormID());
	AddText("\tType: %4.4s\r\n", m_pRecord->GetHeader().RecordType.Name);
	AddText("\tFlags1: 0x%08X\r\n", m_pRecord->GetHeader().Flags1);
	AddText("\tFlags2: 0x%08X\r\n", m_pRecord->GetHeader().Flags2);
	AddText("\tSize: %d bytes\r\n", m_pRecord->GetHeader().Size);
	AddText("\tVersion: %d\r\n", m_pRecord->GetHeader().Version);
	AddText("\tUnknown: %d\r\n", m_pRecord->GetHeader().Unknown);
	AddText("\r\n");

	AddText("%d Subrecords\r\n", m_pRecord->GetNumSubrecords());

	for (dword i = 0; i < m_pRecord->GetNumSubrecords(); ++i)
	{
		m_pCurrentFmt = &m_DefaultFmt;

		CSrSubrecord* pSubrecord = m_pRecord->GetSubrecord(i);
		AddText("\t%d) ", i+1);

		if (pSubrecord == NULL) 
		{
			AddText("Error getting subrecord!\r\n");
			continue;
		}

		AddText("%4.4s,  %d bytes\r\n", pSubrecord->GetRecordType().Name, pSubrecord->GetRecordSize());

		const byte* pData = pSubrecord->GetData();
		dword Size = pSubrecord->GetRecordSize();

		for (dword j = 0; j < Size; )
		{
			CString Buffer;
			dword   k;
			
			AddText("\t\t");			

			for (k = 0; k < 16 && j < Size; ++k, ++j)
			{			
				if (((k/2) % 2) == 0)
					m_pCurrentFmt = &m_HexFmt1;
				else
					m_pCurrentFmt = &m_HexFmt2;

				AddText("%02X ", (dword) pData[j]);

				if (isprint(pData[j]))
					Buffer += pData[j];
				else
					Buffer += (char) 'Ž';
			}

			for (; k < 16; ++k)
			{
				AddText("   ");
			}

			m_pCurrentFmt = &m_StringFmt;
			AddText("  %s\r\n", Buffer);
		}
	}

}
