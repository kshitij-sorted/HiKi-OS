void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void putchar(char c) {
    static unsigned short *video = (unsigned short *)0xB8000;
    static int pos = 0;
    video[pos++] = (0x0F << 8) | c;
}

void main() {
    putchar('>');
    while (1) {
        if ((inb(0x64) & 1) == 0) continue; // wait for key press
        unsigned char scancode = inb(0x60);

        // Simple US QWERTY scancode table
        static char keymap[128] = {
            0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
            '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
            'a','s','d','f','g','h','j','k','l',';','\'','`', 0,
            '\\','z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '
        };

        if (scancode < 128) {
            char c = keymap[scancode];
            if (c) putchar(c);
        }
    }
}
