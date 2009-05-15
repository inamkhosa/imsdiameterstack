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
#include "dmbase_dictionary.h"
#include "dmbase_avp.h"
#include "dmbase_message.h"
#include "dmbase_parser.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_initconfig.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>




/* external */
extern	int							g_nDiamBaseTraceID ;


/************************************************************************************
** Function Name:                                                                   * 
**		  DMBase_ValidateDiamUnsigned32                                             *
**                                                                                  *
** Parameters:                                                                      *
**		 HDIAMETERSTACKCONTEXT     hDiameterStackContext_io,                         *
                      type: input                                                   *
**		      detail : this is a C style NULL terminated char array whose           *
**				    length is to be calculated                                      *
**                                                                                  *
**		void*     pData_i                                                           *
**		      type: input                                                           *
**		      detail: This is a flag indicating whether logging should              *
**			      be done inside this function or not                               *
** Return:                                                                          *
**		                                                                            *
**                                                                                  *
*************************************************************************************
** Created By: 		: Simab Shahid                                                  *
*************************************************************************************
*************************************************************************************/


t_DiamAPIReturnVal DMBase_ValidateDiamUnsigned32 ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   	void*                         pData_i )
{
    
    unsigned int            unAVPData;               
    t_DiamUnsigned32*       poTempDiamUnsigned32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }
        
    if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamUnsigned32 =    (t_DiamUnsigned32*) pData_i;
      
    unAVPData = poTempDiamUnsigned32->punUnsigned32[poTempDiamUnsigned32->unNumOfOctets]; 
     
  //  TODO:  validate unDMBase_AVPData
    
    
    return DMBase_Retval_Success;
    
}




t_DiamAPIReturnVal DMBase_ValidateDiamEnum (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											 void*                      pData_i )
{
    
    int           nAVPData;               
    t_DiamEnum*   poTempDiamEnum = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
            
    poTempDiamEnum =    (t_DiamEnum*) pData_i;
      
    nAVPData = poTempDiamEnum->pnInteger32[poTempDiamEnum->unNumOfOctets]; 
     
  //  TODO:  validate unDMBase_AVPData
    
    return(DMBase_Retval_Success);    
}



t_DiamAPIReturnVal DMBase_ValidateDiamUTF8String (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void*                        pData_i )
{
    
    char *              pcAVPData;
    void *              pMemCpyReturnValue = NULL;              
    t_DiamUTF8String*   poTempDiamUTF8String = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamUTF8String =    (t_DiamUTF8String*) pData_i;
      
    
    //  TODO:  validate unDMBase_AVPData
    
    return(DMBase_Retval_Success);
}



t_DiamAPIReturnVal DMBase_ValidateDiamOctetString (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												    void*                       pData_i )
{
    t_DiamOctetString*       poTempDiamOctetString = NULL;
    
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
            
    poTempDiamOctetString =    (t_DiamOctetString*) pData_i;
      
    
    
    return	DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_ValidateDiamUnsigned64 ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void*                        pData_i )
{
    
    t_DiamUnsigned64*       poTempDiamUnsigned64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamUnsigned64 =    (t_DiamUnsigned64*) pData_i;
      
    
    
    return(DMBase_Retval_Success);
}



t_DiamAPIReturnVal DMBase_ValidateDiamIdent ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											  void*                         pData_i )
{
    
              
    t_DiameterIdentity*     poTempDiameterIdentity = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData-i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiameterIdentity =    (t_DiameterIdentity*) pData_i;
    
    
    return	DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ValidateDiamTime ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											 void*                      pData_i )
{
    
    t_DiamTime*      poTempDiamTime = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamTime =    ( t_DiamTime*) pData_i;
    
    return	DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ValidateDiamIPAddress ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												  void*                         pData_i )
{
    t_DiamIPAddress*     poTempDiamIPAddress = NULL;
    
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
        
    poTempDiamIPAddress =    ( t_DiamIPAddress*) pData_i;
    
    
    return	DMBase_Retval_Success	;
}



t_DiamAPIReturnVal DMBase_ValidateDiamURI ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											void*                       pData_i )
{
    
    t_DiameterURI*       poTempDiameterURI = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
        
    poTempDiameterURI =    ( t_DiameterURI*) pData_i;
      
    
    
    return	DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_ValidateDiamInteger32 (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												  void*                         pData_i )
{
    
    int                    unAVPData=0;               
    t_DiamInteger32*       poTempDiamInteger32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL == pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamInteger32  =    ( t_DiamInteger32*) pData_i;
      
    unAVPData = * (poTempDiamInteger32->pnInteger32); 
    
    
    return	DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ValidateDiamInteger64 (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												  void*                         pData_i )
{
    
    t_DiamInteger64*       poTempDiamInteger64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL == pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamInteger64  =    ( t_DiamInteger64*) pData_i;
    
    return	DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ValidateDiamFloat32 (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, void*                       pData_i )
{
    
    float              flAVPData;               
    t_DiamFloat32*     poTempDiamFloat32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL == pData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
        
    poTempDiamFloat32  =    ( t_DiamFloat32*) pData_i;
      
    flAVPData = *(poTempDiamFloat32->pflFloat32); 
    
    return	DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_ValidateDiamFloat64 (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											   void*                       pData_i )
{
    
    double				dAVPData = 0;               
    t_DiamFloat64*		poTempDiamFloat64= NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter pData_i is passed\n");
        return DMBase_Retval_Null_Pointer;
    }
        
    poTempDiamFloat64  =    ( t_DiamFloat64*) pData_i;
      
    dAVPData = *(poTempDiamFloat64->pdFloat64); 
    
    return	DMBase_Retval_Success;
}

/************************************************************************************
** Function Name:                                                                   * 
**		  DMBase_AVPAllocDiamOctetString                                    *
**                                                                                  *
** Parameters:                                                                      *
**		 HDIAMETERSTACKCONTEXT     hDiameterStackContext_io,                 *
                      type: input                                                   *
**		      detail : this is a C style NULL terminated char array whose   *
**				    length is to be calculated                      *
**                                                                                  *
**		void*     pData_o                                                   *
**		      type: Output                                                  *
**		      detail: This is a flag indicating whether logging should      *
**			      be done inside this function or not                   *
**                                                                                  *
**              int     nSize_i                                                     *
**                    type: input                                                   *
**		      detail: This is a flag indicating whether logging should      *
**			      be done inside this function or not                   *
** Return:                                                                          *
**		                                                                    *
**                                                                                  *
*************************************************************************************
** Created By: 		: Simab Shahid                                              *
*************************************************************************************
*************************************************************************************/

t_DiamAPIReturnVal  DMBase_AVPAllocDiamOctetString( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													void**                       ppData_o,
                                                    unsigned int                unSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    
    t_DiamOctetString*		poTempDiamOctetString= NULL;
	unsigned	int			unPadLen = 0;
	unsigned	int			unActualAllocLen = 0;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is NOT NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }


	if ( 0 == (unSize_i % DMBASE_NUM_OF_OCTETS_IN_32BIT) ) 
	{
		unPadLen = 0;
	}
	else
	{
        unPadLen = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unSize_i % DMBASE_NUM_OF_OCTETS_IN_32BIT);
	}

	unActualAllocLen = unSize_i + unPadLen;

	//first alloc mem for the container


	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io, 
									hMsgAllocCtxt_io,
								    sizeof ( t_DiamOctetString ),
								   (void* )&poTempDiamOctetString)
	    )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc failed , leaving\n");
		oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//now alloc memory for the data 
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io ,
												hMsgAllocCtxt_io,
												unActualAllocLen,
				  (void*) &(poTempDiamOctetString->pucOctetString))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc failed , leaving\n");
		oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}
	

	//As per RFC , padding length will not be reflected in AVP data len
	poTempDiamOctetString->unNumOfOctets = unSize_i;

	

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamOctetString) 
		{
			if (NULL != poTempDiamOctetString->pucOctetString) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamOctetString->pucOctetString));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamOctetString));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamOctetString;
	}
    
    return	oRetval;
}


t_DiamAPIReturnVal DMBase_AVPAllocDiamInteger32(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												 void**                      ppData_o,
                                                 unsigned int                unSize_i,
												HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
                                                    
    t_DiamInteger32*        poTempDiamInteger32 = NULL;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;
    
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL == ppData_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppData_o))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is NOT NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	

	if( sizeof (int ) != unSize_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Value of unSize_i \n");
        return DMBase_Retval_IncorrectParameters;
    }

	//allocate memory for container
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
												hMsgAllocCtxt_io,
												sizeof( t_DiamInteger32),
												(void*) & poTempDiamInteger32) 
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed ,Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
    }

	//allocate mem for data
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													unSize_i,
				  (void*) & poTempDiamInteger32->pnInteger32)
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed ,Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
    }

	

	poTempDiamInteger32->unNumOfOctets = unSize_i;

	

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamInteger32) 
		{
			if (NULL != poTempDiamInteger32->pnInteger32) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger32->pnInteger32));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io ,(void**) (&poTempDiamInteger32));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamInteger32;
	}
    
    return	oRetval;
}



     
t_DiamAPIReturnVal DMBase_AVPAllocDiamInteger64( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												 void**                   ppData_o,
                                                 unsigned int             unSize_i,
												 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
                                                     
    t_DiamInteger64*        poTempDiamInteger64 = NULL;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is NOT NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if ( DMBASE_NUM_OF_OCTETS_IN_INT64 != unSize_i ) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Value of unSize_i \n");
        return DMBase_Retval_IncorrectParameters;
	}

	//allocate memory for container
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc (hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof ( t_DiamInteger64),
													(void*) &poTempDiamInteger64)
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//allocate memory for data
	if (DMBase_Retval_Success != DMBase_AVP_Malloc (hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													unSize_i,
				   (void*) &poTempDiamInteger64->pllInteger64)
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}



	poTempDiamInteger64->unNumOfOctets = unSize_i;
	
    
	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamInteger64) 
		{
			if (NULL != poTempDiamInteger64->pllInteger64) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger64->pllInteger64));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger64));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamInteger64;
	}
    
    return	oRetval;
}

    
t_DiamAPIReturnVal DMBase_AVPAllocDiamUnsigned32(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												  void**                   ppData_o,
                                                  unsigned int             unSize_i,
												 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
         
    t_DiamUnsigned32*		poTempDiamUnsigned32 = NULL;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if ( sizeof ( unsigned int )  != unSize_i ) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Value of unSize_i \n");
        return DMBase_Retval_IncorrectParameters;
	}

	//allocate mem for container
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													sizeof( t_DiamUnsigned32),
													(void*) &poTempDiamUnsigned32) 
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//allocate mem for data
	if (DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
												   hMsgAllocCtxt_io,
												   unSize_i,
				  (void*) &(poTempDiamUnsigned32->punUnsigned32))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}


	

	poTempDiamUnsigned32->unNumOfOctets = unSize_i;
     
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamUnsigned32) 
		{
			if (NULL != poTempDiamUnsigned32->punUnsigned32) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned32->punUnsigned32));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned32));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamUnsigned32;
	}
    
    return	oRetval;
}


