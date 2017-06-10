dnl AUTOCONF configuration for LIBFFCALL
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

dnl Ensure that "configure --help" lists all the command line options that
dnl are usable with the subdir configures. Really AC_CONFIG_SUBDIRS should
dnl do it by itself.
dnl System types:
AC_CANONICAL_HOST
dnl Optional Features: AC_ARG_ENABLE calls
dnl Optional Packages: AC_ARG_WITH calls
dnl Some influential environment variables: AC_ARG_VAR calls
esyscmd([{
cd avcall && autoconf -I.. --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..;
cd vacall && autoconf -I.. --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..;
cd trampoline && autoconf -I.. --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..;
cd callback && autoconf -I.. --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..;
} | sed -f build-aux/ac-help.sed ])

AC_OUTPUT
