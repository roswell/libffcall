/**
  Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
  Copyright 1995-2024 Bruno Haible <bruno@clisp.org>

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

  Foreign function interface for a Intel IA-64 in little-endian mode with gcc.

  This calls a C function with an argument list built up using macros
  defined in avcall.h.

  IA-64 64-bit Argument Passing Conventions:

  The argument sequence is mapped linearly on the registers r32,...,r39,
  and continued on the stack, in [r12+16], [r12+24], ...
  Items in this sequence are word-aligned. In gcc < 3.0, structures larger
  than a single word are even two-word-aligned.
  Integer/pointer arguments are passed in the allocated slots (registers
  or stack slots). The first 8 float/double arguments are passed in
  registers f8,...,f15 instead, but their slots are kept allocated.
  Structure args are passed like multiple integer arguments; except that
  structures consisting only of floats or only of doubles are passed like
  multiple float arguments or multiple double arguments, respectively.

  Integers and pointers are returned in r8, floats and doubles in f8.
  Structures consisting only of at most 8 floats or only of at most 8 doubles
  are returned in f8,...,f15. Other than that, structures of size <= 32 bytes
  are returned in r8,...,r11, as if these were 4 contiguous words in memory.
  Larger structures are returned in memory; the caller passes the address
  of the target memory area in r8, and it is returned unmodified in r8.
  ----------------------------------------------------------------------*/
#include "avcall-internal.h"

#define RETURN(TYPE,VAL)        (*(TYPE*)l->raddr = (TYPE)(VAL))

register __avword*      sret    __asm__("r8");  /* structure return pointer */
/*register __avrword    iret    __asm__("r8");*/
register __avrword      iret2   __asm__("r9");
register __avrword      iret3   __asm__("r10");
register __avrword      iret4   __asm__("r11");
/*register float        fret    __asm__("f8");*/
/*register double       dret    __asm__("f8");*/
register double         farg1   __asm__("f8");
register double         farg2   __asm__("f9");
register double         farg3   __asm__("f10");
register double         farg4   __asm__("f11");
register double         farg5   __asm__("f12");
register double         farg6   __asm__("f13");
register double         farg7   __asm__("f14");
register double         farg8   __asm__("f15");

