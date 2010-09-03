dnl AUTOCONF configuration for CALLBACK
dnl Bruno Haible 2000-04-02
dnl Sam Steingold 2008-2010
dnl
AC_INIT(libffcall/callback,m4_normalize(m4_esyscmd([cat ../VERSION])))
AC_CONFIG_SRCDIR(callback.h.in)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_HEADERS([callback.h],
[sed "s/@LIBFFCALL_VERSION@/${LIBFFCALL_VERSION}/" callback.h > tmp
mv -f tmp callback.h],[LIBFFCALL_VERSION=$PACKAGE_VERSION])
AC_CONFIG_FILES(Makefile)
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
CL_CC_GCC
AC_PROG_RANLIB
AC_PROG_MAKE_SET
AC_CONFIG_AUX_DIR(../build-aux)
AC_PROG_INSTALL
CL_PROG_LN
CL_PROG_LN_S
gl_HOST_CPU_C_ABI
PACKAGE=callback
FFCALL_COMMON_LIBTOOL
dnl This piece of sed script replaces every line containing '@subdir@'
dnl by several consecutive lines, each referencing one subdir.
extrasub="$extrasub"'
/@subdir@/{
h
g
s/@subdir@/vacall_r/
p
g
s/@subdir@/trampoline_r/
p
d
}
'
CL_CONFIG_SUBDIRS(vacall_r trampoline_r)
AC_OUTPUT
