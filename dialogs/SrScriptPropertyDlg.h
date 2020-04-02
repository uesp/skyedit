/*===========================================================================
 *
 * File:		SrScriptPropertyDlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	30 January 2012
 *
 *=========================================================================*/
#ifndef __SRSCRIPTPROPERTYDLG_H
#define __SRSCRIPTPROPERTYDLG_H


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


#define SR_SCRIPTPROPLIST_INDEXNAME		0
#define SR_SCRIPTPROPLIST_INDEXTYPE		1
#define SR_SCRIPTPROPLIST_INDEXVALUE	2


struct srpropertyinfo_t
{
	srvmadproperty_t*	pVmadProperty;
	srscriptproperty_t*	pScriptProperty;
	srscriptreftype_t*  pRefType;
	bool				IsUsed;

	srpropertyinfo_t() : pVmadProperty(NULL), pScriptProperty(NULL), IsUsed(false), pRefType(NULL)
	{
	}
};

typedef CSrPtrArray<srpropertyinfo_t> CSrPropertyInfoArray;


/*===========================================================================
 *
 * Begin Class CSrScriptPropertyDlg
 *
 *=========================================================================*/
class CSrScriptPropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSrScriptPropertyDlg)

protected:
	CSrRecordHandler*		m_pRecordHandler;
	srvmadscript_t*			m_pScriptInfo;
	srvmadscript_t			m_ScriptCopy;
	CSrScriptFile*			m_pScriptFile;
	bool					m_DeleteScriptFile;
	bool					m_IsInitializing;

	CSrPropertyInfoArray	m_PropertyInfos;
	srpropertyinfo_t*		m_pCurrentProperty;

	srvmadpropertydata_t*	m_pCurrentData;
	bool					m_IsPropertyArray;


public:
	enum { IDD = IDD_SCRIPTPROPERTY_DLG };

protected:
	void GetControlData (void);
	void SetControlData (void);

	void InitPropertyLists (void);

	void CreatePropertyInfos (void);

	srpropertyinfo_t* FindPropertyInfo(srvmadproperty_t*   pProperty);
	srpropertyinfo_t* FindPropertyInfo(srscriptproperty_t* pProperty);
	srpropertyinfo_t* FindPropertyInfo(const char* pName);

	int AddPropertyToList (srpropertyinfo_t* pInfo);

	CString GetPropertySingleValue (srvmadproperty_t* pProperty, srscriptreftype_t* pRefType);
	CString GetPropertyDataString  (srvmadpropertydata_t* pData, srscriptreftype_t* pRefType);

	int GetSelectedItem (CListCtrl& List);

	void EnablePropertyControls (void);
	void EnableValueControls (void);
	void SetCurrentProperty (srpropertyinfo_t* pInfo);
	void GetPropertyControlData (void);
	void SetPropertyControlData (void);
	int UpdatePropertyList(srpropertyinfo_t* pInfo);
	void SetPropertyListText (const int ListIndex, srpropertyinfo_t* pInfo);

	void FillPropertyDataList (void);
	void SetCurrentPropertyData(srvmadpropertydata_t* pData);
	void UpdatePropertyDataList (srvmadpropertydata_t* pData);
	void UpdatePropertyDataList (const int ListIndex, srvmadpropertydata_t* pData);
	int AddPropertyDataList (const int ListIndex, srvmadpropertydata_t* pData);
	int FindPropertyData (srvmadpropertydata_t* pData);

public:
	CSrScriptPropertyDlg(CWnd* pParent = NULL);
	virtual ~CSrScriptPropertyDlg();


	bool DoModal (srvmadscript_t& ScriptInfo, CSrRecordHandler*	pRecordHandler);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	CListCtrl m_PropertyList;

	afx_msg void OnLvnItemActivateProperties(NMHDR *pNMHDR, LRESULT *pResult);

	CEdit m_PropertyName;
	CEdit m_PropertyValue;
	CEdit m_PropertyValue2;
	CButton m_ValueButton;
	CButton m_ValueButton2;
	CStatic m_ValueLabel;
	CStatic m_ValueLabel2;
	CButton m_ValueUseDefault;
	CListCtrl m_PropertyDataList;
	CButton m_AddDataButton;
	CButton m_DuplicateDataButton;
	CButton m_DeleteDataButton;
	CButton m_MoveUpDataButton;
	CButton m_MoveDownDataButton;
	
	afx_msg void OnBnClickedSelectPropertyvalue();
	afx_msg void OnBnClickedPropertyvalueUsedefault();
	afx_msg void OnLvnItemchangedPropertylist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedValueUsedefault();
	afx_msg void OnBnClickedSelectPropertyvalue2();
	afx_msg void OnLvnItemchangedPropertydatalist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPropertyAdd();
	afx_msg void OnBnClickedPropertyDuplicate();
	afx_msg void OnBnClickedPropertyDelete();	
	afx_msg void OnBnClickedPropertyMoveup();
	afx_msg void OnBnClickedPropertyMovedown();
	afx_msg void OnBnClickedNewProperty();
};
/*===========================================================================
 *		End of Class CSrScriptPropertyDlg
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrScriptPropertyDlg.H
 *=========================================================================*/
