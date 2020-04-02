/*===========================================================================
 *
 * File:		Srfiletreedlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srFileTreeDlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrFileTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CSrFileTreeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Constructor
 *
 *=========================================================================*/
CSrFileTreeDlg::CSrFileTreeDlg(CWnd* pParent) : CDialog(CSrFileTreeDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CSrFileTreeDlg)
	//}}AFX_DATA_INIT

  //m_pEspFile = NULL;
  m_pTopGroup = NULL;
}
/*===========================================================================
 *		End of Class CSrFileTreeDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void CreateTree (void);
 *
 *=========================================================================*/
void CSrFileTreeDlg::CreateTree (void) {

	/* Clear the current contents */  
  m_FileTree.DeleteAllItems();
  if (m_pTopGroup == NULL) return;

  CreateTree(m_pTopGroup, m_FileTree.GetRootItem());
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::CreateTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void CreateTree (pTopGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::CreateTree (CSrGroup* pTopGroup, HTREEITEM hParent) {
  CSrBaseRecord* pBaseRecord;
  dword          Index;
  HTREEITEM      hFile;

	/* Add the file node */
  hFile = m_FileTree.InsertItem("Filename TODO", hParent);
    
	/* Add the file contents */
  for (Index = 0; Index < pTopGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pTopGroup->GetRecord(Index);
    if (pBaseRecord == NULL) continue;
    
    AddTreeRecord(pBaseRecord, hFile);
  }

}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::CreateTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeRecord (pBaseRecord, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeRecord (CSrBaseRecord* pBaseRecord, HTREEITEM hParent) {
  CSrGroup*       pGroup;
  CSrTypeGroup*   pTypeGroup;
  CSrGridGroup*   pGridGroup;
  CSrBlockGroup*  pBlockGroup;
  CSrFormIDGroup* pFormIDGroup;
  int test = pBaseRecord->GetMyClassType();
  
	/* Determine the type of the record */
  switch (pBaseRecord->GetMyClassType()) {
     case SRCLASS_CSrGroup:
        pGroup = SrCastClass(CSrGroup, pBaseRecord);
	AddTreeGroup(pGroup, hParent);
	break;
     case SRCLASS_CSrTypeGroup:
        pTypeGroup = SrCastClass(CSrTypeGroup, pBaseRecord);
	AddTreeTypeGroup(pTypeGroup, hParent);
	break;
     case SRCLASS_CSrFormIDGroup:
        pFormIDGroup = SrCastClass(CSrFormIDGroup, pBaseRecord);
	AddTreeFormIDGroup(pFormIDGroup, hParent);
	break;
     case SRCLASS_CSrBlockGroup:
        pBlockGroup = SrCastClass(CSrBlockGroup, pBaseRecord);
	AddTreeBlockGroup(pBlockGroup, hParent);
	break;
     case SRCLASS_CSrGridGroup:
        pGridGroup = SrCastClass(CSrGridGroup, pBaseRecord);
	AddTreeGridGroup(pGridGroup, hParent);
	break;
     case SRCLASS_CSrBaseRecord:
     case SRCLASS_CSrRecord:
     default:
	break;
  }

}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeGroupChildren (pGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeGroupChildren (CSrGroup* pGroup, HTREEITEM hParent) {
  CSrBaseRecord* pBaseRecord;
  dword          Index;
   
	/* Add the group contents */
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    if (pBaseRecord == NULL) continue;
    
    AddTreeRecord(pBaseRecord, hParent);
  }

}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeGroupChildren()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeGroup (CSrGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  Buffer.Format(_T("General Group -- %u records"), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeTypeGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeTypeGroup (CSrTypeGroup* pGroup, HTREEITEM hParent) {
  CString Buffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  Buffer.Format(_T("Type Group (%4.4s)-- %u records"), pGroup->GetContainsType().Name, pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeTypeGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeFormIDGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeFormIDGroup (CSrFormIDGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  CString   TypeBuffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  switch (pGroup->GetType()) {
    case SR_GROUP_WORLDCHILD: TypeBuffer = "World Child"; break;
    case SR_GROUP_CELLCHILD: TypeBuffer = "Cell Child"; break;
    case SR_GROUP_TOPICCHILD: TypeBuffer = "Topic Child"; break;
    case SR_GROUP_CELLPERSIST: TypeBuffer = "Cell Persist"; break;
    case SR_GROUP_CELLTEMP: TypeBuffer = "Cell Temp"; break;
    case SR_GROUP_CELLDISTANT: TypeBuffer = "Cell Distance"; break;
    default: TypeBuffer = "Unknown"; break;
  }
  
  Buffer.Format(_T("%s Group (0x%08X) -- %u records"), TypeBuffer, pGroup->GetParentFormID(), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeFormIDGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeBlockGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeBlockGroup (CSrBlockGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  CString   TypeBuffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  switch (pGroup->GetType()) {
    case SR_GROUP_INTCELL: TypeBuffer = "Interior Cell"; break;
    case SR_GROUP_INTSUBCELL: TypeBuffer = "Interior Sub-Cell"; break;
    default: TypeBuffer = "Unknown"; break;
  }

  Buffer.Format(_T("%s Group (%d) -- %u records"), TypeBuffer, pGroup->GetBlock(), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeBlockGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void AddTreeGridGroup (pGroup, hParent);
 *
 *=========================================================================*/
void CSrFileTreeDlg::AddTreeGridGroup (CSrGridGroup* pGroup, HTREEITEM hParent) {
  CString   Buffer;
  CString   TypeBuffer;
  HTREEITEM hItem;

  if (pGroup == NULL) return;

  switch (pGroup->GetType()) {
    case SR_GROUP_EXTCELL: TypeBuffer = "Exterior Cell"; break;
    case SR_GROUP_EXTSUBCELL: TypeBuffer = "Exterior Sub-Cell"; break;
    default: TypeBuffer = "Unknown"; break;
  }

  Buffer.Format(_T("%s Group (%d, %d) -- %u records"), TypeBuffer, pGroup->GetGridX(), pGroup->GetGridY(), pGroup->GetNumRecords());
  hItem = m_FileTree.InsertItem(Buffer, hParent);

  AddTreeGroupChildren(pGroup, hItem);
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::AddTreeGridGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrFileTreeDlg::DoDataExchange (CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(CSrFileTreeDlg)
  DDX_Control(pDX, IDC_TREECTRL, m_FileTree);
  //}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrFileTreeDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrFileTreeDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrFileTreeDlg::OnInitDialog() {
  CDialog::OnInitDialog();

  CreateTree();
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrFileTreeDlg::OnInitDialog()
 *=========================================================================*/
