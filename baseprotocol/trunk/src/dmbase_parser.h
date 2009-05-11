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
 *   59 Temple Place _ Suite 330, Boston, MA  02111_1307, USA.             *
 ***************************************************************************/
#ifndef DMBASE_PARSER_H
#define	DMBASE_PARSER_H

#include "dmbase_data_types.h"

#define     DMBASE_AVP_ACCT_INTERIM_INTERVAL	       85
#define     DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED    483
#define     DMBASE_AVP_ACCT_MULTI_SESSION_ID           50
#define     DMBASE_AVP_ACCOUNTING_RECORD_NUMBER        485
#define     DMBASE_AVP_ACCOUNTING_RECORD_TYPE          480
#define     DMBASE_AVP_ACCOUNTING_SESSION_ID           44
#define     DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID       287
#define     DMBASE_AVP_ACCT_APPLICATION_ID             259
#define     DMBASE_AVP_AUTH_APPLICATION_ID             258
#define     DMBASE_AVP_AUTH_REQUEST_TYPE               274
#define     DMBASE_AVP_AUTHORIZATION_LIFETIME          291
#define     DMBASE_AVP_AUTH_GRACE_PERIOD               276
#define     DMBASE_AVP_AUTH_SESSION_STATE              277
#define     DMBASE_AVP_RE_AUTH_REQUEST_TYPE            285
#define     DMBASE_AVP_CLASS                           25
#define     DMBASE_AVP_DESTINATION_HOST                293
#define     DMBASE_AVP_DESTINATION_REALM               283
#define     DMBASE_AVP_DISCONNECT_CAUSE                273
#define     DMBASE_AVP_ERROR_MESSAGE                   281
#define     DMBASE_AVP_ERROR_REPORTING_HOST            294
#define     DMBASE_AVP_EVENT_TIMESTAMP                 55
#define     DMBASE_AVP_EXPERIMENTATION_RESULT_CODE     298
#define     DMBASE_AVP_FIRMWARE_REVISION               267
#define     DMBASE_AVP_HOST_IP_ADDRESS                 257
#define     DMBASE_AVP_INBAND_SECURITY_ID              299
#define     DMBASE_AVP_MULTI_ROUND_TIME_OUT            272
#define     DMBASE_AVP_ORIGIN_HOST                     264
#define     DMBASE_AVP_ORIGIN_REALM                    296
#define     DMBASE_AVP_ORIGIN_STATE_ID                 278
#define     DMBASE_AVP_PRODUCT_NAME                    269
#define     DMBASE_AVP_PROXY_HOST                      280
#define     DMBASE_AVP_PROXY_STATE                     33
#define     DMBASE_AVP_REDIRECT_HOST                   292
#define     DMBASE_AVP_REDIRECT_HOST_USAGE             261
#define     DMBASE_AVP_REDIRECT_MAX_CACHE_TIME         262
#define     DMBASE_AVP_RESULT_CODE                     268
#define     DMBASE_AVP_ROUTE_RECORD                    282
#define     DMBASE_AVP_SESSION_ID                      263
#define     DMBASE_AVP_SESSION_TIMEOUT                 27
#define     DMBASE_AVP_SESSION_BINDING                 270
#define     DMBASE_AVP_SESSION_SERVER_FAILOVER         271
#define     DMBASE_AVP_SUPPORTED_VENDOR_ID             265
#define     DMBASE_AVP_TERMINATION_CAUSE               295
#define     DMBASE_AVP_USER_NAME                       1
#define     DMBASE_AVP_VENDOR_ID                       266
#define     DMBASE_AVP_E2E_SEQUENCE                    300
#define     DMBASE_AVP_EXPERIMENTAL_RESULT             297
#define     DMBASE_AVP_FAILED_AVP                      279
#define     DMBASE_AVP_PROXY_INFO                      284            
#define     DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID  260  



 
t_DiamAPIReturnVal  DMBase_ParseRawDiameterMessage (HDIAMETERSTACKCONTEXT     hDiameterStackContext_io , 
                                                    unsigned char *                        pRawDiameterPacket_i , 
                                                    HDIAMETERMESSAGE *            phDiaMsgHandle_o );


t_DiamAPIReturnVal  DMBase_ConvertRawAVPsToStructAVPCollection ( 
										HDIAMETERSTACKCONTEXT  hDiameterStackContext_io , 
										HAVPCOLLECTION*		   phCollOfAVPs_o,
										unsigned char* 	       pucRawBuff_i ,
										unsigned int	       unOffsetToListBegin_i ,
										unsigned int 	       unSizeOfRawAVPList_i,
										HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io);

t_DiamAPIReturnVal  DMBase_IsAVPGrouped           ( HDIAMETERSTACKCONTEXT     hDiameterStackContext_io, 
                                                    unsigned int                  unAVPCode ,
                                                    _Bool*                         pbIsAVPGrouped);

#endif //#ifndef DMBASE_PARSER_H
