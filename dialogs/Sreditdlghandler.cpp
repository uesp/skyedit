 /*===========================================================================
 *
 * File:		Sreditdlghandler.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sreditdlghandler.h"
#include "../sreditdoc.h"
#include "mainfrm.h"
#include "childfrmfix.h"
#include "childfrmscript.h"
#include "sredit.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Static class options member */
  srdlghandleroptions_t CSrEditDlgHandler::m_Options;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Dialog Creation Info
 *
 *=========================================================================*/
srdlgcreateinfo_t l_SrDlgCreateInfo[] = {
	{ &SR_NAME_GLOB, "Global",		     CSrGlobView::IDD,   RUNTIME_CLASS(CSrGlobView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes5Mod:SkyEdit/User_Interface/Global"),		_T("Global") },
	{ &SR_NAME_GMST, "Game Setting",     CSrGmstView::IDD,   RUNTIME_CLASS(CSrGmstView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes5Mod:SkyEdit/User_Interface/Game_Setting"),	_T("Game_Setting") },
	{ &SR_NAME_KYWD, "Keyword",		     CSrKywdView::IDD,   RUNTIME_CLASS(CSrKywdView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes5Mod:SkyEdit/User_Interface/Keyword"),		_T("Keyword") },
	{ &SR_NAME_MGEF, "Magic Effect",     CSrMgefView::IDD,   RUNTIME_CLASS(CSrMgefView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes5Mod:SkyEdit/User_Interface/MagicEffect"),	_T("Magic_Effect") },
	{ &SR_NAME_COBJ, "Recipes",		     CSrCobjView::IDD,   RUNTIME_CLASS(CSrCobjView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes5Mod:SkyEdit/User_Interface/Recipe"),		_T("Recipe") },
	{ &SR_NAME_WEAP, "Weapon",		     CSrWeapView::IDD,   RUNTIME_CLASS(CSrWeapView),  RUNTIME_CLASS(CChildFrameFix),	_T("Tes5Mod:SkyEdit/User_Interface/Weapon"),		_T("Weapon") },
	{ &SR_NAME_NULL, NULL, 0, NULL, NULL,	NULL,	NULL }	/* Must be last */
};


srdlgcreateinfo_t l_SrBatchEditCreateInfo = {
	&SR_NAME_NULL, "Batch Edit",	CSrBatchEditDlg::IDD,  RUNTIME_CLASS(CSrBatchEditDlg), RUNTIME_CLASS(CChildFrameFix), _T("Tes5Mod:SkyEdit/User_Interface/Batch_Edit"), NULL
};


srdlgcreateinfo_t l_SrFindCreateInfo = {
	&SR_NAME_NULL, "Find",	CSrFindDlg::IDD,  RUNTIME_CLASS(CSrFindDlg), RUNTIME_CLASS(CChildFrameFix), _T("Tes5Mod:SkyEdit/User_Interface/Find"), NULL
};
/*===========================================================================
 *		End of Dialog Creation Info
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Constructor
 *
 *=========================================================================*/
CSrEditDlgHandler::CSrEditDlgHandler () 
{
  m_pDocument = NULL;
}
/*===========================================================================
 *		End of Class CSrEditDlgHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - void Destroy (void);
 *
 *=========================================================================*/
void CSrEditDlgHandler::Destroy (void) {

	/* Force all currently open dialogs to close */  CloseAll();

}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool BatchEdit (Records);
 *
 * Opens a new batch edit window for the given group of records. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CSrEditDlgHandler::BatchEdit (CSrRefRecordArray& Records) {
  srdlginfo_t* pDlgInfo;

	/* Ignore if nothing to edit */
  if (Records.GetSize() == 0) return (false);

	/* Create the new window */
  pDlgInfo = CreateDlg(l_SrBatchEditCreateInfo);

  if (pDlgInfo == NULL) {
    SrEditShowLastError("Failed to create the batch edit dialog!");
    return (false);
  }

	/* Initialize the batch window */
  if (pDlgInfo->pRecordDlg != NULL && pDlgInfo->pRecordDlg->IsKindOf(RUNTIME_CLASS(CSrBatchEditDlg))) {
    CSrBatchEditDlg* pBatchEditDlg = (CSrBatchEditDlg *) pDlgInfo->pRecordDlg;
    pBatchEditDlg->AddEditRecords(Records);
  }

  pDlgInfo->pFrameWnd->InitialUpdateFrame(m_pDocument, TRUE);
  pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::BatchEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - void CloseAll (void);
 *
 * Closes all currently open dialogs. No record information is saved and
 * the user is not prompted.
 *
 *=========================================================================*/
void CSrEditDlgHandler::CloseAll (void) {
  srdlginfo_t* pDlgInfo;

	/* Pop dialogs before destroying to prevent objects from being deleted
	   twice from the CSrRecordDialog::OnDestroy() event */
  while (m_OpenDialogs.GetSize() > 0) {
    pDlgInfo = m_OpenDialogs.Remove((dword)0);
    Close(pDlgInfo);
    delete pDlgInfo;
  }

  m_OpenDialogs.Destroy();
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::CloseAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - dword CloseAll (pRecord, Source);
 *
 * Closes all currently open dialogs that are editing the given record.
 * No changes are saved and no prompts are given to the user. Returns
 * the number of dialogs closed.
 *
 *=========================================================================*/
dword CSrEditDlgHandler::CloseAll (CSrRecord* pRecord, const long Source) {
  srdlginfo_t* pDlgInfo;
  int          Index;
  dword	       Count = 0;

  for (Index = (int) m_OpenDialogs.GetSize() - 1; Index >= 0; --Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);

    if (pDlgInfo->pRecordDlg == NULL) continue;
    if (Source != 0 && Source == (long) pDlgInfo->pRecordDlg) continue;
    if (!pDlgInfo->pRecordDlg->IsEditRecord(pRecord)) continue;

    pDlgInfo = m_OpenDialogs.Remove(Index);
    Close(pDlgInfo);
    delete pDlgInfo;

    ++Count;
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::CloseAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - void Close (pDlgInfo);
 *
 *=========================================================================*/
void CSrEditDlgHandler::Close (srdlginfo_t* pDlgInfo) {
  pDlgInfo->pFrameWnd->CloseWindow();
  pDlgInfo->pFrameWnd->DestroyWindow();
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::Close()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* CreateDlg (CreateInfo);
 *
 * Creates a new dialog window according to the input creation information.
 * Returns the new dialog information or NULL on any error.
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::CreateDlg (srdlgcreateinfo_t& CreateInfo) {
  srdlginfo_t*     pDlgInfo;
  CCreateContext   Context;
  CFrameWnd*       pFrame;
  CSrRecordDialog* pRecordDlg = NULL;
  CWnd*		   pWnd;

	/* Initialize the context structure */
  Context.m_pCurrentDoc     = (CDocument *) m_pDocument;
  Context.m_pCurrentFrame   = NULL;
  Context.m_pNewDocTemplate = NULL;
  Context.m_pLastView       = NULL;
  Context.m_pNewViewClass   = CreateInfo.pViewClass;

	/* Create the dialog parent frame */  
  pFrame = (CFrameWnd *) CreateInfo.pFrameClass->CreateObject();
  ASSERT_KINDOF(CFrameWnd, pFrame);

	/* Create new form view from resource */
  pFrame->LoadFrame(CreateInfo.ResourceID, WS_OVERLAPPEDWINDOW, NULL, &Context);

  	/* Attempt to initialize the new view */
  pWnd = pFrame->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);

  if (pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CSrRecordDialog))) {
    pRecordDlg = (CSrRecordDialog *) pWnd;

    pRecordDlg->SetDlgHandler(this);
    pRecordDlg->SetRecordHandler(&m_pDocument->GetRecordHandler());
    pRecordDlg->SetTitlePrefix(CreateInfo.pTitlePrefix);
  }

	/* Create and initialize the new dialog info object */
  pDlgInfo = new srdlginfo_t;
  m_OpenDialogs.Add(pDlgInfo);

  pDlgInfo->pCreateInfo = &CreateInfo;
  pDlgInfo->pFrameWnd   = pFrame;
  pDlgInfo->pRecordDlg  = pRecordDlg;

  return (pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::CreateDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* CreateDlg (RecordType);
 *
 * Create a new dialog according to a record type. Returns NULL on any
 * error.
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::CreateDlg (const srrectype_t RecordType) {
  srdlginfo_t*       pDlgInfo;
  srdlgcreateinfo_t* pCreateInfo;

	/* Attempt to find a matching creation info */
  pCreateInfo = FindCreateInfo(RecordType);

  if (pCreateInfo == NULL) {
    AddSrGeneralError("Failed to create a new dialog for record type %4.4s!", RecordType.Name);
    return (NULL);
  }

	/* Create the new dialog */
  pDlgInfo = CreateDlg(*pCreateInfo);
  return (pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::CreateDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* CreateDlg (EditInfo);
 *
 * Creates a dialog according to the input record. Returns NULL on any
 * error. If a dialog for the given record is already open, the existing
 * dialog object is returned.
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::CreateDlg (sreditrecinfo_t& EditInfo) {
  srdlginfo_t* pDlgInfo;

	/* Ignore invalid input */
  if (EditInfo.pOldRecord == NULL) return (NULL);

	/* Search for an existing open dialog */
  pDlgInfo = FindOpenDlg(EditInfo.pOldRecord);
  if (pDlgInfo != NULL) return (pDlgInfo);

	/* Create a new dialog */
  pDlgInfo = CreateDlg(EditInfo.pOldRecord->GetRecordType());
  if (pDlgInfo == NULL) return (NULL);

	/* Initialize the record dialog object some more */
  if (pDlgInfo->pRecordDlg != NULL) {
    pDlgInfo->pRecordDlg->SetEditInfo(EditInfo);
  }

  return (pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::CreateDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool EditRecord (EditInfo);
 *
 * Display a dialog to edit the given record.  The current dialogs that are
 * open are checked to see if the record is already being edited.  If it 
 * is, the dialog is activated.  Otherwise a new dialog is created and
 * displayed to edit the record.
 *
 *=========================================================================*/
bool CSrEditDlgHandler::EditRecord (sreditrecinfo_t& EditInfo) {
  srdlginfo_t* pDlgInfo;

	/* Ignore invalid input */
  if (EditInfo.pOldRecord == NULL) return (true);

	/* See if record is already being edited */
  pDlgInfo = FindOpenDlg(EditInfo.pOldRecord);

  if (pDlgInfo != NULL) {
    pDlgInfo->pFrameWnd->ActivateFrame(SW_RESTORE);
    return (true);
  }  

	/* Create a new dialog to edit the item */
  pDlgInfo = CreateDlg(EditInfo);
  if (pDlgInfo == NULL) return (false);

  pDlgInfo->pFrameWnd->InitialUpdateFrame(m_pDocument, TRUE);
  pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);
 
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::EditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool EditRecord (FormID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::EditRecord (const srformid_t FormID) {
  CSrRecord* pRecord;

  pRecord = m_pDocument->GetRecordHandler().FindFormID(FormID);
  if (pRecord == NULL) return (false);
  
  return EditRecord(pRecord);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::EditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool EditRecord (pRecord);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::EditRecord (CSrRecord* pRecord) {
  sreditrecinfo_t EditInfo;

  if (pRecord == NULL) return (false);
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = false;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.pOldRecord   = pRecord;
  EditInfo.NewEditorID.Empty();

  return EditRecord(EditInfo);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::EditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool EditNewRecord (RecordType);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::EditNewRecord (const srrectype_t RecordType) {
  sreditrecinfo_t    EditInfo;

  if (m_pDocument == NULL) return (false);
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = true;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.NewEditorID.Empty();

  EditInfo.pOldRecord = m_pDocument->GetRecordHandler().PrepareNewRecord(RecordType);
  if (EditInfo.pOldRecord == NULL) return (false);

  return EditRecord(EditInfo);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::EditNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlgcreateinfo_t* FindCreateInfo (RecordType);
 *
 * Static class method to find a creation object for the mathcing record
 * type. Returns NULL if not found.
 *
 *=========================================================================*/
srdlgcreateinfo_t* CSrEditDlgHandler::FindCreateInfo (const srrectype_t RecordType) {
  srdlgcreateinfo_t* pCreateInfo;
  dword		     Index;

  for (Index = 0; *l_SrDlgCreateInfo[Index].pRecordType != SR_NAME_NULL; ++Index) {
    pCreateInfo = &l_SrDlgCreateInfo[Index];
    if (*pCreateInfo->pRecordType == RecordType) return (pCreateInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::FindCreateInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* FindOpenDlg (pRecordDlg);
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::FindOpenDlg (CSrRecordDialog* pRecordDlg) {
  srdlginfo_t* pDlgInfo;
  dword        Index;

	/* Ignore invalid input */
  if (pRecordDlg == NULL) return (NULL);

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pRecordDlg == pRecordDlg) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* FindOpenDlg (pRecord);
 *
 * Finds an open dialog for the given record. Returns NULL if not found.
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::FindOpenDlg (CSrRecord* pRecord) {
  srdlginfo_t* pDlgInfo;
  dword        Index;

	/* Ignore invalid input */
  if (pRecord == NULL) return (NULL);

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pRecordDlg == NULL) continue;
    if (pDlgInfo->pRecordDlg->GetInputRecord() == pRecord) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* FindOpenDlg (pFrameWnd);
 *
 * Find a currently open dialog according to its frame window. Returns NULL
 * if not found.
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::FindOpenDlg (CFrameWnd* pFrameWnd) {
  srdlginfo_t* pDlgInfo;
  dword        Index;

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pFrameWnd == pFrameWnd) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - srdlginfo_t* FindOpenDlg (pRuntimeClass);
 *
 * Find a currently open dialog according to its runtime class. Returns NULL
 * if not found.
 *
 *=========================================================================*/
srdlginfo_t* CSrEditDlgHandler::FindOpenDlg (CRuntimeClass* pRuntimeClass) {
  srdlginfo_t* pDlgInfo;
  dword        Index;

  if (pRuntimeClass == NULL) return (NULL);

  for (Index = 0; Index < m_OpenDialogs.GetSize(); ++Index) {
    pDlgInfo = m_OpenDialogs.GetAt(Index);
    if (pDlgInfo->pRecordDlg == NULL) continue;
    if (pDlgInfo->pRecordDlg->IsKindOf(pRuntimeClass)) return (pDlgInfo);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::FindOpenDlg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - const TCHAR* GetTitle (void);
 *
 *=========================================================================*/
const TCHAR* CSrEditDlgHandler::GetTitle (void) { 
   return m_pDocument ? m_pDocument->GetTitle() : ""; 
}
/*===========================================================================
 *		End of Class Method TCHAR* CSrEditDlgHandler::GetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnPreSaveRecord (EditInfo);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnPreSaveRecord (sreditrecinfo_t& EditInfo) {
  int Result;

  if (m_pDocument == NULL) return (SR_RESULT_ERROR);

	/* Check for a changed and valid editorid */
  Result = m_pDocument->GetRecordHandler().OnPreSaveCheckEditorID(EditInfo);
  if (Result < 0) return (Result);
   
       /* Prompt for a rename/copy if needed */
  if (Result == SR_RESULT_PROMPTRENAMECOPY) {
    Result = PromptRenameCopy(EditInfo);
    if (Result == SREDIT_RECORDPROMPT_CANCEL) return (SR_RESULT_USERABORT);

    if (Result == SREDIT_RECORDPROMPT_COPY) {
      EditInfo.IsRenamed  = false;
      EditInfo.IsCopy     = true;
      EditInfo.IsHandled  = false;
      EditInfo.NeedsIndex = true;
    }
    else if (Result == SREDIT_RECORDPROMPT_RENAME) {
      EditInfo.IsRenamed  = true;
      EditInfo.IsCopy     = false;
      EditInfo.IsHandled  = false;
      EditInfo.NeedsIndex = true;
    }
  }
   
	/* Finish the presave */
  Result =  m_pDocument->GetRecordHandler().OnPreSaveRecord(EditInfo);
  if (Result < 0) return (Result);

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnPreSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnPostSaveRecord (EditInfo);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnPostSaveRecord (sreditrecinfo_t& EditInfo) {

  if (m_pDocument != NULL) {
    m_pDocument->GetRecordHandler().OnPostSaveRecord(EditInfo);
  }

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnPostSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnCancelEditRecord (EditInfo);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnCancelEditRecord (sreditrecinfo_t& EditInfo) {

  if (m_pDocument != NULL) {
    m_pDocument->GetRecordHandler().OnCancelEditRecord(EditInfo);
  }

  return (SR_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnCancelEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool OpenFind (void);
 *
 * Opens a new find or re-activates an existing find window.
 *
 *=========================================================================*/
bool CSrEditDlgHandler::OpenFind (void) 
{
  srdlginfo_t* pDlgInfo;
  
	/* Find an existing open find window */
  pDlgInfo = FindOpenDlg(RUNTIME_CLASS(CSrFindDlg));

  if (pDlgInfo != NULL) 
  {
    pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);
    return (true);
  }

  	/* Create a new find window */
  pDlgInfo = CreateDlg(l_SrFindCreateInfo);

  if (pDlgInfo == NULL) 
  {
    SrEditShowLastError("Failed to create the find dialog!");
    return (false);
  }

	/* Initialize the batch window */
  if (pDlgInfo->pRecordDlg != NULL && pDlgInfo->pRecordDlg->IsKindOf(RUNTIME_CLASS(CSrFindDlg))) 
  {
    CSrFindDlg* pFindDlg = (CSrFindDlg *) pDlgInfo->pRecordDlg;
  }

  pDlgInfo->pFrameWnd->InitialUpdateFrame(m_pDocument, TRUE);
  pDlgInfo->pFrameWnd->ActivateFrame(SW_SHOWNORMAL);

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::OpenFind()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - void RemoveFrame (pFrameWnd);
 *
 * Simply removes the given frame window from the list of currently
 * opened ones.
 *
 *=========================================================================*/
void CSrEditDlgHandler::RemoveFrame (CFrameWnd* pFrameWnd) {
  srdlginfo_t*	pDlgInfo;

	/* Find the dialog by its frame window */
  pDlgInfo = FindOpenDlg(pFrameWnd);
  if (pDlgInfo == NULL) return;

  m_OpenDialogs.Delete(pDlgInfo);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::RemoveFrame()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectItemScript (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectItemScript (CString& EditorID) { 
  if (m_pDocument == NULL) return (false);
  return SrSelectItemScript(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectItemScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectActor (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectActor (CString& EditorID) { 
  if (m_pDocument == NULL) return (false);
  return SrSelectActor(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectActor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectApparelEnchant (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectApparelEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return SrSelectApparelEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectApparelEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectIngrediant (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectIngrediant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return SrSelectIngrediant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectIngrediant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectScrollEnchant (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectScrollEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return SrSelectScrollEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectScrollEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectSound (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectSound (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return SrSelectSound(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectStaffEnchant (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectStaffEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return SrSelectStaffEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectStaffEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectWeaponEnchant (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectWeaponEnchant (CString& EditorID) {
  if (m_pDocument == NULL) return (false);
  return SrSelectWeaponEnchant(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectWeaponEnchant()
 *=========================================================================*/


bool CSrEditDlgHandler::SelectComponent (CString& EditorID)
{
	if (m_pDocument == NULL) return (false);
	return SrSelectComponent(EditorID, &m_pDocument->GetRecordHandler()); 
}


bool CSrEditDlgHandler::SelectEquipSlot (CString& EditorID)
{
	if (m_pDocument == NULL) return (false);
	return SrSelectEquipSlot(EditorID, &m_pDocument->GetRecordHandler()); 
}


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectKeyword (EditorID);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectKeyword (CString& EditorID) 
{
  if (m_pDocument == NULL) return (false);
  return SrSelectKeyword(EditorID, &m_pDocument->GetRecordHandler()); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectKeyword()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectKeyword (EditorID, Filter);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectKeyword (CString& EditorID, const char* pFilter) 
{
  if (m_pDocument == NULL) return (false);
  return SrSelectKeyword(EditorID, &m_pDocument->GetRecordHandler(), pFilter); 
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectKeyword()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - int PromptRenameCopy (EditInfo);
 *
 * Standard prompt for rename/copy/cancel a record.
 *
 *=========================================================================*/
int CSrEditDlgHandler::PromptRenameCopy (sreditrecinfo_t& EditInfo) {
  CString  Buffer;
  //CSString EditorID;
  int      Result;

  //EditInfo.pOldRecord->GetField(EditorID, SR_FIELD_EDITORID);
  Buffer.Format(_T("The editorid has changed to %s.\r\n\r\nDo you wish to create a new copy or rename the record?"), EditInfo.NewEditorID);

  Result = ShowObPromptDlg ("Rename/Copy Record", Buffer, "Copy", "Rename", "Cancel");
  if (Result == 3) Result = 0;

  switch (Result) {
    case 1: return (SREDIT_RECORDPROMPT_COPY);
    case 2: return (SREDIT_RECORDPROMPT_RENAME);
  }

  return (SREDIT_RECORDPROMPT_CANCEL);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::PromptRenameCopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnListenAddRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnListenAddRecord (CSrListenEvent* pEvent) {
  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnListenAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnListenCleanRecord (CSrListenEvent* pEvent) {
  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnListenUpdateRecord (CSrListenEvent* pEvent) {
  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - int OnListenPreUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditDlgHandler::OnListenPreUpdateRecord (CSrListenEvent* pEvent) {

  if (!pEvent->IsFlagNoClosePreUpdate()) {

    if (pEvent->IsFlagNoNotifySource()) {
      CloseAll(pEvent->GetOldRecord(), pEvent->GetSource());
    }
    else {
      CloseAll(pEvent->GetOldRecord());
    }
  }

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnListenPreUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Event - bool OnHelp (pDialog, pHelpInfo);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::OnHelp (CSrRecordDialog* pDialog, HELPINFO* pHelpInfo) {
  srdlginfo_t*   pDlgInfo = NULL;
  CSString	 Buffer;

  if (pDialog != NULL) pDlgInfo = FindOpenDlg(pDialog);

	/* Ignore if web help is disabled */
  if (!m_Options.EnableWebHelp) return (false);
  
  if (m_Options.UseUESPWikiHelp) {
    if (pDlgInfo != NULL && pDlgInfo->pCreateInfo->pUESPPage != NULL) 
      Buffer = pDlgInfo->pCreateInfo->pUESPPage;
    else
      Buffer = m_Options.DefaultUESPPage;
  }
  else {
    if (pDlgInfo != NULL && pDlgInfo->pCreateInfo->pCSPage != NULL) 
      Buffer = pDlgInfo->pCreateInfo->pCSPage;
    else
      Buffer = m_Options.DefaultCSPage;

  }
 
  GetSrEditApp().OpenWebHelp(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Event CSrEditDlgHandler::OnHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectModel (pString);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectModel (const char* pString) {
  CString Buffer(SRRESOURCE_PATH_MESHES);

  Buffer += pString;

  GetSrEditApp().OpenResourceView(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectIcon (pString);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectIcon (const char* pString) {
  CString Buffer(SRRESOURCE_PATH_TEXTURES);

  Buffer += pString;

  GetSrEditApp().OpenResourceView(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDlgHandler Method - bool SelectSoundFile (pString);
 *
 *=========================================================================*/
bool CSrEditDlgHandler::SelectSoundFile (const char* pString) {
  CString Buffer(SRRESOURCE_PATH_SOUNDS);

  Buffer += pString;

  GetSrEditApp().OpenResourceView(Buffer);
  return (true);
}
/*===========================================================================
 *		End of Class Method CSrEditDlgHandler::SelectSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindListBoxItemData (ListBox, ItemData, SelectItem);
 *
 * Looks for a specific item data in the given listbox. Returns the list
 * index if found or -1 on any error. Selects the found item if the
 * SelectItem parameter is true.
 *
 *=========================================================================*/
int FindListBoxItemData (CListBox& ListBox, const dword ItemData, const bool SelectItem) {
  int Index;

  for (Index = 0; Index < ListBox.GetCount(); ++Index) {

    if (ListBox.GetItemData(Index) == ItemData) {
      if (SelectItem) ListBox.SetCurSel(Index);
      return (Index);
    }
  }

	/* Not found */
  if (SelectItem) ListBox.SetCurSel(-1);
  return (-1);
}
/*===========================================================================
 *		End of Function FindListBoxItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindComboBoxItemData (ComboBox, ItemData, SelectItem);
 *
 * Looks for a specific item data in the given combobox. Returns the list
 * index if found or -1 on any error. Selects the found item if the
 * SelectItem parameter is true.
 *
 *=========================================================================*/
int FindComboBoxItemData (CComboBox& ComboBox, const dword ItemData, const bool SelectItem) {
  int Index;

  for (Index = 0; Index < ComboBox.GetCount(); ++Index) {

    if (ComboBox.GetItemData(Index) == ItemData) {
      if (SelectItem) ComboBox.SetCurSel(Index);
      return (Index);
    }
  }

	/* Not found */
  if (SelectItem) ComboBox.SetCurSel(-1);
  return (-1);
}
/*===========================================================================
 *		End of Function FindComboBoxItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindComboBoxEffect (ComboBox, EffectType, SelectItem);
 *
 *=========================================================================*/
int FindComboBoxEffect (CComboBox& ComboBox, const srrectype_t EffectType, const bool SelectItem) {
/*
  obeffectdata_t* pEffectData;
  int             Index;

  for (Index = 0; Index < ComboBox.GetCount(); ++Index) {
    pEffectData = (obeffectdata_t *) ComboBox.GetItemData(Index);
    if (pEffectData == NULL) continue;

    if (*pEffectData->pName == EffectType) {
      if (SelectItem) ComboBox.SetCurSel(Index);
      return (Index);
    }
  }

  if (SelectItem) ComboBox.SetCurSel(-1); */
  return (-1);
}
/*===========================================================================
 *		End of Function FindComboBoxEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int FindComboBoxString (ComboBox, pString, SelectItem);
 *
 * Looks for a string in the given combobox. Returns the list index if
 * found or -1 on any error. Selects the found item if the SelectItem 
 * parameter is true.
 *
 *=========================================================================*/
int FindComboBoxString (CComboBox& ComboBox, const TCHAR* pString, const bool SelectItem) {
  int ListIndex;

  ListIndex = ComboBox.FindStringExact(-1, pString);
  if (SelectItem) ComboBox.SetCurSel(ListIndex);

  return (ListIndex);
}
/*===========================================================================
 *		End of Function FindComboBoxString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - long GetComboBoxSelItemData (ComboBox, Default);
 *
 *=========================================================================*/
dword GetComboBoxSelItemData (CComboBox& ComboBox, const dword Default) {
  int ListIndex;

  ListIndex = ComboBox.GetCurSel();
  if (ListIndex < 0) return (Default);

  return ComboBox.GetItemData(ListIndex);
}
/*===========================================================================
 *		End of Function GetComboBoxSelItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - long GetListBoxSelItemData (ListBox, Default);
 *
 *=========================================================================*/
dword GetListBoxSelItemData (CListBox& ListBox, const dword Default) {
  int ListIndex;

  ListIndex = ListBox.GetCurSel();
  if (ListIndex < 0) return (Default);

  return ListBox.GetItemData(ListIndex);
}
/*===========================================================================
 *		End of Function GetListBoxSelItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int SrAddComboBoxItem (ComboBox, pString, ItemData);
 *
 * Adds an item to a combobox. Returns the new item list index on success.
 *
 *=========================================================================*/
int SrAddComboBoxItem (CComboBox& ComboBox, const TCHAR* pString, const dword ItemData) {
  int ListIndex;

  ListIndex = ComboBox.AddString(pString);
  if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, ItemData);

  return (ListIndex);
}
/*===========================================================================
 *		End of Function SrAddComboBoxItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int SrAddListBoxItem (ListBox, pString, ItemData);
 *
 * Adds an item to a listbox. Returns the new item list index on success.
 *
 *=========================================================================*/
int SrAddListBoxItem (CListBox& ListBox, const TCHAR* pString, const dword ItemData) {
  int ListIndex;

  ListIndex = ListBox.AddString(pString);
  if (ListIndex >= 0) ListBox.SetItemData(ListIndex, ItemData);

  return (ListIndex);
}
/*===========================================================================
 *		End of Function SrAddListBoxItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrFillComboList (ComboBox, pStringValues);
 *
 * Fills the given combobox control with the given string values array.
 *
 *=========================================================================*/
bool SrFillComboList (CComboBox& ComboBox, const stringvalue_t* pStringValues, const dword Flags) {
  dword Index;
  bool  NoDuplicates = (Flags & SRE_FILLCOMBO_NODUPLICATES) != 0;
  int   ListIndex;

	/* Clear the combobox if required */
  if ((Flags & SRE_FILLCOMBO_FORCEEMPTY) != 0) ComboBox.ResetContent();

	/* Ignore invalid input */
  if (pStringValues == NULL) return (false);

	/* Include a NULL value if needed */
  if ((Flags & SRE_FILLCOMBO_INCLUDENULL) != 0) {
    ListIndex = ComboBox.AddString("");
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, 0);
  }

	/* Add all strings in the array */
  for (Index = 0; pStringValues[Index].pString != NULL; ++Index) {

		/* Check for duplicate items if required */
    if (NoDuplicates) {
      ListIndex = FindComboBoxItemData(ComboBox, pStringValues[Index].Value);
      if (ListIndex >= 0) continue;
    }

		/* Add the item */
    ListIndex = ComboBox.AddString(pStringValues[Index].pString);
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, pStringValues[Index].Value);
  }

  return (true);
}
/*===========================================================================
 *		End of Function SrFillComboList()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrFillEffectComboList (ComboBox, Flags, EffectFlagMask, InvalidEffectFlagMask);
 *
 * Fills the given combobox control with a list of magic effects.
 *
 *=========================================================================*/
bool SrFillEffectComboList (CComboBox& ComboBox, const dword Flags, const dword EffectFlagMask, const dword InvalidEffectFlagMask) {
/*
  dword Index;
  bool  NoDuplicates = (Flags & SRE_FILLCOMBO_NODUPLICATES) != 0;
  int   ListIndex;

  if ((Flags & SRE_FILLCOMBO_FORCEEMPTY) != 0) ComboBox.ResetContent();

  if ((Flags & SRE_FILLCOMBO_INCLUDENULL) != 0) {
    ListIndex = ComboBox.AddString("");
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, 0);
  }

  for (Index = 0; l_EffectData[Index].pName != NULL; ++Index) {
    if (EffectFlagMask != 0 && (l_EffectData[Index].DefaultFlags & EffectFlagMask) == 0) continue;
    if ((l_EffectData[Index].DefaultFlags & InvalidEffectFlagMask) != 0) continue;

    if (NoDuplicates) {
      ListIndex = FindComboBoxItemData(ComboBox, l_EffectData[Index].pName->Value);
      if (ListIndex >= 0) continue;
    }

    ListIndex = ComboBox.AddString(l_EffectData[Index].pDescription);
    if (ListIndex >= 0) ComboBox.SetItemData(ListIndex, (long) &l_EffectData[Index]);
  } */

  return (true);
}
/*===========================================================================
 *		End of Function SrFillEffectComboList()
 *=========================================================================*/

