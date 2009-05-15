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
#include "dmbase_message.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_dictionary.h"
#include "dmbase_avp.h"


/* external */
extern	int							g_nDiamBaseTraceID ;

/******************************************************************************
** Function Name:  DMBase_CreateDiameterMessage
**  
** Parameters:
**		  HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		  HDIAMETERMESSAGE*  ophDiaMsg_o
**			type: output
**			detail: This is a diameter Message Structure 
**                
**               unsigned char   ucDiaMsgVersion_i
**                      type: input
**                      detail:  
**
**               unsigned char   ucDiaMsgCommandCode_i
**                      type: input
**                      detail:
**
**               unDiaMsgApplicationID_i 
**                      type: input
**                      detail:
** Return:
**		An integer specifying the size in characters of pcMyString_i  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
*/
 
t_DiamAPIReturnVal DMBase_CreateDiameterMessage( 
				HDIAMETERSTACKCONTEXT   hDiameterStackContext_io , 
				HDIAMETERMESSAGE*       phDiaMsg_o ,
                unsigned char           ucDiaMsgVersion_i,
                unsigned int            unDiaMsgCommandCode_i,  
                unsigned int            unDiaMsgApplicationID_i ,
				unsigned char 			ucFlags_i,
				unsigned int  			unHopByHopID_i,
				unsigned int  			unEndToEndID_i)
{
    unsigned int    	unMsgLengthInBytes =  DMBASE_MSG_HEADER_SIZE_IN_BYTES;
	t_DiamAPIReturnVal	oDiamRetVal = DMBase_Retval_Success;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");


	if( NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving\n");
        oDiamRetVal = DMBase_Retval_Null_Pointer ;   
		goto ExitMe;
    }
    
	if( NULL == phDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter phDiaMsg_o is NULL , Leaving\n");
        oDiamRetVal = DMBase_Retval_Null_Pointer ; 
		goto ExitMe;
    }

	if( NULL != *phDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter *phDiaMsg_o must be NULL, Leaving \n");
        oDiamRetVal = DMBase_Retval_IncorrectParameters;   
		goto ExitMe;
    }

	

	if ( DMBase_Retval_Success != DMBase_Malloc(hDiameterStackContext_io,
												(void**) phDiaMsg_o,sizeof (t_DiameterMessage))
	   )
    
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Problem in Memory Allocation , Leaving \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }

	

	HDIAMETERMESSAGE	hDiamMsg = *phDiaMsg_o;

	hDiamMsg->hDiameterStackContext = hDiameterStackContext_io;
  

	if ( DMBase_Retval_Success != DMBase_SetDiaMsgVersion(hDiameterStackContext_io,
														 hDiamMsg,ucDiaMsgVersion_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetDiaMsgVersion FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }

	if ( DMBase_Retval_Success != DMBase_SetDiaMsgFlagOctet(hDiameterStackContext_io,
														 hDiamMsg,ucFlags_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetDiaMsgFlagOctet FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }


	if ( DMBase_Retval_Success != DMBase_SetDiaMsgLength(hDiameterStackContext_io,
														 hDiamMsg,unMsgLengthInBytes)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetDiaMsgLength FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }

	if ( DMBase_Retval_Success != DMBase_SetDiaMsgCmdCode(hDiameterStackContext_io,
														 hDiamMsg,unDiaMsgCommandCode_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetDiaMsgCmdCode FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }

	if ( DMBase_Retval_Success != DMBase_SetDiaMsgAppId(hDiameterStackContext_io,
														 hDiamMsg,unDiaMsgApplicationID_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetDiaMsgAppId FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }

	if ( DMBase_Retval_Success != DMBase_SetHopByHopID(hDiameterStackContext_io,
														 hDiamMsg,unHopByHopID_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetHopByHopID FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }

	if ( DMBase_Retval_Success != DMBase_SetEndToEndID(hDiameterStackContext_io,
														 hDiamMsg,unEndToEndID_i)
	   )
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_SetEndToEndID FAILED \n");
        oDiamRetVal = DMBase_Retval_Failure; 
		goto ExitMe;
    }
     
    hDiamMsg->hCollectionOfAVPs = NULL;    

	hDiamMsg->oMemBlockForAVPs.pucCurrPtr = hDiamMsg->oMemBlockForAVPs.pucMemBlockForAVP;

	ExitMe:

	if (DMBase_Retval_Success != oDiamRetVal) 
	{
		if (NULL != *phDiaMsg_o) 
		{
			//free mem
			if ( DMBase_Retval_Success != DMBase_Free(hDiameterStackContext_io,
													  (void**) phDiaMsg_o)
				 )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "DMBase_Free FAILED for phDiaMsg_o == %x  \n",phDiaMsg_o);
			}
		}//end if (NULL != *phDiaMsg_o)
	}//end if (DMBase_Retval_Success != oDiamRetVal

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering \n");

    
    return oDiamRetVal ;  
    
}

/******************************************************************************
** Function Name:  DMBase_CreateDiameterMessage
**  
** Parameters:
**		  HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		  HDIAMETERMESSAGE  hDiaMsg_o 
**			type: output
**			detail: This is a diameter Message Structure 
**                
**               DAPI-SList*         pAVPList
**                      type: input
**                      detail:  
** Return:
**		An integer specifying the size in characters of pcMyString_i  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_AddAVPCollectionToDiameterMessage ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                                          HDIAMETERMESSAGE  hDiaMsg_o ,
                                                          HAVPCOLLECTION	hCollOfAVPs_i )  
{
  
  if ( NULL == hDiameterStackContext_io ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }

  if ( NULL == hDiaMsg_o ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }

  if ( NULL == hCollOfAVPs_i ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hCollOfAVPs_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }

  hDiaMsg_o->hCollectionOfAVPs = hCollOfAVPs_i;

  unsigned int	unTotalAVPsSize = 0;

  if (DMBase_Retval_Success !=  DMBase_GetTotalSizeOfAllAVPsInCollection(hDiameterStackContext_io,
									 hDiaMsg_o->hCollectionOfAVPs,
									 &unTotalAVPsSize) )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetTotalSizeOfAllAVPsInCollection Failed , Leaving \n");
	  return DMBase_Retval_Failure;
  }

  
  unsigned int	unDiamMsgLength = 0;
 

  if (DMBase_Retval_Success !=  DMBase_GetDiaMsgLengthFromDiamMsg(hDiameterStackContext_io,
									   hDiaMsg_o,&unDiamMsgLength)
	  )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgLengthFromDiamMsg Failed , Leaving \n");
	  return DMBase_Retval_Failure;
  }

 
  unDiamMsgLength += unTotalAVPsSize;

  

  if (DMBase_Retval_Success !=  DMBase_SetDiaMsgLength(hDiameterStackContext_io,
							    hDiaMsg_o,unDiamMsgLength)
	  )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetDiaMsgLength Failed , Leaving \n");
	  return DMBase_Retval_Failure;
  }

  

  
  return DMBase_Retval_Success ; 
}
/******************************************************************************
** Function Name:  DMBase_CreateDiameterMessage
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE*    hDiaMsg_i
**			type: output
**			detail: This is a diameter Message Structure 
** Return:
**		 An integer specifying the size in characters of pcMyString_i  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal  DMBase_DestroyDiaMessage       ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                                     HDIAMETERMESSAGE*        phDiaMsg_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if (NULL == hDiameterStackContext_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phDiaMsg_i ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! phDiaMsg_i is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}


	t_DiameterMessage*	poDiamMsg = ( t_DiameterMessage*) (*phDiaMsg_i);

	if (NULL == poDiamMsg ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! poDiamMsg is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}


	if (NULL != poDiamMsg->hCollectionOfAVPs) 
	{
		if ( DMBase_Retval_Success != DMBase_DestroyAVPCollection(
						hDiameterStackContext_io,&(poDiamMsg->hCollectionOfAVPs))
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Function Failed \n");
			oRetval = DMBase_Retval_Failure;
			goto ExitMe;
        }
	}
	else
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," AVP Collection inside message is empty , no need to free it .\n");
	}

	ExitMe:

	if (NULL != poDiamMsg) 
	{
		if ( DMBase_Retval_Success !=  DMBase_Free(hDiameterStackContext_io,
												   (void**) &poDiamMsg)
		   )
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Function Failed  \n");
        }
	}//end if (NULL != poDiamMsg) 
	else
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," poDiamMsg is NULL here , why?? \n");
    }
	

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return oRetval;
}                                                       
        					        
 /******************************************************************************
** Function Name:  DMBase_SetHopByHopID
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE        ohDiaMsg_o
**			type: output
**			detail: This is a diameter Message Structure 
**                
**                unsigned int                DiaMsgHopByHopID_i
**                      type: input
**                      detail:  
** Return:
**		An integer specifying the sucess or failure of function  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
 */
t_DiamAPIReturnVal   DMBase_SetHopByHopID( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o,
                                           unsigned int                unDiaMsgHopByHopID_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL == hDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiaMsg_o is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    hDiaMsg_o->oDiaHeader.unHopByHopID = unDiaMsgHopByHopID_i ;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    return DMBase_Retval_Success;  
}
 /******************************************************************************
** Function Name:  DMBase_SetEndToEndID
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE        ohDiaMsg_o
**			type: output
**			detail: This is a diameter Message Structure 
**                
**                unsigned int               DiaMsgEndToEndID_i
**                      type: input
**                      detail:  
** Return:
**		An integer specifying the sucess or failure of function  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
 */                                               
t_DiamAPIReturnVal   DMBase_SetEndToEndID( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
                                           HDIAMETERMESSAGE       hDiaMsg_o ,
                                           unsigned int               unDiaMsgEndToEndID_i )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
    }

    if(NULL == hDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiaMsg_o is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    hDiaMsg_o->oDiaHeader.unEndToEndID = unDiaMsgEndToEndID_i ;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    
    return(DMBase_Retval_Success); 
}

