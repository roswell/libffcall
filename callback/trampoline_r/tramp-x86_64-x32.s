/* Trampoline for x86_64 CPU with x32 ABI */

/*
 * Copyright 2017 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: %rax, %r10, %r11. */

	.globl	tramp
	.type	tramp, @function
tramp:
	movl	$0x73554711,%r10d
	movl	$0xbabebec0,%eax
	jmp	*%rax
	.size	tramp, .-tramp
