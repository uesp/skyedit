

#include "stdafx.h"
#include "sredit.h"
#include "sreditdlghandler.h"
#include "dialogs\SrRacePageModel.h"
#include "afxdialogex.h"
#include "SrBodyPartsListDlg.h"


IMPLEMENT_DYNAMIC(CSrRacePageModel, CPropertyPage)


BEGIN_MESSAGE_MAP(CSrRacePageModel, CPropertyPage)
	ON_BN_CLICKED(IDC_SELECT_MALEMODEL, &CSrRacePageModel::OnBnClickedSelectMalemodel)
	ON_BN_CLICKED(IDC_SELECT_FEMALEMODEL, &CSrRacePageModel::OnBnClickedSelectFemalemodel)
	ON_BN_CLICKED(IDC_SELECT_MALEEGTMODEL, &CSrRacePageModel::OnBnClickedSelectMaleegtmodel)
	ON_BN_CLICKED(IDC_SELECT_MALEHAVOKMODEL, &CSrRacePageModel::OnBnClickedSelectMalehavokmodel)
	ON_BN_CLICKED(IDC_SELECT_FEMALEEGTMODEL, &CSrRacePageModel::OnBnClickedSelectFemaleegtmodel)
	ON_BN_CLICKED(IDC_SELECT_FEMALEHAVOKMODEL, &CSrRacePageModel::OnBnClickedSelectFemalehavokmodel)
	ON_BN_CLICKED(IDC_BODYDATA, &CSrRacePageModel::OnBnClickedBodydata)
	ON_BN_CLICKED(IDC_EDIT_DEFAULTVOICE, &CSrRacePageModel::OnBnClickedEditDefaultvoice)
	ON_BN_CLICKED(IDC_SELECT_DEFAULTVOICE, &CSrRacePageModel::OnBnClickedSelectDefaultvoice)
	ON_BN_CLICKED(IDC_EDIT_DEFAULTHAIRCOLOR, &CSrRacePageModel::OnBnClickedEditDefaulthaircolor)
	ON_BN_CLICKED(IDC_SELECT_DEFAULTHAIRCOLOR, &CSrRacePageModel::OnBnClickedSelectDefaulthaircolor)
	ON_BN_CLICKED(IDC_EDIT_DECAPITATEDHEAD, &CSrRacePageModel::OnBnClickedEditDecapitatedhead)
	ON_BN_CLICKED(IDC_SELECT_DECAPITATEDHEAD, &CSrRacePageModel::OnBnClickedSelectDecapitatedhead)
	ON_BN_CLICKED(IDC_EDIT_MATERIAL, &CSrRacePageModel::OnBnClickedEditMaterial)
	ON_BN_CLICKED(IDC_SELECT_MATERIAL, &CSrRacePageModel::OnBnClickedSelectMaterial)
	ON_BN_CLICKED(IDC_EDIT_IMPACTSET, &CSrRacePageModel::OnBnClickedEditImpactset)
	ON_BN_CLICKED(IDC_SELECT_IMPACTSET, &CSrRacePageModel::OnBnClickedSelectImpactset)
	ON_BN_CLICKED(IDC_EDIT_BLOODFX, &CSrRacePageModel::OnBnClickedEditBloodfx)
	ON_BN_CLICKED(IDC_SELECT_BLOODFX, &CSrRacePageModel::OnBnClickedSelectBloodfx)
	ON_BN_CLICKED(IDC_EDIT_OPENSOUND, &CSrRacePageModel::OnBnClickedEditOpensound)
	ON_BN_CLICKED(IDC_SELECT_OPENSOUND, &CSrRacePageModel::OnBnClickedSelectOpensound)
	ON_BN_CLICKED(IDC_EDIT_CLOSESOUND, &CSrRacePageModel::OnBnClickedEditClosesound)
	ON_BN_CLICKED(IDC_SELECT_CLOSESOUND, &CSrRacePageModel::OnBnClickedSelectClosesound)
	ON_BN_CLICKED(IDC_EDIT_NAME8, &CSrRacePageModel::OnBnClickedEditName8)
	ON_BN_CLICKED(IDC_SELECT_NAME8, &CSrRacePageModel::OnBnClickedSelectName8)
	ON_BN_CLICKED(IDC_EDIT_RNAME, &CSrRacePageModel::OnBnClickedEditRname)
	ON_BN_CLICKED(IDC_SELECT_RNAME, &CSrRacePageModel::OnBnClickedSelectRname)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DEFAULTVOICE, OnDropDefaultVoice)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DEFAULTVOICE, OnDropDefaultVoice)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DEFAULTVOICE2, OnDropDefaultVoice2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DEFAULTVOICE2, OnDropDefaultVoice2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DEFAULTHAIRCOLOR, OnDropDefaultHairColor)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DEFAULTHAIRCOLOR, OnDropDefaultHairColor)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DEFAULTHAIRCOLOR2, OnDropDefaultHairColor2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DEFAULTHAIRCOLOR2, OnDropDefaultHairColor2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DECAPITATEDHEAD, OnDropDecapitatedHead)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DECAPITATEDHEAD, OnDropDecapitatedHead)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_DECAPITATEDHEAD2, OnDropDecapitatedHead2)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_DECAPITATEDHEAD2, OnDropDecapitatedHead2)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_MATERIAL, OnDropMaterial)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_MATERIAL, OnDropMaterial)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_IMPACTSET, OnDropImpactSet)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_IMPACTSET, OnDropImpactSet)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_BLOODFX, OnDropBloodFX)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_BLOODFX, OnDropBloodFX)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_OPENSOUND, OnDropOpenSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_OPENSOUND, OnDropOpenSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_CLOSESOUND, OnDropCloseSound)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_CLOSESOUND, OnDropCloseSound)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_NAME8, OnDropName8)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_NAME8, OnDropName8)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_RNAME, OnDropRName)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_RNAME, OnDropRName)
	ON_BN_CLICKED(IDC_EDIT_DECAPITATEDHEAD2, &CSrRacePageModel::OnBnClickedEditDecapitatedhead2)
	ON_BN_CLICKED(IDC_SELECT_DECAPITATEDHEAD2, &CSrRacePageModel::OnBnClickedSelectDecapitatedhead2)
	ON_BN_CLICKED(IDC_EDIT_DEFAULTHAIRCOLOR2, &CSrRacePageModel::OnBnClickedEditDefaulthaircolor2)
	ON_BN_CLICKED(IDC_SELECT_DEFAULTHAIRCOLOR2, &CSrRacePageModel::OnBnClickedSelectDefaulthaircolor2)
	ON_BN_CLICKED(IDC_EDIT_DEFAULTVOICE2, &CSrRacePageModel::OnBnClickedEditDefaultvoice2)
	ON_BN_CLICKED(IDC_SELECT_DEFAULTVOICE2, &CSrRacePageModel::OnBnClickedSelectDefaultvoice2)
