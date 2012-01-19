/*===========================================================================
 *
 * File:		Srselectrecorddlg.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "resource.h"
#include "SrSelectRecordDlg.h"
#include "dialogs\SrEditDlgHandler.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrSelectRecordDlg Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrSelectRecordDlg, CDialog)
	ON_BN_CLICKED(ID_CLEAR_BUTTON, OnClearButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RECORDLIST, OnItemchangedRecordlist)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecord)
	ON_EN_CHANGE(IDC_CURRENT_TEXT, OnChangeCurrentText)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_TYPEFILTER_LIST, &CSrSelectRecordDlg::OnCbnSelchangeTypefilterList)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrSelectRecordDlg Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Script Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_ScptListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ SR_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


static srselrecdlginfo_t s_ItemScriptSelDlg = { 
 // &SR_NAME_SCPT, NULL, _T("Select Item Script..."), s_ScptListInit, &CSrScptRecord::s_FieldMap, SR_FIELD_FLAGS, s_IsTypeScript, SR_SCRIPTTYPE_OBJECT 
	&SR_NAME_NULL, NULL, _T("Select Item Script..."), s_ScptListInit, NULL, SR_FIELD_FLAGS, NULL, 0 
};
  
/*===========================================================================
 *		End of Script Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enchantment Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_EnchListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ SR_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ SR_FIELD_CHARGE,	60,	LVCFMT_CENTER },
	{ SR_FIELD_COST,	60,	LVCFMT_CENTER },
	{ SR_FIELD_AUTOCALC,	50,	LVCFMT_CENTER },
	{ SR_FIELD_EFFECTCOUNT,	80,	LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


bool s_IsTypeEnchant (CSrRecord* pRecord, long UserData) 
{
/*
  CSrEnchRecord* pEnchant = SrCastClass(CSrEnchRecord, pRecord);
  if (pEnchant == NULL) return (false);
  return (pEnchant->GetType() == (dword)UserData);
  */
	return false;
}


static srselrecdlginfo_t s_ApparelEnchantSelDlg = { 
  //&SR_NAME_ENCH, NULL, _T("Select Apparel Enchantment..."), s_EnchListInit, &CSrEnchRecord::s_FieldMap, SR_FIELD_FLAGS, s_IsTypeEnchant, SR_ENCHTYPE_APPAREL 
	&SR_NAME_ENCH, NULL, _T("Select Apparel Enchantment..."), s_EnchListInit, NULL, SR_FIELD_EDITORID, NULL, 0 
};

static srselrecdlginfo_t s_ScrollEnchantSelDlg = { 
 // &SR_NAME_ENCH, NULL, _T("Select Scroll Enchantment..."), s_EnchListInit, &CSrEnchRecord::s_FieldMap, SR_FIELD_FLAGS, s_IsTypeEnchant, SR_ENCHTYPE_SCROLL 
	 &SR_NAME_ENCH, NULL, _T("Select Scroll Enchantment..."), s_EnchListInit, NULL, SR_FIELD_EDITORID, NULL, 0 
};

static srselrecdlginfo_t s_StaffEnchantSelDlg = { 
  //&SR_NAME_ENCH, NULL, _T("Select Staff Enchantment..."), s_EnchListInit, &CSrEnchRecord::s_FieldMap, SR_FIELD_FLAGS, s_IsTypeEnchant, SR_ENCHTYPE_STAFF 
  &SR_NAME_ENCH, NULL, _T("Select Staff Enchantment..."), s_EnchListInit, NULL, SR_FIELD_EDITORID, NULL, 0 
};

static srselrecdlginfo_t s_WeaponEnchantSelDlg = { 
  //&SR_NAME_ENCH, NULL, _T("Select Weapon Enchantment..."), s_EnchListInit, &CSrEnchRecord::s_FieldMap, SR_FIELD_FLAGS, s_IsTypeEnchant, SR_ENCHTYPE_WEAPON 
	&SR_NAME_ENCH, NULL, _T("Select Weapon Enchantment..."), s_EnchListInit, NULL, SR_FIELD_EDITORID, NULL, 0 
};

