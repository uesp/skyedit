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
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMPACTSET, OnDropImpactSet)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMPACTSET, OnDropImpactSet)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_STATICMODEL, OnDropStaticModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_STATICMODEL, OnDropStaticModel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DRAWSOUND, OnDropDrawSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DRAWSOUND, OnDropDrawSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SHEATHSOUND, OnDropSheathSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SHEATHSOUND, OnDropSheathSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SWINGSOUND, OnDropSwingSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SWINGSOUND, OnDropSwingSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_BOUNDSOUND, OnDropBoundSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_BOUNDSOUND, OnDropBoundSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_TRAPSOUND, OnDropTrapSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_TRAPSOUND, OnDropTrapSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_BASEWEAPON, OnDropBaseWeapon)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_BASEWEAPON, OnDropBaseWeapon)
	ON_BN_CLICKED(IDC_EDIT_IMPACTSET, &CSrWeapView::OnBnClickedEditImpactset)
	ON_BN_CLICKED(IDC_SELECT_IMPACTSET, &CSrWeapView::OnBnClickedSelectImpactset)
	ON_BN_CLICKED(IDC_EDIT_STATICMODEL, &CSrWeapView::OnBnClickedEditStaticmodel)
	ON_BN_CLICKED(IDC_SELECT_STATICMODEL, &CSrWeapView::OnBnClickedSelectStaticmodel)
	ON_BN_CLICKED(IDC_EDIT_DRAWSOUND, &CSrWeapView::OnBnClickedEditDrawsound)
	ON_BN_CLICKED(IDC_SELECT_DRAWSOUND, &CSrWeapView::OnBnClickedSelectDrawsound)
	ON_BN_CLICKED(IDC_EDIT_SHEATHSOUND, &CSrWeapView::OnBnClickedEditSheathsound)
	ON_BN_CLICKED(IDC_SELECT_SHEATHSOUND, &CSrWeapView::OnBnClickedSelectSheathsound)
	ON_BN_CLICKED(IDC_EDIT_SWINGSOUND, &CSrWeapView::OnBnClickedEditSwingsound)
	ON_BN_CLICKED(IDC_SELECT_SWINGSOUND, &CSrWeapView::OnBnClickedSelectSwingsound)
	ON_BN_CLICKED(IDC_EDIT_BOUNDSOUND, &CSrWeapView::OnBnClickedEditBoundsound)
	ON_BN_CLICKED(IDC_SELECT_BOUNDSOUND, &CSrWeapView::OnBnClickedSelectBoundsound)
	ON_BN_CLICKED(IDC_EDIT_TRAPSOUND, &CSrWeapView::OnBnClickedEditTrapsound)
	ON_BN_CLICKED(IDC_SELECT_TRAPSOUND, &CSrWeapView::OnBnClickedSelectTrapsound)
	ON_BN_CLICKED(IDC_EDIT_BASEWEAPON, &CSrWeapView::OnBnClickedEditBaseweapon)
	ON_BN_CLICKED(IDC_SELECT_BASEWEAPON, &CSrWeapView::OnBnClickedSelectBaseweapon)
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
	ADD_SRRECUIFIELDS( SR_FIELD_DESCRIPTION,	IDC_DESCRIPTION,	256,	IDS_TT_DESCRIPTION)
	ADD_SRRECUIFIELDS( SR_FIELD_QUESTITEM,		IDC_QUESTITEM,		0,		IDS_TT_QUESTITEM)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORDS,		IDC_KEYWORDS,		0,		IDS_TT_KEYWORDS)
	ADD_SRRECUIFIELDS( SR_FIELD_EQUIPSLOT,		IDC_EQUIPSLOT,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_BASEWEAPON,		IDC_BASEWEAPON,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_IMPACTSET,		IDC_IMPACTSET,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_STATIC,			IDC_STATICMODEL,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DRAWSOUND,		IDC_DRAWSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SHEATHSOUND,	IDC_SHEATHSOUND,	128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_SWINGSOUND,		IDC_SWINGSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_BOUNDSOUND,		IDC_BOUNDSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_FIRESOUND,		IDC_TRAPSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,		IDC_UNKNOWN1,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,		IDC_UNKNOWN2a,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,		IDC_UNKNOWN3,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPE,			IDC_TYPE_LIST,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN5,		IDC_UNKNOWN5,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN6,		IDC_UNKNOWN6,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN7,		IDC_UNKNOWN7,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN8,		IDC_UNKNOWN8,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN9,		IDC_UNKNOWN9,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN10,		IDC_UNKNOWN10a,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN11,		IDC_UNKNOWN11,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN12,		IDC_UNKNOWN12,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN13,		IDC_UNKNOWN13,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN14,		IDC_UNKNOWN14,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN15,		IDC_UNKNOWN15,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN16,		IDC_UNKNOWN16,		16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWNFLAG1,	IDC_UNKNOWNFLAGS1,	16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_NNAM,			IDC_NNAME,			128,	0)
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
	DDX_Control(pDX, IDC_IMPACTSET, m_ImpactSet);
	DDX_Control(pDX, IDC_STATICMODEL, m_StaticModel);
	DDX_Control(pDX, IDC_DRAWSOUND, m_DrawSound);
	DDX_Control(pDX, IDC_SHEATHSOUND, m_SheathSound);
	DDX_Control(pDX, IDC_SWINGSOUND, m_SwingSound);
	DDX_Control(pDX, IDC_BOUNDSOUND, m_BoundSound);
	DDX_Control(pDX, IDC_TRAPSOUND, m_TrapSound);
	DDX_Control(pDX, IDC_BASEWEAPON, m_BaseWeapon);
	DDX_Control(pDX, IDC_NNAME, m_NName);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2a, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN5, m_Unknown5);
	DDX_Control(pDX, IDC_UNKNOWN6, m_Unknown6);
	DDX_Control(pDX, IDC_UNKNOWN7, m_Unknown7);
	DDX_Control(pDX, IDC_UNKNOWN8, m_Unknown8);
	DDX_Control(pDX, IDC_UNKNOWN9, m_Unknown9);
	DDX_Control(pDX, IDC_UNKNOWN10a, m_Unknown10);
	DDX_Control(pDX, IDC_UNKNOWN11, m_Unknown11);
	DDX_Control(pDX, IDC_UNKNOWN12, m_Unknown12);
	DDX_Control(pDX, IDC_UNKNOWN13, m_Unknown13);
	DDX_Control(pDX, IDC_UNKNOWN14, m_Unknown14);
	DDX_Control(pDX, IDC_UNKNOWN15, m_Unknown15);
	DDX_Control(pDX, IDC_UNKNOWN16, m_Unknown16);
	DDX_Control(pDX, IDC_UNKNOWNFLAGS1, m_UnknownFlags1);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_TYPE_LIST, m_Type);
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

  SrFillComboList(m_Type, s_SrWeaponTypes, 0);

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


