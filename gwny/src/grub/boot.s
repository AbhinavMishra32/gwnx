[BITS 32]

section .text
    ALIGN 4
    DD 0x1BADB002               ; magic number
    DD 0X00000000
    DD -(0x1BADB002 + 0x00000000)

global start
extern kmain

start:
    cli
    mov esp, stack_space
    call kmain
    hlt

HaltKernal:
    cli
    hlt
    jmp HaltKernal

section .bss
resb 8192
stack_space:
