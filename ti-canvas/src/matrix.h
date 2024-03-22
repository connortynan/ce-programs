#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

static uint16_t matrix_XYtoi(uint8_t x, uint8_t y, uint8_t dim) {
    return x + y*dim;
}

#endif //MATRIX_H
