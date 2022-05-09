	.file	"proto64.c"
	.text
	.align	2
	.globl	tramp
	.type	tramp, @function
tramp:
.LFB0 = .
	.cfi_startproc
	lu12i.w	$r13,324501504>>12			# 0x13578000
	lu12i.w	$r14,1130504192>>12			# 0x43622000
	ori	$r13,$r13,1893
	ori	$r14,$r14,341
	lu12i.w	$r12,-559878144>>12			# 0xffffffffdea0f000
	lu32i.d	$r13,0x4567800000000>>32
	lu32i.d	$r14,0x5471100000000>>32
	ori	$r12,$r12,4011
	lu52i.d	$r13,$r13,0x1230000000000000>>52
	lu52i.d	$r14,$r14,0x7350000000000000>>52
	lu32i.d	$r12,0xfffebec000000000>>32
	stptr.d	$r14,$r13,0
	lu52i.d	$r12,$r12,0xbab0000000000000>>52
	jr	$r12
	.cfi_endproc
.LFE0:
	.size	tramp, .-tramp
	.section	.text.unlikely,"ax",@progbits
	.align	2
	.globl	jump
	.type	jump, @function
jump:
.LFB1 = .
	.cfi_startproc
	lu12i.w	$r12,-559878144>>12			# 0xffffffffdea0f000
	ori	$r12,$r12,4011
	lu32i.d	$r12,0xfffebec000000000>>32
	lu52i.d	$r12,$r12,0xbab0000000000000>>52
	jr	$r12
	.cfi_endproc
.LFE1:
	.size	jump, .-jump
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