END_MESSAGE_MAP()


CSrRacePageModel::CSrRacePageModel(srraceinfo_t& RaceInfo)
	: CPropertyPage(), m_pDlgHandler(NULL), m_RaceInfo(RaceInfo)
{
	m_pParent     = NULL;
	m_pDlgHandler = NULL;
}

CSrRacePageModel::~CSrRacePageModel()
{
}


void CSrRacePageModel::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MALEHEIGHT, m_MaleHeight);
	DDX_Control(pDX, IDC_FEMALEHEIGHT, m_FemaleHeight);
	DDX_Control(pDX, IDC_MALEMODEL, m_MaleModel);
	DDX_Control(pDX, IDC_FEMALEMODEL, m_FemaleModel);
	DDX_Control(pDX, IDC_MALEEGTMODEL, m_MaleEgtModel);
	DDX_Control(pDX, IDC_MALEHAVOKMODEL, m_MaleHavokModel);
	DDX_Control(pDX, IDC_FEMALEEGTMODEL, m_FemaleEgtModel);
	DDX_Control(pDX, IDC_FEMALEHAVOKMODEL, m_FemaleHavokModel);
	DDX_Control(pDX, IDC_BODYDATA, m_BodyParts);
	DDX_Control(pDX, IDC_DEFAULTVOICE, m_DefaultVoice);
	DDX_Control(pDX, IDC_DEFAULTHAIRCOLOR, m_DefaultHairColor);
	DDX_Control(pDX, IDC_DECAPITATEDHEAD, m_DecapitatedHead);
	DDX_Control(pDX, IDC_MATERIAL, m_Material);
	DDX_Control(pDX, IDC_IMPACTSET, m_ImpactSet);
	DDX_Control(pDX, IDC_BLOODFX, m_BloodFX);
	DDX_Control(pDX, IDC_OPENSOUND, m_OpenSound);
	DDX_Control(pDX, IDC_CLOSESOUND, m_CloseSound);
	DDX_Control(pDX, IDC_NAME8, m_Name8);
	DDX_Control(pDX, IDC_RNAME, m_RName);
	DDX_Control(pDX, IDC_DEFAULTVOICE2, m_DefaultVoice2);
	DDX_Control(pDX, IDC_DEFAULTHAIRCOLOR2, m_DefaultHairColor2);
	DDX_Control(pDX, IDC_DECAPITATEDHEAD2, m_DecapitatedHead2);
}


