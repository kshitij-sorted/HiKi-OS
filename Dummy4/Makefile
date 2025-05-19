AS=nasm
ASFLAGS=-f bin
CC=i686-elf-gcc
CFLAGS=-m32 -ffreestanding -O2 -Wall -Wextra -c
LD=i686-elf-ld
LDFLAGS=-T linker.ld -m elf_i386

all: os-image.bin

bootloader.bin: bootloader.asm
	$(AS) $(ASFLAGS) bootloader.asm -o bootloader.bin

kernel.o: kernel.c
	$(CC) $(CFLAGS) kernel.c -o kernel.o

kernel.bin: kernel.o linker.ld
	$(LD) $(LDFLAGS) kernel.o -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin

os-image.bin: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os-image.bin

run: os-image.bin
	qemu-system-i386 -drive format=raw,file=os-image.bin

clean:
	rm -f *.bin *.o *.elf os-image.bin
