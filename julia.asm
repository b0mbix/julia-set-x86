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
; x         r8
; --------------------------------------------------

section .text
global julia

julia:
	push rbp
	mov rbp, rsp

row_loop:
    mov r9, rdi     ; column counter

    pixel_loop:
        mov rbx, r8     ; color is the x value

        mov BYTE [rdx], bl
        inc rdx
        mov BYTE [rdx], bl
        inc rdx
        mov BYTE [rdx], bl
        inc rdx
        dec r9      ; if column is not zero, go to next point
        jnz pixel_loop

    add rdx, rcx
    add rdx, rcx

    dec rsi         ; if row is not zero, go to next row
    jnz row_loop

end:
	mov rsp, rbp
	pop rbp
	ret