/*===========================================================================
 *
 * File:		SrAmmoView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srammoview.h"
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

  IMPLEMENT_DYNCREATE(CSrAmmoView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrAmmoView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrAmmoView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_EDIT_PROJECTILE, &CSrAmmoView::OnBnClickedEditProjectile)
	ON_BN_CLICKED(IDC_SELECTPROJECTILE_BUTTON, &CSrAmmoView::OnBnClickedSelectprojectileButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_PROJECTILE, OnDropProjectile)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_PROJECTILE, OnDropProjectile)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrAmmoView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrAmmoView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_DAMAGE,			IDC_DAMAGE,	        8,		IDS_TT_DAMAGE)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
	ADD_SRRECUIFIELDS( SR_FIELD_PROJECTILE,		IDC_PROJECTILE,	    128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DROPSOUND,		IDC_DROPSOUND,      128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_PICKUPSOUND,	IDC_PICKUPSOUND,    128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IGNORERESIST,	IDC_IGNORERESIST,   8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_VANISH,			IDC_VANISH,	        8,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAmmoView Constructor
 *
 *=========================================================================*/
CSrAmmoView::CSrAmmoView() : CSrRecordDialog(CSrAmmoView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrAmmoView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAmmoView Destructor
 *
 *=========================================================================*/
CSrAmmoView::~CSrAmmoView() 
{
}
/*===========================================================================
 *		End of Class CSrAmmoView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAmmoView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrAmmoView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_DAMAGE, m_Damage);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_IGNORERESIST, m_IgnoreResist);
	DDX_Control(pDX, IDC_VANISH, m_Vanish);
	DDX_Control(pDX, IDC_DROPSOUND, m_DropSound);
	DDX_Control(pDX, IDC_PICKUPSOUND, m_PickupSound);
	DDX_Control(pDX, IDC_PROJECTILE, m_Projectile);
}
/*===========================================================================
 *		End of Class Method CSrAmmoView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrAmmoView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrAmmoView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrAmmoView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrAmmoView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrAmmoView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrAmmoView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrAmmoView::OnInitialUpdate()
 *=========================================================================*/


void CSrAmmoView::OnBnClickedEditProjectile()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Projectile, SR_NAME_PROJ);
}


void CSrAmmoView::OnBnClickedSelectprojectileButton()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Projectile, SR_NAME_PROJ, &CSrProjRecord::s_FieldMap);
}


/*===========================================================================
 *
 * Class CSrAmmoView Event - void OnDropProjectile (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrAmmoView::OnDropProjectile (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrIdRecord*       pProjectile;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

	/* Ignore any invalid record types */
  if (pRecord->GetRecordType() != SR_NAME_PROJ) return;
  pProjectile = SrCastClass(CSrIdRecord, pRecord);
  if (pProjectile == NULL) return;

	/* If we're just checking or not */
  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_Projectile.SetWindowText(pProjectile->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrAmmoView::OnDropProjectile()
 *=========================================================================*/


