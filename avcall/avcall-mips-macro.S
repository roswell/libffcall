	.file	1 "avcall-mips.c"
	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align	2
	.globl	__builtin_avcall
	.ent	__builtin_avcall
	.type	__builtin_avcall, @function
__builtin_avcall:
	.frame	$fp,96,$31		# vars= 56, regs= 3/0, args= 16, extra= 8
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	subu	$sp,$sp,96
	.cprestore 16
	sw	$31,88($sp)
	sw	$fp,84($sp)
	sw	$28,80($sp)
	move	$fp,$sp
	sw	$4,96($fp)
	addu	$sp,$sp,-1024
	addu	$2,$sp,16
	sw	$2,24($fp)
	sw	$sp,28($fp)
	lw	$2,96($fp)
	lw	$3,20($2)
	lw	$2,96($fp)
	subu	$2,$3,$2
	addu	$2,$2,-56
	sra	$2,$2,2
	sw	$2,32($fp)
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x400
	beq	$2,$0,$L2
	lw	$2,96($fp)
#APP
	l.s $f12,28($2)
#NO_APP
$L2:
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x1000
	beq	$2,$0,$L3
	lw	$2,96($fp)
#APP
	l.d $f12,40($2)
#NO_APP
$L3:
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x800
	beq	$2,$0,$L4
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x1400
	beq	$2,$0,$L4
	lw	$2,96($fp)
#APP
	l.s $f14,32($2)
#NO_APP
$L4:
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x2000
	beq	$2,$0,$L5
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x1400
	beq	$2,$0,$L5
	lw	$2,96($fp)
#APP
	l.d $f14,48($2)
#NO_APP
$L5:
	li	$2,4			# 0x4
	sw	$2,36($fp)
