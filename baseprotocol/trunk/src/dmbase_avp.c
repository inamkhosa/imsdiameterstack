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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "dmbase_avp.h"
#include "dmbase_dictionary.h"
#include "dmbase_ampswrappers.h"
#include<strings.h>

/* external */
extern	int							g_nDiamBaseTraceID ;


 /******************* Functions definition related to Diameter AVP***************/



t_DiamAPIReturnVal    DMBase_CreateAVP(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
										   HAVP*         		  phAVPHandle_o ,
										   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io,
										   unsigned int           unAVPCode_i ,
										   void*                  pvAVPData_i,
										   unsigned int 	      unDataSizeInBytes_i,
										   unsigned char		  ucFlags_i
										  )
{


    unsigned int    	unAVPLengthInBytes   = DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES + unDataSizeInBytes_i ;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");


	if (NULL == phAVPHandle_o)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phAVPHandle_o is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
	}

	if(NULL != *phAVPHandle_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *phAVPHandle_o is NOT NULL , Leaving \n");
        return DMBase_Retval_IncorrectParameters;
    }

	if(NULL == hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is  NULL , Leaving \n");
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
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

    if( DMBase_Retval_InvalidAVPData == oDictionary.poDictionaryArray[unAVPCode_i].oAVPDictionaryFunctionPtrs.pfValidateAVPData(hDiameterStackContext_io,
																					 pvAVPData_i ) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Error ! Valaidator function failed , leaving ! \n");
        return DMBase_Retval_InvalidAVPData;
    }



	if( DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
												   hMsgAllocCtxt_io,
								sizeof(t_AVP) ,(void**) phAVPHandle_o)
	  )
    {
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in Memory Allocation\n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	(*phAVPHandle_o)->hMsgAllocCtxt_io = hMsgAllocCtxt_io;

	if( DMBase_Retval_Success != DMBase_SetAVPCodeInAVPHeader(hDiameterStackContext_io,
									*phAVPHandle_o,unAVPCode_i)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPCodeInAVPHeader failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }


	unsigned char	ucFlags = ucFlags_i;

	//write flags here based on this AVPs dictionary element
	if (AVPFlagAction_Set == oDictionary.poDictionaryArray[unAVPCode_i].oMFlag.oFlagAction )
	{
		ucFlags = ucFlags | DMBASE_AVP_M_BIT_SET_MASK ;
	}

	if (AVPFlagAction_Set == oDictionary.poDictionaryArray[unAVPCode_i].oPFlag.oFlagAction )
	{
		ucFlags = ucFlags | DMBASE_AVP_P_BIT_SET_MASK ;
	}



	if( DMBase_Retval_Success != DMBase_SetFlagsOctetInAVPHeader (hDiameterStackContext_io,
									*phAVPHandle_o,ucFlags)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetFlagsOctetInAVPHeader failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	if( DMBase_Retval_Success !=  DMBase_SetAVPLengthInAVPHeader(hDiameterStackContext_io,
							*phAVPHandle_o , unAVPLengthInBytes)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPLengthInAVPHeader failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }



	if( DMBase_Retval_Success !=  DMBase_SetAVPData(hDiameterStackContext_io,
							*phAVPHandle_o , pvAVPData_i)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	(*phAVPHandle_o)->hDiameterStackContext = hDiameterStackContext_io;

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != *phAVPHandle_o)
		{
			if (DMBase_Retval_Success != DMBase_AVP_Free(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													 (void** ) phAVPHandle_o)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Free failed ,  \n");
			}
		}//end if (NULL != *phAVPHandle_o)

	}//end if (DMBase_Retval_Success != oRetval)


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

    return oRetval;

}


