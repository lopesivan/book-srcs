#include <memory.h>
#include <cpuid.h>

__attribute__((noinline)) static const char *get_cpu_id(void)
{
  static char cpuAux[12];
  int *p;
  int a, b, c, d;

  __cpuid(0, a, b, c, d);
  p = (int *)cpuAux;
  *p++ = b;
  *p++ = d;
  *p = c;

  return cpuAux;
}

int cpu_is_intel(void)
{
  static char cpustr[] = "GenuineIntel";
 
  return memcmp(cpustr, get_cpu_id(), 12) == 0;
}

int cpu_is_amd(void)
{
  static char cpustr[] = "AuthenticAMD";

  return memcmp(cpustr, get_cpu_id(), 12) == 0;
}

/* Uso:
 *   if (get_cpu_features() & bit_SSE2) ...
 */
int get_cpu_features(void)
{
  int a, b, c, d, _tmp;

  __cpuid(1,a,b,c,d);

  /* Os bits não se sobrepõem, então é seguro fazer um OR com os valores mascarados. */
  c &= bit_SSE3 | bit_SSSE3 | bit_FMA | bit_SSE4_1 | bit_SSE4_2 | bit_AVX | bit_F16C;
  d &= bit_SSE | bit_SSE2 | bit_MMX;
  _tmp = c | d;

  /* Pega outras extensões. */
  __cpuid_count(7,0,a,b,c,d);

  /* Os bits ainda não se sobrepõem, então é seguro fazer um OR com os valores mascarados. */
  b &= bit_BMI | bit_AVX2 | bit_BMI2;
  
  return _tmp | b;
}
