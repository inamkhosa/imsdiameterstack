/***************************************************************************
 *   Copyright (C) 2008 by simab   *
 *   simabshahid@advancedims.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef	DIAM_DATA_TYPES_H
#define	DIAM_DATA_TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "AMPS_API.h"
#include "AMPS_Defines.h"




#define     DMBASE_FLAGS_ALL_SET								0xFF
#define     DMBASE_FLAGS_ALL_CLEAR								0x00
#define     DMBASE_DEFAULT_FLAGS_VALUE                          DMBASE_FLAGS_ALL_CLEAR
#define     DMBASE_TRACE_LEVEL_ERROR                            1
#define     DMBASE_TRACE_LEVEL_WARNING                          2
#define     DMBASE_TRACE_LEVEL_DEBUG                            4
#define	    DMBASE_TRACE_LEVEL_DEBUG_2                          8
#define     DMBASE_TRACE_LEVEL_INFO                             16
#define     DMBASE_STANDARD_DIAMETER_PORT                       3868

#define     TRUE                                                1
#define     FALSE                                               0

#define     DMBASE_HASHTABLE_MAX_SIZE                           1101
#define     DMBASE_HASH_TABLE_KEY_SIZE                          1009
#define     DMBASE_MAX_HASH_KEY_COUNT                           64

#define     DMBASE_MAX_HOST_SUPPORTED_APP                       256

#define     DMBASE_MAX_REALM_SUPPORTED                          16
#define     DMBASE_REALM_NAME_SIZE                              128

#define     DMBASE_MAX_REALM_COUNT                              32
#define     DMBASE_REALM_KEY_SIZE                               128

#define     DMBASE_MAX_PEER_SUPPORTED_APP                       128

#define     DMBASE_MAX_PENDING_MSG_LIST                         16
#define     DMBASE_ROUTING_SERVER                               10

#define		DMBASE_MEM_BLOCK_SIZE_FOR_AVP_ALLOCS				16*1024 //16k buf size

#define		DMBASE_MAX_SMALL_STRING_SIZE						256
#define		DMBASE_MAX_MEDIUM_STRING_SIZE						512
#define		DMBASE_MAX_LARGE_STRING_SIZE						1024

#define		DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS					8388608 // 2^23
#define		DMBASE_MAX_IP_STRING_SIZE							DMBASE_MAX_SMALL_STRING_SIZE

#define		DMBASE_IANA_ADDR_FAMILY_IP_V4						1
#define		DMBASE_IANA_ADDR_FAMILY_IP_V6						2
#define		DMBASE_IPV4_ADDR_SIZE_IN_OCTETS						4
#define		DMBASE_IPV6_ADDR_SIZE_IN_OCTETS						16
#define		DMBASE_IP_ADDRTYPE_SIZE_IN_OCTETS					2

#define 	DMBASE_MAX_DICTIONARY_SIZE							3000
#define 	DMBASE_MAX_DIC_FUNCPTR_MAPTABLE_SIZE				13





typedef void*							FRAMEWORK_HANDLE;

//List typedefs
typedef t_AMPSSList 					DMBase_SList;
typedef t_AMPSDList						DMBase_DList;

//Transport related typedefs
typedef AMPS_MallocCallback				DMBase_MallocCallback;
typedef AMPS_FreeCallback				DMBase_FreeCallback;
typedef AMPS_ReAllocCallback			DMBase_ReAllocCallback;
typedef AMPS_ConnNotifyCallback			DMBase_ConnNotifyCallback;
typedef AMPS_RecvDataCallback			DMBase_RecvDataCallback;
typedef AMPS_CloseEvtCallback			DMBase_CloseEvtCallback;
typedef	AMPS_ConnCfmCallback			DMBase_ConnCfmCallback;

// Timer related  typedefs
typedef AMPS_TIMER_ID                   DMBASE_TIMERID;
typedef AMPS_TimeOutNotifyCallBack      DMBase_TimeOutNotifyCallBack;

//Hash typedefs
typedef AMPS_HASH_HANDLE				DMBASE_HASH_HANDLE;
typedef AMPS_NET_HANDLE                 DMBASE_NET_HANDLE;
typedef void*							DMBASE_HASHTABLE_KEY_HANDLE;
typedef AMPS_HashTableHashCallback		DMBase_HashTableHashCallback;
typedef AMPS_HashTableProcessNodeDataCallback DMBASE_HashTableProcessNodeDataCallback;
typedef t_AMPSHashTableKey				t_DiamHashTableKey;
//MD5 typedefs
typedef AMPS_MD5_HANDLE                 DMBASE_MD5_HANDLE;


//DB typedefs
typedef	t_AMPSDBEngineResult			t_DMBASEDBEngineResult;

            /**s*******************************
            *   Diameter Defined DataTypes   *
            **********************************/

	typedef enum DiamAPIReturnVal
	{
		DMBase_Retval_Success,
		DMBase_Retval_Failure,
		DMBase_Retval_IncorrectParameters,
		DMBase_Retval_MoreInfoRequired,
		DMBase_Retval_AccessDenied,
		DMBase_Retval_UnableToOpenDevice,
		DMBase_Retval_Insufficient_Buffer,
		DMBase_Retval_Not_Found,
		DMBase_Retval_Not_Supported,
		DMBase_Retval_Null_Pointer,
		DMBase_Retval_Unknown_AVP,
		DMBase_Retval_InvalidAVPData,
		DMBase_Retval_InvalidMsgHeader,
		DMBase_Retval_Realm_Not_Supported,
		DMBase_Retval_App_Not_Supported,
		DMBase_Retval_MemNotAvailable,
		DMBase_Retval_Limit_Exceed,
		DMBase_Retval_No_Commom_Application,
		DMBase_Retval_Msg_Stored,
		DMBase_Retval_Invalid_Event,
		DMBase_Retval_Unable_To_Deliver
	} t_DiamAPIReturnVal;


	typedef struct TCPListener_Params
	{
		int 						nMinMsgSize;
		int 						nFixedMsgSize;
		DMBase_MallocCallback		pfMallocCallback;
		DMBase_FreeCallback			pfFreeCallback;
		DMBase_ReAllocCallback		pfReAllocCallback;
		DMBase_ConnNotifyCallback	pfConnNotifyCallback;
		DMBase_RecvDataCallback		pfRecvDataCallback;
		DMBase_CloseEvtCallback		pfCloseEvtCallback;
		void*						pvAppHandle;
	}t_TCPListener_Params;



	typedef struct TCPOpen_Params
	{
		int 						nMinMsgSize;
		int 						nFixedMsgSize;
		DMBase_MallocCallback		pfMallocCallback;
		DMBase_FreeCallback			pfFreeCallback;
		DMBase_ReAllocCallback		pfReAllocCallback;
		DMBase_ConnCfmCallback		pfConnCfmCallback;
		DMBase_RecvDataCallback		pfRecvDataCallback;
		DMBase_CloseEvtCallback		pfCloseEvtCallback;
		void*						pvAppDataHandle;
		void*						pvAppHandle;
	}t_TCPOpen_Params;



    /********************************************************
    **           Diameter Basic Data Types                  *
    ********************************************************/