t_DiamAPIReturnVal DMBase_AVPAllocDiamUnsigned64( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												  void**                      ppData_o,
                                                  unsigned int                unSize_i,
												  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{   
    t_DiamUnsigned64*		poTempDiamUnsigned64 = NULL;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is Not Null,leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if ( DMBASE_NUM_OF_OCTETS_IN_UINT64  != unSize_i ) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Value of unSize_i \n");
        return DMBase_Retval_IncorrectParameters;
	}

	//allocate mem for container
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													sizeof ( t_DiamUnsigned64),
				  (void*) &poTempDiamUnsigned64)
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//allocate mem for data
	if (DMBase_Retval_Success !=   DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 unSize_i,
				  (void*) &( poTempDiamUnsigned64->pullUnsigned64))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	

	poTempDiamUnsigned64->unNumOfOctets = unSize_i;
    
   ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamUnsigned64) 
		{
			if (NULL != poTempDiamUnsigned64->pullUnsigned64) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned64->pullUnsigned64));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned64));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamUnsigned64;
	}
    
    return	oRetval;
}

 
t_DiamAPIReturnVal DMBase_AVPAllocDiamFloat32( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											   void**                      ppData_o,
                                               unsigned int                unSize_i,
											   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{ 
    t_DiamFloat32*			poTempDiamFloat32 = NULL;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is not NULL , leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if ( sizeof (float)  != unSize_i ) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Value of unSize_i \n");
        return DMBase_Retval_IncorrectParameters;
	}

	//allocate memory for container
	if ( DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof ( t_DiamFloat32),
				  (void*) &poTempDiamFloat32)
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//allocate memory for data
	if ( DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 unSize_i,
				  (void*) &(poTempDiamFloat32->pflFloat32))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	

	poTempDiamFloat32->unNumOfOctets = unSize_i;
     
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamFloat32) 
		{
			if (NULL != poTempDiamFloat32->pflFloat32) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat32->pflFloat32));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat32));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamFloat32;
	}
    
    return	oRetval;
    
}
     
t_DiamAPIReturnVal DMBase_AVPAllocDiamFloat64(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
											  void**                   ppData_o,
                                             unsigned int              unSize_i,
											  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{ 
    t_DiamFloat64*			poTempDiamFloat64 = NULL;
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is Not Null , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if ( sizeof (double)  != unSize_i ) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid Value of unSize_i \n");
        return DMBase_Retval_IncorrectParameters;
	}

	//allocate memory for container
	if ( DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													sizeof ( t_DiamFloat64), 
				  (void*) &poTempDiamFloat64)
		 )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//allocate memory for data
	if ( DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													unSize_i,
				  (void*) &(poTempDiamFloat64->pdFloat64))
		 )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}
	

	poTempDiamFloat64->unNumOfOctets = unSize_i;
     
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamFloat64) 
		{
			if (NULL != poTempDiamFloat64->pdFloat64) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat64->pdFloat64));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat64));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamFloat64;
	}
    
    return	oRetval;
}
     
     
     
     
t_DiamAPIReturnVal DMBase_AVPAllocDiamIPAddress(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												void**                      ppData_o,
                                                unsigned int                unSize_i,
												HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    
    t_DiamIPAddress*		poTempDiamIPAddr= NULL;
	
	t_DiamAPIReturnVal		oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL parameter ppData_o is passed\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*ppData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " (*ppData_o) is NOT NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	//first alloc mem for the container


	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io, 
									hMsgAllocCtxt_io,
								    sizeof ( t_DiamIPAddress ),
								   (void* )&poTempDiamIPAddr)
	    )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc failed , leaving\n");
		oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//now alloc memory for the data 
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io ,
												hMsgAllocCtxt_io,
												sizeof(t_IPAddr),
				  (void*) &(poTempDiamIPAddr->poIPAddr))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc failed , leaving\n");
		oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}
	

	
	poTempDiamIPAddr->unNumOfOctets = sizeof(t_IPAddr);

	

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamIPAddr) 
		{
			if (NULL != poTempDiamIPAddr->poIPAddr) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamIPAddr->poIPAddr));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamIPAddr));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppData_o = poTempDiamIPAddr;
	}
    
    return	oRetval;
}

// for Time unsigned32 allocator will be used

// UTF8String Allocator function of OctetString will be used


/************************************************************************************
** Function Name:                                                                   * 
**		  DMBase_AVPDeAllocDiamOctetString                                  *
**                                                                                  *
** Parameters:                                                                      *
**		 HDIAMETERSTACKCONTEXT     hDiameterStackContext_io,                 *
                      type: input                                                   *
**		      detail : this is a C style NULL terminated char array whose   *
**				    length is to be calculated                      *
**                                                                                  *
**		void*     pData_i                                                   *
**		      type: Input                                                   *
**		      detail: This is a flag indicating whether logging should      *
**			      be done inside this function or not                   *    
** Return:                                                                          *
**		                                                                    *
**                                                                                  *
*************************************************************************************
** Created By: 		: Simab Shahid                                              *
*************************************************************************************
*************************************************************************************/

t_DiamAPIReturnVal  DMBase_AVPDeAllocDiamOctetString(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													  void **                   ppData_o,
													 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{                                                   
    
    t_DiamOctetString*        poTempDiamOctetString = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamOctetString = (t_DiamOctetString*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamOctetString->pucOctetString));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamOctetString));
    
    return	DMBase_Retval_Success;  
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamInteger32(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void **                     ppData_o,
												  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamInteger32*        poTempDiamInteger32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamInteger32 = (t_DiamInteger32*) *ppData_o;

	
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamInteger32->pnInteger32));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamInteger32));
	
    
    return	DMBase_Retval_Success	;
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamInteger64(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void **                   ppData_o,
												  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamInteger64*        poTempDiamInteger64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamInteger64 = (t_DiamInteger64*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamInteger64->pllInteger64));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamInteger64));
    
    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamUnsigned32(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												    void **                 ppData_o,
												   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamUnsigned32*        poTempDiamUnsigned32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamUnsigned32	= (t_DiamUnsigned32*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamUnsigned32->punUnsigned32));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamUnsigned32));
    
    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamUnsigned64(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												    void **                  ppData_o,
												   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
                                                        
    t_DiamUnsigned64*        poTempDiamUnsigned64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamUnsigned64 = (t_DiamUnsigned64*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamUnsigned64->pullUnsigned64));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamUnsigned64));
    
    return	DMBase_Retval_Success	;
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamFloat32( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												 void **                 ppData_o,
												 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamFloat32*        poTempDiamFloat32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamFloat32 = ( t_DiamFloat32*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamFloat32->pflFloat32));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamFloat32));
    
    return	DMBase_Retval_Success ;
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamFloat64( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												 void **                 ppData_o,
												 HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamFloat64*        poTempDiamFloat64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamFloat64 = (t_DiamFloat64*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamFloat64->pdFloat64));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamFloat64));

    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_AVPDeAllocDiamIPAddress( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void **                  ppData_o,
												   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
	t_DiamIPAddress*		poTempDiamIPAddr= NULL;
                                                       
    if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == *ppData_o) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " *ppData_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	poTempDiamIPAddr = (t_DiamIPAddress*) *ppData_o;

	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamIPAddr->poIPAddr));
	DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**)(&poTempDiamIPAddr));


    return DMBase_Retval_Success;
}

 
// for Time unsigned32  DeAllocator will be used

// UTF8String DeAllocator function of OctetString will be used

