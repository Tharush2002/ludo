#ifndef TYPES_H
#define TYPES_H

#define NUM_STANDARD_SQUARES 52
#define NUM_BASE_SQUARES 4
#define NUM_HOME_SQUARES 5
#define NUM_PIECES 4
#define NUM_OPPONENTS 4
#define MOVE_SPEED 8.0f

typedef enum {
	STANDARD=0,
	HOME=1,
	BASE=2
} SquareType;

typedef enum {
	COLOUR_RED=0,
	COLOUR_BLUE=1,
	COLOUR_GREEN=2,
	COLOUR_YELLOW=3
} Colour;

typedef enum {
	PIECE_STANDARD=0,
	PIECE_HOME=1,
	PIECE_BASE=2,
	PIECE_FINISHED=3
} PieceStatus;

typedef struct{
	int index, x, y;
} Square;

typedef struct {
	SquareType location_type;
	int index;
	float current_x, current_y;
	PieceStatus status;
	Colour colour;
} Piece;

#endif
