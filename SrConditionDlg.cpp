/*===========================================================================
 *
 * File:		SrConditiondlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	3 Decemberr 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "sredit.h"
#include "SrConditionDlg.h"
#include "afxdialogex.h"
#include "SrFunctionDlg.h"
#include "dialogs/SrFunctionParamDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNAMIC(CSrConditionDlg, CDialogEx)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/
 
 
/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrConditionDlg, CDialogEx)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CONDITION_LIST, &CSrConditionDlg::OnLvnItemchangedConditionList)
	ON_NOTIFY(NM_DBLCLK, IDC_PARAM1_TEXT, &CSrConditionDlg::OnDblClkParam1)
	ON_BN_CLICKED(IDC_SELECTREFERENCE_BUTTON, &CSrConditionDlg::OnBnClickedSelectreferenceButton)
	ON_BN_CLICKED(IDC_SELECTFUNCTION_BUTTON, &CSrConditionDlg::OnBnClickedSelectfunctionButton)
	ON_BN_CLICKED(IDC_SELECTPARAM1_BUTTON, &CSrConditionDlg::OnBnClickedSelectparam1Button)
	ON_BN_CLICKED(IDC_SELECTPARAM2_BUTTON, &CSrConditionDlg::OnBnClickedSelectparam2Button)
	ON_BN_CLICKED(IDC_SELECTPARAM3_BUTTON, &CSrConditionDlg::OnBnClickedSelectparam3Button)
	ON_COMMAND(ID_COND_INSERTBEFORE, &CSrConditionDlg::OnCondInsertBefore)
	ON_COMMAND(ID_COND_INSERTAFTER, &CSrConditionDlg::OnCondInsertAfter)
	ON_COMMAND(ID_COND_MOVEUP, &CSrConditionDlg::OnCondMoveUp)
	ON_COMMAND(ID_COND_MOVEDOWN, &CSrConditionDlg::OnCondMoveDown)
	ON_COMMAND(ID_COND_DELETE, &CSrConditionDlg::OnCondDelete)
	ON_COMMAND(ID_COND_COPYCONDITION, &CSrConditionDlg::OnCondCopyCondition)
	ON_UPDATE_COMMAND_UI(ID_COND_MOVEUP, &CSrConditionDlg::OnUpdateCondMenu)
	ON_UPDATE_COMMAND_UI(ID_COND_MOVEDOWN, &CSrConditionDlg::OnUpdateCondMenu)
	ON_UPDATE_COMMAND_UI(ID_COND_DELETE, &CSrConditionDlg::OnUpdateCondMenu)
	ON_UPDATE_COMMAND_UI(ID_COND_COPYCONDITION, &CSrConditionDlg::OnUpdateCondMenu)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(ID_MOVEUP_BUTTON, &CSrConditionDlg::OnBnClickedMoveupButton)
	ON_BN_CLICKED(ID_MOVEDOWN_BUTTON, &CSrConditionDlg::OnBnClickedMovedownButton)
	ON_BN_CLICKED(ID_ADD_BUTTON, &CSrConditionDlg::OnBnClickedAddButton)
	ON_BN_CLICKED(ID_DELETE_BUTTON, &CSrConditionDlg::OnBnClickedDeleteButton)
	ON_WM_HELPINFO()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_FUNCTION_TEXT, &CSrConditionDlg::OnEnChangeFunctionText)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_CONDITION_LIST, &CSrConditionDlg::OnLvnItemchangingConditionList)
	ON_CBN_SELCHANGE(IDC_RUNON_LIST, &CSrConditionDlg::OnCbnSelchangeRunonList)
	ON_BN_CLICKED(IDC_SELECTVALUE_BUTTON, &CSrConditionDlg::OnBnClickedSelectvalueButton)
	ON_BN_CLICKED(IDC_USEGLOBAL_CHECK, &CSrConditionDlg::OnBnClickedUseglobalCheck)
	ON_EN_CHANGE(IDC_VALUE_TEXT, &CSrConditionDlg::OnEnChangeValueText)
	ON_EN_CHANGE(IDC_REFERENCE_TEXT, &CSrConditionDlg::OnEnChangeReferenceText)
	ON_WM_LBUTTONDBLCLK()
	ON_EN_CHANGE(IDC_PARAM1_TEXT, &CSrConditionDlg::OnEnChangeParam1Text)
	ON_EN_CHANGE(IDC_PARAM2_TEXT, &CSrConditionDlg::OnEnChangeParam2Text)
	ON_EN_CHANGE(IDC_PARAM3_TEXT, &CSrConditionDlg::OnEnChangeParam3Text)
	ON_COMMAND(ID_CONDITION_PASTECONDITION, &CSrConditionDlg::OnConditionPastecondition)
	ON_UPDATE_COMMAND_UI(ID_CONDITION_PASTECONDITION, &CSrConditionDlg::OnUpdateConditionPastecondition)
	ON_COMMAND(ID_CONDITION_DUPLICATE, &CSrConditionDlg::OnConditionDuplicate)
	ON_UPDATE_COMMAND_UI(ID_CONDITION_DUPLICATE, &CSrConditionDlg::OnUpdateConditionDuplicate)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_ConditionListInit[] = 
{
	{ SR_FIELD_RUNON,		 65,		LVCFMT_CENTER },
	{ SR_FIELD_REFERENCE,	 70,		LVCFMT_CENTER },
	{ SR_FIELD_FUNCTION,	 150,		LVCFMT_CENTER },
	{ SR_FIELD_PARAM1,		 90,		LVCFMT_CENTER },
	{ SR_FIELD_PARAM2,		 90,		LVCFMT_CENTER },
	{ SR_FIELD_PARAM3,		 90,		LVCFMT_CENTER },
	{ SR_FIELD_OPERATOR,	 30,		LVCFMT_CENTER },
	{ SR_FIELD_VALUE,		 90,		LVCFMT_CENTER },
	{ SR_FIELD_CONDFLAGSEX,	 70,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_ConditionFields[] = 
{
	{ "Run On",		SR_FIELD_RUNON,			0, NULL },
	{ "Reference",	SR_FIELD_REFERENCE,		0, NULL },
	{ "Function",	SR_FIELD_FUNCTION,		0, NULL },
	{ "Param1",		SR_FIELD_PARAM1,		0, NULL },
	{ "Param2",		SR_FIELD_PARAM2,		0, NULL },
	{ "Param3",		SR_FIELD_PARAM3,		0, NULL },
	{ "Op",			SR_FIELD_OPERATOR,		0, NULL },
	{ "Value",		SR_FIELD_VALUE,			0, NULL },
	{ "Flags",		SR_FIELD_CONDFLAGSEX,	0, NULL },
	{ NULL,			SR_FIELD_NONE,			0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Constructor
 *
 *=========================================================================*/
