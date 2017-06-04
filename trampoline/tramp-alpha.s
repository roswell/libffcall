/* Trampoline for alpha CPU */

/*
 * Copyright 1995 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	ldq $2,20($1)		/* data */
	ldq $3,28($1)		/* variable */
	ldq $27,36($1)		/* function */
	stq $2,0($3)
	/* The called function expects to see its own address in $27. */
	jmp $31,($27),0		/* jump to function */

	.align 3
data:
	.quad 0x73554711

	.align 3
variable:
	.quad 0x12345678

	.align 3
function:
	.quad 0xbabebec0

	.end tramp
