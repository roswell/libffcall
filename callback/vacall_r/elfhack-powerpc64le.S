/* ELF hack for powerpc64 CPU */

/*
 * Copyright 2016 Bruno Haible <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifdef BINFMT_ELF
	ld r11,0(r1)
	addi r1,r1,-16
#endif
