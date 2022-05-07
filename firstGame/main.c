#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "containers.h"
#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
int run = 1;
int attackrecharge = 0;
int angle = 0;
int dmgchek = 0;
SDL_Window *mainWindow = NULL;
SDL_Renderer *mainRender = NULL;
SDL_Event *mainEvent;
container* objects;

int initSDL(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("init error: %s\n", SDL_GetError());
		return 1;
	}
	else return 0;
}

int limitedrandom(int botEdge, int topEdge, int extra){
	int ttime = time(NULL);
	srand(ttime + extra);
	return botEdge + (rand() % (topEdge - botEdge));
}

void randSpawn(SDL_Rect *objrect, SDL_Rect bgrect, int extra){
	objrect->x = bgrect.x + limitedrandom(0, 20, extra*752) * 32;
	objrect->y = bgrect.y + (limitedrandom(0, 20, extra * extra * 257257)) * 32;
}

void multiSpawn(SDL_Renderer *render, container **headcontainer, struct object object, SDL_Rect bgrect, int number){
	SDL_Rect rectangle = object.rectangle;
	container *extcontainer = *headcontainer;
	for(int i = 0; i < number; i++){
		randSpawn(&rectangle, bgrect, i + 1);
		object.rectangle = rectangle;
		addlast(&extcontainer, object);
	}
	extcontainer = *headcontainer;
}

int calculateEntityMoving(struct object entity, container **headcontainer, int randvar){
	container *extcontainer = *headcontainer;
	int moving = 0;
	int counter = 0;
	int unmoving[4] = {0, 0, 0, 0};
	for(int i = 0; i < element_count(&extcontainer); i++){
		if(abs(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x) <= 32 && abs(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y) <= 32){
			if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == 32){
				if(entity.rectangle.y == getlist(&extcontainer, i)->data.rectangle.y){
					unmoving[3] = 4;
				}
			}
			if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == -32){
				if(entity.rectangle.y == getlist(&extcontainer, i)->data.rectangle.y){
					unmoving[1] = 2;
				}
			}
			if(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == 32){
				if(entity.rectangle.x == getlist(&extcontainer, i)->data.rectangle.x){
					unmoving[0] = 1;
				}
			}
			if(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == -32){
				if(entity.rectangle.x == getlist(&extcontainer, i)->data.rectangle.x){
					unmoving[2] = 3;
				}
			}
			if(getlist(&extcontainer, i)->data.moving != -1){
				if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == -32
				&& entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == -32){
					unmoving[1] = 2;
					unmoving[2] = 3;
				}
				if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == 32
				&& entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == 32){
					unmoving[0] = 1;
					unmoving[3] = 4;
				}
				if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == 32
				&& entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == -32){
					unmoving[3] = 4;
					unmoving[2] = 3;
				}
				if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == -32
				&& entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == 32){
					unmoving[1] = 1;
					unmoving[2] = 2;
			}
			}
		}
	}
	if(entity.moving == -1){
		return -1;
	}
	else if((unmoving[0] == 1 && unmoving[1] == 2 && unmoving[2] == 3 && unmoving[3] == 4)){
		return 0;
	}
	else{
		for(int i = 0; i < 4; i++){
			if(unmoving[i] == 0){
				unmoving[0] = 0;
				unmoving[counter + 1] = i + 1;
				counter++;
			}
		}
		moving = unmoving[limitedrandom(0,counter + 1, randvar)];
		return moving;
	}
}

int *calculateTrafficBans(struct object entity, container **headcontainer){
	container *extcontainer = *headcontainer;
	int *unmoving = malloc(4*sizeof(int));
	unmoving[0] = 0;
	unmoving[1] = 0;
	unmoving[2] = 0;
	unmoving[3] = 0;
	entity.rectangle.x += 8;
	entity.rectangle.y += 8;
	for(int i = 0; i < element_count(&extcontainer); i++){
		if(abs(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x) <= 32
		&& abs(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y) <= 32){
			if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == 32){
				if(entity.rectangle.y == getlist(&extcontainer, i)->data.rectangle.y){
					unmoving[3] = 4;
				}
			}
			if(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x == -32){
				if(entity.rectangle.y == getlist(&extcontainer, i)->data.rectangle.y){
					unmoving[1] = 2;
				}
			}
			if(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == 32){
				if(entity.rectangle.x == getlist(&extcontainer, i)->data.rectangle.x){
					unmoving[0] = 1;
				}
			}
			if(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y == -32){
				if(entity.rectangle.x == getlist(&extcontainer, i)->data.rectangle.x){
					unmoving[2] = 3;
				}
			}
		}
	}
	return unmoving;
}

