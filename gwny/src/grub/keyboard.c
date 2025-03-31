#include "idt.h"
#include "stdint.h"
#include "keyboard.h"

void init_keyboard(){
    irq_install_handler(1, &keyboard_handler);
}

void keyboard_handler(struct InterruptRegisters *regs){

}

