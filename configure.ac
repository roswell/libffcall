dnl AUTOCONF configuration for LIBFFCALL
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

AC_INIT([GNU libffcall],m4_normalize(m4_esyscmd([cat VERSION])),[https://savannah.gnu.org/projects/libffcall],[libffcall])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([])

AC_CONFIG_SRCDIR([trampoline/trampoline.h.in])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_HEADERS([avcall/avcall.h])
AC_CONFIG_HEADERS([vacall/vacall.h])
AC_CONFIG_HEADERS([trampoline/trampoline.h])
AC_CONFIG_HEADERS([callback/callback.h])
AC_CONFIG_HEADERS([callback/vacall_r/vacall_r.h])
AC_CONFIG_HEADERS([callback/trampoline_r/trampoline_r.h])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([gnulib-lib/Makefile])
AC_CONFIG_FILES([avcall/Makefile])
AC_CONFIG_FILES([vacall/Makefile])
AC_CONFIG_FILES([trampoline/Makefile])
AC_CONFIG_FILES([callback/Makefile])
AC_CONFIG_FILES([callback/vacall_r/Makefile])
AC_CONFIG_FILES([callback/trampoline_r/Makefile])

dnl Substitutable version number.
changequote(,)
sed_extract_major='/^[0-9]/{s/^\([0-9]*\).*/\1/p;q;}
i\
0
q
'
sed_extract_minor='/^[0-9][0-9]*[.][0-9]/{s/^[0-9]*[.]\([0-9]*\).*/\1/p;q;}
i\
0
q
'
changequote([,])
version_major=`echo "${PACKAGE_VERSION}" | sed -n -e "$sed_extract_major"`
version_minor=`echo "${PACKAGE_VERSION}" | sed -n -e "$sed_extract_minor"`
HEXVERSION=`printf '0x%02X%02X' $version_major $version_minor`
AC_DEFINE_UNQUOTED([LIBFFCALL_VERSION], [$HEXVERSION], [Version number: (major<<8) + minor])

AC_PROG_MAKE_SET

AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
CL_CC_GCC
CL_AS_UNDERSCORE

dnl For a 64-bit build on AIX, AC_PROG_RANLIB is not sufficient.
gl_PROG_AR_RANLIB

AC_PROG_INSTALL
CL_PROG_LN
CL_PROG_LN_S

gl_EARLY

gl_HOST_CPU_C_ABI
FFCALL_ENDIANNESS

PACKAGE=libffcall
LT_INIT([disable-shared])

dnl Checks for avcall, vacall, vacall_r.
FFCALL_PCC_STRUCT_RETURN
FFCALL_SMALL_STRUCT_RETURN
FFCALL_IREG_FLOAT_RETURN
AC_TYPE_LONG_LONG_INT
AC_C_CHAR_UNSIGNED

dnl Checks for trampoline, trampoline_r.
AC_CHECK_HEADERS([unistd_h])
AC_HEADER_STDC
CL_GETPAGESIZE
CL_MACH_VM
FFCALL_MMAP
FFCALL_MPROTECT
CL_SHM_H
CL_SHM
FFCALL_CODEEXEC
FFCALL_CODEEXEC_PAX

dnl List of object files for trampoline, trampoline_r.
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
if test ${HOST_CPU_C_ABI} = sparc -o ${HOST_CPU_C_ABI} = sparc64 -o ${HOST_CPU_C_ABI} = alpha -o ${HOST_CPU_C_ABI} = hppa -o ${HOST_CPU_C_ABI} = powerpc64-elfv2; then
  CPU_OBJECTS="$CPU_OBJECTS "'cache-$(CPU).lo'
fi
if test ${HOST_CPU_C_ABI} = powerpc; then
  case "${host_os}" in
    aix*) ;;
    *) CPU_OBJECTS="$CPU_OBJECTS "'cache-$(CPU).lo' ;;
  esac
fi
AC_SUBST([CPU_OBJECTS])
if test ${HOST_CPU_C_ABI} = mips -o ${HOST_CPU_C_ABI} = mipsn32 -o ${HOST_CPU_C_ABI} = mips64; then
  AC_CHECK_HEADERS([sys/cachectl.h])
fi

gl_INIT

dnl This piece of sed script replaces every line containing '@subdir@'
dnl by several consecutive lines, each referencing one subdir.
extrasub="$extrasub"'
/@subdir@/{
h
g
s/@subdir@/gnulib-lib/g
p
g
s/@subdir@/avcall/g
p
g
s/@subdir@/vacall/g
p
g
s/@subdir@/trampoline/g
p
g
s/@subdir@/callback/g
p
d
}
'
dnl Likewise for the callback subdirectory.
extrasub="$extrasub"'
/@callback_subdir@/{
h
g
s/@callback_subdir@/vacall_r/g
p
g
s/@callback_subdir@/trampoline_r/g
p
d
}
'

AC_OUTPUT
