void kmain(void) {
    char *video_memory = (char*) 0xB8000;
    video_memory[0] = 'H';
    video_memory[1] = 0x07;

    while (1);
}
