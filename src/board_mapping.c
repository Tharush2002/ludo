#include "board_mapping.h"

Square standard[52];
Base_Squares base[4];
Home_Squares home[4];

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
	int index, x, y, i;	

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
					i=0;
					home[i].colour = COLOUR_RED;
				}else if(strcmp(colour, "BLUE") == 0){	
					i=1;
					home[i].colour = COLOUR_BLUE;
				}else if(strcmp(colour, "GREEN") == 0){
					i=2;
					home[i].colour = COLOUR_GREEN;
				}else if(strcmp(colour, "YELLOW") == 0){	
					i=3;
					home[i].colour = COLOUR_YELLOW;
				}	
				home[i].square[index].x = x;
				home[i].square[index].y = y;
				break;
			case BASE:	
				if (sscanf(line, "%[^,],%d,%d,%d\n",colour, &index, &x, &y) != 4) break;		
				if(strcmp(colour, "RED") == 0){
					i=0;
					base[i].colour = COLOUR_RED;
				}else if(strcmp(colour, "BLUE") == 0){	
					i=1;
					base[i].colour = COLOUR_BLUE;
				}else if(strcmp(colour, "GREEN") == 0){
					i=2;
					base[i].colour = COLOUR_GREEN;
				}else if(strcmp(colour, "YELLOW") == 0){	
					i=3;
					base[i].colour = COLOUR_YELLOW;
				}	
				base[i].square[index].x = x;
				base[i].square[index].y = y;
		}
    	}
}
