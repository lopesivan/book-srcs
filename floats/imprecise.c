#include <stdio.h>

float values[] = { 0.1f, 0.2f, 0.3f, 0.5f, 0.7f };
#define ARRAY_SIZE (sizeof(values) / sizeof(values[0]))

void main(void)
{
  int i;

  for (i = 0; i < ARRAY_SIZE; i++)
    printf("%.1f: 0x%08X\n", values[i], *((unsigned *)&values[i]));
}
