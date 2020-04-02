/*===========================================================================
 *
 * File:		SrBodypartslistdlg.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "SrBodyPartsListDlg.h"
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
BEGIN_MESSAGE_MAP(CSrBodyPartsDlg, CDialog)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBodyPartsDlg Constructor
 *
 *=========================================================================*/
CSrBodyPartsDlg::CSrBodyPartsDlg(CWnd* pParent) : CDialog(CSrBodyPartsDlg::IDD, pParent) 
{
	m_BodyParts = 0;
}
/*===========================================================================
 *		End of Class CSrBodyPartsDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBodyPartsDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrBodyPartsDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PARTS_LIST, m_PartsList);
}
/*===========================================================================
 *		End of Class Method CSrBodyPartsDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBodyPartsDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrBodyPartsDlg::GetControlData (void) {
  int   Index;
  
  m_BodyParts = 0;

  for (Index = 0; Index < m_PartsList.GetCount(); ++Index) 
  {
    if (m_PartsList.GetSel(Index)) m_BodyParts |= m_PartsList.GetItemData(Index);
  }

}
/*===========================================================================
 *		End of Class Method CSrBodyPartsDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBodyPartsDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrBodyPartsDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();

  for (dword i = 0; s_SrBodyParts[i].pString != NULL; ++i)
  {
	  SrAddListBoxItem(m_PartsList, s_SrBodyParts[i].pString, s_SrBodyParts[i].Value);
  }  

  SetControlData();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrBodyPartsDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBodyPartsDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CSrBodyPartsDlg::OnOK (void) 
{
  GetControlData();

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrBodyPartsDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBodyPartsDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrBodyPartsDlg::SetControlData (void) 
{
	dword Index;
	int   ListIndex;
	dword Mask = 1;
	
	for (Index = 0; Index < 32; ++Index) 
	{
	
		if ((m_BodyParts & Mask) != 0) 
		{
			ListIndex = FindListBoxItemData(m_PartsList, Mask, false);
			if (ListIndex >= 0) m_PartsList.SetSel(ListIndex, TRUE);
		}
	
		Mask <<= 1;
	}
	
}
/*===========================================================================
 *		End of Class Method CSrBodyPartsDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrEditBodyPartsDlg (BodyParts);
 *
 *=========================================================================*/
bool SrEditBodyPartsDlg (dword& BodyParts) 
{
  CSrBodyPartsDlg Dlg;
  int             Result;

  Dlg.SetBodyParts(BodyParts);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  BodyParts = Dlg.GetBodyParts();
  return (true);
}
/*===========================================================================
 *		End of Function SrEditBodyPartsDlg()
 *=========================================================================*/

