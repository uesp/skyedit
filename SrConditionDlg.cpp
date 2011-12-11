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
	ON_BN_CLICKED(IDC_SELECTREFERENCE_BUTTON, &CSrConditionDlg::OnBnClickedSelectreferenceButton)
	ON_BN_CLICKED(IDC_SELECTFUNCTION_BUTTON, &CSrConditionDlg::OnBnClickedSelectfunctionButton)
	ON_BN_CLICKED(IDC_SELECTPARAM1_BUTTON, &CSrConditionDlg::OnBnClickedSelectparam1Button)
	ON_BN_CLICKED(IDC_SELECTPARAM2_BUTTON, &CSrConditionDlg::OnBnClickedSelectparam2Button)
	ON_COMMAND(ID_COND_INSERTBEFORE, &CSrConditionDlg::OnCondInsertBefore)
	ON_COMMAND(ID_COND_INSERTAFTER, &CSrConditionDlg::OnCondInsertAfter)
	ON_COMMAND(ID_COND_MOVEUP, &CSrConditionDlg::OnCondMoveUp)
	ON_COMMAND(ID_COND_MOVEDOWN, &CSrConditionDlg::OnCondMoveDown)
	ON_COMMAND(ID_COND_DELETE, &CSrConditionDlg::OnCondDelete)
	ON_COMMAND(ID_COND_COPYCONDITION, &CSrConditionDlg::OnCondCopyCondition)
	//ON_UPDATE_COMMAND_UI(ID_COND_INSERTBEFORE, &CSrConditionDlg::OnUpdateCondMenu)
	//ON_UPDATE_COMMAND_UI(ID_COND_INSERTAFTER, &CSrConditionDlg::OnUpdateCondMenu)
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
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_ConditionListInit[] = {
	{ SR_FIELD_REFERENCE,	 100,		LVCFMT_CENTER },
	{ SR_FIELD_FUNCTION,	 150,		LVCFMT_CENTER },
	{ SR_FIELD_PARAM1,		 120,		LVCFMT_CENTER },
	{ SR_FIELD_PARAM2,		 120,		LVCFMT_CENTER },
	{ SR_FIELD_OPERATOR,	 50,		LVCFMT_CENTER },
	{ SR_FIELD_VALUE,		 75,		LVCFMT_CENTER },
	{ SR_FIELD_CONDFLAGSEX,	 100,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_ConditionFields[] = {
	{ "Reference",	SR_FIELD_REFERENCE,		0, NULL },
	{ "Function",	SR_FIELD_FUNCTION,		0, NULL },
	{ "Param1",		SR_FIELD_PARAM1,		0, NULL },
	{ "Param2",		SR_FIELD_PARAM2,		0, NULL },
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
	DDX_Control(pDX, IDC_PARAM1_LABEL, m_Param1Label);
	DDX_Control(pDX, IDC_PARAM2_LABEL, m_Param2Label);
	DDX_Control(pDX, IDC_PARAM2_TEXT, m_Param2);
	DDX_Control(pDX, IDC_VALUE_TEXT, m_Value);
	DDX_Control(pDX, IDC_VALUE_LABEL, m_ValueLabel);
	DDX_Control(pDX, IDC_OPERATOR_LIST, m_Operator);
	DDX_Control(pDX, IDC_OR_CHECK, m_FlagOr);
	DDX_Control(pDX, IDC_RUNTARGET_CHECK, m_FlagRunOnTarget);
	DDX_Control(pDX, IDC_USEGLOBAL_CHECK, m_FlagUseGlobal);
	DDX_Control(pDX, IDC_SELECTFUNCTION_BUTTON, m_FunctionButton);
	DDX_Control(pDX, IDC_SELECTREFERENCE_BUTTON, m_ReferenceButton);
	DDX_Control(pDX, IDC_SELECTPARAM1_BUTTON, m_Param1Button);
	DDX_Control(pDX, IDC_SELECTPARAM2_BUTTON, m_Param2Button);
}
/*===========================================================================
 *		End of Class CSrConditionDlg::DoDataExchange()
 *=========================================================================*/


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
		
		/* Setup the list */
	m_ConditionList.SetListName("ConditionList");
	m_ConditionList.SetDragEnable(true);
	m_ConditionList.DefaultSettings();
	m_ConditionList.SetupCustomList(s_ConditionListInit, NULL, s_ConditionFields);
	m_ConditionList.SetOwner(this);
	m_ConditionList.SetColorEnable(false);
	m_ConditionList.SetDragType(SR_RLDRAG_CUSTOM);
	m_ConditionList.SetSortEnable(false);
	//m_ConditionList.SetActivateType(SR_RLACTIVATE_NONE);

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
  CSrCtdaSubrecord*     pCondition;

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
int CSrConditionDlg::AddConditionList (CSrCtdaSubrecord* pCondition) 
{
  srrlcustomdata_t	CustomData = { 0 };
  CString           Buffer;
  int		        ListIndex;

  CustomData.pRecord = m_pRecord;

		/* Setup the custom data structure for the list */
  CustomData.pSubrecords[0] = pCondition;
  
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
  srrlcustomdata_t* pCustomData;
  srfunction_t*		pFunction;;
  CString			Buffer;

  pCustomData = m_ConditionList.GetCustomData(ListIndex);
  if (pCustomData == NULL) return;

  if (Update) m_ConditionList.UpdateRecord(ListIndex);

  CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->pSubrecords[0]);
  if (pCondition == NULL) return;

  pFunction = GetSrFunction(pCondition->GetCtdtData().Function + SR_CTDA_FUNCOFFSET);
  if (pFunction == NULL) return;

  if (pFunction->NumParams >= 1 && IsSrFunctionParamFormID(pFunction->Params[0].Type)) 
  {
	const SSCHAR* pEditorID = m_pRecord->GetParent()->GetEditorID(pCondition->GetCtdtData().Parameter1);
	if (pEditorID != NULL) m_ConditionList.SetCustomField(ListIndex, SR_FIELD_PARAM1, pEditorID);
  }

  if (pFunction->NumParams >= 2 && IsSrFunctionParamFormID(pFunction->Params[1].Type)) 
  {
	const SSCHAR* pEditorID = m_pRecord->GetParent()->GetEditorID(pCondition->GetCtdtData().Parameter2);
	if (pEditorID != NULL) m_ConditionList.SetCustomField(ListIndex, SR_FIELD_PARAM2, pEditorID);
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
bool CSrConditionDlg::DoModal (CSrRecord* pRecord, CSrCtdaArray* pConditions)
{
	if (pRecord == NULL || pConditions == NULL) return false;

	m_pOrigConditions = pConditions;
	m_pRecord = pRecord;
	m_Conditions.Destroy();

	for (dword i = 0; i < m_pOrigConditions->GetSize(); ++i)
	{
		CSrCtdaSubrecord* pCondition = (*m_pOrigConditions)[i];
		CSrCtdaSubrecord* pNewCond = new CSrCtdaSubrecord;

		pNewCond->Copy(pCondition);
		m_Conditions.Add(pNewCond);
	}

	int Result = CDialogEx::DoModal();
	return (Result == IDOK);
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::DoModal()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - void GetCurrentCondition (void);
 *
 *=========================================================================*/
void CSrConditionDlg::GetCurrentCondition (void)
{
	CString    Buffer;
	srformid_t FormID;

	if (m_pCurrentCondition == NULL) return;
	//SystemLog.Printf("GetValue1 = %g", m_pCurrentCondition->GetCtdtData().Value);

	int Index = m_Operator.GetCurSel();

	if (Index >= 0) 
	{
		m_pCurrentCondition->GetCtdtData().CompareType = m_Operator.GetItemData(Index);
	}

	m_Value.GetWindowText(Buffer);
	m_pCurrentCondition->GetCtdtData().Value = (float) strtod(Buffer, NULL);

	m_Reference.GetWindowText(Buffer);
	Buffer.Trim(" \t\n\r");
	
	if (Buffer.Left(2).CompareNoCase("0x") == 0)
	{
		FormID = strtoul(Buffer, NULL, 0);
		m_pCurrentCondition->GetCtdtData().RefID = FormID;
	}
	else if (Buffer.IsEmpty())
	{
		m_pCurrentCondition->GetCtdtData().RefID = 0;
	}
	else
	{
		CSrIdRecord* pRecord = m_pRecord->GetParent()->FindEditorID(Buffer);

		if (pRecord == NULL) 
			AddSrGeneralError("Unknown editorid '%s' found!", Buffer);
		else
			m_pCurrentCondition->GetCtdtData().RefID = pRecord->GetFormID();
	}

	m_Function.GetWindowText(Buffer);
	Buffer.Trim(" \t\n\r");

	srfunction_t* pFunction = ::GetSrFunction(Buffer);

	if (pFunction == NULL)
	{
		AddSrGeneralError("Unknown function '%s'!", Buffer);
	}
	else
	{
		m_pCurrentCondition->GetCtdtData().Function = pFunction->OpCode - SR_CTDA_FUNCOFFSET;
	}

	m_Param1.GetWindowText(Buffer);
	Buffer.Trim(" \t\n\r");

	if (Buffer.Left(2).CompareNoCase("0x") == 0)
	{
		FormID = strtoul(Buffer, NULL, 0);
		m_pCurrentCondition->GetCtdtData().Parameter1 = FormID;
	}
	else if (Buffer.IsEmpty())
	{
		m_pCurrentCondition->GetCtdtData().Parameter1 = 0;
	}
	else
	{
		CSrIdRecord* pRecord = m_pRecord->GetParent()->FindEditorID(Buffer);

		if (pRecord == NULL) 
			AddSrGeneralError("Unknown editorid '%s' found!", Buffer);
		else
			m_pCurrentCondition->GetCtdtData().Parameter1 = pRecord->GetFormID();
	}

	m_Param2.GetWindowText(Buffer);
	Buffer.Trim(" \t\n\r");

	if (Buffer.Left(2).CompareNoCase("0x") == 0)
	{
		FormID = strtoul(Buffer, NULL, 0);
		m_pCurrentCondition->GetCtdtData().Parameter2 = FormID;
	}
	else if (Buffer.IsEmpty())
	{
		m_pCurrentCondition->GetCtdtData().Parameter2 = 0;
	}
	else
	{
		CSrIdRecord* pRecord = m_pRecord->GetParent()->FindEditorID(Buffer);

		if (pRecord == NULL) 
			AddSrGeneralError("Unknown editorid '%s' found!", Buffer);
		else
			m_pCurrentCondition->GetCtdtData().Parameter2 = pRecord->GetFormID();
	}

	dword Flags = m_pCurrentCondition->GetCtdtData().Flags;
	::FlipFlagBits(Flags, SR_CTDA_FLAG_OR, m_FlagOr.GetCheck() != 0);
	::FlipFlagBits(Flags, SR_CTDA_FLAG_RUNONTARGET, m_FlagRunOnTarget.GetCheck() != 0);
	::FlipFlagBits(Flags, SR_CTDA_FLAG_USEGLOBAL, m_FlagUseGlobal.GetCheck() != 0);
	 m_pCurrentCondition->GetCtdtData().Flags = Flags;

	 for (int i = 0; i < m_ConditionList.GetItemCount(); ++i)
	 {
		 srrlcustomdata_t* pCustomData = (srrlcustomdata_t *) m_ConditionList.GetItemData(i);
		 if (pCustomData == NULL) continue;

		 CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->pSubrecords[0]);
		 if (pCondition == NULL) continue;
		 if (pCondition != m_pCurrentCondition) continue;

		 UpdateConditionList(i, true);
		 break;
	 }
	 	 
	 //SystemLog.Printf("GetValue2 = %g", m_pCurrentCondition->GetCtdtData().Value);
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::GetCurrentCondition()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrConditionDlg Method - void SetCurrentCondition (pCondition);
 *
 *=========================================================================*/
void CSrConditionDlg::SetCurrentCondition (CSrCtdaSubrecord* pCondition)
{
	bool Enable = pCondition != NULL;
	const SSCHAR* pEditorID;
	CString Buffer;

	m_Operator.EnableWindow(Enable);
	m_Reference.EnableWindow(Enable);
	m_Function.EnableWindow(Enable);
	m_Param1.EnableWindow(Enable);
	m_Param2.EnableWindow(Enable);
	m_Value.EnableWindow(Enable);
	m_FlagOr.EnableWindow(Enable);
	m_FlagRunOnTarget.EnableWindow(Enable);
	m_FlagUseGlobal.EnableWindow(Enable);
	m_FunctionButton.EnableWindow(Enable);
	m_ReferenceButton.EnableWindow(Enable);
	m_Param1Button.EnableWindow(Enable);
	m_Param2Button.EnableWindow(Enable);

	m_ReferenceLabel.SetWindowText("");
	m_FunctionLabel.SetWindowText("");
	m_Param1Label.SetWindowText("");
	m_Param2Label.SetWindowText("");
	m_ValueLabel.SetWindowText("");

	if (pCondition == NULL)
	{
		m_Operator.SetCurSel(-1);
		m_Reference.SetWindowText("");
		m_Function.SetWindowText("");
		m_Param1.SetWindowText("");
		m_Param2.SetWindowText("");
		m_Value.SetWindowText("");
		m_pCurrentCondition = NULL;
		return;
	}

	m_pCurrentCondition = pCondition;
	FindComboBoxItemData(m_Operator, pCondition->GetCtdtData().CompareType, true);
	//SystemLog.Printf("SetValue1 = %g", m_pCurrentCondition->GetCtdtData().Value);

	srfunction_t* pFunction = GetSrFunction(pCondition->GetCtdtData().Function + SR_CTDA_FUNCOFFSET);

	if (pFunction != NULL)
	{
		m_Function.SetWindowText(pFunction->Name);
		if (CheckFlagBits(pFunction->Flags, SR_FUNCTION_FLAG_REF)) m_ReferenceLabel.SetWindowText("Required");

		if (pFunction->NumParams > 0) m_Param1Label.SetWindowTextA(::GetSrFunctionParamTypeString(pFunction->Params[0].Type));
		if (pFunction->NumParams > 1) m_Param2Label.SetWindowTextA(::GetSrFunctionParamTypeString(pFunction->Params[1].Type));
	}
	else
	{
		Buffer.Format("0x%08X", pCondition->GetCtdtData().Function);
		m_Function.SetWindowText(Buffer);		
	}

	if (pCondition->GetCtdtData().RefID == 0)
	{
		m_Reference.SetWindowText("");
	}
	else
	{
		const SSCHAR* pEditorID = m_pRecord->GetParent()->GetEditorID(pCondition->GetCtdtData().RefID);

		if (pEditorID != NULL)
		{
			m_Reference.SetWindowText(pEditorID);
		}
		else
		{
			Buffer.Format("0x%08X", pCondition->GetCtdtData().RefID);
			m_Reference.SetWindowText(Buffer);

		}
	}

	Buffer.Format("%g", pCondition->GetCtdtData().Value);
	m_Value.SetWindowText(Buffer);

	pEditorID = NULL;

	if (pFunction != NULL && pFunction->NumParams > 0 && IsSrFunctionParamFormID(pFunction->Params[0].Type))
	{
		pEditorID = m_pRecord->GetParent()->GetEditorID(pCondition->GetCtdtData().Parameter1);
	}

	if (pEditorID == NULL)
	{
		Buffer.Format("0x%08X", pCondition->GetCtdtData().Parameter1);
		m_Param1.SetWindowText(Buffer);
	}
	else
	{
		m_Param1.SetWindowText(pEditorID);
	}

	pEditorID = NULL;
	
	if (pFunction != NULL && pFunction->NumParams > 1 && IsSrFunctionParamFormID(pFunction->Params[1].Type))
	{
		pEditorID = m_pRecord->GetParent()->GetEditorID(pCondition->GetCtdtData().Parameter2);
	}

	if (pEditorID == NULL)
	{
		Buffer.Format("0x%08X", pCondition->GetCtdtData().Parameter2);
		m_Param2.SetWindowText(Buffer);
	}
	else
	{
		m_Param2.SetWindowText(pEditorID);
	}

	m_FlagOr.SetCheck(CheckFlagBits(pCondition->GetCtdtData().Flags, SR_CTDA_FLAG_OR));
	m_FlagRunOnTarget.SetCheck(CheckFlagBits(pCondition->GetCtdtData().Flags, SR_CTDA_FLAG_RUNONTARGET));
	m_FlagUseGlobal.SetCheck(CheckFlagBits(pCondition->GetCtdtData().Flags, SR_CTDA_FLAG_USEGLOBAL));

	//SystemLog.Printf("SetValue2 = %g", m_pCurrentCondition->GetCtdtData().Value);
}
/*===========================================================================
 *		End of Class Method CSrConditionDlg::SetCurrentCondition()
 *=========================================================================*/


void CSrConditionDlg::OnLvnItemchangedConditionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	srrlcustomdata_t* pCustomData;
	
	*pResult = 0;
	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	//SystemLog.Printf("iItem = %d, Condition=0x%08X", pNMLV->iItem, (int) m_pCurrentCondition);
	GetCurrentCondition();

	pCustomData = (srrlcustomdata_t *) m_ConditionList.GetItemData(pNMLV->iItem);

	if (pCustomData == NULL)
	{
		SetCurrentCondition(NULL);
	}
	else
	{
		CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->pSubrecords[0]);
		SetCurrentCondition(pCondition);
	}

}


void CSrConditionDlg::OnBnClickedSelectreferenceButton()
{
}


void CSrConditionDlg::OnBnClickedSelectfunctionButton()
{
	CSrFunctionDlg FuncDlg;
	CString        Buffer;

	m_Function.GetWindowText(Buffer);

	bool Result = SrSelectFunctionScript(Buffer);
	if (Result) m_Function.SetWindowText(Buffer);

	GetCurrentCondition();
	SetCurrentCondition(m_pCurrentCondition);
}


void CSrConditionDlg::OnBnClickedSelectparam1Button()
{
}


void CSrConditionDlg::OnBnClickedSelectparam2Button()
{
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
		CSrCtdaSubrecord* pCondition = m_Conditions[i];
		CSrCtdaSubrecord* pNewCond = new CSrCtdaSubrecord;

		pNewCond->Copy(pCondition);
		m_pOrigConditions->Add(pNewCond);
	}
}


void CSrConditionDlg::OnOK()
{
	if (!CheckCurrentCondition())
	{
		SrEditShowLastError("Failed to save the condition!");		
		return;
	}

	GetCurrentCondition();
	CopyConditions();	
	
	CDialogEx::OnOK();
}


CSrCtdaSubrecord* CSrConditionDlg::GetSelectedCondition()
{
	int SelIndex = m_ConditionList.GetSelectedItem();
	if (SelIndex < 0) return NULL;
		
	srrlcustomdata_t* pCustomData = m_ConditionList.GetCustomData(SelIndex);
	if (pCustomData == NULL) return NULL;

	CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->pSubrecords[0]);
	return pCondition;
}


