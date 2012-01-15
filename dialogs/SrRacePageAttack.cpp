
#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageAttack.h"
#include "afxdialogex.h"
#include <vector>

IMPLEMENT_DYNAMIC(CSrRacePageAttack, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageAttack, CPropertyPage)
	ON_BN_CLICKED(IDC_EDIT_ATTACKKEYWORD, &CSrRacePageAttack::OnBnClickedEditAttackkeyword)
	ON_BN_CLICKED(IDC_SELECT_ATTACKKEYWORD, &CSrRacePageAttack::OnBnClickedSelectAttackkeyword)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ATTACKLIST, &CSrRacePageAttack::OnLvnItemchangedAttacklist)
	ON_BN_CLICKED(IDC_ADD_ATTACK, &CSrRacePageAttack::OnBnClickedAddAttack)
	ON_BN_CLICKED(IDC_DELETE_ATTACK, &CSrRacePageAttack::OnBnClickedDeleteAttack)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ATTACKKEYWORD, OnDropKeyword)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ATTACKKEYWORD, OnDropKeyword)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ATTACKLIST, OnDropAttackList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ATTACKLIST, OnDropAttackList)
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_RaceAttackListInit[] = {
	{ SR_FIELD_LISTUNKNOWN1,		120,	LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN2,		70,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN3,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN4,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN5,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN6,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN7,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN8,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN9,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN10,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN11,		40,		LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN12,		40,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_RaceAttackListFields[] = {
	{ "Event",			SR_FIELD_LISTUNKNOWN1,			0, NULL },
	{ "Keyword",		SR_FIELD_LISTUNKNOWN2,			0, NULL },
	{ "U1",				SR_FIELD_LISTUNKNOWN3,			0, NULL },
	{ "U2",				SR_FIELD_LISTUNKNOWN4,			0, NULL },
	{ "U3",				SR_FIELD_LISTUNKNOWN5,			0, NULL },
	{ "U4",				SR_FIELD_LISTUNKNOWN6,			0, NULL },
	{ "U5",				SR_FIELD_LISTUNKNOWN7,			0, NULL },
	{ "U6",				SR_FIELD_LISTUNKNOWN8,			0, NULL },
	{ "U7",				SR_FIELD_LISTUNKNOWN9,			0, NULL },
	{ "U8",				SR_FIELD_LISTUNKNOWN10,			0, NULL },
	{ "U9",				SR_FIELD_LISTUNKNOWN11,			0, NULL },
	{ "U10",			SR_FIELD_LISTUNKNOWN12,			0, NULL },	
	{ NULL,				SR_FIELD_NONE,					0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


CSrRacePageAttack::CSrRacePageAttack(srraceinfo_t& RaceInfo)
	: CPropertyPage(CSrRacePageAttack::IDD), m_RaceInfo(RaceInfo)
{
	m_pDlgHandler = NULL;
	m_pParent     = NULL;
	m_pCurrentAttack = NULL;
	m_IsInitialized = false;
}


CSrRacePageAttack::~CSrRacePageAttack()
{
}


void CSrRacePageAttack::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ATTACKLIST, m_AttackList);
	DDX_Control(pDX, IDC_ATTACKKEYWORD, m_AttackKeyword);
	DDX_Control(pDX, IDC_UNKNOWN1, m_AttackUnknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_AttackUnknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_AttackUnknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_AttackUnknown4);
	DDX_Control(pDX, IDC_UNKNOWN5, m_AttackUnknown5);
	DDX_Control(pDX, IDC_UNKNOWN6, m_AttackUnknown6);
	DDX_Control(pDX, IDC_UNKNOWN7, m_AttackUnknown7);
	DDX_Control(pDX, IDC_UNKNOWN8, m_AttackUnknown8);
	DDX_Control(pDX, IDC_UNKNOWN9, m_AttackUnknown9);
	DDX_Control(pDX, IDC_UNKNOWN10, m_AttackUnknown10);
	DDX_Control(pDX, IDC_EDIT_ATTACKKEYWORD, m_EditKeyword);
	DDX_Control(pDX, IDC_SELECT_ATTACKKEYWORD, m_SelectKeyword);
	DDX_Control(pDX, IDC_ATTACKEVENT, m_AttackEvent);
	DDX_Control(pDX, IDC_DELETE_ATTACK, m_DeleteAttack);
}


void CSrRacePageAttack::GetControlData (void)
{
	GetAttackControlData();
}


void CSrRacePageAttack::SetControlData (void)
{

	for (dword i = 0; i < m_RaceInfo.Attacks.GetSize(); ++i)
	{
		AddAttack(m_RaceInfo.Attacks[i]);
	}

}


void CSrRacePageAttack::SetCurrentAttack (srraceattackinfo_t* pAttack)
{
	GetAttackControlData();

	m_pCurrentAttack = pAttack;
	EnableAttackControls();

	SetAttackControlData();
}


void CSrRacePageAttack::GetAttackControlData()
{
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pCurrentAttack == NULL) return;

	m_AttackEvent.GetWindowText(Buffer);
	m_pCurrentAttack->Event.SetString(Buffer);

	m_AttackKeyword.GetWindowTextA(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Keyword = pRecord ? pRecord->GetFormID() : 0;

	m_AttackUnknown1.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown1 = (float) atof(Buffer);

	m_AttackUnknown2.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown2 = (float) atof(Buffer);

	m_AttackUnknown3.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown3 = (float) atof(Buffer);

	m_AttackUnknown4.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown4 = strtoul(Buffer, NULL, 0);

	m_AttackUnknown5.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown5 = (float) atof(Buffer);

	m_AttackUnknown6.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown6 = (float) atof(Buffer);

	m_AttackUnknown7.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown7 = (float) atof(Buffer);

	m_AttackUnknown8.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown8 = (float) atof(Buffer);

	m_AttackUnknown9.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown9 = (float) atof(Buffer);

	m_AttackUnknown10.GetWindowTextA(Buffer);
	m_pCurrentAttack->Data.GetAttackData().Unknown10 = (float) atof(Buffer);

	for (int i = 0; i < m_AttackList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_AttackList.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != &m_pCurrentAttack->Event) continue;

		UpdateAttackList(i, true);
		break;
	}
}


void CSrRacePageAttack::SetAttackControlData()
{
	CString Buffer;

	if (m_pCurrentAttack == NULL)
	{
		m_AttackKeyword.SetWindowText("");
		m_AttackEvent.SetWindowText("");
		m_AttackUnknown1.SetWindowText("");
		m_AttackUnknown2.SetWindowText("");
		m_AttackUnknown3.SetWindowText("");
		m_AttackUnknown4.SetWindowText("");
		m_AttackUnknown5.SetWindowText("");
		m_AttackUnknown6.SetWindowText("");
		m_AttackUnknown7.SetWindowText("");
		m_AttackUnknown8.SetWindowText("");
		m_AttackUnknown9.SetWindowText("");
		m_AttackUnknown10.SetWindowText("");
		return;
	}

	m_AttackEvent.SetWindowText(m_pCurrentAttack->Event.GetString().c_str());
	m_AttackKeyword.SetWindowText(m_pParent->m_pRecordHandler->GetEditorID(m_pCurrentAttack->Data.GetAttackData().Keyword));
	
	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown1);
	m_AttackUnknown1.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown2);
	m_AttackUnknown2.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown3);
	m_AttackUnknown3.SetWindowText(Buffer);

	Buffer.Format("%d", m_pCurrentAttack->Data.GetAttackData().Unknown4);
	m_AttackUnknown4.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown5);
	m_AttackUnknown5.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown6);
	m_AttackUnknown6.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown7);
	m_AttackUnknown7.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown8);
	m_AttackUnknown8.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown9);
	m_AttackUnknown9.SetWindowText(Buffer);

	Buffer.Format("%g", m_pCurrentAttack->Data.GetAttackData().Unknown10);
	m_AttackUnknown10.SetWindowText(Buffer);
}


