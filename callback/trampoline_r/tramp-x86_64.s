/* Trampoline for x86_64 CPU */

/*
 * Copyright 2004, 2016 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

/* Available registers: %rax, %r10, %r11. */

.globl tramp
	.type	tramp,@function
tramp:
	movabsq	$0x7355471143622155, %r10
	movabsq	$0xBABEBEC0DEA0FFAB, %rax
	jmp	*%rax
.Lfe1:
	.size	tramp,.Lfe1-tramp

.globl trampelf
	.type	trampelf,@function
trampelf:
	movabsq	$0x7355471143622155, %r10
	movabsq	$0xBABEBEC0DEA0FFAB, %rax
	subq	$16, %rsp
	movq	%r10, (%rsp)
	jmp	*%rax
.Lfe2:
	.size	trampelf,.Lfe2-trampelf
