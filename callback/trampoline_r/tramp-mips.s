/* Trampoline for mips CPU */

/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
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
	lw	$2,16($25)
	lw	$25,20($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	 nop
$LC0:	.word	0x73554711
$LC1:	.word	0xbabebec0
	.end	tramp
