	.file	"proto.c"
.text
	.align	4
.globl tramp
	.type	tramp,@function
tramp:
	stm	%r13,%r15,52(%r15)
	bras	%r13,.LTN0_0
.LT0_0:
.LC0:
	.long	305419896
.LC1:
	.long	1934968593
.LC2:
	.long	-1161904448
.LTN0_0:
	lr	%r14,%r15
	l	%r1,.LC0-.LT0_0(%r13)
	ahi	%r15,-96
	l	%r2,.LC2-.LT0_0(%r13)
	mvc	0(4,%r1),.LC1-.LT0_0(%r13)
	st	%r14,0(%r15)
	basr	%r14,%r2
	l	%r4,152(%r15)
	lm	%r13,%r15,148(%r15)
	br	%r4
.Lfe1:
	.size	tramp,.Lfe1-tramp
	.align	4
.globl jump
	.type	jump,@function
jump:
	st	%r13,52(%r15)
	bras	%r13,.LTN1_0
.LT1_0:
.LC3:
	.long	-1161904448
.LTN1_0:
	l	%r1,.LC3-.LT1_0(%r13)
	br	%r1
.Lfe2:
	.size	jump,.Lfe2-jump
	.ident	"GCC: (GNU) 3.1"
