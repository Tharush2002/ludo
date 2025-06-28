#include "board_mapping.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define BOARD_WIDTH 1024   // Set to your image width
#define BOARD_HEIGHT 1024  // Set to your image height
#define NUM_SQUARES 52
#define MOVE_SPEED 8.0f

typedef struct {
    //Vector2 pos; // Position in pixels
    int board_index;
    float x,y;
    Color color;
} Piece;

int main(void) {
	if (!load_board_map("./assets/mappings.csv")) {
        	printf("Failed to load board map!\n");
	        return 1;
    	}

	InitWindow(BOARD_WIDTH, BOARD_HEIGHT, "Ludo Board Game");

	// Load the board image as a texture
	Texture2D board = LoadTexture("./assets/board.png"); // <-- Use your image file here

	if (board.id == 0) {
        	printf("Failed to load board image!\n");
	        CloseWindow();
	        return 1;
	}

	// Example: one green piece
	Piece greenPiece = { .board_index=0, .x=576, .y=126, .color = GREEN };

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
        	// Example: move piece with arrow keys
	        if (IsKeyPressed(KEY_RIGHT)) greenPiece.board_index = (greenPiece.board_index + 1) % NUM_SQUARES;
		if (IsKeyPressed(KEY_LEFT)) greenPiece.board_index = (greenPiece.board_index + 1) % NUM_SQUARES;
	        //if (IsKeyDown(KEY_DOWN))  greenPiece.pos.y += 2;
	        //if (IsKeyDown(KEY_UP))    greenPiece.pos.y -= 2;

        	BeginDrawing();
	        ClearBackground(RAYWHITE);

        	DrawTexture(board, 0, 0, WHITE); // Draw the board image

	        // Draw the piece on top
	        BoardSquares target = board_squares[greenPiece.board_index];

		if (fabs(greenPiece.x - target.x) > MOVE_SPEED) {
			greenPiece.x += (greenPiece.x < target.x) ? MOVE_SPEED : -MOVE_SPEED;
		} else {
			greenPiece.x = target.x;
		}

		if (fabs(greenPiece.y - target.y) > MOVE_SPEED) {
			greenPiece.y += (greenPiece.y < target.y) ? MOVE_SPEED : -MOVE_SPEED;
		} else {
			greenPiece.y = target.y;
		}

	        DrawCircle(greenPiece.x, greenPiece.y, 20, greenPiece.color);

	        EndDrawing();
	}

	UnloadTexture(board);
	CloseWindow();
	return 0;
}