/******************************************************************************
** Function Name:  DMBase_SetDiaMsgRFlag
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE        ohDiaMsg_o
**			type: output
**			detail: This is a handle to diameter Message Structure 
**                
**                 _Bool                        bFlagValue_i
**                      type: input
**                      detail:  
** Return:
**		An integer specifying the sucess or failure of function  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
 */                                               


t_DiamAPIReturnVal   DMBase_SetDiaMsgRFlag(HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o,
                                           _Bool                        bFlagValue_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL == hDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiaMsg_o is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    if( bFlagValue_i )
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags |= DMBASE_BITMASK_SET_MSG_R_FLAG;
	}
    else
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags &= DMBASE_BITMASK_CLEAR_MSG_R_FLAG ;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    
    return DMBase_Retval_Success; 
}
/******************************************************************************
** Function Name:  DMBase_SetDiaMsgPFlag
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE        ohDiaMsg_o
**			type: output
**			detail: This is a handle to diameter Message Structure 
**                
**                _Bool                        bFlagValue_i
**                      type: input
**                      detail:  
** Return:
**		An integer specifying the sucess or failure of function  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
 */  


t_DiamAPIReturnVal   DMBase_SetDiaMsgPFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io,
                                            HDIAMETERMESSAGE       hDiaMsg_o ,
                                            _Bool                       bFlagValue_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL == hDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiaMsg_o is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }
    
    if( bFlagValue_i )
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags |= DMBASE_BITMASK_SET_MSG_P_FLAG;
	}
    else
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags &= DMBASE_BITMASK_CLEAR_MSG_P_FLAG ;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    
    return DMBase_Retval_Success; 
}
                                            