/*********OctectString**********/


typedef  struct DiamOctetString
{

    unsigned char*	pucOctetString;
    unsigned int	unNumOfOctets;

}t_DiamOctetString;


	/*********Usigned32************/

typedef  struct DiamUnsigned32
{
    unsigned int*	punUnsigned32;
    unsigned int	unNumOfOctets;

}t_DiamUnsigned32;

	/***********Unsigned64***********/

typedef  struct DiamUnsigned64
{
    unsigned long long *	pullUnsigned64;
    unsigned int			unNumOfOctets;
}t_DiamUnsigned64;


	/****************Integer32************/


typedef  struct DiamInteger32
{
    int*			pnInteger32;
    unsigned int	unNumOfOctets;

}t_DiamInteger32;


        /***********Integer64 *********/

typedef  struct DiamInteger64
{
    long long *		pllInteger64;
    unsigned int	unNumOfOctets;

}t_DiamInteger64;

	/*********Float32  *******/

typedef  struct DiamFloat32
{
    float*			pflFloat32;
    unsigned int 	unNumOfOctets;

}t_DiamFloat32;

	/**********Float64  **********/

typedef  struct DiamFloat64
{
    double*			pdFloat64;
    unsigned int	unNumOfOctets;

}t_DiamFloat64;

/********* IP Address (derivd Data type )*/
typedef struct	IPAddr
{
	unsigned	short	usIPVersion;
	unsigned	char	pucIPString[DMBASE_MAX_IP_STRING_SIZE];
}t_IPAddr;

