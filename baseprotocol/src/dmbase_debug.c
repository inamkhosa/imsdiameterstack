#include "dmbase_debug.h"
#include "dmbase_dictionary.h"
#include "dmbase_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>



/* external */
extern	int							g_nDiamBaseTraceID ;




int	DMBase_Debug_console_and_fprintf( FILE* pfFile_i ,const char* pcFormatString_i, ...)
{
	int nRetval = 0;
	
	va_list arguments; 
	va_start ( arguments, pcFormatString_i );

	//first call printf 
	vprintf(pcFormatString_i,arguments);


	//now call fprintf if the file* is given
	if (NULL != pfFile_i) 
	{
		nRetval = vfprintf(pfFile_i,pcFormatString_i,arguments);
	}
	else
	{
		//do nothing
	}
	
	va_end ( arguments );     
	

	return nRetval;

}




int	DMBase_Debug_DumpDictionaryToFile( char* pcDumpFileName_i,
									 t_AVPDictionaryElement* poDiamDict_i,
									   unsigned int unDictSize_i)
{
	FILE *					poDictDumpFile = NULL;
	

	if ( NULL == pcDumpFileName_i ) 
	{
		printf("\n\n Error ! pcDumpFileName_i is NULL \n\n");
		return 0;
	}

	poDictDumpFile = fopen(pcDumpFileName_i,"w+");

	if ( NULL == poDictDumpFile) 
	{
		printf("\n\n Error ! poDictDumpFile is NULL \n\n");
		return 0;
	}

	fprintf(poDictDumpFile ,"CONTENTS OF DIAMETER IN-MEMORY DICTIONARY	\n\n");
	unsigned int unCurrIndex = 0;

	for (unCurrIndex =0 ; unCurrIndex <= unDictSize_i ; unCurrIndex++ ) 
	{
		fprintf(poDictDumpFile , "\n AVP Code = %d \n",unCurrIndex);
		if ( 1 == poDiamDict_i[unCurrIndex].bIsGrouped)
		{
			fprintf(poDictDumpFile , "bIsGrouped \t\t = true\n" ); 
		}
		else
		{
			fprintf(poDictDumpFile , "bIsGrouped \t\t = false\n" ); 
		}

		if ( 1 == poDiamDict_i[unCurrIndex].bIsPredefinedByRFC3588)
		{
			fprintf(poDictDumpFile , "bIsPredefinedByRFC3588 \t\t = true\n" ); 
		}
		else
		{
			fprintf(poDictDumpFile , "bIsPredefinedByRFC3588 \t\t = false\n" ); 
		}

		fprintf( poDictDumpFile , "AVP Data Type \t\t = %s\n",
				  poDiamDict_i[unCurrIndex].oAVPDataType.pucOctetString );


		fprintf( poDictDumpFile , "AVP Name \t\t = %s\n",
				  poDiamDict_i[unCurrIndex].oAVPName.pucOctetString );

		fprintf( poDictDumpFile , "AVP Code \t\t = %d\n",
				  poDiamDict_i[unCurrIndex].unAVPCode );

		fprintf( poDictDumpFile , "AVP VendorID \t\t = %d\n",
				  poDiamDict_i[unCurrIndex].unVendorID );

		//For M Flag
		if (AVPFlagAction_Set == poDiamDict_i[unCurrIndex].oMFlag.oFlagAction )
		{
			fprintf(poDictDumpFile , "M Flag Action = SET\n");
		}
		else if (AVPFlagAction_Clear == poDiamDict_i[unCurrIndex].oMFlag.oFlagAction )
		{
			fprintf(poDictDumpFile , "M Flag Action = CLEAR\n");
		}

		if (AVPFlagRule_May == poDiamDict_i[unCurrIndex].oMFlag.oFlagRule ) 
		{
			fprintf(poDictDumpFile , "M Flag Rule = MAY\n");
		}
		else if (AVPFlagRule_Must == poDiamDict_i[unCurrIndex].oMFlag.oFlagRule) 
		{
			fprintf(poDictDumpFile , "M Flag Rule = MUST\n");
		}
		else if (AVPFlagRule_MustNot == poDiamDict_i[unCurrIndex].oMFlag.oFlagRule) 
		{
			fprintf(poDictDumpFile , "M Flag Rule = MUSTNOT\n");
		}
		else if (AVPFlagRule_ShouldNot == poDiamDict_i[unCurrIndex].oMFlag.oFlagRule) 
		{
			fprintf(poDictDumpFile , "M Flag Rule = SHOULDNOT\n");
		}

		//for P Flag
		if (AVPFlagAction_Set == poDiamDict_i[unCurrIndex].oPFlag.oFlagAction )
		{
			fprintf(poDictDumpFile , "P Flag Action = SET\n");
		}
		else if (AVPFlagAction_Clear == poDiamDict_i[unCurrIndex].oPFlag.oFlagAction )
		{
			fprintf(poDictDumpFile , "P Flag Action = CLEAR\n");
		}

		if (AVPFlagRule_May == poDiamDict_i[unCurrIndex].oPFlag.oFlagRule ) 
		{
			fprintf(poDictDumpFile , "P Flag Rule = MAY\n");
		}
		else if (AVPFlagRule_Must == poDiamDict_i[unCurrIndex].oPFlag.oFlagRule) 
		{
			fprintf(poDictDumpFile , "P Flag Rule = MUST\n");
		}
		else if (AVPFlagRule_MustNot == poDiamDict_i[unCurrIndex].oPFlag.oFlagRule) 
		{
			fprintf(poDictDumpFile , "P Flag Rule = MUSTNOT\n");
		}
		else if (AVPFlagRule_ShouldNot == poDiamDict_i[unCurrIndex].oPFlag.oFlagRule) 
		{
			fprintf(poDictDumpFile , "P Flag Rule = SHOULDNOT\n");
		}
		

     }//end for 


	if (NULL != poDictDumpFile) 
	{
		fclose(poDictDumpFile);
		poDictDumpFile = NULL;
	}

	return 1;
}

