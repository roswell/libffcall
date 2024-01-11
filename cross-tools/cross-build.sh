#!/bin/sh
# Script for building all cross-compilers needed for maintaining GNU libffcall.
#
# Usage:
#   1. Make sure you have the following programs in $PATH:
#      - A C compiler and a C++ compiler (e.g. GNU GCC)
#      - patch (GNU patch)
#      - makeinfo (GNU texinfo)
#      - bison (GNU bison)
#      - flex
#   2. Set an environment variable to indicate where to install the cross
#      compilers. Example:
#      $ export HOST_CROSS_DIR=/arch/x86-linux/cross
#      This directory name must not contain spaces or special characters.
#   3. Set environment variables to indicate how to compile C and C++ code
#      for the host architecture. Example:
#      $ export host_triple="i686-pc-linux-gnu"
#      $ export CC="gcc -m32" CXX="g++ -m32" LDFLAGS="-m32"
#      or
#      $ export host_triple="i686-pc-linux-gnu"
#      $ export CC="i686-linux-gnu-gcc-10" CXX="i686-linux-gnu-g++-10"
#      If your C++ compiler is g++ ≥ 6 or clang++ ≥ 6.0, you need to add
#      the option -std=gnu++98 as part of CXX, because the default with
#      these compilers (-std=gnu++14 or newer) causes compilation errors.
#   4. Optionally, set environment variable GNU_RELEASES_DIR pointing to a
#      directory that contains GNU package releases tarballs.
#      Make sure the wget program is in the PATH and you have an internet
#      connection, so that additional GNU package releases can be downloaded
#      into this directory.
#   5. To build the cross compiler for a particular cpu type:
#      $ ./cross-build.sh sparc
#      To build the 'cross' script:
#      $ ./cross-build.sh cross
#      To build everything:
#      $ ./cross-build.sh all
#      Note: "./cross-build.sh all" may take several hours.
#
# You find a table of the cross-compilers in the file cross.conf.

progname=$0
package=libffcall

# You can set MAKE to 'gmake' if your 'make' program is not GNU make.
MAKE=make

# --------------------- BEGIN copy from gnulib-tool ---------------------

# When using GNU sed, turn off as many GNU extensions as possible,
# to minimize the risk of accidentally using non-portable features.
# However, do this only for gnulib-tool itself, not for the code that
# gnulib-tool generates, since we don't want "sed --posix" to leak
# into makefiles. And do it only for sed versions 4.2 or newer,
# because "sed --posix" is buggy in GNU sed 4.1.5, see
# <https://lists.gnu.org/archive/html/bug-gnulib/2009-02/msg00225.html>.
if (alias) > /dev/null 2>&1 \
   && echo | sed --posix -e d >/dev/null 2>&1 \
   && case `sed --version | sed -e 's/^[^0-9]*//' -e 1q` in \
        [1-3]* | 4.[01]*) false;; \
        *) true;; \
      esac \
   ; then
  # Define sed as an alias.
  # It is not always possible to use aliases. Aliases are guaranteed to work
  # if the executing shell is bash and either it is invoked as /bin/sh or
  # is a version >= 2.0, supporting shopt. This is the common case.
  # Two other approaches (use of a variable $sed or of a function func_sed
  # instead of an alias) require massive, fragile code changes.
  # An other approach (use of function sed) requires `which sed` - but
  # 'which' is hard to emulate, due to missing "test -x" on some platforms.
  if test -n "$BASH_VERSION"; then
    shopt -s expand_aliases >/dev/null 2>&1
  fi
  alias sed='sed --posix'
fi

# func_exit STATUS
# exits with a given status.
# This function needs to be used, rather than 'exit', when a 'trap' handler is
# in effect that refers to $?.
func_exit ()
{
  (exit $1); exit $1
}

# func_fatal_error message
# outputs to stderr a fatal error message, and terminates the program.
# Input:
# - progname                 name of this program
func_fatal_error ()
{
  echo "$progname: *** $1" 1>&2
  echo "$progname: *** Stop." 1>&2
  func_exit 1
}

