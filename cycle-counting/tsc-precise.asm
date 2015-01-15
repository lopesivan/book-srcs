;
; Contador de ciclos mais "preciso", de acordo com a latência documentada
; pelo manual de otimização da Intel.
;
; Forma de uso:
;
;   TSC_READ_START();
;   f();  /* função sob teste. */
;   c = TSC_READ_END();
;
; 'c' conterá a quantidade de ciclos gastos APENAS pela chamada à função 'f'.
;
; Os alinhamentos são usados para não termos fragmentação no cache L1.
;

bits 64

; Declarações equivalentes:
;   static unsigned long count, tmp;
section .bss
      align 8
tmp:  resq  1

section .data
        align 8
count:  dq  0

section .text

global TSC_READ_START
global TSC_READ_END

; Protótipo:
;   void TSC_READ_START(void);
  align 8
TSC_READ_START:
  push  rbx
  cpuid
  rdtsc
  mov   [count],eax   ; 1.5 ciclos
  mov   [count+4],edx ; 1.5 ciclos
  pop   rbx           ; 1.5 ciclos
  ret                 ; 8 ciclos.

; Protótipo:
;   unsigned long TSC_READ_END(void);
  align 8
TSC_READ_END:
                      ; call para essa função toma 1 ciclo.
  rdtscp
  mov   [tmp],eax
  mov   [tmp+4],edx
  push  rbx
  cpuid
  mov   rax,[count]
  sub   rax,[tmp]
  sub   rax,14        ; subtrai todos os "13.5" ciclos "extras".
  pop   rbx
  ret
