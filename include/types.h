#ifndef TYPES_H
#define TYPES_H

//#include "raylib.h"

//#define SQUARE_SIZE 62
//#define PIECE_SCALE 0.8f
//#define PIECE_TARGET_SIZE (SQUARE_SIZE * PIECE_SCALE)
#define NUM_STANDARD_SQUARES 52
#define NUM_BASE_SQUARES 4
#define NUM_HOME_SQUARES 5
#define NUM_PIECES 4
#define NUM_OPPONENTS 4
#define MOVE_SPEED 8.0f

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