int	DMBase_Debug_DumpBufferToFile ( unsigned char* pucBuff_i,
									unsigned int unBuffSize_i,
									char* pcDumpFileName_i )
{
	unsigned int	unCurrIndex = 0;
	FILE* 			poDumpFile = NULL;
	unsigned char	cCurrChar ;

	if ( (NULL == pucBuff_i) || (NULL == pcDumpFileName_i)) 
	{
		return 0;
	}
	poDumpFile = fopen(pcDumpFileName_i,"w+b");

	if ( NULL == poDumpFile) 
	{
		return 0;
	}

	for (unCurrIndex=0; unCurrIndex<= unBuffSize_i; unCurrIndex++) 
	{
		fputc( pucBuff_i[unCurrIndex] , poDumpFile);
	}

	if ( NULL != poDumpFile) 
	{
		fclose (poDumpFile);
		poDumpFile = NULL;
	}

	return 1;
}

int	DMBase_Debug_LoadBufferFromFile ( unsigned char** ppucBuff_o,
									  unsigned int * punBuffSize_o , 
									  char* pcFileToLoad_i )
{
	FILE*			poFileToLoad = NULL;
	unsigned int	unCurrIndex = 0;

	if ( (NULL == ppucBuff_o) || (NULL == punBuffSize_o)
		  || ( NULL != *ppucBuff_o)
	   ) 
	{
		return 0;
	}

	poFileToLoad = fopen ( pcFileToLoad_i , "rb" );
	if (NULL == poFileToLoad) 
	{
		return 0;
	}

	//get the size of the file first to allocate buffer
	unsigned int	unFileSize = 0;
	fseek(poFileToLoad, 0, SEEK_END);
	unFileSize = ftell(poFileToLoad);
	*punBuffSize_o = unFileSize;

	//rewind back for actual reading
	rewind (poFileToLoad);

	*ppucBuff_o = (unsigned char*) malloc ( unFileSize);
	if (NULL == *ppucBuff_o) 
	{
		fclose (poFileToLoad);
		poFileToLoad = NULL;
		return 0;
	}

	unsigned char *	pcTempBuffPtr = *ppucBuff_o;

	//now actually read
	for (unCurrIndex=0; unCurrIndex<= unFileSize; unCurrIndex++) 
	{
		*( pcTempBuffPtr + unCurrIndex) =  fgetc(poFileToLoad);
	}
	

	if (NULL != poFileToLoad) 
	{
		fclose (poFileToLoad);
		poFileToLoad = NULL;
	}

	return 1;
}

