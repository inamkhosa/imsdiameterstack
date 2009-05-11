#include "AMPS_API.h"
#include "dmbase_utility.h"

#include "dmbase_transport_mgmt.h"
#include "dmbase_ampswrappers.h"

extern int g_nDiamBaseTraceID ;

/******************************************************************************
** Function Name:
**			DMBase_AppendSList
**
** Description:
**		This function appends node to the link list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 DMBase_SList** ppSList_io
**			type: input/output
**			detail: this is a pointer to a pointer which points
**				to start of list.
**
**		 void* pvData_i
**			type: input
**			detail: this is a pointer to data which is to be appended
**				to list.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data appended to list
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_AppendSList(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
									   DMBase_SList** ppSList_io, void* pvData_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppSList_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppSList_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pvData_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pvData_i is NULL\n");
        return DMBase_Retval_Null_Pointer;
	}

    if(AMPS_SUCCESS != AMPS_SListAppend((void**) ppSList_io, pvData_i, NULL))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem in Appendinf note to Link List\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_RemoveSListNodeWithOutFree(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
									 DMBase_SList** ppSList_io, DMBase_SList* poSListNode)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppSList_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppSList_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == poSListNode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," poSListNode is NULL\n");
        return DMBase_Retval_Null_Pointer;
	}

	t_DiamAPIReturnVal	oRetVal  = DMBase_Retval_Failure;

    if ( AMPS_SUCCESS !=   AMPS_SListRemoveWithOutFree(ppSList_io, poSListNode))
	{
		oRetVal = DMBase_Retval_Failure;
	}
	else
	{
		oRetVal = DMBase_Retval_Success;
	}

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    return oRetVal;
}

t_DiamAPIReturnVal DMBase_SListCount(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
									 DMBase_SList* pSList_io ,
									  unsigned int* punCount)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pSList_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pSList_io is NULL\n");
		return DMBase_Retval_Null_Pointer;
	}


	if (NULL == punCount)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," punCount is NULL\n");
		return DMBase_Retval_Null_Pointer;
	}


    *punCount = AMPS_SListCount((const DMBase_SList*)pSList_io);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SListGetNodeData
**
** Description:
**		This function returns data from node.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  void* pvNode_i
**			type: input
**			detail: this is a pointer to node.
**
**		 void** ppvData_io
**			type: input/output
**			detail: this is a pointer to a pointer which points to
**			data of the node.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data is extracted
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SListGetNodeData(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
										    void* pvNode_i, void** ppvData_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pvNode_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pvNode_i is NULL\n");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppvData_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppvData_io is NULL\n");
		return DMBase_Retval_Null_Pointer;
	}


    *ppvData_io = AMPS_SListGetNodeData(pvNode_i);

    if(NULL == *ppvData_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," No data available\n ");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_Malloc
**
** Description:
**		This function allocates memory for given size.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  void**  ppMemoryPointer_io
**			type: input/output
**			detail: this is a pointer to a pointer which points to
**				memory which allocated by this function.
**
**		 int nSize_i
**			type: input
**			detail: this is a size of the memory to be allocated.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether memory allocated
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_Malloc( HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
								   void**  ppMemoryPointer_io ,int nSize_i)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

/*	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL == ppMemoryPointer_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppMemoryPointer_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != *ppMemoryPointer_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," *ppMemoryPointer_io is not NULL , it should be NULL\n");
        return DMBase_Retval_IncorrectParameters;
    }*/

    *ppMemoryPointer_io = AMPS_Malloc(nSize_i);

    if (NULL == *ppMemoryPointer_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occurred while allocating memory\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_Free(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
							   void** ppMemoryPointer_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

/*
	if(NULL == hDiameterStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
    }
*/
    if(NULL == ppMemoryPointer_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppMemoryPointer_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL == *ppMemoryPointer_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," *ppMemoryPointer_io is NULL\n");
        return DMBase_Retval_Null_Pointer;
    }

    AMPS_Free(*ppMemoryPointer_io);
	*ppMemoryPointer_io = NULL;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}
