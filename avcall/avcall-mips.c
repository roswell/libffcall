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
  - GCC 3.3.x and 3.4.x pass the next args after two floats in $7 and on the
    stack, instead of in $6, $7, and on the stack. This is a bug that is fixed
    in GCC 4.0.4. We don't support these versions of GCC on mips with -mabi=32.
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

int
__builtin_avcall(av_alist* l)
{
  register __avword*	sp __asm__("$sp");  /* C names for registers */
  register __avword	iret2 __asm__("$3");
  register float	fret_tmp __asm__("$f0");
  register double	dret_tmp __asm__("$f0");
  __avword *space = __builtin_alloca(__AV_ALIST_WORDS * sizeof(__avword));	/* big space for child's stack frame */
  __avword *argframe = sp;	/* stack offset for argument list is 0 */
  int arglen = l->aptr - l->args;
  int i;
  __avword iret;
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

  /* Note: The code of this call ought to put the address of the called function
     in register $25 before the call.  */
  iret = (*l->func)(l->args[0], l->args[1],  /* call function with 1st 4 args */
		    l->args[2], l->args[3]);
  fret = fret_tmp;
  dret = dret_tmp;

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
    ((__avword*)l->raddr)[0] = iret;
    ((__avword*)l->raddr)[1] = iret2;
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
    if (l->flags & __AV_PCC_STRUCT_RETURN) {
      /* pcc struct return convention: need a  *(TYPE*)l->raddr = *(TYPE*)iret;  */
      if (l->rsize == sizeof(char)) {
        RETURN(char, *(char*)iret);
      } else
      if (l->rsize == sizeof(short)) {
        RETURN(short, *(short*)iret);
      } else
      if (l->rsize == sizeof(int)) {
        RETURN(int, *(int*)iret);
      } else
      if (l->rsize == sizeof(double)) {
        ((int*)l->raddr)[0] = ((int*)iret)[0];
        ((int*)l->raddr)[1] = ((int*)iret)[1];
      } else {
        int n = (l->rsize + sizeof(__avword)-1)/sizeof(__avword);
        while (--n >= 0)
          ((__avword*)l->raddr)[n] = ((__avword*)iret)[n];
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
  }
  return 0;
}

#endif /*_avcall_mips_c */
