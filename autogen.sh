#!/bin/sh
# Convenience script for regenerating all easily autogeneratable files that are
# omitted from the version control repository. In particular, this script
# also regenerates all aclocal.m4, config.h.in, configure files with new
# versions of autoconf, automake, or libtool.
#
# This script requires autoconf-2.65..2.69 and automake-1.11..1.15 in the PATH.
# If not used from a released tarball, it also requires either
#   - the GNULIB_SRCDIR environment variable pointing to a gnulib checkout, or
#   - a preceding invocation of './gitsub.sh pull'.
# It also requires either
#   - the LIBTOOL_RELEASES_DIR environment variable pointing to a directory
#     that contains libtool release tarballs, or
#   - a copy of the newest libtool-x.y.z.tar.gz in the current directory, or
#   - the wget program in the PATH and an internet connection.

# Copyright (C) 2016-2019 Bruno Haible.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Usage: ./autogen.sh [--skip-gnulib]

skip_gnulib=false
while :; do
  case "$1" in
    --skip-gnulib) skip_gnulib=true; shift;;
    *) break ;;
  esac
done

# The newest libtool release version.
LIBTOOL_VERSION=2.4.6

if test $skip_gnulib = false; then

  file="libtool-${LIBTOOL_VERSION}.tar.gz"
  if test -n "$LIBTOOL_RELEASES_DIR"; then
    if test -f "${LIBTOOL_RELEASES_DIR}/${file}"; then
      :
    else
      ( echo "File ${file} not found in ${LIBTOOL_RELEASES_DIR} ."
        echo "Download it, through"
        echo "  wget -q --timeout=5 -O ${LIBTOOL_RELEASES_DIR}/${file} https://ftp.gnu.org/gnu/libtool/${file}"
        echo "then retry this script again."
      ) 1>&2
      exit 1
    fi
  else
    if test -f "${file}"; then
      :
    else
      echo "$0: getting $file..."
      wget -q --timeout=5 -O ${file}.tmp https://ftp.gnu.org/gnu/libtool/${file} \
        && mv ${file}.tmp ${file}
      retval=$?
      rm -f ${file}.tmp
      test $retval -eq 0 || exit $retval
    fi
    LIBTOOL_RELEASES_DIR='.'
  fi
  make -f Makefile.maint \
       libtool-clean libtool-imported-files \
       LIBTOOL_RELEASE="${LIBTOOL_RELEASES_DIR}/${file}"

  if test -n "$GNULIB_SRCDIR"; then
    test -d "$GNULIB_SRCDIR" || {
      echo "*** GNULIB_SRCDIR is set but does not point to an existing directory." 1>&2
      exit 1
    }
  else
    GNULIB_SRCDIR=`pwd`/gnulib
    test -d "$GNULIB_SRCDIR" || {
      echo "*** Subdirectory 'gnulib' does not yet exist. Use './gitsub.sh pull' to create it, or set the environment variable GNULIB_SRCDIR." 1>&2
      exit 1
    }
  fi
  # Now it should contain a gnulib-tool.
  GNULIB_TOOL="$GNULIB_SRCDIR/gnulib-tool"
  test -f "$GNULIB_TOOL" || {
    echo "*** gnulib-tool not found." 1>&2
    exit 1
  }
  make -f Makefile.maint \
       gnulib-clean gnulib-m4/gnulib-cache.m4 gnulib-imported-files \
       GNULIB_TOOL="$GNULIB_TOOL"
fi

# Copy files between directories.
(cd callback/trampoline_r && make -f Makefile.maint copied-files)

make -f Makefile.maint totally-clean all || exit $?

echo "$0: done.  Now you can run './configure'."
