/* Trampoline for riscv32 CPU */

/*
 * Copyright 2018-2019 Bruno Haible <bruno@clisp.org>
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
	/* Get tramp in t3. */
	auipc	t3,0
	/* Get <variable>, <data>. */
	lw	t0,24(t3)
	lw	t1,28(t3)
	/* Get <function>. */
	lw	t2,32(t3)
	/* Perform the assignment. */
	sw	t0,(t1)
	/* Jump to <function>. */
	jr	t2
data:
	.word	0x73554711
variable:
	.word	0x12345678
function:
	.word	0xbabebec0
	.size	tramp, .-tramp