typedef  struct DiamIPAddress
{
    t_IPAddr*		poIPAddr;
    unsigned int	unNumOfOctets;
}t_DiamIPAddress;



/*************Defined data types ( derived Datatypes )***************/


typedef     t_DiamUnsigned32       t_DiamTime;
typedef     t_DiamOctetString      t_DiamUTF8String;
typedef     t_DiamOctetString      t_DiameterIdentity;
typedef     t_DiamOctetString      t_DiameterURI;
typedef     t_DiamInteger32        t_DiamEnum;


/*************Message Related Data typed *********************/
typedef struct DiameterHeader
{
	
    unsigned char ucVersion ;
	unsigned int	unMessageLength;
    unsigned char ucFlags;
	unsigned int	unCommandCode;
    unsigned int  unApplicationID;
    unsigned int  unHopByHopID;
    unsigned int  unEndToEndID;

} t_DiameterHeader;

typedef DMBase_SList*	HAVPCOLLECTION;




////////////////////////////////////////////////////////////
typedef enum AVPFlagRule
{
	AVPFlagRule_Must,
	AVPFlagRule_May,
	AVPFlagRule_ShouldNot,
	AVPFlagRule_MustNot
}t_AVPFlagRule;

typedef enum AVPFlagAction
{
	AVPFlagAction_Set,
	AVPFlagAction_Clear
}t_AVPFlagAction;

typedef  struct  AVPFlag
{
    t_AVPFlagRule	oFlagRule;
    t_AVPFlagAction	oFlagAction;
} t_AVPFlag;



////////////////////////////////////////////////////////////
typedef struct PeerTableEntry           t_PeerTableEntry;
typedef t_PeerTableEntry*               HPEERTABLEENTRY;



typedef struct PeerTable
{
    DMBASE_HASH_HANDLE                  hHashTableHandle;
}t_PeerTable;

typedef enum ServerRole
{
    SR_PRIMARY,
    SR_SECONDARY
}t_ServerRole;

typedef struct RoutingServer
{
    unsigned int                        unPriority;
    t_DiamOctetString                   oPeerIdentity;
}t_RoutingServer;

typedef struct RealmHashTable
{
    DMBASE_HASH_HANDLE  hHashTable;
    t_DiamHashTableKey  oHashKeys[DMBASE_MAX_HASH_KEY_COUNT];
    unsigned int        unHashKeyCount;
}t_RealmHashTable;

typedef struct RealmTable
{
    t_RealmHashTable                    oRealmHashTable;
    unsigned char                       ucRealmList[DMBASE_MAX_REALM_SUPPORTED][DMBASE_REALM_NAME_SIZE];
    unsigned int                        unRealmListCount;

}t_RealmTable;



typedef enum DiamAppType
{
    Accounting_Application,
    Authorization_Application,

}t_DiamAppType;

typedef struct DiamAppInfo
{
    unsigned int unAppID;
    t_DiamAppType oAppType;
    unsigned int unVendorID;

}t_DiamAppInfo;

// definition for stack context


typedef 	struct DiameterBaseAPIContext	t_DiameterBaseAPIContext;

typedef     t_DiameterBaseAPIContext* 		HDIAMETERSTACKCONTEXT;


typedef 	struct	MemoryBlockForAVPs	t_MemoryBlockForAVPs;
typedef		t_MemoryBlockForAVPs*	HMSGALLOCATIONCONTEXT;

typedef  t_DiamAPIReturnVal ( * t_PointerToFuncValidateAVPData )
                            (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,void  *pdata);

