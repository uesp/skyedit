
#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageMove.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CSrRacePageMove, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageMove, CPropertyPage)
	ON_BN_CLICKED(IDC_EDIT_WALKMOVE, &CSrRacePageMove::OnBnClickedEditWalkmove)
	ON_BN_CLICKED(IDC_SELECT_WALKMOVE, &CSrRacePageMove::OnBnClickedSelectWalkmove)
	ON_BN_CLICKED(IDC_EDIT_RUNMOVE, &CSrRacePageMove::OnBnClickedEditRunmove)
	ON_BN_CLICKED(IDC_SELECT_RUNMOVE, &CSrRacePageMove::OnBnClickedSelectRunmove)
	ON_BN_CLICKED(IDC_EDIT_SWIMMOVE, &CSrRacePageMove::OnBnClickedEditSwimmove)
	ON_BN_CLICKED(IDC_SELECT_SWIMMOVE, &CSrRacePageMove::OnBnClickedSelectSwimmove)
	ON_BN_CLICKED(IDC_EDIT_FLYMOVE, &CSrRacePageMove::OnBnClickedEditFlymove)
	ON_BN_CLICKED(IDC_SELECT_FLYMOVE, &CSrRacePageMove::OnBnClickedSelectFlymove)
	ON_BN_CLICKED(IDC_EDIT_SNEAKMOVE, &CSrRacePageMove::OnBnClickedEditSneakmove)
	ON_BN_CLICKED(IDC_SELECT_SNEAKMOVE, &CSrRacePageMove::OnBnClickedSelectSneakmove)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_WALKMOVE, OnDropWalkMove)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_WALKMOVE, OnDropWalkMove)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RUNMOVE, OnDropRunMove)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RUNMOVE, OnDropRunMove)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SWIMMOVE, OnDropSwimMove)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SWIMMOVE, OnDropSwimMove)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FLYMOVE, OnDropFlyMove)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FLYMOVE, OnDropFlyMove)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_SNEAKMOVE, OnDropSneakMove)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_SNEAKMOVE, OnDropSneakMove)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MOVETYPE, OnDropMoveType)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MOVETYPE, OnDropMoveType)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MOVETYPELIST, OnDropMoveTypeList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MOVETYPELIST, OnDropMoveTypeList)
	ON_BN_CLICKED(IDC_EDIT_MOVETYPE, &CSrRacePageMove::OnBnClickedEditMovetype)
	ON_BN_CLICKED(IDC_SELECT_MOVETYPE, &CSrRacePageMove::OnBnClickedSelectMovetype)
	ON_BN_CLICKED(IDC_ADD_MOVETYPE, &CSrRacePageMove::OnBnClickedAddMovetype)
	ON_BN_CLICKED(IDC_DELETE_MOVETYPE, &CSrRacePageMove::OnBnClickedDeleteMovetype)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MOVETYPELIST, &CSrRacePageMove::OnLvnItemchangedMovetypelist)
