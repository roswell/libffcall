/* Trampoline for mips CPU */

/*
 * Copyright 1995-1997, 2016 Bruno Haible, <bruno@clisp.org>
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

	.globl	tramp
	.ent	tramp
tramp:
	/* We can assume that our own address (=tramp) is in $25. */
	lw	$2,16($25)
	lw	$25,20($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	 nop
$LC0:	.word	0x73554711
$LC1:	.word	0xbabebec0
	.end	tramp

	.globl	trampelf
	.ent	trampelf
trampelf:
	/* We can assume that our own address (=trampelf) is in $25. */
	subu	$sp,$sp,16
	lw	$2,24($25)
	lw	$25,28($25)
	sw	$2,($sp)
	/* The called function expects to see its own address in $25. */
	j	$25
	 nop
$LC2:	.word	0x73554711
$LC3:	.word	0xbabebec0
	.end	trampelf
