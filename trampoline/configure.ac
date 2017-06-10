dnl AUTOCONF configuration for TRAMPOLINE
dnl Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
dnl Copyright 2003-2010 Sam Steingold <sds@gnu.org>
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.
dnl
AC_INIT([libffcall/trampoline],m4_normalize(m4_esyscmd([cat ../VERSION])))
AC_CONFIG_SRCDIR([trampoline.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_HEADERS([trampoline.h],
[sed "s/@LIBFFCALL_VERSION@/${LIBFFCALL_VERSION}/" trampoline.h > tmp
mv -f tmp trampoline.h],[LIBFFCALL_VERSION=$PACKAGE_VERSION])
AC_CONFIG_FILES([Makefile])
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
CL_CC_GCC
CL_AS_UNDERSCORE
AC_PROG_MAKE_SET
AC_CONFIG_AUX_DIR([../build-aux])
gl_PROG_AR_RANLIB
AC_PROG_INSTALL
CL_PROG_LN
CL_PROG_LN_S
gl_HOST_CPU_C_ABI
AC_CHECK_HEADERS([unistd_h])
FFCALL_COMMON_TRAMPOLINE
CPU_OBJECTS=''
if test ${HOST_CPU_C_ABI} = hppa -o ${HOST_CPU_C_ABI} = powerpc64 -o ${HOST_CPU_C_ABI} = ia64; then
  CPU_OBJECTS="$CPU_OBJECTS "'tramp-$(CPU).o'
fi
if test ${HOST_CPU_C_ABI} = powerpc; then
  case "${host_os}" in
    aix*) CPU_OBJECTS="$CPU_OBJECTS "'tramp-$(CPU).o' ;;
    *) ;;
  esac
fi
if test ${HOST_CPU_C_ABI} = sparc -o ${HOST_CPU_C_ABI} = sparc64 -o ${HOST_CPU_C_ABI} = alpha -o ${HOST_CPU_C_ABI} = hppa -o ${HOST_CPU_C_ABI} = powerpc64-elfv2; then
  CPU_OBJECTS="$CPU_OBJECTS "'cache-$(CPU).o'
fi
if test ${HOST_CPU_C_ABI} = powerpc; then
  case "${host_os}" in
    aix*) ;;
    *) CPU_OBJECTS="$CPU_OBJECTS "'cache-$(CPU).o' ;;
  esac
fi
AC_SUBST([CPU_OBJECTS])
if test ${HOST_CPU_C_ABI} = mips -o ${HOST_CPU_C_ABI} = mipsn32 -o ${HOST_CPU_C_ABI} = mips64; then
AC_CHECK_HEADERS([sys/cachectl.h])
fi
AC_OUTPUT
