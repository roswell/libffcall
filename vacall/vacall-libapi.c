/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef REENTRANT
#include "vacall.h"
#else /* REENTRANT */
#include "vacall_r.h"
#endif

#ifndef REENTRANT

/* This is the function pointer vacall(). A function pointer indirection is
   needed because gcc-3.4 generates invalid code when the address of a symbol
   is casted to a function pointer with different return type.
   (http://gcc.gnu.org/ml/gcc-patches/2003-12/msg01767.html) */
#ifdef __cplusplus
extern "C" void vacall_receiver (); /* the return type is variable, not void! */
#else
extern void vacall_receiver (); /* the return type is variable, not void! */
#endif
void (*vacall) () = vacall_receiver;

/* This is the function called by vacall(). */
void (* vacall_function) (va_alist);

#endif

/* Room for returning structs according to the Sun C non-reentrant struct return convention. */
__va_struct_buffer_t vacall_struct_buffer;

int /* no return type, since this never returns */
vacall_error_type_mismatch (enum __VAtype start_type, enum __VAtype return_type)
{
  /* If you see this, fix your code. */
  fprintf (stderr, "vacall: va_start type %d and va_return type %d disagree.\n",
                   (int)start_type, (int)return_type);
  abort();
#if defined(__cplusplus)
  return 0;
#endif
}

int /* no return type, since this never returns */
vacall_error_struct_too_large (unsigned int size)
{
  /* If you see this, increase __VA_ALIST_WORDS: */
  fprintf (stderr, "vacall: struct of size %u too large for Sun C struct return.\n",
                   size);
  abort();
#if defined(__cplusplus)
  return 0;
#endif
}
