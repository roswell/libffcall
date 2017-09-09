; Trampoline for hppa64 CPU

; Copyright 2017 Bruno Haible <bruno@clisp.org>
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

; Available registers: %r1, %r27, %r31.
; %r27 has a fixed meaning at function calls: pic_base (a.k.a. gp or dp).
; %r31 has a fixed meaning as millicode return pointer (mrp).

	.LEVEL 2.0w
	.text
	.align 8
	.globl tramp
	.type tramp,@function
tramp:
	.PROC
	.CALLINFO FRAME=0,NO_CALLS
	.ENTRY
; Move our own address (program counter / instruction address) to r27.
	mfia %r27
; Move <data> into <variable>.
	ldd 40(%r27),%r31		; get <variable>
	ldd 48(%r27),%r1		; get <data>
	std %r1,0(%r31)			; store <data> in <variable>
; Jump to <function>.
	ldd 56(%r27),%r27		; get <function>
	ldd 16(%r27),%r1
	ldd 24(%r27),%r27
	bve (%r1)			; jump to <function>
	 nop
;	.align 8
;	.dword <variable>
;	.dword <data>
;	.dword <function>
	.EXIT
	.PROCEND
.Lfe1:
	.size	tramp,.Lfe1-tramp
