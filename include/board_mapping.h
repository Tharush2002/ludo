#ifndef BOARD_MAPPING_H
#define BOARD_MAPPING_H

#include "types.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

extern Square standard[NUM_STANDARD_SQUARES];
extern Square base[NUM_OPPONENTS][NUM_BASE_SQUARES];
extern Square home[NUM_OPPONENTS][NUM_HOME_SQUARES];
extern Square center[NUM_OPPONENTS][NUM_CENTER_SQUARES];
 
int load_board_map(const char *filename);
void load_squares(FILE *file, SquareType type);
void bypass_lines_until(FILE *file, char *line, SquareType type);

#endif

