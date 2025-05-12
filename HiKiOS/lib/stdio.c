#include "stdio.h"
#include <stdarg.h>
#include "../drivers/framebuffer.h"

void putchar(char c) {
    fb_draw_char(c); 
}

void puts(const char* str) {
    while (*str) {
        putchar(*str++);
    }
}

void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char ch;
    while ((ch = *format++)) {
        if (ch == '%') {
            char next = *format++;
            if (next == 's') {
                puts(va_arg(args, char*));
            } else if (next == 'c') {
                putchar(va_arg(args, int));
            } else if (next == 'd') {
                int num = va_arg(args, int);
                char buf[32];
                itoa(num, buf, 10);  // You should implement `itoa`
                puts(buf);
            }
        } else {
            putchar(ch);
        }
    }

    va_end(args);
}
