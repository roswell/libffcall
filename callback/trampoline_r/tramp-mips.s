/* Trampoline for mips CPU */

/*
 * Copyright 1995-1997 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: $2, $3. */

	.set	nobopt
	.set	noreorder
	.text
	.globl	tramp
	.ent	tramp
tramp:
	/* We can assume that our own address (=tramp) is in $25. */
	lw	$2,$LC0-tramp($25)
	lw	$25,$LC1-tramp($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	 nop
$LC0:	.word	0x73554711
$LC1:	.word	0xbabebec0
	.end	tramp
