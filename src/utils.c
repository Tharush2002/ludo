#include "utils.h"
//#include "board_mapping.h"

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


