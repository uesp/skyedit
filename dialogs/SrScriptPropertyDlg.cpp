/*===========================================================================
 *
 * File:		SrScriptPropertyDlg.cpp
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	30 January 2012
 *
 *=========================================================================*/
#include "stdafx.h"
#include "sredit.h"
#include "dialogs\SrScriptPropertyDlg.h"
#include "dialogs\SrNewScriptPropertyDlg.h"
#include "afxdialogex.h"
#include "common/srutils.h"
#include "srselectrecorddlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNAMIC(CSrScriptPropertyDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrScriptPropertyDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_PROPERTYLIST, &CSrScriptPropertyDlg::OnLvnItemActivateProperties)
	ON_BN_CLICKED(IDC_SELECT_PROPERTYVALUE, &CSrScriptPropertyDlg::OnBnClickedSelectPropertyvalue)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROPERTYLIST, &CSrScriptPropertyDlg::OnLvnItemchangedPropertylist)
	ON_BN_CLICKED(IDC_VALUE_USEDEFAULT, &CSrScriptPropertyDlg::OnBnClickedValueUsedefault)
	ON_BN_CLICKED(IDC_SELECT_PROPERTYVALUE2, &CSrScriptPropertyDlg::OnBnClickedSelectPropertyvalue2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROPERTYDATALIST, &CSrScriptPropertyDlg::OnLvnItemchangedPropertydatalist)
	ON_BN_CLICKED(IDC_PROPERTY_ADD, &CSrScriptPropertyDlg::OnBnClickedPropertyAdd)
	ON_BN_CLICKED(IDC_PROPERTY_DUPLICATE, &CSrScriptPropertyDlg::OnBnClickedPropertyDuplicate)
	ON_BN_CLICKED(IDC_PROPERTY_DELETE, &CSrScriptPropertyDlg::OnBnClickedPropertyDelete)
	ON_BN_CLICKED(IDC_PROPERTY_MOVEUP, &CSrScriptPropertyDlg::OnBnClickedPropertyMoveup)
	ON_BN_CLICKED(IDC_PROPERTY_MOVEDOWN, &CSrScriptPropertyDlg::OnBnClickedPropertyMovedown)
	ON_BN_CLICKED(IDC_NEW_PROPERTY, &CSrScriptPropertyDlg::OnBnClickedNewProperty)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


CSrScriptPropertyDlg::CSrScriptPropertyDlg(CWnd* pParent)
			: CDialogEx(CSrScriptPropertyDlg::IDD, pParent)
{
	m_pScriptFile = NULL;
	m_pRecordHandler = NULL;
	m_pCurrentProperty = NULL;
	m_DeleteScriptFile = false;
	m_IsInitializing = true;
	m_pCurrentData = NULL;
	m_IsPropertyArray = false;
}


CSrScriptPropertyDlg::~CSrScriptPropertyDlg()
{
	if (m_DeleteScriptFile) delete m_pScriptFile;
}


void CSrScriptPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROPERTYLIST, m_PropertyList);
	DDX_Control(pDX, IDC_PROPERTY_NAME, m_PropertyName);
	DDX_Control(pDX, IDC_PROPERTY_VALUE, m_PropertyValue);
	DDX_Control(pDX, IDC_PROPERTY_VALUE2, m_PropertyValue2);
	DDX_Control(pDX, IDC_SELECT_PROPERTYVALUE, m_ValueButton);
	DDX_Control(pDX, IDC_SELECT_PROPERTYVALUE2, m_ValueButton2);
	DDX_Control(pDX, IDC_VALUE1_LABEL, m_ValueLabel);
	DDX_Control(pDX, IDC_VALUE2_LABEL, m_ValueLabel2);
	DDX_Control(pDX, IDC_VALUE_USEDEFAULT, m_ValueUseDefault);
	DDX_Control(pDX, IDC_PROPERTYDATALIST, m_PropertyDataList);
	DDX_Control(pDX, IDC_PROPERTY_ADD, m_AddDataButton);
	DDX_Control(pDX, IDC_PROPERTY_DUPLICATE, m_DuplicateDataButton);
	DDX_Control(pDX, IDC_PROPERTY_DELETE, m_DeleteDataButton);
	DDX_Control(pDX, IDC_PROPERTY_MOVEUP, m_MoveUpDataButton);
	DDX_Control(pDX, IDC_PROPERTY_MOVEDOWN, m_MoveDownDataButton);
}


