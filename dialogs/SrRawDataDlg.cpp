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
#include "../Srprogressdlg.h"


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
	ON_NOTIFY(EN_SELCHANGE, IDC_TEXTCONTROL, &CSrRawDataDlg::OnEnSelchangeTextcontrol)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrPromptDlg Message Map
 *=========================================================================*/


CSrRawDataDlg::CSrRawDataDlg(CSrRecordHandler&	Handler, CWnd* pParent)
	: CDialogEx(CSrRawDataDlg::IDD, pParent), m_RecordHandler(Handler)
{
	m_pRecord = NULL;
	m_UpdateSelection = false;
	m_SummaryOnly = true;

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
	m_HexFmt1.crTextColor = RGB(0,0,128);
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
	DDX_Control(pDX, IDC_VALUETEXT, m_ValueText);
}


void CSrRawDataDlg::AddText (const char* pString, ...)
{
	CString Buffer;
	va_list Args;
	long    TextLength;

	va_start(Args, pString);
	Buffer.FormatV(pString, Args);
	va_end(Args);

	long OrigTextLength = m_Text.GetTextLengthEx(GTL_NUMCHARS);
	TextLength = m_Text.GetTextLength();
	m_Text.SetSel(TextLength, TextLength);
	m_Text.ReplaceSel(Buffer);
	
	if (m_pCurrentFmt)
	{
		m_Text.SetSel(OrigTextLength, m_Text.GetTextLengthEx(GTL_NUMCHARS));
		m_Text.SetSelectionCharFormat(*m_pCurrentFmt);
		m_Text.SetSel(0, 0);
	}

}


int CSrRawDataDlg::DoModal (CSrRecord* pRecord, const bool SummaryOnly)
{
	if (pRecord == NULL) return -1;
	m_pRecord = pRecord;
	m_SummaryOnly = SummaryOnly;

	return CDialogEx::DoModal();
}


BOOL CSrRawDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Text.SetEventMask(ENM_SELCHANGE);

	m_TextFont.CreatePointFont(11, "FixedSys");
	m_Text.SetFont(&m_TextFont);

	SetControlData();

	m_Text.SetFocus();
	return FALSE; 
}


void CSrRawDataDlg::SetControlData (void)
{
	m_UpdateSelection = false;
	m_pCurrentFmt = &m_DefaultFmt;

	CSrProgressDlg* pProgress = ShowSrProgressDlg("View Data Data", "Creating Raw Data String...");
	m_Text.SetRedraw(FALSE);
	long EventMask = m_Text.GetEventMask();
	m_Text.SetEventMask(0);

	pProgress->Update(0);

	AddText("Record Information\n");
	AddText("\tFormID: 0x%08X\n", m_pRecord->GetFormID());
	AddText("\tType: %4.4s\n", m_pRecord->GetHeader().RecordType.Name);
	AddText("\tFlags1: 0x%08X\n", m_pRecord->GetHeader().Flags1);
	AddText("\tFlags2: 0x%08X\n", m_pRecord->GetHeader().Flags2);
	AddText("\tSize: %d bytes\n", m_pRecord->GetHeader().Size);
	AddText("\tVersion: %d\n", m_pRecord->GetHeader().Version);
	AddText("\tUnknown: %d\n", m_pRecord->GetHeader().Unknown);
	AddText("\n");

	AddText("%d Subrecords\n", m_pRecord->GetNumSubrecords());

	for (dword i = 0; i < m_pRecord->GetNumSubrecords(); ++i)
	{
		pProgress->Update(float(i) / float(m_pRecord->GetNumSubrecords()) * 100.0f);
		if (pProgress->GetIsCancelled()) break;

		m_pCurrentFmt = &m_DefaultFmt;

		CSrSubrecord* pSubrecord = m_pRecord->GetSubrecord(i);
		AddText("\t%d) ", i+1);

		if (pSubrecord == NULL) 
		{
			AddText("Error getting subrecord!\n");
			continue;
		}

		OutputSubrecord(pSubrecord, i);
	}

	DestroySrProgressDlg(pProgress);
	m_Text.SetEventMask(EventMask);
	m_Text.SetRedraw(TRUE);
	m_UpdateSelection = true;
}


