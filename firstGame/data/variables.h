#ifndef VARIABLES_H_
#define VARIABLES_H_
#include "types.h"
#include <SDL_ttf.h>
#include <stdio.h>

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;
const int cellsize;
int run;
int *trafficbans;
int i, j, extravar, extravar2, *unmoving;
Uint32 currenttime;
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
container *objects;
container *extraContainer;
container *extraContainer2, *extraContainer3, *addElement;
object extraObject2;
int counter, counter2, counter3;

FILE *extraStream;

#endif /* VARIABLES_H_ */
