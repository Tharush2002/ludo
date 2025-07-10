#include "game_engine.h"

Piece pieces[NUM_OPPONENTS][NUM_PIECES];

void init_pieces(){
	for(int i = 0 ; i < NUM_OPPONENTS ; i++){
		for(int j = 0 ; j < NUM_PIECES ; j++){
			pieces[i][j].location_type = BASE;
			pieces[i][j].index = j;
			pieces[i][j].current_x = base[i][j].x;
			pieces[i][j].current_y = base[i][j].y; 
			pieces[i][j].status = PIECE_HOME;
			pieces[i][j].colour = i;
		}
	}
}

/*void decide_move(Piece *movable_pieces, int roll){
	int score = 0;
	
	for(int i=0 ; i<NUM_PIECES ; i++){
	
	}		
}*/
