#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([sigmoid], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign subdir-objects]) # Does not require NEWS, COPYING, AUTHORS, ChangeLog or README
LT_INIT

# silent make https://autotools.io/automake/silent.html
# silent rules enabled by default with 'yes'
# disable silent runles with ./configure --disable-silent-rules
AM_SILENT_RULES([yes]) # less verbose make output 
# AM_SILENT_RULES() # use make -s to get silent output

GLIB_MIN_VERSION=2.38.0
AC_SUBST(GLIB_MIN_VERSION)

# i18 support
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19.8])
GETTEXT_PACKAGE=AC_PACKAGE_NAME
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE",[The name of the gettext domain])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h]) # use config.h instead of passing -D in the command line
AC_CONFIG_MACRO_DIR([m4])

AC_LANG([C]) # Use C not C++

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# In case that you want to check for specific versions of gcc 
# For example in case that you need C11 support you want to 
# check for gcc-4.9 
#AC_PROG_CC([gcc-4.9 gcc cc])

AC_PROG_CC_C99 # or AC_PROG_CC_89 to force C89 mode or AC_PROG_CC_STDC to go to latest supported standard (currently C99)

AC_PROG_INSTALL
AC_PROG_CC_C_O # Need to have per product flags myexecutable_CFLAG


# Checks for libraries.

# Found libraries are automatically addded to LIBS
# AC_SEARCH_LIBS([pthread_cond_wait], [pthread],[],[
#                 AC_MSG_ERROR([You need to install pthreads library.])
#                 ])

# AC_SEARCH_LIBS([g_test_init], [glib-2.0],[],[
#                 AC_MSG_ERROR([You need to install glib-2.0 library.])
#                 ])

# Checks for header files.
AC_HEADER_ASSERT # ./configure --disable-assert to define NDEBUG 
AC_CHECK_HEADER([stdlib.h])

# Check for C11's optional Atomic operations library 
# AC_CHECK_HEADER([stdatomic.h], [], [
#                 AC_MSG_ERROR([C11 with atomic support needed.])
#                  ])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
PKG_CHECK_MODULES(SIGMOID, [
                           glib-2.0 >= $GLIB_MIN_VERSION
                           gtk+-3.0
])

# The following statement will use pkg-config --cflags --libs 
# to find out CFLAGS and -l options required to build a target that 
# it's going to link against glib2.0.
# The required CFLAGS and -l options are available as DEPS_CFLAGS
# and DEPS_LIBS in Makefile.am
# PKG_CHECK_MODULES([DEPS], [glib-2.0 >= 2.24.1]) 

AC_ARG_ENABLE([debug], 
              AS_HELP_STRING([--disable-debug],[disable debug to remove support for extra log and debugging]),
              [enable_debug=${enableval}],[enable_debug=yes])

if test "x${enable_debug}" == "xyes"; then
  AC_DEFINE([DEBUG], 1, [debug is enabled])
else
  AC_MSG_WARN([Debug is off])
fi

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 po/Makevars:po/Makevars.template
                 po/Makefile.in
])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AX_VALGRIND_CHECK # http://www.gnu.org/software/autoconf-archive/ax_valgrind_check.html - make check-valgrind
AX_CODE_COVERAGE # http://www.gnu.org/software/autoconf-archive/ax_code_coverage.html#ax_code_coverage - make check-code-coverage generates coverage report
AC_OUTPUT
