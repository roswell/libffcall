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
	/* Start putting together <data>. */
	li	t2,0x73554000
	/* Start putting together <function>. */
	li	t1,0xbabec000
	/* Finish putting together <data>. */
	add	t2,t2,0x711
	/* Finish putting together <function>. */
	add	t1,t1,0xbabebec0-0xbabec000
	/* Jump to <function>. */
	jr	t1
	.size	tramp, .-tramp