t_DiamAPIReturnVal   DMBase_SetAVPVendorID(HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
                                           HAVP           hAVPHandle_o ,
                                           unsigned int                unVendorID_i)
{

    unsigned int   unAVPLengthInBytes =0 ;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");


	if( NULL == hDiameterStackContext_io )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid parameter hDiameterStackContext_io\n");
        return	DMBase_Retval_Null_Pointer;
    }

    if( NULL == hAVPHandle_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid parameter hAVPHandle_o\n");
        return	DMBase_Retval_Null_Pointer;
    }

	if ( DMBase_Retval_Success !=  DMBase_SetVendorIdInAVPHeader(
								hDiameterStackContext_io,hAVPHandle_o,unVendorID_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetVendorIdInAVPHeader failed , leaving  \n");
        return	DMBase_Retval_Failure;
    }

	unsigned char	ucFlags = 0;

	if ( DMBase_Retval_Success !=   DMBase_GetFlagsOctetFromAVPHeader(
						hDiameterStackContext_io,hAVPHandle_o,&ucFlags)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_GetFlagsOctetFromAVPHeader failed , leaving  \n");
        return	DMBase_Retval_Failure;
    }

    ucFlags   |= DMBASE_AVP_V_BIT_SET_MASK;

	if ( DMBase_Retval_Success !=    DMBase_SetFlagsOctetInAVPHeader(
						hDiameterStackContext_io,hAVPHandle_o,ucFlags)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetFlagsOctetInAVPHeader failed , leaving  \n");
        return	DMBase_Retval_Failure;
    }

	if ( DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
			hAVPHandle_o ,&unAVPLengthInBytes)
	   )

	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_GetAVPLengthFromAVPHeader failed , leaving  \n");
        return	DMBase_Retval_Failure;
    }


	unAVPLengthInBytes += DMBASE_VENDOR_ID_SIZE_IN_BYTES;

	if( DMBase_Retval_Success !=  DMBase_SetAVPLengthInAVPHeader(hDiameterStackContext_io,
							hAVPHandle_o , unAVPLengthInBytes)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPLengthInAVPHeader failed , leaving \n");
       return DMBase_Retval_Failure;
    }

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");


    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_CreateGroupedAVP(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
                                            HAVP*          phGroupedAVPHandle_o,
											HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io,
                                            unsigned int                unGroupedAVPCode_i,
											unsigned char		  ucFlags_i)
{
    unsigned int    	unAVPLengthInBytes = DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES ;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if( NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL ,Leaving\n");
        return DMBase_Retval_Null_Pointer ;
    }

    if( NULL == phGroupedAVPHandle_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phGroupedAVPHandle_o is NULL ,Leaving\n");
        return DMBase_Retval_Null_Pointer ;
    }

	 if( NULL == hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL ,Leaving\n");
        return DMBase_Retval_Null_Pointer ;
    }

	if( NULL != (*phGroupedAVPHandle_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*phGroupedAVPHandle_o) is not NULL ,Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

    if( DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
									hMsgAllocCtxt_io,
								sizeof(t_AVP),(void**) phGroupedAVPHandle_o)
	  )
    {
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in Memory Allocation\n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	(*phGroupedAVPHandle_o)->hMsgAllocCtxt_io = hMsgAllocCtxt_io;

	if( DMBase_Retval_Success != DMBase_SetAVPCodeInAVPHeader(hDiameterStackContext_io,
									*phGroupedAVPHandle_o,unGroupedAVPCode_i)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPCodeInAVPHeader failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }


	unsigned char ucFlags = ucFlags_i;

    t_DiamDictionary	oDictionary = {0};


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext_io,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unGroupedAVPCode_i )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}

	if (AVPFlagAction_Set == oDictionary.poDictionaryArray[unGroupedAVPCode_i].oMFlag.oFlagAction )
	{
		ucFlags = ucFlags | DMBASE_AVP_M_BIT_SET_MASK ;
	}

	if (AVPFlagAction_Set == oDictionary.poDictionaryArray[unGroupedAVPCode_i].oPFlag.oFlagAction )
	{
		ucFlags = ucFlags | DMBASE_AVP_P_BIT_SET_MASK ;
	}


    if( DMBase_Retval_Success != DMBase_SetFlagsOctetInAVPHeader (hDiameterStackContext_io,
									*phGroupedAVPHandle_o,ucFlags)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetFlagsOctetInAVPHeader failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	if( DMBase_Retval_Success !=  DMBase_SetAVPLengthInAVPHeader(hDiameterStackContext_io,
							*phGroupedAVPHandle_o , unAVPLengthInBytes)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPLengthInAVPHeader failed , leaving \n");
        oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
    }

	(*phGroupedAVPHandle_o)->hDiameterStackContext = hDiameterStackContext_io;

    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unGroupedAVPCode_i].unVendorID)
    {
        DMBase_SetAVPVendorID(hDiameterStackContext_io, *phGroupedAVPHandle_o, oDictionary.poDictionaryArray[unGroupedAVPCode_i].unVendorID);
    }

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != *phGroupedAVPHandle_o)
		{
			if (DMBase_Retval_Success != DMBase_AVP_Free (hDiameterStackContext_io,
                                                    hMsgAllocCtxt_io,
													 (void**) phGroupedAVPHandle_o)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Free failed ,  \n");
			}
		}//end if (NULL != *phGroupedAVPHandle_o)

	}//end if (DMBase_Retval_Success != oRetval)


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

    return oRetval;
}


