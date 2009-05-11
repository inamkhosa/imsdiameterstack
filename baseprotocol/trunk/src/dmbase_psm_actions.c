
#include "dmbase_psm_actions.h"

#include "dmbase_peerstatemachine.h"
#include "dmbase_parser.h"
#include "dmbase_msgvalidate.h"
#include "dmbase_dictionary.h"
#include "dmbase_realmtablemgmt.h"
#include "dmbase_appcallbackreg.h"
#include "dmbase_failover_failback.h"
#include "dmbase_avp.h"
#include "dmbase_cer_processing.h"

extern int g_nDiamBaseTraceID;

t_DiamAPIReturnVal DMBase_PSMAction_ISndConnReq(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
    	 return DMBase_Retval_Null_Pointer;
     }

     t_NetHandleData *	poNetHandleData = NULL;


     if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io,
												 (void**)&poNetHandleData,
												 sizeof(t_NetHandleData)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to allocate memory.\n");
    	 return DMBase_Retval_Failure;
     }

     poNetHandleData->hPeer = hPeer_i;

	 t_TCPOpen_Params	oTCPOpenParams = {0};
	 oTCPOpenParams.nFixedMsgSize = DMBASE_MSG_HEADER_SIZE_IN_BYTES;
	 oTCPOpenParams.nMinMsgSize = 0;
	 oTCPOpenParams.pfMallocCallback = NULL;
	 oTCPOpenParams.pfReAllocCallback = NULL;
	 oTCPOpenParams.pfFreeCallback = NULL;
	 oTCPOpenParams.pfRecvDataCallback = DMBase_ReceiveMessageOnTCP;
	 oTCPOpenParams.pfCloseEvtCallback = DMBase_ConnectionCloseNotification;
	 oTCPOpenParams.pfConnCfmCallback = DMBase_ConnectConfirm;
	 oTCPOpenParams.pvAppHandle = hDiamStackContext_io;
	 oTCPOpenParams.pvAppDataHandle = poNetHandleData;



     if( (Initiator != hPeer_i->oPeerConnectionRole) ||
    	 (DMBase_Retval_Success != DMBase_OpenTCPConnection(hDiamStackContext_io,
															 hPeer_i->hConfiguredTransport,
															 oTCPOpenParams)))
     {
         DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Unable to setup TCP connection with Peer.\n");
        // DMBase_Free(hDiamStackContext_io, (void**)&poNetHandleData);
         return DMBase_Retval_Failure;
     }


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_RAccept(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
    	 return DMBase_Retval_Null_Pointer;
     }

     if(DMBase_Retval_Success != DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io,
																	hPeer_i,
																	Responder))
     {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem occurred while setting state in Peer table entry\n");
        return DMBase_Retval_Failure;
     }

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}




t_DiamAPIReturnVal DMBase_PSMAction_ProcessCER(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HDIAMETERMESSAGE 		hDiamMsg_i,
												HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
    	 return DMBase_Retval_Null_Pointer;
     }

     t_DiamCER oCER;
     t_DiamAPIReturnVal oReturnVal;

     DMBase_MemsetZero(&oCER, sizeof(t_DiamCER));

     if(DMBase_Retval_Success != (oReturnVal = DMBase_ExtractCER(hDiamStackContext_io, hDiamMsg_i, &oCER)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to extract message.\n");
    	 return oReturnVal;
     }

	 if(DMBase_Retval_No_Commom_Application == (oReturnVal = DMBase_AddCommonAppInfoToPeerEntry(hDiamStackContext_io, hPeer_i, &oCER)))
	 {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " No Common application.\n");
    	 return oReturnVal;
	 }

	 //Add common security check here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_RSndCEA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hRcvDiamMsg_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hRcvDiamMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
    	 return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_Send_CEA(hDiamStackContext_io, hPeer_i, hRcvDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}


