
#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageBasic.h"
#include "afxdialogex.h"
#include "SrBodyPartsListDlg.h"
#include "SrEditFlagsDlg.h"


IMPLEMENT_DYNAMIC(CSrRacePageBasic, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageBasic, CPropertyPage)
	ON_BN_CLICKED(IDC_RACEFLAGS, &CSrRacePageBasic::OnBnClickedRaceflags)
	ON_BN_CLICKED(IDC_ADD_SPELL, &CSrRacePageBasic::OnBnClickedAddSpell)
	ON_BN_CLICKED(IDC_EDIT_SPELL, &CSrRacePageBasic::OnBnClickedEditSpell)
	ON_BN_CLICKED(IDC_DEL_SPELL, &CSrRacePageBasic::OnBnClickedDelSpell)
	ON_LBN_DBLCLK(SPELLS, &CSrRacePageBasic::OnLbnDblclkSpells)
	ON_BN_CLICKED(IDC_ADDKEYWORD_BUTTON, OnBnClickedAddkeywordButton)
	ON_BN_CLICKED(IDC_EDITKEYWORD_BUTTON, OnBnClickedEditkeywordButton)
	ON_BN_CLICKED(IDC_DELKEYWORD_BUTTON, OnBnClickedDelkeywordButton)
	ON_LBN_DBLCLK(IDC_KEYWORDS, OnBnClickedEditkeywordButton)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropKeywords)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropKeywords)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropSpells)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropSpells)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropEquipSlots)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropEquipSlots)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORDS, OnDropUnequipSlot)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORDS, OnDropUnequipSlot)
	ON_BN_CLICKED(IDC_ADD_EQUIPSLOT, &CSrRacePageBasic::OnBnClickedAddEquipslot)
	ON_BN_CLICKED(IDC_EDIT_EQUIPSLOT, &CSrRacePageBasic::OnBnClickedEditEquipslot)
	ON_BN_CLICKED(IDC_DEL_EQUIPSLOT, &CSrRacePageBasic::OnBnClickedDelEquipslot)
	ON_BN_CLICKED(IDC_EDIT_UNEQUIPSLOT, &CSrRacePageBasic::OnBnClickedEditUnequipslot)
	ON_BN_CLICKED(IDC_SELECT_UNEQUIPSLOT, &CSrRacePageBasic::OnBnClickedSelectUnequipslot)
	ON_LBN_DBLCLK(IDC_EQUIPSLOTS, &CSrRacePageBasic::OnLbnDblclkEquipslots)
END_MESSAGE_MAP()


CSrRacePageBasic::CSrRacePageBasic(srraceinfo_t& RaceInfo)
	: CPropertyPage(CSrRacePageBasic::IDD), m_RaceInfo(RaceInfo)
{
	m_pDlgHandler = NULL;
	m_pParent     = NULL;
}

CSrRacePageBasic::~CSrRacePageBasic()
{
}


void CSrRacePageBasic::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_DESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_ACTORVALUE1, m_ActorValue[0]);
	DDX_Control(pDX, IDC_ACTORVALUE2, m_ActorValue[1]);
	DDX_Control(pDX, IDC_ACTORVALUE3, m_ActorValue[2]);
	DDX_Control(pDX, IDC_ACTORVALUE4, m_ActorValue[3]);
	DDX_Control(pDX, IDC_ACTORVALUE5, m_ActorValue[4]);
	DDX_Control(pDX, IDC_ACTORVALUE6, m_ActorValue[5]);
	DDX_Control(pDX, IDC_ACTORVALUE7, m_ActorValue[6]);
	DDX_Control(pDX, IDC_ACTORSKILL1, m_ActorSkill[0]);
	DDX_Control(pDX, IDC_ACTORSKILL2, m_ActorSkill[1]);
	DDX_Control(pDX, IDC_ACTORSKILL3, m_ActorSkill[2]);
	DDX_Control(pDX, IDC_ACTORSKILL4, m_ActorSkill[3]);
	DDX_Control(pDX, IDC_ACTORSKILL5, m_ActorSkill[4]);
	DDX_Control(pDX, IDC_ACTORSKILL6, m_ActorSkill[5]);
	DDX_Control(pDX, IDC_ACTORSKILL7, m_ActorSkill[6]);
	DDX_Control(pDX, IDC_RACEFLAGS, m_RaceFlags);
	DDX_Control(pDX, IDC_SPELLS, m_SpellList);
	DDX_Control(pDX, IDC_KEYWORDS, m_Keywords);
	DDX_Control(pDX, IDC_EQUIPSLOTS, m_EquipSlots);
	DDX_Control(pDX, IDC_UNEQUIPSLOT, m_UnequipSlot);
}


