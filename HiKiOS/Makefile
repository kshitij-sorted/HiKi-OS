# Paths
SRC_DIR = kernel
DRIVERS_DIR = drivers
INCLUDE_DIR = include
LIB_DIR = lib
BOOT_DIR = boot

# Files to compile
OBJS = $(BOOT_DIR)/bootloader.o \
       $(SRC_DIR)/kernel.o \
       $(DRIVERS_DIR)/framebuffer.o \
       $(DRIVERS_DIR)/keyboard.o \
       $(LIB_DIR)/ports.o \
       $(LIB_DIR)/stdio.o

# Compiler options
CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR)

# Linker script
LINKER = linker.ld

# Output kernel binary
KERNEL = kernel.bin

all: $(KERNEL)

$(KERNEL): $(OBJS)
	$(CC) -T $(LINKER) -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

# Compile C source files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile bootloader with NASM
$(BOOT_DIR)/bootloader.o: $(BOOT_DIR)/bootloader.asm
	nasm -f bin $< -o $@

clean:
	rm -f $(OBJS) $(KERNEL)