/************************************************************************************
** Function Name:                                                                   * 
**		  DMBase_GetDiamOctetStringRawData                                  *
**                                                                                  *
** Parameters:                                                                      *
**		 HDIAMETERSTACKCONTEXT     hDiameterStackContext_io,                 *
                      type: input                                                   *
**		      detail : this is a C style NULL terminated char array whose   *
**				    length is to be calculated                      *
**                                                                                  *
**		void*     pRawData_o                                                *
**		      type: Output                                                  *
**		      detail: This is a flag indicating whether logging should      *
**			      be done inside this function or not                   *
**                                                                                  *
**              void    pStructData_i                                               *
**                    type: input                                                   *
**		      detail: This is a flag indicating whether logging should      *
**			      be done inside this function or not                   *
** Return:                                                                          *
**		                                                                    *
**                                                                                  *
*************************************************************************************
** Created By: 		: Simab Shahid                                              *
*************************************************************************************
*************************************************************************************/
t_DiamAPIReturnVal DMBase_GetDiamOctetStringRawData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													 void*                        pRawData_o, 
                                                     void*                        pStructData_i,
													 unsigned int				   unSizeOfRawBuff_i)
{
    
    t_DiamOctetString*		poTempDiamOctetString = NULL;
	unsigned int			unActualRawDataLen = 0;
	unsigned int			unPadLen = 0;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
            
    poTempDiamOctetString =  (t_DiamOctetString*) pStructData_i;


	if ( 0 == (unSizeOfRawBuff_i % DMBASE_NUM_OF_OCTETS_IN_32BIT) ) 
	{
		unPadLen = 0;
	}
	else
	{
        unPadLen = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unSizeOfRawBuff_i % DMBASE_NUM_OF_OCTETS_IN_32BIT);
	}

	if (NULL == poTempDiamOctetString->pucOctetString) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamOctetString->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}

	unActualRawDataLen = unSizeOfRawBuff_i + unPadLen;

	
	memcpy( pRawData_o, (void *) poTempDiamOctetString->pucOctetString,
                                        unActualRawDataLen ); 

    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_GetDiamUnsigned32RawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													void*                        pRawData_o, 
                                                    void*                        pStructData_i,
													unsigned int				   unSizeOfRawBuff_i)
{
    t_DiamUnsigned32*   poTempDiamUnsigned32 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamUnsigned32 =  (t_DiamUnsigned32*) pStructData_i;
      
	if (NULL == poTempDiamUnsigned32->punUnsigned32) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamUnsigned32->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}

	memcpy( pRawData_o, (void *) poTempDiamUnsigned32->punUnsigned32,
                           poTempDiamUnsigned32->unNumOfOctets); 

	//converting to network byte order

	unsigned int	unTempInt = 0;
	unTempInt	= * (unsigned int*) pRawData_o;

	if ( DMBase_Retval_Success != DMBase_HostToNetworkLong(hDiameterStackContext_io,
									unTempInt,(unsigned long *) pRawData_o)
		 )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_HostToNetworkLong Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

	//* (unsigned int* )pRawData_o = htonl ( *(unsigned int * )pRawData_o );

      
    return	DMBase_Retval_Success;     
}

t_DiamAPIReturnVal DMBase_GetDiamUnsigned64RawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													void*                        pRawData_o, 
                                                    void*                        pStructData_i,
													unsigned int				   unSizeOfRawBuff_i)
{
     void*               pMemCpyReturn        = NULL;
     t_DiamUnsigned64*   poTempDiamUnsigned64 = NULL;

	 if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamUnsigned64 =  (t_DiamUnsigned64*) pStructData_i;

	if (NULL == poTempDiamUnsigned64->pullUnsigned64) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamUnsigned64->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}
      
    memcpy( pRawData_o, (void *) poTempDiamUnsigned64->pullUnsigned64,
                           poTempDiamUnsigned64->unNumOfOctets); 

	unsigned long long	ullTemp = *(unsigned long long *) pRawData_o;

	//convert to network order

	if ( DMBase_Retval_Success != DMBase_HostToNetworkLongLong(hDiameterStackContext_io,ullTemp,
								 (unsigned long long *) pRawData_o)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_HostToNetworkLongLong Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}

           
    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_GetDiamIPAddressRawData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void*                        pRawData_o, 
                                                   void*                        pStructData_i,
												   unsigned int				   unSizeOfRawBuff_i)
{
    t_DiamIPAddress*	poTempDiamIPAddress = NULL;
	unsigned char		pucTempData[DMBASE_IP_ADDRTYPE_SIZE_IN_OCTETS + DMBASE_IPV6_ADDR_SIZE_IN_OCTETS] = {0};
    unsigned int		unReqBuffSize=0;
	struct sockaddr_in	sa={0}; // IPv4
	struct sockaddr_in6	sa6={0}; // IPv6

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	poTempDiamIPAddress  =  ( t_DiamIPAddress*) pStructData_i;

	if (NULL == poTempDiamIPAddress->poIPAddr) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL  pointer,  Error \n");
		return DMBase_Retval_Null_Pointer;
	}

	//check Buffer size issues
	if ( DMBASE_IANA_ADDR_FAMILY_IP_V4 == poTempDiamIPAddress->poIPAddr->usIPVersion) 
	{
		unReqBuffSize = DMBASE_IP_ADDRTYPE_SIZE_IN_OCTETS + DMBASE_IPV4_ADDR_SIZE_IN_OCTETS;
	}
	else if (DMBASE_IANA_ADDR_FAMILY_IP_V6 == poTempDiamIPAddress->poIPAddr->usIPVersion) 
	{
		unReqBuffSize = DMBASE_IP_ADDRTYPE_SIZE_IN_OCTETS + DMBASE_IPV6_ADDR_SIZE_IN_OCTETS;
	}
	else
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Invalid value of usIPVersion = %d,  Error \n",poTempDiamIPAddress->poIPAddr->usIPVersion);
		return DMBase_Retval_InvalidAVPData;
	}

	
	if (unSizeOfRawBuff_i < unReqBuffSize )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer unSizeOfRawBuff_i == %d , unReqBuffSize = %d ,  Error \n",unSizeOfRawBuff_i,unReqBuffSize);
		return DMBase_Retval_Insufficient_Buffer;
	}

	//copy into raw data by conversion through socket APIs

	if ( DMBase_Retval_Success != DMBase_HostToNetworkShort(hDiameterStackContext_io,
			(unsigned short ) poTempDiamIPAddress->poIPAddr->usIPVersion,(unsigned short*) pRawData_o)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_HostToNetworkShort failed , leaving ");
		return DMBase_Retval_Failure;
	}

	
    
	if ( DMBASE_IANA_ADDR_FAMILY_IP_V4 == poTempDiamIPAddress->poIPAddr->usIPVersion) 
	{
		inet_pton(AF_INET, poTempDiamIPAddress->poIPAddr->pucIPString, &(sa.sin_addr));

		if ( DMBase_Retval_Success != DMBase_HostToNetworkLong(hDiameterStackContext_io,(unsigned long)sa.sin_addr.s_addr,
					(unsigned long*) (pRawData_o+ sizeof(unsigned short) ))
			 )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_HostToNetworkLong failed , leaving ");
			return DMBase_Retval_Failure;
		}



	}
	else if (DMBASE_IANA_ADDR_FAMILY_IP_V6 == poTempDiamIPAddress->poIPAddr->usIPVersion) 
	{
		inet_pton(AF_INET6, poTempDiamIPAddress->poIPAddr->pucIPString, &(sa6.sin6_addr)); // IPv6
		memcpy(pRawData_o+sizeof(unsigned short),&(sa6.sin6_addr.in6_u.u6_addr16),16);
	}

    
    
    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_GetDiamInteger32RawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void*                        pRawData_o, 
                                                   void*                        pStructData_i,
												   unsigned int				   unSizeOfRawBuff_i)
{
     
    t_DiamInteger32*   poTempDiamInteger32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamInteger32  =  ( t_DiamInteger32*) pStructData_i;

	if (NULL == poTempDiamInteger32->pnInteger32) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamInteger32->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}
      
    memcpy( pRawData_o, (void *) poTempDiamInteger32->pnInteger32,
                           poTempDiamInteger32->unNumOfOctets);

	//converting to network byte order
	unsigned int	unTempInt = 0;
	unTempInt	= * (unsigned int*) pRawData_o;

	if ( DMBase_Retval_Success != DMBase_HostToNetworkLong(hDiameterStackContext_io,
									unTempInt,(unsigned long *) pRawData_o)
		 )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_HostToNetworkLong Failed , Leaving \n");
		return DMBase_Retval_Failure;
	}


	//* (unsigned int* )pRawData_o = htonl ( *(unsigned int * )pRawData_o );
   
    
    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_GetDiamInteger64RawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												   void*                        pRawData_o, 
                                                   void*                        pStructData_i,
												   unsigned int				   unSizeOfRawBuff_i)
{
    t_DiamInteger64*   poTempDiamInteger64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    poTempDiamInteger64  =  ( t_DiamInteger64*) pStructData_i;

	if (NULL == poTempDiamInteger64->pllInteger64) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamInteger64->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}
      
    memcpy( pRawData_o, (void *) poTempDiamInteger64->pllInteger64,
                           poTempDiamInteger64->unNumOfOctets); 

	unsigned long long	ullTemp = *(unsigned long long *) pRawData_o;

	//convert to network order

	if ( DMBase_Retval_Success != DMBase_HostToNetworkLongLong(hDiameterStackContext_io,ullTemp,
								 (unsigned long long *) pRawData_o)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_HostToNetworkLongLong Failed , Leaving \n");
        return DMBase_Retval_Failure;
	}
  
    
    return	DMBase_Retval_Success ;
}


t_DiamAPIReturnVal DMBase_GetDiamFloat32RawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												 void*                        pRawData_o, 
                                                 void*                        pStructData_i,
												 unsigned int				   unSizeOfRawBuff_i)
{
    void*              pMemCpyReturn     = NULL;           
    t_DiamFloat32*     poTempDiamFloat32 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
        
    poTempDiamFloat32  =  ( t_DiamFloat32*) pStructData_i;

	if (NULL == poTempDiamFloat32->pflFloat32) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamFloat32->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}
      
   memcpy( pRawData_o, (void *) poTempDiamFloat32->pflFloat32,
                           poTempDiamFloat32->unNumOfOctets); 
    
    return	DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_GetDiamFloat64RawData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
												 void*                        pRawData_o, 
                                                 void*                        pStructData_i,
												 unsigned int				  unSizeOfRawBuff_i)
{
    void*              pMemCpyReturn     = NULL;
    t_DiamFloat64*     poTempDiamFloat64 = NULL;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == pRawData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_o is  NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(  NULL == pStructData_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pStructData_i is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
        
    poTempDiamFloat64  =  ( t_DiamFloat64*) pRawData_o;

	if (NULL == poTempDiamFloat64->pdFloat64) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "NULL pointer,  Error \n");
        return DMBase_Retval_Null_Pointer;
	}

	if (unSizeOfRawBuff_i < (poTempDiamFloat64->unNumOfOctets) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Insufficient Buffer ,  Error \n");
        return DMBase_Retval_Insufficient_Buffer;
	}
      
    memcpy( pRawData_o, (void *) poTempDiamFloat64->pdFloat64,
                           poTempDiamFloat64->unNumOfOctets); 

    
    return	DMBase_Retval_Success;
}

