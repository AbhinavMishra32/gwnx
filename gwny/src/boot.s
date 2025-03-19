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

    cli                     ; Disable interrupts
    lgdt [gdt_descriptor]   ; Load GDT

    mov eax, cr0
    or eax, 0x01
    mov cr0, eax            ; Enable protected mode

    jmp CODE_SEG:.init_pm
 
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


load_kernel:
    mov ah, 0x02            ; BIOS Read Sector function
    mov al, 10              ; Read 10 sectors
    mov ch, 0               ; Cylinder 0
    mov cl, 2               ; Start at sector 2 (sector 1 is bootloader)
    mov dh, 0               ; Head 0
    mov dl, 0x80            ; First hard drive
    mov bx, 0x100000          ; Load kernel at 0x100000
    int 0x13                ; Call BIOS disk read

    jc disk_error           ; Jump if error

    ret                     ; Return to bootloader

disk_error:
    mov si, disk_err_msg
    call print_string
    hlt

disk_err_msg db "Disk read error!", 0

[bits 32]
.init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; Set stack at high memory
    mov esp, ebp

    call 0x100000           ; Call the kernel at 0x100000

    jmp $                   ; Halt CPU if exit kernel somehow


; ============================
;       GDT Definition
; ============================

gdt_start:
    dq 0                    ; Null descriptor

gdt_code:
    dq 0x00CF9A000000FFFF   ; Code segment (Kernel)

gdt_data:
    dq 0x00CF92000000FFFF   ; Data Segment (Kernel)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start -1           ; GDT size (limit)
    dd gdt_start                        ; GDT base address

; CODE_SEG equ gdt_code - gdt_start
; DATA_SEG equ gdt_data - gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

times 510 - ($-$$) db 0
dw 0xAA55                               ; Boot signature
