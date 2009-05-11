

#include "dmbase_appcallbackreg.h"

extern int g_nDiamBaseTraceID;

t_DiamAPIReturnVal DMBase_RegisterApplicationCallback(	HDIAMETERSTACKCONTEXT 			hDiamStackContext_io,
														unsigned int 					unAppId_i,
														t_DiamAppMsgProcessorCallback 	fpAppMsgProcessor_i,
														t_DiamPeerCloseEventCallback	fpPeerCloseEventCallback_i,
														void* 							pvAppContext_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == hDiamStackContext_io || NULL == hDiamStackContext_io->hAppMsgProcessorCallbackHashTable||
										  NULL == fpAppMsgProcessor_i || NULL == pvAppContext_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    t_DiamAppMsgProcessorCallBackData* poCallBackData = NULL;

    if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io, (void**)&poCallBackData, sizeof(t_DiamAppMsgProcessorCallBackData)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Unable to allocate memory\n");
    	return DMBase_Retval_Failure;
    }

    poCallBackData->fpAppMsgProcessor = fpAppMsgProcessor_i;
    poCallBackData->fpPeerCloseEventCallback = fpPeerCloseEventCallback_i;
    poCallBackData->pvAppContext = pvAppContext_i;

    t_DiamHashTableKey oHashTableKey;
    DMBase_SetIntegerInHashTableKey(&oHashTableKey, unAppId_i);

	if(DMBase_Retval_Success != DMBase_HashTableInsert(	hDiamStackContext_io,
														hDiamStackContext_io->hAppMsgProcessorCallbackHashTable,
														poCallBackData,
														&oHashTableKey))
	{

		DMBase_Free(hDiamStackContext_io, (void**)&poCallBackData);
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to insert into Hash Table\n");
		return DMBase_Retval_Failure;
	}

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_UnregisterApplicationCallback(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
														unsigned int 			unAppId_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == hDiamStackContext_io || NULL == hDiamStackContext_io->hAppMsgProcessorCallbackHashTable)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
	}

    t_DiamHashTableKey oHashTableKey;
    DMBase_SetIntegerInHashTableKey(&oHashTableKey, unAppId_i);

	if(DMBase_Retval_Success != DMBase_HashTableRemove(	hDiamStackContext_io,
														hDiamStackContext_io->hAppMsgProcessorCallbackHashTable,
														&oHashTableKey))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to remove hash table entry\n");
		return DMBase_Retval_Failure;
	}


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_ExecLocalProcessingCallback(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												unsigned int 			unAppId_i,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering\n");

	if(NULL == hDiamStackContext_io || NULL == hDiamStackContext_io->hAppMsgProcessorCallbackHashTable ||
									   NULL == hPeer_i || NULL == hDiamMsg_i)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamHashTableKey oHashTableKey;
	DMBase_SetIntegerInHashTableKey(&oHashTableKey, unAppId_i);

	t_DiamAppMsgProcessorCallBackData *poCallBackData = NULL;

	if(DMBase_Retval_Success != DMBase_HashTableSearch(hDiamStackContext_io,
														hDiamStackContext_io->hAppMsgProcessorCallbackHashTable,
														&oHashTableKey,
														(void**)&poCallBackData))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to search hash table entry\n");
		return DMBase_Retval_App_Not_Supported;
	}

	t_DiamAPIReturnVal oReturnVal = poCallBackData->fpAppMsgProcessor(hPeer_i, hDiamMsg_i, poCallBackData->pvAppContext);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return oReturnVal;
}



void DMBase_ExecuteAppPeerConnCloseCallback(HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
											HPEERTABLEENTRY			hPeerTableEntry_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer.\n");
		return;
	}

	t_PeerCloseEventAppData oCloseEventData;
	oCloseEventData.hDiamStackContext = hDiamStackContext_io;
	oCloseEventData.hPeer = hPeerTableEntry_i;

	DMBASE_HASH_HANDLE hPeerTable = hDiamStackContext_io->hAppMsgProcessorCallbackHashTable;
	DMBase_HashTableTraverseAllEntries(	hDiamStackContext_io,
										hPeerTable,
										DMBase_PeerConnCloseCallback,
										&oCloseEventData);


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
}



void DMBase_PeerConnCloseCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	//HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;
	t_PeerCloseEventAppData* poCloseEventData = (t_PeerCloseEventAppData*)r_hAMPS_APP_HANDLE;

	t_DiamAppMsgProcessorCallBackData* poCallBackData = (t_DiamAppMsgProcessorCallBackData*)r_hAMPS_APP_DATA_HANDLE;

	if(NULL != poCallBackData && NULL != poCallBackData->fpPeerCloseEventCallback)
	{
		poCallBackData->fpPeerCloseEventCallback(poCallBackData->pvAppContext, poCloseEventData->hPeer);
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");


}


