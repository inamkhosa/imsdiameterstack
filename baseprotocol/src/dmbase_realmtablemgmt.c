
#include "dmbase_realmtablemgmt.h"

#include "dmbase_utility.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_dictionary.h"

extern int g_nDiamBaseTraceID;


/******************************************************************************
** Function Name:
**			DMBase_CreateRealmTable
**
** Description:
**		This function creates realm table.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
** Return:
**		A t_DiamAPIReturnVal value specify whether realm table is
**		successfully created or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/


t_DiamAPIReturnVal DMBase_CreateRealmTable(HDIAMETERSTACKCONTEXT  hDiamStackContext_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    if(DMBase_Retval_Success != DMBase_CreateRealmTableObject(hDiamStackContext_io,
                                            &(hDiamStackContext_io->poRealmTable)))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to create Realm table object\r\n");
        return DMBase_Retval_Failure;
    }

    if(DMBase_Retval_Success != DMBase_CreateHashTable(hDiamStackContext_io,
                                    DMBASE_HASHTABLE_MAX_SIZE,
                                    &(hDiamStackContext_io->poRealmTable->oRealmHashTable.hHashTable),
									  NULL))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to create Hash table\r\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");

    return DMBase_Retval_Success;

}


/******************************************************************************
** Function Name:
**			DMBase_CreateRealmTableObject
**
** Description:
**		This function will create a realm table object.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : handle to diameter context.
**
**		  t_RealmTable** ppoRealmTableObject_o
**			type: output
**			detail: pointer to a pointer which points
**				to newly created realm table object
**
** Return:
**		An t_DiamAPIReturnVal value specify whether realm table object
**		created successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_CreateRealmTableObject(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                 t_RealmTable**        ppoRealmTableObject_o)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == ppoRealmTableObject_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    int nSize   = sizeof(t_RealmTable);

    if(DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io,
                                (void **)ppoRealmTableObject_o, nSize))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to allocate memory for "
                                                                    "Realm Table Object.\r\n");
        return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_CreateRealmTableKey
**
** Description:
**		This function create realm table key.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail: this is a diameter context handle.
**
**		  t_DiamOctetString RealmName_i
**			type: input
**			detail: this is realm table name.
**
**		  unsigned int unAppID_i
**			type:input
**			detail: this is application identifier.
**
**		  t_DiamOctetString* pRealmTableKey_o
**			type:output
**			detail: this is pointer to newly created realm table key.
**
** Return:
**		A t_DiamAPIReturnVal value specify whether realm table key is
**		successfully created or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_CreateRealmTableKey(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                              t_DiamOctetString     oRealmName_i,
                                              unsigned int          unAppID_i,
                                              t_DiamHashTableKey*   poHashTableKey_o)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == poHashTableKey_o || NULL == oRealmName_i.pucOctetString)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    unsigned char ucRealmName[DMBASE_HASH_TABLE_KEY_SIZE-100];

	DMBase_MemsetZero(ucRealmName, DMBASE_HASH_TABLE_KEY_SIZE-100);
	DMBase_MemsetZero(poHashTableKey_o, sizeof(t_DiamHashTableKey));

	DMBase_CopyDiamStrToNSizedCharArray(ucRealmName, DMBASE_HASH_TABLE_KEY_SIZE-100, oRealmName_i);
    sprintf(poHashTableKey_o->puchKey,"%s-%d", ucRealmName, unAppID_i);
    poHashTableKey_o->unKeyLength = strlen(poHashTableKey_o->puchKey);

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_PopulateRealmTable
**
** Description:
**		This function build realm table with given list.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBase_SList* pRealmList_i
**			type: output
**			detail: this is list of realms used to build realm table.
**
** Return:
**		A t_DiamAPIReturnVal value specify whether realm table is
**		successfully build or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/


t_DiamAPIReturnVal DMBase_PopulateRealmTable( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
											  DMBase_SList*          poRealmList_i )
{

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == poRealmList_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    DMBase_SList* poList = poRealmList_i;
    HREALMTABLEENTRY	hRealmTableEntry = NULL;

    while(NULL != poList)
    {

    	hRealmTableEntry = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, poList, (void**)&hRealmTableEntry);

        if(DMBase_Retval_Success != DMBase_InsertRealmTableEntry(hDiamStackContext_io,
																	hRealmTableEntry))
        {
            DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to insert realm table entry.\n");
            return DMBase_Retval_Failure;
        }
        DMBase_SListGetNextNode(hDiamStackContext_io, poList, &poList);

    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_InsertRealmTableEntry(HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
												HREALMTABLEENTRY		hRealmTableEntry_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    unsigned char ucRealmName[DMBASE_HASH_TABLE_KEY_SIZE-100];
    t_DiamHashTableKey oHashTableKey;
    unsigned int unRealmListCount;
    unsigned int unHashKeyCount;

    if( DMBase_Retval_Success != DMBase_CreateRealmTableKey(hDiamStackContext_io,
															hRealmTableEntry_i->oRealmName ,
															hRealmTableEntry_i->oAppIdent.unAppID,
															&oHashTableKey))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create realm table key\n");
        return DMBase_Retval_Failure;
    }

    if(DMBase_Retval_Success != DMBase_HashTableInsert(hDiamStackContext_io,
								hDiamStackContext_io->poRealmTable->oRealmHashTable.hHashTable,
								(void*)hRealmTableEntry_i,
                                &oHashTableKey))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to insert in realm table\n");
        return DMBase_Retval_Failure;
    }

    //TODO:Also check for duplicate entries
    unRealmListCount = hDiamStackContext_io->poRealmTable->unRealmListCount;
    if(DMBASE_MAX_REALM_SUPPORTED == unRealmListCount)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, "Maximum Realm list count limit exceed .\n");
    	return DMBase_Retval_Limit_Exceed;
    }
    DMBase_CopyDiamStrToNSizedCharArray(hDiamStackContext_io->poRealmTable->ucRealmList[unRealmListCount],
										DMBASE_REALM_NAME_SIZE, hRealmTableEntry_i->oRealmName);

    hDiamStackContext_io->poRealmTable->unRealmListCount++;

    unHashKeyCount = hDiamStackContext_io->poRealmTable->oRealmHashTable.unHashKeyCount;
    if(DMBASE_MAX_HASH_KEY_COUNT == unHashKeyCount)
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, "Maximum Hash key list count limit exceed .\n");
    	return DMBase_Retval_Limit_Exceed;
    }

    memcpy(&hDiamStackContext_io->poRealmTable->oRealmHashTable.oHashKeys[unHashKeyCount],
    		&oHashTableKey, sizeof(t_DiamHashTableKey));

    hDiamStackContext_io->poRealmTable->oRealmHashTable.unHashKeyCount++;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_RemoveRealmTableEntry( HDIAMETERSTACKCONTEXT  hDiamStackContext_io,
												 unsigned int          	unAppId_i,
		                                         t_DiamOctetString     	oRealmName_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_LookupRealmTableEntry
**
** Description:
**		This function search an entry in realm table against a
**		hash table key.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  DMBASE_HASHTABLE_KEY_HANDLE hHashKey_i
**			type: input
**			detail: this is a hash key handle.
**
**		  void** pData_o
**			type: output
**			detail: this is a pointer to a pointer which points
**				to realm table entry.
** Return:
**		An t_DiamAPIReturnVal value specify whether realm table entry
**		found successfully or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_LookupRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                unsigned int          unAppId_i,
                                                t_DiamOctetString     oRealmName_i,
                                                HREALMTABLEENTRY*     phRealmTableEntry_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == phRealmTableEntry_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    t_DiamHashTableKey oHashTableKey;

    if( DMBase_Retval_Success != DMBase_CreateRealmTableKey(hDiamStackContext_io,
															oRealmName_i ,
															unAppId_i,
															&oHashTableKey))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Failed to create realm table key\n");
        return DMBase_Retval_Failure;
    }

    if(DMBase_Retval_Success != DMBase_HashTableSearch(	hDiamStackContext_io,
														hDiamStackContext_io->poRealmTable->oRealmHashTable.hHashTable,
														&oHashTableKey,
														(void**)phRealmTableEntry_io ))
    {
    	unsigned char ucRealmName[DMBASE_HASH_TABLE_KEY_SIZE] = {0};
    	DMBase_CopyDiamStrToNSizedCharArray(ucRealmName, DMBASE_HASH_TABLE_KEY_SIZE, oRealmName_i);

        int nIndex;
        for(nIndex = 0; nIndex < hDiamStackContext_io->poRealmTable->unRealmListCount; nIndex++)
        {
            if(strcmp(ucRealmName, hDiamStackContext_io->poRealmTable->ucRealmList[nIndex]) == 0)
            {
                return DMBase_Retval_App_Not_Supported;
            }
        }
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
        return DMBase_Retval_Realm_Not_Supported;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

t_DiamAPIReturnVal DMBase_LookupRealmTableByHashKey(HDIAMETERSTACKCONTEXT 	hDiamStackContext_io,
													t_DiamHashTableKey 		oHashTableKey_i,
													HREALMTABLEENTRY*       phRealmTableEntry_io)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == phRealmTableEntry_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }


    if(DMBase_Retval_Success != DMBase_HashTableSearch(	hDiamStackContext_io,
														hDiamStackContext_io->poRealmTable->oRealmHashTable.hHashTable,
														&oHashTableKey_i,
														(void**)phRealmTableEntry_io))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " Realm entry not found.\n");
    	return DMBase_Retval_Not_Found;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



t_DiamAPIReturnVal DMBase_ShowRealmTable(HDIAMETERSTACKCONTEXT  hDiamStackContext_io)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	if(NULL == hDiamStackContext_io)
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, " NULL pointer.\n");
		return DMBase_Retval_Null_Pointer;
	}


	printf("\r\n\r\n\r\n%35s\r\n","Realm Table");
	printf("%35s\r\n","===========");
	printf("%-30s%-20s%10s\r\n", "Realm Name","Application Id", "Local Action");
	printf("%s\r\n", "==============================================================");

	DMBASE_HASH_HANDLE hRealmTable = hDiamStackContext_io->poRealmTable->oRealmHashTable.hHashTable;
	DMBase_HashTableTraverseAllEntries(	hDiamStackContext_io,
										hRealmTable,
										DMBase_ShowRealmTableEntryCallback,
										(void*)hDiamStackContext_io);

	printf("%s\r\n", "==============================================================");

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

void DMBase_ShowRealmTableEntryCallback(	AMPS_HANDLE 			r_hAMPS_HANDLE,
										AMPS_APP_HANDLE 		r_hAMPS_APP_HANDLE,
										AMPS_APP_DATA_HANDLE 	r_hAMPS_APP_DATA_HANDLE)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

	static unsigned char oLocalActions[][50]= { "[LOCAL]", "[RELAY]", "[PROXY]" , "[REDIRECT]" };

	HDIAMETERSTACKCONTEXT hDiamStackContext = (HDIAMETERSTACKCONTEXT)r_hAMPS_APP_HANDLE;
	HREALMTABLEENTRY hRealmTableEntry = (HREALMTABLEENTRY)r_hAMPS_APP_DATA_HANDLE;

	unsigned char ucRealmName[50] = {0};
	DMBase_CopyDiamStrToNSizedCharArray(ucRealmName,50, hRealmTableEntry->oRealmName);

	printf("%-30s%-20d%10s\r\n", ucRealmName,hRealmTableEntry->oAppIdent.unAppID,
			oLocalActions[hRealmTableEntry->oLocalAction]);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");


}

t_DiamAPIReturnVal DMBase_CreateRealmTableEntry(HDIAMETERSTACKCONTEXT  	hDiamStackContext_io,
												HREALMTABLEENTRY*		phRealmTableEntry_io,
                                              	t_DiamOctetString      	oRealmName_i,
                                              	unsigned int           	unAppID_i,
                                              	_Bool                  	bIsStaticEntry_i,
                                              	t_LocalAction          	oLocalAction_i,
                                              	DMBase_SList*          	poServerList_i)
{
    if(NULL == hDiamStackContext_io || NULL == phRealmTableEntry_io)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    if (DMBase_Retval_Success != DMBase_Malloc(hDiamStackContext_io, (void**)phRealmTableEntry_io, sizeof(t_RealmTableEntry)))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to create realm table entry\n");
        return DMBase_Retval_Failure;
    }

    HREALMTABLEENTRY hRealmTableEntry = *phRealmTableEntry_io;

    if(DMBase_Retval_Success != DMBase_SetRealmNameInRealmTableEntry(hDiamStackContext_io, hRealmTableEntry, oRealmName_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to set realm name\n");
        return DMBase_Retval_Failure;
    }

    //TODO: Also set vendor id for vendor specific application
    t_ApplicationIdentifier oAppId;
    oAppId.unAppID = unAppID_i;
    oAppId.unVendorID = 0;

    if(DMBase_Retval_Success != DMBase_SetAppIdInRealmTableEntry(hDiamStackContext_io, hRealmTableEntry, oAppId))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to set Application ID \n");
        return DMBase_Retval_Failure;
    }

    if(DMBase_Retval_Success != DMBase_SetLocalActionInRealmTableEntry(hDiamStackContext_io, hRealmTableEntry, oLocalAction_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to set Local action\n");
        return DMBase_Retval_Failure;
    }

    if(NULL != poServerList_i)
    {
        if(DMBase_SetServerListInRealmTableEntry (hDiamStackContext_io, hRealmTableEntry,  poServerList_i))
        {
            DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to set server list\n");
            return DMBase_Retval_Failure;
        }
    }

    if(DMBase_Retval_Success != DMBase_SetStaticStatusInRealmTableEntry (hDiamStackContext_io, hRealmTableEntry, bIsStaticEntry_i))
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "Failed to set Status\n");
        return DMBase_Retval_Failure;
    }

    //TODO: check usage of unPrimaryServer
    hRealmTableEntry->unPrimaryServer = -1;

/*
	 TODO: Discuss about expiry times
    t_DiamTime oExpiryTime;

    DMBase_SetExpTimeInRealmTableEntry (hDiamStackContext_io, hRealmTabEntry, oExpiryTime );
*/


    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, "Leaving.\n");
    return DMBase_Retval_Success;

}



