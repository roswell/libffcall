/* Trampoline for s390x CPU */

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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Available registers: r0, r1.
   r13 cannot be used as literal pool pointer here, because it is call-saved. */

	.text

	.align	8
	.globl tramp
	.type	tramp, @function
tramp:
	/* Get .L1 in %r1. */
	larl	%r1,.L1
.L1:
	/* Get <variable>, <data>, and perform the assignment. */
	lg	%r0,data-.L1(%r1)
	lg	%r1,variable-.L1(%r1)
	stg	%r0,0(%r1)
	/* Get .L2 in %r1. */
	larl	%r1,.L2
.L2:
	/* Get <function>. */
	lg	%r1,function-.L2(%r1)
	/* Jump to <function>. */
	br	%r1
	.align	8
data:
	.quad	0x7355471143622155
variable:
	.quad	0x1234567813578765
function:
	.quad	0xbabebec0dea0ffab
	.size	tramp, .-tramp
