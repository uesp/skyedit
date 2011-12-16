/*===========================================================================
 *
 * File:		Srresourceview.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srresourceview.h"
#include "dialogs/sreditdlghandler.h"


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

  IMPLEMENT_DYNCREATE(CSrResourceView, CFormView)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrResourceView, CFormView)
	//{{AFX_MSG_MAP(CSrResourceView)
	ON_NOTIFY(NM_DBLCLK, IDC_RESOURCE_TREE, OnDblclkResourceTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_RESOURCE_TREE, OnSelchangedResourceTree)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_BEGINDRAG, IDC_RESOURCE_TREE, OnBegindragResourceTree)
	ON_WM_CAPTURECHANGED()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Constructor
 *
 *=========================================================================*/
CSrResourceView::CSrResourceView() : CFormView(CSrResourceView::IDD) {
	//{{AFX_DATA_INIT(CSrResourceView)
	//}}AFX_DATA_INIT

  m_pCurrentInstance = NULL;
  m_pDragResource    = NULL;
  m_pDragImage       = NULL;
  m_IsDragging       = false;
  m_hGoodDropCursor  = NULL;
  m_EnablePreview    = true;

  m_pBsaFiles        = NULL;
  m_pResourceHandler = NULL;
  
  m_hBadDropCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_NO));
}
/*===========================================================================
 *		End of Class CSrResourceView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Destructor
 *
 *=========================================================================*/
CSrResourceView::~CSrResourceView() {

  if (m_pDragImage != NULL) {
    delete m_pDragImage;
    m_pDragImage = NULL;
  }

}
/*===========================================================================
 *		End of Class CSrResourceView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrResourceView::DoDataExchange(CDataExchange* pDX) {
	CFormView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CSrResourceView)
	DDX_Control(pDX, IDC_PREVIEW_RICHEDIT, m_PreviewText);
	DDX_Control(pDX, IDC_FILETIME, m_Filetime);
	DDX_Control(pDX, IDC_FILESIZE, m_Filesize);
	DDX_Control(pDX, IDC_FILENAME, m_Filename);
	DDX_Control(pDX, IDC_HBAR, m_HBar);
	DDX_Control(pDX, IDC_RESOURCE_TREE, m_ResourceTree);
	DDX_Control(pDX, IDC_PREVIEW_IMAGE, m_PreviewImage);
	//}}AFX_DATA_MAP
}
/*===========================================================================
 *		End of Class Method CSrResourceView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - HTREEITEM AddResourceTree (pFile, hParent);
 *
 *=========================================================================*/
