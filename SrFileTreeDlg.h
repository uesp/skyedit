/*===========================================================================
 *
 * File:	Obfiletreedlg.H
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	August 4, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFILETREEDLG_H
#define __OBFILETREEDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrFileTreeDlg
 *
 *=========================================================================*/
class CSrFileTreeDlg : public CDialog {

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  //CSrEspFile*	m_pEspFile;
  CSrGroup*	m_pTopGroup;


  /*---------- Begin Protected Class Methods ----------------------*/
protected:  

	/* Create the tree contents */
  void CreateTree (void);
  void CreateTree (CSrGroup* pTopGroup, HTREEITEM hParent);

  void AddTreeRecord        (CSrBaseRecord* pBaseRecord, HTREEITEM hParent);
  void AddTreeGroupChildren (CSrGroup* pGroup, HTREEITEM hParent);

  void AddTreeGroup       (CSrGroup*       pGroup, HTREEITEM hParent);
  void AddTreeTypeGroup   (CSrTypeGroup*   pGroup, HTREEITEM hParent);
  void AddTreeFormIDGroup (CSrFormIDGroup* pGroup, HTREEITEM hParent);
  void AddTreeBlockGroup  (CSrBlockGroup*  pGroup, HTREEITEM hParent);
  void AddTreeGridGroup   (CSrGridGroup*   pGroup, HTREEITEM hParent);



  /*---------- Begin Public Class Methods -------------------------*/
public:

	/* Constructor */
  CSrFileTreeDlg(CWnd* pParent = NULL);

	/* Set class members */
  //void SetEspFile (CSrEspFile* pFile) { m_pEspFile = pFile; }
  void SetTopGroup (CSrGroup* pGroup) { m_pTopGroup = pGroup; }


	/* Dialog Data */
  //{{AFX_DATA(CSrFileTreeDlg)
  enum { IDD = IDD_FILETREE_DLG };
  CTreeCtrl	m_FileTree;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrFileTreeDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CSrFileTreeDlg)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrFileTreeDlg
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obfiletreedlg.H
 *=========================================================================*/
