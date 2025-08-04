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
	int i, x, y;	

	bypass_lines_until(file, line, type);

	while (fgets(line, sizeof(line), file)) {
    		line[strcspn(line, "\r\n")] = 0;
		if (line[0] == '\0') break;
		
		switch(type){
			case STANDARD:
				if (sscanf(line, "%d,%d,%d\n",&i, &x, &y) != 3) break;
				standard[i].index = i;
 	 			standard[i].x = x;
				standard[i].y = y;
				standard[i].type = STANDARD;				
				break;
			case HOME:				
				if (sscanf(line, "%[^,],%d,%d,%d\n",colour, &i, &x, &y) != 4) break;		
				if(strcmp(colour, "RED") == 0){
				        home[COLOUR_RED][i].index = i;
					home[COLOUR_RED][i].x = x;
					home[COLOUR_RED][i].y = y;
					home[COLOUR_RED][i].type = HOME;
				}else if(strcmp(colour, "BLUE") == 0){	
				        home[COLOUR_BLUE][i].index = i;
					home[COLOUR_BLUE][i].x = x;
					home[COLOUR_BLUE][i].y = y;
					home[COLOUR_BLUE][i].type = HOME;
				}else if(strcmp(colour, "GREEN") == 0){	
				        home[COLOUR_GREEN][i].index = i;
					home[COLOUR_GREEN][i].x = x;
					home[COLOUR_GREEN][i].y = y;
					home[COLOUR_GREEN][i].type = HOME;
				}else if(strcmp(colour, "YELLOW") == 0){
				        home[COLOUR_YELLOW][i].index = i;
					home[COLOUR_YELLOW][i].x = x;
					home[COLOUR_YELLOW][i].y = y;
					home[COLOUR_YELLOW][i].type = HOME;
				}	
				break;
			case BASE:	
				if (sscanf(line, "%[^,],%d,%d,%d\n",colour, &i, &x, &y) != 4) break;		
				if(strcmp(colour, "RED") == 0){
				        base[COLOUR_RED][i].index = i;
					base[COLOUR_RED][i].x = x;
					base[COLOUR_RED][i].y = y;	
					base[COLOUR_RED][i].type = BASE;
				}else if(strcmp(colour, "BLUE") == 0){	
				        base[COLOUR_BLUE][i].index = i;
					base[COLOUR_BLUE][i].x = x;
					base[COLOUR_BLUE][i].y = y;
					base[COLOUR_BLUE][i].type = BASE;
				}else if(strcmp(colour, "GREEN") == 0){
				        base[COLOUR_GREEN][i].index = i;
					base[COLOUR_GREEN][i].x = x;
					base[COLOUR_GREEN][i].y = y;
					base[COLOUR_GREEN][i].type = BASE;
				}else if(strcmp(colour, "YELLOW") == 0){
				        base[COLOUR_YELLOW][i].index = i;
					base[COLOUR_YELLOW][i].x = x;
					base[COLOUR_YELLOW][i].y = y;
					base[COLOUR_YELLOW][i].type = BASE;
				}	
		}
	}
}