/*===========================================================================
 *		End of Enchantment Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Keyword Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_KeywordListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


bool s_IsTypeKeyword (CSrRecord* pRecord, long UserData) 
{
	return true;
}

static srselrecdlginfo_t s_KeywordSelDlg = 
{ 
	&SR_NAME_KYWD, NULL, _T("Select Keyword..."), s_KeywordListInit, &CSrKywdRecord::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
/*===========================================================================
 *		End of Keyword Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Component Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_ComponentListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_ITEMNAME,	75,		LVCFMT_CENTER },
	{ SR_FIELD_FLAGS,		50,		LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	75,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


bool l_IsComponentRecord (CSrRecord* pRecord, long UserData) 
{
	return true;
}

static const srrectype_t* s_ComponentRecordTypes[] = {
		&SR_NAME_ARMO, &SR_NAME_WEAP, &SR_NAME_MISC, &SR_NAME_ALCH,
		NULL /* Must be last */
};

static srselrecdlginfo_t s_ComponentRecordSelDlg = 
{ 
	&SR_NAME_NULL, &s_ComponentRecordTypes[0], _T("Select Record..."), s_ComponentListInit, &CSrIdRecord::s_FieldMap, SR_FIELD_EDITORID, l_IsComponentRecord, 0 
};
/*===========================================================================
 *		End of Component Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Outfit Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_OutfitListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		50,		LVCFMT_CENTER },
	{ SR_FIELD_ITEMNAME,	75,		LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	75,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


static const srrectype_t* s_OutfitRecordTypes[] = {
		&SR_NAME_ARMO, &SR_NAME_LVLI, NULL
};

static srselrecdlginfo_t s_OutfitRecordSelDlg = 
{ 
	&SR_NAME_NULL, &s_OutfitRecordTypes[0], _T("Select Record..."), s_OutfitListInit, &CSrIdRecord::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
/*===========================================================================
 *		End of Outfit Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Form List Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_FormListInit[] = 
{
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		50,		LVCFMT_CENTER },
	{ SR_FIELD_ITEMNAME,	75,		LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	75,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


static const srrectype_t* s_FormListRecordTypes[] = 
{
	&SR_NAME_AACT, &SR_NAME_ACHR, &SR_NAME_ACTI, &SR_NAME_ADDN, &SR_NAME_ALCH, &SR_NAME_AMMO, &SR_NAME_ANIO, &SR_NAME_APPA, &SR_NAME_ARMA, &SR_NAME_ARMO, 
	&SR_NAME_ARTO, &SR_NAME_ASPC, &SR_NAME_ASTP, &SR_NAME_AVIF, &SR_NAME_BOOK, &SR_NAME_BPTD, &SR_NAME_CAMS, &SR_NAME_CELL, &SR_NAME_CLAS, 
	&SR_NAME_CLFM, &SR_NAME_CLMT, &SR_NAME_COBJ, &SR_NAME_COLL, &SR_NAME_CONT, &SR_NAME_CPTH, &SR_NAME_CSTY, &SR_NAME_DEBR, &SR_NAME_DIAL, &SR_NAME_DLBR, 
	&SR_NAME_DLVW, &SR_NAME_DOBJ, &SR_NAME_DOOR, &SR_NAME_DUAL, &SR_NAME_ECZN, &SR_NAME_EFSH, &SR_NAME_ENCH, &SR_NAME_EQUP, &SR_NAME_EXPL, &SR_NAME_EYES, 
	&SR_NAME_FACT, &SR_NAME_FLOR, &SR_NAME_FLST, &SR_NAME_FSTP, &SR_NAME_FSTS, &SR_NAME_FURN, &SR_NAME_GLOB, &SR_NAME_GMST, &SR_NAME_GRAS, 
	&SR_NAME_HAZD, &SR_NAME_HAZD, &SR_NAME_HDPT, &SR_NAME_IDLE, &SR_NAME_IDLM, &SR_NAME_IMAD, &SR_NAME_IMGS, &SR_NAME_INFO, &SR_NAME_INGR, &SR_NAME_IPCT, 
	&SR_NAME_IPDS, &SR_NAME_KEYM, &SR_NAME_KYWD, &SR_NAME_LAND, &SR_NAME_LCRT, &SR_NAME_LCTN, &SR_NAME_LGTM, &SR_NAME_LIGH, &SR_NAME_LSCR, &SR_NAME_LTEX, 
	&SR_NAME_LVLI, &SR_NAME_LVLN, &SR_NAME_LVSP, &SR_NAME_MATO, &SR_NAME_MATT, &SR_NAME_MESG, &SR_NAME_MGEF, &SR_NAME_MISC, &SR_NAME_MOVT, &SR_NAME_MSTT, 
	&SR_NAME_MUSC, &SR_NAME_MUST, &SR_NAME_NAVI, &SR_NAME_NAVM, &SR_NAME_NPC_, &SR_NAME_OTFT, &SR_NAME_PACK, &SR_NAME_PERK, &SR_NAME_PGRE, &SR_NAME_PHZD, 
	&SR_NAME_PROJ, &SR_NAME_QUST, &SR_NAME_RACE, &SR_NAME_REFR, &SR_NAME_REGN, &SR_NAME_RELA, &SR_NAME_REVB, &SR_NAME_RFCT,  
	&SR_NAME_SCEN, &SR_NAME_SCRL, &SR_NAME_SHOU, &SR_NAME_SLGM, &SR_NAME_SMBN, &SR_NAME_SMEN, &SR_NAME_SMQN, &SR_NAME_SNCT, 
	&SR_NAME_SNDR, &SR_NAME_SOPM, &SR_NAME_SOUN, &SR_NAME_SPEL, &SR_NAME_SPGD, &SR_NAME_STAT, &SR_NAME_TACT, &SR_NAME_TREE, &SR_NAME_TXST, &SR_NAME_VTYP, 
	&SR_NAME_WATR, &SR_NAME_WEAP, &SR_NAME_WOOP, &SR_NAME_WRLD, &SR_NAME_WTHR, 
	NULL
};


static srselrecdlginfo_t s_FormListRecordSelDlg = 
{ 
	&SR_NAME_NULL, &s_FormListRecordTypes[0], _T("Select Record..."), s_FormListInit, &CSrRecord::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
/*===========================================================================
 *		End of Form List Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Equip Slot Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_EquipSlotListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_RECORDTYPE,	75,		LVCFMT_CENTER },
	{ SR_FIELD_FLAGS,		50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };


static srselrecdlginfo_t s_EquipSlotRecordSelDlg = 
{ 
	&SR_NAME_EQUP, NULL,  _T("Select Equipment Slot Record..."), s_EquipSlotListInit, &CSrEqupRecord::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
/*===========================================================================
 *		End of Equip Slot Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Actor Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_ActorListInit[] = 
{
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		60,		LVCFMT_CENTER },
	{ SR_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };

static const srrectype_t* s_ActorTypes[] = { 
	&SR_NAME_NPC_, NULL  //&SR_NAME_CREA,
};

static srselrecdlginfo_t s_ActorSelDlg = 
{
	NULL, s_ActorTypes, _T("Select Actor..."), s_ActorListInit, &CSrNpc_Record::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
  
/*===========================================================================
 *		End of Actor Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Ingrediant Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_IngrediantListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,	75,	LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,	60,	LVCFMT_CENTER },
	{ SR_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };

static srselrecdlginfo_t s_IngrediantSelDlg = 
{
	&SR_NAME_INGR, NULL, _T("Select Ingrediant..."), s_IngrediantListInit, &CSrIngrRecord::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
  
/*===========================================================================
 *		End of Ingrediant Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Sound Dialog Data
 *
 *=========================================================================*/
