# Paths
SRC_DIR = kernel
DRIVERS_DIR = drivers
INCLUDE_DIR = include
LIB_DIR = lib

# Files to compile
OBJS = $(SRC_DIR)/kernel.o \
       $(DRIVERS_DIR)/framebuffer.o \
       $(DRIVERS_DIR)/keyboard.o \
       $(LIB_DIR)/ports.o

# Compiler options
CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE_DIR)

# Linker script (make sure you have one)
LINKER = linker.ld

# Output kernel binary
KERNEL = kernel.bin

all: $(KERNEL)

$(KERNEL): $(OBJS)
	$(CC) -T $(LINKER) -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(KERNEL)