BOOL CSrScriptPropertyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_IsInitializing = true;

	InitPropertyLists();

	m_pScriptFile->ParseProperties();
	CreatePropertyInfos();

	CString Buffer;
	Buffer.Format("Script Properties -- %s", m_pScriptInfo->Name.c_str());
	SetWindowText(Buffer);
	
	SetControlData();
	SetCurrentProperty(NULL);	
	
	m_IsInitializing = false;
	return TRUE;
}


void CSrScriptPropertyDlg::CreatePropertyInfos (void)
{
	CSrScriptPropertyArray& Properties = m_pScriptFile->GetProperties();
	srpropertyinfo_t* pInfo;

	m_PropertyInfos.Destroy();

	for (dword i = 0; i < Properties.GetSize(); ++i)
	{
		pInfo = m_PropertyInfos.AddNew();
		pInfo->pScriptProperty = Properties[i];
		pInfo->pRefType = GetSrScriptRefTypeInfo(pInfo->pScriptProperty->RefType);
	}

	for (dword i = 0; i < m_ScriptCopy.Properties.GetSize(); ++i)
	{
		pInfo = FindPropertyInfo(m_ScriptCopy.Properties[i]->Name);

		if (pInfo != NULL)
		{
			pInfo->pVmadProperty = m_ScriptCopy.Properties[i];
			pInfo->IsUsed = true;
		}
		else
		{
			AddSrGeneralError("Warning: Failed to find used property '%s' in script '%s'!", m_ScriptCopy.Properties[i]->Name.c_str(), m_ScriptCopy.Name.c_str());

				/* TODO: Decide whether to allow 'missing' properties to be saved/displayed */
			//pInfo = m_PropertyInfos.AddNew();
			//pInfo->pScriptProperty = Properties[i];
			//pInfo->IsUsed = true;
		}
	}

}


srpropertyinfo_t* CSrScriptPropertyDlg::FindPropertyInfo(const char* pName)
{
	for (dword i = 0; i < m_PropertyInfos.GetSize(); ++i)
	{
		if (m_PropertyInfos[i]->pScriptProperty && m_PropertyInfos[i]->pScriptProperty->Name.CompareNoCase(pName) == 0) return m_PropertyInfos[i];
		if (m_PropertyInfos[i]->pVmadProperty   && m_PropertyInfos[i]->pVmadProperty->Name.CompareNoCase(pName)   == 0) return m_PropertyInfos[i];
	}

	return NULL;
}



srpropertyinfo_t* CSrScriptPropertyDlg::FindPropertyInfo(srvmadproperty_t* pProperty)
{

	for (dword i = 0; i < m_PropertyInfos.GetSize(); ++i)
	{
		if (m_PropertyInfos[i]->pVmadProperty == pProperty) return m_PropertyInfos[i];
	}

	return NULL;
}


srpropertyinfo_t* CSrScriptPropertyDlg::FindPropertyInfo(srscriptproperty_t* pProperty)
{

	for (dword i = 0; i < m_PropertyInfos.GetSize(); ++i)
	{
		if (m_PropertyInfos[i]->pScriptProperty = pProperty) return m_PropertyInfos[i];
	}

	return NULL;
}


void CSrScriptPropertyDlg::InitPropertyLists (void)
{
	m_PropertyList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_PropertyDataList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_PropertyList.InsertColumn(0, "Property", LVCFMT_CENTER, 190, 0);
	m_PropertyList.InsertColumn(1, "Type",     LVCFMT_CENTER, 150, 1);
	m_PropertyList.InsertColumn(2, "Value",    LVCFMT_CENTER, 190, 1);

	m_PropertyDataList.InsertColumn(0, "Values", LVCFMT_CENTER, 240, 0);
}


void CSrScriptPropertyDlg::OnOK (void)
{
	GetControlData();
	CDialogEx::OnOK();
}


void CSrScriptPropertyDlg::GetControlData (void)
{
	GetPropertyControlData();
}


void CSrScriptPropertyDlg::SetControlData (void)
{
	CSrScriptPropertyArray& Properties = m_pScriptFile->GetProperties();
	CString Buffer;
	
	m_PropertyList.DeleteAllItems();

	for (dword i = 0; i < m_PropertyInfos.GetSize(); ++i)
	{
		AddPropertyToList(m_PropertyInfos[i]);
	}
	
}


