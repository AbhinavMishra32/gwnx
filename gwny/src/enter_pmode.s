switch_to_pmode:
    cli                         ; Disable interrupts
    lgdt [gdt_descriptor]       ; Load Global Descriptor Table (GDT)

    mov eax, cr0
    or eax, 0x1                 ; Set the PE (Protected Mode Enable) bit
    mov cr0, eax

    jmp CODE_SEG:init_pm        ; Far jump to clear instruction queue

    
