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

void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){

}
