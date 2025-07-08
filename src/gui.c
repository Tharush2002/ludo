#include "gui.h"
#include "raylib.h"
#include <stdio.h>

static Texture2D board_texture, red_piece, blue_piece, green_piece, yellow_piece;

void init_gui(void) {
	InitWindow(1024, 1024, "Ludo Board Game");
	board_texture = LoadTexture("./assets/board.png");
	red_piece = LoadTexture("./assets/red.png");
	blue_piece = LoadTexture("./assets/blue.png");
	green_piece = LoadTexture("./assets/green.png");
	yellow_piece = LoadTexture("./assets/yellow.png");
	SetTargetFPS(60);
}

void cleanup_gui(void) {
	UnloadTexture(board_texture);
	UnloadTexture(red_piece);
	UnloadTexture(blue_piece);
	UnloadTexture(green_piece);	
	UnloadTexture(yellow_piece);
	CloseWindow();
}

void render_game(Piece (*pieces)[NUM_PIECES]) {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawTexture(board_texture, 0, 0, WHITE);

	for (int i = 0; i < NUM_OPPONENTS ; i++) {
		Texture2D piece_texture = get_texture(pieces[i][0].colour);
		for(int j = 0 ; j < NUM_PIECES ; j++){
			DrawTexture(
				piece_texture, 
				(int)pieces[i][j].current_x - piece_texture.width / 2, 
				(int)pieces[i][j].current_y - piece_texture.height / 2, 
				WHITE
			);
		}
    	}

	//DrawCircle(512, 512, 20, GREEN);		
	EndDrawing();
}

Texture2D get_texture(Colour colour){
	switch(colour){
		case COLOUR_RED: return red_piece;
		case COLOUR_BLUE: return blue_piece;
		case COLOUR_GREEN: return green_piece;
		case COLOUR_YELLOW: return yellow_piece;
		default:
			assert(0 && "Unhandled colour in getTexture");
        		return red_piece;
	}
}

int should_close_window(void) {
    return WindowShouldClose();
}

