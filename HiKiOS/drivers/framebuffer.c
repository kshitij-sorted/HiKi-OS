#include <stdint.h>
#include <stddef.h>
#include "../../include/drivers/framebuffer.h"

// These will be set from multiboot info or bootloader
uint32_t* framebuffer = 0;
uint32_t screen_width = 0;
uint32_t screen_height = 0;
uint32_t pitch = 0;
uint8_t  bpp = 0;

void fb_init(uint32_t* addr, uint32_t w, uint32_t h, uint32_t p, uint8_t bits_per_pixel) {
    framebuffer = addr;
    screen_width = w;
    screen_height = h;
    pitch = p;
    bpp = bits_per_pixel;
}

void fb_draw_pixel(int x, int y, uint32_t color) {
    if (x >= screen_width || y >= screen_height) return;
    framebuffer[y * (pitch / 4) + x] = color;
}

void fb_clear(uint32_t color) {
    for (uint32_t y = 0; y < screen_height; y++)
        for (uint32_t x = 0; x < screen_width; x++)
            fb_draw_pixel(x, y, color);
}