BOOL CSrRacePageBasic::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SrFillComboList(m_ActorValue[0], s_SrActorSkillValues, 0);
	SrFillComboList(m_ActorValue[1], s_SrActorSkillValues, 0);
	SrFillComboList(m_ActorValue[2], s_SrActorSkillValues, 0);
	SrFillComboList(m_ActorValue[3], s_SrActorSkillValues, 0);
	SrFillComboList(m_ActorValue[4], s_SrActorSkillValues, 0);
	SrFillComboList(m_ActorValue[5], s_SrActorSkillValues, 0);
	SrFillComboList(m_ActorValue[6], s_SrActorSkillValues, 0);	

	return TRUE;
}


void CSrRacePageBasic::OnBnClickedRaceflags()
{
	CString Buffer;
	dword Flags = 0;

	m_RaceFlags.GetWindowText(Buffer);
	Flags = strtoul(Buffer, NULL, 0);	

	if (!SrEditFlagsDlg(Flags, 0xFFFFFFFF)) return;

	Buffer.Format("0x%08X", Flags);
	m_RaceFlags.SetWindowText(Buffer);
}


void CSrRacePageBasic::GetControlData (void)
{
	CString Buffer;

	CSrRaceRecord* pRace = SrCastClass(CSrRaceRecord, m_pParent->GetOutputRecord());
	if (pRace == NULL) return;

	pRace->DeleteSubrecords(SR_NAME_SPLO);
	pRace->DeleteSubrecords(SR_NAME_SPCT);
	
	for (int i = 0; i < m_SpellList.GetCount(); ++i)
	{
		m_SpellList.GetText(i, Buffer);
		CSrRecord* pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord) pRace->AddSpell(pRecord->GetFormID());
	}

	pRace->UpdateSpellCount();
	m_RaceInfo.EquipSlots.Destroy();

	for (int i = 0; i < m_EquipSlots.GetCount(); ++i)
	{
		m_EquipSlots.GetText(i, Buffer);
		CSrRecord* pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		if (pRecord != NULL) m_RaceInfo.AddEquipSlot(pRecord->GetFormID());
	}

	m_UnequipSlot.GetWindowTextA(Buffer);
	CSrRecord* pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.UnequipSlot.SetValue(pRecord ? pRecord->GetFormID() : 0);
}


void CSrRacePageBasic::SetControlData (void)
{
	CSrRaceRecord* pRace = SrCastClass(CSrRaceRecord, m_pParent->GetInputRecord());
	int Position;

	m_SpellList.ResetContent();
	if (pRace == NULL) return;
	
	CSrSubrecord* pSubrecord = pRace->FindFirstSubrecord(SR_NAME_SPLO, Position);

	while (pSubrecord)
	{
		CSrFormidSubrecord* pFormid = SrCastClass(CSrFormidSubrecord, pSubrecord);
		m_SpellList.AddString(m_pParent->m_pRecordHandler->GetEditorID(pFormid->GetValue()));
		pSubrecord = pRace->FindNextSubrecord(SR_NAME_SPLO, Position);
	}

	m_EquipSlots.ResetContent();

	for (dword i = 0; i < m_RaceInfo.EquipSlots.GetSize(); ++i)
	{
		const char* pString = m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.EquipSlots[i]->GetValue());
		if (pString) m_EquipSlots.AddString(pString);
	}

	m_UnequipSlot.SetWindowText(m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.UnequipSlot.GetValue()));
}


