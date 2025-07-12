#ifndef BOARD_MAPPING_H
#define BOARD_MAPPING_H

#include "types.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#define RED_APPROACH 24
#define RED_START 26
#define BLUE_APPROACH 11
#define BLUE_START 13
#define GREEN_APPROACH 37
#define GREEN_START 39
#define YELLOW_APPROACH 50
#define YELLOW_START 0

extern Square standard[NUM_STANDARD_SQUARES];
extern Square base[NUM_OPPONENTS][NUM_BASE_SQUARES];
extern Square home[NUM_OPPONENTS][NUM_HOME_SQUARES];
 
int load_board_map(const char *filename);
void load_squares(FILE *file, SquareType type);
void bypass_lines_until(FILE *file, char *line, SquareType type);

#endif

