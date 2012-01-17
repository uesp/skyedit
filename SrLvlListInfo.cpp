/*===========================================================================
 *
 * File:		SrLvlListInfo.CPP
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 January 2012
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "SrLvlListInfo.h"



bool SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrRecord* pRecord)
{

	if (pRecord == NULL)
	{
		InfoArray.Destroy();
		return false;
	}

	if (pRecord->GetRecordType() == SR_NAME_COBJ)
	{
		CSrCobjRecord* pCobj = SrCastClass(CSrCobjRecord, pRecord);

		if (pCobj != NULL)
		{
			SrCreateLvlListInfo(InfoArray, *pCobj);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_CONT)
	{
		CSrContRecord* pCont = SrCastClass(CSrContRecord, pRecord);

		if (pCont != NULL)
		{
			SrCreateLvlListInfo(InfoArray, *pCont);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_LVLI)
	{
		CSrLvliRecord* pLvli = SrCastClass(CSrLvliRecord, pRecord);

		if (pLvli != NULL)
		{
			SrCreateLvlListInfo(InfoArray, *pLvli);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_LVLN)
	{
		CSrLvlnRecord* pLvln = SrCastClass(CSrLvlnRecord, pRecord);

		if (pLvln != NULL)
		{
			SrCreateLvlListInfo(InfoArray, *pLvln);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_LVSP)
	{
		CSrLvspRecord* pLvsp = SrCastClass(CSrLvspRecord, pRecord);

		if (pLvsp != NULL)
		{
			SrCreateLvlListInfo(InfoArray, *pLvsp);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_NPC_)
	{
		CSrNpc_Record* pNpc = SrCastClass(CSrNpc_Record, pRecord);

		if (pNpc != NULL)
		{
			SrCreateLvlListInfo(InfoArray, *pNpc);
			return true;
		}
	}

	InfoArray.Destroy();
	return false;
}


void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrCobjRecord& Record)
{
	CSrSubrecord*	  pSubrecord;
	CSrCntoSubrecord* pCnto;
	CSrCoedSubrecord* pCoed;
	srlvllistinfo_t*  pNewInfo;
	int			      Position;

	InfoArray.Destroy();
	pSubrecord = Record.FindFirstSubrecord(SR_NAME_CNTO, Position);

	while (pSubrecord != NULL)
	{
		pCnto = SrCastClass(CSrCntoSubrecord, pSubrecord);

		if (pCnto != NULL)
		{
			pNewInfo = InfoArray.AddNew();
			pNewInfo->pCnto = new CSrCntoSubrecord;
			pNewInfo->pCnto->CopyFull(pCnto);
			
			pSubrecord = Record.GetSubrecord(Position + 1);
			pCoed = SrCastClassNull(CSrCoedSubrecord, pSubrecord);

			if (pCoed != NULL)
			{
				pNewInfo->pCoed = new CSrCoedSubrecord;
				pNewInfo->pCoed->CopyFull(pCoed);
			}
		}

		pSubrecord = Record.FindNextSubrecord(SR_NAME_CNTO, Position);
	}

}


void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrContRecord& Record)
{
	CSrSubrecord*	  pSubrecord;
	CSrCntoSubrecord* pCnto;
	CSrCoedSubrecord* pCoed;
	srlvllistinfo_t*  pNewInfo;
	int			      Position;

	InfoArray.Destroy();
	pSubrecord = Record.FindFirstSubrecord(SR_NAME_CNTO, Position);

	while (pSubrecord != NULL)
	{
		pCnto = SrCastClass(CSrCntoSubrecord, pSubrecord);

		if (pCnto != NULL)
		{
			pNewInfo = InfoArray.AddNew();
			pNewInfo->pCnto = new CSrCntoSubrecord;
			pNewInfo->pCnto->CopyFull(pCnto);
			
			pSubrecord = Record.GetSubrecord(Position + 1);
			pCoed = SrCastClassNull(CSrCoedSubrecord, pSubrecord);

			if (pCoed != NULL)
			{
				pNewInfo->pCoed = new CSrCoedSubrecord;
				pNewInfo->pCoed->CopyFull(pCoed);
			}
		}

		pSubrecord = Record.FindNextSubrecord(SR_NAME_CNTO, Position);
	}
}


void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvliRecord& Record)
{
	CSrSubrecord*	  pSubrecord;
	CSrLvloSubrecord* pLvlo;
	CSrCoedSubrecord* pCoed;
	srlvllistinfo_t*  pNewInfo;
	int			      Position;

	InfoArray.Destroy();
	pSubrecord = Record.FindFirstSubrecord(SR_NAME_LVLO, Position);

	while (pSubrecord != NULL)
	{
		pLvlo = SrCastClass(CSrLvloSubrecord, pSubrecord);

		if (pLvlo != NULL)
		{
			pNewInfo = InfoArray.AddNew();
			pNewInfo->pLvlo = new CSrLvloSubrecord;
			pNewInfo->pLvlo->CopyFull(pLvlo);
			
			pSubrecord = Record.GetSubrecord(Position + 1);
			pCoed = SrCastClassNull(CSrCoedSubrecord, pSubrecord);

			if (pCoed != NULL)
			{
				pNewInfo->pCoed = new CSrCoedSubrecord;
				pNewInfo->pCoed->CopyFull(pCoed);
			}
		}

		pSubrecord = Record.FindNextSubrecord(SR_NAME_LVLO, Position);
	}
}


void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvlnRecord& Record)
{
	CSrSubrecord*	  pSubrecord;
	CSrLvloSubrecord* pLvlo;
	CSrCoedSubrecord* pCoed;
	srlvllistinfo_t*  pNewInfo;
	int			      Position;

	InfoArray.Destroy();
	pSubrecord = Record.FindFirstSubrecord(SR_NAME_LVLO, Position);

	while (pSubrecord != NULL)
	{
		pLvlo = SrCastClass(CSrLvloSubrecord, pSubrecord);

		if (pLvlo != NULL)
		{
			pNewInfo = InfoArray.AddNew();
			pNewInfo->pLvlo = new CSrLvloSubrecord;
			pNewInfo->pLvlo->CopyFull(pLvlo);
			
			pSubrecord = Record.GetSubrecord(Position + 1);
			pCoed = SrCastClassNull(CSrCoedSubrecord, pSubrecord);

			if (pCoed != NULL)
			{
				pNewInfo->pCoed = new CSrCoedSubrecord;
				pNewInfo->pCoed->CopyFull(pCoed);
			}
		}

		pSubrecord = Record.FindNextSubrecord(SR_NAME_LVLO, Position);
	}
}


void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvspRecord& Record)
{
	CSrSubrecord*	  pSubrecord;
	CSrLvloSubrecord* pLvlo;
	CSrCoedSubrecord* pCoed;
	srlvllistinfo_t*  pNewInfo;
	int			      Position;

	InfoArray.Destroy();
	pSubrecord = Record.FindFirstSubrecord(SR_NAME_LVLO, Position);

	while (pSubrecord != NULL)
	{
		pLvlo = SrCastClass(CSrLvloSubrecord, pSubrecord);

		if (pLvlo != NULL)
		{
			pNewInfo = InfoArray.AddNew();
			pNewInfo->pLvlo = new CSrLvloSubrecord;
			pNewInfo->pLvlo->CopyFull(pLvlo);
			
			pSubrecord = Record.GetSubrecord(Position + 1);
			pCoed = SrCastClassNull(CSrCoedSubrecord, pSubrecord);

			if (pCoed != NULL)
			{
				pNewInfo->pCoed = new CSrCoedSubrecord;
				pNewInfo->pCoed->CopyFull(pCoed);
			}
		}

		pSubrecord = Record.FindNextSubrecord(SR_NAME_LVLO, Position);
	}
}


void SrCreateLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrNpc_Record& Record)
{
	throw "NotImplemented: SrCreateLvlListInfo(InfoArray, NpcRecord)!";
}


bool SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrRecord* pRecord)
{
	if (pRecord == NULL) InfoArray.Destroy();

	if (pRecord->GetRecordType() == SR_NAME_COBJ)
	{
		CSrCobjRecord* pCobj = SrCastClass(CSrCobjRecord, pRecord);

		if (pCobj != NULL)
		{
			SrSaveLvlListInfo(InfoArray, *pCobj);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_CONT)
	{
		CSrContRecord* pCont = SrCastClass(CSrContRecord, pRecord);

		if (pCont != NULL)
		{
			SrSaveLvlListInfo(InfoArray, *pCont);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_LVLI)
	{
		CSrLvliRecord* pLvli = SrCastClass(CSrLvliRecord, pRecord);

		if (pLvli != NULL)
		{
			SrSaveLvlListInfo(InfoArray, *pLvli);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_LVLN)
	{
		CSrLvlnRecord* pLvln = SrCastClass(CSrLvlnRecord, pRecord);

		if (pLvln != NULL)
		{
			SrSaveLvlListInfo(InfoArray, *pLvln);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_LVSP)
	{
		CSrLvspRecord* pLvsp = SrCastClass(CSrLvspRecord, pRecord);

		if (pLvsp != NULL)
		{
			SrSaveLvlListInfo(InfoArray, *pLvsp);
			return true;
		}
	}
	else if (pRecord->GetRecordType() == SR_NAME_NPC_)
	{
		CSrNpc_Record* pNpc = SrCastClass(CSrNpc_Record, pRecord);

		if (pNpc != NULL)
		{
			SrSaveLvlListInfo(InfoArray, *pNpc);
			return true;
		}
	}

	return false;
}


void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrCobjRecord& Record)
{
	CSrSubrecord* pSubrecord;

	Record.DeleteSubrecords(SR_NAME_COCT);
	Record.DeleteSubrecords(SR_NAME_CNTO);
	Record.DeleteSubrecords(SR_NAME_COED);

	Record.AddInitNewSubrecord(SR_NAME_COCT);

	for (dword i = 0; i < InfoArray.GetSize(); ++i)
	{
		srlvllistinfo_t& Info = *InfoArray[i];
		if (Info.pCnto == NULL) continue;

		pSubrecord = Record.AddInitNewSubrecord(SR_NAME_CNTO);
		pSubrecord->Copy(Info.pCnto);

		if (Info.pCoed != NULL)
		{
			pSubrecord = Record.AddInitNewSubrecord(SR_NAME_COED);
			pSubrecord->Copy(Info.pCoed);
		}
	}

	Record.UpdateComponentCount();
}


void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrContRecord& Record)
{
	CSrSubrecord* pSubrecord;

	Record.DeleteSubrecords(SR_NAME_COCT);
	Record.DeleteSubrecords(SR_NAME_CNTO);
	Record.DeleteSubrecords(SR_NAME_COED);

	Record.AddInitNewSubrecord(SR_NAME_COCT);

	for (dword i = 0; i < InfoArray.GetSize(); ++i)
	{
		srlvllistinfo_t& Info = *InfoArray[i];
		if (Info.pCnto == NULL) continue;

		pSubrecord = Record.AddInitNewSubrecord(SR_NAME_CNTO);
		pSubrecord->Copy(Info.pCnto);

		if (Info.pCoed != NULL)
		{
			pSubrecord = Record.AddInitNewSubrecord(SR_NAME_COED);
			pSubrecord->Copy(Info.pCoed);
		}
	}

	Record.UpdateItemCount();
}


void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvliRecord& Record)
{
	CSrSubrecord* pSubrecord;

	Record.DeleteSubrecords(SR_NAME_LLCT);
	Record.DeleteSubrecords(SR_NAME_LVLO);
	Record.DeleteSubrecords(SR_NAME_COED);

	Record.AddInitNewSubrecord(SR_NAME_LLCT);

	for (dword i = 0; i < InfoArray.GetSize(); ++i)
	{
		srlvllistinfo_t& Info = *InfoArray[i];
		if (Info.pLvlo == NULL) continue;

		pSubrecord = Record.AddInitNewSubrecord(SR_NAME_LVLO);
		pSubrecord->Copy(Info.pLvlo);

		if (Info.pCoed != NULL)
		{
			pSubrecord = Record.AddInitNewSubrecord(SR_NAME_COED);
			pSubrecord->Copy(Info.pCoed);
		}
	}

	Record.UpdateListCount();
}


void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvlnRecord& Record)
{
	CSrSubrecord* pSubrecord;

	Record.DeleteSubrecords(SR_NAME_LLCT);
	Record.DeleteSubrecords(SR_NAME_LVLO);
	Record.DeleteSubrecords(SR_NAME_COED);

	Record.AddInitNewSubrecord(SR_NAME_LLCT);

	for (dword i = 0; i < InfoArray.GetSize(); ++i)
	{
		srlvllistinfo_t& Info = *InfoArray[i];
		if (Info.pLvlo == NULL) continue;

		pSubrecord = Record.AddInitNewSubrecord(SR_NAME_LVLO);
		pSubrecord->Copy(Info.pLvlo);

		if (Info.pCoed != NULL)
		{
			pSubrecord = Record.AddInitNewSubrecord(SR_NAME_COED);
			pSubrecord->Copy(Info.pCoed);
		}
	}

	Record.UpdateListCount();
}


void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrLvspRecord& Record)
{
	CSrSubrecord* pSubrecord;

	Record.DeleteSubrecords(SR_NAME_LLCT);
	Record.DeleteSubrecords(SR_NAME_LVLO);
	Record.DeleteSubrecords(SR_NAME_COED);

	Record.AddInitNewSubrecord(SR_NAME_LLCT);

	for (dword i = 0; i < InfoArray.GetSize(); ++i)
	{
		srlvllistinfo_t& Info = *InfoArray[i];
		if (Info.pLvlo == NULL) continue;

		pSubrecord = Record.AddInitNewSubrecord(SR_NAME_LVLO);
		pSubrecord->Copy(Info.pLvlo);

		if (Info.pCoed != NULL)
		{
			pSubrecord = Record.AddInitNewSubrecord(SR_NAME_COED);
			pSubrecord->Copy(Info.pCoed);
		}
	}

	Record.UpdateListCount();
}


void SrSaveLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrNpc_Record& Record)
{
	throw "NotImplemented: SrSaveLvlListInfo(InfoArray, NpcRecord)!";
}


srlvllistinfo_t* SrFindLvlListInfo (CSrLvlListInfoArray& InfoArray, CSrSubrecord* pSubrecord)
{
	if (pSubrecord == NULL) return NULL;
	CSrCntoSubrecord* pCnto = SrCastClass(CSrCntoSubrecord, pSubrecord);
	CSrLvloSubrecord* pLvlo = SrCastClass(CSrLvloSubrecord, pSubrecord);

	for (dword i = 0; i < InfoArray.GetSize(); ++i)
	{
		if (pCnto != NULL && InfoArray[i]->pCnto == pCnto) return InfoArray[i];
		if (pLvlo != NULL && InfoArray[i]->pLvlo == pLvlo) return InfoArray[i];
	}

	return NULL;
}


void SrCreateLvlListInfoCustomData (srrlcustomdata_t& CustomData, srlvllistinfo_t& Info, CSrRecordHandler* pHandler) 
{
	CSrBaseRecord*    pBaseRecord;
	CSrIdRecord*	  pIdRecord;

	CustomData.Subrecords.Destroy();
	
	if (Info.pCnto != NULL) CustomData.Subrecords.Add(Info.pCnto);
	if (Info.pLvlo != NULL) CustomData.Subrecords.Add(Info.pLvlo);
	if (Info.pCoed != NULL) CustomData.Subrecords.Add(Info.pCoed);
	
	if (pHandler == NULL) return;
	pBaseRecord = pHandler->FindFormID(Info.GetFormID());
	pIdRecord = SrCastClassNull(CSrIdRecord, pBaseRecord);
	CustomData.pRecord = pIdRecord;	
}