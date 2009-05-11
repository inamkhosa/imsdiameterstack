#include "dmbase_utility.h"
#include "dmbase_initconfig.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_failover_failback.h"
#include "dmbase_dictionary.h"

//#include "Trace.h"

extern int g_nDiamBaseTraceID;


/******************************************************************************
** Function Name:
**			DMBase_CreateDiameterContext
**
** Description:
**		This function creates a diameter context.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT* phDiameterContext_io
**			 type: input/output
**			 detail : this is pointer to diameter context handle.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether diameter context
**		created successfully or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal  DMBase_CreateDiameterContext
							(HDIAMETERSTACKCONTEXT* phDiameterContext_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == phDiameterContext_io) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phDiameterContext_io is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL != (*phDiameterContext_io)) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *phDiameterContext_io is NOT NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

    int nSize   = sizeof(t_DiameterBaseAPIContext);

	*phDiameterContext_io = AMPS_Malloc(nSize);

    if(NULL == (*phDiameterContext_io) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in Memory Allocation\n");
        return DMBase_Retval_MemNotAvailable;
    }


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**			DMBase_InitDiameterStack
**
** Description:
**		This function initialize and configure diameter base protocol
**		stack.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			type: input/output
**			detail : this is a diameter context handle.
**
**		  t_DiaStackInitData* pDiaStackInitParams_i
**			type: input
**			detail: this contains all the initializtion and
**				configuration parameters for the diameter
**				base protocol stack.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether diameter context
**		successfully intialized or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal  DMBase_InitDiameterStack ( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  t_DiaStackInitData* pDiaStackInitParams_i)
{

   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

   if ( NULL == hDiameterContext_io)
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL .\n");
        return DMBase_Retval_Null_Pointer;
   }

   if ( NULL == pDiaStackInitParams_i)
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pDiaStackInitParams_i is NULL .\n");
        return DMBase_Retval_Null_Pointer;
   }



   if ( DMBase_Retval_Success != DMBase_SetProductNameInDiameterContext(
	    hDiameterContext_io , pDiaStackInitParams_i->oProductName.pucOctetString) )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetProductNameInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   if ( DMBase_Retval_Success !=  DMBase_SetHostNameInDiameterContext(
	   hDiameterContext_io , pDiaStackInitParams_i->oHostName.pucOctetString))
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetHostNameInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   if ( DMBase_Retval_Success !=  DMBase_SetIPAddressInDiameterContext(
	    hDiameterContext_io , pDiaStackInitParams_i->pucHostIPAddress) )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetIPAddressInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   if ( DMBase_Retval_Success !=  DMBase_SetRealmNameInDiameterContext(
	    hDiameterContext_io , pDiaStackInitParams_i->oRealmName.pucOctetString) )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetRealmNameInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   if ( DMBase_Retval_Success !=  DMBase_SetVendorIDInDiameterContext(
	   hDiameterContext_io ,pDiaStackInitParams_i->unVendorID) )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetVendorIDInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   if ( DMBase_Retval_Success !=   DMBase_SetTcTimerInDiameterContext(
	   hDiameterContext_io ,pDiaStackInitParams_i->unTcTimer) )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetTcTimerInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   // Create Hash table for registration of Application Message Processor callback

   if(DMBase_Retval_Success != DMBase_CreateHashTable(	hDiameterContext_io,
														DMBASE_HASHTABLE_MAX_SIZE,
														&hDiameterContext_io->hAppMsgProcessorCallbackHashTable,
														NULL))
   {
	   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Failed to Create Hash Table\n");
	   return DMBase_Retval_Failure;
   }

   //set dictionary object in the stack context
   t_DiamDictionary	oDiamDictionary = {0};
   oDiamDictionary.unDictSize = DMBASE_MAX_DICTIONARY_SIZE;
   oDiamDictionary.poDictionaryArray = hDiameterContext_io->oDmBase_AVPDictionary;


   if ( DMBase_Retval_Success !=   DMBase_SetDictionaryObjectInDiameterContext(
									hDiameterContext_io ,oDiamDictionary) )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetDictionaryObjectInDiameterContext FAILED .\n");
        return DMBase_Retval_Failure;
   }

   if ( DMBase_Retval_Success !=   DMBase_InitialiseFunctionPointerMappingForDictionary(
											hDiameterContext_io)
	  )
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_InitialiseFunctionPointerMappingForDictionary FAILED .\n");
        return DMBase_Retval_Failure;
   }

 	//Initialise the Dictionary portion which is pre-Defined in RFC 3588
   if ( DMBase_Retval_Success != DMBase_InitBaseProtocolDictionaryElements())
   {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_InitBaseProtocolDictionaryElements Failed.\n");
        return DMBase_Retval_Failure;
   }

   t_DiamOctetString*	poCurrDicFileName = NULL;
   DMBase_SList*		pCurrentNode = NULL;

   //If XML filenames are given for dictionary , then Load the XML files and
   //initialise the dynamic elements
   if (NULL != pDiaStackInitParams_i->pListOfDictionaryFileNames)
   {
	   for(pCurrentNode = pDiaStackInitParams_i->pListOfDictionaryFileNames; NULL != pCurrentNode;DMBase_SListGetNextNode(hDiameterContext_io, pCurrentNode, &pCurrentNode))
	   {
		   poCurrDicFileName = NULL;
		   DMBase_SListGetNodeData(hDiameterContext_io, pCurrentNode, (void**) &poCurrDicFileName);

		   if ( DMBase_Retval_Success != DMBase_PopulateDictionaryFromFile(hDiameterContext_io,*poCurrDicFileName))
		   {
				DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_InitAVPDictionary Failed.\n");
				return DMBase_Retval_Failure;
		   }
		   else
		   {
			   DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " XML dictionary successfully initialised from the configuration file\n");
		   }
	   }//end for
   }
   else
   {
	   DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " XML dictionary configuration files not given, just using preConfig dictionary.\n");

   }
   

    // Create PeerTable
    if (DMBase_Retval_Success != DMBase_CreatePeerTable(hDiameterContext_io))
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Peer Table Creation Failed.\n");
        return DMBase_Retval_Failure;
    }

    //CreateRealmtable

    if (DMBase_Retval_Success != DMBase_CreateRealmTable(hDiameterContext_io))
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Realm Table Creation Failed.\n");
        return DMBase_Retval_Failure;
    }

    // IF ListOfListenAddresses is not Empty StartListeners
    if(NULL != pDiaStackInitParams_i->pListOfListenAddresses)
    {
        if(DMBase_Retval_Success != DMBase_StartListeners(hDiameterContext_io,pDiaStackInitParams_i->pListOfListenAddresses))
        {
            DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in Starting Listeners.\n");
            return DMBase_Retval_Failure;
        }
    }
	else
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " ListOfListenAddresses is not given in base protocol config params.\n");

	}

    // IF ListOFStaticPeers is not Empty BuildPeerTable
    if(NULL != pDiaStackInitParams_i->pListOfStaticPeers)
    {
        if(DMBase_Retval_Success != DMBase_PopulatePeerTable(hDiameterContext_io,
										pDiaStackInitParams_i->pListOfStaticPeers))
        {
            DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Populating Peer Table Failed.\n");
            return DMBase_Retval_Failure;
        }
		else
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Peer Table Populated successfully using ListOFStaticPeers given in base protocol config params.\n");
		}
    }
	else
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " ListOFStaticPeers is not given in base protocol config params.\n");
	}

    // IF ListOfRealmEntries is not empty BuildRealmTable
    if(NULL != pDiaStackInitParams_i->pListOfRealmEntries){

       if(DMBase_Retval_Success != DMBase_PopulateRealmTable(hDiameterContext_io, pDiaStackInitParams_i->pListOfRealmEntries))
       {
           DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Populating Realm Table Failed.\n");
           return DMBase_Retval_Failure;
       }
	   else
	   {
		   DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Realm Table Populating successfully using ListOfRealmEntries given in base protocol config params.\n");
	   }
    }
	else
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " ListOfRealmEntries is not given in base protocol config params.\n");
	}


    DMBase_InitPeerStateMachine(hDiameterContext_io);
    DMBase_InitFailoverStateMachine(hDiameterContext_io);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetProductNameInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchProdName_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	if (NULL == pchProdName_i )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pchProdName_i is NULL.\n");
		return DMBase_Retval_Failure;
	}

	_Bool bIsEmptyString = 0;
	if ( DMBase_Retval_Success !=  DMBase_IsDiamStringEmpty(
								    hDiameterContext_io->oProductName , &bIsEmptyString)
	   )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsDiamStringEmpty has FAILED.\n");
		return DMBase_Retval_Failure;
	}

	if ( 0 == bIsEmptyString)
	{
		if ( DMBase_Retval_Success !=  DMBase_DeleteDiamString(
										&(hDiameterContext_io->oProductName))
			)
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_DeleteDiamString has FAILED.\n");
			return DMBase_Retval_Failure;
		}
	}//end if ( 0 == bIsEmptyString)

	if ( DMBase_Retval_Success !=  DMBase_CopyCharArrayToDiamString(
							&(hDiameterContext_io->oProductName) , pchProdName_i)
	   )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_CopyCharArrayToDiamString has FAILED.\n");
		return DMBase_Retval_Failure;
	}


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetHostNameInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchHostName_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	if (NULL == pchHostName_i )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pchHostName_i is NULL.\n");
		return DMBase_Retval_Failure;
	}
	_Bool bIsEmptyString = 0;
	if ( DMBase_Retval_Success != DMBase_IsDiamStringEmpty(
					hDiameterContext_io->oHostName , &bIsEmptyString)
		)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsDiamStringEmpty has FAILED.\n");
		return DMBase_Retval_Failure;
	}

	if ( 0 == bIsEmptyString)
	{
		if ( DMBase_Retval_Success != DMBase_DeleteDiamString(
								&(hDiameterContext_io->oHostName))
			)
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_DeleteDiamString has FAILED.\n");
			return DMBase_Retval_Failure;
		}
	}

	if ( DMBase_Retval_Success !=  DMBase_CopyCharArrayToDiamString(
							&(hDiameterContext_io->oHostName) , pchHostName_i)
	   )
	{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_CopyCharArrayToDiamString has FAILED.\n");
			return DMBase_Retval_Failure;
	}


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetIPAddressInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchHostIPAddr_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	if (NULL == pchHostIPAddr_i )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pchHostIPAddr_i is NULL.\n");
		return DMBase_Retval_Failure;
	}

	

	if ( NULL ==  strncpy(
						hDiameterContext_io->pucIPAddress , pchHostIPAddr_i,DMBASE_MAX_IP_STRING_SIZE)
		)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " strncpy failed .\n");
		return DMBase_Retval_Failure;
	}


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_SetRealmNameInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char* pchRealmName_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	if (NULL == pchRealmName_i )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pchRealmName_i is NULL.\n");
		return DMBase_Retval_Failure;
	}

	_Bool bIsEmptyString = 0;
	if ( DMBase_Retval_Success !=  DMBase_IsDiamStringEmpty(
						hDiameterContext_io->oRealmName , &bIsEmptyString)
	    )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsDiamStringEmpty failed .\n");
		return DMBase_Retval_Failure;
	}

	if ( 0 == bIsEmptyString)
	{
		if ( DMBase_Retval_Success !=  DMBase_DeleteDiamString(
							&(hDiameterContext_io->oRealmName))
		   )
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_DeleteDiamString failed .\n");
			return DMBase_Retval_Failure;
		}
	}

	if ( DMBase_Retval_Success !=  DMBase_CopyCharArrayToDiamString
				(&(hDiameterContext_io->oRealmName) , pchRealmName_i)
	   )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_CopyCharArrayToDiamString failed .\n");
		return DMBase_Retval_Failure;
	}

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetVendorIDInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,unsigned int unVendorID_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	hDiameterContext_io->unVendorID = unVendorID_i;


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetTcTimerInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,unsigned int unTcTimerVal_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	hDiameterContext_io->unTcTimer = unTcTimerVal_i;


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetFrameworkHandleInDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,FRAMEWORK_HANDLE	hFrameWorkHandle)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hFrameWorkHandle)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hFrameWorkHandle is NULL.\n");
		return DMBase_Retval_Null_Pointer;
	}

	hDiameterContext_io->hFrameworkHandle = hFrameWorkHandle;


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_AddAppInfoToSupportedAppsList(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
													 t_DiamAppInfo	oSupportedApp_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	if ( hDiameterContext_io->unSupportedAppCount >= DMBASE_MAX_HOST_SUPPORTED_APP )
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Limit of DMBASE_MAX_HOST_SUPPORTED_APP  reached , leaving.\n");
		return DMBase_Retval_Failure;
	}

	hDiameterContext_io->SupportedAppList[hDiameterContext_io->unSupportedAppCount] = oSupportedApp_i;


	hDiameterContext_io->unSupportedAppCount++;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_CleanupDiameterStack ( HDIAMETERSTACKCONTEXT*  phDiameterContext_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == phDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	HDIAMETERSTACKCONTEXT	hDiameterContext_io = *phDiameterContext_io;


	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	//Delete all strings from the stack context
	DMBase_DeleteDiamString(&hDiameterContext_io->oDiamAPILogFileName);
	DMBase_DeleteDiamString(&hDiameterContext_io->oHostName);
	DMBase_DeleteDiamString(&hDiameterContext_io->oRealmName);
	DMBase_DeleteDiamString(&hDiameterContext_io->oProductName);







	//disconnect from all transport connections if still connected

	//remove all transport objects , and free them

	//remove all HPEERS from peer table , free each HPEER and free the PEER Table

	//remove all HREALMS from peer table , free each HREALMS and free the REALM Table


	// free the HDIAMETERSTACKCONTEXT





	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");
}

t_DiamAPIReturnVal  DMBase_GetProductNameFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io , char** ppchProdName_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppchProdName_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppchProdName_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppchProdName_o))
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppchProdName_o) is NOT NULL \n");
		return DMBase_Retval_IncorrectParameters;
	}

	if(DMBase_Retval_Success != DMBase_Malloc(hDiameterContext_io,(void**)ppchProdName_o, hDiameterContext_io->oProductName.unNumOfOctets +1 ))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }


	strcpy(*ppchProdName_o,hDiameterContext_io->oProductName.pucOctetString);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");
	return DMBase_Retval_Success;

}


t_DiamAPIReturnVal  DMBase_GetHostNameFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
														  char** ppchHostName_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppchHostName_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppchHostName_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppchHostName_o))
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppchHostName_o) is NOT NULL \n");
		return DMBase_Retval_IncorrectParameters;
	}

	if(DMBase_Retval_Success != DMBase_Malloc(hDiameterContext_io,(void**)ppchHostName_o, hDiameterContext_io->oHostName.unNumOfOctets +1 ))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
		return DMBase_Retval_Failure;
	}


	strcpy(*ppchHostName_o,hDiameterContext_io->oHostName.pucOctetString);



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_GetIPAddressFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
														    char** ppchHostIPAddr_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppchHostIPAddr_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppchHostIPAddr_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppchHostIPAddr_o))
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppchHostIPAddr_o) is NOT NULL \n");
		return DMBase_Retval_IncorrectParameters;
	}

	if(DMBase_Retval_Success != DMBase_Malloc(hDiameterContext_io,(void**)ppchHostIPAddr_o, DMBASE_MAX_IP_STRING_SIZE +1 ))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
		return DMBase_Retval_Failure;
	}


	strncpy(*ppchHostIPAddr_o,hDiameterContext_io->pucIPAddress,DMBASE_MAX_IP_STRING_SIZE);



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetRealmNameFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
														    char** ppchRealmName_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppchRealmName_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppchRealmName_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppchRealmName_o))
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppchRealmName_o) is NOT NULL \n");
		return DMBase_Retval_IncorrectParameters;
	}

	if(DMBase_Retval_Success != DMBase_Malloc(hDiameterContext_io,(void**)ppchRealmName_o, hDiameterContext_io->oRealmName.unNumOfOctets +1 ))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
		return DMBase_Retval_Failure;
	}


	strcpy(*ppchRealmName_o,hDiameterContext_io->oRealmName.pucOctetString);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_GetVendorIDFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
														  unsigned int * punVendorID_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punVendorID_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punVendorID_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	*punVendorID_o = hDiameterContext_io->unVendorID;


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}



t_DiamAPIReturnVal  DMBase_GetTcTimerFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
														 unsigned int* punTcTimerVal_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punTcTimerVal_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punTcTimerVal_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	*punTcTimerVal_o = hDiameterContext_io->unTcTimer;


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_GetFrameworkHandleFromDiameterContext(HDIAMETERSTACKCONTEXT hDiameterContext_io ,
												FRAMEWORK_HANDLE*	phFrameWorkHandle_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phFrameWorkHandle_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " phFrameWorkHandle_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	*phFrameWorkHandle_o = hDiameterContext_io->hFrameworkHandle;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetDictionaryObjectInDiameterContext(
	HDIAMETERSTACKCONTEXT hDiameterContext_io ,t_DiamDictionary oDiamDictionary_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Failure;
	}

	hDiameterContext_io->oDictionary = oDiamDictionary_i;


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_GetDictionaryObjectFromDiameterContext(
	HDIAMETERSTACKCONTEXT hDiameterContext_io ,t_DiamDictionary* poDiamDictionary_o)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == poDiamDictionary_o)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " poDiamDictionary_o is NULL.\n");
		return DMBase_Retval_Null_Pointer;
	}

	*poDiamDictionary_o = hDiameterContext_io->oDictionary;


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_InitialiseFunctionPointerMappingForDictionary(
								HDIAMETERSTACKCONTEXT hDiameterContext_io )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterContext_io is NULL.\n");
		return DMBase_Retval_Null_Pointer;
	}

	//initialise the thirteen elements of the function pointer mapping table
	// 
	//#define	DMBASE_AVP_DATATYPE_OCTETSTRING		"OctetString"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_OCTETSTRING , DMBASE_MAX_SMALL_STRING_SIZE);
	
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamOctetString;
    hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamOctetString;
    hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamOctetString;
    hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamOctetStringRawData;
    hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamOctetStringStructData;
    hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamOctetStringStructData;


    
    //#define	DMBASE_AVP_DATATYPE_INTEGER32		"Integer32"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_INTEGER32 , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamInteger32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamInteger32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamInteger32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamInteger32RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamInteger32StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER32].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamInteger32StructData;




	//#define	DMBASE_AVP_DATATYPE_INTEGER64		"Integer64"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_INTEGER64 , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamInteger64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamInteger64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamInteger64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamInteger64RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamInteger64StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_INTEGER64].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamInteger64StructData;


    //#define	DMBASE_AVP_DATATYPE_UNSIGNED32		"Unsigned32"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_UNSIGNED32 , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamUnsigned32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamUnsigned32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamUnsigned32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamUnsigned32RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamUnsigned32StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamUnsigned32StructData;




	//#define	DMBASE_AVP_DATATYPE_UNSIGNED64		"Unsigned64"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_UNSIGNED64 , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamUnsigned64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamUnsigned64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamUnsigned64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamUnsigned64RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamUnsigned64StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamUnsigned64StructData;

	


    //#define	DMBASE_AVP_DATATYPE_FLOAT32			"Float32"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_FLOAT32 , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamFloat32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamFloat32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamFloat32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamFloat32RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamFloat32StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT32].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamFloat32StructData;



   //#define	DMBASE_AVP_DATATYPE_FLOAT64			"Float64"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_FLOAT64 , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamFloat64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamFloat64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamFloat64;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamFloat64RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamFloat64StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_FLOAT64].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamFloat64StructData;



	//#define	DMBASE_AVP_DATATYPE_IPADDRESS		"Address"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_IPADDRESS , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamIPAddress;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamIPAddress;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamIPAddress;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamIPAddressRawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamIPAddressStructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamIPAddressStructData;



    //#define	DMBASE_AVP_DATATYPE_TIME			"Time"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_OCTETSTRING , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamUnsigned32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamUnsigned32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamUnsigned32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamUnsigned32RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamUnsigned32StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamUnsigned32StructData;


    
	//#define	DMBASE_AVP_DATATYPE_UTF8STRING		"UTF8String"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_UTF8STRING , DMBASE_MAX_SMALL_STRING_SIZE);


	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamOctetStringRawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamOctetStringStructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamOctetStringStructData;




	//#define	DMBASE_AVP_DATATYPE_DMIDENTITY		"DiameterIdentity"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_DMIDENTITY , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamOctetStringRawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamOctetStringStructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamOctetStringStructData;





	//#define	DMBASE_AVP_DATATYPE_DMURI			"DiameterURI"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_DMURI , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamOctetString;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamOctetStringRawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamOctetStringStructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamOctetStringStructData;




    //#define	DMBASE_AVP_DATATYPE_ENUMERATED		"Enumerated"
	strncpy(hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].pucAVPDataTypeName,
		  DMBASE_AVP_DATATYPE_ENUMERATED , DMBASE_MAX_SMALL_STRING_SIZE);

	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs.pfValidateAVPData = &DMBase_ValidateDiamEnum;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs.pfAVPAlloc = &DMBase_AVPAllocDiamInteger32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs.pfAVPDeAlloc = &DMBase_AVPDeAllocDiamInteger32;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs.pfWriteRawDataToMemory = &DMBase_GetDiamInteger32RawData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs.pfGetStructData = &DMBase_GetDiamInteger32StructData;
	hDiameterContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs.pfDebugDumpAVPData = &DMBase_DumpDiamInteger32StructData;






    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}
