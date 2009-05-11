
#ifndef DMBASE_PSM_ACTIONS_H
#define	DMBASE_PSM_ACTIONS_H

#include "dmbase_data_types.h"
#include "dmbase_transport_mgmt.h"
#include "dmbase_avp.h"
#include "dmbase_message.h"

#define DMBASE_TIMER_VALUE 600000 //Unit of Timer value is millisecond
#ifdef	__cplusplus
extern "C" {
#endif


t_DiamAPIReturnVal DMBase_PSMAction_ISndConnReq(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeerTabEntry_i);

t_DiamAPIReturnVal DMBase_PSMAction_RAccept(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_i);

t_DiamAPIReturnVal DMBase_PSMAction_ProcessCER(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HDIAMETERMESSAGE 		hDiamMsg_i,
												HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_RSndCEA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hRDiamMsg_i);

t_DiamAPIReturnVal DMBase_Send_CEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HPEERTABLEENTRY 		hPeer_i,
									HDIAMETERMESSAGE 		hRcvDiamMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_ISndCER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_Send_CER(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
									HPEERTABLEENTRY 	 hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_Cleanup(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_Error(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HTRANSPORTOBJECT 		hTransportObj_i);

t_DiamAPIReturnVal DMBase_PSMAction_ProcessCEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i ,
												HDIAMETERMESSAGE 		hDiamMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_Elect(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											_Bool* 					pbWinElection_o);

t_DiamAPIReturnVal DMBase_PSMAction_IDisc(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);


t_DiamAPIReturnVal DMBase_PSMAction_ISndCEA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hRDiamMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_RDisc(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_RReject(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HTRANSPORTOBJECT 		hTranportObj_i);

t_DiamAPIReturnVal DMBase_SendMessage(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HPEERTABLEENTRY 		hPeerTableEntry_i,
										HDIAMETERMESSAGE 		hDiamMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_RSndMessage(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeerTableEntry_i,
												HDIAMETERMESSAGE 		hDiameMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_ISndMessage(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeerTableEntry_i,
												HDIAMETERMESSAGE 		hDiameMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_Process(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_i,
											HDIAMETERMESSAGE 		hDiamMsg_i);


t_DiamAPIReturnVal DMBase_PSMAction_ProcessDWR(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeerTableEntry_i,
												HDIAMETERMESSAGE 		hDiamMsg_i);


t_DiamAPIReturnVal DMBase_SendDWA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
									HPEERTABLEENTRY 		hPeerTableEntry_i,
									HDIAMETERMESSAGE 		hDiamMsg_i);


t_DiamAPIReturnVal DMBase_PSMAction_RSndDWA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_i,
											HDIAMETERMESSAGE 		hDiamMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_ISndDWA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_i,
											HDIAMETERMESSAGE 		hDiamMsg_i);

t_DiamAPIReturnVal DMBase_PSMAction_ProcessDWA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeerTableEntry_i);

t_DiamAPIReturnVal DMBase_PSMAction_ISndDPR(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_SendDPR(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_RSndDPR(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_RSndDPA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_SendDPA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_PSMAction_ISndDPA(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i);

t_DiamAPIReturnVal DMBase_Invalid_Action(HDIAMETERSTACKCONTEXT hDiamStackContext_io);

t_DiamAPIReturnVal DMBase_ProcessRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeerTableEntry_i,
											HDIAMETERMESSAGE 		hDiamMsg_i);

t_DiamAPIReturnVal DMBase_ProcessAnswer(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HPEERTABLEENTRY 		hPeer_i,
										HDIAMETERMESSAGE 		hRcvMsg_i);


t_DiamAPIReturnVal DMBase_LocalProcessing(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i,
											unsigned int			unAppId_i);

t_DiamAPIReturnVal DMBase_ForwardRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i);

t_DiamAPIReturnVal DMBase_RouteRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
										HREALMTABLEENTRY		hRealm_i,
										HPEERTABLEENTRY			hPeer_i,
										HDIAMETERMESSAGE		hRcvMsg_i);

t_DiamAPIReturnVal DMBase_RelayingRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HREALMTABLEENTRY		hRealm_i,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i);

t_DiamAPIReturnVal DMBase_RedirectingRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HREALMTABLEENTRY		hRealm_i,
												HPEERTABLEENTRY			hPeer_i,
												HDIAMETERMESSAGE		hRcvMsg_i);

t_DiamAPIReturnVal DMBase_ProxingRequest(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HREALMTABLEENTRY		hRealm_i,
											HPEERTABLEENTRY			hPeer_i,
											HDIAMETERMESSAGE		hRcvMsg_i);



#ifdef	__cplusplus
}
#endif

#endif	/* DMBASE_PSM_ACTIONS_H */
