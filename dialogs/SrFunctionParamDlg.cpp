/*=========================================================================
 *
 * File:		SrFunctionParamDlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "sredit.h"
#include "SrFunctionParamDlg.h"
#include "afxdialogex.h"
#include "modfile/srfunctions.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNAMIC(CSrFunctionParamDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/
 
 
/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrFunctionParamDlg, CDialogEx)
	ON_COMMAND(ID_HELP, &CSrFunctionParamDlg::OnHelp)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_PARAM_LIST, &CSrFunctionParamDlg::OnLvnItemchangingParamList)
	ON_NOTIFY(NM_DBLCLK, IDC_PARAM_LIST, OnDblclk)
	ON_EN_CHANGE(IDC_FILTER_TEXT, &CSrFunctionParamDlg::OnEnChangeFilterText)
	ON_BN_CLICKED(ID_CLEAR_FILTER, &CSrFunctionParamDlg::OnBnClickedClearFilter)
	ON_WM_HELPINFO()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_PARAM_LIST, &CSrFunctionParamDlg::OnLvnColumnclickParamList)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_CURRENT_TEXT, &CSrFunctionParamDlg::OnEnChangeCurrentText)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


int CALLBACK l_fnSortFunctionParamList(LPARAM Index1, LPARAM Index2, LPARAM lSortData)
{
	srfuncparasortdata_t* pSortData = (srfuncparasortdata_t *) lSortData;
	if (pSortData == NULL) return 0;

	//int Result = pSortData->List.GetItemText(Index1, pSortData->SubItem).CompareNoCase(pSortData->List.GetItemText(Index2, pSortData->SubItem));
	CSrRecord* pRecord1 = (CSrRecord *) pSortData->List.GetItemData(Index1);
	CSrRecord* pRecord2 = (CSrRecord *) pSortData->List.GetItemData(Index2);
	if (pRecord1 == NULL || pRecord2 == NULL) return 0;
	int Result = 0;

	if (pSortData->SubItem == 0)
	{
		Result = pRecord1->CompareFields(SR_FIELD_EDITORID, pRecord2);
	}
	else if (pSortData->SubItem == 0)
	{
		Result = pRecord1->CompareFields(SR_FIELD_RECORDTYPE, pRecord2);
	}
	
	if (pSortData->SortReverse) return -Result;
	return Result;
}


CSrFunctionParamDlg::CSrFunctionParamDlg(CWnd* pParent)
	: CDialogEx(CSrFunctionParamDlg::IDD, pParent)
{
	m_pRecordHandler   = NULL;
	m_pStringValues    = NULL;
	m_pRecordType      = NULL;
	m_pRecordTypeArray = NULL;

	m_IsRecordType = false;
	m_IsUpdating = false;
	m_ParamType = -1;
	m_LastSortSubItem = -1;
	m_LastSortOrder   = 0;
	m_CurrentValueCheck = SR_CHECKRESULT_NOCHANGE;
}

CSrFunctionParamDlg::~CSrFunctionParamDlg()
{
}


void CSrFunctionParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PREVIOUS_TEXT, m_PreviousValue);
	DDX_Control(pDX, IDC_CURRENT_TEXT, m_CurrentValue);
	DDX_Control(pDX, IDC_PARAM_LIST, m_ParamList);
	DDX_Control(pDX, IDC_FILTER_TEXT, m_Filter);
	DDX_Control(pDX, IDC_FILTER_LABEL, m_FilterLabel);
	DDX_Control(pDX, ID_CLEAR_FILTER, m_FilterReset);
}


void CSrFunctionParamDlg::FillParamList (void)
{
	CString Buffer;
	int SelIndex = -1;

	m_IsUpdating = true;
	m_ParamList.SetRedraw(FALSE);
	m_ParamList.DeleteAllItems();

	if (m_pRecordType != NULL)
		FillParamRecordList();
	else if (m_pRecordTypeArray != NULL)
		FillParamRecordArrayList();
	else if (m_pStringValues != NULL)
		FillParamStringValueList();

	srfuncparasortdata_t SortData = { m_ParamList, 0, false, m_IsRecordType };
	m_ParamList.SortItemsEx(l_fnSortFunctionParamList, (dword) &SortData);
	m_LastSortSubItem = 0;
	
	m_ParamList.SetRedraw(TRUE);

	LVFINDINFO FindInfo;
	FindInfo.flags = LVFI_STRING;
	FindInfo.psz = m_OrigParamValue;
	
	SelIndex = m_ParamList.FindItem(&FindInfo);
	if (SelIndex < 0) SelIndex = 0;

	m_ParamList.SetItemState(SelIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_ParamList.EnsureVisible(SelIndex, FALSE);
	m_IsUpdating = false;
}


void CSrFunctionParamDlg::FillParamRecordList (void)
{
	if (m_pRecordType == NULL) return;
	FillParamList(*m_pRecordType);
}


void CSrFunctionParamDlg::FillParamList (const srrectype_t RecordType)
{
	CSrTypeGroup* pGroup;
	CString       Buffer;
	int           ListIndex;

	if (m_pRecordHandler->GetParent() != NULL) 
		pGroup = m_pRecordHandler->GetParent()->GetTopGroup()->GetTypeGroup(RecordType);
	else
		pGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(RecordType);
	
	if (pGroup == NULL) return;

	for (dword i = 0; i < pGroup->GetNumRecords(); ++i)
	{
		CSrBaseRecord* pBaseRecord = pGroup->GetRecord(i);
		CSrRecord* pRecord = SrCastClassNull(CSrRecord, pBaseRecord);
		if (pRecord == NULL) continue;
		CSrIdRecord* pIdRecord = SrCastClassNull(CSrIdRecord, pBaseRecord);

		if (pIdRecord != NULL)
			Buffer = pIdRecord->GetEditorID();
		else
			Buffer.Format("0x%08X", pRecord->GetFormID());

		ListIndex = m_ParamList.InsertItem(m_ParamList.GetItemCount(), Buffer, SR_FUNCPARAMDLG_SUBITEM_NAME);
		if (ListIndex < 0) continue;
		
		m_ParamList.SetItemData(ListIndex, (DWORD) pRecord);
		Buffer.Format("%4.4s", RecordType.Name);
		m_ParamList.SetItemText(ListIndex, SR_FUNCPARAMDLG_SUBITEM_TYPE, Buffer);
	}

}


void CSrFunctionParamDlg::FillParamRecordArrayList (void)
{
	if (m_pRecordTypeArray == NULL) return;

	for (dword i = 0; i < m_pRecordTypeArray->GetSize(); ++i)
	{
		FillParamList((*m_pRecordTypeArray)[i]);
	}
}


void CSrFunctionParamDlg::FillParamStringValueList (void)
{
	int ListIndex;
	if (m_pStringValues == NULL) return;

	for (dword i = 0; m_pStringValues[i].pString != NULL; ++i)
	{
		ListIndex = m_ParamList.InsertItem(i, m_pStringValues[i].pString, SR_FUNCPARAMDLG_SUBITEM_NAME);
		if (ListIndex >= 0) m_ParamList.SetItemData(ListIndex, m_pStringValues[i].Value);
	}

}


bool CSrFunctionParamDlg::SetupListType (void)
{
	m_pRecordType      = NULL;
	m_pRecordTypeArray = NULL;
	m_pStringValues    = NULL;
	m_IsRecordType     = false;

	switch (m_ParamType)
	{
		case SR_FUNCPARAM_UNKNOWN		 : return false;
		case SR_FUNCPARAM_STRING		 : return false;
		case SR_FUNCPARAM_STAGE			 : return false;
		case SR_FUNCPARAM_INTEGER		 : return false;
		case SR_FUNCPARAM_FLOAT			 : return false;
		case SR_FUNCPARAM_OBJECTID3		 : return false;
		case SR_FUNCPARAM_REFERENCE		 : 
			m_pRecordTypeArray = &GetSrReferenceRecordTypes();
			return true;
		case SR_FUNCPARAM_ACTORVALUE	 : 
			m_pStringValues = s_SrActorValues;
			return true;
		case SR_FUNCPARAM_ACTOR			 : m_pRecordType = &SR_NAME_NPC_; return true;
		case SR_FUNCPARAM_SPELLITEM		 : m_pRecordType = &SR_NAME_SPEL; return true;
		case SR_FUNCPARAM_AXIS			 : 
			m_pStringValues = s_SrAxisTypes;
			return true;
		case SR_FUNCPARAM_CELL			 : m_pRecordType = &SR_NAME_CELL; return true;
		case SR_FUNCPARAM_ANIMGROUP		 : return false;
		case SR_FUNCPARAM_MAGICITEM		 : 
			m_pRecordTypeArray = &GetSrReferenceRecordTypes();
			return true;
		case SR_FUNCPARAM_SOUND			 : m_pRecordType = &SR_NAME_SOUN; return true;
		case SR_FUNCPARAM_TOPIC			 : m_pRecordType = &SR_NAME_INFO; return true;
		case SR_FUNCPARAM_QUEST			 : m_pRecordType = &SR_NAME_QUST; return true;
		case SR_FUNCPARAM_RACE			 : m_pRecordType = &SR_NAME_RACE; return true;
		case SR_FUNCPARAM_CLASS			 : m_pRecordType = &SR_NAME_CLAS; return true;
		case SR_FUNCPARAM_FACTION		 : m_pRecordType = &SR_NAME_FACT; return true;
		case SR_FUNCPARAM_GENDER		 : 
			m_pStringValues = s_SrGenderTypes;
			return true;
		case SR_FUNCPARAM_GLOBAL		 : m_pRecordType = &SR_NAME_GLOB; return true;
		case SR_FUNCPARAM_FURNITURE		 : m_pRecordType = &SR_NAME_FURN; return true;
		case SR_FUNCPARAM_WEAPON		 : m_pRecordType = &SR_NAME_WEAP; return true;
		case SR_FUNCPARAM_VARNAME		 : return false;
		case SR_FUNCPARAM_MAPMARKER		 : return false;
		case SR_FUNCPARAM_ACTORBASE		 : m_pRecordType = &SR_NAME_NPC_; return true;
		case SR_FUNCPARAM_CONTAINER		 : m_pRecordType = &SR_NAME_CONT; return true;
		case SR_FUNCPARAM_WORLDSPACE	 : m_pRecordType = &SR_NAME_WRLD; return true;
		case SR_FUNCPARAM_CRIME			 : 
			m_pStringValues = s_SrCrimeTypes;
			return true;
		case SR_FUNCPARAM_PACKAGE		 : m_pRecordType = &SR_NAME_PACK; return true;
		case SR_FUNCPARAM_COMBATSTYLE	 : m_pRecordType = &SR_NAME_CSTY; return true;
		case SR_FUNCPARAM_MAGICEFFECT	 : m_pRecordType = &SR_NAME_MGEF; return true;
		case SR_FUNCPARAM_FORMTYPE		 : 
			m_pRecordType = &SR_NAME_all;
			return true;
		case SR_FUNCPARAM_WEATHER		 : m_pRecordType = &SR_NAME_WTHR; return true;
		case SR_FUNCPARAM_34			 : return false;
		case SR_FUNCPARAM_OWNER			 : return false;
		case SR_FUNCPARAM_EFFECTSHADER	 : m_pRecordType = &SR_NAME_EFSH; return true;
		case SR_FUNCPARAM_FORMLIST		 : m_pRecordType = &SR_NAME_FLST; return true;
		case SR_FUNCPARAM_38			 : return false;
		case SR_FUNCPARAM_PERK			 : m_pRecordType = &SR_NAME_PERK; return true;
		case SR_FUNCPARAM_NOTE			 : return false;
		case SR_FUNCPARAM_MISCSTAT		 : return false;
		case SR_FUNCPARAM_IMAGESPACEID	 : return false;
		case SR_FUNCPARAM_IMAGESPACE	 : m_pRecordType = &SR_NAME_IMGS; return true;
		case SR_FUNCPARAM_44			 : return false;
		case SR_FUNCPARAM_45			 : return false;
		case SR_FUNCPARAM_EVENTFUNC		 : return false;
		case SR_FUNCPARAM_EVENTMEMBER	 : return false;
		case SR_FUNCPARAM_DATA			 : return false;
		case SR_FUNCPARAM_VOICETYPE		 : m_pRecordType = &SR_NAME_VTYP; return true;
		case SR_FUNCPARAM_ENCOUNTERZONE	 : m_pRecordType = &SR_NAME_ECZN; return true;
		case SR_FUNCPARAM_IDLE			 : m_pRecordType = &SR_NAME_IDLE; return true;
		case SR_FUNCPARAM_MESSAGE		 : m_pRecordType = &SR_NAME_MESG; return true;
		case SR_FUNCPARAM_EQUIPABLEITEM  : 
			m_pRecordTypeArray = &GetSrEquipableRecordTypes();
			return true;
		case SR_FUNCPARAM_ALIGNMENT		 : return false;
		case SR_FUNCPARAM_EQUIPTYPE		 : m_pRecordType = &SR_NAME_EQUP; return true;
		case SR_FUNCPARAM_OBJECTID56	 : return false;
		case SR_FUNCPARAM_MUSIC			 : m_pRecordType = &SR_NAME_MUSC; return true;
		case SR_FUNCPARAM_CRITICALSTAGE	 :
			m_pStringValues = s_SrCriticalStageTypes;
			return true;
		case SR_FUNCPARAM_KEYWORD		 : m_pRecordType = &SR_NAME_KYWD; return true;
		case SR_FUNCPARAM_LOCREFTYPE	 : m_pRecordType = &SR_NAME_LCRT; return true;
		case SR_FUNCPARAM_LOCATION		 : m_pRecordType = &SR_NAME_LCTN; return true;
		case SR_FUNCPARAM_FORM			 : return false;
		case SR_FUNCPARAM_QUESTALIAS	 : return false;
		case SR_FUNCPARAM_SHOUT			 : m_pRecordType = &SR_NAME_SHOU; return true;
		case SR_FUNCPARAM_WORDOFPOWER	 : m_pRecordType = &SR_NAME_WOOP; return true;
		case SR_FUNCPARAM_66			 : return false;
		case SR_FUNCPARAM_SCENE			 : m_pRecordType = &SR_NAME_SCEN; return true;
		case SR_FUNCPARAM_CASTSOURCE	 :
			m_pStringValues = s_SrCastSourceTypes;
			return true;
		case SR_FUNCPARAM_ASSOCTYPE		 : m_pRecordType = &SR_NAME_ASTP; return true;
		case SR_FUNCPARAM_WARDSTATE		 : 
			m_pStringValues = s_SrWardStateTypes;
			return true;
		case SR_FUNCPARAM_PACKDATANULL	 : return false;
		case SR_FUNCPARAM_PACKDATANUM	 : return false;
		case SR_FUNCPARAM_FURNANIM		 : 
			m_pStringValues = s_SrFurnitureAnimTypes;
			return true;
		case SR_FUNCPARAM_FURNENTRY		 : 
			m_pStringValues = s_SrFurnitureEntryTypes;
			return true;
		case SR_FUNCPARAM_75			 : return false;
		case SR_FUNCPARAM_VMVARNAME		 : return false;
		case SR_FUNCPARAM_REFEFEFCT		 : return false;
		case SR_FUNCPARAM_PACKDATALOC	 : return false;
		case SR_FUNCPARAM_SOUNDCATE		 : m_pRecordType = &SR_NAME_SNCT; return true;
		case SR_FUNCPARAM_SKILLACTION	 : 
			m_pStringValues = s_SrSkillActionTypes;
			return true;
		case SR_FUNCPARAM_KNOWFORM		 : 
			m_pRecordTypeArray = &GetSrKnowableRecordTypes();
			return true;
		case SR_FUNCPARAM_REGION		 : m_pRecordType = &SR_NAME_REGN; return true;
		case SR_FUNCPARAM_ACTION		 : m_pRecordType = &SR_NAME_AACT; return true;
		default:						
			return false;
	};

	return false;
}


void CSrFunctionParamDlg::SetupParamList (void)
{
	m_ParamList.InsertColumn(SR_FUNCPARAMDLG_SUBITEM_NAME, "Item", LVCFMT_CENTER, 180, SR_FUNCPARAMDLG_SUBITEM_NAME);

	if (m_IsRecordType) 
	{
		m_ParamList.InsertColumn(SR_FUNCPARAMDLG_SUBITEM_TYPE, "Type", LVCFMT_CENTER, 100,	SR_FUNCPARAMDLG_SUBITEM_TYPE);
	}
	else
	{
		m_Filter.ShowWindow(SW_HIDE);
		m_FilterLabel.ShowWindow(SW_HIDE);
		m_FilterReset.ShowWindow(SW_HIDE);
	}
}


BOOL CSrFunctionParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	SetupParamList();
	FillParamList();

	m_PreviousValue.SetWindowText(m_OrigParamValue);
	m_CurrentValue.SetWindowText(m_OrigParamValue);

	m_ParamList.SetFocus();
	return FALSE;
}


void CSrFunctionParamDlg::OnOK()
{
	CWnd* pWnd = GetFocus();

	if (pWnd == &m_Filter)
	{
		CString Buffer;
		m_Filter.GetWindowText(Buffer);
		Buffer.Trim(" \n\t\r");
	}
	else if (pWnd == &m_CurrentValue)
	{
		m_CurrentValue.GetWindowText(m_CurrentParamValue);
		m_CurrentParamValue.Trim(" \n\t\r");
	}

	CDialogEx::OnOK();
}


bool CSrFunctionParamDlg::DoModal (CString& ParamValue, const int ParamType, CSrRecordHandler& RecordHandler)
{
	m_OrigParamValue    = ParamValue;
	m_CurrentParamValue = ParamValue;
	m_pRecordHandler    = &RecordHandler;
	m_ParamType         = ParamType;

	bool Result = SetupListType();
	if (m_pRecordType == NULL && m_pRecordTypeArray == NULL && m_pStringValues == NULL) Result = false;

	if (!Result)
	{
		CString Buffer;
		Buffer.Format("I don't know how to select a function parameter '%s' (%d)!", GetSrFunctionParamTypeString(ParamType), ParamType); 
		AfxMessageBox(Buffer, MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (m_pRecordType != NULL || m_pRecordTypeArray != NULL) m_IsRecordType = true;

	int iResult = CDialogEx::DoModal();
	if (iResult != IDOK) return false;

	ParamValue = m_CurrentParamValue;
	return true;
}


void CSrFunctionParamDlg::OnLvnItemchangingParamList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (m_IsUpdating) return;

	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	m_CurrentParamValue = m_ParamList.GetItemText(pNMLV->iItem, 0);
	m_CurrentValue.SetWindowText(m_CurrentParamValue);
}


void CSrFunctionParamDlg::OnDblclk (NMHDR* pNMHDR, LRESULT* pResult) 
{
  *pResult = 0;

  OnOK();
  EndModalLoop(IDOK);
}


void CSrFunctionParamDlg::OnEnChangeFilterText()
{
	m_Filter.GetWindowText(m_FilterString);
	//FillFunctionList();
}


void CSrFunctionParamDlg::OnBnClickedClearFilter()
{
	m_Filter.SetWindowText("");
	m_FilterString.Empty();
	//FillFunctionList();	
}


void CSrFunctionParamDlg::OnHelp (void) 
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Function_Parameters", "Function_Parameters");
}


BOOL CSrFunctionParamDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	OnHelp();
	return true;
}


void CSrFunctionParamDlg::OnLvnColumnclickParamList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (m_LastSortSubItem == pNMLV->iSubItem)
	{
		m_LastSortOrder = !m_LastSortOrder;
	}
	else
	{
		m_LastSortSubItem = pNMLV->iSubItem;
		m_LastSortOrder   = 0;
	}

	srfuncparasortdata_t SortData = { m_ParamList, pNMLV->iSubItem, m_LastSortOrder, m_IsRecordType };
	m_ParamList.SortItemsEx(l_fnSortFunctionParamList, (dword) &SortData);
}


HBRUSH CSrFunctionParamDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	const static COLORREF s_UnchangedColor = RGB(255,255,255);
	const static COLORREF s_OkColor        = RGB(204,255,204);
	const static COLORREF s_ErrorColor     = RGB(255,204,204);

	HBRUSH hBrush = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_CurrentValue)
	{
		switch (m_CurrentValueCheck) 
		{
		case SR_CHECKRESULT_NOCHANGE:
			hBrush = CreateSolidBrush(s_UnchangedColor);
			pDC->SetBkColor(s_UnchangedColor);
			break;
		case SR_CHECKRESULT_OK:
			hBrush = CreateSolidBrush(s_OkColor);
			pDC->SetBkColor(s_OkColor);
			break;
		case SR_CHECKRESULT_ERROR:
			hBrush = CreateSolidBrush(s_ErrorColor);
			pDC->SetBkColor(s_ErrorColor);
			break;
		}
	}

	return hBrush;
}


void CSrFunctionParamDlg::OnEnChangeCurrentText()
{
	CString Buffer;
	CString Buffer1;

	m_CurrentValue.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	LVFINDINFO FindInfo;
	FindInfo.flags = LVFI_PARTIAL;
	FindInfo.psz = Buffer;

	int ListIndex = m_ParamList.FindItem(&FindInfo);

	if (ListIndex <= -1)
		m_CurrentValueCheck = SR_CHECKRESULT_ERROR;
	else if (Buffer.CompareNoCase(m_OrigParamValue) == 0)
		m_CurrentValueCheck = SR_CHECKRESULT_NOCHANGE;
	else
	{
		m_IsUpdating = true;
		Buffer1 = m_ParamList.GetItemText(ListIndex, 0);

		if (Buffer.CompareNoCase(Buffer1) == 0)
		{
			m_CurrentParamValue = Buffer;
			m_CurrentValueCheck = SR_CHECKRESULT_OK;
		}
		else
			m_CurrentValueCheck = SR_CHECKRESULT_ERROR;

		m_ParamList.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
		m_ParamList.EnsureVisible(ListIndex, FALSE);
		m_IsUpdating = false;		
	}

		/* Force the color to be updated */
	m_CurrentValue.RedrawWindow();	
}
