#pragma once

#include <stdarg.h>
#include <stdint.h>

// Function to print a single character to the screen
void putchar(char c);

// Function to print a null-terminated string
void puts(const char* str);

// Simplified printf function for formatted output (supports %s and %x)
void printf(const char* format, ...);

// Helper function to print a number in hexadecimal format
void print_hex(uint32_t num);

