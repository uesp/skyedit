/*===========================================================================
 *
 * File:		SrArmaView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srarmaview.h"
#include "dialogs/sreditdlghandler.h"
#include "srbodypartslistdlg.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrArmaView, CSrRecordDialog);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrArmaView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrArmaView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_BODYPARTS, &CSrArmaView::OnBnClickedBodyparts)
	ON_BN_CLICKED(IDC_EDIT_RACE, &CSrArmaView::OnBnClickedEditRace)
	ON_BN_CLICKED(IDC_SELECT_RACE, &CSrArmaView::OnBnClickedSelectRace)
	ON_BN_CLICKED(IDC_ADD_RACELIST, &CSrArmaView::OnBnClickedAddraceList)
	ON_BN_CLICKED(IDC_EDIT_RACELIST, &CSrArmaView::OnBnClickedEditraceList)
	ON_BN_CLICKED(IDC_DEL_RACELIST, &CSrArmaView::OnBnClickedDelraceList)
	ON_BN_CLICKED(IDC_EDIT_MALETEXTURE, &CSrArmaView::OnBnClickedEditMaletexture)
	ON_BN_CLICKED(IDC_SELECT_MALETEXTURE, &CSrArmaView::OnBnClickedSelectMaletexture)
	ON_BN_CLICKED(IDC_EDIT_FEMALETEXTURE, &CSrArmaView::OnBnClickedEditFemaletexture)
	ON_BN_CLICKED(IDC_SELECT_FEMALETEXTURE, &CSrArmaView::OnBnClickedSelectFemaletexture)
	ON_BN_CLICKED(IDC_EDIT_MALE1STTEXTURE, &CSrArmaView::OnBnClickedEditMale1sttexture)
	ON_BN_CLICKED(IDC_SELECT_MALE1STTEXTURE, &CSrArmaView::OnBnClickedSelectMale1sttexture)
	ON_BN_CLICKED(IDC_EDIT_FEMALE1STTEXTURE, &CSrArmaView::OnBnClickedEditFemale1sttexture)
	ON_BN_CLICKED(IDC_SELECT_FEMALE1STTEXTURE, &CSrArmaView::OnBnClickedSelectFemale1sttexture)
	ON_BN_CLICKED(IDC_EDIT_FOOTSTEPS, &CSrArmaView::OnBnClickedEditFootsteps)
	ON_BN_CLICKED(IDC_SELECT_FOOTSTEPS, &CSrArmaView::OnBnClickedSelectFootsteps)
	ON_BN_CLICKED(IDC_SELECT_MALEMODEL, &CSrArmaView::OnBnClickedSelectMalemodel)
	ON_BN_CLICKED(IDC_SELECT_FEMALEMODEL, &CSrArmaView::OnBnClickedSelectFemalemodel)
	ON_BN_CLICKED(IDC_SELECT_MALE1STMODEL, &CSrArmaView::OnBnClickedSelectMale1stmodel)
	ON_BN_CLICKED(IDC_SELECT_FEMALE1STMODEL, &CSrArmaView::OnBnClickedSelectFemale1stmodel)

	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FOOTSTEPS, OnDropFootsteps)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FOOTSTEPS, OnDropFootsteps)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RACE, OnDropRace)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RACE, OnDropRace)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RACE_LIST, OnDropRaceList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RACE_LIST, OnDropRaceList)

	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MALETEXTURE, OnDropMaleTexture)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MALETEXTURE, OnDropMaleTexture)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FEMALETEXTURE, OnDropFemaleTexture)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FEMALETEXTURE, OnDropFemaleTexture)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MALE1STTEXTURE, OnDropMale1stTexture)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MALE1STTEXTURE, OnDropMale1stTexture)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FEMALE1STTEXTURE, OnDropFemale1stTexture)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FEMALE1STTEXTURE, OnDropFemale1stTexture)

	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MALEMODEL, OnDropMaleModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MALEMODEL, OnDropMaleModel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FEMALEMODEL, OnDropFemaleModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FEMALEMODEL, OnDropFemaleModel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MALE1STMODEL, OnDropMale1stModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MALE1STMODEL, OnDropMale1stModel)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_FEMALE1STMODEL, OnDropFemale1stModel)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_FEMALE1STMODEL, OnDropFemale1stModel)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrArmaView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrArmaView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_BODYPARTS,			IDC_BODYPARTS,			256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_FOOTSTEPS,			IDC_FOOTSTEPS,			200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,			IDC_UNKNOWN1,			16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,			IDC_UNKNOWN2,			16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,			IDC_UNKNOWN3,			16,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_RACE,				IDC_RACE,				200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MALEMODEL,			IDC_MALEMODEL,			256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MALE1STMODEL,		IDC_MALE1STMODEL,		256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_FEMALEMODEL,		IDC_FEMALEMODEL,		256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_FEMALE1STMODEL,		IDC_FEMALE1STMODEL,		256,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MALETEXTURE,		IDC_MALETEXTURE,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_FEMALETEXTURE,		IDC_FEMALETEXTURE,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MALE1STTEXTURE,		IDC_MALE1STTEXTURE,		200,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_FEMALE1STTEXTURE,	IDC_FEMALE1STTEXTURE,	200,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrArmaView Constructor
 *
 *=========================================================================*/
