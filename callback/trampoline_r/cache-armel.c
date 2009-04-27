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
    register unsigned long _beg __asm ("a1") = first_addr;
    register unsigned long _end __asm ("a2") = last_addr;
    register unsigned long _flg __asm ("a3") = 0; 
    __asm __volatile__ ("swi 0x9f0002" : : "r" (_beg), "r" (_end), "r" (_flg));
}