void CSrRacePageAttack::EnableAttackControls (void)
{
	bool Enable = m_pCurrentAttack != NULL;

	m_AttackKeyword.EnableWindow(Enable);
	m_EditKeyword.EnableWindow(Enable);
	m_SelectKeyword.EnableWindow(Enable);
	m_AttackUnknown1.EnableWindow(Enable);
	m_AttackUnknown2.EnableWindow(Enable);
	m_AttackUnknown3.EnableWindow(Enable);
	m_AttackUnknown4.EnableWindow(Enable);
	m_AttackUnknown5.EnableWindow(Enable);
	m_AttackUnknown6.EnableWindow(Enable);
	m_AttackUnknown7.EnableWindow(Enable);
	m_AttackUnknown8.EnableWindow(Enable);
	m_AttackUnknown9.EnableWindow(Enable);
	m_AttackUnknown10.EnableWindow(Enable);
	m_AttackEvent.EnableWindow(Enable);
	m_DeleteAttack.EnableWindow(Enable);
}


void CSrRacePageAttack::SetAttackCustomData(srrlcustomdata_t& CustomData, srraceattackinfo_t* pAttack)
{
	CustomData.Subrecords.Destroy();
	CustomData.pRecord = m_pParent->GetInputRecord();
	CustomData.Subrecords.Add(&pAttack->Event);
	CustomData.Subrecords.Add(&pAttack->Data);
}