CSrConditionDlg::CSrConditionDlg(CWnd* pParent)
	: CDialogEx(CSrConditionDlg::IDD, pParent)
{
	m_pRecord = NULL;
	m_pCurrentFunction = NULL;
	m_pCurrentCondition = NULL;
	m_IsInitialized = false;
}
/*===========================================================================
 *		End of Class CSrConditionDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Destructor
 *
 *=========================================================================*/
CSrConditionDlg::~CSrConditionDlg()
{
}
/*===========================================================================
 *		End of Class CSrConditionDlg Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrConditionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CONDITION_LIST, m_ConditionList);
	DDX_Control(pDX, IDC_REFERENCE_TEXT, m_Reference);
	DDX_Control(pDX, IDC_REFERENCE_LABEL, m_ReferenceLabel);
	DDX_Control(pDX, IDC_FUNCTION_TEXT, m_Function);
	DDX_Control(pDX, IDC_FUNCTION_LABEL, m_FunctionLabel);
	DDX_Control(pDX, IDC_PARAM1_TEXT, m_Param1);
	DDX_Control(pDX, IDC_PARAM2_TEXT, m_Param2);
	DDX_Control(pDX, IDC_PARAM3_TEXT, m_Param3);
	DDX_Control(pDX, IDC_PARAM1_LABEL, m_Param1Label);
	DDX_Control(pDX, IDC_PARAM2_LABEL, m_Param2Label);
	DDX_Control(pDX, IDC_PARAM3_LABEL, m_Param3Label);	
	DDX_Control(pDX, IDC_VALUE_TEXT, m_Value);
	DDX_Control(pDX, IDC_VALUE_LABEL, m_ValueLabel);
	DDX_Control(pDX, IDC_OPERATOR_LIST, m_Operator);
	DDX_Control(pDX, IDC_OR_CHECK, m_FlagOr);
	DDX_Control(pDX, IDC_USEGLOBAL_CHECK, m_FlagUseGlobal);
	DDX_Control(pDX, IDC_SELECTFUNCTION_BUTTON, m_FunctionButton);
	DDX_Control(pDX, IDC_SELECTREFERENCE_BUTTON, m_ReferenceButton);
	DDX_Control(pDX, IDC_SELECTPARAM1_BUTTON, m_Param1Button);
	DDX_Control(pDX, IDC_SELECTPARAM2_BUTTON, m_Param2Button);
	DDX_Control(pDX, IDC_SELECTPARAM3_BUTTON, m_Param3Button);
	DDX_Control(pDX, IDC_USEPACKDATA_CHECK, m_FlagPackData);
	DDX_Control(pDX, IDC_QUESTALIASES_CHECK, m_FlagQuestAlias);
	DDX_Control(pDX, IDC_SWAPSUBJECT_CHECK, m_FlagSwapSubject);
	DDX_Control(pDX, IDC_RUNON_LIST, m_RunOnList);
	DDX_Control(pDX, IDC_SELECTVALUE_BUTTON, m_ValueButton);
	DDX_Control(pDX, ID_MOVEUP_BUTTON, m_MoveUpButton);
	DDX_Control(pDX, ID_MOVEDOWN_BUTTON, m_MoveDownButton);
}
/*===========================================================================
 *		End of Class CSrConditionDlg::DoDataExchange()
 *=========================================================================*/


void CSrConditionDlg::FillRunOnList (void)
{
	m_RunOnList.ResetContent();

	SrFillComboList(m_RunOnList, s_SrConditionRunonTypes, 0);
}


/*===========================================================================
 *
 * Class CSrConditionDlg Method - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrConditionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_FunctionIDCheck = SR_CHECKRESULT_NOCHANGE;

	SrFillComboList(m_Operator, s_SrConditionOperators, 0);
	FillRunOnList();
	
		/* Setup the list */	
	m_ConditionList.SetDragEnable(true);
	m_ConditionList.DefaultSettings();
	m_ConditionList.SetListName("ConditionList");
	m_ConditionList.SetupCustomList(s_ConditionListInit, NULL, s_ConditionFields);

	m_ConditionList.SetOwner(this);
	m_ConditionList.SetColorEnable(false);
	m_ConditionList.SetDragType(SR_RLDRAG_CUSTOM);
	m_ConditionList.SetSortEnable(false);

	SetCurrentCondition(NULL);
	SetControlData();

	m_IsInitialized = true;
	return TRUE;
}
/*===========================================================================
 *		End of Class CSrConditionDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrConditionDlg::SetControlData (void) 
{
	SetConditionList();
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - void SetConditionList (void);
 *
 *=========================================================================*/
