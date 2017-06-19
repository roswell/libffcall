	.file	"proto64.c"
.text
	.align	8
.globl tramp
	.type	tramp, @function
tramp:
.LFB0:
	.cfi_startproc
	larl	%r5,.L3
	lg	%r2,.L4-.L3(%r5)
	lg	%r1,.L5-.L3(%r5)
	lg	%r3,.L6-.L3(%r5)
	stg	%r3,0(%r2)
	br	%r1
	.section	.rodata
	.align	8
.L3:
.L6:
	.quad	8310626826852639061
.L5:
	.quad	0xbabebec0dea0ffab
.L4:
	.quad	1311768465192224613
	.align	2
	.previous
	.cfi_endproc
.LFE0:
	.size	tramp, .-tramp
	.align	8
.globl jump
	.type	jump, @function
jump:
.LFB1:
	.cfi_startproc
	larl	%r5,.L9
	lg	%r1,.L10-.L9(%r5)
	br	%r1
	.section	.rodata
	.align	8
.L9:
.L10:
	.quad	0xbabebec0dea0ffab
	.align	2
	.previous
	.cfi_endproc
.LFE1:
	.size	jump, .-jump
	.ident	"GCC: (GNU) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
