/* Imprime o que? */
#include <stdio.h>

#define square(x) x*x

void main(void)
{
  int x = 36/square(6);
  printf("%d\n", x);
}