CSrArmaView::CSrArmaView() : CSrRecordDialog(CSrArmaView::IDD) 
{
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrArmaView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrArmaView Destructor
 *
 *=========================================================================*/
CSrArmaView::~CSrArmaView() 
{
}
/*===========================================================================
 *		End of Class CSrArmaView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrArmaView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrArmaView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_BODYPARTS, m_BodyParts);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_RACE, m_Race);
	DDX_Control(pDX, IDC_RACE_LIST, m_RaceList);
	DDX_Control(pDX, IDC_MALETEXTURE, m_MaleTexture);
	DDX_Control(pDX, IDC_FEMALETEXTURE, m_FemaleTexture);
	DDX_Control(pDX, IDC_MALE1STTEXTURE, m_Male1stTexture);
	DDX_Control(pDX, IDC_FEMALE1STTEXTURE, m_Female1stTexture);
	DDX_Control(pDX, IDC_FOOTSTEPS, m_Footsteps);
	DDX_Control(pDX, IDC_MALEMODEL, m_MaleModel);
	DDX_Control(pDX, IDC_FEMALEMODEL, m_FemaleModel);
	DDX_Control(pDX, IDC_MALE1STMODEL, m_Male1stModel);
	DDX_Control(pDX, IDC_FEMALE1STMODEL, m_Female1stModel);
}
/*===========================================================================
 *		End of Class Method CSrArmaView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrArmaView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrArmaView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrArmaView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrArmaView Diagnostics
 *=========================================================================*/


void CSrArmaView::GetControlData (void) 
{
	CString			Buffer;
	CSrRecord*		pRecord = GetOutputRecord();
	CSrArmaRecord*	pArma = SrCastClassNull(CSrArmaRecord, pRecord);
	CSrSubrecord*   pNewSubrecord;

	CSrRecordDialog::GetControlData();

	if (pArma != NULL)
	{
		m_BodyParts.GetWindowText(Buffer);
		pArma->SetBodyParts(Buffer);
	}

	if (!m_pDlgHandler) return;
	GetOutputRecord()->DeleteSubrecords(SR_NAME_MODL);

	for (int i = 0; i < m_RaceList.GetCount(); ++i)
	{
		m_RaceList.GetText(i, Buffer);
		
		pRecord = m_pDlgHandler->GetDocument()->GetRecordHandler().FindEditorID(Buffer);
		if (pRecord == NULL) continue;

		pNewSubrecord = GetOutputRecord()->AddNewSubrecord(SR_NAME_MODL);
		CSrFormidSubrecord* pNewModl = SrCastClassNull(CSrFormidSubrecord, pNewSubrecord);

		if (pNewModl)
		{
			pNewModl->InitializeNew();
			pNewModl->SetValue(pRecord->GetFormID());
		}
	}
	
}


/*===========================================================================
 *
 * Class CSrArmaView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrArmaView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();


	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrArmaView::OnInitialUpdate()
 *=========================================================================*/


void CSrArmaView::SetControlData (void) 
{
	CSrRecordDialog::SetControlData();
	FillRaceList();
}


void CSrArmaView::FillRaceList (void)
{
	CSrArmaRecord*       pArma;
	CSrSubrecord*        pRace;
	CSrFormidSubrecord*  pFormid;
	int			         Position;

	if (m_pDlgHandler == NULL) return;

	m_RaceList.ResetContent();

	pArma = SrCastClassNull(CSrArmaRecord, GetInputRecord());
	if (pArma == NULL) return;

	pRace = pArma->FindFirstSubrecord(SR_NAME_MODL, Position);

	while (pRace)
	{
		pFormid = SrCastClass(CSrFormidSubrecord, pRace);

		if (pFormid != NULL)
		{
			m_RaceList.AddString(m_pDlgHandler->GetDocument()->GetRecordHandler().GetEditorID(pFormid->GetValue()));
		}
		
		pRace = pArma->FindNextSubrecord(SR_NAME_MODL, Position);
	}

}


void CSrArmaView::OnBnClickedBodyparts()
{
	CString Buffer;
	dword   PartsValue;

	m_BodyParts.GetWindowText(Buffer);
	GetSrBodyPartFlagValue(PartsValue, Buffer);

	if (!SrEditBodyPartsDlg(PartsValue)) return;

	m_BodyParts.SetWindowText(GetSrBodyPartFlagString(PartsValue));
}


void CSrArmaView::OnBnClickedEditRace()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Race, SR_NAME_RACE);
}


void CSrArmaView::OnBnClickedSelectRace()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Race, SR_NAME_RACE, &CSrRaceRecord::s_FieldMap);
}


