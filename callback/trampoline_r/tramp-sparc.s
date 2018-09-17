! Trampoline for sparc CPU

! Copyright 1995-1997 Bruno Haible <bruno@clisp.org>
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
	sethi %hi(0x73554711),%g2
	sethi %hi(0xbabebec0),%g1
	jmp %g1+%lo(0xbabebec0)
	or %g2,%lo(0x73554711),%g2