void CSrRacePageBasic::OnBnClickedAddSpell()
{
	static const srrectype_t* s_Types[] = { &SR_NAME_SPEL, &SR_NAME_SHOU, NULL };
	CString Buffer;
	bool Result;

	Result = SrSelectRecord(Buffer, m_pParent->m_pRecordHandler, &s_Types[0], &CSrIdRecord::s_FieldMap);
	if (!Result) return;

	m_SpellList.AddString(Buffer);
}


void CSrRacePageBasic::OnBnClickedEditSpell()
{
	static const srrectype_t* s_Types[] = { &SR_NAME_SPEL, &SR_NAME_SHOU, NULL};
	CString Buffer;
	bool Result;
	int ListIndex = m_SpellList.GetCurSel();
	if (ListIndex < 0) return;

	m_SpellList.GetText(ListIndex, Buffer);

	Result = SrSelectRecord(Buffer, m_pParent->m_pRecordHandler, &s_Types[0], &CSrIdRecord::s_FieldMap);
	if (!Result) return;

	m_SpellList.DeleteString(ListIndex);
	m_SpellList.InsertString(ListIndex, Buffer);	
}


void CSrRacePageBasic::OnBnClickedDelSpell()
{
	int ListIndex = m_SpellList.GetCurSel();
	if (ListIndex < 0) return;
	m_SpellList.DeleteString(ListIndex);

	if (ListIndex > 0)
		m_SpellList.SetCurSel(ListIndex - 1);
	else
		m_SpellList.SetCurSel(0);
}


void CSrRacePageBasic::OnLbnDblclkSpells()
{
	OnBnClickedEditSpell();
}


/*===========================================================================
 *
 * Class CSrRacePageBasic Event - void OnBnClickedAddkeywordButton (void);
 *
 *=========================================================================*/
 void CSrRacePageBasic::OnBnClickedAddkeywordButton()
 {
	 CString    Buffer;
	 int		Index;
	 bool		Result;
	 	 
	 Result = m_pDlgHandler->SelectKeyword(Buffer);
	 if (!Result) return;
	 
	 Index = m_Keywords.AddString(Buffer);
	 m_Keywords.SetCurSel(Index);
 }
/*===========================================================================
 *		End of Class Event CSrRacePageBasic::OnBnClickedAddkeywordButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRacePageBasic Event - void OnBnClickedEditkeywordButton (void);
 *
 *=========================================================================*/
 void CSrRacePageBasic::OnBnClickedEditkeywordButton()
 {
	 CString	Buffer;
	 int		Index;
	 bool		Result;

	 Index = m_Keywords.GetCurSel();
	 if (Index < 0) return;

	 m_Keywords.GetText(Index, Buffer);

	 Result = m_pDlgHandler->SelectKeyword(Buffer);
	 if (!Result) return;
	 
	 m_Keywords.DeleteString(Index);
	 if (!Buffer.IsEmpty()) Index = m_Keywords.AddString(Buffer);
	 m_Keywords.SetCurSel(Index);
 }
/*===========================================================================
 *		End of Class Event CSrRacePageBasic::OnBnClickedEditkeywordButton()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrRacePageBasic Event - void OnBnClickedDelkeywordButton (void);
 *
 *=========================================================================*/
 void CSrRacePageBasic::OnBnClickedDelkeywordButton()
 {
	 int ListIndex;

	 ListIndex = m_Keywords.GetCurSel();
	 if (ListIndex < 0) return;

	 m_Keywords.DeleteString(ListIndex);

	 if (ListIndex > 0)
		m_Keywords.SetCurSel(ListIndex - 1);
	else
		m_Keywords.SetCurSel(0);
 }
/*===========================================================================
 *		End of Class Event CSrRacePageBasic::OnBnClickedDelkeywordButton()
 *=========================================================================*/


