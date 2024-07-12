#!/bin/sh
# Convenience script for regenerating all easily autogeneratable files that are
# omitted from the version control repository. In particular, this script
# also regenerates all aclocal.m4, config.h.in, configure files with new
# versions of autoconf, automake, or libtool.
#
# This script requires autoconf-2.70..2.72 and automake-1.11..1.17 in the PATH.

# Copyright (C) 2016-2024 Bruno Haible.
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

# Prerequisite (if not used from a released tarball): either
#   - the GNULIB_SRCDIR environment variable pointing to a gnulib checkout, or
#   - a preceding invocation of './autopull.sh'.
#
# Usage: ./autogen.sh [--skip-gnulib]
#
# Options:
#   --skip-gnulib       Avoid fetching files from Gnulib.
#                       This option is useful
#                       - when you are working from a released tarball (possibly
#                         with modifications), or
#                       - as a speedup, if the set of gnulib modules did not
#                         change since the last time you ran this script.

skip_gnulib=false
while :; do
  case "$1" in
    --skip-gnulib) skip_gnulib=true; shift;;
    *) break ;;
  esac
done

if test $skip_gnulib = false; then
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
