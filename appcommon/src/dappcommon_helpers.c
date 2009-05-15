#include "dappcommon_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

extern int g_nDiamBaseTraceID;



t_DappCommonReturnVal DappCommon_GetOctStringFromTLVBuff(unsigned char* pucTLVBuff_i,
													   unsigned int unOffsetToTLVRecd_i,
													   unsigned char ** ppucOctStrRequired_o,
													   unsigned int * punLenOfOctStr_o,
													unsigned int * punAppSpecificTag_o)
{
	if ( NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == punLenOfOctStr_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == ppucOctStrRequired_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL != *ppucOctStrRequired_o)
	{
		return DappCommon_Retval_IncorrectParameters;
	}
	t_Dappcommon_tlv_header*	poTempTLVHdr = (t_Dappcommon_tlv_header*)(pucTLVBuff_i + unOffsetToTLVRecd_i);
	if (DAPPCOMMON_TLV_RECTYPE_OCTSTRING != poTempTLVHdr->unRecordType)
	{
		return DappCommon_Retval_IncorrectParameters;
	}

	unsigned int	unSizeOfStr = poTempTLVHdr->unRecordLength  - DAPPCOMMON_TLV_RECHEADER_SIZE;
	unsigned char* pucTemp = (unsigned char*) malloc (unSizeOfStr);

	//copy string to allocated buff
	memcpy(pucTemp,
		   pucTLVBuff_i+unOffsetToTLVRecd_i +DAPPCOMMON_TLV_RECHEADER_SIZE,
		   unSizeOfStr);

	*ppucOctStrRequired_o = pucTemp;
	*punLenOfOctStr_o = unSizeOfStr;
	if (NULL != punAppSpecificTag_o)
	{
		*punAppSpecificTag_o = poTempTLVHdr->unAppSpecificTag;
	}

	return DappCommon_Retval_Success;


}

t_DappCommonReturnVal DappCommon_GetIntFromTLVBuff(unsigned char* pucTLVBuff_i,
													   unsigned int unOffsetToTLVRecd_i,
													   unsigned int* punIntRequired_o,
												   _Bool	bConvToHostOrder_i,
												   unsigned int * punAppSpecificTag_o )
{
	if ( NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == punIntRequired_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	t_Dappcommon_tlv_header*	poTempTLVHdr = (t_Dappcommon_tlv_header*)(pucTLVBuff_i + unOffsetToTLVRecd_i);
	if (DAPPCOMMON_TLV_RECTYPE_INT != poTempTLVHdr->unRecordType)
	{
		return DappCommon_Retval_IncorrectParameters;
	}
	if ( ( sizeof(unsigned int) != (poTempTLVHdr->unRecordLength - DAPPCOMMON_TLV_RECHEADER_SIZE) ) )
	{
		return DappCommon_Retval_IncorrectParameters;
	}
	unsigned int * punTemp = NULL;
	punTemp = (unsigned int*) ( pucTLVBuff_i + unOffsetToTLVRecd_i + DAPPCOMMON_TLV_RECHEADER_SIZE);
	if (1 == bConvToHostOrder_i)
	{
		*punIntRequired_o = ntohl (*punTemp);
	}
	else
	{
		*punIntRequired_o = *punTemp;
	}
	if (NULL != punAppSpecificTag_o)
	{
		*punAppSpecificTag_o = poTempTLVHdr->unAppSpecificTag;
	}
	return DappCommon_Retval_Success;
}


t_DappCommonReturnVal DappCommon_AddOctStringToTLVBuff(unsigned char ** ppucOrigBuff_io,
											   unsigned int	unOrigBuffLen_i,
											   unsigned int * punNewOrigBuffLen_o,
											   unsigned int	unOffsetInOrigBuff_i,
											   unsigned char* puchOctStrToAdd_i,
												unsigned int unSizeOfOcStr_i,
											    unsigned int  unAppSpecificTag_i)
{
	if ( NULL == ppucOrigBuff_io)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == *ppucOrigBuff_io)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == punNewOrigBuffLen_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == puchOctStrToAdd_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	unsigned char*				pucTempTLVBuff = *ppucOrigBuff_io;
	unsigned int				unNewBuffSize = 0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;
	_Bool						bBuffSizeOK = 0;
	unsigned int				unSizeNeededInBuff = DAPPCOMMON_TLV_RECHEADER_SIZE+ unSizeOfOcStr_i;

	//check if the buffer will hold the data
	if (unOrigBuffLen_i >= (unOffsetInOrigBuff_i+  unSizeNeededInBuff ))
	{
		bBuffSizeOK = 1;
	}
	else
	{
		bBuffSizeOK = 0;
	}

	if ( 0 == bBuffSizeOK)
	{
		//need to realloc
		unNewBuffSize = unOrigBuffLen_i + ( unSizeNeededInBuff - (unOrigBuffLen_i - unOffsetInOrigBuff_i));
		pucTempTLVBuff = (unsigned char*) realloc( (void*) pucTempTLVBuff , unNewBuffSize);
		*ppucOrigBuff_io = pucTempTLVBuff; //realloc can point to a new mem location hence
		*punNewOrigBuffLen_o = unNewBuffSize;
	}
	else
	{
		*punNewOrigBuffLen_o = unOrigBuffLen_i;
	}

	poTempTLVHdr = (t_Dappcommon_tlv_header*)  (pucTempTLVBuff + unOffsetInOrigBuff_i );
	poTempTLVHdr->unRecordType = DAPPCOMMON_TLV_RECTYPE_OCTSTRING;
	poTempTLVHdr->unRecordLength = DAPPCOMMON_TLV_RECHEADER_SIZE + unSizeOfOcStr_i ;
	poTempTLVHdr->unAppSpecificTag = unAppSpecificTag_i;

	//copy the octet string
	memcpy( pucTempTLVBuff + unOffsetInOrigBuff_i + DAPPCOMMON_TLV_RECHEADER_SIZE,
			puchOctStrToAdd_i , unSizeOfOcStr_i);

	return DappCommon_Retval_Success;
}




