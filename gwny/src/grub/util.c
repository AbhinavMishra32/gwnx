#include "util.h"
#include <stdint.h>

void memset(void *dest, char val, uint32_t count){
    char *temp = (char* )dest;
    for (; count != 0; count --){
        *temp ++ = val;
    }
}

void outb(uint16_t port, uint8_t value){
    asm volatile ("outb %1 %0" : : "dN" (port), "a" (value));
}
