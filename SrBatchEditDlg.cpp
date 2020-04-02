/*===========================================================================
 *
 * File:		Srbatcheditdlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srBatchEditDlg.h"
#include "dialogs/sreditdlghandler.h"
#include "sreditdoc.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

  IMPLEMENT_DYNCREATE(CSrBatchEditDlg, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Field Information
 *
 * Fields that will not be seen in the batch edit dialog.
 *
 *=========================================================================*/
srrecfieldid_t l_BadBatchFields[] = {
	SR_FIELD_FORMID,
	SR_FIELD_EDITORID,
	SR_FIELD_USERDATA,
	SR_FIELD_RECORDTYPE,
	SR_FIELD_ARMOR,		/* Use REALARMOR instead */
	SR_FIELD_NONE		/* Must be last */
};


bool l_IsBadBatchField (const srrecfieldid_t Field) {
  dword Index;

  for (Index = 0; l_BadBatchFields[Index] != SR_FIELD_NONE; ++Index) {
    if (l_BadBatchFields[Index] == Field) return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Field Information
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrBatchEditDlg, CSrRecordDialog)
	//{{AFX_MSG_MAP(CSrBatchEditDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FIELD_LIST, OnItemchangedFieldList)
	ON_NOTIFY(NM_KILLFOCUS, IDC_FIELD_LIST, OnKillfocusFieldList)
	ON_NOTIFY(NM_SETFOCUS, IDC_FIELD_LIST, OnSetfocusFieldList)
	ON_EN_CHANGE(IDC_BATCH_EDIT, OnChangeEditCtrl)
	ON_BN_CLICKED(ID_UNCHECKALL_BUTTON, OnUncheckAll)
	ON_BN_CLICKED(ID_CHECKALL_BUTTON, OnCheckAll)
	ON_WM_VSCROLL()
	ON_NOTIFY(NM_CLICK, IDC_FIELD_LIST, OnClickFieldList)
	ON_MESSAGE(ID_BATCHEDIT_MSG_UPDATE, OnEditUpdate)
	ON_EN_KILLFOCUS(IDC_BATCH_EDIT, OnKillfocusBatchEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Constructor
 *
 *=========================================================================*/	
CSrBatchEditDlg::CSrBatchEditDlg(CWnd* pParent)	: CSrRecordDialog(CSrBatchEditDlg::IDD) {
	//{{AFX_DATA_INIT(CSrBatchEditDlg)
	//}}AFX_DATA_INIT

	m_InitialSetData  = false;
	m_SavedFieldCount = 0;
	m_CurrentEditItem = -1;
	m_Initialized     = false;
	m_IsChanging      = false;
}
/*===========================================================================
 *		End of Class CSrBatchEditDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrBatchEditDlg::DoDataExchange(CDataExchange* pDX) {
	CSrRecordDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrBatchEditDlg)
	DDX_Control(pDX, IDC_FIELD_LIST, m_FieldList);
	DDX_Control(pDX, IDC_BATCH_EDIT, m_EditCtrl);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void AddEditRecords (Records);
 *
 *=========================================================================*/
void CSrBatchEditDlg::AddEditRecords (CSrRefRecordArray& Records) {
  dword Index;

  for (Index = 0; Index < Records.GetSize(); ++Index) {
    m_Records.Add(Records[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::AddEditRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void AddEditRecords (Records);
 *
 *=========================================================================*/
void CSrBatchEditDlg::AddEditRecords (CSrRecordArray& Records) {
  dword Index;

  for (Index = 0; Index < Records.GetSize(); ++Index) {
    m_Records.Add(Records[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::AddEditRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void AddFields (pRecord);
 *
 *=========================================================================*/
void CSrBatchEditDlg::AddFields (CSrRecord* pRecord) {
  const srrecfieldmap_t* pFieldMap;
  const srrecfield_t*	 pField;
  srbatchfieldinfo_t*	 pBatchInfo;
  dword			 Index;

	/* Enumerate all fields in the record */
  for (pFieldMap = pRecord->GetFieldMap(); pFieldMap != NULL; pFieldMap = pFieldMap->pBaseFieldMap) {
    assert(pFieldMap != pFieldMap->pBaseFieldMap);

    for (Index = 0; pFieldMap->pField[Index].GetMethod != NULL; ++Index) {
      pField = &pFieldMap->pField[Index];

		/* Don't add some fields */
      if (l_IsBadBatchField(pField->FieldID)) continue;
      if (pField->SetMethod == NULL) continue;
      if (pField->GetMethod == NULL) continue;

      pBatchInfo = new srbatchfieldinfo_t;
      m_Fields.Add(pBatchInfo);

      pBatchInfo->FieldID = pField->FieldID;
      pBatchInfo->Title   = pField->pName;
      
      (pRecord->*pField->GetMethod)(pBatchInfo->Value, 0);
    }
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::AddFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void ClearControlData (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::ClearControlData (void) {

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::ClearControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void CreateFieldArray (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::CreateFieldArray (void) {
  dword Index;

	/* Clear the current fields */
  m_Fields.Destroy();
  if (m_Records.GetSize() == 0) return;

  AddFields(m_Records[0]);

  for (Index = 1; Index < m_Records.GetSize(); ++Index) {
    RemoveMissingFields(m_Records[Index]);
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::CreateFieldArray()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void FillFieldList (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::FillFieldList (void) {
  srbatchfieldinfo_t*	pBatchInfo;
  dword			Index;
  int			ListIndex;

	/* Clear the current contents */
  m_FieldList.DeleteAllItems();

  for (Index = 0; Index < m_Fields.GetSize(); ++Index) {
    pBatchInfo = m_Fields[Index];

    ListIndex = m_FieldList.InsertItem(Index, "");
    if (ListIndex < 0) continue;

    m_FieldList.SetItemData(ListIndex, (long) pBatchInfo);

    m_FieldList.SetItemText(ListIndex, SR_BATCHEDIT_SUBITEM_FIELD, pBatchInfo->Title);
    m_FieldList.SetItemText(ListIndex, SR_BATCHEDIT_SUBITEM_VALUE, pBatchInfo->Value);
    m_FieldList.SetCheck(ListIndex, pBatchInfo->Save);
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::FillFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::GetControlData (void) {
  CSrRecord* pRecord;
  CSrRecord* pNewRecord;
  dword      Index;
  bool	     Result;

  UpdateEditCtrl(-1);
    
	/* Get information from the list */
  UpdateSaveFields();

	/* Update all records */
  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pRecord = m_Records[Index];

		/* Prepare the record for saving */
    pNewRecord = PrepareRecord(pRecord);

    Result = UpdateFields(pNewRecord);
    if (!Result) AddSrGeneralError("Some errors occurred setting fields for record 0x%08X!", pRecord->GetFormID());
    m_Records.SetAt(Index, pNewRecord);

		/* Update listeners */
    if (m_pRecordHandler != NULL) {
      m_pRecordHandler->GetEventHandler().SendUpdateEvent(pNewRecord, pRecord);
    }
  }

  if (m_pDlgHandler != NULL) {
    m_pDlgHandler->GetDocument()->SetModifiedFlag(TRUE);
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - bool IsEditRecord (pRecord);
 *
 *=========================================================================*/
bool CSrBatchEditDlg::IsEditRecord (CSrRecord* pRecord) {
  dword Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    if (m_Records[Index] == pRecord) return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::IsEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnInitialUpdate (void) {
  CSrRecordDialog::OnInitialUpdate();

  //m_EditCtrl.Create(ES_WANTRETURN | WS_CHILD | ES_AUTOHSCROLL, CRect(0, 0, 10, 12), this, ID_BATCH_EDITCTRL);
  //m_EditCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE, 0);

  //m_FieldList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
  m_FieldList.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
  m_FieldList.InsertColumn(0, "Field", LVCFMT_LEFT, 150, SR_BATCHEDIT_SUBITEM_FIELD);
  m_FieldList.InsertColumn(1, "Value", LVCFMT_LEFT, 200, SR_BATCHEDIT_SUBITEM_VALUE);

  m_EditInfo.pNewRecord = NULL;
  m_EditInfo.pOldRecord = NULL;

  CreateFieldArray();

	/* Check for no common fields to batch edit */
  if (m_Fields.GetSize() == 0) {
    AddSrGeneralError("There were no common fields in the %u records to batch edit!", m_Records.GetSize());
    Close();
    return;
  }
  
  SetTitle("");
  FillFieldList();

  m_FieldList.SetItem(0, 0, LVIF_STATE, "", 0, LVIS_SELECTED, LVIS_SELECTED, 0);
  UpdateEditCtrl(-1);

  SetControlData();

  m_Initialized = true;
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnSave (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnSave (void) {
  GetControlData();

	/* Close the window */
  Close();
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnSave()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnCancel (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnCancel (void) {
  Close();
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnCancel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnApply ();
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnApply() {

  GetControlData();

	/* Do another update */
  //SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnApply()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - CSrRecord* PrepareRecord (pRecord);
 *
 *=========================================================================*/
CSrRecord* CSrBatchEditDlg::PrepareRecord (CSrRecord* pRecord) {
  CSrRecord* pNewRecord;
	
  if (m_pRecordHandler == NULL) return (NULL);

	/* Do a preupdate */
  m_pRecordHandler->GetEventHandler().SendPreUpdateEvent(pRecord, SR_EVENTFLAG_NONOTIFYSOURCE, (long) this);    

	/* Ensure the record is active  */
  if (pRecord->IsActive()) {
    pNewRecord = pRecord;
  }
  else {
    pNewRecord = m_pRecordHandler->MakeRecordActivePriv(pRecord, true);
  }

	/* Create the undo event */
  m_pRecordHandler->CreateUndoUpdate(pRecord);
  
  return (pNewRecord);
}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::PrepareRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void RemoveMissingFields (pRecord);
 *
 *=========================================================================*/
void CSrBatchEditDlg::RemoveMissingFields (CSrRecord* pRecord) {
  srbatchfieldinfo_t*	pBatchInfo;
  const srrecfield_t*	pField;
  int			Index;

  for (Index = (int) m_Fields.GetSize() - 1; Index >= 0; --Index) {
    pBatchInfo = m_Fields[Index];

    pField = pRecord->FindField(pBatchInfo->FieldID);
    if (pField == NULL) m_Fields.Delete(Index);
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::RemoveMissingFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::SetControlData (void) { 

	/* TODO: Update data? */

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void SetTitle (pEditorID);
 *
 *=========================================================================*/
void CSrBatchEditDlg::SetTitle (const SSCHAR* pEditorID) {
  CString Buffer;

  Buffer.Format("%s -- Batch Edit %u Record%s", m_pDlgHandler->GetTitle(), GetNumRecords(), GetNumRecords() > 1 ? "s" : "");
  SetWindowText(Buffer);
  SetInternalWindowText(GetParentFrame()->m_hWnd, Buffer);
}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void UpdateFields (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::UpdateSaveFields (void) {
  srbatchfieldinfo_t*	pBatchInfo;
  int			Index;

  m_SavedFieldCount = 0;

  for (Index = 0; Index < m_FieldList.GetItemCount(); ++Index) {
    pBatchInfo = (srbatchfieldinfo_t *) m_FieldList.GetItemData(Index);
    if (pBatchInfo == NULL) continue;

    pBatchInfo->Save  = m_FieldList.GetCheck(Index) != 0;
    pBatchInfo->Value = m_FieldList.GetItemText(Index, SR_BATCHEDIT_SUBITEM_VALUE);
    ++m_SavedFieldCount;
  }

}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::UpdateSaveFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - bool UpdateFields (pRecord);
 *
 * Updates all checked fields for the given record.
 *
 *=========================================================================*/
bool CSrBatchEditDlg::UpdateFields (CSrRecord* pRecord) {
  srbatchfieldinfo_t*	pBatchInfo;
  dword			Index;
  bool			Result = true;
    
	/* Update each checked field */
  for (Index = 0; Index < m_Fields.GetSize(); ++Index) {
    pBatchInfo = m_Fields[Index];
    if (!pBatchInfo->Save) continue;

    Result &= pRecord->SetField(pBatchInfo->FieldID, pBatchInfo->Value);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::UpdateFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnItemchangedFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnItemchangedFieldList (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW *) pNMHDR;
  *pResult = 0;

  if (!m_Initialized) return;

  UpdateEditCtrl(pNMListView->iItem);
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnItemchangedFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Method - void UpdateEditCtrl (NewIndex);
 *
 *=========================================================================*/
void CSrBatchEditDlg::UpdateEditCtrl (const int NewIndex) {
  srbatchfieldinfo_t*	pBatchInfo;
  CString Buffer;
  CString Buffer1;
  CRect   ItemRect;
  CRect   ListRect;
  CSize   ScrollSize;
  BOOL    Result;
  int     XPos;
  int     YPos;
  int     Height;
  int     Width1;
  int     Width2;

  m_IsChanging = true;

  if (m_CurrentEditItem >= 0) {
    m_EditCtrl.GetWindowText(Buffer);
    m_FieldList.SetItemText(m_CurrentEditItem, SR_BATCHEDIT_SUBITEM_VALUE, Buffer);
    pBatchInfo = (srbatchfieldinfo_t *) m_FieldList.GetItemData(m_CurrentEditItem);
    pBatchInfo->Value = Buffer;
  }

  m_CurrentEditItem = NewIndex;

  if (m_CurrentEditItem < 0) {  
    m_EditCtrl.ShowWindow(SW_HIDE);
    m_EditCtrl.SetWindowText("");
    m_IsChanging = false;
    return;
  }

	/* Ensure the item is completely visible */
  m_FieldList.EnsureVisible(m_CurrentEditItem, FALSE);

	/* TODO: Need better control positioning */
  Width1 = m_FieldList.GetColumnWidth(0);
  Width2 = m_FieldList.GetColumnWidth(1);
  Result = m_FieldList.GetItemRect(m_CurrentEditItem, &ItemRect, LVIR_BOUNDS);
  m_FieldList.GetWindowRect(ListRect);
  ScreenToClient(ListRect);
  
  if (!Result) {
    XPos   = 0;
    YPos   = 0;
    Height = 20;
  }
  else {
    XPos    = ItemRect.left + Width1 + ListRect.left + 5;
    YPos    = ItemRect.top  + ListRect.top + 1;
    Height  = ItemRect.Height() + 2;
    Width2 -= 5;
  }

  if (XPos + Width2 >= ListRect.right) {
    Width2 = ListRect.right - XPos - 20;
  }
    
  if (YPos + 20 > ListRect.bottom || YPos < ListRect.top + 18) {
    m_CurrentEditItem = -1;
    m_EditCtrl.ShowWindow(SW_HIDE);
    m_EditCtrl.SetWindowText("");
    m_FieldList.SetFocus();
    m_IsChanging = false;
    return;
  }
  
  m_EditCtrl.SetWindowText(m_FieldList.GetItemText(m_CurrentEditItem, SR_BATCHEDIT_SUBITEM_VALUE));
  m_EditCtrl.SetWindowPos(&m_FieldList, XPos, YPos, Width2, Height, SWP_SHOWWINDOW | SWP_NOZORDER);

  m_EditCtrl.SetFocus();
  //m_EditCtrl.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
  m_IsChanging = false;
}
/*===========================================================================
 *		End of Class Method CSrBatchEditDlg::UpdateEditCtrl()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnKillfocusFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnKillfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnKillfocusFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnKillfocusBatchEdit (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnKillfocusBatchEdit (void) {
  UpdateEditCtrl(-1);
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnKillfocusBatchEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnSetfocusFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnSetfocusFieldList(NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;

  if (!m_Initialized) return;
  //m_IsChanging = true;

  //m_EditCtrl.SetFocus();
  //m_EditCtrl.RedrawWindow();

  //m_IsChanging = false;
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnSetfocusFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnChangeEditCtrl (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnChangeEditCtrl (void) {
  //if (m_IsChanging) return;
  //if (m_CurrentEditItem >= 0) m_FieldList.SetCheck(m_CurrentEditItem, TRUE);
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnChangeEditCtrl()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnUncheckAll (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnUncheckAll (void) {
  int Index;

  for (Index = 0; Index < m_FieldList.GetItemCount(); ++Index) {
    m_FieldList.SetCheck(Index, FALSE);
  }

}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnUncheckAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnCheckAll (void);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnCheckAll (void) {
  int Index;

  for (Index = 0; Index < m_FieldList.GetItemCount(); ++Index) {
    m_FieldList.SetCheck(Index, TRUE);
  }

}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnCheckAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnVScroll (nSBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  CSrRecordDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnVScroll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - void OnClickFieldList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrBatchEditDlg::OnClickFieldList (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;

  m_EditCtrl.SetFocus();
  m_EditCtrl.RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnClickFieldList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrBatchEditDlg Event - LRESULT OnEditUpdate (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrBatchEditDlg::OnEditUpdate (WPARAM wParam, LPARAM lParam) {
  UpdateEditCtrl(wParam);
  return (0);
}
/*===========================================================================
 *		End of Class Event CSrBatchEditDlg::OnEditUpdate()
 *=========================================================================*/

