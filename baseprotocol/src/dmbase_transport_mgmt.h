
#ifndef DMBASE_TRANSPORTANDPEERMGNT_H
#define DMBASE_TRANSPORTANDPEERMGNT_H


#include "dmbase_data_types.h"
#include "dmbase_message.h"

#define DMBASE_MAX_NUMBER_OF_BIND_RETRIES       3
#define DMBASE_RECEIVE_BUFFER                   1024
#define	DMBASE_MSG_SIZE_OFFSET					1

#ifdef __cplusplus
    extern "C" {
#endif


t_DiamAPIReturnVal DMBase_OpenTransportConnection(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io ,
													HTRANSPORTOBJECT 		hTransportObj_i,
													void* 					pvAppDataHandle_i );

t_DiamAPIReturnVal DMBase_CreateTransportObject ( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                  HTRANSPORTOBJECT*     phTransportObject_io,
                                                  t_DiamTransportType	oTransportType_i,
                                                  t_DiamOctetString		oFQDN_i,
                                                  t_DiamOctetString		oIPAddress_i,
                                                  unsigned int			unPort_i,
                                                  t_IPAddrType			oIPType_i,
                                                  void*					pvNetHandle_i);

t_DiamAPIReturnVal DMBase_StartListeners( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                          DMBase_SList*         poListenersList_i);

t_DiamAPIReturnVal DMBase_ListenForTransportConnections( HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                         HTRANSPORTOBJECT 		hTransObj_i );

t_DiamAPIReturnVal DMBase_CloseTransportConnection ( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                     HTRANSPORTOBJECT       hTransportObj_i);

t_DiamAPIReturnVal DMBase_SetTransportType(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
											HTRANSPORTOBJECT       	hTransportObject_o,
                                            t_DiamTransportType    	oTransportType_i);

t_DiamAPIReturnVal	DMBase_SetTransportObjectValue(	HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
													HTRANSPORTOBJECT		hDestTransport_io,
													HTRANSPORTOBJECT		hSrcTransportObj_i);

t_DiamAPIReturnVal DMBase_SetTCPTransportValue(HDIAMETERSTACKCONTEXT    hDiamStackContext_io,
                                               t_DiameterTCPTransport*  poTCPTransport_o,
                                               t_DiamOctetString        oIPAdress_i,
                                               t_DiamOctetString        oFQDN_i,
                                               unsigned int             unPort_i,
                                               t_IPAddrType             IPAddrType_i );

t_DiamAPIReturnVal DMBase_AddIPAdressToTransportObject( HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
														HTRANSPORTOBJECT        hTransportObject_o,
														t_DiamOctetString*      poStrIPAddress_i);

t_DiamAPIReturnVal DMBase_SetDiameterAppContextInTransportObject( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                                  HTRANSPORTOBJECT      hTransportObject_o,
                                                                  void*                 pvDiameterAppContext_i);

t_DiamAPIReturnVal DMBase_SetTransportLevelHandleInTransportObject( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
                                                             HTRANSPORTOBJECT       hTransportObject_o,
                                                             void*                  TransportLevelHandle);

t_DiamAPIReturnVal DMBase_ProcessMessage(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											unsigned char*  		pucMsgBuffer_i,
											t_NetHandleData*		poNetHandleData_io,
											void*					pvNetHanble_i,
											char*					pcIPAddress_i,
											int						nPort_i);

t_DiamAPIReturnVal DMBase_SetupPeer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HDIAMETERMESSAGE		hRcvMsg_i,
									t_NetHandleData*		poNetHandleData_io,
									void*					pvNetHanble_i,
									char*					pcIPAddress_i,
									int						nPort_i);




int DMBase_ConnectionNotification(  AMPS_HANDLE     r_hAMPS_HANDLE,
                                    AMPS_APP_HANDLE r_hAMPS_APP_HANDLE,
                                    AMPS_NET_HANDLE r_hAMPS_NET_HANDLE,
                                    int             nPort_i,
                                    char*           pcIPAddress_i);

int DMBase_ReceiveMessageOnTCP( AMPS_HANDLE     r_hAMPS_HANDLE,
                                AMPS_APP_HANDLE hAMPS_APP_HANDLE_i,
                                AMPS_NET_HANDLE hAMPS_NET_HANDLE_i,
                                unsigned char*  pucBuff_i,
                                int             nBuffLength_i,
                                int             nPort_i,
                                char*           pcIPAddress_i);

int DMBase_ConnectConfirm(  AMPS_HANDLE     		r_hAMPS_HANDLE,
                            AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
                            AMPS_NET_HANDLE 		r_hAMPS_NET_HANDLE,
                            AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE,
                            int             		r_nPort,
                            char*           		r_chIPAddress);

int DMBase_ConnectionCloseNotification( AMPS_HANDLE 	r_hAMPS_HANDLE,
                                        AMPS_APP_HANDLE r_hAMPS_APP_HANDLE,
                                        AMPS_NET_HANDLE r_hAMPS_NET_HANDLE,
                                        int 			r_nPort,
                                        char* 			r_chIPAddress);






#ifdef __cplusplus
   }
#endif

#endif /* DMBASE_TRANSPORTANDPEERMGNT_H */