t_DappCommonReturnVal DappCommon_AddIntToTLVBuff(unsigned char ** ppucOrigBuff_io,
											   unsigned int	unOrigBuffLen_i,
											   unsigned int * punNewOrigBuffLen_o,
											   unsigned int	unOffsetInOrigBuff_i,
											   unsigned int unIntToAdd_i,
												 _Bool	bConvToNetOrder_i,
												unsigned int  unAppSpecificTag_i)
{
	if ( NULL == ppucOrigBuff_io)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == *ppucOrigBuff_io)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == punNewOrigBuffLen_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	unsigned char*				pucTempTLVBuff = *ppucOrigBuff_io;
	unsigned int				unNewBuffSize = 0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;
	_Bool						bBuffSizeOK = 0;
	unsigned int				unSizeNeededInBuff = DAPPCOMMON_TLV_RECHEADER_SIZE+sizeof(unsigned int);

	//check if the buffer will hold the data
	if (unOrigBuffLen_i >= (unOffsetInOrigBuff_i+  unSizeNeededInBuff ) )
	{
		bBuffSizeOK = 1;
	}
	else
	{
		bBuffSizeOK = 0;
	}

	if ( 0 == bBuffSizeOK)
	{
		//need to realloc
		unNewBuffSize = unOrigBuffLen_i + ( unSizeNeededInBuff - (unOrigBuffLen_i - unOffsetInOrigBuff_i));
		pucTempTLVBuff = (unsigned char*) realloc( (unsigned char*) pucTempTLVBuff , unNewBuffSize);
		*ppucOrigBuff_io = pucTempTLVBuff; //realloc can point to a new mem location hence
		*punNewOrigBuffLen_o = unNewBuffSize;
	}
	else
	{
		*punNewOrigBuffLen_o = unOrigBuffLen_i;
	}

	poTempTLVHdr = (t_Dappcommon_tlv_header*)  (pucTempTLVBuff + unOffsetInOrigBuff_i );
	poTempTLVHdr->unRecordType = DAPPCOMMON_TLV_RECTYPE_INT;
	poTempTLVHdr->unRecordLength = DAPPCOMMON_TLV_RECHEADER_SIZE + sizeof( unsigned int );

	poTempTLVHdr->unAppSpecificTag = unAppSpecificTag_i;

	unsigned int * punTempIntToWrite = (unsigned int*) (pucTempTLVBuff + unOffsetInOrigBuff_i + DAPPCOMMON_TLV_RECHEADER_SIZE);
	if (1 == bConvToNetOrder_i)
	{
		*punTempIntToWrite = htonl(unIntToAdd_i);
	}
	else
	{
		*punTempIntToWrite = unIntToAdd_i;
	}


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_Debug_DumpEntireTLVBuffer
											  (unsigned char *pucTLVBuff_i,
											   unsigned int	unTLVBuffLen_i,
											   unsigned int	unOffsetToStartOfTLVRecs_i
											   )
{
	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	unsigned char*				pucTempBuff = NULL;
	unsigned int				unLenProcessed =0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;

	pucTempBuff = pucTLVBuff_i;

	unLenProcessed = unOffsetToStartOfTLVRecs_i;



	printf("\n\n Dumping the Entire contents of TLV Buffer \n\n ");
	unsigned int	unCurrRecord = 1;

	while (unLenProcessed < unTLVBuffLen_i )
	{
		unsigned int	unTemp = 0;
		unsigned char*	pucTemp = NULL;

		pucTempBuff = pucTLVBuff_i + unLenProcessed;

		printf("\n Dumping TLV Record # ===> %d",unCurrRecord);
		poTempTLVHdr = (t_Dappcommon_tlv_header*) pucTempBuff;
		printf("\n\t TLV Record Header:");
		printf("\n\t\t TLV unRecordType = %d", poTempTLVHdr->unRecordType);
		printf("\n\t\t TLV unAppSpecificTag = %d", poTempTLVHdr->unAppSpecificTag);
		printf("\n\t\t TLV unRecordLength = %d", poTempTLVHdr->unRecordLength);
		printf("\n\t TLV Data:");
		unLenProcessed += sizeof( t_Dappcommon_tlv_header);

		if (DAPPCOMMON_TLV_RECTYPE_INT == poTempTLVHdr->unRecordType)
		{
			unTemp = *(unsigned int *) (pucTLVBuff_i+unLenProcessed);
			printf("\n\t\t Integer Value = %d",unTemp);
			unLenProcessed += sizeof( unsigned int );
		}
		else if (DAPPCOMMON_TLV_RECTYPE_OCTSTRING == poTempTLVHdr->unRecordType)
		{
			unsigned int	unTempStrSize = 0;
			pucTemp = pucTLVBuff_i + unLenProcessed;
			unTempStrSize = (poTempTLVHdr->unRecordLength) - DAPPCOMMON_TLV_RECHEADER_SIZE;
			printf("\n\t\t Octet String Value ");
			DappCommon_Debug_PrintRawOctetString(pucTemp,unTempStrSize);
			unLenProcessed += unTempStrSize;
		}


		printf("\n");
		unCurrRecord++;

	}//end while



	return DappCommon_Retval_Success;
}
void	DappCommon_Debug_PrintRawOctetString( unsigned char * pucRawOctStr_i,
										  unsigned int	unOctStrLen_i)
{
	if (NULL == pucRawOctStr_i)
	{
		return;
	}
	printf("\n");

	int i=0;
	for (i=0;i<=unOctStrLen_i ; i++)
	{
		printf("%c",pucRawOctStr_i[i]);
	}

	printf("\n");
}

