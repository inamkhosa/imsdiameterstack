


#include "dappcommon_srvrconfload.h"
#include <unistd.h>



extern int g_nDiamBaseTraceID;


t_DappCommonReturnVal	DappCommon_LoadServerConfigParamsFromFile(
								HDIAMETERSTACKCONTEXT  			hDiameterStackContext_io,
								t_DiamOctetString 				oAppConfigFile_i,
								t_Dappcommon_AppPath* 			poAppPath_i,
								t_DiaStackInitData* 			poDiaInitData_o,
								DMBase_SList**  				ppListOfModInfo_o
							)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	xmlDocPtr poXmlDoc = NULL;
	xmlNodePtr poCurrXMLNode = NULL;

	poXmlDoc = xmlParseFile( oAppConfigFile_i.pucOctetString );

	if (NULL == poXmlDoc )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! poXmlDoc is NULL , leaving .\n");
		return DappCommon_Retval_Failure;
	}

	poCurrXMLNode = xmlDocGetRootElement(poXmlDoc);

	if (NULL == poCurrXMLNode)
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! poCurrXMLNode is NULL , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DappCommon_Retval_Failure;
	}

	if (NULL == ppListOfModInfo_o)
	{

		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! ppListOfModInfo_o is NULL , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DappCommon_Retval_Failure;
	}

	if (xmlStrcmp(poCurrXMLNode->name, (const xmlChar *) "DiameterServerConfiguration"))
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," Error! XML document of wrong type , leaving .\n");
		xmlFreeDoc(poXmlDoc);
		return DappCommon_Retval_Failure;
	}

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

	xmlChar *					poXMLKey = NULL;

	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"HostName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString(&( poDiaInitData_o->oHostName),
											poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"HostIPAddress")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_SetIPAddressInDiameterContext(hDiameterStackContext_io,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"HostRealm")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString(&( poDiaInitData_o->oRealmName),
											poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"TcTimerVal")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			poDiaInitData_o->unTcTimer = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ProductName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString(&( poDiaInitData_o->oProductName),
											poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"VendorID")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			poDiaInitData_o->unVendorID = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"LogFileName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString(&( poDiaInitData_o->oDiamAPILogFileName),
											poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"LogLevel")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			poDiaInitData_o->unDiamAPILogLevel = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Listeners")))
		{
			DappCommon_ProcessListenersNode(hDiameterStackContext_io,poXmlDoc,poCurrXMLNode,
								 poDiaInitData_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"DatabaseModuleConfig")))
		{
			DappCommon_ProcessDBModuleConfigNode (hDiameterStackContext_io, poAppPath_i, poXmlDoc, poCurrXMLNode ,
					poDiaInitData_o , ppListOfModInfo_o,
				     poDiaInitData_o->oProductName.pucOctetString);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"DiameterApplication")))
		{
			DappCommon_ProcessDiamApplicationNode (hDiameterStackContext_io, poAppPath_i, poXmlDoc,
							poCurrXMLNode , poDiaInitData_o , ppListOfModInfo_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"MiscModules")))
		{
			DappCommon_ProcessMiscModuleNode (hDiameterStackContext_io, poAppPath_i, poXmlDoc,
								   poCurrXMLNode  , ppListOfModInfo_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"SNMPConfig")))
		{
			DappCommon_ProcessSNMPConfigNode (hDiameterStackContext_io, poAppPath_i, poXmlDoc,
											  poCurrXMLNode,ppListOfModInfo_o );
		}

		poCurrXMLNode = poCurrXMLNode->next;
	}//end while

	xmlFreeDoc(poXmlDoc);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}


t_DappCommonReturnVal DappCommon_ProcessListenersNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ListenerInfo")))
		{
			DappCommon_ProcessListenerInfoNode(hDiameterStackContext_io,poXmlDoc,poCurrXMLNode,poDiaInitData_o);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}


