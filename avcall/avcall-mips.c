#ifndef _avcall_mips_c				/*-*- C -*-*/
#define _avcall_mips_c
/**
  Copyright 1993 Bill Triggs, <Bill.Triggs@inrialpes.fr>
  Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
  Copyright 2005 Thiemo Seufer  <ths@debian.org>

  This is free software distributed under the GNU General Public
  Licence described in the file COPYING. Contact the author if
  you don't have this or can't live with it. There is ABSOLUTELY
  NO WARRANTY, explicit or implied, on this software.
**/
/*----------------------------------------------------------------------
  !!! THIS ROUTINE MUST BE COMPILED gcc -O !!!

  Foreign function interface for an SGI MIPS with gcc/sgi-cc.

  This calls a C function with an argument list built up using macros
  defined in av_call.h.

  SGI MIPS Argument Passing Conventions

  - The entire argument list forms a structure with all the appropriate
    holes & alignments, and space for this is allocated in the stack frame.
  - Shorter integers are promoted to word length (sizeof(int)=sizeof(long)=4).
  - Doubles are 2 words aligned on even boundaries.
  - The first 4 words of the structure are passed in registers $4...$7, stack
    space for these is always allocated. Remaining words are passed on the
    stack.
  - If the first two args are floats or doubles, they are also passed in $f12
    and $f14. But varargs functions will expect them in the integer registers
    and we can't tell whether the function is varargs so we pass them both ways.
  - Structure arguments are copies embedded in the arglist structure.
  - Structure returns are pointers to caller-allocated space passed in as the
    first argument of the list. The function also returns the pointer.
  - Integer/pointer returns are in $2, float/double returns in $f0.
  - Under IRIX 5, the called function expects to see its own address in $25.

  This file needs to be compiled with gcc for the asm extensions, but the
  assembly version of it and the header file seem to work with SGI cc.
  ----------------------------------------------------------------------*/
#include "avcall.h.in"

#define RETURN(TYPE,VAL)	(*(TYPE*)l->raddr = (TYPE)(VAL))
#define OFFSETOF(struct,member) ((int)&(((struct*)0)->member))

typedef __avword (*func_pointer)();
register func_pointer	t9	__asm__("$25");

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp __asm__("$sp");  /* C names for registers */
  register __avword	iret2_tmp __asm__("$3");
  register float	fret_tmp __asm__("$f0");
  register double	dret_tmp __asm__("$f0");
  __avword *space = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword));	/* big space for child's stack frame */
  __avword *argframe = (__avword*)sp;	/* stack offset for argument list is 0 */
  int arglen = l->aptr - l->args;
  int i;
  __avword iret;
  long long iret2;
  float fret;
  double dret;

  /* load leading float args */
  if (l->flags & __AV_FLOAT_1)
    __asm__("l.s $f12,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,floatarg[0]));
  if (l->flags & __AV_DOUBLE_1)
    __asm__("l.d $f12,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,doublearg[0]));
  if ((l->flags & __AV_FLOAT_2) && (l->flags & (__AV_FLOAT_1 | __AV_DOUBLE_1)))
    __asm__("l.s $f14,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,floatarg[1]));
  if ((l->flags & __AV_DOUBLE_2) && (l->flags & (__AV_FLOAT_1 | __AV_DOUBLE_1)))
    __asm__("l.d $f14,%1(%0)" : : "p" (l), "i" OFFSETOF(av_alist,doublearg[1]));

  for (i = 4; i < arglen; i++)		/* push excess function args */
    argframe[i] = l->args[i];

  iret = (*(t9 = l->func))(l->args[0], l->args[1],  /* call function with 1st 4 args */
			   l->args[2], l->args[3]);
  iret2 = iret2_tmp;
  fret = fret_tmp;
  dret = dret_tmp;

  /* save return value */
  switch (l->rtype) {
  default:
  case __AVvoid:
    break;
  case __AVword:
    RETURN(__avword, iret);
    break;
  case __AVchar:
    RETURN(char, iret);
    break;
  case __AVschar:
    RETURN(signed char, iret);
    break;
  case __AVuchar:
    RETURN(unsigned char, iret);
    break;
  case __AVshort:
    RETURN(short, iret);
    break;
  case __AVushort:
    RETURN(unsigned short, iret);
    break;
  case __AVint:
    RETURN(int, iret);
    break;
  case __AVuint:
    RETURN(unsigned int, iret);
    break;
  case __AVlong:
    RETURN(long, iret);
    break;
  case __AVulong:
    RETURN(unsigned long, iret);
    break;
  case __AVlonglong:
  case __AVulonglong:
    ((__avword*)l->raddr)[0] = (__avword)(iret);
    ((__avword*)l->raddr)[1] = iret2;
    break;
  case __AVfloat:
    RETURN(float, fret);
    break;
  case __AVdouble:
    RETURN(double, dret);
    break;
  case __AVvoidp:
    RETURN(void*, (__avword)iret);
    break;
  case __AVstruct:
    if (l->flags & __AV_PCC_STRUCT_RETURN) {
      /* pcc struct return convention: need a  *(TYPE*)l->raddr = *(TYPE*)i;  */
      if (l->rsize == sizeof(char)) {
        RETURN(char, *(char*)(__avword)iret);
      } else
      if (l->rsize == sizeof(short)) {
        RETURN(short, *(short*)(__avword)iret);
      } else
      if (l->rsize == sizeof(int)) {
        RETURN(int, *(int*)(__avword)iret);
      } else
      if (l->rsize == sizeof(double)) {
        ((int*)l->raddr)[0] = ((int*)(__avword)iret)[0];
        ((int*)l->raddr)[1] = ((int*)(__avword)iret)[1];
      } else {
        int n = (l->rsize + sizeof(__avword)-1)/sizeof(__avword);
        while (--n >= 0)
          ((__avword*)l->raddr)[n] = ((__avword*)(__avword)iret)[n];
      }
    } else {
      /* normal struct return convention */
      if (l->flags & __AV_SMALL_STRUCT_RETURN) {
        if (l->rsize == sizeof(char)) {
          RETURN(char, iret);
        } else
        if (l->rsize == sizeof(short)) {
          RETURN(short, iret);
        } else
        if (l->rsize == sizeof(int)) {
          RETURN(int, iret);
        }
      }
    }
    break;
  }
  return 0;
}

#endif /*_avcall_mips_c */
