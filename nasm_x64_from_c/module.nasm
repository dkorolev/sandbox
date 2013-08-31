[bits 64]

global foo, bar

section .text

foo:
mov rax, 1
mov rdx, rsi
mov rsi, rdi
mov rdi, 1
syscall
ret

bar:
movq xmm0, [rdi+8]  ; extracts x[1] when presented an array of doubles.
ret
