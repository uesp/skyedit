/*===========================================================================
 *
 * File:		SrEditFlagsDlg.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:  12 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "SrEditFlagsDlg.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEditFlagsDlg, CDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditFlagsDlg Constructor
 *
 *=========================================================================*/
CSrEditFlagsDlg::CSrEditFlagsDlg(CWnd* pParent) : CDialog(CSrEditFlagsDlg::IDD, pParent) 
{
	m_Flags = 0;
	m_Mask = 0xFFFFFFFF;
}
/*===========================================================================
 *		End of Class CSrEditFlagsDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditFlagsDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrEditFlagsDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FLAGS_LIST, m_FlagsList);
}
/*===========================================================================
 *		End of Class Method CSrEditFlagsDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditFlagsDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrEditFlagsDlg::GetControlData (void) {
  int   Index;
  
  m_Flags = 0;

  for (Index = 0; Index < m_FlagsList.GetCount(); ++Index) 
  {
    if (m_FlagsList.GetSel(Index)) m_Flags |= m_FlagsList.GetItemData(Index);
  }

}
/*===========================================================================
 *		End of Class Method CSrEditFlagsDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditFlagsDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrEditFlagsDlg::OnInitDialog() 
{
	CString Buffer;

	CDialog::OnInitDialog();

	for (dword i = 0, j = 1; i < 32; ++i, j <<= 1)
	{
		if (j & m_Mask)
		{
			Buffer.Format("0x%08X", j);
			SrAddListBoxItem(m_FlagsList, Buffer, j);
		}
	 
	}  

	SetControlData();

	return TRUE;
}
/*===========================================================================
 *		End of Class Event CSrEditFlagsDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditFlagsDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CSrEditFlagsDlg::OnOK (void) 
{
  GetControlData();

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrEditFlagsDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditFlagsDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrEditFlagsDlg::SetControlData (void) 
{
	dword Index;
	int   ListIndex;
	dword Mask = 1;
	
	for (Index = 0; Index < 32; ++Index) 
	{
	
		if ((m_Flags & Mask) != 0) 
		{
			ListIndex = FindListBoxItemData(m_FlagsList, Mask, false);
			if (ListIndex >= 0) m_FlagsList.SetSel(ListIndex, TRUE);
		}
	
		Mask <<= 1;
	}
	
}
/*===========================================================================
 *		End of Class Method CSrEditFlagsDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrEditFlagsDlg (Flags, Mask);
 *
 *=========================================================================*/
bool SrEditFlagsDlg (dword& Flags, const dword Mask) 
{
	CSrEditFlagsDlg Dlg;
	int             Result;
	
	Dlg.SetFlags(Flags);
	Dlg.SetMask(Mask);
	
	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);
	
	Flags = Dlg.GetFlags();
	return true;
}
/*===========================================================================
 *		End of Function SrEditFlagsDlg()
 *=========================================================================*/

