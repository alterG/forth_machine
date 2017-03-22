%include 'lib.inc'
%include 'dictipnary.asm'
%include 'macros.asm'

%define pc r8
%define w r9

section .data

	program_stub: dq 0
	xt_interpreter: dq .interpreter
	.interpreter: dq interpreter_loop

	error_no_word: db 'Word doesnt exist.', 10, 0

section .text



	_start:
	;
	;smth
		mov pc, xt_interpreter
		jmp next

	
	interpreter_loop:
		call read_word
		test rdx, rdx
		; exit if word is empty 
		jz .exit 
		mov rdi, rax
		call find_word
		test rax, rax 
		; if word doesnt exist
		jz .not_found 
		; if word exist
		jmp .interpretate 
		jmp .interpreter_loop		
		
	


	.exit:
		mov rax, 60	
		xor rdi, rdi
		syscall
	
	.not_found:
		call parse_int ; try to parse (if number)
		test rdx, rdx
		jz .print_error
		push rax
		jmp interpreter_loop

	.print_error:
		mov rdi, error_no_word
		call print_string
		mov pc, xt_interpreter
		jmp interpreter_loop

	.interpretate:
		mov rdi, rax
		call cfa
		mov w, rax
		mov [program_stub], rax
		mov pc, program_stub
		jmp next

	next:
		mov w, pc
		add pc, 8
		mov w, [w]
		jmp [w]
