	.file	"avcall-ia64.c"
	.pred.safe_across_calls p1-p5,p16-p63
	.text
	.align 16
	.global __builtin_avcall#
	.proc __builtin_avcall#
__builtin_avcall:
	.prologue 12, 34
	.save ar.pfs, r35
	alloc r35 = ar.pfs, 1, 5, 8, 0
	.save ar.lc, r37
	mov r37 = ar.lc
	mov r36 = r1
	.save rp, r34
	mov r34 = b0
	.body
	adds r18 = -2032, r12
	adds r14 = 48, r32
	adds r15 = 56, r32
	;;
	ld8 r14 = [r14]
	;;
	sub r14 = r14, r15
	;;
	shr.u r17 = r14, 3
	adds r14 = 40, r32
	adds r15 = 120, r32
	;;
	ld8 r14 = [r14]
	;;
	sub r14 = r14, r15
	;;
	extr r14 = r14, 3, 32
	;;
	cmp.ge p6, p7 = 8, r14
	(p6) br.cond.dpnt .L2
	adds r16 = 184, r32
	mov r15 = r18
	sub r14 = 8, r14
	;;
	andcm r14 = -1, r14
	;;
	mov ar.lc = r14
.L4:
	ld8 r14 = [r16], 8
	;;
	st8 [r15] = r14, 8
	br.cloop.sptk.few .L4
.L2:
	adds r14 = 24, r32
	;;
	ld4 r14 = [r14]
	;;
	cmp4.ne p6, p7 = 16, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r8 = [r14]
	cmp4.ge p6, p7 = 0, r17
	(p6) br.cond.dpnt .L7
	adds r14 = 56, r32
	;;
	ldfd f8 = [r14]
	cmp4.ge p6, p7 = 1, r17
	(p6) br.cond.dpnt .L7
	adds r14 = 64, r32
	;;
	ldfd f9 = [r14]
	cmp4.ge p6, p7 = 2, r17
	(p6) br.cond.dptk .L7
	adds r14 = 72, r32
	;;
	ldfd f10 = [r14]
	cmp4.ge p6, p7 = 3, r17
	(p6) br.cond.dptk .L7
	adds r14 = 80, r32
	;;
	ldfd f11 = [r14]
	cmp4.ge p6, p7 = 4, r17
	(p6) br.cond.dptk .L7
	adds r14 = 88, r32
	;;
	ldfd f12 = [r14]
	cmp4.ge p6, p7 = 5, r17
	(p6) br.cond.dptk .L7
	adds r14 = 96, r32
	;;
	ldfd f13 = [r14]
	cmp4.ge p6, p7 = 6, r17
	(p6) br.cond.dptk .L7
	adds r14 = 104, r32
	;;
	ldfd f14 = [r14]
	cmp4.ge p6, p7 = 7, r17
	;;
	(p7) adds r14 = 112, r32
	;;
	(p7) ldfd f15 = [r14]
.L7:
	adds r14 = 24, r32
	;;
	ld4 r14 = [r14]
	;;
	cmp4.ne p6, p7 = 13, r14
	(p6) br.cond.dptk .L16
	adds r14 = 16, r32
	;;
	ld8 r33 = [r14]
	adds r14 = 120, r32
	adds r15 = 128, r32
	adds r16 = 136, r32
	adds r17 = 144, r32
	adds r18 = 152, r32
	adds r19 = 160, r32
	adds r20 = 168, r32
	adds r21 = 176, r32
	ld8 r22 = [r32]
	;;
	ld8 r38 = [r14]
	ld8 r39 = [r15]
	ld8 r40 = [r16]
	ld8 r41 = [r17]
	ld8 r42 = [r18]
	ld8 r43 = [r19]
	ld8 r44 = [r20]
	ld8 r45 = [r21]
	ld8 r14 = [r22], 8
	;;
	mov b6 = r14
	ld8 r1 = [r22]
	br.call.sptk.many b0 = b6
	;;
	mov r1 = r36
	stfs [r33] = f8
	br .L18
	;;
.L16:
	cmp4.ne p6, p7 = 14, r14
	(p6) br.cond.dptk .L19
	adds r14 = 16, r32
	;;
	ld8 r33 = [r14]
	adds r14 = 120, r32
	adds r15 = 128, r32
	adds r16 = 136, r32
	adds r17 = 144, r32
	adds r18 = 152, r32
	adds r19 = 160, r32
	adds r20 = 168, r32
	adds r21 = 176, r32
	ld8 r22 = [r32]
	;;
	ld8 r38 = [r14]
	ld8 r39 = [r15]
	ld8 r40 = [r16]
	ld8 r41 = [r17]
	ld8 r42 = [r18]
	ld8 r43 = [r19]
	ld8 r44 = [r20]
	ld8 r45 = [r21]
	ld8 r14 = [r22], 8
	;;
	mov b6 = r14
	ld8 r1 = [r22]
	br.call.sptk.many b0 = b6
	;;
	mov r1 = r36
	stfd [r33] = f8
	br .L18
	;;
