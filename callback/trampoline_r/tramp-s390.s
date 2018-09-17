/* Trampoline for s390 CPU */

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

/* Available registers: r0, r1.
   r13 cannot be used as literal pool pointer here, because it is call-saved. */

	.text

	.align	4
	.globl tramp
	.type	tramp, @function
tramp:
	/* Get .L1 in %r1. */
	bras	%r1,.L1
.L1:
	/* Get <data> in %r0 and <function> in %r1. */
	lm	%r0,%r1,data-.L1(%r1)
	/* Jump to <function>. */
	br	%r1
	.align	4
data:
	.long	0x73554711
function:
	.long	0xbabebec0
	.size	tramp, .-tramp
