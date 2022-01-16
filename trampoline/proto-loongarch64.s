	.file	"proto64.c"
	.text
	.align	2
	.globl	tramp
	.type	tramp, @function
tramp:
	lu12i.w	$r12,324501504>>12			# 0x13578000
	ori	$r12,$r12,1893
	lu32i.d	$r12,0x4567800000000>>32
	lu52i.d	$r12,$r12,0x1230000000000000>>52
	addi.w	$r15,$r0,33			# 0x21
	st.b	$r15,$r12,1
	addi.w	$r15,$r0,98			# 0x62
	lu12i.w	$r13,-559878144>>12			# 0xffffffffdea0f000
	st.b	$r15,$r12,2
	addi.w	$r15,$r0,67			# 0x43
	addi.w	$r14,$r0,85			# 0x55
	ori	$r13,$r13,4011
	st.b	$r15,$r12,3
	addi.w	$r15,$r0,17			# 0x11
	lu32i.d	$r13,0xfffebec000000000>>32
	st.b	$r14,$r12,0
	st.b	$r15,$r12,4
	st.b	$r14,$r12,6
	addi.w	$r15,$r0,71			# 0x47
	addi.w	$r14,$r0,115			# 0x73
	st.b	$r15,$r12,5
	st.b	$r14,$r12,7
	lu52i.d	$r13,$r13,0xbab0000000000000>>52
	jr	$r13
	.size	tramp, .-tramp
	.section	.text.unlikely,"ax",@progbits
	.align	2
	.globl	jump
	.type	jump, @function
jump:
	lu12i.w	$r12,-559878144>>12			# 0xffffffffdea0f000
	ori	$r12,$r12,4011
	lu32i.d	$r12,0xfffebec000000000>>32
	lu52i.d	$r12,$r12,0xbab0000000000000>>52
	jr	$r12
	.size	jump, .-jump
	.ident	"GCC: (GNU) 12.0.0 20211224 (experimental)"
	.section	.note.GNU-stack,"",@progbits
