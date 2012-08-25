ACLOCAL_AMFLAGS = -I m4

UN_VERSION=0
UN_REVISION=2
UN_AGE=0

SUBDIRS = po

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA = libuninameslist.pc libuninameslist-fr.pc

lib_LTLIBRARIES = 
lib_LTLIBRARIES += libuninameslist.la
lib_LTLIBRARIES += libuninameslist-fr.la
lib_LTLIBRARIES += libuninameslookup.la

include_HEADERS =
include_HEADERS += uninameslist.h

EXTRA_PROGRAMS = buildnameslist
EXTRA_SCRIPTS = make-names-list.awk

AM_CFLAGS = $(WARNING_CFLAGS)

dist_libuninameslist_la_SOURCES = nameslist.c nameslist.h
libuninameslist_la_LDFLAGS = -no-undefined -version-info	\
	$(UN_VERSION):$(UN_REVISION):$(UN_AGE)

dist_libuninameslist_fr_la_SOURCES = nameslist-fr.c nameslist.h
libuninameslist_fr_la_LDFLAGS = -no-undefined -version-info	\
	$(UN_VERSION):$(UN_REVISION):$(UN_AGE)

dist_libuninameslookup_la_SOURCES = codepoint_arrays.c	\
	uninameslookup_internal.h

buildnameslist_SOURCES = buildnameslist.c

nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt

rebuild-the-sources: rebuild-the-traditional-sources rebuild-the-new-sources

rebuild-the-traditional-sources: buildnameslist NamesList.txt ListeDesNoms.txt
	./buildnameslist
	test "$(builddir)/nameslist.c" -ef "$(srcdir)/nameslist.c" || \
		mv "$(builddir)/nameslist.c" "$(srcdir)/nameslist.c"
	test "$(builddir)/nameslist-fr.c" -ef "$(srcdir)/nameslist-fr.c" || \
		mv "$(builddir)/nameslist-fr.c" "$(srcdir)/nameslist-fr.c"
	test "$(builddir)/nameslist.h" -ef "$(srcdir)/nameslist.h" || \
		mv "$(builddir)/nameslist.h" "$(srcdir)/nameslist.h"

rebuild-the-new-sources: rebuild-codepoint_arrays

rebuild-codepoint_arrays: make-names-list.awk NamesList.utf8
	LC_ALL=en_US.UTF-8 $(AWK) -f $(srcdir)/make-names-list.awk NamesList.utf8 > $(srcdir)/codepoint_arrays.c

NamesList.latin1:
	$(WGET) "http://www.unicode.org/Public/UNIDATA/NamesList.txt" -O NamesList.latin1

NamesList.txt: NamesList.latin1
	$(ICONV) -f latin1 NamesList.latin1 -o NamesList.txt

NamesList.utf8: NamesList.latin1
	$(ICONV) -f latin1 NamesList.latin1 -t UTF-8 -o NamesList.utf8

ListeDesNoms.txt:
	$(WGET) "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt" -O ListeDesNoms.txt

EXTRA_DIST = config/config.rpath
DISTCLEANFILES = NamesList.latin1 NamesList.txt NamesList.utf8	\
	ListeDesNoms.txt buildnameslist
