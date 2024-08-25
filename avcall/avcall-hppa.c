/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2021 Bruno Haible <bruno@clisp.org>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
**/
/*----------------------------------------------------------------------
  !!! THIS ROUTINE MUST BE COMPILED gcc -O !!!

  Foreign function interface for a HP Precision Architecture 1.0 with gcc

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  HPPA Argument Passing Conventions:

  All arguments, except the first 4 words, are passed on the stack
  - growing down! - with word alignment. Doubles take two words and force
  double alignment. Small structures args are passed as true structures
  embedded in the argument stack. They force double alignment and - if they
  don't fit entirely in the 4 register words - are passed in memory.
  The first 2 words are passed like this:
    %r26 = first integer arg, %r25 = second integer arg, or
    %r26 = high word of double arg, %r25 = low word of double arg.
  Similarly for the next 2 words, passed in %r24 and %r23.
  Note that other calling conventions would be in effect if we would call
  an explicitly named function!

  Structures larger than 8 bytes are passed as a pointer.  In GCC >= 8
  it's a caller-made copy; with GCC < 8 and with HP cc it's the callee's
  responsibility to make a copy of the structure, so that side effects
  made by the callee are not visible to the caller.

  To return a structure of more than 8 bytes, the called function copies
  the return value to the address supplied in register "%r28". Smaller
  structures are returned in the registers %r28 (first 4 bytes) and %r29
  (next 4 bytes, if present).

  It is forbidden to modify the stack pointer.

  Compile this routine with gcc -O2 -fomit-frame-pointer to get the right
  register variables.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)        (*(TYPE*)l->raddr = (TYPE)(VAL))

/* This declaration tells gcc not to modify %r28. */
register __avword*      sret    __asm__("%r28");  /* structure return pointer */

register float  farg1   __asm__("%fr4"); /* fr4L */
register float  farg2   __asm__("%fr5"); /* fr5L */
register float  farg3   __asm__("%fr6"); /* fr6L */
register float  farg4   __asm__("%fr7"); /* fr7L */
register double darg1   __asm__("%fr5");
register double darg2   __asm__("%fr7");

