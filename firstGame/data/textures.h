
#ifndef TEXTURES_H_
#define TEXTURES_H_
#include <SDL.h>
#include <SDL_image.h>
#include "variables.h"

void load_textures();


//background
SDL_Texture *backgroundTexture;
SDL_Rect backgroundRect;


//unalive
SDL_Rect item_Rct;

SDL_Texture *stan0_Txtr;
SDL_Rect stan0_Rct;

SDL_Texture *barrel0_Txtr;
SDL_Rect barrel0_Rct;


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

SDL_Texture *weapon257_Txtr;
SDL_Rect weapon257_Rct;


#endif /* TEXTURES_H_ */
