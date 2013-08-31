[bits 64]

global foo

section .text
foo:
mov rax, 1
mov rdx, rsi
mov rsi, rdi
mov rdi, 1
syscall

mov rax,60
mov rdi,0
syscall