t_DiamAPIReturnVal DMBase_Send_CEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HPEERTABLEENTRY 		hPeer_i,
									HDIAMETERMESSAGE 		hRcvDiamMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hRcvDiamMsg_i)
    {
   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
   	 return DMBase_Retval_Null_Pointer;
    }

    unsigned char ucFlags = 0;
    unsigned int unHopByHopID = 0;
    unsigned int unEndToEndID = 0;
    HDIAMETERMESSAGE hDiamCEA = NULL;
    t_DiamAPIReturnVal oReturnValue;

    DMBase_GetHopByHopIDFromDiamMsg(hDiamStackContext_io, hRcvDiamMsg_i, &unHopByHopID);
    DMBase_GetEndToEndIDFromDiamMsg(hDiamStackContext_io, hRcvDiamMsg_i, &unEndToEndID);

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateCEA(hDiamStackContext_io,
																 &hDiamCEA,
																 unHopByHopID,
																 unEndToEndID)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create CEA.\n");
    	return DMBase_Retval_Failure;
    }

    unsigned char *pucBuffer = NULL;
    unsigned int 	unMsgLength = 0;

    if(DMBase_Retval_Success != (oReturnValue = DMBase_GetDiaMsgLengthFromDiamMsg(	hDiamStackContext_io,
																					hDiamCEA,
																					&unMsgLength)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create CEA.\n");
    	goto ExitMe;
    }

    if(DMBase_Retval_Success != (oReturnValue = DMBase_ConvertDiameterMessageToRawForm(hDiamStackContext_io,
																						&pucBuffer,
																						hDiamCEA)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create CEA.\n");
    	goto ExitMe;
    }

    if(Initiator == hPeer_i->oPeerConnectionRole)
    {
    	DMBase_SendBufferOnTransport(	hDiamStackContext_io,
										hPeer_i->hInitiatorTransport,
										pucBuffer,
										unMsgLength);
    }
    else
    {
    	DMBase_SendBufferOnTransport(	hDiamStackContext_io,
										hPeer_i->hResponderTransport,
										pucBuffer,
										unMsgLength);
    }

    ExitMe:

    DMBase_Free(hDiamStackContext_io, (void**)&pucBuffer);
    DMBase_DestroyDiaMessage(hDiamStackContext_io, &hDiamCEA);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;
}

t_DiamAPIReturnVal DMBase_PSMAction_ISndCER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeer_i )
    {
   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
   	 return DMBase_Retval_Null_Pointer;
    }

    t_DiamAPIReturnVal oReturnVal;
    oReturnVal = DMBase_Send_CER(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnVal;
}