void CSrArmaView::OnBnClickedAddraceList()
{
	CString Race;

	if (!m_pDlgHandler) return;
	
	if (!m_pDlgHandler->SelectRecord(Race, SR_NAME_RACE, &CSrRaceRecord::s_FieldMap)) return;
	if (!Race.IsEmpty()) m_RaceList.AddString(Race);
}


void CSrArmaView::OnBnClickedEditraceList()
{
	CString Buffer;
	int ListIndex = m_RaceList.GetCurSel();

	if (ListIndex < 0) return;

	m_RaceList.GetText(ListIndex, Buffer);
	if (!m_pDlgHandler->SelectRecord(Buffer, SR_NAME_RACE, &CSrRaceRecord::s_FieldMap)) return;

	m_RaceList.DeleteString(ListIndex);
	m_RaceList.InsertString(ListIndex, Buffer);
	m_RaceList.SetCurSel(ListIndex);
}


void CSrArmaView::OnBnClickedDelraceList()
{
	int ListIndex = m_RaceList.GetCurSel();
	if (ListIndex < 0) return;

	m_RaceList.DeleteString(ListIndex);
	m_RaceList.SetCurSel(ListIndex - 1);
}


void CSrArmaView::OnBnClickedEditMaletexture()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_MaleTexture, SR_NAME_TXST);
}


void CSrArmaView::OnBnClickedSelectMaletexture()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_MaleTexture, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap);
}


void CSrArmaView::OnBnClickedEditFemaletexture()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_FemaleTexture, SR_NAME_TXST);
}


void CSrArmaView::OnBnClickedSelectFemaletexture()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_FemaleTexture, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap);
}


void CSrArmaView::OnBnClickedEditMale1sttexture()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Male1stTexture, SR_NAME_TXST);
}


void CSrArmaView::OnBnClickedSelectMale1sttexture()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Male1stTexture, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap);
}


void CSrArmaView::OnBnClickedEditFemale1sttexture()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Female1stTexture, SR_NAME_TXST);
}


void CSrArmaView::OnBnClickedSelectFemale1sttexture()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Female1stTexture, SR_NAME_TXST, &CSrTxstRecord::s_FieldMap);
}


void CSrArmaView::OnBnClickedEditFootsteps()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Footsteps, SR_NAME_FSTS);
}


void CSrArmaView::OnBnClickedSelectFootsteps()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Footsteps, SR_NAME_FSTS, &CSrFstsRecord::s_FieldMap);
}


void CSrArmaView::OnBnClickedSelectMalemodel()
{
	CString Buffer;
	m_MaleModel.GetWindowText(Buffer);
	m_pDlgHandler->SelectModel(Buffer);
}


void CSrArmaView::OnBnClickedSelectFemalemodel()
{
	CString Buffer;
	m_FemaleModel.GetWindowText(Buffer);
	m_pDlgHandler->SelectModel(Buffer);
}


void CSrArmaView::OnBnClickedSelectMale1stmodel()
{
	CString Buffer;
	m_Male1stModel.GetWindowText(Buffer);
	m_pDlgHandler->SelectModel(Buffer);
}


void CSrArmaView::OnBnClickedSelectFemale1stmodel()
{
	CString Buffer;
	m_Female1stModel.GetWindowText(Buffer);
	m_pDlgHandler->SelectModel(Buffer);
}


void CSrArmaView::OnDropFootsteps (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Footsteps, SR_NAME_FSTS, 1);
}


void CSrArmaView::OnDropRace (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Race, SR_NAME_RACE, 1);
}


void CSrArmaView::OnDropRaceList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, m_RaceList, SR_NAME_RACE, false);
}


void CSrArmaView::OnDropMaleTexture (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_MaleTexture, SR_NAME_TXST, 1);
}


void CSrArmaView::OnDropFemaleTexture (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_FemaleTexture, SR_NAME_TXST, 1);
}


void CSrArmaView::OnDropMale1stTexture (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Male1stTexture, SR_NAME_TXST, 1);
}


void CSrArmaView::OnDropFemale1stTexture (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Female1stTexture, SR_NAME_TXST, 1);
}


void CSrArmaView::OnDropMaleModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	 srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

	*pResult = SRRESOURCE_DROPCHECK_ERROR;

	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_MaleModel.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}

	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrArmaView::OnDropMale1stModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	 srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

	*pResult = SRRESOURCE_DROPCHECK_ERROR;

	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_Male1stModel.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}

	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrArmaView::OnDropFemaleModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	 srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

	*pResult = SRRESOURCE_DROPCHECK_ERROR;

	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_FemaleModel.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}

	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrArmaView::OnDropFemale1stModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	 srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

	*pResult = SRRESOURCE_DROPCHECK_ERROR;

	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_Female1stModel.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}

	*pResult = SRRESOURCE_DROPCHECK_OK;
}