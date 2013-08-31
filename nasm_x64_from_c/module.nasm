[bits 64]

global foo, add

section .text

foo:
mov rax, 1
mov rdx, rsi
mov rsi, rdi
mov rdi, 1
syscall
ret

add:
movq xmm0, [rdi]
movq xmm1, [rdi+8]
addpd xmm0, xmm1
movq xmm1, [rdi+16]
subpd xmm0, xmm1
movq xmm1, [rdi+24]
mulpd xmm0, xmm1
movq xmm1, [rdi+32]
divpd xmm0, xmm1
ret
