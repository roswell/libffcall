# Sed script for post-processing the trace output of subordinate configures.
# Copyright (C) 2003-2017 Free Software Foundation, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Replace invocations of some libtool macros.
s|._LT_ENABLE_SHARED_DEFAULT.|no|g
s|._LT_ENABLE_STATIC_DEFAULT.|yes|g
s|._LT_ENABLE_FAST_INSTALL_DEFAULT.|yes|g
s|._LT_WITH_AIX_SONAME_DEFAULT.|aix|g
# Avoid loss of brackets, such as  --with-tags[=TAGS] => --with-tags=TAGS
s|\[=TAGS\]|@<:@=TAGS@:>@|g
s|\[=PKGS\]|@<:@=PKGS@:>@|g
# Avoid unwanted comma, such as  [default=use both] => [default=use], [both]
s|\[default=use both\]|@<:@default=use both@:>@|g