typedef  t_DiamAPIReturnVal ( * t_PointerToFuncAVPAlloc )
                            (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
							 void  **pdata, unsigned int unSize_i , HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

typedef  t_DiamAPIReturnVal ( * t_PointerTofuncAVPDeAlloc )
                            (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
							 void  ** ppdata, HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

typedef  t_DiamAPIReturnVal ( * t_PointerTofuncGetRawData )
                            (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,void  *pdata_o, void *pdata_i , unsigned int	unSizeOfRawBuff_i);

typedef  t_DiamAPIReturnVal ( * t_PointerTofuncGetStructData )
                            (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
							 void  *pdata_i, void ** ppdata_o,
							 unsigned int  nSize_i,HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

typedef  t_DiamAPIReturnVal ( * t_PointerTofuncDebugDumpAVPData )
                            (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,void  *pdata_i, unsigned int  nSize_i , FILE* pfFilePtr_i);


typedef  struct  AVPDictionaryFunctionPtrs
{
    t_PointerToFuncValidateAVPData      pfValidateAVPData;
    t_PointerToFuncAVPAlloc             pfAVPAlloc;
    t_PointerTofuncAVPDeAlloc           pfAVPDeAlloc;
    t_PointerTofuncGetRawData	  		pfWriteRawDataToMemory;
    t_PointerTofuncGetStructData        pfGetStructData;
    t_PointerTofuncDebugDumpAVPData		pfDebugDumpAVPData;

}t_AVPDictionaryFunctionPtrs;


typedef  struct  AVPDictionaryElement
{
    unsigned int                        unAVPCode;
    t_DiamOctetString                   oAVPName;
    t_DiamOctetString                   oAVPDataType;
    t_AVPFlag                           oMFlag;
    t_AVPFlag                           oPFlag;
    unsigned int                        unVendorID;
    t_AVPDictionaryFunctionPtrs         oAVPDictionaryFunctionPtrs ;
    _Bool                               bIsGrouped;
    _Bool                               bIsPredefinedByRFC3588;
}t_AVPDictionaryElement;


typedef struct MappingTableElement
{
    unsigned	char					pucAVPDataTypeName[DMBASE_MAX_SMALL_STRING_SIZE];
    t_AVPDictionaryFunctionPtrs         oAVPDictionaryFunctionPtrs ;
}t_MappingTableElement;


typedef struct	DiamDictionary
{
	unsigned int                    unDictSize;
	t_AVPDictionaryElement*         poDictionaryArray;
}t_DiamDictionary;


 struct	MemoryBlockForAVPs
{
	unsigned char	pucMemBlockForAVP[DMBASE_MEM_BLOCK_SIZE_FOR_AVP_ALLOCS];
	unsigned char*	pucCurrPtr;
};



typedef struct DiameterMessage
{
   t_DiameterHeader			oDiaHeader;
   HAVPCOLLECTION			hCollectionOfAVPs;
   t_MemoryBlockForAVPs		oMemBlockForAVPs;
   HDIAMETERSTACKCONTEXT	hDiameterStackContext;//for back pointer access to stack
} t_DiameterMessage;


typedef    t_DiameterMessage*  HDIAMETERMESSAGE;

/***********Failover relatd datatypes ******************/

typedef struct FailoverSupportData
{
    unsigned int unLocalHopByHopId;
    unsigned int unActualHopByHopId;
    unsigned int unEndToEndId;
    HDIAMETERMESSAGE hDiamMsg;
    HPEERTABLEENTRY hPeer;

}t_FailoverSupportData;

typedef t_FailoverSupportData* HFAILOVERSUPPORTDATA;

typedef enum PCBStatus
{
    PS_OKAY,
    PS_SUSPECT,
    PS_DOWN,
    PS_REOPEN,
    PS_INITIAL
}t_PCBStatus;

typedef enum FailoverSMEvent
{
   FSME_RECEIVE_DWA,
   FSME_RECEIVE_NON_DWA,
   FSME_TIMER_EXPIRES,
   FSME_CONNECTION_UP,
   FSME_CONNECTION_DOWN

}t_FailoverSMEvent;

typedef struct PCB
{
    t_PCBStatus oStatus;
    _Bool bPending;
    unsigned int unTw;
    short usNumDWA;
    DMBASE_TIMERID oTimerID;

}t_PCB;

typedef t_PCB* HPCB;

typedef t_DiamAPIReturnVal (*t_DiameterFSMAction)(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                     HPEERTABLEENTRY       hPeer_i,
                                                     t_FailoverSMEvent     oFSMEvent_i,
                                                     void*                 pvData);

/************* Transport and Peer Management ***********/
typedef enum PeerState
{
    Closed,
    Wait_Conn_Ack,
    Wait_I_CEA ,
    Wait_Conn_Ack_Elect,
    Wait_Returns,
    R_Open,
    I_Open,
    Closing

} t_PeerState;




typedef struct __UnknownInitiator
{
    t_DiameterIdentity	oHostName;
	DMBASE_NET_HANDLE	hTransport;
} t_UnknownInitiator;

 typedef struct TLSData
{

} t_TLSData;

typedef enum DiamTransport
{
    TCP,
    SCTP
} t_DiamTransportType;

typedef enum IPAddrType
{
    IP_v4,
    IP_v6
}t_IPAddrType;

typedef struct DiameterTCPTransport
{
    t_DiamOctetString			oIPAddress;
    t_DiamOctetString			oFQDN;
    unsigned int                unPort;
    t_IPAddrType                oIPAddrType;
}t_DiameterTCPTransport;

typedef struct DiameterSCTPTransport
{
    DMBase_SList*               pListOfIPAddresses;
    DMBase_SList*               pListOfFQDNs;
    unsigned int                unPort;
    t_IPAddrType                oIPAddrType;
}t_DiameterSCTPTransport;

typedef struct DiameterTransportObject
{
	t_DiamTransportType         oTransportType;

    union
    {
        t_DiameterTCPTransport  oDiamTCPTransport;
        t_DiameterSCTPTransport oDiamSCTPTransport;
    };

    void*                       pvDiamAppContext;
    void*                       pvTransportLayerHandle;
}t_DiameterTransportObject;

typedef enum PeerRole
{
    Undefined,
    Initiator,
    Responder

}t_PeerRole;

typedef t_DiameterTransportObject*	HTRANSPORTOBJECT;

struct PeerTableEntry
{
    t_DiamOctetString           oHostIdentity;
    t_PeerRole                  oPeerConfiguredRole;
    t_PeerRole                  oPeerConnectionRole;
    t_PeerState                 oPeerState;
    _Bool                       bIsStatic;
    t_DiamTime                  oExpiryTime;
    _Bool                       bIsTLSEnabled;
    t_TLSData                   oOptionalTLSData;
    DMBASE_TIMERID              oTimerID;
    HTRANSPORTOBJECT            hConfiguredTransport;
    HTRANSPORTOBJECT            hInitiatorTransport;
    HTRANSPORTOBJECT            hResponderTransport;
    t_DiamAppInfo               oSupportedAppList[DMBASE_MAX_PEER_SUPPORTED_APP];
    unsigned int                unSupportedAppCount;
    t_PCB                       oPCB;
    void**                      ppvPendingMsgList[DMBASE_MAX_PENDING_MSG_LIST];
    unsigned int                unPendingMsgListCount;
    _Bool		              	bIsWatchdogSupported;
    HDIAMETERSTACKCONTEXT       hDiameterStackContext;
};

////////////////Peer State Machine//////////////////////////////////
typedef enum DiameterPSMEvent
{
    Start,
    R_Conn_CER,
    I_Rcv_Conn_Ack,
    I_Rcv_Conn_Nack,
    I_Rcv_CER,
    R_Rcv_CER,
    I_Rcv_CEA,
    R_Rcv_CEA,
    I_Rcv_Non_CEA,
    I_Peer_Disc,
    R_Peer_Disc,
    I_Rcv_DPR,
    R_Rcv_DPR,
    I_Rcv_DPA,
    R_Rcv_DPA,
    I_Rcv_DWR,
    R_Rcv_DWR,
    R_Rcv_DWA,
    I_Rcv_DWA,
    Win_Election,
    Send_Message,
    I_Rcv_Message,
    R_Rcv_Message,
    Timeout,
    Stop
} t_DiameterPSMEvent;


typedef t_DiamAPIReturnVal (*t_DiameterPSMAction)(	HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
													HPEERTABLEENTRY 		hPeerTableEntry_i,
													HDIAMETERMESSAGE 		hDiameterMsg_i,
													t_DiameterPSMEvent 		oPSMEvent_i,
													void* pData);
/////////Realm Management///////////////////////////////////////////


typedef struct ApplicationIdentifier
{
    unsigned int            unAppID;
    unsigned int            unVendorID;
} t_ApplicationIdentifier;

typedef enum LocalAction
{
    LOCAL,
    RELAY,
    PROXY,
    REDIRECT
} t_LocalAction;

typedef struct RealmTableEntry
{
    t_DiamOctetString       oRealmName;
    t_ApplicationIdentifier oAppIdent;
    t_LocalAction           oLocalAction;
    DMBase_SList*           pServerIDList;
    _Bool                   bIsStatic;
    t_DiamTime              oExpirationTime;
    t_RoutingServer         oRoutServerList[DMBASE_ROUTING_SERVER];
    unsigned int            unRoutingServerCount;
             int            unPrimaryServer;
    DMBase_SList*           poPendingMsgQueue;

} t_RealmTableEntry;

typedef t_RealmTableEntry*  HREALMTABLEENTRY;

typedef struct __NetHandleData
{
    HPEERTABLEENTRY hPeer;
    unsigned char ucMsgHeader[20];
    _Bool	bIsHeaderReceived;
	//TODO : Add Stack Context over here.
}t_NetHandleData;


/////////////////////////////////////////////////////////////////////
typedef struct DiaStackInitData
{
    t_DiamOctetString       oDiamAPILogFileName;
    unsigned int            unDiamAPILogLevel;
    DMBase_SList*           pListOfListenAddresses;
    DMBase_SList*           pListOfStaticPeers;
    DMBase_SList*           pListOfRealmEntries;
    unsigned int            unTcTimer;
    DMBase_SList*           pListOfDictionaryFileNames;
    t_DiameterIdentity      oHostName;
    t_DiameterIdentity      oRealmName;
	unsigned char           pucHostIPAddress[DMBASE_MAX_IP_STRING_SIZE];
    unsigned int            unVendorID;
    t_DiamUTF8String        oProductName;
} t_DiaStackInitData;


//////////////////////////AVP Datatypes///////////////////////////////////
typedef struct AVPHeader
{

    unsigned int            unAVPCode;
    unsigned char           ucFlags;
	unsigned int			unAVPLength;
    unsigned int            unVendorID;
} t_AVPHeader;


typedef enum AVP_Pars_ErrCode
{
	AVP_ParsErrVal_Success

}t_AVP_Pars_ErrCode;


typedef struct AVP
{
    t_AVPHeader				oAVPHeaderInst;
	HAVPCOLLECTION			hCollectionOfAVPs;
    void *					pData;
	//TODO!! Add support for filling this in parsing and change GetAVP and its users to accomodate it!!!
	t_AVP_Pars_ErrCode		oAVP_Pars_ErrCode;
	HDIAMETERSTACKCONTEXT	hDiameterStackContext;//for back pointer access to stack
	HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io;//for allocation management
} t_AVP;

typedef    t_AVP*  HAVP;

////////////////////////Diameter Context//////////////////////////////////////////////////
struct DiameterBaseAPIContext
{
    t_DiamOctetString       oDiamAPILogFileName;
    unsigned int            unDiamAPILogLevel;
    t_DiameterIdentity      oHostName;
    t_DiameterIdentity      oRealmName;
    unsigned char           pucIPAddress[DMBASE_MAX_IP_STRING_SIZE];
    unsigned int            unVendorID;
    t_DiamUTF8String        oProductName;
    t_PeerTable*            poPeerTable;
    t_RealmTable*           poRealmTable;
    DMBase_SList*           pListOfListenAddresses;
    unsigned int            unTcTimer;
    FRAMEWORK_HANDLE        hFrameworkHandle;
    DMBase_SList*           pListOfTempInitiatorTransportObjects;
    t_DiamAppInfo           SupportedAppList[DMBASE_MAX_HOST_SUPPORTED_APP];
    unsigned int            unSupportedAppCount;
    t_DiamDictionary        oDictionary;
    DMBASE_HASH_HANDLE      hAppMsgProcessorCallbackHashTable;
	t_AVPDictionaryElement  oDmBase_AVPDictionary[DMBASE_MAX_DICTIONARY_SIZE];
	t_MappingTableElement	oDiam_FuncPtrMappingTable[DMBASE_MAX_DIC_FUNCPTR_MAPTABLE_SIZE];
    t_DiameterPSMAction		oPSMActions[Closing+1][Stop+1];
    t_DiameterFSMAction		oFSMActions[PS_INITIAL+1][FSME_CONNECTION_DOWN+1];

};

//////////////////////////////////////////////////////////////////////////
#endif // #ifndef DIAM_DATA_TYPES_H


