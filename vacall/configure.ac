dnl AUTOCONF configuration for VACALL
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
AC_INIT([libffcall/vacall],m4_normalize(m4_esyscmd([cat ../VERSION])))
AC_CONFIG_SRCDIR([vacall.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_HEADERS([vacall.h],
[sed "s/@LIBFFCALL_VERSION@/${LIBFFCALL_VERSION}/" vacall.h > tmp
mv -f tmp vacall.h],[LIBFFCALL_VERSION=$PACKAGE_VERSION])
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
gl_HOST_CPU_C_ABI
FFCALL_ENDIANNESS
FFCALL_PCC_STRUCT_RETURN
FFCALL_SMALL_STRUCT_RETURN
FFCALL_IREG_FLOAT_RETURN
AC_TYPE_LONG_LONG_INT
AC_C_CHAR_UNSIGNED
AC_OUTPUT
