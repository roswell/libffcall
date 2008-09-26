/* Instruction cache flushing for arm */

/*
 * Copyright 1997 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */
#include <linux/unistd.h>

void __TR_clear_cache (char *first_addr, char *last_addr)
{
  asm volatile ("swi %0" : : "i" (__ARM_NR_cacheflush));
}
