/*===========================================================================
 *
 * File:		SrBodypartslistdlg.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRBODYPARTSLISTDLG_H
#define __SRBODYPARTSLISTDLG_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/srespfile.h"
  #include "resource.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrBodyPartsDlg Definition
 *
 *=========================================================================*/
class CSrBodyPartsDlg : public CDialog {

  /*---------- Begin Protected Class Members ----------------*/
protected:
  dword		m_BodyParts;
  CButton	m_BodyButtons[16];


  /*---------- Begin Public Class Methods ------------------*/
public:

	/* Constructor */
  CSrBodyPartsDlg(CWnd* pParent = NULL);
  
	/* Get class members */
  dword GetBodyParts (void) { return (m_BodyParts); }

	/* Set class members */
  void SetBodyParts (const dword Flags) { m_BodyParts = Flags; }

	/* Get/Set control data */
  void GetControlData (void);
  void SetControlData (void);


  //{{AFX_DATA(CSrBodyPartsDlg)
  enum { IDD = IDD_BODYPARTS_DLG };
  CListBox	m_PartsList;
  //}}AFX_DATA

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CSrBodyPartsDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  //}}AFX_VIRTUAL

protected:

		/* Generated message map functions */
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  
  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrBodyPartsDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Show a model biped parts dialog */
  bool SrEditBodyPartsDlg (dword& BodyParts);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrBodypartslistdlg.H
 *=========================================================================*/
