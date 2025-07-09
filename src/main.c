#include "board_mapping.h"
#include "game_engine.h"
#include "gui.h"
#include "utils.h"
#include "types.h"
#include <stdio.h>

int main(void) {
	if (!load_board_map("./assets/mappings.csv")) {
	        printf("Failed to load board map!\n");
		return 1;
	}

	init_pieces();
	log_mappings();	
	init_gui();

	while (!should_close_window()) {
	        /*if (IsKeyPressed(KEY_RIGHT)){
			g1.square = g1.square == &standard[NUM_STANDARD_SQUARES-1] ? &standard[0]:g1.square+1;
		}
		update_piece_position(&g1, MOVE_SPEED);*/
        	render_game(pieces);
	}

	cleanup_gui();
	return 0;
}
