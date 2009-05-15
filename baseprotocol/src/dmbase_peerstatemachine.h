/*
 * File:   dmbase_peerstatemachine.h
 * Author: root
 *
 * Created on June 23, 2008, 3:04 AM
 */

#ifndef _PEERSTATEMACHINE_H
#define	_PEERSTATEMACHINE_H

#include "dmbase_data_types.h"
#include "dmbase_transport_mgmt.h"
#include "dmbase_avp.h"
#include "dmbase_message.h"

#define DMBASE_TIMER_VALUE 600000 //Unit of Timer value is millisecond
#ifdef	__cplusplus
extern "C" {
#endif




t_DiamAPIReturnVal DMBase_InitPeerStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io);

t_DiamAPIReturnVal DMBase_CheckEventType(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                         HPEERTABLEENTRY 		hPeer_i,
                                         HDIAMETERMESSAGE 		hDiamMsg_i,
                                         t_DiameterPSMEvent* 		poPSMEvent_i );

t_DiamAPIReturnVal DMBase_Closed_Start(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
										  HPEERTABLEENTRY 		hPeer_i,
										  HDIAMETERMESSAGE 		hDiamMsg_i,
										  t_DiameterPSMEvent 		oPSMEvent_i,
										  void* 				pvData_i);


t_DiamAPIReturnVal DMBase_Closed_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                            HPEERTABLEENTRY 		hPeer_i,
                                            HDIAMETERMESSAGE 		hDiamMsg_i,
                                            t_DiameterPSMEvent 		oPSMEvent_i,
                                            void* 					pvData);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                   HPEERTABLEENTRY			hPeer_i,
                                                   HDIAMETERMESSAGE 		hDiamMsg_i,
                                                   t_DiameterPSMEvent 			oPSMEvent_i,
                                                   void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_I_Rcv_Conn_Ack(   HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
														  HPEERTABLEENTRY 		hPeer_i,
														  HDIAMETERMESSAGE 		hDiamMsg_i,
														  t_DiameterPSMEvent 		oPSMEvent_i,
														  void* 				pData);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_I_Rcv_Conn_Nack(  HDIAMETERSTACKCONTEXT	hDiamStackContext_io,
														  HPEERTABLEENTRY 		hPeer_i,
														  HDIAMETERMESSAGE 		hDiamMsg_i,
														  t_DiameterPSMEvent 		oPSMEvent_i,
														  void* 				pData);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Timeout( HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												 HPEERTABLEENTRY 		hPeer_i,
                                                 HDIAMETERMESSAGE 		hDiamMsg_i,
                                                 t_DiameterPSMEvent 		oPSMEvent_i,
                                                 void* 					pvData_i);


t_DiamAPIReturnVal DMBase_Wait_I_CEA_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                HPEERTABLEENTRY 		hPeer_i,
                                                HDIAMETERMESSAGE 		hDiamMsg_i,
                                                t_DiameterPSMEvent 		oPSMEvent_i,
                                                void* 					pvData);


