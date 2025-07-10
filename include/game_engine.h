#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "types.h"
#include "board_mapping.h"

extern Piece pieces[NUM_OPPONENTS][NUM_PIECES];

typedef struct {
	Piece (*pieces)[NUM_PIECES];
	Colour player;  
	int dice_value; 
	int turn_count;
} GameState;

typedef struct {
	Colour player;
	int piece_index;
	int from_position, to_position;
	SquareType from_location, to_location;
} Move;

extern GameState game;

void init_game();
//void decide_move(Piece *pieces, int roll);

#endif
