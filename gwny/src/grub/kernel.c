#include "display.h"

void kmain(void) {
    reset_display();
    printf("Hi Abhinav!\r\n");
    printf("Yo how are you!?\n");

    for(uint8_t i = 0; i < 5; i++) {
        for(uint8_t j =0; j<i; j++){
            printf("*");
        }
        printf("\n");
    }
}
