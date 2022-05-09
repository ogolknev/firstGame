#ifndef VARIABLES_H_
#define VARIABLES_H_
#include "types.h"
#include <SDL_ttf.h>
#include <stdio.h>

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;
const int cellsize;
int run;
int i, j, extravar, extravar2, *unmoving;
char extraSymbol;

SDL_Window *mainWindow;
SDL_Renderer *mainRender;
SDL_Event *mainEvent;
SDL_Rect extraRect;
SDL_Point extraPoint;
SDL_Texture *extraTexture, *extraTexture2;
SDL_Surface *extraSurface;
SDL_Colour extraColour;
TTF_Font *mainFont;

object extraObject;

FILE *extraStream;

#endif /* VARIABLES_H_ */
