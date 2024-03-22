#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>
#include <graphx.h>
#include <math.h>

static uint8_t color_saturate(int16_t x) {
    if (x < 0)
        return 0;
    if (x > 255)
        return 255;
    return (uint8_t)x;
}

static uint8_t color_RGBToPaletteIndex(uint8_t r, uint8_t g, uint8_t b) {
    return ((r>>5)<<5) | (g>>5) | ((b>>6)<<3);
}

#endif //COLOR_H
