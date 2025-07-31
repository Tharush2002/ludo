#ifndef GUI_H
#define GUI_H

#include "types.h"
#include "raylib.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>

void init_gui(void);
void cleanup_gui(void);
void render_game(Piece (*pieces)[NUM_PIECES]);
Texture2D get_texture(Colour colour);
Texture2D get_dice(int value);
int should_close_window(void);

#endif

