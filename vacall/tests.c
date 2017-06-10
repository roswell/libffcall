/* Some random tests for vacall. */

/*
 * Copyright 1993 Bill Triggs <Bill.Triggs@inrialpes.fr>
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

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vacall.h"
FILE* out;

#if defined(__hppa__) && defined(__GNUC__)
#if (__GNUC__ == 2 && __GNUC_MINOR__ < 6)
/* gcc-2.5.2 bugs prevent the T test from working. */
#define SKIP_T
#endif
#endif
#if defined(__m68k__) && defined(sun) && !defined(__GNUC__)
/* A SunOS 4.0.3 cc bug is triggered by the va_arg_struct macro. */
#define SKIP_STRUCTS
#endif
#if defined(__m68k__) && defined(__GNUC__)
/* "gcc-2.6.3 -freg-struct-return" returns  T = struct { char c[3]; }  (which
 * has size 4 !) in memory, in contrast to  struct { char a,b,c; }  and
 * struct { char c[4]; }  and  struct { char a,b,c,d; }  which have the same
 * size and the same alignment but are returned in registers. I don't know why.
 */
#define SKIP_T
#endif
#if defined(__i386__) && defined(__GNUC__)
#if (__GNUC__ == 2) && (__GNUC_MINOR__ == 7)
/* Problem with gcc-2.7.x on Linux/ELF: The X test fails.
 * The calling convention for C functions returning structures of size > 8 bytes
 * apparently has changed between gcc-2.6.3 and gcc-2.7 (all i386 platforms),
 * and vacall supports only the old one. Since gcc-2.8 will switch back to
 * gcc-2.6.3's calling convention, I won't change libffcall/vacall for this.
 * Just hide the problem by not running the test. The impact isn't big for
 * CLISP: Callbacks returning structures > 8 bytes won't work.
 */
#define SKIP_X
#endif
#endif
#if defined(__sparc__) && defined(sun) && defined(__SUNPRO_C) /* SUNWspro cc */
/* SunPRO cc miscompiles the simulator function for X_BcdB: d.i[1] is
 * temporarily stored in %l2 and put onto the stack from %l2, but in between
 * the copy of X has used %l2 as a counter without saving and restoring its
 * value.
 */
#define SKIP_X
#endif
#if defined(__mipsn32__) && !defined(__GNUC__)
/* The X test crashes for an unknown reason. */
#define SKIP_X
#endif

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int
#define ulong unsigned long

typedef struct { char x; } Char;
typedef struct { short x; } Short;
typedef struct { int x; } Int;
typedef struct { long x; } Long;
typedef struct { float x; } Float;
typedef struct { double x; } Double;
typedef struct { char c; float f; } A;
typedef struct { double d; int i[3]; } B;
typedef struct { long l1; long l2; } J;
typedef struct { long l1; long l2; long l3; long l4; } K;
typedef struct { char x1; } Size1;
typedef struct { char x1; char x2; } Size2;
typedef struct { char x1; char x2; char x3; } Size3;
typedef struct { char x1; char x2; char x3; char x4; } Size4;
typedef struct {
  char x1; char x2; char x3; char x4; char x5; char x6; char x7;
} Size7;
typedef struct {
  char x1; char x2; char x3; char x4; char x5; char x6; char x7; char x8;
} Size8;
typedef struct {
  char x1; char x2; char x3; char x4; char x5; char x6; char x7; char x8;
  char x9; char x10; char x11; char x12;
} Size12;
typedef struct {
  char x1; char x2; char x3; char x4; char x5; char x6; char x7; char x8;
  char x9; char x10; char x11; char x12; char x13; char x14; char x15;
} Size15;
typedef struct {
  char x1; char x2; char x3; char x4; char x5; char x6; char x7; char x8;
  char x9; char x10; char x11; char x12; char x13; char x14; char x15; char x16;
} Size16;
typedef struct { char c[3]; } T;
typedef struct { char c[33],c1; } X;

char c1='a', c2=127, c3=(char)128, c4=(char)255, c5=-1;
short s1=32767, s2=(short)32768, s3=3, s4=4, s5=5, s6=6, s7=7, s8=8, s9=9;
int i1=1, i2=2, i3=3, i4=4, i5=5, i6=6, i7=7, i8=8, i9=9,
    i10=11, i11=12, i12=13, i13=14, i14=15, i15=16, i16=17;
long l1=1, l2=2, l3=3, l4=4, l5=5, l6=6, l7=7, l8=8, l9=9;
#ifdef HAVE_LONG_LONG_INT
long long ll1 = 3875056143130689530LL;
#endif
float f1=0.1, f2=0.2, f3=0.3, f4=0.4, f5=0.5, f6=0.6, f7=0.7, f8=0.8, f9=0.9,
      f10=1.1, f11=1.2, f12=1.3, f13=1.4, f14=1.5, f15=1.6, f16=1.7, f17=1.8,
      f18=1.9, f19=2.1, f20=2.2, f21=2.3, f22=2.4, f23=2.5, f24=2.6;
double d1=0.1, d2=0.2, d3=0.3, d4=0.4, d5=0.5, d6=0.6, d7=0.7, d8=0.8, d9=0.9,
       d10=1.1, d11=1.2, d12=1.3, d13=1.4, d14=1.5, d15=1.6, d16=1.7;

uchar uc1='a', uc2=127, uc3=128, uc4=255, uc5=(uchar)-1;
ushort us1=1, us2=2, us3=3, us4=4, us5=5, us6=6, us7=7, us8=8, us9=9;
uint ui1=1, ui2=2, ui3=3, ui4=4, ui5=5, ui6=6, ui7=7, ui8=8, ui9=9;
ulong ul1=1, ul2=2, ul3=3, ul4=4, ul5=5, ul6=6, ul7=7, ul8=8, ul9=9;

char *str1="hello",str2[]="goodbye",*str3="still here?";
Char C1={'A'}, C2={'B'}, C3={'C'}, C4={'\377'}, C5={-1};
Short S1={1}, S2={2}, S3={3}, S4={4}, S5={5}, S6={6}, S7={7}, S8={8}, S9={9};
Int I1={1}, I2={2}, I3={3}, I4={4}, I5={5}, I6={6}, I7={7}, I8={8}, I9={9};
Float F1={0.1}, F2={0.2}, F3={0.3}, F4={0.4}, F5={0.5}, F6={0.6}, F7={0.7}, F8={0.8}, F9={0.9};
Double D1={0.1}, D2={0.2}, D3={0.3}, D4={0.4}, D5={0.5}, D6={0.6}, D7={0.7}, D8={0.8}, D9={0.9};

