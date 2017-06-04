/* vacall function for ia64 CPU */

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

#ifndef REENTRANT
#include "vacall.h.in"
#else /* REENTRANT */
#include "vacall_r.h.in"
#endif

#ifdef REENTRANT
#define __vacall __vacall_r
register struct { void (*vacall_function) (void*,va_alist); void* arg; }
         *		env	__asm__("r15");
#endif
register double		farg1	__asm__("f8");
register double		farg2	__asm__("f9");
register double		farg3	__asm__("f10");
register double		farg4	__asm__("f11");
register double		farg5	__asm__("f12");
register double		farg6	__asm__("f13");
register double		farg7	__asm__("f14");
register double		farg8	__asm__("f15");
register __vaword*	sret	__asm__("r8");
register __vaword	iret	__asm__("r8");
register __vaword	iret2	__asm__("r9");
register __vaword	iret3	__asm__("r10");
register __vaword	iret4	__asm__("r11");
register float		fret	__asm__("f8");
register double		dret	__asm__("f8");

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6, __vaword word7, __vaword word8,
          __vaword firstword)
{
  /* Put all local variables in a struct, so that we control the allocation
   * order on the stack. */
  struct {
    __va_alist list;
    __vaword arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;
  } locals;
  /* MAGIC ALERT! This is the last struct on the stack, so that
   * &locals + 1 == &firstword. Look at the assembly code to convince yourself.
   */
  /* Move the arguments passed in registers to their stack locations. */
  /* locals.arg1 = */ (&firstword)[-8] = word1; /* r32 */
  /* locals.arg2 = */ (&firstword)[-7] = word2; /* r33 */
  /* locals.arg3 = */ (&firstword)[-6] = word3; /* r34 */
  /* locals.arg4 = */ (&firstword)[-5] = word4; /* r35 */
  /* locals.arg5 = */ (&firstword)[-4] = word5; /* r36 */
  /* locals.arg6 = */ (&firstword)[-3] = word6; /* r37 */
  /* locals.arg7 = */ (&firstword)[-2] = word7; /* r38 */
  /* locals.arg8 = */ (&firstword)[-1] = word8; /* r39 */
  locals.list.farg[0] = farg1;
  locals.list.farg[1] = farg2;
  locals.list.farg[2] = farg3;
  locals.list.farg[3] = farg4;
  locals.list.farg[4] = farg5;
  locals.list.farg[5] = farg6;
  locals.list.farg[6] = farg7;
  locals.list.farg[7] = farg8;
  /* Prepare the va_alocals.list. */
  locals.list.flags = 0;
  locals.list.aptr = (long)(&firstword - 8);
  locals.list.saptr = &firstword - 8;
  locals.list.memfargptr = &locals.list.farg[0];
  locals.list.raddr = (void*)0;
  locals.list.rtype = __VAvoid;
  locals.list.structraddr = sret;
  /* Call vacall_function. The macros do all the rest. */
#ifndef REENTRANT
  (*vacall_function) (&locals.list);
#else /* REENTRANT */
  (*env->vacall_function) (env->arg,&locals.list);
#endif
  /* Put return value into proper register. */
  if (locals.list.rtype == __VAvoid) {
  } else
  if (locals.list.rtype == __VAchar) {
    iret = locals.list.tmp._char;
  } else
  if (locals.list.rtype == __VAschar) {
    iret = locals.list.tmp._schar;
  } else
  if (locals.list.rtype == __VAuchar) {
    iret = locals.list.tmp._uchar;
  } else
  if (locals.list.rtype == __VAshort) {
    iret = locals.list.tmp._short;
  } else
  if (locals.list.rtype == __VAushort) {
    iret = locals.list.tmp._ushort;
  } else
  if (locals.list.rtype == __VAint) {
    iret = locals.list.tmp._int;
  } else
  if (locals.list.rtype == __VAuint) {
    iret = locals.list.tmp._uint;
  } else
  if (locals.list.rtype == __VAlong) {
    iret = locals.list.tmp._long;
  } else
  if (locals.list.rtype == __VAulong) {
    iret = locals.list.tmp._ulong;
  } else
  if (locals.list.rtype == __VAlonglong) {
    iret = locals.list.tmp._long;
  } else
  if (locals.list.rtype == __VAulonglong) {
    iret = locals.list.tmp._ulong;
  } else
  if (locals.list.rtype == __VAfloat) {
    fret = locals.list.tmp._float;
  } else
  if (locals.list.rtype == __VAdouble) {
    dret = locals.list.tmp._double;
  } else
  if (locals.list.rtype == __VAvoidp) {
    iret = (long)locals.list.tmp._ptr;
  } else
  if (locals.list.rtype == __VAstruct) {
    if (locals.list.flags & __VA_PCC_STRUCT_RETURN) {
      /* pcc struct return convention */
      iret = (long) locals.list.raddr;
    } else {
      /* normal struct return convention */
      if (locals.list.flags & __VA_REGISTER_STRUCT_RETURN) {
        /* Return structs of size <= 32 in registers. */
        if (locals.list.rsize > 0 && locals.list.rsize <= 32) {
          iret = (__vaword)((unsigned char *) locals.list.raddr)[0];
          if (locals.list.rsize >= 2)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[1] << 8;
          if (locals.list.rsize >= 3)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[2] << 16;
          if (locals.list.rsize >= 4)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[3] << 24;
          if (locals.list.rsize >= 5)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[4] << 32;
          if (locals.list.rsize >= 6)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[5] << 40;
          if (locals.list.rsize >= 7)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[6] << 48;
          if (locals.list.rsize >= 8)
            iret |= (__vaword)((unsigned char *) locals.list.raddr)[7] << 56;
          if (locals.list.rsize >= 9) {
            iret2 = (__vaword)((unsigned char *) locals.list.raddr)[8];
            if (locals.list.rsize >= 10)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[9] << 8;
            if (locals.list.rsize >= 11)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[10] << 16;
            if (locals.list.rsize >= 12)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[11] << 24;
            if (locals.list.rsize >= 13)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[12] << 32;
            if (locals.list.rsize >= 14)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[13] << 40;
            if (locals.list.rsize >= 15)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[14] << 48;
            if (locals.list.rsize >= 16)
              iret2 |= (__vaword)((unsigned char *) locals.list.raddr)[15] << 56;
            if (locals.list.rsize >= 17) {
              iret3 = (__vaword)((unsigned char *) locals.list.raddr)[16];
              if (locals.list.rsize >= 18)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[17] << 8;
              if (locals.list.rsize >= 19)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[18] << 16;
              if (locals.list.rsize >= 20)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[19] << 24;
              if (locals.list.rsize >= 21)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[20] << 32;
              if (locals.list.rsize >= 22)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[21] << 40;
              if (locals.list.rsize >= 23)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[22] << 48;
              if (locals.list.rsize >= 24)
                iret3 |= (__vaword)((unsigned char *) locals.list.raddr)[23] << 56;
              if (locals.list.rsize >= 25) {
                iret4 = (__vaword)((unsigned char *) locals.list.raddr)[24];
                if (locals.list.rsize >= 26)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[25] << 8;
                if (locals.list.rsize >= 27)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[26] << 16;
                if (locals.list.rsize >= 28)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[27] << 24;
                if (locals.list.rsize >= 29)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[28] << 32;
                if (locals.list.rsize >= 30)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[29] << 40;
                if (locals.list.rsize >= 31)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[30] << 48;
                if (locals.list.rsize >= 32)
                  iret4 |= (__vaword)((unsigned char *) locals.list.raddr)[31] << 56;
              }
            }
          }
        }
      }
    }
  }
}

#ifdef REENTRANT
__vacall_r_t
get__vacall_r (void)
{
  return (__vacall_r_t)(void*)&__vacall;
}
#endif
