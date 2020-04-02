/*===========================================================================
 *
 * File:		SrBoundsDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRBOUNDSDLG_H
#define __SRBOUNDSDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "modfile/subrecords/srboundssubrecord.h"
#include "afxwin.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrBoundsDlg Definition
 *
 *=========================================================================*/
class CSrBoundsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrBoundsDlg)

public:
	srboundsdata_t	m_BoundsData;


	CSrBoundsDlg(CWnd* pParent = NULL);
	virtual ~CSrBoundsDlg();

	enum { IDD = IDD_BOUNDS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	void SetControlData (void);
	void GetControlData (void);

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_X1;
	CEdit m_Y1;
	CEdit m_Z1;
	CEdit m_X2;
	CEdit m_Y2;
	CEdit m_Z2;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
/*===========================================================================
 *		End of Class CSrBoundsDlg Definition
 *=========================================================================*/

	
bool SrEditBoundsDlg (srboundsdata_t& Data);


#endif
/*===========================================================================
 *		End of File SrBoundsDlg.H
 *=========================================================================*/
