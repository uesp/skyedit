/*===========================================================================
 *
 * File:		SrScriptTextCtrl.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	29 January 2012
 *
 *=========================================================================*/
#ifndef __SRSCRIPTTEXTCTRL_H
#define __SRSCRIPTTEXTCTRL_H


class CSrScriptTextCtrl : public CRichEditCtrl
{
  DECLARE_DYNCREATE(CSrScriptTextCtrl);

public:
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP();

};

#endif
/*===========================================================================
 *		End of File SrScriptTextCtrl.H
 *=========================================================================*/
