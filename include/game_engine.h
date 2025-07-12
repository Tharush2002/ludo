#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "types.h"
#include "board_mapping.h"
#include "utils.h"

extern Piece pieces[NUM_OPPONENTS][NUM_PIECES];

typedef struct {
	Piece (*pieces)[NUM_OPPONENTS][NUM_PIECES];
	Colour player;  
	int dice;
	int turn_count;
} GameState;

typedef struct {
	int piece_index, from_index, to_index, score, can_move;
	PieceStatus from_status, to_status;
} Move;

extern GameState game;

void init_game();
Move decide_move();
//int execute_move();

int score_progress_toward_home(Move *move);
int score_reaching_center(Move *move);
int score_capture_opponent(Move *move);
int score_safety(Move *move);
int score_enter_from_base(Move *move);
int score_moving_to_danger(Move *move);

void generate_possible_moves(Move *moves, Piece *movable_pieces);
int is_valid_move(Move *move);

#endif