t_DappCommonReturnVal DappCommon_Add_AVP_Data_ToTLVBuff
										(	HAVP				hAVP_ForData_i,
											unsigned char ** 	ppucOrigBuff_io,
											unsigned int		unOrigBuffLen_i,
											unsigned int * 		punNewOrigBuffLen_o,
											unsigned int		unOffsetInOrigBuff_i
                                         )
{
	if (NULL == hAVP_ForData_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == ppucOrigBuff_io  )
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == *ppucOrigBuff_io)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if (NULL == punNewOrigBuffLen_o  )
	{
		return DappCommon_Retval_Null_Pointer;
	}


	_Bool	bIsAVPStringType = 0;
	_Bool	bIsAVPGrouped = 0;
	DMBase_IsAVPGrouped(NULL,hAVP_ForData_i->oAVPHeaderInst.unAVPCode,
						&bIsAVPGrouped);

	if ( 1 == bIsAVPGrouped)
	{
		return DappCommon_Retval_Not_Supported;
	}

	DMBase_IsTypeOctetStringOrDerived(NULL,hAVP_ForData_i->oAVPHeaderInst.unAVPCode,
									  &bIsAVPStringType);


	t_DiamOctetString*	poTempOctStr = NULL;
	t_DiamUnsigned32*	poTempUint32 = NULL;

    unsigned char*				pucTempTLVBuff = *ppucOrigBuff_io;
	unsigned int				unNewBuffSize = 0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;
	_Bool						bBuffSizeOK = 0;
	unsigned int				unSizeOfData = 0;

	if ( 0 == bIsAVPStringType)
	{
		//string type data
		poTempOctStr = (t_DiamOctetString*) ( hAVP_ForData_i->pData);
		unSizeOfData = poTempOctStr->unNumOfOctets;
	}
	else
	{
		//integer type data
		poTempUint32 = (t_DiamUnsigned32*) (hAVP_ForData_i->pData);
		unSizeOfData = poTempUint32->unNumOfOctets;
	}

	unsigned int	unSizeNeededInBuff = DAPPCOMMON_TLV_RECHEADER_SIZE+ unSizeOfData;

	//check if the buffer will hold the data
	if (unOrigBuffLen_i >= (unOffsetInOrigBuff_i+  unSizeNeededInBuff ))
	{
		bBuffSizeOK = 1;
	}
	else
	{
		bBuffSizeOK = 0;
	}

	if ( 0 == bBuffSizeOK)
	{
		//need to realloc
		unNewBuffSize = unOrigBuffLen_i + ( unSizeNeededInBuff - (unOrigBuffLen_i - unOffsetInOrigBuff_i));
		pucTempTLVBuff = (unsigned char*) realloc( (void*) pucTempTLVBuff , unNewBuffSize);
		*ppucOrigBuff_io = pucTempTLVBuff; //realloc can point to a new mem location hence
		*punNewOrigBuffLen_o = unNewBuffSize;
	}
	else
	{
		*punNewOrigBuffLen_o = unOrigBuffLen_i;
	}

    poTempTLVHdr = (t_Dappcommon_tlv_header*)  (pucTempTLVBuff + unOffsetInOrigBuff_i );
	poTempTLVHdr->unRecordLength = DAPPCOMMON_TLV_RECHEADER_SIZE + unSizeOfData ;
	poTempTLVHdr->unAppSpecificTag = hAVP_ForData_i->oAVPHeaderInst.unAVPCode;

	if (1 == bIsAVPStringType)
	{
		poTempTLVHdr->unRecordType = DAPPCOMMON_TLV_RECTYPE_OCTSTRING;
		//copy the octet string
		memcpy( pucTempTLVBuff + unOffsetInOrigBuff_i + DAPPCOMMON_TLV_RECHEADER_SIZE,
			poTempOctStr->pucOctetString ,
			poTempOctStr->unNumOfOctets);
	}
	else
	{
		poTempTLVHdr->unRecordType = DAPPCOMMON_TLV_RECTYPE_INT;
		//copy the integer
		memcpy( pucTempTLVBuff + unOffsetInOrigBuff_i + DAPPCOMMON_TLV_RECHEADER_SIZE,
			poTempUint32->punUnsigned32,
			poTempUint32->unNumOfOctets);
	}




	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_Make_AVP_FromTLVRecord
										(	HDIAMETERSTACKCONTEXT hDiamStackContext_i,
											 HAVP*				phAVP_FromTLVRec_o,
											unsigned char* 		pucTLVBuff_i,
											unsigned int		unOffsetToTLVRecd_i,
											t_DiamDictionary*	poDiamDict_i,
											HMSGALLOCATIONCONTEXT	hMsgAllocContext_io
										)
{

	if (NULL == hDiamStackContext_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if (NULL == phAVP_FromTLVRec_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL != *phAVP_FromTLVRec_o  )
	{
		return DappCommon_Retval_IncorrectParameters;
	}

	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if (NULL == poDiamDict_i  )
	{
		return DappCommon_Retval_Null_Pointer;
	}

	_Bool	bIsAVPGrouped = 0;

	t_Dappcommon_tlv_header*	poTempTLVHdr = (t_Dappcommon_tlv_header*)(pucTLVBuff_i + unOffsetToTLVRecd_i);

	DMBase_IsAVPGrouped(NULL,poTempTLVHdr->unAppSpecificTag
						,&bIsAVPGrouped);

	if (1 == bIsAVPGrouped)
	{
		return DappCommon_Retval_IncorrectParameters;
	}


	unsigned int	unSizeOfData = poTempTLVHdr->unRecordLength  - DAPPCOMMON_TLV_RECHEADER_SIZE;
	void*			pDataForAVP = NULL;
	unsigned char*	pucTemp = NULL;
	pucTemp = (unsigned char*) poTempTLVHdr;

	poDiamDict_i->poDictionaryArray[poTempTLVHdr->unAppSpecificTag].oAVPDictionaryFunctionPtrs.pfGetStructData(
									hDiamStackContext_i, pucTemp+DAPPCOMMON_TLV_RECHEADER_SIZE,
									&pDataForAVP,unSizeOfData,hMsgAllocContext_io);


	//make the AVP
	DMBase_CreateAVP(hDiamStackContext_i,phAVP_FromTLVRec_o,hMsgAllocContext_io,
					  poTempTLVHdr->unAppSpecificTag,
					 pDataForAVP,unSizeOfData, 0);


	return DappCommon_Retval_Success;

}

t_DappCommonReturnVal DappCommon_GetOctString_ByAppTag_FromTLVBuff
									(unsigned char* pucTLVBuff_i,
									 unsigned int	unOffsetToStartOfTLVRecs_i,
									 unsigned char ** ppucOctStrRequired_o,
									 unsigned int * punLenOfOctStr_o,
									unsigned int 	unAppSpecificTag_i,
									 unsigned int	unTLVBuffLen_i)
{
	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == ppucOctStrRequired_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL != *ppucOctStrRequired_o)
	{
		return DappCommon_Retval_IncorrectParameters;
	}

	if (NULL == punLenOfOctStr_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}


	_Bool	bFound = 0;

	unsigned char*				pucTempBuff = NULL;
	unsigned int				unLenProcessed =0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;

	unLenProcessed = unOffsetToStartOfTLVRecs_i;


	unsigned int	unCurrRecord = 1;

	while (unLenProcessed < unTLVBuffLen_i )
	{
		unsigned char*	pucTemp = NULL;

		poTempTLVHdr = (t_Dappcommon_tlv_header*) (pucTLVBuff_i + unLenProcessed);

		if (unAppSpecificTag_i == poTempTLVHdr->unAppSpecificTag)
		{
			bFound = 1;
			unsigned int	unTempStrSize = 0;

			unTempStrSize = (poTempTLVHdr->unRecordLength) - DAPPCOMMON_TLV_RECHEADER_SIZE;

			unsigned char* pucTempForCopy = (unsigned char*) malloc (unTempStrSize);

			pucTemp = (unsigned char*) poTempTLVHdr;

			//copy string to allocated buff
			memcpy(pucTempForCopy,
				   pucTemp + DAPPCOMMON_TLV_RECHEADER_SIZE,
				   unTempStrSize);

			*ppucOctStrRequired_o = pucTempForCopy;

			*punLenOfOctStr_o = unTempStrSize;

			break;
		}
		else
		{
			//update processed length
			unLenProcessed +=  (poTempTLVHdr->unRecordLength);
		}
		unCurrRecord++;

	}//end while


	if (1 == bFound)
	{
		return DappCommon_Retval_Success;
	}
	else
	{
		return DappCommon_Retval_Not_Found;
	}
}