t_DappCommonReturnVal DappCommon_ProcessListenerInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"TransportDetails")))
		{
			DappCommon_ProcessTransportDetailsNode(hDiameterStackContext_io,poXmlDoc,poCurrXMLNode,poDiaInitData_o);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessTransportDetailsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");
	unsigned int 		unport = 0;
	t_DiamOctetString	oTempIP;
	t_DiamOctetString	oTempFQDN;
	xmlChar*			poXMLKey = NULL;



	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IPAddress")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempIP,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Port")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unport = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"FQDN")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempFQDN,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IpAddrType")))
		{
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	//add to the initdata

	HTRANSPORTOBJECT hTransportObj = NULL;

	DMBase_CreateTransportObject(	hDiameterStackContext_io, &hTransportObj, TCP, oTempFQDN, oTempIP,
									unport, IP_v4, NULL);

	DMBase_AppendSList(hDiameterStackContext_io, &poDiaInitData_o->pListOfListenAddresses, hTransportObj);

	DMBase_DeleteDiamString(&oTempFQDN);
	DMBase_DeleteDiamString(&oTempIP);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessDiamApplicationNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o,
										 DMBase_SList**	ppListOfModInfo_o  )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

	unsigned char	pucTempAppName[DAPPCOMMON_MAX_COMMON_STR_SIZE] = {0};

	unsigned char*	pucTempShParam1 = NULL;
	unsigned char*	pucTempShParam2= NULL;
	unsigned char*	pucTempCxParam1 = NULL;
	unsigned char*	pucTempCxParam2  = NULL;
	t_cdf_CdrFile_config_params		ocdf_CdrFile_config_params = {0};
	

	xmlChar*		poXMLKey = NULL;
	DMBase_SList*	pLocalListModInfo = NULL;

	while (poCurrXMLNode != NULL)
	{

		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"DiameterStackParams")))
		{
			DappCommon_ProcessDiameterStackParamsNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,
									  poCurrXMLNode,poDiaInitData_o,ppListOfModInfo_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ApplicationName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(pucTempAppName,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"AppModules")))
		{
			DappCommon_ProcessAppModuleNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,
										poCurrXMLNode, &pLocalListModInfo );
		}
		/*

		note:
			Add your own application specific nodes information similiar
			to the pattern shown below for Sh and Cx , i.e. you need to:

			1) Add an else if here corresponding to your tag in XML
			2) Write a function for handling it
			3) Call it in else if
			4)Handle it below outside this while loop
			5) Make changes to your config struct so that your new params get into it
			6) Make changes to the mod_init function of your module(s) to get
			   that structure correctly

        */
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"CDRFileConfiguration")))
		{
            
			DappCommon_Process_Cdf_SpecificParamsNode(hDiameterStackContext_io,poXmlDoc,
													  poCurrXMLNode,
													  &ocdf_CdrFile_config_params);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"MyDummySh-Params")))
		{
			DappCommon_Process_Sh_SpecificParamsNode(hDiameterStackContext_io,poXmlDoc,
										poCurrXMLNode, &pucTempShParam1 , &pucTempShParam2 );
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"MyDummyCx-Params")))
		{
			DappCommon_Process_Cx_SpecificParamsNode(hDiameterStackContext_io,poXmlDoc,
						poCurrXMLNode, &pucTempCxParam1 , &pucTempCxParam2 );
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	void*	pvAppModContext = NULL;

	if (0 == strncmp(pucTempAppName, SH_APPLICATION_NAME, DAPPCOMMON_MAX_COMMON_STR_SIZE))
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvAppModContext ,
						sizeof(t_sh_config_params));

		((t_sh_config_params*)pvAppModContext)->hDiameterStackContext = hDiameterStackContext_io;

		strncpy( ((t_sh_config_params*)pvAppModContext)->pucParam1,
				 pucTempShParam1, DAPPCOMMON_MAX_COMMON_STR_SIZE);

		strncpy( ((t_sh_config_params*)pvAppModContext)->pucParam2,
				 pucTempShParam2, DAPPCOMMON_MAX_COMMON_STR_SIZE);
	}
	else if (0 == strncmp(pucTempAppName, CX_APPLICATION_NAME, DAPPCOMMON_MAX_COMMON_STR_SIZE) )
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvAppModContext ,
						sizeof(t_cx_config_params));

		((t_cx_config_params*)pvAppModContext)->hDiameterStackContext = hDiameterStackContext_io;

		strncpy( ((t_cx_config_params*)pvAppModContext)->pucParam1,
				 pucTempCxParam1, DAPPCOMMON_MAX_COMMON_STR_SIZE);

		strncpy( ((t_cx_config_params*)pvAppModContext)->pucParam2,
				 pucTempCxParam2, DAPPCOMMON_MAX_COMMON_STR_SIZE);
	}
	else if (0 == strncmp(pucTempAppName, OCS_APPLICATION_NAME, DAPPCOMMON_MAX_COMMON_STR_SIZE) )
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvAppModContext ,
						sizeof(t_ocs_config_params));

		((t_ocs_config_params*)pvAppModContext)->hDiameterStackContext = hDiameterStackContext_io;

	}
	else if (0 == strncmp(pucTempAppName, CDF_APPLICATION_NAME, DAPPCOMMON_MAX_COMMON_STR_SIZE) )
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvAppModContext ,
						sizeof(t_cdf_config_params));

		((t_cdf_config_params*)pvAppModContext)->hDiameterStackContext = hDiameterStackContext_io;
		((t_cdf_config_params*)pvAppModContext)->ocdf_CdrFile_config_params = ocdf_CdrFile_config_params;

	}
	else if (0 == strncmp(pucTempAppName, NASREQ_APPLICATION_NAME, DAPPCOMMON_MAX_COMMON_STR_SIZE))
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvAppModContext ,
						sizeof(t_nasreq_config_params));

		((t_nasreq_config_params*)pvAppModContext)->hDiameterStackContext = hDiameterStackContext_io;

	}
	else if (0 == strncmp(pucTempAppName, TRANSL_AGENT_APPLICATION_NAME, DAPPCOMMON_MAX_COMMON_STR_SIZE))
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvAppModContext ,
						sizeof(t_transagent_config_params));

		((t_transagent_config_params*)pvAppModContext)->hDiameterStackContext = hDiameterStackContext_io;

	}
	else
	{
		pvAppModContext = hDiameterStackContext_io;
	}

	//get each node from the local modules list and add to the supplied
	//module list by putting the correct context in as well


	DMBase_SList*		pCurrentNode = NULL;


   for(pCurrentNode = pLocalListModInfo; NULL != pCurrentNode;DMBase_SListGetNextNode(hDiameterStackContext_io, pCurrentNode, &pCurrentNode))
   {

	   t_ModuleInfo*	pTempModInfo = NULL;

	   DMBase_SListGetNodeData(hDiameterStackContext_io, pCurrentNode, (void**) &pTempModInfo);

	   pTempModInfo->pvModContext = pvAppModContext;

	   DMBase_AppendSList(hDiameterStackContext_io,ppListOfModInfo_o,
					   (void*) pTempModInfo);

   }//end for



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessRealmTableEntriesNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"RealmInfo")))
		{
			DappCommon_ProcessRealmInfoNode(hDiameterStackContext_io,poXmlDoc,poCurrXMLNode,poDiaInitData_o);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}
