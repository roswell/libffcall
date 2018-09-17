! Trampoline for sparc64 CPU

! Copyright 1999 Bruno Haible <bruno@clisp.org>
!
! This program is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation; either version 2 of the License, or
! (at your option) any later version.
!
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
!
! You should have received a copy of the GNU General Public License
! along with this program.  If not, see <https://www.gnu.org/licenses/>.

! Available registers: %g1, %g2, %g3.

	.global _tramp
	.proc	04
_tramp:
	call _getpc,0		! Put the address of _tramp into %o7
	 mov %o7,%g1		! But save the previous %o7 in %g1
_getpc:
	ldx [%o7+(_variable-_tramp)],%g2
	ldx [%o7+(_data-_tramp)],%g3
	stx %g3,[%g2]
	ldx [%o7+(_function-_tramp)],%g2
	jmp %g2
	 mov %g1,%o7
_variable:
	.long 0x12345678
	.long 0x13578765
_data:
	.long 0x73554711
	.long 0x43622155
_function:
	.long 0xbabebec0
	.long 0xdea0ffab
