#ifndef TYPES_H_
#define TYPES_H_
#include <SDL.h>

typedef struct animations{
	unsigned short int angle;
	Uint32 timer[5];
	SDL_Point center;
	SDL_Rect animationRect;
}animation;

typedef struct items{
	int ID;
	int DMG;
	animation animation;
	unsigned int recharge;
	SDL_Rect rectangle;
	SDL_Texture *texture;
}item;

typedef struct objects{
	int HP;
	int DMG;
	short int LVL;
	int ID;
	int XP;
	float movespeed;
	char direction;
	char restofway;
	float pxpart;
	int pxcount;
	int takendamage;
	unsigned short int attackrecharge;
	char relation;
	item weapon;
	animation animation;
	SDL_Rect damageEffectRect;
	SDL_Texture *damageEffectTexture;
	SDL_Rect rectangle;
	SDL_Texture *texture, *death;
}object;

typedef struct element{
	object data;
    struct element *next, *previous, *head, *tail;
}container;


#endif /* TYPES_H_ */
