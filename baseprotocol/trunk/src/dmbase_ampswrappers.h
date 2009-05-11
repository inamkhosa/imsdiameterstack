#ifndef DMBASE_AMPSWRAPPERS_H
#define DMBASE_AMPSWRAPPERS_H


#include "dmbase_data_types.h"
#include "dmbase_dictionary.h"
#include "dmbase_transport_mgmt.h"

#define DMBASE_TCP_IPV4_SIZE	15
#define DMBASE_TRACE( nModuleID, nTraceLevel, pMessage , a... ) AMPS_Trace( __LINE__, __FILE__, __FUNCTION__, nModuleID, nTraceLevel, pMessage, ## a)

//#define DMBASE_TRACE( nModuleID, nTraceLevel, pMessage , a... )




typedef	AMPS_DBE_HANDLE						DMBASE_DBE_HANDLE;
typedef	t_AMPSDBEngineResult				DMBASE_DBEngineResult;
typedef	AMPS_APP_HANDLE						DB_MODULE_LOCAL_CONTEXT_HANDLE;
typedef	AMPS_EvtHandleValidationCallback	DMBASE_EvtHandleValidationCallback;
typedef	e_AMPSFileMode						DMBase_FileMode;
typedef	AMPS_IOAGENTS_HANDLE				DMBASE_IOAGENTS_HANDLE;
typedef	AMPS_IOAgentsDispatcherCallback 	DMBASE_IOAgentsDispatcherCallback;
typedef AMPS_IOAgentsInitCallback			DMBASE_IOAgentsInitCallback;
typedef	AMPS_IOAgentsCleanupCallback		DMABSE_IOAgentsCleanupCallback;




t_DiamAPIReturnVal DMBase_AppendSList(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBase_SList** ppSList_io, void* pvData_i);
t_DiamAPIReturnVal DMBase_SListGetNodeData(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, void* pvNode_i, void** ppvData_io);
t_DiamAPIReturnVal DMBase_RemoveSListNodeWithOutFree(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBase_SList** ppSList_io, DMBase_SList* poSListNode);
t_DiamAPIReturnVal DMBase_SListCount(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBase_SList* pSList_io , unsigned int* punCount);
t_DiamAPIReturnVal DMBase_SListFree( HDIAMETERSTACKCONTEXT		    hDiameterContext_io,
									 DMBase_SList**                         ppSList_i,
                                     AMPS_LListFreeLinkDataCallback         pfDMBase_LListFreeLinkDataCallBack_i);

t_DiamAPIReturnVal DMBase_SListRemove( HDIAMETERSTACKCONTEXT		    hDiameterContext_io,
                                       DMBase_SList**             	    ppoSList_i  ,
                                       DMBase_SList*              	    poSListNode_i,
                                       void*                            pfDMBase_LListFreeLinkDataCallBack_i);

t_DiamAPIReturnVal DMBase_SListGetNextNode(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											DMBase_SList* poList, DMBase_SList** ppoNextNode);
// Hash Wrappers

t_DiamAPIReturnVal DMBase_CreateHashTable(HDIAMETERSTACKCONTEXT			hDiameterStackContext_io,
										  int							nSizeOfHashTable_i,
										  DMBASE_HASH_HANDLE* 			pHashTableHandle_o,
										  DMBase_HashTableHashCallback	pfHashTableCallback);
t_DiamAPIReturnVal DMBase_HashTableInsert(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_HASH_HANDLE hHashTableHandle_o, void* pvData_i, DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i);
t_DiamAPIReturnVal DMBase_HashTableSearch(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_HASH_HANDLE hHashTableHandle_o, DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i, void** ppvData_o);
t_DiamAPIReturnVal DMBase_HashTableRemove(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_HASH_HANDLE hHashTableHandle_o, DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i);
t_DiamAPIReturnVal DMBase_CreateHashTableKey(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, t_DiamOctetString,DMBASE_HASHTABLE_KEY_HANDLE* phHashKeyHandle_o);
t_DiamAPIReturnVal DMBase_HashTableDelete( HDIAMETERSTACKCONTEXT            hDiameterContext_io,
                                           DMBASE_HASH_HANDLE               hhandleToHashTable_i);

