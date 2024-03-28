#ifndef DITHER_H
#define DITHER_H

#include <stdlib.h>
#include <graphx.h>
#include <math.h>
#include <color.h>
#include "matrix.h"

static void dither_fillBayerMatrix(int16_t* matrix, uint8_t dim) {
    matrix[0] = 0;

    for (int sub = 1; sub < dim; sub *= 2) {
        for (int y = 0; y < sub; y++) {
            for (int x = 0; x < sub; x++) {
                uint16_t val = matrix[x + dim * y];
                matrix[(x      ) + dim * (y      )] = 4 * val;
                matrix[(x + sub) + dim * (y      )] = 4 * val + 2;
                matrix[(x      ) + dim * (y + sub)] = 4 * val + 3;
                matrix[(x + sub) + dim * (y + sub)] = 4 * val + 1;
            }
        }
    }
}

static void dither_generateDitherPattern(int16_t* pattern, uint8_t dim, uint8_t ditherStrength) {
    if (dim < 1) {
        return;
    }
    if (dim == 1) {
        pattern[0] = 0;
        return;
    }

    dither_fillBayerMatrix(pattern, dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            pattern[i + j*dim] = (ditherStrength*(int)pattern[i + j*dim] / (dim*dim)) - (ditherStrength/2);
        }
    }
}
#endif //DITHER_H
