#include <stdlib.h>

unsigned short cksum2(void *data, size_t count)
{
  unsigned long sum, tmp, *p;
  unsigned int u1, u2;
  unsigned short s1, s2;
  size_t ulcount;
  int shift;

  sum = 0;
  p = data;
  ulcount = count >> 3;
  count -= ulcount << 3;

  while (ulcount--)
  {
    sum += *p;
    if (sum < *p) sum++;
    p++;
  }

  if (count)
  {
    shift = (8 - count) * 8;
    tmp = *p & (0xffffffffffffffffUL >> shift);    /* perigoso, mas funciona! */
    sum += tmp;
    if (sum < tmp) sum++;
  }

  u1 = sum;
  u2 = sum >> 32;
  u1 += u2;
  if (u1 < u2) u1++;

  s1 = u1;
  s2 = u1 >> 16;
  s1 += s2;
  if (s1 < s2) s1++;

  return ~s1;
}
