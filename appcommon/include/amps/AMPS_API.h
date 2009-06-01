/******************************************************************************
** Written by Zaka Kiani
**
** Copyright (C) 2007 AdvancedIMS
**
** All rights reserved.
** 
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 3 of the License, or
**  (at your option) any later version.
** 
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
** 
*******************************************************************************
** FILE NAME      		: AMPS_API.h
** DESCRIPTION    		: 
** PROJECT NAME   		: AMPS
** TYPE           		: ANSI C
** CONTRIBUTOR(S) 		: Arif, Zaka Kiani
*******************************************************************************
** $Id: AMPS_API.h,v 1.76 2009/04/20 10:39:37 zaka Exp $
** $Source: /work/cvsroot/amps/include/AMPS_API.h,v $
*******************************************************************************
*******************************************************************************
*/
#ifndef __HEADER_AMPS_API_H__
#define __HEADER_AMPS_API_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "AMPS_Defines.h"

AMPS_API AMPS_HANDLE AMPS_Init(e_AMPSTimerResolution r_oAMPSTimerResolution, AMPS_BOOL r_bTracingPresent, char* r_pchTraceFilePath, e_AMPSPortPoolSize r_oAMPSPortPoolSize, int r_nStartingPort);
AMPS_API void AMPS_Cleanup(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_Main(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_Start(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_Stop(void);

AMPS_API int AMPS_EnableLogging(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchLogFilePath);

AMPS_API int AMPS_SetACParamToNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, t_AMPSCongestionControlParam* r_poAMPSCongestionControlParam);
AMPS_API int AMPS_StartSysMemUsageControl(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSSysMemUsageControlParam* r_poAMPSSysMemUsageControlParam);
AMPS_API int AMPS_StopSysMemUsageControl(AMPS_HANDLE r_hAMPS_HANDLE);

AMPS_API int AMPS_CreateTCPListenerObject(AMPS_HANDLE r_hAMPS_HANDLE, e_AMPSMemoryScheme r_eAMPSMemoryScheme, AMPS_MallocCallback r_pfAMPS_MallocCallback, AMPS_FreeCallback r_pfAMPS_FreeCallback, AMPS_ReAllocCallback r_pfAMPS_ReAllocCallback, int r_nPort, char* r_chIPAddress, int r_nMinMsgSize, int r_nFixedMsgSize, AMPS_ConnNotifyCallback r_pfAMPS_ConnectEvtCallback, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_NET_HANDLE* r_phAMPS_NET_HANDLE, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback);
AMPS_API int AMPS_CreateTCPListenerObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, int r_nPort, char* r_chIPAddress, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_NET_HANDLE* r_phAMPS_NET_HANDLE, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback);

AMPS_API int AMPS_SetRecvBuffOffSetToNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int r_nRecvBuffOffSet);
//In case of TCP use this function to set the status of message i.e if the application is waiting for 100 bytes packet and only 50 have been
//received u can return without processing the received buffer and setting the status of message to PENDING/AWAITING/COMPLETE
AMPS_API void AMPS_SetRecvBuffStatusToNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int r_nMessageStatus, int r_nRemainingBytesToRead);

AMPS_API int AMPS_CreateTCPConnObject(AMPS_HANDLE r_hAMPS_HANDLE, e_AMPSMemoryScheme r_eAMPSMemoryScheme, AMPS_MallocCallback r_pfAMPS_MallocCallback, AMPS_FreeCallback r_pfAMPS_FreeCallback, AMPS_ReAllocCallback r_pfAMPS_ReAllocCallback, char* r_chLocalIPAddress, int r_nRemotePort, char* r_chRemoteIPAddress, int r_nMinMsgSize, int r_nFixedMsgSize, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_ConnCfmCallback r_pfAMPS_ConnectCfmCallback, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback);
AMPS_API int AMPS_CreateTCPConnObjectEx(AMPS_HANDLE r_hAMPS_HANDLE, e_AMPSMemoryScheme r_eAMPSMemoryScheme, AMPS_MallocCallback r_pfAMPS_MallocCallback, AMPS_FreeCallback r_pfAMPS_FreeCallback, AMPS_ReAllocCallback r_pfAMPS_ReAllocCallback, char* r_chLocalIPAddress, int r_nRemotePort, char* r_chRemoteIPAddress, int r_nMinMsgSize, int r_nFixedMsgSize, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_ConnCfmCallback r_pfAMPS_ConnectCfmCallback, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_APP_DATA_HANDLE r_hAMPS_APP_DATA_HANDLE);
AMPS_API int AMPS_CreateTCPConnObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, char* r_chLocalIPAddress, int r_nRemotePort, char* r_chRemoteIPAddress, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_NET_HANDLE* r_phAMPS_NET_HANDLE, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback);

