#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

/* Macro */
#define _TSC_READ(x) \
  { \
    unsigned long lo, hi; \

    __asm__ __volatile__ ( \
      "cpuid;" \
      "rdtsc;" \
      : "=a" (lo), "=d" (hi) : : "%rbx", "%rcx" \
    ); \
    \
    (x) = (hi << 32) lo; \
  }

/* Função externa, em tsc.asm. */
extern unsigned long TSC_READ(void);

#endif