void CSrRacePageModel::GetControlData (void)
{
	CString    Buffer;
	CString    Buffer1;
	CSrRecord* pRecord;

		/* Male skeletal model */
	m_MaleModel.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	m_RaceInfo.MaleModel.SetModel(Buffer);	

		/* Female skeletal model */
	m_FemaleModel.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	m_RaceInfo.FemaleModel.SetModel(Buffer);

		/* Male EGT model */
	m_MaleEgtModel.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	m_RaceInfo.MaleEgt.Model.SetString(Buffer);

		/* Female EGT model */
	m_FemaleEgtModel.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	m_RaceInfo.FemaleEgt.Model.SetString(Buffer);

		/* Male Havok model */
	m_MaleHavokModel.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	m_RaceInfo.MaleHavok.Model.SetString(Buffer);

		/* Female Havok model */
	m_FemaleHavokModel.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	m_RaceInfo.FemaleHavok.Model.SetString(Buffer);

		/* Default voices */
	m_RaceInfo.VoiceTypes.GetFormIDArray().Destroy();
	m_DefaultVoice.GetWindowText(Buffer);
	m_DefaultVoice2.GetWindowText(Buffer1);
	Buffer.Trim(" \r\n\t");
	Buffer1.Trim(" \r\n\t");

	if (!Buffer.IsEmpty() && !Buffer1.IsEmpty())
	{
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		m_RaceInfo.VoiceTypes.GetFormIDArray().Add(pRecord ? pRecord->GetFormID() : 0);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer1);
		m_RaceInfo.VoiceTypes.GetFormIDArray().Add(pRecord ? pRecord->GetFormID() : 0);
	}

		/* Default hair colors */
	m_RaceInfo.HairColors.GetFormIDArray().Destroy();
	m_DefaultHairColor.GetWindowText(Buffer);
	m_DefaultHairColor2.GetWindowText(Buffer1);
	Buffer.Trim(" \r\n\t");
	Buffer1.Trim(" \r\n\t");

	if (!Buffer.IsEmpty() && !Buffer1.IsEmpty())
	{
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		m_RaceInfo.HairColors.GetFormIDArray().Add(pRecord ? pRecord->GetFormID() : 0);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer1);
		m_RaceInfo.HairColors.GetFormIDArray().Add(pRecord ? pRecord->GetFormID() : 0);
	}

		/* Decapitated heads */
	m_RaceInfo.DecapitatedHeads.GetFormIDArray().Destroy();
	m_DecapitatedHead.GetWindowText(Buffer);
	m_DecapitatedHead2.GetWindowText(Buffer1);
	Buffer.Trim(" \r\n\t");
	Buffer1.Trim(" \r\n\t");

	if (!Buffer.IsEmpty() && !Buffer1.IsEmpty())
	{
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
		m_RaceInfo.DecapitatedHeads.GetFormIDArray().Add(pRecord ? pRecord->GetFormID() : 0);
		pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer1);
		m_RaceInfo.DecapitatedHeads.GetFormIDArray().Add(pRecord ? pRecord->GetFormID() : 0);
	}

	m_Material.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetMaterial(pRecord ? pRecord->GetFormID() : 0);

	m_ImpactSet.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetImpactSet(pRecord ? pRecord->GetFormID() : 0);

	m_BloodFX.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetBloodFX(pRecord ? pRecord->GetFormID() : 0);

	m_OpenSound.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetOpenSound(pRecord ? pRecord->GetFormID() : 0);

	m_CloseSound.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetCloseSound(pRecord ? pRecord->GetFormID() : 0);

	m_Name8.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetName8(pRecord ? pRecord->GetFormID() : 0);

	m_RName.GetWindowText(Buffer);
	Buffer.Trim(" \r\n\t");
	pRecord = m_pParent->m_pRecordHandler->FindEditorID(Buffer);
	m_RaceInfo.SetRName(pRecord ? pRecord->GetFormID() : 0);

}


