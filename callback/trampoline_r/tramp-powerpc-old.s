/* Trampoline for powerpc CPU */

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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Available registers: r0, r11, r12. */
/* However, r0 is special in that it cannot be used as a base register. */
/* THIS CODE IS BROKEN, AS IT CLOBBERS r10 !! */

	.globl .tramp
.csect .text[PR]
.tramp:
/* Move <data> into register r11 */
	liu 11,0x7355
	oril 11,11,0x4711
/* Get <function> */
	liu 10,0xbabe
	oril 10,10,0xbec0
/*
 * gcc-2.6.3 source says:
 * A function pointer is a pointer to a data area whose first word contains
 * the actual address of the function, whose second word contains a pointer
 * to its TOC, and whose third word contains a value to place in the static
 * chain register (r11). But we have already placed our information in r11.
 */
/*	l 11,8(10)	   pass static chain in r11 */
	l 2,4(10)	/* pass TOC in r2 */
	l 0,0(10)	/* actual code address */
	mtctr 0
	bctr
