#include <stdio.h>

extern long readtsc(void);

int main(int argc, char *argv[])
{
  /* warmup. */
  readtsc();
  readtsc();
  readtsc();

  printf("%ld ciclos desperdiçados.\n", readtsc());
  return 0;
}
