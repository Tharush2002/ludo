#ifndef BOARD_MAPPING_H
#define BOARD_MAPPING_H

#include "types.h"
#include <stdio.h>

typedef struct {
	Square square[4];
	Colour colour;
} Base_Squares;

typedef struct {
	Square square[5];
	Colour colour;
} Home_Squares;

extern Square standard[52];
extern Base_Squares base[4];
extern Home_Squares home[4];
 
int load_board_map(const char *filename);
void load_squares(FILE *file, SquareType type);
void bypass_lines_until(FILE *file, char *line, SquareType type);

#endif

