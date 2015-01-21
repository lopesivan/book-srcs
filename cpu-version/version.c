#include <stdio.h>
#include <string.h>
#include <cpuid.h>

struct version_s {
  unsigned stepping:4;
  unsigned model:4;
  unsigned family:4;
  unsigned type:2;
  unsigned :2;
  unsigned exmodel:4;
  unsigned exfamily:8;
};

static const char *processor_types[] =
  { "Original OEM", "Overdrive", "Dual", "Reserved" };

const char *getBrandString(void);

void main(void)
{
  unsigned a, b, c, d;
  int type, family, model, stepping;

  __cpuid(1, a, b, c, d);
  type = ((struct version_s *)&a)->type;
  family = ((struct version_s *)&a)->family;
  model = ((struct version_s *)&a)->model;
  stepping = ((struct version_s *)&a)->stepping;

  printf("Seu processador: \"%s\"\n"
         "\tTipo: %s\n"
         "\tFamília: 0x%02X\n"
         "\tModelo: 0x%02X\n"
         "\tStepping: 0x%02X\n",
         getBrandString(),
         processor_types[type],
         family, model, stepping);
}

const char *getBrandString(void)
{
  static char str[49];
  unsigned *p;
  size_t idx;
  unsigned a, b, c, d;
  int i;

  p = (unsigned *)str;
  for (i = 2; i <= 4; i++)
  {
    __cpuid(0x80000000 + i, a, b, c, d);
    *p++ = a;
    *p++ = b;
    *p++ = c;
    *p++ = d;
  }

  *(char *)p = '\0';

  /* Retorna string a partir do ponto onde não há espaços. */
  return (const char *)str + strspn(str, " ");
}