static srreclistcolinit_t s_SoundListInit[] = 
{
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		60,		LVCFMT_CENTER },
	{ SR_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
};

static srselrecdlginfo_t s_SoundSelDlg = 
{
	&SR_NAME_SOUN, NULL, _T("Select Sound..."), s_SoundListInit,  &CSrSounRecord::s_FieldMap, SR_FIELD_EDITORID, NULL, 0 
};
  
/*===========================================================================
 *		End of Sound Dialog Data
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Constructor
 *
 *=========================================================================*/
CSrSelectRecordDlg::CSrSelectRecordDlg (CWnd* pParent) : CDialog(CSrSelectRecordDlg::IDD, pParent) {
  m_pRecordHandler = NULL;
  m_pPrevRecord    = NULL;
  m_pCurrentRecord = NULL;
  m_IsInitialized  = false;
  m_EditorIDCheck  = SR_CHECKRESULT_NOCHANGE;

  m_CurrentTypeFilter = SR_NAME_NULL;

  m_UpdateListOnChange = false;
  m_ListAllOption      = true;

  m_InitialFormID  = SR_FORMID_NULL;
  m_CurrentFormID  = SR_FORMID_NULL;
}
/*===========================================================================
 *		End of Class CSrSelectRecordDlg Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CURRENT_FORMID, m_CurrentFormIDText);
	DDX_Control(pDX, IDC_PREVIOUS_FORMID, m_PreviousFormIDText);
	DDX_Control(pDX, ID_CLEAR_BUTTON, m_ClearButton);
	DDX_Control(pDX, IDC_CURRENT_TEXT, m_CurrentText);
	DDX_Control(pDX, IDC_PREVIOUS_TEXT, m_PreviousText);
	DDX_Control(pDX, IDC_RECORDLIST, m_RecordList);
	DDX_Control(pDX, IDC_TYPEFILTER_STATIC, m_TypeFilterLabel);
	DDX_Control(pDX, IDC_TYPEFILTER_LIST, m_TypeFilterList);
}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void AddListColumns (void);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::AddListColumns (void) {

  m_RecordList.DeleteAllColumns();

  if (m_DlgInfo.pListColumns == NULL || m_DlgInfo.pFieldMap == NULL) return;
  
  if (m_DlgInfo.pRecordType != NULL)
    m_RecordList.SetupList(*m_DlgInfo.pRecordType, m_DlgInfo.pListColumns, m_DlgInfo.pFieldMap);
  else if (m_DlgInfo.ppRecordArray != NULL && m_DlgInfo.ppRecordArray[0] != NULL) 
    m_RecordList.SetupList(*m_DlgInfo.ppRecordArray[0], m_DlgInfo.pListColumns, m_DlgInfo.pFieldMap);

}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::AddListColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void FillRecordList (RecordType);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::FillRecordList (const srrectype_t RecordType) {
  CSrTypeGroup*  pGroup;
  CSrBaseRecord* pBaseRecord;
  CSrRecord*	 pRecord;
  dword			 Index;
  bool           Result;
  
	/* Get the type group for the given record type */
  pGroup = m_pRecordHandler->GetTopGroup()->GetTypeGroup(RecordType);
  if (pGroup == NULL) return;

	/* Add all matching records in the group */
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pRecord     = SrCastRecord(pBaseRecord);
    if (pRecord == NULL) continue;

		/* Use the callback check function if present */
    if (m_DlgInfo.pCheckFunc != NULL) {
      Result = m_DlgInfo.pCheckFunc(pRecord, m_DlgInfo.UserData);
      if (!Result) continue;
    }

		/* Add the record */
    m_RecordList.AddRecord(pRecord);
  }

}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::FillRecordList()
 *=========================================================================*/


