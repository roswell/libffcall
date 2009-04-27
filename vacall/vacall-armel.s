	.cpu arm10tdmi
	.fpu softvfp
	.file	"vacall-armel.c"
	.text
	.align	2
	.global	__vacall
	.type	__vacall, %function
__vacall:
	@ args = 4, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, lr}
	sub	sp, sp, #76
	add	r6, sp, #96
	ldr	lr, [r6, #-4]
	ldr	ip, [sp, #88]
	str	lr, [sp, #32]
	ldr	lr, [sp, #84]
	str	ip, [sp, #36]
	ldr	ip, [sp, #80]
	str	lr, [sp, #40]
	ldr	lr, [sp, #76]
	mov	r4, #0
	str	ip, [sp, #44]
	add	ip, sp, #80
	str	r0, [sp, #80]
	str	lr, [sp, #48]
	str	r1, [sp, #84]
	str	r2, [sp, #88]
	mov	r7, r0
	str	r3, [r6, #-4]
	str	r4, [sp, #12]
	str	ip, [sp, #4]
	str	r0, [sp, #52]
	str	r3, [sp, #64]
	str	r1, [sp, #56]
	str	r2, [sp, #60]
	str	r4, [sp, #0]
	str	r4, [sp, #8]
	mov	r0, sp
	ldr	r3, .L42
	mov	r5, r1
	mov	lr, pc
	ldr	pc, [r3, #0]
	ldr	ip, [sp, #12]
	cmp	ip, r4
	beq	.L3
	cmp	ip, #1
	beq	.L40
	cmp	ip, #2
	ldreqsb	r0, [sp, #24]
	beq	.L3
	cmp	ip, #3
	beq	.L40
	cmp	ip, #4
	ldreqsh	r0, [sp, #24]
	beq	.L3
	cmp	ip, #5
	ldreqh	r0, [sp, #24]
	beq	.L3
	cmp	ip, #6
	beq	.L39
	cmp	ip, #7
	beq	.L39
	cmp	ip, #8
	beq	.L39
	cmp	ip, #9
	beq	.L39
	sub	r3, ip, #10
	cmp	r3, #1
	bls	.L38
	cmp	ip, #12
	ldreq	r0, [sp, #24]	@ float
	beq	.L3
	cmp	ip, #13
	beq	.L38
	cmp	ip, #14
	beq	.L39
	cmp	ip, #15
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
	add	sp, sp, #76
	ldmfd	sp!, {r4, r5, r6, r7, pc}
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
.L43:
	.align	2
.L42:
	.word	vacall_function
	.size	__vacall, .-__vacall
	.ident	"GCC: (GNU) 3.4.4 (release) (CodeSourcery ARM 2005q3-2)"
