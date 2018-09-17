/* Trampoline for arm64 CPU */

/*
 * Copyright 2017 Bruno Haible <bruno@clisp.org>
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

/* Available registers: x9, ..., x18. */

	.cpu generic+fp+simd
	.text

	.align	2
	.p2align 3,,7
	.global	tramp
	.type	tramp, %function
tramp:
	ldr	x9, .+24	/* get <data> */
	ldr	x10, .+28	/* get <variable> */
	ldr	x11, .+32	/* get <function> */
	str	x9, [x10]	/* store */
	br	x11		/* jump to <function> */
	nop			/* for alignment */
data:
	.xword 0x7355471143622155
variable:
	.xword 0x1234567813578765
function:
	.xword 0xbabebec0dea0ffab
	.size	tramp, .-tramp
