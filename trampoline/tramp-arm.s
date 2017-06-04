@ Trampoline for arm CPU

@ Copyright 1995 Bruno Haible <bruno@clisp.org>
@
@ This program is free software: you can redistribute it and/or modify
@ it under the terms of the GNU General Public License as published by
@ the Free Software Foundation; either version 2 of the License, or
@ (at your option) any later version.
@
@ This program is distributed in the hope that it will be useful,
@ but WITHOUT ANY WARRANTY; without even the implied warranty of
@ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
@ GNU General Public License for more details.
@
@ You should have received a copy of the GNU General Public License
@ along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
	stmfd	sp!,{r0}
	ldr	r0,[pc,#12]
	ldr	ip,[pc,#12]
	str	r0,[ip]
	ldmfd	sp!,{r0}
	ldr	pc,[pc,#4]

	.global	_data
	.align	0
_data:
	.word	0x73554711

	.global	_variable
	.align	0
_variable:
	.word	0x12345678

	.global	_function
	.align	0
_function:
	.word	0xbabebec0