void CSrRacePageModel::SetControlData (void)
{
	if (m_RaceInfo.MaleModel.pModel)
		m_MaleModel.SetWindowText(m_RaceInfo.MaleModel.pModel->GetString().c_str());
	else
		m_MaleModel.SetWindowText("");

	if (m_RaceInfo.FemaleModel.pModel)
		m_FemaleModel.SetWindowText(m_RaceInfo.FemaleModel.pModel->GetString().c_str());
	else
		m_FemaleModel.SetWindowText("");

	m_MaleEgtModel.SetWindowText(m_RaceInfo.MaleEgt.Model.GetString().c_str());
	m_FemaleEgtModel.SetWindowText(m_RaceInfo.FemaleEgt.Model.GetString().c_str());
	m_MaleHavokModel.SetWindowText(m_RaceInfo.MaleHavok.Model.GetString().c_str());
	m_FemaleHavokModel.SetWindowText(m_RaceInfo.FemaleHavok.Model.GetString().c_str());

	m_DefaultVoice.SetWindowText(m_RaceInfo.VoiceTypes.GetArraySize()  > 0 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.VoiceTypes.GetFormIDArray()[0]) : "");
	m_DefaultVoice2.SetWindowText(m_RaceInfo.VoiceTypes.GetArraySize() > 1 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.VoiceTypes.GetFormIDArray()[1]) : "");

	m_DefaultHairColor.SetWindowText(m_RaceInfo.HairColors.GetArraySize()  > 0 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.HairColors.GetFormIDArray()[0]) : "");
	m_DefaultHairColor2.SetWindowText(m_RaceInfo.HairColors.GetArraySize() > 1 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.HairColors.GetFormIDArray()[1]) : "");

	m_DecapitatedHead.SetWindowText(m_RaceInfo.DecapitatedHeads.GetArraySize()  > 0 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.DecapitatedHeads.GetFormIDArray()[0]) : "");
	m_DecapitatedHead2.SetWindowText(m_RaceInfo.DecapitatedHeads.GetArraySize() > 1 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.DecapitatedHeads.GetFormIDArray()[1]) : "");

	m_Material.SetWindowText(m_RaceInfo.pMaterial ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pMaterial->GetValue()) : "");
	m_ImpactSet.SetWindowText(m_RaceInfo.pImpactData ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pImpactData->GetValue()) : "");
	m_BloodFX.SetWindowText(m_RaceInfo.pBloodFX ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pBloodFX->GetValue()) : "");
	m_OpenSound.SetWindowText(m_RaceInfo.pOpenSound ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pOpenSound->GetValue()) : "");
	m_CloseSound.SetWindowText(m_RaceInfo.pCloseSound ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pCloseSound->GetValue()) : "");
	m_Name8.SetWindowText(m_RaceInfo.pNam8 ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pNam8->GetValue()) : "");
	m_RName.SetWindowText(m_RaceInfo.pRName ? m_pParent->m_pRecordHandler->GetEditorID(m_RaceInfo.pRName->GetValue()) : "");
}


