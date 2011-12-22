/*===========================================================================
 *
 * File:		Srloaddlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srLoadDlg.h"
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

  CStringArray	CSrLoadDlg::s_ExtraFilePaths;
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrLoadDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CSrLoadDlg)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_FILE_LIST, OnColumnclickFileList)
	ON_NOTIFY(NM_DBLCLK, IDC_FILE_LIST, OnDblclkFileList)
	ON_BN_CLICKED(IDC_SETACTIVE, OnSetactive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CSrLoadDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_FileListCompare (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int CALLBACK l_FileListCompare (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  srloaddlgfileinfo_t*  pData1    = (srloaddlgfileinfo_t  *) lParam1;
  srloaddlgfileinfo_t*  pData2    = (srloaddlgfileinfo_t  *) lParam2;
  srloadfilesortinfo_t* pSortData = (srloadfilesortinfo_t *) lParamSort;
  int		        Result    = 0;

  if (pData1 == NULL || pData2 == NULL || pSortData == NULL) return (0);

  switch (pSortData->SortType) {
    case SRFILELIST_FILENAME:
        Result = _tcsicmp(pData2->FindData.cFileName, pData1->FindData.cFileName);
	break;
    case SRFILELIST_DATE: {
        CTime Time1(pData1->FindData.ftLastWriteTime);
        CTime Time2(pData2->FindData.ftLastWriteTime);
        CTimeSpan TimeDiff = Time2 - Time1;
		Result = (int)(TimeDiff.GetTotalSeconds());
		break; }
    case SRFILELIST_SIZE:
        Result = pData2->FindData.nFileSizeHigh - pData1->FindData.nFileSizeHigh;
		if (Result == 0) Result = pData1->FindData.nFileSizeLow - pData2->FindData.nFileSizeLow;
		break;
    case SRFILELIST_DEFAULTSORT: {
        
		if (pData1->IsMaster != pData2->IsMaster) {
			Result = pData2->IsMaster - pData1->IsMaster;
		}
		else {
          CTime Time1(pData1->FindData.ftLastWriteTime);
          CTime Time2(pData2->FindData.ftLastWriteTime);
          CTimeSpan TimeDiff = Time2 - Time1;
		  Result = (int) (TimeDiff.GetTotalSeconds());
		}

	break; }
  }

  if (pSortData->Reverse) return (-Result);
  return (Result);
}
/*===========================================================================
 *		End of Function l_FileListCompare()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Constructor
 *
 *=========================================================================*/
CSrLoadDlg::CSrLoadDlg(CWnd* pParent) : CDialog(CSrLoadDlg::IDD, pParent) 
{
	m_LastSortReverse = false;
	m_LastSortSubItem = SRFILELIST_FILENAME;
	m_pLastActiveFile = NULL;
}
/*===========================================================================
 *		End of Class CSrLoadDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Method - void AddFile (pPath, FindData);
 *
 *=========================================================================*/
