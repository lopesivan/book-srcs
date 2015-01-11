bits 64
section .text

global TSC_READ:function
TSC_READ:
  push rbx
  cpuid
  pop  rbx
  rdtsc
  shl rdx,32
  or  rax,rdx
  ret