END_MESSAGE_MAP()


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_RaceMoveTypeListInit[] = {
	{ SR_FIELD_LISTUNKNOWN1,		120,	LVCFMT_CENTER },
	{ SR_FIELD_LISTUNKNOWN2,		40,		LVCFMT_CENTER },
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

static srrecfield_t s_RaceMoveTypeListFields[] = {
	{ "MoveType",		SR_FIELD_LISTUNKNOWN1,			0, NULL },
	{ "U1",				SR_FIELD_LISTUNKNOWN2,			0, NULL },
	{ "U2",				SR_FIELD_LISTUNKNOWN3,			0, NULL },
	{ "U3",				SR_FIELD_LISTUNKNOWN4,			0, NULL },
	{ "U4",				SR_FIELD_LISTUNKNOWN5,			0, NULL },
	{ "U5",				SR_FIELD_LISTUNKNOWN6,			0, NULL },
	{ "U6",				SR_FIELD_LISTUNKNOWN7,			0, NULL },
	{ "U7",				SR_FIELD_LISTUNKNOWN8,			0, NULL },
	{ "U8",				SR_FIELD_LISTUNKNOWN9,			0, NULL },
	{ "U9",				SR_FIELD_LISTUNKNOWN10,			0, NULL },
	{ "U10",			SR_FIELD_LISTUNKNOWN11,			0, NULL },
	{ "U11",			SR_FIELD_LISTUNKNOWN12,			0, NULL },	
	{ NULL,				SR_FIELD_NONE,					0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


CSrRacePageMove::CSrRacePageMove(srraceinfo_t& RaceInfo)
	: CPropertyPage(CSrRacePageMove::IDD), m_RaceInfo(RaceInfo)
{
	m_pDlgHandler = NULL;
	m_pParent     = NULL;
	m_pCurrentMoveType = NULL;
	m_IsInitialized = false;

}


CSrRacePageMove::~CSrRacePageMove()
{
}


void CSrRacePageMove::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOVENAMES, m_MoveNames);
	DDX_Control(pDX, IDC_WALKMOVE, m_WalkMove);
	DDX_Control(pDX, IDC_RUNMOVE, m_RunMove);
	DDX_Control(pDX, IDC_SWIMMOVE, m_SwimMove);
	DDX_Control(pDX, IDC_FLYMOVE, m_FlyMove);
	DDX_Control(pDX, IDC_SNEAKMOVE, m_SneakMove);
	DDX_Control(pDX, IDC_MOVETYPELIST, m_MoveTypeList);
	DDX_Control(pDX, IDC_MOVETYPE, m_MoveType);
	DDX_Control(pDX, IDC_SELECT_MOVETYPE, m_SelectMoveType);
	DDX_Control(pDX, IDC_EDIT_MOVETYPE, m_EditMoveType);
	DDX_Control(pDX, IDC_UNKNOWN1, m_MoveUnknown[0]);
	DDX_Control(pDX, IDC_UNKNOWN2, m_MoveUnknown[1]);
	DDX_Control(pDX, IDC_UNKNOWN3, m_MoveUnknown[2]);
	DDX_Control(pDX, IDC_UNKNOWN4, m_MoveUnknown[3]);
	DDX_Control(pDX, IDC_UNKNOWN5, m_MoveUnknown[4]);
	DDX_Control(pDX, IDC_UNKNOWN6, m_MoveUnknown[5]);
	DDX_Control(pDX, IDC_UNKNOWN7, m_MoveUnknown[6]);
	DDX_Control(pDX, IDC_UNKNOWN8, m_MoveUnknown[7]);
	DDX_Control(pDX, IDC_UNKNOWN9, m_MoveUnknown[8]);
	DDX_Control(pDX, IDC_UNKNOWN10, m_MoveUnknown[9]);
	DDX_Control(pDX, IDC_UNKNOWN11, m_MoveUnknown[10]);
	DDX_Control(pDX, IDC_ADD_MOVETYPE, m_AddMoveType);
	DDX_Control(pDX, IDC_DELETE_MOVETYPE, m_DeleteMoveType);
}


BOOL CSrRacePageMove::OnInitDialog()
{
	m_IsInitialized = false;
	CPropertyPage::OnInitDialog();

	m_MoveTypeList.SetListName("RaceMoveTypeList");
	m_MoveTypeList.SetDragEnable(true);
	m_MoveTypeList.DefaultSettings();
	m_MoveTypeList.SetupCustomList(s_RaceMoveTypeListInit, NULL, s_RaceMoveTypeListFields);
	m_MoveTypeList.SetOwner(this);
	m_MoveTypeList.SetColorEnable(false);
	m_MoveTypeList.SetDragType(SR_RLDRAG_CUSTOM);
	m_MoveTypeList.SetSortEnable(false);
	//m_MoveTypeList.SetActivateType(SR_RLACTIVATE_NONE);

	m_IsInitialized = true;

	return TRUE;	
}


void CSrRacePageMove::SetCurrentMoveType (srracemoveinfo_t* pMoveType)
{
	GetMoveTypeControlData();

	m_pCurrentMoveType = pMoveType;
	EnableMoveControls();

	SetMoveTypeControlData();
}


void CSrRacePageMove::GetMoveTypeControlData (void)
{
	CString    Buffer;
	CSrRecord* pRecord;

	if (m_pCurrentMoveType == NULL) return;

	m_MoveType.GetWindowText(Buffer);
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);

	m_pCurrentMoveType->MoveType.SetValue(pRecord ? pRecord->GetFormID() : 0);

	for (dword i = 0; i < 11; ++i)
	{
		m_MoveUnknown[i].GetWindowText(Buffer);
		m_pCurrentMoveType->SpeedData.GetSpedData().Unknown[i] = (float) atof(Buffer);
	}

	for (int i = 0; i < m_MoveTypeList.GetItemCount(); ++i)
	{
		srrlcustomdata_t* pCustomData = m_MoveTypeList.GetCustomData(i);
		if (pCustomData == NULL) continue;
		if (pCustomData->Subrecords[0] != &m_pCurrentMoveType->MoveType) continue;

		UpdateMoveTypeList(i, true);
		break;
	}

}