.L19:
	adds r14 = 120, r32
	adds r15 = 128, r32
	adds r16 = 136, r32
	adds r17 = 144, r32
	adds r18 = 152, r32
	adds r19 = 160, r32
	adds r20 = 168, r32
	adds r21 = 176, r32
	ld8 r22 = [r32]
	;;
	ld8 r38 = [r14]
	ld8 r39 = [r15]
	ld8 r40 = [r16]
	ld8 r41 = [r17]
	ld8 r42 = [r18]
	ld8 r43 = [r19]
	ld8 r44 = [r20]
	ld8 r45 = [r21]
	ld8 r14 = [r22], 8
	;;
	mov b6 = r14
	ld8 r1 = [r22]
	br.call.sptk.many b0 = b6
	;;
	mov r1 = r36
	mov r23 = r8
	adds r14 = 24, r32
	;;
	ld4 r14 = [r14]
	;;
	cmp4.eq p6, p7 = 1, r14
	(p6) br.cond.dpnt .L18
	;;
	cmp4.ne p6, p7 = 0, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st8 [r14] = r8
	(p7) br.cond.dptk .L18
	cmp4.ne p6, p7 = 2, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st1 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 3, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st1 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 4, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st1 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 5, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st2 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 6, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st2 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 7, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st4 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 8, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st4 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 9, r14
	;;
	cmp4.ne.and.orcm p6, p7 = 11, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st8 [r14] = r8
	(p7) br.cond.dptk .L18
	cmp4.ne p6, p7 = 10, r14
	;;
	cmp4.ne.and.orcm p6, p7 = 12, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st8 [r14] = r8
	(p7) br.cond.dptk .L18
	cmp4.ne p6, p7 = 15, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) st8 [r14] = r8
	(p7) br.cond.dpnt .L18
	cmp4.ne p6, p7 = 16, r14
	(p6) br.cond.dptk .L18
	adds r14 = 8, r32
	;;
	ld4 r14 = [r14]
	;;
	tbit.z p6, p7 = r14, 0
	(p6) br.cond.dptk .L45
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.ne p6, p7 = 1, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r15 = [r14]
	(p7) ld1 r14 = [r8]
	;;
	(p7) st1 [r15] = r14
	(p7) br.cond.dpnt .L18
	cmp.ne p6, p7 = 2, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r15 = [r14]
	(p7) ld2 r14 = [r8]
	;;
	(p7) st2 [r15] = r14
	(p7) br.cond.dpnt .L18
	cmp.ne p6, p7 = 4, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r15 = [r14]
	(p7) ld4 r14 = [r8]
	;;
	(p7) st4 [r15] = r14
	(p7) br.cond.dpnt .L18
	cmp.ne p6, p7 = 8, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r15 = [r14]
	(p7) ld8 r14 = [r8]
	;;
	(p7) st8 [r15] = r14
	(p7) br.cond.dpnt .L18
	adds r14 = 7, r14
	;;
	shr.u r25 = r14, 3
	;;
	adds r15 = -1, r25
	;;
	cmp4.gt p6, p7 = r0, r15
	(p6) br.cond.dpnt .L18
	sxt4 r14 = r15
	;;
	shladd r24 = r14, 3, r0
	;;
	add r23 = r8, r24
	adds r16 = 16, r32
	sub r14 = r25, r15
	;;
	adds r14 = -2, r14
	;;
	sub r14 = r15, r14, 1
	;;
	addp4 r14 = r14, r0
	;;
	mov ar.lc = r14
.L56:
	ld8 r14 = [r16]
	;;
	add r14 = r24, r14
	ld8 r15 = [r23], -8
	;;
	st8 [r14] = r15
	adds r24 = -8, r24
	br.cloop.sptk.few .L56
	br .L18
	;;
.L45:
	tbit.z p6, p7 = r14, 9
	(p6) br.cond.dpnt .L18
	adds r16 = 32, r32
	;;
	ld8 r15 = [r16]
	;;
	adds r14 = -1, r15
	;;
	cmp.ltu p6, p7 = 31, r14
	(p6) br.cond.dpnt .L18
	;;
	cmp.eq p6, p7 = 0, r15
	(p6) br.cond.dptk .L59
	adds r15 = 16, r32
	;;
	ld8 r14 = [r15]
	;;
	st1 [r14] = r8
	ld8 r14 = [r16]
	;;
	cmp.geu p6, p7 = 1, r14
	;;
	(p7) ld8 r14 = [r15]
	;;
	(p7) adds r14 = 1, r14
	(p7) shr r15 = r8, 8
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 2, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 2, r14
	(p7) shr r15 = r8, 16
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 3, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 3, r14
	(p7) shr r15 = r8, 24
	;;
	(p7) st1 [r14] = r15
