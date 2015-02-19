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
; o manual de otimização da Intel. Ele também foi verificado através da
; rotina de teste no diretório ./tests/ usando:
;
;   $ for i in {1..100}; do ./test; done
;
; O menor valor lido foi de 48, o maior foi de 112. O valor 52 aparece em
; minhas medidas algumas vezes e é condizente com o calculo do gasto dos 13.5 ciclos de máquina.
;
WASTED_CYCLES equ 10

section .data
; Essas variáveis temporárias não são exportadas!
;
; Declarações equivalentes:
;   static unsigned long count, tmp;
;
        align 16
count:  dq    0
tmp:    dq    0

section .text

global TSC_READ_START:function
global TSC_READ_END:function

  align 16
; Protótipo:
;   void TSC_READ_START(void);
;
TSC_READ_START:
  prefetchw [count]   ; Tenta garantir que as duas variáveis temporárias
                      ; estejam no cache e prontas para serem escritas.
  push  rbx
  cpuid
  pop   rbx
  rdtsc
  mov   [count],eax   ; 1.5 ciclos
  mov   [count+4],edx ; 1.5 ciclos
  ret                 ; 8 ciclos.

; Protótipo:
;   unsigned long TSC_READ_END(void);
;
  align 16
TSC_READ_END:
                      ; call para essa função toma 1 ciclo.
  rdtscp
  mov   [tmp],eax
  mov   [tmp+4],edx
  push  rbx
  cpuid
  mov   rax,[tmp]
  sub   rax,[count]
  sub   rax,WASTED_CYCLES  ; subtrai todos os "13.5" ciclos "extras".

  ; if (rax <= 0)
  ;   rax = 1;
  mov    rbx,1
  cmovle rax,rbx

  pop   rbx
  ret
