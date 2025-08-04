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
        
        // Only make a new move when no pieces are moving
        if (!any_moving) {
            game.dice = get_random_num(6);
            move_piece();
            sleep(1); // Reduced sleep time since movement is animated
        }
        
        render_game(game.pieces);
    }
    cleanup_gui();
    return 0;
}
