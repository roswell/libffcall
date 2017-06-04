/* Trampoline for powerpc CPU with ELFv2 calling convention */

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

/* Available registers: r0, r11, r12. */
/* However, r0 is special in that it cannot be used as a base register. */

/* According to the Power Architecture 64-bit ELF V2 ABI Specification:
   - 2.3.4: "Function pointers shall contain the global entry-point address."
   - 2.3.2.1: "All functions have a global entry point (GEP) available to any
     caller and pointing to the beginning of the prologue. Some functions may
     have a secondary entry point to optimize the cost of TOC pointer manage-
     ment. In particular, functions within a common module sharing the same
     TOC base value in r2 may be entered using a secondary entry point (the
     local entry point or LEP) that may bypass the code that loads a suitable
     TOC pointer value into the r2 register. When a dynamic or global linker
     transfers control from a function to another function in the same module,
     it may choose (but is not required) to use the local entry point."
   - 2.3.6: "For indirect function calls, the address of the function to be
     called is placed in r12 and the CTR register. ... The ELF V2 ABI requires
     the address of the called function to be in r12 when a cross-module
     function call is made."
 */

	.machine "ppc64"

	.globl tramp_r
tramp_r:
	/* We can assume that our own address (=tramp) is in r12. */
/* Move <data> into r11 */
	ld 11,16(12)	/* get <data> */
/* Get <function> */
	ld 12,24(12)
	/* The called function expects to see its own address in r12. */
	mtctr 12
	bctr
