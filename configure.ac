dnl AUTOCONF configuration for FFCALL
dnl Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
dnl Copyright 2008-2010 Sam Steingold <sds@gnu.org>
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
AC_CONFIG_SRCDIR([trampoline/trampoline.h.in])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_AUX_DIR([build-aux])
AC_PROG_MAKE_SET
gl_EARLY
gl_INIT
dnl This piece of sed script replaces every line containing '@subdir@'
dnl by several consecutive lines, each referencing one subdir.
extrasub="$extrasub"'
/@subdir@/{
h
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
AC_CONFIG_SUBDIRS([avcall vacall trampoline callback])
AC_OUTPUT