t_DappCommonReturnVal DappCommon_ProcessRealmInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

	xmlChar*			poXMLKey = NULL;
	t_DiamOctetString	oTempRealmName;
	unsigned int		unTempAppID = 0;
	t_LocalAction		oTempLocAction ;
        DMBase_SList            *poServerList = NULL;

	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"RealmName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempRealmName,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ApplicationID")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unTempAppID = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"LocalAction")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"local") )
			{
				oTempLocAction = LOCAL;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"proxy") )
			{
				oTempLocAction = PROXY;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"redirect") )
			{
				oTempLocAction = REDIRECT;
			}
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"relay") )
			{
				oTempLocAction = RELAY;
			}
			xmlFree(poXMLKey);
		}
                else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Server")))
                {
                    DappCommon_ProcessServerNode(hDiameterStackContext_io ,poXmlDoc, poCurrXMLNode,&poServerList);
                }

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	//insert data into realm table

	HREALMTABLEENTRY hReamlTableEntry = NULL;

	DMBase_CreateRealmTableEntry(hDiameterStackContext_io,
								&hReamlTableEntry,
								oTempRealmName,
								unTempAppID,
								1,
								oTempLocAction,
								poServerList);

	DMBase_AppendSList(hDiameterStackContext_io, &poDiaInitData_o->pListOfRealmEntries, hReamlTableEntry);

	DMBase_DeleteDiamString(&oTempRealmName);

        DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessServerNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 DMBase_SList **ppoServerList)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

        poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;

        xmlChar*         poXMLKey = NULL;
        t_RoutingServer* poServer = NULL;
        DMBase_Malloc(hDiameterStackContext_io, (void**)&poServer, sizeof(t_RoutingServer));

	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Priority")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			poServer->unPriority = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ServerID")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &poServer->oPeerIdentity,poXMLKey);
			xmlFree(poXMLKey);
		}

                poCurrXMLNode = poCurrXMLNode->next;
        }

        DMBase_AppendSList(hDiameterStackContext_io, ppoServerList, poServer);

 	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DappCommon_Retval_Success;
}
t_DappCommonReturnVal DappCommon_ProcessDictionaryFileNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	xmlChar*	poXMLKey = NULL;
	t_DiamOctetString	oTempDicPathName;
	_Bool	bIsPathAbsolute = 0;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"FilePathAndName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempDicPathName,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IsPathAbsolute")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"yes") )
			{
				bIsPathAbsolute = 1;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bIsPathAbsolute = 0;
			}
			xmlFree(poXMLKey);
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	t_DiamOctetString*	poDiamDictFileForInitData = NULL;
	//this is the string that will go to initData , alloc for it

	DMBase_Malloc(hDiameterStackContext_io,(void**) &poDiamDictFileForInitData , sizeof(t_DiamOctetString));

	//find the correct path
	if (0 == bIsPathAbsolute )
	{
		//relative given , make it absolute
		/*unsigned char	pchCWD[1024] = {0};


		if ( NULL == getcwd(pchCWD,1024 ) )
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "getcwd failed.\n");
			return DappCommon_Retval_Failure;
		}*/

		DMBase_CopyCharArrayToDiamString(poDiamDictFileForInitData,poAppPath_i->ucDatadir);
		//DMBase_AppendCharStringToDiamString(poDiamDictFileForInitData,"/");
		DMBase_AppendDiamStringToDiamString(poDiamDictFileForInitData,&oTempDicPathName);
	}
	else
	{
		//already absolute just copy
		DMBase_CopyDiamString(poDiamDictFileForInitData,&oTempDicPathName);
	}

	//add to init data
	DMBase_AppendSList(hDiameterStackContext_io,&(poDiaInitData_o->pListOfDictionaryFileNames),
					   (void*) poDiamDictFileForInitData);



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessPeerTableEntriesNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"PeerInfo")))
		{
			DappCommon_ProcessPeerInfoNode(hDiameterStackContext_io,poXmlDoc,poCurrXMLNode,poDiaInitData_o);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessPeerInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	xmlChar*	poXMLKey = NULL;
	t_DiamOctetString	oTempHostId;
	t_DiamOctetString	oTempIPAddr;
	unsigned int		unTempPort;
	t_PeerRole			oTempConfigRole;
	unsigned short usWatchDogSupported = 1;
	unsigned int		unWatchDogTimerDelay = 0;

	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"HostIdentity")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempHostId,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IPAddress")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempIPAddr,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Port")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unTempPort = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Role")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"initiator") )
			{
				oTempConfigRole = Initiator;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"responder") )
			{
				oTempConfigRole = Responder;
			}

			xmlFree(poXMLKey);
		}
                else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"WatchDogSupport")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				usWatchDogSupported = 0;
			}
                        else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"yes") )
			{
				usWatchDogSupported = 1;
			}

			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"WatchDogTimerDelay")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unWatchDogTimerDelay = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}


		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	//add to init data

	HPEERTABLEENTRY hPeerTableEntry = NULL;
	DMBase_CreatePeerTableEntry(hDiameterStackContext_io,
								&hPeerTableEntry,
								oTempHostId,
								oTempIPAddr,
								unTempPort,
								oTempConfigRole,
								1,
								0,
								usWatchDogSupported,
								unWatchDogTimerDelay);

	DMBase_AppendSList(hDiameterStackContext_io, &poDiaInitData_o->pListOfStaticPeers, hPeerTableEntry);

	DMBase_DeleteDiamString(&oTempHostId);
	DMBase_DeleteDiamString(&oTempIPAddr);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessModuleInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_ModuleInfo*	poModInfo_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	xmlChar*			poXMLKey = NULL;
	t_DiamOctetString	oTempModuleName;
	t_DiamOctetString	oTempModulePathFromFile;
	_Bool				bIsPathAbsolute = 0;
	_Bool				bLoadModule = 1;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempModuleName,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleFilePath")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempModulePathFromFile,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IsPathAbsolute")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"yes") )
			{
				bIsPathAbsolute = 1;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bIsPathAbsolute = 0;
			}
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"LoadModule")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bLoadModule = 0;
			}
			else
			{
				bLoadModule = 1;
			}
			xmlFree(poXMLKey);
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	t_DiamOctetString	oTempFullModulePath={0};

	//find the correct path
	if (0 == bIsPathAbsolute )
	{
		//relative given , make it absolute
		/*unsigned char	pchCWD[DAPPCOMMON_MAX_COMMON_STR_SIZE] = {0};


		if ( NULL == getcwd(pchCWD,DAPPCOMMON_MAX_COMMON_STR_SIZE ) )
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "getcwd failed.\n");
			return DappCommon_Retval_Failure;
		}*/

		DMBase_CopyCharArrayToDiamString(&oTempFullModulePath,poAppPath_i->ucLibdir);
		//DMBase_AppendCharStringToDiamString(&oTempFullModulePath,"/");
		//DMBase_AppendDiamStringToDiamString(&oTempFullModulePath,&oTempModulePathFromFile);
	}
	else
	{
		//already absolute just copy
		DMBase_CopyDiamString(&oTempFullModulePath,&oTempModulePathFromFile);
	}

	//prepare object

	strncpy(poModInfo_o->pchModuleName,oTempModuleName.pucOctetString,DAPPCOMMON_MAX_COMMON_STR_SIZE);
	strncpy(poModInfo_o->pchModuleFullPath,oTempFullModulePath.pucOctetString,DAPPCOMMON_MAX_COMMON_STR_SIZE);
	poModInfo_o->bLoadModule = bLoadModule;

	DMBase_DeleteDiamString(&oTempFullModulePath);
	DMBase_DeleteDiamString(&oTempModuleName);
	DMBase_DeleteDiamString(&oTempModulePathFromFile);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_LoadDiamAppModules(HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							DMBase_SList*  pListOfModInfo_i ,_Bool bExitOnModFail_i )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering \n");

	if ( NULL == pListOfModInfo_i )
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"  pListOfModInfo_i is NULL , Leaving \n");
		return DappCommon_Retval_Null_Pointer;
	}

	DMBase_SList*	pCurrentNode = NULL;
	t_ModuleInfo*	pCurrModInfo = NULL;

   for(pCurrentNode = pListOfModInfo_i ; NULL != pCurrentNode;DMBase_SListGetNextNode(hDiameterStackContext_io, pCurrentNode, &pCurrentNode))
   {
	    pCurrModInfo = NULL;
	    DMBase_SListGetNodeData(hDiameterStackContext_io, pCurrentNode, (void**) &pCurrModInfo);

		if (1 == pCurrModInfo->bLoadModule)
		{
			if (NULL == AMPS_SetupLoadableModule(hDiameterStackContext_io->hFrameworkHandle,
												 pCurrModInfo->pchModuleFullPath,
												 pCurrModInfo->pchModuleName ,pCurrModInfo->pvModContext))
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR,"  Unable to Load Module \n");
				//printf("%s\r\n%s\r\n", pCurrModInfo->pchModuleName, pCurrModInfo->pchModuleFullPath);
				if (1 == bExitOnModFail_i)
				{
					return DappCommon_Retval_Failure;
				}
			}
			else
			{
				DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO,"  Module Loaded Successfully \n");
			}
		}//end if (1 == pCurrModInfo->bLoadModule)

   }//end for


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");

	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessMiscModuleNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleInfo")))
		{
			DappCommon_ProcessMiscModuleInfoNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,
									  poCurrXMLNode,ppListOfModInfo_o);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


}

