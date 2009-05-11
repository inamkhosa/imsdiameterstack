
#include "dmbase_failover_failback.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_avp.h"
#include "dmbase_parser.h"
#include<stdbool.h>

extern	int g_nDiamBaseTraceID ;

t_DiamAPIReturnVal DMBase_InitFailoverStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Null pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

	hDiamStackContext_io->oFSMActions[PS_OKAY][FSME_RECEIVE_DWA] = DMBase_Okay_RcvDWA;
	hDiamStackContext_io->oFSMActions[PS_OKAY][FSME_RECEIVE_NON_DWA] = DMBase_Okay_RcvNonDWA;
	hDiamStackContext_io->oFSMActions[PS_OKAY][FSME_TIMER_EXPIRES] = DMBase_Okay_TimerExpires;
	hDiamStackContext_io->oFSMActions[PS_OKAY][FSME_CONNECTION_DOWN] = DMBase_Okay_ConnectionDown;

	hDiamStackContext_io->oFSMActions[PS_SUSPECT][FSME_RECEIVE_DWA] = DMBase_Suspect_RcvDWA;
	hDiamStackContext_io->oFSMActions[PS_SUSPECT][FSME_RECEIVE_NON_DWA] = DMBase_Suspect_RcvNonDWA;
	hDiamStackContext_io->oFSMActions[PS_SUSPECT][FSME_TIMER_EXPIRES] = DMBase_Suspect_TimerExpires;
	hDiamStackContext_io->oFSMActions[PS_SUSPECT][FSME_CONNECTION_DOWN] = DMBase_Suspect_ConnectionDown;

	hDiamStackContext_io->oFSMActions[PS_DOWN][FSME_RECEIVE_DWA] = DMBase_Down_RcvDWA;
	hDiamStackContext_io->oFSMActions[PS_DOWN][FSME_RECEIVE_NON_DWA] = DMBase_Down_RcvNonDWA;
	hDiamStackContext_io->oFSMActions[PS_DOWN][FSME_TIMER_EXPIRES] = DMBase_Down_TimerExpires;
	hDiamStackContext_io->oFSMActions[PS_DOWN][FSME_CONNECTION_UP] = DMBase_Down_ConnectionUp;

	hDiamStackContext_io->oFSMActions[PS_REOPEN][FSME_RECEIVE_DWA] = DMBase_Reopen_RcvDWA;
	hDiamStackContext_io->oFSMActions[PS_REOPEN][FSME_RECEIVE_NON_DWA] = DMBase_Reopen_RcvNonDWA;
	hDiamStackContext_io->oFSMActions[PS_REOPEN][FSME_TIMER_EXPIRES] = DMBase_Reopen_TimerExpires;
	hDiamStackContext_io->oFSMActions[PS_REOPEN][FSME_CONNECTION_DOWN] = DMBase_Reopen_ConnectionDown;

	hDiamStackContext_io->oFSMActions[PS_INITIAL][FSME_RECEIVE_DWA] = DMBase_Initial_RcvDWA;
	hDiamStackContext_io->oFSMActions[PS_INITIAL][FSME_RECEIVE_NON_DWA] = DMBase_Initial_RcvNonDWA;
	hDiamStackContext_io->oFSMActions[PS_INITIAL][FSME_TIMER_EXPIRES] = DMBase_Initial_TimerExpires;
	hDiamStackContext_io->oFSMActions[PS_INITIAL][FSME_CONNECTION_UP] = DMBase_Initial_ConnectionUp;

	DMBase_InitWatchDogTimer(hDiamStackContext_io);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return DMBase_Retval_Success;
}
int DMBase_TimeOutNotification(void* pvHandle, void* r_pvData)
{
   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

   HPEERTABLEENTRY hPeer = (HPEERTABLEENTRY)r_pvData;

    unsigned char ucPeerName[100];
    strncpy(ucPeerName, hPeer->oHostIdentity.pucOctetString, hPeer->oHostIdentity.unNumOfOctets);
    ucPeerName[hPeer->oHostIdentity.unNumOfOctets] = '\0';

    printf("Timer Expires For %s\r\n",ucPeerName);

   hPeer->oPCB.oTimerID = NULL;
   DMBase_ExecuteFailoverStateMachine(hPeer->hDiameterStackContext, hPeer,
                                        FSME_TIMER_EXPIRES, NULL);

   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
   return 0;
}
t_DiamAPIReturnVal DMBase_SetWatchdog(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                        HPEERTABLEENTRY hPeer_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


    if(NULL != hPeer_io->oPCB.oTimerID)
    {
        DMBase_KillTimer(hDiamStackContext_io, hPeer_io->oPCB.oTimerID);
    }
    DMBase_StartTimer(hDiamStackContext_io, hPeer_io->oPCB.unTw, DMBase_TimeOutNotification,
                      (void*)hPeer_io, &hPeer_io->oPCB.oTimerID);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SendDWR(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                  HPEERTABLEENTRY       hPeer_i)
{

    unsigned int unCommandCode = 280;
    unsigned int unAppID = 0;


    HDIAMETERMESSAGE hReqMsg = NULL;
    DMBase_SList*	pAVPList = NULL;
    HAVP hTempAVP = NULL;

    DMBase_CreateDiameterMessage(hDiamStackContext_io, &hReqMsg, 1, unCommandCode, unAppID ,0,
    		DMBase_GenerateHopByHopId(), DMBase_GenerateEndToEndId());
    DMBase_SetDiaMsgRFlag(hDiamStackContext_io, hReqMsg,1);

	HMSGALLOCATIONCONTEXT hMsgAllocCtxt = NULL;
	DMBase_Get_AllocationContext_ForMessage(hDiamStackContext_io, hReqMsg, &hMsgAllocCtxt);

    hTempAVP = NULL;
    DMBase_CreateUTF8StringAVP(hDiamStackContext_io,
            DMBASE_AVP_ORIGIN_HOST,
            &hTempAVP,
            hDiamStackContext_io->oHostName.pucOctetString,
            hDiamStackContext_io->oHostName.unNumOfOctets ,
            hMsgAllocCtxt);
    DMBase_AppendSList(hDiamStackContext_io, &pAVPList, (void*)hTempAVP);

    hTempAVP = NULL;
    DMBase_CreateUTF8StringAVP(hDiamStackContext_io,
            DMBASE_AVP_ORIGIN_REALM,
            &hTempAVP,
            hDiamStackContext_io->oRealmName.pucOctetString,
            hDiamStackContext_io->oRealmName.unNumOfOctets  ,
            hMsgAllocCtxt);
    DMBase_AppendSList(hDiamStackContext_io, &pAVPList, (void*)hTempAVP);


    DMBase_AddAVPCollectionToDiameterMessage(hDiamStackContext_io, hReqMsg, pAVPList);

    DMBase_SendMessageToPeer(hDiamStackContext_io, hPeer_i, hReqMsg);

    DMBase_DestroyDiaMessage(hDiamStackContext_io, &hReqMsg);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetPCBValues(HPCB           hoPCB,
                                       t_PCBStatus    oStatus,
                                       _Bool          bPending,
                                       unsigned int   unTw,
                                       unsigned short usNumDWA)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    hoPCB->oStatus = oStatus;
    hoPCB->bPending = bPending;
    hoPCB->unTw = unTw;
    hoPCB->usNumDWA = usNumDWA;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetPCBStatus(HPCB       hoPCB,
                                      t_PCBStatus oStatus)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    hoPCB->oStatus = oStatus;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetPCBPendingFlag(HPCB  hoPCB,
                                            _Bool bPending)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    hoPCB->bPending = bPending;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Failover(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                   HPEERTABLEENTRY       hPeer_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    int nCount;
    HREALMTABLEENTRY hRealm;
    t_RealmTable* poRealmTabel = hDiamStackContext_io->poRealmTable;

    for(nCount = 0; nCount < poRealmTabel->oRealmHashTable.unHashKeyCount; nCount++)
    {
        hRealm = NULL;
        DMBase_LookupRealmTableByHashKey(hDiamStackContext_io,
										 poRealmTabel->oRealmHashTable.oHashKeys[nCount],
										 &hRealm);
        if(DMBase_IsPrimaryServer(hDiamStackContext_io, hRealm, hPeer_i))
        {
            if(DMBase_Retval_Success == DMBase_SwitchToAlternateServer(hDiamStackContext_io, hRealm))
            {
                DMBase_SendPendingMsgToAlternateServer(hDiamStackContext_io, hRealm);
            }
			//TODO:Handle Else case
            DMBase_ClearPendingMsgListEntry(hDiamStackContext_io, hRealm, hPeer_i);
        }
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

 t_DiamAPIReturnVal DMBase_SetPendingMsgListEntry(HDIAMETERSTACKCONTEXT hDiameterContext_io, HPEERTABLEENTRY hPeer)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
/*
    int nCount;
    HREALMTABLEENTRY hRealm  = NULL;

    for(nCount = 0; nCount < hDiameterContext_io->poRealmTable->unRealmKeyCount; nCount++)
    {
        hRealm = NULL;

        DMBase_LookupRealmTableEntry(hDiameterContext_io, hDiameterContext_io->poRealmTable->oRealmKeys[nCount].unAppId ,
                                    hDiameterContext_io->poRealmTable->oRealmKeys[nCount].oRealmName , (void**)&hRealm);
        if(PROXY == hRealm->oLocAct)
        {
            if(0 <= hRealm->unPrimaryServer &&
               0 == DMBase_CompareDiamString(&hRealm->oRoutServerList[hRealm->unPrimaryServer].oPeerIdentity, &hPeer->oHostIdentity))
            {
                hPeer->ppvPendingMsgList[hPeer->unPendingMsgListCount++] = (void**)&hRealm->poPendingMsgQueue;
            }
        }
    }*/
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

 t_DiamAPIReturnVal DMBase_ClearPendingMsgListEntry(HDIAMETERSTACKCONTEXT hDiameterContext_io,
                                                    HREALMTABLEENTRY hRealm,
                                                    HPEERTABLEENTRY hPeer)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    int nIndex1, nIndex2;

    for(nIndex1 = hPeer->unPendingMsgListCount-1; nIndex1 >= 0 ; nIndex1--)
    {
        if(hPeer->ppvPendingMsgList[nIndex1] == (void**)&hRealm->poPendingMsgQueue)
        {
            for(nIndex2 = nIndex1; nIndex2 < hPeer->unPendingMsgListCount-1; nIndex2++)
            {
                hPeer->ppvPendingMsgList[nIndex2] = hPeer->ppvPendingMsgList[nIndex2+1];
            }
            hPeer->unPendingMsgListCount--;
            break;
        }
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

 t_DiamAPIReturnVal DMBase_SetActiveServer(HDIAMETERSTACKCONTEXT hDiameterContext_io, HPEERTABLEENTRY hPeer)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");



    int nCount;
    HREALMTABLEENTRY hRealm  = NULL;

    for(nCount = 0; nCount < hDiameterContext_io->poRealmTable->oRealmHashTable.unHashKeyCount; nCount++)
    {
        hRealm = NULL;

        DMBase_LookupRealmTableByHashKey(hDiameterContext_io, hDiameterContext_io->poRealmTable->oRealmHashTable.oHashKeys[nCount] , &hRealm);
        if(PROXY == hRealm->oLocalAction)
        {
			//TODO:Change PrimaryServer to PrimayServerIndex
			//
            if(0 > hRealm->unPrimaryServer)
            {
                int nIndex;

                for(nIndex = 0; nIndex < hRealm->unRoutingServerCount; nIndex++)
                {

                    if(0 == DMBase_CompareDiamString(&hRealm->oRoutServerList[nIndex].oPeerIdentity, &hPeer->oHostIdentity))
                    {
                        hRealm->unPrimaryServer = nIndex;
                        //DMBase_SetPendingMsgListEntry(hDiameterContext_io, hRealm, hPeer);
                        hPeer->ppvPendingMsgList[hPeer->unPendingMsgListCount++] = (void**)&hRealm->poPendingMsgQueue;
                        break;
                    }
                }
            }
            else
            {
                int nIndex;

                for(nIndex = 0; nIndex < hRealm->unRoutingServerCount; nIndex++)
                {

                    if(0 == DMBase_CompareDiamString(&hRealm->oRoutServerList[nIndex].oPeerIdentity, &hPeer->oHostIdentity))
                    {
                        if(hRealm->oRoutServerList[nIndex].unPriority < hRealm->oRoutServerList[hRealm->unPrimaryServer].unPriority)
                        {
                            HPEERTABLEENTRY hActiveServer = NULL;
                            DMBase_LookUpPeerTableEntry(hDiameterContext_io, hRealm->oRoutServerList[hRealm->unPrimaryServer].oPeerIdentity,
                                                        (void**)&hActiveServer);
                            DMBase_ClearPendingMsgListEntry(hDiameterContext_io,hRealm, hActiveServer);
                            hRealm->unPrimaryServer = nIndex;
                            //DMBase_SetPendingMsgListEntry(hDiameterContext_io, hRealm, hPeer);
                            hPeer->ppvPendingMsgList[hPeer->unPendingMsgListCount++] = (void**)&hRealm->poPendingMsgQueue;
                            break;
                        }
                    }
                }
            }
        }
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SwitchToAlternateServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                  HREALMTABLEENTRY      hRealm)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");


    unsigned int unActiveServerPriority = hRealm->oRoutServerList[hRealm->unPrimaryServer].unPriority;

    int nAlternateServerPriority = 0xffff;
    int nAlternateServer = -1;
    HPEERTABLEENTRY hAlternateServer = NULL;
    int i;

    for(i = 0; i<hRealm->unRoutingServerCount; i++)
    {
        if(hRealm->oRoutServerList[i].unPriority > unActiveServerPriority &&
           hRealm->oRoutServerList[i].unPriority < nAlternateServerPriority)
        {
            HPEERTABLEENTRY hPeer = NULL;
            DMBase_LookUpPeerTableEntry(hDiamStackContext_io, hRealm->oRoutServerList[i].oPeerIdentity, (void**)&hPeer);
            if(NULL != hPeer && (I_Open == hPeer->oPeerState || R_Open == hPeer->oPeerState))
            {
                nAlternateServer = i;
                nAlternateServerPriority = hRealm->oRoutServerList[i].unPriority;
                hAlternateServer = hPeer;
            }
        }
    }

    if(-1 != nAlternateServer)
    {
        hRealm->unPrimaryServer = nAlternateServer;
        hAlternateServer->ppvPendingMsgList[hAlternateServer->unPendingMsgListCount++] = (void**)&hRealm->poPendingMsgQueue;
    }
    else
    {
        hRealm->unPrimaryServer = -1;
        return DMBase_Retval_Failure;
    }


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SendPendingMsgToAlternateServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                          HREALMTABLEENTRY      hRealm)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    HPEERTABLEENTRY hPeer = NULL;
    DMBase_LookUpPeerTableEntry(hDiamStackContext_io, hRealm->oRoutServerList[hRealm->unPrimaryServer].oPeerIdentity,
                                (void**)&hPeer);
    if(NULL == hPeer)
    {
        return DMBase_Retval_Failure;
    }
    if(I_Open != hPeer->oPeerState && R_Open == hPeer->oPeerState)
    {
        return DMBase_Retval_Failure;
    }

    DMBase_SList* poPendingMsgQueue = hRealm->poPendingMsgQueue;
    HFAILOVERSUPPORTDATA hSupportData = NULL;

    for(;NULL != poPendingMsgQueue; DMBase_SListGetNextNode(hDiamStackContext_io,
                                    poPendingMsgQueue, &poPendingMsgQueue))
    {
        hSupportData = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, poPendingMsgQueue, (void**)&hSupportData);
        DMBase_SendMessageToPeer(hDiamStackContext_io, hPeer, hSupportData->hDiamMsg);
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SwitchToPrimaryServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                HREALMTABLEENTRY hRealm,
                                                HPEERTABLEENTRY hPeer_i)
{

    if(hRealm->unPrimaryServer > 0)
    {
        HPEERTABLEENTRY hActivePeer = NULL;
        DMBase_LookUpPeerTableEntry(hDiamStackContext_io, hRealm->oRoutServerList[hRealm->unPrimaryServer].oPeerIdentity, (void**)&hActivePeer);
        if(NULL != hActivePeer)
        {
            DMBase_ClearPendingMsgListEntry(hDiamStackContext_io, hRealm, hActivePeer);
        }
    }

    int i;

    for(i = 0; i<hRealm->unRoutingServerCount; i++)
    {
        if(0 == DMBase_CompareDiamString(&hPeer_i->oHostIdentity, &hRealm->oRoutServerList[i].oPeerIdentity))
        {
            hRealm->unPrimaryServer = i;
            hPeer_i->ppvPendingMsgList[hPeer_i->unPendingMsgListCount++] = (void**)&hRealm->poPendingMsgQueue;
            break;
        }
    }

    return DMBase_Retval_Success;
}

int DMBase_HasHighPriority(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                HREALMTABLEENTRY hRealm,
                                                HPEERTABLEENTRY hPeer_i)
{
     int i;
     int nResult = 0;
    if(hRealm->unPrimaryServer < 0)
    {
         return 1;
    }

    for(i = 0; i<hRealm->unRoutingServerCount; i++)
    {
        if(0 == DMBase_CompareDiamString(&hPeer_i->oHostIdentity, &hRealm->oRoutServerList[i].oPeerIdentity))
        {
            if(hRealm->oRoutServerList[i].unPriority < hRealm->oRoutServerList[hRealm->unPrimaryServer].unPriority)
            {
                nResult = 1;
                break;
            }
        }
    }

     return nResult;
}

t_DiamAPIReturnVal DMBase_Failback(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                   HPEERTABLEENTRY       hPeer_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    int nCount;
    HREALMTABLEENTRY hRealm;
    t_RealmTable* poRealmTabel = hDiamStackContext_io->poRealmTable;

    for(nCount = 0; nCount < poRealmTabel->oRealmHashTable.unHashKeyCount; nCount++)
    {
        hRealm = NULL;
        DMBase_LookupRealmTableByHashKey(hDiamStackContext_io,
                                     poRealmTabel->oRealmHashTable.oHashKeys[nCount],
                                     &hRealm);
        if(DMBase_HasHighPriority(hDiamStackContext_io, hRealm, hPeer_i))
        {
            DMBase_SwitchToPrimaryServer(hDiamStackContext_io, hRealm, hPeer_i);
            /*if(DMBase_Retval_Success == )
            {
                DMBase_SendPendingMsgToAlternateServer(hDiamStackContext_io, hRealm);
            }*/
        }
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

int DMBase_IsPrimaryServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                    HREALMTABLEENTRY      hRealmTableEntry_i,
                    HPEERTABLEENTRY       hPeer_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    int nCmpResult = 0;

    if(0 < hRealmTableEntry_i->unRoutingServerCount)
    {
        if(0 == DMBase_CompareDiamString(&hPeer_i->oHostIdentity,
                &hRealmTableEntry_i->oRoutServerList[hRealmTableEntry_i->unPrimaryServer].oPeerIdentity))
        {
            nCmpResult = 1;
        }
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return nCmpResult;
}

t_DiamAPIReturnVal DMBase_ExecuteFailoverStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                      HPEERTABLEENTRY       hPeer_i,
                                                      t_FailoverSMEvent     oFSMEvent_i,
                                                      void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    if( NULL == hDiamStackContext_io->oFSMActions[hPeer_i->oPCB.oStatus][oFSMEvent_i])
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Status/Event Mappinga.\n");
        return DMBase_Retval_Null_Pointer;
    }
    else
    {
       return hDiamStackContext_io->oFSMActions[hPeer_i->oPCB.oStatus][oFSMEvent_i](hDiamStackContext_io,
                                                                                             hPeer_i,
                                                                                             oFSMEvent_i,
                                                                                             pvData);
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Okay_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                      HPEERTABLEENTRY       hPeer_i,
                                      t_FailoverSMEvent     oFSMEvent_i,
                                      void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, false);
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Okay_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData)
 {
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Okay_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(hPeer_i->bIsWatchdogSupported)
    {
        if(!hPeer_i->oPCB.bPending)
        {
            DMBase_SendDWR(hDiamStackContext_io, hPeer_i);
            DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, true);
        }
        else if(hPeer_i->oPCB.bPending)
        {
            //Failover
            //DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
            DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_SUSPECT);
        }
    }

    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Okay_ConnectionDown(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                              HPEERTABLEENTRY       hPeer_i,
                                              t_FailoverSMEvent     oFSMEvent_i,
                                              void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    //Failover
    DMBase_Failover(hDiamStackContext_io, hPeer_i);
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_DOWN);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Suspect_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, false);
    //Failback
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_OKAY);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Suspect_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    // Failback
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_OKAY);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Suspect_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                               HPEERTABLEENTRY       hPeer_i,
                                               t_FailoverSMEvent     oFSMEvent_i,
                                               void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    //Close Connection
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_DOWN);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Suspect_ConnectionDown(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                 HPEERTABLEENTRY       hPeer_i,
                                                 t_FailoverSMEvent     oFSMEvent_i,
                                                 void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    //Close Connection
    hPeer_i->oPeerState = Closed;
    //TODO: Execute PeerStateMachine here for closing

    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_DOWN);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Down_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                      HPEERTABLEENTRY       hPeer_i,
                                      t_FailoverSMEvent     oFSMEvent_i,
                                      void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, false);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Down_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    // Nothing TODO....

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Down_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_ConnectToPeer(hDiamStackContext_io, hPeer_i);
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Down_ConnectionUp(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(hPeer_i->bIsWatchdogSupported)
    {
        hPeer_i->oPCB.usNumDWA = 0;
        DMBase_SendDWR(hDiamStackContext_io, hPeer_i);
        DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, true);
        DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_REOPEN);
    }
    else
    {
        DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_OKAY);
        DMBase_Failback(hDiamStackContext_io, hPeer_i);
    }
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_Reopen_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                        HPEERTABLEENTRY       hPeer_i,
                                        t_FailoverSMEvent     oFSMEvent_i,
                                        void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(2 == hPeer_i->oPCB.usNumDWA)
    {
        DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, false);
        hPeer_i->oPCB.usNumDWA++;
        DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_OKAY);
        DMBase_Failback(hDiamStackContext_io, hPeer_i);
    }
    else if(2 > hPeer_i->oPCB.usNumDWA)
    {
        DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, false);
        hPeer_i->oPCB.usNumDWA++;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Reopen_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                           HPEERTABLEENTRY       hPeer_i,
                                           t_FailoverSMEvent     oFSMEvent_i,
                                           void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Reopen_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                              HPEERTABLEENTRY       hPeer_i,
                                              t_FailoverSMEvent     oFSMEvent_i,
                                              void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(!hPeer_i->oPCB.bPending)
    {
        DMBase_SendDWR(hDiamStackContext_io, hPeer_i);
        DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
        DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, true);
    }
    else if(true == hPeer_i->oPCB.bPending && 0 > hPeer_i->oPCB.usNumDWA)
    {
        //Close connection
        DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
        DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_DOWN);
    }
    else if(true == hPeer_i->oPCB.bPending && 0 <= hPeer_i->oPCB.usNumDWA)
    {
        hPeer_i->oPCB.usNumDWA = -1;
        DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Reopen_ConnectionDown(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                HPEERTABLEENTRY       hPeer_i,
                                                t_FailoverSMEvent     oFSMEvent_i,
                                                void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    //Close Connection
    hPeer_i->oPeerState = Closed;

    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_DOWN);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Initial_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SetPCBPendingFlag(&hPeer_i->oPCB, false);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Initial_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    // Nothind ToDo.....

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Initial_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                               HPEERTABLEENTRY       hPeer_i,
                                               t_FailoverSMEvent     oFSMEvent_i,
                                               void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(Initiator == hPeer_i->oPeerConfiguredRole)
    {
    	DMBase_ConnectToPeer(hDiamStackContext_io, hPeer_i);
    }
    else
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Unable to connect. Server configured Role is responder.\n");
    }
    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Initial_ConnectionUp(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                               HPEERTABLEENTRY       hPeer_i,
                                               t_FailoverSMEvent     oFSMEvent_i,
                                               void*                 pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SetWatchdog(hDiamStackContext_io, hPeer_i);
    DMBase_SetPCBStatus(&hPeer_i->oPCB, PS_OKAY);
    DMBase_SetActiveServer(hDiamStackContext_io, hPeer_i);
    //DMBase_FillPendingMsgList(hDiamStackContext_io, hPeer_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


int DMBase_FreeFailoverSupportData(void** ppvData)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	HFAILOVERSUPPORTDATA hData = (HFAILOVERSUPPORTDATA)*ppvData;
	HDIAMETERSTACKCONTEXT hDiamStackContext = hData->hDiamMsg->hDiameterStackContext;
	DMBase_DestroyDiaMessage(hDiamStackContext, &hData->hDiamMsg);

    DMBase_Free(hDiamStackContext, ppvData);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return 0;
}




t_DiamAPIReturnVal DMBase_InitWatchDogTimer(HDIAMETERSTACKCONTEXT hDiamStackContext_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer.\n");
		return DMBase_Retval_Null_Pointer;
	}

	DMBASE_HASH_HANDLE hPeerTable = hDiamStackContext_io->poPeerTable->hHashTableHandle;
	DMBase_HashTableTraverseAllEntries(	hDiamStackContext_io,
										hPeerTable,
										DMBase_StartWatchDogTimerCallback,
										(void*)hDiamStackContext_io);
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return DMBase_Retval_Success;
}

void DMBase_StartWatchDogTimerCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;
	HPEERTABLEENTRY hPeerTableEntry = (HPEERTABLEENTRY)r_hAMPS_APP_DATA_HANDLE;

	DMBase_SetWatchdog(hDiamStackContext, hPeerTableEntry);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");


}