/******************************************************************************
** Function Name:
**			DMBase_SetRealmNameInRealmTableEntry
**
** Description:
**		This function sets a realm name in realm table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HREALMTABLEENTRY hRealmTabEntry_o
**			type: output
**			detail: this is a realm table entry handle
**
**		  t_DiamOctetString StrRealmName_i
**			type:input
**			detail: this is realm name
** Return:
**		A t_DiamAPIReturnVal value specify whether realm name is
**		successfully set in realm table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/


t_DiamAPIReturnVal DMBase_SetRealmNameInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                        HREALMTABLEENTRY      hRealmTabEntry_o,
                                                        t_DiamOctetString     oRealmName_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hRealmTabEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    DMBase_MemsetZero(&hRealmTabEntry_o->oRealmName, sizeof(t_DiamOctetString));

    if(DMBase_Retval_Success != DMBase_CopyDiamString(&hRealmTabEntry_o->oRealmName, &oRealmName_i))
    {
    	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Failed to set realm name.\n");
    	return DMBase_Retval_Failure;
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetAppIdInRealmTableEntry
**
** Description:
**		This function sets application id in realm table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HREALMTABLEENTRY hRealmTabEntry_o
**			type: output
**			detail: this is a realm table entry handle
**
**		  t_ApplicationIdentifier ApplicationIdentifier_i
**			type:input
**			detail: this is application identifier
** Return:
**		A t_DiamAPIReturnVal value specify whether application identifier
**		is successfully set in realm table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetAppIdInRealmTableEntry(HDIAMETERSTACKCONTEXT   hDiamStackContext_io,
                                                    HREALMTABLEENTRY        hRealmTabEntry_o,
                                                    t_ApplicationIdentifier oAppId_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hRealmTabEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    hRealmTabEntry_o->oAppIdent = oAppId_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_SetLocalActionInRealmTableEntry
**
** Description:
**		This function sets local action in realm table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HREALMTABLEENTRY hRealmTabEntry_o
**			type: output
**			detail: this is a realm table entry handle
**
**		  t_LocalAction LocAct_i
**			type:input
**			detail: this is local action used to identify how a
**			message should be treated.
** Return:
**		A t_DiamAPIReturnVal value specify whether local action is
**		successfully set in realm table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetLocalActionInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                          HREALMTABLEENTRY      hRealmTabEntry_o,
                                                          t_LocalAction         oLocalAction_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hRealmTabEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    hRealmTabEntry_o->oLocalAction = oLocalAction_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}



/******************************************************************************
** Function Name:
**			DMBase_SetServerListInRealmTableEntry
**
** Description:
**		This function sets server list in realm table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HREALMTABLEENTRY hRealmTabEntry_o
**			type: output
**			detail: this is a realm table entry handle
**
**		  DMBase_SList* pServerList_i
**			type:input
**			detail: this is pointer to server list.
** Return:
**		A t_DiamAPIReturnVal value specify whether server list is
**		successfully set in realm table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/
t_DiamAPIReturnVal DMBase_SetServerListInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                         HREALMTABLEENTRY      hRealmTabEntry_o,
                                                         DMBase_SList*         pServerList_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hRealmTabEntry_o || NULL == pServerList_i)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    DMBase_SList* poList = pServerList_i;

    unsigned int unMaxPriority = 0;

    while( NULL != poList)
    {
        void* pvData = NULL;
        DMBase_SListGetNodeData(hDiamStackContext_io, poList, &pvData);

        t_RoutingServer* poServer = (t_RoutingServer*)pvData;

        hRealmTabEntry_o->oRoutServerList[hRealmTabEntry_o->unRoutingServerCount].unPriority = poServer->unPriority;
        DMBase_CopyDiamString(&hRealmTabEntry_o->oRoutServerList[hRealmTabEntry_o->unRoutingServerCount].oPeerIdentity,
                                &poServer->oPeerIdentity);
        hRealmTabEntry_o->unRoutingServerCount++;

		if(1 == hRealmTabEntry_o->unRoutingServerCount)
		{
			hRealmTabEntry_o->unPrimaryServer = 0;
			unMaxPriority = poServer->unPriority;
		}
		else if(unMaxPriority > poServer->unPriority)
		{
			hRealmTabEntry_o->unPrimaryServer = hRealmTabEntry_o->unRoutingServerCount -1;
			unMaxPriority = poServer->unPriority;
		}
		DMBase_SListGetNextNode(hDiamStackContext_io,poList, &poList);
    }

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


/******************************************************************************
** Function Name:
**			DMBase_SetStaticStatusInRealmTableEntry
**
** Description:
**		This function sets static status in realm table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HREALMTABLEENTRY hRealmTabEntry_o
**			type: output
**			detail: this is a realm table entry handle
**
** Return:
**		A t_DiamAPIReturnVal value specify whether static status is
**		successfully set in realm table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SetStaticStatusInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                           HREALMTABLEENTRY      hRealmTabEntry_o,
                                                           _Bool                 bIsStatic_i)
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hRealmTabEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }

    hRealmTabEntry_o->bIsStatic = bIsStatic_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}

/******************************************************************************
** Function Name:
**			DMBase_SetExpTimeInRealmTableEntry
**
** Description:
**		This function sets expiration time in realm table entry.
**
** Parameters:
**		  HDIAMETERSTACKCONTEXT hDiameterContext_io
**			 type: input/output
**			 detail : this is a diameter context handle.
**
**		  HREALMTABLEENTRY hRealmTabEntry_o
**			type: output
**			detail: this is a realm table entry handle
**
**		  t_DiamTime ExpiryTime_i
**			type:input
**			detail: this is expiration time of realm table entry.
** Return:
**		A t_DiamAPIReturnVal value specify whether expiration time is
**		successfully set in realm table entry or any problem occurred.
**
**
*******************************************************************************
** Created By: 		:
*******************************************************************************
*******************************************************************************
*/

t_DiamAPIReturnVal DMBase_SetExpTimeInRealmTableEntry(HDIAMETERSTACKCONTEXT hDiamStackContext_io,
                                                      HREALMTABLEENTRY      hRealmTabEntry_o,
                                                      t_DiamTime            oExpiryTime_i )
{
    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Entering.\n");

    if(NULL == hDiamStackContext_io || NULL == hRealmTabEntry_o)
    {
        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," NULL pointer not allowed\n");
        return DMBase_Retval_Null_Pointer;
    }
//    TODO: discuss about time format
//    hRealmTabEntry_o->oExpirationTime = oExpiryTime_i;

    DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO, " Leaving.\n");
    return DMBase_Retval_Success;
}