t_DappCommonReturnVal DappCommon_GetInt_ByAppTag_FromTLVBuff
									(unsigned char* pucTLVBuff_i,
									 unsigned int	unOffsetToStartOfTLVRecs_i,
                                     unsigned int * punIntRequired_o,
									 unsigned int 	unAppSpecificTag_i,
									 unsigned int	unTLVBuffLen_i)
{

	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == punIntRequired_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	_Bool	bFound = 0;


	unsigned char*				pucTempBuff = NULL;
	unsigned int				unLenProcessed =0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;

	pucTempBuff = pucTLVBuff_i;

	unLenProcessed = unOffsetToStartOfTLVRecs_i;


	unsigned int	unCurrRecord = 1;

	while (unLenProcessed < unTLVBuffLen_i )
	{
		unsigned char*	pucTemp = NULL;

		poTempTLVHdr = (t_Dappcommon_tlv_header*) (pucTLVBuff_i + unLenProcessed);


		if (unAppSpecificTag_i == poTempTLVHdr->unAppSpecificTag)
		{
			bFound = 1;

			pucTemp =  (unsigned char*) poTempTLVHdr;

			*punIntRequired_o = *(unsigned int*) (pucTemp +  DAPPCOMMON_TLV_RECHEADER_SIZE);

			break;
		}
		else
		{
			//update processed length
			unLenProcessed +=  poTempTLVHdr->unRecordLength;
		}
		unCurrRecord++;

	}//end while



	if (1 == bFound)
	{
		return DappCommon_Retval_Success;
	}
	else
	{
		return DappCommon_Retval_Not_Found;
	}

}

