/* Trampoline for mips CPU */

/*
 * Copyright 1996-2017 Bruno Haible <bruno@clisp.org>
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

/* Available registers: $2, $3, $12 ... $15, $24. */

	.set	nobopt
	.set	noreorder
	.text
	.globl	tramp
	.ent	tramp
tramp:
	/* We can assume that our own address (=tramp) is in $25. */
	lw	$2,24($25)
	lw	$3,28($25)
	sw	$3,0($2)
	lw	$25,32($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
	/* We'll actually store the data words immediately after the code. */
	/* The assembler just doesn't like ".word" inside section .text. */
	.data
$LC0:
	.word	0x12345678
$LC1:
	.word	0x73554711
$LC2:
	.word	0xbabebec0
	.end	tramp
