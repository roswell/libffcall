	.file	"proto.c"
	.option nopic
	.text
	.align	1
	.globl	tramp
	.type	tramp, @function
tramp:
	li	t2,1934966784
	li	t1,-1161904128
	add	t2,t2,1809
	add	t1,t1,-320
	jr	t1
	.size	tramp, .-tramp
	.align	1
	.globl	jump
	.type	jump, @function
jump:
	li	a5,-1161904128
	add	a5,a5,-320
	jr	a5
	.size	jump, .-jump
	.ident	"GCC: (GNU) 7.3.0"
