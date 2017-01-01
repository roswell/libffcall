/* Trampoline for mips CPU in 64-bit mode */

/*
 * Copyright 1996, 2016 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: $2, $3, $12 ... $15, $24. */

	.set	nobopt
	.set	noreorder
	.text

	.globl	main
	.ent	main
main:
	.end	main

	.globl	tramp
	.ent	tramp
tramp:
	/* We can assume that our own address (=tramp) is in $25. */
	ld	$2,16($25)
	ld	$25,24($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
$LC0:
	.dword	0x7355471143622155
$LC1:
	.dword	0xbabebec0dea0ffab
	.end	tramp

	.globl	trampelf
	.ent	trampelf
trampelf:
	/* We can assume that our own address (=trampelf) is in $25. */
	dsubu	$sp,$sp,16
	ld	$2,24($25)
	ld	$25,32($25)
	sd	$2,($sp)
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
$LC2:
	.dword	0x7355471143622155
$LC3:
	.dword	0xbabebec0dea0ffab
	.end	trampelf
