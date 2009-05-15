

#ifndef DMBASE_REALMTABLEMGMT_H
#define DMBASE_REALMTABLEMGMT_H


#include "dmbase_data_types.h"
#include "dmbase_message.h"
#include "dmbase_transport_mgmt.h"
#include "AMPS_Defines.h"

#ifdef __cplusplus
    extern "C" {
#endif


t_DiamAPIReturnVal DMBase_CreateRealmTable(HDIAMETERSTACKCONTEXT  hDiamStackContext_io);

t_DiamAPIReturnVal DMBase_CreateRealmTableObject(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                 t_RealmTable**        ppoRealmTableObject_o);

t_DiamAPIReturnVal DMBase_CreateRealmTableKey(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                              t_DiamOctetString     oRealmName_i,
                                              unsigned int          unAppID_i,
                                              t_DiamHashTableKey*   poHashTableKey_o);

t_DiamAPIReturnVal DMBase_PopulateRealmTable( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
											  DMBase_SList*          poRealmList_i );

t_DiamAPIReturnVal DMBase_InsertRealmTableEntry(HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
												HREALMTABLEENTRY		hRealmTableEntry_i);

t_DiamAPIReturnVal DMBase_RemoveRealmTableEntry( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
												 unsigned int          	unAppId_i,
		                                         t_DiamOctetString     	oRealmName_i);

t_DiamAPIReturnVal DMBase_LookupRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                unsigned int          unAppId_i,
                                                t_DiamOctetString     oRealmName_i,
                                                HREALMTABLEENTRY*     phRealmTableEntry_io);

t_DiamAPIReturnVal DMBase_LookupRealmTableByHashKey(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
													t_DiamHashTableKey 		oHashTableKey_i,
													HREALMTABLEENTRY*       phRealmTableEntry_io);

t_DiamAPIReturnVal DMBase_ShowRealmTable(HDIAMETERSTACKCONTEXT  hDiamStackContext_io);

void DMBase_ShowRealmTableEntryCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE);

t_DiamAPIReturnVal DMBase_CreateRealmTableEntry(HDIAMETERSTACKCONTEXT  	hDiamStackContext_io,
												HREALMTABLEENTRY*		phRealmTableEntry_io,
                                              	t_DiamOctetString      	oRealmName_i,
                                              	unsigned int           	unAppID_i,
                                              	_Bool                  	bIsStaticEntry_i,
                                              	t_LocalAction          	oLocalAction_i,
                                              	DMBase_SList*          	poServerList_i);


t_DiamAPIReturnVal DMBase_SetRealmNameInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                        HREALMTABLEENTRY      hRealmTabEntry_o,
                                                        t_DiamOctetString     oRealmName_i);

t_DiamAPIReturnVal DMBase_SetAppIdInRealmTableEntry(HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
                                                    HREALMTABLEENTRY        hRealmTabEntry_o,
                                                    t_ApplicationIdentifier oAppId_i);

t_DiamAPIReturnVal DMBase_SetLocalActionInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                          HREALMTABLEENTRY      hRealmTabEntry_o,
                                                          t_LocalAction         oLocalAction_i);


t_DiamAPIReturnVal DMBase_SetLocalActionInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                          HREALMTABLEENTRY      hRealmTabEntry_o,
                                                          t_LocalAction         oLocalAction_i);

t_DiamAPIReturnVal DMBase_SetServerListInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                         HREALMTABLEENTRY      hRealmTabEntry_o,
                                                         DMBase_SList*         pServerList_i);

t_DiamAPIReturnVal DMBase_SetStaticStatusInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                           HREALMTABLEENTRY      hRealmTabEntry_o,
                                                           _Bool                 bIsStatic_i);


t_DiamAPIReturnVal DMBase_SetExpTimeInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                      HREALMTABLEENTRY      hRealmTabEntry_o,
                                                      t_DiamTime            oExpiryTime_i );


#ifdef __cplusplus
   }
#endif

#endif /* DMBASE_REALMTABLEMGMT_H */
