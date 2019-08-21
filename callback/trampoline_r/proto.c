/* Sample prototype for a trampoline. */

/*
 * Copyright 1995-2019 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define function  (int (*) ()) 0xbabebec0
#define data      (void*)      0x73554711

#ifdef __i386__
register void* env __asm__("%ecx");
#endif
#ifdef __m68k__
register void* env __asm__("a0");
#endif
#if defined(__mips__) || defined(__mipsn32__) || defined(__mips64__)
register void* env __asm__("$2");
#endif
#ifdef __sparc__
register void* env __asm__("%g2");
#endif
#ifdef __alpha__
register void* env __asm__("$1");
#endif
#ifdef __hppa__
register void* env __asm__("%r29");
#endif
#ifdef __arm__
register void* env __asm__("r12");
#endif
#ifdef __powerpc__
register void* env __asm__("r11");
#endif
#ifdef __x86_64_x32__
register void* env __asm__("r10");
#endif
#ifdef __s390__
register void* env __asm__("r0");
#endif
#ifdef __riscv32__
register void* env __asm__("t2");
#endif

int tramp ()
{ env = data;
  return (*function)();
}

int jump ()
{ goto *function; }

