#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "board_mapping.h"
#include <assert.h>

const char* get_colour(Colour colour);
const char* get_square_type(SquareType type);
const char* get_piece_status(PieceStatus status);

#endif
