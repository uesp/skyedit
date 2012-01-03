/*===========================================================================
 *
 * File:		SrRawDataDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRRAWDATADLG_H
#define __SRRAWDATADLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "afxcmn.h"
	#include "modfile/SrMultiRecordHandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrRawDataDlg Definition
 *
 *=========================================================================*/
class CSrRawDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrRawDataDlg)

protected:
	CSrRecord*  m_pRecord;
	CFont		m_TextFont;

	CHARFORMAT2 m_HexFmt1;
	CHARFORMAT2 m_HexFmt2;
	CHARFORMAT2 m_StringFmt;
	CHARFORMAT2 m_DefaultFmt;

	CHARFORMAT2* m_pCurrentFmt;


protected:
	void AddText (const char* pString, ...);

public:
	CSrRawDataDlg(CWnd* pParent = NULL); 
	virtual ~CSrRawDataDlg();

	int DoModal (CSrRecord* pRecord);

	void SetControlData (void);


	enum { IDD = IDD_RAWDATA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()

public:
	CRichEditCtrl m_Text;

	virtual BOOL OnInitDialog();
};
/*===========================================================================
 *		End of Class CSrPromptDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrRawDataDlg.H
 *=========================================================================*/
