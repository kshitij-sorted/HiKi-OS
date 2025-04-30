#include "include/drivers/framebuffer.h"
#include "include/stdio.h"

void kernel_main() {
    framebuffer_init();  // Initialize graphics mode (assumes you've written this)
    printf("Welcome to HiKiOS!\n");

    while (1) {
        // Infinite loop to prevent kernel from exiting
    }
}