t_DappCommonReturnVal DappCommon_Make_AVP_ByAppTag_FromTLVBuff
										(	HDIAMETERSTACKCONTEXT hDiamStackContext_i,
											HAVP*				phAVP_FromTLVRec_o,
											unsigned char* 		pucTLVBuff_i,
											unsigned int		unLenofTLVBuff_i,
											unsigned int		unOffsetToStartOfTLVRecs_i,
											unsigned int		unAppSpecificTag_i,
											t_DiamDictionary*	poDiamDict_i,
											_Bool				bConvToHostOrdIfInt_i,
											HMSGALLOCATIONCONTEXT	hMsgAllocContext_io
										)
{

	if (NULL == hDiamStackContext_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == phAVP_FromTLVRec_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL != *phAVP_FromTLVRec_o  )
	{
		return DappCommon_Retval_IncorrectParameters;
	}

	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if (NULL == poDiamDict_i  )
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if (NULL == hMsgAllocContext_io) 
	{
		return DappCommon_Retval_Null_Pointer;
	}

	_Bool	bIsAVPGrouped = 0;

	DMBase_IsAVPGrouped(NULL,unAppSpecificTag_i,&bIsAVPGrouped);

	if (1 == bIsAVPGrouped)
	{
		return DappCommon_Retval_IncorrectParameters;
	}



	_Bool	bFound = 0;

	unsigned char*				pucTempBuff = NULL;
	unsigned int				unLenProcessed =0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;

	pucTempBuff = pucTLVBuff_i;

	unLenProcessed = unOffsetToStartOfTLVRecs_i;


	unsigned int	unCurrRecord = 1;

	while (unLenProcessed < unLenofTLVBuff_i )
	{
		void*	pDataForAVP = NULL;

		pucTempBuff = pucTLVBuff_i + unLenProcessed;

		poTempTLVHdr = (t_Dappcommon_tlv_header*) pucTempBuff;

		if (unAppSpecificTag_i == poTempTLVHdr->unAppSpecificTag)
		{
			bFound = 1;
			unsigned int	unTempDataSize = 0;
			unTempDataSize = (poTempTLVHdr->unRecordLength) - DAPPCOMMON_TLV_RECHEADER_SIZE;


			//Make AVP
			poDiamDict_i->poDictionaryArray[unAppSpecificTag_i].oAVPDictionaryFunctionPtrs.pfGetStructData(
									hDiamStackContext_i, pucTempBuff+DAPPCOMMON_TLV_RECHEADER_SIZE,
									&pDataForAVP,unTempDataSize,hMsgAllocContext_io);

			_Bool	bIsStringType = 0;
			DMBase_IsTypeOctetStringOrDerived(hDiamStackContext_i,unAppSpecificTag_i,&bIsStringType);

			if (0 == bIsStringType)
			{
				if (1 == bConvToHostOrdIfInt_i)
				{
					t_DiamUnsigned32*	poTempUint = (t_DiamUnsigned32*) pDataForAVP;
					unsigned int	unTemp = *poTempUint->punUnsigned32;
					unTemp = ntohl(unTemp);
					*poTempUint->punUnsigned32 = unTemp;
				}
			}

			//make the AVP
			DMBase_CreateAVP(hDiamStackContext_i,phAVP_FromTLVRec_o,
							 hMsgAllocContext_io, unAppSpecificTag_i,
							 pDataForAVP,unTempDataSize, 0);


			break;
		}
		else
		{
			//update processed length
			unLenProcessed += (poTempTLVHdr->unRecordLength);
		}
		unCurrRecord++;

	}//end while


	if (1 == bFound)
	{
		return DappCommon_Retval_Success;
	}
	else
	{
		return DappCommon_Retval_Not_Found;
	}

}
t_DappCommonReturnVal DappCommon_GetOctStringFromTLVBuff_AddNullTerm
													(unsigned char* pucTLVBuff_i,
													   unsigned int unOffsetToTLVRecd_i,
													   unsigned char ** ppucOctStrRequired_o,
													   unsigned int * punLenOfOctStr_o,
													   unsigned int * punAppSpecificTag_o)
{
	if ( NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == punLenOfOctStr_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL == ppucOctStrRequired_o)
	{
		return DappCommon_Retval_Null_Pointer;
	}
	if ( NULL != *ppucOctStrRequired_o)
	{
		return DappCommon_Retval_IncorrectParameters;
	}
	t_Dappcommon_tlv_header*	poTempTLVHdr = (t_Dappcommon_tlv_header*)(pucTLVBuff_i + unOffsetToTLVRecd_i);
	if (DAPPCOMMON_TLV_RECTYPE_OCTSTRING != poTempTLVHdr->unRecordType)
	{
		return DappCommon_Retval_IncorrectParameters;
	}

	unsigned int	unSizeOfStr = poTempTLVHdr->unRecordLength  - DAPPCOMMON_TLV_RECHEADER_SIZE;
	unsigned char* pucTemp = (unsigned char*) malloc (unSizeOfStr+1);

	//copy string to allocated buff
	memcpy(pucTemp,
		   pucTLVBuff_i+unOffsetToTLVRecd_i +DAPPCOMMON_TLV_RECHEADER_SIZE,
		   unSizeOfStr);

	pucTemp[unSizeOfStr] = '\0';

	*ppucOctStrRequired_o = pucTemp;
	*punLenOfOctStr_o = unSizeOfStr+1;
	if (NULL != punAppSpecificTag_o)
	{
		*punAppSpecificTag_o = poTempTLVHdr->unAppSpecificTag;
	}

	return DappCommon_Retval_Success;


}