t_DiamAPIReturnVal   DMBase_AddAVPToGroup( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
                                           HAVP           hGroupedAVP_o,
                                           HAVP           hAVPToAdd_i )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if( NULL == hDiameterStackContext_io )
    {
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	 if(  NULL == hGroupedAVP_o  )
    {
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hGroupedAVP_o is NULL ,leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == hAVPToAdd_i )
    {
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hAVPToAdd_i is NULL , leaving \n");
        return DMBase_Retval_Null_Pointer;
    }



    if( DMBase_Retval_Success != DMBase_AddAVPToCollection(hDiameterStackContext_io,
									&(hGroupedAVP_o->hCollectionOfAVPs),hAVPToAdd_i)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AddAVPToCollection Failed , Leaving \n");
       return DMBase_Retval_Failure;
	}

	t_AVPDictionaryElement	oDicElem = {0};
	unsigned int			unAVPLen = 0;
	unsigned int			unPadLen = 0;
	unsigned int			unAVPDataSize = 0;
	_Bool					bIsAVPGrouped = 0;

    t_DiamDictionary	oDictionary = {0};

	unsigned int	unAVPCode = (hAVPToAdd_i->oAVPHeaderInst).unAVPCode;


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext_io,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unAVPCode )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}


	oDicElem = oDictionary.poDictionaryArray[unAVPCode];

	if( DMBase_Retval_Success !=  DMBase_IsAVPGrouped(hDiameterStackContext_io,
						unAVPCode,
						&bIsAVPGrouped)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsAVPGrouped Failed , Leaving \n");
       return DMBase_Retval_Failure;
	}



	if( DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
							hAVPToAdd_i,&unAVPLen)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetAVPLengthFromAVPHeader Failed , Leaving \n");
       return DMBase_Retval_Failure;
	}


	if (DMBASE_AVP_V_BIT_IS_SET == (DMBASE_AVP_V_BIT_SET_MASK & (hAVPToAdd_i->oAVPHeaderInst.ucFlags) ) )
	{
		unAVPDataSize = unAVPLen - DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES;
	}
	else
	{
		unAVPDataSize = unAVPLen - DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES;
	}

	if (0 == bIsAVPGrouped)
	{
		_Bool	bNeedToCheckPad = 0;

		if( DMBase_Retval_Success !=   DMBase_IsTypeOctetStringOrDerived(hDiameterStackContext_io,
										  (hAVPToAdd_i->oAVPHeaderInst).unAVPCode,
										  &bNeedToCheckPad)
		  )
		{
		   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsTypeOctetStringOrDerived Failed , Leaving \n");
		   return DMBase_Retval_Failure;
		}

		if ( 1 == bNeedToCheckPad)
		{
			//check for padding requirement
			if ( 0 == (unAVPDataSize % DMBASE_NUM_OF_OCTETS_IN_32BIT) )
			{
				unPadLen = 0;
			}
			else
			{
				unPadLen = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unAVPDataSize % DMBASE_NUM_OF_OCTETS_IN_32BIT);
			}
		}// end if data type is octet string
		else
		{
			unPadLen = 0;
		}
	}// end if AVP is not grouped
	else
	{
		//AVP to add is grouped padding taken care of elsewhere
		unPadLen = 0;
	}

	//updating the length field of the grouped AVP
	unsigned int	unGroupAVPLen = 0;

    if( DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
							hGroupedAVP_o,&unGroupAVPLen)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetAVPLengthFromAVPHeader Failed , Leaving \n");
       return DMBase_Retval_Failure;
	}



	unGroupAVPLen  += unAVPLen;
	unGroupAVPLen += unPadLen;

    if( DMBase_Retval_Success !=  DMBase_SetAVPLengthInAVPHeader(hDiameterStackContext_io,
							hGroupedAVP_o , unGroupAVPLen)
	  )
	{
       DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetAVPLengthInAVPHeader failed , leaving \n");
        return  DMBase_Retval_Failure;
    }


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");



    return DMBase_Retval_Success;
}




 t_DiamAPIReturnVal DMBase_DestroyAVP ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                        HAVP*          phAVP_i)
{


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phAVP_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! phAVP_i is NULL , Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == (*phAVP_i) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! *phAVP_i is NULL , Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	HAVP				hAVP = *phAVP_i;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;
	HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io = hAVP->hMsgAllocCtxt_io;


	_Bool	bIsAVPGrouped;

	if ( DMBase_Retval_Success !=   DMBase_IsAVPGrouped(hDiameterStackContext_io,
					    (hAVP->oAVPHeaderInst).unAVPCode,&bIsAVPGrouped)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_IsAVPGrouped FAILED , Leaving\n");
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}


	if ( bIsAVPGrouped )
	{
		if (NULL == hAVP->hCollectionOfAVPs )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hAVP->hCollectionOfAVPs is NULL , Leaving\n");
			oRetval = DMBase_Retval_Null_Pointer;
			goto ExitMe;
		}
		else
		{
			//recursive call
			if ( DMBase_Retval_Success !=    DMBase_DestroyAVPCollection(
							hDiameterStackContext_io , &(hAVP->hCollectionOfAVPs) )
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_DestroyAVPList FAILED , Leaving\n");
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}
		}
	}//end if ( bIsAVPGrouped
	else
	{
		//AVP is not grouped

		if ( NULL == hAVP->pData)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," hAVP->pData is NULL , no need to free memory \n");
		}
		else
		{
			t_AVPDictionaryElement	oAVPDictElem = {0};
            t_DiamDictionary		oDictionary = {0};
			unsigned int			unAVPCode = (hAVP->oAVPHeaderInst).unAVPCode;

			if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
											hDiameterStackContext_io,&oDictionary)
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}

			if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
													   unAVPCode )
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}



			HMSGALLOCATIONCONTEXT	hMsgAllocCtxt = hAVP->hMsgAllocCtxt_io;
			oAVPDictElem =  oDictionary.poDictionaryArray[ (hAVP->oAVPHeaderInst).unAVPCode];
			if ( DMBase_Retval_Success != oAVPDictElem.oAVPDictionaryFunctionPtrs.pfAVPDeAlloc(hDiameterStackContext_io,
														&(hAVP->pData),hMsgAllocCtxt )
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pfAVPDeAlloc FAILED , Leaving\n");
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}
			hAVP->pData = NULL;
		}// else if hAVP->pData is not NULL

	}

	ExitMe:

	//delete the actual AVP struct mem
	if ( DMBase_Retval_Success !=  DMBase_AVP_Free(hDiameterStackContext_io,
									hMsgAllocCtxt_io, (void*) phAVP_i) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_AVP_Free FAILED , Leaving\n");

	}


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return oRetval;
}


