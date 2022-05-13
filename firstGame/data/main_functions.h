#ifndef MAIN_FUNCTIONS_H_
#define MAIN_FUNCTIONS_H_
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_mixer.h>
#include <math.h>
#include "types.h"
#include "variables.h"
#include "containers.h"
#include "objects.h"
#include "sounds.h"


int initSDL();

int digit_count(int number);

int limitedrandom(int botEdge, int topEdge, int extra);

void spawn(object object, container **headcontainer, SDL_Rect bgrect, int x, int y);

void item_spawn(item item, container **headcontainer, SDL_Rect bgrect, int x, int y);

void randSpawn(object object, container **headcontainer, SDL_Rect bgrect, int extra);

void multiSpawn(container **headcontainer, object object, SDL_Rect bgrect, int number);

SDL_Texture *newtext(char *text, SDL_Renderer *render, int red, int green, int blue);

int *calculateTrafficBans(object entity, container **headcontainer);

int calculatechasing(int *unmoving, object entity, container **headcontainer);

int calculateEntityMoving(object entity, container **headcontainer, int randvar);

object entityMoving(object entity, container **headcontainer, int randvar);

object playerMoving(object prect, int *trafficbans, const Uint8 *keyboardState);

container *attack(int attackernumber, container **headcontainer);

container *loadmap(container **headcontainer, SDL_Rect bgrect, char *path);

void take_weapon(int number, container **headcontainer);

void LVLup(int number, container **headcontainer);

void attackanimation(object *attacker, SDL_RendererFlip flip);

void switch_layers();

void mainmenu();

void maingame();


#endif /* MAIN_FUNCTIONS_H_ */