/************************************************************************************
** Function Name:                                                                   * 
**		  DMBase_GetDiamOctetStringStructData                                       *
**                                                                                  *
** Parameters:                                                                      *
**		 HDIAMETERSTACKCONTEXT     hDiameterStackContext_io,                         *       
                      type: input                                                   *
**		      detail : this is a C style NULL terminated char array whose           *
**				    length is to be calculated                                      *
**                                                                                  *
**		void*     pRawData_o                                                        *
**		      type: Output                                                          *
**		      detail: This is a flag indicating whether logging should              *
**			      be done inside this function or not                               *
**                                                                                  *
**              void    pStructData_i                                               *
**                    type: input                                                   *
**		      detail: This is a flag indicating whether logging should              *
**			      be done inside this function or not                               *
** Return:                                                                          *
**		                                                                            *
**                                                                                  *
*************************************************************************************
** Created By: 		: Simab Shahid                                                  *
*************************************************************************************
*************************************************************************************/
t_DiamAPIReturnVal	DMBase_DumpDiamOctetStringStructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
														 void*                        pStructData_i, 
                            unsigned int unDataSize_i, FILE* pfFilePtr_i)
{
	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	t_DiamOctetString*	pTempDiamOctStr = NULL;

	pTempDiamOctStr = (t_DiamOctetString*) pStructData_i;

	if (NULL == pTempDiamOctStr->pucOctetString) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamOctStr->pucOctetString is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned int	unCurrInd = 0;

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of OctetString Type \n Data = \t\t");
	

	for (unCurrInd=0; unCurrInd <= (pTempDiamOctStr->unNumOfOctets) ; unCurrInd++ ) 
	{
		DMBase_Debug_console_and_fprintf(pfFilePtr_i,"%c",pTempDiamOctStr->pucOctetString[unCurrInd]);
	}

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamInteger32StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
														void*                        pStructData_i, 
														unsigned int unDataSize_i , FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamInteger32*	pTempDiamInt32 = NULL;
	pTempDiamInt32 = (t_DiamInteger32*) pStructData_i;

	if (NULL == pTempDiamInt32->pnInteger32) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamInt32->pnInteger32 is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of Integer32 Type \n Data = \t\t %d",*(pTempDiamInt32->pnInteger32));

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamInteger64StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													    void*                        pStructData_i, 
													unsigned int unDataSize_i , FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamInteger64*	pTempDiamInt64 = NULL;
	pTempDiamInt64 = (t_DiamInteger64*) pStructData_i;

	if (NULL == pTempDiamInt64->pllInteger64) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamInt64->pllInteger64 is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of Integer64 Type \n Data = \t\t %lld",*(pTempDiamInt64->pllInteger64));

	return DMBase_Retval_Success;

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamUnsigned32StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
														 void*                        pStructData_i, 
														unsigned int unDataSize_i , FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamUnsigned32*	pTempDiamUnInt32 = NULL;
	pTempDiamUnInt32 = (t_DiamUnsigned32*) pStructData_i;

	if (NULL == pTempDiamUnInt32->punUnsigned32) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamInt32->punUnsigned32 is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of Unsigned Integer32 Type \n Data = \t\t %u",*(pTempDiamUnInt32->punUnsigned32));


	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamUnsigned64StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
														 void*                        pStructData_i, 
														unsigned int unDataSize_i , FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamUnsigned64*	pTempDiamUnsigned64 = NULL;
	pTempDiamUnsigned64 = (t_DiamUnsigned64*) pStructData_i;

	if (NULL == pTempDiamUnsigned64->pullUnsigned64) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamUnsigned64->pullUnsigned64 is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of Integer64 Type \n Data = \t\t %llu",*(pTempDiamUnsigned64->pullUnsigned64));


	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamFloat32StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													  void*                        pStructData_i, 
													 unsigned int unDataSize_i , FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamFloat32*	pTempDiamFloat32 = NULL;
	pTempDiamFloat32 = (t_DiamFloat32*) pStructData_i;

	if ( NULL == pTempDiamFloat32->pflFloat32 ) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamFloat32->pflFloat32 is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of Float32 Type \n Data = \t\t %f",*(pTempDiamFloat32->pflFloat32));

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamFloat64StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													  void*                        pStructData_i, 
													 unsigned int unDataSize_i, FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamFloat64*	pTempDiamFloat64 = NULL;
	pTempDiamFloat64 = (t_DiamFloat64*) pStructData_i;

	if (NULL == pTempDiamFloat64->pdFloat64) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pTempDiamFloat64->pdFloat64 is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	DMBase_Debug_console_and_fprintf(pfFilePtr_i,"\n Dumping AVP Data of Float64 Type \n Data = \t\t %lf",*(pTempDiamFloat64->pdFloat64));

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DumpDiamIPAddressStructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													    void*                        pStructData_i, 
													   unsigned int unDataSize_i , FILE* pfFilePtr_i)
{
	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pStructData_i) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter pStructData_i is NULL \n");
        return DMBase_Retval_Null_Pointer;
	}

	return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_GetDiamOctetStringStructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													    void*                        pRawData_i, 
                                                        void**                        ppStructData_o,
                                                        unsigned int                 unRawBuffSize_i,
													   HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
	
    t_DiamOctetString*	poTempDiamOctetString = NULL;
	unsigned int		unPadLen = 0;
	unsigned int		unActualAllocLen = 0;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }


	if ( 0 == (unRawBuffSize_i % DMBASE_NUM_OF_OCTETS_IN_32BIT) ) 
	{
		unPadLen = 0;
	}
	else
	{
        unPadLen = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unRawBuffSize_i % DMBASE_NUM_OF_OCTETS_IN_32BIT);
	}

	unActualAllocLen = unRawBuffSize_i + unPadLen;

	//allocate memory for container
	if ( DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													sizeof(t_DiamOctetString),
				  (void*) &poTempDiamOctetString )
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed, Leaving\n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
    }

	//allocate memory for actual data 
	if ( DMBase_Retval_Success != DMBase_AVP_Malloc(hDiameterStackContext_io,
													hMsgAllocCtxt_io,
													unActualAllocLen,
				  (void*) &(poTempDiamOctetString->pucOctetString))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed, Leaving\n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
    }
	

	//fill the container by copying data

	//as per RFC , padding is not reflected in AVP data size
	poTempDiamOctetString->unNumOfOctets = unRawBuffSize_i;

	memcpy(poTempDiamOctetString->pucOctetString,
		   pRawData_i, unActualAllocLen);

	

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamOctetString) 
		{
			if (NULL != poTempDiamOctetString->pucOctetString) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamOctetString->pucOctetString));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamOctetString));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o = poTempDiamOctetString;
	}

       
    return oRetval;
}

t_DiamAPIReturnVal DMBase_GetDiamUnsigned32StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													   void*                        pRawData_i, 
                                                       void**                       ppStructData_o,
                                                       unsigned int                 nSize_i,
													  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    void*               pMemCpyReturn        = NULL;
    t_DiamUnsigned32*   poTempDiamUnsigned32 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }
    

	if ( sizeof (unsigned int ) != nSize_i) 
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter nSize_i is invalid \n");
        return DMBase_Retval_IncorrectParameters;
    } 

	//allocate memory for the structured data container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof (t_DiamUnsigned32),
				   (void* ) &poTempDiamUnsigned32)
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

	 //allocate memory for the actual data inside container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 nSize_i,
				   (void*) &( poTempDiamUnsigned32->punUnsigned32))
		 )
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

   	//update size field inside the container
	 poTempDiamUnsigned32->unNumOfOctets = nSize_i;

	 //copy the Raw data inside the container
	  memcpy( poTempDiamUnsigned32->punUnsigned32,
			  pRawData_i ,
			 nSize_i );

	  unsigned int	unTemp = *( poTempDiamUnsigned32->punUnsigned32);
	  //unTemp = ntohl(unTemp);

	  //*( poTempDiamUnsigned32->punUnsigned32) = unTemp;

	  if (DMBase_Retval_Success !=   DMBase_NetworkToHostLong(hDiameterStackContext_io,
				unTemp,(unsigned long*) poTempDiamUnsigned32->punUnsigned32)
		  )
	  {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_NetworkToHostLong Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

      
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamUnsigned32) 
		{
			if (NULL != poTempDiamUnsigned32->punUnsigned32) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned32->punUnsigned32));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned32));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o  = poTempDiamUnsigned32;
	}

       
    return oRetval;   
}

t_DiamAPIReturnVal DMBase_GetDiamUnsigned64StructData(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													   void*                        pRawData_i, 
                                                       void**                       ppStructData_o,
                                                       unsigned int                 nSize_i,
													  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamUnsigned64*   poTempDiamUnsigned64 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }
           
    if ( sizeof (unsigned long long ) != nSize_i) 
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter nSize_i is invalid \n");
        return DMBase_Retval_IncorrectParameters;
    } 

	//allocate memory for the structured data container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof (t_DiamUnsigned64),
				   (void* ) &poTempDiamUnsigned64)
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

	 //allocate memory for the actual data inside container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 nSize_i,
				   (void*) &( poTempDiamUnsigned64->pullUnsigned64))
		 )
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

   	//update size field inside the container
	 poTempDiamUnsigned64->unNumOfOctets = nSize_i;

	 //copy the Raw data inside the container
	  memcpy( poTempDiamUnsigned64->pullUnsigned64,
			  pRawData_i ,
			 nSize_i );

	  unsigned long long	ullTemp = *( poTempDiamUnsigned64->pullUnsigned64);
	  

	  if (DMBase_Retval_Success !=   DMBase_NetworkToHostLongLong(hDiameterStackContext_io,
				ullTemp,(unsigned long long*) poTempDiamUnsigned64->pullUnsigned64)
		  )
	  {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_NetworkToHostLongLong Failed , Leaving \n");
        oRetval = DMBase_Retval_Failure;
		goto ExitMe;
      }

      
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamUnsigned64) 
		{
			if (NULL != poTempDiamUnsigned64->pullUnsigned64) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned64->pullUnsigned64));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamUnsigned64));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o  = poTempDiamUnsigned64;
	}

       
    return oRetval;  
}