void CSrConditionDlg::SetConditionList (void) 
{
	srconditioninfo_t* pCondition;

	m_ConditionList.DeleteAllItems();

		/* Add all effects in enchantment */
	for (dword i = 0; i < m_Conditions.GetSize(); ++i) 
	{
		pCondition = m_Conditions[i];
		AddConditionList(pCondition);
	}

	m_ConditionList.SelectRecord(0);
	SetCurrentCondition(m_Conditions[0]);
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::SetConditionList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - int AddConditionList (pCondition);
 *
 *=========================================================================*/
int CSrConditionDlg::AddConditionList (srconditioninfo_t* pCondition) 
{
	srrlcustomdata_t	CustomData;
	CString           Buffer;
	int		        ListIndex;

	CustomData.pRecord = m_pRecord;

		/* Setup the custom data structure for the list */
	CustomData.Subrecords.Add(&pCondition->Condition);
	CustomData.Subrecords.Add(pCondition->pParam1);
	CustomData.Subrecords.Add(pCondition->pParam2);
  
		/* Add the custom record to the list */
	ListIndex = m_ConditionList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdateConditionList(ListIndex, false);
	return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::AddConditionList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - void UpdateConditionList (ListIndex, Update);
 *
 *=========================================================================*/
void CSrConditionDlg::UpdateConditionList (const int ListIndex, const bool Update) 
{
	srrlcustomdata_t*	pCustomData;
	srfunction_t*		pFunction;
	CString				Buffer;
	CSString			ParamString;
	CSrSubrecord*		pSubrecord;
	CSrCtdaSubrecord*   pCondition;
	CSrStringSubrecord* pString1 = NULL;
	CSrStringSubrecord* pString2 = NULL;
	const char*			pEditorID;
	bool				Result;
	
	pCustomData = m_ConditionList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;
	
	if (Update) m_ConditionList.UpdateRecord(ListIndex);
	
	pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->Subrecords[0]);
	if (pCondition == NULL) return;

	pFunction = GetSrFunction(pCondition->GetCtdtData().Function + SR_CTDA_FUNCOFFSET);
	if (pFunction == NULL) return;
		
	pSubrecord = pCustomData->Subrecords[1];
	if (pSubrecord != NULL && pSubrecord->GetRecordType() == SR_NAME_CIS1) pString1 = SrCastClass(CSrStringSubrecord, pSubrecord);
	if (pSubrecord != NULL && pSubrecord->GetRecordType() == SR_NAME_CIS2) pString2 = SrCastClass(CSrStringSubrecord, pSubrecord);

	pSubrecord = pCustomData->Subrecords[2];
	if (pSubrecord != NULL && pSubrecord->GetRecordType() == SR_NAME_CIS1) pString1 = SrCastClass(CSrStringSubrecord, pSubrecord);
	if (pSubrecord != NULL && pSubrecord->GetRecordType() == SR_NAME_CIS2) pString2 = SrCastClass(CSrStringSubrecord, pSubrecord);
	
	ParamString.Empty();

	if (pFunction->NumParams >= 1) 
	{
		if (IsSrFunctionParamString(pFunction->Params[0].Type) && pString1 != NULL)
			ParamString = pString1->GetString();
		else
		{
			Result = SrFunctionParamToString(ParamString, pFunction->Params[0].Type, pCondition->GetCtdtData().Parameter1, m_pRecord->GetParent());
			if (!Result) ParamString.Format("0x%08X", pCondition->GetCtdtData().Parameter1);
		}
	}

	m_ConditionList.SetCustomField(ListIndex, SR_FIELD_PARAM1, ParamString);
	ParamString.Empty();

	if (pFunction->NumParams >= 2)
	{
		if (IsSrFunctionParamString(pFunction->Params[1].Type) && pString2 != NULL)
			ParamString = pString2->GetString();
		else
		{
			Result = SrFunctionParamToString(ParamString, pFunction->Params[1].Type, pCondition->GetCtdtData().Parameter2, m_pRecord->GetParent());
			if (!Result) ParamString.Format("0x%08X", pCondition->GetCtdtData().Parameter2);
		}
	}

	m_ConditionList.SetCustomField(ListIndex, SR_FIELD_PARAM2, ParamString);
	ParamString.Empty();

	if (pFunction->NumParams >= 3) 
	{
		if (IsSrFunctionParamString(pFunction->Params[2].Type))
			ParamString = "Error: String Param3";
		else
		{
			SrFunctionParamToString(ParamString, pFunction->Params[2].Type, pCondition->GetCtdtData().Parameter3, m_pRecord->GetParent());
			if (!Result) ParamString.Format("0x%08X", pCondition->GetCtdtData().Parameter3);
		}
	}

	m_ConditionList.SetCustomField(ListIndex, SR_FIELD_PARAM3, ParamString);

	if (pCondition->IsUseGlobal())
	{
		pEditorID = m_pRecord->GetParent()->GetEditorID(pCondition->GetCtdtData().GlobalID);

		if (pEditorID != NULL)
			m_ConditionList.SetCustomField(ListIndex, SR_FIELD_VALUE, pEditorID);
		else if (pCondition->GetCtdtData().GlobalID == 0)
			m_ConditionList.SetCustomField(ListIndex, SR_FIELD_VALUE, "");
		else
		{
			Buffer.Format("0x%08X", pCondition->GetCtdtData().GlobalID);
			m_ConditionList.SetCustomField(ListIndex, SR_FIELD_VALUE, Buffer);
		}
	}
	else
	{
		Buffer.Format("%g", pCondition->GetCtdtData().Value);
		m_ConditionList.SetCustomField(ListIndex, SR_FIELD_VALUE, Buffer);
	}	
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::UpdateConditionList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - bool DoModal (pRecord, pConditions);
 *
 *=========================================================================*/
bool CSrConditionDlg::DoModal (CSrRecord* pRecord, CSrConditionArray* pConditions)
{
	if (pRecord == NULL || pConditions == NULL) return false;

	m_pOrigConditions = pConditions;
	m_pRecord = pRecord;
	m_Conditions.Destroy();

	for (dword i = 0; i < m_pOrigConditions->GetSize(); ++i)
	{
		srconditioninfo_t* pCondition = (*m_pOrigConditions)[i];
		srconditioninfo_t* pNewCond = new srconditioninfo_t;

		pNewCond->Copy(*pCondition);
		m_Conditions.Add(pNewCond);
	}

	int Result = CDialogEx::DoModal();
	return (Result == IDOK);
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::DoModal()
 *=========================================================================*/


void CSrConditionDlg::GetConditionParamControlData (CEdit& ParamEdit, const dword ParamIndex, int& ParamValue)
{
	CString Buffer;
	bool	Result;

	if (m_pCurrentFunction == NULL) return;
	if (m_pCurrentFunction->NumParams < ParamIndex + 1) return;

	ParamEdit.GetWindowTextA(Buffer);

	if (IsSrFunctionParamString(m_pCurrentFunction->Params[ParamIndex].Type))
	{
		m_pCurrentCondition->SetParam(ParamIndex, Buffer);
		return;
	}

	m_pCurrentCondition->DeleteParam(ParamIndex);
	
	Result = SrFunctionParamFromString(ParamValue, Buffer, m_pCurrentFunction->Params[ParamIndex].Type, m_pRecord->GetParent());
	if (Result) return;

	ParamValue = strtoul(Buffer, NULL, 0);
}


void CSrConditionDlg::GetConditionControlData (void)
{
	CString    Buffer;
	int        Index;

	if (m_pCurrentCondition == NULL) return;

	Index = m_Operator.GetCurSel();
	if (Index >= 0) m_pCurrentCondition->Condition.GetCtdtData().CompareType = m_Operator.GetItemData(Index);

	Index = m_RunOnList.GetCurSel();
	if (Index >= 0) m_pCurrentCondition->Condition.GetCtdtData().RunOnType = m_RunOnList.GetItemData(Index);	

	m_Value.GetWindowText(Buffer);

	if (m_FlagUseGlobal.GetCheck())
		m_pCurrentCondition->Condition.GetCtdtData().GlobalID = m_pRecord->GetParent()->FindGeneralFormID(Buffer);
	else
		m_pCurrentCondition->Condition.GetCtdtData().Value = (float) strtod(Buffer, NULL);

	m_Reference.GetWindowText(Buffer);
	m_pCurrentCondition->Condition.GetCtdtData().ReferenceID = m_pRecord->GetParent()->FindGeneralFormID(Buffer);

	m_Function.GetWindowText(Buffer);
	Buffer.Trim(" \t\n\r");
	m_pCurrentFunction = GetSrFunction(Buffer);
	
	if (m_pCurrentFunction == NULL)
		AddSrGeneralError("Unknown condition function '%s'!", Buffer);
	else
		m_pCurrentCondition->Condition.GetCtdtData().Function = m_pCurrentFunction->OpCode - SR_CTDA_FUNCOFFSET;

	GetConditionParamControlData(m_Param1, 0, m_pCurrentCondition->Condition.GetCtdtData().Parameter1);
	GetConditionParamControlData(m_Param2, 1, m_pCurrentCondition->Condition.GetCtdtData().Parameter2);
	GetConditionParamControlData(m_Param3, 2, m_pCurrentCondition->Condition.GetCtdtData().Parameter3);

	dword Flags = m_pCurrentCondition->Condition.GetCtdtData().Flags;
	::FlipFlagBits(Flags, SR_CTDA_FLAG_OR, m_FlagOr.GetCheck() != 0);
	::FlipFlagBits(Flags, SR_CTDA_FLAG_USEGLOBAL, m_FlagUseGlobal.GetCheck() != 0);
	::FlipFlagBits(Flags, SR_CTDA_FLAG_USEQUESTALIASES, m_FlagQuestAlias.GetCheck() != 0);
	::FlipFlagBits(Flags, SR_CTDA_FLAG_USEPACKDATA, m_FlagPackData.GetCheck() != 0);
	::FlipFlagBits(Flags, SR_CTDA_FLAG_SWAPSUBJECTTARGET, m_FlagSwapSubject.GetCheck() != 0);

	 m_pCurrentCondition->Condition.GetCtdtData().Flags = Flags;

		/* Find and update the appropriate item in the list */
	 for (int i = 0; i < m_ConditionList.GetItemCount(); ++i)
	 {
		 srrlcustomdata_t* pCustomData = (srrlcustomdata_t *) m_ConditionList.GetItemData(i);
		 if (pCustomData == NULL) continue;

		 CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->Subrecords[0]);
		 if (pCondition == NULL) continue;

		 srconditioninfo_t* pCondInfo = FindConditionInfo(pCondition);
		 if (pCondInfo == NULL) continue;
		 if (pCondInfo != m_pCurrentCondition) continue;

		 pCustomData->Subrecords.Add(pCondInfo->pParam1);
		 pCustomData->Subrecords.Add(pCondInfo->pParam2);

		 UpdateConditionList(i, true);
		 break;
	 }
	 	 
}


srconditioninfo_t* CSrConditionDlg::FindConditionInfo(CSrCtdaSubrecord* pCondition)
{
	for (dword i = 0; i < m_Conditions.GetSize(); ++i)
	{
		if (&m_Conditions.GetAt(i)->Condition == pCondition) return m_Conditions.GetAt(i);
	}

	return NULL;
}


void CSrConditionDlg::EnableConditionControls (void)
{
	bool Enable = (m_pCurrentCondition != NULL);

	m_Operator.EnableWindow(Enable);
	m_RunOnList.EnableWindow(Enable);
	m_Reference.EnableWindow(Enable);
	m_Function.EnableWindow(Enable);
	m_Param1.EnableWindow(Enable);
	m_Param2.EnableWindow(Enable);
	m_Param3.EnableWindow(Enable);
	m_Value.EnableWindow(Enable);
	m_FlagOr.EnableWindow(Enable);
	m_FlagSwapSubject.EnableWindow(Enable);
	m_FlagUseGlobal.EnableWindow(Enable);
	m_FlagQuestAlias.EnableWindow(Enable);
	m_FlagPackData.EnableWindow(Enable);
	m_FunctionButton.EnableWindow(Enable);
	m_ReferenceButton.EnableWindow(Enable);
	m_ValueButton.EnableWindow(Enable);
	m_Param1Button.EnableWindow(Enable);
	m_Param2Button.EnableWindow(Enable);
	m_Param3Button.EnableWindow(Enable);
}


void CSrConditionDlg::SetCurrentCondition (srconditioninfo_t* pCondition)
{
	GetConditionControlData();

	m_pCurrentCondition = pCondition;
	EnableConditionControls();

	SetConditionControlData();
}


void CSrConditionDlg::SetConditionControlData (void)
{
	const SSCHAR*	pEditorID;
	CString			Buffer;
	CSString		ParamString;
	bool			Result;
	
	if (m_pCurrentCondition == NULL)
	{
		m_Operator.SetCurSel(-1);
		m_pCurrentFunction = NULL;

		UpdateFunctionStatus();
		UpdateReferenceStatus();
		UpdateValueStatus();
		UpdateParamsStatus();
		return;
	}

	m_FlagOr.SetCheck(CheckFlagBits(m_pCurrentCondition->Condition.GetCtdtData().Flags, SR_CTDA_FLAG_OR));
	m_FlagUseGlobal.SetCheck(CheckFlagBits(m_pCurrentCondition->Condition.GetCtdtData().Flags, SR_CTDA_FLAG_USEGLOBAL));
	m_FlagQuestAlias.SetCheck(CheckFlagBits(m_pCurrentCondition->Condition.GetCtdtData().Flags, SR_CTDA_FLAG_USEQUESTALIASES));
	m_FlagPackData.SetCheck(CheckFlagBits(m_pCurrentCondition->Condition.GetCtdtData().Flags, SR_CTDA_FLAG_USEPACKDATA));
	m_FlagSwapSubject.SetCheck(CheckFlagBits(m_pCurrentCondition->Condition.GetCtdtData().Flags, SR_CTDA_FLAG_SWAPSUBJECTTARGET));

	FindComboBoxItemData(m_RunOnList, m_pCurrentCondition->Condition.GetCtdtData().RunOnType, true);
	FindComboBoxItemData(m_Operator, m_pCurrentCondition->Condition.GetCtdtData().CompareType, true);

	m_pCurrentFunction = GetSrFunction(m_pCurrentCondition->Condition.GetCtdtData().Function + SR_CTDA_FUNCOFFSET);
	if (m_pCurrentFunction == NULL) return;
	m_Function.SetWindowText(m_pCurrentFunction->Name);

	if (m_FlagUseGlobal.GetCheck())
	{
		pEditorID = m_pRecord->GetParent()->GetEditorID(m_pCurrentCondition->Condition.GetCtdtData().GlobalID);

		if (pEditorID != NULL)
			m_Value.SetWindowTextA(pEditorID);
		else if (m_pCurrentCondition->Condition.GetCtdtData().GlobalID == 0)
			m_Value.SetWindowTextA("");
		else
		{
			Buffer.Format("0x%08X", m_pCurrentCondition->Condition.GetCtdtData().GlobalID);
			m_Value.SetWindowTextA(Buffer);
		}
	}
	else
	{
		Buffer.Format("%g", m_pCurrentCondition->Condition.GetCtdtData().Value);
		m_Value.SetWindowText(Buffer);
	}	
	
	pEditorID = m_pRecord->GetParent()->GetEditorID(m_pCurrentCondition->Condition.GetCtdtData().ReferenceID);

	if (pEditorID != NULL)
	{
		m_Reference.SetWindowText(pEditorID);
	}
	else if (m_pCurrentCondition->Condition.GetCtdtData().ReferenceID == 0)
	{
		m_Reference.SetWindowText("");
	}
	else
	{
		Buffer.Format("0x%08X", m_pCurrentCondition->Condition.GetCtdtData().ReferenceID);
		m_Reference.SetWindowText(Buffer);
	}

	ParamString.Empty();

	if (m_pCurrentFunction->NumParams >= 1) 
	{
		if (IsSrFunctionParamString(m_pCurrentFunction->Params[0].Type) && m_pCurrentCondition->pParam1 != NULL)
			ParamString = m_pCurrentCondition->pParam1->GetString();
		else
		{
			Result = SrFunctionParamToString(ParamString, m_pCurrentFunction->Params[0].Type, m_pCurrentCondition->Condition.GetCtdtData().Parameter1, m_pRecord->GetParent());
			if (!Result) ParamString.Format("0x%08X", m_pCurrentCondition->Condition.GetCtdtData().Parameter1);
		}
	}

	m_Param1.SetWindowTextA(ParamString);
	ParamString.Empty();

	if (m_pCurrentFunction->NumParams >= 2)
	{
		if (IsSrFunctionParamString(m_pCurrentFunction->Params[1].Type) && m_pCurrentCondition->pParam2 != NULL)
			ParamString = m_pCurrentCondition->pParam2->GetString();
		else
		{
			Result = SrFunctionParamToString(ParamString, m_pCurrentFunction->Params[1].Type, m_pCurrentCondition->Condition.GetCtdtData().Parameter2, m_pRecord->GetParent());
			if (!Result) ParamString.Format("0x%08X", m_pCurrentCondition->Condition.GetCtdtData().Parameter2);
		}
	}

	m_Param2.SetWindowTextA(ParamString);
	ParamString.Empty();

	if (m_pCurrentFunction->NumParams >= 3) 
	{
		if (IsSrFunctionParamString(m_pCurrentFunction->Params[0].Type))
			ParamString = "Error: String Param3";
		else
		{
			Result = SrFunctionParamToString(ParamString, m_pCurrentFunction->Params[2].Type, m_pCurrentCondition->Condition.GetCtdtData().Parameter2, m_pRecord->GetParent());
			if (!Result) ParamString.Format("0x%08X", m_pCurrentCondition->Condition.GetCtdtData().Parameter3);
		}
	}

	m_Param3.SetWindowTextA(ParamString);
	
	UpdateReferenceStatus();
	UpdateFunctionStatus();
	UpdateValueStatus();
	UpdateParamsStatus();
}


void CSrConditionDlg::OnLvnItemchangedConditionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	srrlcustomdata_t* pCustomData;
	
	*pResult = 0;
	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetConditionControlData();
	pCustomData = (srrlcustomdata_t *) m_ConditionList.GetItemData(pNMLV->iItem);

	if (pCustomData == NULL)
	{
		SetCurrentCondition(NULL);
	}
	else
	{
		CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->Subrecords[0]);
		SetCurrentCondition(FindConditionInfo(pCondition));
	}

}


