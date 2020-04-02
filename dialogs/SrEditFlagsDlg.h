/*===========================================================================
 *
 * File:		SrEditFlagsDlg.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	13 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SREDITFLAGSDLG_H
#define __SREDITFLAGSDLG_H


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
 * Begin Class CSrEditFlagsDlg Definition
 *
 *=========================================================================*/
class CSrEditFlagsDlg : public CDialog {

  /*---------- Begin Protected Class Members ----------------*/
protected:
  dword		m_Flags;
  dword		m_Mask;


  /*---------- Begin Public Class Methods ------------------*/
public:

	/* Constructor */
  CSrEditFlagsDlg(CWnd* pParent = NULL);
  
	/* Get class members */
  dword GetFlags (void) { return m_Flags; }

	/* Set class members */
  void SetFlags (const dword Flags) { m_Flags = Flags; }
  void SetMask  (const dword Mask) { m_Mask = Mask; }

	/* Get/Set control data */
  void GetControlData (void);
  void SetControlData (void);


  enum { IDD = IDD_EDITFLAGS_DLG };
  CListBox	m_FlagsList;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);

protected:

		/* Generated message map functions */
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  
  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of Class CSrEditFlagsDlg Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Show a model biped parts dialog */
  bool SrEditFlagsDlg (dword& Flags, const dword Mask);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrEditFlagsDlg.H
 *=========================================================================*/