t_DiamAPIReturnVal  DMBase_ConvertAVPCollectionToRawForm ( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io ,
												 unsigned char  ** ppRawDiameterMsg_o ,
												 HAVPCOLLECTION		hCollOfAVPs_i,
												 unsigned int unoffsetToWriteBuff_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL, Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hCollOfAVPs_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hCollOfAVPs_i is NULL , Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == ppRawDiameterMsg_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! ppRawDiameterMsg_o is NULL , Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}




	unsigned int 		unCurrOffset = 0;
	unsigned int 		unCurrAVPSize = 0;
	HAVP				hCurrAVP = NULL;
	void*				pData = NULL;
	DMBase_SList* 		pCurrentNode = (DMBase_SList*) hCollOfAVPs_i;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	unCurrOffset += unoffsetToWriteBuff_i;


	unsigned int			unPadLen =0;
	_Bool					bIsCurrAVPGrouped = 0;
	t_AVPDictionaryElement	oDicElem = {0};
	unsigned int			unCurrAVPDataSize = 0;

	while (NULL != pCurrentNode)
	{
		unPadLen = 0;
		bIsCurrAVPGrouped = 0;
		unCurrAVPDataSize = 0;

		if (DMBase_Retval_Success != DMBase_SListGetNodeData(hDiameterStackContext_io,
												pCurrentNode, &pData)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_SListGetNodeData FAILED , Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		hCurrAVP = ( HAVP) pData;


		if (DMBase_Retval_Success !=  DMBase_IsAVPGrouped(hDiameterStackContext_io,
							(hCurrAVP->oAVPHeaderInst).unAVPCode,
							&bIsCurrAVPGrouped)
			)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_IsAVPGrouped FAILED for AVP code = %d, Leaving\n",(hCurrAVP->oAVPHeaderInst).unAVPCode);
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		unsigned int	unAVPCode = (hCurrAVP->oAVPHeaderInst).unAVPCode;

        t_DiamDictionary	oDictionary = {0};


		if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
										hDiameterStackContext_io,&oDictionary)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
												   unAVPCode )
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed for AVP code = %d, Leaving \n",unAVPCode);
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}



		oDicElem = oDictionary.poDictionaryArray[unAVPCode];


        if( DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
							hCurrAVP,&unCurrAVPSize)
	       )
		{
		   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetAVPLengthFromAVPHeader Failed , Leaving \n");
		   oRetval =  DMBase_Retval_Failure;
		   goto ExitMe;
		}



        if (DMBase_Retval_Success !=   DMBase_ConvertAVPToRaw(
				hDiameterStackContext_io,hCurrAVP,ppRawDiameterMsg_o, unCurrOffset)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_ConvertAVPToRaw FAILED for AVP code == %d , Leaving\n",hCurrAVP->oAVPHeaderInst.unAVPCode);
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		if ( 0 == bIsCurrAVPGrouped)
		{
			_Bool	bNeedToCheckPad = 0;

			if (DMBase_Retval_Success !=   DMBase_IsTypeOctetStringOrDerived(hDiameterStackContext_io,
											  (hCurrAVP->oAVPHeaderInst).unAVPCode,
											  &bNeedToCheckPad )
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_IsTypeOctetStringOrDerived FAILED for AVP code = %d, Leaving\n",(hCurrAVP->oAVPHeaderInst).unAVPCode);
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}

			if ( 1 == bNeedToCheckPad )
			{
				if (DMBASE_AVP_V_BIT_IS_SET == (DMBASE_AVP_V_BIT_SET_MASK & (hCurrAVP->oAVPHeaderInst.ucFlags) ) )
				{
					unCurrAVPDataSize = unCurrAVPSize - DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES;
				}
				else
				{
					unCurrAVPDataSize = unCurrAVPSize - DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES;
				}
				//check for padding requirement
				if ( 0 == (unCurrAVPDataSize  % DMBASE_NUM_OF_OCTETS_IN_32BIT) )
				{
					unPadLen = 0;
				}
				else
				{
					unPadLen = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unCurrAVPDataSize % DMBASE_NUM_OF_OCTETS_IN_32BIT);
				}
			}//end if ( 1 == bNeedToCheckPad )
			else
			{
				unPadLen = 0;
			}
		}//if ( 0 == bIsCurrAVPGrouped)
		else
		{
			//padding length is already included in the grouped avp header length field
			unPadLen = 0;
		}

		unCurrOffset += unCurrAVPSize;
		//need to include padding size here if required
		unCurrOffset +=  unPadLen;

		if (DMBase_Retval_Success != DMBase_SListGetNextNode( hDiameterStackContext_io ,
										pCurrentNode , &pCurrentNode)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_SListGetNextNode FAILED , Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}
	}//end while (NULL != pCurrentNode)

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != (*ppRawDiameterMsg_o))
		{
			if (DMBase_Retval_Success != DMBase_Free(hDiameterStackContext_io,
													 (void**) ppRawDiameterMsg_o)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_Free FAILED \n");
			}

		}//end if (NULL != (*ppRawDiameterMsg_o))
	}//end if (DMBase_Retval_Success != oRetval)

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return oRetval;
}
t_DiamAPIReturnVal	DMBase_ConvertAVPToRaw ( HDIAMETERSTACKCONTEXT  hDiameterStackContext_io,
											 HAVP hAVPToConvert_i,
											 unsigned char** ppRawBuff_o ,
											 unsigned int unOffsetToWriteBuff_i )

