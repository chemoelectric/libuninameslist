ACLOCAL_AMFLAGS = -I m4

UN_VERSION=0
UN_REVISION=2
UN_AGE=0

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA = libuninameslist.pc libuninameslist-fr.pc

lib_LTLIBRARIES = libuninameslist.la libuninameslist-fr.la
EXTRA_PROGRAMS = buildnameslist
include_HEADERS = uninameslist.h

AM_CFLAGS = $(WARNING_CFLAGS)

dist_libuninameslist_la_SOURCES = nameslist.c nameslist.h
libuninameslist_la_LDFLAGS = -no-undefined -version-info	\
	$(UN_VERSION):$(UN_REVISION):$(UN_AGE)

dist_libuninameslist_fr_la_SOURCES = nameslist-fr.c nameslist.h
libuninameslist_fr_la_LDFLAGS = -no-undefined -version-info	\
	$(UN_VERSION):$(UN_REVISION):$(UN_AGE)

buildnameslist_SOURCES = buildnameslist.c

nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt

rebuild-the-sources: buildnameslist NamesList.txt ListeDesNoms.txt
	./buildnameslist
	test "$(builddir)/nameslist.c" -ef "$(srcdir)/nameslist.c" || \
		mv "$(builddir)/nameslist.c" "$(srcdir)/nameslist.c"
	test "$(builddir)/nameslist-fr.c" -ef "$(srcdir)/nameslist-fr.c" || \
		mv "$(builddir)/nameslist-fr.c" "$(srcdir)/nameslist-fr.c"

NamesList.txt:
	$(WGET) "http://www.unicode.org/Public/UNIDATA/NamesList.txt" -O NamesList.latin1
	$(ICONV) -f latin1 NamesList.latin1 -o NamesList.txt

ListeDesNoms.txt:
	$(WGET) "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt" -O ListeDesNoms.txt

CLEANFILES = NamesList.latin1 NamesList.txt ListeDesNoms.txt buildnameslist
