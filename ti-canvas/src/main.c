#include <ti/screen.h>
#include <ti/getcsc.h>
#include <stdlib.h>
#include <graphx.h>
#include <debug.h>

#include "dither.h"

/* Main function, called first */
int main(void)
{
    os_ClrHome();

    // Get user input
    char choice[10];
    os_GetStringInput("ditherDim? (MUST BE 2^N) ", choice, 10);
    uint8_t ditherDim = atoi(choice);
    os_NewLine();

    os_GetStringInput("ditherStrength? (0-255) ", choice, 10);
    uint8_t ditherStrength = atoi(choice);
    os_NewLine();

    // Assign canvas width and height variables
    const uint16_t w = GFX_LCD_WIDTH, h = GFX_LCD_HEIGHT;

    // Initialize graphx mode
    gfx_Begin();
    gfx_ZeroScreen();
    gfx_SetDefaultPalette(gfx_8bpp);

    // Generate dither matrix, limiting ditherDim to positive numbers
    if (ditherDim < 1) {
        ditherDim = 1;
    }
    int16_t ditherPattern[ditherDim*ditherDim];
    dither_generateDitherPattern(ditherPattern, ditherDim, ditherStrength);

    // Precompute a flipped coordinate array to make RGB dithering easier
    uint8_t flip[ditherDim];
    for (uint8_t i = 0; i < ditherDim; i++) {
        flip[i] = ditherDim-1 - i;
    }

    int16_t rDither, gDither, bDither;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint8_t i  = x&(ditherDim-1);
            uint8_t j  = y&(ditherDim-1);

            rDither = ditherPattern[matrix_XYtoi(i,       j, ditherDim)];
            gDither = ditherPattern[matrix_XYtoi(flip[i], j, ditherDim)];
            bDither = ditherPattern[matrix_XYtoi(i, flip[j], ditherDim)];

            uint8_t r = color_saturate((256*x/w + rDither));
            uint8_t g = color_saturate((256*y/h + gDither));
            uint8_t b = color_saturate(                bDither);
            gfx_SetColor(color_RGBToPaletteIndex(r, g, b));
            gfx_SetPixel(x, y);
        }
    }

    dbg_printf("done rendering");

    while (!os_GetCSC());
    gfx_End();
    return 0;
}