void CSrRacePageModel::OnBnClickedSelectMalemodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_MaleModel);
}


void CSrRacePageModel::OnBnClickedSelectFemalemodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_FemaleModel);
}


void CSrRacePageModel::OnBnClickedSelectMaleegtmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_MaleEgtModel);
}


void CSrRacePageModel::OnBnClickedSelectMalehavokmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_FemaleEgtModel);
}


void CSrRacePageModel::OnBnClickedSelectFemaleegtmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_MaleHavokModel);
}


void CSrRacePageModel::OnBnClickedSelectFemalehavokmodel()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectModelHelper(&m_FemaleHavokModel);
}


void CSrRacePageModel::OnBnClickedBodydata()
{
	CString Buffer;
	dword BodyParts = 0;

	m_BodyParts.GetWindowText(Buffer);
	GetSrBodyPartFlagValue(BodyParts, Buffer);

	if (!SrEditBodyPartsDlg(BodyParts)) return;
	m_BodyParts.SetWindowText(GetSrBodyPartFlagString(BodyParts));
}


void CSrRacePageModel::OnBnClickedEditDefaultvoice()
{
	m_pDlgHandler->EditRecordHelper(&m_DefaultVoice, SR_NAME_VTYP);
}


void CSrRacePageModel::OnBnClickedSelectDefaultvoice()
{
	m_pDlgHandler->SelectRecordHelper(&m_DefaultVoice, SR_NAME_VTYP, &CSrVtypRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditDefaulthaircolor()
{
	m_pDlgHandler->EditRecordHelper(&m_DefaultHairColor, SR_NAME_CLFM);
}


void CSrRacePageModel::OnBnClickedSelectDefaulthaircolor()
{
	m_pDlgHandler->SelectRecordHelper(&m_DefaultHairColor, SR_NAME_CLFM, &CSrClfmRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditDecapitatedhead()
{
	m_pDlgHandler->EditRecordHelper(&m_DecapitatedHead, SR_NAME_ARMO);
}


void CSrRacePageModel::OnBnClickedSelectDecapitatedhead()
{
	m_pDlgHandler->SelectRecordHelper(&m_DecapitatedHead, SR_NAME_ARMO, &CSrArmoRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditMaterial()
{
	m_pDlgHandler->EditRecordHelper(&m_Material, SR_NAME_MATT);
}


void CSrRacePageModel::OnBnClickedSelectMaterial()
{
	m_pDlgHandler->SelectRecordHelper(&m_Material, SR_NAME_MATT, &CSrMattRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditImpactset()
{
	m_pDlgHandler->EditRecordHelper(&m_ImpactSet, SR_NAME_IPDS);
}


void CSrRacePageModel::OnBnClickedSelectImpactset()
{
	m_pDlgHandler->SelectRecordHelper(&m_ImpactSet, SR_NAME_IPDS, &CSrIpdsRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditBloodfx()
{
	m_pDlgHandler->EditRecordHelper(&m_BloodFX, SR_NAME_ARTO);
}


void CSrRacePageModel::OnBnClickedSelectBloodfx()
{
	m_pDlgHandler->SelectRecordHelper(&m_BloodFX, SR_NAME_ARTO, &CSrArtoRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditOpensound()
{
	m_pDlgHandler->EditRecordHelper(&m_OpenSound, SR_NAME_SNDR);
}


void CSrRacePageModel::OnBnClickedSelectOpensound()
{
	m_pDlgHandler->SelectRecordHelper(&m_OpenSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditClosesound()
{
	m_pDlgHandler->EditRecordHelper(&m_CloseSound, SR_NAME_SNDR);
}


void CSrRacePageModel::OnBnClickedSelectClosesound()
{
	m_pDlgHandler->SelectRecordHelper(&m_CloseSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditName8()
{
	m_pDlgHandler->EditRecordHelper(&m_Name8, SR_NAME_RACE);
}


void CSrRacePageModel::OnBnClickedSelectName8()
{
	m_pDlgHandler->SelectRecordHelper(&m_Name8, SR_NAME_RACE, &CSrRaceRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditRname()
{
	m_pDlgHandler->EditRecordHelper(&m_RName, SR_NAME_RACE);
}


void CSrRacePageModel::OnBnClickedSelectRname()
{
	m_pDlgHandler->SelectRecordHelper(&m_RName, SR_NAME_RACE, &CSrRaceRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditDecapitatedhead2()
{
	m_pDlgHandler->EditRecordHelper(&m_DecapitatedHead2, SR_NAME_ARMO);
}


void CSrRacePageModel::OnBnClickedSelectDecapitatedhead2()
{
	m_pDlgHandler->SelectRecordHelper(&m_DecapitatedHead2, SR_NAME_ARMO, &CSrArmoRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditDefaulthaircolor2()
{
	m_pDlgHandler->EditRecordHelper(&m_DefaultHairColor2, SR_NAME_CLFM);
}


void CSrRacePageModel::OnBnClickedSelectDefaulthaircolor2()
{
	m_pDlgHandler->SelectRecordHelper(&m_DefaultHairColor2, SR_NAME_CLFM, &CSrClfmRecord::s_FieldMap);
}


void CSrRacePageModel::OnBnClickedEditDefaultvoice2()
{
	m_pDlgHandler->EditRecordHelper(&m_DefaultVoice2, SR_NAME_VTYP);
}


void CSrRacePageModel::OnBnClickedSelectDefaultvoice2()
{
	m_pDlgHandler->SelectRecordHelper(&m_DefaultVoice2, SR_NAME_VTYP, &CSrVtypRecord::s_FieldMap);
}



void CSrRacePageModel::OnDropDefaultVoice (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DefaultVoice, SR_NAME_VTYP, 1);
}


void CSrRacePageModel::OnDropDefaultVoice2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DefaultVoice2, SR_NAME_VTYP, 1);
}


void CSrRacePageModel::OnDropDefaultHairColor (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DefaultHairColor, SR_NAME_CLFM, 1);
}


void CSrRacePageModel::OnDropDefaultHairColor2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DefaultHairColor2, SR_NAME_CLFM, 1);
}


void CSrRacePageModel::OnDropDecapitatedHead (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DecapitatedHead, SR_NAME_ARMO, 1);
}


void CSrRacePageModel::OnDropDecapitatedHead2 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_DecapitatedHead2, SR_NAME_ARMO, 1);
}


void CSrRacePageModel::OnDropMaterial (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_ImpactSet, SR_NAME_IPDS, 1);
}


void CSrRacePageModel::OnDropImpactSet (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_ImpactSet, SR_NAME_IPDS, 1);
}


void CSrRacePageModel::OnDropBloodFX (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_BloodFX, SR_NAME_ARTO, 1);
}


void CSrRacePageModel::OnDropOpenSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_OpenSound, SR_NAME_SNDR, 1);
}


void CSrRacePageModel::OnDropCloseSound (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_CloseSound, SR_NAME_SNDR, 1);
}


void CSrRacePageModel::OnDropName8 (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_Name8, SR_NAME_RACE, 1);
}


void CSrRacePageModel::OnDropRName (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;
	*pResult = m_pParent->DropRecordHelper(pDropItems, &m_RName, SR_NAME_RACE, 1);
}


