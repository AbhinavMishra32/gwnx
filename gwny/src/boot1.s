[org 0x7C00]

mov bp, 0x9000                  ; Set the stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call switch_to_pm

jmp $

%include "../print/print_string.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

; This is where we arive after protected mode
BEGIN_PM:

    mov ebx, MSG_PROT_MODE
    call print_string_pm            ; Uses 32 bit print routine

    jmp $

; Global variables
MSG_REAL_MODE db " Started in 16 - bit Real Mode " , 0
MSG_PROT_MODE db " Successfully landed in 32 - bit Protected Mode " , 0

; Bootsector padding
times 510 -( $ - $$ ) db 0
dw 0 xaa55
