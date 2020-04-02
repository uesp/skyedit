/*===========================================================================
 *
 * File:		SrLvlListInfo.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 January 2012
 *
 * Defines  the srlvllistinfo_t helper class used by the views of various
 * leveled lists.
 *
 *=========================================================================*/
#ifndef __SRLVLLISTINFO_H
#define __SRLVLLISTINFO_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "modfile/subrecords/srcntosubrecord.h"
	#include "modfile/subrecords/srlvlosubrecord.h"
	#include "modfile/subrecords/srcoedsubrecord.h"
	#include "modfile/records/srcontrecord.h"
	#include "modfile/records/srcobjrecord.h"
	#include "modfile/records/srlvlirecord.h"
	#include "modfile/records/srlvlnrecord.h"
	#include "modfile/records/srlvsprecord.h"
	#include "modfile/records/srnpc_record.h"
	#include "windows/srrecordlistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


struct srlvllistinfo_t
{
	CSrCntoSubrecord* pCnto;
	CSrLvloSubrecord* pLvlo;
	CSrCoedSubrecord* pCoed;

	srlvllistinfo_t()
	{
		pCnto = NULL;
		pLvlo = NULL;
		pCoed = NULL;
	}

	~srlvllistinfo_t()
	{
		delete pCnto;
		delete pLvlo;
		delete pCoed;
	}

	void Destroy()
	{
		delete pCnto;
		delete pLvlo;
		delete pCoed;
		pCnto = NULL;
		pLvlo = NULL;
		pCoed = NULL;
	}

	bool CopyFrom (CSrRefSubrecordArray Subrecords)
	{
		Destroy();

		CSrCntoSubrecord* pSrcCnto = SrCastClassNull(CSrCntoSubrecord, Subrecords[0]);
		CSrLvloSubrecord* pSrcLvlo = SrCastClassNull(CSrLvloSubrecord, Subrecords[0]);
		CSrCoedSubrecord* pSrcCoed = SrCastClassNull(CSrCoedSubrecord, Subrecords[1]);

		if (pSrcCnto != NULL)
		{
			pCnto = new CSrCntoSubrecord;
			pCnto->CopyFull(pSrcCnto);
		}
		else if (pSrcLvlo != NULL)
		{
			pLvlo = new CSrLvloSubrecord;
			pLvlo->CopyFull(pSrcLvlo);
		}
		else
		{
			return false;
		}

		if (pSrcCoed != NULL)
		{
			pCoed = new CSrCoedSubrecord;
			pCoed->CopyFull(pSrcCoed);
		}

		return true;
	}

	void InitializeNew (const srrectype_t Type)
	{
		Destroy();

		if (Type == SR_NAME_CONT || Type == SR_NAME_COBJ || Type == SR_NAME_NPC_)
		{
			pCnto = new CSrCntoSubrecord;
			pCnto->Initialize(SR_NAME_CNTO, 8);
			pCnto->InitializeNew();
		}
		else
		{
			pLvlo = new CSrLvloSubrecord;
			pLvlo->Initialize(SR_NAME_LVLO, SR_LVLO_SUBRECORD_SIZE);
			pLvlo->InitializeNew();
		}
	}

	srformid_t GetFormID (void)
	{
		if (pCnto != NULL) return pCnto->GetFormID();
		if (pLvlo != NULL) return pLvlo->GetFormID();
		return 0;
	}
	
	dword GetCount (void)
	{
		if (pCnto != NULL) return pCnto->GetCount();
		if (pLvlo != NULL) return pLvlo->GetCount();
		return 0;
	}

	dword GetLevel (void)
	{
		if (pLvlo != NULL) return pLvlo->GetLevel();
		return 0;
	}

	void SetFormID (const srformid_t FormID)
	{
		if (pCnto != NULL) pCnto->SetFormID(FormID);
		if (pLvlo != NULL) pLvlo->SetFormID(FormID);
	}

	void SetCount (const dword Count)
	{
		if (pCnto != NULL) pCnto->SetCount(Count);
		if (pLvlo != NULL) pLvlo->SetCount(Count);
	}

	void SetLevel (const dword Level)
	{
		if (pLvlo != NULL) pLvlo->SetLevel(Level);
	}
	
	void SetCoedData (const srformid_t FormID, const dword MinRank, const float Condition)
	{
		if (FormID == 0)
		{
			delete pCoed;
			pCoed = NULL;
			return;
		}

		if (pCoed == NULL)
		{
			pCoed = new CSrCoedSubrecord;
			pCoed->Initialize(SR_NAME_COED, SR_COED_SUBRECORD_SIZE);
			pCoed->InitializeNew();
		}

		pCoed->GetCoedData().FactionID = FormID;
		pCoed->GetCoedData().MinRank   = MinRank;
		pCoed->GetCoedData().Condition = Condition;
	}

};


typedef CSrPtrArray<srlvllistinfo_t> CSrLvlListInfoArray;


srlvllistinfo_t* SrFindLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrSubrecord* pSubrecord);

bool SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrRecord* pRecord);

void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrCobjRecord& Record);
void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrContRecord& Record);
void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvliRecord& Record);
void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvlnRecord& Record);
void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvspRecord& Record);
void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrNpc_Record& Record);


bool SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrRecord* pRecord);

void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrCobjRecord& Record);
void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrContRecord& Record);
void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvliRecord& Record);
void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvlnRecord& Record);
void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvspRecord& Record);
void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrNpc_Record& Record);

void SrCreateLvlListInfoCustomData (srrlcustomdata_t& CustomData, srlvllistinfo_t& Info, CSrRecordHandler* pHandler);

#endif
/*===========================================================================
 *		End of File SrLvlListInfo.H
 *=========================================================================*/
