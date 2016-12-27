dnl AUTOCONF configuration for FFCALL
dnl Bruno Haible 24.10.1997
dnl Sam Steingold 2008-2009
dnl
AC_INIT(GNU libffcall,m4_normalize(m4_esyscmd([cat VERSION])),https://savannah.gnu.org/projects/libffcall,libffcall)
AC_CONFIG_SRCDIR(trampoline/trampoline.h.in)
AC_CONFIG_FILES(Makefile)
AC_CONFIG_AUX_DIR(build-aux)
AC_PROG_MAKE_SET
gl_EARLY
gl_INIT
dnl This piece of sed script replaces every line containing '@subdir@'
dnl by several consecutive lines, each referencing one subdir.
extrasub="$extrasub"'
/@subdir@/{
h
g
s/@subdir@/avcall/
p
g
s/@subdir@/vacall/
p
g
s/@subdir@/trampoline/
p
g
s/@subdir@/callback/
p
d
}
'
CL_CONFIG_SUBDIRS(avcall vacall trampoline callback)
AC_OUTPUT
