#include <stdint.h>
struct idt_entry_struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_idt();
void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
