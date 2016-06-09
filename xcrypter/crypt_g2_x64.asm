sbox: 	times 300 db 0

SECTION .text

SRotateR:		; means String Rotate Right
    push rbp
    mov  rbp, rsp
    sub  rsp, 0x100
	push rbx
	xor  rcx, rcx
	mov  ecx, edx	; the 3rd param is the length of the string
	mov  edx, edi	; the 1st param is how much to rotate each
			; charater
	lea  rax, [rsi] ; the 2nd param is a pointer to the string
.next:	xor  rbx,rbx
	mov  bl, byte [rax+rcx]
	push rcx
	mov  cl, dl
	ror  bl, cl
	pop  rcx
	mov  byte [rax+rcx], bl
	loop SRotateR.next
	xor  rbx,rbx
	mov  cl, dl
	mov  bl, byte [rax]
	ror  bl, cl
	mov  byte [rax], bl
	pop  rbx
    mov  rsp, rbp
    pop  rbp
	ret

SRotateL:		; means String Rotate Left
    push rbp
    mov  rbp, rsp
    sub  rsp, 0x100
	push rbx
	xor  rcx, rcx
	mov  ecx, edx	; the 3rd param is the length of the string
	mov  edx, edi	; the 1st param is how much to rotate each
			; charater
	lea  rax, [rsi] ; the 2nd param is a pointer to the string
.next:	xor  rbx,rbx
	mov  bl, byte [rax+rcx]
	push rcx
	mov  cl, dl
	rol  bl, cl
	pop  rcx
	mov  byte [rax+rcx], bl
	loop SRotateL.next
	xor  rbx,rbx
	mov  cl, dl
	mov  bl, byte [rax]
	rol  bl, cl
	mov  byte [rax], bl
	pop  rbx
    mov  rsp, rbp
    pop  rbp
	ret

GetSBox:
    push rbp
    mov  rbp, rsp
    sub  rsp, 0x100
    push rcx
    push rdx
	lea  rdx, [rdi]
	xor  rcx, rcx
	mov  cl, 0xf8
	xor  rax, rax
.next:
        mov  rax, [rdx+rcx]
        mov [sbox+rcx], rax
        sub cl, 0x7
    loop GetSBox.next
    mov  rax, [rdx]
    mov [sbox], rax
    pop rdx
    pop rcx
    mov  rsp, rbp
    pop  rbp
    ret

Encrypt:
    push rbp
    mov  rbp, rsp
    sub  rsp, 0x100
    push rcx
    push rdx
    ; load the 1st parameter (8-bit char)
    mov  rcx, rdi
    xor  rax, rax
    mov  al, cl
    ; load the 2nd parameter (8-bit char)
    mov  rcx, rsi
    xor  rdx, rdx
    mov  dl, cl

    mov  al, byte [sbox+rax]
    xor  al, byte [sbox+rdx]

    pop  rdx
    pop  rcx
    mov  rsp, rbp
    pop  rbp
    ret

Decrypt:
    push rbp
    mov  rbp, rsp
    sub  rsp, 0x100
    push rcx
    ; load the 2nd parameter (8-bit char)
    mov  rcx, rsi
    xor  rdx, rdx
    mov  dl, cl
    mov  dl, byte [sbox+rdx]
    ; load the 1st parameter (8-bit char)
    mov  rcx, rdi
    xor  rax, rax
    mov  al, cl
    ; get the original s-boxed value
    xor  rax, rdx
    ; do the reverse look up
    xor  rcx, rcx
    mov  cl, 0xff
.next:
    cmp  al, byte [sbox+ecx]
    je Decrypt.found
    loop Decrypt.next
.found:
    mov  al, cl

    pop  rcx
    mov  rsp, rbp
    pop  rbp
    ret
