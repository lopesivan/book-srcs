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

; Este valor é calculado com base na latência das instruções, de acordo com
; o manual de otimização da Intel.
WASTED_CYCLES equ 12

section .data
; Essas variáveis temporárias não são exportadas!
;
; Declarações equivalentes:
;   static unsigned long count, tmp;
;
            align 16
old_count:  dq    0
tmp:        dq    0

section .text

global TSC_READ_START:function
global TSC_READ_END:function

align 16
; Protótipo:
;   void TSC_READ_START(void);
;
TSC_READ_START:
  ; Serializa CPU.
  xor   eax,eax
  push  rbx
  cpuid
  pop   rbx

  ; Certifica-se que todas as leituras e escritas pendentes
  ; sejam feitas.
  mfence

  rdtsc
  mov   [old_count],eax   ; 1.5 ciclos
  mov   [old_count+4],edx ; 1.5 ciclos

  ret                     ; 8 ciclos.

; Protótipo:
;   unsigned long TSC_READ_END(void);
;
; OBS: CALL para essa função toma 1 ciclo.
  align 16
TSC_READ_END:
  rdtscp              ; Lê TSC, serializando o processador.
                      ; Obs: As partes superiores de RAX e RDX estarão zeradas!

  ; Faz RAX <- EDX:EAX.
  shl   rdx,32
  or    rax,rdx

  ; RAX = TSC - old_count - WASTED_CYCLES
  sub   rax,[old_count]
  sbb   rax,WASTED_CYCLES

  ; if (rax <= 0)
  ;   rax = 1;
  mov    rdx,1
  cmovle rax,rdx

  ret
