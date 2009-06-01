
h_sources = dmbase_ampswrappers.h dmbase_appcallbackreg.h dmbase_avp.h dmbase_cer_processing.h dmbase_data_types.h dmbase_debug.h dmbase_dictionary.h dmbase_failover_failback.h dmbase_initconfig.h dmbase_message.h dmbase_msgvalidate.h dmbase_parser.h dmbase_peer_mgmt.h dmbase_peerstatemachine.h dmbase_psm_actions.h dmbase_realmtablemgmt.h dmbase_transport_mgmt.h dmbase_utility.h dmbase_includes.h

c_sources = dmbase_ampswrappers.c dmbase_appcallbackreg.c dmbase_avp.c dmbase_cer_processing.c dmbase_debug.c dmbase_dictionary.c dmbase_failover_failback.c dmbase_initconfig.c dmbase_message.c dmbase_msgvalidate.c dmbase_parser.c dmbase_peer_mgmt.c dmbase_peerstatemachine.c dmbase_psm_actions.c dmbase_realmtablemgmt.c dmbase_transport_mgmt.c dmbase_utility.c



library_includedir=$(includedir)/$(PACKAGE_NAME)/
library_include_HEADERS = $(h_sources)

INCLUDES = -I. -I$(top_srcdir)/include/amps -I$(top_srcdir)/include/libxml2

lib_LTLIBRARIES= libdiameter.la
libdiameter_la_SOURCES= $(h_sources) $(c_sources)
libdiameter_la_LDFLAGS= -version-info $(LIBRARY_VERSION) -release $(RELEASE)
