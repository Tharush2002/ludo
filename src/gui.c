#include "gui.h"
#include "raylib.h"

static Texture2D board_texture;

void init_gui(void) {
    InitWindow(1024, 1024, "Ludo Board Game");
    board_texture = LoadTexture("./assets/board.png");
    SetTargetFPS(60);
}

void cleanup_gui(void) {
    UnloadTexture(board_texture);
    CloseWindow();
}

void render_game(float x, float y) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(board_texture, 0, 0, WHITE);
    DrawCircle((int)x, (int)y, 20, GREEN);
    EndDrawing();
}

int should_close_window(void) {
    return WindowShouldClose();
}

