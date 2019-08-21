/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2019 Bruno Haible <bruno@clisp.org>

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
  Foreign function interface for a Linux riscv32 with ILP32 ABI.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  RISC-V Argument Passing Conventions are documented in
  https://people.eecs.berkeley.edu/~krste/papers/riscv-spec-v2.1.pdf
  chapter 20.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))

register __avword iarg1 __asm__("a0");
register __avword iarg2 __asm__("a1");
register __avword iarg3 __asm__("a2");
register __avword iarg4 __asm__("a3");
register __avword iarg5 __asm__("a4");
register __avword iarg6 __asm__("a5");
register __avword iarg7 __asm__("a6");
register __avword iarg8 __asm__("a7");

register float farg1 __asm__("fa0");
register float farg2 __asm__("fa1");
register float farg3 __asm__("fa2");
register float farg4 __asm__("fa3");
register float farg5 __asm__("fa4");
register float farg6 __asm__("fa5");
register float farg7 __asm__("fa6");
register float farg8 __asm__("fa7");

register double darg1 __asm__("fa0");
register double darg2 __asm__("fa1");
register double darg3 __asm__("fa2");
register double darg4 __asm__("fa3");
register double darg5 __asm__("fa4");
register double darg6 __asm__("fa5");
register double darg7 __asm__("fa6");
register double darg8 __asm__("fa7");

int
avcall_call(av_alist* list)
{
  register __avword	iretreg	 __asm__("a0");
  register __avword	iret2reg __asm__("a1");
  register double	dret	__asm__("fa0");

  __av_alist* l = &AV_LIST_INNER(list);

  __avword* argframe = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword)); /* make room for argument list */
  int arglen = l->aptr - l->args;
  unsigned int fanum = l->fanum;

  {
    int i;
    for (i = 8; i < arglen; i++)	/* push function args onto stack */
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
    __avword iret, iret2;

    iret = (*l->func)();
    iret2 = iret2reg;

    /* save return value */
    if (l->rtype == __AVvoid) {
    } else
    if (l->rtype == __AVword) {
      RETURN(__avword, iret);
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
      ((__avword*)raddr)[0] = iret;
      ((__avword*)raddr)[1] = iret2;
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
      if (l->flags & __AV_SMALL_STRUCT_RETURN) {
        /* Return structs of size <= 8 in registers. */
        if (l->rsize > 0 && l->rsize <= 8) {
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
          if (l->rsize >= 4 && l->rsize <= 8) {
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
            if (l->rsize == 4) {
            } else
            if (l->rsize == 5) {
              ((unsigned char *)raddr)[4+0] = (unsigned char)(iret2);
            } else
            if (l->rsize == 6) {
              ((unsigned char *)raddr)[4+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[4+1] = (unsigned char)(iret2>>8);
            } else
            if (l->rsize == 7) {
              ((unsigned char *)raddr)[4+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[4+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[4+2] = (unsigned char)(iret2>>16);
            } else
            if (l->rsize == 8) {
              ((unsigned char *)raddr)[4+0] = (unsigned char)(iret2);
              ((unsigned char *)raddr)[4+1] = (unsigned char)(iret2>>8);
              ((unsigned char *)raddr)[4+2] = (unsigned char)(iret2>>16);
              ((unsigned char *)raddr)[4+3] = (unsigned char)(iret2>>24);
            }
          }
          #else /* Optimized: fewer conditional jumps, fewer memory accesses */
          uintptr_t count = l->rsize; /* > 0, ≤ 2*sizeof(__avword) */
          __avword* wordaddr = (__avword*)((uintptr_t)raddr & ~(uintptr_t)(sizeof(__avword)-1));
          uintptr_t start_offset = (uintptr_t)raddr & (uintptr_t)(sizeof(__avword)-1); /* ≥ 0, < sizeof(__avword) */
          uintptr_t end_offset = start_offset + count; /* > 0, < 3*sizeof(__avword) */
          if (count <= sizeof(__avword)) {
            /* Use iret. */
            if (end_offset <= sizeof(__avword)) {
              /* 0 < end_offset ≤ sizeof(__avword) */
              __avword mask0 = ((__avword)2 << (end_offset*8-1)) - ((__avword)1 << (start_offset*8));
              wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            } else {
              /* sizeof(__avword) < end_offset < 2*sizeof(__avword), start_offset > 0 */
              __avword mask0 = - ((__avword)1 << (start_offset*8));
              __avword mask1 = ((__avword)2 << (end_offset*8-sizeof(__avword)*8-1)) - 1;
              wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
              wordaddr[1] ^= (wordaddr[1] ^ (iret >> (sizeof(__avword)*8-start_offset*8))) & mask1;
            }
          } else {
            /* Use iret, iret2. */
            __avword mask0 = - ((__avword)1 << (start_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            if (end_offset <= 2*sizeof(__avword)) {
              /* sizeof(__avword) < end_offset ≤ 2*sizeof(__avword) */
              __avword mask1 = ((__avword)2 << (end_offset*8-sizeof(__avword)*8-1)) - 1;
              wordaddr[1] ^= (wordaddr[1] ^ ((iret >> (sizeof(__avword)*4-start_offset*4) >> (sizeof(__avword)*4-start_offset*4)) | (iret2 << (start_offset*8)))) & mask1;
            } else {
              /* 2*sizeof(__avword) < end_offset < 3*sizeof(__avword), start_offset > 0 */
              __avword mask2 = ((__avword)2 << (end_offset*8-2*sizeof(__avword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avword)*8-start_offset*8)) | (iret2 << (start_offset*8));
              wordaddr[2] ^= (wordaddr[2] ^ (iret2 >> (sizeof(__avword)*8-start_offset*8))) & mask2;
            }
          }
          #endif
        }
      }
    }
  }
  return 0;
}
