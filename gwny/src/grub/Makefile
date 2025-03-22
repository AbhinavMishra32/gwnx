CC = gcc
CC_32 = i386-elf-gcc
LD_32 = i386-elf-ld
ASM = nasm
QEMU = qemu-system-i386
TARGET = gwnx_os 		# This is the folder which converts to ISO
ISO_NAME = gwnx_os		# This is just the ISO name

.PHONY: clean iso

run: $(ISO_NAME)
	$(QEMU) $(ISO_NAME).iso

iso: $(TARGET) kernel
	cp kernel $(TARGET)/boot/kernel
	grub-mkrescue -o $(ISO_NAME).iso gwnx_os --directory=grub_i386/i386-pc

kernel.o: kernel.c
	$(CC_32) -ffreestanding -fno-stack-protector -fno-builtin -c kernel.c -o kernel.o

boot.o: boot.s
	$(ASM) -f elf elf32 boot.s -o boot.o

kernel: boot.o kernel.o
	$(LD) -T linker.ld -o kernel boot.o kernel.o

clean:
	rm -f *.o kernel
