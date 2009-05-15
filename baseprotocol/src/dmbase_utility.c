#include "dmbase_utility.h"
#include "dmbase_ampswrappers.h"
#include <string.h>

extern int g_nDiamBaseTraceID;

#define	DMBASE_ARCH_LITTLE_ENDIAN //currently on Intel Arch


/******************************************************************************
** Function Name:
**			DMBase_GetDiamStrLength
**
** Description:
**		This function calculates string length of t_DiamOctetString.
**
** Parameters:
**		 int* pnLength_io,
**			 type: input/output
**			 detail : This is a pointer to interger. It will store
**                                Length of string.
**
**		 t_DiamOctetString*    poDiamString_i
**			type: input
**			detail: this is a pointer of t_DiamOctetString.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether string length is
**		calculated successfully or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_GetDiamStrLength ( int*                  pnLength_io,
                                      t_DiamOctetString*    poDiamString_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == pnLength_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamString_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamString_i->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    *pnLength_io = strlen(poDiamString_i->pucOctetString);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;

}

/******************************************************************************
** Function Name:
**			DMBase_CopyDiamString
**
** Description:
**		This function copies t_DiamOctetString string
**
** Parameters:
**		 t_DiamOctetString*   poDiamStringDest_io,
**			 type: input/output
**			 detail : This is a pointer to t_DiamOctetString
**                                destination object.
**
**		 t_DiamOctetString*   poDiamStringSource_i
**			type: input
**			detail: This is a pointer to t_DiamOctetString
**                              source object.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether string copy process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_CopyDiamString(t_DiamOctetString*   poDiamStringDest_io,
                                  t_DiamOctetString*   poDiamStringSource_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == poDiamStringDest_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL != poDiamStringDest_io->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"  pointer is not NULL \n");
        return DMBase_Retval_IncorrectParameters;
    }

    if(NULL == poDiamStringSource_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamStringSource_i->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    int nSize = 0;

    DMBase_GetDiamStrLength(&nSize,poDiamStringSource_i);

    if(DMBase_Retval_Success != DMBase_Malloc(NULL,(void**)&(poDiamStringDest_io->pucOctetString), nSize+1))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }

    strcpy(poDiamStringDest_io->pucOctetString,poDiamStringSource_i->pucOctetString);
	poDiamStringDest_io->unNumOfOctets = poDiamStringSource_i->unNumOfOctets;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_CopyDiamStringAssumeNoNullTerm ( t_DiamOctetString*  poDiamStringDest_io,
                                           t_DiamOctetString*  poDiamStringSource_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == poDiamStringDest_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL != poDiamStringDest_io->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"  pointer is not NULL \n");
        return DMBase_Retval_IncorrectParameters;
    }

    if(NULL == poDiamStringSource_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamStringSource_i->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    

    if(DMBase_Retval_Success != DMBase_Malloc(NULL,(void**)&(poDiamStringDest_io->pucOctetString),
											   poDiamStringSource_i->unNumOfOctets))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }

    memcpy(poDiamStringDest_io->pucOctetString,poDiamStringSource_i->pucOctetString,
		   poDiamStringSource_i->unNumOfOctets);

	poDiamStringDest_io->unNumOfOctets = poDiamStringSource_i->unNumOfOctets;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_AppendDiamStringToDiamString
**
** Description:
**		This function append two t_DiamOctetString strings
**
** Parameters:
**		 t_DiamOctetString*   poDiamStringDest_io,
**			 type: input/output
**			 detail : This is a pointer to t_DiamOctetString
**                                destination object.
**
**		 t_DiamOctetString*   poDiamStringSource_i
**			type: input
**			detail: This is a pointer to t_DiamOctetString
**                              source object.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether string appending process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_AppendDiamStringToDiamString ( t_DiamOctetString*   poDiamStringDest_io,
                                                  t_DiamOctetString*   poDiamStringSource_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");
    if(NULL == poDiamStringDest_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamStringSource_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamStringDest_io->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamStringSource_i->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    int nDestSize = 0;
    int nSourceSize = 0;

    DMBase_GetDiamStrLength(&nDestSize,poDiamStringDest_io);
    DMBase_GetDiamStrLength(&nSourceSize,poDiamStringSource_i);

    poDiamStringDest_io->pucOctetString = realloc(poDiamStringDest_io->pucOctetString,nDestSize+nSourceSize+1);

    strcat(poDiamStringDest_io->pucOctetString, poDiamStringSource_i->pucOctetString);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_AppendCharStringToDiamString
**
** Description:
**		This function append t_DiamOctetString string and char string
**
** Parameters:
**		 t_DiamOctetString*   poDiamStringDest_io
**			 type: input/output
**			 detail : This is a pointer to t_DiamOctetString
**                                destination object.
**
**		 t_DiamOctetString*   pcStringSource_i
**			type: input
**			detail: This is a pointer to char source string.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether string appending process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_AppendCharStringToDiamString ( t_DiamOctetString*     poDiamStringDest_io,
                                                         char*                  pcStringSource_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == poDiamStringDest_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL == pcStringSource_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDiamStringDest_io->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }


    int nDestSize = 0;
    int nSourceSize = 0;

    DMBase_GetDiamStrLength(&nDestSize,poDiamStringDest_io);
    nSourceSize = strlen(pcStringSource_i);

    poDiamStringDest_io->pucOctetString = realloc(poDiamStringDest_io->pucOctetString,nDestSize+nSourceSize+1);

    strcat(poDiamStringDest_io->pucOctetString, pcStringSource_i);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}



int DMBase_CompareDiamString ( t_DiamOctetString* pDiamString1,
                               t_DiamOctetString* pDiamString2)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == pDiamString1)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pDiamString2)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pDiamString1->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pDiamString2->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(pDiamString1->unNumOfOctets != pDiamString2->unNumOfOctets)
    {
        return DMBase_Retval_Insufficient_Buffer;
    }
    int nCmpResult = memcmp(pDiamString1->pucOctetString,
                            pDiamString2->pucOctetString,
                            pDiamString1->unNumOfOctets);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return nCmpResult;
}

/******************************************************************************
** Function Name:
**			DMBase_DeleteDiamString
**
** Description:
**		This function deletes t_DiamOctetString string.
**
** Parameters:
**		 t_DiamOctetString*   pDiamString_i
**			 type: input
**			 detail : This is a pointer to t_DiamOctetString  object.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether string deletion process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_DeleteDiamString(t_DiamOctetString *pDiamString_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");
    if(NULL == pDiamString_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pDiamString_i->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    free(pDiamString_i->pucOctetString);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_IntToDiamString
**
** Description:
**		This function converts integer to t_DiamOctetString string.
**
** Parameters:
**
**               int    nNumber_i
**                      type: input
**                      detail: This is an integer number.
**
**		 t_DiamOctetString*   pDiamString_io
**                      type: input/output
**			detail: This is a pointer to t_DiamOctetString  object.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether conversion process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_IntToDiamString ( int                    nNumber_i,
                                            t_DiamOctetString*     poDiamString_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == poDiamString_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(DMBase_Retval_Success != DMBase_Malloc(NULL,(void**)&(poDiamString_io->pucOctetString), 30))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }



    sprintf(poDiamString_io->pucOctetString, "%d", nNumber_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_FloatToDiamString
**
** Description:
**		This function converts float to t_DiamOctetString string.
**
** Parameters:
**
**               float    fNumber_i
**                      type: input
**                      detail: This is an floating point number.
**
**		 t_DiamOctetString*   pDiamString_io
**                      type: input/output
**			detail: This is a pointer to t_DiamOctetString  object.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether conversion process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_FloatToDiamString ( float                 fNumber_i,
                                              t_DiamOctetString*    poDiamString_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");
    if(NULL == poDiamString_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

 /*   if(NULL == poDiamString->pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }*/

    if(DMBase_Retval_Success != DMBase_Malloc(NULL,(void**)&(poDiamString_io->pucOctetString), 30))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }

    sprintf(poDiamString_io->pucOctetString,"%f",fNumber_i);
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_BoolToDiamString
**
** Description:
**		This function converts bool to t_DiamOctetString string.
**
** Parameters:
**
**               _Bool    bFlag_i
**                      type: input
**                      detail: This is a bool variable.
**
**		 t_DiamOctetString*   pDiamString_io
**                      type: input/output
**			detail: This is a pointer to t_DiamOctetString  object.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether conversion process
**		successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_BoolToDiamString ( _Bool                 bFlag_i,
                                             t_DiamOctetString*    poDiamString_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == poDiamString_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(DMBase_Retval_Success != DMBase_Malloc(NULL,(void**)&(poDiamString_io->pucOctetString), 30))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }



    sprintf(poDiamString_io->pucOctetString, "%d", bFlag_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;

}

