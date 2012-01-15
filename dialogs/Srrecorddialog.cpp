/*===========================================================================
 *
 * File:		Srrecorddialog.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "srrecorddialog.h"
#include "sreditdlghandler.h"
#include "resource.h"
#include "sredit.h"
#include "sreditdoc.h"
//#include "srbipedpartsdlg.h"
//#include "srbipedpartslistdlg.h"
#include "mainfrm.h"
#include "SrConditionDlg.h"
#include "SrBoundsDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrRecordDialog, CFormView);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrRecordDialog, CFormView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_APPLY_BUTTON, OnApply)
	ON_COMMAND(ID_CANCEL_BUTTON, OnCancel)
	ON_COMMAND(ID_SAVE_BUTTON, OnSave)
	ON_EN_KILLFOCUS(IDC_EDITORID, OnKillfocusEditorid)
	//ON_BN_CLICKED(IDC_BIPEDPARTS_BUTTON, OnBipedpartsButton)
	//ON_BN_CLICKED(IDC_EDIT_SCRIPT, OnEditScript)
	ON_BN_CLICKED(IDC_EDIT_ENCHANTMENT, OnEditEnchantment)
	//ON_BN_CLICKED(IDC_SELECTSCRIPT_BUTTON, OnSelectScript)
	ON_BN_CLICKED(IDC_SELECTENCHANT_BUTTON, OnSelectEnchantment)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)
	//ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SCRIPT, OnDropScript)
	//ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SCRIPT, OnDropScript)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ENCHANTMENT, OnDropEnchant)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ENCHANTMENT, OnDropEnchant)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECTALL, OnUpdateEditSelectAll)
	ON_WM_HELPINFO()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_MODEL, OnDropModel)
	ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_MODEL, OnDropModel)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_INVENTORYICON, OnDropIcon)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_INVENTORYICON, OnDropIcon)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_SOUNDFILE, OnDropSoundFile)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_SOUNDFILE, OnDropSoundFile)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_MALEICON, OnDropMaleIcon)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_MALEICON, OnDropMaleIcon)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_FEMALEICON, OnDropFemaleIcon)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_FEMALEICON, OnDropFemaleIcon)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_MALEWORLD, OnDropMaleWorldModel)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_MALEWORLD, OnDropMaleWorldModel)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_MALEBIPED, OnDropMaleBipedModel)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_MALEBIPED, OnDropMaleBipedModel)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_FEMALEWORLD, OnDropFemaleWorldModel)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_FEMALEWORLD, OnDropFemaleWorldModel)
	//ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_FEMALEBIPED, OnDropFemaleBipedModel)
	//ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_FEMALEBIPED, OnDropFemaleBipedModel)
	ON_COMMAND(IDC_SELECT_MODEL, OnSelectModel)
	//ON_COMMAND(IDC_SELECT_ICON, OnSelectIcon)
	//ON_COMMAND(IDC_SELECT_SOUNDFILE, OnSelectSoundFile)
	//ON_COMMAND(IDC_SELECT_MALEICON, OnSelectMaleIcon)
	//ON_COMMAND(IDC_SELECT_FEMALEICON, OnSelectFemaleIcon)
	//ON_COMMAND(IDC_SELECT_MALEWORLDMODEL, OnSelectMaleWorldModel)
	//ON_COMMAND(IDC_SELECT_MALEBIPEDMODEL, OnSelectMaleBipedModel)
	//ON_COMMAND(IDC_SELECT_FEMALEWORLDMODEL, OnSelectFemaleWorldModel)
	//ON_COMMAND(IDC_SELECT_FEMALEBIPEDMODEL, OnSelectFemaleBipedModel)
	//ON_BN_CLICKED(IDC_SELECTSOUND_BUTTON, OnSelectsoundButton)
	//ON_BN_CLICKED(IDC_EDIT_SOUND, OnEditSound)
	////ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUND, OnDropSound)
	//ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUND, OnDropSound)
	ON_BN_CLICKED(IDC_ADDKEYWORD_BUTTON, OnBnClickedAddkeywordButton)
	ON_BN_CLICKED(IDC_EDITKEYWORD_BUTTON, OnBnClickedEditkeywordButton)
	ON_BN_CLICKED(IDC_DELKEYWORD_BUTTON, OnBnClickedDelkeywordButton)
	ON_LBN_DBLCLK(IDC_KEYWORDS, OnBnClickedEditkeywordButton)
	ON_LBN_SELCHANGE(IDC_KEYWORDS, OnLbnSelchangeKeywords)
	ON_COMMAND(ID_EDIT_FIND, &CSrRecordDialog::OnEditFind)
	ON_BN_CLICKED(IDC_CONDITION_BUTTON, &CSrRecordDialog::OnBnClickedConditionButton)
	ON_BN_CLICKED(IDC_SELECTDROPSOUND_BUTTON, &CSrRecordDialog::OnBnClickedSelectdropsoundButton)
	ON_BN_CLICKED(IDC_SELECTPICKUP_BUTTON, &CSrRecordDialog::OnBnClickedSelectpickupButton)
	ON_BN_CLICKED(IDC_SELECTPICKUPSOUND_BUTTON, &CSrRecordDialog::OnBnClickedSelectpickupButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DROPSOUND, OnDropDropSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DROPSOUND, OnDropDropSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_PICKUPSOUND, OnDropPickupSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_PICKUPSOUND, OnDropPickupSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropKeywords)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropKeywords)
	ON_BN_CLICKED(IDC_EDIT_DROPSOUND, &CSrRecordDialog::OnBnClickedEditDropsound)
	ON_BN_CLICKED(IDC_EDIT_PICKUPSOUND, &CSrRecordDialog::OnBnClickedEditPickupsound)
	ON_BN_CLICKED(IDC_BOUNDS, OnBnClickedBounds)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Default UI Fields
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrRecordDialog)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of Default UI Fields
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Tooltip Definitions
 *
 *=========================================================================*/
struct obrdtooltip_t {
	int ControlID;
	int StringID;
};

