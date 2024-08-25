/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2022 Bruno Haible <bruno@clisp.org>

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
  Foreign function interface for LoongArch 64-bit CPU with LP64 ABI.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  LoongArch64 argument passing conventions:

  Up to 8 words are passed in integer registers (r4, ..., r11); remaining
  words are passed on the stack.
  Up to 8 float/double arguments are passed in floating point registers
  (f0, ..., f7), further float/double arguments are passed in integer
  registers, remaining float/double arguments are passed on the stack.
  Arguments passed on the stack have 8-bytes alignment.
  Structure args <= 16 bytes are passed as up to two words in registers
  (floating-point fields of structures with at most two fields in
  floating-point registers, other fields in integer registers).
  Structure args larger than 16 bytes are passed as pointers to caller-made
  local copies.

  Integers are returned in r4, r5.
  Float/double values are returned in f0, f1.
  Structures <= 16 bytes are returned in registers (floating-point fields
  of structures with at most two fields in floating-point registers, other
  fields in integer registers).
  To return a structure larger than 16 bytes, the caller allocates the
  space and passes a pointer to it as first argument (i.e. in r4).
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)        (*(TYPE*)l->raddr = (TYPE)(VAL))

register __avrword iarg1 __asm__("r4");
register __avrword iarg2 __asm__("r5");
register __avrword iarg3 __asm__("r6");
register __avrword iarg4 __asm__("r7");
register __avrword iarg5 __asm__("r8");
register __avrword iarg6 __asm__("r9");
register __avrword iarg7 __asm__("r10");
register __avrword iarg8 __asm__("r11");

register float farg1 __asm__("f0");
register float farg2 __asm__("f1");
register float farg3 __asm__("f2");
register float farg4 __asm__("f3");
register float farg5 __asm__("f4");
register float farg6 __asm__("f5");
register float farg7 __asm__("f6");
register float farg8 __asm__("f7");

register double darg1 __asm__("f0");
register double darg2 __asm__("f1");
register double darg3 __asm__("f2");
register double darg4 __asm__("f3");
register double darg5 __asm__("f4");
register double darg6 __asm__("f5");
register double darg7 __asm__("f6");
register double darg8 __asm__("f7");

