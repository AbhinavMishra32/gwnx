load_kernel:
    mov ah, 0x02            ; BIOS Read Sector function
    mov al, 10              ; Read 10 sectors
    mov ch, 0               ; Cylinder 0
    mov cl, 2               ; Start at sector 2 (sector 1 is bootloader)
    mov dh, 0               ; Head 0
    mov dl, 0x80            ; First hard drive
    mov bx, 0x100000          ; Load kernel at 0x1000
    int 0x13                ; Call BIOS disk read

    jc disk_error           ; Jump if error

    ret                     ; Return to bootloader

disk_error:
    mov si, disk_err_msg
    call print_string
    hlt

disk_err_msg db "Disk read error!", 0
