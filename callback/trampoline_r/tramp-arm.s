@ Trampoline for arm CPU

@ Copyright 1995-1997, 2016-2017 Bruno Haible, <bruno@clisp.org>
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

@ The normal trampoline with a jump to <function> cannot be used on ARM:
@ It would require that the __vacall_r function uses the r12 value that
@ it gets passed in a register. But I cannot produce such a __vacall_r
@ function with GCC: With -fno-omit-frame-pointer, the function prologue
@ kills the value of r12. With -fomit-frame-pointer, it does not have
@ APCS compliant stack frames, which can be problematic for unwinding
@ (throw in C++), call graph profilers, or debuggers.

	.align	0
	.global	_tramp
_tramp:
	@ Immediate constants are a problem. I take the indirect load approach
	@ because I don't want 4 instructions for each constant.
	ldr	ip,[pc,#0]	@ Put <data> in register r12
	ldr	pc,[pc,#0]	@ Jump to <function>

	.align	0
	.global	_data
_data:
	.word	0x73554711

	.align	0
	.global	_function
_function:
	.word	0xbabebec0

@ The trampoline with a call to <function> works with a __vacall_r function
@ that was compiled with GCC with -fno-omit-frame-pointer. But fprintf calls
@ from within __vacall_r somehow produce wrong output for 'float' and 'double'
@ arguments.

	.align	0
	.global	_trampcallomit
_trampcallomit:
	@ Hand-made prologue.
	@ The extra parameter declarations in vacall-arm.c must be:
	@   __vaword saved_lr, env_t* env,
	@ ATTENTION! sp must remain 8-bytes-aligned, otherwise fprintf() prints
	@ 'double' values incorrectly.
	sub	sp,sp,#8

	ldr	ip,[pc,#16]	@ Get <data>
	str	lr,[sp,#0]	@ Put return address on stack
	str	ip,[sp,#4]	@ Put <data> on stack
	mov	lr,pc		@ Prepare call (put return address in lr)
	ldr	pc,[pc,#4]	@ Call <function> with the same args in registers

	@ Hand-made epilogue.
	ldr	pc,[sp],#8	@ Return to return address and cleanup stack

	.align	0
	.global	_data2
_data2:
	.word	0x73554711

	.align	0
	.global	_function2
_function2:
	.word	0xbabebec0

@ The trampoline with a call to <function> and a standard prologue and epilogue,
@ together with a __vacall_r function that was compiled with GCC with
@ -fno-omit-frame-pointer, works.

	.align	0
	.global	_trampcallwithframe
_trampcallwithframe:
	@ Standard prologue, combined with pushing the first 4 general-purpose
	@ argument words.
	@ The extra parameter declarations in vacall-arm.c must be:
	@   env_t* env, __vaword filler, __vaword saved_fp, __vaword saved_sp, __vaword saved_lr, __vaword saved_pc,
	mov	ip,sp
	stmfd	sp!,{r0,r1,r2,r3}
	stmfd	sp!,{fp,ip,lr,pc}
	sub	fp,ip,#20

	@ Make room on the stack.
	@ ATTENTION! sp must remain 8-bytes-aligned, otherwise fprintf() prints
	@ 'double' values incorrectly.
	sub	sp,sp,#8

	ldr	ip,[pc,#12]	@ Get <data>
	str	ip,[sp,#0]	@ Put <data> on stack
	@ Stack contents at this point:
	@   env, filler, saved_fp, saved_sp, saved_lr, saved_pc, r0, r1, r2, r3, stack-allocated general-purpose args
	@ and fp points here:                         ^
	mov	lr,pc		@ Prepare call (put return address in lr)
	ldr	pc,[pc,#4]	@ Call <function> with the same args in registers

	@ Standard epilogue.
	ldmea	fp,{fp,sp,pc}	@ Restore fp and sp, and return to return address.

	.align	0
	.global	_data3
_data3:
	.word	0x73554711

	.align	0
	.global	_function3
_function3:
	.word	0xbabebec0