int CSrScriptPropertyDlg::AddPropertyToList (srpropertyinfo_t* pInfo)
{
	int ListIndex = m_PropertyList.GetItemCount();
	
	if (pInfo == NULL) return -1;

	if (pInfo->pScriptProperty != NULL)
	{
		ListIndex = m_PropertyList.InsertItem(ListIndex, pInfo->pScriptProperty->Name.c_str());
	}
	else if (pInfo->pVmadProperty != NULL)
	{
		ListIndex = m_PropertyList.InsertItem(ListIndex, pInfo->pVmadProperty->Name.c_str());
	}
	else
	{
		return -1;
	}

	SetPropertyListText(ListIndex, pInfo);
	return ListIndex;
}


void CSrScriptPropertyDlg::SetPropertyListText (const int ListIndex, srpropertyinfo_t* pInfo)
{
	CString Buffer;

	if (pInfo == NULL || ListIndex < 0) return;

	if (pInfo->pScriptProperty != NULL)
	{
		Buffer.Format("%s%s", pInfo->pScriptProperty->TypeName.c_str(), pInfo->pScriptProperty->Type > 10 ? "[ ]" : "");
	}
	else if (pInfo->pVmadProperty != NULL)
	{
		Buffer.Format("%s%s", GetSrScriptPropertyTypeString(pInfo->pVmadProperty->Type), pInfo->pVmadProperty->Type > 10 ? "[ ]" : "");
	}
	else
	{
		return;
	}

	m_PropertyList.SetItemText(ListIndex, SR_SCRIPTPROPLIST_INDEXTYPE, Buffer);
	m_PropertyList.SetItemData(ListIndex, (DWORD) pInfo);

	if (pInfo->pVmadProperty == NULL || !pInfo->IsUsed) 
	{
		m_PropertyList.SetItemText(ListIndex, SR_SCRIPTPROPLIST_INDEXVALUE, "{ none }");
		return;
	}

	if (pInfo->pVmadProperty->Type > 10)
	{
		Buffer.Format("array[%d]", pInfo->pVmadProperty->Data.GetSize());
		m_PropertyList.SetItemText(ListIndex, SR_SCRIPTPROPLIST_INDEXVALUE, Buffer);
	}
	else
		m_PropertyList.SetItemText(ListIndex, SR_SCRIPTPROPLIST_INDEXVALUE, GetPropertySingleValue(pInfo->pVmadProperty, pInfo->pRefType));
}


CString CSrScriptPropertyDlg::GetPropertyDataString (srvmadpropertydata_t* pData, srscriptreftype_t* pRefType)
{
	CString     Output;
	const char* pID1;
	
	if (pData == NULL) return Output;

	switch (pData->Type % 10)
	{		
		case SR_VMAD_PROPDATA_REFERENCE:

			if (m_pRecordHandler == NULL)
			{
				Output.Format("0x%08X", pData->FormID);
				return Output;
			}

			pID1 = m_pRecordHandler->GetEditorID(pData->FormID);

			if (pRefType && pRefType->Type == SR_SCRIPT_REFTYPE_REFERENCEALIAS)
			{
				if (pID1 == NULL)
					Output.Format("0x%08X - Alias %d", pData->FormID, (int) pData->QuestAlias);
				else
					Output.Format("%s - Alias %d", pID1, (int) pData->QuestAlias);
			}
			else
			{
				if (pID1 == NULL)
					Output.Format("0x%08X", pData->FormID);
				else
					Output = pID1;
			}
			
			break;
		case SR_VMAD_PROPDATA_STRING:
			Output = pData->String;
			break;
		case SR_VMAD_PROPDATA_INT:			
			Output.Format("%d", pData->iValue);
			break;
		case SR_VMAD_PROPDATA_FLOAT:
			Output.Format("%g", pData->fValue);
			break;
		case SR_VMAD_PROPDATA_BOOL:
			Output.Format("%s", pData->bValue ? "true" : "false");
			break;
		default:
			Output.Format("{ unknown }");
			break;
	}

	return Output;
}


CString CSrScriptPropertyDlg::GetPropertySingleValue (srvmadproperty_t* pProperty, srscriptreftype_t* pRefType)
{
	CString Output;

	if (pProperty == NULL) return Output;

	if (pProperty->Data.GetSize() < 1)
	{
		Output.Format("{ error }");
		return Output;
	}

	return GetPropertyDataString(pProperty->Data[0], pRefType);
}


