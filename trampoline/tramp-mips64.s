/* Trampoline for mips CPU in 64-bit mode */

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
	.globl	main
	.ent	main
main:
	.end	main
	.globl	tramp
	.ent	tramp
tramp:
	/* We can assume that our own address (=tramp) is in $25. */
	ld	$2,$LC0-tramp($25)
	ld	$3,$LC1-tramp($25)
	sd	$3,0($2)
	ld	$25,$LC2-tramp($25)
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some Mips hardware running Irix-4.0.5 needs this nop. */
	nop
$LC0:
	.dword	0x1234567813578765
$LC1:
	.dword	0x7355471143622155
$LC2:
	.dword	0xbabebec0dea0ffab
	.end	tramp
