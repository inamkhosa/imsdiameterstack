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
** FILE NAME      		: AMPS_Defines.h
** DESCRIPTION    		: The file contains defines and return codes for framework.
** PROJECT NAME   		: AMPS
** TYPE           		: ANSI C
** CONTRIBUTOR(S) 		: Zaka Kiani
*******************************************************************************
** $Id: AMPS_Defines.h,v 1.63 2009/04/30 13:05:30 zaka Exp $
** $Source: /work/cvsroot/amps/include/AMPS_Defines.h,v $
*******************************************************************************
*******************************************************************************
*/
#ifndef __HEADER_AMPS_DEFINES_H__
#define __HEADER_AMPS_DEFINES_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>	
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <ctype.h>


#ifndef WIN32
	#define AMPS_API
#else
#ifndef AMPS_USE_DLL 
	#define AMPS_API			__declspec( dllexport )
#else
	#define AMPS_API			__declspec( dllimport )
#endif
#endif

//#define AMPS_ENABLE_ORACLE_SUPPORT

#ifdef _MSC_VER //Detect Microsoft C++ compiler

// Disable following warnings when including Windows headers
//
// warning C4115: named type definition in parentheses
// warning C4116: unnamed type definition in parentheses
// warning C4127: conditional expression is constant
// warning C4201: nonstandard extension used : nameless struct/union
// warning C4214: nonstandard extension used : bit field types other than int
// warning C4514: unreferenced inline function has been removed
// warning C4786: symbol names being too long for the debug information
// warning C4100: unreferenced formal parameter (Warning level 4)
// warning C4710: function not inlined (Warning level 4)
#pragma warning( disable : 4115 4116 4127 4201 4214 4514 4786 4100 4710)

#endif //_MSC_VER

typedef char 			    				AMPS_BOOL;
typedef unsigned char 						AMPS_BYTE;					//An 8-bit unsigned integer

typedef void*								AMPS_HANDLE;				//amps context
typedef void*								AMPS_APP_HANDLE;			//application context
typedef void*								AMPS_APP_DATA_HANDLE;		//application data stored within AMPS_NET_HANDLE
typedef void*								AMPS_MODULE_HANDLE;			//module context
typedef void*								AMPS_APP_UIOAGENT_HANDLE;	//application thread context
typedef void*								AMPS_NET_HANDLE;			//amps network handle
typedef void*								AMPS_FILE_HANDLE;			//amps file handle
typedef void*								AMPS_CACHE_HANDLE;			//amps cache handle
typedef void*								AMPS_IOAGENTS_HANDLE;		//amps IO agents handle
typedef void*								AMPS_UIOAGENT_HANDLE;		//amps unit IO agent handle
typedef void*								AMPS_SCHED_HANDLE;			//amps sched handle
typedef void*								AMPS_APP_SCHED_HANDLE;		//application defined sched handle
typedef void*								AMPS_DBE_HANDLE;			//amps database engine handle
typedef void*								AMPS_DBES_HANDLE;			//amps database engine statement handle
typedef void*								AMPS_TIMER_ID;				//amps timer ID
typedef void*								AMPS_HASH_HANDLE;			//amps hashtable handle
typedef void*								AMPS_MD5_HANDLE;			//amps md5 handle
typedef void*								AMPS_AES_HANDLE;			//amps aes handle
typedef void*								AMPS_SLIST_HANDLE;			//amps slist handle
typedef void*								AMPS_DLIST_HANDLE;			//amps dlish handle

typedef struct _AMPSString					t_AMPSString;
typedef struct _AMPSAddr					t_AMPSAddr;
typedef struct _AMPSHashTableKey			t_AMPSHashTableKey;
typedef struct _AMPSDBEngineTable			t_AMPSDBEngineTable;
typedef struct _AMPSDBEngineResult         	t_AMPSDBEngineResult;
typedef struct _AMPSSList					t_AMPSSList;
typedef struct _AMPSDList					t_AMPSDList;
typedef struct _AMPSTimerValue    			t_AMPSTimerValue;
typedef struct _AMPSIfaceData				t_AMPSIfaceData;
typedef struct _AMPSIOVector				t_AMPSIOVector;

typedef struct _AMPSDNSNaptrRecord			t_AMPSDNSNaptrRecord;
typedef struct _AMPSDNSSrvRecord			t_AMPSDNSSrvRecord;
typedef struct _AMPSDNSATypeRecord			t_AMPSDNSATypeRecord;
typedef struct _AMPSCongestionControlParam	t_AMPSCongestionControlParam;
typedef struct _AMPSSysMemUsageControlParam	t_AMPSSysMemUsageControlParam;

