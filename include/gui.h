#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include "types.h"

void init_gui(void);
void cleanup_gui(void);
void render_game(const Piece *piece);
int should_close_window(void);

#endif

