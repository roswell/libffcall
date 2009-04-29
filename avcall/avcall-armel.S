#include "asmarm.h"
	.cpu arm10tdmi
	.fpu softvfp
	.file	"avcall-armel.c"
	.text
	.align	2
	.global	__builtin_avcall
	.type	__builtin_avcall, %function
__builtin_avcall:
	@ args = 0, pretend = 0, frame = 1024
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	ldr	r3, [r0, #20]
	mov	lr, #4
	rsb	r3, r0, r3
	sub	r3, r3, #32
	mov	ip, r3, asr #2
	sub	sp, sp, #1024
	cmp	lr, ip
	mov	r4, r0
	mov	r0, sp
	bge	.L59
.L75:
	mov	r3, lr, asl #2
	add	r2, r3, r4
	ldr	r1, [r2, #32]
	add	lr, lr, #1
	add	r3, r3, r0
	cmp	lr, ip
	str	r1, [r3, #-16]
	blt	.L75
.L59:
	add	r0, r4, #32
	ldmia	r0, {r0, r1, r2, r3}	@ phole ldm
	mov	lr, pc
	ldr	pc, [r4, #0]
	ldr	r2, [r4, #12]
	mov	lr, r0
	cmp	r2, #1
	beq	.L7
	cmp	r2, #0
	beq	.L73
	cmp	r2, #2
	beq	.L65
	cmp	r2, #3
	beq	.L65
	cmp	r2, #4
	beq	.L65
	cmp	r2, #5
	beq	.L66
	cmp	r2, #6
	beq	.L66
	cmp	r2, #7
	beq	.L73
	cmp	r2, #8
	beq	.L73
	cmp	r2, #9
	beq	.L73
	cmp	r2, #10
	beq	.L73
	sub	r3, r2, #11
	cmp	r3, #1
	bls	.L72
	cmp	r2, #13
	ldreq	r3, [r4, #8]
	streq	r0, [r3, #0]	@ float
	beq	.L7
	cmp	r2, #14
	beq	.L76
	cmp	r2, #15
	beq	.L73
	cmp	r2, #16
	bne	.L7
	ldr	r3, [r4, #4]
	tst	r3, #1
	beq	.L37
	ldr	r3, [r4, #16]
	cmp	r3, #1
	ldreq	r2, [r4, #8]
	ldreqb	r3, [r0, #0]	@ zero_extendqisi2
	streqb	r3, [r2, #0]
	beq	.L7
	cmp	r3, #2
	ldreq	r3, [r4, #8]
	ldreqh	lr, [r0, #0]
	beq	.L64
	cmp	r3, #4
	ldrls	r2, [r4, #8]
	ldrls	r3, [lr, #0]
	strls	r3, [r2, #0]
	bls	.L7
	cmp	r3, #8
	beq	.L77
	add	r3, r3, #3
	mov	r2, r3, lsr #2
	subs	r2, r2, #1
	bmi	.L7
	ldr	r0, [r4, #8]
.L48:
	ldr	r3, [lr, r2, asl #2]
	str	r3, [r0, r2, asl #2]
	subs	r2, r2, #1
	bpl	.L48
.L7:
	mov	r0, #0
	add	sp, sp, #1024
	ldmfd	sp!, {r4, pc}
.L73:
	ldr	r3, [r4, #8]
	str	lr, [r3, #0]
	b	.L7
.L65:
	ldr	r3, [r4, #8]
	strb	lr, [r3, #0]
	b	.L7
.L66:
	ldr	r3, [r4, #8]
.L64:
	strh	lr, [r3, #0]	@ movhi
	b	.L7
.L37:
	tst	r3, #512
	beq	.L7
	ldr	r3, [r4, #16]
	cmp	r3, #1
	beq	.L65
	cmp	r3, #2
	beq	.L66
	cmp	r3, #4
	bls	.L73
	cmp	r3, #8
	bne	.L7
.L72:
	ldr	r3, [r4, #8]
	str	r1, [r3, #4]
	str	lr, [r3, #0]
	b	.L7
.L76:
	ldr	r3, [r4, #8]
	stmia	r3, {r0-r1}
	b	.L7
.L77:
	ldr	r3, [r4, #8]
	ldr	r2, [lr, #0]
	str	r2, [r3, #0]
	ldr	r1, [lr, #4]
	str	r1, [r3, #4]
	b	.L7
	.size	__builtin_avcall, .-__builtin_avcall
	.ident	"GCC: (GNU) 3.4.4 (release) (CodeSourcery ARM 2005q3-2)"
