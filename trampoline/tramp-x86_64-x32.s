/* Trampoline for x86_64 CPU with x32 ABI */

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

/* Available registers: %rax, %r10, %r11. */

	.globl	tramp
	.type	tramp, @function
tramp:
	movl	$0x73554711,0x12345678
	movl	$0xbabebec0,%eax
	jmp	*%rax
	.size	tramp, .-tramp