void CSrSelectRecordDlg::FillFilterList (void)
{
	m_TypeFilterList.ResetContent();

	if (m_DlgInfo.ppRecordArray == NULL) return;

    for (int i = 0; m_DlgInfo.ppRecordArray[i] != NULL; ++i) 
	{
		CString Buffer;
		Buffer.Format("%4.4s", m_DlgInfo.ppRecordArray[i]->Name );

		int ListIndex = m_TypeFilterList.AddString(Buffer);
		if (ListIndex >= 0) m_TypeFilterList.SetItemData(ListIndex, m_DlgInfo.ppRecordArray[i]->Value);
    }

	if (m_ListAllOption)
	{
		int ListIndex = m_TypeFilterList.InsertString(0, "All");
		if (ListIndex >= 0) m_TypeFilterList.SetItemData(ListIndex, 0);

		if (m_CurrentTypeFilter != SR_NAME_NULL)
		    FindComboBoxItemData (m_TypeFilterList, m_CurrentTypeFilter.Value, true);
		else
			m_TypeFilterList.SelectString(-1, "All");
	}
	else if (m_CurrentTypeFilter != SR_NAME_NULL)
	{
	    FindComboBoxItemData (m_TypeFilterList, m_CurrentTypeFilter.Value, true);
	}
	else
	{
		m_TypeFilterList.SetCurSel(0);
	}

}


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void FillRecordList (void);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::FillRecordList (void) {
  dword Index;

  	/* Clear the current content */
  m_RecordList.SetRedraw(FALSE);
  m_RecordList.DeleteAllItems();

	/* Ensure a valid object state */
  if (m_pRecordHandler == NULL) 
  {
	m_RecordList.SetRedraw(TRUE);
	return;
  }

	/* Add a single record type */
  if (m_DlgInfo.pRecordType != NULL) FillRecordList(*m_DlgInfo.pRecordType);

	/* Add several record types */
  if (m_DlgInfo.ppRecordArray != NULL) {
    for (Index = 0; m_DlgInfo.ppRecordArray[Index] != NULL; ++Index) {

		if (m_CurrentTypeFilter == SR_NAME_NULL || m_CurrentTypeFilter == *m_DlgInfo.ppRecordArray[Index])
		{
			FillRecordList(*m_DlgInfo.ppRecordArray[Index]);
		}
    }
  }

  m_RecordList.SetRedraw(TRUE);
}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::FillRecordList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::GetControlData (void) {
  m_pCurrentRecord = m_RecordList.GetSelectedRecord();

  if (m_pCurrentRecord == NULL) 
    m_CurrentFormID = SR_FORMID_NULL;
  else
    m_CurrentFormID = m_pCurrentRecord->GetFormID();

}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - void OnClearButton ();
 *
 *=========================================================================*/
