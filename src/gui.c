#include "gui.h"

static Texture2D board_texture, red_piece, blue_piece, green_piece, yellow_piece, dice1, dice2, dice3, dice4, dice5, dice6;

void init_gui(void) {
	InitWindow(1024, 1024, "Ludo Board Game");
	board_texture = LoadTexture("./assets/board.png");
	red_piece = LoadTexture("./assets/red.png");
	blue_piece = LoadTexture("./assets/blue.png");
	green_piece = LoadTexture("./assets/green.png");
	yellow_piece = LoadTexture("./assets/yellow.png");
	dice1 = LoadTexture("./assets/1.png");
	dice2 = LoadTexture("./assets/2.png");
	dice3 = LoadTexture("./assets/3.png");
	dice4 = LoadTexture("./assets/4.png");
	dice5 = LoadTexture("./assets/5.png");
	dice6 = LoadTexture("./assets/6.png");
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

	if(game.dice!=0){
		Texture2D dice = get_dice(game.dice);
		DrawTexture(
			dice,
			512 - dice.width / 2,
			512 - dice.height / 2,
			WHITE
		);
	}

	for (int i = 0; i < NUM_OPPONENTS ; i++) {
		Texture2D piece_texture = get_texture(pieces[i][0].colour);
		for(int j = 0 ; j < NUM_PIECES ; j++){
			DrawTexture(
				piece_texture, 
				(int)pieces[i][j].current_square.x - piece_texture.width / 2, 
				(int)pieces[i][j].current_square.y - piece_texture.height / 2, 
				WHITE
			);
			//print_pieces(&pieces[i][j]);
		}
    	}
	
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

Texture2D get_dice(int value){
	switch(value){
		case 1: return dice1;
		case 2: return dice2;
		case 3: return dice3;
		case 4: return dice4;
		case 5: return dice5;
		case 6: return dice6;
		default:
			assert(0 && "Invalid value in get_dice");
			return dice1;
	}
}

int should_close_window(void) {
    return WindowShouldClose();
}

