sbox: 	times 300 db 0

SECTION .text

_SRotateR:			; means String Rotate Right
	push ebp
	mov  ebp, esp
	sub  esp, 0x20
	push ebx
	xor  ecx, ecx
	lea  ebx, [ebp+16]	; the 3rd param is the length of the string
	mov  ecx, [ebx]
	lea  ebx, [ebp+8]	; the 1st param is how much to rotate each
	mov  edx, [ebx]		; charater
	mov  ebx, [ebp+12]
	lea  eax, [ebx]
.next:
        xor  ebx,ebx
        mov  bl, byte [eax+ecx]
        push ecx
        mov  cl, dl
        ror  bl, cl
        pop  ecx
        mov  byte [eax+ecx], bl
	loop _SRotateR.next
	xor  ebx, ebx
	mov  cl, dl
	mov  bl, byte [eax]
	ror  bl, cl
	mov  byte [eax], bl
	pop  ebx
	mov  esp, ebp
	pop  ebp
	ret

_SRotateL:			; means String Rotate Left
	push ebp
	mov  ebp, esp
	sub  esp, 0x20
	push ebx
	xor  ecx, ecx
	lea  ebx, [ebp+16]	; the 3rd param is the length of the string
	mov  ecx, [ebx]
	lea  ebx, [ebp+8]	; the 1st param is how much to rotate each
	mov  edx, [ebx]		; charater
	mov  ebx, [ebp+12]
	lea  eax, [ebx]
.next:
        xor  ebx,ebx
        mov  bl, byte [eax+ecx]
        push ecx
        mov  cl, dl
        rol  bl, cl
        pop  ecx
        mov  byte [eax+ecx], bl
	loop _SRotateL.next
	xor  ebx,ebx
	mov  cl, dl
	mov  bl, byte [eax]
	rol  bl, cl
	mov  byte [eax], bl
	pop  ebx
	mov  esp, ebp
	pop  ebp
	ret

_GetSBox:
    push ebp
    mov  ebp, esp
    sub  esp, 0x20
	push ecx
	push edx
	mov  edx, [ebp+8]
	xor  ecx, ecx
    mov  cl, 0xfc
	xor  eax, eax
.next:
        mov  eax, [edx+ecx]
        mov [ecx+sbox], eax
        sub cx, 0x0003
    loop _GetSBox.next
    mov  eax, [edx]
    mov [sbox], eax
    pop edx
    pop ecx
    mov esp, ebp
    pop ebp
    ret

_Encrypt:
    push ebp
    mov  ebp, esp
    sub  esp, 0x20
    push ecx
    ; load the 1st parameter
    mov  eax, [ebp+8]
    lea  ecx, [eax]
    xor  eax, eax
    mov  al, cl
    ; load the 2nd parameter
    mov  edx, [ebp+12]
    lea  ecx, [edx]
    xor  edx, edx
    mov  dl, cl

    mov  al, byte [eax+sbox]
    xor  al, byte [edx+sbox]
    pop  ecx
    mov  esp, ebp
    pop  ebp
    ret

_Decrypt:
    push ebp
    mov  ebp, esp
    sub  esp, 0x20
    push ecx
    ; load the 2nd parameter (8bit char)
    mov  edx, [ebp+12]
    lea  ecx, [edx]
    xor  edx, edx
    mov  dl, cl
    mov  dl, byte [edx+sbox]
    ; load the 1st parameter (8bit char)
    mov  eax, [ebp+8]
    lea  ecx, [eax]
    xor  eax, eax
    mov  al, cl
    ; get the original s-boxed value
    xor  eax, edx
    ; do the reverse look up
    xor  ecx, ecx
    mov  cx, 0xff
.next:
    cmp  al, byte [ecx+sbox]
    je _Decrypt.found
    loop _Decrypt.next
.found:
    mov  al, cl

    pop  ecx
    mov  esp, ebp
    pop  ebp
    ret
