@ Trampoline for arm CPU

@ Copyright 1995-1997, 2016 Bruno Haible, <bruno@clisp.org>
@
@ This is free software distributed under the GNU General Public Licence
@ described in the file COPYING. Contact the author if you don't have this
@ or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
@ on this software.

@ Available registers: ip.

rfp	.req	r9
sl	.req	r10
fp	.req	r11
ip	.req	r12
sp	.req	r13
lr	.req	r14
pc	.req	r15
.text
	.align	0
	.global	_tramp
_tramp:
	@ Immediate constants are a problem. I take the indirect load approach
	@ because I don't want 4 instructions for each constant.
	add	ip,pc,#8
	ldr	pc,[pc]

	.align	0
	.global	_data
_data:
	.word	0x73554711

	.align	0
	.global	_function
_function:
	.word	0xbabebec0

	.align	0
	.global	_trampelf
_trampelf:
	@ Immediate constants are a problem. I take the indirect load approach
	@ because I don't want 4 instructions for each constant.
	add	ip,pc,#16
	sub	sp,sp,#8
	str	ip,[sp]
	ldr	pc,[pc]

	.align	0
	.global	_data2
_data2:
	.word	0x73554711

	.align	0
	.global	_function2
_function2:
	.word	0xbabebec0