t_DappCommonReturnVal DappCommon_GetIntList_ByAppTag_FromTLVBuff
									(unsigned char* pucTLVBuff_i,
									 unsigned int	unOffsetToStartOfTLVRecs_i,
                                     DMBase_SList **ppoIntList,
									 unsigned int 	unAppSpecificTag_i,
									 unsigned int	unTLVBuffLen_i)
{

	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == ppoIntList)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	_Bool	bFound = 0;


	unsigned char*				pucTempBuff = NULL;
	unsigned int				unLenProcessed =0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;

	pucTempBuff = pucTLVBuff_i;

	unLenProcessed = unOffsetToStartOfTLVRecs_i;


	unsigned int	unCurrRecord = 1;
        unsigned int    *punIntRequired_o = NULL;

	while (unLenProcessed < unTLVBuffLen_i )
	{
		unsigned char*	pucTemp = NULL;

		poTempTLVHdr = (t_Dappcommon_tlv_header*) (pucTLVBuff_i + unLenProcessed);


		if (unAppSpecificTag_i == poTempTLVHdr->unAppSpecificTag)
		{
			bFound = 1;

			pucTemp =  (unsigned char*) poTempTLVHdr;
                        punIntRequired_o = malloc(sizeof(unsigned int));
			*punIntRequired_o = *(unsigned int*) (pucTemp +  DAPPCOMMON_TLV_RECHEADER_SIZE);
                        DMBase_AppendSList(NULL, ppoIntList, (void*)punIntRequired_o);

		}
		//update processed length
		unLenProcessed +=  poTempTLVHdr->unRecordLength;
		unCurrRecord++;

	}//end while



	if (1 == bFound)
	{
		return DappCommon_Retval_Success;
	}
	else
	{
		return DappCommon_Retval_Not_Found;
	}

}


