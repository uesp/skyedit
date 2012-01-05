/*===========================================================================
 *
 * File:		SreditView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Implementation of the CSrEditView class.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "sreditDoc.h"
#include "sreditView.h"
#include "srloaddlg.h"
#include "srprogressdlg.h"
#include "common/csvfile.h"
#include "srfiletreedlg.h"
#include "srfindbinarydlg.h"
#include "common/srtime.h"
#include "modfile/srexport.h"
#include "dialogs/SrRawDataDlg.h"
#include "mainfrm.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

 	/* Debug definitions */
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  IMPLEMENT_DYNCREATE(CSrEditView, CFormView);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrEditView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrEditView, CFormView)
  ON_WM_SIZE()
  ON_NOTIFY(TVN_SELCHANGED, IDC_RECORDTREE, OnSelchangedRecordtree)
  ON_COMMAND(ID_FILE_IMPORT_CSV, OnFileImportCsv)
  ON_COMMAND(ID_FILE_EXPORTCSV_SELECTEDITEMS, OnFileExportcsvSelecteditems)
  ON_COMMAND(ID_RECORDTREE_RELOAD, OnRecordtreeReload)
  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_FILE_EXPORTCSV_ITEMTYPE, OnRecordtreeExporttocsv)
  ON_COMMAND(ID_VIEW_FILESTRUCTURE, OnViewFilestructure)
  ON_COMMAND(ID_FILE_EXPORT_CSVEXTERIORLOCATIONS, OnFileExportCsvexteriorlocations)
  ON_COMMAND(ID_FILE_EXPORT_CSVEXTMAPMARKERS, OnFileExportCsvExtMapMarkers)
  ON_COMMAND(ID_HELP_TESTFIELDLOOKUP, OnHelpTestfieldlookup)
  ON_COMMAND(ID_FILE_EXPORT_CSVEXPORTEXTERIORPLANTS, OnFileExportCsvexportexteriorplants)
  ON_COMMAND(ID_EDIT_FINDBINARYDATA, OnEditFindbinarydata)
  ON_COMMAND(ID_HELP_TESTFINDFORMID, OnHelpTestfindformid)
  ON_COMMAND(ID_TEST_MEMORYSPEED, OnTestMemoryspeed)
  ON_COMMAND(ID_TEST_TOKENSCRIPTS, OnTestTokenscripts)
  ON_COMMAND(ID_RECORD_CLEAN, OnRecordClean)
  ON_UPDATE_COMMAND_UI(ID_RECORD_CLEAN, OnUpdateHasSelectedRecords)
  ON_COMMAND(ID_RECORD_MOVEACTIVE, OnRecordMoveactive)
  ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)  
  ON_WM_DESTROY()
  ON_COMMAND(ID_MENU_EDITRECORD, OnMenuEditrecord)
  ON_COMMAND(ID_EDIT_NEWRECORD, OnEditNewrecord)
  ON_COMMAND(ID_RECORD_TOGGLEQUEST, OnRecordTogglequest)
  ON_COMMAND(ID_RECORD_TOGGLEIGNORE, OnRecordToggleignore)
  ON_COMMAND(ID_RECORD_TOGGLEDELETE, OnRecordToggledelete)
  ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
  ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
  ON_COMMAND(ID_RECORD_RENAME, OnRecordRename)
  ON_COMMAND(ID_RECORD_CREATECOPY, OnRecordCreatecopy)
  ON_COMMAND(ID_RECORD_BATCHEDIT, OnRecordBatchedit)
  ON_COMMAND(ID_EDIT_FIND, OnEditFind)
  ON_COMMAND(ID_HELP_TESTOUTPUTEFFECTS, OnHelpTestoutputeffects)
  ON_COMMAND(ID_HELP_TESTRECORDSIZE, OnHelpTestrecordsize)
  ON_COMMAND(ID_TEST_CLEANRECOMPILEALL, OnTestCleanrecompileall)
  ON_COMMAND(ID_TEST_RECOMPILEALL, OnTestRecompileall)
  ON_COMMAND(ID_HELP_TESTCOMPARESCRIPTS, OnHelpTestcomparescripts)
  ON_COMMAND(ID_RECORDTREE_EXPORTTOCSV, OnRecordtreeExporttocsv)
  ON_UPDATE_COMMAND_UI(ID_RECORD_MOVEACTIVE, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_TOGGLEQUEST, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_TOGGLEIGNORE, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_TOGGLEDELETE, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_CREATECOPY, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_RENAME, OnUpdateHasSelectedRecords)
  ON_UPDATE_COMMAND_UI(ID_RECORD_BATCHEDIT, OnUpdateHasSelectedRecords)
  ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
  ON_COMMAND(ID_MENU_VIEWRAWDATA, &CSrEditView::OnMenuViewrawdata)
  ON_COMMAND(ID_HELP_TESTOUTPUTPERKS, &CSrEditView::OnHelpTestoutputperks)
  ON_BN_CLICKED(IDC_ACTIVECHECK, &CSrEditView::OnBnClickedActivecheck)
  ON_EN_CHANGE(IDC_FILTERTEXT, &CSrEditView::OnEnChangeFiltertext)
  ON_WM_TIMER()
  ON_WM_CLOSE()
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Class CSrEditView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG
void CSrEditView::AssertValid() const {
  CFormView::AssertValid();
 }

void CSrEditView::Dump(CDumpContext& dc) const  {
  CFormView::Dump(dc);
 }

CSrEditDoc* CSrEditView::GetDocument() {
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSrEditDoc)));
  return (CSrEditDoc*)m_pDocument;
 }
#endif
/*===========================================================================
 *		End of Class Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_RenamePromptFunc (EditInfo, UserData);
 *
 * Used to prompt when renaming a record.
 *
 *=========================================================================*/
int l_RenamePromptFunc (sreditrecinfo_t& EditInfo, long UserData) {
  CSrEditDlgHandler* pDlgHandler = (CSrEditDlgHandler *) UserData;

  if (pDlgHandler == NULL) return (0);
  return pDlgHandler->PromptRenameCopy(EditInfo);
}
/*===========================================================================
 *		End of Function l_RenamePromptFunc()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Constructor
 *
 *=========================================================================*/
CSrEditView::CSrEditView() : CFormView(CSrEditView::IDD) 
{
  m_IsInitialized  = false;
  m_pCurrentFilter = NULL;
  m_UpdateFilterCounts = false;
  m_hFilterUpdateThreadID = 0;
  m_hFilterUpdateThread = 0;
}
/*===========================================================================
 *		End of Class CSrEditView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Destructor
 *
 *=========================================================================*/
CSrEditView::~CSrEditView() 
{
	SetEvent(m_ThreadCloseEvent);
	DWORD Result = WaitForSingleObject(m_hFilterUpdateThread, 10000);
	CloseHandle(m_ThreadCloseEvent);	
}
/*===========================================================================
 *		End of Class CSrEditView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrEditView::DoDataExchange(CDataExchange* pDX) 
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_VEDGE, m_VertEdge);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
	DDX_Control(pDX, IDC_RECORDTREE, m_RecordTree);
	DDX_Control(pDX, IDC_FILTERTEXT, m_FilterText);
	DDX_Control(pDX, IDC_ACTIVECHECK, m_ActiveCheck);
}
/*===========================================================================
 *		End of Class Method CSrEditView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrEditView::OnContextMenu(CWnd* pWnd, CPoint Point) {
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_RECORDTREE) {
    Result = Menu.LoadMenu(IDR_RECORDTREE_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }
  else if (pWnd->GetDlgCtrlID() == IDC_RECORDLIST) {
    Result = Menu.LoadMenu(IDR_RECORDLIST_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }

}
/*===========================================================================
 *		End of Class Event CSrEditView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnFileExportCsvexportexteriorplants ();
 *
 *=========================================================================*/