/******************************************************************************
** Function Name:  DMBase_SetDiaMsgEFlag
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE        ohDiaMsg_o
**			type: output
**			detail: This is a handle to diameter Message Structure 
**                
**                 _Bool                        bFlagValue_i
**                      type: input
**                      detail:  
** Return:
**		   An integer specifying the sucess or failure of function  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
 */                                            
                                            
t_DiamAPIReturnVal      DMBase_SetDiaMsgEFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                               HDIAMETERMESSAGE        hDiaMsg_o ,
                                               _Bool                        bFlagValue_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	if( NULL == hDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiaMsg_o is NULL\n");
        return(DMBase_Retval_IncorrectParameters);
    }
    
    if( bFlagValue_i )
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags |= DMBASE_BITMASK_SET_MSG_E_FLAG;
	}
    else
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags &= DMBASE_BITMASK_CLEAR_MSG_E_FLAG ;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    
    return DMBase_Retval_Success; 
    
}

/******************************************************************************
** Function Name:  DMBase_SetDiaMsgFFlag
**  
** Parameters:
**		   HDIAMETERSTACKCONTEXT   hDiameterStackContext_io
**			 type: input
**			 detail : this is a C style Structure contains 
**
**		   HDIAMETERMESSAGE        ohDiaMsg_o
**			type: output
**			detail: This is a handle to diameter Message Structure 
**                
**                 _Bool                        bFlagValue_i
**                      type: input
**                      detail:  
** Return:
**		An integer specifying the sucess or failure of function  
*******************************************************************************
** Created By: 		: Simab Shahid
*******************************************************************************
*******************************************************************************
 */                

