[bits 64]
global foo

section .data
message db "Hello World!",0x0a,0x00

section .text
foo:
mov rax,1
mov rdx,13
mov rsi,message
mov rdi,1
syscall

mov rax,60
mov rdi,0
syscall
