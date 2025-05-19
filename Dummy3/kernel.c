// kernel.c
#define VIDEO_MEMORY ((volatile char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile unsigned char* video = (unsigned char*) VIDEO_MEMORY;
static int cursor_pos = 0;

// Port I/O
static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(unsigned short port, unsigned char val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i++) {
        video[i] = 0;
    }
}

void put_char(char c) {
    if (c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    } else {
        video[cursor_pos * 2] = c;
        video[cursor_pos * 2 + 1] = 0x07; // Light grey on black
        cursor_pos++;
    }
    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT) {
        cursor_pos = 0;
    }
}

int scancode_to_ascii(unsigned char sc) {
    // Simple US QWERTY map for main keys, ignoring shift/caps for simplicity
    static const char scancode_ascii[128] = {
        0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b', '\t',
        'q','w','e','r','t','y','u','i','o','p','[',']', '\n', 0,
        'a','s','d','f','g','h','j','k','l',';','\'','`', 0, '\\',
        'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' ',
        // rest zero
    };
    if (sc > 127) return 0;
    return scancode_ascii[sc];
}

void kernel_main() {
    clear_screen();
    put_char('>');
    while (1) {
        unsigned char status = inb(0x64);
        if (status & 0x01) { // Output buffer full
            unsigned char sc = inb(0x60);
            if (sc & 0x80) continue; // Key release
            char c = scancode_to_ascii(sc);
            if (c) put_char(c);
        }
    }
}