t_DiamAPIReturnVal DMBase_Send_CER(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
									HPEERTABLEENTRY 	 hPeer_i)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeer_i)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
    	return DMBase_Retval_Null_Pointer;
    }

    unsigned char ucFlags = 0;
    unsigned int unHopByHopID = 0;//DMBase_GenerateHopByHopId();
    unsigned int unEndToEndID = 0;//DMBase_GenerateEndToEndId();
    HDIAMETERMESSAGE hDiamCER = NULL;
    t_DiamAPIReturnVal oReturnValue;

    if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateCER(hDiamStackContext_io,
																 &hDiamCER,
																 unHopByHopID,
																 unEndToEndID)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create CEA.\n");
    	return DMBase_Retval_Failure;
    }

    unsigned char *pucBuffer = NULL;
    unsigned int 	unMsgLength = 0;

    if(DMBase_Retval_Success != (oReturnValue = DMBase_GetDiaMsgLengthFromDiamMsg(	hDiamStackContext_io,
																					hDiamCER,
																					&unMsgLength)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create CER.\n");
    	goto ExitMe;
    }

    if(DMBase_Retval_Success != (oReturnValue = DMBase_ConvertDiameterMessageToRawForm(hDiamStackContext_io,
																						&pucBuffer,
																						hDiamCER)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create CEA.\n");
    	goto ExitMe;
    }

    if(Initiator == hPeer_i->oPeerConnectionRole)
    {
    	DMBase_SendBufferOnTransport(	hDiamStackContext_io,
										hPeer_i->hInitiatorTransport,
										pucBuffer,
										unMsgLength);
    }
    else
    {
    	DMBase_SendBufferOnTransport(	hDiamStackContext_io,
										hPeer_i->hResponderTransport,
										pucBuffer,
										unMsgLength);
    }

    ExitMe:

    DMBase_Free(hDiamStackContext_io, (void**)&pucBuffer);
    DMBase_DestroyDiaMessage(hDiamStackContext_io, &hDiamCER);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;


}

t_DiamAPIReturnVal DMBase_PSMAction_Cleanup(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     if(Initiator == hPeer_i->oPeerConnectionRole && NULL != hPeer_i->hInitiatorTransport)
     {
    	 DMBase_DeleteDiamString(&hPeer_i->hInitiatorTransport->oDiamTCPTransport.oFQDN);
    	 DMBase_DeleteDiamString(&hPeer_i->hInitiatorTransport->oDiamTCPTransport.oIPAddress);
    	 DMBase_Free(hDiamStackContext_io, (void**)&hPeer_i->hInitiatorTransport);
     }
     else if(Responder == hPeer_i->oPeerConnectionRole && NULL != hPeer_i->hResponderTransport)
     {
    	 DMBase_DeleteDiamString(&hPeer_i->hResponderTransport->oDiamTCPTransport.oFQDN);
    	 DMBase_DeleteDiamString(&hPeer_i->hResponderTransport->oDiamTCPTransport.oIPAddress);
    	 DMBase_Free(hDiamStackContext_io, (void**)&hPeer_i->hResponderTransport);
     }

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_Error(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HTRANSPORTOBJECT 		hTransportObj_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hTransportObj_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

    DMBase_CloseTCPConnection(hDiamStackContext_io, hTransportObj_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_ProcessCEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i ,
												HDIAMETERMESSAGE 		hDiamMsg_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamCEA oCEA;
     t_DiamAPIReturnVal oReturnVal;

     DMBase_MemsetZero(&oCEA, sizeof(t_DiamCEA));

     if(DMBase_Retval_Success != (oReturnVal = DMBase_ExtractCEA(hDiamStackContext_io, hDiamMsg_i, &oCEA)))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to extract message.\n");
    	 return oReturnVal;
     }

	 if(DMBase_Retval_No_Commom_Application != (oReturnVal = DMBase_AddCommonAppInfoToPeerEntry(hDiamStackContext_io, hPeer_i, &oCEA)))
	 {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " No Common application.\n");
    	 return oReturnVal;
	 }

	 //Add common security check here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;

}

t_DiamAPIReturnVal DMBase_PSMAction_Elect(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											_Bool* 					pbWinElection_o)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
     //Add Election Code Here
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_PSMAction_IDisc(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }


     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_CloseTCPConnection(hDiamStackContext_io, hPeer_i->hInitiatorTransport);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_ISndCEA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hRcvDiamMsg_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hRcvDiamMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }


     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_Send_CEA(hDiamStackContext_io, hPeer_i, hRcvDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_RDisc(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }


     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_CloseTCPConnection(hDiamStackContext_io, hPeer_i->hResponderTransport);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_RReject(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HTRANSPORTOBJECT 		hTranportObj_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hTranportObj_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_CloseTCPConnection(hDiamStackContext_io, hTranportObj_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}

t_DiamAPIReturnVal DMBase_SendMessage(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HPEERTABLEENTRY 		hPeer_i,
										HDIAMETERMESSAGE 		hDiamMsg_i)
{

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal = DMBase_Retval_Success;
     unsigned int unMsgSize = 0;
     DMBase_GetDiaMsgLengthFromDiamMsg(hDiamStackContext_io, hDiamMsg_i, &unMsgSize);

     unsigned char* pucRawBuff = NULL;
     if(DMBase_Retval_Success != DMBase_ConvertDiameterMessageToRawForm(hDiamStackContext_io,&pucRawBuff,hDiamMsg_i))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Message Conversion Failed.\n");
    	 return DMBase_Retval_Failure;
     }



     if(Initiator == hPeer_i->oPeerConnectionRole)
     {
    	 if(DMBase_Retval_Success != DMBase_SendBufferOnTransport(	hDiamStackContext_io,
										hPeer_i->hInitiatorTransport,
										pucRawBuff,
										unMsgSize))
    	 {
        	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Message Sending Failed.\n");
        	 oReturnVal = DMBase_Retval_Failure;
    	 }
     }
     else if(Responder == hPeer_i->oPeerConnectionRole)
     {
    	 if(DMBase_Retval_Success != DMBase_SendBufferOnTransport(	hDiamStackContext_io,
										hPeer_i->hResponderTransport,
										pucRawBuff,
										unMsgSize))
    	 {
        	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Message Sending Failed.\n");
        	 oReturnVal = DMBase_Retval_Failure;
    	 }
     }


     DMBase_Free(hDiamStackContext_io, (void**)&pucRawBuff);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

     return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_RSndMessage(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i)
{

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_SendMessage(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

     return oReturnVal;
}


t_DiamAPIReturnVal DMBase_PSMAction_ISndMessage(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    t_DiamAPIReturnVal oReturnVal;
    oReturnVal = DMBase_SendMessage(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

    return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_Process(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_i,
											HDIAMETERMESSAGE 		hDiamMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamAPIReturnVal	oReturnVal;

    DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeerTableEntry_i, FSME_RECEIVE_NON_DWA, NULL);

    if(DMBASE_BITMASK_SET_MSG_R_FLAG & hDiamMsg_i->oDiaHeader.ucFlags)
    {
    	oReturnVal = DMBase_ProcessRequest(hDiamStackContext_io, hPeerTableEntry_i, hDiamMsg_i);
    }
    else
    {
    	oReturnVal = DMBase_ProcessAnswer(hDiamStackContext_io, hPeerTableEntry_i, hDiamMsg_i);
    }


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

	return oReturnVal;

}



t_DiamAPIReturnVal DMBase_PSMAction_ProcessDWR(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_SendDWA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HPEERTABLEENTRY 		hPeer_i,
									HDIAMETERMESSAGE 		hDiamMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


	DMBase_SList*	pAVPList = NULL;
	HDIAMETERMESSAGE hDiaMsgDWA = NULL;
	unsigned int	unHopByHopID= 0;
	unsigned int 	unEndToEndID = 0;

	DMBase_GetHopByHopIDFromDiamMsg(hDiamStackContext_io, hDiamMsg_i, &unHopByHopID);
	DMBase_GetEndToEndIDFromDiamMsg(hDiamStackContext_io, hDiamMsg_i, &unEndToEndID);

	HAVP hAVP_ResCode = NULL;
	HAVP hAVP_Orig_Host = NULL;
	HAVP hAVP_Orig_Realm = NULL;

	t_DiamAPIReturnVal oReturnValue;
	if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateDiameterMessage(	hDiamStackContext_io,
																				 &hDiaMsgDWA ,
																				 DIAMETER_VERSION_NUMBER,
																				 DMBASE_MSG_CMD_CODE_DWA,
																				 DIAMETER_COMMON_MESSAGE_ID,
																				 0,
																				 unHopByHopID,
																				 unEndToEndID)))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to create message.\n");
		goto ExitMe;
	}

	HMSGALLOCATIONCONTEXT hMsgAllocCtxt = NULL;
	DMBase_Get_AllocationContext_ForMessage(hDiamStackContext_io, hDiaMsgDWA, &hMsgAllocCtxt);

	if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateEnumAVP(	hDiamStackContext_io,
																		DMBASE_AVP_RESULT_CODE,
																		&hAVP_ResCode,
																		DIAMETER_SUCCESS,
																		hMsgAllocCtxt)))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to AVP.\n");
		goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUTF8StringAVP(hDiamStackContext_io,
																			DMBASE_AVP_ORIGIN_HOST,
																			&hAVP_Orig_Host,
																			hDiamStackContext_io->oHostName.pucOctetString,
																			hDiamStackContext_io->oHostName.unNumOfOctets ,
																			hMsgAllocCtxt)))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to AVP.\n");
		goto ExitMe;
	}

	if(DMBase_Retval_Success != (oReturnValue = DMBase_CreateUTF8StringAVP(hDiamStackContext_io,
																			DMBASE_AVP_ORIGIN_REALM,
																			&hAVP_Orig_Realm,
																			hDiamStackContext_io->oRealmName.pucOctetString,
																			hDiamStackContext_io->oRealmName.unNumOfOctets ,
																			hMsgAllocCtxt)))
	{
		 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to AVP.\n");
		 goto ExitMe;
	}

	DMBase_AppendSList(hDiamStackContext_io, &pAVPList, (void*)hAVP_ResCode);
	DMBase_AppendSList(hDiamStackContext_io, &pAVPList, (void*)hAVP_Orig_Host);
	DMBase_AppendSList(hDiamStackContext_io, &pAVPList, (void*)hAVP_Orig_Realm);

	DMBase_AddAVPCollectionToDiameterMessage(hDiamStackContext_io, hDiaMsgDWA, pAVPList);

	DMBase_SendMessageToPeer(hDiamStackContext_io, hPeer_i, hDiaMsgDWA);

	ExitMe:
	DMBase_DestroyDiaMessage(hDiamStackContext_io, &hDiaMsgDWA);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_RSndDWA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hDiamMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

	t_DiamAPIReturnVal oReturnVal;
	oReturnVal = DMBase_SendDWA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return oReturnVal;
}


