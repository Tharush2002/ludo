#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

typedef enum {STANDARD,HOME,BASE} SquareType;
typedef enum {COLOUR_RED,COLOUR_BLUE,COLOUR_GREEN,COLOUR_YELLOW} Colour;
typedef enum {PIECE_STANDARD,PIECE_HOME,PIECE_BASE,PIECE_FINISHED} PieceStatus;

typedef struct{
	int index, x, y;
} Square;

typedef struct {
	Square *square; 
	float current_x, current_y;
	PieceStatus status;
    	Colour colour;
} Piece;

#endif