int CSrScriptPropertyDlg::GetSelectedItem (CListCtrl& List) 
{
	POSITION ListPos;
	int      ListIndex;

	ListPos = List.GetFirstSelectedItemPosition();
	if (ListPos == NULL) return -1;

	ListIndex = List.GetNextSelectedItem(ListPos);
	return ListIndex;
}


void CSrScriptPropertyDlg::EnablePropertyControls (void)
{
	bool Enable = (m_pCurrentProperty != NULL);

	m_PropertyName.EnableWindow(Enable);
	m_ValueUseDefault.EnableWindow(Enable);
	m_PropertyValue.EnableWindow(Enable);
	m_ValueButton.EnableWindow(Enable);	
	m_PropertyValue2.EnableWindow(Enable);
	m_ValueButton2.EnableWindow(Enable);

	m_PropertyDataList.EnableWindow(Enable);
	m_AddDataButton.EnableWindow(Enable);
	m_DuplicateDataButton.EnableWindow(Enable);
	m_DeleteDataButton.EnableWindow(Enable);
	m_MoveUpDataButton.EnableWindow(Enable);
	m_MoveDownDataButton.EnableWindow(Enable);

	EnableValueControls();
}


void CSrScriptPropertyDlg::EnableValueControls (void)
{
	if (m_pCurrentProperty == NULL) return;

	bool EnableArray = m_pCurrentProperty->IsUsed && m_IsPropertyArray;
	bool EnableValue = m_pCurrentProperty->IsUsed && m_pCurrentData != NULL;
	bool EnableSelectButton = (m_pCurrentProperty->pScriptProperty->Type == 1) && (m_pCurrentProperty->pRefType != NULL); 

	bool HasDualValues = m_pCurrentProperty->pRefType != NULL ? (m_pCurrentProperty->pRefType->Type == SR_SCRIPT_REFTYPE_REFERENCEALIAS) : false;
	
	bool EnableValue2 = EnableValue && m_pCurrentProperty->pScriptProperty->Type == 1 && HasDualValues;
	bool EnableSelectButton2 = false;

	m_ValueButton.EnableWindow(EnableSelectButton && EnableValue);
	m_PropertyValue.EnableWindow(EnableValue);

	m_ValueButton2.EnableWindow(EnableSelectButton2 && EnableValue2);
	m_PropertyValue2.EnableWindow(EnableValue2);

	m_PropertyDataList.EnableWindow(EnableArray);
	m_AddDataButton.EnableWindow(EnableArray);
	m_DuplicateDataButton.EnableWindow(EnableArray);
	m_DeleteDataButton.EnableWindow(EnableArray);
	m_MoveUpDataButton.EnableWindow(EnableArray);
	m_MoveDownDataButton.EnableWindow(EnableArray);
}


void CSrScriptPropertyDlg::SetCurrentProperty (srpropertyinfo_t* pInfo)
{
	GetPropertyControlData();

	m_pCurrentProperty = pInfo;
	m_pCurrentData = NULL;
	m_IsPropertyArray = false;
	FillPropertyDataList();

	if (pInfo && pInfo->pVmadProperty) m_pCurrentData = pInfo->pVmadProperty->Data[0];
	if (pInfo && pInfo->pScriptProperty) m_IsPropertyArray = pInfo->pScriptProperty->Type > 10;
	
	EnablePropertyControls();

	SetPropertyControlData();
}