struct object entityMoving(struct object entity, container **headcontainer, int randvar){
	container *extcontainer = *headcontainer;
	if(entity.moving == 0 && entity.playerchek == 0){
		entity.moving = calculateEntityMoving(entity, &extcontainer, randvar);
	}
	else if(entity.moving == 1){
		entity.movingchek++;
		entity.rectangle.y--;
	}
	else if(entity.moving == 2){
		entity.movingchek++;
		entity.rectangle.x++;
	}
	else if(entity.moving == 3){
		entity.movingchek++;
		entity.rectangle.y++;
	}
	else if(entity.moving == 4){
		entity.movingchek++;
		entity.rectangle.x--;
	}
	if(entity.movingchek == 32){
		entity.movingchek = 0;
		entity.moving = 0;
	}
	return entity;
}

struct object playerMoving(struct object prect, int *trafficbans, const Uint8 *keyboardState){
	if((keyboardState[SDL_SCANCODE_UP])||(keyboardState[SDL_SCANCODE_W]))
		if(prect.moving == 0 && trafficbans[0] == 0) prect.moving = 1;

	if((keyboardState[SDL_SCANCODE_DOWN])||(keyboardState[SDL_SCANCODE_S]))
		if(prect.moving == 0 && trafficbans[2] == 0) prect.moving = 3;

	if((keyboardState[SDL_SCANCODE_LEFT])||(keyboardState[SDL_SCANCODE_A]))
		if(prect.moving == 0 && trafficbans[3] == 0) prect.moving = 4;

	if((keyboardState[SDL_SCANCODE_RIGHT])||(keyboardState[SDL_SCANCODE_D]))
		if(prect.moving == 0 && trafficbans[1] == 0) prect.moving = 2;
	return prect;
}

container *attack(struct object attacker, container **headcontainer, SDL_Texture *effecttexture, SDL_Rect *effectrect){
	container *extcontainer = *headcontainer;
	int deathcounter = 0;
	int counter = 0;
	for(int i = 0; i < element_count(&extcontainer); i++){
		if(abs(attacker.rectangle.x + 8 - getlist(&extcontainer, i)->data.rectangle.x) <= 32
		&& abs(attacker.rectangle.y + 8 - getlist(&extcontainer, i)->data.rectangle.y) <= 32
		&& getlist(&extcontainer, i)->data.playerchek != 1 && getlist(&extcontainer, i)->data.LVL != -1){
			getlist(&extcontainer, i)->data.HP -= attacker.DMG;
			dmgchek = 1;
			effectrect->x = getlist(&extcontainer, i)->data.rectangle.x;
			effectrect->y = getlist(&extcontainer, i)->data.rectangle.y;
			SDL_RenderCopy(mainRender, effecttexture, NULL, effectrect);
			if(getlist(&extcontainer, i)->data.HP <= 0){
				deathcounter++;
			}
		}
		while(deathcounter != 0){
			if(getlist(&extcontainer, counter)->data.HP <= 0 && getlist(&extcontainer, counter)->data.LVL != -1){
				delelement(&extcontainer, counter);
				deathcounter--;
			}
			else{
				counter++;
			}
		}
	}
	return *headcontainer;
}

container *loadmap(container **headcontainer, SDL_Rect bgrect, char *path){
	container *extcontainer = *headcontainer;
	printf("%s\n", path);
	struct object newobject;
	SDL_Texture *stTexture = IMG_LoadTexture(mainRender,"Textures/stan.png");
	newobject.rectangle.h = 32;
	newobject.rectangle.w = 32;
	FILE *mapinput;
	mapinput = fopen(path, "r");
	char objectsymbol;
	int x = 0;
	int y = 0;
	fscanf(mapinput, "%c", &objectsymbol);
	while(feof(mapinput) == 0){
		while(objectsymbol != '\\'){
			printf("s = %c ", objectsymbol);
			printf("x:%i y:%i\n", x, y);
			if(objectsymbol == 'x'){
				newobject.rectangle.x = bgrect.x + x * 32;
				newobject.rectangle.y = bgrect.y + y * 32;
				newobject.DMG = 0;
				newobject.HP = -1;
				newobject.LVL = -1;
				newobject.moving = -1;
				newobject.movingchek = 0;
				newobject.playerchek = 0;
				newobject.texture = stTexture;
				addlast(&extcontainer, newobject);
			}
			x++;
			fscanf(mapinput, "%c", &objectsymbol);
		}
		y++;
		x = -1;
		fscanf(mapinput, "%c", &objectsymbol);
	}
	printf("s = %c ", objectsymbol);
	printf("x:%i y:%i\n", x, y);
	x++;
	fclose(mapinput);
	return extcontainer;
}