void CSrConditionDlg::OnBnClickedSelectreferenceButton()
{
	AfxMessageBox("I can't select references yet, sorry!", MB_ICONEXCLAMATION | MB_OK);
}


void CSrConditionDlg::OnBnClickedSelectfunctionButton()
{
	CSrFunctionDlg FuncDlg;
	CString        Buffer;

	m_Function.GetWindowText(Buffer);

	bool Result = SrSelectFunctionCondition(Buffer);
	if (!Result) return;

	m_Function.SetWindowText(Buffer);
	m_pCurrentFunction = GetSrFunction(Buffer);

	UpdateFunctionStatus();

	m_Param1.RedrawWindow();
	m_Param2.RedrawWindow();
	m_Param3.RedrawWindow();
	m_Value.RedrawWindow();
	m_Reference.RedrawWindow();

	//GetConditionControlData();
}


void CSrConditionDlg::UpdateReferenceStatus (void)
{
	int RunOnType = 0;
	int ListIndex = m_RunOnList.GetCurSel();
	if (ListIndex >= 0) RunOnType = m_RunOnList.GetItemData(ListIndex);
	bool Enable = (RunOnType == SR_CONDITION_RUNON_REFERENCE);

	m_Reference.EnableWindow(Enable);
	m_ReferenceButton.EnableWindow(Enable);

	if (RunOnType == SR_CONDITION_RUNON_REFERENCE)
		m_ReferenceLabel.SetWindowTextA("Reference");
	else
		m_ReferenceLabel.SetWindowTextA("None");
}


