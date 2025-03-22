CC := gcc
CC_32 := i386-elf-gcc
LD_32 := i386-elf-ld
ASM := nasm
QEMU := qemu-system-i386
TARGET := gwnx_os# This is the folder which converts to ISO
ISO_NAME := gwnx_os# This is just the ISO name

.PHONY: clean iso run dockbuild

run: $(ISO_NAME).iso
	$(QEMU) $(ISO_NAME).iso

iso: kernel
	mkdir -p $(TARGET)/boot
	cp kernel $(TARGET)/boot/
	@echo "Copied kernel to boot successfully"
	docker run --rm -v $(PWD):/work -w /work grub-mkrescue-image \
		grub-mkrescue -o $(ISO_NAME).iso $(TARGET) --directory=/work/grub_i386/i386-pc

kernel.o: kernel.c
	$(CC_32) -ffreestanding -fno-stack-protector -fno-builtin -c kernel.c -o kernel.o

boot.o: boot.s
	$(ASM) -f elf32 boot.s -o boot.o

kernel: boot.o kernel.o
	$(LD_32) -T linker.ld -o kernel boot.o kernel.o

dockbuild:
	docker build -t grub-mkrescue-image .

clean:
	rm -f *.o kernel