t_DiamAPIReturnVal    DMBase_SetDiaMsgTFlag( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                             HDIAMETERMESSAGE        hDiaMsg_o ,
                                             _Bool                       bFlagValue_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiameterStackContext_io is NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL == hDiaMsg_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " parameter hDiaMsg_o is NULL\n");
        return(DMBase_Retval_IncorrectParameters);
    }
    
    if( bFlagValue_i )
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags |= DMBASE_BITMASK_SET_MSG_T_FLAG;
	}
    else
	{ 
		(hDiaMsg_o->oDiaHeader).ucFlags &= DMBASE_BITMASK_CLEAR_MSG_T_FLAG ;
	}         

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    return	DMBase_Retval_Success; 
}
t_DiamAPIReturnVal  DMBase_ConvertDiameterMessageToRawForm (
									 HDIAMETERSTACKCONTEXT   hDiameterStackContext_io , 
                                     unsigned char **        ppRawDiameterMsg_o , 
                                     HDIAMETERMESSAGE       hDiaMsgHandle_i )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;

	if (NULL == hDiameterStackContext_io) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ERROR! hDiameterStackContext_io is NULL , leaving\n");
		oRetval =  DMBase_Retval_Null_Pointer;
		goto ExitMe;
	}

	if (NULL == hDiaMsgHandle_i) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ERROR! hDiaMsgHandle_i is NULL , leaving\n");
		oRetval =  DMBase_Retval_Null_Pointer;
		goto ExitMe;
	}

	if (NULL == ppRawDiameterMsg_o) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ERROR! ppRawDiameterMsg_o is NULL , leaving\n");
		oRetval =  DMBase_Retval_Null_Pointer;
		goto ExitMe;
	}

	if (NULL != *ppRawDiameterMsg_o) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ERROR! NULL != *ppRawDiameterMsg_o , leaving\n");
		oRetval =  DMBase_Retval_IncorrectParameters;
		goto ExitMe;
	}

	t_DiameterMessage*	poDiamMsg = (t_DiameterMessage*) hDiaMsgHandle_i ;

	



	unsigned int 	unMsgLength = 0;

     if (DMBase_Retval_Success !=  DMBase_GetDiaMsgLengthFromDiamMsg(hDiameterStackContext_io,
									   hDiaMsgHandle_i,&unMsgLength)
	  )
	  {
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_GetDiaMsgLengthFromDiamMsg  leaving\n");
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}
	
	

	if (DMBase_Retval_Success !=  DMBase_Malloc( hDiameterStackContext_io , 
									(void*) ppRawDiameterMsg_o , unMsgLength)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_Malloc FAILED  leaving\n");
		oRetval =  DMBase_Retval_MemNotAvailable;
		goto ExitMe;
	}

	unsigned char* pucTempBuff = *ppRawDiameterMsg_o;

	//writing the message header from the struct to buffer


	t_DiameterHeader oTempDiaHdr = poDiamMsg->oDiaHeader;
	unsigned int unCurrOffset = 0;

	//version one octet
	pucTempBuff[unCurrOffset ] = oTempDiaHdr.ucVersion;
	unCurrOffset++;

	//message length three octets

	unsigned char	pucTemp[3] = {0};
	if (DMBase_Retval_Success !=   DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder(
									oTempDiaHdr.unMessageLength,pucTemp)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder FAILED  leaving\n");
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}
	
	pucTempBuff[unCurrOffset ] = pucTemp[0];
	unCurrOffset++;

	pucTempBuff[unCurrOffset ] = pucTemp[1];
	unCurrOffset++;

	pucTempBuff[unCurrOffset ] = pucTemp[2];
	unCurrOffset++;

	//one octet of command flags
	pucTempBuff[unCurrOffset ] = oTempDiaHdr.ucFlags;
	unCurrOffset++;

	//three bytes of command code
	if (DMBase_Retval_Success !=   DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder(
									oTempDiaHdr.unCommandCode,pucTemp)
		)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder FAILED  leaving\n");
		oRetval =  DMBase_Retval_Failure;
		goto ExitMe;
	}
	pucTempBuff[unCurrOffset ] = pucTemp[0];
	unCurrOffset++;

	pucTempBuff[unCurrOffset ] = pucTemp[1];
	unCurrOffset++;

	pucTempBuff[unCurrOffset ] = pucTemp[2];
	unCurrOffset++;

	//four octets of applicationID
	unsigned int *	punTempIntPtr = NULL;
	punTempIntPtr = (unsigned int * ) ( pucTempBuff + unCurrOffset );
	//*punTempIntPtr = htonl( oTempDiaHdr.unApplicationID);
	if ( DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,oTempDiaHdr.unApplicationID,
											(unsigned long *) punTempIntPtr)
		 )
	{
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	unCurrOffset += 4;

	//four octets of Hop By Hop ID
	punTempIntPtr = (unsigned int * ) ( pucTempBuff + unCurrOffset );
	//*punTempIntPtr = htonl( oTempDiaHdr.unHopByHopID);
	if ( DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,oTempDiaHdr.unHopByHopID,
											(unsigned long *)punTempIntPtr)
		 )
	{
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	unCurrOffset += 4;

	//four octets of end to end ID
	punTempIntPtr = (unsigned int * ) ( pucTempBuff + unCurrOffset );
	//*punTempIntPtr = htonl( oTempDiaHdr.unEndToEndID);
	if ( DMBase_Retval_Success !=  DMBase_HostToNetworkLong(hDiameterStackContext_io,
											oTempDiaHdr.unEndToEndID,
											(unsigned long *)punTempIntPtr)
		 )
	{
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	unCurrOffset += 4;

	//now convert the AVPs 
	if ( DMBase_Retval_Success !=  DMBase_ConvertAVPCollectionToRawForm(
								   hDiameterStackContext_io , ppRawDiameterMsg_o ,
	 							   poDiamMsg->hCollectionOfAVPs , unCurrOffset)
		)
	{
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	ExitMe:

	if (DMBase_Retval_Success != oRetval) 
	{
		if (NULL != (*ppRawDiameterMsg_o)) 
		{
			//free mem
			if (DMBase_Retval_Success != DMBase_Free(hDiameterStackContext_io,
											(void**) ppRawDiameterMsg_o)
				)
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_Free Failed ! \n");
			}
		}//end if (NULL != (*ppRawDiameterMsg_o)) 
	}//end if (DMBase_Retval_Success != oRetval) 


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return oRetval;
}

t_DiamAPIReturnVal  DMBase_GetTotalSizeOfAllAVPsInCollection ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io , 
                                                     HAVPCOLLECTION	hCollOfAVPs_i, 
                                                     unsigned int* punTotalSize_o )
{
	unsigned int			unCurrIndex = 0;
	HAVP					hCurrAVP = NULL;
	unsigned int			unCurrAVPLength = 0;
	unsigned int			unTotalAVPsSize = 0;
	DMBase_SList*			pCurrentNode = (DMBase_SList*) hCollOfAVPs_i;
	void*					pData = NULL;	
	

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL , leaving ! \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == punTotalSize_o) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," punTotalSize_o is NULL , leaving ! \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hCollOfAVPs_i) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hCollOfAVPs_i is NULL , leaving ! \n");
		return DMBase_Retval_Null_Pointer;
	}

	  unsigned int				unPadLenForCurrAVP = 0;
	  _Bool						bIsCurrAVPGrouped = 0;
	  t_AVPDictionaryElement	oDicElem = {0};
	  unsigned int				unCurrAVPDataSize = 0;
      
	  while (NULL != pCurrentNode) 
	  {
		  unPadLenForCurrAVP = 0;

		  if (DMBase_Retval_Success != DMBase_SListGetNodeData(hDiameterStackContext_io,
										 pCurrentNode, &pData) )
		  {
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," FAILED , leaving ! \n");
			return DMBase_Retval_Failure;
		  }

		  hCurrAVP = ( HAVP) pData;
          t_DiamDictionary	oDictionary = {0};
	

			if ( DMBase_Retval_Success != DMBase_GetDictionaryObjectFromDiameterContext(
											hDiameterStackContext_io,&oDictionary)
			   )
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDictionaryObjectFromDiameterContext Failed , Leaving \n");
				return DMBase_Retval_Failure;
			}
		
			if ( 0 == DMBase_IsSafeToAccessDictElement(oDictionary.poDictionaryArray , 
													   hCurrAVP->oAVPHeaderInst.unAVPCode )
			   ) 
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_IsSafeToAccessDictElement Failed , Leaving \n");
				return DMBase_Retval_Failure;
			}

		  if (DMBase_Retval_Success !=  DMBase_IsAVPGrouped(hDiameterStackContext_io,
							  hCurrAVP->oAVPHeaderInst.unAVPCode,
							  &bIsCurrAVPGrouped) 
			  )
		  {
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," FAILED , leaving ! \n");
			return DMBase_Retval_Failure;
		  }

		  oDicElem = oDictionary.poDictionaryArray[hCurrAVP->oAVPHeaderInst.unAVPCode];

		  if (DMBase_Retval_Success !=  DMBase_GetAVPLengthFromAVPHeader(hDiameterStackContext_io,
																hCurrAVP,&unCurrAVPLength)
			 )
		  {
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_GetAVPLengthFromAVPHeader FAILED , leaving ! \n");
			return DMBase_Retval_Failure;
		  }
		  

		  if (0 == bIsCurrAVPGrouped ) 
		  {
			  _Bool		bNeedPadCheck = 0;

			  if (DMBase_Retval_Success !=  DMBase_IsTypeOctetStringOrDerived(hDiameterStackContext_io,
												hCurrAVP->oAVPHeaderInst.unAVPCode,
												&bNeedPadCheck )
				  )
			  {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," FAILED , leaving ! \n");
				return DMBase_Retval_Failure;
			  }

			  	if ( 1 == bNeedPadCheck )
				{
					if (DMBASE_AVP_V_BIT_IS_SET == (DMBASE_AVP_V_BIT_SET_MASK & (hCurrAVP->oAVPHeaderInst.ucFlags) ) ) 
					{
						unCurrAVPDataSize = unCurrAVPLength - DMBASE_AVP_HDR_SIZE_WITH_VNDR_ID_IN_BYTES;
					}
					else
					{
						unCurrAVPDataSize = unCurrAVPLength - DMBASE_AVP_HDR_SIZE_WITHOUT_VNDR_ID_IN_BYTES;
					}

					//check for padding requirement
					if ( 0 == (unCurrAVPDataSize % DMBASE_NUM_OF_OCTETS_IN_32BIT) ) 
					{
						unPadLenForCurrAVP = 0;
					}
					else
					{
						unPadLenForCurrAVP = DMBASE_NUM_OF_OCTETS_IN_32BIT - (unCurrAVPDataSize % DMBASE_NUM_OF_OCTETS_IN_32BIT); 
					}
				}
				else
				{
					unPadLenForCurrAVP = 0;
				}
		  }//end if AVP is not grouped
		  else
		  {
			  //for grouped case , padding is taken care of at add AVP to group time
			  unPadLenForCurrAVP = 0;
		  }
			 
		  unTotalAVPsSize  += unCurrAVPLength;
		  unTotalAVPsSize  += unPadLenForCurrAVP;
		  
		  if (DMBase_Retval_Success !=  DMBase_SListGetNextNode( 
									hDiameterStackContext_io , pCurrentNode , 
									&pCurrentNode)
			 )
		  {
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," FAILED , leaving ! \n");
				return DMBase_Retval_Failure;
		  }
	  }//end while

	  *punTotalSize_o = unTotalAVPsSize;
  

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DMBase_Retval_Success;
}

