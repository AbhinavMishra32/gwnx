#include "display.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

void kmain(void) {
    reset_display();
    init_gdt();
    kprintf("GDT initialized!\r\n");
    kprintf("Hello!\r\n");
    init_idt();
    kprintf("IDT initialized!\r\n");
    init_timer();
    
    for(;;);

    /* int x = 1; */
    /* int y = 0; */
    /**/
    /* int z = x/y; */
}
