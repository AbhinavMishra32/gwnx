CC = gcc
CC_32 = i386-elf-gcc
LD_32 = i386-elf-ld
ASM = nasm

.PHONY: clean

kernel.o: kernel.c
	$(CC_32) -ffreestanding -fno-stack-protector -fno-builtin -c kernel.c -o kernel.o

boot.o: boot.s
	$(ASM) -f elf elf32 boot.s -o boot.o

kernel: boot.o kernel.o
	$(LD) -T linker.ld -o kernel boot.o kernel.o

clean:
	rm -f *.o kernel