unsigned int DMBase_GenerateHopByHopId()
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    static unsigned int unHopByHopID = 0;
    
    return ++unHopByHopID;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

}

unsigned int DMBase_GenerateEndToEndId()
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    static unsigned int unEndToEndID = 0;
    
    return ++unEndToEndID;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

}

t_DiamAPIReturnVal DMBase_AddAVPToDiameterMessage ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                                        HDIAMETERMESSAGE  hDiaMsg_o ,
                                                        HAVP hAVPToAdd_i )  
{

  if ( NULL == hDiameterStackContext_io ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }
  
  if ( NULL == hDiaMsg_o ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }

  if ( NULL == hAVPToAdd_i ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hAVPToAdd_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }

  if ( NULL == hDiaMsg_o->hCollectionOfAVPs ) 
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o->hCollectionOfAVPs is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
  }
  
  unsigned int	unTotalAVPsSize = 0;

  if ( DMBase_Retval_Success !=  DMBase_GetTotalSizeOfAllAVPsInCollection(hDiameterStackContext_io, 
							hDiaMsg_o->hCollectionOfAVPs,&unTotalAVPsSize)
	  )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Function Failed ,Leaving \n");
	  return DMBase_Retval_Failure;
  }

  unsigned int	unDiamMsgLength = 0;

  if (DMBase_Retval_Success !=  DMBase_GetDiaMsgLengthFromDiamMsg(hDiameterStackContext_io,
									   hDiaMsg_o,&unDiamMsgLength)
	  )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_GetDiaMsgLengthFromDiamMsg Failed , Leaving \n");
	  return DMBase_Retval_Failure;
  }

  
  unsigned int unDiamMsgHeaderSize = unDiamMsgLength - unTotalAVPsSize;

  if ( DMBase_Retval_Success !=   DMBase_AddAVPToCollection(hDiameterStackContext_io,
								&(hDiaMsg_o->hCollectionOfAVPs),hAVPToAdd_i) 
	 )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Function Failed ,Leaving \n");
	  return DMBase_Retval_Failure;
  }

  

  unTotalAVPsSize = 0;

  if ( DMBase_Retval_Success !=   DMBase_GetTotalSizeOfAllAVPsInCollection(hDiameterStackContext_io, 
							hDiaMsg_o->hCollectionOfAVPs,&unTotalAVPsSize) )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Function Failed ,Leaving \n");
	  return DMBase_Retval_Failure;
  }


  unDiamMsgLength = unDiamMsgHeaderSize + unTotalAVPsSize;

  if (DMBase_Retval_Success !=  DMBase_SetDiaMsgLength(hDiameterStackContext_io,
							    hDiaMsg_o,unDiamMsgLength)
	  )
  {
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " DMBase_SetDiaMsgLength Failed , Leaving \n");
	  return DMBase_Retval_Failure;
  }

  return DMBase_Retval_Success ; 
}

