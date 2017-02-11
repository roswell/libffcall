/* Trampoline for powerpc64 CPU with ELFv2 calling convention */

/*
 * Copyright 2017 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
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

	.globl tramp
tramp:
	/* We can assume that our own address (=tramp) is in r12. */
/* Move <data> into <variable> */
	ld 11,24(12)	/* get <variable> */
	ld 0,32(12)	/* get <data> */
	std 0,0(11)
/* Get <function> */
	ld 12,40(12)
	/* The called function expects to see its own address in r12. */
	mtctr 12
	bctr
