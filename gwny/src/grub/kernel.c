#include "display.h"
#include "gdt.h"

void kmain(void) {
    init_gdt();
    reset_display();
    /* printf("GDT is loaded!\r\n"); */
    printf("Hi Abhinav!\r\n");
    printf("Yo how are you!?\n");

    for(uint8_t i = 0; i < 5; i++) {
        for(uint8_t j =0; j<i; j++){
            printf("*");
        }
        printf("\n");
    }
}
