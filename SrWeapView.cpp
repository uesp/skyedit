/*===========================================================================
 *
 * File:		SrWeapView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	27 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srweapview.h"
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

  IMPLEMENT_DYNCREATE(CSrWeapView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrWeapView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrWeapView, CSrRecordDialog)
	//{{AFX_MSG_MAP(CSrWeapView)
	//}}AFX_MSG_MAP	
	ON_BN_CLICKED(IDC_EDIT_EQUIPSLOT, &CSrWeapView::OnBnClickedEditEquipslot)
	ON_BN_CLICKED(IDC_SELECTEQUIPSLOT_BUTTON, &CSrWeapView::OnBnClickedSelectequipslotButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_EQUIPSLOT, OnDropEquipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_EQUIPSLOT, OnDropEquipSlot)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrWeapView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrWeapView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_VALUE,			IDC_VALUE,			16,		IDS_TT_VALUE)
	ADD_SRRECUIFIELDS( SR_FIELD_WEIGHT,			IDC_WEIGHT,			16,		IDS_TT_WEIGHT)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTMENT,	IDC_ENCHANTMENT,	128,	IDS_TT_ENCHANTMENT)
	ADD_SRRECUIFIELDS( SR_FIELD_ENCHANTPOINTS,	IDC_ENCHANTCHARGE,	8,		IDS_TT_ENCHANTPOINTS)
	ADD_SRRECUIFIELDS( SR_FIELD_DAMAGE,			IDC_DAMAGE,	        8,		IDS_TT_DAMAGE)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,	        256,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
	ADD_SRRECUIFIELDS( SR_FIELD_EQUIPSLOT,		IDC_EQUIPSLOT,		128,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWeapView Constructor
 *
 *=========================================================================*/
CSrWeapView::CSrWeapView() : CSrRecordDialog(CSrWeapView::IDD) 
{
  //{{AFX_DATA_INIT(CSrWeapView)
  //}}AFX_DATA_INIT

  m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrWeapView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWeapView Destructor
 *
 *=========================================================================*/
CSrWeapView::~CSrWeapView() 
{
}
/*===========================================================================
 *		End of Class CSrWeapView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWeapView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrWeapView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_DAMAGE, m_Damage);
	DDX_Control(pDX, IDC_ENCHANTCHARGE, m_EnchantPoints);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_QUESTITEM, m_QuestItem);
	DDX_Control(pDX, IDC_ENCHANTMENT, m_Enchantment);
	DDX_Control(pDX, IDC_NAME, m_Name);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_EQUIPSLOT, m_EquipSlot);
 }
/*===========================================================================
 *		End of Class Method CSrWeapView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrWeapView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrWeapView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrWeapView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrWeapView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrWeapView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrWeapView::OnInitialUpdate (void) 
{
  CSrRecordDialog::OnInitialUpdate();

  SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrWeapView::OnInitialUpdate()
 *=========================================================================*/


 void CSrWeapView::OnBnClickedEditEquipslot()
 {
	 if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_EquipSlot, SR_NAME_EQUP);
 }


 void CSrWeapView::OnBnClickedSelectequipslotButton()
 {
	CString    Buffer;

	if (m_pDlgHandler == NULL) return;
	m_EquipSlot.GetWindowText(Buffer);

	bool Result = m_pDlgHandler->SelectEquipSlot(Buffer);
	if (!Result) return;

	m_EquipSlot.SetWindowText(Buffer);
 }


 /*===========================================================================
 *
 * Class CSrWeapView Event - void OnDropEquipSlot (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrWeapView::OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult) {
  srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
  CSrRecord*	     pRecord;
  CSrEqupRecord*     pEquipSlot;

  *pResult = SRRL_DROPCHECK_ERROR;
  if (pDropItems->pRecords == NULL) return;
  if (pDropItems->pRecords->GetSize() != 1) return;

  pRecord = pDropItems->pRecords->GetAt(0);

  if (pRecord->GetRecordType() != SR_NAME_EQUP) return;
  pEquipSlot = SrCastClass(CSrEqupRecord, pRecord);
  if (pEquipSlot == NULL) return;

  if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
  {
    m_EquipSlot.SetWindowText(pEquipSlot->GetEditorID());
  }

  *pResult = SRRL_DROPCHECK_OK;
}
/*===========================================================================
 *		End of Class Event CSrWeapView::OnDropEquipSlot()
 *=========================================================================*/