.L59:
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 4, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 4, r14
	(p7) shr r15 = r23, 32
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 5, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 5, r14
	(p7) shr r15 = r23, 40
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 6, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 6, r14
	(p7) shr r15 = r23, 48
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 7, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 7, r14
	(p7) shr r15 = r23, 56
	;;
	(p7) st1 [r14] = r15
	adds r15 = 32, r32
	;;
	ld8 r14 = [r15]
	;;
	cmp.geu p6, p7 = 8, r14
	(p6) br.cond.dpnt .L18
	adds r16 = 16, r32
	;;
	ld8 r14 = [r16]
	;;
	adds r14 = 8, r14
	;;
	st1 [r14] = r9
	ld8 r14 = [r15]
	;;
	cmp.geu p6, p7 = 9, r14
	;;
	(p7) ld8 r14 = [r16]
	;;
	(p7) adds r14 = 9, r14
	(p7) shr r15 = r9, 8
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 10, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 10, r14
	(p7) shr r15 = r9, 16
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 11, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 11, r14
	(p7) shr r15 = r9, 24
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 12, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 12, r14
	(p7) shr r15 = r9, 32
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 13, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 13, r14
	(p7) shr r15 = r9, 40
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 14, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 14, r14
	(p7) shr r15 = r9, 48
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 15, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 15, r14
	(p7) shr r15 = r9, 56
	;;
	(p7) st1 [r14] = r15
	adds r15 = 32, r32
	;;
	ld8 r14 = [r15]
	;;
	cmp.geu p6, p7 = 16, r14
	(p6) br.cond.dpnt .L18
	adds r16 = 16, r32
	;;
	ld8 r14 = [r16]
	;;
	adds r14 = 16, r14
	;;
	st1 [r14] = r10
	ld8 r14 = [r15]
	;;
	cmp.geu p6, p7 = 17, r14
	;;
	(p7) ld8 r14 = [r16]
	;;
	(p7) adds r14 = 17, r14
	(p7) shr r15 = r10, 8
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 18, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 18, r14
	(p7) shr r15 = r10, 16
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 19, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 19, r14
	(p7) shr r15 = r10, 24
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 20, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 20, r14
	(p7) shr r15 = r10, 32
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 21, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 21, r14
	(p7) shr r15 = r10, 40
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 22, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 22, r14
	(p7) shr r15 = r10, 48
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 23, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 23, r14
	(p7) shr r15 = r10, 56
	;;
	(p7) st1 [r14] = r15
	adds r15 = 32, r32
	;;
	ld8 r14 = [r15]
	;;
	cmp.geu p6, p7 = 24, r14
	(p6) br.cond.dpnt .L18
	adds r16 = 16, r32
	;;
	ld8 r14 = [r16]
	;;
	adds r14 = 24, r14
	;;
	st1 [r14] = r11
	ld8 r14 = [r15]
	;;
	cmp.geu p6, p7 = 25, r14
	;;
	(p7) ld8 r14 = [r16]
	;;
	(p7) adds r14 = 25, r14
	(p7) shr r15 = r11, 8
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 26, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 26, r14
	(p7) shr r15 = r11, 16
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 27, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 27, r14
	(p7) shr r15 = r11, 24
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 28, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 28, r14
	(p7) shr r15 = r11, 32
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 29, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 29, r14
	(p7) shr r15 = r11, 40
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 30, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 30, r14
	(p7) shr r15 = r11, 48
	;;
	(p7) st1 [r14] = r15
	adds r14 = 32, r32
	;;
	ld8 r14 = [r14]
	;;
	cmp.geu p6, p7 = 31, r14
	;;
	(p7) adds r14 = 16, r32
	;;
	(p7) ld8 r14 = [r14]
	;;
	(p7) adds r14 = 31, r14
	(p7) shr r15 = r11, 56
	;;
	(p7) st1 [r14] = r15
.L18:
	mov r8 = r0
	mov ar.pfs = r35
	mov ar.lc = r37
	mov b0 = r34
	br.ret.sptk.many b0
	;;
	.endp __builtin_avcall#
	.ident	"GCC: (GNU) 4.1.0 (SUSE Linux)"
