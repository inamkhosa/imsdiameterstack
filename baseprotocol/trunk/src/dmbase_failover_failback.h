
#ifndef _DMBASE_FAILOVER_FAILBACK_H_
#define _DMBASE_FAILOVER_FAILBACK_H_

#include "dmbase_message.h"
#include "dmbase_realmtablemgmt.h"
#ifdef __cplusplus
    extern "C" {
#endif

//Watchdog timer initial value
#define TWINIT  30000     //MilliSeconds


int DMBase_TimeOutNotification(void* pvHandle, void* r_pvData);

t_DiamAPIReturnVal DMBase_SendDWR(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                  HPEERTABLEENTRY       hPeer_i);

t_DiamAPIReturnVal DMBase_SetPCBValues(HPCB           hoPCB,
                                       t_PCBStatus    oStatus,
                                       _Bool          bPending,
                                       unsigned int   unTw,
                                       unsigned short usNumDWA);

t_DiamAPIReturnVal DMBase_SetPCBStatus(HPCB        hoPCB,
                                       t_PCBStatus oStatus);

t_DiamAPIReturnVal DMBase_SetPCBPendingFlag(HPCB  hoPCB,
                                            _Bool bPending);

t_DiamAPIReturnVal DMBase_SetWatchdog(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                        HPEERTABLEENTRY hPeer_io);

t_DiamAPIReturnVal DMBase_Failover(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                   HPEERTABLEENTRY       hPeer_i);

t_DiamAPIReturnVal DMBase_SwitchToAlternateServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                  HREALMTABLEENTRY      hRealm);

t_DiamAPIReturnVal DMBase_SendPendingMsgToAlternateServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                          HREALMTABLEENTRY      hRealm);

t_DiamAPIReturnVal DMBase_Failback(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                   HPEERTABLEENTRY       hPeer_i);

 t_DiamAPIReturnVal DMBase_ClearPendingMsgListEntry(HDIAMETERSTACKCONTEXT hDiameterContext_io,
                                                    HREALMTABLEENTRY hRealm,
                                                    HPEERTABLEENTRY hPeer);

 t_DiamAPIReturnVal DMBase_SetActiveServer(HDIAMETERSTACKCONTEXT hDiameterContext_io, HPEERTABLEENTRY hPeer);

int DMBase_IsPrimaryServer(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                           HREALMTABLEENTRY      hRealmTableEntry_i,
                           HPEERTABLEENTRY       hPeer_i);

t_DiamAPIReturnVal DMBase_ExecuteFailoverStateMachine(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                      HPEERTABLEENTRY       hPeer_i,
                                                      t_FailoverSMEvent     oFSMEvent_i,
                                                      void*                 pvData);

t_DiamAPIReturnVal DMBase_Okay_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                      HPEERTABLEENTRY       hPeer_i,
                                      t_FailoverSMEvent     oFSMEvent_i,
                                      void*                 pvData);

t_DiamAPIReturnVal DMBase_Okay_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData);

t_DiamAPIReturnVal DMBase_Okay_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData);

t_DiamAPIReturnVal DMBase_Okay_ConnectionDown(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                              HPEERTABLEENTRY       hPeer_i,
                                              t_FailoverSMEvent     oFSMEvent_i,
                                              void*                 pvData);

t_DiamAPIReturnVal DMBase_Suspect_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData);

t_DiamAPIReturnVal DMBase_Suspect_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData);

t_DiamAPIReturnVal DMBase_Suspect_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                               HPEERTABLEENTRY       hPeer_i,
                                               t_FailoverSMEvent     oFSMEvent_i,
                                               void*                 pvData);

t_DiamAPIReturnVal DMBase_Suspect_ConnectionDown(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                 HPEERTABLEENTRY       hPeer_i,
                                                 t_FailoverSMEvent     oFSMEvent_i,
                                                 void*                 pvData);

t_DiamAPIReturnVal DMBase_Down_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                      HPEERTABLEENTRY       hPeer_i,
                                      t_FailoverSMEvent     oFSMEvent_i,
                                      void*                 pvData);

t_DiamAPIReturnVal DMBase_Down_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData);

t_DiamAPIReturnVal DMBase_Down_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData);

t_DiamAPIReturnVal DMBase_Down_ConnectionUp(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                            HPEERTABLEENTRY       hPeer_i,
                                            t_FailoverSMEvent     oFSMEvent_i,
                                            void*                 pvData);

t_DiamAPIReturnVal DMBase_Reopen_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                        HPEERTABLEENTRY       hPeer_i,
                                        t_FailoverSMEvent     oFSMEvent_i,
                                        void*                 pvData);

t_DiamAPIReturnVal DMBase_Reopen_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                           HPEERTABLEENTRY       hPeer_i,
                                           t_FailoverSMEvent     oFSMEvent_i,
                                           void*                 pvData);

t_DiamAPIReturnVal DMBase_Reopen_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                              HPEERTABLEENTRY       hPeer_i,
                                              t_FailoverSMEvent     oFSMEvent_i,
                                              void*                 pvData);

t_DiamAPIReturnVal DMBase_Reopen_ConnectionDown(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                HPEERTABLEENTRY       hPeer_i,
                                                t_FailoverSMEvent     oFSMEvent_i,
                                                void*                 pvData);

t_DiamAPIReturnVal DMBase_Initial_RcvDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData);

t_DiamAPIReturnVal DMBase_Initial_RcvNonDWA(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                         HPEERTABLEENTRY       hPeer_i,
                                         t_FailoverSMEvent     oFSMEvent_i,
                                         void*                 pvData);

t_DiamAPIReturnVal DMBase_Initial_TimerExpires(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                               HPEERTABLEENTRY       hPeer_i,
                                               t_FailoverSMEvent     oFSMEvent_i,
                                               void*                 pvData);

t_DiamAPIReturnVal DMBase_Initial_ConnectionUp(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                               HPEERTABLEENTRY       hPeer_i,
                                               t_FailoverSMEvent     oFSMEvent_i,
                                               void*                 pvData);

int DMBase_FreeFailoverSupportData(void** ppvData);

t_DiamAPIReturnVal DMBase_InitWatchDogTimer(HDIAMETERSTACKCONTEXT hDiamStackContext_io);


void DMBase_StartWatchDogTimerCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE);


#ifdef __cplusplus
   }
#endif

#endif

