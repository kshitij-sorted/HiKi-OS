#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint16_t* video_memory = (uint16_t*) VIDEO_MEMORY;
static int cursor_row = 0;
static int cursor_col = 0;

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void putchar(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= VGA_HEIGHT) cursor_row = 0;
        return;
    }
    video_memory[cursor_row * VGA_WIDTH + cursor_col] = (uint16_t) c | 0x0700;
    cursor_col++;
    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= VGA_HEIGHT) cursor_row = 0;
    }
}

char get_char() {
    uint8_t scancode;
    while (1) {
        if ((inb(0x64) & 1) != 0) {
            scancode = inb(0x60);
            break;
        }
    }
    if (scancode & 0x80) return 0;
    if (scancode == 0x1C) return '\n';
    if (scancode >= 0x02 && scancode <= 0x0D) {
        static const char map[] = "1234567890-=";
        return map[scancode - 0x02];
    }
    if (scancode >= 0x10 && scancode <= 0x19) {
        static const char map[] = "qwertyuiop";
        return map[scancode - 0x10];
    }
    if (scancode >= 0x1E && scancode <= 0x26) {
        static const char map[] = "asdfghjkl";
        return map[scancode - 0x1E];
    }
    if (scancode >= 0x2C && scancode <= 0x32) {
        static const char map[] = "zxcvbnm";
        return map[scancode - 0x2C];
    }
    return 0;
}

void kernel_main() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video_memory[i] = (uint16_t) ' ' | 0x0700;
    }
    cursor_row = 0;
    cursor_col = 0;

    putchar('>');
    while (1) {
        char c = get_char();
        if (c) {
            putchar(c);
        }
    }
}
