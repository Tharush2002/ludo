#include "game_engine.h"

GameState game = {.dice=0};
Move best_move = {0};

int player_order[NUM_PIECES] = {0};

//Initialize the game by mapping the pieces into bases
void init_game(){
	set_player_order();
	for(int i = 0 ; i < NUM_OPPONENTS ; i++){
		for(int j = 0 ; j < NUM_PIECES ; j++){
			game.pieces[i][j].current_square = base[i][j];
			game.pieces[i][j].destination_square = base[i][j];
			game.pieces[i][j].colour = (Colour)i;
			game.pieces[i][j].is_moving = 0;
		}
	}
	game.turn_count = game.six_rolls = 0;
	game.player = (Colour)player_order[game.turn_count%4];
	
	game.show_dice = 0;
    	game.dice_show_time = 0;
	game.dice_phase = 0;
}

//Decides the best possible move currently
Move decide_move(){
	Move moves[NUM_PIECES], best_move = {.can_move=0};
	int moves_with_same_scores[NUM_PIECES], same_count=0, best_score = -1000;

	generate_possible_moves(moves, game.pieces[game.player]);			
	
	for(int i=0 ; i<NUM_PIECES ; i++){
		if(moves[i].can_move){
			get_score(moves[i]);
		}
	}
        
        for(int i=0 ; i<NUM_PIECES ; i++){
                if(moves[i].can_move && moves[i].score > best_score){
                        best_move = moves[i];
                        best_score = moves[i].score;
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

void get_score(Move move){
        move.score += score_reaching_center(&move);           // Highest priority
        move.score += score_capture_opponent(&move);          // High priority
        move.score += score_clear_start_position(&move);      // High priority when needed
        move.score += score_enter_from_base(&move);           // High priority when needed
        move.score += score_safety(&move);                   // Medium-high priority
        move.score += score_progress_toward_home(&move);      // Medium priority
        move.score += score_defensive_formation(&move);       // Low priority
        move.score += score_moving_to_danger(&move);          // Negative scoring
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
	//printf("Move is to %s\n",get_colour(game.player));
	best_move = decide_move();
	
	if(game.dice == 6) game.six_rolls++;
	//print_move(&best_move);

	if(best_move.can_move){
	        Piece *piece = &game.pieces[game.player][best_move.piece_index];
	        Square destination = get_square(best_move.to_index, best_move.to);
	        if (!(destination.type == 0 && destination.x == 0 && destination.y == 0 && destination.index == 0)) {
                        piece->destination_square = get_square(best_move.to_index, best_move.to);
                        piece->is_moving=1;        
                        //print_piece(piece);
			check_captures(&destination);	
                }
		
	}else{
		printf("MOVE PASSED\n======================\n");
	}

	if(game.dice != 6 || (game.dice == 6 && game.six_rolls > 3)){
		game.six_rolls = 0;
		game.turn_count++;
	}
}

void check_captures(Square *destination){
	for(int i=0 ; i<NUM_OPPONENTS ; i++){
		if ((Colour)i==game.player) continue;
		for(int j=0 ; j<NUM_PIECES ; j++){
			Piece *temp = &game.pieces[i][j]; 
			if(destination->index == temp->current_square.index && destination->type == temp->current_square.type){
				for(int k=0 ; k<NUM_BASE_SQUARES ; k++){
					int base_occupied = 0;
					for(int l=0 ; l<NUM_PIECES; l++){
						if(game.pieces[temp->colour][l].current_square.type == BASE && 
							game.pieces[temp->colour][l].current_square.index == k){
							base_occupied = 1;
							break;
						}	
					}
					if(!base_occupied){
						temp->destination_square = base[temp->colour][k];
						best_move.capture_available = 1;
						best_move.captured = temp;
					        return;
					}
				}
			}
		}
	}
}

//Score system for clearing start position to allow base pieces to enter
int score_clear_start_position(Move *move) {
        int start_pos = get_start(game.player);
        
        // High priority: Move piece away from start position if others are in base
        if (move->from == STANDARD && move->from_index == start_pos) {
                // Count pieces still in base
                int pieces_in_base = 0;
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (game.pieces[game.player][i].current_square.type == BASE) {
                        pieces_in_base++;
                    }
                }
                
                // The more pieces in base, the higher the priority to clear start
                return pieces_in_base * 15; // 15, 30, 45 points based on pieces in base
        }
        
        return 0;
}

//Score system for getting pieces out of base (entering board)
int score_enter_from_base(Move *move) {
        if (move->from == BASE && move->to == STANDARD) {
                // Count how many pieces are still in base
                int pieces_in_base = 0;
                for (int i = 0; i < NUM_PIECES; i++) {
                    if (game.pieces[game.player][i].current_square.type == BASE) {
                        pieces_in_base++;
                    }
                }
                
                // Higher score for getting pieces out when more are stuck
                return 10 + (pieces_in_base * 5); // 15-25 points based on base pieces
        }
        return 0;
}

//Score system for making progress toward home
int score_progress_toward_home(Move *move) {
        if (move->from == BASE && move->to == STANDARD) {
                return 5; // Basic progress from base
        }
        else if (move->from == STANDARD && move->to == STANDARD) {
                // Progress on main track
                return 3;
        }
        else if (move->from == STANDARD && move->to == HOME) {
                return 8; // Entering home stretch
        }
        else if (move->from == HOME && move->to == HOME) {
                return game.dice; // Progress in home based on dice value
        }
        else if (move->from == HOME && move->to == CENTER) {
                return game.dice + 5; // Bonus for reaching center
        }
        
        return 0;
}

//Score system for reaching center (winning)
int score_reaching_center(Move *move) {
        if (move->from == HOME && move->to == CENTER) {
                return 100; // Very high priority - this wins the piece!
        }
        return 0;
}

//Score system for capturing opponents
int score_capture_opponent(Move *move) {
        for (int i = 0; i < NUM_OPPONENTS; i++) {
                if (game.player == (Colour)i) continue;
                
                for (int j = 0; j < NUM_PIECES; j++) {
                        if ((move->to_index == game.pieces[i][j].current_square.index) && 
                            	(move->to == game.pieces[i][j].current_square.type) &&
	                	(move->to == STANDARD)) { // Can only capture on standard squares

                            	// Bonus for capturing pieces that are closer to home
                            	int opponent_progress = game.pieces[i][j].current_square.index;
                            	return 25 + (opponent_progress / 4); // 25-38 points based on opponent progress
                        }
                }
        }
        return 0;
}

//Score system for safety (entering home stretch)
int score_safety(Move *move) {
        if (move->from == STANDARD && move->to == HOME) {
                return 12; // High value for reaching safety
        }
        return 0;
}

//Score system for avoiding danger
int score_moving_to_danger(Move *move) {
        if (move->to != STANDARD) {
                return 0; // Only standard squares can be dangerous
        }
        
        int danger_penalty = 0;
        
        for (int i = 0; i < NUM_OPPONENTS; i++) {
            if (game.player == (Colour)i) continue;
            
            for (int j = 0; j < NUM_PIECES; j++) {
                    if (game.pieces[i][j].current_square.type != STANDARD) continue;
                    
                    int opponent_pos = game.pieces[i][j].current_square.index;
                    int distance = get_distance_standard(opponent_pos, move->to_index);
                    
                    // Danger zones: opponent can reach us in 1-6 moves
                    if (distance >= 1 && distance <= 6) {
                            // More dangerous if opponent is closer
                            danger_penalty -= (7 - distance) * 3; // -18 to -3 points
                            
                            // Extra penalty if opponent is very close (1-2 moves away)
                            if (distance <= 2) {
                                danger_penalty -= 10;
                            }
                    }
            }
        }
        
        return danger_penalty;
}

//Score system for forming defensive positions
int score_defensive_formation(Move *move) {
        if (move->to != STANDARD) return 0;
        
        // Small bonus for keeping pieces spread out on the board
        int pieces_on_board = 0;
        for (int i = 0; i < NUM_PIECES; i++) {
                if (game.pieces[game.player][i].current_square.type == STANDARD) {
                    pieces_on_board++;
                }
        }
        
        // Encourage having multiple pieces active
        return pieces_on_board * 2;
}

//generate the all the possible moves for the player
void generate_possible_moves(Move *moves, Piece *movable_pieces){
	for(int i=0 ; i<NUM_PIECES ; i++){

		moves[i].piece_index = i;
		moves[i].from_index = movable_pieces[i].current_square.index;
		moves[i].from = movable_pieces[i].current_square.type;
		moves[i].score = 0;
		moves[i].capture_available = 0;
		moves[i].captured = NULL;
	
		Square destination = get_destination(&movable_pieces[i], game.dice);
		
		//printf("dice is %d and %s - %d\n", game.dice, get_colour(movable_pieces[i].colour), destination.index);
		
		if(destination.x == 0 && destination.y == 0 && destination.type == 0 && destination.index == 0){
			moves[i].can_move = 0;
		}else{
		        moves[i].to_index = destination.index;
		        moves[i].to = destination.type;
		        moves[i].can_move = is_valid_move(&moves[i]);
		}
		//print_move(&moves[i]);
	}
}

//Checks the validity of the current move
int is_valid_move(Move *move){
	
	switch(move->from){
		case STANDARD:
			for(int i=0 ; i < NUM_PIECES ; i++){
                                if(move->piece_index == i) continue;

                                if((game.pieces[game.player][i].current_square.type == move->to) && 
                                  (move->to_index == game.pieces[game.player][i].current_square.index)){ 
					return 0;
				}
                        }
			return 1;

		case HOME:
			if(move->to_index != 0 && move->to != CENTER){
				return 0;
			}
			for(int i=0 ; i < NUM_PIECES ; i++){
				if(move->piece_index == i) continue;
				if((game.pieces[game.player][i].current_square.type == HOME) 
					&& (move->from_index <= game.pieces[game.player][i].current_square.index)
					&& (move->to_index >= game.pieces[game.player][i].current_square.index))
					 return 0;
			}
			return 1;		

		case BASE:
		        if(game.dice != 6) return 0;
			for(int i=0 ; i<NUM_PIECES ; i++){
				if (move->piece_index==i) continue;
				if(game.pieces[game.player][i].current_square.type == STANDARD && game.pieces[game.player][i].current_square.index == get_start(game.player)) return 0;
			}			
			return 1;
		case CENTER: return 0;			
		default: return 0;
	}
}
