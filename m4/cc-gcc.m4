dnl -*- Autoconf -*-
dnl Copyright (C) 1993-2024 Free Software Foundation, Inc.
dnl This file is free software, distributed under the terms of the GNU
dnl General Public License as published by the Free Software Foundation;
dnl either version 2 of the License, or (at your option) any later version.
dnl As a special exception to the GNU General Public License, this file
dnl may be distributed as part of a program that contains a configuration
dnl script generated by Autoconf, under the same distribution terms as
dnl the rest of that program.

dnl From Bruno Haible, Marcus Daniels.

AC_PREREQ([2.13])

AC_DEFUN([CL_CC_GCC],
[
  AC_REQUIRE([AC_PROG_CPP])
  AC_CACHE_CHECK([whether using GNU C], [cl_cv_prog_cc_gcc],
    [AC_EGREP_CPP([yes],
       [#ifdef __GNUC__
        yes
        #endif
       ],
       [cl_cv_prog_cc_gcc=yes],
       [cl_cv_prog_cc_gcc=no])
    ])
  if test $cl_cv_prog_cc_gcc = yes; then
    CC_GCC=true
    GCC_X_NONE='-x none'

    dnl On arm, there are two slightly different syntaxes for assembly language:
    dnl The "divided" syntax (standard since ca. 2000) and the "unified" syntax
    dnl (supported by GNU binutils since 2009).  See
    dnl https://sourceware.org/binutils/docs/as/ARM_002dInstruction_002dSet.html
    dnl While GNU as and thus GCC supports both, clang by default uses an
    dnl "integrated" assembler that supports only the "unified" syntax, leading
    dnl to errors "error: invalid instruction" on instructions such as stmeqia.
    dnl We therefore need to tell clang to use the external assembler.
    AC_CACHE_CHECK([whether using clang], [cl_cv_prog_cc_clang],
      [AC_EGREP_CPP([yes],
         [#ifdef __clang__
          yes
          #endif
         ],
         [cl_cv_prog_cc_clang=yes],
         [cl_cv_prog_cc_clang=no])
      ])
    if test $cl_cv_prog_cc_clang = yes; then
      GCC_X_NONE="$GCC_X_NONE -no-integrated-as"
    fi
  else
    CC_GCC=false
    GCC_X_NONE=''
  fi
  AC_SUBST([CC_GCC])
  AC_SUBST([GCC_X_NONE])
])