t_DiamAPIReturnVal DMBase_GetDiamIPAddressStructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													  void*                        pRawData_i, 
                                                      void**                       ppStructData_o,
                                                      unsigned int                 nSize_i,
													  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    t_DiamIPAddress*	poTempDiamIPAddr = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;
	unsigned short		usIPVer = 0;
    struct sockaddr_in	sa = {0};
	struct sockaddr_in6 sa6={0};   
							

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	//allocate memory for container
    
    if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io, 
									hMsgAllocCtxt_io,
								    sizeof ( t_DiamIPAddress ),
								   (void* )&poTempDiamIPAddr)
	    )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc failed , leaving\n");
		oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	//now alloc memory for the data 
	if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io ,
												hMsgAllocCtxt_io,
												sizeof(t_IPAddr),
				  (void*) &(poTempDiamIPAddr->poIPAddr))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_AVP_Malloc failed , leaving\n");
		oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}
	

	
	poTempDiamIPAddr->unNumOfOctets = sizeof(t_IPAddr);
	

	
	//fill the container by manipulating data

	usIPVer = *(unsigned short*) pRawData_i;
	if ( DMBase_Retval_Success !=  DMBase_NetworkToHostShort(hDiameterStackContext_io,
					usIPVer,
					(unsigned short*)(&poTempDiamIPAddr->poIPAddr->usIPVersion))
		)
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostShort failed , leaving\n");
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	if (DMBASE_IANA_ADDR_FAMILY_IP_V4 == poTempDiamIPAddr->poIPAddr->usIPVersion) 
	{
		if ( DMBase_Retval_Success !=  DMBase_NetworkToHostLong(hDiameterStackContext_io,
				*(unsigned long*)(pRawData_i+sizeof(unsigned short) ) ,(unsigned long*) &sa.sin_addr.s_addr)
		    )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_NetworkToHostLong failed , leaving\n");
			oRetval = DMBase_Retval_Failure;
			goto ExitMe;
		}


		inet_ntop(AF_INET, &(sa.sin_addr), poTempDiamIPAddr->poIPAddr->pucIPString, DMBASE_MAX_IP_STRING_SIZE);
	}
	else if (DMBASE_IANA_ADDR_FAMILY_IP_V6 == poTempDiamIPAddr->poIPAddr->usIPVersion) 
	{
		inet_ntop(AF_INET6, &(sa6.sin6_addr), poTempDiamIPAddr->poIPAddr->pucIPString, DMBASE_MAX_IP_STRING_SIZE);
	}
	else
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Invalid value of poTempDiamIPAddr->poIPAddr->usIPVersion ==%d \n",poTempDiamIPAddr->poIPAddr->usIPVersion);
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}



	

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamIPAddr) 
		{
			if (NULL != poTempDiamIPAddr->poIPAddr) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamIPAddr->poIPAddr));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamIPAddr));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o = poTempDiamIPAddr;
	}
       
    return oRetval;
}

t_DiamAPIReturnVal DMBase_GetDiamInteger32StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													  void*                        pRawData_i, 
                                                      void**                       ppStructData_o,
                                                      unsigned int                 nSize_i,
													  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
     
    t_DiamInteger32*   poTempDiamInteger32 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	

	if ( sizeof ( int ) != nSize_i) 
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter nSize_i is invalid \n");
        return DMBase_Retval_IncorrectParameters;
    } 

	//allocate memory for the structured data container
	 if ( DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													  hMsgAllocCtxt_io,
													  sizeof (t_DiamInteger32),
				   (void* ) &poTempDiamInteger32)
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
      }

	 //allocate memory for the actual data inside container
	 if ( DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													  hMsgAllocCtxt_io,
													  nSize_i,
				   (void*) &( poTempDiamInteger32->pnInteger32))
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
      }

   	//update size field inside the container
	 poTempDiamInteger32->unNumOfOctets = nSize_i;

	 //copy the Raw data inside the container
	  memcpy( poTempDiamInteger32->pnInteger32,
			  pRawData_i ,
			 nSize_i );

	  int	nTemp = *( poTempDiamInteger32->pnInteger32);
	  if ( DMBase_Retval_Success !=  DMBase_NetworkToHostLong(hDiameterStackContext_io,
										(unsigned long) nTemp,
							 (unsigned long*) poTempDiamInteger32->pnInteger32)
		 )
	  {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_NetworkToHostLong Failed , Leaving \n");
        oRetval = DMBase_Retval_Failure;
		goto ExitMe;
      }

	ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamInteger32) 
		{
			if (NULL != poTempDiamInteger32->pnInteger32) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger32->pnInteger32));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger32));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o  = poTempDiamInteger32;
	}

       
    return oRetval;  
}

t_DiamAPIReturnVal DMBase_GetDiamInteger64StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													  void*                        pRawData_i, 
                                                      void**                       ppStructData_o,
                                                      unsigned int                 nSize_i,
													  HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    void*				pMemCpyReturn       = NULL;    
    t_DiamInteger64*	poTempDiamInteger64 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	 if ( sizeof ( long long ) != nSize_i) 
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter nSize_i is invalid \n");
        return DMBase_Retval_IncorrectParameters;
    } 

	//allocate memory for the structured data container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof (t_DiamInteger64),
				   (void* ) &poTempDiamInteger64)
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

	 //allocate memory for the actual data inside container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 nSize_i,
				   (void*) &( poTempDiamInteger64->pllInteger64))
		 )
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

   	//update size field inside the container
	 poTempDiamInteger64->unNumOfOctets = nSize_i;

	 //copy the Raw data inside the container
	  memcpy( poTempDiamInteger64->pllInteger64,
			  pRawData_i ,
			 nSize_i );

	  long long	llTemp = *( poTempDiamInteger64->pllInteger64);
	  

	  if (DMBase_Retval_Success !=   DMBase_NetworkToHostLongLong(hDiameterStackContext_io,
				llTemp,(unsigned long long*) poTempDiamInteger64->pllInteger64)
		  )
	  {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_NetworkToHostLongLong Failed , Leaving \n");
        oRetval = DMBase_Retval_Failure;
		goto ExitMe;
      }

      
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamInteger64) 
		{
			if (NULL != poTempDiamInteger64->pllInteger64) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger64->pllInteger64));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamInteger64));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o  = poTempDiamInteger64;
	}

       
    return oRetval;
}


t_DiamAPIReturnVal DMBase_GetDiamFloat32StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													void*                        pRawData_i, 
                                                    void**                       ppStructData_o,
                                                    unsigned int                 nSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    void*				pMemCpyReturn     = NULL;           
    t_DiamFloat32*		poTempDiamFloat32 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	 if ( sizeof ( float) != nSize_i) 
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter nSize_i is invalid \n");
        return DMBase_Retval_IncorrectParameters;
    } 

	//allocate memory for the structured data container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof (t_DiamFloat32),
				   (void* ) &poTempDiamFloat32)
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

	 //allocate memory for the actual data inside container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 nSize_i,
				   (void*) &( poTempDiamFloat32->pflFloat32))
		 )
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

   	//update size field inside the container
	 poTempDiamFloat32->unNumOfOctets = nSize_i;

	 //copy the Raw data inside the container
	  memcpy( poTempDiamFloat32->pflFloat32,
			  pRawData_i ,
			 nSize_i );

      
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamFloat32) 
		{
			if (NULL != poTempDiamFloat32->pflFloat32) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat32->pflFloat32));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat32));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o  = poTempDiamFloat32;
	}

       
    return oRetval;
}

t_DiamAPIReturnVal DMBase_GetDiamFloat64StructData( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
													void*                        pRawData_i, 
                                                    void**                       ppStructData_o,
                                                    unsigned int                 nSize_i,
													HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io)
{
    void*              pMemCpyReturn     = NULL;
    t_DiamFloat64*     poTempDiamFloat64 = NULL;
	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL==hMsgAllocCtxt_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hMsgAllocCtxt_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == ppStructData_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "ppStructData_o  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL != (*ppStructData_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*ppStructData_o  is Not NULL , Leaving\n");
        return DMBase_Retval_IncorrectParameters;
    }

	if( NULL == pRawData_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "pRawData_i  is NULL , Leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

	 if ( sizeof ( double) != nSize_i) 
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "parameter nSize_i is invalid \n");
        return DMBase_Retval_IncorrectParameters;
    } 

	//allocate memory for the structured data container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 sizeof (t_DiamFloat64),
				   (void* ) &poTempDiamFloat64)
		)
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

	 //allocate memory for the actual data inside container
	 if (DMBase_Retval_Success !=  DMBase_AVP_Malloc(hDiameterStackContext_io,
													 hMsgAllocCtxt_io,
													 nSize_i,
				   (void*) &( poTempDiamFloat64->pdFloat64))
		 )
	 {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_AVP_Malloc Failed , Leaving \n");
        oRetval = DMBase_Retval_MemNotAvailable;
		goto ExitMe;
     }

   	//update size field inside the container
	 poTempDiamFloat64->unNumOfOctets = nSize_i;

	 //copy the Raw data inside the container
	  memcpy( poTempDiamFloat64->pdFloat64,
			  pRawData_i ,
			 nSize_i );

      
    ExitMe:

	if (DMBase_Retval_Success != oRetval)
	{
		if (NULL != poTempDiamFloat64) 
		{
			if (NULL != poTempDiamFloat64->pdFloat64) 
			{
				DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat64->pdFloat64));
			}

			DMBase_AVP_Free(hDiameterStackContext_io,hMsgAllocCtxt_io,(void**) (&poTempDiamFloat64));
		}
	}//end if (DMBase_Retval_Success != oRetval)
	else
	{
		*ppStructData_o  = poTempDiamFloat64;
	}

       
    return oRetval;
}


