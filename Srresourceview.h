/*===========================================================================
 *
 * File:		Srresourceview.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRRESOURCEVIEW_H
#define __SRRESOURCEVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "srimagectrl.h"
  #include "bsafile/srresourcehandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Custom window messages */
  #define ID_SRRESOURCE_CHECKDROP (WM_APP + 901)
  #define ID_SRRESOURCE_DROP      (WM_APP + 902)

	/* Return values from notify messages */
  #define SRRESOURCE_DROPCHECK_OK	2345
  #define SRRESOURCE_DROPCHECK_ERROR	5432
  #define SRRESOURCE_DROPCHECK_NOCHANGE 2346

	/* Default main resource paths */
  #define SRRESOURCE_PATH_TEXTURES	"textures\\"
  #define SRRESOURCE_PATH_MESHES	"meshes\\"
  #define SRRESOURCE_PATH_SOUNDS	"sound\\"

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  struct srrespreviewinfo_t {
	CSrResourceInstance*	pInstance;
	CString			Filename;
	int64			Filesize;
	int64			StartOffset;
	bool			PlainFile;
  };

	/* Used to test drop targets */
  struct obresourcedropinfo_t {
   	NMHDR			Notify;
   	CSrResourceFile*	pResourceFile;
	dword			ParentThread;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrResourceView Definition
 *
 *=========================================================================*/
class CSrResourceView : public CFormView {
  DECLARE_DYNCREATE(CSrResourceView);

  /*---------- Begin Protected Class Members ------------------------------*/
protected:
  CSrResourceHandler*	m_pResourceHandler;	/* References to resource objects */
  CSrBsaFileArray*	m_pBsaFiles;

  CSrResourceInstance*	m_pCurrentInstance;
  CImageList		m_ImageList;

  CSrResourceFile*	m_pDragResource;
  CImageList*		m_pDragImage;
  bool			m_IsDragging;
  HCURSOR		m_hGoodDropCursor;
  HCURSOR		m_hBadDropCursor;
  bool			m_LastDropValid;
  CWnd*			m_pLastDropWnd;

  bool			m_EnablePreview;

  CBitmap		m_Bitmaps[10];


  /*---------- Begin Protected Class Methods ------------------------------*/
protected:

	/* Create from serialization only */
  CSrResourceView();

	/* Update helpers */
  void      FillResourceTree   (void);
  void      FillResourceTree   (CSrResourceFolder* pFolder, HTREEITEM hParent);
  HTREEITEM AddResourceTree    (CSrResourceFile* pFile, HTREEITEM hParent);
  void      UpdateResourceTree (CSrResourceFile* pFile, HTREEITEM hItem);

  void ClearDisplayedInstance  (void);
  void UpdateDisplayedInstance (void);

  void PreviewInstance (CSrResourceInstance* pInstance);
  void PreviewImage    (CSrResourceInstance* pInstance, srrespreviewinfo_t& PreviewInfo);
  void PreviewUnknown  (CSrResourceInstance* pInstance, srrespreviewinfo_t& PreviewInfo);
  void PreviewText     (CSrResourceInstance* pInstance, srrespreviewinfo_t& PreviewInfo);
  void ClearPreview    (void);

  void CleanupDrag    (void);
  int  SendDropNotify (CPoint Point, const int MessageID);


  /*---------- Begin Public Class Methods ---------------------------------*/
public:
	/* Destructor */
  virtual ~CSrResourceView();

	/* Set class members */
  void SetEnablePreview   (const bool              Flag) { m_EnablePreview    = Flag; }
  void SetResourceHandler (CSrResourceHandler* pHandler) { m_pResourceHandler = pHandler; }
  void SetBsaFileArray    (CSrBsaFileArray*      pArray) { m_pBsaFiles        = pArray; }

	/* Find and select a particular resource */
  bool SelectResource (const char* pResource);


	/* Resource members */
  //{{AFX_DATA(CSrResourceView)
  enum { IDD = IDD_RESOURCE_VIEW };
  CRichEditCtrl	m_PreviewText;
  CEdit		m_Filetime;
  CEdit		m_Filesize;
  CEdit		m_Filename;
  CStatic	m_HBar;
  CTreeCtrl	m_ResourceTree;
  CSrImageCtrl  m_PreviewImage;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrResourceView)
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnInitialUpdate();
  //}}AFX_VIRTUAL

// Implementation
public:


#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CSrResourceView)
  afx_msg void OnDblclkResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSelchangedResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnBegindragResourceTree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnCaptureChanged(CWnd *pWnd);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnHelp (void);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrResourceView Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obresourceview.H
 *=========================================================================*/
 