void CSrLoadDlg::AddFile (const char* pPath, WIN32_FIND_DATA& FindData) 
{
	srloaddlgfileinfo_t*	pNewData;
	CString					Buffer;
	int						ListIndex;

		/* Create a copy of the find data */
	pNewData  = new srloaddlgfileinfo_t;
	m_FileInfos.Add(pNewData);

	pNewData->FindData = FindData;
	pNewData->IsActive = false;
	pNewData->IsMaster = false;
	pNewData->Path     = pPath;

		/* Add the file to the list control */
	ListIndex = m_FileList.InsertItem(0, FindData.cFileName);
	if (ListIndex < 0) return;
	m_FileList.SetItemData(ListIndex, (DWORD) pNewData);

	if (SrCheckExtension(FindData.cFileName, "esm")) 
	{
		pNewData->IsMaster = true;
	}
  
	UpdateFile(ListIndex, pNewData);
}
/*===========================================================================
 *		End of Class Method CSrLoadDlg::AddFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_SortLoadInfosByDate (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int __stdcall l_SortLoadInfosByDate (long lParam1, long lParam2, long lParamSort) 
{
  srloaddlgfileinfo_t* pFileInfo1 = (srloaddlgfileinfo_t *) lParam1;
  srloaddlgfileinfo_t* pFileInfo2 = (srloaddlgfileinfo_t *) lParam2;

		/* Special case for Skyrim.esm to ensure it is loaded first */
  if (stricmp(pFileInfo1->FindData.cFileName, "Skyrim.esm") == 0) return -1;
  if (stricmp(pFileInfo2->FindData.cFileName, "Skyrim.esm") == 0) return 1;

  if (pFileInfo1 == NULL || pFileInfo2 == NULL) return (0);

  CTime Time1(pFileInfo1->FindData.ftLastWriteTime);
  CTime Time2(pFileInfo2->FindData.ftLastWriteTime);
  CTimeSpan TimeDiff = Time1 - Time2;

  return(int) TimeDiff.GetTotalSeconds();
}
/*===========================================================================
 *		End of Function l_SortLoadInfosByDate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Method - void CreateLoadInfo (void);
 *
 *=========================================================================*/
void CSrLoadDlg::CreateLoadInfo (void) 
{
	 CSrRefLoadDlgFileInfos SortLoadInfos;
	 srloaddlgfileinfo_t*	 pFileData;
	 CSString*				 pNewString;
	 dword					 Index;
	 int					 ListIndex;

		/* Clear the current load information */
	 m_LoadInfo.m_MasterFilenames.Destroy();
	 m_LoadInfo.m_ActiveFilename.Empty();

		/* Iterate through all checked items in the list */
	for (ListIndex = 0; ListIndex < m_FileList.GetItemCount(); ++ListIndex) 
	{
		if (!m_FileList.GetCheck(ListIndex)) continue;

	    pFileData = (srloaddlgfileinfo_t *) m_FileList.GetItemData(ListIndex);
	    if (pFileData == NULL) continue;

	    if (pFileData->IsActive) 
		{
			//m_LoadInfo.m_ActiveFilename = m_FilePath + pFileData->FindData.cFileName;
			m_LoadInfo.m_ActiveFilename = pFileData->Path + pFileData->FindData.cFileName;
		}	
		else if (pFileData->IsMaster) 
		{
			SortLoadInfos.Add(pFileData);
		}
		else 
		{
			AddSrGeneralError("Cannot add non-master file '%s' as a dependancy!", pFileData->FindData.cFileName);
		}
	} 

		/* Sort and load the masters according to date */
	SortLoadInfos.Sort(l_SortLoadInfosByDate, 0);

	for (Index = 0; Index < SortLoadInfos.GetSize(); ++Index) 
	{
		pNewString = new CSString;
		m_LoadInfo.m_MasterFilenames.Add(pNewString);
		*pNewString = SortLoadInfos[Index]->Path + SortLoadInfos[Index]->FindData.cFileName;
		//SystemLog.Printf("%d) %s", Index, pNewString->c_str());
	}

}
/*===========================================================================
 *		End of Class Method CSrLoadDlg::CreateLoadInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrLoadDlg::DoDataExchange (CDataExchange* pDX) 
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FILE_LIST, m_FileList);
}
/*===========================================================================
 *		End of Class Method CSrLoadDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Method - void FillFileList (void);
 *
 *=========================================================================*/
void CSrLoadDlg::FillFileList (void) 
{
  CSString DataPath;
  CSString FileSpec;
  bool     Result;

		/* Clear the current contents */
  m_FileList.DeleteAllItems();
  m_FileInfos.Empty();
  m_pLastActiveFile = NULL;

		/* Attempt to get Skyrim's data path */
  Result = GetSrInstallPath(DataPath);
  if (Result) DataPath += "data\\";

		/* Find all plugins in the game's \DATA path */
  FillFileList(DataPath, "*.esp");
  FillFileList(DataPath, "*.esm");

		/* Find all plugins in the extra paths */
  for (INT_PTR i = 0; i < s_ExtraFilePaths.GetSize(); ++i)
  {
		FillFileList(s_ExtraFilePaths[i], "*.esp");
		FillFileList(s_ExtraFilePaths[i], "*.esm");
  }

}
/*===========================================================================
 *		End of Class Method CSrLoadDlg::FillFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Method - int FillFileList (pPath, pFileSpec);
 *
 *=========================================================================*/
