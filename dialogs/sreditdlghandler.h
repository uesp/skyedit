/*===========================================================================
 *
 * File:		Sreditdlghandler.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	6 December 2011
 *
 * Defines the CSrEditDlgHandler class used for handling all child windows
 * to the main view.
 *
 *=========================================================================*/
#ifndef __SREDITDLGHANDLER_H
#define __SREDITDLGHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/srmultirecordhandler.h"
  #include "srrecorddialog.h"
  #include "../childfrm.h"
  #include "resource.h"
  #include "../srresourceview.h"

  #include "srpromptdlg.h"
  #include "srinputdialog.h"

  #include "srselectrecorddlg.h"
  #include "srbatcheditdlg.h"
  #include "srfinddlg.h"

  #include "srcobjview.h"
  #include "srglobview.h"
  #include "srgmstview.h"
  #include "srkywdview.h"
  #include "srmgefview.h"
  #include "srweapview.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Record rename/copy results */
  #define SREDIT_RECORDPROMPT_CANCEL	0
  #define SREDIT_RECORDPROMPT_COPY	1
  #define SREDIT_RECORDPROMPT_RENAME	2

	/* Flags for the ObFillComboList function */
  #define SRE_FILLCOMBO_NODUPLICATES	1
  #define SRE_FILLCOMBO_INCLUDENULL	2
  #define SRE_FILLCOMBO_FORCEEMPTY	4

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used to create a dialog */
  struct srdlgcreateinfo_t 
  {
	const srrectype_t*	pRecordType;
	const TCHAR*		pTitlePrefix;
	int					ResourceID;
	CRuntimeClass*		pViewClass;
	CRuntimeClass*		pFrameClass;
	const TCHAR*		pUESPPage;
	const TCHAR*		pCSPage;
  };

	/* Holds information about a currently open dialog */
  struct srdlginfo_t 
  {
	CFrameWnd*			pFrameWnd;		/* The frame window object for the dialog */
	srdlgcreateinfo_t*	pCreateInfo;	/* The creation informatio used to create the dialog */
	CSrRecordDialog*	pRecordDlg;		/* The object for a record dialog */

  };

  typedef CSrPtrArray<srdlginfo_t> CSrDlgInfoArray;

	/* Forward class definitions */
  class CSrEditDoc;

	/* Options */
  struct srdlghandleroptions_t 
  {
	bool		EnableWebHelp;
	bool		UseUESPWikiHelp;
	CSString	CSWikiPrefix;
	CSString	UESPWikiPrefix;
	CSString	DefaultCSPage;
	CSString	DefaultUESPPage;

	srdlghandleroptions_t() 
	{
		EnableWebHelp   = true;
		UseUESPWikiHelp = true;
		CSWikiPrefix    = "http://cs.elderscrolls.com/constwiki/index.php/";
		UESPWikiPrefix  = "http://www.uesp.net/wiki/";
		DefaultCSPage   = "";
		DefaultUESPPage = "Tes5Mod:SkyEdit";
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrEditDlgHandler Definition
 *
 * Handles all child windows of the main view (record dialogs, find, etc...).
 *
 *=========================================================================*/
class CSrEditDlgHandler : public ISrListener {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSrDlgInfoArray	m_OpenDialogs;		/* List of currently open dialogs */

  CSrEditDoc*		m_pDocument;		/* Current document */

	/* Dialog handler options */
  static srdlghandleroptions_t m_Options;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper close method */
  void Close (srdlginfo_t* pDlgInfo);

	/* Creates a new dialog according to the given creation info */
  srdlginfo_t* CreateDlg (srdlgcreateinfo_t& CreateInfo);
  srdlginfo_t* CreateDlg (const srrectype_t  RecordType);
  srdlginfo_t* CreateDlg (sreditrecinfo_t&   EditInfo);

  	/* Find an open dialog */
  srdlginfo_t* FindOpenDlg (CFrameWnd*       pFrameWnd);
  srdlginfo_t* FindOpenDlg (CSrRecord*       pRecord);
  srdlginfo_t* FindOpenDlg (CRuntimeClass*   pRuntimeClass);
  srdlginfo_t* FindOpenDlg (CSrRecordDialog* pRecordDlg);

	/* Finds a creation object for the given record type */
  static srdlgcreateinfo_t* FindCreateInfo (const srrectype_t RecordType);



  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CSrEditDlgHandler();
  virtual ~CSrEditDlgHandler() { Destroy(); }
  virtual void Destroy (void);

	/* Batch edit a group of similar records */
  bool BatchEdit (CSrRefRecordArray& Records);

	/* Force all open dialogs to close */
  void  CloseAll (void);
  dword CloseAll (CSrRecord* pRecord, const long Source = 0);

	/* Edits a record */
  bool EditRecord    (sreditrecinfo_t&  EditInfo);
  bool EditRecord    (CSrRecord*        pRecord);
  bool EditRecord    (const srformid_t  FormID);
  bool EditNewRecord (const srrectype_t RecordType);

	/* Get class members */
  CSrEditDoc*  GetDocument (void) { return (m_pDocument); }
  const TCHAR* GetTitle    (void); 

	/* Access the static options member */
  static srdlghandleroptions_t& GetOptions (void) { return (m_Options); }

	/* Record edit events */
  virtual int OnPreSaveRecord    (sreditrecinfo_t& EditInfo);
  virtual int OnPostSaveRecord   (sreditrecinfo_t& EditInfo);
  virtual int OnCancelEditRecord (sreditrecinfo_t& EditInfo);

	/* Other events */
  virtual bool OnHelp (CSrRecordDialog* pDialog, HELPINFO* pHelpInfo);

  	/* Listener events */
  virtual int OnListenAddRecord       (CSrListenEvent* pEvent);
  virtual int OnListenCleanRecord     (CSrListenEvent* pEvent);
  virtual int OnListenUpdateRecord    (CSrListenEvent* pEvent);
  virtual int OnListenPreUpdateRecord (CSrListenEvent* pEvent);
  virtual int GetListenEvents         (void) { return (SR_EVENTMASK_ALL); }

	/* Prompt user to rename or copy a changed record */
  int PromptRenameCopy (sreditrecinfo_t& EditInfo);

	/* Remove a frame from the list of currently opened frames */
  void RemoveFrame (CFrameWnd* pFrameWnd);

	/* Open a find dialog */
  bool OpenFind (void);

  	/* Set class members */
  void SetDocument (CSrEditDoc* pDoc) { m_pDocument = pDoc; }

	/* Item selection dialogs */
  bool SelectItemScript     (CString& EditorID);
  bool SelectActor          (CString& EditorID);
  bool SelectApparelEnchant (CString& EditorID);
  bool SelectIngrediant     (CString& EditorID);
  bool SelectScrollEnchant  (CString& EditorID);
  bool SelectSound          (CString& EditorID);
  bool SelectStaffEnchant   (CString& EditorID);
  bool SelectWeaponEnchant  (CString& EditorID);
  bool SelectKeyword		(CString& EditorID);
  bool SelectKeyword        (CString& EditorID, const char* pFilter);
  bool SelectComponent      (CString& EditorID);

	/* Resource selection */
  bool SelectModel     (const char* pString);
  bool SelectIcon      (const char* pString);
  bool SelectSoundFile (const char* pString);

};
/*===========================================================================
 *		End of Class CSrEditDlgHandler Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Find items in a list */
  int FindListBoxItemData  (CListBox&  ListBox,  const dword ItemData, const bool SelectItem = false);
  int FindComboBoxItemData (CComboBox& ComboBox, const dword ItemData, const bool SelectItem = false);
  int FindComboBoxEffect   (CComboBox& ComboBox, const srrectype_t EffectType, const bool SelectItem = false);
  int FindComboBoxString   (CComboBox& ComboBox, const TCHAR* pString, const bool SelectItem = false);
  int SrAddComboBoxItem    (CComboBox& ComboBox, const TCHAR* pString, const dword ItemData);
  int SrAddListBoxItem     (CListBox&  ListBox,  const TCHAR* pString, const dword ItemData);

  dword GetComboBoxSelItemData (CComboBox& ComboBox, const dword Default = 0);
  dword GetListBoxSelItemData  (CListBox&  ListBox,  const dword Default = 0);

	/* Create list contents */
  bool SrFillComboList       (CComboBox& ComboBox, const stringvalue_t* pStringValues, const dword Flags);
  bool SrFillEffectComboList (CComboBox& ComboBox, const dword Flags, const dword EffectFlagMask, const dword InvalidEffectFlagMask);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/

  
#endif
/*===========================================================================
 *		End of File Sreditdlghandler.H
 *=========================================================================*/
