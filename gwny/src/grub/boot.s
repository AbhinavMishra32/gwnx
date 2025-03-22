[bits 32]
section .text
global _start
extern kmain


_start:
    mov esp, stack_top              ; Set up stack
    push ebx                        ; Multiboot info structure
    call kmain                      ; Call C kernel function

    hlt                             ; Halt if kmain returns

section .bss
align 16
resb 8192

stack_top:
