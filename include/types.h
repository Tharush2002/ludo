#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

typedef struct {
    int board_index; // logical square index (0-51)
    float x, y;      // current pixel position (for animation)
    Color color;
} Piece;

#endif

