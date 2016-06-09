%ifdef WIN32
BITS 32
SECTION .bss
	global _SRotateR	; rotates the entire string
	global _SRotateL	; rotates the entire string
	global _GetSBox     ; loads the s-box into the internal memory
	global _Encrypt     ; encrypts a single charater acording to a counter
	global _Decrypt     ; decrypts a single charater acording to a counter
 %include "crypt_g2_x86.asm"
%elifdef ELF32
BITS 32
SECTION .bss
	global SRotateR 	; rotates the entire string
	global SRotateL 	; rotates the entire string
	global GetSBox      ; loads the s-box into the internal memory
	global Encrypt      ; encrypts a single charater acording to a counter
	global Decrypt      ; decrypts a single charater acording to a counter
 %include "crypt_g2_x86.asm"
; relocation jump table to internal symbols
; for only to have one file for all x86 code.
SRotateR:
	jmp  _SRotateR

SRotateL:
	jmp  _SRotateL

GetSBox:
	jmp  _GetSBox

Encrypt:
	jmp  _Encrypt

Decrypt:
	jmp  _Decrypt

%elifdef ELF64
BITS 64
SECTION .bss
	global SRotateR 	; rotates the entire string
	global SRotateL 	; rotates the entire string
	global GetSBox      ; loads the s-box into the internal memory
	global Encrypt      ; encrypts a single charater acording to a counter
	global Decrypt      ; decrypts a single charater acording to a counter
 %include "crypt_g2_x64.asm"
%endif