t_DiamAPIReturnVal DMBase_PSMAction_ISndDWA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hDiamMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamAPIReturnVal oReturnVal;
	oReturnVal = DMBase_SendDWA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return oReturnVal;
}

t_DiamAPIReturnVal DMBase_PSMAction_ProcessDWA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
     	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeer_i, FSME_RECEIVE_DWA, NULL);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_ISndDPR(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}
t_DiamAPIReturnVal DMBase_PSMAction_SendDPR(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_RSndDPR(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}
t_DiamAPIReturnVal DMBase_PSMAction_RSndDPA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}
t_DiamAPIReturnVal DMBase_PSMAction_SendDPA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_PSMAction_ISndDPA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Invalid_Action(HDIAMETERSTACKCONTEXT hDiamStackContext_io)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     printf("Invalid Action Handler called\n");

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ProcessRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hRcvMsg_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hRcvMsg_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oRetValue;
	 HAVP hDestHostAVP = NULL;
	 HAVP hDestRealmAVP = NULL;
	 unsigned int unAppId = 0;
	 int nComparisonResult = 0;

	 DMBase_GetDiaMsgAppIdFromDiamMsg(hDiamStackContext_io, hRcvMsg_i, &unAppId);
	 DMBase_GetAVP(hDiamStackContext_io, DMBASE_AVP_DESTINATION_HOST, hRcvMsg_i, &hDestHostAVP);
	 DMBase_GetAVP(hDiamStackContext_io, DMBASE_AVP_DESTINATION_REALM, hRcvMsg_i, &hDestRealmAVP);

	 if(NULL != hDestHostAVP)
	 {
		 nComparisonResult = DMBase_CompareDiamString(	(t_DiamOctetString*)hDestHostAVP->pData,
												&(hDiamStackContext_io->oHostName));
	 }


	 HREALMTABLEENTRY hRealmTableEntry = NULL;

	 if(NULL != hDestRealmAVP )
	 {
		 oRetValue = DMBase_LookupRealmTableEntry(	hDiamStackContext_io,
													unAppId,
													*((t_DiamOctetString*)hDestRealmAVP->pData),
													&hRealmTableEntry);
		 if(DMBase_Retval_Success != oRetValue)
		 {
			 if(DMBase_Retval_Realm_Not_Supported == oRetValue)
			 {
				 DMBase_GenerateProtocolErr(hDiamStackContext_io, hPeer_i,
						 hRcvMsg_i, DIAMETER_REALM_NOT_SERVED, NULL);
			 }
			 else if(DMBase_Retval_App_Not_Supported == oRetValue)
			 {
				 DMBase_GenerateProtocolErr(hDiamStackContext_io, hPeer_i,
						 hRcvMsg_i, DIAMETER_APPLICATION_UNSUPPORTED, NULL);
			 }
			 goto ExitMe;
		 }
	 }

	 HPEERTABLEENTRY hPeerTableEntry = NULL;

	 if((NULL != hDestHostAVP && 0 == nComparisonResult) ||
		(NULL == hDestHostAVP && NULL == hDestRealmAVP) ||
		(NULL == hDestHostAVP && NULL != hDestRealmAVP &&
		 NULL != hRealmTableEntry && LOCAL == hRealmTableEntry->oLocalAction))
	 {
		//Process Locally

		 oRetValue = DMBase_LocalProcessing(hDiamStackContext_io, hPeer_i, hRcvMsg_i, unAppId);

	 }
	 else if(NULL != hDestHostAVP &&
		DMBase_Retval_Success == DMBase_LookUpPeerTableEntry(hDiamStackContext_io,
															*((t_DiamOctetString*)hDestHostAVP->pData),
															&hPeerTableEntry))
	 {
		 /*  Request Forwarding */
		//TODO: Discussion pending
		 oRetValue = DMBase_ForwardRequest(hDiamStackContext_io, hPeer_i, hRcvMsg_i);
	 }
	else if(NULL != hRealmTableEntry && LOCAL != hRealmTableEntry->oLocalAction)
	{
		/* Request Routing */
		oRetValue = DMBase_RouteRequest(hDiamStackContext_io, hRealmTableEntry, hPeer_i, hRcvMsg_i);
	}
	else
	{
		DMBase_GenerateProtocolErr(hDiamStackContext_io, hPeer_i, hRcvMsg_i, DIAMETER_UNABLE_TO_DELIVER, NULL);
		oRetValue = DMBase_Retval_Unable_To_Deliver;
	}

     ExitMe:

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oRetValue;
}


