#include "board_mapping.h"

Square standard[52], base[NUM_OPPONENTS][4], home[NUM_OPPONENTS][5];

int load_board_map(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) return 0;
	
	load_squares(file, STANDARD);
	load_squares(file, HOME);
	load_squares(file, BASE);
	
	fclose(file);
	return 1;
}

void load_squares(FILE *file, SquareType type){
	char line[256], colour[10];
	int index, x, y;	

	bypass_lines_until(file, line, type);

	while (fgets(line, sizeof(line), file)) {
    		line[strcspn(line, "\r\n")] = 0;
		if (line[0] == '\0') break;
		
		switch(type){
			case STANDARD:
				if (sscanf(line, "%d,%d,%d\n",&index, &x, &y) != 3) break;
	 			standard[index].x = x;
				standard[index].y = y;				
				break;
			case HOME:				
				if (sscanf(line, "%[^,],%d,%d,%d\n",colour, &index, &x, &y) != 4) break;		
				if(strcmp(colour, "RED") == 0){
					home[COLOUR_RED][index].x = x;
					home[COLOUR_RED][index].y = y;
				}else if(strcmp(colour, "BLUE") == 0){	
					home[COLOUR_BLUE][index].x = x;
					home[COLOUR_BLUE][index].y = y;
				}else if(strcmp(colour, "GREEN") == 0){	
					home[COLOUR_GREEN][index].x = x;
					home[COLOUR_GREEN][index].y = y;
				}else if(strcmp(colour, "YELLOW") == 0){		
					home[COLOUR_YELLOW][index].x = x;
					home[COLOUR_YELLOW][index].y = y;
				}	
				break;
			case BASE:	
				if (sscanf(line, "%[^,],%d,%d,%d\n",colour, &index, &x, &y) != 4) break;		
				if(strcmp(colour, "RED") == 0){
					base[COLOUR_RED][index].x = x;
					base[COLOUR_RED][index].y = y;
				}else if(strcmp(colour, "BLUE") == 0){	
					base[COLOUR_BLUE][index].x = x;
					base[COLOUR_BLUE][index].y = y;
				}else if(strcmp(colour, "GREEN") == 0){
					base[COLOUR_GREEN][index].x = x;
					base[COLOUR_GREEN][index].y = y;
				}else if(strcmp(colour, "YELLOW") == 0){	
					base[COLOUR_YELLOW][index].x = x;
					base[COLOUR_YELLOW][index].y = y;
				}	
		}
	}
}
