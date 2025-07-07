#include "board_mapping.h"
#include "gui.h"
#include "utils.h"
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

	/*for(size_t i=0 ; i<sizeof(standard)/sizeof(standard[0]) ; i++){
		printf("x - %d\ty - %d\n",standard[i].x,standard[i].y);
	}	

	printf("================================================\n");
	printf("HOME\n");
	printf("================================================\n");

	for(size_t i=0 ; i<sizeof(home)/sizeof(home[0]) ; i++){
		for(size_t j=0 ; j<sizeof(home[i].square)/sizeof(home[i].square[0]) ; j++){
			printf("colour - %s\tx - %d\ty - %d\n",get_colour(home[i].colour), home[i].square[j].x, home[i].square[j].y);
		}
	}	
	
	printf("================================================\n");
	printf("BASE\n");
	printf("================================================\n");

	for(size_t i=0 ; i<sizeof(base)/sizeof(base[0]) ; i++){
		for(size_t j=0 ; j<sizeof(base[i].square)/sizeof(base[i].square[0]) ; j++){
			printf("colour - %s\tx - %d\ty - %d\n",get_colour(base[i].colour), base[i].square[j].x, base[i].square[j].y);
		}
	}*/
	
	init_gui();

	Piece g1 = { .square = &standard[0], .current_x = standard[0].x, .current_y = standard[0].y, .status = PIECE_STANDARD, .colour = COLOUR_GREEN};

	while (!should_close_window()) {
	        if (IsKeyPressed(KEY_RIGHT)){
			g1.square = g1.square == &standard[NUM_SQUARES-1] ? &standard[0]:g1.square+1;
		}
		update_piece_position(&g1, MOVE_SPEED);
        	render_game(g1.current_x, g1.current_y);
	}

	cleanup_gui();
	return 0;
}

void update_piece_position(Piece *piece, float speed) {
	Square target = *piece->square;
	if (fabsf(piece->current_x - target.x) > speed){
		piece->current_x += (piece->current_x < target.x) ? speed : -speed;
	}else{
        	piece->current_x = target.x;
	}
	
	if (fabsf(piece->current_y - target.y) > speed){
        	piece->current_y += (piece->current_y < target.y) ? speed : -speed;
	}else{
		piece->current_y = target.y;
	}
}

