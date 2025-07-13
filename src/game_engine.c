#include "game_engine.h"

Piece pieces[NUM_OPPONENTS][NUM_PIECES];
GameState game;
int player_order[NUM_PIECES] = {0};

//Initialize the game by mapping the pieces into bases
void init_game(){
	set_player_order();
	for(int i = 0 ; i < NUM_OPPONENTS ; i++){
		for(int j = 0 ; j < NUM_PIECES ; j++){
			pieces[i][j].index = j;
			pieces[i][j].current_x = base[i][j].x;
			pieces[i][j].current_y = base[i][j].y; 
			pieces[i][j].status = PIECE_BASE;
			pieces[i][j].colour = i;
		}
	}
	game.pieces = &pieces;
	game.turn_count = 0;
}

//Decides the best possible move currently
Move decide_move(){
	Move moves[NUM_PIECES], best_move;
	int moves_with_same_scores[NUM_PIECES], same_count=0;

	generate_possible_moves(moves, (*game.pieces)[game.player]);		

	for(int i=0 ; i<NUM_PIECES ; i++){
		if(moves[i].can_move){
			moves[i].score += score_progress_toward_home(&moves[i]);
			moves[i].score += score_reaching_center(&moves[i]);
			moves[i].score += score_capture_opponent(&moves[i]);
			moves[i].score += score_safety(&moves[i]);
			moves[i].score += score_enter_from_base(&moves[i]);
			moves[i].score += score_moving_to_danger(&moves[i]);
		} 
	}

	for(int i=0 ; i<NUM_PIECES-1 ; i++){
		if(moves[i].score > moves [i+1].score && moves[i].can_move) best_move = moves[i];
	}
	
	for(int i=0 ; i<NUM_PIECES ; i++){
		if(best_move.score == moves[i].score && moves[i].can_move){
			moves_with_same_scores[same_count] = i;
			same_count++;
		}
	}

	if(same_count==1){
		return best_move;
	}else if(same_count>1){
		int random = get_random_num(same_count);
		return moves[moves_with_same_scores[random-1]];
	}else{
		Move no_valid_move = {.can_move=0};
		return no_valid_move;
	}

}

//Set the playing order
void set_player_order(){
	PlayerRoll order[NUM_PIECES];
	int is_rolls_unique = 0;

	for(int i=0 ; i<NUM_PIECES ; i++){
		order[i].roll = get_random_num(6);
		order[i].player = (Colour)i;
	}

	while(!is_rolls_unique){
		is_rolls_unique = 1;
		for(int i=0 ; i<NUM_PIECES ; i++){
			for(int j=0 ; j<NUM_PIECES ; j++){
				if(i==j) continue;
				if(order[i].roll == order[j].roll){
					is_rolls_unique = 0;
					order[i].roll = get_random_num(6);
					order[j].roll = get_random_num(6);
					break;
				}
			}		
			if(!is_rolls_unique) break;	
		}
	}

	for (int i = 0; i < NUM_OPPONENTS - 1; i++) {
		for (int j = 1; j < NUM_OPPONENTS - i; j++) {
		        if (order[i].roll > order[j].roll) {
				PlayerRoll temp = order[j];
				order[j] = order[i];
				order[i] = temp;
        		}
    		}
	}

	for(int i=0 ; i<NUM_PIECES ; i++){
		player_order[i] = order[i].player;
	}
}

//Move a piece according to its best move
int move_piece(){
	Move best_move = decide_move();
	if(best_move.can_move){
		(*game.pieces)[game.player][best_move.piece_index].index = best_move.to_index;
		(*game.pieces)[game.player][best_move.piece_index].status = best_move.to_status;
		game.turn_count++;			
		return 1;
	}else{
		game.turn_count++;
		return 0;
	}	
}

//Score system for the possible moves
int score_progress_toward_home(Move *move){
	if((move->from_status == PIECE_BASE) && (move->to_status == PIECE_STANDARD)){
		return 1;
	}else if((move->from_status == PIECE_HOME) && (move->to_status == PIECE_FINISHED)){
		return game.dice-1;
	}else{
		return game.dice;
	}
}

//Score system for the possible moves
int score_reaching_center(Move *move){
	if((move->from_status == PIECE_HOME) && (move->to_status == PIECE_FINISHED)){
		return 20;
	}else{
		return 0;
	}
}

//Score system for the possible moves
int score_capture_opponent(Move *move){
	for(int i=0 ; i<NUM_OPPONENTS ; i++){
		if(game.player == (Colour)i) continue;
		for(int j=0 ; j<NUM_PIECES ; j++){
			if(move->to_index == (*game.pieces)[i][j].index) return 20;
		}
	}
	return 0;
}

