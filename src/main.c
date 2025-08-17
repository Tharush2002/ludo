#include "board_mapping.h"
#include "game_engine.h"
#include "gui.h"
#include "utils.h"
#include "types.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void manage_dice(int any_moving);
void automatic_mode();
void manual_mode();

int main(){
        srand(time(NULL));
   	if (!load_board_map("./assets/mappings.csv")) {
        	printf("Failed to load board map!\n");
        	return 1;
    	} 
	init_game();
	//log_mappings();    
    	init_gui();
    	render_game(game.pieces);
    	
    	// Automatic mode for demonstration
    	automatic_mode();
    	
    	// A fully manual mode to handle debugging more easier
    	//manual_mode();
    	
    	return 0;
}

void automatic_mode() {
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
        	
		update_finished_pieces();
		check_winner();

		if(!game.game_over){
			manage_dice(any_moving);		
		}
        	render_game(game.pieces);
    	}
    	cleanup_gui();
}

void manual_mode() {    
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
                
                // Update finished pieces (remove after 2 seconds in center)
                update_finished_pieces();
                
                // Check for winner
                check_winner();
                
                // Only allow moves if game is not over
                if (!game.game_over) {
                        // Check for SPACE key press to trigger next move
                        if (IsKeyPressed(KEY_SPACE)) {
                                // Only make a move if no pieces are currently moving
                                if (!any_moving) {
                                        printf("\n=== MOVE %d ===\n", game.turn_count + 1);
                                        printf("Player: %s\n", get_colour((Colour)game.player));
                                        
                                        game.dice = get_random_num(6);
                                        printf("Dice rolled: %d\n", game.dice);
                                        
                                        move_piece();
                                        
                                        printf("Move completed. Press SPACE for next move.\n");
                                } else {
                                        printf("Wait for current animation to complete...\n");
                                }
                        }
                } else {
                        // Game is over, show instructions
                        static int message_shown = 0;
                        if (!message_shown) {
                                printf("\n🎉 GAME FINISHED! 🎉\n");
                                printf("Winner: %s\n", get_colour(game.winner));
                                printf("Press ESC to exit.\n");
                                message_shown = 1;
                        }
                }
                
                render_game(game.pieces);
        }
        
        cleanup_gui();
}

void manage_dice(int any_moving){
        double current_time = GetTime();
        
        // State machine for dice and movement
        switch(game.dice_phase) {
        	case READY: // Ready for new dice roll
               		if (!any_moving) {
        	       		// Roll dice and show it
                		game.dice = get_random_num(6);
                		game.show_dice = 1;
                		game.dice_show_time = current_time;
                		game.dice_phase = 1;
                	}
                	break;
                
            	case SHOW: // Showing dice
                	if (current_time - game.dice_show_time > 1.5) { // Show dice for 1.5 seconds
                		// Hide dice and start movement
                		game.show_dice = 0;
                		move_piece();
                    		game.dice_phase = 2;
                	}
                	break;
                
            	case MOVE: // Moving pieces
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