static obrdtooltip_t s_ToolTipInfo[] = {
	{ ID_SAVE_BUTTON,				IDS_TT_SAVE },
	{ ID_APPLY_BUTTON,				IDS_TT_APPLY },
	{ ID_CANCEL_BUTTON,				IDS_TT_CANCEL },
	{ IDC_KEYWORDS,					IDS_TT_KEYWORDS },
	{ IDC_ADDKEYWORD_BUTTON,		IDS_TT_KEYWORDS },
	{ IDC_EDITKEYWORD_BUTTON,		IDS_TT_KEYWORDS },
	{ IDC_DELKEYWORD_BUTTON,		IDS_TT_KEYWORDS },
	//{ IDC_BIPEDPARTS_BUTTON,		IDS_TT_EDITBIPED },
	//{ IDC_EDIT_SCRIPT,				IDS_TT_EDITSCRIPT },
	//{ IDC_SELECTSCRIPT_BUTTON,		IDS_TT_SELECTSCRIPT },
	{ IDC_EDIT_ENCHANTMENT,			IDS_TT_EDITENCHANT },
	//{ IDC_SELECTENCHANT_BUTTON,		IDS_TT_SELECTENCHANT },
	//{ IDC_SELECTCREATURE_BUTTON,	IDS_TT_SELECTCREATURE },
	//{ IDC_EDIT_CREATURETEMPLATE,	IDS_TT_EDITCREATURE },
	//{ IDC_EDIT_SOUND,				IDS_TT_EDITSOUND },
	//{ IDC_SELECTSOUND_BUTTON,		IDS_TT_SELECTSOUND },
	//{ IDC_EDIT_OPENSOUND,           IDS_TT_EDITSOUND },
	//{ IDC_EDIT_CLOSESOUND,          IDS_TT_EDITSOUND },
	//{ IDC_SELECTOPENSOUND_BUTTON,   IDS_TT_SELECTSOUND },
	//{ IDC_SELECTCLOSESOUND_BUTTON,  IDS_TT_SELECTSOUND },
	//{ IDC_EDIT_INGREDIANT,			IDS_TT_EDITINGREDIENT },
	//{ IDC_SELECTINGREDIANT_BUTTON,  IDS_TT_SELECTINGREDIENT },
	//{ IDC_MINATT_SLIDER,            IDS_TT_MINATTENUATION },
	//{ IDC_MAXATT_SLIDER,            IDS_TT_MAXATTENUATION },
	//{ IDC_STATATT_SLIDER,           IDS_TT_STATICATTENUATION },
	//{ IDC_STARTTIME_SLIDER,         IDS_TT_STARTTIME },
	//{ IDC_STOPTIME_SLIDER,          IDS_TT_STOPTIME },
	//{ IDC_COLOR,					IDS_TT_COLORBOX },
	{ 0, 0 }
};
/*===========================================================================
 *		End of Tooltip Definitions
 *=========================================================================*/



/*===========================================================================
 *
 * Class CSrRecordDialog Constructor
 *
 *=========================================================================*/
CSrRecordDialog::CSrRecordDialog (const int ID) : CFormView(ID)
{
  m_pRecordHandler   = NULL;
  m_pDlgHandler      = NULL;
  m_pEditorIDField   = NULL;
  m_pBipedPartsField = NULL;
  m_pScriptField     = NULL;
  m_pEnchantField    = NULL;
  m_pSoundField      = NULL;
  m_pModelField      = NULL;
  m_pIconField       = NULL;
  m_pSoundFileField  = NULL;
  m_pConditionField  = NULL;
  m_pPickupSoundField = NULL;
  m_pDropSoundField    = NULL;
  m_pBoundsField       = NULL;
  m_IgnoreConditions   = false;

  m_pMaleWorldModelField   = NULL;
  m_pMaleBipedModelField   = NULL;
  m_pFemaleWorldModelField = NULL;
  m_pFemaleBipedModelField = NULL;
  m_pMaleIconField         = NULL;
  m_pFemaleIconField       = NULL;

  m_pTabControl = NULL;

  m_pKeywordsField = NULL;

  m_NoActivateRecord = false;

  m_hAccelerator  = NULL;
  m_AcceleratorID = IDR_DEFAULT_RECORD_ACCEL;

  m_InitialSetData = true;

  m_ScriptType  = 0;
  m_EnchantType = 0;

  m_TitlePrefix = _T("Unknown");

  memset(&m_BoundsCopy, 0, sizeof(m_BoundsCopy));
}
/*===========================================================================
 *		End of Class CSrRecordDialog Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CSrRecordDialog::ClearControlData (void) 
{
  SetTitle(NULL);
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void Close (void);
 *
 *=========================================================================*/
void CSrRecordDialog::Close (void) 
{
  GetParentFrame()->DestroyWindow();
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::Close()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrRecordDialog::DoDataExchange(CDataExchange* pDX) 
{
  CFormView::DoDataExchange(pDX);
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrRecordDialog::GetControlData (void) {
  CSrIdRecord* pIdRecord;

  assert(m_EditInfo.pNewRecord != NULL);
  if (GetOutputRecord() == NULL) return;

	/* Update the editor id if required */
  if (m_EditInfo.HasUpdatedID || m_EditInfo.IsNew) {
    pIdRecord = SrCastClass(CSrIdRecord, GetOutputRecord());
    if (pIdRecord != NULL) pIdRecord->SetEditorID(m_EditInfo.NewEditorID);
  }

  UpdateEditorID();
  GetUIFieldData();
  SaveConditions();
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void GetUIFieldData (void);
 *
 *=========================================================================*/
void CSrRecordDialog::GetUIFieldData (void) {
  sruirecfields_t*	pFields;
  CButton*			pButton;
  CString			Buffer;
  CWnd*				pWnd;
  dword				Index;
  bool				Result;

  if (GetOutputRecord() == NULL) return;

  pFields = GetUIFields();
  if (pFields == NULL) return;

  for (Index = 0; pFields[Index].FieldID != SR_FIELD_NONE; ++Index) {
    if (pFields[Index].FieldID == SR_FIELD_FORMID) continue;
    if (pFields[Index].FieldID == SR_FIELD_EDITORID) continue;

    pWnd = GetDlgItem(pFields[Index].ControlID);

    if (pWnd == NULL)
	{	
		if (m_pTabControl != NULL) pWnd = m_pTabControl->FindChild(pFields[Index].ControlID);
		if (pWnd == NULL) continue;
	}
	
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      pWnd->GetWindowText(Buffer);

      Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
      if (!Result) continue;
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox))) {
      pWnd->GetWindowText(Buffer);
      
      Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
      if (!Result) continue;
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CButton))) {
      pButton = (CButton *) pWnd;

	  if ((pButton->GetButtonStyle() & BS_CHECKBOX) != 0)
	  {
		Buffer = (pButton->GetCheck() != 0) ? "true" : "false" ;
		Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
		if (!Result) continue;
	  }
	  else if (pButton == m_pBoundsField)
	  {
		  pButton->GetWindowText(Buffer);
		  Result = GetOutputRecord()->SetField(pFields[Index].FieldID, Buffer);
		  if (!Result) continue;
	  }
    }
	else if (pWnd->IsKindOf(RUNTIME_CLASS(CListBox)))
	{
		if (pFields[Index].FieldID == SR_FIELD_KEYWORDS) GetKeywords(pFields[Index], (CListBox *) pWnd);
	}
	
  }

}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::GetUIFieldData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - bool GetKeywords (FieldInfo, pListBox);
 *
 *=========================================================================*/
