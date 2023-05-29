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
; ----------------- Used registers -----------------
; xmm0 - current x pixel
; xmm1 - current y pixel
; xmm2 - scale
; xmm3 - c real part
; xmm4 - c imaginary part
; xmm5 - calculated number real part
; xmm6 - calculated number imaginary part
; xmm7 - real part squared, calculated module squared
; xmm8 - imaginary part squared
; xmm9 - temporary register to perform calculations
; xmm10 - saved left_x to use for row start
; rdi - width
; r8 - column counter
; rsi - row counter
; rdx - data pointer
; rcx - pitch
; rax - color, iteration
; --------------------------------------------------

section .text
global julia

julia:
	push rbp
	mov rbp, rsp
    movapd xmm10, xmm0

row_loop:
    mov r8, rdi     ; column counter
    movapd xmm0, xmm10 ; set x to left_x

    pixel_loop:
        mov rbx, 0      ; paint color, iteration
        movapd xmm5, xmm0
        movapd xmm6, xmm1

        algo_loop:
            ; real part squared
            movapd xmm7, xmm5
            mulsd xmm7, xmm7
            ; imaginary part squared
            movapd xmm8, xmm6
            mulsd xmm8, xmm8

            ; y = 2xy + cy
            mulsd xmm6, xmm5 ; x*y
            mov rax,2
            cvtsi2sd xmm9, rax
            mulsd xmm6, xmm9 ; *2
            addsd xmm6, xmm4 ; +cy

            ; x = x^2 - y^2 + cx
            movapd xmm5, xmm7 ; x^2
            subsd xmm5, xmm8 ; -y^2
            addsd xmm5, xmm3 ; +cx

            ; xmm7 = module squared
            addsd xmm7, xmm8

            inc bl

            ; if module squared > 4: draw
            mov rax, 4
            cvtsi2sd xmm9, rax
            comisd xmm7, xmm9
            jnb draw

            cmp rbx, 255
            jb algo_loop

    draw:
        mov byte [rdx], bl
        inc rdx
        mov byte [rdx], bl
        inc rdx
        mov byte [rdx], bl
        inc rdx
        addsd xmm0, xmm2 ; go to next pixel
        dec r8      ; if column is not zero, go to next point
        jnz pixel_loop

    add rdx, rcx
    add rdx, rcx

    subsd xmm1, xmm2 ; go to next pixel
    dec rsi         ; if row is not zero, go to next row
    jnz row_loop

end:
	mov rsp, rbp
	pop rbp
	ret