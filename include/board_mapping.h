#ifndef BOARD_MAPPING_H
#define BOARD_MAPPING_H

#include "types.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

extern Square standard[52];
extern Square base[NUM_OPPONENTS][4];
extern Square home[NUM_OPPONENTS][5];
 
int load_board_map(const char *filename);
void load_squares(FILE *file, SquareType type);
void bypass_lines_until(FILE *file, char *line, SquareType type);

#endif

