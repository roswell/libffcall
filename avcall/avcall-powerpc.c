/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2024 Bruno Haible <bruno@clisp.org>
  Copyright 2000 Adam Fedor <fedor@gnu.org>
  Copyright 2004 Paul Guyot <pguyot@kallisys.net>

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

  Foreign function interface for an IBM RS/6000 with gcc

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  RS6000 Argument Passing Conventions:

  All arguments, except the first 8 words, are passed on the stack with
  word alignment. Doubles take two words. The first 13 doubles and floats
  are also passed in floating-point-registers.
  To return a structure, the called function copies the value to space
  pointed to by its first argument, and all other arguments are shifted
  down by one.

  Differences between AIX and SysV.4 argument passing conventions:
  - AIX: the first 13 doubles and floats are passed in FP registers,
         and when they do, there is still room allocated for them in the
         argument sequence (integer regs or stack).
    SysV.4: the first 8 doubles and floats are passed in FP registers,
         and no room is allocated for them in the argument sequence.
  - AIX: Structures are passed in the argument sequence.
    SysV.4: Structures are passed by reference: only a pointer appears in
         the argument sequence.
  - AIX: Long longs are only word aligned.
    SysV.4: Long longs are two-word aligned, both when passed in registers
         (pairs: 3/4, 5/6, 7/8, 9/10) and when passed on the stack. (Recall
         that the stack is always 8-byte aligned).

  Compile this routine with gcc -O (or -O2 -fno-omit-frame-pointer or -g -O)
  to get the right register variables. For other compilers use the
  pre-compiled assembler version.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
#define STACK_OFFSET 14
#else /* __powerpc_sysv4__ */
#define STACK_OFFSET 2
#endif

#define RETURN(TYPE,VAL)        (*(TYPE*)l->raddr = (TYPE)(VAL))

register double farg1   __asm__("fr1");
register double farg2   __asm__("fr2");
register double farg3   __asm__("fr3");
register double farg4   __asm__("fr4");
register double farg5   __asm__("fr5");
register double farg6   __asm__("fr6");
register double farg7   __asm__("fr7");
register double farg8   __asm__("fr8");
register double farg9   __asm__("fr9");
register double farg10  __asm__("fr10");
register double farg11  __asm__("fr11");
register double farg12  __asm__("fr12");
register double farg13  __asm__("fr13");

int
avcall_call(av_alist* list)
{
  register __avword*    sp      __asm__("r1");  /* C names for registers */
/*register __avrword    iret    __asm__("r3"); */
  register __avrword    iret2   __asm__("r4");
  register float        fret    __asm__("fr1");
  register double       dret    __asm__("fr1");

  __av_alist* l = &AV_LIST_INNER(list);

#if defined(_AIX) /* for some reason, this does not work on Mac OS X and Linux! */
  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
#else
  __avword space[__AV_ALIST_WORDS];    /* space for callee's stack frame */
  __avword* argframe = sp + STACK_OFFSET;/* stack offset for argument list */
#endif
  int arglen = l->aptr - l->args;
  __avrword iret;
  int i;
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
  int farglen = 0;

  for (i = (8-farglen); i < arglen; i++) /* push function args onto stack */
    argframe[i-8+farglen] = l->args[i];
#else /* __powerpc_sysv4__ */
  for (i = 0; i < arglen; i++) /* push function args onto stack */
    argframe[i] = l->args[i];
#endif

  /* pass first 13 floating-point args in registers */
  arglen = l->faptr - l->fargs;
  if (arglen == 0) goto fargs0;
  else if (arglen == 1) goto fargs1;
  else if (arglen == 2) goto fargs2;
  else if (arglen == 3) goto fargs3;
  else if (arglen == 4) goto fargs4;
  else if (arglen == 5) goto fargs5;
  else if (arglen == 6) goto fargs6;
  else if (arglen == 7) goto fargs7;
  else if (arglen == 8) goto fargs8;
#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
  else if (arglen == 9) goto fargs9;
  else if (arglen == 10) goto fargs10;
  else if (arglen == 11) goto fargs11;
  else if (arglen == 12) goto fargs12;
  else if (arglen == 13) goto fargs13;
  fargs13: farg13 = l->fargs[12];
  fargs12: farg12 = l->fargs[11];
  fargs11: farg11 = l->fargs[10];
  fargs10: farg10 = l->fargs[9];
  fargs9: farg9 = l->fargs[8];
#endif
  fargs8: farg8 = l->fargs[7];
  fargs7: farg7 = l->fargs[6];
  fargs6: farg6 = l->fargs[5];
  fargs5: farg5 = l->fargs[4];
  fargs4: farg4 = l->fargs[3];
  fargs3: farg3 = l->fargs[2];
  fargs2: farg2 = l->fargs[1];
  fargs1: farg1 = l->fargs[0];
  fargs0: ;

#if defined(_AIX) || (defined(__MACH__) && defined(__APPLE__)) /* __powerpc_aix__ */
                                /* call function, pass 8 args in registers */
  iret = (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7]);
#else /* __powerpc_sysv4__ */
  iret = (*l->func)(l->iargs[0], l->iargs[1], l->iargs[2], l->iargs[3],
                    l->iargs[4], l->iargs[5], l->iargs[6], l->iargs[7]);
#endif

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
    if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
      /* On Linux, AIX, only structs of sizes 1, 2, 4, 8 can be returned in
         registers. But on FreeBSD, NetBSD, structs of any size <= 8 are
         returned in registers. */
      if (l->rsize > 0 && l->rsize <= 8) {
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