int CSrLoadDlg::FillFileList (const char* pPath, const char* pFileSpec) {
  HANDLE			hFind;
  WIN32_FIND_DATA	FindData;
  BOOL				FindResult;
  CString			FullFileSpec(pPath);
  int				Count = 0;

  TerminatePathString(FullFileSpec);
  FullFileSpec += pFileSpec;
  
  hFind = FindFirstFile(FullFileSpec, &FindData);
  FindResult = (hFind != INVALID_HANDLE_VALUE);
  
  while (FindResult) {
    ++Count;

    AddFile(pPath, FindData);
    
    FindResult = FindNextFile(hFind, &FindData);
  }

  FindClose(hFind);
  return (Count);
}
/*===========================================================================
 *		End of Class Method CSrLoadDlg::FillFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Event - void OnColumnclickFileList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrLoadDlg::OnColumnclickFileList(NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW*         pNMListView = (NM_LISTVIEW *) pNMHDR;
  srloadfilesortinfo_t SortData;

  SortData.Reverse  = false;
  SortData.SortType = pNMListView->iSubItem;

  if (pNMListView->iSubItem == m_LastSortSubItem) {
    m_LastSortReverse = !m_LastSortReverse;
    SortData.Reverse  = m_LastSortReverse;
  }
  else {
    m_LastSortSubItem  = pNMListView->iSubItem;
    m_LastSortReverse  = false;
  }

  m_FileList.SortItems(l_FileListCompare, (DWORD) &SortData);
	
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrLoadDlg::OnColumnclickFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Event - void OnDblclkFileList (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrLoadDlg::OnDblclkFileList (NMHDR* pNMHDR, LRESULT* pResult) {
  srloaddlgfileinfo_t*	pFileData;
  POSITION		ItemPos;
  int			ListIndex;
  
	/* Get the first, and only, selected item */
  ItemPos = m_FileList.GetFirstSelectedItemPosition();
  if (ItemPos == NULL) return;
  ListIndex = m_FileList.GetNextSelectedItem(ItemPos);
  if (ListIndex < 0) return;
  pFileData = (srloaddlgfileinfo_t *) m_FileList.GetItemData(ListIndex);
  if (pFileData == NULL) return;

	/* Set the check state */
  if (m_FileList.GetCheck(ListIndex)) {
    m_FileList.SetCheck(ListIndex, FALSE);

    if (pFileData->IsActive) { 
      pFileData->IsActive = false; 
      m_pLastActiveFile = NULL;
    }
  }
  else {
    m_FileList.SetCheck(ListIndex, TRUE);

    if (m_pLastActiveFile == NULL && !pFileData->IsMaster) {
      pFileData->IsActive = true;
      m_pLastActiveFile = pFileData;
    }
  }

  UpdateFile(ListIndex, pFileData);
  *pResult = 0;
}
/*===========================================================================
 *		End of Class Event CSrLoadDlg::OnDblclkFileList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrLoadDlg::OnInitDialog() {
  srloadfilesortinfo_t SortData;

  CDialog::OnInitDialog();

	/* Initialize the file list */
  m_FileList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
  m_FileList.InsertColumn(0, _T("Filename"),      LVCFMT_LEFT,   240, SRFILELIST_FILENAME);
  m_FileList.InsertColumn(1, _T("Date"),          LVCFMT_CENTER, 120, SRFILELIST_DATE);
  m_FileList.InsertColumn(2, _T("Size (bytes)"),  LVCFMT_CENTER,  75, SRFILELIST_SIZE);
  m_FileList.InsertColumn(3, _T("Type"),          LVCFMT_CENTER,  90, SRFILELIST_DEFAULTSORT);

  FillFileList();

  SortData.Reverse  = false;
  SortData.SortType = SRFILELIST_DEFAULTSORT;
  m_FileList.SortItems(l_FileListCompare, (DWORD) &SortData);
	
  return (TRUE);
}
/*===========================================================================
 *		End of Class Event CSrLoadDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Event - void OnOK (void);
 *
 *=========================================================================*/
