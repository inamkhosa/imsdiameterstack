## top directory

#Build in these directories:
SUBDIRS= src

#Distribute these directories:
DIST_SUBDIRS = src

EXTRA_DIST=$(PACKAGE).spec $(PACKAGE).spec.in $(PACKAGE).pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(PACKAGE)-$(API_VERSION).pc
