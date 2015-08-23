	.file	"avcall-powerpc64le.c"
	.abiversion 2
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.globl __builtin_avcall
	.type	__builtin_avcall, @function
__builtin_avcall:
0:	addis 2,12,.TOC.-0b@ha
	addi 2,2,.TOC.-0b@l
	.localentry	__builtin_avcall,.-__builtin_avcall
	mflr 0
	addi 9,3,48
	std 31,-8(1)
	mr 31,3
	std 0,16(1)
	stdu 1,-2192(1)
	ld 10,40(3)
	subf 9,9,10
	sradi 9,9,3
	extsw 9,9
	cmpwi 7,9,8
	ble- 7,.L5
	sldi 8,9,3
	addi 7,1,24
	addi 10,3,104
	addi 9,1,88
	add 7,7,8
	.p2align 4,,15
.L6:
	ldu 8,8(10)
	stdu 8,8(9)
	cmpld 7,9,7
	bne+ 7,.L6
.L5:
	ld 10,2096(31)
	addi 9,31,2104
	subf 9,9,10
	sradi 9,9,3
	extsw. 10,9
	beq 0,.L3
	cmpwi 7,10,1
	beq 7,.L7
	cmpwi 7,10,2
	beq 7,.L8
	cmpwi 7,10,3
	beq 7,.L9
	cmpwi 7,10,4
	beq 7,.L10
	cmpwi 7,10,5
	beq 7,.L11
	cmpwi 7,10,6
	beq 7,.L12
	cmpwi 7,10,7
	beq 7,.L13
	cmpwi 7,10,8
	beq 7,.L14
	cmpwi 7,10,9
	beq 7,.L15
	cmpwi 7,10,10
	beq 7,.L16
	cmpwi 7,10,11
	beq 7,.L17
	cmpwi 7,10,12
	beq 7,.L18
.L19:
	lfd 13,2200(31)
.L18:
	lfd 12,2192(31)
.L17:
	lfd 11,2184(31)
.L16:
	lfd 10,2176(31)
.L15:
	lfd 9,2168(31)
.L14:
	lfd 8,2160(31)
.L13:
	lfd 7,2152(31)
.L12:
	lfd 6,2144(31)
.L11:
	lfd 5,2136(31)
.L10:
	lfd 4,2128(31)
.L9:
	lfd 3,2120(31)
.L8:
	lfd 2,2112(31)
.L7:
	lfd 1,2104(31)
.L3:
	ld 11,0(31)
	ld 9,96(31)
	ld 3,48(31)
	ld 4,56(31)
	ld 5,64(31)
	ld 6,72(31)
	ld 7,80(31)
	ld 8,88(31)
	ld 10,104(31)
	std 2,24(1)
	mtctr 11
	mr 12,11
	bctrl
	ld 2,24(1)
	lwz 9,24(31)
	cmplwi 7,9,1
	beq 7,.L21
	cmpdi 7,9,0
	beq 7,.L62
	cmplwi 7,9,2
	beq 7,.L59
	cmplwi 7,9,3
	beq 7,.L59
	cmplwi 7,9,4
	beq 7,.L59
	cmplwi 7,9,5
	beq 7,.L60
	cmplwi 7,9,6
	beq 7,.L60
	cmplwi 7,9,7
	beq 7,.L61
	cmplwi 7,9,8
	beq 7,.L61
	cmplwi 7,9,9
	beq 7,.L62
	cmplwi 7,9,10
	beq 7,.L62
	cmplwi 7,9,11
	beq 7,.L62
	cmplwi 7,9,12
	beq 7,.L62
	cmplwi 7,9,13
	beq 7,.L64
	cmplwi 7,9,14
	beq 7,.L65
	cmplwi 7,9,15
	beq 7,.L62
	cmplwi 7,9,16
	bne 7,.L21
	lwz 9,8(31)
	rldicl. 10,9,55,63
	beq 0,.L21
	ld 9,32(31)
	addi 9,9,-1
	cmpldi 7,9,15
	bgt 7,.L21
	ld 9,16(31)
	stb 3,0(9)
	ld 9,32(31)
	cmpldi 7,9,1
	ble 7,.L21
	ld 9,16(31)
	sradi 10,3,8
	stb 10,1(9)
	ld 9,32(31)
	cmpldi 7,9,2
	ble 7,.L21
	ld 9,16(31)
	sradi 10,3,16
	stb 10,2(9)
	ld 9,32(31)
	cmpldi 7,9,3
	ble 7,.L21
	ld 9,16(31)
	sradi 10,3,24
	stb 10,3(9)
	ld 9,32(31)
	cmpldi 7,9,4
	ble 7,.L21
	ld 9,16(31)
	sradi 10,3,32
	stb 10,4(9)
	ld 9,32(31)
	cmpldi 7,9,5
	ble 7,.L21
	ld 9,16(31)
	sradi 10,3,40
	stb 10,5(9)
	ld 9,32(31)
	cmpldi 7,9,6
	ble 7,.L21
	ld 9,16(31)
	sradi 10,3,48
	stb 10,6(9)
	ld 9,32(31)
	cmpldi 7,9,7
	ble 7,.L21
	ld 9,16(31)
	sradi 3,3,56
	stb 3,7(9)
	ld 9,32(31)
	cmpldi 7,9,8
	ble 7,.L21
	ld 9,16(31)
	stb 4,8(9)
	ld 9,32(31)
	cmpldi 7,9,9
	ble 7,.L21
	ld 9,16(31)
	sradi 10,4,8
	stb 10,9(9)
	ld 9,32(31)
	cmpldi 7,9,10
	ble 7,.L21
	ld 9,16(31)
	sradi 10,4,16
	stb 10,10(9)
	ld 9,32(31)
	cmpldi 7,9,11
	ble 7,.L21
	ld 9,16(31)
	sradi 10,4,24
	stb 10,11(9)
	ld 9,32(31)
	cmpldi 7,9,12
	ble 7,.L21
	ld 9,16(31)
	sradi 10,4,32
	stb 10,12(9)
	ld 9,32(31)
	cmpldi 7,9,13
	ble 7,.L21
	ld 9,16(31)
	sradi 10,4,40
	stb 10,13(9)
	ld 9,32(31)
	cmpldi 7,9,14
	ble 7,.L21
	ld 9,16(31)
	sradi 10,4,48
	stb 10,14(9)
	ld 9,32(31)
	cmpldi 7,9,15
	ble 7,.L21
	ld 9,16(31)
	sradi 4,4,56
	stb 4,15(9)
.L21:
	addi 1,1,2192
	li 3,0
	ld 0,16(1)
	ld 31,-8(1)
	mtlr 0
	blr
.L62:
	ld 9,16(31)
	addi 1,1,2192
	std 3,0(9)
	li 3,0
	ld 0,16(1)
	ld 31,-8(1)
	mtlr 0
	blr
.L59:
	ld 9,16(31)
	addi 1,1,2192
	stb 3,0(9)
	li 3,0
	ld 0,16(1)
	ld 31,-8(1)
	mtlr 0
	blr
.L60:
	ld 9,16(31)
	sth 3,0(9)
	b .L21
.L61:
	ld 9,16(31)
	stw 3,0(9)
	b .L21
.L65:
	ld 9,16(31)
	stfd 1,0(9)
	b .L21
.L64:
	ld 9,16(31)
	stfs 1,0(9)
	b .L21
	.long 0
	.byte 0,0,0,1,128,1,0,0
	.size	__builtin_avcall,.-__builtin_avcall
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-9)"
	.section	.note.GNU-stack,"",@progbits
