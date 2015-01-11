#include <stdlib.h>

unsigned short cksumrfc(void *addr, size_t count)
{
  register unsigned int sum = 0;
  register unsigned int tmp;

  /* FIXME: Esse loop não considera o "carry" vindo da soma anterior! */
  while (count > 1)  
  {
    sum += *(unsigned short *)addr++;
    count -= 2;
  }

  if (count)
    sum += * (unsigned char *) addr;

  /* Se a soma tem mais que 16 bits, acresenta os bits superiores */
  while (tmp = sum >> 16)
    sum = (sum & 0xffff) + tmp;

  return ~sum;
}

