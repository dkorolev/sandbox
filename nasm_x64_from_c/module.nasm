[bits 64]

global foo, do_math
extern exp, log, sin, cos, tan, atan

section .text

foo:
mov rax, 1
mov rdx, rsi
mov rsi, rdi
mov rdi, 1
syscall
ret

do_math:
; return exp(x[0]) + log(x[1]) + sin(x[2])
; a[0] = x[0]
; a[1] = exp(a[0])
; a[2] = x[1]
; a[3] = log(a[2])
; a[4] = x[2]
; a[5] = sin(a[4])
; a[6] = a[1] + a[3]
; a[7] = a[6] + a[5]
; return a[7]

; a[0] = x[0]
mov rax, [rdi]
mov [rsi], rax

; a[1] = exp(a[0])
movq xmm0, [rsi]
push rdi
push rsi
call exp
pop rsi
pop rdi
movq [rsi+8], xmm0

; a[2] = x[1]
mov rax, [rdi+8]
mov [rsi+16], rax

; a[3] = log(a[2])
movq xmm0, [rsi+16]
push rdi
push rsi
call log
pop rsi
pop rdi
movq [rsi+24], xmm0

; a[4] = x[2]
mov rax, [rdi + 16]
mov [rsi + 32], rax

; a[5] = sin(a[4])
movq xmm0, [rsi+32]
push rdi
push rsi
call sin
pop rsi
pop rdi
movq [rsi+40], xmm0

; a[6] = a[1] + a[3]
movq xmm0, [rsi+8]
movq xmm1, [rsi+24]
addpd xmm0, xmm1
movq [rsi+48], xmm0

; a[7] = a[6] + a[5]
movq xmm0, [rsi+48]
movq xmm1, [rsi+40]
addpd xmm0, xmm1
movq [rsi+56], xmm0

; return a[7]
movq xmm0, [rsi+56]
ret
