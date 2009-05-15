
#include "dmbase_peer_mgmt.h"

#include "dmbase_utility.h"
#include "dmbase_transport_mgmt.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_parser.h"
#include "dmbase_msgvalidate.h"
#include "dmbase_peerstatemachine.h"
#include "dmbase_failover_failback.h"

extern int g_nDiamBaseTraceID;



/******************************************************************************
** Function Name:
**			DMBase_CreatePeerTable
**
** Description:
**		This function creates peer table.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiamStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
** Return:
**		A t_DiamAPIReturnVal value specify whether peer table is
**		successfully created or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_CreatePeerTable ( HDIAMETERSTACKCONTEXT  hDiamStackContext_io )
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
		return DMBase_Retval_Null_Pointer;
	}

    if(DMBase_Retval_Success != DMBase_CreatePeerTableObject(hDiamStackContext_io,&(hDiamStackContext_io->poPeerTable)))
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Peer Table Object Creation Failed.\n");
        return DMBase_Retval_Failure;
    }
    if(DMBase_Retval_Success != DMBase_CreateHashTable( hDiamStackContext_io, DMBASE_HASHTABLE_MAX_SIZE,
					&(hDiamStackContext_io->poPeerTable->hHashTableHandle), NULL))
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Hash Table Creation Failed.\n");
        return DMBase_Retval_Failure;
    }


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;

}

/******************************************************************************
** Function Name:
**			DMBase_CreatePeerTableObject
**
** Description:
**		This function create a peer table object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  PeerTableObject** ppoPeerTableObject_o
**			type: output
**			detail: this is a pointer to a pointer which points
**				to newly created peer table object
**
** Return:
**		An t_DiamAPIReturnVal value specify whether peer table object
**		created successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_CreatePeerTableObject( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                 t_PeerTable**          ppoPeerTableObject_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == ppoPeerTableObject_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io, (void **)ppoPeerTableObject_io, sizeof(t_PeerTable)))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Memory Allocation Failed.\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**		 	DMBase_PopulatePeerTable
**
** Description:
**		This function build peer table with given list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiamStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBase_SList* pPeerList_i
**			type: output
**			detail: this is list of peers used to build peer table.
**
** Return:
**		A t_DiamAPIReturnVal value specify whether peer table is
**		successfully build or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_PopulatePeerTable ( 	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
												DMBase_SList*           poPeerList_i)
{


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == poPeerList_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    DMBase_SList* poList = poPeerList_i;
    HPEERTABLEENTRY  hPeerTableEntry = NULL;

    while(NULL != poList)
    {
        hPeerTableEntry = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, poList, (void**)&hPeerTableEntry);
        if(DMBase_Retval_Success != DMBase_InsertPeerTableEntry(hDiamStackContext_io, hPeerTableEntry))
        {
        	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Peer table entry insertion failed");
        	return DMBase_Retval_Failure;
        }

        DMBase_SListGetNextNode(hDiamStackContext_io, poList, &poList);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_InsertPeerTableEntry(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
												HPEERTABLEENTRY			hPeerTableEntry_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerTableEntry_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    t_DiamHashTableKey oHashTableKey;
    DMBase_MemsetZero(&oHashTableKey, sizeof(t_DiamHashTableKey));
    DMBase_CopyDiamStrToNSizedCharArray(oHashTableKey.puchKey,
										DMBASE_HASH_TABLE_KEY_SIZE,
										hPeerTableEntry_i->oHostIdentity);
    oHashTableKey.unKeyLength = strlen(oHashTableKey.puchKey);

    if(DMBase_Retval_Success != DMBase_HashTableInsert(hDiamStackContext_io,
														hDiamStackContext_io->poPeerTable->hHashTableHandle,
														hPeerTableEntry_i,
														&oHashTableKey))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to insert Peer Table entry.\n");
        return DMBase_Retval_Failure;
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_LookUpPeerTableEntry(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												t_DiamOctetString 		oPeerIdentity_i,
												HPEERTABLEENTRY* 		phPeerTableEntry_o)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamHashTableKey oHashTablekey;
    DMBase_MemsetZero(&oHashTablekey, sizeof(t_DiamHashTableKey));
    DMBase_CopyDiamStrToNSizedCharArray(oHashTablekey.puchKey, DMBASE_HASH_TABLE_KEY_SIZE, oPeerIdentity_i);
    oHashTablekey.unKeyLength = strlen(oHashTablekey.puchKey);

    if ( DMBase_Retval_Not_Found == DMBase_HashTableSearch(hDiamStackContext_io,
															hDiamStackContext_io->poPeerTable->hHashTableHandle,
															&oHashTablekey,
															(void**)phPeerTableEntry_o ))
    {

        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Value not found\n");
        return DMBase_Retval_Failure;
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_RemovePeerTableEntry(HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
												t_DiamOctetString*		poPeerIdentity_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ShowPeerTable(HDIAMETERSTACKCONTEXT	hDiamStackContext_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer.\n");
		return DMBase_Retval_Null_Pointer;
	}


	printf("\r\n\r\n\r\n%25s\r\n","Peer Table");
	printf("%25s\r\n","==========");
	printf("%-30s%10s\r\n", "Peer Host Identity", "Status");
	printf("%s\r\n", "========================================");

	DMBASE_HASH_HANDLE hPeerTable = hDiamStackContext_io->poPeerTable->hHashTableHandle;
	DMBase_HashTableTraverseAllEntries(	hDiamStackContext_io,
										hPeerTable,
										DMBase_ShowPeerTableEntryCallback,
										(void*)hDiamStackContext_io);

	printf("%s\r\n\r\n", "========================================");

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

void DMBase_ShowPeerTableEntryCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	static unsigned char oPeerStateStrings[][50]= {
													"[Closed]",
													"[Wait_Conn_Ack]",
													"[Wait_I_CEA]" ,
													"[Wait_Conn_Ack_Elect]",
													"[Wait_Returns]",
													"[R_Open]",
													"[I_Open]",
													"[Closing]"
													};

	HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;
	HPEERTABLEENTRY hPeerTableEntry = (HPEERTABLEENTRY)r_hAMPS_APP_DATA_HANDLE;

	unsigned char ucPeerId[50] = {0};
	DMBase_CopyDiamStrToNSizedCharArray(ucPeerId,50, hPeerTableEntry->oHostIdentity);

	printf("%-30s%10s\r\n", ucPeerId, oPeerStateStrings[hPeerTableEntry->oPeerState]);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");


}


t_DiamAPIReturnVal DMBase_CreatePeerTableEntry(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY*		phPeerTableEntry_io,
												t_DiamOctetString	   	oHostIdentity_i,
												t_DiamOctetString	   	oIPAddress_i,
												unsigned int          	unPort_i,
												t_PeerRole            	oConfiguredRole_i,
												_Bool                 	bIsStatic_i,
												_Bool                 	bIsTLSEnable_i,
												_Bool        			bIsWatchgogSupported_i,
												unsigned int			unWatchdogTimerDelay_i)
{


    if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io, (void**)phPeerTableEntry_io, sizeof(t_PeerTableEntry)))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to Create Peer table entry.\n");
        return DMBase_Retval_Failure;
    }


    if(DMBase_Retval_Success != DMBase_SetHostIdentityInPeerTableEntry(	hDiamStackContext_io,
																		*phPeerTableEntry_io,
																		oHostIdentity_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to set Host identity.\n");
        return DMBase_Retval_Failure;
    }

    (*phPeerTableEntry_io)->oPeerConfiguredRole = oConfiguredRole_i;
    (*phPeerTableEntry_io)->hDiameterStackContext = hDiamStackContext_io;
    (*phPeerTableEntry_io)->bIsWatchdogSupported = bIsWatchgogSupported_i;
    (*phPeerTableEntry_io)->bIsStatic = bIsStatic_i;
    (*phPeerTableEntry_io)->bIsTLSEnabled = bIsTLSEnable_i;

    t_DiameterTransportObject oTranportObj;
    DMBase_MemsetZero(&oTranportObj, sizeof(t_DiameterTransportObject));

    oTranportObj.oTransportType = TCP;
    oTranportObj.oDiamTCPTransport.oIPAddrType = IP_v4;
    oTranportObj.oDiamTCPTransport.oIPAddress = oIPAddress_i;
    oTranportObj.oDiamTCPTransport.oFQDN = oHostIdentity_i;
    oTranportObj.oDiamTCPTransport.unPort = unPort_i;


    DMBase_SetPeerConfiguredTransportObject(hDiamStackContext_io, *phPeerTableEntry_io, &oTranportObj);

    int unsigned unTimerDelay = (TWINIT > unWatchdogTimerDelay_i*1000 ? TWINIT:unWatchdogTimerDelay_i*1000); //To convert timer delay into milliseconds, Multiplied it by 1000


    DMBase_SetPCBValues(&(*phPeerTableEntry_io)->oPCB, PS_INITIAL, FALSE, unTimerDelay, 0);

    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetHostIdentityInPeerTableEntry
**
** Description:
**		This function sets a host identity in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  t_DiamOctetString StrHostIdentity_i
**			type:input
**			detail: this is host entity.
** Return:
**		A t_DiamAPIReturnVal value specify whether host identity is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetHostIdentityInPeerTableEntry ( HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
                                                            HPEERTABLEENTRY         hPeerEntry_o,
                                                            t_DiamOctetString       oHostIdentity_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


	if (DMBase_Retval_Success !=  DMBase_CopyDiamString( & (hPeerEntry_o->oHostIdentity) ,&oHostIdentity_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem in Memory Allocation.\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetStateInPeerTableEntry
**
** Description:
**		This function sets a Peer's State in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  t_PeerState oPeerStatus_i
**			type:input
**			detail: this is Peer's Status.
** Return:
**		A t_DiamAPIReturnVal value specify whether peer's status is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetStateInPeerTableEntry ( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                     HPEERTABLEENTRY        hPeerEntry_o,
                                                     t_PeerState 			oPeerState_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


    hPeerEntry_o->oPeerState = oPeerState_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetRoleInPeerTableEntry
**
** Description:
**		This function sets a Peer's Role in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  t_PeerRole oPeerRole_i
**			type:input
**			detail: this is Peer's Role.
** Return:
**		A t_DiamAPIReturnVal value specify whether peer's role is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetPeerRoleInPeerTableEntry ( HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
                                                        HPEERTABLEENTRY     	hPeerEntry_o,
                                                        t_PeerRole 				oPeerRole_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


    hPeerEntry_o->oPeerConnectionRole = oPeerRole_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetStaticStatusInPeerTableEntry
**
** Description:
**		This function sets static status in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
** Return:
**		A t_DiamAPIReturnVal value specify whether static status is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetStaticStatusInPeerTableEntry ( HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
                                                            HPEERTABLEENTRY         hPeerEntry_o,
                                                            _Bool                   bIsStatic_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    hPeerEntry_o->bIsStatic = bIsStatic_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_SetExpiryTimeInPeerTableEntry
**
** Description:
**		This function sets expiration time in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  t_DiamTime ExpiryTime_i
**			type:input
**			detail: this is expiration time of peer table entry.
** Return:
**		A t_DiamAPIReturnVal value specify whether expiration time is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SetExpiryTimeInPeerTableEntry( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                         HPEERTABLEENTRY        hPeerEntry_o,
                                                         t_DiamTime             ExpiryTime_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

//	TDOD: discuss about time format
    hPeerEntry_o->oExpiryTime.unNumOfOctets = ExpiryTime_i.unNumOfOctets;
    * ((hPeerEntry_o->oExpiryTime).punUnsigned32) = * (ExpiryTime_i.punUnsigned32);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_SetTLSEnableStatusInPeerTableEntry
**
** Description:
**		This function sets TLS enable status in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  _Bool bIsTLSEnabled_i
**			type:input
**			detail: this is TLS enable status of peer table entry.
** Return:
**		A t_DiamAPIReturnVal value specify whether TLS enable status is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SetTLSEnableStatusInPeerTableEntry( HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
                                                              HPEERTABLEENTRY 		hPeerEntry_o,
                                                              _Bool 				bIsTLSEnabled_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


    hPeerEntry_o->bIsTLSEnabled = bIsTLSEnabled_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_SetOptionalTLSDataInPeerTableEntry
**
** Description:
**		This function sets optional TLS data in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  t_TLSData OptTLSData
**			type:input
**			detail: this is Optional TLS data of peer table entry.
** Return:
**		A t_DiamAPIReturnVal value specify whether optional TLS data is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SetOptionalTLSDataInPeerTableEntry( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                              HPEERTABLEENTRY       hPeerEntry_o,
                                                              t_TLSData             OptTLSData_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

     hPeerEntry_o->oOptionalTLSData = OptTLSData_i;

     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**			DMBase_SetTransportObjectInPeerTableEntry
**
** Description:
**		This function sets transport object in peer table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HPEERTABLEENTRY hPeerEntry_o
**			type: output
**			detail: this is a peer table entry handle
**
**		  t_DiameterTransportObject TransportObject_i
**			type:input
**			detail: this is transport object of peer table entry.
** Return:
**		A t_DiamAPIReturnVal value specify whether transport object is
**		successfully set in peer table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetPeerConfiguredTransportObject(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
                                                            HPEERTABLEENTRY         hPeerEntry_o,
                                                            HTRANSPORTOBJECT		hTransportObj_i )
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o || NULL == hTransportObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(DMBase_Retval_Success != DMBase_CreateTransportObject(	hDiamStackContext_io,
																&(hPeerEntry_o->hConfiguredTransport),
																hTransportObj_i->oTransportType,
																hTransportObj_i->oDiamTCPTransport.oFQDN,
																hTransportObj_i->oDiamTCPTransport.oIPAddress,
																hTransportObj_i->oDiamTCPTransport.unPort,
																hTransportObj_i->oDiamTCPTransport.oIPAddrType,
																hTransportObj_i->pvTransportLayerHandle))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create transport object.\n");
		return DMBase_Retval_Failure;
	}

   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
   return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetPeerInitiatorTransportObject( 	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
															HPEERTABLEENTRY         hPeerEntry_o,
                                                            HTRANSPORTOBJECT		hTransportObj_i )
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o || NULL == hTransportObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(DMBase_Retval_Success != DMBase_CreateTransportObject(	hDiamStackContext_io,
																&(hPeerEntry_o->hInitiatorTransport),
																hTransportObj_i->oTransportType,
																hTransportObj_i->oDiamTCPTransport.oFQDN,
																hTransportObj_i->oDiamTCPTransport.oIPAddress,
																hTransportObj_i->oDiamTCPTransport.unPort,
																hTransportObj_i->oDiamTCPTransport.oIPAddrType,
																hTransportObj_i->pvTransportLayerHandle))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create transport object.\n");
		return DMBase_Retval_Failure;
	}

   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
   return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetPeerResponderTransportObject( 	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
															HPEERTABLEENTRY         hPeerEntry_o,
                                                            HTRANSPORTOBJECT		hTransportObj_i )
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o || NULL == hTransportObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


	if(DMBase_Retval_Success != DMBase_CreateTransportObject(	hDiamStackContext_io,
																&(hPeerEntry_o->hResponderTransport),
																hTransportObj_i->oTransportType,
																hTransportObj_i->oDiamTCPTransport.oFQDN,
																hTransportObj_i->oDiamTCPTransport.oIPAddress,
																hTransportObj_i->oDiamTCPTransport.unPort,
																hTransportObj_i->oDiamTCPTransport.oIPAddrType,
																hTransportObj_i->pvTransportLayerHandle))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create transport object.\n");
		return DMBase_Retval_Failure;
	}


   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
   return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_AddPeerSupportedApp(  HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
												HPEERTABLEENTRY         hPeerEntry_o,
                                                t_DiamAppInfo			oSupportedApp_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(hPeerEntry_o->unSupportedAppCount == DMBASE_MAX_PEER_SUPPORTED_APP)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Maximum peer supported application limit exceed.\n");
        return DMBase_Retval_Limit_Exceed;
    }

    hPeerEntry_o->oSupportedAppList[hPeerEntry_o->unSupportedAppCount].unAppID = oSupportedApp_i.unAppID;
    hPeerEntry_o->oSupportedAppList[hPeerEntry_o->unSupportedAppCount].oAppType = oSupportedApp_i.oAppType;
    hPeerEntry_o->oSupportedAppList[hPeerEntry_o->unSupportedAppCount].unVendorID = oSupportedApp_i.unVendorID;
    hPeerEntry_o->unSupportedAppCount++;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ConnectToPeer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HPEERTABLEENTRY 		hPeerTableEntry_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hPeerTableEntry_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    t_DiamAPIReturnVal oReturnValue = DMBase_ExecutePeerStateMachine(hDiamStackContext_io,
																		hPeerTableEntry_io,
																		NULL,
																		Start,
																		NULL);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnValue;
}

t_DiamAPIReturnVal DMBase_ConnectToPeerByName(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												t_DiamOctetString 		oPeerIdentity_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }

    HPEERTABLEENTRY hPeer = NULL;

    if(DMBase_Retval_Success != DMBase_LookUpPeerTableEntry(hDiamStackContext_io,
															oPeerIdentity_i,
															&hPeer))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,
									" No such peer exist in Peer Table Entry.\n");
    	return DMBase_Retval_Not_Found;
    }

    DMBase_ConnectToPeer(hDiamStackContext_io, hPeer );

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SendMessageToPeer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_io,
											HDIAMETERMESSAGE 		hDiamMsg_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    t_DiamAPIReturnVal oReturnVal = DMBase_ExecutePeerStateMachine(	hDiamStackContext_io,
																	hPeerTableEntry_io,
																	hDiamMsg_i,
																	Send_Message,
																	NULL);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnVal;

}



