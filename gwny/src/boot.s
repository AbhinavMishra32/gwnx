[ORG 0x7C00]
[BITS 16]


start:
    cli                     ; Disable interrupts
    mov ax, 0x07C0          ; Set up segement registers
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00          ; This is at top and will grow downwards

    ; Print "Booting..."
    mov si, boot_msg
    call print_string

    ; Load kernel from disk
    call load_kernel

    ; Switch to protected mode
    call switch_pmode

    ; If we reach here, something went wrong
    hlt

boot_msg db "Booting OS...", 0

print_string:
    pusha                   ; Save all registers

next_char:
    lodsb                   ; Load next character from DS:SI into Al
    or al, al               ; Check if its the null terminator (0)
    jz done                 ; If so, we're done

    mov ah, 0x0E            ; BIOS teletype function
    mov bh, 0x00            ; Page number (default)
    int 0x10                ; Call BIOS interrupt to print character

    jmp next_char           ; Repeat for the next character

done:
    popa                    ; Restore registers
    ret                     ; Return to caller