#define AMPS_Max(x, y)	(((x) > (y)) ? (x) : (y))
#define AMPS_Min(x, y)	(((x) < (y)) ? (x) : (y))

#define AMPS_TRUE 								1
#define AMPS_FALSE 								0              

#ifdef WIN32
#ifdef _DEBUG
#define TRACE( nModuleID, nTraceLevel, pMessage , ... ) AMPS_Trace( __LINE__, __FILE__, __FUNCTION__, nModuleID, nTraceLevel, pMessage, __VA_ARGS__)
#else
#define TRACE( nModuleID, nTraceLevel, pMessage , ... ) 
#endif
#define LOG						AMPS_Log
#define AMPS_INLINE				__inline
#define AMPS_RAND_MAX			UINT_MAX
#else
#define TRACE( nModuleID, nTraceLevel, pMessage , a... ) AMPS_Trace( __LINE__, __FILE__, __FUNCTION__, nModuleID, nTraceLevel, pMessage, ## a)
//#define TRACE( nModuleID, nTraceLevel, pMessage , a... )
#define LOG(r_pvAMPSContext, r_puchMessage , a... ) AMPS_Log(r_pvAMPSContext, r_puchMessage, ## a)
#define AMPS_RAND_MAX		RAND_MAX
#define AMPS_INLINE			inline 
#endif

#define AMPS_INVALID_HANDLE              		0
#define AMPS_MAX_IP_STRING_LENGTH				32
#define AMPS_MAX_TUNNELING_KEY_LENGTH			32
#define AMPS_SIZE_OF_DB_USER_NAME				128
#define AMPS_SIZE_OF_DB_PWD						128
#define AMPS_SIZE_OF_DB_NAME					128
#define AMPS_SIZE_OF_DB_UNIX_SOCKET				128
#define AMPS_HASH_TABLE_KEY_SIZE				1009
#define AMPS_DNS_MAX_NAME_SIZE					256

typedef enum 
{
	AMPS_DB_TYPE_MYSQL = 1,
	AMPS_DB_TYPE_ORACLE

}e_AMPSDBType;

typedef enum 
{
	AMPS_TIMER_RESOLUTION_20MS = 1,
	AMPS_TIMER_RESOLUTION_25MS,
	AMPS_TIMER_RESOLUTION_50MS,
	AMPS_TIMER_RESOLUTION_100MS
}e_AMPSTimerResolution;

typedef enum 
{
	AMPS_MEMORY_SCHEME_STATIC = 1,
	AMPS_MEMORY_SCHEME_DYNAMIC
}e_AMPSMemoryScheme;

typedef enum 
{
	AMPS_PORT_POOL_SIZE_05 = 5,
	AMPS_PORT_POOL_SIZE_10 = 10
}e_AMPSPortPoolSize;

typedef enum 
{
	AMPS_ERROR_AC_FAILED = -15,
	AMPS_DNS_NO_RR_FOUND = -14,
	AMPS_ERROR_SOCKET_CLOSED = -13,
	AMPS_ERROR_HANDLE_EOF = -12,
	AMPS_ERROR_IO_PENDING = -11,
	AMPS_INVALID_TRACE_ID = -2,
	AMPS_ERROR_FAILURE = -1,
	AMPS_SUCCESS = 0,
	AMPS_ADDRESS_NATTED = 1,
	AMPS_ADDRESS_NOT_NATTED = 2, 
	AMPS_STATUS_PENDING = 3,
	AMPS_INTERFACE_CLOSED = 4
}e_AMPSErrorCode;

typedef enum 
{
	AMPS_MSG_AWAITING = 11,
	AMPS_MSG_PENDING = 12,
	AMPS_MSG_COMPLETED = 13
}e_AMPSMsgStatus;

typedef enum 
{
	AMPS_CONNECTION_TYPE_TCP = 5,
	AMPS_CONNECTION_TYPE_UDP = 6,
	AMPS_CONNECTION_TYPE_SCTP = 7,
	AMPS_CONNECTION_TYPE_FIFO = 10,
	AMPS_CONNECTION_TYPE_PIPE = 11,
	AMPS_CONNECTION_TYPE_STCP = 30,
	AMPS_CONNECTION_TYPE_SUDP = 31
}e_AMPSTransportType;

typedef enum 
{
	AMPS_LLIST_KEYS_ARE_EQUAL = 0,
	AMPS_LLIST_KEY_IS_GREATER = 1,
	AMPS_LLIST_KEY_IS_SMALLER = 2,
	AMPS_LLIST_KEYS_CANNOT_BE_COMPARED = 4
}e_AMPSLListKeysCompResult;

