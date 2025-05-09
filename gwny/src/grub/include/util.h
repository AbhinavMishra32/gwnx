#ifndef UTIL_H
#define UTIL_H

#include "stdint.h"

void memset(void *dest, char val, uint32_t count);
void outb(uint16_t port, uint8_t value);
char inb(uint16_t port);

struct InterruptRegisters {
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};

#endif
