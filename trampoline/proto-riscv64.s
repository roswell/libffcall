	.file	"proto64.c"
	.option nopic
	.text
	.align	1
	.globl	tramp
	.type	tramp, @function
tramp:
	lui	a5,%hi(.LC0)
	ld	a5,%lo(.LC0)(a5)
	li	a3,33
	li	a4,85
	sb	a3,1(a5)
	li	a3,98
	sb	a3,2(a5)
	li	a3,67
	sb	a3,3(a5)
	li	a3,17
	sb	a4,0(a5)
	sb	a3,4(a5)
	sb	a4,6(a5)
	li	a3,71
	li	a4,115
	sb	a3,5(a5)
	sb	a4,7(a5)
	lui	a5,%hi(.LC1)
	ld	t1,%lo(.LC1)(a5)
	jr	t1
	.size	tramp, .-tramp
	.align	1
	.globl	jump
	.type	jump, @function
jump:
	lui	a5,%hi(.LC1)
	ld	a5,%lo(.LC1)(a5)
	jr	a5
	.size	jump, .-jump
	.section	.srodata.cst8,"aM",@progbits,8
	.align	3
.LC0:
	.dword	1311768465192224613
.LC1:
	.dword	-4990341601501839445
	.ident	"GCC: (GNU) 7.3.0"