HTREEITEM CSrResourceView::AddResourceTree (CSrResourceFile* pFile, HTREEITEM hParent) {
  HTREEITEM hNewItem;

  if (pFile == NULL) return (NULL);
  
  hNewItem = m_ResourceTree.InsertItem("", 1, 1, hParent);
  if (hNewItem == NULL) return (NULL);

  m_ResourceTree.SetItemData(hNewItem, (DWORD) pFile);
  pFile->SetUserDataPtr(hNewItem);

  UpdateResourceTree(pFile, hNewItem);
  return (hNewItem);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::AddResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void UpdateResourceTree (pFile, hItem);
 *
 *=========================================================================*/
void CSrResourceView::UpdateResourceTree (CSrResourceFile* pFile, HTREEITEM hItem) {
  CString Buffer;

  if (pFile == NULL) {
    m_ResourceTree.SetItemText(hItem, "");
    return;
  }

  if (pFile->GetNumInstances() > 1)
    Buffer.Format("%s (%u)", pFile->GetName(), pFile->GetNumInstances());
  else
    Buffer.Format("%s", pFile->GetName());

  m_ResourceTree.SetItemText(hItem, Buffer);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::UpdateResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_DefaultTreeCompare (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int CALLBACK l_DefaultTreeCompare (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  CSrResourceBase* pBase1 = (CSrResourceBase *) lParam1;
  CSrResourceBase* pBase2 = (CSrResourceBase *) lParam2;

  if (pBase1->IsFolder() && pBase2->IsFolder()) {
    CSrResourceFolder* pFolder1 = (CSrResourceFolder *) pBase1;
    CSrResourceFolder* pFolder2 = (CSrResourceFolder *) pBase2;
    return stricmp(pFolder1->GetName(), pFolder2->GetName());
  }
  else if (pBase1->IsFolder()) {
    return (-1);
  }
  else if (pBase2->IsFolder()) {
    return (1);
  }
  else {
    CSrResourceFile* pFile1 = (CSrResourceFile *) pBase1;
    CSrResourceFile* pFile2 = (CSrResourceFile *) pBase2;
    return stricmp(pFile1->GetName(), pFile2->GetName());
  }

  return (0);
}
/*===========================================================================
 *		End of Function CALLBACK l_DefaultTreeCompare()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void FillResourceTree (pFolder, hParent);
 *
 *=========================================================================*/
void CSrResourceView::FillResourceTree (CSrResourceFolder* pFolder, HTREEITEM hParent) {
  CSrResourceBase*   pBase;
  CSrResourceFolder* pNewFolder;
  CSrResourceFile*   pFile;
  MAPPOSITION	     Position;
  TVSORTCB	     SortInfo;
  HTREEITEM	     hNewItem;

  if (pFolder == NULL) return;

  pBase = pFolder->GetResources().GetFirstRecord(Position);

  while (pBase != NULL) {

    if (pBase->IsFolder()) {
      pNewFolder = (CSrResourceFolder *) pBase;
      hNewItem = m_ResourceTree.InsertItem(pNewFolder->GetName(), 0, 0, hParent);

      m_ResourceTree.SetItemData(hNewItem, (DWORD) pNewFolder);
      pNewFolder->SetUserDataPtr(hNewItem);

      FillResourceTree(pNewFolder, hNewItem);
    }
    else {
      pFile = (CSrResourceFile *) pBase;
      AddResourceTree(pFile, hParent);
    }

    pBase = pFolder->GetResources().GetNextRecord(Position);
  }

  SortInfo.hParent     = hParent;
  SortInfo.lParam      = (long) this;
  SortInfo.lpfnCompare = l_DefaultTreeCompare;
 
  m_ResourceTree.SortChildrenCB(&SortInfo);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::FillResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void FillResourceTree (void);
 *
 *=========================================================================*/
void CSrResourceView::FillResourceTree (void) {
  //m_ResourceTree.LockWindowUpdate();

	/* Clear the current tree */
  m_ResourceTree.DeleteAllItems();

  if (m_pResourceHandler != NULL) {
    FillResourceTree(&m_pResourceHandler->GetRootFolder(), m_ResourceTree.GetRootItem());
  }

  //m_ResourceTree.UnlockWindowUpdate();
}
/*===========================================================================
 *		End of Class Method CSrResourceView::FillResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CSrResourceView::PreCreateWindow(CREATESTRUCT& cs) {
  return CFormView::PreCreateWindow(cs);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::PreCreateWindow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CSrResourceView::OnInitialUpdate() {

  CFormView::OnInitialUpdate();
  ResizeParentToFit();

  this->SetScrollSizes(MM_TEXT, CSize(0, 0));

  m_Bitmaps[0].LoadBitmap(IDB_FOLDER);
  m_Bitmaps[1].LoadBitmap(IDB_FILE);
  m_ImageList.Create(16, 16, ILC_COLOR16, 64, 8);
  //m_ImageList.Create(IDB_FOLDER, 16, 10, RGB(0,0,0));
  m_ImageList.Add(&m_Bitmaps[0], (CBitmap *)NULL);
  m_ImageList.Add(&m_Bitmaps[1], (CBitmap *)NULL);
  m_ResourceTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

  m_PreviewImage.OnInitialUpdate();
  m_PreviewImage.ShowWindow(SW_HIDE);
  
  m_PreviewText.SetBackgroundColor(FALSE, RGB(214,209,204));
  m_PreviewText.LimitText(0);

  FillResourceTree();
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrResourceView::AssertValid() const {
  CFormView::AssertValid();
}


void CSrResourceView::Dump(CDumpContext& dc) const {
  CFormView::Dump(dc);
}


#endif
/*===========================================================================
 *		End of Class Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnDblclkResourceTree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrResourceView::OnDblclkResourceTree (NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnDblclkResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnSelchangedResourceTree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrResourceView::OnSelchangedResourceTree (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_TREEVIEW*     pNMTreeView = (NM_TREEVIEW *) pNMHDR;
  CSrResourceBase* pBase;
  CSrResourceFile* pFile = NULL;
  HTREEITEM        hTree;
  *pResult = 0;

  hTree = m_ResourceTree.GetSelectedItem();

  if (hTree == NULL) {
    m_pCurrentInstance = NULL;
  }
  else {
    pBase = (CSrResourceBase *) m_ResourceTree.GetItemData(hTree);
    if (pBase != NULL && !pBase->IsFolder()) pFile = (CSrResourceFile *) pBase;

    if (pFile == NULL)
      m_pCurrentInstance = NULL;
    else
      m_pCurrentInstance = pFile->GetMainInstance();
  }

  UpdateDisplayedInstance();
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnSelchangedResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CSrResourceView::OnSize(UINT nType, int cx, int cy) {
  CFormView::OnSize(nType, cx, cy);

	/* Update the available client size */
  CRect ClientRect;
  GetClientRect(&ClientRect);
  cx = ClientRect.Width();
  cy = ClientRect.Height();

  if (IsWindow(m_ResourceTree.m_hWnd)) {
    m_ResourceTree.SetWindowPos(NULL, 0, 0, 250, cy - 0, SWP_NOMOVE | SWP_NOZORDER);
  }

  if (IsWindow(m_HBar.m_hWnd)) {
    m_HBar.SetWindowPos(NULL, 250, 100, cx - 250, 1, SWP_NOZORDER);
  }

  if (IsWindow(m_PreviewText.m_hWnd)) {
    m_PreviewText.SetWindowPos(NULL, 250, 102, cx - 250, cy - 102, SWP_NOZORDER);
  }

  if (IsWindow(m_PreviewImage.m_hWnd)) {
    m_PreviewImage.SetWindowPos(NULL, 250, 102, cx - 250, cy - 102, SWP_NOZORDER);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void ClearDisplayedInstance (void);
 *
 *=========================================================================*/
void CSrResourceView::ClearDisplayedInstance (void) {
  m_Filename.SetWindowText("");
  m_Filesize.SetWindowText("");
  m_Filetime.SetWindowText("");

  ClearPreview();
}
/*===========================================================================
 *		End of Class Method CSrResourceView::ClearDisplayedInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void UpdateDisplayedInstance (void);
 *
 *=========================================================================*/
void CSrResourceView::UpdateDisplayedInstance (void) {
  CString  Buffer;
  FILETIME FileTime;

  if (m_pCurrentInstance == NULL) {
    ClearDisplayedInstance();
    return;
  }

  m_Filename.SetWindowText(m_pCurrentInstance->GetFilename());

  if (!m_pCurrentInstance->HasFilesize()) {
   m_Filetime.SetWindowText("n/a");
  }
  else {
    Buffer.Format("%I64d bytes", m_pCurrentInstance->GetFilesize());
    m_Filesize.SetWindowText(Buffer);
  }

  if (!m_pCurrentInstance->HasFiletime()) {
    m_Filetime.SetWindowText("n/a");
  }
  else {
    FileTime.dwHighDateTime = (dword) (m_pCurrentInstance->GetFiletime() >> 32);
    FileTime.dwLowDateTime  = (dword) (m_pCurrentInstance->GetFiletime() & 0xffffffff);

    CTime TmpTime(FileTime);
    m_Filetime.SetWindowText(TmpTime.Format("%c"));
  }

  PreviewInstance(m_pCurrentInstance);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::UpdateDisplayedInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void ClearPreview (void);
 *
 *=========================================================================*/
void CSrResourceView::ClearPreview (void) {
  m_PreviewText.ShowWindow(SW_HIDE);
  m_PreviewImage.ShowWindow(SW_HIDE);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::ClearPreview()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void PreviewText (pInstance, PreviewInfo);
 *
 *=========================================================================*/
void CSrResourceView::PreviewText (CSrResourceInstance* pInstance, srrespreviewinfo_t& PreviewInfo) {
  CSrFile  File;
  CString  Buffer;
  long     Filesize;
  bool     Result;
  
  Result = File.Open(PreviewInfo.Filename, "rb");

  if (!Result) {
    Buffer.Format("Error trying to read the text file '%s'!", PreviewInfo.Filename);
    m_PreviewText.SetWindowText(Buffer); 
    m_PreviewText.ShowWindow(SW_SHOW);
    return;
  }

  if (PreviewInfo.Filesize > 256000) {
    Buffer.Format("File size of %I64d bytes too large to preview!", PreviewInfo.Filesize);
    m_PreviewText.SetWindowText(Buffer); 
    m_PreviewText.ShowWindow(SW_SHOW);
    return;
  }

	/* Jump to start of data */
  Result = File.Seek((long)PreviewInfo.StartOffset);

  if (!Result) {
    Buffer.Format("Error trying to read the text file '%s'!", PreviewInfo.Filename);
    m_PreviewText.SetWindowText(Buffer); 
    m_PreviewText.ShowWindow(SW_SHOW);
    return;
  }

  Filesize = (long) PreviewInfo.Filesize;
  Result   = File.Read(Buffer.GetBuffer(Filesize + 10), Filesize);
  Buffer.ReleaseBuffer(Filesize);
  File.Close();

  m_PreviewText.SetWindowText(Buffer);

  m_PreviewText.SetSel(0, 0);
  m_PreviewText.ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::PreviewText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void PreviewImage (pInstance, PreviewInfo);
 *
 *=========================================================================*/
void CSrResourceView::PreviewImage (CSrResourceInstance* pInstance, srrespreviewinfo_t& PreviewInfo) {
  FILE* pFile;

  if (PreviewInfo.PlainFile) {
    m_PreviewImage.Load(PreviewInfo.Filename);
  }
  else {
    pFile = fopen(PreviewInfo.Filename, "rb");

    if (pFile != NULL) {
      m_PreviewImage.Load(pFile, (long)PreviewInfo.Filesize, (long)PreviewInfo.StartOffset);
      fclose(pFile);
    }
  }

  m_PreviewImage.ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::PreviewImage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void PreviewUnknown (pInstance, PreviewInfo);
 *
 *=========================================================================*/
void CSrResourceView::PreviewUnknown (CSrResourceInstance* pInstance, srrespreviewinfo_t& PreviewInfo) {

  m_PreviewText.SetWindowText("Unknown file type!");

  m_PreviewText.ShowWindow(SW_SHOW);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::PreviewUnknown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void PreviewInstance (pInstance);
 *
 *=========================================================================*/
void CSrResourceView::PreviewInstance (CSrResourceInstance* pInstance) {
  srrespreviewinfo_t PreviewInfo;
  CSString           TmpFilename;
  bool	             Result;
  int		     Type;

  ClearPreview();
  if (pInstance == NULL || !m_EnablePreview) return;

  PreviewInfo.Filename    = pInstance->GetFullFilenameAbs();
  PreviewInfo.Filesize    = pInstance->GetFilesize();
  PreviewInfo.StartOffset = 0;
  PreviewInfo.pInstance   = pInstance;

	/* Use a temporary file for BSA resources */
	/* TODO: Reuse temporary output files */
	/* TODO: Read directly from BSA? */
  if (pInstance->GetBsaRecord() != NULL) {
    //TmpFilename = _tempnam("", "bsatmp");
    //Result = pInstance->GetBsaRecord()->SaveTempFile(TmpFilename, "tmpfiles\\");
    Result = pInstance->GetBsaRecord()->GetExistingTempFile(TmpFilename, "tmpfiles\\");
    if (!Result) return;
    //PreviewInfo.StartOffset = (int64)(uint64) pInstance->GetBsaRecord()->GetOffset();
    //PreviewInfo.Filename    = pInstance->GetBsaRecord()->GetParentFile()->GetFilename();
    PreviewInfo.Filename    = TmpFilename;
    PreviewInfo.StartOffset = 0;
    PreviewInfo.PlainFile   = true;
  }
  else {
	/* TODO: Update size from current file */
    PreviewInfo.Filesize  = pInstance->GetFilesize();
    PreviewInfo.PlainFile = true;
  }

  Type = pInstance->GetResourceType();

  switch (Type) {
    case SR_RESOURCETYPE_TEXT:
    case SR_RESOURCETYPE_HTML:
    case SR_RESOURCETYPE_XML:
        PreviewText(pInstance, PreviewInfo);
	break;
   case SR_RESOURCETYPE_IMAGE:
        PreviewImage(pInstance, PreviewInfo);
	break;
    default:
        PreviewUnknown(pInstance, PreviewInfo);
	break;
  }

}
/*===========================================================================
 *		End of Class Method CSrResourceView::PreviewInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrResourceView::OnContextMenu (CWnd* pWnd, CPoint Point) {
	
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnBegindragResourceTree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrResourceView::OnBegindragResourceTree (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_TREEVIEW*     pNMTreeView = (NM_TREEVIEW *) pNMHDR;
  CSrResourceBase* pBase;
  HTREEITEM        hSelItem;

  hSelItem = pNMTreeView->itemNew.hItem;
  if (hSelItem == NULL) return;

  m_ResourceTree.Select(hSelItem, TVGN_CARET);

  pBase = (CSrResourceBase *) m_ResourceTree.GetItemData(hSelItem);
  if (pBase == NULL || pBase->IsFolder()) return;
  m_pDragResource = (CSrResourceFile *) pBase;
  if (m_pDragResource == NULL) return;

  m_hGoodDropCursor = GetCursor();
  SetCursor(m_hBadDropCursor);

  m_pDragImage = m_ResourceTree.CreateDragImage(hSelItem);
  if (m_pDragImage == NULL) return;

  m_IsDragging    = true;
  m_LastDropValid = false;

  m_pDragImage->BeginDrag(0, CPoint(10, 10));
  m_pDragImage->DragEnter(GetDesktopWindow(), pNMTreeView->ptDrag);

  SetCapture();
	
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnBegindragResourceTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - void CleanupDrag (void);
 *
 *=========================================================================*/
void CSrResourceView::CleanupDrag (void) {

  if (!m_IsDragging) return;

  if (m_pDragImage != NULL) {
    delete m_pDragImage;
    m_pDragImage = NULL;
  }

  m_pDragResource = NULL;
  m_IsDragging    = false;
  m_LastDropValid = false;
}
/*===========================================================================
 *		End of Class Method CSrResourceView::CleanupDrag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnCaptureChanged (pWnd);
 *
 *=========================================================================*/
void CSrResourceView::OnCaptureChanged(CWnd *pWnd) {
  CFormView::OnCaptureChanged(pWnd);

  CleanupDrag();

}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnCaptureChanged()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnLButtonUp (nFlags, Point);
 *
 *=========================================================================*/
void CSrResourceView::OnLButtonUp (UINT nFlags, CPoint Point) {

  if (!m_IsDragging) {
    CFormView::OnLButtonUp(nFlags, Point);
    return;
  }  

  CPoint MousePt(Point);
  ClientToScreen(&MousePt);

  m_pDragImage->DragLeave(GetDesktopWindow());
  m_pDragImage->EndDrag();

	/* Drop the resource if required */
  if (m_LastDropValid) {
    SendDropNotify(MousePt, ID_SRRESOURCE_DROP);
  }

  ReleaseCapture();
  CleanupDrag();
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnLButtonUp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnMouseMove (nFlags, Point);
 *
 *=========================================================================*/
void CSrResourceView::OnMouseMove (UINT nFlags, CPoint Point) {
  int    Result;

  if (!m_IsDragging) {
    CFormView::OnMouseMove(nFlags, Point);
    return;
  }

  CPoint MousePt(Point);
  ClientToScreen(&MousePt);

  m_pDragImage->DragMove(MousePt);
  m_pDragImage->DragShowNolock(false);

	/* Check the current drop window */
  Result = SendDropNotify(MousePt, ID_SRRESOURCE_CHECKDROP);

  if (Result == SRRESOURCE_DROPCHECK_OK) {
    m_LastDropValid = true;
    SetCursor(m_hGoodDropCursor);
  }
  else if (Result == SRRESOURCE_DROPCHECK_NOCHANGE) {
	/* do nothing */   
  }
  else {
    m_LastDropValid = false;
    SetCursor(m_hBadDropCursor);
  }

  m_pDragImage->DragShowNolock(true);
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnMouseMove()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - int SendDropNotify (Point, MessageID);
 *
 *=========================================================================*/
int CSrResourceView::SendDropNotify (CPoint Point, const int MessageID) {
  srresourcedropinfo_t NotifyData;
  CWnd*	               pDropWnd;
  CWnd*		       pParentWnd = NULL;
  int		       Result = 0;

  	/* Get the CWnd pointer of the window that is under the given location */
  pDropWnd = WindowFromPoint(Point);
  if (pDropWnd == NULL) return (SRRESOURCE_DROPCHECK_ERROR);
  if (pDropWnd == this) return (SRRESOURCE_DROPCHECK_ERROR);

	/* Don't drag outside this application */
  dword Test1 = GetWindowThreadProcessId(m_hWnd, NULL);
  dword Test2 = GetWindowThreadProcessId(pDropWnd->m_hWnd, NULL);
  if (Test1 != Test2) return (SRRESOURCE_DROPCHECK_ERROR);
 
	/* Don't do anything if the window has not changed */
  if (m_pLastDropWnd == pDropWnd && MessageID != ID_SRRESOURCE_DROP) return (SRRESOURCE_DROPCHECK_NOCHANGE);

  m_pLastDropWnd = pDropWnd;
  if (pDropWnd == NULL) return (SRRESOURCE_DROPCHECK_ERROR);

	/* Send a notify message to the potential drop window */
  NotifyData.Notify.code     = MessageID;
  NotifyData.Notify.hwndFrom = pDropWnd->m_hWnd;
  NotifyData.Notify.idFrom   = pDropWnd->GetDlgCtrlID();
  NotifyData.pResourceFile   = m_pDragResource;

  pParentWnd = pDropWnd->GetParent();
  if (pParentWnd == NULL) return (SRRESOURCE_DROPCHECK_ERROR);

  Result = pParentWnd->SendMessage(WM_NOTIFY, NotifyData.Notify.idFrom, (LPARAM) &NotifyData);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::SendDropNotify()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Method - bool SelectResource (pResource);
 *
 *=========================================================================*/
bool CSrResourceView::SelectResource (const char* pResource) {
  CSrResourceBase* pBase;
  HTREEITEM        hTree;

  if (m_pResourceHandler == NULL) return (false);
  
  pBase = m_pResourceHandler->FindName(pResource);
  if (pBase == NULL) return (false);

  hTree = (HTREEITEM) pBase->GetUserDataPtr();
  if (hTree == NULL) return (false);

  m_ResourceTree.Expand(hTree, TVE_EXPAND);
  m_ResourceTree.EnsureVisible(hTree);
  m_ResourceTree.SelectItem(hTree);

  return (true);
}
/*===========================================================================
 *		End of Class Method CSrResourceView::SelectResource()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrResourceView Event - void OnHelp (void);
 *
 *=========================================================================*/
void CSrResourceView::OnHelp (void) {
  CString Buffer;

	/* Ignore if web help is disabled */
  if (!CSrEditDlgHandler::GetOptions().EnableWebHelp) return;
  
  Buffer  = CSrEditDlgHandler::GetOptions().UESPWikiPrefix;
  Buffer += "Tes4Mod:User_Interface/Resource_Viewer";

  OpenWebPage(Buffer);
}
/*===========================================================================
 *		End of Class Event CSrResourceView::OnHelp()
 *=========================================================================*/