void CSrConditionDlg::UpdateFunctionStatus (void)
{
	UpdateValueStatus();
	UpdateParamsStatus();
}


bool CSrConditionDlg::IsFunctionParamSelectable (const int ParamType)
{

	switch (ParamType)
	{
		case SR_FUNCPARAM_REFERENCE		:
		case SR_FUNCPARAM_ACTORVALUE	:
		case SR_FUNCPARAM_ACTOR			:
		case SR_FUNCPARAM_SPELLITEM		:
		case SR_FUNCPARAM_AXIS			:
		case SR_FUNCPARAM_CELL			:
		case SR_FUNCPARAM_ANIMGROUP		:
		case SR_FUNCPARAM_MAGICITEM		:
		case SR_FUNCPARAM_SOUND			:
		case SR_FUNCPARAM_TOPIC			:
		case SR_FUNCPARAM_QUEST			:
		case SR_FUNCPARAM_RACE			:
		case SR_FUNCPARAM_CLASS			:
		case SR_FUNCPARAM_FACTION		:
		case SR_FUNCPARAM_GENDER		:
		case SR_FUNCPARAM_GLOBAL		:
		case SR_FUNCPARAM_FURNITURE		:
		case SR_FUNCPARAM_WEAPON		:
		case SR_FUNCPARAM_STAGE			:
		case SR_FUNCPARAM_ACTORBASE		:
		case SR_FUNCPARAM_CONTAINER		:
		case SR_FUNCPARAM_WORLDSPACE	:
		case SR_FUNCPARAM_CRIME			:
		case SR_FUNCPARAM_PACKAGE		:
		case SR_FUNCPARAM_COMBATSTYLE	:
		case SR_FUNCPARAM_MAGICEFFECT	:
		case SR_FUNCPARAM_FORMTYPE		:
		case SR_FUNCPARAM_WEATHER		:
		case SR_FUNCPARAM_OWNER			:
		case SR_FUNCPARAM_EFFECTSHADER	:
		case SR_FUNCPARAM_FORMLIST		:
		case SR_FUNCPARAM_PERK			:
		case SR_FUNCPARAM_IMAGESPACE	:
		case SR_FUNCPARAM_VOICETYPE		:
		case SR_FUNCPARAM_ENCOUNTERZONE	:
		case SR_FUNCPARAM_IDLE			:
		case SR_FUNCPARAM_MESSAGE		:
		case SR_FUNCPARAM_EQUIPABLEITEM	:
		case SR_FUNCPARAM_EQUIPTYPE		:
		case SR_FUNCPARAM_MUSIC			:
		case SR_FUNCPARAM_CRITICALSTAGE	:
		case SR_FUNCPARAM_KEYWORD		:
		case SR_FUNCPARAM_LOCREFTYPE	:
		case SR_FUNCPARAM_LOCATION		:
		case SR_FUNCPARAM_QUESTALIAS	:
		case SR_FUNCPARAM_SHOUT			:
		case SR_FUNCPARAM_WORDOFPOWER	:
		case SR_FUNCPARAM_SCENE			:
		case SR_FUNCPARAM_CASTSOURCE	:
		case SR_FUNCPARAM_ASSOCTYPE		:
		case SR_FUNCPARAM_WARDSTATE		:
		case SR_FUNCPARAM_FURNANIM		:
		case SR_FUNCPARAM_FURNENTRY		:
		case SR_FUNCPARAM_SOUNDCATE		:
		case SR_FUNCPARAM_SKILLACTION	:
		case SR_FUNCPARAM_KNOWFORM		:
		case SR_FUNCPARAM_REGION		:
		case SR_FUNCPARAM_ACTION		:
			return true;
	};

	return false;
}


