[bits 64]

global eval, dim
extern exp, log, sin, cos, tan, atan

section .text

eval:
  ; a[0] = 0x1p+0;
  mov rax, 4607182418800017408
  mov [rsi+0], rax
  ; a[1] = x[0];
  mov rax, [rdi+0]
  mov [rsi+8], rax
  ; a[2] = a[1] + a[0];
  movq xmm0, [rsi+8]
  movq xmm1, [rsi+0]
  addpd xmm0, xmm1
  movq [rsi+16], xmm0
  ; return a[2]
  movq xmm0, [rsi+16]
  ret

dim:
  mov rax, 3
  ret
