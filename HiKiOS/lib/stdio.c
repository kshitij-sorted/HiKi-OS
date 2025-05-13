#include "stdio.h"

// Function to print a single character to the screen using BIOS interrupt 0x10
void putchar(char c) {
    __asm__ (
        "movb %0, %%al\n"         // Load char into AL
        "movb $0x0E, %%ah\n"      // BIOS teletype function
        "int $0x10\n"              // BIOS interrupt
        :
        : "r" (c)
        : "%ax"
    );
}

// Function to print a null-terminated string
void puts(const char* str) {
    while (*str) {
        putchar(*str++);
    }
}

// Helper function to print a 32-bit number in hexadecimal format
void print_hex(uint32_t num) {
    char hex_digits[] = "0123456789ABCDEF";
    char buffer[9]; // For 32-bit hex numbers
    int i = 8;

    buffer[8] = '\0'; // Null-terminate the string

    while (i > 0) {
        buffer[--i] = hex_digits[num & 0xF];  // Get the last hex digit
        num >>= 4;  // Shift the number by 4 bits
    }

    // Print the hex string using putchar
    puts(buffer);
}

// Simplified printf function to handle %s and %x format specifiers
void printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;  // Skip the '%' character
            if (*format == 's') {
                // Print string
                char* str = va_arg(args, char*);
                puts(str);
            }
            else if (*format == 'x') {
                // Print hexadecimal
                uint32_t num = va_arg(args, uint32_t);
                print_hex(num);
            }
            // Add more formats (e.g., %d for integers) as needed
        } else {
            // Just print the character as is
            putchar(*format);
        }
        format++;
    }

    va_end(args);
}