AMPS_API int AMPS_DestroyTCPObject(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);
AMPS_API int AMPS_DestroyTCPObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);

AMPS_API int AMPS_CreateSecUDPObject(AMPS_HANDLE r_hAMPS_HANDLE, e_AMPSMemoryScheme r_eAMPSMemoryScheme, AMPS_MallocCallback r_pfAMPS_MallocCallback, AMPS_FreeCallback r_pfAMPS_FreeCallback, int r_nPort, char* r_chIPAddress, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_NET_HANDLE* r_phAMPS_NET_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, unsigned char* r_puchSecurityKey, unsigned int r_nKeyLength, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback);
AMPS_API int AMPS_DestroySecUDPObject(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);

AMPS_API int AMPS_CreateUDPObject(AMPS_HANDLE r_hAMPS_HANDLE, e_AMPSMemoryScheme r_eAMPSMemoryScheme, AMPS_MallocCallback r_pfAMPS_MallocCallback, AMPS_FreeCallback r_pfAMPS_FreeCallback, int r_nPort, char* r_chIPAddress, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_NET_HANDLE* r_phAMPS_NET_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_CloseEvtCallback r_pfAMPS_CloseEvtCallback);
AMPS_API int AMPS_CreateUDPObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, int r_nPort, char* r_chIPAddress, AMPS_RecvDataCallback r_pfAMPS_RecvDataCallback, AMPS_NET_HANDLE* r_phAMPS_NET_HANDLE, void* r_pvCallbackData);

AMPS_API int AMPS_DestroyUDPObject(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);
AMPS_API int AMPS_DestroyUDPObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);

AMPS_API int AMPS_IsAddressNatted(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchIPAddress);
AMPS_API AMPS_BOOL AMPS_IsAddressLoopBack(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchIPAddress);

AMPS_API int AMPS_GetPublicIPAndPort(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, unsigned char* r_puchStunServerAddress, AMPS_StunClientResultCallback r_pfAMPS_StunClientResultCallback, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE);

AMPS_API int AMPS_SndBuffer(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, unsigned char* r_puchBuffer, int r_nBufferLength, int r_nPort, char* r_chIPAddress);
AMPS_API int AMPS_SndBufferList(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, t_AMPSDList* r_poAMPSIOVectorList, int r_nPort, char* r_chIPAddress);

AMPS_API int AMPS_CreateFileObject(AMPS_HANDLE r_hAMPS_HANDLE, const char* r_pcchFileName, AMPS_FILE_HANDLE* r_phAMPS_FILE_HANDLE, e_AMPSFileMode r_oAMPSFileMode);
AMPS_API int AMPS_CreateFileObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, const char* r_pcchFileName, AMPS_FILE_HANDLE* r_phAMPS_FILE_HANDLE, e_AMPSFileMode r_oAMPSFileMode);

AMPS_API int AMPS_DestroyFileObject(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_FILE_HANDLE r_hAMPS_FILE_HANDLE);
AMPS_API int AMPS_DestroyFileObjectBlocking(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_FILE_HANDLE r_hAMPS_FILE_HANDLE);

AMPS_API int AMPS_FileWrite(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_FILE_HANDLE r_hAMPS_FILE_HANDLE, const void* r_pvWriteBuffer, int r_nSizeOfBuffer, int* r_pnTotalBytesWritten);
AMPS_API int AMPS_FileRead(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_FILE_HANDLE r_hAMPS_FILE_HANDLE, void* r_pvRecieveBuffer, int r_nBytesToRead, int* r_pnTotalBytesRead);

AMPS_API void AMPS_SetAppServerCtxt(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_phAMPS_APP_HANDLE);
AMPS_API AMPS_APP_HANDLE AMPS_GetAppServerCtxt(AMPS_HANDLE r_hAMPS_HANDLE);

AMPS_API void* AMPS_GetUsrDataFromNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);
AMPS_API void  AMPS_SetUsrDataToNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, void* r_pvUserData);

AMPS_API int  AMPS_GetConnTypeFromNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE);

AMPS_API void AMPS_SetRemoteIPAddressOnNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, char* r_chIPAddress);
AMPS_API void AMPS_SetRemotePortOnNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int r_nPort);

AMPS_API void AMPS_GetRemotePortFromNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int* r_pnPort);
AMPS_API void AMPS_GetRemoteIPAddressFromNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, char* r_pchIPAddress);

