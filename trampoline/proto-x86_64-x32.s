	.file	"proto.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	tramp
	.type	tramp, @function
tramp:
	movl	$1934968593, 305419896
	xorl	%eax, %eax
	movl	$3133062848, %edx
	jmp	*%rdx
	.size	tramp, .-tramp
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	jump
	.type	jump, @function
jump:
	movl	$3133062848, %eax
	jmp	*%rax
	.size	jump, .-jump
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
