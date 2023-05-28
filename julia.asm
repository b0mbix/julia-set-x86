; ---------------- Passed arguments ----------------
; width     rdi
; height    rsi
; left_x    xmm0
; up_y      xmm1
; scale     xmm2
; c_re      xmm3
; c_im      xmm4
; *data     rdx
; pitch     rcx
; --------------------------------------------------

section .text
global julia

julia:
	push rbp
	mov rbp, rsp
end:
	mov rsp, rbp
	pop rbp
	ret