#ifndef MAIN_FUNCTIONS_H_
#define MAIN_FUNCTIONS_H_
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <math.h>
#include "types.h"
#include "variables.h"
#include "containers.h"


int initSDL();

int digit_count(int number);

int limitedrandom(int botEdge, int topEdge, int extra);

void randSpawn(object object, container **headcontainer, SDL_Rect bgrect, int extra);

void multiSpawn(SDL_Renderer *render, container **headcontainer, object object, SDL_Rect bgrect, int number);

SDL_Texture *newtext(char *text, SDL_Renderer *render, int red, int green, int blue);

int *calculateTrafficBans(object entity, container **headcontainer);

int calculatechasing(int *unmoving, object entity, container **headcontainer);

int calculateEntityMoving(object entity, container **headcontainer, int randvar);

object entityMoving(object entity, container **headcontainer, int randvar);

object playerMoving(object prect, int *trafficbans, const Uint8 *keyboardState);

container *attack(int attackernumber, container **headcontainer);

container *loadmap(container **headcontainer, SDL_Rect bgrect, char *path);

void attackanimation(object *attacker, SDL_RendererFlip flip);

void maingame();


#endif /* MAIN_FUNCTIONS_H_ */
