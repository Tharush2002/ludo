#include "game_engine.h"

//Piece pieces[NUM_OPPONENTS][NUM_PIECES];
GameState game = {.dice=0};
int player_order[NUM_PIECES] = {0};

//Initialize the game by mapping the pieces into bases
void init_game(){
	set_player_order();
	for(int i = 0 ; i < NUM_OPPONENTS ; i++){
		for(int j = 0 ; j < NUM_PIECES ; j++){
			game.pieces[i][j].index = j;
			game.pieces[i][j].current_x = base[i][j].x;
			game.pieces[i][j].current_y = base[i][j].y; 
			game.pieces[i][j].status = PIECE_BASE;
			game.pieces[i][j].colour = i;
		}
	}
	game.turn_count = 0;
	game.player = player_order[game.turn_count%4];
}

//Decides the best possible move currently
Move decide_move(){
	Move moves[NUM_PIECES], best_move;
	int moves_with_same_scores[NUM_PIECES], same_count=0;

	generate_possible_moves(moves, game.pieces[game.player]);			
	
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
		if(moves[i].score >= moves [i+1].score && moves[i].can_move){
			best_move = moves[i];			
		}		
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
		Move move = moves[moves_with_same_scores[random-1]];
		return move;
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

	for(int i=0;i<NUM_OPPONENTS;i++){
		for(int j=0;j<NUM_OPPONENTS-i-1;j++){
			if(order[j].roll > order[j+1].roll){
				PlayerRoll temp = order[j];
				order[j] = order[j+1];
				order[j+1] = temp;
			}
		}
	}

	for(int i=0 ; i<NUM_PIECES ; i++){
		player_order[i] = order[i].player;
		printf("%d - %s\n",i+1,get_colour(order[i].player));
	}
}

//Move a piece according to its best move
void move_piece(){
	game.player = player_order[game.turn_count%4];
	Move best_move = decide_move();
	

	//print_move(&best_move);


	if(best_move.can_move){
	        Piece *piece = &game.pieces[game.player][best_move.piece_index];
        
                piece->index = best_move.to_index;
                piece->status = best_move.to_status;
	}
	game.turn_count++;
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
			if(move->to_index == game.pieces[i][j].index) return 20;
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
			
			int approach_attacker = get_approach(game.pieces[i][j].colour);
			int distance = get_distance_standard(game.pieces[i][j].index, move->to_index);
			
			if(approach_attacker == move->to_index) return -10;

			if (distance == 0 || distance > 6) {
        			return 0;
			}

			int steps_to_approach = (approach_attacker - game.pieces[i][j].index + NUM_STANDARD_SQUARES) % NUM_STANDARD_SQUARES;
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
		moves[i].from_status = movable_pieces[i].status;
		moves[i].score = 0;
	
		Square destination = get_destination(&movable_pieces[i], game.dice);
		moves[i].to_index = destination.index;
		
		printf("dice is %d and %s - %d\n", game.dice, get_colour(movable_pieces[i].colour), destination.index);
		

		switch(destination.type){
			case STANDARD:
				moves[i].to_status = PIECE_STANDARD;
				break;
			case HOME:
				moves[i].to_status = PIECE_HOME;
				break;
			case BASE:	
				moves[i].to_status = PIECE_BASE;
		}
		
		if(destination.x == 0 && destination.y == 0 && destination.type == 0 && destination.index == 0){
			moves[i].can_move = 0;
		}else{
			moves[i].can_move = is_valid_move(&moves[i]);
		}

		//print_move(&moves[i]);
	}
}

//Checks the validity of the current move
int is_valid_move(Move *move){
	
	switch(move->to_status){
		case PIECE_STANDARD:
			for(int i=0 ; i < NUM_PIECES ; i++){
				if(move->piece_index == i) continue;
				if((move->to_status == game.pieces[game.player][i].status) && (move->to_index == game.pieces[game.player][i].index)) return 0;
			}
			return 1;

		case PIECE_HOME:
			if(move->to_index > NUM_HOME_SQUARES){
				return 0;
			}
			for(int i=0 ; i < NUM_PIECES ; i++){
				if(move->piece_index == i) continue;
				if((game.pieces[game.player][i].status == PIECE_HOME) && (move->to_index >= game.pieces[game.player][i].index)) return 0;
			}
			if(move->to_index == NUM_HOME_SQUARES) move->to_status = PIECE_FINISHED;
			return 1;		

		case PIECE_BASE:
			for(int i=0 ; i<NUM_PIECES ; i++){
				if (move->piece_index==i) continue;
				if(game.pieces[game.player][i].index == get_start(game.player))
					return 0;
			}			
			return 1;
		case PIECE_FINISHED: return 0;			
		default: return 0;
	}
}
