/* Trampoline test */

/*
 * Copyright 1995-1999, 2001-2002, 2004-2006, 2017 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#include "config.h"  /* Define __${host_cpu}__ */

#include <stdio.h>
#include <stdlib.h>

#include "callback.h"

#define MAGIC1  0x9db9af42
#define MAGIC2  0xa2f9d045
#define MAGIC3  0x7aff3cb4

#ifdef __cplusplus
typedef int (*function)(...);
#else
typedef int (*function)();
#endif

int f (int x)
{
  return x + MAGIC3;
}

void vf (void* data, va_alist alist)
{
  if (data != (void*)MAGIC1) { printf("wrong data\n"); exit(1); }
  va_start_int(alist);
 {int a = va_arg_int(alist);
  int r = f(a);
  va_return_int(alist, r);
}}

int main ()
{
  function cf = alloc_callback((function)&vf, (void*)MAGIC1);
  if ((*cf)(MAGIC2) == MAGIC2+MAGIC3)
    { free_callback(cf); printf("Works, test1 passed.\n"); exit(0); }
  else
    { printf("Doesn't work!\n"); exit(1); }
}