{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL, Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hAVPToConvert_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hAVPToConvert_i is NULL, Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == ppRawBuff_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppRawBuff_o is NULL, Leaving\n");
		return DMBase_Retval_Null_Pointer;
	}




	_Bool				bIsAVPGrouped ;
	unsigned int		unAVPLength =0;
	unsigned int		unAVPDataSize = 0;
	t_AVPHeader			oAVPHeader = {0};
	unsigned char*		pucBuff = NULL;
	unsigned int 		unTempIndex = unOffsetToWriteBuff_i;
	unsigned int * 		punTempIntPtr = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;



	if (DMBase_Retval_Success !=  DMBase_IsAVPGrouped(hDiameterStackContext_io ,
						(hAVPToConvert_i->oAVPHeaderInst).unAVPCode  ,
						 &bIsAVPGrouped)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_IsAVPGrouped Failed for AVP code => %d, Leaving\n",(hAVPToConvert_i->oAVPHeaderInst).unAVPCode);
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}


	if ( bIsAVPGrouped )
	{

		//write the Grouped AVP Header first

		oAVPHeader = hAVPToConvert_i->oAVPHeaderInst;
		pucBuff = *ppRawBuff_o;

		//writing 4 octets AVP code

		punTempIntPtr = ( unsigned int *) ( pucBuff+ unTempIndex );
		//*punTempIntPtr = htonl ( oAVPHeader.unAVPCode );

		if (DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,
									oAVPHeader.unAVPCode,(unsigned long * ) punTempIntPtr)
			)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_HostToNetworkLong Failed, Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		unTempIndex+= 4;

		//writing one octet AVP flags
		pucBuff[unTempIndex] = oAVPHeader.ucFlags;
		unTempIndex++;

		//writing three octets  of AVP length

		unsigned char	pucTemp[3] = {0};
		if (DMBase_Retval_Success !=  DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder(
										oAVPHeader.unAVPLength,pucTemp)
			)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder Failed, Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		pucBuff[unTempIndex] = pucTemp[0];
		unTempIndex++;

		pucBuff[unTempIndex] = pucTemp[1];
		unTempIndex++;

		pucBuff[unTempIndex] = pucTemp[2];
		unTempIndex++;

		//write optional vendorID four octets if V bit is set in flags
		if (DMBASE_AVP_V_BIT_IS_SET == (oAVPHeader.ucFlags & DMBASE_AVP_V_BIT_SET_MASK ))
		{
			punTempIntPtr = ( unsigned int *) (  pucBuff+ unTempIndex );
			//*punTempIntPtr = htonl ( oAVPHeader.unVendorID );
			if (DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,
									oAVPHeader.unVendorID,(unsigned long *) punTempIntPtr)
			)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_HostToNetworkLong Failed, Leaving\n");
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}
			unTempIndex+= 4;
		}



        if( DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
	 						hAVPToConvert_i,&unAVPLength)
	      )
		{
		   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetAVPLengthFromAVPHeader Failed , Leaving \n");
		   oRetval =  DMBase_Retval_Failure;
		   goto ExitMe;
		}




		//convert the AVPs in this Grouped AVP to Raw now
		if (DMBase_Retval_Success !=  DMBase_ConvertAVPCollectionToRawForm(
					hDiameterStackContext_io ,ppRawBuff_o,
									   hAVPToConvert_i->hCollectionOfAVPs ,
									    unTempIndex)
			)

		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertAVPCollectionToRawForm Failed for grouped AVP code = %d , Leaving\n",hAVPToConvert_i->oAVPHeaderInst.unAVPCode);
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

	} // end if AVP is grouped
	else
	{
		//AVP is not grouped

		//write AVP header first

		oAVPHeader = hAVPToConvert_i->oAVPHeaderInst;
		pucBuff = *ppRawBuff_o;

		//writing 4 octets AVP code

		punTempIntPtr = ( unsigned int *) ( pucBuff+ unTempIndex );
		//*punTempIntPtr = htonl ( oAVPHeader.unAVPCode );
		if (DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,
									oAVPHeader.unAVPCode,(unsigned long*) punTempIntPtr)
			)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_HostToNetworkLong Failed, Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		unTempIndex+= 4;

		//writing one octet AVP flags
		pucBuff[unTempIndex] = oAVPHeader.ucFlags;
		unTempIndex++;

		//writing three octets  of AVP length

		unsigned char pucTemp[3] = {0};
		if (DMBase_Retval_Success !=  DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder(
										oAVPHeader.unAVPLength,pucTemp)
			)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder Failed, Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}



		pucBuff[unTempIndex] = pucTemp[0];
		unTempIndex++;

		pucBuff[unTempIndex] = pucTemp[1];
		unTempIndex++;

		pucBuff[unTempIndex] = pucTemp[2];
		unTempIndex++;

		//write optional vendorID four octets if V bit is set in flags
		if (DMBASE_AVP_V_BIT_IS_SET == (oAVPHeader.ucFlags & DMBASE_AVP_V_BIT_SET_MASK ))
		{
			punTempIntPtr = ( unsigned int *) (  pucBuff+ unTempIndex );
			//*punTempIntPtr = htonl ( oAVPHeader.unVendorID );
			if (DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,
									oAVPHeader.unVendorID,(unsigned long*) punTempIntPtr)
			)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_HostToNetworkLong Failed, Leaving\n");
				oRetval =  DMBase_Retval_Failure;
				goto ExitMe;
			}
			unTempIndex+= 4;
		}

        unAVPLength =0;
		unAVPDataSize = 0;




        if( DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
							 hAVPToConvert_i,&unAVPLength)
	      )
		{
		   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetAVPLengthFromAVPHeader Failed , Leaving \n");
		   oRetval =  DMBase_Retval_Failure;
		   goto ExitMe;
		}


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
		t_AVPDictionaryElement	oAVPDictElem = {0};

        t_DiamDictionary	oDictionary = {0};
		unsigned int		unAVPCode = oAVPHeader.unAVPCode;


		if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
										hDiameterStackContext_io,&oDictionary)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

		if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
												   unAVPCode )
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed for AVP code = %d , Leaving \n",unAVPCode);
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}


		oAVPDictElem =  oDictionary.poDictionaryArray[ unAVPCode ];


		if (DMBase_Retval_Success !=   oAVPDictElem.oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory(hDiameterStackContext_io,
												 pucBuff+unTempIndex,
												hAVPToConvert_i->pData,
												unAVPDataSize)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pfWriteRawDataToMemory Failed for AVP code = %d, Leaving\n",unAVPCode);
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}

	}//end else if AVP is not grouped

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != (*ppRawBuff_o))
		{
			if (DMBase_Retval_Success != DMBase_Free(hDiameterStackContext_io,
													 (void**) ppRawBuff_o)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_Free FAILED \n");
			}

		}//end if (NULL != (*ppRawDiameterMsg_o))
	}//end if (DMBase_Retval_Success != oRetval)

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return oRetval;
}

