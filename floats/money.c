#include <stdio.h>
#include <math.h>

#define MUL100(x) ((x) * 100)
#define DIV100(x) ((x) / 100)

float money_to_float(long x) { return (float)x / 100.0f; }
long float_to_money(float x) { return (long)floorf(x * 100.0f); }

long money_add(long x, long y) { return x + y; }
long money_sub(long x, long y) { return x - y; }
long money_mul(long x, long y) { return DIV100(x * y); }
long money_div(long x, long y) { return MUL100(x) / y; }

void main(void)
{
  long v1;
  long v2;

  v1 = money_mul(float_to_money(3.14f), float_to_money(4.0f));
  v2 = money_div(float_to_money(3.0f), float_to_money(2.0f));

  printf("%.2f, %.2f\n", money_to_float(v1), money_to_float(v2));
}
