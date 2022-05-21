#ifndef TYPES_H_
#define TYPES_H_
#include <SDL.h>
#include <SDL_mixer.h>

typedef struct Animations{
	unsigned short int angle;
	Uint64 timer[5];
	SDL_Point center;
	SDL_Rect animationRect;
}Animation;

typedef struct Items{
	int ID;
	int DMG;
	Animation animation;
	Mix_Chunk *impact_sound;
	float recharge;
	int using;
	float attackdelay;
	SDL_Rect rectangle;
	SDL_Texture *texture;
}Item;

typedef struct Objects{
	int HP;
	int DMG;
	int LVL;
	int object_ID;
	int ID;
	int XP;
	float movespeed;
	int direction;
	int restofway;
	float pxpart;
	int pxcount;
	int takendamage;
	Uint64 attackrecharge;
	int relation;
	Item weapon;
	Animation animation;
	SDL_Rect damageEffectRect;
	SDL_Texture *damageEffectTexture;
	SDL_Rect rectangle;
	SDL_Texture *texture, *death;
}Object;

typedef struct Element{
	Object data;
    struct Element *next, *previous, *head, *tail;
}Container;


typedef struct SettingsConf{
	int sound;
	int resolution;
	int fullscreen;
}Settings;

#endif /* TYPES_H_ */