int
avcall_call(av_alist* list)
{
  register __avword*    sp      __asm__("r12"); /* C names for registers */

  __av_alist* l = &AV_LIST_INNER(list);

  int arglen = l->aptr - l->args;
  int farglen = l->faptr - l->fargs;
  __avrword iret;

  /* struct return address */
  if (l->rtype == __AVstruct)
    sret = l->raddr;

  /* put max. 8 double args in registers */
  if (farglen > 0) {
    farg1 = l->fargs[0];
    if (farglen > 1) {
      farg2 = l->fargs[1];
      if (farglen > 2) {
        farg3 = l->fargs[2];
        if (farglen > 3) {
          farg4 = l->fargs[3];
          if (farglen > 4) {
            farg5 = l->fargs[4];
            if (farglen > 5) {
              farg6 = l->fargs[5];
              if (farglen > 6) {
                farg7 = l->fargs[6];
                if (farglen > 7)
                  farg8 = l->fargs[7];
              }
            }
          }
        }
      }
    }
  }

  /* call function, pass 8 integer and 8 double args in registers */
  if (l->rtype == __AVfloat) {
    *(float*)l->raddr =
      (arglen <= 8
       ? (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                l->args[4], l->args[5], l->args[6], l->args[7])
       : arglen <= 16
       ? (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                l->args[4], l->args[5], l->args[6], l->args[7],
                                l->args[8], l->args[9], l->args[10], l->args[11],
                                l->args[12], l->args[13], l->args[14], l->args[15])
       : arglen <= 32
       ? (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                l->args[4], l->args[5], l->args[6], l->args[7],
                                l->args[8], l->args[9], l->args[10], l->args[11],
                                l->args[12], l->args[13], l->args[14], l->args[15],
                                l->args[16], l->args[17], l->args[18], l->args[19],
                                l->args[20], l->args[21], l->args[22], l->args[23],
                                l->args[24], l->args[25], l->args[26], l->args[27],
                                l->args[28], l->args[29], l->args[30], l->args[31])
       : arglen <= 64
       ? (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                l->args[4], l->args[5], l->args[6], l->args[7],
                                l->args[8], l->args[9], l->args[10], l->args[11],
                                l->args[12], l->args[13], l->args[14], l->args[15],
                                l->args[16], l->args[17], l->args[18], l->args[19],
                                l->args[20], l->args[21], l->args[22], l->args[23],
                                l->args[24], l->args[25], l->args[26], l->args[27],
                                l->args[28], l->args[29], l->args[30], l->args[31],
                                l->args[32], l->args[33], l->args[34], l->args[35],
                                l->args[36], l->args[37], l->args[38], l->args[39],
                                l->args[40], l->args[41], l->args[42], l->args[43],
                                l->args[44], l->args[45], l->args[46], l->args[47],
                                l->args[48], l->args[49], l->args[50], l->args[51],
                                l->args[52], l->args[53], l->args[54], l->args[55],
                                l->args[56], l->args[57], l->args[58], l->args[59],
                                l->args[60], l->args[61], l->args[62], l->args[63])
       : arglen <= 128
       ? (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                l->args[4], l->args[5], l->args[6], l->args[7],
                                l->args[8], l->args[9], l->args[10], l->args[11],
                                l->args[12], l->args[13], l->args[14], l->args[15],
                                l->args[16], l->args[17], l->args[18], l->args[19],
                                l->args[20], l->args[21], l->args[22], l->args[23],
                                l->args[24], l->args[25], l->args[26], l->args[27],
                                l->args[28], l->args[29], l->args[30], l->args[31],
                                l->args[32], l->args[33], l->args[34], l->args[35],
                                l->args[36], l->args[37], l->args[38], l->args[39],
                                l->args[40], l->args[41], l->args[42], l->args[43],
                                l->args[44], l->args[45], l->args[46], l->args[47],
                                l->args[48], l->args[49], l->args[50], l->args[51],
                                l->args[52], l->args[53], l->args[54], l->args[55],
                                l->args[56], l->args[57], l->args[58], l->args[59],
                                l->args[60], l->args[61], l->args[62], l->args[63],
                                l->args[64], l->args[65], l->args[66], l->args[67],
                                l->args[68], l->args[69], l->args[70], l->args[71],
                                l->args[72], l->args[73], l->args[74], l->args[75],
                                l->args[76], l->args[77], l->args[78], l->args[79],
                                l->args[80], l->args[81], l->args[82], l->args[83],
                                l->args[84], l->args[85], l->args[86], l->args[87],
                                l->args[88], l->args[89], l->args[90], l->args[91],
                                l->args[92], l->args[93], l->args[94], l->args[95],
                                l->args[96], l->args[97], l->args[98], l->args[99],
                                l->args[100], l->args[101], l->args[102], l->args[103],
                                l->args[104], l->args[105], l->args[106], l->args[107],
                                l->args[108], l->args[109], l->args[110], l->args[111],
                                l->args[112], l->args[113], l->args[114], l->args[115],
                                l->args[116], l->args[117], l->args[118], l->args[119],
                                l->args[120], l->args[121], l->args[122], l->args[123],
                                l->args[124], l->args[125], l->args[126], l->args[127])
       : /* arglen <= __AV_ALIST_WORDS = 256 */
         (*(float(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                l->args[4], l->args[5], l->args[6], l->args[7],
                                l->args[8], l->args[9], l->args[10], l->args[11],
                                l->args[12], l->args[13], l->args[14], l->args[15],
                                l->args[16], l->args[17], l->args[18], l->args[19],
                                l->args[20], l->args[21], l->args[22], l->args[23],
                                l->args[24], l->args[25], l->args[26], l->args[27],
                                l->args[28], l->args[29], l->args[30], l->args[31],
                                l->args[32], l->args[33], l->args[34], l->args[35],
                                l->args[36], l->args[37], l->args[38], l->args[39],
                                l->args[40], l->args[41], l->args[42], l->args[43],
                                l->args[44], l->args[45], l->args[46], l->args[47],
                                l->args[48], l->args[49], l->args[50], l->args[51],
                                l->args[52], l->args[53], l->args[54], l->args[55],
                                l->args[56], l->args[57], l->args[58], l->args[59],
                                l->args[60], l->args[61], l->args[62], l->args[63],
                                l->args[64], l->args[65], l->args[66], l->args[67],
                                l->args[68], l->args[69], l->args[70], l->args[71],
                                l->args[72], l->args[73], l->args[74], l->args[75],
                                l->args[76], l->args[77], l->args[78], l->args[79],
                                l->args[80], l->args[81], l->args[82], l->args[83],
                                l->args[84], l->args[85], l->args[86], l->args[87],
                                l->args[88], l->args[89], l->args[90], l->args[91],
                                l->args[92], l->args[93], l->args[94], l->args[95],
                                l->args[96], l->args[97], l->args[98], l->args[99],
                                l->args[100], l->args[101], l->args[102], l->args[103],
                                l->args[104], l->args[105], l->args[106], l->args[107],
                                l->args[108], l->args[109], l->args[110], l->args[111],
                                l->args[112], l->args[113], l->args[114], l->args[115],
                                l->args[116], l->args[117], l->args[118], l->args[119],
                                l->args[120], l->args[121], l->args[122], l->args[123],
                                l->args[124], l->args[125], l->args[126], l->args[127],
                                l->args[128], l->args[129], l->args[130], l->args[131],
                                l->args[132], l->args[133], l->args[134], l->args[135],
                                l->args[136], l->args[137], l->args[138], l->args[139],
                                l->args[140], l->args[141], l->args[142], l->args[143],
                                l->args[144], l->args[145], l->args[146], l->args[147],
                                l->args[148], l->args[149], l->args[150], l->args[151],
                                l->args[152], l->args[153], l->args[154], l->args[155],
                                l->args[156], l->args[157], l->args[158], l->args[159],
                                l->args[160], l->args[161], l->args[162], l->args[163],
                                l->args[164], l->args[165], l->args[166], l->args[167],
                                l->args[168], l->args[169], l->args[170], l->args[171],
                                l->args[172], l->args[173], l->args[174], l->args[175],
                                l->args[176], l->args[177], l->args[178], l->args[179],
                                l->args[180], l->args[181], l->args[182], l->args[183],
                                l->args[184], l->args[185], l->args[186], l->args[187],
                                l->args[188], l->args[189], l->args[190], l->args[191],
                                l->args[192], l->args[193], l->args[194], l->args[195],
                                l->args[196], l->args[197], l->args[198], l->args[199],
                                l->args[200], l->args[201], l->args[202], l->args[203],
                                l->args[204], l->args[205], l->args[206], l->args[207],
                                l->args[208], l->args[209], l->args[210], l->args[211],
                                l->args[212], l->args[213], l->args[214], l->args[215],
                                l->args[216], l->args[217], l->args[218], l->args[219],
                                l->args[220], l->args[221], l->args[222], l->args[223],
                                l->args[224], l->args[225], l->args[226], l->args[227],
                                l->args[228], l->args[229], l->args[230], l->args[231],
                                l->args[232], l->args[233], l->args[234], l->args[235],
                                l->args[236], l->args[237], l->args[238], l->args[239],
                                l->args[240], l->args[241], l->args[242], l->args[243],
                                l->args[244], l->args[245], l->args[246], l->args[247],
                                l->args[248], l->args[249], l->args[250], l->args[251],
                                l->args[252], l->args[253], l->args[254], l->args[255]));
  } else
  if (l->rtype == __AVdouble) {
    *(double*)l->raddr =
      (arglen <= 8
       ? (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                 l->args[4], l->args[5], l->args[6], l->args[7])
       : arglen <= 16
       ? (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                 l->args[4], l->args[5], l->args[6], l->args[7],
                                 l->args[8], l->args[9], l->args[10], l->args[11],
                                 l->args[12], l->args[13], l->args[14], l->args[15])
       : arglen <= 32
       ? (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                 l->args[4], l->args[5], l->args[6], l->args[7],
                                 l->args[8], l->args[9], l->args[10], l->args[11],
                                 l->args[12], l->args[13], l->args[14], l->args[15],
                                 l->args[16], l->args[17], l->args[18], l->args[19],
                                 l->args[20], l->args[21], l->args[22], l->args[23],
                                 l->args[24], l->args[25], l->args[26], l->args[27],
                                 l->args[28], l->args[29], l->args[30], l->args[31])
       : arglen <= 64
       ? (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                 l->args[4], l->args[5], l->args[6], l->args[7],
                                 l->args[8], l->args[9], l->args[10], l->args[11],
                                 l->args[12], l->args[13], l->args[14], l->args[15],
                                 l->args[16], l->args[17], l->args[18], l->args[19],
                                 l->args[20], l->args[21], l->args[22], l->args[23],
                                 l->args[24], l->args[25], l->args[26], l->args[27],
                                 l->args[28], l->args[29], l->args[30], l->args[31],
                                 l->args[32], l->args[33], l->args[34], l->args[35],
                                 l->args[36], l->args[37], l->args[38], l->args[39],
                                 l->args[40], l->args[41], l->args[42], l->args[43],
                                 l->args[44], l->args[45], l->args[46], l->args[47],
                                 l->args[48], l->args[49], l->args[50], l->args[51],
                                 l->args[52], l->args[53], l->args[54], l->args[55],
                                 l->args[56], l->args[57], l->args[58], l->args[59],
                                 l->args[60], l->args[61], l->args[62], l->args[63])
       : arglen <= 128
       ? (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                 l->args[4], l->args[5], l->args[6], l->args[7],
                                 l->args[8], l->args[9], l->args[10], l->args[11],
                                 l->args[12], l->args[13], l->args[14], l->args[15],
                                 l->args[16], l->args[17], l->args[18], l->args[19],
                                 l->args[20], l->args[21], l->args[22], l->args[23],
                                 l->args[24], l->args[25], l->args[26], l->args[27],
                                 l->args[28], l->args[29], l->args[30], l->args[31],
                                 l->args[32], l->args[33], l->args[34], l->args[35],
                                 l->args[36], l->args[37], l->args[38], l->args[39],
                                 l->args[40], l->args[41], l->args[42], l->args[43],
                                 l->args[44], l->args[45], l->args[46], l->args[47],
                                 l->args[48], l->args[49], l->args[50], l->args[51],
                                 l->args[52], l->args[53], l->args[54], l->args[55],
                                 l->args[56], l->args[57], l->args[58], l->args[59],
                                 l->args[60], l->args[61], l->args[62], l->args[63],
                                 l->args[64], l->args[65], l->args[66], l->args[67],
                                 l->args[68], l->args[69], l->args[70], l->args[71],
                                 l->args[72], l->args[73], l->args[74], l->args[75],
                                 l->args[76], l->args[77], l->args[78], l->args[79],
                                 l->args[80], l->args[81], l->args[82], l->args[83],
                                 l->args[84], l->args[85], l->args[86], l->args[87],
                                 l->args[88], l->args[89], l->args[90], l->args[91],
                                 l->args[92], l->args[93], l->args[94], l->args[95],
                                 l->args[96], l->args[97], l->args[98], l->args[99],
                                 l->args[100], l->args[101], l->args[102], l->args[103],
                                 l->args[104], l->args[105], l->args[106], l->args[107],
                                 l->args[108], l->args[109], l->args[110], l->args[111],
                                 l->args[112], l->args[113], l->args[114], l->args[115],
                                 l->args[116], l->args[117], l->args[118], l->args[119],
                                 l->args[120], l->args[121], l->args[122], l->args[123],
                                 l->args[124], l->args[125], l->args[126], l->args[127])
       : /* arglen <= __AV_ALIST_WORDS = 256 */
         (*(double(*)())l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                                 l->args[4], l->args[5], l->args[6], l->args[7],
                                 l->args[8], l->args[9], l->args[10], l->args[11],
                                 l->args[12], l->args[13], l->args[14], l->args[15],
                                 l->args[16], l->args[17], l->args[18], l->args[19],
                                 l->args[20], l->args[21], l->args[22], l->args[23],
                                 l->args[24], l->args[25], l->args[26], l->args[27],
                                 l->args[28], l->args[29], l->args[30], l->args[31],
                                 l->args[32], l->args[33], l->args[34], l->args[35],
                                 l->args[36], l->args[37], l->args[38], l->args[39],
                                 l->args[40], l->args[41], l->args[42], l->args[43],
                                 l->args[44], l->args[45], l->args[46], l->args[47],
                                 l->args[48], l->args[49], l->args[50], l->args[51],
                                 l->args[52], l->args[53], l->args[54], l->args[55],
                                 l->args[56], l->args[57], l->args[58], l->args[59],
                                 l->args[60], l->args[61], l->args[62], l->args[63],
                                 l->args[64], l->args[65], l->args[66], l->args[67],
                                 l->args[68], l->args[69], l->args[70], l->args[71],
                                 l->args[72], l->args[73], l->args[74], l->args[75],
                                 l->args[76], l->args[77], l->args[78], l->args[79],
                                 l->args[80], l->args[81], l->args[82], l->args[83],
                                 l->args[84], l->args[85], l->args[86], l->args[87],
                                 l->args[88], l->args[89], l->args[90], l->args[91],
                                 l->args[92], l->args[93], l->args[94], l->args[95],
                                 l->args[96], l->args[97], l->args[98], l->args[99],
                                 l->args[100], l->args[101], l->args[102], l->args[103],
                                 l->args[104], l->args[105], l->args[106], l->args[107],
                                 l->args[108], l->args[109], l->args[110], l->args[111],
                                 l->args[112], l->args[113], l->args[114], l->args[115],
                                 l->args[116], l->args[117], l->args[118], l->args[119],
                                 l->args[120], l->args[121], l->args[122], l->args[123],
                                 l->args[124], l->args[125], l->args[126], l->args[127],
                                 l->args[128], l->args[129], l->args[130], l->args[131],
                                 l->args[132], l->args[133], l->args[134], l->args[135],
                                 l->args[136], l->args[137], l->args[138], l->args[139],
                                 l->args[140], l->args[141], l->args[142], l->args[143],
                                 l->args[144], l->args[145], l->args[146], l->args[147],
                                 l->args[148], l->args[149], l->args[150], l->args[151],
                                 l->args[152], l->args[153], l->args[154], l->args[155],
                                 l->args[156], l->args[157], l->args[158], l->args[159],
                                 l->args[160], l->args[161], l->args[162], l->args[163],
                                 l->args[164], l->args[165], l->args[166], l->args[167],
                                 l->args[168], l->args[169], l->args[170], l->args[171],
                                 l->args[172], l->args[173], l->args[174], l->args[175],
                                 l->args[176], l->args[177], l->args[178], l->args[179],
                                 l->args[180], l->args[181], l->args[182], l->args[183],
                                 l->args[184], l->args[185], l->args[186], l->args[187],
                                 l->args[188], l->args[189], l->args[190], l->args[191],
                                 l->args[192], l->args[193], l->args[194], l->args[195],
                                 l->args[196], l->args[197], l->args[198], l->args[199],
                                 l->args[200], l->args[201], l->args[202], l->args[203],
                                 l->args[204], l->args[205], l->args[206], l->args[207],
                                 l->args[208], l->args[209], l->args[210], l->args[211],
                                 l->args[212], l->args[213], l->args[214], l->args[215],
                                 l->args[216], l->args[217], l->args[218], l->args[219],
                                 l->args[220], l->args[221], l->args[222], l->args[223],
                                 l->args[224], l->args[225], l->args[226], l->args[227],
                                 l->args[228], l->args[229], l->args[230], l->args[231],
                                 l->args[232], l->args[233], l->args[234], l->args[235],
                                 l->args[236], l->args[237], l->args[238], l->args[239],
                                 l->args[240], l->args[241], l->args[242], l->args[243],
                                 l->args[244], l->args[245], l->args[246], l->args[247],
                                 l->args[248], l->args[249], l->args[250], l->args[251],
                                 l->args[252], l->args[253], l->args[254], l->args[255]));
  } else {
    iret =
      (arglen <= 8
       ? (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7])
       : arglen <= 16
       ? (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7],
                    l->args[8], l->args[9], l->args[10], l->args[11],
                    l->args[12], l->args[13], l->args[14], l->args[15])
       : arglen <= 32
       ? (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7],
                    l->args[8], l->args[9], l->args[10], l->args[11],
                    l->args[12], l->args[13], l->args[14], l->args[15],
                    l->args[16], l->args[17], l->args[18], l->args[19],
                    l->args[20], l->args[21], l->args[22], l->args[23],
                    l->args[24], l->args[25], l->args[26], l->args[27],
                    l->args[28], l->args[29], l->args[30], l->args[31])
       : arglen <= 64
       ? (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7],
                    l->args[8], l->args[9], l->args[10], l->args[11],
                    l->args[12], l->args[13], l->args[14], l->args[15],
                    l->args[16], l->args[17], l->args[18], l->args[19],
                    l->args[20], l->args[21], l->args[22], l->args[23],
                    l->args[24], l->args[25], l->args[26], l->args[27],
                    l->args[28], l->args[29], l->args[30], l->args[31],
                    l->args[32], l->args[33], l->args[34], l->args[35],
                    l->args[36], l->args[37], l->args[38], l->args[39],
                    l->args[40], l->args[41], l->args[42], l->args[43],
                    l->args[44], l->args[45], l->args[46], l->args[47],
                    l->args[48], l->args[49], l->args[50], l->args[51],
                    l->args[52], l->args[53], l->args[54], l->args[55],
                    l->args[56], l->args[57], l->args[58], l->args[59],
                    l->args[60], l->args[61], l->args[62], l->args[63])
       : arglen <= 128
       ? (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7],
                    l->args[8], l->args[9], l->args[10], l->args[11],
                    l->args[12], l->args[13], l->args[14], l->args[15],
                    l->args[16], l->args[17], l->args[18], l->args[19],
                    l->args[20], l->args[21], l->args[22], l->args[23],
                    l->args[24], l->args[25], l->args[26], l->args[27],
                    l->args[28], l->args[29], l->args[30], l->args[31],
                    l->args[32], l->args[33], l->args[34], l->args[35],
                    l->args[36], l->args[37], l->args[38], l->args[39],
                    l->args[40], l->args[41], l->args[42], l->args[43],
                    l->args[44], l->args[45], l->args[46], l->args[47],
                    l->args[48], l->args[49], l->args[50], l->args[51],
                    l->args[52], l->args[53], l->args[54], l->args[55],
                    l->args[56], l->args[57], l->args[58], l->args[59],
                    l->args[60], l->args[61], l->args[62], l->args[63],
                    l->args[64], l->args[65], l->args[66], l->args[67],
                    l->args[68], l->args[69], l->args[70], l->args[71],
                    l->args[72], l->args[73], l->args[74], l->args[75],
                    l->args[76], l->args[77], l->args[78], l->args[79],
                    l->args[80], l->args[81], l->args[82], l->args[83],
                    l->args[84], l->args[85], l->args[86], l->args[87],
                    l->args[88], l->args[89], l->args[90], l->args[91],
                    l->args[92], l->args[93], l->args[94], l->args[95],
                    l->args[96], l->args[97], l->args[98], l->args[99],
                    l->args[100], l->args[101], l->args[102], l->args[103],
                    l->args[104], l->args[105], l->args[106], l->args[107],
                    l->args[108], l->args[109], l->args[110], l->args[111],
                    l->args[112], l->args[113], l->args[114], l->args[115],
                    l->args[116], l->args[117], l->args[118], l->args[119],
                    l->args[120], l->args[121], l->args[122], l->args[123],
                    l->args[124], l->args[125], l->args[126], l->args[127])
       : /* arglen <= __AV_ALIST_WORDS = 256 */
         (*l->func)(l->args[0], l->args[1], l->args[2], l->args[3],
                    l->args[4], l->args[5], l->args[6], l->args[7],
                    l->args[8], l->args[9], l->args[10], l->args[11],
                    l->args[12], l->args[13], l->args[14], l->args[15],
                    l->args[16], l->args[17], l->args[18], l->args[19],
                    l->args[20], l->args[21], l->args[22], l->args[23],
                    l->args[24], l->args[25], l->args[26], l->args[27],
                    l->args[28], l->args[29], l->args[30], l->args[31],
                    l->args[32], l->args[33], l->args[34], l->args[35],
                    l->args[36], l->args[37], l->args[38], l->args[39],
                    l->args[40], l->args[41], l->args[42], l->args[43],
                    l->args[44], l->args[45], l->args[46], l->args[47],
                    l->args[48], l->args[49], l->args[50], l->args[51],
                    l->args[52], l->args[53], l->args[54], l->args[55],
                    l->args[56], l->args[57], l->args[58], l->args[59],
                    l->args[60], l->args[61], l->args[62], l->args[63],
                    l->args[64], l->args[65], l->args[66], l->args[67],
                    l->args[68], l->args[69], l->args[70], l->args[71],
                    l->args[72], l->args[73], l->args[74], l->args[75],
                    l->args[76], l->args[77], l->args[78], l->args[79],
                    l->args[80], l->args[81], l->args[82], l->args[83],
                    l->args[84], l->args[85], l->args[86], l->args[87],
                    l->args[88], l->args[89], l->args[90], l->args[91],
                    l->args[92], l->args[93], l->args[94], l->args[95],
                    l->args[96], l->args[97], l->args[98], l->args[99],
                    l->args[100], l->args[101], l->args[102], l->args[103],
                    l->args[104], l->args[105], l->args[106], l->args[107],
                    l->args[108], l->args[109], l->args[110], l->args[111],
                    l->args[112], l->args[113], l->args[114], l->args[115],
                    l->args[116], l->args[117], l->args[118], l->args[119],
                    l->args[120], l->args[121], l->args[122], l->args[123],
                    l->args[124], l->args[125], l->args[126], l->args[127],
                    l->args[128], l->args[129], l->args[130], l->args[131],
                    l->args[132], l->args[133], l->args[134], l->args[135],
                    l->args[136], l->args[137], l->args[138], l->args[139],
                    l->args[140], l->args[141], l->args[142], l->args[143],
                    l->args[144], l->args[145], l->args[146], l->args[147],
                    l->args[148], l->args[149], l->args[150], l->args[151],
                    l->args[152], l->args[153], l->args[154], l->args[155],
                    l->args[156], l->args[157], l->args[158], l->args[159],
                    l->args[160], l->args[161], l->args[162], l->args[163],
                    l->args[164], l->args[165], l->args[166], l->args[167],
                    l->args[168], l->args[169], l->args[170], l->args[171],
                    l->args[172], l->args[173], l->args[174], l->args[175],
                    l->args[176], l->args[177], l->args[178], l->args[179],
                    l->args[180], l->args[181], l->args[182], l->args[183],
                    l->args[184], l->args[185], l->args[186], l->args[187],
                    l->args[188], l->args[189], l->args[190], l->args[191],
                    l->args[192], l->args[193], l->args[194], l->args[195],
                    l->args[196], l->args[197], l->args[198], l->args[199],
                    l->args[200], l->args[201], l->args[202], l->args[203],
                    l->args[204], l->args[205], l->args[206], l->args[207],
                    l->args[208], l->args[209], l->args[210], l->args[211],
                    l->args[212], l->args[213], l->args[214], l->args[215],
                    l->args[216], l->args[217], l->args[218], l->args[219],
                    l->args[220], l->args[221], l->args[222], l->args[223],
                    l->args[224], l->args[225], l->args[226], l->args[227],
                    l->args[228], l->args[229], l->args[230], l->args[231],
                    l->args[232], l->args[233], l->args[234], l->args[235],
                    l->args[236], l->args[237], l->args[238], l->args[239],
                    l->args[240], l->args[241], l->args[242], l->args[243],
                    l->args[244], l->args[245], l->args[246], l->args[247],
                    l->args[248], l->args[249], l->args[250], l->args[251],
                    l->args[252], l->args[253], l->args[254], l->args[255]));

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
        /* Return structs of size <= 32 in registers. */
        if (l->rsize > 0 && l->rsize <= 32) {
          void* raddr = l->raddr;
          #if 0 /* Unoptimized */
          if (l->rsize >= 1)
            ((unsigned char *)raddr)[0] = (unsigned char)(iret);
          if (l->rsize >= 2)
            ((unsigned char *)raddr)[1] = (unsigned char)(iret>>8);
          if (l->rsize >= 3)
            ((unsigned char *)raddr)[2] = (unsigned char)(iret>>16);
          if (l->rsize >= 4)
            ((unsigned char *)raddr)[3] = (unsigned char)(iret>>24);
          if (l->rsize >= 5)
            ((unsigned char *)raddr)[4] = (unsigned char)(iret>>32);
          if (l->rsize >= 6)
            ((unsigned char *)raddr)[5] = (unsigned char)(iret>>40);
          if (l->rsize >= 7)
            ((unsigned char *)raddr)[6] = (unsigned char)(iret>>48);
          if (l->rsize >= 8)
            ((unsigned char *)raddr)[7] = (unsigned char)(iret>>56);
          if (l->rsize >= 9) {
            ((unsigned char *)raddr)[8] = (unsigned char)(iret2);
            if (l->rsize >= 10)
              ((unsigned char *)raddr)[9] = (unsigned char)(iret2>>8);
            if (l->rsize >= 11)
              ((unsigned char *)raddr)[10] = (unsigned char)(iret2>>16);
            if (l->rsize >= 12)
              ((unsigned char *)raddr)[11] = (unsigned char)(iret2>>24);
            if (l->rsize >= 13)
              ((unsigned char *)raddr)[12] = (unsigned char)(iret2>>32);
            if (l->rsize >= 14)
              ((unsigned char *)raddr)[13] = (unsigned char)(iret2>>40);
            if (l->rsize >= 15)
              ((unsigned char *)raddr)[14] = (unsigned char)(iret2>>48);
            if (l->rsize >= 16)
              ((unsigned char *)raddr)[15] = (unsigned char)(iret2>>56);
            if (l->rsize >= 17) {
              ((unsigned char *)raddr)[16] = (unsigned char)(iret3);
              if (l->rsize >= 18)
                ((unsigned char *)raddr)[17] = (unsigned char)(iret3>>8);
              if (l->rsize >= 19)
                ((unsigned char *)raddr)[18] = (unsigned char)(iret3>>16);
              if (l->rsize >= 20)
                ((unsigned char *)raddr)[19] = (unsigned char)(iret3>>24);
              if (l->rsize >= 21)
                ((unsigned char *)raddr)[20] = (unsigned char)(iret3>>32);
              if (l->rsize >= 22)
                ((unsigned char *)raddr)[21] = (unsigned char)(iret3>>40);
              if (l->rsize >= 23)
                ((unsigned char *)raddr)[22] = (unsigned char)(iret3>>48);
              if (l->rsize >= 24)
                ((unsigned char *)raddr)[23] = (unsigned char)(iret3>>56);
              if (l->rsize >= 25) {
                ((unsigned char *)raddr)[24] = (unsigned char)(iret4);
                if (l->rsize >= 26)
                  ((unsigned char *)raddr)[25] = (unsigned char)(iret4>>8);
                if (l->rsize >= 27)
                  ((unsigned char *)raddr)[26] = (unsigned char)(iret4>>16);
                if (l->rsize >= 28)
                  ((unsigned char *)raddr)[27] = (unsigned char)(iret4>>24);
                if (l->rsize >= 29)
                  ((unsigned char *)raddr)[28] = (unsigned char)(iret4>>32);
                if (l->rsize >= 30)
                  ((unsigned char *)raddr)[29] = (unsigned char)(iret4>>40);
                if (l->rsize >= 31)
                  ((unsigned char *)raddr)[30] = (unsigned char)(iret4>>48);
                if (l->rsize >= 32)
                  ((unsigned char *)raddr)[31] = (unsigned char)(iret4>>56);
              }
            }
          }
          #else /* Optimized: fewer conditional jumps, fewer memory accesses */
          uintptr_t count = l->rsize; /* > 0, ≤ 4*sizeof(__avrword) */
          __avrword* wordaddr = (__avrword*)((uintptr_t)raddr & ~(uintptr_t)(sizeof(__avrword)-1));
          uintptr_t start_offset = (uintptr_t)raddr & (uintptr_t)(sizeof(__avrword)-1); /* ≥ 0, < sizeof(__avrword) */
          uintptr_t end_offset = start_offset + count; /* > 0, < 5*sizeof(__avrword) */
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
          } else if (count <= 2*sizeof(__avrword)) {
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
          } else if (count <= 3*sizeof(__avrword)) {
            /* Use iret, iret2, iret3. */
            __avrword mask0 = - ((__avrword)1 << (start_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            if (end_offset <= 3*sizeof(__avrword)) {
              /* 2*sizeof(__avrword) < end_offset ≤ 3*sizeof(__avrword) */
              __avrword mask2 = ((__avrword)2 << (end_offset*8-sizeof(__avrword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avrword)*4-start_offset*4) >> (sizeof(__avrword)*4-start_offset*4)) | (iret2 << (start_offset*8));
              wordaddr[2] ^= (wordaddr[2] ^ ((iret2 >> (sizeof(__avrword)*4-start_offset*4) >> (sizeof(__avrword)*4-start_offset*4)) | (iret3 << (start_offset*8)))) & mask2;
            } else {
              /* 3*sizeof(__avrword) < end_offset < 4*sizeof(__avrword), start_offset > 0 */
              __avrword mask3 = ((__avrword)2 << (end_offset*8-2*sizeof(__avrword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avrword)*8-start_offset*8)) | (iret2 << (start_offset*8));
              wordaddr[2] = (iret2 >> (sizeof(__avrword)*8-start_offset*8)) | (iret3 << (start_offset*8));
              wordaddr[3] ^= (wordaddr[3] ^ (iret3 >> (sizeof(__avrword)*8-start_offset*8))) & mask3;
            }
          } else {
            /* Use iret, iret2, iret3, iret4. */
            __avrword mask0 = - ((__avrword)1 << (start_offset*8));
            wordaddr[0] ^= (wordaddr[0] ^ (iret << (start_offset*8))) & mask0;
            if (end_offset <= 4*sizeof(__avrword)) {
              /* 3*sizeof(__avrword) < end_offset ≤ 4*sizeof(__avrword) */
              __avrword mask3 = ((__avrword)2 << (end_offset*8-sizeof(__avrword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avrword)*4-start_offset*4) >> (sizeof(__avrword)*4-start_offset*4)) | (iret2 << (start_offset*8));
              wordaddr[2] = (iret2 >> (sizeof(__avrword)*4-start_offset*4) >> (sizeof(__avrword)*4-start_offset*4)) | (iret3 << (start_offset*8));
              wordaddr[3] ^= (wordaddr[3] ^ ((iret >> (sizeof(__avrword)*4-start_offset*4) >> (sizeof(__avrword)*4-start_offset*4)) | (iret2 << (start_offset*8)))) & mask3;
            } else {
              /* 4*sizeof(__avrword) < end_offset < 5*sizeof(__avrword), start_offset > 0 */
              __avrword mask4 = ((__avrword)2 << (end_offset*8-2*sizeof(__avrword)*8-1)) - 1;
              wordaddr[1] = (iret >> (sizeof(__avrword)*8-start_offset*8)) | (iret2 << (start_offset*8));
              wordaddr[2] = (iret2 >> (sizeof(__avrword)*8-start_offset*8)) | (iret3 << (start_offset*8));
              wordaddr[3] = (iret3 >> (sizeof(__avrword)*8-start_offset*8)) | (iret4 << (start_offset*8));
              wordaddr[4] ^= (wordaddr[4] ^ (iret4 >> (sizeof(__avrword)*8-start_offset*8))) & mask4;
            }
          }
          #endif
        }
      }
    }
  }
  return 0;
}
