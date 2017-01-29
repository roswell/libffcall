/* Trampoline for powerpc64 CPU with AIX calling convention */

/*
 * Copyright 1995-2017 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: r0, r11, r12. */
/* However, r0 is special in that it cannot be used as a base register. */

	.machine "ppc64"

#ifdef _AIX
	.rename H.4.NO_SYMBOL{PR},""
	.lglobl H.4.NO_SYMBOL{PR}

	.globl .tramp_r
	.csect  H.4.NO_SYMBOL{PR},7
#else
	.globl tramp_r
	.globl .tramp_r
tramp_r:
	.quad .tramp_r
#endif
.tramp_r:
/* Move <data> into register r11 */
	ld 11,0(2)	/* get <data> */
/* Get <function> */
	ld 12,8(2)
/*
 * gcc-2.6.3 source says:
 * A function pointer is a pointer to a data area whose first word contains
 * the actual address of the function, whose second word contains a pointer
 * to its TOC, and whose third word contains a value to place in the static
 * chain register (r11). But we have already placed our information in r11.
 */
/*	ld 11,16(12)	   pass static chain in r11 */
	ld 2,8(12)	/* pass TOC in r2 */
	ld 0,0(12)	/* actual code address */
	mtctr 0
	bctr
