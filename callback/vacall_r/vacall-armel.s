	.cpu arm10tdmi
	.fpu softvfp
	.file	"vacall-armel.c"
	.text
	.align	2
	.global	__vacall_r
	.type	__vacall_r, %function
__vacall_r:
	@ args = 4, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #72
	add	r6, sp, #96
	ldr	r4, [r6, #-4]
	ldr	lr, [sp, #88]
	str	r4, [sp, #32]
	ldr	r4, [sp, #84]
	str	lr, [sp, #36]
	ldr	lr, [sp, #80]
	mov	r5, #0
	str	r4, [sp, #40]
	ldr	r4, [sp, #76]
	str	lr, [sp, #44]
	str	r5, [sp, #8]
	add	lr, sp, #80
	str	r0, [sp, #80]
	str	r1, [sp, #84]
	str	r4, [sp, #48]
	str	r2, [sp, #88]
	mov	r7, r0
	str	r3, [r6, #-4]
	mov	r8, r1
	str	lr, [sp, #4]
	str	r0, [sp, #52]
	str	r1, [sp, #56]
	str	r5, [sp, #12]
	str	r2, [sp, #60]
	str	r3, [sp, #64]
	str	r5, [sp, #0]
	ldr	r0, [ip, #4]
	mov	r1, sp
	mov	lr, pc
	ldr	pc, [ip, #0]
	ldr	lr, [sp, #12]
	cmp	lr, r5
	beq	.L3
	cmp	lr, #1
	beq	.L40
	cmp	lr, #2
	ldreqsb	r0, [sp, #24]
	beq	.L3
	cmp	lr, #3
	beq	.L40
	cmp	lr, #4
	ldreqsh	r0, [sp, #24]
	beq	.L3
	cmp	lr, #5
	ldreqh	r0, [sp, #24]
	beq	.L3
	cmp	lr, #6
	beq	.L39
	cmp	lr, #7
	beq	.L39
	cmp	lr, #8
	beq	.L39
	cmp	lr, #9
	beq	.L39
	sub	r3, lr, #10
	cmp	r3, #1
	bls	.L38
	cmp	lr, #12
	ldreq	r0, [sp, #24]	@ float
	beq	.L3
	cmp	lr, #13
	beq	.L38
	cmp	lr, #14
	beq	.L39
	cmp	lr, #15
	bne	.L3
	ldr	r3, [sp, #0]
	tst	r3, #1
	ldrne	r0, [sp, #8]
	bne	.L3
	tst	r3, #1024
	beq	.L3
	ldr	r3, [sp, #16]
	cmp	r3, #1
	ldreq	r3, [sp, #8]
	ldreqb	r0, [r3, #0]	@ zero_extendqisi2
	beq	.L3
	cmp	r3, #2
	ldreq	r3, [sp, #8]
	ldrne	r3, [sp, #8]
	ldreqh	r0, [r3, #0]
	ldrne	r0, [r3, #0]
.L3:
	ldr	r3, [sp, #32]
	str	r3, [r6, #-4]
	ldr	r2, [sp, #48]
	str	r2, [r6, #-20]
	ldr	r3, [sp, #36]
	str	r3, [r6, #-8]
	ldr	r2, [sp, #40]
	str	r2, [r6, #-12]
	ldr	r3, [sp, #44]
	str	r3, [r6, #-16]
	add	sp, sp, #72
	ldmfd	sp!, {r4, r5, r6, r7, r8, pc}
.L40:
	ldrb	r0, [sp, #24]	@ zero_extendqisi2
	b	.L3
.L39:
	ldr	r0, [sp, #24]
	b	.L3
.L38:
	ldr	r0, [sp, #24]
	ldr	r1, [sp, #28]
	b	.L3
	.size	__vacall_r, .-__vacall_r
	.ident	"GCC: (GNU) 3.4.4 (release) (CodeSourcery ARM 2005q3-2)"