t_DiamAPIReturnVal	DMBase_Debug_DumpDiamMsgContents(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
													 FILE*	poDumpFile_i ,
													 HDIAMETERMESSAGE hMsg_i )
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Entering\n");

	if (NULL == hMsg_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsg is NULL , Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	t_DiameterHeader	oTempDiaHdr = hMsg_i->oDiaHeader;
	unsigned char		pucTempLen[3] = {0};
	

	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n\n Dumping the contents of Diameter Message \n\n");


	//version :one octet
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nVersion \t\t = %d", oTempDiaHdr.ucVersion);


	//message length 
	unsigned int unMsgLen = 0;

     if (DMBase_Retval_Success !=  DMBase_GetDiaMsgLengthFromDiamMsg(hDiameterStackContext_io,
									   hMsg_i,&unMsgLen)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgLengthFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }



	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nMessage Length \t\t = %d",unMsgLen);


	//one octet of command flags
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nMessage Flags \t\t = %d",oTempDiaHdr.ucFlags);

	//command code
	
	unsigned int	unCmdCode  = 0;

	 if (DMBase_Retval_Success !=  DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiameterStackContext_io,
									   hMsg_i,&unCmdCode)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgCmdCodeFromDiamMsg Failed , Leaving \n");
		  return DMBase_Retval_Failure;
	  }


	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nCommand Code \t\t = %d",unCmdCode);

	//four octets of applicationID
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nApplication ID = \t\t = %d",oTempDiaHdr.unApplicationID);

	//four octets of Hop By Hop ID
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nHop By Hop ID = \t\t = %d",oTempDiaHdr.unHopByHopID);

	//four octets of end to end ID
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\nEnd To End ID = \t\t = %d",oTempDiaHdr.unEndToEndID);

	if (NULL == hMsg_i->hCollectionOfAVPs) 
	{
		DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n No AVPs in the current message \n\n");
	}
	else
	{
		DMBase_Debug_DumpAVPListContents(hDiameterStackContext_io, poDumpFile_i,hMsg_i->hCollectionOfAVPs);
	}
	
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DMBase_Retval_Success;
}
t_DiamAPIReturnVal	DMBase_Debug_DumpAVPListContents(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
													 FILE*	poDumpFile_i , 
													 DMBase_SList*	pListOfAVPs_i )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	HAVP					hCurrAVP = NULL;
	void*					pData = NULL;
	DMBase_SList* 			pCurrentNode = pListOfAVPs_i;

	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n\n Dumping the contents of the AVP List \n");
	
	while (NULL != pCurrentNode) 
	{
		DMBase_SListGetNodeData(hDiameterStackContext_io, pCurrentNode, &pData);
		hCurrAVP = ( HAVP) pData;
		DMBase_Debug_DumpAVPContents(hDiameterStackContext_io, poDumpFile_i,hCurrAVP);
		DMBase_SListGetNextNode( hDiameterStackContext_io , pCurrentNode , &pCurrentNode);
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    
	return DMBase_Retval_Success;
}
t_DiamAPIReturnVal	DMBase_Debug_DumpAVPContents(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
												 FILE*	poDumpFile_i , 
												 HAVP hAVP_i )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");
	
	if ( NULL == hAVP_i ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! hAVP_i is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n\n Dumping the contents of AVP \n ");


	_Bool			bIsAVPGrouped ;
	unsigned int	unAVPLength =0;
	unsigned int	unAVPDataSize = 0;
	unsigned char	pucTempLen[3] = {0};
	t_AVPHeader		oAVPHeader;
	unsigned int	unTemp = 0;


	DMBase_IsAVPGrouped(hDiameterStackContext_io ,
						(hAVP_i->oAVPHeaderInst).unAVPCode  ,
						 &bIsAVPGrouped);


	//write the Grouped AVP Header first

	oAVPHeader = hAVP_i->oAVPHeaderInst;

	//writing 4 octets AVP code 
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n AVP Code == \t\t %d",oAVPHeader.unAVPCode);


	if (bIsAVPGrouped) 
	{
		DMBase_Debug_console_and_fprintf(poDumpFile_i,"( Grouped AVP ) ");
	}

    t_DiamDictionary	oDictionary = {0};
	

	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext_io,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray , 
											   hAVP_i->oAVPHeaderInst.unAVPCode )
	   ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

	//printing AVP Name
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n AVP Name == \t\t %s",
		 oDictionary.poDictionaryArray[oAVPHeader.unAVPCode].oAVPName.pucOctetString);
	
	//printing AVP Data Type
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n AVP Data Type == \t\t %s",
		 oDictionary.poDictionaryArray[oAVPHeader.unAVPCode].oAVPDataType.pucOctetString);

	//writing one octet AVP flags
	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n AVP Flags == \t\t %d",oAVPHeader.ucFlags);

	//writing AVP length
	if ( DMBase_Retval_Success != DMBase_GetAVPLengthFromAVPHeader(
								hDiameterStackContext_io,hAVP_i,&unTemp)
		)
    {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetAVPLengthFromAVPHeader Failed , Leaving \n");
	  return DMBase_Retval_Failure;
	}
	

	DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n AVP Length == \t\t %d",unTemp);

	//write optional vendorID four octets if V bit is set in flags
	if (DMBASE_AVP_V_BIT_IS_SET == (oAVPHeader.ucFlags & DMBASE_AVP_V_BIT_SET_MASK )) 
	{
		DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n Vendor ID == \t\t %d",oAVPHeader.unVendorID);
	}

	if ( bIsAVPGrouped ) 
	{
		//print the list of AVPs in this grouped AVP

		DMBase_Debug_console_and_fprintf(poDumpFile_i,"\n Dumping the contents of this grouped AVP \n ");

		DMBase_Debug_DumpAVPListContents(hDiameterStackContext_io, poDumpFile_i,
										 hAVP_i->hCollectionOfAVPs);
	} // end if AVP is grouped
	else
	{
		//AVP is not grouped
		
		//write AVP data now
		if (DMBASE_AVP_V_BIT_IS_SET == (oAVPHeader.ucFlags & DMBASE_AVP_V_BIT_SET_MASK ))
		{
			unAVPDataSize = unAVPLength - DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES ;
		}
		else
		{
			unAVPDataSize = unAVPLength - DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES; 
		}

		//copy data through dictionary function pointers
		t_AVPDictionaryElement	oAVPDictElem;

		oAVPDictElem =  oDictionary.poDictionaryArray[ oAVPHeader.unAVPCode ];


		oAVPDictElem.oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData(hDiameterStackContext_io, hAVP_i->pData,
												unAVPDataSize, poDumpFile_i);

	}//end else if AVP is not grouped

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	
	return DMBase_Retval_Success;
}



void	DMBase_Debug_PrintRawOctetString( unsigned char * pucRawOctStr_i,
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