void CSrScriptPropertyDlg::GetPropertyControlData (void)
{
	CString Buffer;

	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pScriptProperty == NULL) return;

	m_pCurrentProperty->IsUsed = !(m_ValueUseDefault.GetCheck() != 0);

	if (!m_pCurrentProperty->IsUsed && m_pCurrentProperty->pVmadProperty == NULL)
	{
		UpdatePropertyList(m_pCurrentProperty);
		UpdatePropertyDataList(m_pCurrentData);
		return;
	}

	if (m_pCurrentProperty->pVmadProperty == NULL)
	{
		m_pCurrentProperty->pVmadProperty = m_ScriptCopy.Properties.AddNew();
		m_pCurrentProperty->pVmadProperty->Name = m_pCurrentProperty->pScriptProperty->Name;
		m_pCurrentProperty->pVmadProperty->Type = m_pCurrentProperty->pScriptProperty->Type;

		if (m_pCurrentProperty->pScriptProperty->Type < 10)	
		{
			m_pCurrentData = m_pCurrentProperty->pVmadProperty->Data.AddNew();
			m_pCurrentData->Type = m_pCurrentProperty->pVmadProperty->Type;
		}
	}

	m_PropertyValue.GetWindowTextA(Buffer);
	if (m_pCurrentData == NULL) return;

	switch (m_pCurrentData->Type % 10)
	{		
		case SR_VMAD_PROPDATA_REFERENCE:
			Buffer.Trim(" ");

			if (m_pRecordHandler == NULL)
			{			
				m_pCurrentData->FormID = strtoul(Buffer, NULL, 0);
				m_PropertyValue2.GetWindowTextA(Buffer);
				m_pCurrentData->QuestAlias = (word) strtoul(Buffer, NULL, 0); 
				break;
			}
			
			if (m_pCurrentProperty->pRefType && m_pCurrentProperty->pRefType->Type == SR_SCRIPT_REFTYPE_REFERENCEALIAS)
			{
				m_pCurrentData->FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
				m_PropertyValue2.GetWindowTextA(Buffer);
				m_pCurrentData->QuestAlias = (word) strtoul(Buffer, NULL, 0); /* TODO: Proper setting/getting */
			}
			else
			{
				m_pCurrentData->FormID = m_pRecordHandler->FindGeneralFormID(Buffer);
			}

			break;
		case SR_VMAD_PROPDATA_STRING:
			m_pCurrentData->String = Buffer;
			break;
		case SR_VMAD_PROPDATA_INT:			
			m_pCurrentData->iValue = strtol(Buffer, NULL, 0);
			break;
		case SR_VMAD_PROPDATA_FLOAT:
			m_pCurrentData->fValue = (float) strtod(Buffer, NULL);
			break;
		case SR_VMAD_PROPDATA_BOOL:
			Buffer.Trim(" ");

			if (Buffer.CompareNoCase("true") == 0)
				m_pCurrentData->bValue = true;
			else if (Buffer.CompareNoCase("false") == 0)
				m_pCurrentData->bValue = false;
			else
				m_pCurrentData->bValue = strtol(Buffer, NULL, 0) != 0;

			break;
		default:
			break;
	}

	UpdatePropertyDataList(m_pCurrentData);
	UpdatePropertyList(m_pCurrentProperty);
}


int CSrScriptPropertyDlg::UpdatePropertyList(srpropertyinfo_t* pInfo)
{

	for (int i = 0; i < m_PropertyList.GetItemCount(); ++i)
	{
		srpropertyinfo_t* pThisInfo = (srpropertyinfo_t *) m_PropertyList.GetItemData(i);
		if (pThisInfo != pInfo) continue;
		
		SetPropertyListText(i, pInfo);
		return i;
	}

	return -1;
}


void CSrScriptPropertyDlg::SetPropertyControlData (void)
{
	CString Buffer;

	if (m_pCurrentProperty == NULL) 
	{
		m_PropertyName.SetWindowTextA("");
		m_PropertyValue.SetWindowTextA("");
		m_PropertyValue2.SetWindowTextA("");
		m_ValueLabel.SetWindowText("");
		m_ValueLabel2.SetWindowText("");
		FillPropertyDataList();
		return;
	}

	if (m_pCurrentProperty->pScriptProperty == NULL) return;

	m_ValueUseDefault.SetCheck(!m_pCurrentProperty->IsUsed);
	m_PropertyName.SetWindowTextA(m_pCurrentProperty->pScriptProperty->Name.c_str());

	switch (m_pCurrentProperty->pScriptProperty->RefType)
	{
		case SR_SCRIPT_REFTYPE_REFERENCEALIAS:
			m_ValueLabel.SetWindowTextA("Quest");
			m_ValueLabel2.SetWindowTextA("Alias");
			break;
		default:
			Buffer.Format("%s", m_pCurrentProperty->pScriptProperty->TypeName.c_str());
			m_ValueLabel.SetWindowTextA(Buffer);
			m_ValueLabel2.SetWindowTextA("");
			break;
	}
		
	if (m_pCurrentProperty->pVmadProperty == NULL || m_pRecordHandler == NULL || m_pCurrentData == NULL)
	{
		m_PropertyValue.SetWindowTextA("");
		m_PropertyValue2.SetWindowTextA("");
		return;
	}

	switch (m_pCurrentProperty->pScriptProperty->RefType)
	{
		case SR_SCRIPT_REFTYPE_REFERENCEALIAS:
			m_PropertyValue.SetWindowTextA("");
			m_PropertyValue2.SetWindowTextA("");
			m_PropertyValue.SetWindowTextA(m_pRecordHandler->GetEditorID(m_pCurrentData->FormID));
			Buffer.Format("%d", (int) m_pCurrentData->QuestAlias);
			m_PropertyValue2.SetWindowTextA(Buffer);
			break;
		default:
			m_PropertyValue.SetWindowTextA(GetPropertyDataString(m_pCurrentData, m_pCurrentProperty->pRefType));
			m_PropertyValue2.SetWindowTextA("");
			break;
	}
}


