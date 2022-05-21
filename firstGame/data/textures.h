
#ifndef TEXTURES_H_
#define TEXTURES_H_
#include <SDL.h>
#include <SDL_image.h>
#include "items.h"
#include "containers.h"
#include "variables.h"

Container * loadTextures();

void initTextures();

Container *textures_list;
Object txtr_object;

//interface
SDL_Texture *button512_txtr;
SDL_Rect button512_rct;
SDL_Rect button512_state;

//background
SDL_Texture *background_txtr;
SDL_Rect background_rct;


//unalive
SDL_Rect item_Rct;

SDL_Texture *stan0_Txtr;
SDL_Rect stan0_Rct;

SDL_Texture *barrel0_Txtr;
SDL_Texture *barrel0_death;
SDL_Rect barrel0_Rct;

SDL_Texture *bush0_txtr;
SDL_Rect bush0_rct;

SDL_Texture *bush1_txtr;
SDL_Rect bush1_rct;

SDL_Texture *bush2_txtr;
SDL_Rect bush2_rct;

SDL_Texture *bush3_txtr;
SDL_Rect bush3_rct;


//entities
SDL_Texture *playerTexture;
SDL_Rect playerRect;

SDL_Texture *goblinTexture;
SDL_Texture *goblinDeath;
SDL_Rect goblinRect;

SDL_Texture *alienTexture;
SDL_Rect alienRect;


//effects
SDL_Texture *bloodTexture;
SDL_Rect bloodRect;


//weapons
SDL_Texture *kick_Txtr;
SDL_Rect hand_Rct;

SDL_Texture *weapon0_Txtr;
SDL_Rect weapon0_Rct;

SDL_Texture *weapon1_Txtr;
SDL_Rect weapon1_Rct;

SDL_Texture *weapon2_Txtr;
SDL_Rect weapon2_Rct;

SDL_Texture *weapon3_txtr;
SDL_Rect weapon3_rct;

SDL_Texture *weapon4_txtr;
SDL_Rect weapon4_rct;

SDL_Texture *weapon257_Txtr;
SDL_Rect weapon257_Rct;


#endif /* TEXTURES_H_ */
