/* vacall function for alpha CPU */

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
         *		env	__asm__("$1");
#endif
register long		arg1	__asm__("$16");
register long		arg2	__asm__("$17");
register long		arg3	__asm__("$18");
register long		arg4	__asm__("$19");
register long		arg5	__asm__("$20");
register long		arg6	__asm__("$21");
register double		farg1	__asm__("$f16");
register double		farg2	__asm__("$f17");
register double		farg3	__asm__("$f18");
register double		farg4	__asm__("$f19");
register double		farg5	__asm__("$f20");
register double		farg6	__asm__("$f21");
register __vaword	iret	__asm__("$0");
register __vaword	iret2	__asm__("$1");
register float		fret	__asm__("$f0");
register double		dret	__asm__("$f0");

#ifdef REENTRANT
static
#endif
void /* the return type is variable, not void! */
__vacall (__vaword word1, __vaword word2, __vaword word3, __vaword word4,
          __vaword word5, __vaword word6,
          __vaword firstword)
{
  /* Put all local variables in a struct, so that we control the allocation
   * order on the stack. */
  struct {
    __va_alist list;
    double farg1, farg2, farg3, farg4, farg5, farg6;
    long arg1, arg2, arg3, arg4, arg5, arg6;
  } locals;
  /* MAGIC ALERT! This is the last struct on the stack, so that
   * &locals + 1 == &firstword. Look at the assembly code to convince yourself.
   */
  /* Move the arguments passed in registers to their stack locations. */
  /* locals.arg1 = */ (&firstword)[-6] = word1; /* $16 */
  /* locals.arg2 = */ (&firstword)[-5] = word2; /* $17 */
  /* locals.arg3 = */ (&firstword)[-4] = word3; /* $18 */
  /* locals.arg4 = */ (&firstword)[-3] = word4; /* $19 */
  /* locals.arg5 = */ (&firstword)[-2] = word5; /* $20 */
  /* locals.arg6 = */ (&firstword)[-1] = word6; /* $21 */
  locals.farg1 = farg1;
  locals.farg2 = farg2;
  locals.farg3 = farg3;
  locals.farg4 = farg4;
  locals.farg5 = farg5;
  locals.farg6 = farg6;
  /* Prepare the va_alist. */
  locals.list.flags = 0;
  locals.list.aptr = (long)(&firstword - 6);
  locals.list.raddr = (void*)0;
  locals.list.rtype = __VAvoid;
  locals.list.memargptr = (long)&firstword;
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
        if (locals.list.rsize == sizeof(char)) {
          iret = *(unsigned char *) locals.list.raddr;
        } else
        if (locals.list.rsize == sizeof(short)) {
          iret = *(unsigned short *) locals.list.raddr;
        } else
        if (locals.list.rsize == sizeof(int)) {
          iret = *(unsigned int *) locals.list.raddr;
        } else
        if (locals.list.rsize == sizeof(long)) {
          iret = *(unsigned long *) locals.list.raddr;
        } else
        if (locals.list.rsize == 2*sizeof(__vaword)) {
          iret  = ((__vaword *) locals.list.raddr)[0];
          iret2 = ((__vaword *) locals.list.raddr)[1];
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