t_DiamAPIReturnVal  DMBase_SetDiaMsgFlagOctet( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           unsigned char               ucFlagsVal_i    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}


	if ( NULL == hDiaMsg_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	hDiaMsg_o->oDiaHeader.ucFlags = ucFlagsVal_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	
	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_SetDiaMsgVersion( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_o ,
                                           unsigned char               ucVersion_i    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}


	if ( NULL == hDiaMsg_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	hDiaMsg_o->oDiaHeader.ucVersion = ucVersion_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetDiaMsgAppId( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o ,
                                           unsigned int			   unAppId_i    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}


	if ( NULL == hDiaMsg_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	hDiaMsg_o->oDiaHeader.unApplicationID = unAppId_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_SetDiaMsgLength( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o ,
                                           unsigned int			   unMsgLen_i    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}


	if ( NULL == hDiaMsg_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if (unMsgLen_i > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " unMsgLen_i = %d > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS \n",unMsgLen_i );
        return DMBase_Retval_IncorrectParameters ;   
    }

	hDiaMsg_o->oDiaHeader.unMessageLength = unMsgLen_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	
	
	return DMBase_Retval_Success;
}



t_DiamAPIReturnVal  DMBase_SetDiaMsgCmdCode( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_o ,
                                           unsigned int			   unCmdCode_i    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}


	if ( NULL == hDiaMsg_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if (unCmdCode_i > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS) 
	{
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " unCmdCode_i = %d > DMBASE_MAX_UNSIGNED_VAL_IN_3_OCTETS \n",unCmdCode_i );
        return DMBase_Retval_IncorrectParameters ;   
    }

	hDiaMsg_o->oDiaHeader.unCommandCode = unCmdCode_i;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	
	
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetHopByHopIDFromDiamMsg ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_i,
                                           unsigned int*  punDiaMsgHopByHopID_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == punDiaMsgHopByHopID_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punDiaMsgHopByHopID_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*punDiaMsgHopByHopID_o = hDiaMsg_i->oDiaHeader.unHopByHopID;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetEndToEndIDFromDiamMsg ( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io ,
                                           HDIAMETERMESSAGE            hDiaMsg_i ,
                                           unsigned int* punDiaMsgEndToEndID_o )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == punDiaMsgEndToEndID_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punDiaMsgEndToEndID_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*punDiaMsgEndToEndID_o = hDiaMsg_i->oDiaHeader.unEndToEndID;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}



t_DiamAPIReturnVal  DMBase_GetDiaMsgFlagOctetFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_i ,
                                           unsigned char*      pucFlagsVal_o    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == pucFlagsVal_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pucFlagsVal_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*pucFlagsVal_o = hDiaMsg_i->oDiaHeader.ucFlags;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_GetDiaMsgVersionFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE            hDiaMsg_i ,
                                           unsigned char*               pucVersion_o    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == pucVersion_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " pucVersion_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*pucVersion_o = hDiaMsg_i->oDiaHeader.ucVersion;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_GetDiaMsgAppIdFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_i ,
                                           unsigned int*			   punAppId_o    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == punAppId_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punAppId_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*punAppId_o = hDiaMsg_i->oDiaHeader.unApplicationID;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetDiaMsgLengthFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_i ,
                                           unsigned int*		punMsgLen_o    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    
	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == punMsgLen_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punMsgLen_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*punMsgLen_o = hDiaMsg_i->oDiaHeader.unMessageLength;
	

    
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_GetDiaMsgCmdCodeFromDiamMsg( HDIAMETERSTACKCONTEXT   hDiameterStackContext_io, 
                                           HDIAMETERMESSAGE        hDiaMsg_i ,
                                           unsigned int*			   punCmdCode_o    )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    
	if ( NULL == hDiameterStackContext_io ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiameterStackContext_io is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == hDiaMsg_i ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " hDiaMsg_i is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	if ( NULL == punCmdCode_o ) 
	{
	  DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " punCmdCode_o is NULL , Leaving \n");
	  return DMBase_Retval_Null_Pointer;
	}

	*punCmdCode_o = hDiaMsg_i->oDiaHeader.unCommandCode;

    
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal	DMBase_DuplicateDiameterMessage(HDIAMETERSTACKCONTEXT	hDiameterStackContext_io ,
							 HDIAMETERMESSAGE hOrignalMsg_i, HDIAMETERMESSAGE* phNewMsg_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hOrignalMsg_i ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hOrignalMsg_i is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phNewMsg_o ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! phNewMsg_o is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*phNewMsg_o) ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! (*phNewMsg_o) is NOT NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	t_DiamAPIReturnVal	oRetval = DMBase_Retval_Success;
	unsigned char*	pucTempBuff = NULL;

	if ( DMBase_Retval_Success !=  DMBase_ConvertDiameterMessageToRawForm(
						hDiameterStackContext_io,&pucTempBuff,hOrignalMsg_i)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ConvertDiameterMessageToRawForm Failed , Leaving \n");
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}

	if ( DMBase_Retval_Success !=   DMBase_ParseRawDiameterMessage(hDiameterStackContext_io,
										pucTempBuff,phNewMsg_o)
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_ParseRawDiameterMessage Failed , Leaving \n");
		oRetval = DMBase_Retval_Failure;
		goto ExitMe;
	}



	ExitMe:

	if (NULL != pucTempBuff) 
	{
		if ( DMBase_Retval_Success !=  DMBase_Free(hDiameterStackContext_io,(void**)&pucTempBuff))
		{
			DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," DMBase_Free Failed , Leaving \n");
        }
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return oRetval;


}

