#include "gdt.h"
#include "util.h"
#include "stdint.h"

typedef uint32_t addr_t;
extern void gdt_flush(addr_t);
extern void tss_flush();

struct gdt_entry gdt_entries[6];
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;

void init_gdt(){
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 6) - 1;
    gdt_ptr.base = (addr_t)&gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0); // Null segment (required convention)
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment
    write_tss(5, 0x10, 0x0);
    gdt_flush((addr_t)&gdt_ptr);

    tss_flush();
    
    //
}

void write_tss(uint32_t num, uint16_t ss0, uint32_t esp0){
    uint32_t base = (uint32_t) &tss_entry;
    uint32_t limit = sizeof(tss_entry) - 1;

    set_gdt_entry(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;

    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
}

void set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[index].base_low = (base & 0xFFFF);
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high = (base >> 24) & 0xFF;

    gdt_entries[index].limit = (limit & 0xFFFF);
    gdt_entries[index].flags = (limit >> 16) & 0x0F;
    gdt_entries[index].flags |= (gran & 0xF0);

    gdt_entries[index].access = access;
}
