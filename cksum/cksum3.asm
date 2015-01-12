bits 64
section .text

; Tentative de gerar um código melhor que o compilador... FAIL!
global cksum3:function
align 16
cksum3:
  mov   rcx,rsi
  xor   rax,rax

  shr   rcx,5             ; RCX contém a quantidade de blocos de 32 bytes.
  jz    .L1               ; Se não existem blocos de 32 bytes, então temos 31 bytes ou menos.
  clc

  ; Acumula blocos de 32 em 32 bytes. Note que só uso ADC para aproveitar o bit carry da soma anterior!
  align 16
.L2:
  adc   rax,[rdi]
  adc   rax,[rdi+8]
  adc   rax,[rdi+16]
  adc   rax,[rdi+24]
  lea   rdi,[rdi+32]      ; Uso LEA para não afetar o carry!
  dec   rcx               ; DEC não afeta carry!
  jnz   .L2
  adc   rax,0

.L1:
  test  rsi,16
  jz    .L3
  add   rax,[rdi]
  adc   rax,[rdi+8]
  adc   rax,0
  add   rdi,16

.L3:
  test  rsi,8
  jz    .L4
  add   rax,[rdi]
  adc   rax,0
  add   rdi,8

.L4:
  test  rsi,4
  jz    .L5
  mov   edx,dword [rdi]
  add   rax,rdx
  adc   rax,0
  add   rdi,4

.L5:
  test  rsi,2
  jz    .L6
  movzx rdx,word [rdi]
  add   rax,rdx
  adc   rax,0
  add   rdi,2

.L6:
  test  rsi,1
  jz    .L7
  movzx rdx,byte [rdi]
  add   rax,rdx
  adc   rax,0

.L7:
  mov   edx,eax
  shr   rax,32
  add   rax,rdx
  adc   rax,0

  mov   edx,eax
  shr   eax,16
  add   ax,dx
  adc   ax,0

  not   ax
  ret

