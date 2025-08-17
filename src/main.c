/*#include "board_mapping.h"
#include "game_engine.h"
#include "gui.h"
#include "utils.h"
#include "types.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    srand(time(NULL));
    if (!load_board_map("./assets/mappings.csv")) {
        printf("Failed to load board map!\n");
        return 1;
    }
    init_game();
    log_mappings();    
    init_gui();
    render_game(game.pieces);
    
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
            
            // Only make a new move when no pieces are moving AND sufficient time has passed
            static double last_move_time = 0;
            double current_time = GetTime();
            
            if (!any_moving && (current_time - last_move_time) > 1.0) {
                game.dice = get_random_num(6);
                move_piece();
                last_move_time = current_time;
            }
            
            render_game(game.pieces);
    }
    cleanup_gui();
    return 0;
}*/

#include "board_mapping.h"
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
}



