	.file	"proto.c"
	.text
	.align	2
	.global	tramp
	.type	tramp,function
tramp:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	ldr	r0, .L2
	sub	fp, ip, #4
	ldr	ip, .L2+4
	mov	lr, pc
	mov	pc, r0
	ldmea	fp, {fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	-1161904448
	.word	1934968593
.Lfe1:
	.size	tramp,.Lfe1-tramp
	.align	2
	.global	jump
	.type	jump,function
jump:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	ldr	r3, .L5
	sub	fp, ip, #4
	mov	pc, r3	@ indirect register jump
.L6:
	.align	2
.L5:
	.word	-1161904448
.Lfe2:
	.size	jump,.Lfe2-jump
	.ident	"GCC: (GNU) 3.1"