t_DiamAPIReturnVal DMBase_ProcessAnswer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HPEERTABLEENTRY 		hPeer_i,
										HDIAMETERMESSAGE 		hRcvMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    unsigned int unListCount = 0;
    DMBase_SList *poPendingMsgList = NULL;
    HFAILOVERSUPPORTDATA hSupportData = NULL;
    t_DiamAPIReturnVal oReturnVal;
    _Bool bIsMsgSent = FALSE;

    for(; unListCount < hPeer_i->unPendingMsgListCount; unListCount++)
    {
        poPendingMsgList = *hPeer_i->ppvPendingMsgList[unListCount];

        while(NULL != poPendingMsgList)
        {
            hSupportData = NULL;
            DMBase_SListGetNodeData(hDiamStackContext_io, poPendingMsgList, (void**)&hSupportData);

            if(hRcvMsg_i->oDiaHeader.unHopByHopID == hSupportData->unLocalHopByHopId)
            {
                if(NULL != hSupportData->hPeer)
                {
                    DMBase_SetHopByHopID(hDiamStackContext_io, hRcvMsg_i, hSupportData->unActualHopByHopId);
                    oReturnVal = DMBase_SendMessageToPeer(hDiamStackContext_io, hSupportData->hPeer, hRcvMsg_i);
                    bIsMsgSent = TRUE;
                    //Delete Message form Pending Messages queue.
                }
                DMBase_SListRemove(hDiamStackContext_io,
                                   (DMBase_SList**)hPeer_i->ppvPendingMsgList[unListCount],
                                   poPendingMsgList,
                                   DMBase_FreeFailoverSupportData);
                break;
            }
            DMBase_SListGetNextNode(hDiamStackContext_io,poPendingMsgList, &poPendingMsgList);
        }
    }

    if(FALSE == bIsMsgSent)
    {
        unsigned int unAppId = 0;
        DMBase_GetDiaMsgAppIdFromDiamMsg(hDiamStackContext_io, hRcvMsg_i, &unAppId);
        oReturnVal = DMBase_ExecLocalProcessingCallback(hDiamStackContext_io,unAppId, hPeer_i, hRcvMsg_i);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnVal;
}