/******************************************************************************
** Function Name:
**			DMBase_MemsetZero
**
** Description:
**		This function fill memory with zeros.
**
** Parameters:
**
**               void* pvMemorypointer_io
**                     type: input/output
**                     detail: This is pointer to void memory.
**
**		 int nSize_i
**                     type: input
**                     detail: This is an integer variable.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether memory filling
**		process successfully completed or any problem occured.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_MemsetZero( void*  pvMemorypointer_io ,int nSize_i)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == memset(pvMemorypointer_io, '\0', nSize_i))
    {
         DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " Memset problem\n");
         return DMBase_Retval_Failure;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

inline unsigned int 	DMBase_Convert3BytesToUInt( unsigned char * puc3Bytes_i)
{
	unsigned int	unRetVal = 0;
	int 			nCurrIndex =0;


	unsigned char * pucTemp = ( unsigned char * )  &unRetVal;


	for (nCurrIndex=0 ; nCurrIndex<3 ; nCurrIndex++)
	{
		*( pucTemp + nCurrIndex)  = puc3Bytes_i[nCurrIndex];

	}

	return unRetVal;
}

t_DiamAPIReturnVal DMBase_CopyCharArrayToDiamString(t_DiamOctetString *poDiamStringDest ,char* pcSrcBuff)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == poDiamStringDest)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid poDiamStringDest pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pcSrcBuff)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Invalid pcSrcBuff pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

    int nSrcSize = 0;

    nSrcSize = strlen( pcSrcBuff ) ;

    if(DMBase_Retval_Success != DMBase_Malloc(NULL,(void**)&(poDiamStringDest->pucOctetString), nSrcSize+1))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occured while allocating memory \n");
        return DMBase_Retval_Failure;
    }

    strcpy(poDiamStringDest->pucOctetString,pcSrcBuff);
	poDiamStringDest->unNumOfOctets = nSrcSize;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

inline t_DiamAPIReturnVal 	DMBase_ConvertUIntTo3BytesAndFromHostToNetOrder(
														unsigned int unToConvert_i ,
														unsigned char * puc3Bytes_o)
{

	if (NULL == puc3Bytes_o)
	{
		return DMBase_Retval_Null_Pointer;
	}

	if (DMBase_Retval_Success != DMBase_ConvertUIntTo3Bytes( unToConvert_i , puc3Bytes_o)
	   )
	{
		return DMBase_Retval_Failure;
	}

	if (DMBase_Retval_Success != DMBase_Convert3ByteFromHtoN_Order(puc3Bytes_o)
	   )
	{
		return DMBase_Retval_Failure;
	}


	return DMBase_Retval_Success;


}

inline t_DiamAPIReturnVal 	DMBase_ConvertUIntTo3BytesAndFromNetToHostOrder(
														unsigned int unToConvert_i ,
														unsigned char * puc3Bytes_o)
{

	if (NULL == puc3Bytes_o)
	{
		return DMBase_Retval_Null_Pointer;
	}

	if (DMBase_Retval_Success != DMBase_ConvertUIntTo3Bytes( unToConvert_i , puc3Bytes_o)
	   )
	{
		return DMBase_Retval_Failure;
	}

	if (DMBase_Retval_Success != DMBase_Convert3ByteFromNtoH_Order(puc3Bytes_o)
	   )
	{
		return DMBase_Retval_Failure;
	}


	return DMBase_Retval_Success;


}

inline t_DiamAPIReturnVal 	DMBase_ConvertUIntTo3Bytes( unsigned int unToConvert_i ,
														unsigned char * puc3Bytes_o)
{
	int 			nCurrIndex =0;

	if (NULL == puc3Bytes_o)
	{
		return DMBase_Retval_Null_Pointer;
	}

	unsigned char * pucTemp = ( unsigned char * )  &unToConvert_i;


	for (nCurrIndex=0 ;  nCurrIndex<3 ; nCurrIndex++)
	{
		 puc3Bytes_o[nCurrIndex] = *( pucTemp + nCurrIndex );
	}

	return DMBase_Retval_Success;
}

inline t_DiamAPIReturnVal	DMBase_Convert3ByteFromHtoN_Order(
									unsigned char * puc3Bytes_io )
{

	if (NULL == puc3Bytes_io)
	{
		return DMBase_Retval_Null_Pointer;
	}

	// Network byte order is Big Endian , converting to Big Endian Order

	#ifdef	DMBASE_ARCH_BIG_ENDIAN

	//no need to do anything

	#endif

	#ifdef  DMBASE_ARCH_LITTLE_ENDIAN

	unsigned char	pucForSwap[3] = {0};
	int				nCurrIndex = 0;

	for (nCurrIndex=2; nCurrIndex >= 0 ; nCurrIndex--)
	{
		pucForSwap[nCurrIndex] = puc3Bytes_io[ 2-nCurrIndex];
	}

	puc3Bytes_io[0] = pucForSwap[0];
	puc3Bytes_io[1] = pucForSwap[1];
	puc3Bytes_io[2] = pucForSwap[2];


	#endif


	return DMBase_Retval_Success;
}

inline t_DiamAPIReturnVal	DMBase_Convert3ByteFromNtoH_Order(
									unsigned char * puc3Bytes_io )
{
	if (NULL == puc3Bytes_io)
	{
		return DMBase_Retval_Null_Pointer;
	}

	//network byte order is big endian


	#ifdef	DMBASE_ARCH_BIG_ENDIAN

		//no need to do anything

	#endif

	#ifdef   DMBASE_ARCH_LITTLE_ENDIAN

	unsigned char	pucForSwap[3] = {0};
	int				nCurrIndex = 0;

	for (nCurrIndex=2; nCurrIndex >= 0 ; nCurrIndex--)
	{
		pucForSwap[nCurrIndex] = puc3Bytes_io[ 2-nCurrIndex];
	}

	puc3Bytes_io[0] = pucForSwap[0];
	puc3Bytes_io[1] = pucForSwap[1];
	puc3Bytes_io[2] = pucForSwap[2];


	#endif

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_IsDiamStringEmpty ( t_DiamOctetString     oDiamStringDest_i,
                                              _Bool*	pbIsStringEmpty_o           )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == pbIsStringEmpty_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pbIsStringEmpty_o is NULL , leaving\n");
		return DMBase_Retval_Failure;
	}

	*pbIsStringEmpty_o = ( NULL == oDiamStringDest_i.pucOctetString) ;

	return DMBase_Retval_Success;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
}


inline	t_DiamAPIReturnVal 	DMBase_GiveUIntInNetOrderFor3Bytes(
							unsigned char * puc3Bytes_i , unsigned int* punInt_o)
{
	unsigned char	pucTemp[3] = {0};
	unsigned int	unTemp = 0;

	if ( (NULL==puc3Bytes_i) || (NULL==punInt_o) )
	{
		return DMBase_Retval_Null_Pointer;
	}

	pucTemp[0] = puc3Bytes_i[0];
	pucTemp[1] = puc3Bytes_i[1];
	pucTemp[2] = puc3Bytes_i[2];


	if ( DMBase_Retval_Success !=  DMBase_Convert3ByteFromHtoN_Order(pucTemp) )
	{
		return DMBase_Retval_Failure;
	}

	unTemp = DMBase_Convert3BytesToUInt(pucTemp);

	*punInt_o = unTemp;


	return DMBase_Retval_Success;

}


inline	t_DiamAPIReturnVal 	DMBase_GiveUIntInHostOrderFor3Bytes(
							 unsigned char * puc3Bytes_i , unsigned int* punInt_o)
{
	unsigned char	pucTemp[3] = {0};
	unsigned int	unTemp = 0;

	if ( (NULL==puc3Bytes_i) || (NULL==punInt_o) )
	{
		return DMBase_Retval_Null_Pointer;
	}

	pucTemp[0] = puc3Bytes_i[0];
	pucTemp[1] = puc3Bytes_i[1];
	pucTemp[2] = puc3Bytes_i[2];


	if ( DMBase_Retval_Success !=  DMBase_Convert3ByteFromNtoH_Order(pucTemp) )
	{
		return DMBase_Retval_Failure;
	}

	unTemp = DMBase_Convert3BytesToUInt(pucTemp);

	*punInt_o = unTemp;


	return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_SetStringInHashTableKey( t_DiamHashTableKey*	poHashTableKey_io,
		                                                 unsigned char*		pucStringContent_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if(NULL == poHashTableKey_io || NULL == pucStringContent_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL Pointer not allowed\n");
		return DMBase_Retval_Null_Pointer;
	}

    DMBase_MemsetZero(poHashTableKey_io, sizeof(t_DiamHashTableKey));
    memcpy(poHashTableKey_io->puchKey, pucStringContent_i, strlen(pucStringContent_i));
    poHashTableKey_io->unKeyLength = strlen(pucStringContent_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_SetIntegerInHashTableKey( t_DiamHashTableKey*	poHashTableKey_io,
		                                                 unsigned int			unContent_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if(NULL == poHashTableKey_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL Pointer not allowed\n");
		return DMBase_Retval_Null_Pointer;
	}

    DMBase_MemsetZero(poHashTableKey_io, sizeof(t_DiamHashTableKey));

    sprintf(poHashTableKey_io->puchKey, "%d", unContent_i);
    poHashTableKey_io->unKeyLength = strlen(poHashTableKey_io->puchKey);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;

}


int DMBase_CopyDiamStrToCharArray(unsigned char *pucDest, t_DiamOctetString oSrcDiamStr)
{
    memcpy(pucDest, oSrcDiamStr.pucOctetString, oSrcDiamStr.unNumOfOctets);
    pucDest[oSrcDiamStr.unNumOfOctets] = '\0';
    return oSrcDiamStr.unNumOfOctets;
}

int DMBase_CopyDiamStrToNSizedCharArray(unsigned char       *pucDest,
                                        unsigned int        unDestCharArraySize,
                                        t_DiamOctetString   oSrcDiamStr)
{
	if(NULL == oSrcDiamStr.pucOctetString || NULL == pucDest)
	{
		return 0;
	}

    int nStrSize = oSrcDiamStr.unNumOfOctets;

    if(nStrSize > unDestCharArraySize-1)
    {
        nStrSize = unDestCharArraySize-1;
    }

    memcpy(pucDest, oSrcDiamStr.pucOctetString, nStrSize);
    pucDest[nStrSize] = '\0';
    return nStrSize;
}

int DMBase_CopyNChar(unsigned char *pucDest, unsigned char *pucSrc, unsigned int unCount)
{
    memcpy(pucDest, pucSrc, unCount);
    pucDest[unCount] = '\0';
    return unCount;
}

int DMBase_CopyNCharToNCharArray(unsigned char *pucDest_o, unsigned int unDestSize_i, unsigned char *pucSrc_i, unsigned int unCount_i)
{

	if(NULL == pucDest_o || NULL == pucSrc_i)
	{
		return 0;
	}
	int nStrSize = unCount_i;

	if(nStrSize > unDestSize_i-1)
	{
		nStrSize = unDestSize_i-1;
	}

	memcpy(pucDest_o, pucSrc_i, nStrSize);
	pucDest_o[nStrSize] = '\0';

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    return nStrSize;
}

t_DiamAPIReturnVal DMBase_HostToNetworkLongLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long long ullToConvert_i,
											  unsigned long long * pullConvertedLong_o)
{
	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pullConvertedLong_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pullConvertedLong_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	//network byte order is big endian


	#ifdef	DMBASE_ARCH_BIG_ENDIAN

		//no need to do anything

	#endif

	#ifdef   DMBASE_ARCH_LITTLE_ENDIAN

    

	unsigned long long ullTemp=0;
	unsigned long ulTemp1=0;
	unsigned long ulTemp2=0;

	ulTemp1 = (unsigned long )((ullToConvert_i << 32) >> 32);
	if ( DMBase_Retval_Success != DMBase_NetworkToHostLong(hDiameterContext_io,
										ulTemp1,&ulTemp2))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_NetworkToHostLong Failed , leaving\n");
        return DMBase_Retval_Failure;
	}

	ullTemp = (unsigned long long ) ulTemp2;
	ullTemp <<= 32;

	ulTemp1 = ulTemp2 = 0;

	ulTemp1 = (unsigned long )(ullToConvert_i  >> 32);
	if ( DMBase_Retval_Success != DMBase_NetworkToHostLong(hDiameterContext_io,
										ulTemp1,&ulTemp2))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_NetworkToHostLong Failed , leaving\n");
        return DMBase_Retval_Failure;
	}

	ullTemp |= (unsigned long) ulTemp2;

	
	*pullConvertedLong_o = ullTemp;


	/*


	unsigned char*		pucTemp = NULL;
	unsigned char*		pucTemp1 = NULL;
	int					nCurrIndex = 0;
	unsigned long long	ullTemp = 0;

	pucTemp = (unsigned char*) &ullToConvert_i;
	pucTemp += 7; //reach the MSB of long long

	pucTemp1 = (unsigned char*) &ullTemp; //pointing to LSB of returned long long


	for (nCurrIndex=7; nCurrIndex >= 0 ; nCurrIndex--)
	{
        pucTemp1[7-nCurrIndex] = pucTemp[nCurrIndex];
	}

	*pullConvertedLong_o = ullTemp;

	*/

	#endif


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");

	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_NetworkToHostLongLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long long ullToConvert_i,
											  unsigned long long * pullConvertedLong_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering \n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pullConvertedLong_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pullConvertedLong_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

		//network byte order is big endian


	#ifdef	DMBASE_ARCH_BIG_ENDIAN

		//no need to do anything

	#endif

	#ifdef   DMBASE_ARCH_LITTLE_ENDIAN

	unsigned long long ullTemp=0;
	unsigned long ulTemp1=0;
	unsigned long ulTemp2=0;

	ulTemp1 = (unsigned long )((ullToConvert_i << 32) >> 32);
	if ( DMBase_Retval_Success != DMBase_NetworkToHostLong(hDiameterContext_io,
										ulTemp1,&ulTemp2))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_NetworkToHostLong Failed , leaving\n");
        return DMBase_Retval_Failure;
	}

	ullTemp = (unsigned long long ) ulTemp2;
	ullTemp <<= 32;

	ulTemp1 = ulTemp2 = 0;

	ulTemp1 = (unsigned long )(ullToConvert_i  >> 32);
	if ( DMBase_Retval_Success != DMBase_NetworkToHostLong(hDiameterContext_io,
										ulTemp1,&ulTemp2))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"DMBase_NetworkToHostLong Failed , leaving\n");
        return DMBase_Retval_Failure;
	}

	ullTemp |= (unsigned long) ulTemp2;

	
	*pullConvertedLong_o = ullTemp;

	/*
	unsigned char*		pucTemp = NULL;
	unsigned char*		pucTemp1 = NULL;
	int					nCurrIndex = 0;
	unsigned long long	ullTemp = 0;

	pucTemp = (unsigned char*) &ullToConvert_i;
	pucTemp += 7; //reach the MSB of long long

	pucTemp1 = (unsigned char*) &ullTemp; //pointing to LSB of returned long long


	for (nCurrIndex=7; nCurrIndex >= 0 ; nCurrIndex--)
	{
        pucTemp1[7-nCurrIndex] = pucTemp[nCurrIndex];
	}

	*pullConvertedLong_o = ullTemp;
	*/

	#endif

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");

	return DMBase_Retval_Success;

}