void CSrConditionDlg::OnCondInsertBefore()
{
	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;

	GetCurrentCondition();

	CSrCtdaSubrecord* pNewCond = new CSrCtdaSubrecord;
	pNewCond->InitializeNew();
	
	m_Conditions.InsertBefore(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex-1);
}


void CSrConditionDlg::OnCondInsertAfter()
{
	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;

	GetCurrentCondition();

	CSrCtdaSubrecord* pNewCond = new CSrCtdaSubrecord;
	pNewCond->InitializeNew();
	
	m_Conditions.InsertAfter(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex+1);
}


void CSrConditionDlg::OnCondMoveUp()
{
	CSrCtdaSubrecord* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetCurrentCondition();
	m_pCurrentCondition = NULL;

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex <= 0) return;

	CSrCtdaSubrecord* pNewCond = m_Conditions[ListIndex];
	if (pNewCond == NULL) return;

	m_Conditions.Remove(ListIndex);
	m_Conditions.InsertBefore(ListIndex-1, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex-1);
}


void CSrConditionDlg::OnCondMoveDown()
{
	CSrCtdaSubrecord* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetCurrentCondition();
	m_pCurrentCondition = NULL;

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) return;
	if (ListIndex >= (int) m_Conditions.GetSize()-1) return;

	CSrCtdaSubrecord* pNewCond = m_Conditions[ListIndex];
	if (pNewCond == NULL) return;

	m_Conditions.Remove(ListIndex);
	m_Conditions.InsertAfter(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex+1);
}


