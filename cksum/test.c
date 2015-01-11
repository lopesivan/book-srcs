#include <stdio.h>
#include <time.h>

extern unsigned short cksumrfc(void *, size_t);
extern unsigned short cksum2(void *, size_t);
extern unsigned long TSC_READ(void);

#define BUFFER_SIZE 32768+7 
char buffer[BUFFER_SIZE];

void fillbuffer(void *, size_t);
void viewbuffer(void *, size_t);

int main(int argc, char *argv)
{
  unsigned long c1, c2;
  unsigned short sum1, sum2;

  fillbuffer(buffer, BUFFER_SIZE);

  c1 = TSC_READ();
  sum1 = cksumrfc(buffer, BUFFER_SIZE);
  c1 = TSC_READ() - c1;  

  c2 = TSC_READ();
  sum2 = cksum2(buffer, BUFFER_SIZE);
  c2 = TSC_READ() - c2;  

  printf("Buffer: %d bytes.\n"
         "\tcksumrfc: 0x%04X.\t"
         "\tcksum2: 0x%04X.\n",
         BUFFER_SIZE,
         sum1, sum2); 

  printf("Ciclos de clock:\n"
         "\tchksumrfc: %lu ciclos."
         "\tchksum2: %lu ciclos.\n",
         c1, c2);

  //viewbuffer(buffer, BUFFER_SIZE);

  return 0;
}

void fillbuffer(void *ptr, size_t count)
{
  char *p = ptr;

  srand(time(NULL));
  while (count--)
    *p++ = (unsigned int)rand() >> 24;
}

void viewbuffer(void *ptr, size_t count)
{
  unsigned char *p = ptr;
  int nl = 0, c = 0;

  printf("\nBuffer:\n");
  while (count--)
  {
    if (nl) { printf("\n"); nl = 0; }
    if (++c == 16) { nl = 1; c = 0; }
    printf("%02X ", *p++);
  }
  printf("\n");
}
