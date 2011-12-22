/*===========================================================================
 *
 * File:		Srloaddlg.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRLOADDLG_H
#define __SRLOADDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/srespfile.h"
  #include "common/srutils.h"
  #include "modfile/srmultirecordhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* File list subitems indices */
  #define SRFILELIST_FILENAME     0
  #define SRFILELIST_DATE         1
  #define SRFILELIST_SIZE         2
  #define SRFILELIST_DEFAULTSORT  3

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  struct srloadfilesortinfo_t 
  {
	bool Reverse;
	int  SortType;
  };

	/* Used to hold information of files in the list */
  struct srloaddlgfileinfo_t 
  {
		WIN32_FIND_DATA FindData;
		CString			Path;
		bool			IsActive;
		bool			IsMaster;
  };

  typedef CSrPtrArray<srloaddlgfileinfo_t>    CSrLoadDlgFileInfos;
  typedef CSrRefPtrArray<srloaddlgfileinfo_t> CSrRefLoadDlgFileInfos;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrLoadDlg Definition
 *
 *=========================================================================*/
class CSrLoadDlg : public CDialog 
{

  /*---------- Protected Class Members ---------------------------------*/
protected:
  CSrLoadDlgFileInfos	m_FileInfos;		/* Holds file information */
  srloaddlgfileinfo_t*  m_pLastActiveFile;

  srfileloadinfo_t		m_LoadInfo;

  bool					m_LastSortReverse;
  int					m_LastSortSubItem;


public:
	static CStringArray	s_ExtraFilePaths;


  /*---------- Protected Class Methods ---------------------------------*/
protected:

	/* Populate the file list with plugins */
  void FillFileList (void);
  int  FillFileList (const char* pPath, const char* pFileSpec);
  void AddFile      (const char* pPath, WIN32_FIND_DATA& FindData);
  void UpdateFile   (const int ListIndex, srloaddlgfileinfo_t* pFileData);

	/* Create the loadinfo structure from the current list */
  void CreateLoadInfo (void);


  /*---------- Public Class Methods ------------------------------------*/
public:

	/* Construction */
  CSrLoadDlg (CWnd* pParent = NULL);

	/* Get class members */
  srfileloadinfo_t& GetLoadInfo (void) { return (m_LoadInfo); }

	/* Dialog Data */
  //{{AFX_DATA(CSrLoadDlg)
  enum { IDD = IDD_LOAD_DLG };
  CListCtrl	m_FileList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrLoadDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual void OnOK();
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrLoadDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnColumnclickFileList(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetactive();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrLoadDlg Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Srloaddlg.H
 *=========================================================================*/
