/* This program tests whether the stack is executable.  */

/*
 * Copyright 2017 Bruno Haible <bruno@clisp.org>
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

#include <string.h>
#include <stdio.h>

/* Define the instruction of a no-op function returning void.  */
#if defined(__alpha)
unsigned int voidfunc[1] = { 0x6bfa8001 };
#endif
#if defined(__aarch64__)
unsigned int voidfunc[1] = { 0xd65f03c0 };
#elif defined(__arm) || defined(__arm__)
unsigned int voidfunc[1] = { 0xe1a0f00e };
#endif
#if defined(__i386) || defined(__i386__) || defined(_I386) || defined(_M_IX86) || defined(_X86_) || defined(__x86_64__) || defined(__amd64__)
unsigned char voidfunc[1] = { 0xc3 };
#endif
#if defined(__hppa) || defined(__hppa__)
unsigned int voidfunc[1] = { 0xe840c002 };
#endif
#if defined(__ia64__)
unsigned char voidfunc[16] = { 0x17, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x10, 0x80, 0x08, 0x00, 0x84, 0x00 };
#endif
#if defined(__m68k__)
unsigned short voidfunc[1] = { 0x4e75 };
#endif
#if defined(__mips) || defined(__mips__)
unsigned int voidfunc[2] = { 0x03e00008, 0x00000000 };
#endif
#if defined(_IBMR2) || defined(__powerpc) || defined(__powerpc__) || defined(__ppc) || defined(__ppc__)
unsigned int voidfunc[1] = { 0x4e800020 };
#endif
#if defined(__s390__)
unsigned char voidfunc[4] = { 0x07, 0xfe, 0x07, 0x07 };
#endif
#if defined(__sparc__)
unsigned int voidfunc[2] = { 0x81c3e008, 0x01000000 };
#endif

int
main ()
{
  unsigned int voidfunc_in_stack[4];

  /* Copy the function into the stack. */
  memcpy (voidfunc_in_stack, voidfunc, sizeof (voidfunc));

  /* Invoke it.
     If the stack is not executable, it crashes with SIGSEGV.
     If the instructions above are incorrect, it crashes with SIGILL. */
  (*(void (*) (void)) voidfunc_in_stack) ();

  puts ("OK");

  return 0;
}
