#include "stdint.h"
#include "util.h"
#include "idt.h"
#include "display.h"
#include "timer.h"

uint64_t ticks;
const uint32_t freq = 100;

void onirq0(struct InterruptRegisters *regs) {
    ticks += 1;

    kprintf("Timer ticked!\n");
}

void init_timer() {
    ticks = 0;
    irq_install_handler(0, &onirq0);

    // 1.1931816666 Mhz
    uint32_t divisor = 1193180/freq;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)(divisor >> 8) & 0xFF);
}
