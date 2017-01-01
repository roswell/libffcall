/* Trampoline for powerpc CPU with SysV.4 ABI */

/*
 * Copyright 1995-2006, 2016 Bruno Haible, <bruno@clisp.org>
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
/* Move <data> into register r11 */
	lis 11,0x7355
	ori 11,11,0x4711
/* Get <function> */
	lis 0,0xbabe
	ori 0,0,0xbec0
/* Jump to <function> */
	mtctr 0
	bctr

	.globl trampelf
trampelf:
/* Move <data> into register r11 */
	lis 11,0x7355
	ori 11,11,0x4711
/* Get <function> */
	lis 0,0xbabe
	ori 0,0,0xbec0
/* Make room on the stack */
	addi 1,1,-16
/* Store <data> on the stack */
	stw 11,0(1)
/* Jump to <function> */
	mtctr 0
	bctr
