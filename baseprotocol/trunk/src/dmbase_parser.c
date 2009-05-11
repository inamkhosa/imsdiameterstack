/***************************************************************************
 *   Copyright (C) 2008 by simab   *
 *   simabshahid@advancedims.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place _ Suite 330, Boston, MA  02111_1307, USA.             *
 ***************************************************************************/
#include "dmbase_includes.h"

/* external */
extern	int							g_nDiamBaseTraceID ;

 
t_DiamAPIReturnVal  DMBase_ParseRawDiameterMessage (HDIAMETERSTACKCONTEXT  hDiameterStackContext_io , 
                                                    unsigned char *     pRawDiameterPacket_i , 
                                                    HDIAMETERMESSAGE*             phDiaMsgHandle_o )

{       
        int                 nSizeOfRawAVPList =    0;
        void*               pMemCpyReturnValue  =    NULL;
		unsigned char		pucTempLen[3] = {0};
		unsigned int		unTempIndex = 0;
		unsigned char 		ucVersion = 0;
		unsigned int		unDiamMsgLength = 0;
		unsigned char		ucFlags = 0;
		unsigned int		unCommandCode = 0;
		unsigned int		unApplicationID = 0;
		unsigned int		unHopByHopID = 0;
		unsigned int  		unEndToEndID = 0;
		t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


		if (NULL == hDiameterStackContext_io ) 
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
			return DMBase_Retval_Null_Pointer;
		}

		if (NULL == pRawDiameterPacket_i ) 
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pRawDiameterPacket_i is NULL .\n");
			return DMBase_Retval_Null_Pointer;
		}

		if (NULL == phDiaMsgHandle_o ) 
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phDiaMsgHandle_o is NULL .\n");
			return DMBase_Retval_Null_Pointer;
		}

		if (NULL != (*phDiaMsgHandle_o) ) 
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*phDiaMsgHandle_o) is NOT NULL .\n");
			return DMBase_Retval_IncorrectParameters;
		}

		//Parsing the fixed size Diameter Message header 

		//get one octet of version
		ucVersion = * (pRawDiameterPacket_i + unTempIndex);
		unTempIndex++;

		//get three octets of message length
		pucTempLen[0] = *(pRawDiameterPacket_i + unTempIndex);
		unTempIndex++;
		pucTempLen[1] = * (pRawDiameterPacket_i + unTempIndex);
		unTempIndex++;
		pucTempLen[2] = * (pRawDiameterPacket_i + unTempIndex);
		unTempIndex++;

		if (DMBase_Retval_Success != DMBase_GiveUIntInHostOrderFor3Bytes(
										pucTempLen , &unDiamMsgLength)
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GiveUIntInHostOrderFor3Bytes FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}

		
		if (unDiamMsgLength < DMBASE_MSG_HEADER_SIZE_IN_BYTES ) 
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Message length is less than fixed diameter message header size !! , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}

		if (unDiamMsgLength > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS ) 
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Message length is more than DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS !! , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}


		//get one octet of command flags
		ucFlags = * ( pRawDiameterPacket_i + unTempIndex );
		unTempIndex++;

		//get three octets of command code
		pucTempLen[0] = * (pRawDiameterPacket_i + unTempIndex );
		unTempIndex++;
		pucTempLen[1] = * (pRawDiameterPacket_i + unTempIndex);
		unTempIndex++;
		pucTempLen[2] = * (pRawDiameterPacket_i + unTempIndex );
		unTempIndex++;

		
		if (DMBase_Retval_Success != DMBase_GiveUIntInHostOrderFor3Bytes(
										pucTempLen , &unCommandCode)
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GiveUIntInHostOrderFor3Bytes FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}

		if (unCommandCode > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS ) 
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Command Code is more than DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS !! , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}
		

		unsigned int	unTemp = 0;
		//get four octets of Application ID
		unsigned int*	punTempIntPtr = NULL;
		punTempIntPtr = (unsigned int* ) (pRawDiameterPacket_i + unTempIndex);
		unTemp = *punTempIntPtr;
		//unApplicationID = ntohl( unApplicationID);

		if (DMBase_Retval_Success != DMBase_NetworkToHostLong(
				hDiameterStackContext_io,unTemp,(unsigned long *) &unApplicationID)
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostLong FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}



		unTempIndex += 4;

		//get four octets of HopByHop ID
		punTempIntPtr = (unsigned int* ) (pRawDiameterPacket_i + unTempIndex);
		unTemp = *punTempIntPtr;
		//unHopByHopID = ntohl( unHopByHopID);
		if (DMBase_Retval_Success != DMBase_NetworkToHostLong(
				hDiameterStackContext_io,unTemp,(unsigned long *) &unHopByHopID)
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostLong FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}
		unTempIndex += 4;

		//get four octets of EndToEndID
		punTempIntPtr = (unsigned int* ) (pRawDiameterPacket_i + unTempIndex);
		unTemp = *punTempIntPtr;
		//unEndToEndID = ntohl( unEndToEndID);
		if (DMBase_Retval_Success != DMBase_NetworkToHostLong(
				hDiameterStackContext_io,unTemp,(unsigned long *) &unEndToEndID)
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostLong FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}

		//TODO!! Make the 4 below and similar things to be DEFINES to relevant offsets!!!!!!

		unTempIndex += 4; 

		// Now make memory for Message structure and parse the message data i.e. AVPs

		
		
       if (DMBase_Retval_Success !=  DMBase_CreateDiameterMessage(  
							hDiameterStackContext_io ,phDiaMsgHandle_o , ucVersion, 
							unCommandCode ,unApplicationID,ucFlags,
							unHopByHopID , unEndToEndID)
		   )
	   {
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_CreateDiameterMessage FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
	   }

	   unsigned int	unOffsetToMsgLength = 1;

	   if (DMBase_Retval_Success !=  DMBase_SetDiaMsgLength(hDiameterStackContext_io,
							    (*phDiaMsgHandle_o),unDiamMsgLength)
	  )
	  {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetDiaMsgLength Failed , Leaving \n");
		  oRetval=  DMBase_Retval_Failure;
		  goto ExitMe;
	  }
       
	   nSizeOfRawAVPList = unDiamMsgLength -  DMBASE_MSG_HEADER_SIZE_IN_BYTES ;

	   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt = NULL;
	   if (DMBase_Retval_Success !=  DMBase_Get_AllocationContext_ForMessage(
					hDiameterStackContext_io,*phDiaMsgHandle_o,&hMsgAllocCtxt)
		   )
	   {
		  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_Get_AllocationContext_ForMessage Failed , Leaving \n");
		  oRetval=  DMBase_Retval_Failure;
		  goto ExitMe;
	  }

	   

 	   if (0 != nSizeOfRawAVPList) 
	   {
          
		   if (DMBase_Retval_Success !=  DMBase_ConvertRawAVPsToStructAVPCollection ( hDiameterStackContext_io ,
										   & ((*phDiaMsgHandle_o)->hCollectionOfAVPs) ,  
										  ( unsigned char*)pRawDiameterPacket_i,
										  DMBASE_MSG_HEADER_SIZE_IN_BYTES ,
										   nSizeOfRawAVPList,
											hMsgAllocCtxt)
			   )
		   {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_FillRawAVPListToStruct FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
		   }
	   }
	   else
	   {
		   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " No data in the message to parse after the msg header...\n");
	   }

	   ExitMe:

	   if (DMBase_Retval_Success != oRetval) 
	   {
		   if (NULL != (*phDiaMsgHandle_o)) 
		   {
			   if (DMBase_Retval_Success != DMBase_DestroyDiaMessage(
									hDiameterStackContext_io,phDiaMsgHandle_o)
				  )
			   {
				   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_DestroyDiaMessage Failed.\n");
			   }

		   }//end if (NULL != (*phDiaMsgHandle_o))

	   }//end if (DMBase_Retval_Success != oRetval)

	   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");


	   return oRetval;
}