t_DappCommonReturnVal DappCommon_GetOctStringList_ByAppTag_FromTLVBuff(unsigned char* pucTLVBuff_i,
								   unsigned int	unOffsetToStartOfTLVRecs_i,
                                                                   DMBase_SList **ppoStringList,
                                                                   unsigned int 	unAppSpecificTag_i,
                                                                   unsigned int	unTLVBuffLen_i)
{
	if (NULL == pucTLVBuff_i)
	{
		return DappCommon_Retval_Null_Pointer;
	}

	if (NULL == ppoStringList)
	{
		return DappCommon_Retval_Null_Pointer;
	}


	_Bool	bFound = 0;

	unsigned char*				pucTempBuff = NULL;
	unsigned int				unLenProcessed =0;
	t_Dappcommon_tlv_header*	poTempTLVHdr = NULL;

	unLenProcessed = unOffsetToStartOfTLVRecs_i;

        t_DiamOctetString *poStringReq = NULL;
	unsigned int	unCurrRecord = 1;

	while (unLenProcessed < unTLVBuffLen_i )
	{
		unsigned char*	pucTemp = NULL;

		poTempTLVHdr = (t_Dappcommon_tlv_header*) (pucTLVBuff_i + unLenProcessed);

		if (unAppSpecificTag_i == poTempTLVHdr->unAppSpecificTag)
		{
			bFound = 1;
			unsigned int	unTempStrSize = 0;

			unTempStrSize = (poTempTLVHdr->unRecordLength) - DAPPCOMMON_TLV_RECHEADER_SIZE;

			unsigned char* pucTempForCopy = (unsigned char*) malloc (unTempStrSize);

			pucTemp = (unsigned char*) poTempTLVHdr;

			//copy string to allocated buff
			memcpy(pucTempForCopy,
				   pucTemp + DAPPCOMMON_TLV_RECHEADER_SIZE,
				   unTempStrSize);
                        poStringReq = NULL;
                        DMBase_Malloc(NULL, (void**)&poStringReq, sizeof(t_DiamOctetString));
                        poStringReq->pucOctetString = pucTempForCopy;
                        poStringReq->unNumOfOctets = unTempStrSize;
                        DMBase_AppendSList(NULL, ppoStringList, poStringReq);
		}

                //update processed length
                unLenProcessed +=  (poTempTLVHdr->unRecordLength);
		unCurrRecord++;

	}//end while


	if (1 == bFound)
	{
		return DappCommon_Retval_Success;
	}
	else
	{
		return DappCommon_Retval_Not_Found;
	}
}

