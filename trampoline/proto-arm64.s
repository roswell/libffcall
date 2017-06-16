	.cpu generic+fp+simd
	.file	"proto64.c"
	.text
	.align	2
	.p2align 3,,7
	.global	tramp
	.type	tramp, %function
tramp:
	mov	x1, 34661
	mov	x2, 8533
	movk	x1, 0x1357, lsl 16
	mov	x0, 65451
	movk	x1, 0x5678, lsl 32
	movk	x2, 0x4362, lsl 16
	movk	x1, 0x1234, lsl 48
	movk	x0, 0xdea0, lsl 16
	movk	x2, 0x4711, lsl 32
	movk	x0, 0xbec0, lsl 32
	movk	x2, 0x7355, lsl 48
	movk	x0, 0xbabe, lsl 48
	str	x2, [x1]
	br	x0
	.size	tramp, .-tramp
	.align	2
	.p2align 3,,7
	.global	jump
	.type	jump, %function
jump:
	mov	x0, 65451
	movk	x0, 0xdea0, lsl 16
	movk	x0, 0xbec0, lsl 32
	movk	x0, 0xbabe, lsl 48
	br	x0
	.size	jump, .-jump
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",%progbits