void CSrConditionDlg::OnCondDelete()
{
	CSrCtdaSubrecord* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetCurrentCondition();
	m_pCurrentCondition = NULL;

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) return;

	m_Conditions.Delete(ListIndex);
	SetConditionList();
	SelectCondition(ListIndex);
}


void CSrConditionDlg::OnCondCopyCondition()
{
	CSrCtdaSubrecord* pCondition = GetSelectedCondition();
	if (pCondition == NULL) return;

	GetCurrentCondition();

	int ListIndex = m_ConditionList.GetSelectedItem();
	if (ListIndex < 0) ListIndex = 0;

	CSrCtdaSubrecord* pNewCond = new CSrCtdaSubrecord;
	pNewCond->Copy(pCondition);

	m_Conditions.InsertAfter(ListIndex, pNewCond);

	SetConditionList();
	SelectCondition(ListIndex+1);
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

	GetCurrentCondition();

	if (ListIndex < 0) ListIndex = 0;
	if (ListIndex >= NumItems) ListIndex = NumItems - 1;

	m_ConditionList.SelectRecord(ListIndex);

	m_pCurrentCondition = NULL;
	srrlcustomdata_t* pCustomData = m_ConditionList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pCustomData->pSubrecords[0]);
	m_pCurrentCondition = pCondition;
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



