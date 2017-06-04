dnl AUTOCONF configuration for CALLBACK
dnl Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
dnl Copyright 2007-2010 Sam Steingold <sds@gnu.org>
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
AC_INIT([libffcall/callback],m4_normalize(m4_esyscmd([cat ../VERSION])))
AC_CONFIG_SRCDIR([callback.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_HEADERS([callback.h],
[sed "s/@LIBFFCALL_VERSION@/${LIBFFCALL_VERSION}/" callback.h > tmp
mv -f tmp callback.h],[LIBFFCALL_VERSION=$PACKAGE_VERSION])
AC_CONFIG_FILES([Makefile])
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
CL_CC_GCC
AC_PROG_MAKE_SET
AC_CONFIG_AUX_DIR([../build-aux])
AC_PROG_RANLIB
AC_PROG_INSTALL
CL_PROG_LN
CL_PROG_LN_S
gl_HOST_CPU_C_ABI
PACKAGE=callback
FFCALL_COMMON_LIBTOOL
AC_TYPE_LONG_LONG_INT
dnl This piece of sed script replaces every line containing '@subdir@'
dnl by several consecutive lines, each referencing one subdir.
extrasub="$extrasub"'
/@subdir@/{
h
g
s/@subdir@/vacall_r/g
p
g
s/@subdir@/trampoline_r/g
p
d
}
'
AC_CONFIG_SUBDIRS([vacall_r trampoline_r])
AC_OUTPUT
