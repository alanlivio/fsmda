############################## Autotools initialization #######################
### Autoconf initialization
AC_PREREQ([2.62])
AC_INIT([libfsmda],
        0.1,
        [bugs@libfsmda.or],
        [libfsmda], [http://www.libfsmda.org])
AC_CONFIG_MACRO_DIR([build-aux])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([/usr])
AC_PREFIX_PROGRAM([/usr])

### Automake initialization
# See http://www.gnu.org/software/automake/manual/html_node/List-of-Automake-options.html
AM_INIT_AUTOMAKE([-Wall 
                  1.11
                  foreign
                  gnu
                  no-define
                  subdir-objects
                  std-options
                  serial-tests])
AM_SILENT_RULES
AM_PROG_AR

### Libtool initialization
LT_PREREQ([2.2])
LT_INIT([disable-static])

############################## Program Checks ################################
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG
AS_IF([test -z "$PKG_CONFIG"],
 [AC_MSG_ERROR([pkg-config >= $PKGCONFIG_REQUIRED required.])])

############################## Libraries Checks ###############################
### Define versions
#m4_define([gtk_required_version],   [3.4.2])
#AC_SUBST([GTK_REQUIRED_VERSION], gtk_required_version)

### Check for pthread
ACX_PTHREAD([have_pthread=yes], [heve_pthread=no])
if test "x$have_pthread" = "xyes"; then
  GTEST_EXTRA_CPPFLAGS="-DGTEST_HAS_PTHREAD=1"
  GTEST_EXTRA_LDFLAGS="$PTHREAD_LIBS"
  AC_SUBST([GTEST_EXTRA_CPPFLAGS])
  AC_SUBST([GTEST_EXTRA_LDFLAGS])
fi

### Check for PLATINUMKIT
PKG_CHECK_MODULES([PLATINUMKIT], [libplatinumkit], [],
  [AC_MSG_ERROR([The libplatinumkit is required.
  Try in https://github.com/alanlivio/platinumkit-autotools-library.])])

### Check for LIBXML2
PKG_CHECK_MODULES([LIBXML2], [libxml-2.0], [],
  [AC_MSG_ERROR([The libxml-2.0 is required.])])

### Check for libgflags2
  PKG_CHECK_MODULES([LIBGFLAGS], [libgflags], [],
  [AC_MSG_ERROR([The libgflags is required.])])
 
############################## Files configuration ############################
### Autoconf source configuration
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES(Makefile
                src/Makefile
                src/libfsmda.pc
                programs/Makefile
                tests/Makefile)

############################## Output #########################################
AC_OUTPUT
AC_MSG_NOTICE([summary of main build options:

  Version:            ${VERSION}
  Host type:          ${host}
  Install prefix:     ${prefix}
  Compiler:           cc: ${CC} cflags: ${CFLAGS} cppflags: ${CPPFLAGS}
  Warning flags:      ${WERROR_CFLAGS} ${WARN_CFLAGS}
  Library types:      Shared=${enable_shared}, Static=${enable_static}
])
