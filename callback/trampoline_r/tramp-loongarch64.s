/* Trampoline for LoongArch CPU in 64-bit mode */

/*
 * Copyright 1996-2022 Bruno Haible <bruno@clisp.org>
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

/* Available registers: $r12 ... $r20. */

	.text
	.align	3
	.globl	tramp
	.type	tramp, @function
tramp:
	pcaddu12i	$r12, 0
	/* Now our own address (=tramp) is in $r12. */
	ld.d		$r20, $r12, 16 /* $LC0-tramp */
	ld.d		$r12, $r12, 24 /* $LC1-tramp */
	jr		$r12
$LC0:
	.dword	0x7355471143622155
$LC1:
	.dword	0xbabebec0dea0ffab
	.size	tramp, .-tramp
