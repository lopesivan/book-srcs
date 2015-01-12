#include <stdio.h>
#include <time.h>

extern unsigned short cksumrfc(void *, size_t);
extern unsigned short cksum2(void *, size_t);
extern unsigned short cksum3(void *, size_t);
extern unsigned long TSC_READ(void);

#define BUFFER_SIZE 32768+7
char buffer[BUFFER_SIZE];

void fillbuffer(void *, size_t);

int main(int argc, char *argv)
{
  unsigned long c1, c2, c3;
  unsigned short sum1, sum2, sum3;

  fillbuffer(buffer, BUFFER_SIZE);

  c1 = TSC_READ();
  sum1 = cksumrfc(buffer, BUFFER_SIZE);
  c1 = TSC_READ() - c1;  

  c2 = TSC_READ();
  sum2 = cksum2(buffer, BUFFER_SIZE);
  c2 = TSC_READ() - c2;  

  c3 = TSC_READ();
  sum3 = cksum2(buffer, BUFFER_SIZE);
  c3 = TSC_READ() - c3;  

  printf("Buffer: %d bytes.\n"
         "\tcksumrfc: 0x%04X."
         "\tcksum2: 0x%04X."
         "\tcksum3: 0x%04X.\n",
         BUFFER_SIZE,
         sum1, sum2, sum3); 

  printf("Ciclos de clock:\n"
         "\tchksumrfc: %lu ciclos."
         "\tchksum2: %lu ciclos."
         "\tcksum3: %lu ciclos.\n",
         c1, c2, c3);

  return 0;
}

void fillbuffer(void *ptr, size_t count)
{
  char *p = ptr;

  srand(time(NULL));
  while (count--)
    *p++ = (unsigned int)rand() >> 24;
}

