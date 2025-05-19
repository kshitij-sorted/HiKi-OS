CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS = -nostdlib -T kernel.ld

all: kernel.img

boot.bin: boot.S
	nasm -f bin boot.S -o boot.bin

kernel.bin: kernel.c kernel.ld
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o
	$(LD) $(LDFLAGS) kernel.o -o kernel.bin

kernel.img: boot.bin kernel.bin
	cat boot.bin kernel.bin > kernel.img

clean:
	rm -f *.bin *.o *.img
