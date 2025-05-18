#pragma once

#include <stdint.h>

void fb_init(uint32_t* addr, uint32_t width, uint32_t height, uint32_t pitch, uint8_t bpp);
void fb_draw_pixel(uint32_t x, uint32_t y, uint8_t color);
void fb_clear(uint32_t color);
void fb_draw_char(int c, int x, int y, uint32_t color);
void fb_write_string(const char* str, int x, int y, uint32_t color);
void fb_print(const char* str);
void fb_print_char(char c);