t_DiamAPIReturnVal DMBase_LocalProcessing(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i,
											unsigned int			unAppId_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamAPIReturnVal oRetValue;

    if((oRetValue = DMBase_ExecLocalProcessingCallback(hDiamStackContext_io,unAppId_i,
                     hPeer_i, hRcvMsg_i)) != DMBase_Retval_Success)
    {
        if(DMBase_Retval_App_Not_Supported == oRetValue)
        {
        	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Application Not Supported.\n");
            DMBase_GenerateProtocolErr(hDiamStackContext_io, hPeer_i,
									hRcvMsg_i, DIAMETER_APPLICATION_UNSUPPORTED, NULL);
        }

    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oRetValue;
}

t_DiamAPIReturnVal DMBase_ForwardRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_RouteRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HREALMTABLEENTRY		hRealm_i,
										HPEERTABLEENTRY			hPeer_i,
										HDIAMETERMESSAGE		hRcvMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamAPIReturnVal oReturnVal;

	switch(hRealm_i->oLocalAction)
	{
		case RELAY:
			oReturnVal = DMBase_RelayingRequest(hDiamStackContext_io, hRealm_i, hPeer_i, hRcvMsg_i);
			break;
		case REDIRECT:
			oReturnVal = DMBase_RedirectingRequest(hDiamStackContext_io, hRealm_i, hPeer_i, hRcvMsg_i);
			break;
		case PROXY:
			oReturnVal = DMBase_ProxingRequest(hDiamStackContext_io, hRealm_i, hPeer_i, hRcvMsg_i);
			break;
	}


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnVal;
}


