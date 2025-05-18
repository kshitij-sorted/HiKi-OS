#include "drivers/framebuffer.h"
#include "stdio.h"
#include "keyboard.h"
#include "ports.h"

void kernel_main() {
    fb_init(0,0,0,0,0);  // Initialize graphics
    fb_print("Welcome to HiKiOS!\n");

    while (1) {
        if (inb(0x64) & 1) { // Check if keyboard data is ready
            char scancode = inb(0x60);
            char c = scancode_to_ascii(scancode);
            if (c) {
                putchar(c); // Display character to screen
            }
        }
    }
}
void print(const char *str) {
    char *video = (char *) 0xB8000;  // VGA text buffer starting address
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07;  // White text on black background
    }
}