# func_cross_tools_dir
# locates the directory where the cross-tools lives
# Input:
# - progname                 name of this program
# Sets variables
# - self_abspathname         absolute pathname of this script
# - cross_tools_dir          absolute pathname of cross-tools directory
func_cross_tools_dir ()
{
  case "$progname" in
    /* | ?:*) self_abspathname="$progname" ;;
    */*) self_abspathname=`pwd`/"$progname" ;;
    *)
      # Look in $PATH.
      # Iterate through the elements of $PATH.
      # We use IFS=: instead of
      #   for d in `echo ":$PATH:" | sed -e 's/:::*/:.:/g' | sed -e 's/:/ /g'`
      # because the latter does not work when some PATH element contains spaces.
      # We use a canonicalized $pathx instead of $PATH, because empty PATH
      # elements are by definition equivalent to '.', however field splitting
      # according to IFS=: loses empty fields in many shells:
      #   - /bin/sh on OSF/1 and Solaris loses all empty fields (at the
      #     beginning, at the end, and in the middle),
      #   - /bin/sh on IRIX and /bin/ksh on IRIX and OSF/1 lose empty fields
      #     at the beginning and at the end,
      #   - GNU bash, /bin/sh on AIX and HP-UX, and /bin/ksh on AIX, HP-UX,
      #     Solaris lose empty fields at the end.
      # The 'case' statement is an optimization, to avoid evaluating the
      # explicit canonicalization command when $PATH contains no empty fields.
      self_abspathname=
      if test "$PATH_SEPARATOR" = ";"; then
        # On Windows, programs are searched in "." before $PATH.
        pathx=".;$PATH"
      else
        # On Unix, we have to convert empty PATH elements to ".".
        pathx="$PATH"
        case :$PATH: in
          *::*)
            pathx=`echo ":$PATH:" | sed -e 's/:::*/:.:/g' -e 's/^://' -e 's/:\$//'`
            ;;
        esac
      fi
      save_IFS="$IFS"
      IFS="$PATH_SEPARATOR"
      for d in $pathx; do
        IFS="$save_IFS"
        test -z "$d" && d=.
        if test -x "$d/$progname" && test ! -d "$d/$progname"; then
          self_abspathname="$d/$progname"
          break
        fi
      done
      IFS="$save_IFS"
      if test -z "$self_abspathname"; then
        func_fatal_error "could not locate the cross-build.sh program - how did you invoke it?"
      fi
      ;;
  esac
  while test -h "$self_abspathname"; do
    # Resolve symbolic link.
    linkval=`func_readlink "$self_abspathname"`
    test -n "$linkval" || break
    case "$linkval" in
      /* | ?:* ) self_abspathname="$linkval" ;;
      * ) self_abspathname=`echo "$self_abspathname" | sed -e 's,/[^/]*$,,'`/"$linkval" ;;
    esac
  done
  cross_tools_dir=`echo "$self_abspathname" | sed -e 's,/[^/]*$,,'`
}

# --------------------- END copy from gnulib-tool ---------------------

# func_usage
# outputs to stdout the --help usage message.
func_usage ()
{
  echo "\
Usage: cross-build.sh CPU ...      Build tools for some CPUs.
       cross-build.sh cross        Create the 'cross' script.
       cross-build.sh all          Build everything.
       cross-build.sh --help       Show this help text.
       cross-build.sh --version    Show version and authorship information.

Report bugs in the bug tracker at <https://savannah.gnu.org/projects/libffcall>
or by email to <libffcall@gnu.org>."
}

# func_version
# outputs to stdout the --version message.
func_version ()
{
  echo "\
cross-build.sh (GNU $package)
Copyright (C) 2017-2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
"
  printf "Written by %s.\n" "Bruno Haible"
}

func_cross_tools_dir

# func_get_all_cpus
# retrieves the list of all known/supported CPUs.
# Output:
# - all_cpus        List of known/supported CPUs, separated by spaces
func_get_all_cpus ()
{
  # Cache the value.
  if test -z "$all_cpus"; then
    {
      read line; read line; read line
      all_cpus=
      while read cpu target gccversion binutilsversion binutilstarget; do
        # Avoid duplicates.
        case " $all_cpus " in
          *" $cpu "*) ;;
          *) all_cpus="$all_cpus $cpu" ;;
        esac
      done
    } < "$cross_tools_dir/cross.conf"
  fi
}

# Command-line option processing.
mode=
cpus=
while test $# -gt 0; do
  case "$1" in
    cross )
      if test -n "$mode"; then
        echo "Conflicting options. Try '$progname --help'." 1>&2
        func_exit 1
      fi
      mode=cross
      ;;
    all )
      if test -n "$mode"; then
        echo "Conflicting options. Try '$progname --help'." 1>&2
        func_exit 1
      fi
      mode=all
      ;;
    --help )
      func_usage
      func_exit 0
      ;;
    --version )
      func_version
      func_exit 0
      ;;
    * )
      func_get_all_cpus
      case " $all_cpus " in
        *" $1 "*)
          if test -n "$mode" && test "$mode" != some; then
            echo "Conflicting options." 1>&2
            echo "Try '$progname --help' for more information." 1>&2
            func_exit 1
          fi
          mode=some
          cpus="$cpus $1"
          ;;
        *)
          echo "Unknown option $1" 1>&2
          echo "Try '$progname --help' for more information." 1>&2
          func_exit 1
          ;;
      esac
      ;;
  esac
  shift
done

if test -z "$mode"; then
  echo "Insufficient options" 1>&2
  echo "Try '$progname --help' for more information." 1>&2
  func_exit 1
fi

if test -z "$HOST_CROSS_DIR"; then
  echo "Missing environment variable HOST_CROSS_DIR." 1>&2
  func_exit 1
fi
# Make it absolute.
case "$HOST_CROSS_DIR" in
  /* | ?:*) ;;
  *) HOST_CROSS_DIR=`pwd`/"$HOST_CROSS_DIR" ;;
esac
mkdir -p "$HOST_CROSS_DIR"

if test -z "$GNU_RELEASES_DIR"; then
  GNU_RELEASES_DIR="$cross_tools_dir/gnu-releases"
fi

# func_build_cross
# Creates the 'cross' script.
func_build_cross ()
{
  sed -e "s|@HOST_CROSS_DIR@|$HOST_CROSS_DIR|g" -e "s|@host_triple@|$host_triple|g" < "$cross_tools_dir/cross.in" > "$cross_tools_dir/cross"
  chmod a+x "$cross_tools_dir/cross"
}

# func_ensure_tarball package version suffix urldirname
# Ensure a given package is present in the GNU_RELEASES_DIR.
# Input:
# - package         Package name
# - version         Version
# - suffix          Tarball compression suffix
# - urldirname      Download URL dirname
func_ensure_tarball ()
{
  pkg_package="$1"
  pkg_version="$2"
  pkg_suffix="$3"
  pkg_urldirname="$4"
  if test -f "$GNU_RELEASES_DIR/$pkg_package-$pkg_version.tar.$pkg_suffix"; then
    # Already there.
    :
  else
    pkg_url="$pkg_urldirname/$pkg_package-$pkg_version.tar.$pkg_suffix"
    mkdir -p "$GNU_RELEASES_DIR" || func_exit 1
    echo "Fetching $pkg_url ..."
    wget -nv -O "$GNU_RELEASES_DIR/$pkg_package-$pkg_version.tar.$pkg_suffix" "$pkg_url" || func_exit 1
  fi
}

# func_ensure_unpacked_source package version suffix urldirname
# Ensures a given package's source is present in this directory.
# Input:
# - package         Package name
# - version         Version
# - suffix          Tarball compression suffix
# - urldirname      Download URL dirname
func_ensure_unpacked_source ()
{
  pkg_package="$1"
  pkg_version="$2"
  pkg_suffix="$3"
  pkg_urldirname="$4"
  if test -d "$cross_tools_dir/sources/$pkg_package-$pkg_version"; then
    # Already there.
    :
  else
    func_ensure_tarball "$pkg_package" "$pkg_version" "$pkg_suffix" "$pkg_urldirname" || func_exit 1
    echo "Unpacking $pkg_package-$pkg_version.tar.$pkg_suffix ..."
    case $pkg_suffix in
      gz) unpacker=gzip ;;
      bz2) unpacker=bzip2 ;;
      xz) unpacker=xz ;;
      *) echo "Don't know how to unpack $pkg_package-$pkg_version.tar.$pkg_suffix" 1>&2; func_exit 1 ;;
    esac
    rm -rf "$cross_tools_dir/sources/$pkg_package-$pkg_version"
    mkdir -p "$cross_tools_dir/sources"
    $unpacker -d -c < "$GNU_RELEASES_DIR/$pkg_package-$pkg_version.tar.$pkg_suffix" | (cd "$cross_tools_dir/sources" && tar xf -) || func_exit 1
    test -d "$cross_tools_dir/sources/$pkg_package-$pkg_version" || {
      echo "No directory $cross_tools_dir/sources/$pkg_package-$pkg_version was created!" 1>&2; func_exit 1
    }
    # Apply patches.
    if test -f "$cross_tools_dir/patches/$pkg_package-$pkg_version.patch"; then
      echo "Patching $cross_tools_dir/sources/$pkg_package-$pkg_version ..."
      (cd "$cross_tools_dir/sources" && patch -p0 < "../patches/$pkg_package-$pkg_version.patch") || func_exit 1
    fi
    # For binutils, remove the gprof directory. When this subdirectory exists
    # and the host platform happens to be the same as the target platform,
    # the binutils configure adds 'gprof' to the @configdirs@ value and thus
    # causes this subdirectory to be included in the build. But this directory
    # has extra prerequisites: an Objective-C compiler.
    if test "$pkg_package" = binutils; then
      rm -rf "$cross_tools_dir/sources/$pkg_package-$pkg_version/gprof"
    fi
  fi
}

# func_build_gmp version
# Builds the GNU gmp library.
# Input:
# - target          Directory component indicating the target.
# - version         gmp version
func_build_gmp ()
{
  pkg_version="$1"
  func_ensure_unpacked_source gmp "$pkg_version" bz2 "https://ftp.gnu.org/pub/gnu/gmp" || func_exit 1
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/gmp-$pkg_version"
  mkdir "$cross_tools_dir/build/build-$target/gmp-$pkg_version"
  echo "Building in $cross_tools_dir/build/build-$target/gmp-$pkg_version ..."
  (cd "$cross_tools_dir/build/build-$target/gmp-$pkg_version" \
   && ../../../sources/gmp-$pkg_version/configure --host="$host_triple" --prefix="$HOST_CROSS_DIR/${target}-tools" \
   && $MAKE \
   && $MAKE install \
  ) > "$cross_tools_dir/build/build-$target/gmp-$pkg_version/all.log" 2>&1 || func_exit 1
}

# func_build_mpfr version
# Builds the GNU mpfr library.
# Input:
# - target          Directory component indicating the target.
# - version         mpfr version
func_build_mpfr ()
{
  pkg_version="$1"
  func_ensure_unpacked_source mpfr "$pkg_version" bz2 "https://ftp.gnu.org/pub/gnu/mpfr" || func_exit 1
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/mpfr-$pkg_version"
  mkdir "$cross_tools_dir/build/build-$target/mpfr-$pkg_version"
  echo "Building in $cross_tools_dir/build/build-$target/mpfr-$pkg_version ..."
  (cd "$cross_tools_dir/build/build-$target/mpfr-$pkg_version" \
   && ../../../sources/mpfr-$pkg_version/configure --host="$host_triple" --prefix="$HOST_CROSS_DIR/${target}-tools" --with-gmp="$HOST_CROSS_DIR/${target}-tools" --enable-shared \
   && $MAKE \
   && $MAKE install \
  ) > "$cross_tools_dir/build/build-$target/mpfr-$pkg_version/all.log" 2>&1 || func_exit 1
}

# func_build_mpc version
# Builds the GNU mpc library.
# Input:
# - target          Directory component indicating the target.
# - version         mpc version
func_build_mpc ()
{
  pkg_version="$1"
  # was: func_ensure_unpacked_source mpc "$pkg_version" gz "http://www.multiprecision.org/mpc/download" || func_exit 1
  func_ensure_unpacked_source mpc "$pkg_version" gz "https://gcc.gnu.org/pub/gcc/infrastructure" || func_exit 1
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/mpc-$pkg_version"
  mkdir "$cross_tools_dir/build/build-$target/mpc-$pkg_version"
  echo "Building in $cross_tools_dir/build/build-$target/mpc-$pkg_version ..."
  (cd "$cross_tools_dir/build/build-$target/mpc-$pkg_version" \
   && ../../../sources/mpc-$pkg_version/configure --host="$host_triple" --prefix="$HOST_CROSS_DIR/${target}-tools" --with-gmp="$HOST_CROSS_DIR/${target}-tools" --with-mpfr="$HOST_CROSS_DIR/${target}-tools" --enable-shared \
   && $MAKE \
   && $MAKE install \
  ) > "$cross_tools_dir/build/build-$target/mpc-$pkg_version/all.log" 2>&1 || func_exit 1
}

# func_build_libelf version
# Builds the libelf library.
# Input:
# - target          Directory component indicating the target.
# - version         libelf version
func_build_libelf ()
{
  pkg_version="$1"
  func_ensure_unpacked_source libelf "$pkg_version" gz "http://www.mr511.de/software" || func_exit 1
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/libelf-$pkg_version"
  mkdir "$cross_tools_dir/build/build-$target/libelf-$pkg_version"
  echo "Building in $cross_tools_dir/build/build-$target/libelf-$pkg_version ..."
  (cd "$cross_tools_dir/build/build-$target/libelf-$pkg_version" \
   && ../../../sources/libelf-$pkg_version/configure --host="$host_triple" --prefix="$HOST_CROSS_DIR/${target}-tools" --enable-shared \
   && $MAKE \
   && $MAKE install \
  ) > "$cross_tools_dir/build/build-$target/libelf-$pkg_version/all.log" 2>&1 || func_exit 1
}

# func_build_isl version
# Builds the isl library.
# Input:
# - target          Directory component indicating the target.
# - version         isl version
func_build_isl ()
{
  pkg_version="$1"
  func_ensure_unpacked_source isl "$pkg_version" bz2 "ftp://gcc.gnu.org/pub/gcc/infrastructure" || func_exit 1
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/isl-$pkg_version"
  mkdir "$cross_tools_dir/build/build-$target/isl-$pkg_version"
  echo "Building in $cross_tools_dir/build/build-$target/isl-$pkg_version ..."
  (cd "$cross_tools_dir/build/build-$target/isl-$pkg_version" \
   && ../../../sources/isl-$pkg_version/configure --host="$host_triple" --prefix="$HOST_CROSS_DIR/${target}-tools" --with-gmp-prefix="$HOST_CROSS_DIR/${target}-tools" --enable-shared \
   && $MAKE \
   && $MAKE install \
  ) > "$cross_tools_dir/build/build-$target/isl-$pkg_version/all.log" 2>&1 || func_exit 1
}

# func_build_zstd version
# Builds the Facebook zstd library.
# Input:
# - target          Directory component indicating the target.
# - version         zstd version
func_build_zstd ()
{
  pkg_version="$1"
  func_ensure_unpacked_source zstd "$pkg_version" gz "https://github.com/facebook/zstd/releases/download/v$pkg_version" || func_exit 1
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/zstd-$pkg_version"
  cp -a  "$cross_tools_dir/sources/zstd-$pkg_version" "$cross_tools_dir/build/build-$target/zstd-$pkg_version"
  echo "Building in $cross_tools_dir/build/build-$target/zstd-$pkg_version ..."
  (cd "$cross_tools_dir/build/build-$target/zstd-$pkg_version" \
   && $MAKE         CC="$CC" \
   && $MAKE install CC="$CC" prefix="$HOST_CROSS_DIR/${target}-tools" \
  ) > "$cross_tools_dir/build/build-$target/zstd-$pkg_version/all.log" 2>&1 || func_exit 1
}

# func_build_binutils
# Builds the GNU binutils for a given target.
# Input:
# - target          Directory component indicating the target.
# - version         binutils version
# - binutilstarget  Target argument to pass to configure
func_build_binutils ()
{
  if case "$version" in 2.12.*) true;; *) false;; esac \
     && test `echo "$version" | wc -c` -gt 9; then
    # An intermediate release by H.J.Lu
    func_ensure_unpacked_source binutils "$version" gz "https://www.kernel.org/pub/linux/devel/binutils"
  else
    # An official GNU release
    func_ensure_unpacked_source binutils "$version" bz2 "https://ftp.gnu.org/pub/gnu/binutils"
  fi
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/binutils-$version"
  mkdir "$cross_tools_dir/build/build-$target/binutils-$version"
  echo "Building in $cross_tools_dir/build/build-$target/binutils-$version ..."
  (cd "$cross_tools_dir/build/build-$target/binutils-$version" \
   && ../../../sources/binutils-$version/configure --host="$host_triple" --prefix="$HOST_CROSS_DIR/${target}-tools" --target=$binutilstarget --enable-shared --disable-werror \
   && $MAKE \
   && $MAKE install \
  ) > "$cross_tools_dir/build/build-$target/binutils-$version/all.log" 2>&1 || func_exit 1
  if test "$target" != "$binutilstarget"; then
    # Put symbolic links, so that gcc and the 'cross' script find the installed binaries.
    (cd "$HOST_CROSS_DIR/${target}-tools/bin"
     echo "Putting symlinks in $HOST_CROSS_DIR/${target}-tools/bin:"
     for f in "$binutilstarget"-*; do
       g=`echo "$f" | sed -e "s|^$binutilstarget|$target|"`
       ln -s $f $g
       ls -l "$g"
     done
    )
  fi
}

# func_build_gcc
# Builds the GNU gcc for a given target.
# Input:
# - target          Directory component indicating the target.
# - version         gcc version
# - gcctarget       Target argument to pass to configure
func_build_gcc ()
{
  # Build the prerequisites.
  configure_options=
  case "$version" in
    4.[3-9]* | [5-9]* | 1[0-9]*)
      func_build_gmp 4.3.2 || func_exit 1
      configure_options="$configure_options --with-gmp=$HOST_CROSS_DIR/${target}-tools"
      ;;
  esac
  case "$version" in
    4.[3-9]* | [5-9]*)
      func_build_mpfr 2.4.2 || func_exit 1
      configure_options="$configure_options --with-mpfr=$HOST_CROSS_DIR/${target}-tools"
      ;;
    1[0-9]*)
      func_build_mpfr 3.1.0 || func_exit 1
      configure_options="$configure_options --with-mpfr=$HOST_CROSS_DIR/${target}-tools"
      ;;
  esac
  case "$version" in
    4.[5-9]* | [5-9]*)
      func_build_mpc 0.8.1 || func_exit 1
      configure_options="$configure_options --with-mpc=$HOST_CROSS_DIR/${target}-tools"
      ;;
    1[0-9]*)
      func_build_mpc 1.0.3 || func_exit 1
      configure_options="$configure_options --with-mpc=$HOST_CROSS_DIR/${target}-tools"
      ;;
  esac
  #case "$version" in
  #  6*)
  #    func_build_libelf 0.8.13 || func_exit 1
  #    configure_options="$configure_options --with-libelf=$HOST_CROSS_DIR/${target}-tools"
  #    ;;
  #esac
  case "$version" in
    [5-6]*)
      func_build_isl 0.14 || func_exit 1
      configure_options="$configure_options --with-isl=$HOST_CROSS_DIR/${target}-tools"
      ;;
    [7-9]* | 1[0-9]*)
      func_build_isl 0.16.1 || func_exit 1
      configure_options="$configure_options --with-isl=$HOST_CROSS_DIR/${target}-tools"
      ;;
  esac
  case "$version" in
    1[2-9]*)
      func_build_zstd 1.5.2 || func_exit 1
      configure_options="$configure_options --with-zstd=$HOST_CROSS_DIR/${target}-tools"
      ;;
  esac
  # Build gcc itself.
  case "$version" in
    3.[0-2]*) pkg_suffix=gz ;;
    [3-5]*)   pkg_suffix=bz2 ;;
    *)        pkg_suffix=xz ;;
  esac
  case "$version" in
    *-*)
      # A fork's snapshot.
      func_ensure_unpacked_source gcc "$version" "$pkg_suffix" "https://alpha.gnu.org/gnu/libffcall/gcc-$version" || func_exit 1
      ;;
    *)
      # An official GNU release
      func_ensure_unpacked_source gcc "$version" "$pkg_suffix" "https://ftp.gnu.org/pub/gnu/gcc/gcc-$version" || func_exit 1
      ;;
  esac
  if test "$target" = armv7l-linux-gnueabihf; then
    configure_options="$configure_options --with-arch=armv7-a --with-float=hard --with-fpu=vfpv3-d16"
  fi
  mkdir -p "$cross_tools_dir/build/build-$target"
  rm -rf "$cross_tools_dir/build/build-$target/gcc-$version"
  mkdir "$cross_tools_dir/build/build-$target/gcc-$version"
  echo "Building in $cross_tools_dir/build/build-$target/gcc-$version ..."
  (PATH="$HOST_CROSS_DIR/${target}-tools/bin:$PATH"
   LD_LIBRARY_PATH="$HOST_CROSS_DIR/${target}-tools/lib"${LD_LIBRARY_PATH+":$LD_LIBRARY_PATH"}
   cd "$cross_tools_dir/build/build-$target/gcc-$version" \
   && ../../../sources/gcc-$version/configure --prefix="$HOST_CROSS_DIR/${target}-tools" --target="$gcctarget" $configure_options --with-as="$HOST_CROSS_DIR/${target}-tools/bin/${target}-as" --with-ld="$HOST_CROSS_DIR/${target}-tools/bin/${target}-ld" --enable-languages=c \
   && { : "make usually fails during the libgcc phase, either because cc1 does not find its shared libraries, or because no include files are present yet, or because it invokes the wrong assembler"; \
        $MAKE; \
        cd gcc; \
        $MAKE EXTRA_PASSES= EXTRA_PARTS= LANGUAGES="c"; \
        $MAKE EXTRA_PASSES= EXTRA_PARTS= LANGUAGES="c" install-driver; \
        $MAKE EXTRA_PASSES= EXTRA_PARTS= LANGUAGES="c" install; \
        $MAKE EXTRA_PASSES= LANGUAGES="c" install; \
        $MAKE LANGUAGES="c" install; \
        true; \
      }
  ) > "$cross_tools_dir/build/build-$target/gcc-$version/all.log" 2>&1 || func_exit 1
  # Verify that the essential parts of the C compiler were installed.
  # gcc < 3.4 uses lib/gcc-lib/${gcctarget}/${version}/ whereas
  # gcc >= 3.4 uses libexec/gcc/${gcctarget}/${version}/.
  if { test -f "$HOST_CROSS_DIR/${target}-tools/bin/${target}-gcc" \
       && { test -f "$HOST_CROSS_DIR/${target}-tools/libexec/gcc/${gcctarget}/`echo ${version} | sed -e 's/-.*//'`/cc1" \
            || test -f "$HOST_CROSS_DIR/${target}-tools/lib/gcc-lib/${gcctarget}/`echo ${version} | sed -e 's/-.*//'`/cc1"; }; \
     }; then
    echo "Installation of gcc is complete."
  else
    echo "Installation of gcc in $HOST_CROSS_DIR/${target}-tools/ is incomplete." 1>&2
    func_exit 1
  fi
}

# func_build_cpu
# Builds the cross tools for one CPU.
# Input:
# - target_cpu      The CPU to build for
func_build_cpu ()
{
  {
    read line; read line; read line
    while read cpu target gccversion binutilsversion binutilstarget; do
      if test "$cpu" = "$target_cpu"; then
        if test "x$binutilsversion" != "x--"; then
          for version in `echo "$binutilsversion" | tr ',' ' '`; do
            func_build_binutils
          done
        fi
        gcctarget="$target"
        for version in `echo "$gccversion" | tr ',' ' '`; do
          func_build_gcc
        done
      fi
    done
  } < "$cross_tools_dir/cross.conf"
}

case "$mode" in
  cross )
    func_build_cross || func_exit 1
    ;;
  some )
    for target_cpu in $cpus
    do
      func_build_cpu || func_exit 1
    done
    ;;
  all )
    func_build_cross || func_exit 1
    func_get_all_cpus
    for target_cpu in $all_cpus
    do
      func_build_cpu || func_exit 1
    done
    ;;
esac

func_exit 0
