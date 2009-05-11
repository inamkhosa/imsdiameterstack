#include "dmbase_peerstatemachine.h"
#include "dmbase_parser.h"
#include "dmbase_msgvalidate.h"
#include "dmbase_dictionary.h"
#include "dmbase_realmtablemgmt.h"
#include "dmbase_appcallbackreg.h"
#include "dmbase_failover_failback.h"
#include "dmbase_avp.h"
#include "dmbase_psm_actions.h"

extern int g_nDiamBaseTraceID;


t_DiamAPIReturnVal DMBase_InitPeerStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    hDiamStackContext_io->oPSMActions[Closed][Start] =	DMBase_Closed_Start;
    hDiamStackContext_io->oPSMActions[Closed][R_Conn_CER] = DMBase_Closed_R_Conn_CER;

    hDiamStackContext_io->oPSMActions[Wait_Conn_Ack][I_Rcv_Conn_Ack] = DMBase_Wait_Conn_Ack_I_Rcv_Conn_Ack;
    hDiamStackContext_io->oPSMActions[Wait_Conn_Ack][I_Rcv_Conn_Nack] = DMBase_Wait_Conn_Ack_I_Rcv_Conn_Nack;
    hDiamStackContext_io->oPSMActions[Wait_Conn_Ack][R_Conn_CER] = DMBase_Wait_Conn_Ack_R_Conn_CER;
    hDiamStackContext_io->oPSMActions[Wait_Conn_Ack][Timeout] = DMBase_Wait_Conn_Ack_Timeout;

    hDiamStackContext_io->oPSMActions[Wait_I_CEA][I_Rcv_CEA] = DMBase_Wait_I_CEA_I_Rcv_CEA;
    hDiamStackContext_io->oPSMActions[Wait_I_CEA][R_Conn_CER] = DMBase_Wait_I_CEA_R_Conn_CER;
    hDiamStackContext_io->oPSMActions[Wait_I_CEA][I_Peer_Disc] = DMBase_Wait_I_CEA_I_Peer_Disc;
    hDiamStackContext_io->oPSMActions[Wait_I_CEA][I_Rcv_Non_CEA] = DMBase_Wait_I_CEA_I_Rcv_Non_CEA;
    hDiamStackContext_io->oPSMActions[Wait_I_CEA][Timeout] = DMBase_Wait_I_CEA_Timeout;

    hDiamStackContext_io->oPSMActions[Wait_Conn_Ack_Elect][I_Rcv_Conn_Ack] = DMBase_Wait_Conn_Ack_Elect_I_Rcv_Conn_Ack;
	hDiamStackContext_io->oPSMActions[Wait_Conn_Ack_Elect][I_Rcv_Conn_Nack] = DMBase_Wait_Conn_Ack_Elect_I_Rcv_Conn_Nack;
	hDiamStackContext_io->oPSMActions[Wait_Conn_Ack_Elect][R_Peer_Disc] = DMBase_Wait_Conn_Ack_Elect_R_Peer_Disc;
	hDiamStackContext_io->oPSMActions[Wait_Conn_Ack_Elect][R_Conn_CER] = DMBase_Wait_Conn_Ack_Elect_R_Conn_CER;
	hDiamStackContext_io->oPSMActions[Wait_Conn_Ack_Elect][Timeout] = DMBase_Wait_Conn_Ack_Elect_Timeout;

	hDiamStackContext_io->oPSMActions[Wait_Returns][Win_Election] = DMBase_Wait_Returns_Win_Election;
	hDiamStackContext_io->oPSMActions[Wait_Returns][I_Peer_Disc] = DMBase_Wait_Returns_I_Peer_Disc;
	hDiamStackContext_io->oPSMActions[Wait_Returns][I_Rcv_CEA] = DMBase_Wait_Returns_I_Rcv_CEA;
	hDiamStackContext_io->oPSMActions[Wait_Returns][R_Peer_Disc] = DMBase_Wait_Returns_R_Peer_Disc;
	hDiamStackContext_io->oPSMActions[Wait_Returns][R_Conn_CER] = DMBase_Wait_Returns_R_Conn_CER;
	hDiamStackContext_io->oPSMActions[Wait_Returns][Timeout] = DMBase_Wait_Returns_Timeout;

	hDiamStackContext_io->oPSMActions[R_Open][Send_Message] = DMBase_R_Open_Send_Message;
	hDiamStackContext_io->oPSMActions[R_Open][R_Rcv_Message] = DMBase_R_Open_R_Rcv_Message;
	hDiamStackContext_io->oPSMActions[R_Open][R_Rcv_DWR] = DMBase_R_Open_R_Rcv_DWR;
	hDiamStackContext_io->oPSMActions[R_Open][R_Rcv_DWA] = DMBase_R_Open_R_Rcv_DWA;
	hDiamStackContext_io->oPSMActions[R_Open][R_Conn_CER] = DMBase_R_Open_R_Conn_CER;
	hDiamStackContext_io->oPSMActions[R_Open][Stop] = DMBase_R_Open_Stop;
	hDiamStackContext_io->oPSMActions[R_Open][R_Rcv_DPR] = DMBase_R_Open_R_Rcv_DPR;
	hDiamStackContext_io->oPSMActions[R_Open][R_Peer_Disc] = DMBase_R_Open_R_Peer_Disc;
	hDiamStackContext_io->oPSMActions[R_Open][R_Rcv_CER] = DMBase_R_Open_R_Rcv_CER;
	hDiamStackContext_io->oPSMActions[R_Open][R_Rcv_CEA] = DMBase_R_Open_R_Rcv_CEA;

	hDiamStackContext_io->oPSMActions[I_Open][Send_Message] = DMBase_I_Open_Send_Message;
	hDiamStackContext_io->oPSMActions[I_Open][I_Rcv_Message] = DMBase_I_Open_I_Rcv_Message;
	hDiamStackContext_io->oPSMActions[I_Open][I_Rcv_DWR] = DMBase_I_Open_I_Rcv_DWR;
	hDiamStackContext_io->oPSMActions[I_Open][I_Rcv_DWA] = DMBase_I_Open_I_Rcv_DWA;
	hDiamStackContext_io->oPSMActions[I_Open][R_Conn_CER] = DMBase_I_Open_R_Conn_CER;
	hDiamStackContext_io->oPSMActions[I_Open][Stop] = DMBase_I_Open_Stop;
	hDiamStackContext_io->oPSMActions[I_Open][I_Rcv_DPR] = DMBase_I_Open_I_Rcv_DPR;
	hDiamStackContext_io->oPSMActions[I_Open][I_Peer_Disc] = DMBase_I_Open_I_Peer_Disc;
	hDiamStackContext_io->oPSMActions[I_Open][I_Rcv_CER] = DMBase_I_Open_I_Rcv_CER;
	hDiamStackContext_io->oPSMActions[I_Open][I_Rcv_CEA] = DMBase_I_Open_I_Rcv_CEA;

	hDiamStackContext_io->oPSMActions[Closing][I_Rcv_DPA] = DMBase_Closing_I_Rcv_DPA;
	hDiamStackContext_io->oPSMActions[Closing][R_Rcv_DPA] = DMBase_Closing_R_Rcv_DPA;
	hDiamStackContext_io->oPSMActions[Closing][Timeout] = DMBase_Closing_Timeout;
	hDiamStackContext_io->oPSMActions[Closing][I_Peer_Disc] = DMBase_Closing_I_Peer_Disc;
	hDiamStackContext_io->oPSMActions[Closing][R_Peer_Disc] = DMBase_Closing_R_Peer_Disc;


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_CheckEventType(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                         HPEERTABLEENTRY 		hPeer_i,
                                         HDIAMETERMESSAGE 		hDiamMsg_i,
                                         t_DiameterPSMEvent* 		poPSMEvent_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeer_i || NULL == hDiamMsg_i || NULL == poPSMEvent_i)
    {
   	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    unsigned int unCommandCode = 0;

    DMBase_GetDiaMsgCmdCodeFromDiamMsg(hDiamStackContext_io, hDiamMsg_i, &unCommandCode);

    if(Wait_I_CEA == hPeer_i->oPeerState && DMBASE_MSG_CMD_CODE_CEA != unCommandCode)
    {
        *poPSMEvent_i = I_Rcv_Non_CEA;
    }
    else if( DMBASE_MSG_CMD_CODE_CER == unCommandCode &&
             DMBASE_BITMASK_SET_MSG_R_FLAG & hDiamMsg_i->oDiaHeader.ucFlags )
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_CER;
        else
            *poPSMEvent_i = R_Rcv_CER;

    }
    else if ( DMBASE_MSG_CMD_CODE_CEA == unCommandCode  )
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_CEA;
        else
            *poPSMEvent_i = R_Rcv_CEA;

    }
    else if ( DMBASE_MSG_CMD_CODE_DPR == unCommandCode &&
              DMBASE_BITMASK_SET_MSG_R_FLAG & hDiamMsg_i->oDiaHeader.ucFlags )
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_DPR;
        else
            *poPSMEvent_i = R_Rcv_DPR;

    }
    else if ( DMBASE_MSG_CMD_CODE_DPA == unCommandCode )
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_DPA;
        else
            *poPSMEvent_i = R_Rcv_DPA;

    }
    else if ( DMBASE_MSG_CMD_CODE_DWR == unCommandCode &&
              DMBASE_BITMASK_SET_MSG_R_FLAG & hDiamMsg_i->oDiaHeader.ucFlags )
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_DWR;
        else
            *poPSMEvent_i = R_Rcv_DWR;

    }
    else if ( DMBASE_MSG_CMD_CODE_DWA == unCommandCode )
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_DWA;
        else
            *poPSMEvent_i = R_Rcv_DWA;

    }
    else
    {
        if(Initiator == hPeer_i->oPeerConnectionRole)
            *poPSMEvent_i = I_Rcv_Message;
        else
            *poPSMEvent_i = R_Rcv_Message;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Closed_Start(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
										  HPEERTABLEENTRY 		hPeer_i,
										  HDIAMETERMESSAGE 		hDiamMsg_i,
										  t_DiameterPSMEvent 		oPSMEvent_i,
										  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     if(DMBase_Retval_Success != DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io, hPeer_i, Initiator))
     {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem occurred while setting state in Peer table entry\n");
        return DMBase_Retval_Failure;
     }

     if(DMBase_Retval_Success != DMBase_PSMAction_ISndConnReq(hDiamStackContext_io, hPeer_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem occurred while executing I-Snd-Conn-Req Action\n");
        return DMBase_Retval_Failure;
    }
     if(DMBase_Retval_Success != DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Wait_Conn_Ack))
     {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem occured while setting state in Peer table entry\n");
        return DMBase_Retval_Failure;
     }

/*
     DMBASE_TIMERID oTimerID = NULL;
     DMBase_StartTimer( hDiamStackContext_io,
                        DMBASE_TIMER_VALUE,
                        DMBase_TimeOutNotifyCallBack,
                        (void*)hPeer_i,
                        &oTimerID);
     hPeer_i->oTimerID = oTimerID;
*/
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Closed_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                            HPEERTABLEENTRY 		hPeer_i,
                                            HDIAMETERMESSAGE 		hDiamMsg_i,
                                            t_DiameterPSMEvent 		oPSMEvent_i,
                                            void* 					pvData)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal;
     if(DMBase_Retval_Success != DMBase_PSMAction_RAccept(hDiamStackContext_io, hPeer_i))
     {
         DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " \n");
         return DMBase_Retval_Failure;
     }

     DMBase_SetPeerResponderTransportObject(hDiamStackContext_io, hPeer_i, (HTRANSPORTOBJECT)pvData);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, R_Open);

     oReturnVal = DMBase_PSMAction_ProcessCER(hDiamStackContext_io,hDiamMsg_i, hPeer_i);


     if(DMBase_Retval_No_Commom_Application == oReturnVal)
     {
    	 //Generate Error

    	 DMBase_GeneratePermanentFailure(hDiamStackContext_io, hPeer_i, hDiamMsg_i, DIAMETER_NO_COMMON_APPLICATION, NULL);
         DMBase_PSMAction_RDisc(hDiamStackContext_io, hPeer_i);
         DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);
         DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io, hPeer_i, Undefined);

     }
     else if(DMBase_Retval_Success == oReturnVal)
     {
    	 oReturnVal = DMBase_PSMAction_RSndCEA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);
    	 if(DMBase_Retval_Success == oReturnVal)
		 {
    		 DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeer_i, FSME_CONNECTION_UP, NULL);
		 }
    	 else
    	 {
    		 DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);
    	 }

     }


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                   HPEERTABLEENTRY			hPeer_i,
                                                   HDIAMETERMESSAGE 		hDiamMsg_i,
                                                   t_DiameterPSMEvent 			oPSMEvent_i,
                                                   void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_I_Rcv_Conn_Ack(   HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
														  HPEERTABLEENTRY 		hPeer_i,
														  HDIAMETERMESSAGE 		hDiamMsg_i,
														  t_DiameterPSMEvent 		oPSMEvent_i,
														  void* 				pData)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal;

     if(DMBase_Retval_Success != (oReturnVal = DMBase_PSMAction_ISndCER(hDiamStackContext_io, hPeer_i)))
     {
    	 DMBase_PSMAction_IDisc(hDiamStackContext_io, hPeer_i);
    	 return oReturnVal;

     }

     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Wait_I_CEA);

 /*
     DMBase_KillTimer(hDiamStackContext_io, hPeer_i->oTimerID);
     hPeer_i->oTimerID = NULL;

     DMBASE_TIMERID oTimerID = NULL;
     DMBase_StartTimer( hDiamStackContext_io,
                        DMBASE_TIMER_VALUE,
                        DMBase_TimeOutNotifyCallBack,
                        (void*)hPeer_i,
                        &oTimerID);
     hPeer_i->oTimerID = oTimerID;*/

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_I_Rcv_Conn_Nack(  HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
														  HPEERTABLEENTRY 		hPeer_i,
														  HDIAMETERMESSAGE 		hDiamMsg_i,
														  t_DiameterPSMEvent 		oPSMEvent_i,
														  void* 				pData)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //DMBase_Cleanup(HDIAMETERSTACKCONTEXT hDiamStackContext_io);

     //Remove transport object , if created
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);
     DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io, hPeer_i, Undefined);

     /*
     DMBase_KillTimer(hDiamStackContext_io, hPeer_i->oTimerID);
     hPeer_i->oTimerID = NULL;
     */

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Timeout( HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												 HPEERTABLEENTRY 		hPeer_i,
                                                 HDIAMETERMESSAGE 		hDiamMsg_i,
                                                 t_DiameterPSMEvent 		oPSMEvent_i,
                                                 void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_Error(hDiamStackContext_io, hPeer_i->hInitiatorTransport);
    if(DMBase_Retval_Success != DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem occured while setting state in Peer table entry\n");
        return DMBase_Retval_Failure;
    }

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_I_CEA_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                HPEERTABLEENTRY 		hPeer_i,
                                                HDIAMETERMESSAGE 		hDiamMsg_i,
                                                t_DiameterPSMEvent 		oPSMEvent_i,
                                                void* 					pvData)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_I_CEA_I_Rcv_CEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i,
                                                t_DiameterPSMEvent 		oPSMEvent_i,
                                                void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessCEA(hDiamStackContext_io,hPeer_i, hDiamMsg_i);

     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, I_Open);
     DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io, hPeer_i, Initiator);

     DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeer_i, FSME_CONNECTION_UP, NULL);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_I_CEA_I_Rcv_Non_CEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
													HPEERTABLEENTRY 		hPeer_i,
                                                    HDIAMETERMESSAGE 		hDiamMsg_i,
                                                    t_DiameterPSMEvent 		oPSMEvent_i,
                                                    void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_Error(hDiamStackContext_io, hPeer_i->hInitiatorTransport);
     //Free Transport if created
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_I_CEA_I_Peer_Disc(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                 HPEERTABLEENTRY 		hPeer_i,
                                                 HDIAMETERMESSAGE 		hDiamMsg_i,
                                                 t_DiameterPSMEvent 		oPSMEvent_i,
                                                 void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Free Transport if created
     //DMBase_PSMAction_IDisc(hDiamStackContext_io, hPeer_i);

     DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeer_i, FSME_CONNECTION_DOWN, NULL);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);
     DMBase_KillTimer(hDiamStackContext_io, hPeer_i->oTimerID);
     hPeer_i->oTimerID = NULL;


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_I_CEA_Timeout(  HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											   HPEERTABLEENTRY 			hPeer_i,
                                               HDIAMETERMESSAGE 		hDiamMsg_i,
                                               t_DiameterPSMEvent 			oPSMEvent_i,
                                               void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_Error(hDiamStackContext_io, hPeer_i->hInitiatorTransport);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                         HPEERTABLEENTRY 		hPeer_i,
                                                         HDIAMETERMESSAGE 		hDiamMsg_i,
                                                         t_DiameterPSMEvent 		oPSMEvent_i,
                                                         void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_I_Rcv_Conn_Ack(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
															 HPEERTABLEENTRY 		hPeer_i,
															 HDIAMETERMESSAGE 		hDiamMsg_i,
															 t_DiameterPSMEvent 		oPSMEvent_i,
															 void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_I_Rcv_Conn_Nack(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
															  HPEERTABLEENTRY 		hPeer_i,
															  HDIAMETERMESSAGE 		hDiamMsg_i,
															  t_DiameterPSMEvent 		oPSMEvent_i,
															  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_R_Peer_Disc(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													      HPEERTABLEENTRY 		hPeer_i,
													      HDIAMETERMESSAGE 		hDiamMsg_i,
													      t_DiameterPSMEvent 		oPSMEvent_i,
													      void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_Timeout(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

//TODO: Clarify this State

t_DiamAPIReturnVal DMBase_Wait_Returns_R_Conn_CER(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_Returns_I_Rcv_CEA( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Returns_I_Peer_Disc(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_Returns_R_Peer_Disc(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Wait_Returns_Win_Election(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election processing here

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Wait_Returns_Timeout(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //Election Processing
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Conn_CER(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }



     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_CER(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessCER(hDiamStackContext_io, hDiamMsg_i, hPeer_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_CEA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessCEA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Peer_Disc( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //DMBase_PSMAction_RDisc(hDiamStackContext_io, hPeer_i);
     DMBase_DeleteDiamString(&hPeer_i->hResponderTransport->oDiamTCPTransport.oFQDN);
     DMBase_DeleteDiamString(&hPeer_i->hResponderTransport->oDiamTCPTransport.oIPAddress);
     DMBase_Free(hDiamStackContext_io, (void**)&hPeer_i->hResponderTransport);

     DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeer_i, FSME_CONNECTION_DOWN, NULL);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_DPR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_RSndDPA(hDiamStackContext_io, hPeer_i);
     DMBase_PSMAction_RDisc(hDiamStackContext_io,hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);
     DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io, hPeer_i, Undefined);


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_DWR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_RSndDWA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_DWA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessDWA(hDiamStackContext_io, hPeer_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_R_Open_Send_Message(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     if(DMBase_Retval_Success != DMBase_PSMAction_RSndMessage(hDiamStackContext_io, hPeer_i, hDiamMsg_i))
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Message Sending Failed.\n");
    	 return DMBase_Retval_Failure;
     }
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, R_Open);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_Message(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     t_DiamAPIReturnVal oReturnVal;
     oReturnVal = DMBase_PSMAction_Process(hDiamStackContext_io, hPeer_i, hDiamMsg_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, R_Open);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}



t_DiamAPIReturnVal DMBase_R_Open_Stop(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
									  HPEERTABLEENTRY 		hPeer_i,
									  HDIAMETERMESSAGE 		hDiamMsg_i,
									  t_DiameterPSMEvent 		oPSMEvent_i,
									  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_RSndDPR(hDiamStackContext_io, hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closing);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hDiamMsg_i,
											t_DiameterPSMEvent 		oPSMEvent_i,
											void* 					pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

    HTRANSPORTOBJECT hTempTransObj = (HTRANSPORTOBJECT)pvData_i;
//    DMBase_R_Reject(hDiamStackContext_io, hTempTransObj);
    DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, I_Open);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_CER(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessCER(hDiamStackContext_io,hDiamMsg_i, hPeer_i);
     DMBase_PSMAction_ISndCEA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_CEA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessCEA(hDiamStackContext_io,hPeer_i ,hDiamMsg_i);


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Peer_Disc( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     //DMBase_PSMAction_IDisc(hDiamStackContext_io, hPeer_i);
     //Free Resources
     DMBase_ExecuteFailoverStateMachine(hDiamStackContext_io, hPeer_i, FSME_CONNECTION_DOWN, NULL);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_DPR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ISndDPA(hDiamStackContext_io, hPeer_i);
     DMBase_PSMAction_IDisc(hDiamStackContext_io, hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);
     DMBase_SetPeerRoleInPeerTableEntry(hDiamStackContext_io, hPeer_i, Undefined);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_DWR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ISndDWA(hDiamStackContext_io, hPeer_i, hDiamMsg_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_DWA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ProcessDWA(hDiamStackContext_io, hPeer_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_Send_Message(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ISndMessage(hDiamStackContext_io, hPeer_i,hDiamMsg_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, I_Open);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_Message(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io || NULL == hPeer_i)
	{
	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
	 return DMBase_Retval_Null_Pointer;
	}

	t_DiamAPIReturnVal oReturnVal;
	oReturnVal = DMBase_PSMAction_Process(hDiamStackContext_io, hPeer_i, hDiamMsg_i);
	DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, I_Open);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return oReturnVal;
}


t_DiamAPIReturnVal DMBase_I_Open_Stop(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
									  HPEERTABLEENTRY 		hPeer_i,
									  HDIAMETERMESSAGE 		hDiamMsg_i,
									  t_DiameterPSMEvent 		oPSMEvent_i,
									  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_ISndDPR(hDiamStackContext_io, hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closing);


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Closing_I_Peer_Disc(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }


      DMBase_PSMAction_IDisc(hDiamStackContext_io, hPeer_i);
      DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Closing_R_Peer_Disc(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_RDisc(hDiamStackContext_io, hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Closing_I_Rcv_DPA(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }


     DMBase_PSMAction_IDisc(hDiamStackContext_io, hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);


     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Closing_R_Rcv_DPA(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     DMBase_PSMAction_RDisc(hDiamStackContext_io, hPeer_i);
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Closing_Timeout(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
										  HPEERTABLEENTRY 		hPeer_i,
										  HDIAMETERMESSAGE 		hDiamMsg_i,
										  t_DiameterPSMEvent 		oPSMEvent_i,
										  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

     if(NULL == hDiamStackContext_io || NULL == hPeer_i)
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     if(Initiator == hPeer_i->oPeerConnectionRole)
     {
        DMBase_PSMAction_Error(hDiamStackContext_io, hPeer_i->hInitiatorTransport);
     }
     else if(Responder == hPeer_i->oPeerConnectionRole)
     {
        DMBase_PSMAction_Error(hDiamStackContext_io, hPeer_i->hResponderTransport);
     }
     DMBase_SetStateInPeerTableEntry(hDiamStackContext_io, hPeer_i, Closed);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_ExecutePeerStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	 if(NULL == hPeer_i )
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
         return DMBase_Retval_Null_Pointer;
     }

     if( NULL == hDiamStackContext_io->oPSMActions[hPeer_i->oPeerState][oPSMEvent_i])
     {
    	 DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Event.\n");
         return DMBase_Retval_Failure;
     }

     t_DiamAPIReturnVal oReturnVal ;

	 oReturnVal=  hDiamStackContext_io->oPSMActions[hPeer_i->oPeerState][oPSMEvent_i]( hDiamStackContext_io,
																				hPeer_i,
																				hDiamMsg_i,
																				oPSMEvent_i,
																				pvData_i);

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return oReturnVal;
}

int DMBase_TimeOutNotifyCallBack_ForPSM(FRAMEWORK_HANDLE hoAMPSFrameWork, void* r_pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    HPEERTABLEENTRY hPeerEntry = (HPEERTABLEENTRY)r_pvData;
    hPeerEntry->oTimerID = NULL;

    DMBase_ExecutePeerStateMachine(hPeerEntry->hDiameterStackContext, hPeerEntry, NULL, Timeout, NULL);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;

}

