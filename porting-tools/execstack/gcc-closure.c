/* Test whether a lexical closure created by GCC requires an executable stack.
   Compile this file with
     cross <target> gcc -O2 -S -fomit-frame-pointer gcc-closure.c
 */

extern int callback (void (*) (void));

int foo (void)
{
  int x = 0;

  void increment_x (void) { x++; }

  callback (increment_x);

  return x;
}

/* Result:
   i386             yes
   x86_64           yes
   m68k             yes
   mips             yes
   mips64           yes
   sparc            yes
   sparc64          yes
   alpha            yes
   hppa             ?
   hppa64           ?
   arm              yes
   arm64            yes
   powerpc          no
   powerpc64        no
   powerpc64-elfv2  no
   ia64             no
   s390             yes
   s390x            yes
   riscv32          yes
   riscv64          yes
 */
