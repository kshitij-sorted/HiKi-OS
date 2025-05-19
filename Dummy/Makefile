all: os-image

bootloader.bin: bootloader.asm
	nasm -f bin bootloader.asm -o bootloader.bin

kernel.bin: kernel.c
	i686-elf-gcc -ffreestanding -m32 -c kernel.c -o kernel.o
	i686-elf-ld -T linker.ld -m elf_i386 kernel.o -o kernel.elf
	objcopy -O binary kernel.elf kernel.bin

os-image: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os-image.bin

run: os-image
	qemu-system-i386 -fda os-image.bin

clean:
	rm -f *.bin *.o *.elf
