#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "board_mapping.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

const char* get_colour(Colour colour);
const char* get_square_type(SquareType type);
void log_mappings();
void update_piece_position(Piece *piece, float speed);
void bypass_lines_until(FILE *file, char *line, SquareType type);
int roll_dice();
//const char* get_piece_status(PieceStatus status);

#endif
