dnl AUTOCONF configuration for TRAMPOLINE_R
dnl Bruno Haible 2001-01-27
dnl Sam Steingold 2008-2010
dnl
AC_INIT(libffcall/trampoline_r,m4_normalize(m4_esyscmd([cat ../../VERSION])))
AC_CONFIG_SRCDIR(trampoline_r.h.in)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_HEADERS([trampoline_r.h],
[sed "s/@LIBFFCALL_VERSION@/${LIBFFCALL_VERSION}/" trampoline_r.h > tmp
mv -f tmp trampoline_r.h],[LIBFFCALL_VERSION=$PACKAGE_VERSION])
AC_CONFIG_FILES(Makefile)
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
CL_CC_GCC
CL_AS_UNDERSCORE
AC_PROG_RANLIB
AC_PROG_MAKE_SET
AC_CONFIG_AUX_DIR(../../build-aux)
AC_PROG_INSTALL
CL_PROG_LN
CL_PROG_LN_S
gl_HOST_CPU_C_ABI
PACKAGE=callback
FFCALL_COMMON_LIBTOOL
AC_CHECK_HEADERS(unistd_h)
FFCALL_COMMON_TRAMPOLINE
CPU_OBJECTS=''
if test ${HOST_CPU_C_ABI} = hppa -o ${HOST_CPU_C_ABI} = powerpc64 -o ${HOST_CPU_C_ABI} = ia64; then
  CPU_OBJECTS="$CPU_OBJECTS "'tramp-$(CPU).lo'
fi
if test ${HOST_CPU_C_ABI} = powerpc; then
  case "${host_os}" in
    aix*) CPU_OBJECTS="$CPU_OBJECTS "'tramp-$(CPU).lo' ;;
    *) ;;
  esac
fi
if test ${HOST_CPU_C_ABI} = sparc -o ${HOST_CPU_C_ABI} = sparc64 -o ${HOST_CPU_C_ABI} = alpha -o ${HOST_CPU_C_ABI} = hppa -o ${HOST_CPU_C_ABI} = convex -o ${HOST_CPU_C_ABI} = arm -o ${HOST_CPU_C_ABI} = armel; then
  CPU_OBJECTS="$CPU_OBJECTS "'cache-$(CPU).lo'
fi
if test ${HOST_CPU_C_ABI} = powerpc; then
  case "${host_os}" in
    aix*) ;;
    *) CPU_OBJECTS="$CPU_OBJECTS "'cache-$(CPU).lo' ;;
  esac
fi
AC_SUBST(CPU_OBJECTS)
if test ${HOST_CPU_C_ABI} = mips -o ${HOST_CPU_C_ABI} = mipsn32 -o ${HOST_CPU_C_ABI} = mips64; then
AC_CHECK_HEADERS(sys/cachectl.h)
fi
if test ${HOST_CPU_C_ABI} = m88k; then
AC_CHECK_HEADERS(sys/m88kbcs.h)
fi
AC_OUTPUT
