/* Sample prototype for a trampoline. */

/*
 * Copyright 1995-2017 Bruno Haible <bruno@clisp.org>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define function  (int (*) ()) 0xbabebec0dea0ffabL
#define data      (void*)      0x7355471143622155L

#ifdef __mips64__
register void* env __asm__("$2");
#endif
#ifdef __sparc64__
register void* env __asm__("%g5");
#endif
#ifdef __alpha__
register void* env __asm__("$1");
#endif
#ifdef __arm64__
register void* env __asm__("x18");
#endif
#ifdef __powerpc64__
register void* env __asm__("r11");
#endif
#ifdef __ia64__
register void* env __asm__("r15");
#endif
#ifdef __x86_64__
register void* env __asm__("r10");
#endif
#ifdef __s390x__
register void* env __asm__("r0");
#endif

int tramp ()
{ env = data;
  return (*function)();
}

int jump ()
{ goto *function; }