t_DiamAPIReturnVal DMBase_Wait_I_CEA_I_Rcv_CEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
												HPEERTABLEENTRY 		hPeer_i,
												HDIAMETERMESSAGE 		hDiamMsg_i,
                                                t_DiameterPSMEvent 		oPSMEvent_i,
                                                void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_I_CEA_I_Rcv_Non_CEA(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
													HPEERTABLEENTRY 		hPeer_i,
                                                    HDIAMETERMESSAGE 		hDiamMsg_i,
                                                    t_DiameterPSMEvent 		oPSMEvent_i,
                                                    void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_I_CEA_I_Peer_Disc(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                 HPEERTABLEENTRY 		hPeer_i,
                                                 HDIAMETERMESSAGE 		hDiamMsg_i,
                                                 t_DiameterPSMEvent 		oPSMEvent_i,
                                                 void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_I_CEA_Timeout(  HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											   HPEERTABLEENTRY 			hPeer_i,
                                               HDIAMETERMESSAGE 		hDiamMsg_i,
                                               t_DiameterPSMEvent 			oPSMEvent_i,
                                               void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
                                                         HPEERTABLEENTRY 		hPeer_i,
                                                         HDIAMETERMESSAGE 		hDiamMsg_i,
                                                         t_DiameterPSMEvent 		oPSMEvent_i,
                                                         void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_I_Rcv_Conn_Ack(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
															 HPEERTABLEENTRY 		hPeer_i,
															 HDIAMETERMESSAGE 		hDiamMsg_i,
															 t_DiameterPSMEvent 		oPSMEvent_i,
															 void* 					pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_I_Rcv_Conn_Nack(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
															  HPEERTABLEENTRY 		hPeer_i,
															  HDIAMETERMESSAGE 		hDiamMsg_i,
															  t_DiameterPSMEvent 		oPSMEvent_i,
															  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_R_Peer_Disc(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													      HPEERTABLEENTRY 		hPeer_i,
													      HDIAMETERMESSAGE 		hDiamMsg_i,
													      t_DiameterPSMEvent 		oPSMEvent_i,
													      void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Conn_Ack_Elect_Timeout(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Returns_R_Conn_CER(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Returns_I_Rcv_CEA( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Returns_I_Peer_Disc(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Returns_R_Peer_Disc(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Returns_Win_Election(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
													  HPEERTABLEENTRY 		hPeer_i,
													  HDIAMETERMESSAGE 		hDiamMsg_i,
													  t_DiameterPSMEvent 		oPSMEvent_i,
													  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Wait_Returns_Timeout(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Conn_CER(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_CER(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_CEA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Peer_Disc( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_DPR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_DWR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_DWA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_Send_Message(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_R_Rcv_Message(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_R_Open_Stop(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
									  HPEERTABLEENTRY 		hPeer_i,
									  HDIAMETERMESSAGE 		hDiamMsg_i,
									  t_DiameterPSMEvent 		oPSMEvent_i,
									  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_R_Conn_CER(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
											HPEERTABLEENTRY 		hPeer_i,
											HDIAMETERMESSAGE 		hDiamMsg_i,
											t_DiameterPSMEvent 		oPSMEvent_i,
											void* 					pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_CER(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_CEA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Peer_Disc( HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_DPR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_DWR(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_DWA(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_Send_Message(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_I_Rcv_Message(   HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_I_Open_Stop(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
									  HPEERTABLEENTRY 		hPeer_i,
									  HDIAMETERMESSAGE 		hDiamMsg_i,
									  t_DiameterPSMEvent 		oPSMEvent_i,
									  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Closing_I_Peer_Disc(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Closing_R_Peer_Disc(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Closing_I_Rcv_DPA(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Closing_R_Rcv_DPA(  HDIAMETERSTACKCONTEXT hDiamStackContext_io,
											  HPEERTABLEENTRY 		hPeer_i,
											  HDIAMETERMESSAGE 		hDiamMsg_i,
											  t_DiameterPSMEvent 		oPSMEvent_i,
											  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_Closing_Timeout(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
										  HPEERTABLEENTRY 		hPeer_i,
										  HDIAMETERMESSAGE 		hDiamMsg_i,
										  t_DiameterPSMEvent 		oPSMEvent_i,
										  void* 				pvData_i);

t_DiamAPIReturnVal DMBase_ExecutePeerStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
												  HPEERTABLEENTRY 		hPeer_i,
												  HDIAMETERMESSAGE 		hDiamMsg_i,
												  t_DiameterPSMEvent 		oPSMEvent_i,
												  void* 				pvData_i);

int DMBase_TimeOutNotifyCallBack_ForPSM(FRAMEWORK_HANDLE hoAMPSFrameWork, void* r_pvData);
#ifdef	__cplusplus
}
#endif

#endif	/* _PEERSTATEMACHINE_H */






