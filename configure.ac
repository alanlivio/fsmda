############################## Initialization ############################
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
AM_INIT_AUTOMAKE([-Wall 1.11 foreign gnu no-define subdir-objects])
AM_SILENT_RULES
AM_PROG_AR

### Libtool initialization
LT_PREREQ([2.2])
LT_INIT([disable-static])

############################## Checks ####################################
###Autoconf check for programs
AC_CANONICAL_HOST
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

PKG_PROG_PKG_CONFIG
AS_IF([test -z "$PKG_CONFIG"],
 [AC_MSG_ERROR([pkg-config >= $PKGCONFIG_REQUIRED required.])])
          
### Define versions
#m4_define([gtk_required_version],   [3.4.2])
#AC_SUBST([GTK_REQUIRED_VERSION], gtk_required_version)

### Checks for libraries
PKG_CHECK_MODULES([PLATINUMKIT], [libplatinumkit], [],
    		[AC_MSG_ERROR([Platinumlkit library is required. Try in https://github.com/alanlivio/platinumkit-autotools-library.])])
AC_CHECK_LIB([pthread], [pthread_mutex_init], [], 
            [AC_MSG_ERROR([pthread library is required])])

### Configure automake contionals
#AS_IF([test "$have_gtk" = yes],
# [AC_DEFINE([HAVE_GTK], [1], [Define to 1 if we have GTK+-3.0.])])
#AM_CONDITIONAL([HAVE_GTK], [test "$have_gtk" = yes])
 
############################## Files configuration #######################
### Autoconf source configuration
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES(Makefile
                src/Makefile
                src/libfsmda.pc
                examples/Makefile
                tests/Makefile)
############################## Output ####################################
AC_OUTPUT
AC_MSG_NOTICE([summary of main build options:

  Version:            ${VERSION}
  Host type:          ${host}
  Install prefix:     ${prefix}
  Compiler:           cc: ${CC} cflags: ${CFLAGS} cppflags: ${CPPFLAGS}
  Warning flags:      ${WERROR_CFLAGS} ${WARN_CFLAGS}
  Library types:      Shared=${enable_shared}, Static=${enable_static}
])