t_DiamAPIReturnVal  DMBase_AVP_Malloc ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                          HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io ,
										unsigned int	unAllocSize_i,
                                        void**	ppvMemBuff_o )  
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	if (NULL == hDiameterStackContext_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hMsgAllocCtxt_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hMsgAllocCtxt_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppvMemBuff_o ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! ppvMemBuff_o is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppvMemBuff_o) ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," (*ppvMemBuff_o) is NOT NULL , Leaving \n");
		return DMBase_Retval_IncorrectParameters;
	}

	if (0 == unAllocSize_i ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Nothing to do , zero allocation size requested , leaving \n");
		return DMBase_Retval_Success;
	}

	

	if ( (hMsgAllocCtxt_io->pucCurrPtr+unAllocSize_i)  >= 
		 (hMsgAllocCtxt_io->pucMemBlockForAVP + DMBASE_MEM_BLOCK_SIZE_FOR_AVP_ALLOCS ) 
	   )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Memory Not available for hMsgAllocCtxt_io -> 0x%x and unAllocSize_i == %d \n",hMsgAllocCtxt_io,unAllocSize_i);
		return DMBase_Retval_MemNotAvailable;
	}

	*ppvMemBuff_o = (void*) hMsgAllocCtxt_io->pucCurrPtr;

	(hMsgAllocCtxt_io->pucCurrPtr) += unAllocSize_i;


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal  DMBase_AVP_Free ( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                       HMSGALLOCATIONCONTEXT	hMsgAllocCtxt_io ,
									  void**	ppvMemToFree_i	)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	void*	pvMemToFree = NULL;


	if (NULL == hDiameterStackContext_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hMsgAllocCtxt_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hMsgAllocCtxt_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppvMemToFree_i ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! ppvMemToFree_i is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == (*ppvMemToFree_i) ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! *ppvMemToFree_i is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	pvMemToFree = *ppvMemToFree_i;

	if ((unsigned char* )pvMemToFree < hMsgAllocCtxt_io->pucMemBlockForAVP) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Something is WRONG , pvMemToFree is BELOW the mem block range !!. Leaving \n");
		return DMBase_Retval_Failure;
	}

	if ((unsigned char* )pvMemToFree > ( hMsgAllocCtxt_io->pucMemBlockForAVP + DMBASE_MEM_BLOCK_SIZE_FOR_AVP_ALLOCS) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Something is WRONG , pvMemToFree is ABOVE the mem block range !!. Leaving \n");
		return DMBase_Retval_Failure;
	}

	*ppvMemToFree_i = NULL;
	//Free is a NO-OP For NOW , nothing to do


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DMBase_Retval_Success;
}
t_DiamAPIReturnVal  DMBase_Get_AllocationContext_ForMessage( 
									HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                     HDIAMETERMESSAGE  hDiaMsg_i,
									HMSGALLOCATIONCONTEXT*	phMsgAllocCtxt_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	if (NULL == hDiameterStackContext_io ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiameterStackContext_io is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hDiaMsg_i ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! hDiaMsg_o is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phMsgAllocCtxt_o ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! phMsgAllocCtxt_o is NULL , Leaving \n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*phMsgAllocCtxt_o) ) 
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error ! (*phMsgAllocCtxt_o) is NOT NULL , Leaving \n");
		return DMBase_Retval_IncorrectParameters;
	}

	*phMsgAllocCtxt_o = &(hDiaMsg_i->oMemBlockForAVPs);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DMBase_Retval_Success;
}

