#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "board_mapping.h"
#include "game_engine.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

const char* get_colour(Colour colour);
const char* get_square_type(SquareType type);
int get_approach(Colour colour);
int get_start(Colour colour);
int get_random_num(int num);
int get_clockwise_distance_between_pieces(int from, int to);
int is_approach_passed(Piece *selected_piece);
void log_mappings();
void update_piece_position(Piece *piece, float speed);
void bypass_lines_until(FILE *file, char *line, SquareType type);

//const char* get_piece_status(PieceStatus status);

#endif
