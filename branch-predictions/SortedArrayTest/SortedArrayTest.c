#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 100000
#define MAX_BUFFER_SIZE 32768

int buffer[MAX_BUFFER_SIZE];

/* Preenche array com valores aleatórios entre 0 e 255. */
void random_fill_buffer(void)
{
  int i;

  srand(time(NULL));
  for (i = 0; i < MAX_BUFFER_SIZE; i++)
    buffer[i] = rand() % 256;
}

/* Usada por qsort. */
int compare(const void *x, const void *y) { return *(int *)x < *(int *)y; }

int main(void)
{
  int i, j;
  long sum;
  clock_t clkstart;
  double clkelapsed;

  random_fill_buffer();

  // Retire isso daqui para testar com o array fora de ordem.
  qsort(buffer, MAX_BUFFER_SIZE, sizeof(int), compare);

  clkstart = clock();

  for (i = 0; i < MAX_ITERATIONS; i++)
    for (j = 0; j < MAX_BUFFER_SIZE; j++)
      if (buffer[j] >= 128)
        sum += buffer[j];

  clkelapsed = (double)(clock() - clkstart) / CLOCKS_PER_SEC;

  printf("sum = %ld.\n"
         "Tempo decorrido: %.3f segundos.\n", sum, clkelapsed);

  return 0;
}
