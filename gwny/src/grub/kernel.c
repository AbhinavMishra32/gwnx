void kmain(void);

volatile char *video = (volatile char*) 0xB8000;

void kmain(void) {
    video[0] = 'H';
    video[1] = 0x07;
    video[2] = 'i';
    video[3] = 0x07;
}