$L6:
	lw	$2,36($fp)
	lw	$3,32($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L9
	b	$L7
$L9:
	lw	$2,36($fp)
	sll	$3,$2,2
	lw	$2,28($fp)
	addu	$4,$3,$2
	lw	$3,96($fp)
	lw	$2,36($fp)
	sll	$2,$2,2
	addu	$2,$2,$3
	addu	$2,$2,56
	lw	$2,0($2)
	sw	$2,0($4)
	lw	$2,36($fp)
	addu	$2,$2,1
	sw	$2,36($fp)
	b	$L6
$L7:
	lw	$2,96($fp)
	lw	$25,0($2)
	lw	$2,96($fp)
	lw	$3,96($fp)
	lw	$6,96($fp)
	lw	$7,96($fp)
	lw	$4,56($2)
	lw	$5,60($3)
	lw	$6,64($6)
	lw	$7,68($7)
	jal	$31,$25
	sw	$2,40($fp)
#ifdef _MIPSEB
	sw	$3,52($fp)
#else
	sw	$3,48($fp)
#endif
	sra	$2,$3,31
#ifdef _MIPSEB
	sw	$2,48($fp)
#else
	sw	$2,52($fp)
#endif
	s.s	$f0,56($fp)
	s.d	$f0,64($fp)
	lw	$2,96($fp)
	sw	$2,76($fp)
	lw	$3,76($fp)
	lw	$2,12($3)
	sltu	$2,$2,17
	beq	$2,$0,$L10
	lw	$3,76($fp)
	lw	$2,12($3)
	sll	$3,$2,2
	la	$2,$L48
	addu	$2,$3,$2
	lw	$2,0($2)
	.cpadd	$2
	j	$2
	.rdata
	.align	2
$L48:
	.gpword	$L13
	.gpword	$L10
	.gpword	$L14
	.gpword	$L15
	.gpword	$L16
	.gpword	$L17
	.gpword	$L18
	.gpword	$L19
	.gpword	$L20
	.gpword	$L21
	.gpword	$L22
	.gpword	$L24
	.gpword	$L24
	.gpword	$L25
	.gpword	$L26
	.gpword	$L27
	.gpword	$L28
	.text
$L13:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	b	$L10
$L14:
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lbu	$2,43($fp)
#else
	lbu	$2,40($fp)
#endif
	sb	$2,0($3)
	b	$L10
$L15:
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lbu	$2,43($fp)
#else
	lbu	$2,40($fp)
#endif
	sb	$2,0($3)
	b	$L10
$L16:
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lbu	$2,43($fp)
#else
	lbu	$2,40($fp)
#endif
	sb	$2,0($3)
	b	$L10
$L17:
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lhu	$2,42($fp)
#else
	lhu	$2,40($fp)
#endif
	sh	$2,0($3)
	b	$L10
$L18:
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lhu	$2,42($fp)
#else
	lhu	$2,40($fp)
#endif
	sh	$2,0($3)
	b	$L10
$L19:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	b	$L10
$L20:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	b	$L10
$L21:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	b	$L10
$L22:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	b	$L10
$L24:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	lw	$2,96($fp)
	lw	$2,8($2)
	addu	$3,$2,4
#ifdef _MIPSEB
	lw	$2,52($fp)
#else
	lw	$2,48($fp)
#endif
	sw	$2,0($3)
	b	$L10
$L25:
	lw	$2,96($fp)
	lw	$2,8($2)
	l.s	$f0,56($fp)
	s.s	$f0,0($2)
	b	$L10
$L26:
	lw	$2,96($fp)
	lw	$2,8($2)
	l.d	$f0,64($fp)
	s.d	$f0,0($2)
	b	$L10
$L27:
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
	b	$L10
$L28:
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x1
	beq	$2,$0,$L29
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,1			# 0x1
	bne	$3,$2,$L30
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	lbu	$2,0($2)
	sb	$2,0($3)
	b	$L10
$L30:
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,2			# 0x2
	bne	$3,$2,$L32
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	lhu	$2,0($2)
	sh	$2,0($3)
	b	$L10
$L32:
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,4			# 0x4
	bne	$3,$2,$L34
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	lw	$2,0($2)
	sw	$2,0($3)
	b	$L10
$L34:
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,8			# 0x8
	bne	$3,$2,$L36
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	lw	$2,0($2)
	sw	$2,0($3)
	lw	$2,96($fp)
	lw	$2,8($2)
	addu	$3,$2,4
	lw	$2,40($fp)
	addu	$2,$2,4
	lw	$2,0($2)
	sw	$2,0($3)
	b	$L10
$L36:
	lw	$2,96($fp)
	lw	$2,16($2)
	addu	$2,$2,3
	srl	$2,$2,2
	sw	$2,72($fp)
$L38:
	lw	$2,72($fp)
	addu	$2,$2,-1
	sw	$2,72($fp)
	bgez	$2,$L40
	b	$L10
$L40:
	lw	$4,96($fp)
	lw	$2,72($fp)
	sll	$3,$2,2
	lw	$2,8($4)
	addu	$4,$3,$2
	lw	$2,72($fp)
	sll	$3,$2,2
	lw	$2,40($fp)
	addu	$2,$3,$2
	lw	$2,0($2)
	sw	$2,0($4)
	b	$L38
$L29:
	lw	$2,96($fp)
	lw	$2,4($2)
	andi	$2,$2,0x2
	beq	$2,$0,$L10
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,1			# 0x1
	bne	$3,$2,$L43
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lbu	$2,43($fp)
#else
	lbu	$2,40($fp)
#endif
	sb	$2,0($3)
	b	$L10
$L43:
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,2			# 0x2
	bne	$3,$2,$L45
	lw	$2,96($fp)
	lw	$3,8($2)
#ifdef _MIPSEB
	lhu	$2,42($fp)
#else
	lhu	$2,40($fp)
#endif
	sh	$2,0($3)
	b	$L10
$L45:
	lw	$2,96($fp)
	lw	$3,16($2)
	li	$2,4			# 0x4
	bne	$3,$2,$L10
	lw	$2,96($fp)
	lw	$3,8($2)
	lw	$2,40($fp)
	sw	$2,0($3)
$L10:
	move	$2,$0
	move	$sp,$fp
	lw	$31,88($sp)
	lw	$fp,84($sp)
	addu	$sp,$sp,96
	j	$31
	.end	__builtin_avcall
	.ident	"GCC: (GNU) 3.3.5 (Debian 1:3.3.5-8)"