/*===========================================================================
 *
 * Class CSrConditionDlg Event - void OnHelp (void);
 *
 *=========================================================================*/
void CSrConditionDlg::OnHelp (void) 
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Conditions", "Conditions");
}
/*===========================================================================
 *		End of Class Event CSrConditionDlg::OnHelp()
 *=========================================================================*/


BOOL CSrConditionDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	GetSrEditApp().OpenWebHelp("Tes5Mod:SkyEdit/User_Interface/Conditions", "Conditions");
	return TRUE;
	//return CDialogEx::OnHelpInfo(pHelpInfo);
}


HBRUSH CSrConditionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_Function) {
		switch (m_FunctionIDCheck) {
		case SR_CHECKRESULT_NOCHANGE:
			hBrush = CreateSolidBrush(RGB(255,255,255));
			pDC->SetBkColor(RGB(255,255,255));
			break;
		case SR_CHECKRESULT_OK:
			hBrush = CreateSolidBrush(RGB(204,255,204));
			pDC->SetBkColor(RGB(204,255,204));
			break;
		case SR_CHECKRESULT_ERROR:
			hBrush = CreateSolidBrush(RGB(255,204,204));
			pDC->SetBkColor(RGB(255,204,204));
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

	srfunction_t* pFunc = GetSrFunction(Buffer);

	if (pFunc == NULL)
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

	if (!CheckCurrentCondition())
	{
		SrEditShowLastError("Failed to save the condition!");
		//*pResult = TRUE;
	}
	
}
