
h_sources = dappcommon_helpers.h dappcommon_dbqueryload.h dappcommon_xmlutils.h dappcommon_srvrconfload.h

c_sources = dappcommon_dbqueryload.c dappcommon_xmlutils.c dappcommon_srvrconfload.c dappcommon_helpers.c 



library_includedir=$(includedir)/diameter/$(PACKAGE_NAME)/
library_include_HEADERS = $(h_sources)

INCLUDES = -I. -I$(includedir)/diameter -I$(top_srcdir)/include/amps -I$(top_srcdir)/include/libxml2

lib_LTLIBRARIES= libdiamappcommon.la
libdiamappcommon_la_SOURCES= $(h_sources) $(c_sources)
libdiamappcommon_la_LDFLAGS= -version-info $(LIBRARY_VERSION) -release $(RELEASE)