A A1={'a',0.1},A2={'b',0.2},A3={'\377',0.3};
B B1={0.1,{1,2,3}},B2={0.2,{5,4,3}};
J J1={47,11},J2={73,55};
K K1={19,69,12,28};
Size1 Size1_1={'a'};
Size2 Size2_1={'a','b'};
Size3 Size3_1={'a','b','c'};
Size4 Size4_1={'a','b','c','d'};
Size7 Size7_1={'a','b','c','d','e','f','g'};
Size8 Size8_1={'a','b','c','d','e','f','g','h'};
Size12 Size12_1={'a','b','c','d','e','f','g','h','i','j','k','l'};
Size15 Size15_1={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o'};
Size16 Size16_1={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
T T1={'t','h','e'},T2={'f','o','x'};
X X1={"abcdefghijklmnopqrstuvwxyzABCDEF",'G'}, X2={"123",'9'}, X3={"return-return-return",'R'};

/* void tests */
void v_v (void)
{
  fprintf(out,"void f(void):\n");
  fflush(out);
}

/* int tests */
int i_v (void)
{
  int r=99;
  fprintf(out,"int f(void):");
  fflush(out);
  return r;
}
int i_i (int a)
{
  int r=a+1;
  fprintf(out,"int f(int):(%d)",a);
  fflush(out);
  return r;
}
int i_i2 (int a, int b)
{
  int r=a+b;
  fprintf(out,"int f(2*int):(%d,%d)",a,b);
  fflush(out);
  return r;
}
int i_i4 (int a, int b, int c, int d)
{
  int r=a+b+c+d;
  fprintf(out,"int f(4*int):(%d,%d,%d,%d)",a,b,c,d);
  fflush(out);
  return r;
}
int i_i8 (int a, int b, int c, int d, int e, int f, int g, int h)
{
  int r=a+b+c+d+e+f+g+h;
  fprintf(out,"int f(8*int):(%d,%d,%d,%d,%d,%d,%d,%d)",a,b,c,d,e,f,g,h);
  fflush(out);
  return r;
}
int i_i16 (int a, int b, int c, int d, int e, int f, int g, int h,
           int i, int j, int k, int l, int m, int n, int o, int p)
{
  int r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"int f(16*int):(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
          a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  return r;
}

/* float tests */
float f_f (float a)
{
  float r=a+1.0;
  fprintf(out,"float f(float):(%g)",a);
  fflush(out);
  return r;
}
float f_f2 (float a, float b)
{
  float r=a+b;
  fprintf(out,"float f(2*float):(%g,%g)",a,b);
  fflush(out);
  return r;
}
float f_f4 (float a, float b, float c, float d)
{
  float r=a+b+c+d;
  fprintf(out,"float f(4*float):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  return r;
}
float f_f8 (float a, float b, float c, float d, float e, float f,
            float g, float h)
{
  float r=a+b+c+d+e+f+g+h;
  fprintf(out,"float f(8*float):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  return r;
}
float f_f16 (float a, float b, float c, float d, float e, float f, float g, float h,
             float i, float j, float k, float l, float m, float n, float o, float p)
{
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"float f(16*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  return r;
}
float f_f24 (float a, float b, float c, float d, float e, float f, float g, float h,
             float i, float j, float k, float l, float m, float n, float o, float p,
             float q, float s, float t, float u, float v, float w, float x, float y)
{
  float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+s+t+u+v+w+x+y;
  fprintf(out,"float f(24*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,u,v,w,x,y);
  fflush(out);
  return r;
}

/* double tests */
double d_d (double a)
{
  double r=a+1.0;
  fprintf(out,"double f(double):(%g)",a);
  fflush(out);
  return r;
}
double d_d2 (double a, double b)
{
  double r=a+b;
  fprintf(out,"double f(2*double):(%g,%g)",a,b);
  fflush(out);
  return r;
}
double d_d4 (double a, double b, double c, double d)
{
  double r=a+b+c+d;
  fprintf(out,"double f(4*double):(%g,%g,%g,%g)",a,b,c,d);
  fflush(out);
  return r;
}
double d_d8 (double a, double b, double c, double d, double e, double f,
             double g, double h)
{
  double r=a+b+c+d+e+f+g+h;
  fprintf(out,"double f(8*double):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
  fflush(out);
  return r;
}
double d_d16 (double a, double b, double c, double d, double e, double f,
              double g, double h, double i, double j, double k, double l,
              double m, double n, double o, double p)
{
  double r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
  fprintf(out,"double f(16*double):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
  fflush(out);
  return r;
}

/* pointer tests */
void* vp_vpdpcpsp (void* a, double* b, char* c, Int* d)
{
  void* ret = (char*)b + 1;
  fprintf(out,"void* f(void*,double*,char*,Int*):(0x%lx,0x%lx,0x%lx,0x%lx)",(long)a,(long)b,(long)c,(long)d);
  fflush(out);
  return ret;
}

/* mixed number tests */
uchar uc_ucsil (uchar a, ushort b, uint c, ulong d)
{
  uchar r = (uchar)-1;
  fprintf(out,"uchar f(uchar,ushort,uint,ulong):(%u,%u,%u,%lu)",a,b,c,d);
  fflush(out);
  return r;
}
double d_iidd (int a, int b, double c, double d)
{
  double r = a+b+c+d;
  fprintf(out,"double f(int,int,double,double):(%d,%d,%g,%g)",a,b,c,d);
  fflush(out);
  return r;
}
double d_iiidi (int a, int b, int c, double d, int e)
{
  double r = a+b+c+d+e;
  fprintf(out,"double f(int,int,int,double,int):(%d,%d,%d,%g,%d)",a,b,c,d,e);
  fflush(out);
  return r;
}
double d_idid (int a, double b, int c, double d)
{
  double r = a+b+c+d;
  fprintf(out,"double f(int,double,int,double):(%d,%g,%d,%g)",a,b,c,d);
  fflush(out);
  return r;
}
double d_fdi (float a, double b, int c)
{
  double r = a+b+c;
  fprintf(out,"double f(float,double,int):(%g,%g,%d)",a,b,c);
  fflush(out);
  return r;
}
ushort us_cdcd (char a, double b, char c, double d)
{
  ushort r = (ushort)(a + b + c + d);
  fprintf(out,"ushort f(char,double,char,double):('%c',%g,'%c',%g)",a,b,c,d);
  fflush(out);
  return r;
}

#ifdef HAVE_LONG_LONG_INT
long long ll_iiilli (int a, int b, int c, long long d, int e)
{
  long long r = (long long)(int)a+(long long)(int)b+(long long)(int)c+d+(long long)(int)e;
  fprintf(out,"long long f(int,int,int,long long,int):(%d,%d,%d,0x%lx%08lx,%d)",a,b,c,(long)(d>>32),(long)(d&0xffffffff),e);
  fflush(out);
  return r;
}
long long ll_flli (float a, long long b, int c)
{
  long long r = (long long)(int)a + b + (long long)c;
  fprintf(out,"long long f(float,long long,int):(%g,0x%lx%08lx,0x%lx)",a,(long)(b>>32),(long)(b&0xffffffff),(long)c);
  fflush(out);
  return r;
}
#endif

/* small structure return tests */
Size1 S1_v (void)
{
  fprintf(out,"Size1 f(void):");
  fflush(out);
  return Size1_1;
}
Size2 S2_v (void)
{
  fprintf(out,"Size2 f(void):");
  fflush(out);
  return Size2_1;
}
Size3 S3_v (void)
{
  fprintf(out,"Size3 f(void):");
  fflush(out);
  return Size3_1;
}
Size4 S4_v (void)
{
  fprintf(out,"Size4 f(void):");
  fflush(out);
  return Size4_1;
}
Size7 S7_v (void)
{
  fprintf(out,"Size7 f(void):");
  fflush(out);
  return Size7_1;
}
Size8 S8_v (void)
{
  fprintf(out,"Size8 f(void):");
  fflush(out);
  return Size8_1;
}
Size12 S12_v (void)
{
  fprintf(out,"Size12 f(void):");
  fflush(out);
  return Size12_1;
}
Size15 S15_v (void)
{
  fprintf(out,"Size15 f(void):");
  fflush(out);
  return Size15_1;
}
Size16 S16_v (void)
{
  fprintf(out,"Size16 f(void):");
  fflush(out);
  return Size16_1;
}

/* structure tests */
Int I_III (Int a, Int b, Int c)
{
  Int r;
  r.x = a.x + b.x + c.x;
  fprintf(out,"Int f(Int,Int,Int):({%d},{%d},{%d})",a.x,b.x,c.x);
  fflush(out);
  return r;
}
Char C_CdC (Char a, double b, Char c)
{
  Char r;
  r.x = (a.x + c.x)/2;
  fprintf(out,"Char f(Char,double,Char):({'%c'},%g,{'%c'})",a.x,b,c.x);
  fflush(out);
  return r;
}
Float F_Ffd (Float a, float b, double c)
{
  Float r;
  r.x = a.x + b + c;
  fprintf(out,"Float f(Float,float,double):({%g},%g,%g)",a.x,b,c);
  fflush(out);
  return r;
}
Double D_fDd (float a, Double b, double c)
{
  Double r;
  r.x = a + b.x + c;
  fprintf(out,"Double f(float,Double,double):(%g,{%g},%g)",a,b.x,c);
  fflush(out);
  return r;
}
Double D_Dfd (Double a, float b, double c)
{
  Double r;
  r.x = a.x + b + c;
  fprintf(out,"Double f(Double,float,double):({%g},%g,%g)",a.x,b,c);
  fflush(out);
  return r;
}
J J_JiJ (J a, int b, J c)
{
  J r;
  r.l1 = a.l1+c.l1; r.l2 = a.l2+b+c.l2;
  fprintf(out,"J f(J,int,J):({%ld,%ld},%d,{%ld,%ld})",a.l1,a.l2,b,c.l1,c.l2);
  fflush(out);
  return r;
}
T T_TcT (T a, char b, T c)
{
  T r;
  r.c[0]='b'; r.c[1]=c.c[1]; r.c[2]=c.c[2];
  fprintf(out,"T f(T,char,T):({\"%c%c%c\"},'%c',{\"%c%c%c\"})",a.c[0],a.c[1],a.c[2],b,c.c[0],c.c[1],c.c[2]);
  fflush(out);
  return r;
}
X X_BcdB (B a, char b, double c, B d)
{
  static X xr={"return val",'R'};
  X r;
  r = xr;
  r.c1 = b;
  fprintf(out,"X f(B,char,double,B):({%g,{%d,%d,%d}},'%c',%g,{%g,{%d,%d,%d}})",
          a.d,a.i[0],a.i[1],a.i[2],b,c,d.d,d.i[0],d.i[1],d.i[2]);
  fflush(out);
  return r;
}

/* Test for cases where some argument (especially structure, 'long long', or
   'double') may be passed partially in general-purpose argument registers
   and partially on the stack. Different ABIs pass between 4 and 8 arguments
   (or none) in general-purpose argument registers. */

long l_l0K (K b, long c)
{
  long r = b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(K,long):(%ld,%ld,%ld,%ld,%ld)",b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}
long l_l1K (long a1, K b, long c)
{
  long r = a1 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld)",a1,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}
long l_l2K (long a1, long a2, K b, long c)
{
  long r = a1 + a2 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(2*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}
long l_l3K (long a1, long a2, long a3, K b, long c)
{
  long r = a1 + a2 + a3 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(3*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}
long l_l4K (long a1, long a2, long a3, long a4, K b, long c)
{
  long r = a1 + a2 + a3 + a4 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(4*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}
long l_l5K (long a1, long a2, long a3, long a4, long a5, K b, long c)
{
  long r = a1 + a2 + a3 + a4 + a5 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(5*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,a5,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}
long l_l6K (long a1, long a2, long a3, long a4, long a5, long a6, K b, long c)
{
  long r = a1 + a2 + a3 + a4 + a5 + a6 + b.l1 + b.l2 + b.l3 + b.l4 + c;
  fprintf(out,"long f(6*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,a5,a6,b.l1,b.l2,b.l3,b.l4,c);
  fflush(out);
  return r;
}

#ifdef HAVE_LONG_LONG_INT
long long ll_l2ll (long a1, long a2, long long b, long c)
{
  long long r = (long long) (a1 + a2) + b + c;
  fprintf(out,"long long f(2*long,long long,long):(%ld,%ld,0x%lx%08lx,%ld)",a1,a2,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  return r;
}
long long ll_l3ll (long a1, long a2, long a3, long long b, long c)
{
  long long r = (long long) (a1 + a2 + a3) + b + c;
  fprintf(out,"long long f(3*long,long long,long):(%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  return r;
}
long long ll_l4ll (long a1, long a2, long a3, long a4, long long b, long c)
{
  long long r = (long long) (a1 + a2 + a3 + a4) + b + c;
  fprintf(out,"long long f(4*long,long long,long):(%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  return r;
}
long long ll_l5ll (long a1, long a2, long a3, long a4, long a5, long long b, long c)
{
  long long r = (long long) (a1 + a2 + a3 + a4 + a5) + b + c;
  fprintf(out,"long long f(5*long,long long,long):(%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  return r;
}
long long ll_l6ll (long a1, long a2, long a3, long a4, long a5, long a6, long long b, long c)
{
  long long r = (long long) (a1 + a2 + a3 + a4 + a5 + a6) + b + c;
  fprintf(out,"long long f(6*long,long long,long):(%ld,%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,a6,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  return r;
}
long long ll_l7ll (long a1, long a2, long a3, long a4, long a5, long a6, long a7, long long b, long c)
{
  long long r = (long long) (a1 + a2 + a3 + a4 + a5 + a6 + a7) + b + c;
  fprintf(out,"long long f(7*long,long long,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,a6,a7,(long)(b>>32),(long)(b&0xffffffff),c);
  fflush(out);
  return r;
}
#endif

double d_l2d (long a1, long a2, double b, long c)
{
  double r = (double) (a1 + a2) + b + c;
  fprintf(out,"double f(2*long,double,long):(%ld,%ld,%g,%ld)",a1,a2,b,c);
  fflush(out);
  return r;
}
double d_l3d (long a1, long a2, long a3, double b, long c)
{
  double r = (double) (a1 + a2 + a3) + b + c;
  fprintf(out,"double f(3*long,double,long):(%ld,%ld,%ld,%g,%ld)",a1,a2,a3,b,c);
  fflush(out);
  return r;
}
double d_l4d (long a1, long a2, long a3, long a4, double b, long c)
{
  double r = (double) (a1 + a2 + a3 + a4) + b + c;
  fprintf(out,"double f(4*long,double,long):(%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,b,c);
  fflush(out);
  return r;
}
double d_l5d (long a1, long a2, long a3, long a4, long a5, double b, long c)
{
  double r = (double) (a1 + a2 + a3 + a4 + a5) + b + c;
  fprintf(out,"double f(5*long,double,long):(%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,b,c);
  fflush(out);
  return r;
}
double d_l6d (long a1, long a2, long a3, long a4, long a5, long a6, double b, long c)
{
  double r = (double) (a1 + a2 + a3 + a4 + a5 + a6) + b + c;
  fprintf(out,"double f(6*long,double,long):(%ld,%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,a6,b,c);
  fflush(out);
  return r;
}
double d_l7d (long a1, long a2, long a3, long a4, long a5, long a6, long a7, double b, long c)
{
  double r = (double) (a1 + a2 + a3 + a4 + a5 + a6 + a7) + b + c;
  fprintf(out,"double f(7*long,double,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,a6,a7,b,c);
  fflush(out);
  return r;
}


void* current_function;

/* This function simulates the behaviour of current_function. */
void simulator (va_alist alist)
{
  /* void tests */
  if (current_function == (void*)&v_v)
    {
      va_start_void(alist);
      fprintf(out,"void f(void):\n");
      fflush(out);
      va_return_void(alist);
    }

  /* int tests */
  else if (current_function == (void*)&i_v)
    {
      va_start_int(alist);
     {int r=99;
      fprintf(out,"int f(void):");
      fflush(out);
      va_return_int(alist, r);
    }}
  else if (current_function == (void*)&i_i)
    {
      va_start_int(alist);
     {int a = va_arg_int(alist);
      int r=a+1;
      fprintf(out,"int f(int):(%d)",a);
      fflush(out);
      va_return_int(alist, r);
    }}
  else if (current_function == (void*)&i_i2)
    {
      va_start_int(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      int r=a+b;
      fprintf(out,"int f(2*int):(%d,%d)",a,b);
      fflush(out);
      va_return_int(alist, r);
    }}
  else if (current_function == (void*)&i_i4)
    {
      va_start_int(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      int c = va_arg_int(alist);
      int d = va_arg_int(alist);
      int r=a+b+c+d;
      fprintf(out,"int f(4*int):(%d,%d,%d,%d)",a,b,c,d);
      fflush(out);
      va_return_int(alist, r);
    }}
  else if (current_function == (void*)&i_i8)
    {
      va_start_int(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      int c = va_arg_int(alist);
      int d = va_arg_int(alist);
      int e = va_arg_int(alist);
      int f = va_arg_int(alist);
      int g = va_arg_int(alist);
      int h = va_arg_int(alist);
      int r=a+b+c+d+e+f+g+h;
      fprintf(out,"int f(8*int):(%d,%d,%d,%d,%d,%d,%d,%d)",a,b,c,d,e,f,g,h);
      fflush(out);
      va_return_int(alist, r);
    }}
  else if (current_function == (void*)&i_i16)
    {
      va_start_int(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      int c = va_arg_int(alist);
      int d = va_arg_int(alist);
      int e = va_arg_int(alist);
      int f = va_arg_int(alist);
      int g = va_arg_int(alist);
      int h = va_arg_int(alist);
      int i = va_arg_int(alist);
      int j = va_arg_int(alist);
      int k = va_arg_int(alist);
      int l = va_arg_int(alist);
      int m = va_arg_int(alist);
      int n = va_arg_int(alist);
      int o = va_arg_int(alist);
      int p = va_arg_int(alist);
      int r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
      fprintf(out,"int f(16*int):(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
              a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
      fflush(out);
      va_return_int(alist, r);
    }}

  /* float tests */
  else if (current_function == (void*)&f_f)
    {
      va_start_float(alist);
     {float a = va_arg_float(alist);
      float r=a+1.0;
      fprintf(out,"float f(float):(%g)",a);
      fflush(out);
      va_return_float(alist, r);
    }}
  else if (current_function == (void*)&f_f2)
    {
      va_start_float(alist);
     {float a = va_arg_float(alist);
      float b = va_arg_float(alist);
      float r=a+b;
      fprintf(out,"float f(2*float):(%g,%g)",a,b);
      fflush(out);
      va_return_float(alist, r);
    }}
  else if (current_function == (void*)&f_f4)
    {
      va_start_float(alist);
     {float a = va_arg_float(alist);
      float b = va_arg_float(alist);
      float c = va_arg_float(alist);
      float d = va_arg_float(alist);
      float r=a+b+c+d;
      fprintf(out,"float f(4*float):(%g,%g,%g,%g)",a,b,c,d);
      fflush(out);
      va_return_float(alist, r);
    }}
  else if (current_function == (void*)&f_f8)
    {
      va_start_float(alist);
     {float a = va_arg_float(alist);
      float b = va_arg_float(alist);
      float c = va_arg_float(alist);
      float d = va_arg_float(alist);
      float e = va_arg_float(alist);
      float f = va_arg_float(alist);
      float g = va_arg_float(alist);
      float h = va_arg_float(alist);
      float r=a+b+c+d+e+f+g+h;
      fprintf(out,"float f(8*float):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
      fflush(out);
      va_return_float(alist, r);
    }}
  else if (current_function == (void*)&f_f16)
    {
      va_start_float(alist);
     {float a = va_arg_float(alist);
      float b = va_arg_float(alist);
      float c = va_arg_float(alist);
      float d = va_arg_float(alist);
      float e = va_arg_float(alist);
      float f = va_arg_float(alist);
      float g = va_arg_float(alist);
      float h = va_arg_float(alist);
      float i = va_arg_float(alist);
      float j = va_arg_float(alist);
      float k = va_arg_float(alist);
      float l = va_arg_float(alist);
      float m = va_arg_float(alist);
      float n = va_arg_float(alist);
      float o = va_arg_float(alist);
      float p = va_arg_float(alist);
      float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
      fprintf(out,"float f(16*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
      fflush(out);
      va_return_float(alist, r);
    }}
  else if (current_function == (void*)&f_f24)
    {
      va_start_float(alist);
     {float a = va_arg_float(alist);
      float b = va_arg_float(alist);
      float c = va_arg_float(alist);
      float d = va_arg_float(alist);
      float e = va_arg_float(alist);
      float f = va_arg_float(alist);
      float g = va_arg_float(alist);
      float h = va_arg_float(alist);
      float i = va_arg_float(alist);
      float j = va_arg_float(alist);
      float k = va_arg_float(alist);
      float l = va_arg_float(alist);
      float m = va_arg_float(alist);
      float n = va_arg_float(alist);
      float o = va_arg_float(alist);
      float p = va_arg_float(alist);
      float q = va_arg_float(alist);
      float s = va_arg_float(alist);
      float t = va_arg_float(alist);
      float u = va_arg_float(alist);
      float v = va_arg_float(alist);
      float w = va_arg_float(alist);
      float x = va_arg_float(alist);
      float y = va_arg_float(alist);
      float r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+s+t+u+v+w+x+y;
      fprintf(out,"float f(24*float):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,u,v,w,x,y);
      fflush(out);
      va_return_float(alist, r);
    }}

  /* double tests */
  else if (current_function == (void*)&d_d)
    {
      va_start_double(alist);
     {double a = va_arg_double(alist);
      double r=a+1.0;
      fprintf(out,"double f(double):(%g)",a);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_d2)
    {
      va_start_double(alist);
     {double a = va_arg_double(alist);
      double b = va_arg_double(alist);
      double r=a+b;
      fprintf(out,"double f(2*double):(%g,%g)",a,b);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_d4)
    {
      va_start_double(alist);
     {double a = va_arg_double(alist);
      double b = va_arg_double(alist);
      double c = va_arg_double(alist);
      double d = va_arg_double(alist);
      double r=a+b+c+d;
      fprintf(out,"double f(4*double):(%g,%g,%g,%g)",a,b,c,d);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_d8)
    {
      va_start_double(alist);
     {double a = va_arg_double(alist);
      double b = va_arg_double(alist);
      double c = va_arg_double(alist);
      double d = va_arg_double(alist);
      double e = va_arg_double(alist);
      double f = va_arg_double(alist);
      double g = va_arg_double(alist);
      double h = va_arg_double(alist);
      double r=a+b+c+d+e+f+g+h;
      fprintf(out,"double f(8*double):(%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_d16)
    {
      va_start_double(alist);
     {double a = va_arg_double(alist);
      double b = va_arg_double(alist);
      double c = va_arg_double(alist);
      double d = va_arg_double(alist);
      double e = va_arg_double(alist);
      double f = va_arg_double(alist);
      double g = va_arg_double(alist);
      double h = va_arg_double(alist);
      double i = va_arg_double(alist);
      double j = va_arg_double(alist);
      double k = va_arg_double(alist);
      double l = va_arg_double(alist);
      double m = va_arg_double(alist);
      double n = va_arg_double(alist);
      double o = va_arg_double(alist);
      double p = va_arg_double(alist);
      double r=a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;
      fprintf(out,"double f(16*double):(%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g)",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
      fflush(out);
      va_return_double(alist, r);
    }}

  /* pointer tests */
  else if (current_function == (void*)&vp_vpdpcpsp)
    {
      va_start_ptr(alist, void*);
     {void* a = va_arg_ptr(alist, void*);
      double* b = va_arg_ptr(alist, double*);
      char* c = va_arg_ptr(alist, char*);
      Int* d = va_arg_ptr(alist, Int*);
      void* ret = (char*)b + 1;
      fprintf(out,"void* f(void*,double*,char*,Int*):(0x%lx,0x%lx,0x%lx,0x%lx)",(long)a,(long)b,(long)c,(long)d);
      fflush(out);
      va_return_ptr(alist, void*, ret);
    }}

  /* mixed number tests */
  else if (current_function == (void*)&uc_ucsil)
    {
      va_start_uchar(alist);
     {uchar a = va_arg_uchar(alist);
      ushort b = va_arg_ushort(alist);
      uint c = va_arg_uint(alist);
      ulong d = va_arg_ulong(alist);
      uchar r = (uchar)-1;
      fprintf(out,"uchar f(uchar,ushort,uint,ulong):(%u,%u,%u,%lu)",a,b,c,d);
      fflush(out);
      va_return_uchar(alist, r);
    }}
  else if (current_function == (void*)&d_iidd)
    {
      va_start_double(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      double c = va_arg_double(alist);
      double d = va_arg_double(alist);
      double r=a+b+c+d;
      fprintf(out,"double f(int,int,double,double):(%d,%d,%g,%g)",a,b,c,d);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_iiidi)
    {
      va_start_double(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      int c = va_arg_int(alist);
      double d = va_arg_double(alist);
      int e = va_arg_int(alist);
      double r=a+b+c+d+e;
      fprintf(out,"double f(int,int,int,double,int):(%d,%d,%d,%g,%d)",a,b,c,d,e);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_idid)
    {
      va_start_double(alist);
     {int a = va_arg_int(alist);
      double b = va_arg_double(alist);
      int c = va_arg_int(alist);
      double d = va_arg_double(alist);
      double r=a+b+c+d;
      fprintf(out,"double f(int,double,int,double):(%d,%g,%d,%g)",a,b,c,d);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_fdi)
    {
      va_start_double(alist);
     {float a = va_arg_float(alist);
      double b = va_arg_double(alist);
      int c = va_arg_int(alist);
      double r=a+b+c;
      fprintf(out,"double f(float,double,int):(%g,%g,%d)",a,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&us_cdcd)
    {
      va_start_ushort(alist);
     {char a = va_arg_char(alist);
      double b = va_arg_double(alist);
      char c = va_arg_char(alist);
      double d = va_arg_double(alist);
      ushort r = (ushort)(a + b + c + d);
      fprintf(out,"ushort f(char,double,char,double):('%c',%g,'%c',%g)",a,b,c,d);
      fflush(out);
      va_return_ushort(alist, r);
    }}
#ifdef HAVE_LONG_LONG_INT
  else if (current_function == (void*)&ll_iiilli)
    {
      va_start_longlong(alist);
     {int a = va_arg_int(alist);
      int b = va_arg_int(alist);
      int c = va_arg_int(alist);
      long long d = va_arg_longlong(alist);
      int e = va_arg_int(alist);
      long long r = (long long)a + (long long)b + (long long)c + d + (long long)e;
      fprintf(out,"long long f(int,int,int,long long,int):(%d,%d,%d,0x%lx%08lx,%d)",a,b,c,(long)(d>>32),(long)(d&0xffffffff),e);
      fflush(out);
      va_return_longlong(alist, r);
    }}
  else if (current_function == (void*)&ll_flli)
    {
      va_start_longlong(alist);
     {float a = va_arg_float(alist);
      long long b = va_arg_longlong(alist);
      int c = va_arg_int(alist);
      long long r = (long long)(int)a + b + (long long)c;
      fprintf(out,"long long f(float,long long,int):(%g,0x%lx%08lx,0x%lx)",a,(long)(b>>32),(long)(b&0xffffffff),(long)c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
#endif

  /* small structure return tests */
  else if (current_function == (void*)&S1_v)
    {
      Size1 r;
      va_start_struct(alist, Size1, 1);
      r = Size1_1;
      fprintf(out,"Size1 f(void):");
      fflush(out);
      va_return_struct(alist, Size1, r);
    }
  else if (current_function == (void*)&S2_v)
    {
      Size2 r;
      va_start_struct(alist, Size2, 1);
      r = Size2_1;
      fprintf(out,"Size2 f(void):");
      fflush(out);
      va_return_struct(alist, Size2, r);
    }
  else if (current_function == (void*)&S3_v)
    {
      Size3 r;
      va_start_struct(alist, Size3, 1);
      r = Size3_1;
      fprintf(out,"Size3 f(void):");
      fflush(out);
      va_return_struct(alist, Size3, r);
    }
  else if (current_function == (void*)&S4_v)
    {
      Size4 r;
      va_start_struct(alist, Size4, 1);
      r = Size4_1;
      fprintf(out,"Size4 f(void):");
      fflush(out);
      va_return_struct(alist, Size4, r);
    }
  else if (current_function == (void*)&S7_v)
    {
      Size7 r;
      va_start_struct(alist, Size7, 1);
      r = Size7_1;
      fprintf(out,"Size7 f(void):");
      fflush(out);
      va_return_struct(alist, Size7, r);
    }
  else if (current_function == (void*)&S8_v)
    {
      Size8 r;
      va_start_struct(alist, Size8, 1);
      r = Size8_1;
      fprintf(out,"Size8 f(void):");
      fflush(out);
      va_return_struct(alist, Size8, r);
    }
  else if (current_function == (void*)&S12_v)
    {
      Size12 r;
      va_start_struct(alist, Size12, 1);
      r = Size12_1;
      fprintf(out,"Size12 f(void):");
      fflush(out);
      va_return_struct(alist, Size12, r);
    }
  else if (current_function == (void*)&S15_v)
    {
      Size15 r;
      va_start_struct(alist, Size15, 1);
      r = Size15_1;
      fprintf(out,"Size15 f(void):");
      fflush(out);
      va_return_struct(alist, Size15, r);
    }
  else if (current_function == (void*)&S16_v)
    {
      Size16 r;
      va_start_struct(alist, Size16, 1);
      r = Size16_1;
      fprintf(out,"Size16 f(void):");
      fflush(out);
      va_return_struct(alist, Size16, r);
    }

#ifndef SKIP_STRUCTS
  /* structure tests */
  else if (current_function == (void*)&I_III)
    {
      Int a;
      Int b;
      Int c;
      Int r;
      va_start_struct(alist, Int, 1);
      a = va_arg_struct(alist, Int);
      b = va_arg_struct(alist, Int);
      c = va_arg_struct(alist, Int);
      r.x = a.x + b.x + c.x;
      fprintf(out,"Int f(Int,Int,Int):({%d},{%d},{%d})",a.x,b.x,c.x);
      fflush(out);
      va_return_struct(alist, Int, r);
    }
#ifndef SKIP_EXTRA_STRUCTS
  else if (current_function == (void*)&C_CdC)
    {
      Char a;
      double b;
      Char c;
      Char r;
      va_start_struct(alist, Char, 1);
      a = va_arg_struct(alist, Char);
      b = va_arg_double(alist);
      c = va_arg_struct(alist, Char);
      r.x = (a.x + c.x)/2;
      fprintf(out,"Char f(Char,double,Char):({'%c'},%g,{'%c'})",a.x,b,c.x);
      fflush(out);
      va_return_struct(alist, Char, r);
    }
  else if (current_function == (void*)&F_Ffd)
    {
      Float a;
      float b;
      double c;
      Float r;
      va_start_struct(alist, Float, va_word_splittable_1(float));
      a = va_arg_struct(alist, Float);
      b = va_arg_float(alist);
      c = va_arg_double(alist);
      r.x = a.x + b + c;
      fprintf(out,"Float f(Float,float,double):({%g},%g,%g)",a.x,b,c);
      fflush(out);
      va_return_struct(alist, Float, r);
    }
  else if (current_function == (void*)&D_fDd)
    {
      float a;
      Double b;
      double c;
      Double r;
      va_start_struct(alist, Double, va_word_splittable_1(double));
      a = va_arg_float(alist);
      b = va_arg_struct(alist, Double);
      c = va_arg_double(alist);
      r.x = a + b.x + c;
      fprintf(out,"Double f(float,Double,double):(%g,{%g},%g)",a,b.x,c);
      fflush(out);
      va_return_struct(alist, Double, r);
    }
  else if (current_function == (void*)&D_Dfd)
    {
      Double a;
      float b;
      double c;
      Double r;
      va_start_struct(alist, Double, va_word_splittable_1(double));
      a = va_arg_struct(alist, Double);
      b = va_arg_float(alist);
      c = va_arg_double(alist);
      r.x = a.x + b + c;
      fprintf(out,"Double f(Double,float,double):({%g},%g,%g)",a.x,b,c);
      fflush(out);
      va_return_struct(alist, Double, r);
    }
#endif
  else if (current_function == (void*)&J_JiJ)
    {
      J a;
      int b;
      J c;
      J r;
      va_start_struct(alist, J, va_word_splittable_2(long,long));
      a = va_arg_struct(alist, J);
      b = va_arg_int(alist);
      c = va_arg_struct(alist, J);
      r.l1 = a.l1+c.l1; r.l2 = a.l2+b+c.l2;
      fprintf(out,"J f(J,int,J):({%ld,%ld},%d,{%ld,%ld})",a.l1,a.l2,b,c.l1,c.l2);
      fflush(out);
      va_return_struct(alist, J, r);
    }
#ifndef SKIP_EXTRA_STRUCTS
  else if (current_function == (void*)&T_TcT)
    {
      T a;
      char b;
      T c;
      T r;
      va_start_struct(alist, T, 1);
      a = va_arg_struct(alist, T);
      b = va_arg_char(alist);
      c = va_arg_struct(alist, T);
      r.c[0]='b'; r.c[1]=c.c[1]; r.c[2]=c.c[2];
      fprintf(out,"T f(T,char,T):({\"%c%c%c\"},'%c',{\"%c%c%c\"})",a.c[0],a.c[1],a.c[2],b,c.c[0],c.c[1],c.c[2]);
      fflush(out);
      va_return_struct(alist, T, r);
    }
  else if (current_function == (void*)&X_BcdB)
    {
      B a;
      char b;
      double c;
      B d;
      static X xr={"return val",'R'};
      X r;
      va_start_struct(alist, X, 0);
      a = va_arg_struct(alist, B);
      b = va_arg_char(alist);
      c = va_arg_double(alist);
      d = va_arg_struct(alist, B);
      r = xr;
      r.c1 = b;
      fprintf(out,"X f(B,char,double,B):({%g,{%d,%d,%d}},'%c',%g,{%g,{%d,%d,%d}})",
              a.d,a.i[0],a.i[1],a.i[2],b,c,d.d,d.i[0],d.i[1],d.i[2]);
      fflush(out);
      va_return_struct(alist, X, r);
    }
#endif
#endif

  /* gpargs boundary tests */
  else if (current_function == (void*)&l_l0K)
    {
      va_start_long(alist);
     {K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(K,long):(%ld,%ld,%ld,%ld,%ld)",b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
  else if (current_function == (void*)&l_l1K)
    {
      va_start_long(alist);
     {long a1 = va_arg_long(alist);
      K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = a1 + b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld)",a1,b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
  else if (current_function == (void*)&l_l2K)
    {
      va_start_long(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = a1 + a2 + b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(2*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
  else if (current_function == (void*)&l_l3K)
    {
      va_start_long(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = a1 + a2 + a3 + b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(3*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
  else if (current_function == (void*)&l_l4K)
    {
      va_start_long(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = a1 + a2 + a3 + a4 + b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(4*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
  else if (current_function == (void*)&l_l5K)
    {
      va_start_long(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = a1 + a2 + a3 + a4 + a5 + b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(5*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,a5,b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
  else if (current_function == (void*)&l_l6K)
    {
      va_start_long(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      long a6 = va_arg_long(alist);
      K b = va_arg_struct(alist, K);
      long c = va_arg_long(alist);
      long r = a1 + a2 + a3 + a4 + a5 + a6 + b.l1 + b.l2 + b.l3 + b.l4 + c;
      fprintf(out,"long f(6*long,K,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld)",a1,a2,a3,a4,a5,a6,b.l1,b.l2,b.l3,b.l4,c);
      fflush(out);
      va_return_long(alist, r);
    }}
#ifdef HAVE_LONG_LONG_INT
  else if (current_function == (void*)&ll_l2ll)
    {
      va_start_longlong(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long long b = va_arg_longlong(alist);
      long c = va_arg_long(alist);
      long long r = (long long) (a1 + a2) + b + c;
      fprintf(out,"long long f(2*long,long long,long):(%ld,%ld,0x%lx%08lx,%ld)",a1,a2,(long)(b>>32),(long)(b&0xffffffff),c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
  else if (current_function == (void*)&ll_l3ll)
    {
      va_start_longlong(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long long b = va_arg_longlong(alist);
      long c = va_arg_long(alist);
      long long r = (long long) (a1 + a2 + a3) + b + c;
      fprintf(out,"long long f(3*long,long long,long):(%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,(long)(b>>32),(long)(b&0xffffffff),c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
  else if (current_function == (void*)&ll_l4ll)
    {
      va_start_longlong(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long long b = va_arg_longlong(alist);
      long c = va_arg_long(alist);
      long long r = (long long) (a1 + a2 + a3 + a4) + b + c;
      fprintf(out,"long long f(4*long,long long,long):(%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,(long)(b>>32),(long)(b&0xffffffff),c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
  else if (current_function == (void*)&ll_l5ll)
    {
      va_start_longlong(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      long long b = va_arg_longlong(alist);
      long c = va_arg_long(alist);
      long long r = (long long) (a1 + a2 + a3 + a4 + a5) + b + c;
      fprintf(out,"long long f(5*long,long long,long):(%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,(long)(b>>32),(long)(b&0xffffffff),c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
  else if (current_function == (void*)&ll_l6ll)
    {
      va_start_longlong(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      long a6 = va_arg_long(alist);
      long long b = va_arg_longlong(alist);
      long c = va_arg_long(alist);
      long long r = (long long) (a1 + a2 + a3 + a4 + a5 + a6) + b + c;
      fprintf(out,"long long f(6*long,long long,long):(%ld,%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,a6,(long)(b>>32),(long)(b&0xffffffff),c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
  else if (current_function == (void*)&ll_l7ll)
    {
      va_start_longlong(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      long a6 = va_arg_long(alist);
      long a7 = va_arg_long(alist);
      long long b = va_arg_longlong(alist);
      long c = va_arg_long(alist);
      long long r = (long long) (a1 + a2 + a3 + a4 + a5 + a6 + a7) + b + c;
      fprintf(out,"long long f(7*long,long long,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,0x%lx%08lx,%ld)",a1,a2,a3,a4,a5,a6,a7,(long)(b>>32),(long)(b&0xffffffff),c);
      fflush(out);
      va_return_longlong(alist, r);
    }}
#endif
  else if (current_function == (void*)&d_l2d)
    {
      va_start_double(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      double b = va_arg_double(alist);
      long c = va_arg_long(alist);
      double r = (double) (a1 + a2) + b + c;
      fprintf(out,"double f(2*long,double,long):(%ld,%ld,%g,%ld)",a1,a2,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_l3d)
    {
      va_start_double(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      double b = va_arg_double(alist);
      long c = va_arg_long(alist);
      double r = (double) (a1 + a2 + a3) + b + c;
      fprintf(out,"double f(3*long,double,long):(%ld,%ld,%ld,%g,%ld)",a1,a2,a3,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_l4d)
    {
      va_start_double(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      double b = va_arg_double(alist);
      long c = va_arg_long(alist);
      double r = (double) (a1 + a2 + a3 + a4) + b + c;
      fprintf(out,"double f(4*long,double,long):(%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_l5d)
    {
      va_start_double(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      double b = va_arg_double(alist);
      long c = va_arg_long(alist);
      double r = (double) (a1 + a2 + a3 + a4 + a5) + b + c;
      fprintf(out,"double f(5*long,double,long):(%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_l6d)
    {
      va_start_double(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      long a6 = va_arg_long(alist);
      double b = va_arg_double(alist);
      long c = va_arg_long(alist);
      double r = (double) (a1 + a2 + a3 + a4 + a5 + a6) + b + c;
      fprintf(out,"double f(6*long,double,long):(%ld,%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,a6,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}
  else if (current_function == (void*)&d_l7d)
    {
      va_start_double(alist);
     {long a1 = va_arg_long(alist);
      long a2 = va_arg_long(alist);
      long a3 = va_arg_long(alist);
      long a4 = va_arg_long(alist);
      long a5 = va_arg_long(alist);
      long a6 = va_arg_long(alist);
      long a7 = va_arg_long(alist);
      double b = va_arg_double(alist);
      long c = va_arg_long(alist);
      double r = (double) (a1 + a2 + a3 + a4 + a5 + a6 + a7) + b + c;
      fprintf(out,"double f(7*long,double,long):(%ld,%ld,%ld,%ld,%ld,%ld,%ld,%g,%ld)",a1,a2,a3,a4,a5,a6,a7,b,c);
      fflush(out);
      va_return_double(alist, r);
    }}

  else
    {
      fprintf(out,"simulate: unknown function\n");
      fflush(out);
    }
}

/*
 * The way we run these tests - first call the function directly, then
 * through vacall() - there is the danger that arguments or results seem
 * to be passed correctly, but what we are seeing are in fact the vestiges
 * (traces) or the previous call. This may seriously fake the test.
 * Avoid this by clearing the registers between the first and the second call.
 */
long clear_traces_i (long a, long b, long c, long d, long e, long f, long g, long h,
                     long i, long j, long k, long l, long m, long n, long o, long p)
{ return 0; }
float clear_traces_f (float a, float b, float c, float d, float e, float f, float g,
                      float h, float i, float j, float k, float l, float m, float n,
                      float o, float p)
{ return 0.0; }
double clear_traces_d (double a, double b, double c, double d, double e, double f, double g,
                       double h, double i, double j, double k, double l, double m, double n,
                       double o, double p)
{ return 0.0; }
J clear_traces_J (void)
{ J j; j.l1 = j.l2 = 0; return j; }
void clear_traces (void)
{ clear_traces_i(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  clear_traces_f(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  clear_traces_d(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  clear_traces_J();
}

int main (void)
{
  out = stdout;

  vacall_function = &simulator;

  /* void tests */
  v_v();
  clear_traces();
  current_function = (void*) &v_v; ((void (*) (void)) vacall) ();

  /* int tests */
  { int ir;

    ir = i_v();
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    current_function = (void*) &i_v; ir = ((int (*) (void)) vacall) ();
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i(i1);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    current_function = (void*) &i_i; ir = ((int (*) (int)) vacall) (i1);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i2(i1,i2);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    current_function = (void*) &i_i2; ir = ((int (*) (int,int)) vacall) (i1,i2);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i4(i1,i2,i3,i4);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    current_function = (void*) &i_i4; ir = ((int (*) (int,int,int,int)) vacall) (i1,i2,i3,i4);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i8(i1,i2,i3,i4,i5,i6,i7,i8);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    current_function = (void*) &i_i8; ir = ((int (*) (int,int,int,int,int,int,int,int)) vacall) (i1,i2,i3,i4,i5,i6,i7,i8);
    fprintf(out,"->%d\n",ir);
    fflush(out);

    ir = i_i16(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
    fprintf(out,"->%d\n",ir);
    fflush(out);
    ir = 0; clear_traces();
    current_function = (void*) &i_i16; ir = ((int (*) (int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)) vacall) (i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16);
    fprintf(out,"->%d\n",ir);
    fflush(out);
  }

  /* float tests */
  { float fr;

    fr = f_f(f1);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    current_function = (void*) &f_f; fr = ((float (*) (float)) vacall) (f1);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f2(f1,f2);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    current_function = (void*) &f_f2; fr = ((float (*) (float,float)) vacall) (f1,f2);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f4(f1,f2,f3,f4);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    current_function = (void*) &f_f4; fr = ((float (*) (float,float,float,float)) vacall) (f1,f2,f3,f4);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f8(f1,f2,f3,f4,f5,f6,f7,f8);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    current_function = (void*) &f_f8; fr = ((float (*) (float,float,float,float,float,float,float,float)) vacall) (f1,f2,f3,f4,f5,f6,f7,f8);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f16(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    current_function = (void*) &f_f16; fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)) vacall) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16);
    fprintf(out,"->%g\n",fr);
    fflush(out);

    fr = f_f24(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24);
    fprintf(out,"->%g\n",fr);
    fflush(out);
    fr = 0.0; clear_traces();
    current_function = (void*) &f_f24; fr = ((float (*) (float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float)) vacall) (f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24);
    fprintf(out,"->%g\n",fr);
    fflush(out);
  }

  /* double tests */
  { double dr;

    dr = d_d(d1);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_d; dr = ((double (*) (double)) vacall) (d1);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d2(d1,d2);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_d2; dr = ((double (*) (double,double)) vacall) (d1,d2);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d4(d1,d2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_d4; dr = ((double (*) (double,double,double,double)) vacall) (d1,d2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d8(d1,d2,d3,d4,d5,d6,d7,d8);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_d8; dr = ((double (*) (double,double,double,double,double,double,double,double)) vacall) (d1,d2,d3,d4,d5,d6,d7,d8);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_d16(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_d16; dr = ((double (*) (double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)) vacall) (d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16);
    fprintf(out,"->%g\n",dr);
    fflush(out);
  }

  /* pointer tests */
  { void* vpr;

    vpr = vp_vpdpcpsp(&uc1,&d2,str3,&I4);
    fprintf(out,"->0x%lx\n",(long)vpr);
    fflush(out);
    vpr = 0; clear_traces();
    current_function = (void*) &vp_vpdpcpsp; vpr = ((void* (*) (void*,double*,char*,Int*)) vacall) (&uc1,&d2,str3,&I4);
    fprintf(out,"->0x%lx\n",(long)vpr);
    fflush(out);
  }

  /* mixed number tests */
  { uchar ucr;
    ushort usr;
    double dr;
#ifdef HAVE_LONG_LONG_INT
    long long llr;
#endif

    ucr = uc_ucsil(uc1,us2,ui3,ul4);
    fprintf(out,"->%u\n",ucr);
    fflush(out);
    ucr = 0; clear_traces();
    current_function = (void*) &uc_ucsil; ucr = ((uchar (*) (uchar,ushort,uint,ulong)) vacall) (uc1,us2,ui3,ul4);
    fprintf(out,"->%u\n",ucr);
    fflush(out);

    dr = d_iidd(i1,i2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_iidd; dr = ((double (*) (int,int,double,double)) vacall) (i1,i2,d3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_iiidi(i1,i2,i3,d4,i5);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_iiidi; dr = ((double (*) (int,int,int,double,int)) vacall) (i1,i2,i3,d4,i5);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_idid(i1,d2,i3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_idid; dr = ((double (*) (int,double,int,double)) vacall) (i1,d2,i3,d4);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_fdi(f1,d2,i3);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_fdi; dr = ((double (*) (float,double,int)) vacall) (f1,d2,i3);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    usr = us_cdcd(c1,d2,c3,d4);
    fprintf(out,"->%u\n",usr);
    fflush(out);
    usr = 0; clear_traces();
    current_function = (void*) &us_cdcd; usr = ((ushort (*) (char,double,char,double)) vacall) (c1,d2,c3,d4);
    fprintf(out,"->%u\n",usr);
    fflush(out);

#ifdef HAVE_LONG_LONG_INT
    llr = ll_iiilli(i1,i2,i3,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_iiilli; llr = ((long long (*) (int,int,int,long long,int)) vacall) (i1,i2,i3,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_flli(f13,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_flli; llr = ((long long (*) (float,long long,int)) vacall) (f13,ll1,i13);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
#endif
  }

  /* small structure return tests */
  {
    Size1 r = S1_v();
    fprintf(out,"->{%c}\n",r.x1);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S1_v; r = ((Size1 (*) (void)) vacall) ();
    fprintf(out,"->{%c}\n",r.x1);
    fflush(out);
  }
  {
    Size2 r = S2_v();
    fprintf(out,"->{%c%c}\n",r.x1,r.x2);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S2_v; r = ((Size2 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c}\n",r.x1,r.x2);
    fflush(out);
  }
  {
    Size3 r = S3_v();
    fprintf(out,"->{%c%c%c}\n",r.x1,r.x2,r.x3);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S3_v; r = ((Size3 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c}\n",r.x1,r.x2,r.x3);
    fflush(out);
  }
  {
    Size4 r = S4_v();
    fprintf(out,"->{%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S4_v; r = ((Size4 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4);
    fflush(out);
  }
  {
    Size7 r = S7_v();
    fprintf(out,"->{%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S7_v; r = ((Size7 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7);
    fflush(out);
  }
  {
    Size8 r = S8_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S8_v; r = ((Size8 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8);
    fflush(out);
  }
  {
    Size12 r = S12_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S12_v; r = ((Size12 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12);
    fflush(out);
  }
  {
    Size15 r = S15_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S15_v; r = ((Size15 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15);
    fflush(out);
  }
  {
    Size16 r = S16_v();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15,r.x16);
    fflush(out);
    memset(&r,0,sizeof(r)); clear_traces();
    current_function = (void*) &S16_v; r = ((Size16 (*) (void)) vacall) ();
    fprintf(out,"->{%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c}\n",r.x1,r.x2,r.x3,r.x4,r.x5,r.x6,r.x7,r.x8,r.x9,r.x10,r.x11,r.x12,r.x13,r.x14,r.x15,r.x16);
    fflush(out);
  }

#ifndef SKIP_STRUCTS
  /* structure tests */
  { Int Ir;
    Char Cr;
    Float Fr;
    Double Dr;
    J Jr;
    T Tr;
    X Xr;

    Ir = I_III(I1,I2,I3);
    fprintf(out,"->{%d}\n",Ir.x);
    fflush(out);
    Ir.x = 0; clear_traces();
    current_function = (void*) &I_III; Ir = ((Int (*) (Int,Int,Int)) vacall) (I1,I2,I3);
    fprintf(out,"->{%d}\n",Ir.x);
    fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
    Cr = C_CdC(C1,d2,C3);
    fprintf(out,"->{'%c'}\n",Cr.x);
    fflush(out);
    Cr.x = '\0'; clear_traces();
    current_function = (void*) &C_CdC; Cr = ((Char (*) (Char,double,Char)) vacall) (C1,d2,C3);
    fprintf(out,"->{'%c'}\n",Cr.x);
    fflush(out);

    Fr = F_Ffd(F1,f2,d3);
    fprintf(out,"->{%g}\n",Fr.x);
    fflush(out);
    Fr.x = 0.0; clear_traces();
    current_function = (void*) &F_Ffd; Fr = ((Float (*) (Float,float,double)) vacall) (F1,f2,d3);
    fprintf(out,"->{%g}\n",Fr.x);
    fflush(out);

    Dr = D_fDd(f1,D2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
    Dr.x = 0.0; clear_traces();
    current_function = (void*) &D_fDd; Dr = ((Double (*) (float,Double,double)) vacall) (f1,D2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);

    Dr = D_Dfd(D1,f2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
    Dr.x = 0.0; clear_traces();
    current_function = (void*) &D_Dfd; Dr = ((Double (*) (Double,float,double)) vacall) (D1,f2,d3);
    fprintf(out,"->{%g}\n",Dr.x);
    fflush(out);
#endif

    Jr = J_JiJ(J1,i2,J2);
    fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
    fflush(out);
    Jr.l1 = Jr.l2 = 0; clear_traces();
    current_function = (void*) &J_JiJ; Jr = ((J (*) (J,int,J)) vacall) (J1,i2,J2);
    fprintf(out,"->{%ld,%ld}\n",Jr.l1,Jr.l2);
    fflush(out);

#ifndef SKIP_EXTRA_STRUCTS
#ifndef SKIP_T
    Tr = T_TcT(T1,' ',T2);
    fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
    fflush(out);
    Tr.c[0] = Tr.c[1] = Tr.c[2] = 0; clear_traces();
    current_function = (void*) &T_TcT; Tr = ((T (*) (T,char,T)) vacall) (T1,' ',T2);
    fprintf(out,"->{\"%c%c%c\"}\n",Tr.c[0],Tr.c[1],Tr.c[2]);
    fflush(out);
#endif

#ifndef SKIP_X
    Xr = X_BcdB(B1,c2,d3,B2);
    fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
    fflush(out);
    Xr.c[0]=Xr.c1='\0'; clear_traces();
    current_function = (void*) &X_BcdB; Xr = ((X (*) (B,char,double,B)) vacall) (B1,c2,d3,B2);
    fprintf(out,"->{\"%s\",'%c'}\n",Xr.c,Xr.c1);
    fflush(out);
#endif
#endif
  }
#endif

  /* gpargs boundary tests */
  { long lr;
#ifdef HAVE_LONG_LONG_INT
    long long llr;
#endif
    double dr;

    lr = l_l0K(K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l0K; lr = ((long (*) (K,long)) vacall) (K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l1K(l1,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l1K; lr = ((long (*) (long,K,long)) vacall) (l1,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l2K(l1,l2,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l2K; lr = ((long (*) (long,long,K,long)) vacall) (l1,l2,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l3K(l1,l2,l3,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l3K; lr = ((long (*) (long,long,long,K,long)) vacall) (l1,l2,l3,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l4K(l1,l2,l3,l4,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l4K; lr = ((long (*) (long,long,long,long,K,long)) vacall) (l1,l2,l3,l4,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l5K(l1,l2,l3,l4,l5,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l5K; lr = ((long (*) (long,long,long,long,long,K,long)) vacall) (l1,l2,l3,l4,l5,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

    lr = l_l6K(l1,l2,l3,l4,l5,l6,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);
    lr = 0; clear_traces();
    current_function = (void*) &l_l6K; lr = ((long (*) (long,long,long,long,long,long,K,long)) vacall) (l1,l2,l3,l4,l5,l6,K1,l9);
    fprintf(out,"->%ld\n",lr);
    fflush(out);

#ifdef HAVE_LONG_LONG_INT
    llr = ll_l2ll(l1,l2,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_l2ll; llr = ((long long (*) (long,long,long long,long)) vacall) (l1,l2,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l3ll(l1,l2,l3,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_l3ll; llr = ((long long (*) (long,long,long,long long,long)) vacall) (l1,l2,l3,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l4ll(l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_l4ll; llr = ((long long (*) (long,long,long,long,long long,long)) vacall) (l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l5ll(l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_l5ll; llr = ((long long (*) (long,long,long,long,long,long long,long)) vacall) (l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l6ll(l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_l6ll; llr = ((long long (*) (long,long,long,long,long,long,long long,long)) vacall) (l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);

    llr = ll_l7ll(l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
    llr = 0; clear_traces();
    current_function = (void*) &ll_l7ll; llr = ((long long (*) (long,long,long,long,long,long,long,long long,long)) vacall) (l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->0x%lx%08lx\n",(long)(llr>>32),(long)(llr&0xffffffff));
    fflush(out);
#endif

    dr = d_l2d(l1,l2,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_l2d; dr = ((double (*) (long,long,double,long)) vacall) (l1,l2,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l3d(l1,l2,l3,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_l3d; dr = ((double (*) (long,long,long,double,long)) vacall) (l1,l2,l3,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l4d(l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_l4d; dr = ((double (*) (long,long,long,long,double,long)) vacall) (l1,l2,l3,l4,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l5d(l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_l5d; dr = ((double (*) (long,long,long,long,long,double,long)) vacall) (l1,l2,l3,l4,l5,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l6d(l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_l6d; dr = ((double (*) (long,long,long,long,long,long,double,long)) vacall) (l1,l2,l3,l4,l5,l6,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);

    dr = d_l7d(l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
    dr = 0.0; clear_traces();
    current_function = (void*) &d_l7d; dr = ((double (*) (long,long,long,long,long,long,long,double,long)) vacall) (l1,l2,l3,l4,l5,l6,l7,ll1,l9);
    fprintf(out,"->%g\n",dr);
    fflush(out);
  }

  exit(0);
}
