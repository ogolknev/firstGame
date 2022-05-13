#ifndef VARIABLES_H_
#define VARIABLES_H_
#include "types.h"
#include <SDL_ttf.h>
#include <stdio.h>

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;
const int cellsize;
int run;
char layer;
int mouse_x, mouse_y, *unmoving;
Uint64 current_time;

SDL_Window *main_window;
SDL_Renderer *main_render;
SDL_Event *main_event;
TTF_Font *main_font;
SDL_RendererFlip sword_flip;


const Uint8 *key_state;
Uint32 mouse_state;


Container *objects;

#endif /* VARIABLES_H_ */
