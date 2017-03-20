section .text

string_length:	
	push rbx
	mov rax, rdi
	.loop:
	mov bl, [rdi]
	inc rdi
	cmp bl, 0
	jnz .loop
	sub rdi, rax
	mov rax, rdi
	dec rax 
	pop rbx
	ret

print_string:
    mov rsi, rdi
    call string_length
    mov rdx, rax
    mov rax, 1
    mov rdi, 1
    syscall
    ret

print_char:
	
	push rdi
    mov rax, 1
	mov rdx, 1
	mov rsi, rsp
	mov rdi, 1
	syscall
	pop rdi
    ret

print_newline:
    xor rax, rax
    ret


print_uint:

xor rcx,rcx
mov rax, rdi
mov rsi, 10
dec rsp
mov byte[rsp], 0
.loop:
xor rdx, rdx
div rsi
dec rsp
inc rcx
add dl,48
mov [rsp], dl
test rax, rax
jnz .loop
mov rdi, rsp
inc rcx
push rcx
call print_string 
pop rcx 
add rsp, rcx 
ret  


print_int:

	mov r8, rdi
	test r8, r8
	jns .positive
	
	mov rdi, 0x2D
	call print_char
	neg r8
	mov rdi, r8	
	xor r10, r10
	inc r10

	.positive:
	call print_uint
	ret

string_equals:
	xor rax, rax
	.loop:    
	mov r8b, byte[rdi]
	mov r9b, byte[rsi]
	cmp r8b, r9b
	jne .end
	inc rdi
	inc rsi
	cmp r8b, 0
	jne .loop
	mov rax, 1
	ret	

	.end:
	xor rax, rax
    ret


read_char:

    push 0
	mov rax, 0 ; descriptor read
	mov rdi, 0 ; descriptor stdin
	mov rdx, 1 ; 1 byte to read
	mov rsi, rsp ; write in stack
	syscall
	pop rax
    ret 

section .data
word_buffer times 256 db 0

section .text

read_word:

	;.define_first_correct_symbol:	
	;mov rax, 0 ; descriptor read
	;mov rdi, 0 ; descriptor stdin
	;mov rdx, 1 ; 1 byte to read
	;mov rsi, word_buffer ; write in memory
	;syscall
	;mov al, [word_buffer]
	;cmp al, 9
	;jz .define_first_correct_symbol
	;cmp al, 10
	;jz .define_first_correct_symbol
	;cmp al, 36
	;jz .define_first_correct_symbol


	

    ;ret

.start_loop:
    mov rdx, 1 
    mov rdi, 0
    mov rsi, word_buffer
    mov rax, 0
    syscall
	xor r8, r8
	inc r8
	test al, al
	jz .final2
    cmp al, 0x0A
    jz .start_loop
    cmp al, 0x020
    jz .start_loop
    cmp al, 0x09
    jz .start_loop
	
  	xor r8, r8
	xor rdx,rdx
    jz .main_loop

    .main_loop:
    xor rax, rax
    inc rdx
	inc r8
    lea rsi, [word_buffer+rdx]
    push rdx
    mov rdx, 1
    syscall
    pop rdx
    mov rax, [word_buffer+rdx]
	test al, al
	jz .final
    cmp al, 0x20
    jz .final
    cmp al,0x0A
    jz .final
    cmp al, 0x09
    jz .final
    jmp .main_loop

    .ex_final:
	dec r8
    mov rdx, r8
    ret
    .final:
    cmp rdx, 1
    jz .ex_final
    mov al, 0
    mov[word_buffer+rdx], al
    mov rax, word_buffer
	mov rdx, r8
    ret
	
	.final2:
	xor rax, rax
	mov rdx, 0
	ret

	;.final3:
	

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:

	mov r8, 10	; multiplicator
	xor rax, rax
	xor rdx, rdx	
	;xor r10, r10 ; counter
	
	.loop:	
	cmp byte[rdi+ r10], 0x30
	jb .end
	cmp byte[rdi+ r10], 0x39
	ja .end
	mul r8
	mov r9b, byte[rdi+ r10]
	inc r10	
	sub r9b, 0x30
	add rax, r9
	jmp .loop

	.end:
	mov rdx, r10
    ret
 

; rdi points to a string
; returns rax: number, rdx : length
parse_int:

	cmp byte[rdi], 0x2D
    jnz parse_uint 
    inc rdi
    call parse_uint
    neg rax
    test rdx, rdx
    jz .end
    inc rdx
    .end:
    ret
		
	;xor r10, r10
	;cmp byte[rdi], '-'    
	;jne .positive_number	
	
;	push rdi
;	mov rdi, 0x2D
;	call print_char
;	pop rdi
;	inc rdi
;	inc r10
;	
;	.positive_number:	
;	call parse_uint
;	add rdx, r10
;	ret

string_copy:

	mov al, [rdi]
	mov [rsi], al
	inc rdi
	inc rsi
	cmp al, 0
	jnz string_copy

    ret
