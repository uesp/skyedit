/*===========================================================================
 *
 * File:		SrClfmView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	8 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srclfmview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrClfmView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrClfmView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrClfmView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_EN_CHANGE(IDC_RED, OnChangeColor)
	ON_EN_CHANGE(IDC_GREEN, OnChangeColor)
	ON_EN_CHANGE(IDC_BLUE, OnChangeColor)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrClfmView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrClfmView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_REDCOLOR,		IDC_RED,	        4,		IDS_TT_REDCOLOR)
	ADD_SRRECUIFIELDS( SR_FIELD_GREENCOLOR,		IDC_GREEN,	        4,		IDS_TT_GREENCOLOR)
	ADD_SRRECUIFIELDS( SR_FIELD_BLUECOLOR,		IDC_BLUE,	        4,		IDS_TT_BLUECOLOR)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		0,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClfmView Constructor
 *
 *=========================================================================*/
CSrClfmView::CSrClfmView() : CSrRecordDialog(CSrClfmView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrClfmView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClfmView Destructor
 *
 *=========================================================================*/
CSrClfmView::~CSrClfmView() 
{
}
/*===========================================================================
 *		End of Class CSrClfmView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClfmView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrClfmView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BLUESPIN, m_BlueSpin);
	DDX_Control(pDX, IDC_GREENSPIN, m_GreenSpin);
	DDX_Control(pDX, IDC_REDSPIN, m_RedSpin);
	DDX_Control(pDX, IDC_COLOR, m_ColorBox);
	DDX_Control(pDX, IDC_BLUE, m_BlueColor);
	DDX_Control(pDX, IDC_GREEN, m_GreenColor);
	DDX_Control(pDX, IDC_RED, m_RedColor);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
}
/*===========================================================================
 *		End of Class Method CSrClfmView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrClfmView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrClfmView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrClfmView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrClfmView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClfmView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrClfmView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	m_RedSpin.SetRange(0, 255);
	m_GreenSpin.SetRange(0, 255);
	m_BlueSpin.SetRange(0, 255);

	m_InitialSetData = true;

	SetControlData();

	m_ColorBox.SetColor(RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos()));
	m_ColorBox.RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CSrClfmView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClfmView Event - void OnColor ();
 *
 *=========================================================================*/
void CSrClfmView::OnColor() 
{
	COLORREF     Color = RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos());
	CColorDialog Dlg(Color, CC_RGBINIT | CC_FULLOPEN, this);
	int          Result;

	Result = Dlg.DoModal();
	if (Result != IDOK) return;

	Color = Dlg.GetColor();

	m_RedSpin.SetPos(GetRValue(Color));
	m_GreenSpin.SetPos(GetGValue(Color));
	m_BlueSpin.SetPos(GetBValue(Color));

	m_ColorBox.SetColor(Color);
	m_ColorBox.RedrawWindow();	
}
/*===========================================================================
 *		End of Class Event CSrClfmView::OnColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrClfmView Event - void OnChangeColor ();
 *
 *=========================================================================*/
void CSrClfmView::OnChangeColor() 
{
	if (!m_InitialSetData) return;

	COLORREF Color = RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos());

	m_ColorBox.SetColor(Color);
	m_ColorBox.RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CSrClfmView::OnChangeColor()
 *=========================================================================*/