bool CSrScriptPropertyDlg::DoModal (srvmadscript_t& ScriptInfo, CSrRecordHandler* pRecordHandler)
{
	m_pScriptInfo    = &ScriptInfo;
	m_ScriptCopy.Copy(ScriptInfo);
	m_pScriptFile    = GetSrEditApp().FindScriptName(ScriptInfo.Name);
	m_pRecordHandler = pRecordHandler;

	if (m_pScriptFile == NULL)
	{
		m_pScriptFile = new CSrScriptFile;
		m_DeleteScriptFile = true;
	}

	if (!m_pScriptFile->IsLoaded())
	{
		CSString Filename;

		GetSrInstallPath(Filename);
		Filename += "data\\scripts\\source\\";
		Filename += ScriptInfo.Name;
		Filename += ".psc";

		bool Result = m_pScriptFile->Load(Filename);
		if (!Result) return SrEditShowError("Script Property Error", "Failed to load the script '%s'!", ScriptInfo.Name);
	}

	int Result = CDialogEx::DoModal();
	if (Result != IDOK) return false;

	ScriptInfo.Properties.Destroy();
	
	for (dword i = 0; i < m_PropertyInfos.GetSize(); ++i)
	{
		srpropertyinfo_t* pInfo = m_PropertyInfos[i];
		if (!pInfo->IsUsed) continue;
		if (pInfo->pVmadProperty == NULL) continue;
		
		srvmadproperty_t* pNewProperty = ScriptInfo.Properties.AddNew();
		pNewProperty->Copy(*pInfo->pVmadProperty);
	}

	return true;
}


void CSrScriptPropertyDlg::OnLvnItemActivateProperties(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
}


void CSrScriptPropertyDlg::OnLvnItemchangedPropertylist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;
	if (m_IsInitializing) return;

	srpropertyinfo_t* pInfo = (srpropertyinfo_t *) m_PropertyList.GetItemData(pNMLV->iItem);
	SetCurrentProperty(pInfo);
}


void CSrScriptPropertyDlg::OnBnClickedValueUsedefault()
{
	GetPropertyControlData();
	EnableValueControls();
}