t_DiamAPIReturnVal DMBase_HashTableTraverseAllEntries(	HDIAMETERSTACKCONTEXT 					hDiameterStackContext_io,
														DMBASE_HASH_HANDLE 						hHashTable_i,
														DMBASE_HashTableProcessNodeDataCallback pfCallback_i,
														void*				pvAppContext_i);


// Transport Wrappers
t_DiamAPIReturnVal DMBase_CreateTCPListenerObject(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, HTRANSPORTOBJECT hTransObj_i,t_TCPListener_Params	oTCPListenerParams_i);
t_DiamAPIReturnVal DMBase_SendBufferOnTransport(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, HTRANSPORTOBJECT hTransport_i, unsigned char* puchBuffer_i, int nBufferLength_i);
t_DiamAPIReturnVal DMBase_OpenTCPConnection(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, HTRANSPORTOBJECT hTransport_i, t_TCPOpen_Params	oTCPOpenParams_i);
t_DiamAPIReturnVal DMBase_CloseTCPConnection(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, HTRANSPORTOBJECT hTransportObject);
// Mempry Wrappers
t_DiamAPIReturnVal DMBase_Malloc(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, void**  ppMemoryPointer_io ,int nSize_i);
t_DiamAPIReturnVal DMBase_Free(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, void** ppMemoryPointer_io);

t_DiamAPIReturnVal DMBase_GetUsrDataFromNetHandle(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, void** ppvUserData);
t_DiamAPIReturnVal DMBase_SetUsrDataToNetHandle(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, void* pvUserData);

//Timer APIs

t_DiamAPIReturnVal DMBase_StartTimer(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, unsigned int unExpiryTime, DMBase_TimeOutNotifyCallBack pfTimerCallBack, void* pvData, DMBASE_TIMERID* poTimerID);
t_DiamAPIReturnVal DMBase_KillTimer(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_TIMERID oTimerID);


// Database API Wrappers

t_DiamAPIReturnVal DMBASE_DBEngin_Init(HDIAMETERSTACKCONTEXT		hDiameterContext_io,
                                       char*                        pchHostName_i,
                                       char*                        pchUserName_i,
                                       char*                        pchPassword_i,
                                       char*                        pchDataBaseName_i,
                                       DMBASE_DBE_HANDLE*           phBDEngineHandle_o);

t_DiamAPIReturnVal DMBASE_DBEngin_Cleanup(HDIAMETERSTACKCONTEXT		hDiameterContext_io,
                                          DMBASE_DBE_HANDLE         hBDEngineHandle_o);

t_DiamAPIReturnVal DMBASE_DBEngineQuery(HDIAMETERSTACKCONTEXT		hDiameterContext_io,
                                        DMBASE_DBE_HANDLE           hBDEngineHandle_i,
                                        const char*                 pcchQueryStatement_i,
                                        unsigned long               ulLengthOfQuery_i,
                                        DMBASE_DBEngineResult*      poDBEngineResult_o);

t_DiamAPIReturnVal DMBASE_DBEngineFreeResults( HDIAMETERSTACKCONTEXT	     hDiameterContext_io,
                                               DMBASE_DBE_HANDLE             hBDEngineHandle_i,
                                               DMBASE_DBEngineResult*        poDBEngineResult_i);


//MD5 APIs
t_DiamAPIReturnVal  DMBase_MD5Init(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_MD5_HANDLE* phMD5_io);
void                DMBase_MD5Cleanup(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_MD5_HANDLE hMD5_io);
t_DiamAPIReturnVal  DMBase_MD5Update(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_MD5_HANDLE hMD5_io,
                                        unsigned char* puchData_i, int nDataLength_i);
