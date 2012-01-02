/*===========================================================================
 *
 * File:		SrActiView.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	1 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "sractiview.h"
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

  IMPLEMENT_DYNCREATE(CSrActiView, CSrRecordDialog);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrActiView Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrActiView, CSrRecordDialog)
	ON_BN_CLICKED(IDC_SELECT_DESTROYMODEL, &CSrActiView::OnBnClickedSelectDestroymodel)
	ON_BN_CLICKED(IDC_EDIT_KEYWORD, &CSrActiView::OnBnClickedEditKeyword)
	ON_BN_CLICKED(IDC_SELECT_KEYWORD, &CSrActiView::OnBnClickedSelectKeyword)
	ON_BN_CLICKED(IDC_EDIT_AMBIENTSOUND, &CSrActiView::OnBnClickedEditAmbientsound)
	ON_BN_CLICKED(IDC_SELECT_AMBIENTSOUND, &CSrActiView::OnBnClickedSelectAmbientsound)
	ON_BN_CLICKED(IDC_EDIT_USESOUND, &CSrActiView::OnBnClickedEditUsesound)
	ON_BN_CLICKED(IDC_SELECTUSESOUND_BUTTON, &CSrActiView::OnBnClickedSelectusesoundButton)
	ON_BN_CLICKED(IDC_EDIT_WATER, &CSrActiView::OnBnClickedEditWater)
	ON_BN_CLICKED(IDC_SELECT_WATER, &CSrActiView::OnBnClickedSelectWater)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_AMBIENTSOUND, OnDropAmbientSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_AMBIENTSOUND, OnDropAmbientSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_USESOUND, OnDropUseSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_USESOUND, OnDropUseSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_WATER, OnDropWater)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_WATER, OnDropWater)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_KEYWORD, OnDropKeyword)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_KEYWORD, OnDropKeyword)
	ON_NOTIFY(ID_SRRESOURCE_CHECKDROP, IDC_DESTROYMODEL, OnDropDestroyModel)
	ON_NOTIFY(ID_SRRESOURCE_DROP, IDC_DESTROYMODEL, OnDropDestroyModel)
	ON_COMMAND(IDC_SELECT_DESTROYMODEL, OnSelectDestroyModel)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CSrActiView Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrActiView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,			IDC_EDITORID,			128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,				IDC_FORMID,				128,	IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,			IDC_ITEMNAME,			128,	IDS_TT_FULLNAME)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORD,			IDC_KEYWORD,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,				IDC_MODEL,				128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_USESOUND,			IDC_USESOUND,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_AMBIENTSOUND,		IDC_AMBIENTSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_DESTROYMODEL,		IDC_DESTROYMODEL,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_WATER,				IDC_WATER,				128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_KEYWORD,			IDC_KEYWORD,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN1,			IDC_UNKNOWN1,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN2,			IDC_UNKNOWN2,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN3,			IDC_UNKNOWN3,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_UNKNOWN4,			IDC_UNKNOWN4,			8,		0)
	ADD_SRRECUIFIELDS( SR_FIELD_VERB,				IDC_VERB,				64,		0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrActiView Constructor
 *
 *=========================================================================*/
CSrActiView::CSrActiView() : CSrRecordDialog(CSrActiView::IDD) 
{
}
/*===========================================================================
 *		End of Class CSrActiView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrActiView Destructor
 *
 *=========================================================================*/
CSrActiView::~CSrActiView() 
{
}
/*===========================================================================
 *		End of Class CSrActiView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrActiView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrActiView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ITEMNAME, m_ItemName);
	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_VERB, m_Verb);
	DDX_Control(pDX, IDC_UNKNOWN1, m_Unknown1);
	DDX_Control(pDX, IDC_UNKNOWN2, m_Unknown2);
	DDX_Control(pDX, IDC_UNKNOWN3, m_Unknown3);
	DDX_Control(pDX, IDC_UNKNOWN4, m_Unknown4);
	DDX_Control(pDX, IDC_KEYWORD, m_Keyword);
	DDX_Control(pDX, IDC_AMBIENTSOUND, m_AmbientSound);
	DDX_Control(pDX, IDC_USESOUND, m_UseSound);
	DDX_Control(pDX, IDC_WATER, m_Water);
	DDX_Control(pDX, IDC_DESTROYMODEL, m_DestroyModel);
}
/*===========================================================================
 *		End of Class Method CSrActiView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrActiView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrActiView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrActiView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrActiView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrActiView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrActiView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();
  
	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrActiView::OnInitialUpdate()
 *=========================================================================*/


void CSrActiView::OnBnClickedSelectDestroymodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_DestroyModel);
}


void CSrActiView::OnBnClickedEditKeyword()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Keyword, SR_NAME_KYWD);
}


void CSrActiView::OnBnClickedSelectKeyword()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Keyword, SR_NAME_KYWD, &CSrKywdRecord::s_FieldMap);
}


void CSrActiView::OnBnClickedEditAmbientsound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_AmbientSound, SR_NAME_SNDR);
}


void CSrActiView::OnBnClickedSelectAmbientsound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_AmbientSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrActiView::OnBnClickedEditUsesound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_UseSound, SR_NAME_SNDR);
}


void CSrActiView::OnBnClickedSelectusesoundButton()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_UseSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrActiView::OnBnClickedEditWater()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_Water, SR_NAME_WATR);
}


void CSrActiView::OnBnClickedSelectWater()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_Water, SR_NAME_WATR, &CSrWatrRecord::s_FieldMap);
}


void CSrActiView::OnDropAmbientSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_AmbientSound, SR_NAME_SNDR, 1);
}


void CSrActiView::OnDropUseSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_UseSound, SR_NAME_SNDR, 1);
}


void CSrActiView::OnDropWater (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Water, SR_NAME_WATR, 1);
}


void CSrActiView::OnDropKeyword (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = DropRecordHelper(pDropItems, &m_Keyword, SR_NAME_KYWD, 1);
}


void CSrActiView::OnDropDestroyModel (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	 srresourcedropinfo_t* pDropInfo = (srresourcedropinfo_t *) pNotifyStruct;

	*pResult = SRRESOURCE_DROPCHECK_ERROR;

	if (pDropInfo->pResourceFile == NULL) return;
	if (pDropInfo->pResourceFile->GetResourceType() != SR_RESOURCETYPE_NIF) return;
	if (!pDropInfo->pResourceFile->IsInPath(SRRESOURCE_PATH_MESHES)) return;

	if (pDropInfo->Notify.code == ID_SRRESOURCE_DROP) 
	{
		m_DestroyModel.SetWindowText(pDropInfo->pResourceFile->GetCSName());    
	}

	*pResult = SRRESOURCE_DROPCHECK_OK;
}


void CSrActiView::OnSelectDestroyModel (void) 
{
  CString Buffer;
  m_DestroyModel.GetWindowText(Buffer);
  m_pDlgHandler->SelectModel(Buffer);
}