bool CSrRecordDialog::GetKeywords(sruirecfields_t& FieldInfo, CListBox* pListBox)
{
	CString			Buffer; 
	CSrIdRecord*	pRecord;
	CSrSubrecord*	pSubrecord;

	if (GetOutputRecord()->GetParent() == NULL) return false;

	pSubrecord = GetOutputRecord()->FindSubrecord(SR_NAME_KSIZ);

	if (pSubrecord == NULL) 
	{
		pSubrecord = GetOutputRecord()->AddNewSubrecord(SR_NAME_KSIZ);
		if (pSubrecord == NULL) return AddSrGeneralError("Failed to find or create KSIZ subrecord!");
		pSubrecord->InitializeNew();
	}
		
	CSrDwordSubrecord* pFormIdCount = SrCastClass(CSrDwordSubrecord, pSubrecord);
	if (pFormIdCount == NULL) return AddSrGeneralError("Invalid keyword count subrecord type!");

	pSubrecord = GetOutputRecord()->FindSubrecord(SR_NAME_KWDA);

	if (pSubrecord == NULL) 
	{
		pSubrecord = GetOutputRecord()->AddNewSubrecord(SR_NAME_KWDA);
		if (pSubrecord == NULL) return AddSrGeneralError("Failed to find or create KWDA subrecord!");
		pSubrecord->InitializeNew();
	}

	CSrFormidArraySubrecord* pFormIDs = SrCastClass(CSrFormidArraySubrecord, pSubrecord);
	if (pFormIDs == NULL) return AddSrGeneralError("Cannot add keywords to non-formid array!");
	pFormIDs->GetFormIDArray().Empty();

	for (int i = 0; i < pListBox->GetCount(); ++i)
	{
		pListBox->GetText(i, Buffer);
		if (Buffer.IsEmpty()) continue;
			
		pRecord = GetOutputRecord()->GetParent()->FindEditorID(Buffer);
		if (pRecord == NULL) continue;

		pFormIDs->GetFormIDArray().Add(pRecord->GetFormID());
	}

	pFormIdCount->SetValue(pFormIDs->GetFormIDArray().GetSize());
	return true;
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::GetKeywords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void InitToolTips (void);
 *
 *=========================================================================*/
void CSrRecordDialog::InitToolTips (void) {
  sruirecfields_t* pFields;
  CString	   Buffer;
  CWnd*		   pWnd;
  dword		   Index;
  int		   Result;

  pFields = GetUIFields();
  if (pFields == NULL) return;

  for (Index = 0; pFields[Index].FieldID != SR_FIELD_NONE; ++Index) {
    if (pFields[Index].ToolTipID == 0) continue;

    pWnd = GetDlgItem(pFields[Index].ControlID);
    if (pWnd == NULL) continue;

    Result = Buffer.LoadString(pFields[Index].ToolTipID);
    if (Result) m_ToolTip.AddTool(pWnd, Buffer);
  }

	/* Add more fields */
  for (Index = 0; s_ToolTipInfo[Index].ControlID != 0; ++Index) {
    pWnd = GetDlgItem(s_ToolTipInfo[Index].ControlID);
    if (pWnd == NULL) continue;

    Result = Buffer.LoadString(s_ToolTipInfo[Index].StringID);
    if (Result) m_ToolTip.AddTool(pWnd, Buffer);
  }

  m_ToolTip.SetMaxTipWidth(300);
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::InitToolTips()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDestroy ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnDestroy() {
  CFormView::OnDestroy();
  if (m_pDlgHandler != NULL) m_pDlgHandler->RemoveFrame(GetParentFrame());
 }
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnInitialUpdate (void) {

  CFormView::OnInitialUpdate();
  ResizeParentToFit(FALSE);

  m_ToolTip.Create(this, 0);
  InitToolTips();
  m_ToolTip.Activate(TRUE);
  m_ToolTip.SetDelayTime(TTDT_AUTOPOP, 30000);

  assert(m_pDlgHandler != NULL);

	/* Load the accelerator table if present */
  if (m_AcceleratorID != 0) {
    m_hAccelerator = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(m_AcceleratorID));
  }

  m_EditInfo.IsHandled  = false;
  m_EditInfo.NeedsIndex = false;

  CopyConditions();
   
  if (m_InitialSetData) SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - int OnPreSaveRecord (void);
 *
 *=========================================================================*/
int CSrRecordDialog::OnPreSaveRecord (void) {
  int Result;

	/* This shouldn't happen... */
  if (m_pDlgHandler == NULL) {
    AddSrGeneralError("Parent dialog handler for record dialog has not been set!");
    return (SR_RESULT_ERROR);
  }

         /* Update the editorid from the UI (do not save to record), check for validity */
  Result = UpdateEditorID();
  if (Result < 0) return (Result);
   
  Result = m_pDlgHandler->OnPreSaveRecord(m_EditInfo);
  if (Result < 0) return (Result);

  if (m_pRecordHandler != NULL && !m_EditInfo.IsNew && !m_EditInfo.IsCopy) {
    m_pRecordHandler->GetEventHandler().SendPreUpdateEvent(m_EditInfo.pOldRecord, SR_EVENTFLAG_NONOTIFYSOURCE, (long) this);
  }

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnPreSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - int OnPostSaveRecord (void);
 *
 *=========================================================================*/
int CSrRecordDialog::OnPostSaveRecord (void) {
  
  if (m_pDlgHandler != NULL) {
    m_pDlgHandler->OnPostSaveRecord(m_EditInfo);
  }

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnPostSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - int OnCancelEditRecord (void);
 *
 *=========================================================================*/
int CSrRecordDialog::OnCancelEditRecord (void) {
  
  if (m_pDlgHandler != NULL) {
    m_pDlgHandler->OnCancelEditRecord(m_EditInfo);
  }

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnCancelEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSave (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSave (void) {
  int Result;

  Result = OnPreSaveRecord();

  if (Result < 0) {
    if (Result != SR_RESULT_USERABORT) SrEditShowLastError("Failed to save the record changes!");
    return;
  }

  GetControlData();

  Result = OnPostSaveRecord();

  if (Result < 0) {
    SrEditShowLastError("Failed to save the record changes!");
    return;
  }

  GetDocument()->SetModifiedFlag(TRUE);
  Close();
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnCancel (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnCancel (void) {
  int Result;

  Result = OnCancelEditRecord();
  if (Result < 0) return;

  Close();
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnApply ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnApply() {
  int Result;

  Result = OnPreSaveRecord();

  if (Result < 0) {
    if (Result != SR_RESULT_USERABORT) SrEditShowLastError("Failed to apply the record changes!");
    return;
  }

  GetControlData();

  Result = OnPostSaveRecord();

  if (Result < 0) {
    SrEditShowLastError("Failed to apply the record changes!");
    return;
  }

	/* Reset the edit information */
  m_EditInfo.pOldRecord   = m_EditInfo.pNewRecord;
  m_EditInfo.pNewRecord   = NULL;
  m_EditInfo.HasUpdatedID = false;
  m_EditInfo.IsCopy       = false;
  m_EditInfo.IsRenamed    = false;
  m_EditInfo.IsNew        = false;
  m_EditInfo.IsHandled    = false;
  m_EditInfo.NeedsIndex   = false;

  GetDocument()->SetModifiedFlag(TRUE);

	/* Do another update */
  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnUpdate (pSender, lHint, pHint);
 *
 *=========================================================================*/
void CSrRecordDialog::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) {

  switch (lHint) {
    case SREDIT_DOC_HINT_UPDATERECORD:
	break;
    default:
	CFormView::OnUpdate(pSender, lHint, pHint);
	break;
   }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - BOOL PreTranslateMessage (pMsg);
 *
 *=========================================================================*/
BOOL CSrRecordDialog::PreTranslateMessage (MSG* pMsg) {
  int Result;

  m_ToolTip.RelayEvent(pMsg);

  if (m_hAccelerator != NULL) {
    if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST && m_hAccelerator != NULL) {
      Result = TranslateAccelerator(m_hWnd, m_hAccelerator, pMsg);
      if (Result != 0) return (Result);
    }
  }
	
  return CFormView::PreTranslateMessage(pMsg);
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::PreTranslateMessage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrRecordDialog::SetControlData (void) { 
  CSString Buffer;
  bool     Result;

  Result = GetInputRecord()->GetField(Buffer, SR_FIELD_EDITORID);

  if (Result)
    SetTitle(Buffer);
  else
    SetTitle("");

	/* Ignore invalid records */
  if (GetInputRecord() == NULL) {
    ClearControlData();
    return;
  }

  SetUIFieldData();
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void SetEditInfo (InputInfo);
 *
 *=========================================================================*/
void CSrRecordDialog::SetEditInfo (sreditrecinfo_t& InputInfo) {
  m_EditInfo.HasUpdatedID = InputInfo.HasUpdatedID;
  m_EditInfo.IsCopy       = InputInfo.IsCopy;
  m_EditInfo.IsNew        = InputInfo.IsNew;
  m_EditInfo.IsRenamed    = InputInfo.IsRenamed;
  m_EditInfo.NewEditorID  = InputInfo.NewEditorID;
  m_EditInfo.pNewRecord   = InputInfo.pNewRecord;
  m_EditInfo.pOldRecord   = InputInfo.pOldRecord;
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::SetEditInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void SetTitle (pEditorID);
 *
 *=========================================================================*/
void CSrRecordDialog::SetTitle (const SSCHAR* pEditorID) {
  CString Buffer;
  bool    IsActive = false;

  if (GetInputRecord() != NULL) IsActive = GetInputRecord()->IsActive();

  Buffer.Format("%s -- %s -- %s %s", m_pDlgHandler->GetTitle(), GetTitlePrefix(), pEditorID == NULL ? "" : pEditorID, IsActive ? "*" : "");

  //SetWindowText(Buffer);
  //SetInternalWindowText(GetParentFrame()->m_hWnd, Buffer);

  CWnd* pWnd = GetParentFrame();

  if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd))) {
    CFrameWnd* pFrame = (CFrameWnd *) pWnd;
    pFrame->SetTitle(Buffer);
    pFrame->SetWindowText(Buffer);
  }


}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - bool SetKeywords (FieldInfo, pListBox);
 *
 *=========================================================================*/
bool CSrRecordDialog::SetKeywords(sruirecfields_t& FieldInfo, CListBox* pListBox)
{
	CSrRecord*		pRecord;
	CString			Buffer;
	CSrFormidArraySubrecord* pKeywords;
	int				ListResult;

	if (GetInputRecord()->GetParent() == NULL || pListBox == NULL) return false;
			
	pListBox->ResetContent();

	pKeywords = SrCastClassNull(CSrFormidArraySubrecord, GetInputRecord()->FindSubrecord(SR_NAME_KWDA));
	if (pKeywords == NULL) return false;

	for (dword i = 0; i < pKeywords->GetFormIDArray().GetSize(); ++i)
	{
		srformid_t FormID = pKeywords->GetFormIDArray()[i];
		pRecord = GetInputRecord()->GetParent()->FindFormID(FormID);
		CSrIdRecord* pIdRecord = SrCastClassNull(CSrIdRecord, pRecord);

		if (pRecord == NULL || pIdRecord == NULL)
		{
			Buffer.Format("0x%08X", FormID);
			ListResult = pListBox->AddString(Buffer);
		}
		else
		{
			ListResult = pListBox->AddString(pIdRecord->GetEditorID());
		}

	}

	return true;
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::SetKeywords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - void SetUIFieldData (void);
 *
 *=========================================================================*/
void CSrRecordDialog::SetUIFieldData (void) {
  sruirecfields_t*  pFields;
  CButton*			pButton;
  CEdit*			pEdit;
  CComboBox*		pComboBox;
  CSString			Buffer;
  CWnd*				pWnd;
  dword				Index;
  bool				Result;

  pFields = GetUIFields();
  if (pFields == NULL) return;

  for (Index = 0; pFields[Index].FieldID != SR_FIELD_NONE; ++Index) {
    pWnd = this->GetDlgItem(pFields[Index].ControlID);

    if (pWnd == NULL) 
	{	
		if (m_pTabControl != NULL) pWnd = m_pTabControl->FindChild(pFields[Index].ControlID);
		if (pWnd == NULL) continue;
	}

		/* Save special fields for later use */
    switch (pFields[Index].FieldID) {
	  case SR_FIELD_KEYWORDS:	 m_pKeywordsField   = pWnd; break;
      case SR_FIELD_EDITORID:    m_pEditorIDField   = pWnd; break;
      case SR_FIELD_BIPED:       m_pBipedPartsField = pWnd; break;
      case SR_FIELD_SCRIPT:      m_pScriptField     = pWnd; break;
      case SR_FIELD_ENCHANTMENT: m_pEnchantField    = pWnd; break;
      case SR_FIELD_MODEL:       m_pModelField      = pWnd; m_pMaleBipedModelField = pWnd; break;
      case SR_FIELD_ICON:        m_pIconField       = pWnd; m_pMaleIconField = pWnd; break;
      case SR_FIELD_SOUNDFILE:   m_pSoundFileField  = pWnd; break;
      case SR_FIELD_SOUND:       m_pSoundField      = pWnd; break;
      case SR_FIELD_MODEL2:      m_pMaleWorldModelField   = pWnd; break;
      case SR_FIELD_MODEL3:      m_pFemaleBipedModelField = pWnd; break;
      case SR_FIELD_MODEL4:      m_pFemaleWorldModelField = pWnd; break;
      case SR_FIELD_ICON2:       m_pFemaleIconField = pWnd; break;
	  case SR_FIELD_CONDITIONCOUNT:   m_pConditionField   = pWnd; break;
	  case SR_FIELD_DROPSOUND:        m_pDropSoundField   = pWnd; break;
	  case SR_FIELD_PICKUPSOUND:      m_pPickupSoundField = pWnd; break;
	  case SR_FIELD_BOUNDS:  
		  m_pBoundsField = pWnd; 
		  CSrIdRecord* pIdRecord = SrCastClass(CSrIdRecord, GetInputRecord());
		  if (pIdRecord && pIdRecord->GetBoundsData()) m_BoundsCopy = *pIdRecord->GetBoundsData();
		  break;		  
    }

    Result = GetInputRecord()->GetField(Buffer, pFields[Index].FieldID);
    if (!Result) continue;

    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      pEdit = (CEdit *) pWnd;
      if (pFields[Index].MaxLength > 0) pEdit->SetLimitText(pFields[Index].MaxLength);
      pWnd->SetWindowText(Buffer);
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox))) {
      pComboBox = (CComboBox *) pWnd;
      FindComboBoxString(*pComboBox, Buffer, true);
     }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CButton))) {
      pButton = (CButton *) pWnd;

	  if ((pButton->GetButtonStyle() & BS_CHECKBOX) !=0 )
	  {
		pButton->SetCheck(tolower(Buffer[0]) == 't');

	  }
	  else 
	  {
		  pButton->SetWindowTextA(Buffer);
	  }

    }
	else if (pWnd->IsKindOf(RUNTIME_CLASS(CListBox))) {
		if (pFields[Index].FieldID == SR_FIELD_KEYWORDS) SetKeywords(pFields[Index], (CListBox *) pWnd);
	}

  }

}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::SetUIFieldData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CSrRecordDialog::UpdateEditorID (void) {
  CString Buffer;

  m_EditInfo.NewEditorID.Empty();
  m_EditInfo.HasUpdatedID = false;

  if (m_pEditorIDField != NULL) {
    m_pEditorIDField->GetWindowText(Buffer);
    m_EditInfo.NewEditorID = Buffer;

    SrPrepareEditorID(m_EditInfo.NewEditorID);
  }

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CSrRecordDialog::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnKillfocusEditorid ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnKillfocusEditorid() {
  CString  Buffer;
  CSString TempString;

  if (m_pEditorIDField != NULL) {
    m_pEditorIDField->GetWindowText(Buffer);
    TempString = Buffer;

    SrPrepareEditorID(TempString);

    m_pEditorIDField->SetWindowText(TempString);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnKillfocusEditorid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnBipedpartsButton ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnBipedpartsButton() {
	/*
  CString  Buffer;
  CSString TempString;
  bool     Result;
  dword    Parts;

  if (m_pBipedPartsField == NULL) return;

  m_pBipedPartsField->GetWindowText(Buffer);
  Parts = ParseObBipedFlagString(Buffer, ",");

  //Result = SrEditBipedParts(Parts);
  Result = SrEditBipedPartsList(Parts);
  
  MakeObBipedFlagString(TempString, Parts, ", ");
  m_pBipedPartsField->SetWindowText(TempString);
  */
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnBipedpartsButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditScript ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditScript() {
  CString    Buffer;
  CSrRecord* pRecord;

  if (m_pScriptField == NULL || m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_pScriptField->GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    //m_pDlgHandler->EditNewRecord(SR_NAME_SCPT);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditEnchantment ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditEnchantment() {
  CString    Buffer;
  CSrRecord* pRecord;

  if (m_pEnchantField == NULL || m_pDlgHandler == NULL || m_pDlgHandler == NULL) return;
  m_pEnchantField->GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(SR_NAME_ENCH);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditEnchantment()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectScript ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectScript() {
/*
  CString    Buffer;
  bool       Result;

  if (m_pScriptField == NULL) return;
  m_pScriptField->GetWindowText(Buffer);
  
  switch (m_ScriptType) {
    case SR_SCRIPTTYPE_OBJECT:      Result = m_pDlgHandler->SelectItemScript(Buffer); break;
    case SR_SCRIPTTYPE_QUEST:       Result = false; break;
    case SR_SCRIPTTYPE_MAGICEFFECT: Result = false; break;
    default:                        Result = false; break;
  }

  if (Result) m_pScriptField->SetWindowText(Buffer);
  */
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectEnchantment ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectEnchantment() 
{
	CString    Buffer;
	bool       Result;

	if (m_pEnchantField == NULL) return;
	m_pEnchantField->GetWindowText(Buffer);

	Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_ENCH, &CSrEnchRecord::s_FieldMap);

	/*
	switch (m_EnchantType) {
		case SR_ENCHTYPE_APPAREL: Result = m_pDlgHandler->SelectApparelEnchant(Buffer); break;
		case SR_ENCHTYPE_WEAPON:  Result = m_pDlgHandler->SelectWeaponEnchant(Buffer);  break;
		case SR_ENCHTYPE_STAFF:   Result = m_pDlgHandler->SelectStaffEnchant(Buffer);  break;
		case SR_ENCHTYPE_SCROLL:  Result = m_pDlgHandler->SelectScrollEnchant(Buffer); break;
		default:                  Result = false; break;
	} */

	if (Result) m_pEnchantField->SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectEnchantment()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
 *
 *=========================================================================*/
void CSrRecordDialog::OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {

  if (bActivate && pActivateView != NULL) {
    AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &m_pRecordHandler->GetUndoItems(), 0);
  }
  else if (pActivateView != NULL)  {
  }

  CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnActivateView()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CSrRecordDialog Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrRecordDialog::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  CSrRecord*      pRecord = (CSrRecord *) wParam;
  sreditrecinfo_t EditInfo;

  if (pRecord == NULL) return (0);
  if (m_NoActivateRecord) return (0);
  if (m_pDlgHandler == NULL) return (0);
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = false;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.pOldRecord   = pRecord;
  EditInfo.NewEditorID.Empty();

  m_pDlgHandler->EditRecord(EditInfo);

  return (0);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropScript (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropScript (NMHDR* pNotifyStruct, LRESULT* pResult) {
/*
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrScptRecord*     pScript;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (m_pScriptField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_SCPT) return;
  pScript = SrCastClass(CSrScptRecord, pRecord);
  if (pScript == NULL) return;
  if (pScript->GetType() != m_ScriptType) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) {
    m_pScriptField->SetWindowText(pScript->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
  */
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropEnchant (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropEnchant (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrEnchRecord*     pEnchant;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (m_pEnchantField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_ENCH) return;
  pEnchant = SrCastClass(CSrEnchRecord, pRecord);
  if (pEnchant == NULL) return;
  //if (pEnchant->GetType() != m_EnchantType) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_pEnchantField->SetWindowText(pEnchant->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditCut (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditCut (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Cut();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Cut();
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditCut()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditCopy (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditCopy (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Copy();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Copy();
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditPaste (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditPaste (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Paste();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Paste();
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditPaste()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditSelectAll (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditSelectAll (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->SetSel(0, pEdit->GetWindowTextLength());
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->SetSel(0, pRichEdit->GetWindowTextLength());
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
    CListCtrl* pList = (CListCtrl *) pWnd;

    for (int Index = 0; Index < pList->GetItemCount(); ++Index) {
      pList->SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
    }
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditSelectAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnUpdateEditSelectAll (pCmdUI);
 *
 *=========================================================================*/
void CSrRecordDialog::OnUpdateEditSelectAll (CCmdUI* pCmdUI) {
  CWnd* pWnd = GetFocus();
  bool  EnableCmd = false;

  if (pWnd != NULL) {
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
      EnableCmd = true;
    }
  }

  pCmdUI->Enable(EnableCmd);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnUpdateEditSelectAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnUpdateEditPaste (pCmdUI);
 *
 *=========================================================================*/
void CSrRecordDialog::OnUpdateEditPaste (CCmdUI* pCmdUI) {
  CWnd* pWnd = GetFocus();
  bool  EnableCmd = false;

  if (pWnd != NULL) {
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
      EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl))) {
      EnableCmd = false;
    }
  }

  pCmdUI->Enable(EnableCmd);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnUpdateEditPaste()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnUpdateEditCopy (pCmdUI);
 *
 *=========================================================================*/
void CSrRecordDialog::OnUpdateEditCopy (CCmdUI* pCmdUI) {
  CWnd* pWnd = GetFocus();
  bool  EnableCmd = false;

  if (pWnd != NULL) {
    if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
      CEdit* pEdit = (CEdit *) pWnd;
      int    StartSel;
      int    EndSel;
      pEdit->GetSel(StartSel, EndSel);
      if (EndSel > StartSel) EnableCmd = true;
    }
    else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
      CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
      if (pRichEdit->GetSelectionType() != SEL_EMPTY) EnableCmd = true;
    }
  }

  pCmdUI->Enable(EnableCmd);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnUpdateEditCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditUndo (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditUndo (void) {
  CWnd* pWnd = GetFocus();

  if (pWnd == NULL) return;

  if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) {
    CEdit* pEdit = (CEdit *) pWnd;
    pEdit->Undo();
  }
  else if (pWnd->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) {
    CRichEditCtrl* pRichEdit = (CRichEditCtrl *) pWnd;
    pRichEdit->Undo();
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - BOOL OnHelpInfo (pHelpInfo);
 *
 *=========================================================================*/
BOOL CSrRecordDialog::OnHelpInfo (HELPINFO* pHelpInfo) {
  
  m_pDlgHandler->OnHelp(this, pHelpInfo);

  return (true);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnHelpInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnHelp (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnHelp (void) 
{
  m_pDlgHandler->OnHelp(this, NULL);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropMaleWorldModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropMaleWorldModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pMaleWorldModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pMaleWorldModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropMaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropMaleBipedModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropMaleBipedModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pMaleBipedModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pMaleBipedModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropMaleBipedModel()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropFemaleWorldModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropFemaleWorldModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pFemaleWorldModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pFemaleWorldModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropFemaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropFemaleBipedModel (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropFemaleBipedModel (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pFemaleBipedModelField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pFemaleBipedModelField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropFemaleBipedModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropIcon (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropIcon (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pIconField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_IMAGE) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_TEXTURES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pIconField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropMaleIcon (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropMaleIcon (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pMaleIconField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_IMAGE) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_TEXTURES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pMaleIconField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropMaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropFemaleIcon (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropFemaleIcon (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pFemaleIconField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_IMAGE) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_TEXTURES)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pFemaleIconField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropFemaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropSoundFile (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropSoundFile (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

  *pResult = SRRESOURCE_DROPCHECK_ERROR;

  if (m_pSoundFileField == NULL) return;
  if (pDropInfo->pResourceFile == NULL) return;
  if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_SOUND) return;
  if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_SOUNDS)) return;

	/* If we're just checking or not */
  if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) {
    m_pSoundFileField->SetWindowText(pDropInfo->pResourceFile->GetCSName());    
  }

  *pResult = SRRESOURCE_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectModel (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectModel (void) {
  CString Buffer;

  if (m_pModelField == NULL) return;
  m_pModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectIcon (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectIcon (void) {
  CString Buffer;

  if (m_pIconField == NULL) return;
  m_pIconField->GetWindowText(Buffer);

  m_pDlgHandler->SelectIcon(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectSoundFile (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectSoundFile (void) {
  CString Buffer;

  if (m_pSoundFileField == NULL) return;
  m_pSoundFileField->GetWindowText(Buffer);

  m_pDlgHandler->SelectSoundFile(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectMaleIcon (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectMaleIcon (void) {
  CString Buffer;

  if (m_pMaleIconField == NULL) return;
  m_pMaleIconField->GetWindowText(Buffer);

  m_pDlgHandler->SelectIcon(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectMaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectFemaleIcon (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectFemaleIcon (void) {
  CString Buffer;

  if (m_pFemaleIconField == NULL) return;
  m_pFemaleIconField->GetWindowText(Buffer);

  m_pDlgHandler->SelectIcon(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectMaleIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectMaleWorldModel (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectMaleWorldModel (void) {
  CString Buffer;

  if (m_pMaleWorldModelField == NULL) return;
  m_pMaleWorldModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectMaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectMaleBipedModel (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectMaleBipedModel (void) {
  CString Buffer;

  if (m_pMaleBipedModelField == NULL) return;
  m_pMaleBipedModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectMaleBipedModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectFemaleWorldModel (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectFemaleWorldModel (void) {
  CString Buffer;

  if (m_pFemaleWorldModelField == NULL) return;
  m_pFemaleWorldModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectFemaleWorldModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectFemaleBipedModel (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectFemaleBipedModel (void) {
  CString Buffer;

  if (m_pFemaleBipedModelField == NULL) return;
  m_pFemaleBipedModelField->GetWindowText(Buffer);

  m_pDlgHandler->SelectModel(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectFemaleBipedModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnSelectsoundButton ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnSelectsoundButton() {
  CString    Buffer;
  bool       Result;

  if (m_pSoundField == NULL) return;
  m_pSoundField->GetWindowText(Buffer);

  Result = m_pDlgHandler->SelectSound(Buffer);
  if (Result) m_pSoundField->SetWindowText(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnSelectsoundButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnEditSound ();
 *
 *=========================================================================*/
void CSrRecordDialog::OnEditSound() {
  CString    Buffer;
  CSrRecord* pRecord;

  if (m_pSoundField == NULL) return;
  if (m_pRecordHandler == NULL || m_pDlgHandler == NULL) return;
  m_pSoundField->GetWindowText(Buffer);

  if (Buffer.IsEmpty()) {
    m_pDlgHandler->EditNewRecord(SR_NAME_SOUN);
  }
  else {
    pRecord = m_pRecordHandler->FindEditorID(Buffer);
    if (pRecord != NULL) m_pDlgHandler->EditRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnEditSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropSound (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropSound (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrIdRecord*       pSound;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (m_pSoundField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != SR_NAME_SOUN) return;
  pSound = SrCastClass(CSrIdRecord, pRecord);
  if (pSound == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_pSoundField->SetWindowText(pSound->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropDropSound (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropDropSound (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrIdRecord*       pSound;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (m_pDropSoundField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != SR_NAME_SNDR) return;
  pSound = SrCastClass(CSrIdRecord, pRecord);
  if (pSound == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) {
    m_pDropSoundField->SetWindowText(pSound->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropDropSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnDropPickupSound (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrRecordDialog::OnDropPickupSound (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrIdRecord*       pSound;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (m_pPickupSoundField == NULL) return;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != SR_NAME_SNDR) return;
  pSound = SrCastClass(CSrIdRecord, pRecord);
  if (pSound == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) {
    m_pPickupSoundField->SetWindowText(pSound->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnDropPickupSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnBnClickedAddkeywordButton (void);
 *
 *=========================================================================*/
 void CSrRecordDialog::OnBnClickedAddkeywordButton()
 {
	 CWnd*		pWnd;
	 CListBox*	pList;
	 CString    Buffer;
	 int		Index;
	 bool		Result;

	 pWnd = GetDlgItem(IDC_KEYWORDS);
	 if (pWnd == NULL) return;

	 pList = static_cast<CListBox *>(pWnd);
	 if (pList == NULL) return;

	 Result = m_pDlgHandler->SelectKeyword(Buffer);
	 if (!Result) return;
	 
	 Index = pList->AddString(Buffer);
	 pList->SetCurSel(Index);
 }
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnBnClickedAddkeywordButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnBnClickedEditkeywordButton (void);
 *
 *=========================================================================*/
 void CSrRecordDialog::OnBnClickedEditkeywordButton()
 {
	 CWnd*		pWnd;
	 CListBox*	pList;
	 CString	Buffer;
	 int		Index;
	 bool		Result;

	 pWnd = GetDlgItem(IDC_KEYWORDS);
	 if (pWnd == NULL) return;

	 pList = static_cast<CListBox *>(pWnd);
	 if (pList == NULL) return;

	 Index = pList->GetCurSel();
	 if (Index < 0) return;

	 pList->GetText(Index, Buffer);

	 Result = m_pDlgHandler->SelectKeyword(Buffer);
	 if (!Result) return;
	 
	 pList->DeleteString(Index);
	 if (!Buffer.IsEmpty()) Index = pList->AddString(Buffer);
	 pList->SetCurSel(Index);
 }
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnBnClickedEditkeywordButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnBnClickedDelkeywordButton (void);
 *
 *=========================================================================*/
 void CSrRecordDialog::OnBnClickedDelkeywordButton()
 {
	 CWnd*		pWnd;
	 CListBox*	pList;
	 int		Index;

	 pWnd = GetDlgItem(IDC_KEYWORDS);
	 if (pWnd == NULL) return;

	 pList = static_cast<CListBox *>(pWnd);
	 if (pList == NULL) return;

	 Index = pList->GetCurSel();
	 if (Index < 0) return;

	 pList->DeleteString(Index);
	 pList->SetCurSel(Index);
 }
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnBnClickedDelkeywordButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRecordDialog Event - void OnLbnSelchangeKeywords (void);
 *
 *=========================================================================*/
void CSrRecordDialog::OnLbnSelchangeKeywords()
{
	//OnBnClickedEditkeywordButton();
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::OnLbnSelchangeKeywords()
 *=========================================================================*/


srconditioninfo_t* CSrRecordDialog::CreateConditionInfo (CSrCtdaSubrecord* pCondition, CSrRecord* pRecord, const dword Index)
{
	srconditioninfo_t* pNewCond;
	CSrSubrecord*      pSubrecord;

	pNewCond = new srconditioninfo_t;
	pNewCond->Condition.Copy(pCondition);
	m_ConditionsCopy.Add(pNewCond);

	pSubrecord = pRecord->GetSubrecord(Index+1);
	if (pSubrecord == NULL) return pNewCond;

	if (pSubrecord->GetRecordType() == SR_NAME_CIS1)
	{
		pNewCond->pParam1 = new CSrStringSubrecord;
		pNewCond->pParam1->Initialize(SR_NAME_CIS1, 1);
		pNewCond->pParam1->Copy(pSubrecord);
	}
	else if (pSubrecord->GetRecordType() == SR_NAME_CIS2)
	{
		pNewCond->pParam2 = new CSrStringSubrecord;
		pNewCond->pParam2->Initialize(SR_NAME_CIS2, 1);
		pNewCond->pParam2->Copy(pSubrecord);
	}

	pSubrecord = pRecord->GetSubrecord(Index+2);
	if (pSubrecord == NULL) return pNewCond;

	if (pSubrecord->GetRecordType() == SR_NAME_CIS2 && pNewCond->pParam2 == NULL)
	{
		pNewCond->pParam2 = new CSrStringSubrecord;
		pNewCond->pParam2->Initialize(SR_NAME_CIS2, 1);
		pNewCond->pParam2->Copy(pSubrecord);
	}

	return pNewCond;
}


void CSrRecordDialog::CopyConditions (void) 
{
	if (GetInputRecord() == NULL) return;
	if (m_IgnoreConditions) return;

	for (dword i = 0; i < GetInputRecord()->GetNumSubrecords(); ++i)
	{
		CSrSubrecord* pSubrecord = GetInputRecord()->GetSubrecord(i);
		if (pSubrecord->GetRecordType() != SR_NAME_CTDA) continue;

		CSrCtdaSubrecord* pCondition = SrCastClassNull(CSrCtdaSubrecord, pSubrecord);
		if (pCondition != NULL) CreateConditionInfo(pCondition, GetInputRecord(), i);
	}

	m_ConditionsChanged = false;
}


void CSrRecordDialog::SaveConditions (void) 
{
	if (!m_ConditionsChanged) return;
	if (GetOutputRecord() == NULL) return;
	if (m_IgnoreConditions) return;

	GetOutputRecord()->DeleteSubrecords(SR_NAME_CTDA);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_CIS1);
	GetOutputRecord()->DeleteSubrecords(SR_NAME_CIS2);

	for (dword i = 0; i < m_ConditionsCopy.GetSize(); ++i)
	{
		srconditioninfo_t* pCondition = m_ConditionsCopy[i];
		
		if (pCondition != NULL) 
		{
			CSrSubrecord* pNewCond = GetOutputRecord()->AddNewSubrecord(SR_NAME_CTDA);
			if (pNewCond) pNewCond->Copy(&pCondition->Condition);

			if (pCondition->pParam1)
			{
				CSrSubrecord* pNewParam = GetOutputRecord()->AddNewSubrecord(SR_NAME_CIS1);
				if (pNewParam) pNewParam->Copy(pCondition->pParam1);
			}

			if (pCondition->pParam2)
			{
				CSrSubrecord* pNewParam = GetOutputRecord()->AddNewSubrecord(SR_NAME_CIS2);
				if (pNewParam) pNewParam->Copy(pCondition->pParam2);
			}
		}

	}

}


void CSrRecordDialog::OnEditFind()
{
	if (m_pDlgHandler) m_pDlgHandler->OpenFind();	
}


void CSrRecordDialog::OnBnClickedConditionButton()
{
	if (m_pConditionField == NULL) return;

	CSrConditionDlg ConditionDlg;
	int Result = ConditionDlg.DoModal(GetInputRecord(), &m_ConditionsCopy);
	if (Result == IDOK) m_ConditionsChanged = true;

	CString Buffer;
	Buffer.Format("%d", m_ConditionsCopy.GetSize());
	m_pConditionField->SetWindowText(Buffer);
}


void CSrRecordDialog::OnBnClickedSelectdropsoundButton()
{
	if (m_pDlgHandler == NULL || m_pDropSoundField == NULL) return;
	CString Buffer;

	m_pDropSoundField->GetWindowText(Buffer);
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap)) return;
	m_pDropSoundField->SetWindowText(Buffer);
}


void CSrRecordDialog::OnBnClickedSelectpickupButton()
{
	if (m_pDlgHandler == NULL || m_pPickupSoundField == NULL) return;
	CString Buffer;

	m_pPickupSoundField->GetWindowText(Buffer);
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap)) return;
	m_pPickupSoundField->SetWindowText(Buffer);
}


void CSrRecordDialog::OnBnClickedEditDropsound()
{
	if (m_pDlgHandler && m_pDropSoundField) m_pDlgHandler->EditRecordHelper(m_pDropSoundField, SR_NAME_SNDR);
}


void CSrRecordDialog::OnBnClickedEditPickupsound()
{
	if (m_pDlgHandler && m_pPickupSoundField) m_pDlgHandler->EditRecordHelper(m_pPickupSoundField, SR_NAME_SNDR);
}



/*===========================================================================
 *
 * Class CSrRecordDialog Event - void DropRecordHelper ();
 *
 *=========================================================================*/
int CSrRecordDialog::DropRecordHelper (srrldroprecords_t* pDropItems, CWnd* pWnd, const srrectype_t AllowedType, const int AllowedCount) {
	CSrRecord*	     pRecord;
	CSrIdRecord*     pIdRecord;
  
	if (pWnd == NULL || pDropItems == NULL) return SRRL_DROPCHECK_ERROR;
	if (pDropItems->pRecords == NULL) return SRRL_DROPCHECK_ERROR;
	if ((int) pDropItems->pRecords->GetSize() > AllowedCount) return SRRL_DROPCHECK_ERROR;

	pRecord = pDropItems->pRecords->GetAt(0);

		/* Ignore any invalid record types */
	if (pRecord->GetRecordType() != AllowedType) return SRRL_DROPCHECK_ERROR;
	pIdRecord = SrCastClass(CSrIdRecord, pRecord);
	if (pIdRecord == NULL) return SRRL_DROPCHECK_ERROR;

		/* If we're just checking or not */
	if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
	{
		pWnd->SetWindowText(pIdRecord->GetEditorID());
	}
	
	return SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrRecordDialog::DropRecordHelper()
 *=========================================================================*/


int CSrRecordDialog::DropRecordHelper (srrldroprecords_t* pDropItems, CListBox& ListBox, const srrectype_t AllowedType, const bool PermitDuplicates) {
	CSrRecord*	     pRecord;
	CSrIdRecord*     pIdRecord;
  
	if (pDropItems == NULL) return SRRL_DROPCHECK_ERROR;
	if (pDropItems->pRecords == NULL) return SRRL_DROPCHECK_ERROR;

	for (dword i = 0; i < pDropItems->pRecords->GetSize(); ++i)
	{
		pRecord = pDropItems->pRecords->GetAt(i);

			/* Ignore any invalid record types */
		if (pRecord->GetRecordType() != AllowedType) return SRRL_DROPCHECK_ERROR;
		pIdRecord = SrCastClass(CSrIdRecord, pRecord);
		if (pIdRecord == NULL) return SRRL_DROPCHECK_ERROR;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			if (PermitDuplicates)
			{
				ListBox.AddString(pIdRecord->GetEditorID());
			}
			else
			{
				if (ListBox.FindString(-1, pIdRecord->GetEditorID()) < 0) ListBox.AddString(pIdRecord->GetEditorID());
			}
		}
	}
	
	return SRRL_DROPCHECK_OK;
}


void CSrRecordDialog::OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	CSrRecord*	     pRecord;
	CSrIdRecord*     pIdRecord;
	CListBox*		 pListBox;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (m_pKeywordsField == NULL) return;
	if (!m_pKeywordsField->IsKindOf(RUNTIME_CLASS(CListBox))) return;

	if (pDropItems == NULL) return;
	if (pDropItems->pRecords == NULL) return;
	
	pListBox = (CListBox *) m_pKeywordsField;

	for (dword i = 0; i < pDropItems->pRecords->GetSize(); ++i)
	{
		pRecord = pDropItems->pRecords->GetAt(i);

			/* Ignore any invalid record types */
		if (pRecord->GetRecordType() != SR_NAME_KYWD) return;
		pIdRecord = SrCastClass(CSrIdRecord, pRecord);
		if (pIdRecord == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			if (pListBox->FindString(-1, pIdRecord->GetEditorID()) < 0) pListBox->AddString(pIdRecord->GetEditorID());
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;
}


void CSrRecordDialog::OnBnClickedBounds()
{
	CString Buffer;

	if (m_pBoundsField == NULL) return;
	if (!SrEditBoundsDlg(m_BoundsCopy)) return;

	Buffer.Format("(%hd, %hd, %hd) (%hd, %hd, %hd)", 
		m_BoundsCopy.X1, m_BoundsCopy.Y1, m_BoundsCopy.Z1,
		m_BoundsCopy.X2, m_BoundsCopy.Y2, m_BoundsCopy.Z2);
	m_pBoundsField->SetWindowText(Buffer);
}

