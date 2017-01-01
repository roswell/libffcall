/* ELF hack for x86_64 CPU */

/*
 * Copyright 2016 Bruno Haible <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifdef BINFMT_ELF
	movq (%rsp),%r10
	addq $16,%rsp
#endif
