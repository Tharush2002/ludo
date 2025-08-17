#ifndef TYPES_H
#define TYPES_H

#define NUM_STANDARD_SQUARES 52
#define NUM_BASE_SQUARES 4
#define NUM_HOME_SQUARES 5
#define NUM_CENTER_SQUARES 1
#define NUM_PIECES 4
#define NUM_OPPONENTS 4
#define MOVE_SPEED 10.0f

#define RED_APPROACH 24
#define RED_START 26
#define BLUE_APPROACH 11
#define BLUE_START 13
#define GREEN_APPROACH 37
#define GREEN_START 39
#define YELLOW_APPROACH 50
#define YELLOW_START 0

typedef enum {
	STANDARD=0,
	HOME=1,
	BASE=2,
	CENTER=3
} SquareType;

typedef enum{
	READY = 0,
	SHOW = 1,
	MOVE = 2
} DicePhase;

typedef enum {
	COLOUR_RED=0,
	COLOUR_BLUE=1,
	COLOUR_GREEN=2,
	COLOUR_YELLOW=3
} Colour;

typedef struct{
	int index, x, y;
	SquareType type;
} Square;

typedef struct {
	Square current_square, destination_square;
	Colour colour;
	int is_moving, is_finished;
	double finish_time;
} Piece;

typedef struct {
        Piece pieces[NUM_OPPONENTS][NUM_PIECES];
        Colour player, winner;
	int dice, turn_count, six_rolls, show_dice, game_over;
	DicePhase dice_phase;
	double dice_show_time; 	
} GameState;
 
typedef struct {
        int piece_index, from_index, to_index, score, can_move, capture_available;
        SquareType from, to;
	Piece *captured;
} Move;
 
typedef struct {
         int roll;
         Colour player;
} PlayerRoll;


#endif
