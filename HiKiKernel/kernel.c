
void kernel_main(void) __attribute__((cdecl));
void kernel_main(void) {
    const char *msg = "HiKiOS: Kernel in C is running!";
    char *vga = (char *)0xB8000;
    for (int i = 0; msg[i] != '\0'; i++) {
        vga[i * 2] = msg[i];      // ASCII character
        vga[i * 2 + 1] = 0x07;    // Color byte
    }

    while (1);
}