t_DiamAPIReturnVal  DMBase_MD5Final(HDIAMETERSTACKCONTEXT hDiameterStackContext_io, DMBASE_MD5_HANDLE hMD5_io,
                                    unsigned char* puchMD5Hash_o);



t_DiamAPIReturnVal DMBase_EvtSysSetEvtHandleValidationCallback( HDIAMETERSTACKCONTEXT    				hDiameterContext_io,
				DMBASE_EvtHandleValidationCallback		pf_EvtValidationCallback_i );



t_DiamAPIReturnVal DMBase_EvtSysRegIntEvt(HDIAMETERSTACKCONTEXT hDiameterContext_io,
                        int nEventType_i,void* pvfuncEvtHandler_i,void* pvEventdata_i);

t_DiamAPIReturnVal DMBase_EvtSysRegExtEvt(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											int nEventType_i, void* pvfuncEvtHandler_i,
											void* pvEventdata_i);

t_DiamAPIReturnVal DMBase_IOAgentsRegEvt(	void*	pvIOAgentHandle_io,
											int 	nEventType_i,
											void* 	pvfuncEvtHandler_i);

t_DiamAPIReturnVal DMBASE_EvtSysSendIntEvt(HDIAMETERSTACKCONTEXT		hDiameterContext_io,
                                           int                          nEventType,
                                           void*                        poEventData,
                                           unsigned int                 unSizeofEventData);



t_DiamAPIReturnVal DMBase_CreateFileObject( HDIAMETERSTACKCONTEXT    	hDiameterContext_io,
											   char*					 	pcFileName_i,
											   void**					 	ppvFileHadle_o,
											   DMBase_FileMode			 	oFileMode_i );

t_DiamAPIReturnVal DMBase_FileWrite( HDIAMETERSTACKCONTEXT    	hDiameterContext_io,
										void*					  	pvFileHadle_o,
										char*					  	pcBuffTowrite_i,
										int					  		nSizeOfBuff_i,
										int*					  	pnNumBytesWritten_o );


t_DiamAPIReturnVal DMBase_NetworkToHostShort( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned short usToConvert_i,
											  unsigned short* pusConvertedShort_o);

t_DiamAPIReturnVal DMBase_NetworkToHostLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long unToConvert_i,
											  unsigned long* punConvertedLong_o);

t_DiamAPIReturnVal DMBase_HostToNetworkShort( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned short usToConvert_i,
											  unsigned short* pusConvertedShort_o);

t_DiamAPIReturnVal DMBase_HostToNetworkLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long unToConvert_i,
											  unsigned long* punConvertedLong_o);


t_DiamAPIReturnVal DMBase_EvtSysGetEventType(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											void* pvEventHandle_i, int* pnEventType_io);

t_DiamAPIReturnVal DMBase_EvtSysGetEventSize(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											void* pvEventHandle_i, int* pnEventSize_io);

/*
t_DiamAPIReturnVal DMBase_CreateUDPObject(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											void* pvEventHandle_i, int* pnEventSize_io);

t_DiamAPIReturnVal DMBase_CreateUDPObjectBlocking(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											void* pvEventHandle_i, int* pnEventSize_io);

*/

t_DiamAPIReturnVal DMBase_IOAgentsInit(HDIAMETERSTACKCONTEXT    			hDiameterContext_i,
									   int 									nNoOfThreads_i,
									   DMBASE_IOAgentsDispatcherCallback 	pf_IOAgentsDispatcherCallback_i,
									   DMBASE_IOAgentsInitCallback 			pf_IOAgentsInitCallback_i,
									   DMABSE_IOAgentsCleanupCallback 		pf_IOAgentsCleanupCallback_i,
									   void* 								pvUserData_i,
									   DMBASE_IOAGENTS_HANDLE*		 		phIOAgentsHandle_o);



#endif /* DMBASE_AMPSWRAPPERS_H */

