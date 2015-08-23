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

/* Available registers: r0, r12, r11, r10, r9, r8, r7, r6, r5, r4, r3. */
/* However, r0 is special in that it cannot be used as a base register. */
/* And r3...r10 should not be clobbered because they contain the first 8
 * integer arguments to the function being called. */

	.globl tramp
tramp:
0:	std  3,4f-0b(12)  /* save r3 */
	ld   3,1f-0b(12)  /* get variable */
	ld  11,2f-0b(12)  /* get data */
	std 11,0(3)       /* Put data into variable */
	ld   3,4f-0b(12)  /* restore r3 */
	ld  12,3f-0b(12)  /* get function */
	mtctr 12
	bctr
1:	.quad 0x1234567813578765 /* variable */
2:	.quad 0x7355471143622155 /* data */
3:	.quad 0xbabebec0dea0ffab /* function */
4:	.quad 0x0		 /* r3 save */
