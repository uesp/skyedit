
#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageUnknown.h"
#include "afxdialogex.h"
#include "SrInputDialog.h"


IMPLEMENT_DYNAMIC(CSrRacePageUnknown, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageUnknown, CPropertyPage)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_BODYNAMELIST, &CSrRacePageUnknown::OnLvnItemActivateBodynamelist)
END_MESSAGE_MAP()


CSrRacePageUnknown::CSrRacePageUnknown(srraceinfo_t& RaceInfo)
	: CPropertyPage(CSrRacePageUnknown::IDD), m_RaceInfo(RaceInfo)
{
	m_pDlgHandler = NULL;
	m_pParent     = NULL;
}


CSrRacePageUnknown::~CSrRacePageUnknown()
{
}


void CSrRacePageUnknown::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RACEUNKNOWN1, m_Unknown[0]);
	DDX_Control(pDX, IDC_RACEUNKNOWN2, m_Unknown[1]);
	DDX_Control(pDX, IDC_RACEUNKNOWN4, m_Unknown[3]);
	DDX_Control(pDX, IDC_RACEUNKNOWN5, m_Unknown[4]);
	DDX_Control(pDX, IDC_RACEUNKNOWN6, m_Unknown[5]);
	DDX_Control(pDX, IDC_RACEUNKNOWN7, m_Unknown[6]);
	DDX_Control(pDX, IDC_RACEUNKNOWN8, m_Unknown[7]);
	DDX_Control(pDX, IDC_RACEUNKNOWN9, m_Unknown[8]);
	DDX_Control(pDX, IDC_RACEUNKNOWN10, m_Unknown[9]);
	DDX_Control(pDX, IDC_RACEUNKNOWN11, m_Unknown[10]);
	DDX_Control(pDX, IDC_RACEUNKNOWN12, m_Unknown[11]);
	DDX_Control(pDX, IDC_RACEUNKNOWN13, m_Unknown[12]);
	DDX_Control(pDX, IDC_RACEUNKNOWN14, m_Unknown[13]);
	DDX_Control(pDX, IDC_RACEUNKNOWN15, m_Unknown[14]);
	DDX_Control(pDX, IDC_RACEUNKNOWN16, m_Unknown[15]);
	DDX_Control(pDX, IDC_RACEUNKNOWN17, m_Unknown[16]);
	DDX_Control(pDX, IDC_RACEUNKNOWN18, m_Unknown[17]);
	DDX_Control(pDX, IDC_RACEUNKNOWN19, m_Unknown[18]);
	DDX_Control(pDX, IDC_RACEUNKNOWN20, m_Unknown[19]);
	DDX_Control(pDX, IDC_RACEUNKNOWN21, m_Unknown[20]);
	DDX_Control(pDX, IDC_RACEUNKNOWN22, m_Unknown[21]);
	DDX_Control(pDX, IDC_RACEUNKNOWN23, m_Unknown[22]);
	DDX_Control(pDX, IDC_RACEUNKNOWN24, m_Unknown[23]);
	DDX_Control(pDX, IDC_RACEUNKNOWN25, m_Unknown[24]);
	DDX_Control(pDX, IDC_RACEUNKNOWN26, m_Unknown[25]);
	DDX_Control(pDX, IDC_RACETINL, m_Tinl);
	DDX_Control(pDX, IDC_RACEPNAME, m_PName);
	DDX_Control(pDX, IDC_RACEUNAME, m_UName);
	DDX_Control(pDX, IDC_VNAME, m_VName);
	DDX_Control(pDX, IDC_BODYNAMELIST, m_BodyNameList);
}


void CSrRacePageUnknown::GetControlData (void)
{
	CString Buffer;

	m_Tinl.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	m_RaceInfo.SetTinl(Buffer);

	m_VName.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	m_RaceInfo.SetVName(Buffer);

	for (dword i = 0; i < m_RaceInfo.BodyNames.GetSize(); ++i)
	{
		Buffer = m_BodyNameList.GetItemText(i, 0);
		m_RaceInfo.BodyNames[i]->SetString(Buffer);
	}
}


void CSrRacePageUnknown::SetControlData (void)
{	CString Buffer;

	Buffer.Empty();
	if (m_RaceInfo.pTinl) Buffer.Format("%hd", m_RaceInfo.pTinl->GetValue());
	m_Tinl.SetWindowText(Buffer);

	Buffer.Empty();
	if (m_RaceInfo.pVName) Buffer.Format("0x%08X", m_RaceInfo.pVName->GetValue());
	m_VName.SetWindowText(Buffer);

	Buffer.Format("%g", m_RaceInfo.PName.GetValue());
	m_PName.SetWindowText(Buffer);

	Buffer.Format("%g", m_RaceInfo.UName.GetValue());
	m_UName.SetWindowText(Buffer);

	for (dword i = 0; i < m_RaceInfo.BodyNames.GetSize(); ++i)
	{
		m_BodyNameList.InsertItem(i, m_RaceInfo.BodyNames[i]->GetString().c_str());
	}
}


void CSrRacePageUnknown::OnLvnItemActivateBodynamelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	CString Buffer = m_BodyNameList.GetItemText(pNMIA->iItem, 0);

	if (!SrInputDialog(Buffer, "Body Name", "Enter body name:")) return;

	m_BodyNameList.SetItemText(pNMIA->iItem, 0, Buffer);
}


BOOL CSrRacePageUnknown::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_BodyNameList.InsertColumn(0, "", LVCFMT_LEFT, 100);
	m_BodyNameList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}
