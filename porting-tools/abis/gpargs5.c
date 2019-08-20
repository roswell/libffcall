typedef struct { unsigned long a; unsigned long b; } II;
typedef struct { long a; long b; long c; long d; } IIII;

extern void dummy (II *);

long f1 (long a1, long a2, long a3, IIII s, long z)
{
  return a1+a2+a3+s.a+s.b+s.c+s.d+z;
}

long long f2 (long a1, long a2, long a3, long a4, II s, long z)
{
  dummy(&s);
  return (long long)(a1+a2+a3+a4)+ (((unsigned long long)s.a<<32)|(unsigned long long)s.b) +z;
}

long long f3 (long a1, long a2, long a3, long a4, long long ll, long z)
{
  return (long long)(a1+a2+a3+a4)+ll+z;
}

double f4 (long a1, long a2, long a3, long a4, double d, long z)
{
  return (double)(a1+a2+a3+a4)+d+z;
}