t_DappCommonReturnVal DappCommon_ProcessMiscModuleInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	xmlChar*			poXMLKey = NULL;
	t_DiamOctetString	oTempModuleName;
	t_DiamOctetString	oTempModulePathFromFile;
	_Bool				bIsPathAbsolute = 0;
	_Bool				bLoadModule = 0;

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempModuleName,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleFilePath")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempModulePathFromFile,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IsPathAbsolute")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"yes") )
			{
				bIsPathAbsolute = 1;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bIsPathAbsolute = 0;
			}
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"LoadModule")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bLoadModule = 0;
			}
			else
			{
				bLoadModule = 1;
			}
			xmlFree(poXMLKey);
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	t_ModuleInfo*	poModInfo = NULL;
	//alloc for it , this has to go in the linked list of module Infos

	DMBase_Malloc(hDiameterStackContext_io,(void**) &poModInfo , sizeof(t_ModuleInfo));
	poModInfo->pvModContext = hDiameterStackContext_io;

	t_DiamOctetString	oTempFullModulePath;

	//find the correct path
	if (0 == bIsPathAbsolute )
	{
		//relative given , make it absolute
		/*unsigned char	pchCWD[1024] = {0};


		if ( NULL == getcwd(pchCWD,1024 ) )
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "getcwd failed.\n");
			return DappCommon_Retval_Failure;
		}*/

		DMBase_CopyCharArrayToDiamString(&oTempFullModulePath,poAppPath_i->ucLibdir);
		//DMBase_AppendCharStringToDiamString(&oTempFullModulePath,"/");
		//DMBase_AppendDiamStringToDiamString(&oTempFullModulePath,&oTempModulePathFromFile);
	}
	else
	{
		//already absolute just copy
		DMBase_CopyDiamString(&oTempFullModulePath,&oTempModulePathFromFile);
	}

	//prepare object

	strncpy(poModInfo->pchModuleName,oTempModuleName.pucOctetString,DAPPCOMMON_MAX_COMMON_STR_SIZE);
	strncpy(poModInfo->pchModuleFullPath,oTempFullModulePath.pucOctetString,DAPPCOMMON_MAX_COMMON_STR_SIZE);
	poModInfo->bLoadModule = bLoadModule;

	//add to link list
	DMBase_AppendSList(hDiameterStackContext_io,ppListOfModInfo_o,
					   (void*) poModInfo);

	DMBase_DeleteDiamString(&oTempFullModulePath);
	DMBase_DeleteDiamString(&oTempModuleName);
	DMBase_DeleteDiamString(&oTempModulePathFromFile);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;

}

