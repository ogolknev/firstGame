#include "includes.h"


int initSDL(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("init error: %s\n", SDL_GetError());
		return 1;
	}
	if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) < 0){
		printf("init error: %s\n", SDL_GetError());
		return 1;
	}
	if(TTF_Init() != 0){
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


void randSpawn(struct object object, container **headcontainer, SDL_Rect bgrect, int extra){
	container *extcontainer = *headcontainer;
	object.rectangle.x = bgrect.x + limitedrandom(1, 19, extra*752) * 32;
	object.rectangle.y = bgrect.y + (limitedrandom(1, 19, extra * extra * 257257)) * 32;
	object.ID = element_count(&extcontainer);
	addlast(&extcontainer, object);
	extcontainer = *headcontainer;
}


void multiSpawn(SDL_Renderer *render, container **headcontainer, struct object object, SDL_Rect bgrect, int number){
	container *extcontainer = *headcontainer;
	for(int i = 0; i < number; i++){
		randSpawn(object, &extcontainer, bgrect, i + 1);
	}
	extcontainer = *headcontainer;
}


SDL_Texture *newtext(char *text, SDL_Renderer *render, char *pathfontfile, int red, int green, int blue, int fontsize){
	SDL_Colour colour = {255, blue, green, red};
	TTF_Font *font = TTF_OpenFont(pathfontfile, fontsize);
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, colour);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);
	return texture;
}


