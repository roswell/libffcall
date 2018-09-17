/* Trampoline for powerpc CPU with SysV.4 ABI */

/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
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

/* Available registers: r0, r11, r12. */
/* However, r0 is special in that it cannot be used as a base register. */

	.globl tramp
tramp:
/* Move <data> into register r11 */
	lis 11,0x7355
	ori 11,11,0x4711
/* Get <function> */
	lis 0,0xbabe
	ori 0,0,0xbec0
/* Jump to <function> */
	mtctr 0
	bctr
