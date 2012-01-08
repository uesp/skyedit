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
	#include "afxwin.h"
	#include <vector>
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


	struct srrawdata_lineinfo_t
	{
		long			SelIndex;
		CSrSubrecord*	pSubrecord;
		dword			SubrecordIndex;
		dword			DataOffset;
	};

	typedef std::vector<srrawdata_lineinfo_t> CLineInfoArray;

/*===========================================================================
 *
 * Begin Class CSrRawDataDlg Definition
 *
 *=========================================================================*/
class CSrRawDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrRawDataDlg)

protected:
	CSrRecord*			m_pRecord;
	CSrRecordHandler&	m_RecordHandler;
	CFont				m_TextFont;

	CHARFORMAT2 m_HexFmt1;
	CHARFORMAT2 m_HexFmt2;
	CHARFORMAT2 m_StringFmt;
	CHARFORMAT2 m_DefaultFmt;

	CHARFORMAT2* m_pCurrentFmt;

	bool		m_UpdateSelection;
	bool		m_SummaryOnly;

	CLineInfoArray	m_LineInfos;
	

protected:
	void AddText (const char* pString, ...);
	void OutputSubrecord (CSrSubrecord* pSubrecord, const int i);
	bool FindLineInfo (srrawdata_lineinfo_t& Result, const long SelIndex);
	CString FormatValueText (const dword Data);

public:
	CSrRawDataDlg(CSrRecordHandler&	Handler, CWnd* pParent = NULL); 
	virtual ~CSrRawDataDlg();

	int DoModal (CSrRecord* pRecord, const bool SummaryOnly);

	void SetControlData (void);


	enum { IDD = IDD_RAWDATA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()

public:
	CRichEditCtrl m_Text;

	virtual BOOL OnInitDialog();
	CEdit m_ValueText;
	afx_msg void OnEnSelchangeTextcontrol(NMHDR *pNMHDR, LRESULT *pResult);
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