AMPS_API void AMPS_GetLocalPortFromNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int* r_pnPort);
AMPS_API void AMPS_GetLocalIPAddressFromNetHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, char* r_pchIPAddress);

//Timer APIs
AMPS_API AMPS_TIMER_ID AMPS_StartTimer(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTimerValue, AMPS_TimeOutNotifyCallBack r_pfAMPS_TimerCallBack, void* r_pvUserData);
AMPS_API int AMPS_DeleteTimer(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_TIMER_ID r_AMPS_TIMER_ID);

//Cache APIs
AMPS_API AMPS_CACHE_HANDLE AMPS_CacheInit(AMPS_HANDLE r_hAMPS_HANDLE, int r_nCacheSize, AMPS_CacheProcessUserDataCallback r_pfAMPS_CacheProcessUserDataCallback);
AMPS_API void AMPS_CacheCleanup(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_CACHE_HANDLE r_hAMPS_CACHE_HANDLE);

AMPS_API int AMPS_CacheAddEntry(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_CACHE_HANDLE r_hAMPS_CACHE_HANDLE, t_AMPSHashTableKey* r_poAMPSHashTableKey, void* r_pvUserData);
AMPS_API int AMPS_CacheRemoveEntry(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_CACHE_HANDLE r_hAMPS_CACHE_HANDLE, t_AMPSHashTableKey* r_poAMPSHashTableKey);
AMPS_API int AMPS_CacheUpdateEntry(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_CACHE_HANDLE r_hAMPS_CACHE_HANDLE, t_AMPSHashTableKey* r_poAMPSHashTableKey);
AMPS_API void* AMPS_CacheLookupEntry(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_CACHE_HANDLE r_hAMPS_CACHE_HANDLE, t_AMPSHashTableKey* r_poAMPSHashTableKey);

//System APIs
AMPS_API unsigned short AMPS_NetworkToHostShort(AMPS_HANDLE r_hAMPS_HANDLE, unsigned short r_unNetShort);
AMPS_API unsigned long AMPS_NetworkToHostLong(AMPS_HANDLE r_hAMPS_HANDLE, unsigned long r_ulNetLong);
AMPS_API unsigned short AMPS_HostToNetworkShort(AMPS_HANDLE r_hAMPS_HANDLE, unsigned short r_unHostShort);
AMPS_API unsigned long AMPS_HostToNetworkLong(AMPS_HANDLE r_hAMPS_HANDLE, unsigned long r_ulHostLong);

AMPS_API int AMPS_INetAtoN(AMPS_HANDLE r_hAMPS_HANDLE, const char* r_pccAddressInDottedNotation, unsigned long* r_punlAddressInBinarry);
AMPS_API int AMPS_INetNtoA(AMPS_HANDLE r_hAMPS_HANDLE, unsigned long r_unlAddressInBinarry, char* r_cpAddressInDottedNotation);
AMPS_API int AMPS_Rand(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int* r_punRandomValue);
AMPS_API int AMPS_StrnCaseCMP(AMPS_HANDLE r_hAMPS_HANDLE, const char* r_pccString1, const char* r_pccString2, unsigned int r_unSize);

AMPS_API AMPS_MODULE_HANDLE AMPS_SetupLoadableModule(AMPS_HANDLE r_hAMPS_HANDLE, const char* r_pcchModulePath, const char* r_pcchModuleName, void* r_pvModuleData);
AMPS_API void AMPS_CleanupLoadableModule(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_MODULE_HANDLE r_hAMPS_MODULE_HANDLE);
AMPS_API void* AMPS_GetLoadableModuleContext(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_MODULE_HANDLE r_hAMPS_MODULE_HANDLE);

AMPS_API int AMPS_GetHostIPAddress(AMPS_HANDLE r_hAMPS_HANDLE, unsigned char* r_puchIPAddress);
AMPS_API int AMPS_GetPeerName(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, char* r_chIPAddress);
AMPS_API int AMPS_GetHostByName(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchHost, char* r_pchHostName);
AMPS_API int AMPS_GetLocalIfaceAddress(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSDList* r_poAMPSIfaceDataList);

//DNS APIs
AMPS_API int AMPS_GetATypeRecords(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchHost, t_AMPSDList** r_ppoAMPSDNSATypeRecordList);
AMPS_API void AMPS_FreeATypeRecords(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSDList** r_ppoAMPSDNSATypeRecordList);
AMPS_API int AMPS_GetSRVRecords(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchHost, t_AMPSDList** r_ppoAMPSDNSSRVRecordList);
AMPS_API void AMPS_FreeSRVRecords(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSDList** r_ppoAMPSDNSSRVRecordList);
AMPS_API int AMPS_GetNAPTRRecords(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchHost, t_AMPSDList** r_ppoAMPSDNSNAPTRRecordList);
AMPS_API void AMPS_FreeNAPTRRecords(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSDList** r_ppoAMPSDNSNAPTRRecordList);