void CSrWeapView::OnBnClickedEditImpactset()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_ImpactSet, SR_NAME_IPDS);
}


void CSrWeapView::OnBnClickedSelectImpactset()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_ImpactSet, SR_NAME_IPDS, &CSrIpdsRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditStaticmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_StaticModel, SR_NAME_STAT);
}


void CSrWeapView::OnBnClickedSelectStaticmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_StaticModel, SR_NAME_STAT, &CSrStatRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditDrawsound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_DrawSound, SR_NAME_SNDR);
}


void CSrWeapView::OnBnClickedSelectDrawsound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_DrawSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditSheathsound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_SheathSound, SR_NAME_SNDR);
}


void CSrWeapView::OnBnClickedSelectSheathsound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_SheathSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditSwingsound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_SwingSound, SR_NAME_SNDR);
}


void CSrWeapView::OnBnClickedSelectSwingsound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_SwingSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditBoundsound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_BoundSound, SR_NAME_SNDR);
}


void CSrWeapView::OnBnClickedSelectBoundsound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_BoundSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditTrapsound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_TrapSound, SR_NAME_SNDR);
}


void CSrWeapView::OnBnClickedSelectTrapsound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_TrapSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrWeapView::OnBnClickedEditBaseweapon()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_BaseWeapon, SR_NAME_WEAP);
}


void CSrWeapView::OnBnClickedSelectBaseweapon()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_BaseWeapon, SR_NAME_WEAP, &CSrWeapRecord::s_FieldMap);
}


void CSrWeapView::OnDropImpactSet (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_ImpactSet, SR_NAME_IPDS, 1);
}


void CSrWeapView::OnDropStaticModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_StaticModel, SR_NAME_STAT, 1);
}


void CSrWeapView::OnDropDrawSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_DrawSound, SR_NAME_SNDR, 1);
}


void CSrWeapView::OnDropSheathSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SheathSound, SR_NAME_SNDR, 1);
}


void CSrWeapView::OnDropSwingSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_SwingSound, SR_NAME_SNDR, 1);
}


void CSrWeapView::OnDropBoundSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_BoundSound, SR_NAME_SNDR, 1);
}


void CSrWeapView::OnDropTrapSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_TrapSound, SR_NAME_SNDR, 1);
}


void CSrWeapView::OnDropBaseWeapon (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_BaseWeapon, SR_NAME_WEAP, 1);
}
