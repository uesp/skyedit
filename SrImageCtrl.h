/*===========================================================================
 *
 * File:	Obimagectrl.H
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	October 5, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBIMAGECTRL_H
#define __OBIMAGECTRL_H



class CSrImageCtrl : public CWnd {

  /*---------- Begin Protected Class Members ---------------------*/
protected:
  CBitmap	m_Bitmap;		/* The bitmap image to draw */
  bool		m_IsInitialized;

  bool		m_ZoomToFit;
  bool		m_KeepAspect;
  bool		m_ZoomLarger;
  bool		m_ZoomSmaller;

  int		m_ImageWidth;
  int		m_ImageHeight;


  /*---------- Begin Protected Class Methods ---------------------*/
protected:



  /*---------- Begin Public Class Methods ------------------------*/
public:

  CSrImageCtrl();
  virtual ~CSrImageCtrl();

  	/* Called after the frame window is created */
  void OnInitialUpdate (void);

  bool Load (const TCHAR* pFilename);
  bool Load (FILE* pFile, const long FileSize, const long Offset);

	// ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSrImageCtrl)
  //}}AFX_VIRTUAL

	// Generated message map functions
protected:
  //{{AFX_MSG(CSrImageCtrl)
  afx_msg void OnPaint();
  afx_msg void OnHScroll (UINT SBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnVScroll (UINT SBCode, UINT nPos, CScrollBar* pScrollBar);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obimagectrl.H
 *=========================================================================*/
