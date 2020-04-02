/*===========================================================================
 *
 * File:		Srfindbinarydlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srFindBinaryDlg.h"


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
 * Begin CSrFindBinaryDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrFindBinaryDlg, CDialog)
	//{{AFX_MSG_MAP(CSrFindBinaryDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrFindBinaryDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindBinaryDlg Constructor
 *
 *=========================================================================*/
CSrFindBinaryDlg::CSrFindBinaryDlg(CWnd* pParent) : CDialog(CSrFindBinaryDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CSrFindBinaryDlg)
	//}}AFX_DATA_INIT
}
/*===========================================================================
 *		End of Class CSrFindBinaryDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindBinaryDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrFindBinaryDlg::DoDataExchange (CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrFindBinaryDlg)
	DDX_Control(pDX, IDC_BINARYDATA_TEXT, m_BinaryDataText);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrFindBinaryDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindBinaryDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrFindBinaryDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrFindBinaryDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFindBinaryDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CSrFindBinaryDlg::OnOK() {

  m_BinaryDataText.GetWindowText(m_BinaryData);
  m_BinaryData.TrimLeft(" \t");
  m_BinaryData.TrimRight(" \t");

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrFindBinaryDlg::OnOK()
 *=========================================================================*/