t_DappCommonReturnVal DappCommon_ProcessDBModuleConfigNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o,
									     DMBase_SList**  ppListOfModInfo_o,
										 unsigned char*	pucProductName_i)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	t_DappCommon_DBMSConfigParams	oTempDBMSConfParams = {0};
	t_ModuleInfo*					poModInfo = NULL;


	DMBase_Malloc(hDiameterStackContext_io,(void**) &poModInfo , sizeof(t_ModuleInfo));


	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleInfo")))
		{
			DappCommon_ProcessModuleInfoNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,poCurrXMLNode,
								  poModInfo);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"DBMS_Configuration")))
		{
			DappCommon_ProcessDBMS_ConfigNode(hDiameterStackContext_io,poXmlDoc,poCurrXMLNode,
								   &oTempDBMSConfParams);
		}
		/*

		note:

		Add any further parsing logic specific to some particular dbconfig node
		over here


        */
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	/*
	   Add further logic regarding which type of db config data structure
	   to allocate memory for in the logic below
    */

	void*	pvDBModContext = NULL;

	if (0 == strcmp(pucProductName_i, PRODUCT_NAME_HSS) )
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvDBModContext ,
						sizeof(t_hss_db_config_params));

		((t_hss_db_config_params*)pvDBModContext)->hDiameterStackContext = hDiameterStackContext_io;
		((t_hss_db_config_params*)pvDBModContext)->oDBMSConfigParams = oTempDBMSConfParams;
	}
	else if (0 == strcmp(pucProductName_i, PRODUCT_NAME_OCS) )
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvDBModContext ,
						sizeof(t_ocs_db_config_params));
		((t_ocs_db_config_params*)pvDBModContext)->hDiameterStackContext = hDiameterStackContext_io;
		((t_ocs_db_config_params*)pvDBModContext)->oDBMSConfigParams = oTempDBMSConfParams;
	}
	else if (0 == strcmp(pucProductName_i, PRODUCT_NAME_CDF) )
	{
		DMBase_Malloc(hDiameterStackContext_io,(void**) &pvDBModContext ,
						sizeof(t_cdf_db_config_params));
		((t_cdf_db_config_params*)pvDBModContext)->hDiameterStackContext = hDiameterStackContext_io;
		((t_cdf_db_config_params*)pvDBModContext)->oDBMSConfigParams = oTempDBMSConfParams;
	}

	poModInfo->pvModContext = pvDBModContext;

	//add to link list
	DMBase_AppendSList(hDiameterStackContext_io,ppListOfModInfo_o,
					   (void*) poModInfo);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessDBMS_ConfigNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							 xmlDocPtr poXmlDoc,
							 xmlNodePtr poCurrXMLNode,
							 t_DappCommon_DBMSConfigParams*		poDBMSConfParams_o)
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	xmlChar *					poXMLKey = NULL;

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"HostName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(poDBMSConfParams_o->pucHostName,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
            xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"UserName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(poDBMSConfParams_o->pucUserName,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"Password")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(poDBMSConfParams_o->pucPassword,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"DatabaseName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(poDBMSConfParams_o->pucDatabaseName,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}

