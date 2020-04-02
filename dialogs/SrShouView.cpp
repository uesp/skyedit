/*===========================================================================
 *
 * File:		SrShouView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	2 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srshouview.h"
#include "dialogs/sreditdlghandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrShouView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrShouView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrShouView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_STATICMODEL, &CSrShouView::OnBnClickedEditStaticmodel)
	ON_BN_CLICKED(IDC_SELECT_STATICMODEL, &CSrShouView::OnBnClickedSelectStaticmodel)
	ON_BN_CLICKED(IDC_EDIT_POWERWORD1, &CSrShouView::OnBnClickedEditPowerword1)
	ON_BN_CLICKED(IDC_SELECT_POWERWORD1, &CSrShouView::OnBnClickedSelectPowerword1)
	ON_BN_CLICKED(IDC_EDIT_SPELL1, &CSrShouView::OnBnClickedEditSpell1)
	ON_BN_CLICKED(IDC_SELECT_SPELL1, &CSrShouView::OnBnClickedSelectSpell1)
	ON_BN_CLICKED(IDC_EDIT_POWERWORD2, &CSrShouView::OnBnClickedEditPowerword2)
	ON_BN_CLICKED(IDC_SELECT_POWERWORD2, &CSrShouView::OnBnClickedSelectPowerword2)
	ON_BN_CLICKED(IDC_EDIT_SPELL2, &CSrShouView::OnBnClickedEditSpell2)
	ON_BN_CLICKED(IDC_SELECT_SPELL2, &CSrShouView::OnBnClickedSelectSpell2)
	ON_BN_CLICKED(IDC_EDIT_POWERWORD3, &CSrShouView::OnBnClickedEditPowerword3)
	ON_BN_CLICKED(IDC_SELECT_POWERWORD3, &CSrShouView::OnBnClickedSelectPowerword3)
	ON_BN_CLICKED(IDC_EDIT_SPELL3, &CSrShouView::OnBnClickedEditSpell3)
	ON_BN_CLICKED(IDC_SELECT_SPELL3, &CSrShouView::OnBnClickedSelectSpell3)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_STATICMODEL, OnDropStaticModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_STATICMODEL, OnDropStaticModel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SPELL1, OnDropSpell1)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SPELL1, OnDropSpell1)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SPELL2, OnDropSpell2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SPELL2, OnDropSpell2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SPELL3, OnDropSpell3)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SPELL3, OnDropSpell3)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_POWERWORD1, OnDropPowerWord1)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_POWERWORD1, OnDropPowerWord1)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_POWERWORD2, OnDropPowerWord2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_POWERWORD2, OnDropPowerWord2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_POWERWORD3, OnDropPowerWord3)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_POWERWORD3, OnDropPowerWord3)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrShouView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrShouView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,	IDC_DESCRIPTION,	256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_STATIC,			IDC_STATICMODEL,	200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SPELL1,			IDC_SPELL1,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SPELL2,			IDC_SPELL2,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SPELL3,			IDC_SPELL3,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_POWERWORD1,		IDC_POWERWORD1,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_POWERWORD2,		IDC_POWERWORD2,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_POWERWORD3,		IDC_POWERWORD3,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_RECHARGE1,		IDC_RECHARGE1,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_RECHARGE2,		IDC_RECHARGE2,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_RECHARGE3,		IDC_RECHARGE3,		16,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrShouView Constructor
 *
 *=========================================================================*/
CSrShouView::CSrShouView() : CSrRecordDialog(CSrShouView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrShouView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrShouView Destructor
 *
 *=========================================================================*/
CSrShouView::~CSrShouView() 
{
}
/*===========================================================================
 *		End of Class CSrShouView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrShouView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrShouView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_STATICMODEL, m_StaticModel);
	DDX_Control(pDX, IDC_POWERWORD1, m_PowerWord1);
	DDX_Control(pDX, IDC_SPELL1, m_Spell1);
	DDX_Control(pDX, IDC_RECHARGE1, m_Recharge1);
	DDX_Control(pDX, IDC_POWERWORD2, m_PowerWord2);
	DDX_Control(pDX, IDC_SPELL2, m_Spell2);
	DDX_Control(pDX, IDC_RECHARGE2, m_Recharge2);
	DDX_Control(pDX, IDC_POWERWORD3, m_PowerWord3);
	DDX_Control(pDX, IDC_SPELL3, m_Spell3);
	DDX_Control(pDX, IDC_RECHARGE3, m_Recharge3);
}
/*===========================================================================
 *		End of Class Method CSrShouView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrShouView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrShouView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrShouView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrShouView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrShouView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrShouView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();
	
	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrShouView::OnInitialUpdate()
 *=========================================================================*/


void CSrShouView::GetControlData (void)
{
	CSrShouRecord* pShout = SrCastClassNull(CSrShouRecord, GetOutputRecord());

	if (pShout != NULL)
	{
		pShout->ForceValidSnamCount();
	}

	CSrRecordDialog::GetControlData();
}


void CSrShouView::OnBnClickedEditStaticmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_StaticModel, SR_NAME_STAT);
}


void CSrShouView::OnBnClickedSelectStaticmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_StaticModel, SR_NAME_STAT, &CSrStatRecord::s_FieldMap);
}


void CSrShouView::OnBnClickedEditPowerword1()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_PowerWord1, SR_NAME_WOOP);
}


void CSrShouView::OnBnClickedEditPowerword2()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_PowerWord2, SR_NAME_WOOP);
}


void CSrShouView::OnBnClickedEditPowerword3()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_PowerWord3, SR_NAME_WOOP);
}


void CSrShouView::OnBnClickedSelectPowerword1()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_PowerWord1, SR_NAME_WOOP, &CSrWoopRecord::s_FieldMap);
}


void CSrShouView::OnBnClickedSelectPowerword2()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_PowerWord2, SR_NAME_WOOP, &CSrWoopRecord::s_FieldMap);
}


void CSrShouView::OnBnClickedSelectPowerword3()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_PowerWord3, SR_NAME_WOOP, &CSrWoopRecord::s_FieldMap);
}


void CSrShouView::OnBnClickedEditSpell1()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Spell1, SR_NAME_SPEL);
}


void CSrShouView::OnBnClickedEditSpell2()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Spell2, SR_NAME_SPEL);
}


void CSrShouView::OnBnClickedEditSpell3()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Spell3, SR_NAME_SPEL);
}


void CSrShouView::OnBnClickedSelectSpell1()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Spell1, SR_NAME_SPEL, &CSrSpelRecord::s_FieldMap);
}


void CSrShouView::OnBnClickedSelectSpell2()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Spell2, SR_NAME_SPEL, &CSrSpelRecord::s_FieldMap);
}


void CSrShouView::OnBnClickedSelectSpell3()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Spell3, SR_NAME_SPEL, &CSrSpelRecord::s_FieldMap);
}


void CSrShouView::OnDropStaticModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_StaticModel, SR_NAME_STAT, 1);
}


void CSrShouView::OnDropSpell1 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Spell1, SR_NAME_SPEL, 1);
}


void CSrShouView::OnDropSpell2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Spell2, SR_NAME_SPEL, 1);
}


void CSrShouView::OnDropSpell3 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Spell3, SR_NAME_SPEL, 1);
}


void CSrShouView::OnDropPowerWord1 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_PowerWord1, SR_NAME_WOOP, 1);
}


void CSrShouView::OnDropPowerWord2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_PowerWord3, SR_NAME_WOOP, 1);
}


void CSrShouView::OnDropPowerWord3 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_PowerWord3, SR_NAME_WOOP, 1);
}