t_DappCommonReturnVal DappCommon_GiveNewUUID(
								   unsigned char* pucUUIDBuff_o,
								   unsigned int	unBuffLen_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering \n");

	if (unBuffLen_i  < DAPPCOMMON_UUID_SIZE_IN_BYTES ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Insufficient Buffer unBuffLen_i = %d ,Reqiured = %d  \n",
					  unBuffLen_i,DAPPCOMMON_UUID_SIZE_IN_BYTES );
		return DappCommon_Retval_InsufficientBuffer;
	}

	//zero out the buffer
	if ( DMBase_Retval_Success != DMBase_MemsetZero(pucUUIDBuff_o,
												DAPPCOMMON_UUID_SIZE_IN_BYTES)
		 )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_MemsetZero failed \n" );
		return DappCommon_Retval_Failure;
	}


	
	FILE*					fpUUID = NULL;
	t_DappCommonReturnVal	oRetVal = DappCommon_Retval_Success;

	fpUUID = fopen("/proc/sys/kernel/random/uuid","rb");
	if (NULL == fpUUID) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Unable to open UUID file from filesystem" );
		oRetVal =  DappCommon_Retval_Failure;
		goto ExitMe;
	}

	if ( ( DAPPCOMMON_UUID_SIZE_IN_BYTES -1 ) != fread(pucUUIDBuff_o,
								sizeof(unsigned char),DAPPCOMMON_UUID_SIZE_IN_BYTES-1,fpUUID)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Unable to read UUID from file in filesystem" );
		oRetVal = DappCommon_Retval_Failure;
		goto ExitMe;
	}


	ExitMe:
	if (NULL != fpUUID) 
	{
		fclose(fpUUID);
		fpUUID= NULL;
	}


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");

	return oRetVal;
}









