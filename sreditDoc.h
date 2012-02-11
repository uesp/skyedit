/*===========================================================================
 *
 * File:		SrbeditDoc.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Definition of the CSrEditDoc document class.
 *
 *=========================================================================*/
#ifndef __SREDITDOC_H
#define __SREDITDOC_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "common/csvfile.h"
  #include "modfile/srsimplerecordhandler.h"
  #include "modfile/srmultirecordhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* View update hints */
   #define SREDIT_DOC_HINT_UPDATEALL	 8001
   #define SREDIT_DOC_HINT_GETDATA		 8002
   #define SREDIT_DOC_HINT_CLEARFILTERS  8003
   #define SREDIT_DOC_HINT_UPDATEFILTERS 8004
   #define SREDIT_DOC_HINT_UPDATERECORD  8005
   #define SREDIT_DOC_HINT_ADDRECORD     8006

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used for view updates */
  class srrecupdateinfo_t : public CObject 
  {
	public:
		CSrRecord*	pOldRecord;
		CSrRecord*	pNewRecord;
  };
  
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrEditDoc Definition
 * 
 *=========================================================================*/
class CSrEditDoc : public CDocument {

  /*---------- Begin Protected Class Members --------------------------*/
protected:
  CSrMultiRecordHandler	m_RecordHandler;

  bool					m_HasActiveContent;


  /*---------- Begin Protected Class Methods --------------------------*/
protected:
	
	/* Create from serialization only */
  CSrEditDoc();
  DECLARE_DYNCREATE(CSrEditDoc)


  /*---------- Begin Public Class Methods -----------------------------*/
public:

	/* Destructor */
  virtual ~CSrEditDoc();

	/* Find operations */
  dword Search (srfinddata_t& FindData, CSrCallback* pCallback) { return m_RecordHandler.Search(FindData, pCallback); }

	/* Get class members */
  CSrEspFile&				GetActiveFile    (void) { return (m_RecordHandler.GetActiveFile()); }
  CSrGroup*					GetTopGroup      (void) { return m_RecordHandler.GetTopGroup(); }
  CSrMultiRecordHandler&	GetRecordHandler (void) { return (m_RecordHandler); }

	/* Backup methods */
  bool DoSaveBackup     (const char* pFilename);

  static bool DoBackup         (const char* pFilename);
  static bool MakeBackupFile   (CString& OutputFile, CString& InputFile);
  static bool CreateBackupPath (void);
  static bool CheckBackups     (const char* OldestFile, const dword BackupCount, const int64 BackupSize);


	/* Diagnostics */
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrEditDoc)
public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);
  virtual void DeleteContents();
  virtual BOOL OnOpenDocument (LPCTSTR lpszPathName);
  virtual BOOL OnSaveDocument (LPCTSTR lpszPathName);
  virtual BOOL DoFileSave();
  //}}AFX_VIRTUAL


	/* Generated message map functions */
protected:
  //{{AFX_MSG(CSrEditDoc)
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

 };
/*===========================================================================
 *		End of Class CSrEditDoc Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File SrEditDoc.H
 *=========================================================================*/