typedef enum 
{
	AMPS_TRACE_MODE_DISPLAY = 1,
	AMPS_TRACE_MODE_FILE = 2,
	AMPS_TRACE_MODE_BOTH = 3
}e_AMPSTraceMode;

typedef enum 
{
	AMPS_TRACE_LEVEL_ERROR = 1,
	AMPS_TRACE_LEVEL_WARNING = 2,
	AMPS_TRACE_LEVEL_DEBUG = 4,
	AMPS_TRACE_LEVEL_DEBUG_2 = 8,
	AMPS_TRACE_LEVEL_INFO = 16
}e_AMPSTraceLevel;

typedef enum 
{
	AMPS_FILE_MODE_READ_ONLY = 1,
	AMPS_FILE_MODE_READ_WRITE,
	AMPS_FILE_MODE_WRITE_CREATE,
	AMPS_FILE_MODE_READ_WRITE_CREATE,
	AMPS_FILE_MODE_APPEND_WRITE_CREATE,

	AMPS_FILE_MODE_APPEND_READ_WRITE_CREATE
}e_AMPSFileMode;

#define AMPS_STRING_INITIALIZER {NULL, 0}

struct _AMPSString
{
	unsigned char*	puchData;		//pointer to the message data
	unsigned int	unLength;		//size of buffer
};

struct _AMPSAddr
{
	char				pchAddr[AMPS_MAX_IP_STRING_LENGTH];
	int 				nAddrPort;
	e_AMPSTransportType oAMPSTransportType;
};

struct _AMPSHashTableKey
{
	unsigned char   puchKey[AMPS_HASH_TABLE_KEY_SIZE];       //KEY, used as node identifier
	unsigned int    unKeyLength;
};

struct _AMPSDBEngineTable
{
	int		nLengthOfField;
	char*	pchField;
};

struct _AMPSDBEngineResult
{
	void* 					pvResultObj;
	unsigned long 			ulNumberOfResults;
	unsigned long 			ulNumberOfColumns;
	unsigned long 			ulNumberOfRows;
	t_AMPSDBEngineTable**	ppoAMPSDBEngineTable;
};

struct _AMPSSList
{
	void*			pvData;
	t_AMPSSList*	poAMPSSListNext;
	t_AMPSSList*	poAMPSSListPrev;
};

struct _AMPSDList
{
	unsigned char 	uchCount;
	t_AMPSSList* 	poAMPSSListHead;
};

struct _AMPSTimerValue
{
	long	lMicroSecond;
	int		nMilliSecond;
	int		nSecond;
	int		nMinute;
	int		nHour;
	int		nDay;
	int		nMonth;
	int		nYear;
};

struct _AMPSIfaceData
{
    unsigned char	puchIfaceAddress[AMPS_MAX_IP_STRING_LENGTH];
};

struct _AMPSIOVector
{
	void*	pvIOVectorBase;
	int		nIOVectorLength;
};

struct	_AMPSDNSNaptrRecord
{
	unsigned short 		usOrder;
	unsigned short		usPreference;
	char*				pchFlags;
	char*				pchService;
	char*				pchRegexp;
	char*				pchReplacement;
};

struct _AMPSDNSSrvRecord
{
	unsigned int 		unPref;
	unsigned int 		unPort;
	unsigned int 		unWeight;
	unsigned char 		puchName[AMPS_DNS_MAX_NAME_SIZE];
};

struct _AMPSDNSATypeRecord
{
	unsigned char 		puchName[AMPS_DNS_MAX_NAME_SIZE];
};

typedef int(*AMPS_RecvDataCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, unsigned char* r_puchBuff, int r_nBuffLength, int r_nPort, char* r_chIPAddress);
typedef int(*AMPS_ConnCfmCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, AMPS_APP_DATA_HANDLE r_hAMPS_APP_DATA_HANDLE, int r_nPort, char* r_chIPAddress);
typedef int(*AMPS_ConnNotifyCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int r_nPort, char* r_chIPAddress);
typedef int(*AMPS_CloseEvtCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, int r_nPort, char* r_chIPAddress);

typedef int(*AMPS_StunClientResultCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, int r_nPort, char* r_chIPAddress);

typedef void*(*AMPS_MallocCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, int r_nSize);
typedef void*(*AMPS_ReAllocCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, void* r_pvData, int r_nSize);
typedef void(*AMPS_FreeCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, void* r_pvData);