void CSrRacePageBasic::OnDropKeywords (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	CSrRecord*	       pRecord;
	CSrIdRecord*       pIdRecord;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pRecords == NULL) return;
	
	for (dword i = 0; i < pDropItems->pRecords->GetSize(); ++i)
	{
		pRecord = pDropItems->pRecords->GetAt(i);

			/* Ignore any invalid record types */
		if (pRecord->GetRecordType() != SR_NAME_KYWD) return;
		pIdRecord = SrCastClass(CSrIdRecord, pRecord);
		if (pIdRecord == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			if (m_Keywords.FindString(-1, pIdRecord->GetEditorID()) < 0) m_Keywords.AddString(pIdRecord->GetEditorID());
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;
}


void CSrRacePageBasic::OnDropSpells (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	CSrRecord*	       pRecord;
	CSrIdRecord*       pIdRecord;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pRecords == NULL) return;
	
	for (dword i = 0; i < pDropItems->pRecords->GetSize(); ++i)
	{
		pRecord = pDropItems->pRecords->GetAt(i);

			/* Ignore any invalid record types */
		if (pRecord->GetRecordType() != SR_NAME_SPEL && pRecord->GetRecordType() != SR_NAME_SHOU) return;
		pIdRecord = SrCastClass(CSrIdRecord, pRecord);
		if (pIdRecord == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			if (m_SpellList.FindString(-1, pIdRecord->GetEditorID()) < 0) m_SpellList.AddString(pIdRecord->GetEditorID());
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;	
}


void CSrRacePageBasic::OnDropEquipSlots (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	CSrRecord*	       pRecord;
	CSrIdRecord*       pIdRecord;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pRecords == NULL) return;
	
	for (dword i = 0; i < pDropItems->pRecords->GetSize(); ++i)
	{
		pRecord = pDropItems->pRecords->GetAt(i);

			/* Ignore any invalid record types */
		if (pRecord->GetRecordType() != SR_NAME_EQUP) return;
		pIdRecord = SrCastClass(CSrIdRecord, pRecord);
		if (pIdRecord == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			if (m_EquipSlots.FindString(-1, pIdRecord->GetEditorID()) < 0) m_EquipSlots.AddString(pIdRecord->GetEditorID());
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;	
}


void CSrRacePageBasic::OnBnClickedAddEquipslot()
{
	 CString    Buffer;
	 int		Index;
	 bool		Result;
	 	 
	 Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_EQUP, &CSrEqupRecord::s_FieldMap);
	 if (!Result) return;
	 
	 Index = m_EquipSlots.AddString(Buffer);
	 m_EquipSlots.SetCurSel(Index);
}


void CSrRacePageBasic::OnBnClickedEditEquipslot()
{
	 CString	Buffer;
	 int		Index;
	 bool		Result;

	 Index = m_EquipSlots.GetCurSel();
	 if (Index < 0) return;

	 m_EquipSlots.GetText(Index, Buffer);

	 Result = m_pDlgHandler->SelectRecord(Buffer, SR_NAME_EQUP, &CSrEqupRecord::s_FieldMap);
	 if (!Result) return;
	 
	 m_EquipSlots.DeleteString(Index);
	 if (!Buffer.IsEmpty()) Index = m_EquipSlots.AddString(Buffer);
	 m_EquipSlots.SetCurSel(Index);
}


void CSrRacePageBasic::OnBnClickedDelEquipslot()
{
	 int ListIndex;

	 ListIndex = m_EquipSlots.GetCurSel();
	 if (ListIndex < 0) return;

	 m_EquipSlots.DeleteString(ListIndex);

	 if (ListIndex > 0)
		m_EquipSlots.SetCurSel(ListIndex - 1);
	else
		m_EquipSlots.SetCurSel(0);
}


void CSrRacePageBasic::OnBnClickedEditUnequipslot()
{
	m_pDlgHandler->EditRecordHelper(&m_UnequipSlot, SR_NAME_EQUP);
}


void CSrRacePageBasic::OnBnClickedSelectUnequipslot()
{
	m_pDlgHandler->SelectRecordHelper(&m_UnequipSlot, SR_NAME_EQUP, &CSrEqupRecord::s_FieldMap);
}


void CSrRacePageBasic::OnDropUnequipSlot (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_UnequipSlot, SR_NAME_EQUP, 1);
}


void CSrRacePageBasic::OnLbnDblclkEquipslots()
{
	OnBnClickedEditEquipslot();	
}