t_DappCommonReturnVal DappCommon_ProcessDiameterStackParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o,
										 DMBase_SList**	ppListOfModInfo_o  )
{
	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;
	while (poCurrXMLNode != NULL)
	{

		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ApplicationInfo")))
		{
			DappCommon_ProcessApplicationInfoNode(hDiameterStackContext_io,poXmlDoc,
									  poCurrXMLNode,poDiaInitData_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"DictionaryFile")))
		{
			DappCommon_ProcessDictionaryFileNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,
									  poCurrXMLNode,poDiaInitData_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"PeerTableEntries")))
		{
			DappCommon_ProcessPeerTableEntriesNode(hDiameterStackContext_io,poXmlDoc,
										poCurrXMLNode,poDiaInitData_o);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"RealmTableEntries")))
		{
			DappCommon_ProcessRealmTableEntriesNode(hDiameterStackContext_io,poXmlDoc,
										 poCurrXMLNode,poDiaInitData_o);
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;
}
t_DappCommonReturnVal DappCommon_ProcessAppModuleNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleInfo")))
		{
			DappCommon_ProcessAppModuleInfoNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,
									  poCurrXMLNode,ppListOfModInfo_o);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


}

t_DappCommonReturnVal DappCommon_ProcessAppModuleInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
														   xmlDocPtr poXmlDoc,
														   xmlNodePtr poCurrXMLNode,
														   DMBase_SList**  ppListOfModInfo_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	xmlChar*			poXMLKey = NULL;
	t_DiamOctetString	oTempModuleName;
	t_DiamOctetString	oTempModulePathFromFile;
	_Bool				bIsPathAbsolute = 0;
	_Bool				bLoadModule = 0;

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempModuleName,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleFilePath")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			DMBase_CopyCharArrayToDiamString( &oTempModulePathFromFile,poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"IsPathAbsolute")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"yes") )
			{
				bIsPathAbsolute = 1;
			}
			else if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bIsPathAbsolute = 0;
			}
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"LoadModule")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"no") )
			{
				bLoadModule = 0;
			}
			else
			{
				bLoadModule = 1;
			}
			xmlFree(poXMLKey);
		}


		poCurrXMLNode = poCurrXMLNode->next;
	} //end while

	t_ModuleInfo*	poModInfo = NULL;
	//alloc for it , this has to go in the linked list of module Infos

	DMBase_Malloc(hDiameterStackContext_io,(void**) &poModInfo , sizeof(t_ModuleInfo));
	poModInfo->pvModContext = hDiameterStackContext_io;

	t_DiamOctetString	oTempFullModulePath;

	//find the correct path
	if (0 == bIsPathAbsolute )
	{
		//relative given , make it absolute
		/*unsigned char	pchCWD[1024] = {0};


		if ( NULL == getcwd(pchCWD,1024 ) )
		{
			DMBASE_TRACE( g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR, "getcwd failed.\n");
			return DappCommon_Retval_Failure;
		}*/

		DMBase_CopyCharArrayToDiamString(&oTempFullModulePath,poAppPath_i->ucLibdir);
		//DMBase_AppendCharStringToDiamString(&oTempFullModulePath,"/");
		//DMBase_AppendDiamStringToDiamString(&oTempFullModulePath,&oTempModulePathFromFile);
	}
	else
	{
		//already absolute just copy
		DMBase_CopyDiamString(&oTempFullModulePath,&oTempModulePathFromFile);
	}

	//prepare object

	strncpy(poModInfo->pchModuleName,oTempModuleName.pucOctetString,DAPPCOMMON_MAX_COMMON_STR_SIZE);
	strncpy(poModInfo->pchModuleFullPath,oTempFullModulePath.pucOctetString,DAPPCOMMON_MAX_COMMON_STR_SIZE);
	poModInfo->bLoadModule = bLoadModule;

	//add to link list
	DMBase_AppendSList(hDiameterStackContext_io,ppListOfModInfo_o,(void*) poModInfo);

	DMBase_DeleteDiamString(&oTempFullModulePath);
	DMBase_DeleteDiamString(&oTempModuleName);
	DMBase_DeleteDiamString(&oTempModulePathFromFile);

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DappCommon_Retval_Success;

}