void CSrRacePageMove::SetMoveTypeControlData (void)
{
	CString Buffer;

	if (m_pCurrentMoveType == NULL)
	{
		m_MoveType.SetWindowText("");
		for (dword i = 0; i < 11; ++i) m_MoveUnknown[i].SetWindowText("");
		return;
	}

	m_MoveType.SetWindowTextA(m_pParent->m_pRecordHandler->GetEditorID(m_pCurrentMoveType->MoveType.GetValue()));

	for (dword i = 0; i < 11; ++i) 
	{
		Buffer.Format("%g", m_pCurrentMoveType->SpeedData.GetSpedData().Unknown[i]);
		m_MoveUnknown[i].SetWindowText(Buffer);
	}

}


void CSrRacePageMove::SetMoveTypeList (void)
{
	m_MoveTypeList.DeleteAllItems();
	
	for (dword i = 0; i < m_RaceInfo.MovementTypes.GetSize(); ++i) 
	{
		AddMoveTypeList(m_RaceInfo.MovementTypes[i]);
	}

	m_MoveTypeList.SelectRecord(0);
	SetCurrentMoveType(m_RaceInfo.MovementTypes[0]);
}


void CSrRacePageMove::SetMoveTypeCustomData(srrlcustomdata_t& CustomData, srracemoveinfo_t* pMoveType)
{
	CustomData.Subrecords.Destroy();
	CustomData.pRecord = m_pParent->GetInputRecord();
	CustomData.Subrecords.Add(&pMoveType->MoveType);
	CustomData.Subrecords.Add(&pMoveType->SpeedData);
}


int CSrRacePageMove::AddMoveTypeList (srracemoveinfo_t* pMoveType)
{
	srrlcustomdata_t  CustomData;
	CString           Buffer;
	int		          ListIndex;

	SetMoveTypeCustomData(CustomData, pMoveType);	
  
	ListIndex = m_MoveTypeList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return (-1);

	UpdateMoveTypeList(ListIndex, false);
	return (ListIndex);
}


void CSrRacePageMove::UpdateMoveTypeList(const int ListIndex, const bool Update)
{
	srrlcustomdata_t*   pCustomData = m_MoveTypeList.GetCustomData(ListIndex);
	CSrFormidSubrecord* pFormid; 
	CSrSpedSubrecord*   pSped;
	CString				Buffer;

	if (Update) m_MoveTypeList.UpdateRecord(ListIndex);
	if (pCustomData == NULL) return;

	pFormid = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
	pSped   = SrCastClassNull(CSrSpedSubrecord, pCustomData->Subrecords[1]);

	if (pFormid != NULL)
	{
		m_MoveTypeList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN1, m_pParent->m_pRecordHandler->GetEditorID(pFormid->GetValue()));
	}

	if (pSped == NULL) return;

	for (dword i = 0; i < 11; ++i)
	{
		Buffer.Format("%g", pSped->GetSpedData().Unknown[i]);
		m_MoveTypeList.SetCustomField(ListIndex, SR_FIELD_LISTUNKNOWN2 + i, Buffer);
	}
}


