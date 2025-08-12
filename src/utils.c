#include "utils.h"

const char* get_colour(Colour colour){
	switch(colour){
		case COLOUR_RED: return "RED";
		case COLOUR_BLUE: return "BLUE";
		case COLOUR_GREEN: return "GREEN";
		case COLOUR_YELLOW: return "YELLOW";
		default: 
			assert(0 && "Unhandled colour in get_colour");
			return "UNKNOWN";
	}	
}

const char* get_square_type(SquareType type){
	switch(type){
		case STANDARD: return "STANDARD SQUARES";
		case HOME: return "HOME SQUARES";
		case BASE: return "BASE SQUARES";
		default: 	
			assert(0 && "Unhandled square type in get_square_type");
			return "UNKNOWN";
	}
}

const char* get_piece_status(PieceStatus status){
	switch(status){
		case PIECE_STANDARD: return "PIECE_STANDARD";
		case PIECE_HOME: return "PIECE_HOME";
		case PIECE_BASE: return "PIECE_BASE";
		case PIECE_FINISHED: return "PIECE_FINISHED";
		default: 
			assert(0 && "Unhandled piece status in get_piece_status");
			return "UNKNOWN";
	}
}

int get_approach(Colour colour){
	switch(colour){
		case COLOUR_RED: return RED_APPROACH;
		case COLOUR_BLUE: return BLUE_APPROACH;
		case COLOUR_GREEN: return GREEN_APPROACH;
		case COLOUR_YELLOW: return YELLOW_APPROACH;
		default: 	
			assert(0 && "Unhandled colour to get an approach index");
			return -1;
	}
}

int get_start(Colour colour){
	switch(colour){
		case COLOUR_RED: return RED_START;
		case COLOUR_BLUE: return BLUE_START;
		case COLOUR_GREEN: return GREEN_START;
		case COLOUR_YELLOW: return YELLOW_START;
		default: 	
			assert(0 && "Unhandled colour to get an start index");
			return -1;
	}
}

int get_random_num(int num){
	return rand() % num + 1;
}

int get_distance_standard(int from, int to) {
    return (to - from + 52) % 52;
}

int is_approach_passed(Piece *selected_piece, int steps){
	int current = selected_piece->current_square.index, destination = (current + steps)%52, approach = get_approach(selected_piece->colour);
	
	if (current < destination) {
        	if (approach > current && approach <= destination) return 1;
        
    	}else if (current > destination) {
        	if (approach > current || approach <= destination) return 1;
        }
	return 0;
}

Square get_square(int index, SquareType type){
	Square empty = {0};
        switch(type){
                case STANDARD:
                      	return standard[index]; 
                case HOME:
	                return home[game.player][index];
                case BASE:
                      	return base[game.player][index];
		case CENTER:
			return center[game.player][0];
		default:
			assert(0 && "Unhandled square type in get_square");
			return empty;
        }
}

Square get_destination(Piece *piece, int steps) {
        Square square = {0};
        
        switch(piece->current_square.type) {
                case STANDARD:
                        if(is_approach_passed(piece, steps)) {
                            int distance_to_approach = get_distance_standard(
                                piece->current_square.index, 
                                get_approach(piece->colour)
                            );
                            int remaining_steps = steps - distance_to_approach - 1;
                            
                            if (remaining_steps < NUM_HOME_SQUARES) {
                                return home[piece->colour][remaining_steps];
                                //square.type = HOME; // Ensure type is set
                                //return square;
                            }
                        } else {
                            return standard[(piece->current_square.index + steps) % NUM_STANDARD_SQUARES];
                            //square.type = STANDARD; // Ensure type is set
                            //return square;
                        }
                        break;
                    
                case HOME:
                        if((piece->current_square.index + steps) < NUM_HOME_SQUARES) {
                            return home[piece->colour][piece->current_square.index + steps];
                            //square.type = HOME;
                        } else if((piece->current_square.index + steps) == NUM_HOME_SQUARES) {
                            return center[piece->colour][0];
                            //square.type = CENTER;
                        }
                        return square;
                    
                case BASE:
                        if (steps == 6) {
                            int start = get_start(piece->colour);
                            return standard[start];
                            //square.type = STANDARD;
                        }
                        return square;
                    
                case CENTER:
                        return square; // Cannot move from center
                    
                default:
                        return square;
        }
        
        return square;
}

Square get_next_square_in_path(Piece *piece) {
        Square current = piece->current_square;
        Square destination = piece->destination_square;
        Square empty = {0};
        
        // If already at destination
        if (current.x == destination.x && current.y == destination.y &&
                current.index == destination.index && current.type == destination.type) {
                return empty;
        }
        
        // Handle different path scenarios
        if (current.type == STANDARD && destination.type == STANDARD) {
                // Moving along standard track
                int current_index = current.index;
                int destination_index = destination.index;
                
                // Calculate next index (wrapping around if necessary)
                int next_index = (current_index + 1) % NUM_STANDARD_SQUARES;
                
                // If we're going backwards or the direct path is shorter
                int forward_distance = (destination_index - current_index + NUM_STANDARD_SQUARES) % NUM_STANDARD_SQUARES;
                
                if (forward_distance == 0) {
                    return empty; // Already at destination
                }
                
                return standard[next_index];
        }
        else if (current.type == STANDARD && destination.type == HOME) {
                // Check if we need to turn into home path
                int approach = get_approach(piece->colour);
                
                if (current.index == approach) {
                    // Turn into home path
                    return home[piece->colour][0];
                } else {
                    // Continue on standard track toward approach
                    int next_index = (current.index + 1) % NUM_STANDARD_SQUARES;
                    return standard[next_index];
                }
        }
        else if (current.type == HOME && destination.type == HOME) {
                // Moving along home path
                if (current.index + 1 <= destination.index && current.index + 1 < NUM_HOME_SQUARES) {
                    return home[piece->colour][current.index + 1];
                }
                return empty;
        }
        else if (current.type == HOME && destination.type == CENTER) {
                // Check if we're at the last home square
                if (current.index == NUM_HOME_SQUARES - 1) {
                    return destination; // Move directly to center
                } else {
                    // Move to next home square
                    return home[piece->colour][current.index + 1];
                }
        }
        else if (current.type == BASE && destination.type == STANDARD) {
                // Moving from base directly to start position
                return destination;
        }
        
        return empty;
}

