#include "dmbase_utility.h"
#include "dmbase_transport_mgmt.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_parser.h"
#include "dmbase_msgvalidate.h"
#include "dmbase_peerstatemachine.h"

#include "AMPS_API.h"
#include "AMPS_Defines.h"

#include <stdbool.h>

extern int g_nDiamBaseTraceID;


/******************************************************************************
** Function Name:
**			DMBase_OpenTransportConnection
**
** Description:
**		This function open transport connection with the peer.
**
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			type: input/output
**			detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransObj_i
**			type: input
**			detail: this is peer transport object which used to
**				open transport connection with peer.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether transport connection is
**		successfully opened or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_OpenTransportConnection(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io ,
													HTRANSPORTOBJECT 		hTransportObj_i,
													void* 					pvAppDataHandle_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hTransportObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(TCP == hTransportObj_i->oTransportType)
    {
		 t_TCPOpen_Params	oTCPOpenParams = {0};
		 oTCPOpenParams.nFixedMsgSize = DMBASE_MSG_HEADER_SIZE_IN_BYTES;
		 oTCPOpenParams.nMinMsgSize = 0;
		 oTCPOpenParams.pfMallocCallback = NULL;
		 oTCPOpenParams.pfReAllocCallback = NULL;
		 oTCPOpenParams.pfFreeCallback = NULL;
		 oTCPOpenParams.pfRecvDataCallback = DMBase_ReceiveMessageOnTCP;
		 oTCPOpenParams.pfCloseEvtCallback = DMBase_ConnectionCloseNotification;
		 oTCPOpenParams.pfConnCfmCallback = DMBase_ConnectConfirm;
		 oTCPOpenParams.pvAppDataHandle = pvAppDataHandle_i;


        if(DMBase_Retval_Success != DMBase_OpenTCPConnection(	hDiamStackContext_io,
																hTransportObj_i,
																oTCPOpenParams))
        {
            DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in opening transport connection\n");
            return DMBase_Retval_Failure;
        }

    }
    else if(SCTP == hTransportObj_i->oTransportType)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Currently SCTP is not supported.\n");
        return DMBase_Retval_Not_Supported;
    }
    else
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid transport type.\n");
        return DMBase_Retval_Not_Supported;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}




/******************************************************************************
** Function Name:
**			DMBase_CreateTransportObject
**
** Description:
**		This function create a transport object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT* pTransportObjectHandle_io
**			type: output
**			detail: this is a pointer to newly created transport
**				object's handle.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether transport object
**		created successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_CreateTransportObject ( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                  HTRANSPORTOBJECT*     phTransportObject_io,
                                                  t_DiamTransportType	oTransportType_i,
                                                  t_DiamOctetString		oFQDN_i,
                                                  t_DiamOctetString		oIPAddress_i,
                                                  unsigned int			unPort_i,
                                                  t_IPAddrType			oIPType_i,
                                                  void*					pvNetHandle_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == phTransportObject_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(DMBase_Retval_Success != DMBase_Malloc(	hDiamStackContext_io,
												(void **)phTransportObject_io,
												sizeof(t_DiameterTransportObject)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Memory Allocation Failed.\n");
        return DMBase_Retval_Failure;
    }

    if(TCP == oTransportType_i)
    {
    	(*phTransportObject_io)->oTransportType = oTransportType_i;
    	(*phTransportObject_io)->pvTransportLayerHandle = pvNetHandle_i;

    	DMBase_SetTCPTransportValue(hDiamStackContext_io,
									&(*phTransportObject_io)->oDiamTCPTransport,
									oIPAddress_i,
									oFQDN_i,
									unPort_i,
									oIPType_i);

    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_StartListeners
**
** Description:
**		This function starts listeners for given list of transport
**		objects.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBase_SList* pListenersList_i
**			type: output
**			detail: this is a list of transport objects for which
**				listeners to be started.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether listeners started
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_StartListeners( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                          DMBase_SList*         poListenersList_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == poListenersList_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    DMBase_SList* poList = poListenersList_i;
    HTRANSPORTOBJECT  hTransObject = NULL;

    while(NULL != poList)
    {
    	hTransObject = NULL;

        DMBase_SListGetNodeData(hDiamStackContext_io, poList, (void**)&hTransObject);

        DMBase_ListenForTransportConnections( hDiamStackContext_io, hTransObject);

        DMBase_SListGetNextNode(hDiamStackContext_io, poList, &poList);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_ListenForTransportConnections( HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                         HTRANSPORTOBJECT 		hTransObj_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hTransObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed.\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(TCP == hTransObj_i->oTransportType)
    {

		t_TCPListener_Params	oTCPListenerParams = {0};
		oTCPListenerParams.nFixedMsgSize = 0;
		oTCPListenerParams.nMinMsgSize = DMBASE_MSG_HEADER_SIZE_IN_BYTES;
		oTCPListenerParams.pfCloseEvtCallback = DMBase_ConnectionCloseNotification;
		oTCPListenerParams.pfConnNotifyCallback = DMBase_ConnectionNotification;
		oTCPListenerParams.pfFreeCallback = NULL;
		oTCPListenerParams.pfMallocCallback = NULL;
		oTCPListenerParams.pfReAllocCallback = NULL;
		oTCPListenerParams.pfRecvDataCallback = DMBase_ReceiveMessageOnTCP;
		oTCPListenerParams.pvAppHandle = hDiamStackContext_io;


        if (DMBase_Retval_Failure == DMBase_CreateTCPListenerObject(hDiamStackContext_io,hTransObj_i,oTCPListenerParams))
        {
            DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBASE_CreateTCPListenerObject failed.\n");
            return DMBase_Retval_Failure;
        }
    }
    else if(SCTP == hTransObj_i->oTransportType)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Currently SCTP is not supported.\n");
        return DMBase_Retval_Not_Supported;
    }
    else
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid transport type.\n");
        return DMBase_Retval_Not_Supported;
    }


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_CloseTransportConnection
**
** Description:
**		This function close transport connection with the peer.
**
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			type: input/output
**			detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransObj_i
**			type: input
**			detail: this is peer transport object which used to
**				close transport connection with peer.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether transport connection is
**		successfully closed or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_CloseTransportConnection ( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                     HTRANSPORTOBJECT       hTransportObj_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hTransportObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(TCP == hTransportObj_i->oTransportType)
    {
        if(DMBase_Retval_Success != DMBase_CloseTCPConnection(hDiamStackContext_io, hTransportObj_i))
        {
            DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in closing transport connection\n");
            return DMBase_Retval_Failure;
        }
    }
    else if(SCTP == hTransportObj_i->oTransportType)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Currently SCTP is not supported.\n");
        return DMBase_Retval_Not_Supported;
    }
    else
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid transport type.\n");
        return DMBase_Retval_Not_Supported;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
     return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetDiameterTransportTypeInTransportObject
**
** Description:
**		This function sets transport type in transport object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransportObject_o
**			type: output
**			detail: this is a transport object handle
**
**		  t_DiamTransport TransportType_i
**			type:input
**			detail: this is transport type.
** Return:
**		A t_DiamAPIReturnVal value specify whether transport type is
**		successfully set in transport object or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SetTransportType(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
											HTRANSPORTOBJECT       	hTransportObject_o,
                                            t_DiamTransportType    	oTransportType_i)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hTransportObject_o)
   {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
        return DMBase_Retval_Null_Pointer;
   }
    hTransportObject_o->oTransportType = oTransportType_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**			DMBase_SetDiameterTransport
**
** Description:
**		This function sets transport related values in transport object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransportObject_o
**			type: output
**			detail: this is a transport object handle
**
**		  t_DiamTransport TransportType_i
**			type:input
**			detail: this is transport type.
**
**		  t_DiamOctetString strIPAdress_i
**			type:input
**			detail: this is transport IP address.
**
**		  t_DiamOctetString strFQDN_i
**			type:input
**			detail: this is fully qualified domain name.
**
**		  unsigned int unPort_i
**			type:input
**			detail: this is port number.
**
**		  t_IPAddrType IPAddrType_i
**			type:input
**			detail: this is IP address type.
** Return:
**		A t_DiamAPIReturnVal value specify whether transport related
**		values successfully set in transport object or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal	DMBase_SetTransportObjectValue(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
													HTRANSPORTOBJECT		hDestTransport_io,
													HTRANSPORTOBJECT		hSrcTransportObj_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hDestTransport_io || NULL == hSrcTransportObj_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(TCP == hSrcTransportObj_i->oTransportType)
      {

    	hDestTransport_io->oTransportType = hSrcTransportObj_i->oTransportType;
    	hDestTransport_io->pvTransportLayerHandle	= hSrcTransportObj_i->pvTransportLayerHandle;

  		DMBase_SetTCPTransportValue(hDiamStackContext_io,
  									&hDestTransport_io->oDiamTCPTransport,
  									hSrcTransportObj_i->oDiamTCPTransport.oIPAddress,
  									hSrcTransportObj_i->oDiamTCPTransport.oFQDN,
  									hSrcTransportObj_i->oDiamTCPTransport.unPort,
  									hSrcTransportObj_i->oDiamTCPTransport.oIPAddrType);



      }
      else if(SCTP == hSrcTransportObj_i->oTransportType)
      {
          DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " SCTP currently not supported.\n");
          return DMBase_Retval_Not_Supported;
      }
      else
      {
          DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Protocol not supported.\n");
          return DMBase_Retval_Not_Supported;
      }


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_SetTCPTransportValue(HDIAMETERSTACKCONTEXT    hDiamStackContext_io,
                                               t_DiameterTCPTransport*  poTCPTransport_o,
                                               t_DiamOctetString        oIPAdress_i,
                                               t_DiamOctetString        oFQDN_i,
                                               unsigned int             unPort_i,
                                               t_IPAddrType             oIPAddrType_i )
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == poTCPTransport_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    poTCPTransport_o->unPort = unPort_i;
    poTCPTransport_o->oIPAddrType = oIPAddrType_i;

	if ( DMBase_Retval_Success !=  DMBase_CopyDiamString (&(poTCPTransport_o->oIPAddress),
														   &oIPAdress_i ))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem in Copying Diam String.\n");
		return DMBase_Retval_Failure;
	}

	if ( DMBase_Retval_Success !=  DMBase_CopyDiamString (&(poTCPTransport_o->oFQDN),
														   &oFQDN_i ))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Problem in Copying Diam String.\n");
		return DMBase_Retval_Failure;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_AddIPAdressToTransportObject
**
** Description:
**		This function sets IP address in transport object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransportObject_o
**			type: output
**			detail: this is a transport object handle
**
**		  t_DiamOctetString* pStrIPAddress_i
**			type:input
**			detail: this is IP address string.
** Return:
**		A t_DiamAPIReturnVal value specify whether IP address is
**		successfully set in transport object or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_AddIPAdressToTransportObject( HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
														HTRANSPORTOBJECT        hTransportObject_o,
														t_DiamOctetString*      poIPAddress_i)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    if(NULL == hTransportObject_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(TCP == hTransportObject_o->oTransportType)
    {

        if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io, (void**)&(hTransportObject_o->oDiamTCPTransport.oIPAddress.pucOctetString), strlen(poIPAddress_i->pucOctetString)+1))
        {
            DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in Memory Allocation.\n");
            return DMBase_Retval_Failure;
	}
	strcpy(hTransportObject_o->oDiamTCPTransport.oIPAddress.pucOctetString, poIPAddress_i->pucOctetString);
	hTransportObject_o->oDiamTCPTransport.oIPAddress.unNumOfOctets = strlen(poIPAddress_i->pucOctetString);
    }
    else if(SCTP == hTransportObject_o->oTransportType)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " SCTP currently not supported.\n");
        return DMBase_Retval_Not_Supported;
    }else{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Protocol not supported.\n");
        return DMBase_Retval_Not_Supported;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetDiameterAppContextInTransportObject
**
** Description:
**		This function sets application context in transport object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransportObject_o
**			type: output
**			detail: this is a transport object handle
**
**		  void* pvDiameterAppContext_i
**			type:input
**			detail: this is a void pointer to an application context.
** Return:
**		A t_DiamAPIReturnVal value specify whether application context
**		is successfully set in transport object or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetDiameterAppContextInTransportObject( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                                  HTRANSPORTOBJECT      hTransportObject_o,
                                                                  void*                 pvDiameterAppContext_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    if(NULL == hTransportObject_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
        return DMBase_Retval_Null_Pointer;
    }
    hTransportObject_o->pvDiamAppContext = pvDiameterAppContext_i;
//    printf(" \n ApplicationContext is -- %s \n",  hTransportObject->pDiamAppContext);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**			DMBase_SetTransportLevelHandleInTransportObject
**
** Description:
**		This function sets transport level handle in transport object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransportObject_o
**			type: output
**			detail: this is a transport object handle
**
**		  void* TransportLevelHandle
**			type:input
**			detail: this is a void pointer to an transport level
**				handle.
** Return:
**		A t_DiamAPIReturnVal value specify whether transport level
**		handle is successfully set in transport object or any
**		problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetTransportLevelHandleInTransportObject( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                             HTRANSPORTOBJECT       hTransportObject_o,
                                                             void*                  TransportLevelHandle)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    if(NULL == hTransportObject_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL Pointer Error.\n");
        return DMBase_Retval_Null_Pointer;
    }

    hTransportObject_o->pvTransportLayerHandle = TransportLevelHandle;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_ProcessMessage(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											unsigned char*  		pucMsgBuffer_i,
											t_NetHandleData*		poNetHandleData_io,
											void*					pvNetHanble_i,
											char*					pcIPAddress_i,
											int						nPort_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    HDIAMETERMESSAGE hRcvMsg = NULL;
    t_DiamAPIReturnVal oReturnVal;

    if(DMBase_Retval_Success != (oReturnVal = DMBase_ParseRawDiameterMessage( 	hDiamStackContext_io,
																				pucMsgBuffer_i,
																				&hRcvMsg)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to Parse message.\n");
		goto ExitMe;
	}

    //Perform Message validation here

    if(NULL == poNetHandleData_io->hPeer)
    {
    	oReturnVal = DMBase_SetupPeer(	hDiamStackContext_io,
										hRcvMsg,
										poNetHandleData_io,
										pvNetHanble_i,
										pcIPAddress_i,
										nPort_i);

    }
    else
    {
        t_DiameterPSMEvent oPeerEvent;
        DMBase_CheckEventType(  hDiamStackContext_io, poNetHandleData_io->hPeer, hRcvMsg, &oPeerEvent);
        oReturnVal = DMBase_ExecutePeerStateMachine(hDiamStackContext_io,
													poNetHandleData_io->hPeer,
													hRcvMsg,
													oPeerEvent,
													NULL);
    }



    if(DMBase_Retval_Msg_Stored != oReturnVal)
    {
    	if(DMBase_Retval_Success != (oReturnVal = DMBase_DestroyDiaMessage(hDiamStackContext_io, &hRcvMsg)))
    	{
    		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to destroy message.\n");
    	}
    }

	ExitMe:


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return oReturnVal;


}

t_DiamAPIReturnVal DMBase_SetupPeer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HDIAMETERMESSAGE		hRcvMsg_i,
									t_NetHandleData*		poNetHandleData_io,
									void*					pvNetHanble_i,
									char*					pcIPAddress_i,
									int						nPort_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    unsigned int unCmdCode = 0;
    t_DiamAPIReturnVal oReturnVal;
	t_DiameterTransportObject oDiamTransport;
	t_DiamUTF8String oIPAddress;

    DMBase_GetDiaMsgCmdCodeFromDiamMsg( hDiamStackContext_io, 	hRcvMsg_i, &unCmdCode);
	DMBase_MemsetZero(&oDiamTransport, sizeof(t_DiameterTransportObject));
	DMBase_MemsetZero(&oIPAddress, sizeof(t_DiamUTF8String));

	if(DMBase_Retval_Success != (oReturnVal = DMBase_CopyCharArrayToDiamString(&oIPAddress, pcIPAddress_i)))
	{
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to copy string.\n");
    	goto ExitMe;
	}

	oDiamTransport.oTransportType = TCP;
	oDiamTransport.pvTransportLayerHandle = pvNetHanble_i;
	oDiamTransport.oDiamTCPTransport.oIPAddrType = IP_v4;
	oDiamTransport.oDiamTCPTransport.oIPAddress = oIPAddress;
	oDiamTransport.oDiamTCPTransport.unPort =	nPort_i;

	if(DMBASE_BITMASK_SET_MSG_R_FLAG & hRcvMsg_i->oDiaHeader.ucFlags && DMBASE_MSG_CMD_CODE_CER == unCmdCode )
	{
		HAVP hOriginHostAVP = NULL;
		unsigned char ucPeerId[128] = {0};
		HPEERTABLEENTRY hPeer = NULL;
		t_DiameterIdentity* poOriginHost = NULL;

		DMBase_GetAVP(hDiamStackContext_io, DMBASE_AVP_ORIGIN_HOST, hRcvMsg_i, &hOriginHostAVP);
		poOriginHost = (t_DiameterIdentity*)hOriginHostAVP->pData;
		DMBase_CopyDiamStrToNSizedCharArray(ucPeerId, 128, *poOriginHost);
		oReturnVal = DMBase_LookUpPeerTableEntry(hDiamStackContext_io, *poOriginHost, (void**)&hPeer);

		if(DMBase_Retval_Success == oReturnVal)
		{

			oDiamTransport.oDiamTCPTransport.oFQDN = *poOriginHost;

			oReturnVal = DMBase_ExecutePeerStateMachine(hDiamStackContext_io,
														hPeer,
														hRcvMsg_i,
														R_Conn_CER,
														&oDiamTransport);

			if(DMBase_Retval_Success == oReturnVal)
			{
				printf("Connection established with peer \"%s\"\r\n", ucPeerId);
				poNetHandleData_io->hPeer = hPeer;
				DMBase_ShowPeerTable(hDiamStackContext_io);
			}
			else
			{
				printf("Failed to established connection with peer \"%s\"\r\n", ucPeerId);
			}

		}
		else
		{
			printf("Unknown Peer \"%s\"\r\n", ucPeerId);
		}
	}
	else
	{
		oReturnVal = DMBase_Retval_IncorrectParameters;
	}

	ExitMe:

	if(DMBase_Retval_Success != oReturnVal)
	{
		//Close transport connection
		DMBase_CloseTCPConnection(hDiamStackContext_io, &oDiamTransport);
	}
	DMBase_DeleteDiamString(&oIPAddress);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
	return oReturnVal;

}




/******************************************************************************
** Function Name:
**			DMBase_ConnectionNotification
**
** Description:
**		This callback is executed by AMPS framework when connection is
**		established.
**
** Parameters:
**		  AMPS_HANDLE r_hAMPS_HANDLE
**			 type: input/output
**			 detail : this is a AMPS handle.
**
**		  AMPS_APP_HANDLE hAMPS_APP_HANDLE_i
**			type: output
**			detail: this is a AMPS Application handle
**
**		  AMPS_NET_HANDLE hAMPS_NET_HANDLE_i
**			type:input
**			detail: this is AMPS transport handle.
**
**		  int nPort_i
**			type:input
**			detail: this is port number.
**
**		  char* pcIPAddress_i
**			type:input
**			detail: this is IP address of the peer.
**
** Return:
**		Aa integer value specify whether callback executed
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

int DMBase_ConnectionNotification(  AMPS_HANDLE     r_hAMPS_HANDLE,
                                    AMPS_APP_HANDLE r_hAMPS_APP_HANDLE,
                                    AMPS_NET_HANDLE r_hAMPS_NET_HANDLE,
                                    int             nPort_i,
                                    char*           pcIPAddress_i)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    printf( "\nRequest Received for Connection set up. IP = %s:%d\n",
            pcIPAddress_i,nPort_i);

    HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;

    t_NetHandleData *poNetHandleData = NULL;
    DMBase_Malloc(hDiamStackContext, (void**)&poNetHandleData, sizeof (t_NetHandleData));

    DMBase_SetUsrDataToNetHandle(hDiamStackContext,
                                    r_hAMPS_NET_HANDLE, poNetHandleData);


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return 0;
}


/******************************************************************************
** Function Name:
**			DMBase_ReceiveMessageOnTCP
**
** Description:
**		This callback is executed by AMPS framework when data is
**		received from transport connection.
**
** Parameters:
**		  AMPS_HANDLE r_hAMPS_HANDLE
**			 type: input/output
**			 detail : this is a AMPS handle.
**
**		  AMPS_APP_HANDLE hAMPS_APP_HANDLE_i
**			type: output
**			detail: this is a AMPS Application handle
**
**		  AMPS_NET_HANDLE hAMPS_NET_HANDLE_i
**			type:input
**			detail: this is AMPS transport handle.
**
**		  unsigned char* pucBuff_i
**			type:input
**			detail: this is received data buffer.
**
**      	  int nBuffLength_i
**			type:input
**			detail: this is size of received data buffer.
**
**		  int nPort_i
**			type:input
**			detail: this is port number.
**
**		  char* pcIPAddress_i
**			type:input
**			detail: this is IP address of the peer.
**
** Return:
**		Aa interger value specify whether callback executed
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

int DMBase_ReceiveMessageOnTCP( AMPS_HANDLE     r_hAMPS_HANDLE,
                                AMPS_APP_HANDLE hAMPS_APP_HANDLE_i,
                                AMPS_NET_HANDLE hAMPS_NET_HANDLE_i,
                                unsigned char*  pucBuff_i,
                                int             nBuffLength_i,
                                int             nPort_i,
                                char*           pcIPAddress_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");



    if (0 == nBuffLength_i)
    {
            return 0;
    }

    t_NetHandleData *poNetHandleData = NULL;
    DMBase_GetUsrDataFromNetHandle( hAMPS_APP_HANDLE_i,
									hAMPS_NET_HANDLE_i,
									(void**)&poNetHandleData);
    if(NULL == poNetHandleData)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " No Net handle data available.\n");
    	return 0;
    }

    HDIAMETERSTACKCONTEXT hDiamStackContext = hAMPS_APP_HANDLE_i;
    unsigned int unMsgSize = 0;

    if(!poNetHandleData->bIsHeaderReceived)
    {
        memcpy(poNetHandleData->ucMsgHeader, pucBuff_i, nBuffLength_i);
        DMBase_GiveUIntInHostOrderFor3Bytes(pucBuff_i+DMBASE_MSG_SIZE_OFFSET, &unMsgSize);
        DMBase_SetRecvBuffStatusToNetHandle(r_hAMPS_HANDLE,
											hAMPS_NET_HANDLE_i,
											AMPS_MSG_PENDING,
											unMsgSize-DMBASE_MSG_HEADER_SIZE_IN_BYTES);
        poNetHandleData->bIsHeaderReceived = TRUE;
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
        return 0;
    }

    unMsgSize = DMBASE_MSG_HEADER_SIZE_IN_BYTES+nBuffLength_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_DEBUG, "Data received Size = %d Bytes\n" , unMsgSize);


    unsigned char *pucMsgBuffer = NULL;

    t_DiamAPIReturnVal oReturnVal;
    if(DMBase_Retval_Success != (oReturnVal = DMBase_Malloc(hDiamStackContext, (void**)&pucMsgBuffer, unMsgSize)))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to allocate memory.\n");
    	goto ExitMe;
    }

    memcpy(pucMsgBuffer, poNetHandleData->ucMsgHeader, DMBASE_MSG_HEADER_SIZE_IN_BYTES);
    memcpy(pucMsgBuffer+DMBASE_MSG_HEADER_SIZE_IN_BYTES, pucBuff_i, nBuffLength_i);

    DMBase_SetRecvBuffStatusToNetHandle(r_hAMPS_HANDLE,
										hAMPS_NET_HANDLE_i,
										AMPS_MSG_COMPLETED,
										0);

    DMBase_SetRecvBuffStatusToNetHandle(r_hAMPS_HANDLE,
										hAMPS_NET_HANDLE_i,
										AMPS_MSG_AWAITING,
										DMBASE_MSG_HEADER_SIZE_IN_BYTES);
    poNetHandleData->bIsHeaderReceived = FALSE;
    DMBase_ProcessMessage(hDiamStackContext,
							pucMsgBuffer,
							poNetHandleData,
							hAMPS_NET_HANDLE_i,
							pcIPAddress_i,
							nPort_i);

    DMBase_Free(hDiamStackContext, (void**)&pucMsgBuffer);


    ExitMe:


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return 0;



}



/******************************************************************************
** Function Name:
**			DMBase_ConnectConfirm
**
** Description:
**		This callback is executed by AMPS framework when connection
**		establishment is confirmed.
**
** Parameters:
**		  AMPS_HANDLE r_hAMPS_HANDLE
**			 type: input/output
**			 detail : this is a AMPS handle.
**
**		  AMPS_APP_HANDLE hAMPS_APP_HANDLE_i
**			type: output
**			detail: this is a AMPS Application handle
**
**		  AMPS_NET_HANDLE hAMPS_NET_HANDLE_i
**			type:input
**			detail: this is AMPS transport handle.
**
**		  int nPort_i
**			type:input
**			detail: this is port number.
**
**		  char* pcIPAddress_i
**			type:input
**			detail: this is IP address of the peer.
**
** Return:
**		Aa interger value specify whether callback executed
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
int DMBase_ConnectConfirm(  AMPS_HANDLE     		r_hAMPS_HANDLE,
                            AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
                            AMPS_NET_HANDLE 		r_hAMPS_NET_HANDLE,
                            AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE,
                            int             		r_nPort,
                            char*           		r_chIPAddress)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");
    //printf("Connection Confirm-----\n");


    HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;
    t_NetHandleData *poNetHandleData = (t_NetHandleData*)r_hAMPS_APP_DATA_HANDLE;
    HPEERTABLEENTRY hPeer = poNetHandleData->hPeer;

    if(NULL == r_hAMPS_NET_HANDLE)
    {
        DMBase_ExecutePeerStateMachine(hDiamStackContext,hPeer,NULL,I_Rcv_Conn_Nack, NULL);
        DMBase_Free(hDiamStackContext, (void**)&poNetHandleData);
    }
    else
    {
    	t_DiameterTransportObject oTransport;
    	t_DiamOctetString oIPAddress;

    	DMBase_MemsetZero(&oIPAddress, sizeof(t_DiamOctetString));
    	DMBase_CopyCharArrayToDiamString(&oIPAddress, r_chIPAddress);
    	DMBase_MemsetZero(&oTransport, sizeof(t_DiameterTransportObject));

    	oTransport.oTransportType = TCP;
    	oTransport.pvTransportLayerHandle = r_hAMPS_NET_HANDLE;
    	oTransport.oDiamTCPTransport.oIPAddrType = IP_v4;
    	oTransport.oDiamTCPTransport.oFQDN = hPeer->oHostIdentity;
    	oTransport.oDiamTCPTransport.oIPAddress = oIPAddress;
    	oTransport.oDiamTCPTransport.unPort = r_nPort;

    	DMBase_SetPeerInitiatorTransportObject(hDiamStackContext, hPeer, &oTransport);
        DMBase_ExecutePeerStateMachine(hDiamStackContext,hPeer,NULL,I_Rcv_Conn_Ack, NULL);

        DMBase_DeleteDiamString(&oIPAddress);

    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return 0;
}



/******************************************************************************
** Function Name:
**			DMBase_ConnectionCloseNotification
**
** Description:
**		This callback is executed by AMPS framework when connection
**		is closed.
**
** Parameters:
**		  AMPS_HANDLE r_hAMPS_HANDLE
**			 type: input/output
**			 detail : this is a AMPS handle.
**
**		  AMPS_APP_HANDLE hAMPS_APP_HANDLE_i
**			type: output
**			detail: this is a AMPS Application handle
**
**		  AMPS_NET_HANDLE hAMPS_NET_HANDLE_i
**			type:input
**			detail: this is AMPS transport handle.
**
**
** Return:
**		Aa integer value specify whether callback executed
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
int DMBase_ConnectionCloseNotification( AMPS_HANDLE 	r_hAMPS_HANDLE,
                                        AMPS_APP_HANDLE r_hAMPS_APP_HANDLE,
                                        AMPS_NET_HANDLE r_hAMPS_NET_HANDLE,
                                        int 			r_nPort,
                                        char* 			r_chIPAddress)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;
    t_NetHandleData *poNetHandleData = NULL;

    DMBase_GetUsrDataFromNetHandle( hDiamStackContext, r_hAMPS_NET_HANDLE,
                                    (void**)&poNetHandleData);

    if(NULL != poNetHandleData)
    {

		HPEERTABLEENTRY hPeerTableEntry_i = poNetHandleData->hPeer;

		if(NULL != hPeerTableEntry_i)
		{
			t_DiameterPSMEvent oEvent = (hPeerTableEntry_i->oPeerConnectionRole == Initiator ? I_Peer_Disc : R_Peer_Disc);

			DMBase_ExecutePeerStateMachine(hDiamStackContext, hPeerTableEntry_i, NULL, oEvent, NULL);
			unsigned char ucPeerName[100];

			DMBase_CopyDiamStrToNSizedCharArray(ucPeerName, 100, hPeerTableEntry_i->oHostIdentity);
			printf("\nConnection Terminated by Peer \"%s\"\r\n", ucPeerName);
			printf("Peer \"%s\" State is [Closed]\r\n", ucPeerName);
			DMBase_ExecuteAppPeerConnCloseCallback(hDiamStackContext, hPeerTableEntry_i);
			DMBase_ShowPeerTable(hDiamStackContext);
		}

		DMBase_Free(hDiamStackContext, (void**)&poNetHandleData);
    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return 0;
}

t_DiamAPIReturnVal DMBase_LookUpUnknownInitiatorDataForNetHandle(HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                 t_UnknownInitiator** ppoUnknownInitiator, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, DMBase_SList* pList)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SList* pHeadNode = NULL;
    void* pData = NULL;
    t_UnknownInitiator* poUnknownInitiator = NULL;
    for(pHeadNode = pList; NULL != pHeadNode; DMBase_SListGetNextNode(hDiamStackContext_io, pHeadNode,&pHeadNode))
    {

        pData = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, pHeadNode, &pData);
        poUnknownInitiator = (t_UnknownInitiator* )pData;
        if(r_hAMPS_NET_HANDLE == poUnknownInitiator->hTransport )
        {
            *ppoUnknownInitiator = poUnknownInitiator;
            return DMBase_Retval_Success;
        }
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Not_Found;
}

t_DiamAPIReturnVal DMBase_LookUpUnknownInitiatorDataForOriginHost(HDIAMETERSTACKCONTEXT  	hDiamStackContext_io,
																 t_UnknownInitiator** 		ppoUnknownInitiator,
																 t_DiamOctetString* 		poFQDN,
																 DMBase_SList* 				pList)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SList* pHeadNode = NULL;
    void* pData = NULL;
    t_UnknownInitiator* poUnknownInitiator = NULL;
    for(pHeadNode = pList; NULL != pHeadNode; DMBase_SListGetNextNode(hDiamStackContext_io, pHeadNode,&pHeadNode))
    {

        pData = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, pHeadNode, &pData);
        poUnknownInitiator = (t_UnknownInitiator* )pData;
        if(strcmp(poUnknownInitiator->oHostName.pucOctetString, poFQDN->pucOctetString) == 0)
        {
            *ppoUnknownInitiator = poUnknownInitiator;
            return DMBase_Retval_Success;
        }
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Not_Found;
}


t_DiamAPIReturnVal DMBase_DeleteNodeFromTransportList(  HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                        DMBase_SList** ppList, void* pvData)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBase_SList* pHeadNode = NULL;
    void* pvTempData = NULL;
    HTRANSPORTOBJECT hTempTransObj = NULL;
    for(pHeadNode = *ppList; NULL != pHeadNode; DMBase_SListGetNextNode(hDiamStackContext_io, pHeadNode,&pHeadNode))
    {

        pvTempData = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, pHeadNode, &pvTempData);
        if(pvData == pvTempData)
        {
            DMBase_RemoveSListNodeWithOutFree(hDiamStackContext_io, ppList, pHeadNode);
            return DMBase_Retval_Success;
        }
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Not_Found;
}





