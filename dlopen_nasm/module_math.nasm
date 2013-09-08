[bits 64]

global eval, dim
extern exp, log, sin, cos, tan, atan

section .text

eval:
  ; a[0] = x[5];
  mov rax, [rdi+40]
  mov [rsi+0], rax
  ; a[1] = atan(a[0]);
  movq xmm0, [rsi+0]
  push rdi
  push rsi
  call atan
  pop rsi
  pop rdi
  movq [rsi+8], xmm0
  ; a[2] = x[4];
  mov rax, [rdi+32]
  mov [rsi+16], rax
  ; a[3] = tan(a[2]);
  movq xmm0, [rsi+16]
  push rdi
  push rsi
  call tan
  pop rsi
  pop rdi
  movq [rsi+24], xmm0
  ; a[4] = x[3];
  mov rax, [rdi+24]
  mov [rsi+32], rax
  ; a[5] = cos(a[4]);
  movq xmm0, [rsi+32]
  push rdi
  push rsi
  call cos
  pop rsi
  pop rdi
  movq [rsi+40], xmm0
  ; a[6] = x[2];
  mov rax, [rdi+16]
  mov [rsi+48], rax
  ; a[7] = sin(a[6]);
  movq xmm0, [rsi+48]
  push rdi
  push rsi
  call sin
  pop rsi
  pop rdi
  movq [rsi+56], xmm0
  ; a[8] = x[1];
  mov rax, [rdi+8]
  mov [rsi+64], rax
  ; a[9] = log(a[8]);
  movq xmm0, [rsi+64]
  push rdi
  push rsi
  call log
  pop rsi
  pop rdi
  movq [rsi+72], xmm0
  ; a[10] = x[0];
  mov rax, [rdi+0]
  mov [rsi+80], rax
  ; a[11] = exp(a[10]);
  movq xmm0, [rsi+80]
  push rdi
  push rsi
  call exp
  pop rsi
  pop rdi
  movq [rsi+88], xmm0
  ; a[12] = a[11] + a[9];
  movq xmm0, [rsi+88]
  movq xmm1, [rsi+72]
  addpd xmm0, xmm1
  movq [rsi+96], xmm0
  ; a[13] = a[12] + a[7];
  movq xmm0, [rsi+96]
  movq xmm1, [rsi+56]
  addpd xmm0, xmm1
  movq [rsi+104], xmm0
  ; a[14] = a[13] + a[5];
  movq xmm0, [rsi+104]
  movq xmm1, [rsi+40]
  addpd xmm0, xmm1
  movq [rsi+112], xmm0
  ; a[15] = a[14] + a[3];
  movq xmm0, [rsi+112]
  movq xmm1, [rsi+24]
  addpd xmm0, xmm1
  movq [rsi+120], xmm0
  ; a[16] = a[15] + a[1];
  movq xmm0, [rsi+120]
  movq xmm1, [rsi+8]
  addpd xmm0, xmm1
  movq [rsi+128], xmm0
  ; return a[16]
  movq xmm0, [rsi+128]
  ret

dim:
  mov rax, 17
  ret