AMPS_API int AMPS_GetCurrentTime(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSTimerValue* r_poAMPSTimerValue);
AMPS_API int AMPS_GetTimeDiffInMilliSec(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSTimerValue* r_poAMPSTimerValue1, t_AMPSTimerValue* r_poAMPSTimerValue2);
AMPS_API int AMPS_GetCurrentTimeInMilliSec(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_Sleep(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_nSeconds);
AMPS_API void AMPS_SleepInMilliSeconds(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_nMilliSeconds);
AMPS_API int AMPS_GetTimeDiffInSec(AMPS_HANDLE r_hAMPS_HANDLE, t_AMPSTimerValue* r_poAMPSTimerValue1, t_AMPSTimerValue* r_poAMPSTimerValue2);
AMPS_API int AMPS_GetFormattedTime(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchFormat, unsigned char* r_puchFormattedBuff, unsigned int r_unSizeOfBuff);

//DBEngine APIs
AMPS_API AMPS_DBE_HANDLE AMPS_DBEngineInit(AMPS_HANDLE r_hAMPS_HANDLE, char* r_pchHostName, char* r_pchUserName, char* r_pchPassword, char* r_pchDataBaseName);
AMPS_API AMPS_DBE_HANDLE AMPS_DBEngineInitEx(AMPS_HANDLE r_hAMPS_HANDLE, e_AMPSDBType r_oAMPSDBType, char* r_pchHostName, char* r_pchUserName, char* r_pchPassword, char* r_pchDataBaseName);
AMPS_API void AMPS_DBEngineCleanup(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_DBE_HANDLE r_phAMPS_DBE_HANDLE);
AMPS_API int AMPS_DBEngineQuery(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_DBE_HANDLE r_phAMPS_DBE_HANDLE, const char* r_pcchQueryStatement, unsigned long r_ulLengthOfQuery, t_AMPSDBEngineResult* r_poAMPSDBEngineResult);
AMPS_API void AMPS_DBEngineFreeResults(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_DBE_HANDLE r_phAMPS_DBE_HANDLE, t_AMPSDBEngineResult* r_poAMPSDBEngineResult);

//EventSystem APIs
AMPS_API int AMPS_EvtSysRegExtEvt(AMPS_HANDLE r_hAMPS_HANDLE, int r_nEventType, AMPS_EvtHandlerCallback r_pfAMPS_EventCallback, void* r_pvEventData);
AMPS_API int AMPS_EvtSysCancelExtEvt(AMPS_HANDLE r_hAMPS_HANDLE, int r_nEventType, AMPS_EvtHandlerCallback r_pfAMPS_EventCallback);
AMPS_API int AMPS_EvtSysRegIntEvt(AMPS_HANDLE r_hAMPS_HANDLE, int r_nEventType, AMPS_EvtHandlerCallback r_pfAMPS_EventCallback, void* r_pvEventData);
AMPS_API int AMPS_EvtSysCancelIntEvt(AMPS_HANDLE r_hAMPS_HANDLE, int r_nEventType, AMPS_EvtHandlerCallback r_pfAMPS_EventCallback);
AMPS_API int AMPS_EvtSysSendExtEvt(AMPS_HANDLE r_hAMPS_HANDLE, int r_nEventType, void* r_pvEventData, int r_nSizeOfEventData);
AMPS_API int AMPS_EvtSysSendIntEvt(AMPS_HANDLE r_hAMPS_HANDLE, int r_nEventType, void* r_pvEventData, int r_nSizeOfEventData);
AMPS_API void AMPS_EvtSysSetEvtHandleValidationCallback(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_EvtHandleValidationCallback r_pfAMPS_EventHandleValidationCallback);
AMPS_API int AMPS_EvtSysConfigure(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_SCHED_HANDLE r_hAMPS_SCHED_HANDLE, int r_nMaxNumberOfInternalEvents, int r_nLenghtOfInternalEventQueue, int r_nMaxNumberOfExternalEvents, int r_nLenghtOfExternalEventQueue);
AMPS_API int AMPS_EvtSysGetEventType(AMPS_HANDLE r_hAMPS_HANDLE, void* r_pvEventHandle);
AMPS_API int AMPS_EvtSysGetEventSize(AMPS_HANDLE r_hAMPS_HANDLE, void* r_pvEventHandle);
AMPS_API int AMPS_EvtSysGetMaxExternalNumberOfEvents(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API int AMPS_EvtSysGetMaxInternalNumberOfEvents(AMPS_HANDLE r_hAMPS_HANDLE);

//Hash APIs
AMPS_API AMPS_HASH_HANDLE AMPS_HashTableCreate(AMPS_HANDLE r_hAMPS_HANDLE, int r_SizeOfHashTable, AMPS_HashTableHashCallback r_pfAMPS_HashTableHashCallback);
AMPS_API void AMPS_HashTableDelete (AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE);
AMPS_API void AMPS_HashTableDeleteAllEntries(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE);
AMPS_API void AMPS_HashTableTraverseAllEntries(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, AMPS_HashTableProcessNodeDataCallback r_pfAMPS_HashTableProcessNodeDataCallback, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE);
AMPS_API void AMPS_HashTableDeleteAllEntriesEx(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, AMPS_HashTableProcessNodeDataCallback r_pfAMPS_HashTableProcessNodeDataCallback, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE);
AMPS_API int AMPS_HashTableInsert(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, void* r_pvData, t_AMPSHashTableKey* r_poHASHKey);
AMPS_API int AMPS_HashTableRemoveByHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, int r_nHandle);
AMPS_API int AMPS_HashTableRemoveByKey(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, t_AMPSHashTableKey* r_poHASHKey);
AMPS_API void* AMPS_HashTableSearch(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, t_AMPSHashTableKey* r_poHASHKey);
AMPS_API void* AMPS_HashTableLookupByHandleAndHashKey(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, t_AMPSHashTableKey* r_poHASHKey, int r_nHandle);
AMPS_API void* AMPS_HashTableLookupByHandle(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_hAMPS_HASH_HANDLE, int r_nHandle);

//IOAgents APIs
AMPS_API AMPS_IOAGENTS_HANDLE AMPS_IOAgentsInit(AMPS_HANDLE r_hAMPS_HANDLE, int r_nNoOfThreads, AMPS_IOAgentsDispatcherCallback r_pfAMPS_IOAgentsDispatcherCallback, AMPS_IOAgentsInitCallback r_pfAMPS_IOAgentsInitCallback, AMPS_IOAgentsCleanupCallback r_pfAMPS_IOAgentsCleanupCallback, void* r_pvUserData);
AMPS_API AMPS_IOAGENTS_HANDLE AMPS_IOAgentsInitEx(AMPS_HANDLE r_hAMPS_HANDLE, int r_nNoOfThreads, t_AMPSCongestionControlParam* r_poAMPSCongestionControlParam, AMPS_IOAgentsDispatcherCallback r_pfAMPS_IOAgentsDispatcherCallback, AMPS_IOAgentsInitCallback r_pfAMPS_IOAgentsInitCallback, AMPS_IOAgentsCleanupCallback r_pfAMPS_IOAgentsCleanupCallback, void* r_pvUserData);
AMPS_API void AMPS_IOAgentsCleanup(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_IOAGENTS_HANDLE r_hAMPS_IOAGENTS_HANDLE);
AMPS_API int AMPS_IOAgentsRegEvt(AMPS_IOAGENTS_HANDLE r_hAMPS_IOAGENTS_HANDLE, int r_nEventType, AMPS_EvtHandlerCallback r_pfAMPS_EventCallback);
AMPS_API int AMPS_IOAgentsCancelEvt(AMPS_IOAGENTS_HANDLE r_hAMPS_IOAGENTS_HANDLE, int r_nEventType, AMPS_EvtHandlerCallback r_pfAMPS_EventCallback);
AMPS_API int AMPS_IOAgentsSendEvt(AMPS_UIOAGENT_HANDLE r_hAMPS_UIOAGENT_HANDLE, int r_nEventType, void* r_pvEventData, int r_nSizeOfEventData);

//Log API
AMPS_API int AMPS_Log(AMPS_HANDLE r_hAMPS_HANDLE, const char* r_puchMessage , ...);

//MD5 APIs
AMPS_API AMPS_MD5_HANDLE AMPS_MD5Init(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_MD5Cleanup(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_MD5_HANDLE r_hAMPS_MD5_HANDLE);
AMPS_API int AMPS_MD5Update(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_MD5_HANDLE r_hAMPS_MD5_HANDLE, unsigned char* r_puchData, int r_nDataLength);
AMPS_API int AMPS_MD5Final(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_MD5_HANDLE r_hAMPS_MD5_HANDLE, unsigned char* r_puchMD5Hash);

//AES APIs
AMPS_API AMPS_AES_HANDLE AMPS_AESInit(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_AESCleanup(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_AES_HANDLE r_hAMPS_AES_HANDLE);
AMPS_API int AMPS_AESSetKey(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_AES_HANDLE r_hAMPS_AES_HANDLE, unsigned char* r_puchKey, int r_nBits);
AMPS_API void AMPS_AESEncrypt(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_AES_HANDLE r_hAMPS_AES_HANDLE, unsigned char* r_puchInputBuff, unsigned int r_unInputBuffLength, unsigned char* r_puchOutputBuff);
AMPS_API void AMPS_AESDecrypt(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_AES_HANDLE r_hAMPS_AES_HANDLE, unsigned char* r_puchInputBuff, unsigned int r_unInputBuffLength, unsigned char* r_puchOutputBuff);

// Memory Management APIs
AMPS_API void* AMPS_Malloc(int r_nSize);
AMPS_API void* AMPS_Realloc(void* r_pvData, int r_nSize);
AMPS_API void  AMPS_Free(void* r_pvData);

// Extended Memory Management APIs
AMPS_API void* AMPS_MemMgrInit(int r_nSize);
AMPS_API void* AMPS_MallocEx(void* r_pvMemmgr, int r_nSize);
AMPS_API void  AMPS_FreeEx(void* r_pvMemmgr, void* r_pvData);

//Scheduler APIs
AMPS_API AMPS_SCHED_HANDLE AMPS_SchedInit(AMPS_HANDLE r_hAMPS_HANDLE, int r_nMaxNumberOfInternalEvents, int r_nMaxNumberOfExternalEvents,
							  AMPS_SchedInitCallback r_pfAMPS_SchedulerInitCallback, AMPS_SchedCleanupCallback r_pfAMPS_SchedulerCleanupCallback, 
							  AMPS_SchedSetParamCallback r_pfAMPS_SchedulerSetParamCallback, AMPS_SchedScheduleCallback r_pfAMPS_SchedulerScheduleCallback);
AMPS_API void AMPS_SchedCleanup(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_SCHED_HANDLE r_hAMPS_SCHED_HANDLE);

//LinkList APIs
AMPS_API int AMPS_SListInsertSortedPrepend(void** r_ppvList, void* r_pvKey, void* r_pvData, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback);
AMPS_API int AMPS_SListInsertSortedAppend(void** r_ppvList, void* r_pvKey, void* r_pvData, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback);
AMPS_API void AMPS_SListSortPrepend(void** r_ppvList, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback);
AMPS_API void AMPS_SListSortAppend(void** r_ppvList, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback);
AMPS_API int AMPS_SListTraverse(void* r_ppvList, AMPS_LListProcessCallback r_pfAMPS_LListProcessCallback, void* r_pvArg);
AMPS_API int AMPS_SListCopy(void** r_ppvDest, void* r_pvSrc, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback, AMPS_LListCloneCallback r_pfAMPS_LListCloneCallback);
AMPS_API int AMPS_SListRemoveKey(void** r_ppvList, void* r_pvData, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback);
AMPS_API void* AMPS_SListFindData (void* r_pvList, void* r_pvData);
AMPS_API void* AMPS_SListGetNextNode(void* r_pvList);
AMPS_API void* AMPS_SListGetNodeData(void* r_pvNode);
AMPS_API void AMPS_SListAppendGivenNode(void** r_ppvList, void* r_pvSListNode);
AMPS_API void AMPS_SListPrependGivenNode(void** r_ppvList, void* r_pvGivenNode, void* r_pvNewNode);
AMPS_API t_AMPSSList* AMPS_SListPrepend(t_AMPSSList** r_ppoSList, void* r_pvData);
AMPS_API int AMPS_SListAppend(void** r_ppvList, void* r_pvData, AMPS_LListCompareCallback r_pfAMPS_LListCompareCallback);
AMPS_API t_AMPSSList* AMPS_SListLast(t_AMPSSList* r_poSList);
AMPS_API t_AMPSSList* AMPS_SListSearch(t_AMPSSList* r_poSList, AMPS_LListCompareLinkDataCallback r_pfAMPS_LListCompareCallback, void* r_pvSrcData);
AMPS_API t_AMPSSList* AMPS_SListFind (t_AMPSSList* r_poSList, t_AMPSSList* r_poSListNode);
AMPS_API int AMPS_SListRemove(t_AMPSSList** r_ppoSList, t_AMPSSList* r_poSListNode, AMPS_LListFreeLinkDataCallback r_pfAMPS_LListFreeLinkDataCallback);
AMPS_API int AMPS_SListRemoveWithOutFree(t_AMPSSList** r_ppoSList, t_AMPSSList* r_poSListNode);
AMPS_API int AMPS_SListFree(t_AMPSSList** r_ppoSList, AMPS_LListFreeLinkDataCallback r_pfAMPS_LListFreeLinkDataCallback);
AMPS_API unsigned int AMPS_SListCount(const t_AMPSSList* r_cpoSList);
AMPS_API int AMPS_SListConcat(t_AMPSSList** r_ppoSListSrc, t_AMPSSList* r_poSListDst);

AMPS_API t_AMPSDList* AMPS_DListInit(t_AMPSDList** r_ppoDList);
AMPS_API int AMPS_DListConcat(t_AMPSDList** r_ppoDListSrc, t_AMPSDList* r_poDListDst);
AMPS_API t_AMPSSList* AMPS_DListAppend(t_AMPSDList* list, void* r_pvData);
AMPS_API t_AMPSSList* AMPS_DListPrepend(t_AMPSDList* r_poDList, void* r_pvData);
AMPS_API void AMPS_DListPrependGivenNode(t_AMPSDList* r_poDList, void* r_pvData, t_AMPSSList* r_poSListNode);
AMPS_API void AMPS_DListAppendGivenNode(t_AMPSDList* r_poDList, void* r_pvData, t_AMPSSList* r_poSListNode);
AMPS_API t_AMPSSList* AMPS_DListSearch(t_AMPSDList* r_poDList, AMPS_LListCompareLinkDataCallback r_pfAMPS_LListCompareCallback, void* r_pvData);
AMPS_API t_AMPSSList* AMPS_DListFind (t_AMPSDList* r_poDList, t_AMPSSList* r_poSListNode);
AMPS_API int AMPS_DListRemove(t_AMPSDList** r_ppoDList, t_AMPSSList* r_poSListNode, AMPS_LListRemoveLinkDataCallback r_pfAMPS_LListRemoveLinkDataCallback);
AMPS_API int AMPS_DListSort(t_AMPSDList** r_ppoDList, AMPS_LListCompareLinkDataCallback r_pfAMPS_LListCompareCallback);
AMPS_API void AMPS_DListSwapNodesData(t_AMPSSList* r_poNodeOne, t_AMPSSList* r_poNodeTwo);
AMPS_API int AMPS_DListRemoveFirstNode(t_AMPSDList** r_ppoDList, AMPS_LListRemoveLinkDataCallback AMPS_LListRemoveLinkDataCallback);
AMPS_API t_AMPSSList* AMPS_DListInsertAfter (t_AMPSDList* r_poDList, t_AMPSSList* r_poSListPositionNode, void* r_pvData);
AMPS_API t_AMPSSList* AMPS_DListInsertBefore (t_AMPSDList* r_poDList, t_AMPSSList* r_poSListPositionNode, void* r_pvData);
AMPS_API void AMPS_DListFree(t_AMPSDList** r_ppoDList, AMPS_LListRemoveLinkDataCallback AMPS_LListRemoveLinkDataCallback);
AMPS_API void AMPS_DListFreeNodes(t_AMPSDList** r_ppoDList, AMPS_LListRemoveLinkDataCallback AMPS_LListRemoveLinkDataCallback);
AMPS_API void AMPS_DListTraverse(t_AMPSDList* r_poDList, AMPS_LListProcessCallback r_fpAMPS_LListProcessCallback, void* r_pvArg);
AMPS_API int AMPS_DListRemoveWithOutFree(t_AMPSDList* r_poDList, t_AMPSSList* r_poSListNode);
AMPS_API void AMPS_RemoveNthNode(t_AMPSDList** r_ppoDList, int r_nNodeLocation, AMPS_LListRemoveLinkDataCallback AMPS_LListRemoveLinkDataCallback);

AMPS_API void* AMPS_DListGetNthNode(t_AMPSDList* r_poAMPSDList, int r_nNodeLocation);
AMPS_API int AMPS_DListCopy(t_AMPSDList* r_poAMPSDListSrc, t_AMPSDList* r_poAMPSDListDest, AMPS_LListDuplicate r_pfAMPS_LListDuplicate);
AMPS_API int AMPS_DListRemoveFromData(t_AMPSDList* r_poDList, void* r_pvData, AMPS_LListRemoveLinkDataCallback r_pfAMPS_LListRemoveLinkDataCallback);

//Trace APIs
AMPS_API void AMPS_Trace(int r_nLineNumber, char* r_pchFileName, const char* r_pchFunctionName, unsigned int r_unModuleId, unsigned int r_unTraceLevel, char* r_puchMessage , ...);
AMPS_API int AMPS_GetTraceID(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForTraceID(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTraceID);
AMPS_API void AMPS_ClearTraceForTraceID(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTraceID);

AMPS_API void AMPS_SetTraceLevel(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTraceLevel);
AMPS_API void AMPS_ClearTraceLevel(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTraceLevel);
AMPS_API void AMPS_SetTraceMode(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTraceMode);
AMPS_API void AMPS_ClearTraceMode(AMPS_HANDLE r_hAMPS_HANDLE, unsigned int r_unTraceMode);

AMPS_API void AMPS_SetTraceForAMPS(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForAMPS(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForCache(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForCache(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForSAPI(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForSAPI(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForTimer(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForTimer(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForDBEngine(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForDBEngine(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForMemoryManager(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForMemoryManager(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForEventSystem(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForEventSystem(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForIOAgent(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForIOAgent(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForHeap(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForHeap(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForLog(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForLog(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForHash(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForHash(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForMemoryManagerWithGC(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForMemoryManagerWithGC(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForSched(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForSched(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_SetTraceForMD5(AMPS_HANDLE r_hAMPS_HANDLE);
AMPS_API void AMPS_ClearTraceForMD5(AMPS_HANDLE r_hAMPS_HANDLE);

//String AMPS
AMPS_API int AMPS_StringIntToString(unsigned char* r_puchBuffer, int r_nValue, int r_nBase);
AMPS_API int AMPS_StringStringToInt(t_AMPSString* r_poAMPSString, int r_nBase);
AMPS_API int AMPS_StringCopyDuplicate(t_AMPSString* r_poAMPSStringDst, t_AMPSString* r_poAMPSStringSrc);
AMPS_API void AMPS_StringFree(t_AMPSString* r_poAMPSString);
AMPS_API void AMPS_StringMove(t_AMPSString* r_poAMPSStringSrc, t_AMPSString* r_poAMPSStringDst);
AMPS_API int AMPS_StringSet(char* r_pchSrc, t_AMPSString* poAMPSStringDst);
AMPS_API int AMPS_StringSetN(char* r_pchSrc, unsigned int r_unSrcLength, t_AMPSString* r_poAMPSStringDst);
AMPS_API t_AMPSString* AMPS_StringAlloc(void);
AMPS_API int AMPS_StringAllocBuffer(t_AMPSString* r_poAMPSString, unsigned int r_unSize);
AMPS_API t_AMPSString* AMPS_StringDuplicate(t_AMPSString* r_poAMPSString);
AMPS_API int AMPS_StringCompare(t_AMPSString* r_poAMPSString1, t_AMPSString* r_poAMPSString2);
// Case insensitive
AMPS_API int AMPS_StringCompareCase(t_AMPSString* r_poAMPSString1, t_AMPSString* r_poAMPSString2);
AMPS_API int AMPS_StringPrint(int r_nTraceID, int r_nTraceLevel, char* r_pchPrefix, t_AMPSString* r_poAMPSString);
AMPS_API int AMPS_StringPrintN(int r_nTraceID, int r_nTraceLevel, char* r_pchPrefix, unsigned char* r_puchData, unsigned int r_unLength);
AMPS_API int AMPS_StringGenerateRandomString(t_AMPSString* r_poAMPSString);
AMPS_API unsigned int AMPS_StringGetOffsetOfChar(t_AMPSString* r_poAMPSString, unsigned int r_unStartOffset, unsigned char r_ucSeachChar);
AMPS_API int AMPS_StringCopySubString(t_AMPSString* r_poAMPSStringSrc, t_AMPSString* r_poAMPSStringDst, unsigned int r_unStartOffset, unsigned int r_unEndOffset);
AMPS_API int AMPS_StringAsciiDigitToNumber(char r_chDigit);
AMPS_API char AMPS_StringNumToAsciiDigit(int r_nNum);
AMPS_API char* AMPS_StringGetStringZ(t_AMPSString* r_poAMPSString);
AMPS_API int AMPS_StringCompareSubString(t_AMPSString* r_poAMPSString, t_AMPSString* poAMPSStringSubString);
AMPS_API int AMPS_StringAssign(char* r_pchSrc, t_AMPSString* r_poAMPSStringDst);
AMPS_API int AMPS_StringAssignN(char* r_pchSrc, unsigned int r_unSrcLength, t_AMPSString* r_poAMPSStringDst);
AMPS_API unsigned long AMPS_StringStringToUL(t_AMPSString* r_poAMPSString, int r_nBase);

#ifdef __cplusplus
	}
#endif

#endif //end of __HEADER_AMPS_API_H__

