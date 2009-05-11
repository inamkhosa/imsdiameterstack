dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

AC_INIT([libdiameter],[1.0])
AC_PREREQ

PACKAGE=libdiameter
PACKAGE_NAME=diameter

#release versioning
MAJOR_VERSION=1
MINOR_VERSION=0
MICRO_VERSION=0

#API version
API_VERSION=$MAJOR_VERSION.$MINOR_VERSION
AC_SUBST(API_VERSION)

#shared library versioning
LIBRARY_VERSION=$MAJOR_VERSION:$MINOR_VERSION:$MICRO_VERSION
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed


AC_SUBST(LIBRARY_VERSION)

VERSION=$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION
RELEASE=$MAJOR_VERSION.$MINOR_VERSION
AC_SUBST(RELEASE)
AC_SUBST(VERSION)

VERSION=$VERSION
AC_SUBST(PACKAGE_NAME)

dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AM_CONFIG_HEADER(config.h)


AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AM_PROG_LIBTOOL
AM_SANITY_CHECK
AC_PROG_AWK
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET

dnl -----------------------------------------------
dnl Checks for libraries.
dnl -----------------------------------------------

PKG_CHECK_MODULES(LIBXML_DEPS, libxml-2.0 >= 2.6.16)
AC_SUBST(LIBXML_DEPS_CFLAGS)
AC_SUBST(LIBXML_DEPS_LIBS)

PKG_CHECK_MODULES(LIBAMPS_DEPS, libamps-1.0 >= 1.0.0)
AC_SUBST(LIBAMPS_DEPS_CFLAGS)
AC_SUBST(LIBAMPS_DEPS_LIBS)

#AC_CHECK_LIB(amps,[AMPS_Init], [], [AC_MSG_ERROR([AMPS library not found])])

dnl -----------------------------------------------
dnl Checks for header files.
dnl -----------------------------------------------
AC_CHECK_HEADERS([arpa/inet.h])                        
AC_CHECK_HEADERS([netdb.h])                         
AC_CHECK_HEADERS([stdlib.h])                         
AC_CHECK_HEADERS([string.h])                         
AC_CHECK_HEADERS([strings.h])                         
AC_CHECK_HEADERS([sys/socket.h])                       
AC_CHECK_HEADERS([unistd.h])
#AC_CHECK_HEADERS([amps/AMPS_API.h amps/AMPS_Defines.h], [], [AC_MSG_ERROR([AMPS header files not found])])
                        
AC_HEADER_RESOLV
AC_HEADER_SYS_WAIT
AC_HEADER_TIME


# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset])


dnl -----------------------------------------------
dnl Checks for options
dnl -----------------------------------------------

AC_ARG_ENABLE(debug,[AS_HELP_STRING([--enable-debug],[Add compiler debugging options @<:@default=no@:>@])], [enable_debug=$enableval], [enable_debug=no])

AC_ARG_ENABLE(opt,[AS_HELP_STRING([--enable-opt],[Define compiler optimization level (applicable if debug disabled)@<:@default=8@:>@])], [opt_level=$enableval], [opt_level=8])

CFLAGS=""
AS_IF([test "x$enable_debug" == xyes],[CFLAGS="$CFLAGS -g -O0"])
AS_IF([test "x$enable_debug" == xno],[CFLAGS="$CFLAGS -O$opt_level"])


dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_CONFIG_FILES(Makefile \
          libdiameter.spec \
          [libdiameter-$API_VERSION.pc:libdiameter.pc.in] \
          src/Makefile
)

AC_OUTPUT


