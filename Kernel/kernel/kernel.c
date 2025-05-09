#include "include/drivers/framebuffer.h"
#include "include/stdio.h"
#include "include/keyboard.h"
#include "include/ports.h"

void kernel_main() {
    framebuffer_init();  // Initialize graphics
    printf("Welcome to HiKiOS!\n");

    while (1) {
        if (inb(0x64) & 1) { // Check if keyboard data is ready
            char scancode = inb(0x60);
            char c = scancode_to_ascii(scancode);
            if (c) {
                printf("%c", c); // Display character to screen
            }
        }
    }
}
