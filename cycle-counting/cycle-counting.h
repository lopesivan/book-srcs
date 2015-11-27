#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

#include <x86intrin.h>

/* Macro */
inline unsigned long START_TSC_READ(void)
{
  unsigned long r;

  __asm__ __volatile__ ( "mfence\n"
                         "rdtsc\n"
                         "shll $32,%%rdx\n"
                         "orl  %%rdx,%%rax" : "=a" (r) : : "%rdx" );

  return r;
}

inline unsigned long END_TSC_READ(void)
{
  unsigned long r;

  __asm__ __volatile__ ( "rdtscp\n"
                         "shll $32,%%rdx\n"
                         "orl  %%rdx,%%rax" : "=a" (r) : : "%rcx", "%rdx" );
  return r;
}

#endif