/******************************************************************************
** Function Name:
**			DMBase_CreateHashTable
**
** Description:
**		This function creates hash table.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  int nSizeOfHashTable_i
**			type: input
**			detail: this is size of hash table to be created.
**
**		 DMBASE_HASH_HANDLE* pHashTableHandle_o
**			type: output
**			detail: this is pointer to newly created hash table
**				handle.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether hash table created
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_CreateHashTable(HDIAMETERSTACKCONTEXT			hDiameterStackContext_io,
										  int							nSizeOfHashTable_i,
										  DMBASE_HASH_HANDLE* 			pHashTableHandle_o,
										  DMBase_HashTableHashCallback	pfHashTableCallback)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pHashTableHandle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pHashTableHandle_o is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL != *pHashTableHandle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," *pHashTableHandle_o is NOT NULL, it should be NULL \n ");
        return DMBase_Retval_IncorrectParameters;
	}

    *pHashTableHandle_o = AMPS_HashTableCreate(hDiameterStackContext_io->hFrameworkHandle,
												 nSizeOfHashTable_i, pfHashTableCallback);

    if (NULL == *pHashTableHandle_o )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Problem occurred while creating Hash table\n ");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_HashTableInsert
**
** Description:
**		This function insert item in hash table.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBASE_HASH_HANDLE hHashTableHandle_o
**			type: input/output
**			detail: this is hash table handle.
**
**		 void* pvData_i
**			type: input
**			detail: this is pointer to data which is to be inserted
**				in hash table.
**
**		 DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i
**			type: input
**			detail: This is handle of hash key used to insert data
**				in hash table.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data is iserted
**		successfully in hash table or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_HashTableInsert(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
							DMBASE_HASH_HANDLE hHashTableHandle_o, void* pvData_i,
								 DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hHashTableHandle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hHashTableHandle_o is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pvData_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pvData_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hHashKey_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hHashKey_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

    int nHashReturn = AMPS_HashTableInsert (hDiameterStackContext_io->hFrameworkHandle,
											hHashTableHandle_o, pvData_i, hHashKey_i);


    if (AMPS_INVALID_HANDLE == nHashReturn)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, "Insertion Failed\n");

        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_HashTableSearch
**
** Description:
**		This function search data from hash table against hash
**		key.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBASE_HASH_HANDLE hHashTableHandle_o
**			type: input/output
**			detail: this is hash table handle.
**
**		 DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i
**			type: input
**			detail: This is handle of hash key used to search data
**				from hash table.
**		 void** ppvData_o
**			type: output
**			detail: this is pointer to a pointer which points to
**				data which is searched from hash table.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data is searched
**		successfully from hash table or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_HashTableSearch(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
							DMBASE_HASH_HANDLE hHashTableHandle_o,
							DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i, void** ppvData_o)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hHashTableHandle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hHashTableHandle_o is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hHashKey_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hHashKey_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppvData_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppvData_o is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL != (*ppvData_o) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," *ppvData_o is NOT  NULL \n ");
        return DMBase_Retval_IncorrectParameters;
	}

    *ppvData_o = AMPS_HashTableSearch(hDiameterStackContext_io->hFrameworkHandle,
									  hHashTableHandle_o, hHashKey_i);

    if(NULL == (*ppvData_o) )
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Item not found.\n");
        return DMBase_Retval_Not_Found;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_HashTableRemove
**
** Description:
**		This function remove data from hash table against hash
**		key.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBASE_HASH_HANDLE hHashTableHandle_o
**			type: input/output
**			detail: this is hash table handle.
**
**		 DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i
**			type: input
**			detail: This is handle of hash key used to remove data
**				from hash table.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data is removed
**		successfully from hash table or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_HashTableRemove(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
										  DMBASE_HASH_HANDLE hHashTableHandle_o,
										   DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hHashTableHandle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hHashTableHandle_o is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hHashKey_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hHashKey_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

    if(AMPS_SUCCESS != AMPS_HashTableRemoveByKey(hDiameterStackContext_io->hFrameworkHandle,
												 hHashTableHandle_o, hHashKey_i))
    {

        DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " A Problem Occurred while removing data from Hash Table.\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_CreateHashTableKey
**
** Description:
**		This function creates hash key.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  t_DiamOctetString StrHashkey_i
**			type: input/output
**			detail: this is hash key value.
**
**		 DMBASE_HASHTABLE_KEY_HANDLE* phHashKeyHandle_o
**			type: input
**			detail: This is a pointer to handle of newly created hash
**				key.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether hash key
**		successfully created or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_CreateHashTableKey(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											t_DiamOctetString StrHashkey_i,
											DMBASE_HASHTABLE_KEY_HANDLE* phHashKeyHandle_o)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    t_AMPSHashTableKey *pHASHTableKey = NULL;

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == phHashKeyHandle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," phHashKeyHandle_o is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (StrHashkey_i.unNumOfOctets >  AMPS_HASH_TABLE_KEY_SIZE)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," StrHashkey_i.unNumOfOctets >  AMPS_HASH_TABLE_KEY_SIZE  , StrHashkey_i.unNumOfOctets == %d  \n ",StrHashkey_i.unNumOfOctets);
        return DMBase_Retval_Insufficient_Buffer;
	}

    if(DMBase_Malloc(hDiameterStackContext_io, (void**)&pHASHTableKey, sizeof(t_AMPSHashTableKey)) != DMBase_Retval_Success)
    {

        DMBASE_TRACE(g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, "Memory Allocation Failed failed\n");
        return DMBase_Retval_Failure;
    }

	memcpy(pHASHTableKey-> puchKey ,StrHashkey_i.pucOctetString,StrHashkey_i.unNumOfOctets );

    pHASHTableKey ->unKeyLength = StrHashkey_i.unNumOfOctets;
    *phHashKeyHandle_o = pHASHTableKey;

    DMBASE_TRACE(g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_CreateTCPListenerObject
**
** Description:
**		This function creates TCP listener object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HTRANSPORTOBJECT hTransObj_i
**			type: input
**			detail: this is transport object for listener object
**				to be created.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether listener object
**		successfully created or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_CreateTCPListenerObject(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
												  HTRANSPORTOBJECT hTransObj_i,
												  t_TCPListener_Params	oTCPListenerParams_i)
{

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");
    int nBindRetries = 0;
	int	nAMPSRetVal = 0;

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hTransObj_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hTransObj_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	unsigned char ucHostIP[DMBASE_TCP_IPV4_SIZE+1]={0};

	DMBase_CopyDiamStrToNSizedCharArray(ucHostIP, DMBASE_TCP_IPV4_SIZE+1,hTransObj_i->oDiamTCPTransport.oIPAddress);

	do
	{
		nAMPSRetVal =  AMPS_CreateTCPListenerObject(hDiameterStackContext_io->hFrameworkHandle,
													AMPS_MEMORY_SCHEME_STATIC,
													oTCPListenerParams_i.pfMallocCallback,
													oTCPListenerParams_i.pfFreeCallback,
													oTCPListenerParams_i.pfReAllocCallback ,
													hTransObj_i->oDiamTCPTransport.unPort,
													(char*)ucHostIP,
													oTCPListenerParams_i.nMinMsgSize,
													oTCPListenerParams_i.nFixedMsgSize,
													oTCPListenerParams_i.pfConnNotifyCallback,
													oTCPListenerParams_i.pvAppHandle,
													oTCPListenerParams_i.pfRecvDataCallback,
													&hTransObj_i->pvTransportLayerHandle,
													oTCPListenerParams_i.pfCloseEvtCallback);

		nBindRetries++;

	} while ((AMPS_SUCCESS != nAMPSRetVal) && (nBindRetries < DMBASE_MAX_NUMBER_OF_BIND_RETRIES) );



    if (DMBASE_MAX_NUMBER_OF_BIND_RETRIES == nBindRetries)
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, "Number of Bind retries exhausted ... exiting application\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");

    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SListGetNextNode
**
** Description:
**		This function moves to next node of the link list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 void* pvList
**			type: input
**			detail: this is a pointer to current node of link list.
**
**		  void** ppvNextNode
**			type: input/output
**			detail: this is a pointer to a pointer which points to
**				next node of link list.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether next node is
**		successfully obtained or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SListGetNextNode(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
											DMBase_SList* poList, DMBase_SList** ppoNextNode)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == poList)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," pvList is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == ppoNextNode)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ppvNextNode is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

    *ppoNextNode = AMPS_SListGetNextNode(poList);

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SendBufferOnTransport
**
** Description:
**		This function sends data on transport connection.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 HTRANSPORTOBJECT hTransport_i
**			type: input
**			detail: this is handle of transport object.
**
**		  unsigned char* puchBuffer_i
**			type: input
**			detail: this is a pointer to buffer which is to be sent
**				on transport connection.
**
**		  int nBufferLength_i
**			type: input
**			detail: this is a size of the buffer.
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data is
**		successfully sent on transport connection  or any problem
**		occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SendBufferOnTransport(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
									 HTRANSPORTOBJECT hTransport_i,
									 unsigned char* puchBuffer_i,
									 int nBufferLength_i)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == hTransport_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hTransport_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

	if (NULL == puchBuffer_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," puchBuffer_i is NULL \n ");
        return DMBase_Retval_Null_Pointer;
	}

    if(TCP == hTransport_i->oTransportType)
    {

    	unsigned char ucIPAddress[32] = {0};
    	DMBase_CopyDiamStrToNSizedCharArray(ucIPAddress, 32, hTransport_i->oDiamTCPTransport.oIPAddress);

        if(AMPS_SUCCESS != AMPS_SndBuffer(	hDiameterStackContext_io->hFrameworkHandle,
											hTransport_i->pvTransportLayerHandle,
											puchBuffer_i,
											nBufferLength_i,
											hTransport_i->oDiamTCPTransport.unPort,
											ucIPAddress))
        {
            DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Problem occurred while sending data.\n");
            return DMBase_Retval_Failure;
        }


    }//end if(TCP == hTransport_i->otransportType)
    else if(SCTP == hTransport_i->oTransportType)
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " SCTP related functionality is not available.\n");
        return DMBase_Retval_Failure;
    }
    else
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " Invalid Transport type.\n");
        return DMBase_Retval_Failure;
    }


    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**			DMBase_OpenTCPConnection
**
** Description:
**		This function creates a TCP connection object with the peer.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 HTRANSPORTOBJECT hTransport_i
**			type: input
**			detail: this is handle of transport object.
**
** Return:
**		An DMBase_ReturnVal_t value specify whether TCP connection
**		is successfully created or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/


t_DiamAPIReturnVal DMBase_OpenTCPConnection(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                HTRANSPORTOBJECT hTransport_i, t_TCPOpen_Params	oTCPOpenParams_i)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");



	t_DiamAPIReturnVal	oRetVal = DMBase_Retval_Success;
	char*				pchHostIPAddr = NULL;

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hDiameterStackContext_io is NULL \n ");
        oRetVal = DMBase_Retval_Null_Pointer;
		goto ExitMe;
	}

	if (NULL == hTransport_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," hTransport_i is NULL \n ");
		oRetVal = DMBase_Retval_Null_Pointer;
		goto ExitMe;
	}

	if ( DMBase_Retval_Success != DMBase_GetIPAddressFromDiameterContext(hDiameterStackContext_io,&pchHostIPAddr))
	{
        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, "DMBase_GetIPAddressFromDiameterContext Failed !! ");
        oRetVal = DMBase_Retval_Failure;
		goto ExitMe;
    }

	unsigned char ucRemoteIP[DMBASE_TCP_IPV4_SIZE+1]={0};
	DMBase_CopyDiamStrToNSizedCharArray(ucRemoteIP, DMBASE_TCP_IPV4_SIZE+1,
										hTransport_i->oDiamTCPTransport.oIPAddress);

	if(AMPS_SUCCESS != AMPS_CreateTCPConnObjectEx(hDiameterStackContext_io->hFrameworkHandle,
													AMPS_MEMORY_SCHEME_STATIC,
													oTCPOpenParams_i.pfMallocCallback,
													oTCPOpenParams_i.pfFreeCallback,
													oTCPOpenParams_i.pfReAllocCallback,
													pchHostIPAddr,
													hTransport_i->oDiamTCPTransport.unPort,
													(char*)ucRemoteIP,
													oTCPOpenParams_i.nMinMsgSize,
													oTCPOpenParams_i.nFixedMsgSize,
													oTCPOpenParams_i.pfRecvDataCallback,
													oTCPOpenParams_i.pfConnCfmCallback,
													oTCPOpenParams_i.pfCloseEvtCallback,
													oTCPOpenParams_i.pvAppHandle,
													oTCPOpenParams_i.pvAppDataHandle))
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, "Problem in creating transport object");
        oRetVal = DMBase_Retval_Failure;
		goto ExitMe;
    }


	ExitMe:

	if (NULL != pchHostIPAddr)
	{
		DMBase_Free(hDiameterStackContext_io,(void**) &pchHostIPAddr);
	}

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return oRetVal;

}


/******************************************************************************
** Function Name:
**			DMBase_CloseTCPConnection
**
** Description:
**		This function closes a TCP connection with the peer.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 HTRANSPORTOBJECT hTransport_i
**			type: input
**			detail: this is handle of transport object.
**
** Return:
**		An DMBase_ReturnVal_t value specify whether TCP connection
**		is successfully closed or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_CloseTCPConnection(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                             HTRANSPORTOBJECT hTransportObject)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " hDiameterStackContext_io = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

	if (NULL == hTransportObject)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " hTransportObject = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

    if(AMPS_SUCCESS != AMPS_DestroyTCPObject(hDiameterStackContext_io->hFrameworkHandle,
                                             hTransportObject->pvTransportLayerHandle))
    {

            DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " Problem occurred while terminating connection\n");
            return DMBase_Retval_Failure;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_GetUsrDataFromNetHandle(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
							AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, void** ppvUserData)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " hDiameterStackContext_io = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

	if (NULL == ppvUserData)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " ppvUserData = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

	if (NULL != *ppvUserData)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " *ppvUserData != NULL \n");
		return DMBase_Retval_IncorrectParameters;
    }

    *ppvUserData = AMPS_GetUsrDataFromNetHandle(hDiameterStackContext_io->hFrameworkHandle,
												r_hAMPS_NET_HANDLE);


    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetUsrDataToNetHandle(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
								 AMPS_NET_HANDLE r_hAMPS_NET_HANDLE, void* pvUserData)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " hDiameterStackContext_io = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

	AMPS_SetUsrDataToNetHandle(hDiameterStackContext_io->hFrameworkHandle,
						r_hAMPS_NET_HANDLE, pvUserData);



	DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_StartTimer(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
			unsigned int unExpiryTime, DMBase_TimeOutNotifyCallBack pfTimerCallBack,
			void* pvData, DMBASE_TIMERID* poTimerID)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " hDiameterStackContext_io = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

	if (NULL == poTimerID)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " poTimerID = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }



    *poTimerID = AMPS_StartTimer(hDiameterStackContext_io->hFrameworkHandle, unExpiryTime,
								  pfTimerCallBack, pvData);

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_KillTimer(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
									DMBASE_TIMERID oTimerID)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if (NULL == hDiameterStackContext_io || NULL == oTimerID)
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " hDiameterStackContext_io = NULL \n");
		return DMBase_Retval_Null_Pointer;
    }

    if ( AMPS_SUCCESS != AMPS_DeleteTimer(hDiameterStackContext_io->hFrameworkHandle,
										  oTimerID))
	{
		DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " AMPS_DeleteTimer FAILED  \n");
		return DMBase_Retval_Failure;
	}

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}
/******************************************************************************
** Function Name:
**			DMBase_HashTableDelete
**
** Description:
**		This function appends node to the link list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 DMBase_SList** ppSList_io
**			type: input/output
**			detail: this is a pointer to a pointer which points
**				to start of list.
**
**		 void* pvData_i
**			type: input
**			detail: this is a pointer to data which is to be appended
**				to list.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data appended to list
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_HashTableDelete( HDIAMETERSTACKCONTEXT            hDiameterContext_io,
                                           DMBASE_HASH_HANDLE               hhandleToHashTable_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering \n");

    if(NULL == hDiameterContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_io , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == (hDiameterContext_io->hFrameworkHandle) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_i->hFrameworkHandle , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if( NULL == hhandleToHashTable_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hhandleToHashTable_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	AMPS_HashTableDelete (hDiameterContext_io->hFrameworkHandle, hhandleToHashTable_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
    return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_HashTableTraverseAllEntries(	HDIAMETERSTACKCONTEXT 					hDiameterStackContext_io,
														DMBASE_HASH_HANDLE 						hHashTable_i,
														DMBASE_HashTableProcessNodeDataCallback pfCallback_i,
														void*				pvAppContext_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering \n");

    if( NULL == hDiameterStackContext_io || NULL == hHashTable_i || NULL == pfCallback_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Pointer \n");
        return DMBase_Retval_Null_Pointer;
    }

	AMPS_HashTableTraverseAllEntries(hDiameterStackContext_io->hFrameworkHandle,
									 hHashTable_i,
									 pfCallback_i,
									 pvAppContext_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
    return DMBase_Retval_Success;
}
/******************************************************************************
** Function Name:
**			DMBase_SListFree
**
** Description:
**		This function appends node to the link list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 DMBase_SList** ppSList_io
**			type: input/output
**			detail: this is a pointer to a pointer which points
**				to start of list.
**
**		 void* pvData_i
**			type: input
**			detail: this is a pointer to data which is to be appended
**				to list.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data appended to list
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SListFree(HDIAMETERSTACKCONTEXT		    hDiameterContext_io,
									DMBase_SList**                      ppSList_i,
                                    AMPS_LListFreeLinkDataCallback    pfDMBase_LListFreeLinkDataCallBack_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiameterContext_io )
    {
          DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_io , Leaving \n");
          return DMBase_Retval_Null_Pointer;
    }

    if(NULL == ppSList_i )
    {
          DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter ppSList_i , Leaving \n");
          return DMBase_Retval_Null_Pointer;
    }

    if(NULL == *ppSList_i )
    {
          DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter *ppSList_i , Leaving \n");
          return DMBase_Retval_IncorrectParameters;
    }


    if(AMPS_SUCCESS !=  AMPS_SListFree(ppSList_i,pfDMBase_LListFreeLinkDataCallBack_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "AMPS_SListFree() Fails , Leaving \n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}
/******************************************************************************
** Function Name:
**			DMBAse_SListRemove
**
** Description:
**		This function appends node to the link list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterStackContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		 DMBase_SList** ppSList_io
**			type: input/output
**			detail: this is a pointer to a pointer which points
**				to start of list.
**
**		 void* pvData_i
**			type: input
**			detail: this is a pointer to data which is to be appended
**				to list.
**
**
** Return:
**		An t_DiamAPIReturnVal value specify whether data appended to list
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

// Base Protocol Wrapper Function

t_DiamAPIReturnVal DMBase_SListRemove(HDIAMETERSTACKCONTEXT    hDiameterContext_io,
                                      DMBase_SList**           ppoSList_i,
                                      DMBase_SList*            poSListNode_i,
                                      void*                    pfDMBase_LListFreeLinkDataCallBack_i)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == ppoSList_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter ppoSList , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == hDiameterContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_io , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }


    if(NULL == *ppoSList_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter *ppoSList , Leaving \n");
        return DMBase_Retval_IncorrectParameters;
    }

    if(NULL == poSListNode_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter poSListNode , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }


   if( AMPS_SUCCESS!= AMPS_SListRemove(ppoSList_i,
                                       poSListNode_i,
                                       pfDMBase_LListFreeLinkDataCallBack_i) )
   {
         DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Problem occurred while removing node from Slist , Leaving \n");
         return DMBase_Retval_Failure;
   }

   DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
   return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBASE_DBEngin_Init(HDIAMETERSTACKCONTEXT		hDiameterContext_i,
                                       char*                        pchHostName_i,
                                       char*                        pchUserName_i,
                                       char*                        pchPassword_i,
                                       char*                        pchDataBaseName_i,
                                       DMBASE_DBE_HANDLE*           phBDEngineHandle_o)
{



     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    if(NULL == hDiameterContext_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pchHostName_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter pchHostName_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pchUserName_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter pchUserName_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pchPassword_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter pchPassword_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pchDataBaseName_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter pchDataBaseName_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == phBDEngineHandle_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter phBDEngineHandle_o , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

	if(NULL != (*phBDEngineHandle_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "(*phBDEngineHandle_o) is Not NULL , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

   *phBDEngineHandle_o = AMPS_DBEngineInit( hDiameterContext_i->hFrameworkHandle,
                                            pchHostName_i,
                                            pchUserName_i,
                                            pchPassword_i,
                                            pchDataBaseName_i);



    if(NULL == *phBDEngineHandle_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, "AMPS_DBEngineInit() Fails, Leaving \n");
        DMBase_Retval_Failure;

    }
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;

}


t_DiamAPIReturnVal DMBASE_DBEngin_Cleanup( HDIAMETERSTACKCONTEXT		  hDiameterContext_i,
                                           DMBASE_DBE_HANDLE              hBDEngine_Handle)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiameterContext_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == hBDEngine_Handle)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hBDEngine_Handle , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }


    AMPS_DBEngineCleanup( hDiameterContext_i->hFrameworkHandle,
                          hBDEngine_Handle);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBASE_DBEngineQuery(HDIAMETERSTACKCONTEXT		hDiameterContext_i,
                                        DMBASE_DBE_HANDLE           hBDEngineHandle_i,
                                        const char*                 pcchQueryStatement_i,
                                        unsigned long               ulLengthOfQuery_i,
                                        DMBASE_DBEngineResult*      poDBEngineResult_o)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

    if(NULL == hDiameterContext_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == hBDEngineHandle_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hBDEngineHandle_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pcchQueryStatement_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter pcchQueryStatement_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == poDBEngineResult_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter poDBEngineResult_o , Leaving \n");
        return DMBase_Retval_Null_Pointer;
    }

    if( AMPS_SUCCESS != AMPS_DBEngineQuery(hDiameterContext_i->hFrameworkHandle,
                                           hBDEngineHandle_i,
                                           pcchQueryStatement_i,
                                           ulLengthOfQuery_i,
                                           poDBEngineResult_o) )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "AMPS_DBEngineQuery() Fails , Leaving \n");
        return DMBase_Retval_Failure;

    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBASE_DBEngineFreeResults( HDIAMETERSTACKCONTEXT	     hDiameterContext_i,
                                               DMBASE_DBE_HANDLE             hBDEngineHandle_i,
                                               DMBASE_DBEngineResult*        poDBEngineResult_i)
{
     DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

     if(NULL == hDiameterContext_i)
     {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hDiameterContext_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
     }

     if(NULL == hBDEngineHandle_i)
     {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter hBDEngineHandle_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
     }

     if(NULL == poDBEngineResult_i)
     {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Null Parameter poDBEngineResult_i , Leaving \n");
        return DMBase_Retval_Null_Pointer;
     }

     AMPS_DBEngineFreeResults(hDiameterContext_i->hFrameworkHandle,
                              hBDEngineHandle_i,
                              poDBEngineResult_i);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



t_DiamAPIReturnVal  DMBase_MD5Init(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
								   DMBASE_MD5_HANDLE* phMD5_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hDiameterStackContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL == phMD5_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "phMD5_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL != (*phMD5_io) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "*phMD5_io is not NULL \n");
		return DMBase_Retval_IncorrectParameters;
	}



    *phMD5_io = AMPS_MD5Init(hDiameterStackContext_io->hFrameworkHandle);

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


void                DMBase_MD5Cleanup(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                        DMBASE_MD5_HANDLE hMD5_io)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hDiameterStackContext_io is NULL \n");
		return ;
	}

	if(NULL == hMD5_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hMD5_io is NULL \n");
		return ;
	}

    AMPS_MD5Cleanup(hDiameterStackContext_io->hFrameworkHandle, hMD5_io);

	DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");

}

t_DiamAPIReturnVal  DMBase_MD5Update(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                        DMBASE_MD5_HANDLE hMD5_io,
                                        unsigned char* puchData_i, int nDataLength_i)
{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hDiameterStackContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL == hMD5_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hMD5_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL == puchData_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "puchData_i is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}


    if( AMPS_SUCCESS != AMPS_MD5Update(hDiameterStackContext_io->hFrameworkHandle, hMD5_io, puchData_i, nDataLength_i))
    {
        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " Problem occurred while updating MD5.\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


t_DiamAPIReturnVal  DMBase_MD5Final(HDIAMETERSTACKCONTEXT hDiameterStackContext_io,
                                    DMBASE_MD5_HANDLE hMD5_io, unsigned char* puchMD5Hash_o)

{
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiameterStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hDiameterStackContext_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL == hMD5_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "hMD5_io is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL == puchMD5Hash_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "puchMD5Hash_o is NULL \n");
		return DMBase_Retval_Null_Pointer;
	}

	if(AMPS_SUCCESS != AMPS_MD5Final(hDiameterStackContext_io->hFrameworkHandle, hMD5_io, puchMD5Hash_o))
    {

        DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_ERROR, " Problem occurred while Reteiving MD5.\n");
        return DMBase_Retval_Failure;
    }
    DMBASE_TRACE( g_nDiamBaseTraceID, AMPS_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}





/******************************************************************************
** Function Name:
**			DMBase_EvtSysSetEvtHandleValidationCallback
**
** Description:
**
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT    		hDiameterContext_i
**			 type: input
**			 detail : This is a Handle to Diameter Base Protocol Stack  context.
**
**
**		  DMBASE_EvtHandleValidationCallback		pf_Rf_EvtValidationCallback_i
**			 type: input
**			 detail : This is a function pointer to Evtent Validation call back .
**
** Return:
**		An t_DiamAPIReturnVal value specifing  the success or failure of the function .
**
*******************************************************************************
** Created By: 	Simab Shahid
*******************************************************************************
*******************************************************************************
*/


