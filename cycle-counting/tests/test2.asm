bits 64
section .data
      align 8
q1:   dq    0
q2:   dq    0

section .text

global readtsc:function
  align 8
readtsc:
  push  rbx
  prefetchw [q1]
  cpuid
  rdtsc
  mov     [q1],eax
  mov     [q1+4],edx
  rdtscp
  mov     [q2],eax
  mov     [q2+4],edx
  cpuid
  mov     rax,[q2]
  sub     rax,[q1]
  pop   rbx
  ret
