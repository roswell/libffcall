/* ELF hack for s390 CPU */

/*
 * Copyright 2016 Bruno Haible <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#ifdef BINFMT_ELF
	l %r0,0(%r15)
	ahi %r15,8
#endif
