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

int get_clockwise_distance_between_pieces(int from, int to) {
    return (to - from + 52) % 52;
}

int is_approach_passed(Piece *selected_piece){
	int current = selected_piece->index, destination = (current + game.dice)%52, approach = get_approach(game.player);
	
	if (current <= approach && destination > approach) {
    		return 1;
	} else if (current > approach && (destination > approach || destination < current)) {
		return 1;
	} else {
		return 0;
	}
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

void update_piece_position(Piece *piece, float speed) {
	Square target;
	switch(piece->location_type){
		case STANDARD:
			target = standard[piece->index];
			break;
		case HOME:
			target = home[piece->colour][piece->index];
			break;
		case BASE:
			target = base[piece->colour][piece->index];
			break;
	}
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

/*const char* get_piece_status(PieceStatus status){
	switch(status){
		case PIECE_STANDARD: return "PIECE_STANDARD";
		case PIECE_HOME: return "PIECE_HOME";
		case PIECE_BASE: return "PIECE_BASE";
		case PIECE_FINISHED: return "PIECE_FINISHED";
		default: 
			assert(0 && "Unhandled piece status in get_piece_status");
			return "UNKNOWN";
	}
}*/


