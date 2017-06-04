/* Trampoline for s390 CPU */

/*
 * Copyright 1995 Bruno Haible <bruno@clisp.org>
 * Copyright 2001 Gerhard Tonn <gt@debian.org>
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

/* Available registers: r0, r1. */

.globl _tramp
_tramp:
	lr	%r0,%r13
	bras    %r13,.LTN0_0
.LT0_0:
.LC0:
        .long   0x73554711
.LC1:
        .long   0x12345678
.LC2:
        .long   0xbabebec0
.LTN0_0:
        l       %r1,.LC0-.LT0_0(%r13)
        mvc     0(4,%r1),.LC1-.LT0_0(%r13)
        l       %r1,.LC2-.LT0_0(%r13)
	lr	%r13,%r0
        br      %r1