t_DiamAPIReturnVal DMBase_CreateIntAVP(	HDIAMETERSTACKCONTEXT 	hDiameterStackContext,
										unsigned int 			unAVPCode,
										HAVP* 					phIntAVP,
										int 					nIntValue,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamInteger32* 	poIntAVPValue = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

    t_DiamDictionary	oDictionary = {0};


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unAVPCode )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}


    if (DMBase_Retval_Success != oDictionary.poDictionaryArray[unAVPCode].oAVPDictionaryFunctionPtrs.pfAVPAlloc(
								   hDiameterStackContext, (void**)&poIntAVPValue, sizeof(int),hMsgAllocCtxt_io)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_IsAVPGrouped Failed, Leaving\n");
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}

	*(poIntAVPValue->pnInteger32) = nIntValue;

    if (DMBase_Retval_Success !=   DMBase_CreateAVP(hDiameterStackContext, phIntAVP,hMsgAllocCtxt_io, unAVPCode, poIntAVPValue,
                          poIntAVPValue->unNumOfOctets,DMBASE_DEFAULT_FLAGS_VALUE )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_CreateAVP Failed, Leaving\n");
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}


    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unAVPCode].unVendorID)
    {
        if (DMBase_Retval_Success !=   DMBase_SetAVPVendorID(hDiameterStackContext,
						*phIntAVP, oDictionary.poDictionaryArray[unAVPCode].unVendorID)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_CreateAVP Failed, Leaving\n");
			oRetval =  DMBase_Retval_Failure;
			goto ExitMe;
		}
    }

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poIntAVPValue)
		{
			if (DMBase_Retval_Success !=DMBase_AVP_Free(hDiameterStackContext,hMsgAllocCtxt_io,
											(void**) poIntAVPValue)
			    )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_AVP_Free Failed \n");
			}
		}
	}//end if (DMBase_Retval_Success != oRetval)

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_CreateInteger64AVP(HDIAMETERSTACKCONTEXT 	hDiameterStackContext,
											 unsigned int 			unAVPCode,
											 HAVP* 					phInteger64AVP,
											 long long 				llInteger64Value,
											 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamInteger64* poInteger64AVPValue = NULL;
    t_DiamDictionary	oDictionary = {0};


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unAVPCode )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

    oDictionary.poDictionaryArray[unAVPCode].oAVPDictionaryFunctionPtrs.pfAVPAlloc(hDiameterStackContext,(void**)&poInteger64AVPValue, sizeof(long long),hMsgAllocCtxt_io);
    *(poInteger64AVPValue->pllInteger64) = llInteger64Value;

    DMBase_CreateAVP(hDiameterStackContext, phInteger64AVP, hMsgAllocCtxt_io, unAVPCode, poInteger64AVPValue,
                          poInteger64AVPValue->unNumOfOctets, DMBASE_DEFAULT_FLAGS_VALUE);
    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unAVPCode].unVendorID)
    {
        DMBase_SetAVPVendorID(hDiameterStackContext, *phInteger64AVP, oDictionary.poDictionaryArray[unAVPCode].unVendorID);
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_CreateUnsigned32AVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phUnsigned32AVP, unsigned int unUnsigned32Value,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamUnsigned32* poUnsigned32AVPValue = NULL;

    t_DiamDictionary	oDictionary = {0};


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unAVPCode )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

    oDictionary.poDictionaryArray[unAVPCode].oAVPDictionaryFunctionPtrs.pfAVPAlloc(hDiameterStackContext,(void**)&poUnsigned32AVPValue, sizeof(unsigned int),hMsgAllocCtxt_io);
    *(poUnsigned32AVPValue->punUnsigned32) = unUnsigned32Value;

    DMBase_CreateAVP(hDiameterStackContext, phUnsigned32AVP, hMsgAllocCtxt_io, unAVPCode, poUnsigned32AVPValue,
                          poUnsigned32AVPValue->unNumOfOctets, DMBASE_DEFAULT_FLAGS_VALUE);
    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unAVPCode].unVendorID)
    {
        DMBase_SetAVPVendorID(hDiameterStackContext, *phUnsigned32AVP, oDictionary.poDictionaryArray[unAVPCode].unVendorID);
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_CreateUnsigned64AVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phUnsigned64AVP, unsigned long long unUnsigned64Value,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamUnsigned64* poUnsigned64AVPValue = NULL;
    t_DiamDictionary	oDictionary = {0};


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unAVPCode )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

    oDictionary.poDictionaryArray[unAVPCode].oAVPDictionaryFunctionPtrs.pfAVPAlloc(hDiameterStackContext,(void**)&poUnsigned64AVPValue, sizeof(unsigned long long),hMsgAllocCtxt_io);
    *(poUnsigned64AVPValue->pullUnsigned64) = unUnsigned64Value;

    DMBase_CreateAVP(hDiameterStackContext, phUnsigned64AVP, hMsgAllocCtxt_io, unAVPCode, poUnsigned64AVPValue,
                          poUnsigned64AVPValue->unNumOfOctets, DMBASE_DEFAULT_FLAGS_VALUE);
    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unAVPCode].unVendorID)
    {
        DMBase_SetAVPVendorID(hDiameterStackContext, *phUnsigned64AVP, oDictionary.poDictionaryArray[unAVPCode].unVendorID);
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_CreateEnumAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phEnumAVP, int nEnumValue,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");
    DMBase_CreateIntAVP(hDiameterStackContext, unAVPCode, phEnumAVP, nEnumValue,hMsgAllocCtxt_io);
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_CreateOctetStringAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phOctetstringAVP,
                                        unsigned char* pucOctetString, unsigned int unSize,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

    HAVP hSIPAuthorization  = NULL;

    t_DiamOctetString* poOctetStrValue = NULL;


    t_DiamDictionary	oDictionary = {0};


	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext,&oDictionary)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
        return DMBase_Retval_Failure;
    }

	if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray ,
											   unAVPCode )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

    oDictionary.poDictionaryArray[unAVPCode].oAVPDictionaryFunctionPtrs.pfAVPAlloc(hDiameterStackContext , (void**)&poOctetStrValue, unSize,hMsgAllocCtxt_io);

    memcpy(poOctetStrValue->pucOctetString, pucOctetString, unSize);

    DMBase_CreateAVP(hDiameterStackContext, phOctetstringAVP, hMsgAllocCtxt_io, unAVPCode, poOctetStrValue,
                                    poOctetStrValue->unNumOfOctets,DMBASE_DEFAULT_FLAGS_VALUE);

    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unAVPCode].unVendorID)
    {
            DMBase_SetAVPVendorID(hDiameterStackContext, *phOctetstringAVP,
                      oDictionary.poDictionaryArray[unAVPCode].unVendorID);
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_CreateUTF8StringAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext, unsigned int unAVPCode, HAVP* phUTF8StringAVP,
                                        unsigned char* pucUTF8String, unsigned int unSize,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");
    if(NULL == hDiameterStackContext || NULL == phUTF8StringAVP || NULL == pucUTF8String)
    {
            DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " NULL Pointer Error\n");
            return DMBase_Retval_Null_Pointer;
    }

    t_DiamAPIReturnVal oReturnValue = DMBase_CreateOctetStringAVP(hDiameterStackContext, unAVPCode, phUTF8StringAVP, pucUTF8String, unSize,hMsgAllocCtxt_io);
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;
}

