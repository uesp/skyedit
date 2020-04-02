/*===========================================================================
 *
 * File:		Srimagectrl.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "Sredit.h"
#include "SrImageCtrl.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CSrImageCtrl, CWnd)
	//{{AFX_MSG_MAP(CSrImageCtrl)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Class CSrImageCtrl Constructor
 *
 *=========================================================================*/
CSrImageCtrl::CSrImageCtrl() {
  m_IsInitialized = false;
  m_ZoomToFit     = false;
  m_KeepAspect    = true;
  m_ZoomLarger    = false;
  m_ZoomSmaller   = true;

  m_ImageHeight   = 0;
  m_ImageWidth    = 0;
}
/*===========================================================================
 *		End of Class CSrImageCtrl Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Destructor
 *
 *=========================================================================*/
CSrImageCtrl::~CSrImageCtrl() {

	/* Destroy the frame's bitmap if required */
  if (m_IsInitialized) {
    m_Bitmap.DeleteObject();
    m_IsInitialized = false;
  }

}
/*===========================================================================
 *		End of Class CSrImageCtrl Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrImageCtrl::OnInitialUpdate (void) {
  CRect	ClientRect;
  CDC*  pDC;

  EnableScrollBarCtrl(SB_HORZ, TRUE);

	/* Get the output area */
  GetClientRect(&ClientRect);
  pDC = GetDC();

	/* Create the bitmap of the desired size that is compatible
	 * with the current output DC */
  //m_Bitmap.CreateCompatibleBitmap(pDC, MWESM_ICON_DEFAULTWIDTH, MWESM_ICON_DEFAULTHEIGHT);
  ReleaseDC(pDC);

  m_IsInitialized = true;
}
/*===========================================================================
 *		End of Class Event CSrImageCtrl::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Event - void OnPaint ();
 *
 *=========================================================================*/
void CSrImageCtrl::OnPaint() {
  CPaintDC DC(this);
  CRect    ClientRect;
  CDC	   BitmapDC;
  bool	   IsClientLarger = true;
  bool	   StretchOutput;
  int	   OffsetX = 0;
  int	   OffsetY = 0;

	/* Get the output area */
  GetClientRect(&ClientRect);

  if (m_Bitmap.m_hObject == NULL) return;

	/* Initialize the bitmap memory DC */
  BitmapDC.CreateCompatibleDC(&DC);
  BitmapDC.SelectObject(&m_Bitmap);

	/* Show/hide scrollbars */
  if (m_ImageWidth > ClientRect.Width()) {
    ShowScrollBar(SB_HORZ, TRUE);
    SetScrollRange(SB_HORZ, 0, m_ImageWidth - ClientRect.Width() + 1);
    OffsetX = GetScrollPos(SB_HORZ);
    IsClientLarger = false;
  }
  else {
    ShowScrollBar(SB_HORZ, FALSE);
    SetScrollPos(SB_HORZ, 0, FALSE);
  }

  if (m_ImageHeight > ClientRect.Height()) {
    ShowScrollBar(SB_VERT, TRUE);
    SetScrollRange(SB_VERT, 0, m_ImageHeight - ClientRect.Height() + 1);
    OffsetY = GetScrollPos(SB_VERT);
    IsClientLarger = false;
  }
  else {
    ShowScrollBar(SB_VERT, FALSE);
    SetScrollPos(SB_VERT, 0, FALSE);
  }

  StretchOutput = false;

  if (m_ZoomToFit) {
    if (!m_ZoomLarger && IsClientLarger) 
      StretchOutput = false;
    else
      StretchOutput = true;
  }

	/* Output the bitmap to the frame */
  if (StretchOutput) {
    /*DC.StretchBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &BitmapDC, 
			  0, 0, m_ImageWidth, m_ImageHeight, SRCCOPY); //*/
    DC.BitBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &BitmapDC,
			OffsetX, OffsetY, SRCCOPY);
  }
  else {
    DC.BitBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &BitmapDC, 
			OffsetX, OffsetY, SRCCOPY);
  }

}
/*===========================================================================
 *		End of Class Event CSrImageCtrl::OnPaint()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Method - bool Load (pFile, FileSize, Offset);
 *
 * TODO: Does not work?
 *
 *=========================================================================*/
bool CSrImageCtrl::Load (FILE* pFile, const long FileSize, const long Offset) {
  HBITMAP   hBMP = NULL;
  BITMAP    BmpInfo;
  CDC*      pDC;
  ILboolean Result;
  int	    iResult;

  if (pFile == NULL) return (false);

	/* Ensure things are initialized */
  if (!m_IsInitialized) OnInitialUpdate();
  SetScrollPos(SB_HORZ, 0, FALSE);
  SetScrollPos(SB_VERT, 0, FALSE);

  m_Bitmap.DeleteObject();
  m_ImageHeight = 0;
  m_ImageWidth  = 0;

  iResult = fseek(pFile, Offset, SEEK_SET);
  if (iResult != 0) return (false);

	/* Attempt to load the given image into a bitmap handle that is
	 * compatible with the current display */
  pDC = GetDC();

  ilBindImage(0);
  Result = ilLoadF(IL_TYPE_UNKNOWN, pFile);
  if (Result) hBMP = ilutConvertToHBitmap(pDC->GetSafeHdc());

  	/* Copy the bitmap to the local bitmap object */
  if (hBMP != NULL) {;
    m_Bitmap.Attach(hBMP);

    Result = ilActiveMipmap(0);
    Result = ilActiveMipmap(1);
    Result = ilActiveMipmap(2);
  }
 
  ReleaseDC(pDC);
  
	/* Update the bitmap size */  
  iResult = m_Bitmap.GetBitmap(&BmpInfo);

  if (iResult) {
    m_ImageHeight = BmpInfo.bmHeight;
    m_ImageWidth  = BmpInfo.bmWidth;
  }

  RedrawWindow();
  return (hBMP != NULL);
}
/*===========================================================================
 *		End of Class Method CSrImageCtrl::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Method - void Load (pFilename);
 *
 *=========================================================================*/