void CSrScriptPropertyDlg::OnBnClickedSelectPropertyvalue()
{
	CString Buffer;

	if (m_pCurrentProperty == NULL) return;
	if (m_pRecordHandler == NULL) return;
	if (m_pCurrentProperty->pRefType == NULL) return;

	if (m_pCurrentProperty->pRefType->RecordType == SR_NAME_NULL || m_pCurrentProperty->pRefType->RecordType == SR_NAME_all)
	{
		Buffer.Format("I can't select records of type '%s' yet!", m_pCurrentProperty->pRefType->pName);
		AfxMessageBox(Buffer, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	m_PropertyValue.GetWindowTextA(Buffer);

	bool Result = SrSelectRecord(Buffer, m_pRecordHandler, m_pCurrentProperty->pRefType->RecordType, &CSrIdRecord::s_FieldMap);
	if (!Result) return;
	
	m_PropertyValue.SetWindowTextA(Buffer);
	GetPropertyControlData();
}


void CSrScriptPropertyDlg::OnBnClickedSelectPropertyvalue2()
{
	if (m_pCurrentProperty == NULL) return;
}


void CSrScriptPropertyDlg::OnLvnItemchangedPropertydatalist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;
	if (m_pCurrentProperty == NULL) return;
	if (!m_IsPropertyArray) return;
	if (m_IsInitializing) return;

	srvmadpropertydata_t* pData = (srvmadpropertydata_t *) m_PropertyDataList.GetItemData(pNMLV->iItem);
	SetCurrentPropertyData(pData);
}


void CSrScriptPropertyDlg::SetCurrentPropertyData(srvmadpropertydata_t* pData)
{
	if (m_pCurrentProperty == NULL) return;

	GetPropertyControlData();

	m_pCurrentData = pData;
	EnablePropertyControls();

	SetPropertyControlData();
}


void CSrScriptPropertyDlg::UpdatePropertyDataList (srvmadpropertydata_t* pData)
{
	if (pData == NULL) return;

	for (int i = 0; i < m_PropertyDataList.GetItemCount(); ++i)
	{
		srvmadpropertydata_t* pThisData = (srvmadpropertydata_t *) m_PropertyDataList.GetItemData(i);
		if (pThisData != pData) continue;

		UpdatePropertyDataList(i, pData);
		return;
	}

}


void CSrScriptPropertyDlg::UpdatePropertyDataList (const int ListIndex, srvmadpropertydata_t* pData)
{
	CString Buffer;

	if (ListIndex < 0 || pData == NULL) return;

	Buffer = GetPropertyDataString(pData, m_pCurrentProperty->pRefType);
	m_PropertyDataList.SetItemText(ListIndex, 0, Buffer);
}


void CSrScriptPropertyDlg::FillPropertyDataList (void)
{
	CString Buffer;

	m_PropertyDataList.DeleteAllItems();

	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pVmadProperty == NULL) return;

	for (dword i = 0; i < m_pCurrentProperty->pVmadProperty->Data.GetSize(); ++i)
	{
		AddPropertyDataList(-1, m_pCurrentProperty->pVmadProperty->Data[i]);
	}

	m_pCurrentData = m_pCurrentProperty->pVmadProperty->Data[0];
	m_PropertyDataList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
}


int CSrScriptPropertyDlg::AddPropertyDataList (const int TargetIndex, srvmadpropertydata_t* pData)
{
	if (pData == NULL) return -1;

	CString Buffer;
	Buffer = GetPropertyDataString(pData, m_pCurrentProperty->pRefType);

	int ListIndex = TargetIndex;
	if (ListIndex < 0) ListIndex = m_PropertyDataList.GetItemCount();
	ListIndex = m_PropertyDataList.InsertItem(ListIndex, Buffer);
	m_PropertyDataList.SetItemData(ListIndex, (DWORD) pData);

	return ListIndex;
}


int CSrScriptPropertyDlg::FindPropertyData (srvmadpropertydata_t* pData)
{

	for (int i = 0; i < m_PropertyDataList.GetItemCount(); ++i)
	{
		srvmadpropertydata_t* pThisData = (srvmadpropertydata_t *) m_PropertyDataList.GetItemData(i);
		if (pThisData == pData) return i;
	}

	return -1;
}


void CSrScriptPropertyDlg::OnBnClickedPropertyAdd()
{
	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pVmadProperty == NULL) return;
	if (!m_IsPropertyArray) return;

	m_IsInitializing = true;
	GetPropertyControlData();

	srvmadpropertydata_t* pNewData = m_pCurrentProperty->pVmadProperty->Data.AddNew();
	pNewData->Type = m_pCurrentProperty->pVmadProperty->Type;

	int ListIndex = AddPropertyDataList(-1, pNewData);
			
	SetCurrentPropertyData(pNewData);
	
	m_PropertyDataList.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_IsInitializing = false;
}


void CSrScriptPropertyDlg::OnBnClickedPropertyDuplicate()
{
	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pVmadProperty == NULL) return;
	if (!m_IsPropertyArray) return;
	if (m_pCurrentData == NULL) return;

	m_IsInitializing = true;
	GetPropertyControlData();

	srvmadpropertydata_t* pNewData = m_pCurrentProperty->pVmadProperty->Data.AddNew();
	*pNewData = *m_pCurrentData;
	pNewData->Type = m_pCurrentProperty->pVmadProperty->Type;

	int ListIndex = AddPropertyDataList(-1, pNewData);
			
	SetCurrentPropertyData(pNewData);
	
	m_PropertyDataList.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_IsInitializing = false;
}


