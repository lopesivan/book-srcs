bits 64
section .text

;  RDI = ptr
;  RSI = count
global cksumasm:function
cksumasm:
  xor rax,rax
  jmp .L1
.L2:
  sub rsi,8
  add rax,[rdi]  
  adc rax,0
  add rdi,8
.L1:
  cmp rsi,8
  jae .L2

  cmp rsi,4
  jb  .L3
  mov r8d,[rdi]
  sub rsi,4
  add rax,r8
  adc rax,0
  add rdi,4

.L3:
  cmp rsi,2
  jb  .L4
  movzx r8,word [rdi]
  sub rsi,2
  add rax,r8
  add rax,0
  add rdi,2

.L4:
  or rsi,rsi
  jz .L5
  movzx r8d,byte [rdi]
  add rax,r8
  adc rax,0

.L5:
  mov r8,rax
  shr r8,32
  add eax,r8d
  adc rax,0
  mov r8d,eax
  shr r8d,16
  add ax,r8w
  add ax,0
  not ax
  ret

