.PHONY: clean iso run dockbuild compiler-flags

all: iso

BUILD ?= Debug

CC := gcc
CC_32 := i386-elf-gcc
LD_32 := i386-elf-ld
ASM := nasm
QEMU := qemu-system-i386
QEMU-DEBUG := qemu-system-i386 -s -S
TARGET := gwnx_os# This is the folder which converts to ISO
ISO_NAME := gwnx_os# This is just the ISO name

ifeq ($(BUILD), Debug)
	CARGS := -g -m32 -nostdlib -nostdinc -nodefaultlibs -nostartfiles -ffreestanding -fno-stack-protector -fno-builtin -Iinclude
else ifeq ($(BUILD), Release)
	CARGS := -m32 -nostdlib -nostdinc -nodefaultlibs -nostartfiles -ffreestanding -fno-stack-protector -fno-builtin -Iinclude
endif


SRC_C = kernel.c display.c gdt.c
OBJ_C = $(SRC_C:.c=.o)		# converts all C files in SRC_C to object files

iso: kernel
	mkdir -p $(TARGET)/boot
	cp kernel/kernel.elf $(TARGET)/boot/
	@echo "Copied kernel to boot successfully"
	docker run --rm -v $(PWD):/work -w /work grub-mkrescue-image \
		grub-mkrescue -o $(ISO_NAME).iso $(TARGET) --directory=/work/grub_i386/i386-pc
	@echo "ISO Ready"

run: $(ISO_NAME).iso
	$(QEMU) $(ISO_NAME).iso

debug: $(ISO_NAME).iso
	$(QEMU-DEBUG) $(ISO_NAME).iso

%.o: %.c
	$(CC_32) $(CARGS) -c $< -o $@
boot.o: boot.s
	$(ASM) -f elf32 boot.s -o boot.o

gdts.o: gdt.s
	$(ASM) -f elf32 gdt.s -o gdts.o

kernel: boot.o gdts.o $(OBJ_C)
	mkdir -p kernel
	$(LD_32) -T linker.ld -o kernel/kernel.elf boot.o gdts.o $(OBJ_C)

dockbuild:
	docker build -t grub-mkrescue-image .

compiler-flags:
	echo "-I$(shell pwd)/include" > compile_flags.txt

clean:
	rm -f *.o kernel/kernel.elf
