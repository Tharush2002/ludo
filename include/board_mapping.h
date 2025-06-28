#ifndef BOARD_MAPPING_H
#define BOARD_MAPPING_H

typedef struct {
	int index;
	int x;
	int y;
} BoardSquares;

extern BoardSquares board_squares[52]; 
int load_board_map(const char *filename);

#endif

