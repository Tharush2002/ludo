#include "board_mapping.h"
#include "gui.h"
#include "types.h"
#include <stdio.h>
#include <math.h>

#define NUM_SQUARES 52
#define MOVE_SPEED 8.0f

void update_piece_position(Piece *piece, float speed);

int main(void) {
	if (!load_board_map("./assets/mappings.csv")) {
	        printf("Failed to load board map!\n");
		return 1;
	}

	init_gui();

	// Start piece at square 0
	Piece greenPiece = { .board_index = 0,
                         .x = board_squares[0].x,
                         .y = board_squares[0].y,
                         .color = GREEN };

	while (!should_close_window()) {
        // Move on key press
	        if (IsKeyPressed(KEY_RIGHT))
			greenPiece.board_index = (greenPiece.board_index + 1) % NUM_SQUARES;
		if (IsKeyPressed(KEY_LEFT))
        		greenPiece.board_index = (greenPiece.board_index - 1 + NUM_SQUARES) % NUM_SQUARES;

		update_piece_position(&greenPiece, MOVE_SPEED);
        	render_game(&greenPiece);
	}

	cleanup_gui();
	return 0;
}

// Smoothly animate piece toward its target square
void update_piece_position(Piece *piece, float speed) {
	BoardSquares target = board_squares[piece->board_index];
	if (fabs(piece->x - target.x) > speed)
		piece->x += (piece->x < target.x) ? speed : -speed;
	else
        	piece->x = target.x;

	if (fabs(piece->y - target.y) > speed)
        	piece->y += (piece->y < target.y) ? speed : -speed;
	else
		piece->y = target.y;
}