void CSrEditView::OnFileExportCsvexportexteriorplants() {
  srexportinfo_t ExportInfo = g_ExportCsvPlants;
  CString        Buffer;
  
	/* Prompt user for output filename */
  Buffer.Format(_T("Select CSV File to Export Exterior Plant Locations..."));
  ExportInfo.GroupFormID = 0;

  OnCsvExport(ExportInfo, Buffer);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnFileExportCsvexportexteriorplants()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnFileExportCsvexteriorlocations ();
 *
 *=========================================================================*/
void CSrEditView::OnFileExportCsvexteriorlocations() {
  srexportinfo_t ExportInfo = g_ExportCsvExtLocations;
  CString        Buffer;
  
  Buffer.Format(_T("Select CSV File to Export Exterior Locations..."));
  ExportInfo.GroupFormID = 0;

  OnCsvExport(ExportInfo, Buffer);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnFileExportCsvexteriorlocations()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnFileExportCsvExtMapMarkers ();
 *
 *=========================================================================*/
void CSrEditView::OnFileExportCsvExtMapMarkers() {
  srexportinfo_t ExportInfo = g_ExportCsvMapMarkers;
  CString        Buffer;
  
  Buffer.Format(_T("Select CSV File to Export Exterior Map Markers..."));
  ExportInfo.GroupFormID = 0;

  OnCsvExport(ExportInfo, Buffer);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnFileExportCsvExtMapMarkers()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - bool OnCsvExport (ExportInfo, pDialogTitle);
 *
 *=========================================================================*/
bool CSrEditView::OnCsvExport (srexportinfo_t& ExportInfo, const TCHAR* pDialogTitle) {
  CFileDialog  OpenDlg(FALSE, SREDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, SREDIT_CSV_FILTER, this);
  int          Result;

	/* Prompt user for output filename */
  if (pDialogTitle != NULL) OpenDlg.m_ofn.lpstrTitle = pDialogTitle;
  Result = OpenDlg.DoModal();
  if (Result != IDOK) return (true);

  Result = SrCsvExport(OpenDlg.GetPathName(), GetDocument()->GetActiveFile(), ExportInfo);

  if (Result != 0) {
    SrEditShowError(_T("CSV Error"), _T("Error exporting records to the CSV file '%s'!"), OpenDlg.GetPathName());
  }

  return (Result != 0);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnCsvExport()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnFileExportcsvSelecteditems ();
 *
 *=========================================================================*/
void CSrEditView::OnFileExportcsvSelecteditems() {
  CFileDialog  OpenDlg(FALSE, SREDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, SREDIT_CSV_FILTER, this);
  POSITION     ItemPos;
  CSrRecord*   pRecord;
  CSrRecord*   pFirstRecord;
  srcsvinfo_t  CsvInfo;
  CCsvFile     CsvFile;
  CString      Buffer;
  int          ListIndex;
  int          Result;

	/* Ignore if no records to export */
  ItemPos = m_RecordList.GetFirstSelectedItemPosition();
  if (ItemPos == NULL) return;

	/* Prompt user for output filename */
  Buffer.Format(_T("Select CSV File to Export %d Records..."), m_RecordList.GetSelectedCount());
  OpenDlg.m_ofn.lpstrTitle = Buffer;
  Result = OpenDlg.DoModal();
  if (Result != IDOK) return;

  CsvInfo.pCsvFile = &CsvFile;

	/* Output all selected records in the current list */
  while (ItemPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ItemPos);
    pRecord = m_RecordList.GetRecord(ListIndex);
    if (pRecord == NULL) continue;

		/* Initialize the CSV file on the first record */
    if (CsvFile.GetNumRows() == 0) {
      pFirstRecord = pRecord;
      Result = PrepareSrCsvExport(CsvInfo, pRecord->GetFieldMap());
      if (!Result) return;
     }
	
		/* Ensure all records are the same type */
    if (pFirstRecord->GetRecordType() != pRecord->GetRecordType()) continue;

    pRecord->ExportCsv(CsvInfo);
  }

  Result = CsvFile.Save(OpenDlg.GetPathName());

  if (!Result) {
    SrEditShowError(_T("CSV Error"), _T("Error saving the CSV file '%s'!"), OpenDlg.GetPathName());
  }
	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnFileExportcsvSelecteditems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordtreeExporttocsv ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordtreeExporttocsv() {
  CFileDialog  OpenDlg(FALSE, SREDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, SREDIT_CSV_FILTER, this);
  CSrRecord*   pRecord;
  CSrRecord*   pFirstRecord;
  srcsvinfo_t  CsvInfo;
  CCsvFile     CsvFile;
  CString      Buffer;
  int          ListIndex;
  int          Result;

	/* Ignore if no filter currently in use or no records to export */
  if (m_pCurrentFilter == NULL) return;	
  if (m_RecordList.GetItemCount() <= 0) return;

	/* Prompt user for output filename */
  Buffer.Format(_T("Select CSV File to Export %d Records..."), m_RecordList.GetItemCount());
  OpenDlg.m_ofn.lpstrTitle = Buffer;
  Result = OpenDlg.DoModal();
  if (Result != IDOK) return;

  CsvInfo.pCsvFile = &CsvFile;

	/* Output all records in the current list */
  for (ListIndex = 0; ListIndex < m_RecordList.GetItemCount(); ++ListIndex) {
    pRecord = m_RecordList.GetRecord(ListIndex);
    if (pRecord == NULL) continue;

		/* Initialize the CSV file on the first record */
    if (CsvFile.GetNumRows() == 0) {
      pFirstRecord = pRecord;
      Result = PrepareSrCsvExport(CsvInfo, pRecord->GetFieldMap());
      if (!Result) return;
    }
	
		/* Ensure all records are the same type */
    if (pFirstRecord->GetRecordType() != pRecord->GetRecordType()) continue;
    pRecord->ExportCsv(CsvInfo);
  }

  Result = CsvFile.Save(OpenDlg.GetPathName());

  if (!Result) {
    SrEditShowError(_T("Error saving the CSV file '%s'!"), OpenDlg.GetPathName());
  }

}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordtreeExporttocsv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnFileImportCsv ();
 *
 *=========================================================================*/
void CSrEditView::OnFileImportCsv() {
  CFileDialog OpenDlg(TRUE, SREDIT_CSV_EXT, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, SREDIT_CSV_FILTER, this);
  CString     Buffer;
  CCsvFile    CsvFile;
  dword       NewRecords;
  int         Result;

  OpenDlg.m_ofn.lpstrTitle = _T("Select CSV File to Import...");

  Result = OpenDlg.DoModal();
  if (Result != IDOK) return;

  Result = CsvFile.Load(OpenDlg.GetPathName());

  if (!Result) {
    SrEditShowError(_T("Failed to load the file '%s'!"), OpenDlg.GetPathName());
    return;
  }

  Buffer.Format(_T("Loaded %d rows from csv file"), CsvFile.GetNumRows());
  MessageBox(Buffer);

  Result = GetDocument()->GetRecordHandler().ImportCsv(NewRecords, CsvFile);
  if (NewRecords > 0) GetDocument()->SetModifiedFlag(TRUE);

  if (!Result) SrEditShowError(_T("Error importing CSV file!"));
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnFileImportCsv()
 *=========================================================================*/


DWORD WINAPI l_ThreadFilterUpdate(LPVOID lpParameter)
{
	CSrEditView* pView = (CSrEditView *) lpParameter;
	if (pView == NULL) return 1;

	pView->ThreadUpdateFilterProc();
	
	return 0;
}


/*===========================================================================
 *
 * Class CSrEditView Event - void OnInitialUpdate ();
 *
 *=========================================================================*/
void CSrEditView::OnInitialUpdate() {

		/* Call the base class method first */
  CFormView::OnInitialUpdate();

  m_ThreadCloseEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("SkyEditThreadClose")); 
  
  m_hFilterUpdateThread = CreateThread(NULL, 0, l_ThreadFilterUpdate, this, 0, &m_hFilterUpdateThreadID);

  m_DlgHandler.SetDocument(GetDocument());
  GetDocument()->GetRecordHandler().GetEventHandler().AddListener(this);
  GetDocument()->GetRecordHandler().GetEventHandler().AddListener(&m_DlgHandler);
  
	/* Setup the tree control */
  m_RecordTree.Initialize(CSrRecordTreeCtrl::GetOptions().FullFilterFile);
  
	/* Setup the list control */
  m_RecordList.SetListName("MainList");
  m_RecordList.DefaultSettings();
  //m_RecordList.SetupList(SR_NAME_ARMO);
  m_RecordList.SetOwner(this);

  ResizeParentToFit();

  m_RecordList.SetAutoResizeOffset();
  m_RecordList.SetAutoResize(true);
  
  m_IsInitialized = true;

	/* Disable the view scroll bars */
  SetScrollSizes(MM_TEXT, CSize(0, 0) );

  //GetParentFrame()->RecalcLayout();
  //ResizeParentToFit();
  
  UpdateContents();
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnEditFindbinarydata ();
 *
 *=========================================================================*/
void CSrEditView::OnEditFindbinarydata() {
  CSrProgressDlg*  pProgressDlg;
  CSrCallback	   SrEditFindCallback;
  CSrFindBinaryDlg FindDlg;
  CString          Buffer;
  const TCHAR*     pParse;
  dword		   Index;
  srfinddata_t	   FindData;
  dword		   Count;
  int		   Result;
  srtimer_t	   Timer;
  double	   DeltaTime;
  byte*		   pNewData = NULL;

  Result = FindDlg.DoModal();
  if (Result != IDOK) return;

	/* Initialize the find data */
  FindData.Flags = SR_FIND_OUTPUTLOG /*| SR_FIND_ALLHEADERS*/;
  FindData.DataSize  = _tcslen(FindDlg.GetBinaryData())/2;
  if (FindData.DataSize == 0) return;
  pNewData = new byte[FindData.DataSize + 4];
  FindData.pData = pNewData;

	/* Parse the binary data text */
  Index  = 0;
  pParse = FindDlg.GetBinaryData();

  while (Index < FindData.DataSize*2) {
    pNewData[Index/2] = ConvertFromHexByte(pParse + Index);
    Index += 2;
  }

  Buffer.Empty();

  for (Index = 0; Index < FindData.DataSize; ++Index) {
    Buffer += ConvertByteToHexChar(FindData.pData[Index]);
  }

  SystemLog.Printf("Searching for binary data '%s' (%.*s)...", Buffer, FindData.DataSize, FindData.pData);

  pProgressDlg = ShowSrProgressDlg(_T("Find Data"), _T("Finding binary data..."));
  SrEditFindCallback.SetCallbackInterval(1);
  SrEditFindCallback.SetFunction(SrEditDefaultProgressCallback);
  SrEditFindCallback.SetUserPtr((void *) pProgressDlg);
  SrEditFindCallback.Reset();
  SrEditFindCallback.ForceCallback(0);
  
  SrStartTimer(Timer);
 
	/* Perform the find */
  Count = GetDocument()->Search(FindData, &SrEditFindCallback);
  
  DeltaTime = SrEndTimer(Timer);
  SystemLog.Printf("Found %u matches in %u files, %u groups, %u records, and %u subrecords in %f seconds!", Count, 
		FindData.FileCount, FindData.GroupCount, FindData.RecordCount, FindData.SubrecordCount, DeltaTime);

  DestroySrProgressDlg(pProgressDlg);

	/* Cleanup the find data */
  delete[] pNewData;	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditFindbinarydata()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnHelpTestfindformid ();
 *
 *=========================================================================*/
void CSrEditView::OnHelpTestfindformid() {
  CSrProgressDlg*    pProgressDlg;
  CString            Buffer;
  CSrRecord*	     pRecord;
  srfinddata_t	     FindData;
  CSrCallback	     SrEditFindCallback;
  dword				 Count = 0;
  dword				 TotalCount;
  dword				 LimitCount = 200;
  dword              Index;
  srrectype_t	     ExcludeNames[] = { SR_NAME_LAND, SR_NAME_NULL }; //SR_NAME_PGRD
  byte*				 pNewData = NULL;

  CSrGroup* pGroup = GetDocument()->GetTopGroup()->GetTypeGroup(SR_NAME_ARMO);
  if (pGroup == NULL) return;

  TotalCount = pGroup->GetNumRecords();
  TotalCount = LimitCount;

  pProgressDlg = ShowSrProgressDlg(_T("Find FormID"), _T("Finding formid..."));
  SrEditFindCallback.SetCallbackInterval(1);
  SrEditFindCallback.SetFunction(SrEditDefaultProgressCallback);
  SrEditFindCallback.SetUserPtr((void *) pProgressDlg);
  SrEditFindCallback.SetTotalRecords(TotalCount);
  SrEditFindCallback.Reset();
  
	/* Initialize the find data */
  FindData.Flags = SR_FIND_OUTPUTLOG /*| SR_FIND_ALLHEADERS*/;
  FindData.DataSize = 4;
  pNewData = new byte[8];
  FindData.pData = pNewData;
  FindData.pExcludeRecords = &ExcludeNames[0];

  Index = 0;
  pRecord = SrCastClassNull(CSrRecord, pGroup->GetRecord(Index));
  
  while (pRecord) {
    Buffer.Format("Finding formId 0x%08X... (%4.4s)", pRecord->GetFormID(), pRecord->GetRecordType().Name);
    SystemLog.Printf(Buffer);
    pProgressDlg->SetLabel(Buffer);
    pProgressDlg->SetProgress((float)Count*100.0f / (float) TotalCount);
    ++Count;
    ++Index;
    if (Count > LimitCount) break;

    *(dword *)(pNewData) = pRecord->GetFormID();

    GetDocument()->GetActiveFile().Find(FindData, &SrEditFindCallback);

    pRecord = SrCastClassNull(CSrRecord, pGroup->GetRecord(Index));
  }
  
  DestroySrProgressDlg(pProgressDlg);

	/* Cleanup the find data */
  delete[] pNewData;
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnHelpTestfindformid()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordtreeReload ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordtreeReload() {
  m_RecordTree.LoadFilters(CSrRecordTreeCtrl::GetOptions().FullFilterFile);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordtreeReload()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnSize (nType, CX, CY);
 *
 *=========================================================================*/
void CSrEditView::OnSize (UINT nType, int CX, int CY) 
{
  CFormView::OnSize(nType, CX, CY);

  if (m_IsInitialized) 
  {
    m_RecordList.AutoResize();
    m_RecordTree.SetWindowPos(NULL, 0, 0, 188, CY - 48, SWP_NOMOVE | SWP_NOZORDER);
    m_VertEdge.SetWindowPos(NULL, 0, 0, 3, CY+2, SWP_NOMOVE | SWP_NOZORDER);
  }
	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnSelchangedRecordtree (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrEditView::OnSelchangedRecordtree (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_TREEVIEW*     pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  CSrRecordFilter* pFilter;
  DWORD            Value;

  *pResult = 0;
  Value = m_RecordTree.GetItemData(pNMTreeView->itemNew.hItem);
  if (Value == 0) return;

  pFilter = (CSrRecordFilter *) Value;
  if (pFilter == m_pCurrentFilter) return;

  if (pFilter->IsFlagEmpty() || pFilter->GetRecordType() == SR_NAME_NULL) pFilter = NULL;

  m_pCurrentFilter = pFilter;
  
  m_RecordList.SetupList(m_pCurrentFilter);
  m_RecordList.AddAllRecords(GetDocument()->GetTopGroup());
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnSelchangedRecordtree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnUpdate (pSender, lHint, pHint);
 *
 *=========================================================================*/
void CSrEditView::OnUpdate (CView* pSender, LPARAM lHint, CObject* pHint) {
  srrecupdateinfo_t*	pUpdateInfo = (srrecupdateinfo_t *) pHint;

  switch (lHint) {
    case SREDIT_DOC_HINT_UPDATEALL:
        UpdateContents();
	break;
    case SREDIT_DOC_HINT_UPDATERECORD:
        m_RecordList.UpdateRecord(pUpdateInfo->pNewRecord, pUpdateInfo->pOldRecord);
        m_RecordTree.UpdateFilterCounts(GetDocument()->GetTopGroup());
	break;
    case SREDIT_DOC_HINT_ADDRECORD:
        m_RecordList.AddRecord(pUpdateInfo->pNewRecord);
        m_RecordTree.IncludeInCounts(pUpdateInfo->pNewRecord);
	break;
    case SREDIT_DOC_HINT_GETDATA:
	/* TODO */
	break;
    case SREDIT_DOC_HINT_CLEARFILTERS: {
	break; }
    case SREDIT_DOC_HINT_UPDATEFILTERS: {
	break; }
    default:
	CView::OnUpdate(pSender, lHint, pHint);
	break;
  }
	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnViewFilestructure ();
 *
 *=========================================================================*/
void CSrEditView::OnViewFilestructure() {
  CSrFileTreeDlg TreeDlg;

  TreeDlg.SetTopGroup(GetDocument()->GetTopGroup());
  TreeDlg.DoModal();
	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnViewFilestructure()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Method - BOOL PreCreateWindow (cs);
 *
 *=========================================================================*/
BOOL CSrEditView::PreCreateWindow (CREATESTRUCT& cs) {
  return CFormView::PreCreateWindow(cs);
 }
/*===========================================================================
 *		End of Class Method CSrEditView::PreCreateWindow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnHelpTestfieldlookup ();
 *
   1096769 Records
	09:17:59 (24609) - Iteration Time = 0.013028 secs
	09:17:59 (24718) - Iteration Time with Class Cast = 0.095499 secs
	09:17:59 (25234) - Find WEIGHT Field = 0.522570 secs
	09:18:00 (25781) - Get WEIGHT String = 0.551424 secs
	09:18:00 (26234) - Find EDITORID Field = 0.452844 secs
	09:18:01 (26750) - Get EDITORID String = 0.511969 secs
	09:18:01 (26984) - Find WEIGHT Field1 = 0.232224 secs
	09:18:01 (27218) - Find EDITORID Field1 = 0.228567 secs
	09:18:01 (27468) - Get WEIGHT String1 = 0.251833 secs
	09:18:02 (27718) - Get EDITORID String1 = 0.255710 secs
	09:18:05 (30984) - Iteration Time = 0.013076 secs
	09:18:05 (31078) - Iteration Time with Class Cast = 0.095586 secs
	09:18:06 (31593) - Find WEIGHT Field = 0.508603 secs
	09:18:06 (32015) - Get WEIGHT String = 0.425909 secs
	09:18:06 (32453) - Find EDITORID Field = 0.439205 secs
	09:18:07 (32859) - Get EDITORID String = 0.393132 secs
	09:18:07 (33031) - Find WEIGHT Field1 = 0.173945 secs
	09:18:07 (33187) - Find EDITORID Field1 = 0.166808 secs
	09:18:07 (33375) - Get WEIGHT String1 = 0.181755 secs
	09:18:08 (33609) - Get EDITORID String1 = 0.233427 secs

  1023759 Records using GetFirst/GetNext...
	11:36:29 (26968) - Iteration Time = 0.102827 secs
	11:36:29 (27093) - Iteration Time with Class Cast = 0.139105 secs
	11:36:29 (27312) - Find WEIGHT Field = 0.217886 secs
	11:36:30 (27562) - Get WEIGHT String = 0.247051 secs
	11:36:30 (27781) - Find EDITORID Field = 0.212212 secs
	11:36:30 (28078) - Get EDITORID String = 0.292917 secs
	11:36:30 (28218) - Find WEIGHT Field1 = 0.140716 secs
	11:36:30 (28359) - Find EDITORID Field1 = 0.140012 secs
	11:36:30 (28500) - Get WEIGHT String1 = 0.141654 secs
	11:36:31 (28640) - Get EDITORID String1 = 0.139036 secs
	11:36:31 (28640) - Record Count = 1023759

   Using Switch Compare
	10:03:11 (30968) - Compare WEIGHT Field = 0.173250 secs
	10:03:11 (31140) - Compare EDITORID Field = 0.175900 secs

   Using Field Map Compare
	01:06:38 (72687) - Compare WEIGHT Field = 0.239074 secs
	01:06:39 (72984) - Compare EDITORID Field = 0.303329 secs

 *=========================================================================*/
void CSrEditView::OnHelpTestfieldlookup() {

	/*
  srtimer_t			Timer;
  CSrRecordHandler*	pHandler = &(GetDocument()->GetRecordHandler());
  //CSrEspFile*		pFile = &(GetDocument()->GetEspFile());
  CSrBaseRecord*	pBaseRecord;
  const srrecfield_t*	pField;
  CSString			Buffer;
  CSrRecord*		pRecord;
  //CSrWeapRecord		TestRecord;
  SRMAPPOS			RecordPos;
  dword				Count = 0;

  TestRecord.InitializeNew();
  TestRecord.SetEditorID("testeditorid01");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		++Count;
		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Iteration Time");
  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Iteration Time with Class Cast");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			pField = pRecord->FindField(SR_FIELD_WEIGHT);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Find WEIGHT Field");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			pRecord->GetField(Buffer, SR_FIELD_WEIGHT);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Get WEIGHT String");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			pField = pRecord->FindField(SR_FIELD_EDITORID);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Find EDITORID Field");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			pRecord->GetField(Buffer, SR_FIELD_EDITORID);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Get EDITORID String");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(SR_FIELD_WEIGHT);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Find WEIGHT Field1");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(SR_FIELD_EDITORID);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Find EDITORID Field1");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(SR_FIELD_WEIGHT);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Get WEIGHT String1");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			//pField = pRecord->GetField1(SR_FIELD_EDITORID);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Get EDITORID String1");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			pRecord->CompareFields(SR_FIELD_WEIGHT, &TestRecord);
			//pField = pRecord->GetField1(SR_FIELD_EDITORID);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Compare WEIGHT Field");

  SrStartTimer(Timer);
	pBaseRecord = pHandler->GetFirstRecord(RecordPos);

	while (pBaseRecord != NULL) {
		pRecord = SrCastClass(CSrRecord, pBaseRecord);

		if (pRecord) {
			pRecord->CompareFields(SR_FIELD_EDITORID, &TestRecord);
			//pField = pRecord->GetField1(SR_FIELD_EDITORID);
			//if (pField) (pRecord->*pField->GetMethod)(Buffer);
		}

		pBaseRecord = pHandler->GetNextRecord(RecordPos);
	}
  SrEndTimer(Timer, "Compare EDITORID Field");

  SystemLog.Printf("Record Count = %d", Count); */
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnHelpTestfieldlookup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnTestMemoryspeed ();
 *
 *=========================================================================*/
#define TEST_MEMORY_SIZE	1000000
#define TEST_MEMORY_ARRAYSIZE	1000

  CSrRecord* pRecords[TEST_MEMORY_SIZE];
  CSString*  pStrings[TEST_MEMORY_SIZE];
  CSrRecord* pRecordArray[TEST_MEMORY_ARRAYSIZE];
  CSString*  pStringArray[TEST_MEMORY_ARRAYSIZE];

  TSrBlockAllocator<CSString> TestStringAllocator;

void CSrEditView::OnTestMemoryspeed() {
  DWORD     Index;
  srtimer_t Timer;

  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    pRecords[Index] = new CSrRecord;
  }

  SrEndTimer(Timer, "Allocated 1000000 CSrRecords in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    pStrings[Index] = new CSString;
  }

  SrEndTimer(Timer, "Allocated 1000000 CSStrings in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    pRecordArray[Index] = new CSrRecord[TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE];
  }

  SrEndTimer(Timer, "Allocated 1000 CSrRecords[1000] in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    pStringArray[Index] = new CSString[TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE];
  }

  SrEndTimer(Timer, "Allocated 1000 CSStrings[1000] in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    delete pRecords[Index];
  }

  SrEndTimer(Timer, "Deleted 1000000 CSrRecords in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
    delete pStrings[Index];
  }

  SrEndTimer(Timer, "Deleted 1000000 CSStrings in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    delete[] pRecordArray[Index];
  }

  SrEndTimer(Timer, "Deleted 1000 CSrRecords[1000] in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE/TEST_MEMORY_ARRAYSIZE; ++Index) {
    delete[] pStringArray[Index];
  }

  SrEndTimer(Timer, "Deleted 1000 CSStrings[1000] in ");
  SrStartTimer(Timer);

  for (Index = 0; Index < TEST_MEMORY_SIZE; ++Index) {
	  pStrings[Index] = TestStringAllocator.CreateObject();
  }

  SrEndTimer(Timer, "Allocated 1000000 CSString from a block allocator in ");
  SrStartTimer(Timer);

  TestStringAllocator.Destroy();

  SrEndTimer(Timer, "Deleted 1000000 CSStrings from a block allocator in ");
	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnTestMemoryspeed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnTestTokenscripts ();
 *
 *=========================================================================*/
void CSrEditView::OnTestTokenscripts() {
/*
  CCustomCompiler   Compiler;
  CScanSourceString ScanSource;
  CSrBaseRecord*    pBaseRecord;
  CSrScptRecord*    pScript;
  CSrTypeGroup*	    pScriptGroup;
  bool		    Result;
  dword		    ScriptCount = 0;
  dword		    ErrorCount = 0;
  dword		    ByteCount = 0;
  dword		    LineCount = 0;
  srtimer_t	    Timer;
  double	    DeltaTime;
  dword		    Index;

  Result = Compiler.Load("testtable1.dat");
  if (!Result) return;
  GetSrEditApp().UpdateScriptColorOptions(Compiler, true);
  SrStartTimer(Timer);

  //ScanSource.SetString("end");
  //Compiler.Tokenize(&ScanSource);

  pScriptGroup = GetDocument()->GetRecordHandler().GetTopGroup()->GetTypeGroup(SR_NAME_SCPT);
  if (pScriptGroup == NULL) return;

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = SrCastClass(CSrScptRecord, pBaseRecord);
    if (pScript == NULL) continue;

    //SystemLog.Printf("Tokenizing script %s...", pScript->GetEditorID());

    ScanSource.SetString(pScript->GetScriptText());

    Result = Compiler.Tokenize(&ScanSource);
    if (!Result) ++ErrorCount;

    ++ScriptCount;
    ByteCount += pScript->GetScriptSize();
    LineCount += pScript->GetNumLines();
  }

  DeltaTime = SrEndTimer(Timer);
  SystemLog.Printf("Succesfully tokenized %u of %u scripts (%u lines, %u bytes) in %f seconds.", ScriptCount - ErrorCount, ScriptCount, LineCount, ByteCount, DeltaTime);
  */
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnTestTokenscripts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordClean ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordClean() {
  CSrProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  CSrRecord*      pRecord;
  CSrRecord*      pNewRecord;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();
  int             ListIndex;

  if (SelectedCount > SREDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowSrProgressDlg("Clean Records", "Cleaning selected records from active file...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  SrLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    pRecord   = m_RecordList.GetRecord(ListIndex);
    ++Count;
    if (pRecord == NULL) continue;

    	/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }

		/* Ignore non-active records */
    if (!pRecord->IsActive()) continue;

		/* Perform the clean */
    pNewRecord = GetDocument()->GetRecordHandler().CleanRecord(pRecord);
    GetDocument()->SetModifiedFlag(TRUE);
  }

  DestroySrProgressDlg(pProgressDlg);
  SrLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordClean()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Method - void UpdateContents (void);
 *
 *=========================================================================*/
void CSrEditView::UpdateContents (void) 
{
	m_RecordList.DeleteAllItems();
	m_RecordList.AddAllRecords(GetDocument()->GetRecordHandler().GetTopGroup());
	m_RecordTree.UpdateFilterCounts(GetDocument()->GetRecordHandler().GetTopGroup());
	AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);
}
/*===========================================================================
 *		End of Class Method CSrEditView::UpdateContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordMoveactive ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordMoveactive() {
  CSrProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  CSrRecord*      pRecord;
  bool	          Result;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();
  int             ListIndex;

  if (SelectedCount > SREDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowSrProgressDlg("Move Active", "Moving selected records to active file...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  SrLockUndoUpdates(true);
  
  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    pRecord   = m_RecordList.GetRecord(ListIndex);
    ++Count;
    if (pRecord == NULL) continue;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }

		/* Ignore active records */
    if (pRecord->IsActive()) continue;

		/* Perform the move */
    Result = GetDocument()->GetRecordHandler().MakeRecordActive(pRecord);
    if (Result) GetDocument()->SetModifiedFlag(TRUE);
  }

  DestroySrProgressDlg(pProgressDlg);
  SrLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordMoveactive()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnUpdateHasSelectedRecords (pCmdUI);
 *
 *=========================================================================*/
void CSrEditView::OnUpdateHasSelectedRecords (CCmdUI* pCmdUI) {
  pCmdUI->Enable(m_RecordList.GetSelectedCount() > 0); 	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnUpdateHasSelectedRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrEditView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) {
  CSrRecord* pRecord = (CSrRecord *) wParam;
  OnEditRecord(pRecord);

  return (0);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnEditRecord (pRecord);
 *
 *=========================================================================*/
void CSrEditView::OnEditRecord (CSrRecord* pRecord) {
  sreditrecinfo_t EditInfo;

  if (pRecord == NULL) return;
  
  EditInfo.HasUpdatedID = false;
  EditInfo.IsCopy       = false;
  EditInfo.IsNew        = false;
  EditInfo.IsRenamed    = false;
  EditInfo.pNewRecord   = NULL;
  EditInfo.pOldRecord   = pRecord;
  EditInfo.NewEditorID.Empty();
  
  m_DlgHandler.EditRecord(EditInfo);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnDestroy (void);
 *
 *=========================================================================*/
void CSrEditView::OnDestroy (void) 
{
	m_DlgHandler.CloseAll();

	CFormView::OnDestroy();
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnDestroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnMenuEditrecord ();
 *
 *=========================================================================*/
void CSrEditView::OnMenuEditrecord() {
  POSITION ListPos;
  int      ListIndex;

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  if (ListPos == NULL) return;
  ListIndex = m_RecordList.GetNextSelectedItem(ListPos);

  OnEditRecord(m_RecordList.GetRecord(ListIndex));
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnMenuEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnEditNewrecord ();
 *
 *=========================================================================*/
void CSrEditView::OnEditNewrecord() {
  const srrectype_t* pRecordType;
  sreditrecinfo_t    EditInfo;

  pRecordType = m_RecordList.GetCurrentRecordType();
  if (pRecordType == NULL) return;

  m_DlgHandler.EditNewRecord(*pRecordType);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditNewrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordTogglequest ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordTogglequest() {
  CSrProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  int             ListIndex;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();

  if (SelectedCount > SREDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowSrProgressDlg("Toggle Quest", "Toggling quest flag of selected records...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  SrLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    OnToggleQuestRecord(m_RecordList.GetRecord(ListIndex));
    ++Count;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }
  }

  DestroySrProgressDlg(pProgressDlg);
  SrLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordTogglequest()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordToggleignore ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordToggleignore() {
  CSrProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  int             ListIndex;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();

  if (SelectedCount > SREDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowSrProgressDlg("Toggle Ignore", "Toggling ignore flag of selected records...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  SrLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    OnToggleIgnoreRecord(m_RecordList.GetRecord(ListIndex));
    ++Count;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }
  }

  DestroySrProgressDlg(pProgressDlg);
  SrLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordToggleignore()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordToggledelete ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordToggledelete() {
  CSrProgressDlg* pProgressDlg = NULL;
  POSITION        ListPos;
  int             ListIndex;
  dword           Count = 0;
  dword           SelectedCount = m_RecordList.GetSelectedCount();

  if (SelectedCount > SREDIT_MINIMUM_PROGRESS_COUNT) {
    pProgressDlg = ShowSrProgressDlg("Toggle Delete", "Toggling delete flag of selected records...");
  }

  ListPos = m_RecordList.GetFirstSelectedItemPosition();
  SrLockUndoUpdates(true);

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    OnToggleDeleteRecord(m_RecordList.GetRecord(ListIndex));
    ++Count;

		/* Update the operation progress if required */
    if (pProgressDlg != NULL) {
      pProgressDlg->Update(Count * 100.0f / SelectedCount);
      if (pProgressDlg->GetIsCancelled()) break;
    }
  }

  DestroySrProgressDlg(pProgressDlg);
  SrLockUndoUpdates(false);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordToggledelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - bool OnToggleQuestRecord (pRecord);
 *
 *=========================================================================*/
bool CSrEditView::OnToggleQuestRecord (CSrRecord* pRecord) {
  CSrRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  pNewRecord = GetDocument()->GetRecordHandler().ToggleQuestFlag(pRecord);
  if (pNewRecord != NULL) GetDocument()->SetModifiedFlag(TRUE);

  return (true);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnToggleQuestRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - bool OnToggleIgnoreRecord (pRecord);
 *
 *=========================================================================*/
bool CSrEditView::OnToggleIgnoreRecord (CSrRecord* pRecord) {
  CSrRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  pNewRecord = GetDocument()->GetRecordHandler().ToggleIgnoreFlag(pRecord);
  if (pNewRecord != NULL) GetDocument()->SetModifiedFlag(TRUE);

  return (true);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnToggleIgnoreRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - bool OnToggleDeleteRecord (pRecord);
 *
 *=========================================================================*/
bool CSrEditView::OnToggleDeleteRecord (CSrRecord* pRecord) {
  CSrRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  pNewRecord = GetDocument()->GetRecordHandler().ToggleDeleteFlag(pRecord);
  if (pNewRecord != NULL) GetDocument()->SetModifiedFlag(TRUE);

  return (true);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnToggleDeleteRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnEditUndo ();
 *
 *=========================================================================*/
void CSrEditView::OnEditUndo() {
  CSrUndoItem* pUndoItem;
  CSrRecord*   pRecord;

	/* Get the item to undo, if any */
  pUndoItem = GetDocument()->GetRecordHandler().GetTopUndoItem();
  if (pUndoItem == NULL) return;

	/* TODO: Do in proper event handler? */
  pRecord = GetDocument()->GetRecordHandler().FindFormID(pUndoItem->GetNewFormID());
  //if (pRecord) m_DlgHandler.CloseAll(pRecord);

  if (pUndoItem->GetRecord() != NULL) {
    pRecord = GetDocument()->GetRecordHandler().FindFormID(pUndoItem->GetRecord()->GetFormID());
    //if (pRecord) m_DlgHandler.CloseAll(pRecord);
  }

  GetDocument()->GetRecordHandler().PerformUndo();
  //AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);
  
	/* TODO: Update by proper event handler? */
  UpdateContents();
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnUpdateEditUndo (pCmdUI);
 *
 *=========================================================================*/
void CSrEditView::OnUpdateEditUndo (CCmdUI* pCmdUI) {
  pCmdUI->Enable(GetDocument()->GetRecordHandler().GetNumUndoItems());
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnUpdateEditUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
 *
 *=========================================================================*/
void CSrEditView::OnActivateView (BOOL bActivate, CView* pActivateView, CView* pDeactiveView) {
/*  CDocument* pDoc1 = NULL;
  CDocument* pDoc2 = NULL;

  SystemLog.Printf("%s, Active = %p, Deactive = %p", bActivate ? "Activate" : "Deactivate", pActivateView, pDeactiveView);
  
  if (pActivateView != NULL) pDoc1 = pActivateView->GetDocument();
  if (pDeactiveView != NULL) pDoc2 = pDeactiveView->GetDocument();

  if (pDoc1 == NULL) {
     AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) NULL, 0);
  }
  else if (bActivate) {
    //AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &(((CSrEditDoc *)pDoc1)->GetRecordHandler().GetUndoItems()), 0);
  } //*/

//*	
  if (bActivate && pActivateView != NULL) {
    AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);
  }
  else if (pActivateView != NULL)  {
    //AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) 0, 0);
  } //*/

  CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnActivateView()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - int OnListenAddRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditView::OnListenAddRecord (CSrListenEvent* pEvent) {
  
  m_RecordList.UpdateRecord(pEvent->GetNewRecord(), NULL);
  m_RecordTree.IncludeInCounts(pEvent->GetNewRecord());

  AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnListenAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditView::OnListenCleanRecord (CSrListenEvent* pEvent) {

  m_RecordList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  //if (pEvent->GetOldRecord() != NULL) m_RecordTree.RemoveFromCounts(pEvent->GetOldRecord());
  if (pEvent->GetNewRecord() != NULL) m_RecordTree.IncludeInCounts(pEvent->GetNewRecord());

  AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditView::OnListenUpdateRecord (CSrListenEvent* pEvent) {

  m_RecordList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

  if (pEvent->GetNewRecord() != NULL) m_RecordTree.IncludeInCounts(pEvent->GetNewRecord());

  AfxGetMainWnd()->SendMessage(SRE_MSG_UPDATEUNDO, (WPARAM) &GetDocument()->GetRecordHandler().GetUndoItems(), 0);

  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - int OnListenPreUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrEditView::OnListenPreUpdateRecord (CSrListenEvent* pEvent) {
  
  m_RecordTree.RemoveFromCounts(pEvent->GetOldRecord());
  
  return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnListenPreUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_CheckRenameID (pString, pOrigString UserData);
 *
 * Callback function used by the input dialog called from OnRecordRename().
 *
 *=========================================================================*/
int l_CheckRenameID (const char* pString, const char* pOrigString, long UserData) {
  CSrMultiRecordHandler* pHandler = (CSrMultiRecordHandler *) UserData;
  CSString		 Buffer = pString;
  CSrRecord*		 pRecord;

  if (pHandler == NULL) return (SR_INPUTDLG_CHECK_OK);
  SrPrepareEditorID(Buffer);

  if (Buffer.CompareNoCase(pOrigString) == 0) return (SR_INPUTDLG_CHECK_NOCHANGE);

  pRecord = pHandler->FindEditorID(Buffer);
  if (pRecord != NULL) return (SR_INPUTDLG_CHECK_ERROR);

  return (SR_INPUTDLG_CHECK_OK);
}
/*===========================================================================
 *		End of Function l_CheckRenameID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordRename ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordRename() {
  CSrRecord*	pRecord;
  CSrIdRecord*	pIdRecord;
  CString		Buffer;
  CSString		EditorID;
  bool			Result;

  pRecord = m_RecordList.GetSelectedRecord();
  if (pRecord == NULL) return;
  pIdRecord = SrCastClass(CSrIdRecord, pRecord);
  if (pIdRecord == NULL) return;
  Buffer = pIdRecord->GetEditorID();

	/* Prompt user for a new editorid */
  Result = SrInputDialogValidate(Buffer, _T("Enter New EditorID"), _T("Enter a new editorid for the renamed record:"), l_CheckRenameID, (long) &GetDocument()->GetRecordHandler(), isalnum);
  if (!Result) return;

	/* Perform initial preparations on the new id */
  EditorID = Buffer;
  SrPrepareEditorID(EditorID);

	/* Ensure it has actually changed */
  if (pIdRecord->IsEditorID(EditorID)) return;
  
	/* Check for a valid editorid */
  Result = GetDocument()->GetRecordHandler().IsValidNewEditorID(Buffer);

  if (!Result) {
    SrEditShowLastError(_T("The new editorid is not valid!"));
    return;
  }

	/* Perform the rename */
  Result = GetDocument()->GetRecordHandler().RenameIDRecord(pIdRecord, EditorID);	
  if (Result) GetDocument()->SetModifiedFlag(TRUE);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordRename()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_CheckCopyID (pString, pOrigString, UserData);
 *
 * Callback function used by the input dialog called from OnRecordCreatecopy().
 *
 *=========================================================================*/
int l_CheckCopyID (const char* pString, const char* pOrigString, long UserData) {
  CSrMultiRecordHandler* pHandler = (CSrMultiRecordHandler *) UserData;
  CSString		 Buffer = pString;
  CSrRecord*		 pRecord;

  if (pHandler == NULL) return (SR_INPUTDLG_CHECK_OK);
  SrPrepareEditorID(Buffer);

  pRecord = pHandler->FindEditorID(Buffer);
  if (pRecord != NULL) return (SR_INPUTDLG_CHECK_ERROR);

  return (SR_INPUTDLG_CHECK_OK);
}
/*===========================================================================
 *		End of Function l_CheckCopyID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordCreatecopy ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordCreatecopy() {
  CSrRecord*	pRecord;
  CSrIdRecord*	pIdRecord;
  CString	Buffer;
  CSString	EditorID;
  bool		Result;

  pRecord = m_RecordList.GetSelectedRecord();
  if (pRecord == NULL) return;
  pIdRecord = SrCastClass(CSrIdRecord, pRecord);
  if (pIdRecord == NULL) return;
  Buffer = pIdRecord->GetEditorID();
  
	/* Prompt user for a new editorid */
  Result = SrInputDialogValidate(Buffer, _T("Enter New EditorID"), _T("Enter a new editorid for the record copy:"), l_CheckCopyID, (long) &GetDocument()->GetRecordHandler(), isalnum);
  
  if (!Result) return;

  	/* Perform initial preparations on the new id */
  EditorID = Buffer;
  SrPrepareEditorID(EditorID);

	/* Check for a valid editorid */
  Result = GetDocument()->GetRecordHandler().IsValidNewEditorID(Buffer);

  if (!Result) {
    SrEditShowLastError(_T("The new editorid is not valid!"));
    return;
  }

	/* Perform the rename */
  Result = GetDocument()->GetRecordHandler().CreateIDRecordCopy(pIdRecord, EditorID);	
  if (Result) GetDocument()->SetModifiedFlag(TRUE);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordCreatecopy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnRecordBatchedit ();
 *
 *=========================================================================*/
void CSrEditView::OnRecordBatchedit() {
  CSrRefRecordArray Records;
  CSrRecord*	    pRecord;
  POSITION	    ListPos;
  int		    ListIndex;

	/* Get the records to edit */
  ListPos = m_RecordList.GetFirstSelectedItemPosition();

  while (ListPos != NULL) {
    ListIndex = m_RecordList.GetNextSelectedItem(ListPos);
    pRecord   = m_RecordList.GetRecord(ListIndex);
    if (pRecord != NULL) Records.Add(pRecord);
  }

	/* Ignore if no records to edit */
  if (Records.GetSize() == 0) return;

  m_DlgHandler.BatchEdit(Records);
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnRecordBatchedit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnEditFind ();
 *
 *=========================================================================*/
void CSrEditView::OnEditFind() 
{
  m_DlgHandler.OpenFind();	
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditFind()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnHelpTestoutputeffects ();
 *
 *=========================================================================*/
void CSrEditView::OnHelpTestoutputeffects() {
	/*
  CSrFile		 OutputFile;
  CSrBaseRecord* pBaseRecord;
  CSrMgefRecord* pEffect;
  CSrTypeGroup*  pEffectGroup;
  obmgefdata_t*  pEffectData;
  dword			Index;
  bool			Result;

  pEffectGroup = GetDocument()->GetTopGroup()->GetTypeGroup(SR_NAME_MGEF);
  if (pEffectGroup == NULL) return;

  Result = OutputFile.Open("effects.csv", "wt");
  if (!Result) return;

  for (Index = 0; Index < pEffectGroup->GetNumRecords(); ++Index){
    pBaseRecord = pEffectGroup->GetRecord(Index); 

    pEffect = SrCastClass(CSrMgefRecord, pBaseRecord);
    if (pEffect == NULL) continue;

    pEffectData = pEffect->GetEffectData();
    if (pEffectData == NULL) continue;

    //OutputFile.Printf("%s, %s, ", pEffect->GetEditorID(), pEffect->GetFullName());
    //OutputFile.Printf("0x%08X, %f\n", pEffectData->Flags, pEffectData->BaseCost);
    //ADD_EFFECTVALUE( SR_MGEF_BAHE, "Bound Helmet")
    OutputFile.Printf("\tADD_EFFECTVALUE( SR_MGEF_%4.4s, \"%s\", 0x%08X )\n", pEffect->GetEditorID(), pEffect->GetFullName(), pEffectData->Flags);

  }
  */
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnHelpTestoutputeffects()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnHelpTestrecordsize ();
 *
 *=========================================================================*/
void CSrEditView::OnHelpTestrecordsize() {
  TGenPtrMap<srrectype_t, dword, dword > RecordSizes;
  CSrRecord*   pRecord;
  srrectype_t* pRecType;
  SRMAPPOS     Pos;
  MAPPOSITION  MapPos;
  dword*       pNewValue;
  dword	       TotalSize = 0;

  pRecord = GetDocument()->GetRecordHandler().GetFirstRecord(Pos);

  while (pRecord != NULL) {
    pNewValue = RecordSizes.Lookup(pRecord->GetRecordType());

    if (pNewValue != NULL) {
      //*pNewValue += pRecord->GetHeader().Size;
      *pNewValue += pRecord->GetSubrecordSize();
    }
    else {
      pNewValue  = new dword;
      //*pNewValue = pRecord->GetHeader().Size;
      *pNewValue = pRecord->GetSubrecordSize();
      RecordSizes.SetAt(pRecord->GetRecordType(), pNewValue);
    }

    //TotalSize += pRecord->GetHeader().Size;
    TotalSize += pRecord->GetSubrecordSize();
    pRecord = GetDocument()->GetRecordHandler().GetNextRecord(Pos);
  }

  pNewValue = RecordSizes.GetFirstRecord(MapPos);
  //TotalSize = 0;

  while (pNewValue != NULL) {
    pRecType = RecordSizes.GetPosKey(MapPos);
    //TotalSize += *pNewValue;

    if (pRecType != NULL) {
      float Ratio = (float) (((double)(*pNewValue)) / (double)TotalSize * 100.0);
      SystemLog.Printf("%4.4s = %u kb (%.1f%%)", pRecType->Name, *pNewValue/1000, Ratio);
    }
      
    pNewValue = RecordSizes.GetNextRecord(MapPos);
  }

  SystemLog.Printf("Total Size = %u kb", (dword)(TotalSize/1000));
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnHelpTestrecordsize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnTestCleanrecompileall ();
 *
 *=========================================================================*/
void CSrEditView::OnTestCleanrecompileall() {
/*
  CSrTypeGroup*     pScriptGroup;
  CSrBaseRecord*    pBaseRecord;
  CSrScptRecord*    pScript;
  CCustomCompiler   Compiler;
  srtimer_t         Timer;
  dword             Index;
  double            DeltaTime;
  bool              Result;
  dword		    TotalCount = 0;
  dword		    FailCount  = 0;

  pScriptGroup = GetDocument()->GetRecordHandler().GetTypeGroup(SR_NAME_SCPT);

  if (pScriptGroup == NULL) {
    AddSrGeneralError("No scripts in active file!");
    return;
  }

  SrStartTimer(Timer);

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = SrCastClass(CSrScptRecord, pBaseRecord);
    if (pScript == NULL) continue;

    Result = Compiler.Compile(pScript);
    if (!Result) ++FailCount;
    ++TotalCount;
  }

  DeltaTime = SrEndTimer(Timer);
  SystemLog.Printf("Compiled %u of %u scripts in active file in %g secs!", TotalCount-FailCount, TotalCount, DeltaTime);	
  */
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnTestCleanrecompileall()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnTestRecompileall ();
 *
 *=========================================================================*/
void CSrEditView::OnTestRecompileall() {
/*
  CSrTypeGroup*     pScriptGroup;
  CSrBaseRecord*    pBaseRecord;
  CSrScptRecord*    pScript;
  CCustomCompiler   Compiler;
  srtimer_t         Timer;
  dword             Index;
  double            DeltaTime;
  bool              Result;
  dword		    TotalCount = 0;
  dword		    FailCount  = 0;

  pScriptGroup = GetDocument()->GetRecordHandler().GetTypeGroup(SR_NAME_SCPT);

  if (pScriptGroup == NULL) {
    AddSrGeneralError("No scripts in active file!");
    return;
  }

  Compiler.SetRecordHandler(&GetDocument()->GetRecordHandler());
  Compiler.Load("testtable1.dat");
  GetSrEditApp().UpdateScriptColorOptions(Compiler, true);
  
  SrStartTimer(Timer);

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pScriptGroup->GetRecord(Index);
    pScript = SrCastClass(CSrScptRecord, pBaseRecord);
    if (pScript == NULL) continue;

    SystemLog.Printf("Compiling %s...", pScript->GetEditorID());

    Result = Compiler.Compile(pScript);

    ObOutputScriptErrorsToLog(Compiler.GetErrors());

    if (!Result) {
      SystemLog.Printf("Failed to compile script (%u errors, %u warnings)!", Compiler.GetErrorCount(), Compiler.GetWarningCount());
      ++FailCount;
    }
    else {
      SystemLog.Printf("Successfully compiled script (%u errors, %u warnings)!", Compiler.GetErrorCount(), Compiler.GetWarningCount());
    }

    ++TotalCount;
  }

  DeltaTime = SrEndTimer(Timer);
  SystemLog.Printf("Compiled %u of %u scripts in active file in %g secs!", TotalCount-FailCount, TotalCount, DeltaTime);
  */
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnTestRecompileall()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnHelpTestcomparescripts ();
 *
 *=========================================================================*/
void CSrEditView::OnHelpTestcomparescripts() {
/*
  CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, 
			"Plugin Files (*.esp)|*.esp|Master Files (*.esm)|*.esm|All Files (*.*)|*.*||", this);
  CSrSimpleRecordHandler EspFile;
  CSrCallback	         LoadCallback;
  CSrProgressDlg*        pProgressDlg;
  CSrTypeGroup*          pScriptGroup;
  CSrBaseRecord*         pRecord;
  CSrScptRecord*         pScript;
  srtimer_t              CompareTimer;
  obscriptcompare_t      CompareInfo;
  int                    DlgResult;  
  dword                  Index;
  int                    ScriptCount = 0;
  int                    ErrorCount  = 0;
  bool			 Result;

  FileDlg.m_ofn.lpstrTitle = "Select Plugin With Scripts To Compare";
  DlgResult = FileDlg.DoModal();
  if (DlgResult != IDOK) return;

  pProgressDlg = ShowSrProgressDlg(_T("Load"), _T("Loading Plugin File..."));
  LoadCallback.SetCallbackInterval(1);
  LoadCallback.SetFunction(SrEditDefaultProgressCallback);
  LoadCallback.SetUserPtr((void *) pProgressDlg);
  LoadCallback.Reset();
  LoadCallback.ForceCallback(0);

  Result = EspFile.Load(FileDlg.GetPathName(), &LoadCallback);
  DestroySrProgressDlg(pProgressDlg);
  if (!Result) return;

  SystemLog.Printf("Comparing all scripts in file '%s'...", FileDlg.GetPathName());
  SrStartTimer(CompareTimer);

  pScriptGroup = EspFile.GetTopGroup()->GetTypeGroup(SR_NAME_SCPT);

  if (pScriptGroup == NULL) {
    SystemLog.Printf("No scripts in file to compare!");
    return;
  }

  for (Index = 0; Index < pScriptGroup->GetNumRecords(); ++Index) {
    pRecord = pScriptGroup->GetRecord(Index);
    pScript = SrCastClass(CSrScptRecord, pRecord);
    if (pScript == NULL) continue;

    CompareInfo.pScript2 = pScript;

    pRecord = GetDocument()->GetRecordHandler().FindEditorID(pScript->GetEditorID());

    if (pRecord == NULL) {
      continue;
    }

    CompareInfo.pScript1 = SrCastClass(CSrScptRecord, pRecord);
    
    SystemLog.Printf("Comparing script %s (0x%06X, 0x%06X)...", pScript->GetEditorID(), pScript->GetFormID(), CompareInfo.pScript2->GetFormID());
    Result = ObCompareScripts(CompareInfo);

    if (!Result) {
      ++ErrorCount;
      SystemLog.Printf("\tERROR comparing script data!");
    }
    else {
      SystemLog.Printf("\tSuccessfully compared script data!");
    }

    ++ScriptCount;
  }

  SystemLog.Printf("Finished comparing %u scripts with %u errors in %g seconds.", ScriptCount, ErrorCount, SrEndTimer(CompareTimer));
*/
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnHelpTestcomparescripts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditView Event - void OnEditSelectall ();
 *
 *=========================================================================*/
void CSrEditView::OnEditSelectall() {
  int Index;

  for (Index = 0; Index < m_RecordList.GetItemCount(); ++Index) {
    m_RecordList.SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
  }

  m_RecordList.SetFocus();
}
/*===========================================================================
 *		End of Class Event CSrEditView::OnEditSelectall()
 *=========================================================================*/


void CSrEditView::OnMenuViewrawdata()
 {
	 CSrRawDataDlg Dlg(GetDocument()->GetRecordHandler());
	 CSrRecord* pRecord = m_RecordList.GetSelectedRecord();

	 if (pRecord == NULL) return;
	 Dlg.DoModal(pRecord);
 }


void CSrEditView::OnHelpTestoutputperks()
{
	CSrTypeGroup *pPerkGroup = GetDocument()->GetRecordHandler().GetTypeGroup(SR_NAME_PERK);
	CString Buffer;
	int Position;
	if ( pPerkGroup == NULL) return;

	SystemLog.Printf("Dumping PERKs...");

	for (dword i = 0; i < pPerkGroup->GetNumRecords(); ++i)
	{
		CSrBaseRecord* pRecord = pPerkGroup->GetRecord(i);
		CSrPerkRecord* pPerk = SrCastClassNull(CSrPerkRecord, pRecord);
		if (pPerk == NULL) continue;

		/*
		CSrSubrecord* pLastData = NULL;

		for (dword j = 0; j < pPerk->GetNumSubrecords(); ++j)
		{
			CSrSubrecord* pSubrecord = pPerk->GetSubrecord(j);

			if (pSubrecord->GetRecordType() == SR_NAME_DATA && pSubrecord->GetRecordSize() == 3)
			{
				pLastData = pSubrecord;
			}
			else if (pSubrecord->GetRecordType() == SR_NAME_EPFT && pLastData)
			{
				CString Buffer1;
				CString Buffer2;

				Buffer1.Format("%02X %02X %02X", (int) (pLastData->GetData()[0]), (int) (pLastData->GetData()[1]), (int) (pLastData->GetData()[2]));
				Buffer2.Format("%02X", (int) (pSubrecord->GetData()[0]));
				SystemLog.Printf("\t%32.32s: DATA %s EPFT %s", pPerk->GetEditorID(), Buffer1, Buffer2);
			}
		} //*/

		/*
		CSrSubrecord* pSubrecord = pPerk->FindFirstSubrecord(SR_NAME_EPFT, Position);

		while (pSubrecord)
		{
			Buffer.Empty();

			for (dword j = 0; j < pSubrecord->GetRecordSize(); ++j)
			{
				CString Tmp;
				Tmp.Format("%02X ", (dword) pSubrecord->GetData()[j]);
				Buffer += Tmp;
			}

			SystemLog.Printf("\t%32.32s(%02d): EPFT(%d bytes) = %s", pPerk->GetEditorID(), (dword)pPerk->GetHeader().Version, pSubrecord->GetRecordSize(), Buffer);
			pSubrecord = pPerk->FindNextSubrecord(SR_NAME_EPFT, Position);
		} //*/

		//*
		CSrSubrecord* pSubrecord = pPerk->FindFirstSubrecord(SR_NAME_PRKC, Position);

		while (pSubrecord)
		{
			Buffer.Empty();

			for (dword j = 0; j < pSubrecord->GetRecordSize(); ++j)
			{
				CString Tmp;
				Tmp.Format("%02X ", (dword) pSubrecord->GetData()[j]);
				Buffer += Tmp;
			}

			SystemLog.Printf("\t%32.32s(%02d): PRKC(%d bytes) = %s", pPerk->GetEditorID(), (dword)pPerk->GetHeader().Version, pSubrecord->GetRecordSize(), Buffer);
			pSubrecord = pPerk->FindNextSubrecord(SR_NAME_PRKC, Position);
		} //*/

		/*
		CSrSubrecord* pSubrecord = pPerk->FindFirstSubrecord(SR_NAME_PRKE, Position);

		while (pSubrecord)
		{
			Buffer.Empty();

			for (dword j = 0; j < pSubrecord->GetRecordSize(); ++j)
			{
				CString Tmp;
				Tmp.Format("%02X ", (dword) pSubrecord->GetData()[j]);
				Buffer += Tmp;
			}

			SystemLog.Printf("\t%32.32s(%02d): PRKE(%d bytes) = %s", pPerk->GetEditorID(), (dword)pPerk->GetHeader().Version, pSubrecord->GetRecordSize(), Buffer);
			pSubrecord = pPerk->FindNextSubrecord(SR_NAME_PRKE, Position);
		} //*/

		/*
		CSrSubrecord* pSubrecord = pPerk->FindFirstSubrecord(SR_NAME_DATA, Position);
		pSubrecord = pPerk->FindNextSubrecord(SR_NAME_DATA, Position);

		while (pSubrecord)
		{
			Buffer.Empty();

			for (dword j = 0; j < pSubrecord->GetRecordSize(); ++j)
			{
				CString Tmp;
				Tmp.Format("%02X ", (dword) pSubrecord->GetData()[j]);
				Buffer += Tmp;
			}

			SystemLog.Printf("\t%32.32s(%02d): DATA(%d bytes) = %s", pPerk->GetEditorID(), (dword)pPerk->GetHeader().Version, pSubrecord->GetRecordSize(), Buffer);
			pSubrecord = pPerk->FindNextSubrecord(SR_NAME_DATA, Position);
		} //*/
	}

}
/*
EPFT
	01 = Float
	02 = (float AV, float Factor)?
	04 =
		EPF2 = LString "verb" (feed) (optional)
		EPF3 = dword?
		EPFD = formid (optional)
	05 = SPEL?
	06 = GMST boolean string?
	07 = EPFD = LString "verb"

PRKC = Condition index?
	00 = Normal?
	01 = AND conditions?
	02 = ?

PRKE
	word U1
		0000
			Just a DATA (formid Qust, dword Stage?)
		0001
			Just a DATA (formid Record)
		0002
			Data (3 bytes) followed by other subrecords
	byte U2
		00, 03-22, 50, 100
		Index of some sort (can have duplicates)
		
		

struct data1		//Always present
{
	word NullBytes
	byte U1			//01 or 05
	byte U2			//00 or 01
	byte U3			//00 or 01
}



struct data2		//3 4 or 8 bytes
{
	dword ID1
	dword ID2
}

PRKE=2 (data2 = 3 bytes)
	struct data2-3
	{
		byte U1;
		byte U2;
		byte U3;
	}
	U2:
		01 = Absolute: New = EPFD
		02 = Additive: New = Old + EPFD
		03 = Factor:   New = Old * EPFD
		09 = Apply activate verb?
		0A = Cast spell?
		0B = Set GMST?
		0E = two floats: (ActorValue, SkillAdjustFactor)?
		0F = Apply activate verb?

	U3:
		01 = 
		02 = 
		03 =

	U1:
		00  ?
		01  Critical Damage (EPFD = dmg multiplier)
		02	Critical Chance (EPFD = percent chance increase)
		08  Buy price factor 
		0E  Apply custom activate verb? (EPF2 = Verb string)
		12  Backstab (EPFD = dmg mult/2, so EPFD=1.5 means a x3 dmg mult)
		14  Zoom factor (EPFD = zoom amount, 0.6) EagleEye
		15  Recover arrows (EPFD = Percent Chance?)
		16  Skill increase mod (EPFD = mult)
		1A  Bash damage mod (EPFD = mod)
		1B  Stamina cost mod (EPFD = mod)
		1C  Power attack damage mod (EPFD = mod)
		1D  Spell magnitude mod (EPFD = mod)
		1E  Spell duration mod (EPFD = mod)
		20  Armor weight+movement penalty mod (EPFD = weight mult)
		21  Player Stagger chance (EPFD = mult)
		22  Enemy staff chance (EPFD = mult)
		23  Damage mod (EPFD = mult)
		24  Received Damage mod (EPFD = amount) Abs
		25  Ignore armor (EPFD = factor, 0.5 = ignore 50%)
		26  Spell Cost (EPFD = mult)
		27  Blocking chance (EPFD = mult)
		28  Blocking damage mod? (EPFD = percent amount, 100 = 100% damage blocked)  
		29  Incoming spell dmg? (EPFD = mult)
		2B  Intimidation success mod (EPFD = mod)		
		2F  Detection mod? (EPFD = mod) MQ101IncreaseDetection
		30  Detection mod? (EPFD = mod) MQ101IncreaseDetection
		31  Soul charge mod (EPFD = percent factor?)
		32  Hit chance? (EPFD = chance, 1=100%?) sweep
		33  Hit cast spell? (EPFD = spell)
		34  Bash cast spell? (EPFD = spell)
		35  Spell cast spell? (EPFD = spell)
		36  Set GMST bool? (EPFD = GMST string)
		37  Casting noise mod? (EPFD = mult)
		38  Pickpocket
		39  Stealth
		3A  Falling damage mod (EPFD = mod)
		3B  Lockpicking easier mod? (EPFD = mod, 1.6 = 60% easier)
		3C  Sell price mod
		3D  Pickpocket equipped wepons (EPFD = bool)
		3F  Lockpick starts closer (EPFD = percent closer? 45)
		41  Lockpicking
		42  Alchemy
		43  Is attacking? QuickReflexes
		44  Number of raised dead mod (EPFD = mult or count?)
		45  Sneak cast spell (EPFD = spell)
		46  Set something (QuickReflexes)
		47  Spell absorb mod? (EPFD = chance or effect? 0.25 = ?)  
		48  Eating ingredient effect count (EPFD = number of effects to show) 
		49  Potion Purity? (EPFD = effect chance? 1 = 100%)
		4A  Door access? (EPFD = bool)
		4B  Permit dual casting? (EPFD = bool) 
		4C  Armor smithing mod (EPFD = mod)
		4D  Enchantment effect mod (EPFD = mod)
		4E  Weapon recharge on creature death (EPFD = soul absorb amount, 0.05 = 5%)
		50  Enchant effect count (EPFD = effect count)
		51	EPFT=7, EPFD=verb lstring "feed" (werewolf feed)
		52  Allow shouts? (EPFD = bool, 1=allow?)
		53  Poison hit count (EPFD = number of hits)
		54  Permit placing poisons with PP? (EPFD = bool)
		55  Armor rating (EPFD = armor mod, 1.8 = +80%)
		56  Lockpick noise mod? (EPFD = noise mod)
		57  Gather plant count (EPFD = number of ingredients gathered)
		58  Summon range (EPFD = range mod)
		59  Create duplicate potion? (EPFD = float, 1.0?) NN01Perk
		5A  Make wax key (EPFD = percent chance? 100 = 100%)


*/


void CSrEditView::OnBnClickedActivecheck()
{
	bool Check = m_ActiveCheck.GetCheck() != 0;

	m_RecordList.GetExtraFilter().ActiveOnly = Check;
	m_RecordTree.GetExtraFilter().ActiveOnly = Check;

	//UpdateContents();
	m_RecordList.DeleteAllItems();
	m_RecordList.AddAllRecords(GetDocument()->GetRecordHandler().GetTopGroup());
	m_UpdateFilterCounts = true;
}


void CSrEditView::OnEnChangeFiltertext()
{
	CString Buffer;

	m_FilterText.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	
	if (Buffer.CompareNoCase(m_RecordList.GetExtraFilter().FilterText.c_str()) == 0) return;

	m_RecordList.GetExtraFilter().FilterText = Buffer;
	m_RecordTree.GetExtraFilter().FilterText = Buffer;

	//UpdateContents();
	m_RecordList.DeleteAllItems();
	m_RecordList.AddAllRecords(GetDocument()->GetRecordHandler().GetTopGroup());
	m_UpdateFilterCounts = true;
	//m_RecordTree.UpdateFilterCounts(GetDocument()->GetRecordHandler().GetTopGroup());
}



void CSrEditView::ThreadUpdateFilterProc (void)
{

	while (1)
	{
		DWORD dwWaitResult = WaitForSingleObject(m_ThreadCloseEvent, 1000);

		if (dwWaitResult == WAIT_OBJECT_0) 
		{
			break;
		}
        
		if (m_UpdateFilterCounts)
		{
			m_UpdateFilterCounts = false;
			m_RecordTree.UpdateFilterCounts(GetDocument()->GetRecordHandler().GetTopGroup());
		}
	}

	ExitThread(0);
}



void CSrEditView::OnTimer(UINT_PTR nIDEvent)
{
	__super::OnTimer(nIDEvent);
}


void CSrEditView::OnClose()
{
	__super::OnClose();
}
