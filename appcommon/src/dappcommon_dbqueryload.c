
#include <unistd.h>
#include "dappcommon_dbqueryload.h"



t_DappCommonReturnVal DappCommon_LoadDBQueryConfigFromFile(
										t_DiamOctetString oDBQueryConfigFile_i,
										t_Dappcommon_DBQueryMap*	poDBQueryMapArray_o,
										unsigned int	unDBMapArrSize_i
									 )
{

	xmlDocPtr poXmlDoc = NULL;
	xmlNodePtr poCurrXMLNode = NULL;

	if (NULL == poDBQueryMapArray_o ) 
	{
		printf(" Error! poDBQueryMapArray_o is NULL , leaving .\n");
		return DappCommon_Retval_Null_Pointer;
	}

	poXmlDoc = xmlParseFile( oDBQueryConfigFile_i.pucOctetString );

	if (NULL == poXmlDoc ) 
	{
		printf(" Error! poXmlDoc is NULL , leaving .\n");
		return DappCommon_Retval_Failure;
	}

	

	poCurrXMLNode = xmlDocGetRootElement(poXmlDoc);

	if (NULL == poCurrXMLNode) 
	{

		printf(" Error! poCurrXMLNode is NULL , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DappCommon_Retval_Failure;
	}

	if (xmlStrcmp(poCurrXMLNode->name, (const xmlChar *) "DiameterServerDatabaseQueryConfig")) 
	{
		printf(" Error! XML document of wrong type , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DappCommon_Retval_Failure;
	}

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

	xmlChar *					poXMLKey = NULL;

	while (poCurrXMLNode != NULL) 
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"QueryInfo")))
		{
			ProcessQueryInfoNode(poXmlDoc,poCurrXMLNode,poDBQueryMapArray_o,unDBMapArrSize_i);
		}
	
		poCurrXMLNode = poCurrXMLNode->next;
	}//end while 

	xmlFreeDoc(poXmlDoc);

	printf(" Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal ProcessQueryInfoNode (xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										t_Dappcommon_DBQueryMap*	poDBQueryMapArray_o,
										unsigned int	unDBMapArrSize_i
										 )
{

	
	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

	t_DiamOctetString	oTempQueryString = {0};
	t_DiamOctetString	oTempQueryName = {0};
	unsigned int		unTempQueryID = 0;

	xmlChar *					poXMLKey = NULL;

	
	while (poCurrXMLNode != NULL) 
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"QueryString")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempQueryString,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"QueryID")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unTempQueryID = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"QueryName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempQueryName,poXMLKey);
			xmlFree(poXMLKey);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	if ( unTempQueryID >= unDBMapArrSize_i)
	{
		printf("\n ERROR ! Ignoring QueryID == %d since it is equal to or greater than unDBMapArrSize_i == %d",unTempQueryID,unDBMapArrSize_i);
	}
	else
	{
		//stuff data into relevant array item
		poDBQueryMapArray_o[unTempQueryID].bIsInit = 1;
		poDBQueryMapArray_o[unTempQueryID].unQueryID = unTempQueryID;
		DMBase_CopyDiamString(&(poDBQueryMapArray_o[unTempQueryID].oQueryName),
							  &oTempQueryName);
		DMBase_CopyDiamString(&(poDBQueryMapArray_o[unTempQueryID].oQueryString),
							  &oTempQueryString);

	}


	DMBase_DeleteDiamString(&oTempQueryName);
	DMBase_DeleteDiamString(&oTempQueryString);


	return DappCommon_Retval_Success;
}