bool CSrImageCtrl::Load (const TCHAR* pFilename) {
  HBITMAP   hBMP;
  BITMAP    BmpInfo;
  CBitmap   TempBitmap;
  CDC*      pDC;
  ILboolean Result;
  BOOL      iResult;

  if (pFilename == NULL) return (false);

	/* Ensure things are initialized */
  if (!m_IsInitialized) OnInitialUpdate();
  SetScrollPos(SB_HORZ, 0, FALSE);
  SetScrollPos(SB_VERT, 0, FALSE);

  m_Bitmap.DeleteObject();
  m_ImageHeight = 0;
  m_ImageWidth  = 0;

	/* Attempt to load the given image into a bitmap handle that is
	 * compatible with the current display */
  pDC = GetDC();

  ilBindImage(0);
  Result = ilLoad(IL_TYPE_UNKNOWN, pFilename);
  if (Result) hBMP = ilutConvertToHBitmap(pDC->GetSafeHdc());

  	/* Copy the bitmap to the local bitmap object */
  if (hBMP != NULL) {;
    m_Bitmap.Attach(hBMP);

    //Result = ilActiveMipmap(0);
    //Result = ilActiveMipmap(1);
    //Result = ilActiveMipmap(2);
  }
 
  ReleaseDC(pDC);

  	/* Update the bitmap size */  
  iResult = m_Bitmap.GetBitmap(&BmpInfo);

  if (iResult) {
    m_ImageHeight = BmpInfo.bmHeight;
    m_ImageWidth  = BmpInfo.bmWidth;
  }

  RedrawWindow();
  return (hBMP != NULL);
 }
/*===========================================================================
 *		End of Class Method CSrImageCtrl::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Event - void OnHScroll (SBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CSrImageCtrl::OnHScroll (UINT SBCode, UINT nPos, CScrollBar* pScrollBar) {
  int Pos   = GetScrollPos(SB_HORZ);
  int Limit = GetScrollLimit(SB_HORZ);

  switch (SBCode) {
    case SB_BOTTOM:
	SetScrollPos(SB_HORZ, Limit, TRUE);
	break;
    case SB_TOP:
        SetScrollPos(SB_HORZ, 0, TRUE);
	break;
    case SB_ENDSCROLL:
	RedrawWindow();
	break;
    case SB_LINEDOWN:
	SetScrollPos(SB_HORZ, Pos + 1, TRUE);
	break;
    case SB_LINEUP:
	SetScrollPos(SB_HORZ, Pos - 1, TRUE);
	break;
    case SB_PAGEDOWN:
	SetScrollPos(SB_HORZ, Pos + Limit/5 + 1, TRUE);
	break;
    case SB_PAGEUP:
        SetScrollPos(SB_HORZ, Pos - Limit/5 - 1, TRUE);
	break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        SetScrollPos(SB_HORZ, nPos, TRUE);
	break;
  }

}
/*===========================================================================
 *		End of Class Event CSrImageCtrl::OnHScroll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrImageCtrl Event - void OnVScroll (SBCode, nPos, pScrollBar);
 *
 *=========================================================================*/
void CSrImageCtrl::OnVScroll (UINT SBCode, UINT nPos, CScrollBar* pScrollBar) {
  int Pos   = GetScrollPos(SB_VERT);
  int Limit = GetScrollLimit(SB_VERT);

  switch (SBCode) {
    case SB_BOTTOM:
	SetScrollPos(SB_VERT, Limit, TRUE);
	break;
    case SB_TOP:
        SetScrollPos(SB_VERT, 0, TRUE);
	break;
    case SB_ENDSCROLL:
	RedrawWindow();
	break;
    case SB_LINEDOWN:
	SetScrollPos(SB_VERT, Pos + 1, TRUE);
	break;
    case SB_LINEUP:
	SetScrollPos(SB_VERT, Pos - 1, TRUE);
	break;
    case SB_PAGEDOWN:
	SetScrollPos(SB_VERT, Pos + Limit/5 + 1, TRUE);
	break;
    case SB_PAGEUP:
        SetScrollPos(SB_VERT, Pos - Limit/5 - 1, TRUE);
	break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        SetScrollPos(SB_VERT, nPos, TRUE);
	break;
  }


}
/*===========================================================================
 *		End of Class Event CSrImageCtrl::OnVScroll()
 *=========================================================================*/