int
avcall_call(av_alist* list)
{
  register __avword*    sp      __asm__("%r30");  /* C names for registers */
  register float        fret    __asm__("%fr4");
  register double       dret    __asm__("%fr4");
/*register __avrword    iret1   __asm__("%r28"); */
  register __avrword    iret2   __asm__("%r29");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  argframe += __AV_ALIST_WORDS + 20;
  int arglen = l->args_end - l->aptr;
  __avrword iret;

  {
    int i;
    for (i = -arglen; i < -4; i++)      /* push function args onto stack */
      argframe[i] = l->args_end[i];
  }

  if (l->rtype == __AVstruct)           /* push struct return address */
    sret = l->raddr;

  /* The floats and doubles among the first 4 argument words are passed
   * - in both general registers and floating-point registers when the
   *   function call is a variadic one, which means:
   *     - for HP cc: the call is done through a function pointer or
   *       directly to a function declared with a varargs prototype,
   *     - for GCC: the function's type is a varargs function.
   * - in floating-point registers otherwise.
   * To cover both cases, put these floating-point values into the general
   * registers and the floating-point registers always.
   */
  if (arglen >= 1) {
    if (l->farg_mask & (1 << 0))
      /*__asm__ __volatile__ ("fldw %0,%%fr4R" : : "m" (*(float*)&l->args_end[-1]));*/ farg1 = *((float*)&l->args_end[-1]);
    if (arglen >= 2) {
      if (l->farg_mask & (1 << 1))
        /* __asm__ __volatile__ ("fldw %0,%%fr5R" : : "m" (*(float*)&l->args_end[-2])); */ farg2 = *((float*)&l->args_end[-2]);
      if (l->darg_mask & (1 << 1))
        darg1 = *((double*)&l->args_end[-2]);
      if (arglen >= 3) {
        if (l->farg_mask & (1 << 2))
          /* __asm__ __volatile__ ("fldw %0,%%fr6R" : : "m" (*(float*)&l->args_end[-3])); */ farg3 = *((float*)&l->args_end[-3]);
        if (arglen >= 4) {
          if (l->farg_mask & (1 << 3))
            /* __asm__ __volatile__ ("fldw %0,%%fr7R" : : "m" (*(float*)&l->args_end[-4])); */ farg4 = *((float*)&l->args_end[-4]);
          if (l->darg_mask & (1 << 3))
            darg2 = *((double*)&l->args_end[-4]);
        }
      }
    }
  }
  /* call function, pass first 4 arg words in general registers */
  iret = (*l->func)(l->args_end[-1], l->args_end[-2],
                    l->args_end[-3], l->args_end[-4]);

  /* save return value */
  if (l->rtype == __AVvoid) {
  } else
  if (l->rtype == __AVchar) {
    RETURN(char, iret);
  } else
  if (l->rtype == __AVschar) {
    RETURN(signed char, iret);
  } else
  if (l->rtype == __AVuchar) {
    RETURN(unsigned char, iret);
  } else
  if (l->rtype == __AVshort) {
    RETURN(short, iret);
  } else
  if (l->rtype == __AVushort) {
    RETURN(unsigned short, iret);
  } else
  if (l->rtype == __AVint) {
    RETURN(int, iret);
  } else
  if (l->rtype == __AVuint) {
    RETURN(unsigned int, iret);
  } else
  if (l->rtype == __AVlong) {
    RETURN(long, iret);
  } else
  if (l->rtype == __AVulong) {
    RETURN(unsigned long, iret);
  } else
  if (l->rtype == __AVlonglong || l->rtype == __AVulonglong) {
    void* raddr = l->raddr;
    ((__avrword*)raddr)[0] = iret;
    ((__avrword*)raddr)[1] = iret2;
  } else
  if (l->rtype == __AVfloat) {
    RETURN(float, fret);
  } else
  if (l->rtype == __AVdouble) {
    RETURN(double, dret);
  } else
  if (l->rtype == __AVvoidp) {
    RETURN(void*, iret);
  } else
  if (l->rtype == __AVstruct) {
    if (l->flags & __AV_SMALL_STRUCT_RETURN) {
      /* cc, c89 and gcc >= 2.7 return structs of size <= 8 in registers. */
      if (l->rsize > 0 && l->rsize <= 8) {
        /* This is really weird code, unlike all other big-endian platforms. */
        void* raddr = l->raddr;
        #if 0 /* Unoptimized */
        if (l->rsize == 1) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
        } else
        if (l->rsize == 2) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret);
        } else
        if (l->rsize == 3) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret);
        } else
        if (l->rsize == 4) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>24);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret);
        } else
        if (l->rsize == 5) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2);
        } else
        if (l->rsize == 6) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret2);
        } else
        if (l->rsize == 7) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[6] = (unsigned char)(iret2);
        } else
        if (l->rsize == 8) {
          ((unsigned char *)raddr)[0] = (unsigned char)(iret>>24);
          ((unsigned char *)raddr)[1] = (unsigned char)(iret>>16);
          ((unsigned char *)raddr)[2] = (unsigned char)(iret>>8);
          ((unsigned char *)raddr)[3] = (unsigned char)(iret);
          ((unsigned char *)raddr)[4] = (unsigned char)(iret2>>24);
          ((unsigned char *)raddr)[5] = (unsigned char)(iret2>>16);
          ((unsigned char *)raddr)[6] = (unsigned char)(iret2>>8);
          ((unsigned char *)raddr)[7] = (unsigned char)(iret2);
        }
        #else /* Optimized: fewer conditional jumps, fewer memory accesses */
        uintptr_t count = l->rsize; /* > 0, ≤ 2*sizeof(__avrword) */
        __avrword* wordaddr = (__avrword*)((uintptr_t)raddr & ~(uintptr_t)(sizeof(__avrword)-1));
        uintptr_t start_offset = (uintptr_t)raddr & (uintptr_t)(sizeof(__avrword)-1); /* ≥ 0, < sizeof(__avrword) */
        uintptr_t end_offset = start_offset + count; /* > 0, < 3*sizeof(__avrword) */
        if (count <= sizeof(__avrword)) {
          /* Use iret. */
          if (end_offset <= sizeof(__avrword)) {
            /* 0 < end_offset ≤ sizeof(__avrword) */
            __avrword mask0 = ((__avrword)2 << (sizeof(__avrword)*8-start_offset*8-1)) - ((__avrword)1 << (sizeof(__avrword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (sizeof(__avrword)*8-end_offset*8))) & mask0;
          } else {
            /* sizeof(__avrword) < end_offset < 2*sizeof(__avrword), start_offset > 0 */
            __avrword mask0 = ((__avrword)2 << (sizeof(__avrword)*8-start_offset*8-1)) - 1;
            __avrword mask1 = - ((__avrword)1 << (2*sizeof(__avrword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret >> (end_offset*8-sizeof(__avrword)*8))) & mask0;
            wordaddr[1] ^= (wordaddr[1] ^ (iret << (2*sizeof(__avrword)*8-end_offset*8))) & mask1;
          }
        } else {
          /* Use iret, iret2. */
          __avrword mask0 = ((__avrword)2 << (sizeof(__avrword)*8-start_offset*8-1)) - 1;
          if (end_offset <= 2*sizeof(__avrword)) {
            /* sizeof(__avrword) < end_offset ≤ 2*sizeof(__avrword) */
            __avrword mask1 = - ((__avrword)1 << (2*sizeof(__avrword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ ((iret << (2*sizeof(__avrword)*8-end_offset*8)) | (iret2 >> (end_offset*4-sizeof(__avrword)*4) >> (end_offset*4-sizeof(__avrword)*4)))) & mask0;
            wordaddr[1] ^= (wordaddr[1] ^ (iret2 << (2*sizeof(__avrword)*8-end_offset*8))) & mask1;
          } else {
            /* 2*sizeof(__avrword) < end_offset < 3*sizeof(__avrword), start_offset > 0 */
            __avrword mask2 = - ((__avrword)1 << (3*sizeof(__avrword)*8-end_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret >> (end_offset*8-2*sizeof(__avrword)*8))) & mask0;
            wordaddr[1] = (iret << (3*sizeof(__avrword)*8-end_offset*8)) | (iret2 >> (end_offset*8-2*sizeof(__avrword)*8));
            wordaddr[2] ^= (wordaddr[2] ^ (iret2 << (3*sizeof(__avrword)*8-end_offset*8))) & mask2;
          }
        }
        #endif
      }
    }
  }
  return 0;
}
