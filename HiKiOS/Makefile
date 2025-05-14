# Directories
SRC_DIR = kernel
DRIVERS_DIR = drivers
INCLUDE_DIR = include
LIB_DIR = lib
BOOT_DIR = boot

# Files and outputs
BOOTLOADER = $(BOOT_DIR)/bootloader.bin
KERNEL_ELF = kernel.elf
KERNEL_BIN = kernel.bin

OBJS = \
    $(SRC_DIR)/kernel.o \
    $(DRIVERS_DIR)/framebuffer.o \
    $(DRIVERS_DIR)/keyboard.o \
    $(LIB_DIR)/ports.o \
    $(LIB_DIR)/stdio.o

CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR)
LINKER = linker.ld

all: $(KERNEL_BIN)

# Step 1: Build the bootloader binary (raw binary)
$(BOOTLOADER): $(BOOT_DIR)/bootloader.asm
	nasm -f bin $< -o $@

# Step 2: Build the kernel ELF file (linked binary)
$(KERNEL_ELF): $(OBJS)
	$(CC) -T $(LINKER) -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

# Step 3: Combine bootloader and kernel ELF into a final binary
$(KERNEL_BIN): $(BOOTLOADER) $(KERNEL_ELF)
	cat $(BOOTLOADER) $(KERNEL_ELF) > $@

# Step 4: Compile C source files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build
clean:
	rm -f $(OBJS) $(KERNEL_ELF) $(KERNEL_BIN) $(BOOTLOADER)

# Run in QEMU (optional)
run: $(KERNEL_BIN)
	qemu-system-i386 -drive format=raw,file=$(KERNEL_BIN)
