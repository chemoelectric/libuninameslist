#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libuninameslist],[1.1.0_beta1],[fontforge-devel@lists.sourceforge.net])
AC_CONFIG_SRCDIR([buildnameslist.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.12.2 foreign silent-rules -Wall -Werror])
AM_MAINTAINER_MODE([enable])
AC_USE_SYSTEM_EXTENSIONS
AM_PROG_AR
LT_INIT


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PATH_PROGS([ENV],[env],[env])
AC_PATH_PROGS([GAWK],[gawk],[gawk])
AC_PATH_PROGS([ICONV],[iconv],[iconv])
AC_PATH_PROGS([WGET],[wget],[wget])


# Checks for libraries.


# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])


# Checks for typedefs, structures, and compiler characteristics.
AC_SUBST([WARNING_CFLAGS],[])
AC_SUBST([EXTRA_WARNING_CFLAGS],[])
AX_CHECK_COMPILE_FLAG([-Wall],[WARNING_CFLAGS+=" -Wall"])
AX_CHECK_COMPILE_FLAG([-Wextra],[WARNING_CFLAGS+=" -Wextra"])
AX_CHECK_COMPILE_FLAG([-Wno-sign-compare],[EXTRA_WARNING_CFLAGS+=" -Wno-sign-compare"])
AX_CHECK_COMPILE_FLAG([-Wno-unused-parameter],[EXTRA_WARNING_CFLAGS+=" -Wno-unused-parameter"])


# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strdup strtol])


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libuninameslist.pc])
AC_CONFIG_FILES([libuninameslist-fr.pc])
AC_CONFIG_FILES([uninameslist.h:nameslist.h])
AC_OUTPUT
