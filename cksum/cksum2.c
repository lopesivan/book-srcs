/*
 *  T50 - Experimental Mixed Packet Injector
 *
 *  Copyright (C) 2010 - 2014 - T50 developers
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdint.h>

unsigned short cksum2(void *data, size_t count)
{
  unsigned long sum, oldsum, *p = data;
  unsigned int u32_1, u32_2;
  unsigned short u16_1, u16_2;

  oldsum = sum = 0;

  /* Sums 8 bytes at a time... */
  while (count >= sizeof(unsigned long))
  {
    sum += *p++;
    if (sum < oldsum) sum++;
    oldsum = sum;
    count -= sizeof(unsigned long);
  }

  /* Sums the remaing data, if any */
  data = p;
  if (count >= sizeof(unsigned int))
  {
    sum += *(unsigned int *)data;
    if (sum < oldsum) sum++;
    oldsum = sum;

    count -= sizeof(unsigned int);
    data += sizeof(unsigned int);
  }

  if (count >= sizeof(unsigned short))
  {
    sum += *(unsigned short *)data;
    if (sum < oldsum) sum++;
    oldsum = sum;

    count -= sizeof(unsigned short);
    data += sizeof(unsigned short);
  }

  if (count)
  {
    sum += *(unsigned char *)data;
    if (sum < oldsum) sum++;
  }

  u32_1 = sum;
  u32_2 = sum >> 32;
  u32_1 += u32_2;
  if (u32_1 < u32_2) u32_1++;

  u16_1 = u32_1;
  u16_2 = u32_1 >> 16;
  u16_1 += u16_2;
  if (u16_1 < u16_2) u16_1++;

  return ~u16_1;
}
