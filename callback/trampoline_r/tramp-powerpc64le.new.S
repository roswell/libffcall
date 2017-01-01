/* Trampoline for powerpc64 CPU with ELF v2 calling convention */

/*
 * Copyright 1995-2006, 2016 Bruno Haible, <bruno@clisp.org>
 * Copyright 2015 Masanori Mitsugi, <mitsugi@linux.vnet.ibm.com>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: r0, r11, r12. */
/* However, r0 is special in that it cannot be used as a base register. */
/* And r12 is, by convention, the address of the current function. */

	.globl tramp
tramp:
        /* We can assume that our own address (=tramp) is in r12. */
0:      ld  11,1f-0b(12)  /* get data */
        ld  12,2f-0b(12)  /* get function */
        /* The called function expects to see its own address in r12. */
        mtctr 12
        bctr
1:      .quad 0x7355471143622155 /* data */
2:      .quad 0xbabebec0dea0ffab /* function */

	.globl trampelf
trampelf:
        /* We can assume that our own address (=trampelf) is in r12. */
0:      ld  11,1f-0b(12)  /* get data */
        ld  12,2f-0b(12)  /* get function */
        addi 1,1,-16  /* Make room on the stack */
        std 11,0(1)  /* Store data on the stack */
        /* The called function expects to see its own address in r12. */
        mtctr 12
        bctr
1:      .quad 0x7355471143622155 /* data */
2:      .quad 0xbabebec0dea0ffab /* function */