t_DappCommonReturnVal DappCommon_ProcessApplicationInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
															 xmlDocPtr poXmlDoc,
															 xmlNodePtr poCurrXMLNode,
															 t_DiaStackInitData* poDiaInitData_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	xmlChar*			poXMLKey = NULL;

	unsigned int		unTempAppId = 0;
	unsigned int		unVendorID = 0;
	unsigned char		pucTempAppType[DAPPCOMMON_MAX_COMMON_STR_SIZE] = {0};



	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ApplicationID")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unTempAppId = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ApplicationType")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(pucTempAppType,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"VendorID")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			unVendorID = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


	t_DiamAppInfo	oTempDiamAppInfo = {0};

	oTempDiamAppInfo.unAppID = unTempAppId;
        oTempDiamAppInfo.unVendorID = unVendorID;


	if ( 0 == strncmp(pucTempAppType , "Authorization" , DAPPCOMMON_MAX_COMMON_STR_SIZE))
	{
		oTempDiamAppInfo.oAppType = Authorization_Application;
	}
	else if ( 0 == strncmp(pucTempAppType , "Accounting" , DAPPCOMMON_MAX_COMMON_STR_SIZE))
	{
		oTempDiamAppInfo.oAppType = Accounting_Application;
	}
	else
	{
		DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_ERROR," ERROR! Incorrect Application Type in config file => %s\n",pucTempAppType);
		return DappCommon_Retval_Failure;
	}

	DMBase_AddAppInfoToSupportedAppsList(hDiameterStackContext_io,oTempDiamAppInfo);


	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;

}

t_DappCommonReturnVal DappCommon_Process_Cx_SpecificParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 unsigned char** ppucParam1_o,
										 unsigned char** ppucParam2_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	xmlChar*			poXMLKey = NULL;




	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"param1")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);

			*ppucParam1_o = strdup(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"param2")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			*ppucParam2_o = strdup(poXMLKey);
			xmlFree(poXMLKey);
		}


		poCurrXMLNode = poCurrXMLNode->next;
	} //end while



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;

}

