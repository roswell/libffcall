	.LEVEL 2.0w
	.section	.rodata
	.align 8
.LC0:
	.dword	8310626826852639061
	.align 8
.LC1:
	.dword	-4990341601501839445
	.text
	.align 8
.globl tramp
		.type		 tramp,@function
tramp:
	.PROC
	.CALLINFO FRAME=128,CALLS,SAVE_RP,ENTRY_GR=3
	.ENTRY
	addil LT'.LC0,%r27
	std %r2,-16(%r30)
	copy %r1,%r19
	ldo 128(%r30),%r30
	addil LT'.LC1,%r27
	ldd RT'.LC0(%r19),%r19
	ldd RT'.LC1(%r1),%r20
	ldo -16(%r30),%r29
	std %r4,-112(%r30)
	copy %r27,%r4
	ldd 0(%r19),%r31
	ldd 0(%r20),%r28
	ldd 16(%r28),%r2
	ldd 24(%r28),%r27
	bve,l (%r2),%r2
	nop
	ldd -144(%r30),%r2
	copy %r4,%r27
	ldd -112(%r30),%r4
	bve (%r2)
	ldo -128(%r30),%r30
	.EXIT
	.PROCEND
.Lfe1:
	.size	tramp,.Lfe1-tramp
	.section	.rodata
	.align 8
.LC2:
	.dword	-4990341601501839445
	.text
	.align 8
.globl jump
		.type		 jump,@function
jump:
	.PROC
	.CALLINFO FRAME=128,NO_CALLS
	.ENTRY
	addil LT'.LC2,%r27
	ldd RT'.LC2(%r1),%r1
	ldd 0(%r1),%r19
	bv %r0(%r19)
	ldo 128(%r30),%r30
	.EXIT
	.PROCEND
.Lfe2:
	.size	jump,.Lfe2-jump
	.ident	"GCC: (GNU) 3.1"
