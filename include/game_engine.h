#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "types.h"
#include "board_mapping.h"
#include "utils.h"
#include <unistd.h>

//extern Piece pieces[NUM_OPPONENTS][NUM_PIECES];
extern GameState game;
extern Move best_move;

void init_game();
Move decide_move();
void get_score(Move move);
void set_player_order();
void move_piece();
void check_captures(Square *destination);

int score_clear_start_position(Move *move);
int score_enter_from_base(Move *move);
int score_progress_toward_home(Move *move);
int score_reaching_center(Move *move);
int score_capture_opponent(Move *move);
int score_safety(Move *move);
int score_moving_to_danger(Move *move);
int score_defensive_formation(Move *move);

void generate_possible_moves(Move *moves, Piece *movable_pieces);
int is_valid_move(Move *move);

#endif