int update_piece_position(Piece *piece, float speed) {
        const float epsilon = 1.0f;
        
        // If piece is not marked as moving, don't update position
        if (!piece->is_moving) {
                return 0;
        }
        
        // Check if we've reached the final destination
        if (piece->current_square.x == piece->destination_square.x && 
                piece->current_square.y == piece->destination_square.y &&
                piece->current_square.index == piece->destination_square.index &&
                piece->current_square.type == piece->destination_square.type) {
                piece->is_moving = 0;
                return 0; // Movement complete
        }
        
        // Get the next square in the path
        Square next_square = get_next_square_in_path(piece);
        
        // If no valid next square, stop movement
        if (next_square.type == 0 && next_square.x == 0 && next_square.y == 0) {
                piece->is_moving = 0;
                return 0;
        }
        
        // Calculate distance to next square (not final destination)
        float delta_x = (float)next_square.x - (float)piece->current_square.x;
        float delta_y = (float)next_square.y - (float)piece->current_square.y;
        
        // Check if we've reached this intermediate square
        if (fabsf(delta_x) <= epsilon && fabsf(delta_y) <= epsilon) {
                // Move to the next square
                piece->current_square = next_square;
                
                // Check if this was our final destination
                if (next_square.x == piece->destination_square.x && 
                    next_square.y == piece->destination_square.y &&
                    next_square.index == piece->destination_square.index &&
                    next_square.type == piece->destination_square.type) {
                    piece->is_moving = 0;
                    return 0; // Reached final destination
                }
                
                return 1; // Continue moving to next square
        }
        
        // Move towards the next square
        if (fabsf(delta_x) > speed) {
                piece->current_square.x += (int)((delta_x > 0) ? speed : -speed);
        } else {
                piece->current_square.x = next_square.x;
        }
        
        if (fabsf(delta_y) > speed) {
                piece->current_square.y += (int)((delta_y > 0) ? speed : -speed);
        } else {
                piece->current_square.y = next_square.y;
        }
        
        return 1; // Still moving
}

int any_piece_moving() {
        for (int i = 0; i < NUM_OPPONENTS; i++) {
                for (int j = 0; j < 4; j++) {
                        if (game.pieces[i][j].is_moving) {
                                return 1;
                        }
                }
        }
        return 0;
}

void bypass_lines_until(FILE *file, char *line, SquareType type){
	const char *section = get_square_type(type);
	while (fgets(line, 256, file)) {
		line[strcspn(line, "\r\n")] = 0;
		if (strcmp(line, section) == 0){
			break;
		}
	}
	fgets(line, sizeof(line), file);
}

void log_mappings(){	
	printf("================================================\n");
	printf("=====================STANDARD===================\n");
	printf("================================================\n");

	for(size_t i=0 ; i<sizeof(standard)/sizeof(standard[0]) ; i++){
		printf("x - %d\ty - %d\n",standard[i].x,standard[i].y);
	}	

	printf("================================================\n");
	printf("======================HOME======================\n");
	printf("================================================\n");

	for(size_t i=0 ; i<sizeof(home)/sizeof(home[0]) ; i++){
		for(size_t j=0 ; j<sizeof(home[0])/sizeof(home[0][0]) ; j++){
			printf("colour - %s\tx - %d\ty - %d\n",get_colour(i), home[i][j].x, home[i][j].y);
		}
	}	
	
	printf("================================================\n");
	printf("======================BASE======================\n");
	printf("================================================\n");

	for(size_t i=0 ; i<sizeof(base)/sizeof(base[0]) ; i++){
		for(size_t j=0 ; j<sizeof(base[0])/sizeof(base[0][0]) ; j++){
			printf("colour - %s\tx - %d\ty - %d\n",get_colour(i), base[i][j].x, base[i][j].y);
		}
	}
}

void print_piece(Piece *p){
	printf("=====================\n");
	printf("Current Index - %d\n",p->current_square.index);
	printf("Current Piece Status - %s\n",get_square_type(p->current_square.type));
	printf("Current X - %d\n",p->current_square.x);
	printf("Current Y - %d\n",p->current_square.y);
	printf("Destination Index - %d\n",p->destination_square.index);
	printf("Destination Piece Status - %s\n",get_square_type(p->destination_square.type));
	printf("Destination X - %d\n",p->destination_square.x);
	printf("Destination Y - %d\n",p->destination_square.y);
	printf("Colour - %s\n",get_colour(p->colour));
	printf("=====================\n");
}

void print_move(Move *m){
	printf("======================\n");
	printf("Piece Index - %d\n",m->piece_index);
	printf("From Index - %d\n",m->from_index);
	printf("To Index - %d\n",m->to_index);
	printf("Score - %d\n",m->score);
	printf("Can move - %s\n",m->can_move==1 ? "TRUE":"FALSE");
	printf("From Status - %s\n",get_square_type(m->from));
	printf("To Status - %s\n",get_square_type(m->to));
	printf("======================\n");
}


