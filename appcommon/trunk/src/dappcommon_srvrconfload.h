#ifndef	DAPPCOMMON_SRVCONFLOAD_H
#define DAPPCOMMON_SRVCONFLOAD_H

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "dmbase_data_types.h"
#include "dmbase_ampswrappers.h"
#include "dmbase_initconfig.h"
#include "dappcommon_helpers.h"

#define	DAPPCOMMON_MAX_COMMON_STR_SIZE	1024
#define	CX_APPLICATION_NAME				"Cx"
#define	SH_APPLICATION_NAME				"Sh"
#define	OCS_APPLICATION_NAME			"OCS"
#define	CDF_APPLICATION_NAME			"CDF"
#define	NASREQ_APPLICATION_NAME			"Nasreq"
#define	TRANSL_AGENT_APPLICATION_NAME	"Translation Agent"

#define	PRODUCT_NAME_HSS				"Home Subscriber Server"
#define	PRODUCT_NAME_CDF				"Offline Charging Server"
#define PRODUCT_NAME_OCS				"Online Charging Server"
#define	PRODUCT_NAME_NASREQ				"Nasreq Application Server"
#define PRODUCT_NAME_TRANS_AGENT		"Translation Agent"

typedef struct DappCommon_DBMSConfigParams
{
	unsigned char	pucHostName[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned char	pucUserName[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned char	pucPassword[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned char	pucDatabaseName[DAPPCOMMON_MAX_COMMON_STR_SIZE];
}t_DappCommon_DBMSConfigParams;

typedef struct DappCommon_SNMPConfigParams
{
	unsigned char	pucListenerIP[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned char	pucTrapIP[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned int	unListenerPort;
	unsigned int	unTrapPort;
}t_DappCommon_SNMPConfigParams;



typedef struct ModuleInfo
{
	char							pchModuleName[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	char							pchModuleFullPath[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	void*							pvModContext;
	_Bool							bLoadModule;
} t_ModuleInfo;


//TODO!!! Remove Config from the name of all param structs 
//and make it meaningful!!!!!
// 

typedef struct snmp_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	t_DappCommon_SNMPConfigParams	oSNMPConfigParams;
}t_snmp_config_params;

typedef struct hss_db_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	t_DappCommon_DBMSConfigParams	oDBMSConfigParams;
}t_hss_db_config_params;


typedef struct ocs_db_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	t_DappCommon_DBMSConfigParams	oDBMSConfigParams;
}t_ocs_db_config_params;


typedef struct cdf_db_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	t_DappCommon_DBMSConfigParams	oDBMSConfigParams;
}t_cdf_db_config_params;



typedef struct nasreq_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
}t_nasreq_config_params;

typedef struct transagent_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
}t_transagent_config_params;

typedef struct ocs_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
}t_ocs_config_params;

typedef struct cdf_CdrFile_config_params
{
	unsigned int 					unFileRotationType;
	unsigned int 					unMaxNumCdrsInOneFile;
	unsigned int 					unRotationTimerValueInMinutes;
	unsigned int 					unFileRunningCount;
	_Bool							bUTCDifferentialSign; // one for plus sign  and 0 for mins sign
	unsigned int 					nUTCDifferentialHour;
	unsigned int 					nUTCDifferentialMinute;
	unsigned char					pucCdrFileDirectoryName[DAPPCOMMON_MAX_COMMON_STR_SIZE];
}t_cdf_CdrFile_config_params;



typedef struct cdf_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	t_cdf_CdrFile_config_params		ocdf_CdrFile_config_params;
	t_DappCommon_DBMSConfigParams	oDBMSConfigParams;
}t_cdf_config_params;


typedef struct sh_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	unsigned char					pucParam1[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned char					pucParam2[DAPPCOMMON_MAX_COMMON_STR_SIZE];
}t_sh_config_params;

typedef struct cx_config_params
{
	HDIAMETERSTACKCONTEXT			hDiameterStackContext;
	unsigned char					pucParam1[DAPPCOMMON_MAX_COMMON_STR_SIZE];
	unsigned char					pucParam2[DAPPCOMMON_MAX_COMMON_STR_SIZE];
}t_cx_config_params;