void CSrRawDataDlg::OutputSubrecord (CSrSubrecord* pSubrecord, const int i)
{
	srrawdata_lineinfo_t LineInfo;

	AddText("%4.4s,  %d bytes\n", pSubrecord->GetRecordType().Name, pSubrecord->GetRecordSize());
	if (m_SummaryOnly) return;

	const byte* pData = pSubrecord->GetData();
	dword Size = pSubrecord->GetRecordSize();

	for (dword j = 0; j < Size; )
	{
		CString Buffer;
		dword   k;
		
		AddText("\t\t");			

		LineInfo.DataOffset = j;
		LineInfo.pSubrecord = pSubrecord;
		LineInfo.SelIndex   = m_Text.GetTextLengthEx(GTL_NUMCHARS);
		LineInfo.SubrecordIndex = i;
		m_LineInfos.push_back(LineInfo);

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
		AddText("  %s\n", Buffer);
	}

}

CString CSrRawDataDlg::FormatValueText (const dword Data)
{
	CString Result;
	CString Tmp;

	Tmp.Format("Raw: 0x%08X\r\n", Data);
	Result += Tmp;

	Tmp.Format("Byte: %u   ", (byte) Data);
	Result += Tmp;

	Tmp.Format("Word: %u   ", (word) Data);
	Result += Tmp;

	Tmp.Format("DWord: %u   ", (dword) Data);
	Result += Tmp;

	Tmp.Format("Float: %g\r\n", *(float *) &Data);
	Result += Tmp;

	CSString* pString = m_RecordHandler.FindLocalString(Data);
	Tmp.Format("LString: \"%s\"    ", pString ? pString->c_str() : "[Not Found]");
	Result += Tmp;

	CSrRecord* pRecord = m_RecordHandler.FindFormID(Data);

	if (pRecord)
	{
		Tmp.Format("Record(%4.4s): %s    \r\n", pRecord->GetRecordType().Name, m_RecordHandler.GetEditorID(pRecord->GetFormID()));
		Result += Tmp;
	}
	else
	{
		Result += "Record: [Not Found]    \r\n";
	}	

	srfunction_t* pFunction = GetSrFunction((word) Data);

	if (pFunction)
	{
		Tmp.Format("Function: %s   ", pFunction->Name);
		Result += Tmp;
	}
	else
	{
		Result += "Function: [none]   ";
	}

	pFunction = GetSrFunction((word) Data + 4096);

	if (pFunction)
	{
		Tmp.Format("Function(+4096): %s   ", pFunction->Name);
		Result += Tmp;
	}
	else
	{
		Result += "Function(+4096): [none]   ";
	}

	

	return Result;
}


void CSrRawDataDlg::OnEnSelchangeTextcontrol(NMHDR *pNMHDR, LRESULT *pResult)
{
	SELCHANGE *pSelChange = reinterpret_cast<SELCHANGE *>(pNMHDR);
	*pResult = 0;

	if (!m_UpdateSelection) return;

	CString Buffer;
	srrawdata_lineinfo_t LineInfo;

	bool Result = FindLineInfo (LineInfo, pSelChange->chrg.cpMin);
	
	if (Result)
	{
		//Buffer.Format("%d - %d\r\nLineInfo %d\r\n", pSelChange->chrg.cpMin, pSelChange->chrg.cpMax, LineInfo.SelIndex);

		CString Buffer1;
		dword Data = 0;
		dword Offset = (pSelChange->chrg.cpMin - LineInfo.SelIndex + 1) / 3 + LineInfo.DataOffset;

		if (Offset + 4 < LineInfo.pSubrecord->GetRecordSize())
		{
			memcpy(&Data, LineInfo.pSubrecord->GetData() + Offset, 4);
			//Buffer1.Format("Data = %08X", Data);
			Buffer = FormatValueText(Data);
		}
		else if (Offset < LineInfo.pSubrecord->GetRecordSize())
		{
			memcpy(&Data, LineInfo.pSubrecord->GetData() + Offset, LineInfo.pSubrecord->GetRecordSize() - Offset);
			//Buffer1.Format("Data = %08X", Data);
			Buffer = FormatValueText(Data);
		}
		else
		{
			//Buffer1 = "No Data";
		}

		//Buffer += Buffer1;
	}
	else
	{
		//Buffer.Format("%d - %d\r\nLineInfo Not Found", pSelChange->chrg.cpMin, pSelChange->chrg.cpMax);
		Buffer = "";
	}

	m_ValueText.SetWindowText(Buffer);	
}


 bool CSrRawDataDlg::FindLineInfo (srrawdata_lineinfo_t& Result, const long SelIndex)
{

	for (CLineInfoArray::iterator i = m_LineInfos.begin(); i != m_LineInfos.end(); ++i)
	{
		if (SelIndex < i->SelIndex) continue;
		if (SelIndex > i->SelIndex + 48) continue;

		Result = *i;
		return true;
	}

	return false;
}