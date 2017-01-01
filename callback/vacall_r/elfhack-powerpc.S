/* ELF hack for powerpc CPU */

/*
 * Copyright 2016 Bruno Haible <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifdef BINFMT_ELF
	lwz 11,0(1)
	addi 1,1,16
#endif