void CSrSelectRecordDlg::OnClearButton() {

  m_pCurrentRecord = NULL;
  m_CurrentFormID  = SR_FORMID_NULL;
  m_CurrentEditorID.Empty();

  EndDialog(IDOK);
  //UpdateCurrentRecord();
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnClearButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - LRESULT OnEditRecord (lParam, wParam);
 *
 *=========================================================================*/
LRESULT CSrSelectRecordDlg::OnEditRecord (WPARAM lParam, LPARAM wParam) {
  CSrRecord* pRecord = (CSrRecord *) lParam;

  OnOK();
  return (0);
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - BOOL OnInitDialog ();
 *
 *=========================================================================*/
BOOL CSrSelectRecordDlg::OnInitDialog() {
  CDialog::OnInitDialog();	

  m_UpdateListOnChange = false;
  SetWindowText(m_DlgInfo.pTitle);
  m_ClearButton.ShowWindow(m_AllowNullRecord ? SW_SHOW : SW_HIDE);

  if (m_pRecordHandler != NULL) 
  {
    if (!m_InitialEditorID.IsEmpty()) 
	{
      m_pPrevRecord = m_pRecordHandler->FindEditorID(m_InitialEditorID);
    }
    else 
	{
      m_pPrevRecord = m_pRecordHandler->FindFormID(m_InitialFormID);
    }

    m_pCurrentRecord = m_pPrevRecord;
  }

  if (m_pCurrentRecord != NULL)
  {
	  m_CurrentTypeFilter = m_pCurrentRecord->GetRecordType();
  }
  else if (m_DlgInfo.ppRecordArray != NULL)
  {
	  m_CurrentTypeFilter = *m_DlgInfo.ppRecordArray[0];
  }
  else if (m_DlgInfo.pRecordType != NULL)
  {
	  m_CurrentTypeFilter = *m_DlgInfo.pRecordType;
  }
  
  bool ShowFilter = m_DlgInfo.ppRecordArray != NULL;
  m_TypeFilterLabel.ShowWindow(ShowFilter);
  m_TypeFilterList.ShowWindow(ShowFilter);
  if (ShowFilter) FillFilterList();

	/* Initialize the record list */
  m_RecordList.SetListName("SelectRecordList");
  m_RecordList.DefaultSettings();
  AddListColumns();
  FillRecordList();

  SetControlData();
  m_RecordList.SetFocus();

  m_IsInitialized      = true;
  m_UpdateListOnChange = true;

  return (false);
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnInitDialog()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - void OnItemchangedRecordlist (pNMHDR, pResult);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::OnItemchangedRecordlist (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

  *pResult = 0;
  if (!m_IsInitialized) return;
  if (!m_UpdateListOnChange) return;

  GetControlData();
  UpdateCurrentRecord();
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnItemchangedRecordlist()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - void OnOK ();
 *
 *=========================================================================*/
void CSrSelectRecordDlg::OnOK() {
  //GetControlData();

  CDialog::OnOK();
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnOK()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::SetControlData (void) {
  CString      Buffer;
  CString      EditorID;
  CSrIdRecord* pIdRecord;

  m_RecordList.SortList(SR_FIELD_EDITORID);
  if (m_DlgInfo.SortField != SR_FIELD_EDITORID) m_RecordList.SortList(m_DlgInfo.SortField);

  m_RecordList.SelectRecord(m_pCurrentRecord);

  if (m_pPrevRecord == NULL) {
    m_PreviousText.SetWindowText("");
    m_PreviousFormIDText.SetWindowText("0x00000000");
  }
  else {
    pIdRecord = SrCastClass(CSrIdRecord, m_pPrevRecord);
    if (pIdRecord != NULL) EditorID = pIdRecord->GetEditorID();

    Buffer.Format("%s", EditorID);
    m_PreviousText.SetWindowText(Buffer);

    Buffer.Format("0x%08X", m_pPrevRecord->GetFormID());
    m_PreviousFormIDText.SetWindowText(Buffer);
  }

  UpdateCurrentRecord();
}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - void UpdateCurrentRecord (void);
 *
 *=========================================================================*/
void CSrSelectRecordDlg::UpdateCurrentRecord (void) { 
  CString      Buffer;
  CSrIdRecord* pIdRecord;

  //m_pCurrentRecord = m_RecordList.GetSelectedRecord();
  m_CurrentEditorID.Empty();

  if (m_pCurrentRecord == NULL) {
    m_CurrentText.SetWindowText("");
    m_CurrentFormIDText.SetWindowText("0x00000000");
  }
  else {
    pIdRecord = SrCastClass(CSrIdRecord, m_pCurrentRecord);
    if (pIdRecord != NULL) m_CurrentEditorID = pIdRecord->GetEditorID();

    Buffer.Format("%s", m_CurrentEditorID);
    m_CurrentText.SetWindowText(Buffer);

    Buffer.Format("0x%08X", m_pCurrentRecord->GetFormID());
    m_CurrentFormIDText.SetWindowText(Buffer);
  }

}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::UpdateCurrentRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - void OnChangeCurrentText ();
 *
 *=========================================================================*/
void CSrSelectRecordDlg::OnChangeCurrentText() {
  CString       Buffer;
  int		Result;
  int		ListIndex;
  
  Result = UpdateEditorID();

  if (Result != m_EditorIDCheck) 
  {
    m_EditorIDCheck = Result;
    m_CurrentText.RedrawWindow();
  }

  if (m_UpdateListOnChange) 
  {
    m_UpdateListOnChange = false;
    m_CurrentText.GetWindowText(Buffer);
    
    ListIndex = m_RecordList.FindEditorID(Buffer);

    if (ListIndex >= 0) m_RecordList.SelectRecord(ListIndex);
   /*
    int StartSel;
    int EndSel;
    CSrRecord*   pRecord = m_RecordList.GetRecord(ListIndex);
    CSrIdRecord* pIdRecord = NULL;
    if (pRecord != NULL) pIdRecord = SrCastClass(CSrIdRecord, pRecord);

    if (pIdRecord != NULL) {
      m_CurrentText.GetSel(StartSel, EndSel);
      m_CurrentText.SetWindowText(pIdRecord->GetEditorID());
      m_CurrentText.SetSel(StartSel, -1);
    } /*/

    m_UpdateListOnChange = true;
  }
	
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnChangeCurrentText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Event - HBRUSH OnCtlColor (pDC, pWnd, nCtlColor);
 *
 *=========================================================================*/
HBRUSH CSrSelectRecordDlg::OnCtlColor (CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
  HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

  if (nCtlColor == CTLCOLOR_EDIT && pWnd == &m_CurrentText) {
    switch (m_EditorIDCheck) {
      case SR_CHECKRESULT_NOCHANGE:
        hBrush = CreateSolidBrush(RGB(255,255,255));
        pDC->SetBkColor(RGB(255,255,255));
	break;
      case SR_CHECKRESULT_OK:
        hBrush = CreateSolidBrush(RGB(204,255,204));
        pDC->SetBkColor(RGB(204,255,204));
	break;
      case SR_CHECKRESULT_ERROR:
        hBrush = CreateSolidBrush(RGB(255,204,204));
        pDC->SetBkColor(RGB(255,204,204));
	break;
    }
  }

  return (hBrush);
}
/*===========================================================================
 *		End of Class Event CSrSelectRecordDlg::OnCtlColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrSelectRecordDlg Method - int UpdateEditorID (void);
 *
 *=========================================================================*/
int CSrSelectRecordDlg::UpdateEditorID (void) {
  CString	Buffer;
  CSString	EditorID;
  CSrIdRecord*	pIdRecord;
  int		ListIndex;

  m_CurrentText.GetWindowText(Buffer);
  EditorID = Buffer;

  SrPrepareEditorID(EditorID);

  if (EditorID.IsEmpty()) 
  {
    m_CurrentFormID = 0;
  }
  else 
  {  
    pIdRecord = m_pRecordHandler->FindEditorID(EditorID);
    if (pIdRecord == NULL) return (SR_CHECKRESULT_ERROR);

    ListIndex = m_RecordList.FindRecord(pIdRecord);
    if (ListIndex < 0) return (SR_CHECKRESULT_ERROR);

	m_CurrentEditorID = pIdRecord->GetEditorID();
    m_CurrentFormID = pIdRecord->GetFormID();
  }

  if (m_CurrentFormID == m_InitialFormID) return (SR_CHECKRESULT_NOCHANGE);

  Buffer.Format(_T("0x%08X"), m_CurrentFormID);
  m_CurrentFormIDText.SetWindowText(Buffer);

  return (SR_CHECKRESULT_OK);
}
/*===========================================================================
 *		End of Class Method CSrSelectRecordDlg::UpdateEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectActor (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectActor (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ActorSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectActor()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectItemScript (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectItemScript (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ItemScriptSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectItemScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectIngrediant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectIngrediant (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_IngrediantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectIngrediant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectApparelEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectApparelEnchant (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ApparelEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectApparelEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectScrollEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectScrollEnchant (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_ScrollEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectScrollEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectSound (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectSound (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_SoundSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectStaffEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectStaffEnchant (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_StaffEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectStaffEnchant()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectWeaponEnchant (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectWeaponEnchant (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_WeaponEnchantSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectWeaponEnchant()
 *=========================================================================*/


bool SrSelectFormListItem (srformid_t& FormID, CSrRecordHandler* pRecordHandler) 
{
	CSrSelectRecordDlg  Dlg;
	int					Result;
	
	Dlg.SetListAllOption(false);
	Dlg.SetInitialFormID(FormID);
	Dlg.SetRecordHandler(pRecordHandler);
	Dlg.SetDlgInfo(s_FormListRecordSelDlg);
	Dlg.SetAllowNull(true);
	
	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);
	
	FormID = Dlg.GetCurrentFormID();
	return (true);
}


bool SrSelectOutfitItem (CString& EditorID, CSrRecordHandler* pRecordHandler) 
{
	CSrSelectRecordDlg  Dlg;
	int					Result;
	
	Dlg.SetInitialEditorID(EditorID);
	Dlg.SetRecordHandler(pRecordHandler);
	Dlg.SetDlgInfo(s_OutfitRecordSelDlg);
	Dlg.SetAllowNull(true);
	
	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);
	
	EditorID = Dlg.GetCurrentEditorID();
	return (true);
}


bool SrSelectRecord (CString& EditorID, CSrRecordHandler* pRecordHandler, const srrectype_t** ppType, const srrecfieldmap_t* pFieldMap) 
{
	
srreclistcolinit_t GeneralListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		60,		LVCFMT_CENTER },
	{ SR_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };

srselrecdlginfo_t GeneralSelDlg = {
	NULL, ppType, _T("Select Record..."), GeneralListInit, pFieldMap, SR_FIELD_EDITORID, NULL, 0 
};

	CSrSelectRecordDlg Dlg;
	int				   Result;

	Dlg.SetInitialEditorID(EditorID);
	Dlg.SetRecordHandler(pRecordHandler);
	Dlg.SetDlgInfo(GeneralSelDlg);
	Dlg.SetAllowNull(true);

	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);

	EditorID = Dlg.GetCurrentEditorID();
	return (true);
}


bool SrSelectRecord (CString& EditorID, CSrRecordHandler* pRecordHandler, const srrectype_t Type, const srrecfieldmap_t* pFieldMap) 
{
	srrectype_t ThisType(Type);

srreclistcolinit_t GeneralListInit[] = {
	{ SR_FIELD_EDITORID,	200,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,		75,		LVCFMT_LEFT },
	{ SR_FIELD_FLAGS,		60,		LVCFMT_CENTER },
	{ SR_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ SR_FIELD_RECORDTYPE,	60,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
  };

srselrecdlginfo_t GeneralSelDlg = {
	&ThisType, NULL, _T("Select Record..."), GeneralListInit, pFieldMap, SR_FIELD_EDITORID, NULL, 0 
};

	CSrSelectRecordDlg Dlg;
	int				   Result;

	Dlg.SetInitialEditorID(EditorID);
	Dlg.SetRecordHandler(pRecordHandler);
	Dlg.SetDlgInfo(GeneralSelDlg);
	Dlg.SetAllowNull(true);

	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);

	EditorID = Dlg.GetCurrentEditorID();
	return (true);
}


bool SrSelectComponent (CString& EditorID, CSrRecordHandler* pRecordHandler)
{
	CSrSelectRecordDlg	Dlg;
	int					Result;

	Dlg.SetInitialEditorID(EditorID);
	Dlg.SetRecordHandler(pRecordHandler);
	Dlg.SetDlgInfo(s_ComponentRecordSelDlg);
	Dlg.SetAllowNull(false);

	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);

	EditorID = Dlg.GetCurrentEditorID();
  	return true;
}


bool SrSelectEquipSlot (CString& EditorID, CSrRecordHandler* pRecordHandler)
{
	CSrSelectRecordDlg	Dlg;
	int					Result;

	Dlg.SetInitialEditorID(EditorID);
	Dlg.SetRecordHandler(pRecordHandler);
	Dlg.SetDlgInfo(s_EquipSlotRecordSelDlg);
	Dlg.SetAllowNull(false);

	Result = Dlg.DoModal();
	if (Result != IDOK) return (false);

	EditorID = Dlg.GetCurrentEditorID();
  	return true;
}


/*===========================================================================
 *
 * Function - bool SrSelectKeyword (EditorID, pRecordHandler);
 *
 *=========================================================================*/
bool SrSelectKeyword (CString& EditorID, CSrRecordHandler* pRecordHandler) {
  CSrSelectRecordDlg Dlg;
  int		     Result;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(s_KeywordSelDlg);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectKeyword()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool SrSelectKeyword (EditorID, pRecordHandler, pFilter);
 *
 *=========================================================================*/
bool l_IsTypeKeywordFilter (CSrRecord* pRecord, long UserData) 
{
	const char* pFilter = (const char *) UserData;
	if (pFilter == NULL) return true;

	CSrKywdRecord* pKeyword = SrCastClassNull(CSrKywdRecord, pRecord);
	if (pKeyword == NULL) return false;

	size_t Length = strlen(pFilter);
	return strnicmp(pKeyword->GetEditorID(), pFilter, Length) == 0;
}


bool SrSelectKeyword (CString& EditorID, CSrRecordHandler* pRecordHandler, const char* pFilter) {
  CSrSelectRecordDlg	Dlg;
  srselrecdlginfo_t		TmpInfo(s_KeywordSelDlg);
  int					Result;

  TmpInfo.UserData = (dword) pFilter;
  TmpInfo.pCheckFunc = l_IsTypeKeywordFilter;

  Dlg.SetInitialEditorID(EditorID);
  Dlg.SetRecordHandler(pRecordHandler);
  Dlg.SetDlgInfo(TmpInfo);
  Dlg.SetAllowNull(true);

  Result = Dlg.DoModal();
  if (Result != IDOK) return (false);

  EditorID = Dlg.GetCurrentEditorID();
  return (true);
}
/*===========================================================================
 *		End of Function SrSelectKeyword()
 *=========================================================================*/


void CSrSelectRecordDlg::OnCbnSelchangeTypefilterList()
{
	srrectype_t NewFilter = SR_NAME_NULL;
	int ListIndex = m_TypeFilterList.GetCurSel();

	if (ListIndex >= 0)
	{
		NewFilter = (srrectype_t) m_TypeFilterList.GetItemData(ListIndex);
	}
	
	if (NewFilter == m_CurrentTypeFilter) return;

	m_CurrentTypeFilter = NewFilter;

	m_IsInitialized = false;
	m_UpdateListOnChange = false;

	FillRecordList();

	m_IsInitialized = true;
	m_UpdateListOnChange = true;
}

