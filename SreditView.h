/*===========================================================================
 *
 * File:		SReditView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Interface of the CSrEditView class.
 *
 *=========================================================================*/
#ifndef __SREDITVIEW_H
#define __SREDITVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "windows/srrecordlistctrl.h"
  #include "windows/srrecordvirtuallistctrl.h"
  #include "windows/srrecordtreectrl.h"
  #include "modfile/srexport.h"
  #include "dialogs/sreditdlghandler.h"
  #include "srresourceview.h"
  #include "il/il.h"
  #include "il/ilu.h"
  #include "il/ilut.h"
#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* File filters for the open/save dialog */
  #define SREDIT_CSV_FILTER _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||")

	/* Default file extensions */
  #define SREDIT_CSV_EXT _T("csv")

	/* Number of operations required for a progress dlg to be shown */
  #define SREDIT_MINIMUM_PROGRESS_COUNT 100

  #define SREDIT_FILTERUPDATE_TIMERID 0x1234

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrEditView Definition
 *
 *=========================================================================*/
class CSrEditView : public CFormView, public ISrListener {

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  CSrEditDlgHandler	m_DlgHandler;		/* Handles all child windows */

  bool				m_IsInitialized;	/* Has the view been initialized yet? */

  CSrRecordFilter*	m_pCurrentFilter;	/* Currently displayed record filter */
  CSString			m_LastFilterID; 
  bool				m_UpdateFilterCounts;
  DWORD				m_hFilterUpdateThreadID;
  HANDLE			m_hFilterUpdateThread;
  HANDLE			m_ThreadCloseEvent;


  /*---------- Begin Protected Class Methods ----------------------*/
protected: 

	/* Create from serialization only */
  CSrEditView();
  DECLARE_DYNCREATE(CSrEditView)


public:
  enum { IDD = IDD_SREDIT_FORM };
  CStatic					m_VertEdge;
  CSrRecordVirtualListCtrl	m_RecordList;
  CSrRecordTreeCtrl			m_RecordTree;


  /*---------- Begin Public Class Methods --------------------------*/
public:

	/* Class destructor */
  virtual ~CSrEditView();

  void ThreadUpdateFilterProc (void);

	/* Get the parent document */
  CSrEditDoc*        GetDocument();
  CSrEditDlgHandler& GetDlgHandler (void) { return m_DlgHandler; }

	/* Helper export methods */
  bool OnCsvExport (srexportinfo_t& ExportInfo, const TCHAR* pDialogTitle);

	/* Update events */
  void OnEditRecord (CSrRecord* pRecord);

	/* Listener events */
  virtual int OnListenAddRecord       (CSrListenEvent* pEvent);
  virtual int OnListenCleanRecord     (CSrListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CSrListenEvent* pEvent);
  virtual int OnListenPreUpdateRecord (CSrListenEvent* pEvent);
  virtual int GetListenEvents         (void) { return (SR_EVENTMASK_ALL); }

  bool OnToggleDeleteRecord (CSrRecord* pRecord);
  bool OnToggleIgnoreRecord (CSrRecord* pRecord);
  bool OnToggleQuestRecord  (CSrRecord* pRecord);

	/* Updates the main view content display */
  void UpdateContents (void);


	/* Diagnostics */
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
  virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnSelchangedRecordtree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnFileImportCsv();
  afx_msg void OnFileExportcsvSelecteditems();
	afx_msg void OnRecordtreeReload();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRecordtreeExporttocsv();
	afx_msg void OnViewFilestructure();
	afx_msg void OnFileExportCsvexteriorlocations();
	afx_msg void OnFileExportCsvExtMapMarkers();
	afx_msg void OnHelpTestfieldlookup();
	afx_msg void OnFileExportCsvexportexteriorplants();
	afx_msg void OnEditFindbinarydata();
	afx_msg void OnHelpTestfindformid();
	afx_msg void OnTestMemoryspeed();
	afx_msg void OnTestTokenscripts();
	afx_msg void OnRecordClean();
	afx_msg void OnUpdateHasSelectedRecords(CCmdUI* pCmdUI);
	afx_msg void OnRecordMoveactive();
	afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy (void);
	afx_msg void OnMenuEditrecord();
	afx_msg void OnEditNewrecord();
	afx_msg void OnRecordTogglequest();
	afx_msg void OnRecordToggleignore();
	afx_msg void OnRecordToggledelete();
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnRecordRename();
	afx_msg void OnRecordCreatecopy();
	afx_msg void OnRecordBatchedit();
	afx_msg void OnEditFind();
	afx_msg void OnHelpTestoutputeffects();
	afx_msg void OnHelpTestrecordsize();
	afx_msg void OnTestCleanrecompileall();
	afx_msg void OnTestRecompileall();
	afx_msg void OnHelpTestcomparescripts();
	afx_msg void OnEditSelectall();

  DECLARE_MESSAGE_MAP();

 public:
	 afx_msg void OnMenuViewrawdata();
	 afx_msg void OnHelpTestoutputperks();
	 CEdit m_FilterText;
	 CButton m_ActiveCheck;
	 afx_msg void OnBnClickedActivecheck();
	 afx_msg void OnEnChangeFiltertext();
	 afx_msg void OnTimer(UINT_PTR nIDEvent);
	 afx_msg void OnClose();
	 afx_msg void OnEditUselocalstrings();
	 afx_msg void OnUpdateEditUselocalstrings(CCmdUI *pCmdUI);
	 afx_msg void OnEditSetmodauthor();
	 afx_msg void OnEditSetmoddescription();
	 afx_msg void OnMenuViewsummary();
};
/*===========================================================================
 *		End of Class CSrEditView Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Inline Class Methods
 *
 *=========================================================================*/
#ifndef _DEBUG
  inline CSrEditDoc* CSrEditView::GetDocument() {
    return (CSrEditDoc*)m_pDocument; }
#endif
/*===========================================================================
 *		End of Inline Class Methods
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File View.H
 *=========================================================================*/
