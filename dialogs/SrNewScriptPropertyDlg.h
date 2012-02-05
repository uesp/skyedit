/*===========================================================================
 *
 * File:		SrNewScriptPropertyDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 February 2012
 *
 *=========================================================================*/
#ifndef __SRNEWSCRIPTPROPERTYDLG_H
#define __SRNEWSCRIPTPROPERTYDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "scripts/SrScriptFile.h"
	#include "modfile/subrecords/srvmadsubrecord.h"
	#include "afxwin.h"
	#include "afxcmn.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrNewScriptPropertyDlg
 *
 *=========================================================================*/
class CSrNewScriptPropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrNewScriptPropertyDlg)

protected:
	srnewscriptpropertyinfo_t	m_NewProperty;


protected:
	void GetControlData (void);
	void FillTypeList (void);

public:
	CSrNewScriptPropertyDlg(CWnd* pParent = NULL);
	virtual ~CSrNewScriptPropertyDlg();

	bool DoModal (srnewscriptpropertyinfo_t& Property);

	enum { IDD = IDD_NEWSCRIPTPROPERTY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK (void);

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_ArrayCheck;
	CButton m_HiddenCheck;
	CComboBox m_TypeList;
	CEdit m_Name;
	CEdit m_Value;
	CEdit m_Document;
};
/*===========================================================================
 *		End of Class CSrNewScriptPropertyDlg
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrNewScriptPropertyDlg.h
 *=========================================================================*/
