#include <stdint.h>

#define VIDEO_MEMORY ((volatile uint16_t*)0xB8000)
#define KEYBOARD_PORT 0x60

volatile uint16_t cursor_pos = 0;

// Print character to screen
void print_char(char c) {
    if (c == '\n') {
        cursor_pos += 80 - (cursor_pos % 80);
        return;
    }
    VIDEO_MEMORY[cursor_pos++] = (uint8_t)c | (0x07 << 8);
}

// Read byte from port
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Map scancode to ASCII (basic)
char scancode_to_char(uint8_t sc) {
    static const char map[128] = {
        0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
        0,  'a','s','d','f','g','h','j','k','l',';','\'','`', 0,
        '\\','z','x','c','v','b','n','m',',','.','/', 0,  '*', 0,
        ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    if (sc > 127) return 0;
    return map[sc];
}

void kernel_main() {
    // Clear screen
    for (int i = 0; i < 80*25; i++) {
        VIDEO_MEMORY[i] = (uint16_t)(' ') | (0x07 << 8);
    }
    cursor_pos = 0;

    const char *prompt = "Type something: ";
    for (int i = 0; prompt[i] != '\0'; i++) {
        print_char(prompt[i]);
    }

    while (1) {
        uint8_t status = inb(0x64);
        if (status & 1) {
            uint8_t sc = inb(KEYBOARD_PORT);
            if (sc & 0x80) continue;
            char c = scancode_to_char(sc);
            if (c) print_char(c);
        }
    }
}
