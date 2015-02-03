#include <stdio.h>
#include <errno.h>
#include <math.h>

float div(float x, float y) { return x / y; }
int idiv(int x, int y) { return x / y; }

void main(void)
{
  float x;
  int y;

  x = div(0.0f, 0.0f);
  printf("ERR=%d, VALUE=%f\n", errno, x);

  x = div(1.0f, 0.0f);
  printf("ERR=%d, VALUE=%f\n", errno, x);

  y = idiv(0,0);
  printf("%d\n", y);
}