t_DiamAPIReturnVal DMBase_PopulateDictionaryFromFile( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                             t_DiamOctetString           oXMLDictionaryFileFullPath_i )
{
	/*
	  Load the XML dictionary file , and populate the in-memory 
	  dictionary data structures from its information
    */
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if(NULL==hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
        return DMBase_Retval_Null_Pointer;
    }

    xmlDocPtr poXmlDoc = NULL;
    xmlNodePtr poCurrXMLNode = NULL;

    poXmlDoc = xmlParseFile( oXMLDictionaryFileFullPath_i.pucOctetString );
        
    if (NULL == poXmlDoc ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! poXmlDoc is NULL , leaving .\n");
		return DMBase_Retval_Failure;
    }
        
    poCurrXMLNode = xmlDocGetRootElement(poXmlDoc);
        
    if (NULL == poCurrXMLNode) 
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! poCurrXMLNode is NULL , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DMBase_Retval_Failure;
    }
        
    if (xmlStrcmp(poCurrXMLNode->name, (const xmlChar *) "DiameterDictionaryConfiguration")) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! XML document of wrong type , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DMBase_Retval_Failure;
    }
        
    poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

	while (poCurrXMLNode != NULL) 
	{
        if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"AVP")))
		{
			ProcessAVPNode ( hDiameterStackContext_io, poXmlDoc, poCurrXMLNode);
        }
                 
        poCurrXMLNode = poCurrXMLNode->next;
    }
        
    xmlFreeDoc(poXmlDoc);
       
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}
void ProcessAVPNode (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,xmlDocPtr poXmlDoc, xmlNodePtr poXMLNode) 
{

        xmlChar *					poXMLKey = NULL;
		t_AVPDictionaryElement		oTempAVPDictElem ; 
		t_DiamDictionary			oDictionary = {0};

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


		if(NULL==hDiameterStackContext_io)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
			return ;
		}

        poXMLNode = poXMLNode->xmlChildrenNode;
		oTempAVPDictElem.unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;//default
        while (poXMLNode != NULL) 
		{
            if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"Code"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
				    oTempAVPDictElem.unAVPCode = atoi( poXMLKey );
                    xmlFree(poXMLKey);
            }
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"Name"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
					DMBase_CopyCharArrayToDiamString(&oTempAVPDictElem.oAVPName , poXMLKey);
                    xmlFree(poXMLKey);
            }
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"DataType"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
					DMBase_CopyCharArrayToDiamString(&oTempAVPDictElem.oAVPDataType , poXMLKey);
                    xmlFree(poXMLKey);
            }  
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"VendorID"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
				    oTempAVPDictElem.unVendorID = atoi( poXMLKey );
                    xmlFree(poXMLKey);
            }
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"IsGrouped"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
                    if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"yes") )
					{
						oTempAVPDictElem.bIsGrouped = 1;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
					{
						oTempAVPDictElem.bIsGrouped = 0;
					}
                    xmlFree(poXMLKey);
            }
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"FlagActions"))) 
			{
                ProcessFlagActionsNode(hDiameterStackContext_io, poXmlDoc , poXMLNode , &oTempAVPDictElem);
            }  
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"FlagRules"))) 
			{
				ProcessFlagRulesNode(hDiameterStackContext_io, poXmlDoc,poXMLNode , &oTempAVPDictElem);
            }
			poXMLNode = poXMLNode->next;
        }

		//insert this node into the XML dictionary at the right place

		if ( oTempAVPDictElem.unAVPCode > DMBASE_MAX_DICTIONARY_SIZE) 
		{
			//log an error !!
			//TODO: Log over here 
			return;
		}
			
		oTempAVPDictElem.bIsPredefinedByRFC3588 = 0;
                
                if(1 != oTempAVPDictElem.bIsGrouped )
                {
                        DMBase_LookupFuncPtrsFromMapTable (hDiameterStackContext_io, oTempAVPDictElem.oAVPDataType
			             , & (oTempAVPDictElem.oAVPDictionaryFunctionPtrs) );
                }
                else
                {
                 //   oTempAVPDictElem.oAVPDictionaryFunctionPtrs = NULL;
					//TODO: Call zero mem function on the above data struct
                }

		if (DMBase_Retval_Success !=  DMBase_GetDictionaryObjectFromDiameterContext(hDiameterStackContext_io,&oDictionary))
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_GetDictionaryObjectFromDiameterContext failed , Leaving\n");
			return;
		}
		AddElementToDictionary ( & (oDictionary.poDictionaryArray[oTempAVPDictElem.unAVPCode]),
										 &oTempAVPDictElem);

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	

    return ;
}
void ProcessFlagActionsNode (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,xmlDocPtr poXmlDoc, xmlNodePtr poXMLNode , t_AVPDictionaryElement* poDictElem_o) 
{

        xmlChar *poXMLKey;
        poXMLNode = poXMLNode->xmlChildrenNode;

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


		if(NULL==hDiameterStackContext_io)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
			return ;
		}

        while (poXMLNode != NULL) 
		{
            if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"M_Flag"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
                    if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"set") )
					{
						(poDictElem_o->oMFlag).oFlagAction = AVPFlagAction_Set;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"clear") )
					{
						(poDictElem_o->oMFlag).oFlagAction = AVPFlagAction_Clear;
					}
                    xmlFree(poXMLKey);
            }
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"P_Flag"))) 
			{
				poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
				if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"set") )
				{
					(poDictElem_o->oPFlag).oFlagAction = AVPFlagAction_Set;
				}
				else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"clear") )
				{
					(poDictElem_o->oPFlag).oFlagAction = AVPFlagAction_Clear;
				}
				xmlFree(poXMLKey);
			 }     
        poXMLNode = poXMLNode->next;
        }

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return;
}
void ProcessFlagRulesNode (HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,xmlDocPtr poXmlDoc, xmlNodePtr poXMLNode,  t_AVPDictionaryElement* poDictElem_o) 
{

        xmlChar *poXMLKey;
        poXMLNode = poXMLNode->xmlChildrenNode;
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


		if(NULL==hDiameterStackContext_io)
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , leaving\n");
			return ;
		}

        while (poXMLNode != NULL) 
		{
            if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"M_Flag"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
                    if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"must") )
					{
						(poDictElem_o->oMFlag).oFlagRule = AVPFlagRule_Must;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"may") )
					{
						(poDictElem_o->oMFlag).oFlagRule = AVPFlagRule_May;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"shouldnot") )
					{
						(poDictElem_o->oMFlag).oFlagRule = AVPFlagRule_ShouldNot;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"mustnot") )
					{
						(poDictElem_o->oMFlag).oFlagRule = AVPFlagRule_MustNot;
					}
                    xmlFree(poXMLKey);
            }
			else if ((!xmlStrcmp(poXMLNode->name, (const xmlChar *)"P_Flag"))) 
			{
                    poXMLKey = xmlNodeListGetString(poXmlDoc, poXMLNode->xmlChildrenNode, 1);
                    if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"must") )
					{
						(poDictElem_o->oPFlag).oFlagRule = AVPFlagRule_Must;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"may") )
					{
						(poDictElem_o->oPFlag).oFlagRule = AVPFlagRule_May;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"shouldnot") )
					{
						(poDictElem_o->oPFlag).oFlagRule = AVPFlagRule_ShouldNot;
					}
					else  if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"mustnot") )
					{
						(poDictElem_o->oPFlag).oFlagRule = AVPFlagRule_MustNot;
					}
                    xmlFree(poXMLKey);
			}      
        poXMLNode = poXMLNode->next;
        }
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return;
}