void CSrRacePageMove::GetControlData (void)
{
	CString Buffer;
	CSrRecord* pRecord;

	GetMoveTypeControlData();

	m_WalkMove.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetWalkMove(pRecord ? pRecord->GetFormID() : 0);

	m_RunMove.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetRunMove(pRecord ? pRecord->GetFormID() : 0);

	m_SwimMove.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetSwimMove(pRecord ? pRecord->GetFormID() : 0);

	m_FlyMove.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetFlyMove(pRecord ? pRecord->GetFormID() : 0);

	m_SneakMove.GetWindowText(Buffer);
	Buffer.Trim(" \t\r\n");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetSneakMove(pRecord ? pRecord->GetFormID() : 0);

}


void CSrRacePageMove::SetControlData (void)
{
	CString Buffer;

	m_MoveNames.ResetContent();

	for (dword i = 0; i < m_RaceInfo.MovementNames.GetSize(); ++i)
	{
		dword Value = m_RaceInfo.MovementNames[i]->GetValue();
		Buffer.Format("%c%c%c%c", Value & 0xff, (Value >> 8) & 0xff, (Value >> 16) & 0xff, (Value >> 24) & 0xff);
		m_MoveNames.AddString(Buffer);
	}

	m_WalkMove.SetWindowText(m_RaceInfo.pWalkMove   ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pWalkMove->GetValue())  : "");
	m_RunMove.SetWindowText(m_RaceInfo.pRunMove     ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pRunMove->GetValue())   : "");
	m_SwimMove.SetWindowText(m_RaceInfo.pSwimMove   ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pSwimMove->GetValue())  : "");
	m_FlyMove.SetWindowText(m_RaceInfo.pFlyMove     ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pFlyMove->GetValue())   : "");
	m_SneakMove.SetWindowText(m_RaceInfo.pSneakMove ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pSneakMove->GetValue()) : "");

	SetMoveTypeList();
}


void CSrRacePageMove::OnBnClickedEditWalkmove()
{
	m_pDlgHandler->EditRecordHelper(&m_WalkMove, SR_NAME_MOVT);
}


void CSrRacePageMove::OnBnClickedSelectWalkmove()
{
	m_pDlgHandler->SelectRecordHelper(&m_WalkMove, SR_NAME_MOVT, &CSrMovtRecord::s_FieldMap);
}


void CSrRacePageMove::OnBnClickedEditRunmove()
{
	m_pDlgHandler->EditRecordHelper(&m_RunMove, SR_NAME_MOVT);
}


void CSrRacePageMove::OnBnClickedSelectRunmove()
{
	m_pDlgHandler->SelectRecordHelper(&m_RunMove, SR_NAME_MOVT, &CSrMovtRecord::s_FieldMap);
}


void CSrRacePageMove::OnBnClickedEditSwimmove()
{
	m_pDlgHandler->EditRecordHelper(&m_SwimMove, SR_NAME_MOVT);
}


void CSrRacePageMove::OnBnClickedSelectSwimmove()
{
	m_pDlgHandler->SelectRecordHelper(&m_SwimMove, SR_NAME_MOVT, &CSrMovtRecord::s_FieldMap);
}


void CSrRacePageMove::OnBnClickedEditFlymove()
{
	m_pDlgHandler->EditRecordHelper(&m_FlyMove, SR_NAME_MOVT);
}


void CSrRacePageMove::OnBnClickedSelectFlymove()
{
	m_pDlgHandler->SelectRecordHelper(&m_FlyMove, SR_NAME_MOVT, &CSrMovtRecord::s_FieldMap);
}


void CSrRacePageMove::OnBnClickedEditSneakmove()
{
	m_pDlgHandler->EditRecordHelper(&m_SneakMove, SR_NAME_MOVT);
}


void CSrRacePageMove::OnBnClickedSelectSneakmove()
{
	m_pDlgHandler->SelectRecordHelper(&m_SneakMove, SR_NAME_MOVT, &CSrMovtRecord::s_FieldMap);
}


void CSrRacePageMove::OnDropWalkMove (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_WalkMove, SR_NAME_MOVT, 1);
}


void CSrRacePageMove::OnDropRunMove (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_RunMove, SR_NAME_MOVT, 1);
}


void CSrRacePageMove::OnDropSwimMove (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_SwimMove, SR_NAME_MOVT, 1);
}


