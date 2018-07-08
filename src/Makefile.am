## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = sigmoid.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(SIGMOID_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

include_HEADERS = 
nodist_include_HEADERS = common.h

noinst_LTLIBRARIES = libcommon.la

libcommon_la_SOURCES = common.c

bin_PROGRAMS = sigmoid

sigmoid_SOURCES = \
	main.c \
	add.c \
	add.h \
	sigmoid.h \
	sigmoid.c	


sigmoid_LDFLAGS = \
	-Wl,--export-dynamic

sigmoid_LDADD = $(SIGMOID_LIBS)




EXTRA_DIST = $(ui_DATA)

MOSTLYCLEANFILES = *~ \#* .\#*
#DISTCLEANFILES = 

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

