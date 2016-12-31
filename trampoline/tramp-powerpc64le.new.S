/* Trampoline for powerpc64le CPU with ELF v2 calling convention */

/*
 * Copyright 1995-2006 Bruno Haible, <bruno@clisp.org>
 * Copyright 2015 Masanori Mitsugi, <mitsugi@linux.vnet.ibm.com>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: r0, r11, r12. */
/* However, r0 is special in that it cannot be used as a base register. */

	.globl tramp
tramp:
        /* We can assume that our own address (=tramp) is in r12. */
0:	std  3,4f-0b(12)  /* save r3 */
	ld   3,1f-0b(12)  /* get variable */
	ld  11,2f-0b(12)  /* get data */
	std 11,0(3)       /* Put data into variable */
	ld   3,4f-0b(12)  /* restore r3 */
	ld  12,3f-0b(12)  /* get function */
        /* The called function expects to see its own address in r12. */
	mtctr 12
	bctr
1:	.quad 0x1234567813578765 /* variable */
2:	.quad 0x7355471143622155 /* data */
3:	.quad 0xbabebec0dea0ffab /* function */
4:	.quad 0x0		 /* r3 save */
