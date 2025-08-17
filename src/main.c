#include "board_mapping.h"
#include "game_engine.h"
#include "gui.h"
#include "utils.h"
#include "types.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void manage_dice(int any_moving);

int main() {
	srand(time(NULL));
   	if (!load_board_map("./assets/mappings.csv")) {
        	printf("Failed to load board map!\n");
        	return 1;
    	} 
	init_game();
	//log_mappings();    
    	init_gui();
    	render_game(game.pieces);
   	sleep_ms(1000);
	 
    	while (!should_close_window()) {        
        	// Update all piece positions every frame
        	int any_moving = 0;
        	for (int i = 0; i < NUM_OPPONENTS; i++) {
            		for (int j = 0; j < NUM_PIECES ; j++) {
                		if (update_piece_position(&game.pieces[i][j], MOVE_SPEED)) {
                    			any_moving = 1;
                		}
            		}
        	}
        	
		manage_dice(any_moving);		
        	render_game(game.pieces);
    	}
    	cleanup_gui();
    	return 0;
}

void manage_dice(int any_moving){
        double current_time = GetTime();
        
        // State machine for dice and movement
        switch(game.dice_phase) {
        	case 0: // Ready for new dice roll
               		if (!any_moving) {
        	       		// Roll dice and show it
                		game.dice = get_random_num(6);
                		game.show_dice = 1;
                		game.dice_show_time = current_time;
                		game.dice_phase = 1;
                	}
                	break;
                
            	case 1: // Showing dice
                	if (current_time - game.dice_show_time > 1.5) { // Show dice for 1.5 seconds
                		// Hide dice and start movement
                		game.show_dice = 0;
                		move_piece();
                    		game.dice_phase = 2;
                	}
                	break;
                
            	case 2: // Moving pieces
                	if (!any_moving) {
                		// All movement complete, ready for next dice roll after small delay
                		static double movement_complete_time = 0;
                		if (movement_complete_time == 0) {
                       			movement_complete_time = current_time;
                		}
                    
                		if (current_time - movement_complete_time > 0.5) { // Small delay before next roll
                      			movement_complete_time = 0;
                       			game.dice_phase = 0;
                		}
                	}
                	break;
        }
        
}

/*#include "board_mapping.h"
#include "game_engine.h"
#include "gui.h"
#include "utils.h"
#include "types.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    srand(time(NULL));
    if (!load_board_map("./assets/mappings.csv")) {
        printf("Failed to load board map!\n");
        return 1;
    }
    init_game();
    log_mappings();    
    init_gui();
    render_game(game.pieces);
    
    printf("=== DEBUG MODE CONTROLS ===\n");
    printf("SPACE: Make next move\n");
    printf("ESC: Exit game\n");
    printf("===========================\n");
    
    while (!should_close_window()) {
        // Update all piece positions every frame (animations continue)
        int any_moving = 0;
        for (int i = 0; i < NUM_OPPONENTS; i++) {
            for (int j = 0; j < NUM_PIECES ; j++) {
                if (update_piece_position(&game.pieces[i][j], MOVE_SPEED)) {
                    any_moving = 1;
                }
            }
        }
        
        //double current_time = GetTime();
        
        // Check for SPACE key press to trigger next move
        if (IsKeyPressed(KEY_SPACE)) {
            // Only make a move if no pieces are currently moving
            if (!any_moving) {
                //printf("\n=== MOVE %d ===\n", game.turn_count + 1);
                //printf("Player: %s\n", get_colour((Colour)game.player));
                
                game.dice = get_random_num(6);
                //printf("Dice rolled: %d\n", game.dice);
                
                move_piece();
                
                //printf("Move completed. Press SPACE for next move.\n");
            } else {
                //printf("Wait for current animation to complete...\n");
            }
        }
        
        render_game(game.pieces);
    }
    
    cleanup_gui();
    return 0;
}*/



