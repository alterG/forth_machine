%define link 0 ; start value for link

; macro for native words with 3 arguments: word name, word identifier, flags
%macro native 3
section .data
w_ %+ %2:
	%%link dq link ; previous word
%define link %%link ; 
	db %1, 0 ; word name
	db %3 ; flags
xt_ %+ %2: ; label to implementation
dq %2 %+ _impl
section .text
%2 %+ _impl: ; implementation
%endmacro

; native with 2 arguments 
%macro native 2
native %1 %2
%endmacro

; macro for colon words with 3 arguments: word name, word identifier, flags
%macro colon 3
section .data
w_ %+ %2:
	%%link dq link
%define link %%link
	db %1, 0
	db %3
xt_ %+ %2:
	dq docol
%endmacro

; colon with 2 arguments
%macro colon 2
colon %1 %2
%endmacro