int *calculateTrafficBans(struct object entity, container **headcontainer){
	container *extcontainer = *headcontainer;
	int *unmoving = calloc(4,sizeof(int));
	for(int i = 0; i < element_count(&extcontainer); i++){
		if(abs(entity.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x) <= 32
		&& abs(entity.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y) <= 32
		&& getlist(&extcontainer, i)->data.LVL != -1){
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
			if(getlist(&extcontainer, i)->data.direction != -1 && entity.ID != -1){
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
	return unmoving;
}


int calculateEntityMoving(struct object entity, container **headcontainer, int randvar){
	container *extcontainer = *headcontainer;
	int moving = 0;
	int counter = 0;
	int *unmoving = calculateTrafficBans(entity, &extcontainer);
	if(entity.direction == -1 || entity.LVL == -1){
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
		moving = unmoving[limitedrandom(0,counter + 1, time(NULL) * randvar+counter)];
		return moving;
	}
}


struct object entityMoving(struct object entity, container **headcontainer, int randvar){
	container *extcontainer = *headcontainer;
	if(entity.direction == 0 && entity.ID != -1){
		entity.direction = calculateEntityMoving(entity, &extcontainer, randvar);
		if(entity.direction != 0) entity.restofway = cellsize;
	}
	else if(entity.direction == 1){
		entity.restofway--;
		entity.rectangle.y--;
	}
	else if(entity.direction == 2){
		entity.restofway--;
		entity.rectangle.x++;
	}
	else if(entity.direction == 3){
		entity.restofway--;
		entity.rectangle.y++;
	}
	else if(entity.direction == 4){
		entity.restofway--;
		entity.rectangle.x--;
	}
	if(entity.restofway == 0 && entity.direction != -1){
		entity.direction = 0;
	}
	return entity;
}


struct object playerMoving(struct object prect, int *trafficbans, const Uint8 *keyboardState){
	if((keyboardState[SDL_SCANCODE_UP])||(keyboardState[SDL_SCANCODE_W]))
		if(prect.direction == 0 && trafficbans[0] == 0){
			prect.direction = 1;
			prect.restofway = cellsize;
		}

	if((keyboardState[SDL_SCANCODE_DOWN])||(keyboardState[SDL_SCANCODE_S]))
		if(prect.direction == 0 && trafficbans[2] == 0){
			prect.direction = 3;
			prect.restofway = cellsize;
		}

	if((keyboardState[SDL_SCANCODE_LEFT])||(keyboardState[SDL_SCANCODE_A]))
		if(prect.direction == 0 && trafficbans[3] == 0){
			prect.direction = 4;
			prect.restofway = cellsize;
		}

	if((keyboardState[SDL_SCANCODE_RIGHT])||(keyboardState[SDL_SCANCODE_D]))
		if(prect.direction == 0 && trafficbans[1] == 0){
			prect.direction = 2;
			prect.restofway = cellsize;
		}
	return prect;
}


container *attack(int attackernumber, container **headcontainer){
	container *extcontainer = *headcontainer;
	struct object attacker = getlist(&extcontainer, attackernumber)->data;
	if(getlist(&extcontainer, attackernumber)->data.attackrecharge == 0 && getlist(&extcontainer, attackernumber)->data.LVL != -1){
		for(int i = 0; i < element_count(&extcontainer); i++){
			if(abs(attacker.rectangle.x - getlist(&extcontainer, i)->data.rectangle.x) <= 32
			&& abs(attacker.rectangle.y - getlist(&extcontainer, i)->data.rectangle.y) <= 32
			&& (attacker.ID != getlist(&extcontainer, i)->data.ID) && getlist(&extcontainer, i)->data.HP > 0){
				getlist(&extcontainer, i)->data.HP -= attacker.DMG + attacker.weapon.DMG;
				getlist(&extcontainer, i)->data.takendamage = attacker.DMG + attacker.weapon.DMG;
				getlist(&extcontainer, attackernumber)->data.weapon.animation.angle = 0;
				getlist(&extcontainer, i)->data.animation.timer[0] = 60;
				getlist(&extcontainer, i)->data.animation.timer[1] = 0;
				getlist(&extcontainer, attackernumber)->data.attackrecharge = getlist(&extcontainer, attackernumber)->data.weapon.recharge;
				getlist(&extcontainer, i)->data.damageEffectRect.x = getlist(&extcontainer, i)->data.rectangle.x;
				getlist(&extcontainer, i)->data.damageEffectRect.y = getlist(&extcontainer, i)->data.rectangle.y;
				getlist(&extcontainer, i)->data.animation.animationRect.x = getlist(&extcontainer, i)->data.rectangle.x + cellsize/2;
				getlist(&extcontainer, i)->data.animation.animationRect.y = getlist(&extcontainer, i)->data.rectangle.y + cellsize/2;
				getlist(&extcontainer, i)->data.animation.animationRect.w = 10;
				getlist(&extcontainer, i)->data.animation.animationRect.h = 15;
				if(getlist(&extcontainer, i)->data.HP <= 0){
					getlist(&extcontainer, i)->data.animation.timer[2] = 700;
					getlist(&extcontainer, i)->data.LVL = -1;
					getlist(&extcontainer, i)->data.direction = -1;
					getlist(&extcontainer, i)->data.texture = getlist(&extcontainer, i)->data.death;
				}
			}
		}
		getlist(&extcontainer, attackernumber)->data.weapon.animation.angle = 0;
		getlist(&extcontainer, attackernumber)->data.attackrecharge = getlist(&extcontainer, attackernumber)->data.weapon.recharge;
	}
	return *headcontainer;
}


container *loadmap(container **headcontainer, SDL_Rect bgrect, char *path){
	container *extcontainer = *headcontainer;
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
			if(objectsymbol == 'x'){
				newobject.rectangle.x = bgrect.x + x * 32;
				newobject.rectangle.y = bgrect.y + y * 32;
				newobject.DMG = -1;
				newobject.HP = -1;
				newobject.LVL = 0;
				newobject.direction = -1;
				newobject.ID = element_count(&extcontainer);
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
	x++;
	fclose(mapinput);
	return extcontainer;
}


int attackanimation(struct object *attacker, SDL_RendererFlip flip, int angle){
	attacker->weapon.animation.angle = angle;
	attacker->weapon.animation.angle += 720/attacker->weapon.recharge;
	extraPoint = attacker->weapon.animation.center;
	extraRect = attacker->weapon.rectangle;
	extraRect.x = attacker->rectangle.x + 8;
	extraRect.y = attacker->rectangle.y + 16;
	SDL_RenderCopyEx(mainRender, attacker->weapon.texture, NULL,
				 	 &extraRect, attacker->weapon.animation.angle,
					 &extraPoint, flip);
	return attacker->weapon.animation.angle;
}


int main(int argc, char* argv[]){
	if(initSDL() == 1){
		return 0;
	}
	mainWindow = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
								  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
	char* damageIndicator = malloc(20*sizeof(char));

	SDL_Texture *bgTexture = IMG_LoadTexture(mainRender,"Textures/backgrounds/background_0.png");
	SDL_Rect bgrect;
	bgrect.h = 640;
	bgrect.w = 640;
	bgrect.x = (SCREEN_WIDTH - bgrect.w) / 2;
	bgrect.y = (SCREEN_HEIGHT - bgrect.h) / 2;

	SDL_Texture *pTexture = IMG_LoadTexture(mainRender,"Textures/helmet1.png");
	SDL_Rect prect;
	prect.h = cellsize;
	prect.w = cellsize;
	prect.x = cellsize * 10;
	prect.y = cellsize * 10;

	SDL_Texture *bloodTexture = IMG_LoadTexture(mainRender,"Textures/blood.png");
	SDL_Rect bloodrect;
	bloodrect.h = cellsize;
	bloodrect.w = cellsize;

	SDL_Texture *swordTexture = IMG_LoadTexture(mainRender, "Textures/sword.png");
	SDL_Rect swordrect;
	swordrect.h = 55;
	swordrect.w = cellsize;

	struct item initial_sword;
	initial_sword.ID = 0;
	initial_sword.DMG = 1;
	initial_sword.recharge = 55;
	initial_sword.texture = swordTexture;
	initial_sword.rectangle = swordrect;
	initial_sword.animation.center.x = cellsize / 2;
	initial_sword.animation.center.y = 0;
	initial_sword.animation.angle = 0;

	SDL_Texture *goblinStickTexture = IMG_LoadTexture(mainRender, "Textures/goblin_stick.png");;
	SDL_Rect goblinSickRect;
	goblinSickRect.h = cellsize;
	goblinSickRect.w = cellsize;

	struct item goblin_stick;
	goblin_stick.ID = 1;
	goblin_stick.DMG = 1;
	goblin_stick.recharge = 120;
	goblin_stick.texture = goblinStickTexture;
	goblin_stick.rectangle = goblinSickRect;
	goblin_stick.animation.center.x = cellsize / 2;
	goblin_stick.animation.center.y = 0;
	goblin_stick.animation.angle = 0;

	SDL_Texture *stanTexture = IMG_LoadTexture(mainRender,"Textures/stan.png");
	SDL_Rect stanrect;
	stanrect.h = cellsize;
	stanrect.w = cellsize;

	SDL_Texture *goblinTexture = IMG_LoadTexture(mainRender, "Textures/enemy.png");
	SDL_Texture *deathgoblin = IMG_LoadTexture(mainRender, "Textures/deadgoblin.png");
	SDL_Rect enemyrect;
	enemyrect.h = cellsize;
	enemyrect.w = cellsize;

	objects = newcontainer();
	SDL_RendererFlip swordflip = SDL_FLIP_VERTICAL;

	struct object player;
	player.LVL = 0;
	player.HP = 15;
	player.DMG = 2;
	player.ID = -1;
	player.direction = 0;
	player.attackrecharge = 100;
	player.restofway = 0;
	player.takendamage = 0;
	player.damageEffectTexture = bloodTexture;
	player.damageEffectRect = bloodrect;
	player.rectangle = prect;
	player.texture = pTexture;
	player.weapon = initial_sword;
	player.weapon.animation.angle = 360;


	addtolist(&objects, player, 0);


	struct object goblin;
	goblin.HP = 5;
	goblin.LVL = 0;
	goblin.DMG = 0;
	goblin.attackrecharge = 100;
	goblin.direction = 0;
	goblin.restofway = 0;
	goblin.takendamage = 0;
	goblin.rectangle = enemyrect;
	goblin.texture = goblinTexture;
	goblin.weapon = goblin_stick;
	goblin.damageEffectTexture = bloodTexture;
	goblin.damageEffectRect = bloodrect;
	goblin.death = deathgoblin;
	goblin.weapon.animation.angle = 360;


	struct object stan;
	stan.HP = -1;
	stan.LVL = 0;
	stan.DMG = -1;
	stan.direction = -1;
	stan.restofway = 0;
	stan.takendamage = 0;
	stan.rectangle = stanrect;
	stan.texture = stanTexture;
	stan.animation.timer[0] = 0;

	struct object extraobject;


	objects = loadmap(&objects, bgrect, "maps/map1.txt");
	multiSpawn(mainRender, &objects, goblin, bgrect, 20);
	multiSpawn(mainRender, &objects, stan, bgrect, 15);
	printf("%i\n", element_count(&objects));

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	SDL_SetRenderDrawColor(mainRender, 0, 0 ,0 ,0);

	while(run == 1 && mainEvent->type != SDL_QUIT){
		SDL_PollEvent(mainEvent);
		SDL_PumpEvents();
		SDL_RenderClear(mainRender);
		SDL_RenderCopy(mainRender, bgTexture, NULL, &bgrect);


		//rendering unalive
		for(int i = 0; i < element_count(&objects) ; i++){
			SDL_Rect currentRect = getlistdata(&objects, i).rectangle;
			if(getlist(&objects, i)->data.LVL == -1)SDL_RenderCopy(mainRender, getlistdata(&objects, i).texture, NULL, &currentRect);
		}


		//rendering alive
		for(int i = 0; i < element_count(&objects) ; i++){
			SDL_Rect currentRect = getlistdata(&objects, i).rectangle;
			if(getlist(&objects, i)->data.LVL != -1)SDL_RenderCopy(mainRender, getlistdata(&objects, i).texture, NULL, &currentRect);
		}


		//player attack
		if(keystate[SDL_SCANCODE_F] && getlist(&objects, 0)->data.attackrecharge == 0){
			objects = attack(0, &objects);
		}
		int *trafficbans = calculateTrafficBans(getlist(&objects, 0)->data, &objects);
		getlist(&objects, 0)->data = playerMoving(getlist(&objects, 0)->data, trafficbans, keystate);


		//action cycle
		for(int i = 0; i < element_count(&objects); i++){


			//entities moving
			getlist(&objects, i)->data = entityMoving(getlist(&objects, i)->data, &objects, i);


			//recharging attack
			if(getlist(&objects, i)->data.attackrecharge > 0) getlist(&objects, i)->data.attackrecharge--;


			//rendering effects
			if(getlist(&objects, i)->data.animation.timer[0] > 0 && getlist(&objects, i)->data.takendamage > 0){


				//damage effect
				getlist(&objects, i)->data.animation.timer[0]--;
				extraRect = getlist(&objects, i)->data.damageEffectRect;
				SDL_RenderCopy(mainRender, getlist(&objects, i)->data.damageEffectTexture, NULL, &extraRect);


				//damage indicator
				if(getlist(&objects, i)->data.takendamage > 0){
					itoa(getlist(&objects, i)->data.takendamage, damageIndicator, 10);
					getlist(&objects, i)->data.animation.timer[1]++;
					getlist(&objects, i)->data.animation.animationRect.y --;
					extraRect = getlist(&objects, i)->data.animation.animationRect;
					SDL_RenderCopy(mainRender, newtext(damageIndicator, mainRender, "fonts/bauhaus.ttf", 255, 255, 255, 100), NULL, &extraRect);
					if(getlist(&objects, i)->data.animation.timer[1] >= 50) getlist(&objects, i)->data.takendamage = 0;
				}
			}


			//attacks of entities
			if(getlist(&objects, i)->data.DMG != -1){
				if(abs(getlist(&objects, 0)->data.rectangle.x - getlist(&objects, i)->data.rectangle.x) <= 32
				&& abs(getlist(&objects, 0)->data.rectangle.y - getlist(&objects, i)->data.rectangle.y) <= 32
				&& getlist(&objects, 0)->data.ID == -1 && i != 0 && limitedrandom(0,2,i))
				{
					objects = attack(i, &objects);
				}
			}

			//attack animation
			if(getlist(&objects, i)->data.weapon.animation.angle < 360 && getlist(&objects, i)->data.attackrecharge > 0){
				extraobject = getlist(&objects, i)->data;
				getlist(&objects, i)->data.weapon.animation.angle
				= attackanimation(&extraobject, swordflip, getlist(&objects, i)->data.weapon.animation.angle);
			}


			//removal of corpses
			if(getlist(&objects, i)->data.animation.timer[2] > 0) getlist(&objects, i)->data.animation.timer[2]--;
			if(getlist(&objects, i)->data.animation.timer[2] == 0 && getlist(&objects, i)->data.LVL == -1) delelement(&objects, i);
		}


		SDL_RenderPresent(mainRender);
		SDL_Delay(13);
	}
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}
