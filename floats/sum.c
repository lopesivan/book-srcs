#include <stdio.h>

void main(void)
{
  float f = 0.1f;
  float sum = 0;
  float product = f * 10;
  int i;

  for (i = 0; i < 10; ++i)
    sum += f;

  printf("sum = %1.15f, mul = %1.15f, mul2 = %1.15f\n",
      sum, product, f * 10);
}
