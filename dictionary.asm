%define word_size 8

section .text

; searching word in dictionary
; rdi - target word
; rax - result (0 if no matches)
find_word:
	xor rax, rax
	mov rsi, [last_word]
	.loop:
		push rsi
		add rsi, 8 ; skip link to previous word
		call string_equals
		pop rsi
		test rax, rax
		jnz .end
		mov rsi, [rsi]
		test rsi, rsi
		jz .end
		xor rax, rax ; probably dont need
		jmp .loop				
	.end:
		mov rax, rsi
	ret

; return xt adress of word
; rdi - target word
; rax - result
cfa:
	xor rax, rax
	add rdi, word_size
	.loop:
		mov al, [rdi]
		test al, 0xFF
		jz .end
		inc rdi
		jmp .loop
	.end:
		add rdi, 2
		mov rax, rdi
	ret
