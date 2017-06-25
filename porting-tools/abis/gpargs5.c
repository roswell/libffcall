typedef struct { long a; long b; long c; long d; } IIII;

long f1 (long a1, long a2, long a3, IIII s, long z)
{
  return a1+a2+a3+s.a+s.b+s.c+s.d+z;
}

long long f2 (long a1, long a2, long a3, long a4, long long ll, long z)
{
  return (long long)(a1+a2+a3+a4)+ll+z;
}

double f3 (long a1, long a2, long a3, long a4, double d, long z)
{
  return (double)(a1+a2+a3+a4)+d+z;
}