int
avcall_call(av_alist* list)
{
  register __avrword    iretreg  __asm__("r4");
  register __avrword    iret2reg __asm__("r5");
  register double       dret    __asm__("f0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  unsigned int fanum = l->fanum;

  {
    int i;
    for (i = 8; i < arglen; i++)        /* push function args onto stack */
      argframe[i-8] = l->args[i];
  }

  /* Put up to 8 integer args into registers. */
  if (arglen >= 1) {
    iarg1 = l->args[0];
    if (arglen >= 2) {
      iarg2 = l->args[1];
      if (arglen >= 3) {
        iarg3 = l->args[2];
        if (arglen >= 4) {
          iarg4 = l->args[3];
          if (arglen >= 5) {
            iarg5 = l->args[4];
            if (arglen >= 6) {
              iarg6 = l->args[5];
              if (arglen >= 7) {
                iarg7 = l->args[6];
                if (arglen >= 8) {
                  iarg8 = l->args[7];
                }
              }
            }
          }
        }
      }
    }
  }

  /* Put upto 8 floating-point args into registers. */
  if (fanum >= 1) {
    if (l->darg_mask & (1 << 0)) darg1 = l->dargs[0];
    else if (l->farg_mask & (1 << 0)) farg1 = l->fargs[0];
    if (fanum >= 2) {
      if (l->darg_mask & (1 << 1)) darg2 = l->dargs[1];
      else if (l->farg_mask & (1 << 1)) farg2 = l->fargs[1];
      if (fanum >= 3) {
        if (l->darg_mask & (1 << 2)) darg3 = l->dargs[2];
        else if (l->farg_mask & (1 << 2)) farg3 = l->fargs[2];
        if (fanum >= 4) {
          if (l->darg_mask & (1 << 3)) darg4 = l->dargs[3];
          else if (l->farg_mask & (1 << 3)) farg4 = l->fargs[3];
          if (fanum >= 5) {
            if (l->darg_mask & (1 << 4)) darg5 = l->dargs[4];
            else if (l->farg_mask & (1 << 4)) farg5 = l->fargs[4];
            if (fanum >= 6) {
              if (l->darg_mask & (1 << 5)) darg6 = l->dargs[5];
              else if (l->farg_mask & (1 << 5)) farg6 = l->fargs[5];
              if (fanum >= 7) {
                if (l->darg_mask & (1 << 6)) darg7 = l->dargs[6];
                else if (l->farg_mask & (1 << 6)) farg7 = l->fargs[6];
                if (fanum >= 8) {
                  if (l->darg_mask & (1 << 7)) darg8 = l->dargs[7];
                  else if (l->farg_mask & (1 << 7)) farg8 = l->fargs[7];
                }
              }
            }
          }
        }
      }
    }
  }
        
  /* Call function. */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr = (*(float(*)())l->func)();
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr = (*(double(*)())l->func)();
  } else {
    __avrword iret, iret2;

    iret = (*l->func)();
    iret2 = iret2reg;

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
    if (l->rtype == __AVlong || l->rtype == __AVlonglong) {
      RETURN(long, iret);
    } else
    if (l->rtype == __AVulong || l->rtype == __AVulonglong) {
      RETURN(unsigned long, iret);
    } else
  /* see above
    if (l->rtype == __AVfloat) {
    } else
    if (l->rtype == __AVdouble) {
    } else
  */
    if (l->rtype == __AVvoidp) {
      RETURN(void*, iret);
    } else
    if (l->rtype == __AVstruct) {
      if (l->flags & __AV_REGISTER_STRUCT_RETURN) {
        /* Return structs of size <= 16 in registers. */
        if (l->rsize > 0 && l->rsize <= 16) {
          void* raddr = l->raddr;
          #if 0 /* Unoptimized */
          if (l->rsize == 1) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          } else
          if (l->rsize == 2) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          } else
          if (l->rsize == 3) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
          } else
          if (l->rsize == 4) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
          } else
          if (l->rsize == 5) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
          } else
          if (l->rsize == 6) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
          } else
          if (l->rsize == 7) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>48);
          } else
          if (l->rsize >= 8 && l->rsize <= 16) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>48);
            ((unsigned char *)raddr)[7] = (unsigned char)(iret>>56);
            if (l->rsize == 8) {
            } else
            if (l->rsize == 9) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
            } else
            if (l->rsize == 10) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
            } else
            if (l->rsize == 11) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
            } else
            if (l->rsize == 12) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
            } else
            if (l->rsize == 13) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
            } else
            if (l->rsize == 14) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>40);
            } else
            if (l->rsize == 15) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>48);
            } else
            if (l->rsize == 16) {
              ((unsigned char *)raddr)[8+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[8+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[8+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[8+3] = (unsigned char)(iret2>>24);
              ((unsigned char *)raddr)[8+4] = (unsigned char)(iret2>>32);
              ((unsigned char *)raddr)[8+5] = (unsigned char)(iret2>>40);
              ((unsigned char *)raddr)[8+6] = (unsigned char)(iret2>>48);
              ((unsigned char *)raddr)[8+7] = (unsigned char)(iret2>>56);
            }
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
              __avrword mask0 = ((__avrword)2 << (end_offset*8-1)) - ((__avrword)1 << (start_offset*8));
              wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            } else {
              /* sizeof(__avrword) < end_offset < 2*sizeof(__avrword), start_offset > 0 */
              __avrword mask0 = - ((__avrword)1 << (start_offset*8));
              __avrword mask1 = ((__avrword)2 << (end_offset*8-sizeof(__avrword)*8-1)) - 1;
              wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
              wordaddr[1] ^= (wordaddr[1] ^ (iret >> (sizeof(__avrword)*8-start_offset*8))) & mask1;
            }
          } else {
            /* Use iret, iret2. */
            __avrword mask0 = - ((__avrword)1 << (start_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            if (end_offset <= 2*sizeof(__avrword)) {
              /* sizeof(__avrword) < end_offset ≤ 2*sizeof(__avrword) */
              __avrword mask1 = ((__avrword)2 << (end_offset*8-sizeof(__avrword)*8-1)) - 1;
              wordaddr[1] ^= (wordaddr[1] ^ ((iret >> (sizeof(__avrword)*4-start_offset*4) >> (sizeof(__avrword)*4-start_offset*4)) | (iret2 << (start_offset*8)))) & mask1;
            } else {
              /* 2*sizeof(__avrword) < end_offset < 3*sizeof(__avrword), start_offset > 0 */
              __avrword mask2 = ((__avrword)2 << (end_offset*8-2*sizeof(__avrword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avrword)*8-start_offset*8)) | (iret2 << (start_offset*8));
              wordaddr[2] ^= (wordaddr[2] ^ (iret2 >> (sizeof(__avrword)*8-start_offset*8))) & mask2;
            }
          }
          #endif
        }
      }
    }
  }
  return 0;
}
