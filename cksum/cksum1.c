#include <stdlib.h>

unsigned short cksumrfc(void *addr, size_t count)
{
  unsigned int sum = 0;
  unsigned short *p = addr;
  unsigned int tmp;

  /* FIXME: Esse loop não considera o "carry" vindo da soma anterior! */
  while (count > 1)  
  {
    sum += *p++;
    count -= 2;
  }

  if (count)
    sum += *(unsigned char *)p;

  /* Se a soma tem mais que 16 bits, acresenta os bits superiores */
  while (tmp = sum >> 16)
    sum = (sum & 0xffff) + tmp;

  return ~sum;
}