t_DiamAPIReturnVal DMBase_GetAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, unsigned int unAVPCode, HDIAMETERMESSAGE hDiamMsg_i ,HAVP* phAVP_io)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBase_SList* pListOfAVPs = NULL;
     void* pData = NULL;
     HAVP  hTempAVP = NULL;
     pListOfAVPs = (DMBase_SList*) hDiamMsg_i->hCollectionOfAVPs;
     DMBase_SList* pHeadNode = NULL;


     for(pHeadNode = pListOfAVPs; NULL != pHeadNode; DMBase_SListGetNextNode(hDiameterStackContext_io, pHeadNode, &pHeadNode))
     {

         DMBase_SListGetNodeData(hDiameterStackContext_io, pHeadNode, &pData);
         hTempAVP = (HAVP)pData;
         if(unAVPCode == hTempAVP->oAVPHeaderInst.unAVPCode)
         {
             *phAVP_io = hTempAVP;
             return DMBase_Retval_Success;
         }

     }
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Not_Found;
}

t_DiamAPIReturnVal DMBase_GetAVPFromGroup(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, unsigned int unAVPCode, HAVP hGroupedAVP ,HAVP* phAVP_io)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBase_SList* pListOfAVPs = NULL;
     void* pData = NULL;
     HAVP  hTempAVP = NULL;
     pListOfAVPs = (DMBase_SList*) hGroupedAVP->hCollectionOfAVPs;
     DMBase_SList* pHeadNode = NULL;


     for(pHeadNode = pListOfAVPs; NULL != pHeadNode; DMBase_SListGetNextNode(hDiameterStackContext_io, pHeadNode, &pHeadNode))
     {

         DMBase_SListGetNodeData(hDiameterStackContext_io, pHeadNode, &pData);
         hTempAVP = (HAVP)pData;
         if(unAVPCode == hTempAVP->oAVPHeaderInst.unAVPCode)
         {
             *phAVP_io = hTempAVP;
             return DMBase_Retval_Success;
         }

     }
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Not_Found;
}

t_DiamAPIReturnVal DMBase_GetAVPList(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, unsigned int unAVPCode, HDIAMETERMESSAGE hDiamMsg_i , DMBase_SList** ppListOfAVPs)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBase_SList* pListOfAVPs = NULL;
     void* pData = NULL;
     HAVP  hTempAVP = NULL;
     pListOfAVPs = (DMBase_SList*) hDiamMsg_i->hCollectionOfAVPs;
     DMBase_SList* pHeadNode = NULL;
     _Bool bFound = 0;

     for(pHeadNode = pListOfAVPs; NULL != pHeadNode; DMBase_SListGetNextNode(hDiameterStackContext_io, pHeadNode, &pHeadNode))
     {

         DMBase_SListGetNodeData(hDiameterStackContext_io, pHeadNode, &pData);
         hTempAVP = (HAVP)pData;
         if(unAVPCode == hTempAVP->oAVPHeaderInst.unAVPCode)
         {
             //*phAVP_io = hTempAVP;
             DMBase_AppendSList(hDiameterStackContext_io, ppListOfAVPs, pData);
             bFound = 1;
//             return DMBase_Retval_Success;
         }

     }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    if(bFound)
    {
         return DMBase_Retval_Success;
    }
    else
    {
        return DMBase_Retval_Not_Found;
    }
}

t_DiamAPIReturnVal DMBase_DuplicateAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
									   HAVP hOrignalAVP_i, HAVP* phNewAVP_o)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hOrignalAVP_i )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hOrignalAVP_i is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phNewAVP_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! phNewAVP_o is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*phNewAVP_o) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! (*phNewAVP_o) is NOT NULL , Leaving \n");
		return DMBase_Retval_IncorrectParameters;
	}

	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	unsigned char*	pucTempBuff = NULL;

	if ( DMBase_Retval_Success != DMBase_ConvertAVPToRaw(hDiameterStackContext_io,
										hOrignalAVP_i,&pucTempBuff,0)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertAVPToRaw Failed , Leaving \n");
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	ExitMe:

	if (NULL != pucTempBuff)
	{
		if ( DMBase_Retval_Success !=  DMBase_Free(hDiameterStackContext_io,(void**)&pucTempBuff))
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_Free Failed , Leaving \n");
        }
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oRetval;
}


int	DMBase_CallBack_FreeAVPNodeInAVPList(void** r_ppvData)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == r_ppvData )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " r_ppvData is NULL .\n");
		return AMPS_ERROR_FAILURE;
	}

	if (NULL == (*r_ppvData) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " No data in current node of AVP List to delete .\n");
		return AMPS_SUCCESS;
	}

	HDIAMETERSTACKCONTEXT	hDiamStackContext = NULL;

	HAVP	hAVP = (HAVP) *r_ppvData;

	hDiamStackContext = hAVP->hDiameterStackContext;

	if (DMBase_Retval_Success !=  DMBase_DestroyAVP(hDiamStackContext,&hAVP))
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_DestroyAVP Failed  .\n");
		return AMPS_ERROR_FAILURE;
	}


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return AMPS_SUCCESS;
}

t_DiamAPIReturnVal	DMBase_AddAVPToCollection(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											  HAVPCOLLECTION*	phCollOfAVPs_o,
											  HAVP hAVPToAdd_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phCollOfAVPs_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phCollOfAVPs_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPToAdd_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPToAdd_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}



	if (DMBase_Retval_Success != DMBase_AppendSList(hDiameterStackContext_io,
										(DMBase_SList**) phCollOfAVPs_o, (void*)hAVPToAdd_i)
		)
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Function Failed .\n");
		return DMBase_Retval_Failure;
	}

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


	return DMBase_Retval_Success;

}

