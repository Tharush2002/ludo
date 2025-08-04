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
	int current = selected_piece->index, destination = (current + steps)%52, approach = get_approach(selected_piece->colour);
	
	if (current < destination) {
        	if (approach > current && approach <= destination) return 1;
        
    	}else if (current > destination) {
        	if (approach > current || approach <= destination) return 1;
        }
	return 0;
}

Square get_destination(Piece *piece, int steps){
	Square empty = {0};
	switch(piece->status){
		case PIECE_STANDARD:
			if(is_approach_passed(piece, game.dice)){
				int i = get_distance_standard(piece->index, get_approach(piece->colour));
				int j = steps - i - 1; // because home path is zero based	
				return home[piece->colour][j];
			}else{
				return standard[(piece->index + steps)%52];
			}
		case PIECE_HOME:
			if((piece->index + steps)<5){
				return home[piece->colour][piece->index + steps];
			}
			return empty;
		case PIECE_BASE:
			int start = get_start(piece->colour);
			//printf("\n\n\n\nPiece %s start is %d\n\n\n\n",get_colour(piece->colour),start);
			return steps == 6 ? standard[start] : empty;
		case PIECE_FINISHED:
			return empty;
		default:
			assert(0 && "Unhandled piece status in get_destination");
			return empty;
	}
}

int update_piece_position(Piece *piece, float speed) {
    Square *target;
    switch(piece->status) {
        case PIECE_STANDARD:
            target = &standard[piece->index];
            break;
        case PIECE_BASE:
            target = &base[piece->colour][piece->index];
            break;
        case PIECE_HOME:
            target = &home[piece->colour][piece->index];
            break;
        default:            
            return 0; // No valid target
    }
    
    const float epsilon = 1.0f; // When to consider "arrived"
    
    // Calculate distance to target
    float delta_x = target->x - piece->current_x;
    float delta_y = target->y - piece->current_y;
    
    // Check if we're close enough to target
    if (fabsf(delta_x) <= epsilon && fabsf(delta_y) <= epsilon) {
        piece->current_x = target->x;  // Snap to exact position
        piece->current_y = target->y;
        piece->is_moving = 0;      // Mark as not moving
        return 0; // Movement complete
    }
    
    // Move towards target
    piece->is_moving = 1;
    
    if (fabsf(delta_x) > speed) {
        piece->current_x += (delta_x > 0) ? speed : -speed;
    } else {
        piece->current_x = target->x;
    }
    
    if (fabsf(delta_y) > speed) {
        piece->current_y += (delta_y > 0) ? speed : -speed;
    } else {
        piece->current_y = target->y;
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
	printf("Index - %d\n",p->index);
	printf("Piece Status - %s\n",get_piece_status(p->status));
	printf("Current X - %f\n",p->current_x);
	printf("Current Y - %f\n",p->current_y);
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
	printf("From Status - %s\n",get_piece_status(m->from_status));
	printf("To Status - %s\n",get_piece_status(m->to_status));
	printf("======================\n");
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


