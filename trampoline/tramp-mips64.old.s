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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
#	dli	$2,0x1234567813578765
	lui	$2,0x1234
	ori	$2,$2,0x5678
	dsll	$2,$2,16
	ori	$2,$2,0x1357
	dsll	$2,$2,16
	ori	$2,$2,0x8765
#	dli	$3,0x7355471143622155
	lui	$3,0x7355
	ori	$3,$3,0x4711
	dsll	$3,$3,16
	ori	$3,$3,0x4362
	dsll	$3,$3,16
	ori	$3,$3,0x2155
	sd	$3,0($2)
#	dli	$25,0xbabebec0dea0ffab
	lui	$25,0xbabe
	ori	$25,$25,0xbec0
	dsll	$25,$25,16
	ori	$25,$25,0xdea0
	dsll	$25,$25,16
	ori	$25,$25,0xffab
	/* The called function expects to see its own address in $25. */
	j	$25
	/* Some MIPS hardware needs this nop. It fills the branch delay slot. */
	nop
	.end	tramp
