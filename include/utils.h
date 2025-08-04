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
int get_distance_standard(int from, int to);
int is_approach_passed(Piece *selected_piece, int steps);
Square get_destination(Piece *piece, int steps);
int update_piece_position(Piece *piece, float speed);
int any_piece_moving();

void bypass_lines_until(FILE *file, char *line, SquareType type);
void log_mappings();
void print_piece(Piece *p);
void print_move(Move *m);
const char* get_piece_status(PieceStatus status);

#endif
