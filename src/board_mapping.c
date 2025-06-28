#include "board_mapping.h"
#include <stdio.h>

BoardSquares board_squares[52];

int load_board_map(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    int index, x, y;

    fscanf(file, "index,x,y\n");
    for (int i = 0; i < 52; ++i) {
        if (fscanf(file, "%d,%d,%d\n", &index, &x, &y) != 3) break;
        board_squares[index].x = x;
        board_squares[index].y = y;
    }
    fclose(file);
    return 1;
}

