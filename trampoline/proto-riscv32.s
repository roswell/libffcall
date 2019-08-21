	.file	"proto.c"
	.option nopic
	.text
	.align	1
	.globl	tramp
	.type	tramp, @function
tramp:
	li	a5,1934966784
	li	a4,305418240
	add	a5,a5,1809
	li	t1,-1161904128
	sw	a5,1656(a4)
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
