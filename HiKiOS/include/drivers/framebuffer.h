#pragma once

#include <stdint.h>

void fb_init(uint32_t* addr, uint32_t width, uint32_t height, uint32_t pitch, uint8_t bpp);
void fb_draw_pixel(int x, int y, uint32_t color);
void fb_clear(uint32_t color);
