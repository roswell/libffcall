/* Trampoline for riscv64 CPU */

/*
 * Copyright 2018 Bruno Haible <bruno@clisp.org>
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

/* Available registers: t0, ..., t6. */

	.text

	.globl tramp
	.type	tramp, @function
tramp:
	/* Get tramp in t0. */
	auipc	t0,0
	/* Get <data> in t2 and <function> in t1. */
	ld	t1,24(t0)
	ld	t2,16(t0)
	/* Jump to <function>. */
	jr	t1
data:
	.quad	0x7355471143622155
function:
	.quad	0xbabebec0dea0ffab
	.size	tramp, .-tramp
