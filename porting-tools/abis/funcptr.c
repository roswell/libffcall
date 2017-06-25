/* Test code, used to determine what a function pointer really is
   and how "nested functions" are implemented by GCC. */

typedef int (*funcptr) (void);

static int oracle (void) { return 7355; }

funcptr global_funcptr = oracle;

int call_global_funcptr (void)
{
  return (*global_funcptr)();
}

int call_fixedaddr_funcptr (void)
{
  return (*(funcptr)0xbabebec0)();
}

#include <stdio.h>

#ifdef __GNUC__

/* Nested functions, cf. https://gcc.gnu.org/onlinedocs/gcc-7.1.0/gcc/Nested-Functions.html */

typedef int (*mathfuncptr) (int);

mathfuncptr global_mathfuncptr;

int call_global_mathfuncptr_twice (int a)
{
  return (*global_mathfuncptr) ((*global_mathfuncptr) (a));
}

int use_local_function (int x)
{
  int add (int y) { return x + y; }
  global_mathfuncptr = add;
  return call_global_mathfuncptr_twice (x);
}

int main ()
{
  int result = use_local_function(100);
  printf ("%d\n", result);
}

#else

int main ()
{
  (*global_funcptr) ();
  printf ("value of global_funcptr = 0x%lx\n", (long)global_funcptr);
  
}

#endif
