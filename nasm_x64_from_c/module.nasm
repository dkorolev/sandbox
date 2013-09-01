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
; return exp(x[0]) + log(x[1])
; a[0] = x[0]
; a[0] = exp(a[0])
; a[1] = x[1]
; a[1] = log(x[1])
; a[2] = a[0] + a[1]
; return a[2]
;mov rax, 0
;movq xmm1, rax

; a[0] = x[0]
mov rax, [rdi]
mov [rsi], rax

; a[0] = exp(a[0])
movq xmm0, [rsi]
push rdi
push rsi
call exp
pop rsi
pop rdi
movq [rsi], xmm0

; a[1] = x[1]
mov rax, [rdi+8]
mov [rsi+8], rax

; a[1] = log(a[1])
movq xmm0, [rsi+8]
push rdi
push rsi
call log
pop rsi
pop rdi
movq [rsi+8], xmm0

; a[2] = a[0] + a[1]
movq xmm0, [rsi]
movq xmm1, [rsi+8]
addpd xmm0, xmm1
movq [rsi+16], xmm0

ret

movq xmm0, [rdi]
;push rdi
call exp
;pop rdi
;addpd xmm1, xmm0
ret

;movq xmm0, [rdi+8]
;push rdi
;call log
;pop rdi
;addpd xmm1, xmm0

movq xmm0, xmm1
ret


movq xmm0, [rdi+16]
push rdi
;call sin
pop rdi
subpd xmm1, xmm0
movq xmm0, [rdi+24]
push rdi
call cos
pop rdi
mulpd xmm1, xmm0
movq xmm0, [rdi+32]
push rdi
call atan
pop rdi
divpd xmm1, xmm0
ret