//Score system for the possible moves
int score_safety(Move *move){
	if((move->from_status == PIECE_STANDARD) && (move->to_status == PIECE_HOME)){
		return 5;
	}else{
		return 0;
	}
}

//Score system for the possible moves
int score_enter_from_base(Move *move){
	if(move->from_status == PIECE_BASE && move->to_status == PIECE_STANDARD){
		return 10;
	}else{
		return 0;
	}
}

//Score system for the possible moves
int score_moving_to_danger(Move *move){	
	for(int i=0 ; i<NUM_OPPONENTS ; i++){
		if(game.player == (Colour)i) continue;
		for(int j=0 ; j<NUM_PIECES ; j++){
			int approach_attacker = get_approach(game.pieces[i][j]->colour);
			int distance = get_clockwise_distance_between_pieces(game.pieces[i][j]->index, move->to_index);
			
			if(approach_attacker == move->to_index) return -10;

			if (distance == 0 || distance > 6) {
        			return 0;
			}

			int steps_to_approach = (approach_attacker - game.pieces[i][j]->index + NUM_STANDARD_SQUARES) % NUM_STANDARD_SQUARES;
			if (distance > steps_to_approach) {
			        return 0;
			}

			return -10;
		}
	}
	return 0;
}

//generate the all the possible moves for the player
void generate_possible_moves(Move *moves, Piece *movable_pieces){
	for(int i=0 ; i<NUM_PIECES ; i++){
		moves[i].piece_index = i;
		moves[i].from_index = movable_pieces[i].index;
		moves[i].score = 0;
		
		switch(movable_pieces[i].status){
			case PIECE_STANDARD:
				moves[i].from_status = PIECE_STANDARD;
				
				moves[i].to_index = (moves[i].from_index + game.dice)%52;
				moves[i].to_status = is_approach_passed(&movable_pieces[i]) == 1 ? PIECE_HOME : PIECE_STANDARD;
				
				moves[i].can_move = is_valid_move(&moves[i]);
				break;	
			case PIECE_HOME:
				moves[i].from_status = PIECE_HOME;
				moves[i].to_status = PIECE_HOME;

				moves[i].to_index = moves[i].from_index + game.dice;	
				moves[i].can_move = is_valid_move(&moves[i]);
				break;
			case PIECE_BASE:
				moves[i].from_status = PIECE_BASE;
				moves[i].to_status = PIECE_BASE;

				switch(game.player){
					case COLOUR_RED:
						moves[i].to_index = RED_START;
						break;
					case COLOUR_BLUE:
						moves[i].to_index = BLUE_START;
						break;
					case COLOUR_GREEN:
						moves[i].to_index = GREEN_START;
						break;
					case COLOUR_YELLOW:
						moves[i].to_index = YELLOW_START;
						break;
				}
			
				moves[i].can_move = is_valid_move(&moves[i]);
				break;
			case PIECE_FINISHED:
				moves[i].from_status = PIECE_FINISHED;
				moves[i].to_status = PIECE_FINISHED;	
				moves[i].can_move = is_valid_move(&moves[i]);
		}
	}
}

//Checks the validity of the current move
int is_valid_move(Move *move){
	switch(move->to_status){
		case PIECE_STANDARD:
			for(int i=0 ; i < NUM_PIECES ; i++){
				if(move->piece_index == game.pieces[game.player][i]->index) continue;
				if(move->to_index == game.pieces[game.player][i]->index) return 0;
			}
			return 1;

		case PIECE_HOME:
			if(move->to_index > NUM_HOME_SQUARES){
				return 0;
			}
			for(int i=0 ; i < NUM_PIECES ; i++){
				if(move->piece_index == game.pieces[game.player][i]->index) continue;
				if((game.pieces[game.player][i]->status == PIECE_HOME) && (move->to_index >= game.pieces[game.player][i]->index)) return 0;
			}
			if(move->to_index == NUM_HOME_SQUARES) move->to_status = PIECE_FINISHED;
			return 1;		

		default:			
			switch(move->from_status){
				case PIECE_BASE:
					if(game.dice == 6){
						for(int i=0 ; i<NUM_PIECES ; i++){
							if((*game.pieces)[game.player][i].index == get_start(game.player))
								return 0;
						}
						move->to_status = PIECE_STANDARD;
						return 1;
					}else{
						return 0;
					}
					break;

				case PIECE_FINISHED: return 0;		
				default: return 0;
			}
	}
}