t_DiamAPIReturnVal DMBase_RelayingRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HREALMTABLEENTRY		hRealm_i,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_RedirectingRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HREALMTABLEENTRY		hRealm_i,
												HPEERTABLEENTRY			hPeer_i,
												HDIAMETERMESSAGE		hRcvMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_ProxingRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HREALMTABLEENTRY		hRealm_i,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	t_DiamAPIReturnVal oReturnVal;
	t_FailoverSupportData* poSupportData = NULL;
	HAVP hRouteRecord = NULL;

    if(0 <= hRealm_i->unPrimaryServer)
    {
        HPEERTABLEENTRY hNextHopPeer = NULL;
        oReturnVal = DMBase_LookUpPeerTableEntry(hDiamStackContext_io,
												hRealm_i->oRoutServerList[hRealm_i->unPrimaryServer].oPeerIdentity,
												(void**)&hNextHopPeer);
        if(DMBase_Retval_Success == oReturnVal)
        {
            if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io,
														(void**)&poSupportData,
														sizeof(t_FailoverSupportData)))
            {
            	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to allocate memory.\n");
            	oReturnVal = DMBase_Retval_Failure;
            	goto ExitMe;
            }

            poSupportData->hDiamMsg = hRcvMsg_i;
            poSupportData->hPeer = hPeer_i;
            poSupportData->unActualHopByHopId = hRcvMsg_i->oDiaHeader.unHopByHopID;
            poSupportData->unEndToEndId = hRcvMsg_i->oDiaHeader.unEndToEndID;
            poSupportData->unLocalHopByHopId = DMBase_GenerateHopByHopId();
            DMBase_SetHopByHopID(hDiamStackContext_io, hRcvMsg_i, poSupportData->unLocalHopByHopId);
            HMSGALLOCATIONCONTEXT hMsgAllocCtxt = NULL;

            DMBase_Get_AllocationContext_ForMessage(hDiamStackContext_io,hRcvMsg_i, &hMsgAllocCtxt);

            if(DMBase_Retval_Success != DMBase_CreateOctetStringAVP(hDiamStackContext_io,
																	DMBASE_AVP_ROUTE_RECORD,
																	&hRouteRecord,
																	hPeer_i->oHostIdentity.pucOctetString,
																	hPeer_i->oHostIdentity.unNumOfOctets,
																	hMsgAllocCtxt))
            {
            	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to create Route-Record AVP.\n");
            	oReturnVal = DMBase_Retval_Failure;
            	goto ExitMe;
            }

            DMBase_AddAVPToDiameterMessage(	hDiamStackContext_io, hRcvMsg_i, hRouteRecord);

            if(DMBase_Retval_Success == DMBase_SendMessageToPeer(hDiamStackContext_io, hNextHopPeer, hRcvMsg_i))
            {
                DMBase_AppendSList(hDiamStackContext_io, &hRealm_i->poPendingMsgQueue,
                                    (void*)poSupportData);
                oReturnVal = DMBase_Retval_Msg_Stored;
            }
            else
            {
                DMBase_SetHopByHopID(hDiamStackContext_io, hRcvMsg_i, poSupportData->unActualHopByHopId);
                oReturnVal = DMBase_Retval_Unable_To_Deliver;
            }
        }
        else
        {
             oReturnVal = DMBase_Retval_Unable_To_Deliver;
        }
    }
    else
    {
         oReturnVal = DMBase_Retval_Unable_To_Deliver;
    }

    ExitMe:

    if(DMBase_Retval_Unable_To_Deliver == oReturnVal)
    {
        DMBase_GenerateProtocolErr(hDiamStackContext_io, hPeer_i, hRcvMsg_i, DIAMETER_UNABLE_TO_DELIVER, NULL);
    }

    if(DMBase_Retval_Msg_Stored != oReturnVal)
    {
    	DMBase_Free(hDiamStackContext_io, (void**)&poSupportData);
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnVal;
}