typedef struct Dappcommon_AppPath
{
	unsigned char ucDatadir[1024];
	unsigned char ucLibdir[1024];
}t_Dappcommon_AppPath;

t_DappCommonReturnVal DappCommon_ProcessListenersNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);


t_DappCommonReturnVal DappCommon_ProcessListenerInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);


t_DappCommonReturnVal	DappCommon_LoadServerConfigParamsFromFile(
								HDIAMETERSTACKCONTEXT  			hDiameterStackContext_io,
								t_DiamOctetString 				oAppConfigFile_i,
								t_Dappcommon_AppPath* 			poAppPath_i,
								t_DiaStackInitData* 			poDiaInitData_o,
								DMBase_SList**  				ppListOfModInfo_o);


t_DappCommonReturnVal DappCommon_ProcessTransportDetailsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);


t_DappCommonReturnVal DappCommon_ProcessDiamApplicationNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o,
									     DMBase_SList**  ppListOfModInfo_o);

t_DappCommonReturnVal DappCommon_ProcessDBModuleConfigNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o,
									     DMBase_SList**  ppListOfModInfo_o,
										 unsigned char*	pucProductName_i);

t_DappCommonReturnVal DappCommon_ProcessDBMS_ConfigNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
									 xmlDocPtr poXmlDoc, 
									 xmlNodePtr poCurrXMLNode,
									 t_DappCommon_DBMSConfigParams*	poDBMSConfParams_o);


t_DappCommonReturnVal DappCommon_ProcessRealmTableEntriesNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);

t_DappCommonReturnVal DappCommon_ProcessServerNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 DMBase_SList **ppoServerList);

t_DappCommonReturnVal DappCommon_ProcessDictionaryFileNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);



t_DappCommonReturnVal DappCommon_ProcessPeerTableEntriesNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);


t_DappCommonReturnVal DappCommon_ProcessRealmInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);

t_DappCommonReturnVal DappCommon_ProcessPeerInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o);

t_DappCommonReturnVal DappCommon_ProcessModuleInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_ModuleInfo*	poModInfo_o);


t_DappCommonReturnVal DappCommon_LoadDiamAppModules(HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 DMBase_SList*  pListOfModInfo_i ,
										_Bool bExitOnModFail_i);

t_DappCommonReturnVal DappCommon_ProcessMiscModuleNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o);

t_DappCommonReturnVal DappCommon_ProcessMiscModuleInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o);

t_DappCommonReturnVal DappCommon_ProcessDiameterStackParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
								xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 t_DiaStackInitData* poDiaInitData_o,
										 DMBase_SList**	ppListOfModInfo_o  );

t_DappCommonReturnVal DappCommon_ProcessAppModuleNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o);

t_DappCommonReturnVal DappCommon_ProcessAppModuleInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
								t_Dappcommon_AppPath* poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o);

t_DappCommonReturnVal DappCommon_ProcessApplicationInfoNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  t_DiaStackInitData* poDiaInitData_o);

t_DappCommonReturnVal DappCommon_Process_Sh_SpecificParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 unsigned char** ppucParam1_o,
										 unsigned char** ppucParam2_o);

t_DappCommonReturnVal DappCommon_Process_Cdf_SpecificParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
																 xmlDocPtr poXmlDoc,
																 xmlNodePtr poCurrXMLNode,
																 t_cdf_CdrFile_config_params*		pocdf_CdrFile_config_params_o);

t_DappCommonReturnVal DappCommon_Process_Cx_SpecificParamsNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										 unsigned char** ppucParam1_o,
										 unsigned char** ppucParam2_o);


t_DappCommonReturnVal DappCommon_ProcessSNMPConfigNode (HDIAMETERSTACKCONTEXT hDiameterStackContext_io ,
							t_Dappcommon_AppPath* 	poAppPath_i,
										 xmlDocPtr poXmlDoc, 
										 xmlNodePtr poCurrXMLNode,
										  DMBase_SList**  ppListOfModInfo_o
										  );



#endif //#define DAPPCOMMON_SRVCONFLOAD_H