int CSrRacePageAttack::AddAttack (srraceattackinfo_t* pAttack)
{
	srrlcustomdata_t  CustomData;
	CString           Buffer;
	int		          ListIndex;

	SetAttackCustomData(CustomData, pAttack);	
  
	ListIndex = m_AttackList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return -1;

	UpdateAttackList(ListIndex, false);
	return ListIndex;
}


void CSrRacePageAttack::UpdateAttackList(const int ListIndex, const bool Update)
{
	srrlcustomdata_t*   pCustomData = m_AttackList.GetCustomData(ListIndex);
	CSrAtkdSubrecord*	pAttackData; 
	CSrStringSubrecord* pAttackEvent;
	CString				Buffer;

	if (Update) m_AttackList.UpdateRecord(ListIndex);
	if (pCustomData == NULL) return;

	pAttackEvent = SrCastClassNull(CSrStringSubrecord, pCustomData->Subrecords[0]);
	pAttackData  = SrCastClassNull(CSrAtkdSubrecord,   pCustomData->Subrecords[1]);

	if (pAttackEvent != NULL)
	{
		m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN1, pAttackEvent->GetString().c_str());
	}

	if (pAttackData == NULL) return;

	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN2, m_pParent->m_pRecordHandler->GetEditorID(pAttackData->GetAttackData().Keyword));

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown1);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN3, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown2);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN4, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown3);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN5, Buffer);

	Buffer.Format("%d", pAttackData->GetAttackData().Unknown4);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN6, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown5);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN7, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown6);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN8, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown7);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN9, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown8);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN10, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown9);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN11, Buffer);

	Buffer.Format("%g", pAttackData->GetAttackData().Unknown10);
	m_AttackList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN12, Buffer);	
}


void CSrRacePageAttack::OnBnClickedEditAttackkeyword()
{	
	m_pDlgHandler->EditRecordHelper(&m_AttackKeyword, SR_NAME_KYWD);
}


void CSrRacePageAttack::OnBnClickedSelectAttackkeyword()
{
	m_pDlgHandler->SelectRecordHelper(&m_AttackKeyword, SR_NAME_KYWD, &CSrKywdRecord::s_FieldMap);
}


