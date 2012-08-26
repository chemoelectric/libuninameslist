ACLOCAL_AMFLAGS = -I m4

UN_VERSION=0
UN_REVISION=2
UN_AGE=0

UNLU_VERSION=1
UNLU_REVISION=0
UNLU_AGE=0

NAMESLIST_EN = "http://www.unicode.org/Public/UNIDATA/NamesList.txt"
NAMESLIST_EN_ENCODING = ISO-8859-1
NAMESLIST_FR = "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt"
NAMESLIST_FR_ENCODING = UTF-8

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA = libuninameslist.pc libuninameslist-fr.pc	\
	libuninameslookup.pc

lib_LTLIBRARIES = libuninameslist.la libuninameslist-fr.la	\
	libuninameslookup.la
include_HEADERS = uninameslookup.h uninameslist.h
pkgdata_DATA = en.names-db fr.names-db

EXTRA_PROGRAMS = buildnameslist
EXTRA_SCRIPTS = make-names-db.awk

MAKE_NAMES_DB = $(ENV) LC_ALL=C $(GAWK) -f $(srcdir)/make-names-db.awk

AM_CFLAGS = $(WARNING_CFLAGS)

dist_libuninameslist_la_SOURCES = nameslist.c nameslist.h
libuninameslist_la_LDFLAGS = -no-undefined -version-info	\
	$(UN_VERSION):$(UN_REVISION):$(UN_AGE)

dist_libuninameslist_fr_la_SOURCES = nameslist-fr.c nameslist.h
libuninameslist_fr_la_LDFLAGS = -no-undefined -version-info	\
	$(UN_VERSION):$(UN_REVISION):$(UN_AGE)

libuninameslookup_la_SOURCES = uninameslookup.c uninameslookup.h
libuninameslookup_la_LDFLAGS = -no-undefined -version-info	\
	$(UNLU_VERSION):$(UNLU_REVISION):$(UNLU_AGE)

buildnameslist_SOURCES = buildnameslist.c
buildnameslist_CFLAGS = $(WARNING_CFLAGS) $(EXTRA_WARNING_CFLAGS)

nodist_EXTRA_DATA = NamesList.latin1 NamesList.txt ListeDesNoms.txt

rebuild-the-sources: rebuild-the-traditional-sources rebuild-the-names-db

rebuild-the-traditional-sources: buildnameslist NamesList.txt ListeDesNoms.txt
	./buildnameslist
	test "$(builddir)/nameslist.c" -ef "$(srcdir)/nameslist.c" || \
		mv "$(builddir)/nameslist.c" "$(srcdir)/nameslist.c"
	test "$(builddir)/nameslist-fr.c" -ef "$(srcdir)/nameslist-fr.c" || \
		mv "$(builddir)/nameslist-fr.c" "$(srcdir)/nameslist-fr.c"
	test "$(builddir)/nameslist.h" -ef "$(srcdir)/nameslist.h" || \
		mv "$(builddir)/nameslist.h" "$(srcdir)/nameslist.h"

rebuild-the-names-db:
	$(MAKE_NAMES_DB) NamesList.txt > $(srcdir)/en.names-db
	$(MAKE_NAMES_DB) ListeDesNoms.txt > $(srcdir)/fr.names-db

NamesList.txt.download:
	$(WGET) $(NAMESLIST_EN) -O NamesList.txt.download

NamesList.txt: NamesList.txt.download
	$(ICONV) -f $(NAMESLIST_EN_ENCODING) NamesList.txt.download -t UTF-8 -o NamesList.txt

ListeDesNoms.txt.download:
	$(WGET) $(NAMESLIST_FR) -O ListeDesNoms.txt.download

ListeDesNoms.txt: ListeDesNoms.txt.download
	$(ICONV) -f $(NAMESLIST_FR_ENCODING) ListeDesNoms.txt.download -t UTF-8 -o ListeDesNoms.txt

MOSTLYCLEANFILES = buildnameslist
DISTCLEANFILES = NamesList.txt.download NamesList.txt	\
	ListeDesNoms.txt.download ListeDesNoms.txt
