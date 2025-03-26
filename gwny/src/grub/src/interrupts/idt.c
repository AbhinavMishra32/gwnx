#include "idt.h"
#include "stdint.h"
#include "util.h"
#include "display.h"

struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32_t);

void init_idt(){
    idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
    idt_ptr.base = (uint32_t) &idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

    // 0x20 is for commands and 0x21 data
    // 0xA0 commands and 0xA1 data

    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);

void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){

}