int main(int argc, char* argv[]){
	if(initSDL() == 1){
		return 0;
	}
	mainWindow = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(mainWindow == NULL){
		printf("SDL could not create window! SDL error: %s\n", SDL_GetError());
		return 1;
	}
	mainRender = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(mainRender == NULL){
		printf("SDL could not create render! SDL error: %s\n", SDL_GetError());
		return 1;
	}
	mainEvent = malloc(sizeof(SDL_Event));

	SDL_Texture *bgTexture = IMG_LoadTexture(mainRender,"Textures/backgrounds/background_0.png");
	SDL_Rect bgrect;
	bgrect.h = 640;
	bgrect.w = 640;
	bgrect.x = (SCREEN_WIDTH - bgrect.w) / 2;
	bgrect.y = (SCREEN_HEIGHT - bgrect.h) / 2;

	SDL_Texture *pTexture = IMG_LoadTexture(mainRender,"Textures/helmet20.png");
	SDL_Rect prect;
	prect.h = 48;
	prect.w = 48;
	prect.x = 32 * 10 - 8;
	prect.y = 32 * 10 - 8;

	SDL_Texture *bloodEffect = IMG_LoadTexture(mainRender,"Textures/blood.png");
	SDL_Rect bldrect;
	bldrect.h = 32;
	bldrect.w = 32;

	SDL_Texture *sTexture = IMG_LoadTexture(mainRender, "Textures/sword.png");
	SDL_Rect srect;
	srect.h = 55;
	srect.w = 32;
	SDL_Point swordCenter;
	swordCenter.x = srect.w / 2;
	swordCenter.y = 0;

	SDL_Texture *stTexture = IMG_LoadTexture(mainRender,"Textures/stan.png");
	SDL_Rect strect;
	strect.h = 32;
	strect.w = 32;

	SDL_Texture *enTexture = IMG_LoadTexture(mainRender, "Textures/enemy.png");
	SDL_Rect enrect;
	enrect.h = 32;
	enrect.w = 32;
	randSpawn(&enrect, bgrect, -1);

	objects = newcontainer();
	SDL_RendererFlip swordflip = SDL_FLIP_VERTICAL;

	struct object player;
	player.HP = 3;
	player.LVL = 0;
	player.DMG = 3;
	player.moving = 0;
	player.movingchek = 0;
	player.playerchek = 1;
	player.rectangle = prect;
	player.texture = pTexture;

	addtolist(&objects, player, 0);

	struct object enemy;
	enemy.HP = 2;
	enemy.LVL = 0;
	enemy.DMG = 1;
	enemy.moving = 0;
	enemy.movingchek = 0;
	enemy.playerchek = 0;
	enemy.rectangle = enrect;
	enemy.texture = enTexture;

	struct object stan;
	stan.HP = -1;
	stan.LVL = -1;
	stan.DMG = 0;
	stan.moving = -1;
	stan.movingchek = 0;
	stan.playerchek = 0;
	stan.rectangle = strect;
	stan.texture = stTexture;

	addlast(&objects, enemy);

	objects = loadmap(&objects, bgrect, "maps/map1.txt");
	multiSpawn(mainRender, &objects, enemy, bgrect, 40);
	multiSpawn(mainRender, &objects, stan, bgrect, 0);
	printf("%i\n", element_count(&objects));

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	while(run == 1 && mainEvent->type != SDL_QUIT){
		SDL_PollEvent(mainEvent);
		SDL_PumpEvents();
		SDL_SetRenderDrawColor(mainRender, 0, 0 ,0 ,0);
		SDL_RenderClear(mainRender);
		SDL_RenderCopy(mainRender, bgTexture, NULL, &bgrect);
		if(keystate[SDL_SCANCODE_F] && attackrecharge == 0){
			angle = 0;
			objects = attack(getlist(&objects, 0)->data, &objects, bloodEffect, &bldrect);
			attackrecharge = 36;
		}
		if(attackrecharge > 0){
			if(angle < 360){
				angle += 10;
				srect.x = getlist(&objects, 0)->data.rectangle.x + (getlist(&objects, 0)->data.rectangle.w / 10);
				srect.y = getlist(&objects, 0)->data.rectangle.y + (getlist(&objects, 0)->data.rectangle.h / 2);
				SDL_RenderCopyEx(mainRender, sTexture, NULL, &srect , angle, &swordCenter, swordflip);
			}
			if(angle >= 360) attackrecharge = 0;
		}
		if(angle > 180) dmgchek = 0;
		if(dmgchek == 1) SDL_RenderCopy(mainRender, bloodEffect, NULL, &bldrect);
		for(int i = 0; i < element_count(&objects); i++){
			SDL_Rect currentRect = getlistdata(&objects, i).rectangle;
			SDL_RenderCopy(mainRender, getlistdata(&objects, i).texture, NULL, &currentRect);
		}

		int *trafficbans = calculateTrafficBans(getlist(&objects, 0)->data, &objects);
		getlist(&objects, 0)->data = playerMoving(getlist(&objects, 0)->data, trafficbans, keystate);
		for(int i = 0; i < element_count(&objects); i++){
			getlist(&objects, i)->data = entityMoving(getlist(&objects, i)->data, &objects, i);
		}


		SDL_RenderPresent(mainRender);
		SDL_Delay(15);
	}
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}
