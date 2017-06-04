/* Trampoline accessor test */

/*
 * Copyright 1995-2005 Bruno Haible <bruno@clisp.org>
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

#include <stdio.h>
#include <stdlib.h>

#include "trampoline.h"

#ifdef __cplusplus
typedef int (*function)(...);
#else
typedef int (*function)();
#endif

int f (int x)
{ return x; }

void* variable;

static int data;

int main ()
{
  function cf = alloc_trampoline((function)&f, &variable, &data);
  if (is_trampoline((void*)&main))
    { printf("is_trampoline(&main) returns true!\n"); exit(1); }
  if (!is_trampoline((void*)cf))
    { printf("is_trampoline() returns false!\n"); exit(1); }
  if (trampoline_address((void*)cf) != (function)&f)
    { printf("trampoline_address() doesn't work!\n"); exit(1); }
  if (trampoline_variable((void*)cf) != &variable)
    { printf("trampoline_variable() doesn't work!\n"); exit(1); }
  if (trampoline_data((void*)cf) != &data)
    { printf("trampoline_data() doesn't work!\n"); exit(1); }
  printf("test2 passed.\n");
  exit(0);
}
