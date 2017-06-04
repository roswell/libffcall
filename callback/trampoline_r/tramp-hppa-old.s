; Trampoline for hppa CPU

; Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.

; Available registers: %r19, %r20, %r21, %r22, %r29.

	.SPACE $PRIVATE$
	.SUBSPA $DATA$,QUAD=1,ALIGN=8,ACCESS=31
	.SUBSPA $BSS$,QUAD=1,ALIGN=8,ACCESS=31,ZERO,SORT=82
	.SPACE $TEXT$
	.SUBSPA $LIT$,QUAD=0,ALIGN=8,ACCESS=44
	.SUBSPA $CODE$,QUAD=0,ALIGN=8,ACCESS=44,CODE_ONLY

	.SPACE $TEXT$
	.SUBSPA $CODE$

	.align 4
	.EXPORT tramp
tramp
	.PROC
	.CALLINFO
	.ENTRY
; Move <data> into <variable>
	ldil L'0x73554711,%r29
	ldo R'0x73554711(%r29),%r29
; Get <function>
	ldil L'0xbabebec0,%r21
	ldo R'0xbabebec0(%r21),%r21
; Jump to %r21, just like the gcc-2.6.3 trampoline does it:
	bb,>=,n %r21,30,tramp2	; check bit 1 of %r21
	depi 0,31,2,%r21	; if set, clear bits 1..0
	ldw 4(0,%r21),%r19	; ... dereference the function struct
	ldw 0(0,%r21),%r21	; ... to get the actual code address
tramp2
	ldsid (0,%r21),%r1
	mtsp %r1,%sr0		; set segment register
	be,n 0(%sr0,%r21)	; now do an inter-module jump
	nop
	.EXIT
	.PROCEND