typedef AMPS_APP_UIOAGENT_HANDLE(*AMPS_IOAgentsInitCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_UIOAGENT_HANDLE r_hAMPS_UIOAGENT_HANDLE, void* r_pvUserData);
typedef void(*AMPS_IOAgentsCleanupCallback)(AMPS_APP_UIOAGENT_HANDLE r_hAMPS_APP_UIOAGENT_HANDLE);
typedef void(*AMPS_IOAgentsDispatcherCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_IOAGENTS_HANDLE r_hAMPS_IOAGENTS_HANDLE, void* r_pvEventHandle, void* r_pvEventPayload);
typedef void(*AMPS_IOAgentsEvtHandlerCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_UIOAGENT_HANDLE r_hAMPS_UIOAGENT_HANDLE, void* r_pvEventHandle, void* r_pvEventPayload);

typedef void(*AMPS_EvtHandlerCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, void* r_pvEventHandle, void* r_pvEventPayload);
typedef int(*AMPS_EvtHandleValidationCallback)(AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, int r_nEventID, void* r_pvEventPayload);

typedef AMPS_APP_SCHED_HANDLE(*AMPS_SchedInitCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_SCHED_HANDLE r_hAMPS_SCHED_HANDLE, int r_nMaxNumberOfInternalEvents, int r_nMaxNumberOfExternalEvents);
typedef void(*AMPS_SchedCleanupCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_SCHED_HANDLE r_hAMPS_APP_SCHED_HANDLE);
typedef int(*AMPS_SchedSetParamCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_SCHED_HANDLE r_hAMPS_APP_SCHED_HANDLE);
typedef int(*AMPS_SchedScheduleCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_SCHED_HANDLE r_hAMPS_APP_SCHED_HANDLE);

typedef int(*AMPS_TimeOutNotifyCallBack)(AMPS_HANDLE r_hAMPS_HANDLE, void* r_pvData);
typedef void(*AMPS_CacheProcessUserDataCallback)(AMPS_HANDLE r_hAMPS_HANDLE, void* r_pvData);
typedef unsigned int(*AMPS_HashTableHashCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_HASH_HANDLE r_phAMPS_HASH_HANDLE, t_AMPSHashTableKey* r_poAMPSHashTableKey);
typedef void(*AMPS_HashTableProcessNodeDataCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, AMPS_APP_DATA_HANDLE r_hAMPS_APP_DATA_HANDLE);

typedef int(*AMPS_LListCompareLinkDataCallback)(void* r_pvSrcData, void* r_pvDstData);
typedef t_AMPSSList*(*AMPS_LListAppendLinkDataCallback)(t_AMPSSList** r_ppoSList, void* r_pvData);
typedef int(*AMPS_LListRemoveLinkDataCallback)(void** r_ppvData);
typedef int(*AMPS_LListFreeLinkDataCallback)(void** r_ppvData);
typedef int(*AMPS_LListCompareCallback)(void* r_pvKey1, void* r_pvKey2);
typedef void*(*AMPS_LListCloneCallback)(void* r_pvData);
typedef void(*AMPS_LListProcessCallback)(void* r_pvListNodeData, void* r_pvArg);
typedef void*(*AMPS_LListDuplicate)(void* r_pvData);

typedef AMPS_MODULE_HANDLE(*AMPS_ModuleInit)(AMPS_HANDLE r_hAMPS_HANDLE, void* r_pvUserData);
typedef void(*AMPS_ModuleCleanup)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_MODULE_HANDLE r_hAMPS_MODULE_HANDLE);

typedef enum 
{
	AMPS_CONGESTION_OFF = 1,
	AMPS_CONGESTION_ON
}e_AMPSCongestionState;

typedef void(*AMPS_CongestionControlCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, e_AMPSCongestionState r_oAMPSCongestionState);

struct _AMPSCongestionControlParam
{
	AMPS_APP_HANDLE					hAMPS_APP_HANDLE;
	int								nLowerThreshold;
	int								nHigherThreshold;
	AMPS_CongestionControlCallback	pfAMPS_CongestionControlCallback;
};

typedef enum 
{
	AMPS_SYS_MEM_USAGE_OVER_LIMIT = 1,
	AMPS_SYS_MEM_USAGE_BELOW_LIMIT
}e_AMPSSysMemUsageState;

typedef void(*AMPS_SysMemUsageControlCallback)(AMPS_HANDLE r_hAMPS_HANDLE, AMPS_APP_HANDLE r_hAMPS_APP_HANDLE, e_AMPSSysMemUsageState r_oAMPSSysMemUsageState);

struct _AMPSSysMemUsageControlParam
{
	AMPS_APP_HANDLE						hAMPS_APP_HANDLE;
	int									nLowerThreshold;
	int									nHigherThreshold;
	AMPS_SysMemUsageControlCallback		pfAMPS_SysMemUsageControlCallback;
};

#ifdef __cplusplus
   }
#endif

#endif /* __HEADER_AMPS_DEFINES_H__ */