void CSrRacePageMove::OnDropFlyMove (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_FlyMove, SR_NAME_MOVT, 1);
}


void CSrRacePageMove::OnDropSneakMove (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_SneakMove, SR_NAME_MOVT, 1);
}


void CSrRacePageMove::OnDropMoveType (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	if (m_pCurrentMoveType == NULL) return;

	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_MoveType, SR_NAME_MOVT, 1);
}


void CSrRacePageMove::OnDropMoveTypeList (NMHDR* pNotifyStruct, LRESULT* pResult) 
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

		CSrFormidSubrecord* pMtyp = SrCastClassNull(CSrFormidSubrecord, pCustomData->Subrecords[0]);
		CSrSpedSubrecord*   pSped = SrCastClassNull(CSrSpedSubrecord, pCustomData->Subrecords[1]);
		if (pMtyp == NULL || pSped == NULL) return;
				
			/* If we're just checking or not */
		if (pDropItems->Notify.code == ID_SRRECORDLIST_DROP) 
		{
			srracemoveinfo_t* pMoveType = m_RaceInfo.MovementTypes.AddNew();			
			pMoveType->MoveType.CopyFull(pMtyp);
			pMoveType->SpeedData.CopyFull(pSped);

			AddMoveTypeList(pMoveType);
		}
	}
	
	*pResult = SRRL_DROPCHECK_OK;	
}


void CSrRacePageMove::EnableMoveControls (void)
{
	bool Enable = (m_pCurrentMoveType != NULL);

	m_MoveType.EnableWindow(Enable);
	m_EditMoveType.EnableWindow(Enable);
	m_SelectMoveType.EnableWindow(Enable);
	m_DeleteMoveType.EnableWindow(Enable);

	for (dword i = 0; i < 11; ++i)
	{
		m_MoveUnknown[i].EnableWindow(Enable);
	}
}


void CSrRacePageMove::OnBnClickedEditMovetype()
{
	if (m_pCurrentMoveType == NULL) return;
	m_pDlgHandler->EditRecordHelper(&m_MoveType, SR_NAME_MOVT);
}


void CSrRacePageMove::OnBnClickedSelectMovetype()
{
	if (m_pCurrentMoveType == NULL) return;
	m_pDlgHandler->SelectRecordHelper(&m_MoveType, SR_NAME_MOVT, &CSrMovtRecord::s_FieldMap);
}


void CSrRacePageMove::OnBnClickedAddMovetype()
{
	GetMoveTypeControlData();

	srracemoveinfo_t* pNewMoveType = m_RaceInfo.MovementTypes.AddNew();
	pNewMoveType->InitializeNew();

	int ListIndex = AddMoveTypeList(pNewMoveType);
	m_MoveTypeList.SelectRecord(ListIndex);
	SetCurrentMoveType(pNewMoveType);
}


void CSrRacePageMove::OnBnClickedDeleteMovetype()
{
	if (m_pCurrentMoveType == NULL) return;
	int ListIndex = m_MoveTypeList.GetSelectedItem();
	if (ListIndex < 0) return;
	
	m_MoveTypeList.DeleteItem(ListIndex);
	m_RaceInfo.MovementTypes.Delete(m_pCurrentMoveType);
	m_pCurrentMoveType = NULL;

	if (ListIndex > 0)
	{
		SetCurrentMoveType(m_RaceInfo.MovementTypes[ListIndex - 1]);
		m_MoveTypeList.SelectRecord(ListIndex - 1);
	}
	else if ( m_RaceInfo.MovementTypes.GetSize() > 0)
	{
		SetCurrentMoveType(m_RaceInfo.MovementTypes[0]);
		m_MoveTypeList.SelectRecord(0);
	}
	else
	{
		m_MoveTypeList.SelectRecord(-1);
		SetCurrentMoveType(NULL);
	}
	
}


void CSrRacePageMove::OnLvnItemchangedMovetypelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (!m_IsInitialized) return;
	if ((pNMLV->uNewState & LVIS_SELECTED) == 0) return;

	GetMoveTypeControlData();
	SetCurrentMoveType(m_RaceInfo.MovementTypes[pNMLV->iItem]);
	SetMoveTypeControlData();
}
