/*===========================================================================
 *
 * File:		SrLighview.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	18 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srlighview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
//#ifdef _DEBUG
//  #define new DEBUG_NEW
//  #undef THIS_FILE
//  static char THIS_FILE[] = __FILE__;
//#endif

  IMPLEMENT_DYNCREATE(CSrLighView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrLighView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrLighView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_EN_CHANGE(IDC_RED, OnChangeColor)
	ON_EN_CHANGE(IDC_GREEN, OnChangeColor)
	ON_EN_CHANGE(IDC_BLUE, OnChangeColor)
	ON_BN_CLICKED(IDC_EDIT_SOUND, &CSrLighView::OnBnClickedEditSound)
	ON_BN_CLICKED(IDC_SELECTSOUND_BUTTON, &CSrLighView::OnBnClickedSelectsoundButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SOUND, OnDropSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SOUND, OnDropSound)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrLighView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrLighView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,			IDC_WEIGHT,			16,		IDS_TT_WEIGHT)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,			256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_HOLDSOUND,		IDC_SOUND,	        200,	IDS_TT_SOUND)
	ADD_SRRECUIFIELDS( SR_FIELD_TIME,			IDC_TIME,	        8,		IDS_TT_TIME)
	ADD_SRRECUIFIELDS( SR_FIELD_FADE,			IDC_FADE,	        8,		IDS_TT_FADE)
	ADD_SRRECUIFIELDS( SR_FIELD_FOV,			IDC_FOV,	        8,		IDS_TT_FOV)
	ADD_SRRECUIFIELDS( SR_FIELD_FALLOFF,		IDC_FALLOFF,	    8,		IDS_TT_FALLOFF)
	ADD_SRRECUIFIELDS( SR_FIELD_RADIUS,			IDC_RADIUS,	        8,		IDS_TT_RADIUS)
	ADD_SRRECUIFIELDS( SR_FIELD_REDCOLOR,		IDC_RED,	        4,		IDS_TT_REDCOLOR)
	ADD_SRRECUIFIELDS( SR_FIELD_GREENCOLOR,		IDC_GREEN,	        4,		IDS_TT_GREENCOLOR)
	ADD_SRRECUIFIELDS( SR_FIELD_BLUECOLOR,		IDC_BLUE,	        4,		IDS_TT_BLUECOLOR)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPE,			IDC_FLICKERTYPE,	0,		IDS_TT_TYPE)
	ADD_SRRECUIFIELDS( SR_FIELD_DYNAMIC,		IDC_DYNAMIC,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_CARRIED,		IDC_CARRIED,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_SPOTSHADOW,		IDC_SPOTSHADOW,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG1,	IDC_UNKNOWNFLAG1,	0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG2,	IDC_UNKNOWNFLAG2,	0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG3,	IDC_UNKNOWNFLAG3,	0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2a,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,		0,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,		IDC_UNKNOWN4,		0,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Constructor
 *
 *=========================================================================*/
CSrLighView::CSrLighView() : CSrRecordDialog(CSrLighView::IDD) 
{
  m_EnchantType = 0;
  m_InitialSetData = false;
  m_Initialized    = false;
}
/*===========================================================================
 *		End of Class CSrLighView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Destructor
 *
 *=========================================================================*/
CSrLighView::~CSrLighView() 
{
}
/*===========================================================================
 *		End of Class CSrLighView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrLighView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FALLOFF, m_Falloff);
	DDX_Control(pDX, IDC_RADIUS, m_Radius);
	DDX_Control(pDX, IDC_FOV, m_FOV);
	DDX_Control(pDX, IDC_BLUESPIN, m_BlueSpin);
	DDX_Control(pDX, IDC_GREENSPIN, m_GreenSpin);
	DDX_Control(pDX, IDC_REDSPIN, m_RedSpin);
	DDX_Control(pDX, IDC_FLICKERTYPE, m_FlickerType);
	DDX_Control(pDX, IDC_COLOR, m_ColorBox);
	DDX_Control(pDX, IDC_FADE, m_Fade);
	DDX_Control(pDX, IDC_BLUE, m_BlueColor);
	DDX_Control(pDX, IDC_GREEN, m_GreenColor);
	DDX_Control(pDX, IDC_RED, m_RedColor);
	DDX_Control(pDX, IDC_SOUND, m_Sound);
	DDX_Control(pDX, IDC_TIME, m_Time);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_DYNAMIC, m_Dynamic);
	DDX_Control(pDX, IDC_CARRIED, m_Carried);
	DDX_Control(pDX, IDC_SPOTSHADOW, m_SpotShadow);
	DDX_Control(pDX, IDC_UNKNOWNFLAG1, m_UnknownFlag1);
	DDX_Control(pDX, IDC_UNKNOWNFLAG2, m_UnknownFlag2);
	DDX_Control(pDX, IDC_UNKNOWNFLAG3, m_UnknownFlag3);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2a, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Unknown4);
}
/*===========================================================================
 *		End of Class Method CSrLighView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Method - void EnableCarried (Enable);
 *
 *=========================================================================*/
void CSrLighView::EnableCarried (const bool Enable) 
{
	m_Name.EnableWindow(Enable);
	m_Icon.EnableWindow(Enable);
	//m_OffByDefault.EnableWindow(Enable);
	m_Weight.EnableWindow(Enable);
	m_Value.EnableWindow(Enable);
	m_Time.EnableWindow(Enable);
}
/*===========================================================================
 *		End of Class Method CSrLighView::EnableCarried()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrLighView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrLighView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrLighView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrLighView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrLighView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	SrFillComboList(m_FlickerType, s_SrLightTypes, SRE_FILLCOMBO_NODUPLICATES);

	m_RedSpin.SetRange(0, 255);
	m_GreenSpin.SetRange(0, 255);
	m_BlueSpin.SetRange(0, 255);

	SetControlData();

	m_ColorBox.SetColor(RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos()));
	m_ColorBox.RedrawWindow();

	OnCarried();

	m_Initialized = true;
}
/*===========================================================================
 *		End of Class Event CSrLighView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Event - void OnCarried ();
 *
 *=========================================================================*/
void CSrLighView::OnCarried() 
{
  //bool Carried = m_CanCarry.GetCheck() != 0;
  //EnableCarried(Carried);
}
/*===========================================================================
 *		End of Class Event CSrLighView::OnCarried()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Event - void OnColor ();
 *
 *=========================================================================*/
void CSrLighView::OnColor() 
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
 *		End of Class Event CSrLighView::OnColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrLighView Event - void OnChangeColor ();
 *
 *=========================================================================*/
void CSrLighView::OnChangeColor() 
{
	if (!m_Initialized) return;

	COLORREF Color = RGB(m_RedSpin.GetPos(), m_GreenSpin.GetPos(), m_BlueSpin.GetPos());

	m_ColorBox.SetColor(Color);
	m_ColorBox.RedrawWindow();
}
/*===========================================================================
 *		End of Class Event CSrLighView::OnChangeColor()
 *=========================================================================*/


void CSrLighView::OnBnClickedEditSound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Sound, SR_NAME_SNDR);
}


void CSrLighView::OnBnClickedSelectsoundButton()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Sound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrLighView::OnDropSound (NMHDR* pNotifyStruct, LRESULT* pResult)
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Sound, SR_NAME_SNDR, 1);
}

