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

int digitCount(int number);

int limitedRandom(int bot_edge, int top_edge, int extravar);

void spawn(Object object, Container **headcontainer, SDL_Rect bgrect, int x, int y);

void itemSpawn(Item item, Container **headcontainer, SDL_Rect bgrect, int x, int y);

void randSpawn(Object object, Container **headcontainer, SDL_Rect bgrect, int extravar);

void multiSpawn(Container **headcontainer, Object object, SDL_Rect bgrect, int number);

SDL_Texture *newText(char *text, int red, int green, int blue);

int *calculateTrafficBans(Object entity, Container **headcontainer);

int calculateChasing(int *unmoving, Object entity, Container **headcontainer);

int calculateEntityMoving(Object entity, Container **headcontainer, int randvar);

Object entityMoving(Object entity, Container **headcontainer, int randvar);

Object playerMoving(Object prect, int *trafficbans, const Uint8 *keyboard_state);

Container *attack(int attacker_number, Container **headcontainer);

Container *loadMap(Container **headcontainer, SDL_Rect background_rect, char *path);

void takeWeapon(int number, Container **headcontainer);

void lvlUp(int number, Container **headcontainer);

void attackAnimation(Object *attacker, SDL_RendererFlip flip);

void switchLayers();

void pauseMenu();

void game();


#endif /* MAIN_FUNCTIONS_H_ */