t_DiamAPIReturnVal  DMBase_DestroyAVPCollection  (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                            HAVPCOLLECTION*   phCollOfAVPs_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phCollOfAVPs_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phCollOfAVPs_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if ( DMBase_Retval_Success !=  DMBase_SListFree( hDiameterStackContext_io,
					(DMBase_SList**)phCollOfAVPs_io,DMBase_CallBack_FreeAVPNodeInAVPList )
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_SListFree FAILED  ! \n");
		return DMBase_Retval_Failure;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetVendorIdInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int            unVendorID_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	hAVPHandle_o->oAVPHeaderInst.unVendorID = unVendorID_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetAVPCodeInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int            unAVPCode_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	hAVPHandle_o->oAVPHeaderInst.unAVPCode = unAVPCode_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetFlagsOctetInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned char           ucFlags_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	hAVPHandle_o->oAVPHeaderInst.ucFlags = ucFlags_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetAVPLengthInAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                unsigned int            unAVPLen_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (unAVPLen_i > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " unAVPLen_i == %d > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS .\n",unAVPLen_i);
		return DMBase_Retval_IncorrectParameters;
	}

	hAVPHandle_o->oAVPHeaderInst.unAVPLength= unAVPLen_i;



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetVendorIdFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_i ,
                                unsigned int*           punVendorID_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punVendorID_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punVendorID_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}



	*punVendorID_o = hAVPHandle_i->oAVPHeaderInst.unVendorID;



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetAVPCodeFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_i ,
                                unsigned int*            punAVPCode_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punAVPCode_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punAVPCode_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}


	*punAVPCode_o = hAVPHandle_i->oAVPHeaderInst.unAVPCode;


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetFlagsOctetFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_i ,
                                unsigned char*          pucFlags_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pucFlags_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pucFlags_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}


	*pucFlags_o = hAVPHandle_i->oAVPHeaderInst.ucFlags;


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetAVPLengthFromAVPHeader  (
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_i ,
                                unsigned int*            punAVPLen_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punAVPLen_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punAVPLen_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}


	*punAVPLen_o = hAVPHandle_i->oAVPHeaderInst.unAVPLength;


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetAVPData(
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_o ,
                                void*            		pvAVPData_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}


	hAVPHandle_o->pData = pvAVPData_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}




t_DiamAPIReturnVal  DMBase_GetAVPData(
								HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                HAVP		            hAVPHandle_i ,
                                void**            		ppvAVPData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hAVPHandle_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPHandle_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppvAVPData_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppvAVPData_o is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppvAVPData_o) )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppvAVPData_o is NOT NULL .\n");
		return DMBase_Retval_IncorrectParameters;
	}



	*ppvAVPData_o =   hAVPHandle_i->pData;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return DMBase_Retval_Success;
}
t_DiamAPIReturnVal DMBase_CreateIPAddressAVP(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
										unsigned int unAVPCode_i, HAVP* phIPAddrAVP_o,
                                        unsigned char* pucIPString_i, unsigned short usIPType_i,
                                        HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");



    t_DiamIPAddress* poIPAddress = NULL;


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

    oDictionary.poDictionaryArray[unAVPCode_i].oAVPDictionaryFunctionPtrs.pfAVPAlloc(hDiameterStackContext_io, (void**)&poIPAddress, sizeof(t_IPAddr),hMsgAllocCtxt_io);

    strncpy(poIPAddress->poIPAddr->pucIPString, pucIPString_i, DMBASE_MAX_IP_STRING_SIZE);
    poIPAddress->poIPAddr->usIPVersion = usIPType_i;

    unsigned int unSize = 0;
    if ( DMBASE_IANA_ADDR_FAMILY_IP_V4 == usIPType_i)
    {
    	unSize = DMBASE_IPV4_ADDR_SIZE_IN_OCTETS + DMBASE_IP_ADDRTYPE_SIZE_IN_OCTETS;
    }
    else if (DMBASE_IANA_ADDR_FAMILY_IP_V6 == usIPType_i)
    {
    	unSize = DMBASE_IPV6_ADDR_SIZE_IN_OCTETS + DMBASE_IP_ADDRTYPE_SIZE_IN_OCTETS;
    }

    DMBase_CreateAVP(hDiameterStackContext_io, phIPAddrAVP_o, hMsgAllocCtxt_io, unAVPCode_i, poIPAddress,
    		unSize,DMBASE_DEFAULT_FLAGS_VALUE);

    if(DMBASE_AVP_VENDOR_ID_NOT_USED != oDictionary.poDictionaryArray[unAVPCode_i].unVendorID)
    {
            DMBase_SetAVPVendorID(hDiameterStackContext_io, *phIPAddrAVP_o,
                      oDictionary.poDictionaryArray[unAVPCode_i].unVendorID);
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_GetAVPCountInCollection(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
					 unsigned int unAVPCode_i, HAVPCOLLECTION hCollOfAVPs_i ,
						unsigned int* punAVPCount_o )
{
	DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");
	unsigned int	unAVPCount=0;
	DMBase_SList*	pListOfAVPs = NULL;
	void* 			pData = NULL;
	HAVP  			hTempAVP = NULL;
	DMBase_SList*	pHeadNode = NULL;

	if (NULL == hDiamStackContext_io )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiamStackContext_io is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hCollOfAVPs_i )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hCollOfAVPs_i is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punAVPCount_o )
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punAVPCount is NULL .\n");
		return DMBase_Retval_Null_Pointer;
	}



	pListOfAVPs = (DMBase_SList*) hCollOfAVPs_i;



	for(pHeadNode = pListOfAVPs; NULL != pHeadNode; DMBase_SListGetNextNode(hDiamStackContext_io, pHeadNode, &pHeadNode))
	{

		DMBase_SListGetNodeData(hDiamStackContext_io, pHeadNode, &pData);
		hTempAVP = (HAVP)pData;
		if(unAVPCode_i == hTempAVP->oAVPHeaderInst.unAVPCode)
		{
			unAVPCount++;
		}
	}//end for

	*punAVPCount_o = unAVPCount;



	DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}
