#!/bin/sh
# Convenience script for fetching auxiliary files that are omitted from
# the version control repository of this package.
#
# This script requires either
#   - the LIBTOOL_RELEASES_DIR environment variable pointing to a directory
#     that contains libtool release tarballs, or
#   - a copy of the newest libtool-x.y.z.tar.gz in the current directory, or
#   - the wget program in the PATH and an internet connection.

# Copyright (C) 2016-2026 Bruno Haible.
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

# Usage: ./autopull.sh [--one-time]
#
# Options:
#   --one-time          Optimize, assuming that the current directory will be
#                       used to build the current version only and will be
#                       thrown away afterwards.

# Parse options.

shallow=

while :; do
  case "$1" in
    --one-time) shallow='--depth 1'; shift;;
    *) break ;;
  esac
done


./gitsub.sh pull $shallow || exit 1

# The newest libtool release version.
LIBTOOL_VERSION=2.6.0

file="libtool-${LIBTOOL_VERSION}.tar.gz"
if test -n "$LIBTOOL_RELEASES_DIR"; then
  if test -f "${LIBTOOL_RELEASES_DIR}/${file}"; then
    :
  else
    ( echo "File ${file} not found in ${LIBTOOL_RELEASES_DIR} ."
      echo "Download it, through"
      echo "  wget -q --timeout=5 -O ${LIBTOOL_RELEASES_DIR}/${file} https://alpha.gnu.org/gnu/libtool/${file}"
      echo "then retry this script again."
    ) 1>&2
    exit 1
  fi
else
  if test -f "${file}"; then
    :
  else
    echo "$0: getting $file..."
    wget -q --timeout=5 -O ${file}.tmp https://alpha.gnu.org/gnu/libtool/${file} \
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

echo "$0: done.  Now you can run './autogen.sh'."
