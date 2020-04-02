/*===========================================================================
 *
 * File:		SrScriptTextCtrl.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	29 January 2012
 *
 * Implements the CSrScriptTextCtrl class
 *
 *=========================================================================*/
#include "stdafx.h"
#include "SrScriptTextCtrl.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

	IMPLEMENT_DYNCREATE(CSrScriptTextCtrl, CRichEditCtrl);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrScriptTextCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrScriptTextCtrl, CRichEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrScriptTextCtrl Message Map
 *=========================================================================*/


void CSrScriptTextCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	if (nChar == '\t') 
	{
		ReplaceSel("\t", true);
	}
	else 
	{
		CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	}
	
}


UINT CSrScriptTextCtrl::OnGetDlgCode()
{
	return CRichEditCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}
