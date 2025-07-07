#include "board_mapping.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

Square standard[52];
Base_Squares base[4];
Home_Squares home[4];

int load_board_map(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) return 0;

	printf("Loading board map...\n");	
	load_squares(file, STANDARD);
	load_squares(file, HOME);
	load_squares(file, BASE);
	
	fclose(file);
	printf("Finished loading map\n");
	return 1;
}

void load_squares(FILE *file, SquareType type){
	char line[256], colour[10];
	int index, x, y, i;	

	printf("→ Calling bypass_lines_until for %s\n", get_square_type(type));
	bypass_lines_until(file, line, type);
	printf("✓ Section header found: %s\n", line);

	while (fgets(line, sizeof(line), file)) {
    		line[strcspn(line, "\r\n")] = 0;
		if (line[0] == '\0') break;
		
		switch(type){
			case STANDARD:
				if (sscanf(line, "%d,%d,%d\n",&index, &x, &y) != 3) break;
	 			standard[index].x = x;
				standard[index].y = y;			
				printf("STANDARD[%d] = (%d, %d)\n", index, x, y);	
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

void bypass_lines_until(FILE *file, char *line, SquareType type){
	const char *section = get_square_type(type);
	printf("→ Looking for section: '%s'\n", section);
	while (fgets(line, 256, file)) {
		line[strcspn(line, "\r\n")] = 0;
		printf("Comparing line: '%s'\n", line);
		if (strcmp(line, section) == 0){
			printf("✓ Found section: '%s'\n", section);
			break;
		}
	}
	fgets(line, sizeof(line), file);
}

/*int load_main_squares(const char *main_squares){
	FILE *file = fopen(main_squares, "r");
	if(!file) return 0;
	int index, x, y;

	fscanf(file, "index, x coordinates, y coordinates\n");
	for (int i = 0; i < 52; ++i) {
        	if (fscanf(file, "%d,%d,%d\n",&index, &x, &y) != 3) break;
	        main[index].x = x;
        	main[index].y = y;

		printf("%d\t%d",main[index].x,main[index].y);
	}
	fclose(file);
	return 1;
}

int load_non_main_squares(const char *non_main_squares){	
	FILE *file = fopen(non_main_squares, "r");
	if(!file) return 0;
	int index, x, y;
	char *colour;

	fscanf(file, "index, colour, x coordinates, y coordinates\n");
	for (int i = 0; i < 52; ++i) {
        	if (fscanf(file, "%d,%s,%d,%d\n", &index, *colour, &x, &y) != 4) break;
	        [index].x = x;
        	main[index].y = y;
		

		printf("%d\t%d",main[index].x,main[index].y);
	}
	fclose(file);
}
*/