void CSrScriptPropertyDlg::OnBnClickedPropertyDelete()
{
	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pVmadProperty == NULL) return;
	if (!m_IsPropertyArray) return;
	if (m_pCurrentData == NULL) return;

	m_IsInitializing = true;
	GetPropertyControlData();

	m_pCurrentProperty->pVmadProperty->Data.Delete(m_pCurrentData);
	int ListIndex = FindPropertyData(m_pCurrentData);
	m_PropertyDataList.DeleteItem(ListIndex);

	if (ListIndex > 0) --ListIndex;
	m_pCurrentData = NULL;

	SetCurrentPropertyData(m_pCurrentProperty->pVmadProperty->Data[ListIndex]);
	m_PropertyDataList.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_IsInitializing = false;
}


void CSrScriptPropertyDlg::OnBnClickedPropertyMoveup()
{
	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pVmadProperty == NULL) return;
	if (!m_IsPropertyArray) return;
	if (m_pCurrentData == NULL) return;

	m_IsInitializing = true;
	GetPropertyControlData();

	int ListIndex = FindPropertyData(m_pCurrentData);
	if (ListIndex <= 0) return;

	m_pCurrentProperty->pVmadProperty->Data.MoveUp(m_pCurrentData);

	m_PropertyDataList.DeleteItem(ListIndex);
	AddPropertyDataList(ListIndex - 1, m_pCurrentData);	
	m_PropertyDataList.SetItemState(ListIndex - 1, LVIS_SELECTED, LVIS_SELECTED);

	m_IsInitializing = false;
}


void CSrScriptPropertyDlg::OnBnClickedPropertyMovedown()
{
	if (m_pCurrentProperty == NULL) return;
	if (m_pCurrentProperty->pVmadProperty == NULL) return;
	if (!m_IsPropertyArray) return;
	if (m_pCurrentData == NULL) return;

	m_IsInitializing = true;
	GetPropertyControlData();

	int ListIndex = FindPropertyData(m_pCurrentData);
	if (ListIndex < 0) return;
	if (ListIndex+1 >= m_PropertyDataList.GetItemCount()) return;

	m_pCurrentProperty->pVmadProperty->Data.MoveDown(m_pCurrentData);

	m_PropertyDataList.DeleteItem(ListIndex);
	AddPropertyDataList(ListIndex + 1, m_pCurrentData);	
	m_PropertyDataList.SetItemState(ListIndex + 1, LVIS_SELECTED, LVIS_SELECTED);

	m_IsInitializing = false;
}


void CSrScriptPropertyDlg::OnBnClickedNewProperty()
{
	CSrNewScriptPropertyDlg   Dlg;
	srnewscriptpropertyinfo_t NewProperty;
	srpropertyinfo_t*         pNewInfo;
	bool					  Result;

	if (!Dlg.DoModal(NewProperty)) return;

	if (NewProperty.Name.IsEmpty())
	{
		AddSrGeneralError("Property with an empty name is not allowed!");
		SrEditShowError("Script Property Error", "Failed to add property to script '%s'!", m_pScriptFile->GetScriptName());
		return;
	}

	pNewInfo = FindPropertyInfo(NewProperty.Name);

	if (pNewInfo != NULL)
	{
		AddSrGeneralError("Property '%s' already exists!", NewProperty.Name.c_str());
		SrEditShowError("Script Property Error", "Failed to add property to script '%s'!", m_pScriptFile->GetScriptName());
		return;
	}

	GetSrEditApp().UpdateScript(m_pScriptFile->GetScriptName());

	srscriptproperty_t* pNewProperty = m_pScriptFile->AddProperty(NewProperty);

	if (pNewProperty == NULL)
	{
		SrEditShowError("Script Property Error", "Failed to add property to script '%s'!", m_pScriptFile->GetScriptName());
		return;
	}

	Result = m_pScriptFile->Save();

	if (!Result)
	{
		SrEditShowError("Script Property Error", "Failed to save modified script '%s'!", m_pScriptFile->GetScriptName());
		return;
	}

	GetSrEditApp().UpdateScriptView(m_pScriptFile->GetScriptName());

	pNewInfo = m_PropertyInfos.AddNew();
	pNewInfo->IsUsed = false;
	pNewInfo->pScriptProperty = pNewProperty;
	pNewInfo->pVmadProperty = NULL;
	pNewInfo->pRefType = GetSrScriptRefTypeInfo(pNewProperty->RefType);

	m_IsInitializing = true;

	int ListIndex = AddPropertyToList(pNewInfo);
	m_PropertyList.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	SetCurrentProperty(pNewInfo);

	m_IsInitializing = false;
}
