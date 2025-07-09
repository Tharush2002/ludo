#include "game_engine.h"

Piece pieces[NUM_OPPONENTS][NUM_PIECES];

void init_pieces(){
	for(int i = 0 ; i < NUM_OPPONENTS ; i++){
		for(int j = 0 ; j < NUM_PIECES ; j++){
			pieces[i][j].square = &base[i].square[j];
			pieces[i][j].current_x = base[i].square[j].x;
			pieces[i][j].current_y = base[i].square[j].y; 
			pieces[i][j].status = PIECE_HOME;
			pieces[i][j].colour = i;
		}
	}
}
