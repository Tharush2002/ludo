#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "types.h"
#include "board_mapping.h"
#include "utils.h"

extern Piece pieces[NUM_OPPONENTS][NUM_PIECES];
extern GameState game;

void init_game();
Move decide_move();
void set_player_order();
void move_piece();

int score_progress_toward_home(Move *move);
int score_reaching_center(Move *move);
int score_capture_opponent(Move *move);
int score_safety(Move *move);
int score_enter_from_base(Move *move);
int score_moving_to_danger(Move *move);

void generate_possible_moves(Move *moves, Piece *movable_pieces);
int is_valid_move(Move *move);

#endif
