/* Trampoline for alpha CPU */

/*
 * Copyright 1995-1997, 2016 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: $1, $2, $3, $4, $5, $6, $7, $8. */

	.set noreorder
	.set noat
.text
	.align 3

	.globl tramp
	.ent tramp
tramp:
	br $1,tramp1		/* $1 := address of tramp1 */
tramp1:	/* Load everything relative to $1. If we were to use "lda" instructions
	 * we would have to do the usual  ldgp $29,0($27)
	 */
	ldq $27,20($1)		/* function */
	ldq $1,12($1)		/* data */
	/* The called function expects to see its own address in $27. */
	jmp $31,($27),0		/* jump to function */

	.align 3
data:
	.quad 0x73554711

	.align 3
function:
	.quad 0xbabebec0

	.end tramp

.text
	.align 3

	.globl trampelf
	.ent trampelf
trampelf:
	br $1,trampelf1		/* $1 := address of tramp1 */
trampelf1: /* Load everything relative to $1. If we were to use "lda" instructions
	 * we would have to do the usual  ldgp $29,0($27)
	 */
	ldq $2,20($1)		/* data2 */
	lda $30,-16($30)
	ldq $27,28($1)		/* function2 */
	stq $2,0($30)
	/* The called function expects to see its own address in $27. */
	jmp $31,($27),0		/* jump to function */

	.align 3
data2:
	.quad 0x73554711

	.align 3
function2:
	.quad 0xbabebec0

	.end trampelf
