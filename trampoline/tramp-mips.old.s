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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Available registers: $2, $3, $12 ... $15, $24. */

	.set	nobopt
	.set	noreorder
	.text
	.globl	tramp
	.ent	tramp
tramp:
	li	$2,0x73550000
	ori	$2,$2,0x4711
	sw	$2,0x12345678
	li	$25,0xbabe0000
	ori	$25,$25,0xbec0
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some MIPS hardware needs this nop. It fills the branch delay slot. */
	nop
	.end	tramp
