#ifndef VARIABLES_H_
#define VARIABLES_H_
#include "types.h"
#include <SDL_ttf.h>
#include <stdio.h>

const int SCREEN_WIDTH_1;
const int SCREEN_HEIGHT_1;
const int SCREEN_WIDTH_2;
const int SCREEN_HEIGHT_2;
int screen_height, screen_width;
int full_screen;
int volume;
int soundof;
int cellsize;
int run;
int click_chek;
int render_sequence;
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

Settings *SettingsConf;
Container *objects;

#endif /* VARIABLES_H_ */
