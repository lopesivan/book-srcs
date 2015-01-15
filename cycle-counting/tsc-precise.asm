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

section .text

global TSC_READ_START:function
global TSC_READ_END:function

; Declarações equivalentes:
;   static unsigned long count, tmp;
;
; No entanto, coloquei na sessão .text para aproveitar
; o modo de endereçamento relativo via RIP.
;
        align 8
count:  dq  0
tmp:    dq  0

; Protótipo:
;   void TSC_READ_START(void);
;
  align 8
TSC_READ_START:
  push  rbx
  cpuid
  prefetchw [rel count]   ; Tenta garantir que as duas variáveis temporárias
                          ; estejam no cache e prontas para serem escritas.
  rdtsc
  mov   [rel count],eax   ; 1.5 ciclos
  mov   [rel count+4],edx ; 1.5 ciclos
  pop   rbx               ; 1.5 ciclos
  ret                     ; 8 ciclos.

; Protótipo:
;   long TSC_READ_END(void);
;
  align 8
TSC_READ_END:
                      ; call para essa função toma 1 ciclo.
  rdtscp
  mov   [rel tmp],eax
  mov   [rel tmp+4],edx
  push  rbx
  cpuid
  mov   rax,[rel count]
  sub   rax,[rel tmp]
  sub   rax,14        ; subtrai todos os "13.5" ciclos "extras".
  cmp   rax,0         ; if (rax <= 0) rax = 1; /* Só para garantir! */
  jg    .L1
  mov   rax,1
.L1:
  pop   rbx
  ret