void CSrConditionDlg::UpdateParamsStatus (void)
{
	UpdateParam1Status();
	UpdateParam2Status();
	UpdateParam3Status();
}


void CSrConditionDlg::UpdateParam1Status (void)
{

	if (m_pCurrentCondition == NULL || m_pCurrentFunction == NULL || m_pCurrentFunction->NumParams < 1)
	{
		m_Param1.EnableWindow(false);
		m_Param1Button.EnableWindow(false);
		m_Param1Label.SetWindowTextA("");
		return;
	}

	m_Param1.EnableWindow(true);
	m_Param1Label.SetWindowTextA(GetSrFunctionParamTypeString(m_pCurrentFunction->Params[0].Type));
	m_Param1Button.EnableWindow(IsFunctionParamSelectable(m_pCurrentFunction->Params[0].Type));
}


void CSrConditionDlg::UpdateParam2Status (void)
{

	if (m_pCurrentCondition == NULL || m_pCurrentFunction == NULL || m_pCurrentFunction->NumParams < 2)
	{
		m_Param2.EnableWindow(false);
		m_Param2Button.EnableWindow(false);
		m_Param2Label.SetWindowTextA("");
		return;
	}

	m_Param2.EnableWindow(true);
	m_Param2Label.SetWindowTextA(GetSrFunctionParamTypeString(m_pCurrentFunction->Params[1].Type));
	m_Param2Button.EnableWindow(IsFunctionParamSelectable(m_pCurrentFunction->Params[1].Type));
}


void CSrConditionDlg::UpdateParam3Status (void)
{

	if (m_pCurrentCondition == NULL || m_pCurrentFunction == NULL || m_pCurrentFunction->NumParams < 3)
	{
		m_Param3.EnableWindow(false);
		m_Param3Button.EnableWindow(false);
		m_Param3Label.SetWindowTextA("");
		return;
	}

	m_Param3.EnableWindow(true);
	m_Param3Label.SetWindowTextA(GetSrFunctionParamTypeString(m_pCurrentFunction->Params[2].Type));
	m_Param3Button.EnableWindow(IsFunctionParamSelectable(m_pCurrentFunction->Params[2].Type));
}


void CSrConditionDlg::UpdateValueStatus (void)
{

	if (m_pCurrentCondition == NULL || m_pCurrentFunction == NULL)
	{
		m_Value.EnableWindow(false);
		m_ValueButton.EnableWindow(false);
		m_ValueLabel.SetWindowTextA("");
		return;
	}

	m_Value.EnableWindow(true);
		
	if (m_FlagUseGlobal.GetCheck())
	{
		m_ValueButton.EnableWindow(true);
		m_ValueLabel.SetWindowTextA("Global");
		m_Value.RedrawWindow();
		return;
	}

	m_ValueButton.EnableWindow(false);
	m_ValueLabel.SetWindowTextA("Value");
	m_Value.RedrawWindow();
}


void CSrConditionDlg::OnBnClickedSelectparam1Button()
{
	CSrFunctionParamDlg Dlg;
	CString				Buffer;

	if (m_pCurrentCondition == NULL) return;
	if (m_pCurrentFunction  == NULL) return;
	if (m_pCurrentFunction->NumParams < 1) return;

	m_Param1.GetWindowTextA(Buffer);

	if (!Dlg.DoModal(Buffer, m_pCurrentFunction->Params[0].Type, *m_pRecord->GetParent())) return;

	m_Param1.SetWindowTextA(Buffer);
}


void CSrConditionDlg::OnBnClickedSelectparam2Button()
{
	CSrFunctionParamDlg Dlg;
	CString				Buffer;

	if (m_pCurrentCondition == NULL) return;
	if (m_pCurrentFunction  == NULL) return;
	if (m_pCurrentFunction->NumParams < 2) return;

	m_Param2.GetWindowTextA(Buffer);

	if (!Dlg.DoModal(Buffer, m_pCurrentFunction->Params[1].Type, *m_pRecord->GetParent())) return;

	m_Param2.SetWindowTextA(Buffer);
}


void CSrConditionDlg::OnBnClickedSelectparam3Button()
{
	CSrFunctionParamDlg Dlg;
	CString				Buffer;

	if (m_pCurrentCondition == NULL) return;
	if (m_pCurrentFunction  == NULL) return;
	if (m_pCurrentFunction->NumParams < 3) return;

	m_Param3.GetWindowTextA(Buffer);

	if (!Dlg.DoModal(Buffer, m_pCurrentFunction->Params[2].Type, *m_pRecord->GetParent())) return;

	m_Param3.SetWindowTextA(Buffer);
}


