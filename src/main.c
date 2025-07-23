#include "board_mapping.h"
#include "game_engine.h"
#include "gui.h"
#include "utils.h"
#include "types.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	srand(time(NULL));

	if (!load_board_map("./assets/mappings.csv")) {
	        printf("Failed to load board map!\n");
		return 1;
	}

	init_game();
	log_mappings();	
	init_gui();

	while (!should_close_window()) {
		/*if (IsKeyPressed(KEY_RIGHT)){
			if(move_piece()){
				render_game(pieces);
				game.dice = get_random_num(6);
				printf("============ %d", game.dice);
				printf("==========================\n");
				printf("Dice Roll - %d\n",game.dice);
				printf("==========================\n");
				printf("%d\n\n",get_random_num(6));
				
				Piece* piece = move_piece();
				print_pieces(piece);
				//printf("%d - %s",piece->index,get_colour(piece->colour));
				update_piece_position(piece, MOVE_SPEED);
			}
		}*/
		//update_piece_position(&g1, MOVE_SPEED);
		//render_game(pieces);
		//game.dice = get_random_num(6);
		game.dice = 6;
                                
                move_piece();
		
		//sleep(5);
                //printf("%d - %s",piece->index,get_colour(piece->colour));
                //update_piece_position(piece, MOVE_SPEED);
        	render_game(pieces);
		sleep(2);
	}

	cleanup_gui();
	return 0;
}