t_DiamAPIReturnVal AddElementToDictionary ( t_AVPDictionaryElement* poDestDictElem_o,
	 											   t_AVPDictionaryElement* poSrcDictElem_i )
{
	if ( ( NULL == poDestDictElem_o ) || ( NULL==poSrcDictElem_i) ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Error ! NULL pointer in input , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

    poDestDictElem_o->bIsPredefinedByRFC3588 = poSrcDictElem_i->bIsPredefinedByRFC3588;
	poDestDictElem_o->bIsGrouped = poSrcDictElem_i->bIsGrouped;
	poDestDictElem_o->oAVPDictionaryFunctionPtrs = poSrcDictElem_i->oAVPDictionaryFunctionPtrs;
	poDestDictElem_o->oMFlag = poSrcDictElem_i->oMFlag;
	poDestDictElem_o->oPFlag = poSrcDictElem_i->oPFlag;
	poDestDictElem_o->unAVPCode =  poSrcDictElem_i->unAVPCode;
	poDestDictElem_o->unVendorID = poSrcDictElem_i->unVendorID;

	//now copying the strings 

        
        DMBase_MemsetZero(&poDestDictElem_o->oAVPDataType, sizeof(t_DiamOctetString));
        DMBase_MemsetZero(&poDestDictElem_o->oAVPName, sizeof(t_DiamOctetString));
        
	DMBase_CopyDiamString(&poDestDictElem_o->oAVPDataType , &poSrcDictElem_i->oAVPDataType);
	DMBase_CopyDiamString(&poDestDictElem_o->oAVPName , &poSrcDictElem_i->oAVPName);

	return DMBase_Retval_Success;
}
t_DiamAPIReturnVal DMBase_DeleteDictElem ( t_AVPDictionaryElement oAVPDictElem )
{
	DMBase_DeleteDiamString( &(oAVPDictElem.oAVPDataType) );
	DMBase_DeleteDiamString( &(oAVPDictElem.oAVPName ) );

	return DMBase_Retval_Success;
}
t_DiamAPIReturnVal DMBase_LookupFuncPtrsFromMapTable (HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											   t_DiamOctetString  oAVPDataType ,  
												t_AVPDictionaryFunctionPtrs*  poAVPDictFptrs_o )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if ( NULL == poAVPDictFptrs_o )
    {
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Error ,poAVPDictFptrs_o is NULL , Leaving  \n");
		return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiameterStackContext_io )
    {
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Error ,hDiameterStackContext_io is NULL , Leaving  \n");
		return DMBase_Retval_Null_Pointer;
	}

	unsigned int unCurrInd = 0;
	_Bool bFound = 0;
	for ( unCurrInd=0 ; unCurrInd<= DMBASE_MAX_DIC_FUNCPTR_MAPTABLE_SIZE ; unCurrInd++) 
	{
		if ( 0 == strncmp ( hDiameterStackContext_io->oDiam_FuncPtrMappingTable[unCurrInd].pucAVPDataTypeName,
							 oAVPDataType.pucOctetString,DMBASE_MAX_SMALL_STRING_SIZE )
		   )
		{
			*poAVPDictFptrs_o = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[unCurrInd].oAVPDictionaryFunctionPtrs;
			bFound = 1;
			break;
		}
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	if (1 == bFound) 
	{
		return DMBase_Retval_Success;
	}
	else
	{
		return DMBase_Retval_Not_Found;
	}
	
}
t_DiamAPIReturnVal	DMBase_InitBaseProtocolDictionaryElements(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io)
{
	static	_Bool	bIsInit = 0;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " hDiameterStackContext_io is NULL , leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (1 == bIsInit) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Static part of Dictionary already initialised , leaving \n");
		return DMBase_Retval_Success;
	}

	t_DiamDictionary	oDictionary = {0};
	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
											hDiameterStackContext_io,&oDictionary)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " DMBase_GetDictionaryObjectFromDiameterContext failed , leaving \n");
		return DMBase_Retval_Failure;
	}

	
		//BEGIN initialising the elements of dictionary which are preDefined in RFC 3588

	//DMBASE_AVP_ACCT_INTERIM_INTERVAL 		85
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString (&oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oAVPDataType ,
							   DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString (&oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oAVPName ,
							    "Accounting Interim Interval" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].unAVPCode = DMBASE_AVP_ACCT_INTERIM_INTERVAL;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_INTERIM_INTERVAL].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	//DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED    483
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString (&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oAVPDataType ,
							    DMBASE_AVP_DATATYPE_ENUMERATED ) ;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oAVPName ,
							  "Accounting Realtime Required");
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].unAVPCode = DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_REALTIME_REQUIRED].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	//DMBASE_AVP_ACCT_MULTI_SESSION_ID           50
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oAVPDataType,
							   DMBASE_AVP_DATATYPE_UTF8STRING);
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oAVPName,
							  "Accounting Multisession ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].unAVPCode = DMBASE_AVP_ACCT_MULTI_SESSION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_MULTI_SESSION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ACCOUNTING_RECORD_NUMBER            485
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oAVPDataType,
							   DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oAVPName ,
							  "Accounting Record Number" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].unAVPCode = DMBASE_AVP_ACCOUNTING_RECORD_NUMBER;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_NUMBER].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ACCOUNTING_RECORD_TYPE              480
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oAVPName,
							   "Accounting Record Type" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].oPFlag.oFlagAction= AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].unAVPCode = DMBASE_AVP_ACCOUNTING_RECORD_TYPE;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_RECORD_TYPE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ACCOUNTING_SESSION_ID           44
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_OCTETSTRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oAVPName ,
							  "AVP Accounting Session ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].unAVPCode = DMBASE_AVP_ACCOUNTING_SESSION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SESSION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID       287
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED64 );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED64].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oAVPName ,
							   "Accounting Sub session ID");
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].unAVPCode = DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCOUNTING_SUB_SESSION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ACCT_APPLICATION_ID             259
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oAVPName 
							  , "Accounting Application ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].unAVPCode = DMBASE_AVP_ACCT_APPLICATION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_ACCT_APPLICATION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_AUTH_APPLICATION_ID             258
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oAVPName ,
							  "Auth Application ID");
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].unAVPCode = DMBASE_AVP_AUTH_APPLICATION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_APPLICATION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_AUTH_REQUEST_TYPE               274
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oAVPName 
							  ,"Auth Request Type");
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].unAVPCode = DMBASE_AVP_AUTH_REQUEST_TYPE;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_REQUEST_TYPE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_AUTHORIZATION_LIFETIME          291
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oAVPName,
							   "Authorization lifetime");
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].unAVPCode = DMBASE_AVP_AUTHORIZATION_LIFETIME;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTHORIZATION_LIFETIME].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_AUTH_GRACE_PERIOD               276
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oAVPName,
							  "Auth Grace Period" );
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].unAVPCode = DMBASE_AVP_AUTH_GRACE_PERIOD;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_GRACE_PERIOD].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_AUTH_SESSION_STATE              277
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oAVPDataType ,
							   DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oAVPName ,
							  "Auth Session State");
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].unAVPCode = DMBASE_AVP_AUTH_SESSION_STATE;
	oDictionary.poDictionaryArray[DMBASE_AVP_AUTH_SESSION_STATE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_RE_AUTH_REQUEST_TYPE            285
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oAVPName ,
							  "ReAuth Request Type" );
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].unAVPCode = DMBASE_AVP_RE_AUTH_REQUEST_TYPE;
	oDictionary.poDictionaryArray[DMBASE_AVP_RE_AUTH_REQUEST_TYPE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_CLASS                           25
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_OCTETSTRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oAVPName ,
							  "Class" );
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].unAVPCode = DMBASE_AVP_CLASS;
	oDictionary.poDictionaryArray[DMBASE_AVP_CLASS].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_DESTINATION_HOST                293
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oAVPName ,
							  "Destination Host" );
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].unAVPCode = DMBASE_AVP_DESTINATION_HOST;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_HOST].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_DESTINATION_REALM               283
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].bIsGrouped =  0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oAVPName ,
							  "Destination Realm" );
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].unAVPCode = DMBASE_AVP_DESTINATION_REALM;
	oDictionary.poDictionaryArray[DMBASE_AVP_DESTINATION_REALM].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_DISCONNECT_CAUSE                273
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oAVPDataType 
							  , DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oAVPName ,
							  "Disconnect Cause" );
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].unAVPCode = DMBASE_AVP_DISCONNECT_CAUSE;
	oDictionary.poDictionaryArray[DMBASE_AVP_DISCONNECT_CAUSE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ERROR_MESSAGE                   281
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oAVPDataType,
							   DMBASE_AVP_DATATYPE_UTF8STRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oAVPName ,
							  "Error Message" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oMFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oMFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].unAVPCode = DMBASE_AVP_ERROR_MESSAGE;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_MESSAGE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ERROR_REPORTING_HOST            294
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oAVPDataType ,
							   DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oAVPName ,
							  "Error Reporting Host");
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oMFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oMFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].unAVPCode = DMBASE_AVP_ERROR_REPORTING_HOST;
	oDictionary.poDictionaryArray[DMBASE_AVP_ERROR_REPORTING_HOST].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_EVENT_TIMESTAMP                 55
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_TIME );
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_TIME].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oAVPName ,
							  "Event Timestamp" );
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].unAVPCode = DMBASE_AVP_EVENT_TIMESTAMP;
	oDictionary.poDictionaryArray[DMBASE_AVP_EVENT_TIMESTAMP].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_EXPERIMENTATION_RESULT_CODE     298
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 ) ;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oAVPName ,
							  "Experimentation Result Code" );
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].unAVPCode = DMBASE_AVP_EXPERIMENTATION_RESULT_CODE;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTATION_RESULT_CODE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_FIRMWARE_REVISION               267
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oAVPName ,
							  "Firmware Revision" );
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oMFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oMFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oPFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].oPFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].unAVPCode = DMBASE_AVP_FIRMWARE_REVISION;
	oDictionary.poDictionaryArray[DMBASE_AVP_FIRMWARE_REVISION].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_HOST_IP_ADDRESS                 257
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_IPADDRESS );
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_IPADDRESS].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oAVPName ,
							  "Host IP Address" );
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].unAVPCode = DMBASE_AVP_HOST_IP_ADDRESS;
	oDictionary.poDictionaryArray[DMBASE_AVP_HOST_IP_ADDRESS].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_INBAND_SECURITY_ID              299
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oAVPName ,
							  "Inband Security ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].unAVPCode = DMBASE_AVP_INBAND_SECURITY_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_INBAND_SECURITY_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_MULTI_ROUND_TIME_OUT            272
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oAVPName ,
							  "Multiround Timeout" );
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].unAVPCode = DMBASE_AVP_MULTI_ROUND_TIME_OUT;
	oDictionary.poDictionaryArray[DMBASE_AVP_MULTI_ROUND_TIME_OUT].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ORIGIN_HOST                     264
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oAVPName ,
							  "Origin Host" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].unAVPCode = DMBASE_AVP_ORIGIN_HOST;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_HOST].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ORIGIN_REALM                    296
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oAVPName ,
							  "Origin Realm" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].unAVPCode = DMBASE_AVP_ORIGIN_REALM;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_REALM].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ORIGIN_STATE_ID                 278
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oAVPName ,
							  "Origin State ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].unAVPCode = DMBASE_AVP_ORIGIN_STATE_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_ORIGIN_STATE_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_PRODUCT_NAME                    269
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UTF8STRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oAVPName ,
							  "Product Name" );
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oMFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oMFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oPFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].oPFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].unAVPCode = DMBASE_AVP_PRODUCT_NAME;
	oDictionary.poDictionaryArray[DMBASE_AVP_PRODUCT_NAME].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_PROXY_HOST                      280
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oAVPName ,
							  "Proxy Host" );
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oPFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].oPFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].unAVPCode = DMBASE_AVP_PROXY_HOST;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_HOST].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_PROXY_STATE                     33
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oAVPDataType ,
							   DMBASE_AVP_DATATYPE_OCTETSTRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_OCTETSTRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oAVPName ,
							  "Proxy state" );
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oPFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].oPFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].unAVPCode = DMBASE_AVP_PROXY_STATE;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_STATE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_REDIRECT_HOST                   292
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_DMURI );
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMURI].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oAVPName ,
							  "Redirect Host" );
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].unAVPCode = DMBASE_AVP_REDIRECT_HOST;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_REDIRECT_HOST_USAGE             261
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oAVPName ,
							  "Redirect Host Usage" );
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].unAVPCode = DMBASE_AVP_REDIRECT_HOST_USAGE;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_HOST_USAGE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_REDIRECT_MAX_CACHE_TIME         262
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oAVPDataType,
							   DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oAVPDictionaryFunctionPtrs =hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oAVPName ,
							  "redirect max cache time" );
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].unAVPCode = DMBASE_AVP_REDIRECT_MAX_CACHE_TIME;
	oDictionary.poDictionaryArray[DMBASE_AVP_REDIRECT_MAX_CACHE_TIME].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_RESULT_CODE                     268
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oAVPName ,
							  "result code" );
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].unAVPCode = DMBASE_AVP_RESULT_CODE;
	oDictionary.poDictionaryArray[DMBASE_AVP_RESULT_CODE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_ROUTE_RECORD                    282
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oAVPDataType,
							  DMBASE_AVP_DATATYPE_DMIDENTITY );
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_DMIDENTITY].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oAVPName  ,
							  "Route Record" );
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oPFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].oPFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].unAVPCode = DMBASE_AVP_ROUTE_RECORD;
	oDictionary.poDictionaryArray[DMBASE_AVP_ROUTE_RECORD].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_SESSION_ID                      263
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UTF8STRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oAVPName ,
							  "Session ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;  
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].unAVPCode = DMBASE_AVP_SESSION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_SESSION_TIMEOUT                 27
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oAVPDataType,
							   DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oAVPName ,
							  "Session Timeout"  );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].unAVPCode = DMBASE_AVP_SESSION_TIMEOUT;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_TIMEOUT].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_SESSION_BINDING                 270
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oAVPName ,
							  "Session Binding" );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].unAVPCode = DMBASE_AVP_SESSION_BINDING;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_BINDING].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_SESSION_SERVER_FAILOVER         271
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oAVPName ,
							  "Session Server Failover" );
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].unAVPCode = DMBASE_AVP_SESSION_SERVER_FAILOVER;
	oDictionary.poDictionaryArray[DMBASE_AVP_SESSION_SERVER_FAILOVER].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_SUPPORTED_VENDOR_ID             265
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oAVPName ,
							  "Supported Vendor ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].unAVPCode = DMBASE_AVP_SUPPORTED_VENDOR_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_SUPPORTED_VENDOR_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_TERMINATION_CAUSE               295
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_ENUMERATED );
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_ENUMERATED].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oAVPName , 
							  "Termination Cause" );
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].unAVPCode = DMBASE_AVP_TERMINATION_CAUSE;
	oDictionary.poDictionaryArray[DMBASE_AVP_TERMINATION_CAUSE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_USER_NAME                       1
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_UTF8STRING );
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UTF8STRING].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oAVPName ,
							  "User Name" );
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].unAVPCode = DMBASE_AVP_USER_NAME;
	oDictionary.poDictionaryArray[DMBASE_AVP_USER_NAME].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_VENDOR_ID                       266
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].bIsGrouped = 0;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oAVPDataType ,
													DMBASE_AVP_DATATYPE_UNSIGNED32 );
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oAVPDictionaryFunctionPtrs = hDiameterStackContext_io->oDiam_FuncPtrMappingTable[DMBASE_DIC_FPTR_TAB_INDX_UNSIGNED32].oAVPDictionaryFunctionPtrs;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oAVPName ,
							  "Vendor ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].unAVPCode = DMBASE_AVP_VENDOR_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_E2E_SEQUENCE                    300
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].bIsGrouped = 1;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_GROUPED );
	//NO need , initialised to zero oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oAVPDictionaryFunctionPtrs ;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oAVPName ,
							  "E2E Sequence");
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].unAVPCode = DMBASE_AVP_E2E_SEQUENCE;
	oDictionary.poDictionaryArray[DMBASE_AVP_E2E_SEQUENCE].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_EXPERIMENTAL_RESULT             297
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].bIsGrouped = 1;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_GROUPED );
	//NO need , initialised to zero oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oAVPDictionaryFunctionPtrs = NULL;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oAVPName ,
							  "Experimental Result" );
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].unAVPCode = DMBASE_AVP_EXPERIMENTAL_RESULT;
	oDictionary.poDictionaryArray[DMBASE_AVP_EXPERIMENTAL_RESULT].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_FAILED_AVP                     279
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].bIsGrouped = 1;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_GROUPED );
	//NO need , initialised to zero oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oAVPDictionaryFunctionPtrs = NULL;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oAVPName ,
							  "Failed AVP" );
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].unAVPCode = DMBASE_AVP_FAILED_AVP;
	oDictionary.poDictionaryArray[DMBASE_AVP_FAILED_AVP].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_PROXY_INFO                      284            
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].bIsGrouped = 1; 
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oAVPDataType ,
							  DMBASE_AVP_DATATYPE_GROUPED );
	//NO need , initialised to zero oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oAVPDictionaryFunctionPtrs = NULL;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oAVPName ,
							  "Proxy Info" );
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oPFlag.oFlagRule = AVPFlagRule_MustNot;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].oPFlag.oFlagAction = AVPFlagAction_Clear;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].unAVPCode = DMBASE_AVP_PROXY_INFO;
	oDictionary.poDictionaryArray[DMBASE_AVP_PROXY_INFO].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID  260
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].bIsPredefinedByRFC3588 = 1;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].bIsGrouped = 1;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oAVPDataType,
							   DMBASE_AVP_DATATYPE_GROUPED );
	//NO need , initialised to zero oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oAVPDictionaryFunctionPtrs = NULL;
	DMBase_CopyCharArrayToDiamString(&oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oAVPName ,
							  "Vendor Specific Application ID" );
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oMFlag.oFlagRule = AVPFlagRule_Must;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oMFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oPFlag.oFlagRule = AVPFlagRule_May;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].oPFlag.oFlagAction = AVPFlagAction_Set;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].unAVPCode = DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID;
	oDictionary.poDictionaryArray[DMBASE_AVP_VENDOR_SPECIFIC_APPLICATION_ID].unVendorID = DMBASE_AVP_VENDOR_ID_NOT_USED;
	
	
	//END initialising the elements of dictionary which are preDefined in RFC 3588

	bIsInit = 1;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_IsTypeOctetStringOrDerived ( HDIAMETERSTACKCONTEXT    hDiameterStackContext_io,
														unsigned int	unAVPCode_i,
														_Bool*	pbIsOctstDer_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if ( NULL == hDiameterStackContext_io) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " hDiameterStackContext_io is NULL , Leaving \n");
		return	DMBase_Retval_Null_Pointer;
	}

	if ( NULL == pbIsOctstDer_o) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " pbIsOctstDer_o is NULL , Leaving \n");
		return	DMBase_Retval_Null_Pointer;
	}

	t_DiamDictionary	oDictionary = {0};
	if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
									hDiameterStackContext_io,&oDictionary)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " DMBase_GetDictionaryObjectFromDiameterContext failed , Leaving \n");
		return	DMBase_Retval_Failure;
	}
	

	if (	( 0 == strcmp(oDictionary.poDictionaryArray[unAVPCode_i].oAVPDataType.pucOctetString,
					 DMBASE_AVP_DATATYPE_OCTETSTRING)
			 ) ||
			( 0 == strcmp(oDictionary.poDictionaryArray[unAVPCode_i].oAVPDataType.pucOctetString,
					 DMBASE_AVP_DATATYPE_UTF8STRING)
			) ||
			( 0 == strcmp(oDictionary.poDictionaryArray[unAVPCode_i].oAVPDataType.pucOctetString,
					 DMBASE_AVP_DATATYPE_DMIDENTITY)
			) ||
			( 0 == strcmp(oDictionary.poDictionaryArray[unAVPCode_i].oAVPDataType.pucOctetString,
					 DMBASE_AVP_DATATYPE_DMURI)
			) ||
			( 0 == strcmp(oDictionary.poDictionaryArray[unAVPCode_i].oAVPDataType.pucOctetString,
					 DMBASE_AVP_DATATYPE_IPADDRESS)
			) 
	    ) 
	{
		*pbIsOctstDer_o = 1;
	}
	else
	{
		*pbIsOctstDer_o = 0;
	}



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");

	return	DMBase_Retval_Success;
}

inline	_Bool	DMBase_IsSafeToAccessDictElement(t_AVPDictionaryElement* poDiamDict_i,
												 unsigned int	unAVPCode_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

	if (NULL == poDiamDict_i) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " poDiamDict_i is NULL , Leaving \n");
        return 0;
	}

	if (unAVPCode_i >= DMBASE_MAX_DICTIONARY_SIZE) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " unAVPCode_i = %d >= DMBASE_MAX_DICTIONARY_SIZE = %d , Leaving \n",unAVPCode_i,DMBASE_MAX_DICTIONARY_SIZE);
        return 0;
	}

	if ( (unAVPCode_i != poDiamDict_i[unAVPCode_i].unAVPCode) ||
		 (0 == poDiamDict_i[unAVPCode_i].oAVPName.unNumOfOctets)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " unAVPCode_i = %d != poDiamDict_i[unAVPCode_i].unAVPCode= %d , Leaving \n",unAVPCode_i,poDiamDict_i[unAVPCode_i].unAVPCode);
        return 0;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving \n");
	return 1; //reached till here then it is ok and safe to access current element of array
}
