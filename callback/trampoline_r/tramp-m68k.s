| Trampoline for m68k CPU

| Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
|
| This program is free software: you can redistribute it and/or modify
| it under the terms of the GNU General Public License as published by
| the Free Software Foundation; either version 2 of the License, or
| (at your option) any later version.
|
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program.  If not, see <https://www.gnu.org/licenses/>.

| Available registers: d0, d1, a0, a1.

.globl tramp
tramp:
	movel #0x73554711,%a0
	jmp 0xbabebec0
	nop