t_DiamAPIReturnVal DMBase_EvtSysSetEvtHandleValidationCallback(
				HDIAMETERSTACKCONTEXT   				hDiameterContext_io,
				DMBASE_EvtHandleValidationCallback		pf_EvtValidationCallback_i )
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering \n");

	if (NULL == hDiameterContext_io )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

	if (NULL == pf_EvtValidationCallback_i )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pf_EvtValidationCallback_i is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

	AMPS_EvtSysSetEvtHandleValidationCallback(hDiameterContext_io->hFrameworkHandle,pf_EvtValidationCallback_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving \n");
	return DMBase_Retval_Success;

}



/******************************************************************************
** Function Name:
**			DMBase_EvtSysRegIntEvt
**
** Description:
**		This is a Wrapper function for AMPS_EvtSysRegIntEvt.
**
** Parameters:
**		  void* pvHandle_i
**			 type: input
**			 detail : this is a Handle to Message Received By RF Application.
**
**       void* r_pvData_i
**			 type: input
**			 detail : this is a void pointer to data received by the Timer
**                     handler function From the application.
**
**
** Return:
**		An t_Offline_CS_ReturnVal value specifing  whether function is returning
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 	Simab Shahid
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_EvtSysRegIntEvt(HDIAMETERSTACKCONTEXT    hDiameterContext_io,
                                          int                      nEventType_i,
                                          void*                    pvfuncEvtHandler_i,
                                          void*                    pvEventdata_i)
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Enterning \n");

	if (NULL == hDiameterContext_io )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pvfuncEvtHandler_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvfuncEvtHandler_i is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

    if ( AMPS_SUCCESS != AMPS_EvtSysRegIntEvt(hDiameterContext_io->hFrameworkHandle,
                                              nEventType_i,
                                              pvfuncEvtHandler_i,
                                              pvEventdata_i))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"AMPS_EvtSysRegIntEvt() Fail, Leaving\n");
		DMBase_Retval_Failure;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_EvtSysRegExtEvt(	HDIAMETERSTACKCONTEXT 	hDiameterContext_io,
											int 					nEventType_i,
											void* 					pvfuncEvtHandler_i,
											void* 					pvEventdata_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Enterning \n");

	if (NULL == hDiameterContext_io )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pvfuncEvtHandler_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvfuncEvtHandler_i is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

    if ( AMPS_SUCCESS != AMPS_EvtSysRegExtEvt(hDiameterContext_io->hFrameworkHandle,
                                              nEventType_i,
                                              pvfuncEvtHandler_i,
                                              pvEventdata_i))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"AMPS_EvtSysRegIntEvt() Fail, Leaving\n");
		DMBase_Retval_Failure;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_IOAgentsRegEvt(	void*	pvIOAgentHandle_io,
											int 	nEventType_i,
											void* 	pvfuncEvtHandler_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering \n");

	if (NULL == pvIOAgentHandle_io )
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvIOAgentHandle_io is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }

    if(NULL == pvfuncEvtHandler_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvfuncEvtHandler_i is null pointer \n ");
        return DMBase_Retval_Null_Pointer;
    }
    if(AMPS_SUCCESS != AMPS_IOAgentsRegEvt(pvIOAgentHandle_io, nEventType_i, pvfuncEvtHandler_i))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"AMPS_EvtSysRegIntEvt() Fail, Leaving\n");
		DMBase_Retval_Failure;
	}


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
	return DMBase_Retval_Success;

}

/******************************************************************************
** Function Name:
**			DMBASE_EvtSysSendIntEvt
**
** Description:
**		This is a event triggering function .
**
** Parameters:
**		  AMPS_HANDLE     hAMPSHandle_i
**			 type: input
**			 detail : this is a handle to AMPS framework.
**
**		 int             nEventType_i,
**			type: input
**			detail: this is a integer variable contains the type of Event.
**
**		 void*           pvEventData_i
**			type: input
**			detail: this is a pointer to data which the Aplication Wants
**                  to send through the event.
**
**      unsigned int    unSizeofEventData_i
**          Type: input
**          detail: this is size of the the Data that the application is
**                  sending through the events.
** Return:
**		An t_DiamAPIReturnVal value specify whether the event has been fired
**		successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: Simab Shahid
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBASE_EvtSysSendIntEvt(HDIAMETERSTACKCONTEXT    hDiameterContext_io,
                                           int             nEventType_i,
                                           void*           pvEventData_i,
                                           unsigned int    unSizeofEventData_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering \n");

	if (NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is null pointer \n ");
		return DMBase_Retval_Null_Pointer;
	}

	if (NULL == pvEventData_i )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvEventData_i is null pointer \n ");
		return DMBase_Retval_Null_Pointer;
	}

	if(AMPS_SUCCESS != AMPS_EvtSysSendIntEvt(hDiameterContext_io->hFrameworkHandle,
											 nEventType_i,
											 pvEventData_i,
											 unSizeofEventData_i))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"ERROR! AMPS_EvtSysSendIntEvt Fails, Leaving \n");
		return DMBase_Retval_Failure;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving \n");
	return	DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_CreateFileObject( HDIAMETERSTACKCONTEXT    hDiameterContext_io,
										    char*					 pcFileName_i,
											void**					 ppvFileHadle_o,
											DMBase_FileMode			 oFileMode_i )
{

	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}


	if(NULL == pcFileName_i)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pcFileName_i is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}


	if(NULL == ppvFileHadle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"ppvFileHadle_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if(NULL != *ppvFileHadle_o)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"ppvFileHadle_o is Incorrect , leaving\n");
		return DMBase_Retval_IncorrectParameters;
	}

	FILE*  pFileHandle = NULL;


	if( AMPS_SUCCESS != AMPS_CreateFileObject(	hDiameterContext_io->hFrameworkHandle,
												pcFileName_i,
												(void**)&pFileHandle,
												oFileMode_i ) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"Problem in Creating File object ,Leaving\n");
		return DMBase_Retval_Failure;
	}

	*ppvFileHadle_o = pFileHandle;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
 }


t_DiamAPIReturnVal DMBase_FileWrite( HDIAMETERSTACKCONTEXT    hDiameterContext_io,
                                     void*					  pvFileHadle_o,
									 char*					  pcBuffTowrite_i,
									 int					  nSizeOfBuff_i,
									 int*					  pnNumBytesWritten_o )
{
	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pvFileHadle_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvFileHadle_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pcBuffTowrite_i )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pcBuffTowrite_i is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pnNumBytesWritten_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pnNumBytesWritten_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( AMPS_SUCCESS != AMPS_FileWrite(hDiameterContext_io->hFrameworkHandle,
										pvFileHadle_o,pcBuffTowrite_i,
										nSizeOfBuff_i,pnNumBytesWritten_o ) )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"Problem in writing to File ,Leaving\n");
		return DMBase_Retval_Failure;
	}

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;

}

t_DiamAPIReturnVal DMBase_NetworkToHostShort( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned short usToConvert_i,
											  unsigned short* pusConvertedShort_o)
{
	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pusConvertedShort_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pusConvertedShort_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	*pusConvertedShort_o = AMPS_NetworkToHostShort(hDiameterContext_io->hFrameworkHandle
												   ,usToConvert_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_NetworkToHostLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long unToConvert_i,
											  unsigned long* punConvertedLong_o)
{
	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == punConvertedLong_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"punConvertedLong_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	*punConvertedLong_o = AMPS_NetworkToHostLong(hDiameterContext_io->hFrameworkHandle
												   ,unToConvert_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_HostToNetworkShort( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned short usToConvert_i,
											  unsigned short* pusConvertedShort_o)
{
	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pusConvertedShort_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pusConvertedShort_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	*pusConvertedShort_o = AMPS_HostToNetworkShort(hDiameterContext_io->hFrameworkHandle
												   ,usToConvert_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_HostToNetworkLong( HDIAMETERSTACKCONTEXT  hDiameterContext_io,
											  unsigned long unToConvert_i,
											  unsigned long* punConvertedLong_o)
{
	DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_io )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_io is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == punConvertedLong_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"punConvertedLong_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	*punConvertedLong_o = AMPS_HostToNetworkLong(hDiameterContext_io->hFrameworkHandle
												   ,unToConvert_i);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_SetRecvBuffStatusToNetHandle(	AMPS_HANDLE 	hAMPS_HANDLE_i,
														AMPS_NET_HANDLE hAMPS_NET_HANDLE_io,
														int 			nMessageStatus_i,
														int 			nRemainingBytesToRead_i)
{

	AMPS_SetRecvBuffStatusToNetHandle(	hAMPS_HANDLE_i,
										hAMPS_NET_HANDLE_io,
										nMessageStatus_i,
										nRemainingBytesToRead_i);
}


t_DiamAPIReturnVal DMBase_EvtSysGetEventType(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											void* pvEventHandle_i, int* pnEventType_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, "Entering\n");

	if( NULL == hDiameterContext_io || NULL == hDiameterContext_io->hFrameworkHandle ||
			NULL == pvEventHandle_i || NULL == pnEventType_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer\n");
		return DMBase_Retval_Null_Pointer;
	}

	int nEventType = AMPS_EvtSysGetEventType(hDiameterContext_io->hFrameworkHandle, pvEventHandle_i);
	*pnEventType_io = nEventType;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}


t_DiamAPIReturnVal DMBase_EvtSysGetEventSize(HDIAMETERSTACKCONTEXT hDiameterContext_io,
											void* pvEventHandle_i, int* pnEventSize_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, "Entering\n");

	if( NULL == hDiameterContext_io || NULL == hDiameterContext_io->hFrameworkHandle ||
			NULL == pvEventHandle_i || NULL == pnEventSize_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer\n");
		return DMBase_Retval_Null_Pointer;
	}

	int nEventSize = AMPS_EvtSysGetEventSize(hDiameterContext_io->hFrameworkHandle, pvEventHandle_i);
	*pnEventSize_io = nEventSize;

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_IOAgentsInit(HDIAMETERSTACKCONTEXT    			hDiameterContext_i,
									   int 									nNoOfThreads_i,
									   DMBASE_IOAgentsDispatcherCallback 	pf_IOAgentsDispatcherCallback_i,
									   DMBASE_IOAgentsInitCallback 			pf_IOAgentsInitCallback_i,
									   DMABSE_IOAgentsCleanupCallback 		pf_IOAgentsCleanupCallback_i,
									   void* 								pvUserData_i,
									   DMBASE_IOAGENTS_HANDLE*		 		phIOAgentsHandle_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Entering\n");

	if( NULL == hDiameterContext_i )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"hDiameterContext_i is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == pvUserData_i )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"pvUserData_i is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL == phIOAgentsHandle_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"phIOAgentsHandle_o is NULL , leaving\n");
		return DMBase_Retval_Null_Pointer;
	}

	if( NULL != *phIOAgentsHandle_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"*phIOAgentsHandle_o is not NULL , leaving\n");
		return DMBase_Retval_IncorrectParameters;
	}

	*phIOAgentsHandle_o = AMPS_IOAgentsInit( hDiameterContext_i->hFrameworkHandle,
											 nNoOfThreads_i,
											 pf_IOAgentsDispatcherCallback_i,
											 pf_IOAgentsInitCallback_i,
											 pf_IOAgentsCleanupCallback_i,
											 pvUserData_i);

	if( NULL == *phIOAgentsHandle_o )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"IOAgents_Init failed, leaving\n");
		return DMBase_Retval_Failure;
	}


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"Leaving\n");
	return DMBase_Retval_Success;
}



