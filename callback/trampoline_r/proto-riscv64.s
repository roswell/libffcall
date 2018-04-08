	.file	"proto64.c"
	.option nopic
	.text
	.align	1
	.globl	tramp
	.type	tramp, @function
tramp:
	lui	a5,%hi(.LC0)
	ld	t2,%lo(.LC0)(a5)
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
	.dword	8310626826852639061
.LC1:
	.dword	-4990341601501839445
	.ident	"GCC: (GNU) 7.3.0"
