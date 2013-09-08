[bits 64]

global eval, dim
extern exp, log, sin, cos, tan, atan

section .text

eval:
  ; a[0] = 0x1.5p+5;
  mov rax, 4631107791820423168
  mov [rsi+0], rax
  ; return a[0]
  movq xmm0, [rsi+0]
  ret

dim:
  mov rax, 1
  ret
