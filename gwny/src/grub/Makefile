CC := gcc
CC_32 := i386-elf-gcc
LD_32 := i386-elf-ld
ASM := nasm
QEMU := qemu-system-i386
TARGET := gwnx_os# This is the folder which converts to ISO
ISO_NAME := gwnx_os# This is just the ISO name

CARGS = -m32 -nostdlib -nostdinc -nodefaultlibs -nostartfiles -ffreestanding -fno-stack-protector -fno-builtin -Iinclude -Wall -Wextra -Werror

.PHONY: clean iso run dockbuild compiler-flags

SRC_C = kernel.c display.c
OBJ_C = $(SRC_C:.c=.o)		# converts all C files in SRC_C to object files

run: $(ISO_NAME).iso
	$(QEMU) $(ISO_NAME).iso

iso: kernel
	mkdir -p $(TARGET)/boot
	cp kernel/kernel.elf $(TARGET)/boot/
	@echo "Copied kernel to boot successfully"
	docker run --rm -v $(PWD):/work -w /work grub-mkrescue-image \
		grub-mkrescue -o $(ISO_NAME).iso $(TARGET) --directory=/work/grub_i386/i386-pc
	@echo "ISO Ready"

%.o: %.c
	$(CC_32) $(CARGS) -c $< -o $@

kernel.o: kernel.c
	$(CC_32) $(CARGS) -c kernel.c -o kernel.o

boot.o: boot.s
	$(ASM) -f elf32 boot.s -o boot.o

kernel: boot.o $(OBJ_C)
	mkdir -p kernel
	$(LD_32) -T linker.ld -o kernel/kernel.elf boot.o $(OBJ_C)

dockbuild:
	docker build -t grub-mkrescue-image .

compiler-flags:
	echo "-I$(shell pwd)/include" > compile_flags.txt

clean:
	rm -f *.o kernel/kernel.elf