bool CSrConditionDlg::CheckCurrentCondition (void)
{
	CString Buffer;

	if (m_pCurrentCondition == NULL) return true;
	
	m_Function.GetWindowTextA(Buffer);
	Buffer.Trim(" \t");

	srfunction_t* pFunc = GetSrFunction(Buffer);
	if (pFunc == NULL) return AddSrGeneralError("Unknown function '%s'!", Buffer);

	m_Reference.GetWindowTextA(Buffer);
	Buffer.Trim(" \t");

	if (!Buffer.IsEmpty() && m_pRecord != NULL)
	{
		CSrIdRecord* pRecord = m_pRecord->GetParent()->FindEditorID(Buffer);
		if (pRecord == NULL) return AddSrGeneralError("Unknown record '%s'!", Buffer);
		if (pRecord->GetRecordType() != SR_NAME_REFR) return AddSrGeneralError("Record '%s' is not a reference!", Buffer);
	}

	return true;
}


void CSrConditionDlg::CopyConditions(void)
{
	m_pOrigConditions->Destroy();

	for (dword i = 0; i < m_Conditions.GetSize(); ++i)
	{
		srconditioninfo_t* pCondition = m_Conditions[i];
		srconditioninfo_t* pNewCond = new srconditioninfo_t;

		pNewCond->Copy(*pCondition);
		m_pOrigConditions->Add(pNewCond);
	}
}


void CSrConditionDlg::OnOK()
{
	GetConditionControlData();
	CopyConditions();	
	
	CDialogEx::OnOK();
}


srconditioninfo_t* CSrConditionDlg::GetSelectedCondition()
{
	int SelIndex = m_ConditionList.GetSelectedItem();
	if (SelIndex < 0) return NULL;
		
	srrlcustomdata_t* pCustomData = m_ConditionList.GetCustomData(SelIndex);
	if (pCustomData == NULL) return NULL;

	CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->Subrecords[0]);
	return FindConditionInfo(pCondition);
}


void CSrConditionDlg::OnCondInsertBefore()
{
	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;

	GetConditionControlData();

	srconditioninfo_t* pNewCond = new srconditioninfo_t;
	pNewCond->Condition.InitializeNew();
	
	m_Conditions.InsertBefore(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex-1);
}


void CSrConditionDlg::OnCondInsertAfter()
{
	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;

	GetConditionControlData();

	srconditioninfo_t* pNewCond = new srconditioninfo_t;
	pNewCond->Condition.InitializeNew();
	
	m_Conditions.InsertAfter(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex+1);
}


void CSrConditionDlg::OnCondMoveUp()
{
	srconditioninfo_t* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetConditionControlData();
	m_pCurrentCondition = NULL;

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex <= 0) return;

	srconditioninfo_t* pNewCond = m_Conditions[ListIndex];
	if (pNewCond == NULL) return;

	m_Conditions.Remove(ListIndex);
	m_Conditions.InsertBefore(ListIndex-1, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex-1);
}


void CSrConditionDlg::OnCondMoveDown()
{
	srconditioninfo_t* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetConditionControlData();
	m_pCurrentCondition = NULL;

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) return;
	if (ListIndex >= (int) m_Conditions.GetSize()-1) return;

	srconditioninfo_t* pNewCond = m_Conditions[ListIndex];
	if (pNewCond == NULL) return;

	m_Conditions.Remove(ListIndex);
	m_Conditions.InsertAfter(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex+1);
}


void CSrConditionDlg::OnCondDelete()
{
	srconditioninfo_t* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetConditionControlData();
	m_pCurrentCondition = NULL;

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) return;

	m_Conditions.Delete(ListIndex);
	SetConditionList();
	SelectCondition(ListIndex);
}


void CSrConditionDlg::OnConditionDuplicate()
{
	srconditioninfo_t* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetConditionControlData();

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;

	srconditioninfo_t* pNewCond = new srconditioninfo_t;
	pNewCond->Copy(*pCondition);

	m_Conditions.InsertAfter(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex+1);
}


void CSrConditionDlg::OnUpdateConditionDuplicate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_ConditionList.GetSelectedCount() > 0);
}


void CSrConditionDlg::OnCondCopyCondition()
{
	POSITION Pos = m_ConditionList.GetFirstSelectedItemPosition();

	SrGlobClipClearConditions();
	GetConditionControlData();

	while (Pos)
	{
		int ListIndex = m_ConditionList.GetNextSelectedItem(Pos);
		srconditioninfo_t* pCondition = m_Conditions[ListIndex];
		SrGlobClipAddCondition(pCondition);
	}

}


void CSrConditionDlg::OnConditionPastecondition()
{
	GetConditionControlData();

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;
	
	for (dword i = 0; i < SrGlobClipGetConditions().GetSize(); ++i)
	{
		srconditioninfo_t* pNewCond = new srconditioninfo_t;
		pNewCond->Copy(*SrGlobClipGetConditions()[i]);

		m_Conditions.InsertAfter(ListIndex, pNewCond);
	}

	SetConditionList();
	SelectCondition(ListIndex+1);
}


void CSrConditionDlg::OnUpdateConditionPastecondition(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(SrGlobClipGetConditions().GetSize() > 0);

	CString Buffer;

	if (SrGlobClipGetConditions().GetSize() == 0)
		Buffer = "Paste Condition(s)";
	else if (SrGlobClipGetConditions().GetSize() == 1)
		Buffer = "Paste 1 Condition";
	else
		Buffer.Format("Paste %d Conditions", SrGlobClipGetConditions().GetSize());
		
	pCmdUI->SetText(Buffer);
}


void CSrConditionDlg::OnUpdateCondMenu(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetSelectedCondition() != NULL);
}


void CSrConditionDlg::OnContextMenu(CWnd* pWnd, CPoint Point)
{
	CMenu  Menu;
	CMenu* pSubMenu;
	int    Result;

	if (pWnd->GetDlgCtrlID() == IDC_CONDITION_LIST) 
	{
		Result = Menu.LoadMenu(IDR_CONDITION_MENU);
		if (!Result) return;

		pSubMenu = Menu.GetSubMenu(0);
		if (pSubMenu == NULL) return;

		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
	}
		
}


void CSrConditionDlg::SelectCondition (const int Index)
{
	int ListIndex = Index;
	int NumItems = m_ConditionList.GetItemCount();

	if (NumItems <= 0) return;

	GetConditionControlData();

	if (ListIndex < 0) ListIndex = 0;
	if (ListIndex >= NumItems) ListIndex = NumItems - 1;

	m_ConditionList.SelectRecord(ListIndex);

	m_pCurrentCondition = NULL;
	srrlcustomdata_t* pCustomData = m_ConditionList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->Subrecords[0]);
	m_pCurrentCondition = FindConditionInfo(pCondition);
}