t_DiamAPIReturnVal  DMBase_ConvertRawAVPsToStructAVPCollection ( 
										HDIAMETERSTACKCONTEXT  hDiameterStackContext_io , 
										HAVPCOLLECTION*		   phCollOfAVPs_o,
										unsigned char* 	       pucRawBuff_i ,
										unsigned int	       unOffsetToListBegin_i ,
										unsigned int 	       unSizeOfRawAVPList_i,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{

	 int			    nBytes  			    = 3;
     unsigned int       unAVPDataSize	         = 0;
	 unsigned int		unCurrentAVPSize         = 0;
     unsigned int       unSizeofRawAVPList       = 0;
     unsigned int	 	unIndexofParsedAVPList = 0;
     _Bool              bIsAVPGrouped		    =FALSE;
     HAVP  				hTempAVP		       	= NULL;
     HAVP				hAVP		        	= NULL;
	 HAVP 				hGroupedAVP			    = NULL;
	 void*			    pMemCpyReturnValue	    = NULL;
     void*              pAVPRawData           	= NULL;
     void*              pAVPStructData        	= NULL;
	 unsigned int 		unCurrAVPCode = 0;
	 unsigned int   	unCurrAVPVendorID = 0 ;
	 unsigned char		pucTempLen[3] = {0};
	 unsigned char		ucCurrAVPFlags = 0;
	 t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;
	 



	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


	if ( NULL == hDiameterStackContext_io) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving\n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hMsgAllocCtxt_io) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , Leaving\n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == phCollOfAVPs_o) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phCollOfAVPs_o is NULL , Leaving\n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL != (*phCollOfAVPs_o)) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*phCollOfAVPs_o) is NOT NULL , Leaving\n");
	  return DMBase_Retval_IncorrectParameters;
	}

	if ( NULL == pucRawBuff_i) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pucRawBuff_i is NULL , Leaving\n");
	  return DMBase_Retval_Null_Pointer;
	}

	 
	unsigned char*	pucStartOfCurrentAVP = NULL;

	//various offsets
	const unsigned int	unOffsetToAVPCodeInAVPHdr = 0;
	const unsigned int	unOffsetToFlagsInAVPHdr = 4;
	const unsigned int	unOffsetToAVPLenInAVPHdr = 5;
	const unsigned int	unOffsetToVendorIDInAVPHdr = 8;

	unsigned int		unPadLen =0;
	

    while(  unIndexofParsedAVPList < unSizeOfRawAVPList_i )
    {

        pucStartOfCurrentAVP =  pucRawBuff_i + unOffsetToListBegin_i + unIndexofParsedAVPList ;
		

		pucTempLen[0] = * (pucStartOfCurrentAVP + unOffsetToAVPLenInAVPHdr);
		pucTempLen[1] = * (pucStartOfCurrentAVP + unOffsetToAVPLenInAVPHdr + 1);
		pucTempLen[2] = * (pucStartOfCurrentAVP + unOffsetToAVPLenInAVPHdr + 2);

		if (DMBase_Retval_Success != DMBase_GiveUIntInHostOrderFor3Bytes(
										pucTempLen,&unCurrentAVPSize)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GiveUIntInHostOrderFor3Bytes FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}

		if (unCurrentAVPSize > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS) 
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " unCurrentAVPSize > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}
		

		unsigned int*	punTemp = NULL;
		unsigned int	unTemp = 0;

		punTemp = (unsigned int*) (pucStartOfCurrentAVP +unOffsetToAVPCodeInAVPHdr);

		unTemp = *punTemp;

		//unCurrAVPCode = ntohl ( unCurrAVPCode );
		if (DMBase_Retval_Success != DMBase_NetworkToHostLong(
				hDiameterStackContext_io,unTemp,(unsigned long *) &unCurrAVPCode)
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostLong FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}

		ucCurrAVPFlags = *(pucStartOfCurrentAVP +unOffsetToFlagsInAVPHdr);

      
	    if (DMBase_Retval_Success !=  DMBase_IsAVPGrouped( hDiameterStackContext_io,
											unCurrAVPCode ,  &bIsAVPGrouped )
		   )
		{
	
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsAVPGrouped FAILED , Leaving .\n");
			oRetval=  DMBase_Retval_Failure;
			goto ExitMe;
		}


	    if( bIsAVPGrouped)
	    {
			 hGroupedAVP = NULL;

			 
             if (DMBase_Retval_Success !=   DMBase_CreateGroupedAVP(
						hDiameterStackContext_io , &hGroupedAVP,hMsgAllocCtxt_io, 
						unCurrAVPCode,ucCurrAVPFlags )
				)
			 {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_CreateGroupedAVP FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			 }

			 //set the things in the current grouped AVP header

			 if (DMBase_Retval_Success != DMBase_SetAVPLengthInAVPHeader(hDiameterStackContext_io,
											hGroupedAVP,unCurrentAVPSize)
				 )
			 {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPLengthInAVPHeader FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			 }
			
			 //	update size since group header has been processed
			 if (DMBASE_AVP_V_BIT_SET_MASK == (DMBASE_AVP_V_BIT_SET_MASK & hGroupedAVP->oAVPHeaderInst.ucFlags) )
			 {
				 unSizeofRawAVPList = (unCurrentAVPSize - DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES);
				  unIndexofParsedAVPList += DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES;
			 }
			 else
			 {
				 unSizeofRawAVPList = (unCurrentAVPSize - DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES);
				 unIndexofParsedAVPList += DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES;
			 }


			 //call recursively
             if (DMBase_Retval_Success !=   DMBase_ConvertRawAVPsToStructAVPCollection ( hDiameterStackContext_io ,
								 & ( hGroupedAVP->hCollectionOfAVPs ) , 
								 pucRawBuff_i,
								( unOffsetToListBegin_i + unIndexofParsedAVPList ) ,
								 unSizeofRawAVPList,hMsgAllocCtxt_io)
				)
			 {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_ConvertRawAVPsToStructAVPCollection FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			 }

			 if (DMBase_Retval_Success !=   DMBase_AddAVPToCollection(
							hDiameterStackContext_io,phCollOfAVPs_o,hGroupedAVP)
				)
			 {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AddAVPToCollection FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			 }

			 unIndexofParsedAVPList += unSizeofRawAVPList;

	    }//end if( bIsAVPGrouped)
        else
        {
			//AVP is not grouped 
			hAVP								= NULL;
			pAVPStructData						= NULL;
			unPadLen							= 0;
			t_AVPDictionaryElement	oDictElem	= {0};
			

			unsigned int	unTotalOffsetToAVPData = 0;

            if( DMBASE_AVP_V_BIT_IS_SET == (ucCurrAVPFlags & DMBASE_AVP_V_BIT_SET_MASK ) )
			{
				
                 unAVPDataSize = ( unCurrentAVPSize -  DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES );
				 unTotalOffsetToAVPData = unOffsetToListBegin_i + unIndexofParsedAVPList + DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES;
			}
			else
			{
				unAVPDataSize = ( unCurrentAVPSize -  DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES );
				unTotalOffsetToAVPData = unOffsetToListBegin_i + unIndexofParsedAVPList + DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES; 
			}

			t_DiamDictionary	oDictionary = {0};
	

			if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
											hDiameterStackContext_io,&oDictionary)
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			}
		
			if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray , 
													   unCurrAVPCode )
			   ) 
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			}


			oDictElem = oDictionary.poDictionaryArray[unCurrAVPCode];
			_Bool	bNeedPadCheck = 0;

			if (DMBase_Retval_Success !=   DMBase_IsTypeOctetStringOrDerived(
						hDiameterStackContext_io,unCurrAVPCode,&bNeedPadCheck)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsTypeOctetStringOrDerived FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			}

			//check for padding in case of OctetString
			if ( 1 == bNeedPadCheck )
			{
				if ( 0 == (unAVPDataSize  % DMBASE_NUM_OF_OCTETS_IN_32BIT) ) 
				{
					unPadLen = 0;
				}
				else
				{
					unPadLen = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unAVPDataSize % DMBASE_NUM_OF_OCTETS_IN_32BIT); 
				}
			}
			else
			{
				unPadLen = 0;
			}



			if (DMBase_Retval_Success !=  oDictElem.oAVPDictionaryFunctionPtrs.pfGetStructData(hDiameterStackContext_io,
													 pucRawBuff_i +   unTotalOffsetToAVPData ,
																   &pAVPStructData, 
																  unAVPDataSize ,hMsgAllocCtxt_io)
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pfGetStructData FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			}

			

			if (DMBase_Retval_Success !=   DMBase_CreateAVP ( hDiameterStackContext_io,
													&hAVP , 
													hMsgAllocCtxt_io,
												   unCurrAVPCode , 
												   pAVPStructData ,
												   unAVPDataSize,ucCurrAVPFlags)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pfGetStructData FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			}


			//setting fields in the current AVP header

			

			//set the vendor ID
			if( DMBASE_AVP_V_BIT_IS_SET == (ucCurrAVPFlags & DMBASE_AVP_V_BIT_SET_MASK ) )
            {   
				punTemp = (unsigned int * ) (pucStartOfCurrentAVP + unOffsetToVendorIDInAVPHdr);
				unTemp =  *punTemp;

				//TODO !! replace ntohl with amps wrappers!!!
				// 
				//unCurrAVPVendorID = ntohl ( unCurrAVPVendorID );

				if (DMBase_Retval_Success != DMBase_NetworkToHostLong(
					hDiameterStackContext_io,unTemp,(unsigned long *) &unCurrAVPVendorID)
		           )
				{
			
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostLong FAILED , Leaving .\n");
					oRetval=  DMBase_Retval_Failure;
					goto ExitMe;
				}

                if (DMBase_Retval_Success != DMBase_SetAVPVendorID( hDiameterStackContext_io ,
																hAVP ,
															   unCurrAVPVendorID)
				   )
				{
			
					DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPVendorID FAILED , Leaving .\n");
					oRetval=  DMBase_Retval_Failure;
					goto ExitMe;
				}
            }//end if V bit is set

			if (DMBase_Retval_Success !=   DMBase_AddAVPToCollection(
							hDiameterStackContext_io,phCollOfAVPs_o,hAVP)
				)
			 {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AddAVPToCollection FAILED , Leaving .\n");
				oRetval=  DMBase_Retval_Failure;
				goto ExitMe;
			 }
			
			 unIndexofParsedAVPList += unCurrentAVPSize ;
			 unIndexofParsedAVPList += unPadLen;

        } //end if not grouped
    }//end while

	ExitMe:

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return oRetval;
}

t_DiamAPIReturnVal  DMBase_IsAVPGrouped           ( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io, 
                                                    unsigned int                  unAVPCode_i ,
                                                    _Bool*                         pbIsAVPGrouped_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if ( NULL == hDiameterStackContext_io) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving\n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == pbIsAVPGrouped_o) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pbIsAVPGrouped_o is NULL , Leaving\n");
	  return DMBase_Retval_Null_Pointer;
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
											   unAVPCode_i )
	   ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}
	


    *pbIsAVPGrouped_o = oDictionary.poDictionaryArray[unAVPCode_i].bIsGrouped;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

    return DMBase_Retval_Success;
}