t_DappCommonReturnVal DappCommon_Process_Cdf_SpecificParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
																 xmlDocPtr poXmlDoc,
																 xmlNodePtr poCurrXMLNode,
																 t_cdf_CdrFile_config_params*		pocdf_CdrFile_config_params_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

	xmlChar*			poXMLKey = NULL;

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"CdrsFileDirectoryName")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(pocdf_CdrFile_config_params_o->pucCdrFileDirectoryName,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"FileRotationType")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"CdrBasedRotation") )
			{
				pocdf_CdrFile_config_params_o->unFileRotationType = 1;
			}
			else
			{
				pocdf_CdrFile_config_params_o->unFileRotationType= 2;
			}
            xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"MaxNumCdrsInOneFile")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			pocdf_CdrFile_config_params_o->unMaxNumCdrsInOneFile = atoi(poXMLKey);
            xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"RotationTimerVlaue")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			pocdf_CdrFile_config_params_o->unRotationTimerValueInMinutes = atoi(poXMLKey);
            xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"UTCDifferentialSign")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			if ( !xmlStrcmp(poXMLKey, (const xmlChar *)"+") )
			{
				pocdf_CdrFile_config_params_o->bUTCDifferentialSign = 1;
			}
			else
			{
				pocdf_CdrFile_config_params_o->bUTCDifferentialSign = 0;
			}
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"UTCDifferentialHour")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			pocdf_CdrFile_config_params_o->nUTCDifferentialHour = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"UTCDifferentialMinute")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			pocdf_CdrFile_config_params_o->nUTCDifferentialMinute = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		poCurrXMLNode = poCurrXMLNode->next;
	} //end while



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");
	return DappCommon_Retval_Success;

}



t_DappCommonReturnVal DappCommon_Process_Sh_SpecificParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc,
										 xmlNodePtr poCurrXMLNode,
										 unsigned char** ppucParam1_o,
										 unsigned char** ppucParam2_o)
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");


	xmlChar*			poXMLKey = NULL;




	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"param1")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);

			*ppucParam1_o = strdup(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"param2")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			*ppucParam2_o = strdup(poXMLKey);
			xmlFree(poXMLKey);
		}


		poCurrXMLNode = poCurrXMLNode->next;
	} //end while



	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


	return DappCommon_Retval_Success;

}



t_DappCommonReturnVal DappCommon_ProcessSNMPConfigNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o
										  )
{

	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Entering\n");

    
	t_DappCommon_SNMPConfigParams	oTempSNMPConfParams = {0};
	t_ModuleInfo*					poModInfo = NULL;
	xmlChar*						poXMLKey = NULL;


	DMBase_Malloc(hDiameterStackContext_io,(void**) &poModInfo , sizeof(t_ModuleInfo));

	poCurrXMLNode = poCurrXMLNode->xmlChildrenNode;


	while (poCurrXMLNode != NULL)
	{
		if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ListenerPort")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			oTempSNMPConfParams.unListenerPort = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ListenerIP")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(oTempSNMPConfParams.pucListenerIP,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"TrapPort")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			oTempSNMPConfParams.unTrapPort = atoi(poXMLKey);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"TrapIP")))
		{
			poXMLKey = xmlNodeListGetString(poXmlDoc, poCurrXMLNode->xmlChildrenNode, 1);
			strncpy(oTempSNMPConfParams.pucTrapIP,poXMLKey,DAPPCOMMON_MAX_COMMON_STR_SIZE);
			xmlFree(poXMLKey);
		}
		else if ((!xmlStrcmp(poCurrXMLNode->name, (const xmlChar *)"ModuleInfo")))
		{
			DappCommon_ProcessModuleInfoNode(hDiameterStackContext_io, poAppPath_i, poXmlDoc,poCurrXMLNode,
								  poModInfo);
		}

		poCurrXMLNode = poCurrXMLNode->next;
	} //end while


    void*	pvDBModContext = NULL;


	DMBase_Malloc(hDiameterStackContext_io,(void**) &pvDBModContext ,
					sizeof(t_snmp_config_params));
	((t_snmp_config_params*)pvDBModContext)->hDiameterStackContext = hDiameterStackContext_io;
	((t_snmp_config_params*)pvDBModContext)->oSNMPConfigParams = oTempSNMPConfParams;


	poModInfo->pvModContext = pvDBModContext;

	//add to link list
	DMBase_AppendSList(hDiameterStackContext_io,ppListOfModInfo_o,
					   (void*) poModInfo);





	DMBASE_TRACE(g_nDiamBaseTraceID, DMBASE_TRACE_LEVEL_INFO," Leaving\n");


}
