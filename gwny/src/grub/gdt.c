#include "gdt.h"

typedef uint32_t addr_t;
extern void gdt_flush(addr_t);

struct gdt_entry gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;
void init_gdt(){
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = (addr_t)&gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0); // Null segment (required convention)
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment

    gdt_flush((addr_t)&gdt_ptr);
    
    //
}

void set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[index].base_low = (base & 0xFFFF);
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high = (base >> 24) & 0xFF;

    gdt_entries[index].limit = (limit & 0xFFFF);
    gdt_entries[index].flags = (limit >> 16) & 0x0F;
    gdt_entries[index].flags = (gran & 0xF0);

    gdt_entries[index].access = access;
}
