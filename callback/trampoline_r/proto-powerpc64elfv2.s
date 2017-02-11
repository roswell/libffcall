	.file	"proto64.c"
	.machine power8
	.abiversion 2
	.section	".toc","aw"
	.section	".text"
	.align 2
	.p2align 4,,15
	.globl tramp
	.type	tramp, @function
tramp:
0:	addis 2,12,.TOC.-0b@ha
	addi 2,2,.TOC.-0b@l
	.localentry	tramp,.-tramp
	mflr 0
	lis 12,0xbabe
	lis 9,0x7355
	ori 12,12,0xbec0
	ori 9,9,0x4711
	sldi 12,12,32
	sldi 9,9,32
	oris 12,12,0xdea0
	oris 9,9,0x4362
	ori 12,12,0xffab
	mtctr 12
	std 0,16(1)
	stdu 1,-96(1)
	ori 11,9,0x2155
	std 2,24(1)
	bctrl
	ld 2,24(1)
	addi 1,1,96
	ld 0,16(1)
	mtlr 0
	blr
	.long 0
	.byte 0,0,0,1,128,0,0,0
	.size	tramp,.-tramp
	.align 2
	.p2align 4,,15
	.globl jump
	.type	jump, @function
jump:
	lis 9,0xbabe
	ori 9,9,0xbec0
	sldi 9,9,32
	oris 9,9,0xdea0
	ori 9,9,0xffab
	mtctr 9
	bctr
	.long 0
	.byte 0,0,0,0,0,0,0,0
	.size	jump,.-jump
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