BOOL CSrRacePageAttack::OnInitDialog()
{
	m_IsInitialized = false;

	CPropertyPage::OnInitDialog();

	m_AttackList.SetListName("RaceAttackList");
	m_AttackList.SetDragEnable(true);
	m_AttackList.DefaultSettings();
	m_AttackList.SetupCustomList(s_RaceAttackListInit, NULL, s_RaceAttackListFields);
	m_AttackList.SetOwner(this);
	m_AttackList.SetColorEnable(false);
	m_AttackList.SetDragType(SR_RLDRAG_CUSTOM);
	m_AttackList.SetSortEnable(false);
	//m_AttackList.SetActivateType(SR_RLACTIVATE_NONE);

	m_IsInitialized = true;
	EnableAttackControls();
		
	return TRUE;	
}


void CSrRacePageAttack::OnLvnItemchangedAttacklist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetAttackControlData();
	SetCurrentAttack(m_RaceInfo.Attacks[pNMLV->iItem]);
	SetAttackControlData();
}


void CSrRacePageAttack::OnBnClickedAddAttack()
{
	GetAttackControlData();

	srraceattackinfo_t* pAttack = m_RaceInfo.Attacks.AddNew();
	pAttack->InitializeNew();

	AddAttack(pAttack);
	SetCurrentAttack(pAttack);
}


void CSrRacePageAttack::OnBnClickedDeleteAttack()
{
	std::vector<int> IndexList;
	POSITION		 Pos;
	int				 ListIndex;

	GetAttackControlData();

	Pos = m_AttackList.GetFirstSelectedItemPosition();

	while (Pos)
	{
		ListIndex = m_AttackList.GetNextSelectedItem(Pos);
		IndexList.push_back(ListIndex);
	}

	if (IndexList.size() <= 0) return;

	while (IndexList.size())
	{
		ListIndex = IndexList.back();

		m_AttackList.DeleteItem(ListIndex);
		m_RaceInfo.Attacks.Delete(ListIndex);

		IndexList.pop_back();
	}

	m_pCurrentAttack = NULL;

	if (ListIndex < (int) m_RaceInfo.Attacks.GetSize())
	{
		SetCurrentAttack(m_RaceInfo.Attacks[ListIndex]);
		m_AttackList.SelectRecord(ListIndex);
	}
	else
	{
		SetCurrentAttack(m_RaceInfo.Attacks[ListIndex - 1]);
		m_AttackList.SelectRecord(ListIndex - 1);
	}
}


void CSrRacePageAttack::OnDropKeyword (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	CSrRecord*	       pRecord;
	CSrIdRecord*       pIdRecord;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pRecords == NULL) return;
	
	pRecord = pDropItems->pRecords->GetAt(0);
	if (pRecord == NULL) return;

			/* Ignore any invalid record types */
	if (pRecord->GetRecordType() != SR_NAME_KYWD) return;
	pIdRecord = SrCastClass(CSrIdRecord, pRecord);
	if (pIdRecord == NULL) return;

			/* If we're just checking or not */
	if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
	{
		m_AttackKeyword.SetWindowText(pIdRecord->GetEditorID());
	}
	
	*pResult = SRRL_DROPCHECK_OK;
}


void CSrRacePageAttack::OnDropAttackList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	srrlcustomdata_t*  pCustomData;

	*pResult = SRRL_DROPCHECK_ERROR;

	if (pDropItems == NULL) return;
	if (pDropItems->pCustomDatas == NULL) return;
	
	for (dword i = 0; i < pDropItems->pCustomDatas->GetSize(); ++i)
	{
		pCustomData = pDropItems->pCustomDatas->GetAt(i);
		if (pCustomData == NULL) continue;

		CSrStringSubrecord* pEvent = SrCastClassNull(CSrStringSubrecord, pCustomData->Subrecords[0]);
		CSrAtkdSubrecord*    pData = SrCastClassNull(CSrAtkdSubrecord,   pCustomData->Subrecords[1]);
		if (pEvent == NULL || pData == NULL) return;

			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			srraceattackinfo_t* pAttack = m_RaceInfo.Attacks.AddNew();
			pAttack->Event.CopyFull(pEvent);
			pAttack->Data.CopyFull(pData);
			AddAttack(pAttack);
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;
}