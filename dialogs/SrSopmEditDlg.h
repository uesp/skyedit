/*===========================================================================
 *
 * File:		SrSopmEditDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	8 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRSOPMEDITDLG_H
#define __SRSOPMEDITDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "afxwin.h"
	#include "afxcmn.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


	struct srsopmeditinfo_t
	{
		srsopmanamdata_t*	pAnamData;
		srsopmonamdata_t*	pOnamData;
		srsopmsnamdata_t*	pSnamData;
	};

/*===========================================================================
 *
 * Begin Class CSrSopmEditDlg Definition
 *
 *=========================================================================*/
class CSrSopmEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrSopmEditDlg)

public: 
	srsopmeditinfo_t	m_EditInfo;


	CSrSopmEditDlg(CWnd* pParent = NULL);
	virtual ~CSrSopmEditDlg();

	enum { IDD = IDD_SOPMEDIT_DLG };

	void GetControlData (void);
	void SetControlData (void);

	void EnableControls (void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog (void);
	afx_msg void OnBnClickedOk();

	CEdit m_Data[24];
	CStatic m_DataLabel[8];

	DECLARE_MESSAGE_MAP()
};
/*===========================================================================
 *		End of Class CSrSopmEditDlg Definition
 *=========================================================================*/


bool SrSopmEditDlg (srsopmeditinfo_t EditInfo);

#endif
/*===========================================================================
 *		End of File SrSopmEditDlg.H
 *=========================================================================*/