void CSrConditionDlg::OnBnClickedMoveupButton()
{
	OnCondMoveUp(); 
}


void CSrConditionDlg::OnBnClickedMovedownButton()
{
	OnCondMoveDown(); 
}


void CSrConditionDlg::OnBnClickedAddButton()
{
	OnCondInsertAfter(); 
}


void CSrConditionDlg::OnBnClickedDeleteButton()
{
	OnCondDelete(); 
}


void CSrConditionDlg::OnHelp (void) 
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Conditions", "Conditions");
}


BOOL CSrConditionDlg::OnHelpInfo (HELPINFO* pHelpInfo)
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Conditions", "Conditions");
	return TRUE;
}


int CSrConditionDlg::IsValidRecordType (CString& InputString, const srrectype_t Type)
{
	InputString.Trim(" ");
	CSrRecord* pRecord = m_pRecord->GetParent()->FindEditorID(InputString);

	if (pRecord == NULL) 
	{
		char*  pError;
		dword  Value = strtoul(InputString, &pError, 0);
		if (*pError != '\0') return SR_CHECKRESULT_ERROR;	

		pRecord = m_pRecord->GetParent()->FindFormID(Value);
		if (pRecord == NULL) return SR_CHECKRESULT_ERROR;
	}

	if (pRecord->GetRecordType() != Type) return SR_CHECKRESULT_ERROR;
	return SR_CHECKRESULT_OK;
}


int CSrConditionDlg::IsValidReference (void)
{
	if (m_pCurrentCondition == NULL) return SR_CHECKRESULT_UNKNOWN;
	if (m_pCurrentFunction  == NULL) return SR_CHECKRESULT_UNKNOWN;

	CString Buffer;
	m_Value.GetWindowTextA(Buffer);
	return IsValidRecordType(Buffer, SR_NAME_REFR);
}


int CSrConditionDlg::IsValidParam (CEdit& ParamEdit, const dword ParamIndex)
{
	if (m_pCurrentCondition == NULL) return SR_CHECKRESULT_UNKNOWN;
	if (m_pCurrentFunction  == NULL) return SR_CHECKRESULT_UNKNOWN;
	if (m_pCurrentFunction->NumParams < ParamIndex + 1) return SR_CHECKRESULT_UNKNOWN;

	CString Buffer;
	ParamEdit.GetWindowTextA(Buffer);

	if (SrCheckFunctionParam(Buffer, m_pCurrentFunction->Params[ParamIndex].Type, m_pRecord->GetParent())) return SR_CHECKRESULT_OK;
	return SR_CHECKRESULT_ERROR;
}


int CSrConditionDlg::IsValidValue (void)
{
	if (m_pCurrentCondition == NULL) return SR_CHECKRESULT_UNKNOWN;
	if (m_pCurrentFunction  == NULL) return SR_CHECKRESULT_UNKNOWN;

	CString Buffer;
	m_Value.GetWindowTextA(Buffer);

	if (m_FlagUseGlobal.GetCheck())	return IsValidRecordType(Buffer, SR_NAME_GLOB);
	
	char*   pError;
	double  Value;
	Value = strtod(Buffer, &pError);

	if (*pError != '\0') return SR_CHECKRESULT_ERROR;	
	return SR_CHECKRESULT_OK;
}


HBRUSH CSrConditionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Function) 
	{
		switch (m_FunctionIDCheck) 
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
	else if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Value) 
	{
		switch (IsValidValue())
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
	else if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Param1) 
	{
		switch (IsValidParam1())
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
	else if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Param2) 
	{
		switch (IsValidParam2())
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
	else if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Param3) 
	{
		switch (IsValidParam3())
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
	else if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Reference) 
	{
		switch (IsValidReference())
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


void CSrConditionDlg::OnEnChangeFunctionText()
{
	CString Buffer;
	int     NewCheck;

	m_Function.GetWindowTextA(Buffer);
	Buffer.Trim(" \t");

	m_pCurrentFunction = GetSrFunction(Buffer);

	if (m_pCurrentFunction == NULL || (m_pCurrentFunction->Flags & SR_FUNCTION_FLAG_CONDITION) == 0)
		NewCheck = SR_CHECKRESULT_ERROR;
	else
		NewCheck = SR_CHECKRESULT_OK;

	if (NewCheck == m_FunctionIDCheck) return;
	m_FunctionIDCheck = NewCheck;
	m_Function.RedrawWindow();
}


void CSrConditionDlg::OnLvnItemchangingConditionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	srrlcustomdata_t* pCustomData;
	
	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;
	
	pCustomData = (srrlcustomdata_t *) m_ConditionList.GetItemData(pNMLV->iItem);
	if (pCustomData == NULL) return;	
}


void CSrConditionDlg::OnCbnSelchangeRunonList()
{
	UpdateReferenceStatus();
}


void CSrConditionDlg::OnBnClickedSelectvalueButton()
{
	if (m_pCurrentFunction == NULL) return;
	if (m_FlagUseGlobal.GetCheck() == 0) return;

	CString Buffer;
	m_Value.GetWindowTextA(Buffer);
	Buffer.Trim(" ");

	if (!SrSelectRecord(Buffer, m_pRecord->GetParent(), SR_NAME_GLOB, &CSrGlobRecord::s_FieldMap)) return;

	m_Value.SetWindowTextA(Buffer);
}


void CSrConditionDlg::OnBnClickedUseglobalCheck()
{
	UpdateValueStatus();
}


void CSrConditionDlg::OnEnChangeValueText()
{
		/* Force redraw to update valid/invalid color */
	m_Value.RedrawWindow();
}


void CSrConditionDlg::OnEnChangeReferenceText()
{
		/* Force redraw to update valid/invalid color */
	m_Reference.RedrawWindow();
}


void CSrConditionDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CSrConditionDlg::OnDblClkParam1(NMHDR *pNMHDR, LRESULT *pResult)
{
	SystemLog.Printf("Double Click");
	OnBnClickedSelectparam1Button();
}


void CSrConditionDlg::OnEnChangeParam1Text()
{
		/* Force redraw to update valid/invalid color */
	m_Param1.RedrawWindow();
}


void CSrConditionDlg::OnEnChangeParam2Text()
{
		/* Force redraw to update valid/invalid color */
	m_Param2.RedrawWindow();
}


void CSrConditionDlg::OnEnChangeParam3Text()
{
		/* Force redraw to update valid/invalid color */
	m_Param3.RedrawWindow();
}


BOOL CSrConditionDlg::PreTranslateMessage (MSG* pMsg)
{
	UpdateDialogControls(this, TRUE);
	return CDialogEx::PreTranslateMessage( pMsg );
}