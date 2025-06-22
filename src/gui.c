#include "raylib.h"

#define BOARD_SIZE 15
#define CELL_SIZE 40

typedef struct {
    int x, y; // Board coordinates
    Color color;
} Piece;

int main(void) {
    InitWindow(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE, "Ludo Demo - Raylib");

    Piece piece = {1, 6, GREEN}; // Start at (1,6) for demonstration

    while (!WindowShouldClose()) {
        // Move piece with arrow keys
        if (IsKeyPressed(KEY_RIGHT)) piece.x++;
        if (IsKeyPressed(KEY_LEFT))  piece.x--;
        if (IsKeyPressed(KEY_UP))    piece.y--;
        if (IsKeyPressed(KEY_DOWN))  piece.y++;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw board grid
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHTGRAY);

        // Draw piece
        DrawCircle(piece.x * CELL_SIZE + CELL_SIZE/2, piece.y * CELL_SIZE + CELL_SIZE/2, CELL_SIZE/2 - 5, piece.color);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