void CSrLoadDlg::OnOK (void) {
  CreateLoadInfo();
  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrLoadDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Event - void OnSetactive ();
 *
 *=========================================================================*/
void CSrLoadDlg::OnSetactive() {
  srloaddlgfileinfo_t*	pFileData;
  POSITION		ItemPos;
  LVFINDINFO		FindInfo;
  int			ListIndex;
  int			ActiveIndex;
  
	/* Get the first, and only, selected item */
  ItemPos = m_FileList.GetFirstSelectedItemPosition();
  if (ItemPos == NULL) return;
  ListIndex = m_FileList.GetNextSelectedItem(ItemPos);
  if (ListIndex < 0) return;
  pFileData = (srloaddlgfileinfo_t *) m_FileList.GetItemData(ListIndex);
  if (pFileData == NULL) return;

	/* Update the previous active file, if any */
  if (m_pLastActiveFile != NULL) {
    FindInfo.flags       = LVFI_PARAM;
    FindInfo.psz         = NULL;
    FindInfo.lParam      = (long) m_pLastActiveFile;
    FindInfo.vkDirection = 0;

    m_pLastActiveFile->IsActive = false; 
    ActiveIndex = m_FileList.FindItem(&FindInfo, -1);
    if (ActiveIndex >= 0) UpdateFile(ActiveIndex, m_pLastActiveFile);
  }

  if (pFileData->IsActive) { 
    pFileData->IsActive = false; 
    m_pLastActiveFile = NULL;
  }
  else {
    m_FileList.SetCheck(ListIndex, TRUE);
    pFileData->IsActive = true;
    m_pLastActiveFile = pFileData;
    UpdateFile(ListIndex, pFileData);	
  }
 
}
/*===========================================================================
 *		End of Class Event CSrLoadDlg::OnSetactive()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLoadDlg Method - void UpdateFile (ListIndex, pFileData);
 *
 *=========================================================================*/
void CSrLoadDlg::UpdateFile (const int ListIndex, srloaddlgfileinfo_t* pFileData) {
  CString Buffer;
  int64   FileSize;

  m_FileList.SetItemText(ListIndex, SRFILELIST_FILENAME, pFileData->FindData.cFileName);

  CTime FileTime(pFileData->FindData.ftLastWriteTime);
  m_FileList.SetItemText(ListIndex, SRFILELIST_DATE, FileTime.Format(_T("%c")));
  
  FileSize  = (int64)pFileData->FindData.nFileSizeLow + (((int64) pFileData->FindData.nFileSizeHigh) << 32);
  Buffer.Format(_T("%I64d"), FileSize);
  m_FileList.SetItemText(ListIndex, SRFILELIST_SIZE, Buffer);

  if (pFileData->IsActive) {
    if (pFileData->IsMaster)
      m_FileList.SetItemText(ListIndex, SRFILELIST_DEFAULTSORT, _T("Active Master"));
    else
      m_FileList.SetItemText(ListIndex, SRFILELIST_DEFAULTSORT, _T("Active"));
  }
  else if (pFileData->IsMaster) {
    m_FileList.SetItemText(ListIndex, SRFILELIST_DEFAULTSORT, _T("Master"));
  }
  else {
    m_FileList.SetItemText(ListIndex, SRFILELIST_DEFAULTSORT, _T(""));
  }

}
/*===========================================================================
 *		End of Class Method CSrLoadDlg::UpdateFile()
 *=========================================================================*/
