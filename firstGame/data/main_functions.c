#include "main_functions.h"


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


int digitCount(int number){
	if(number > 0){
		return 1 + digitCount(number/10);
	}
	return 0;
}


int limitedRandom(int bot_edge, int top_edge, int extra){
	srand(time(NULL) + extra);
	return bot_edge + (rand() % (top_edge + 1 - bot_edge));
}


void spawn(Object object, Container **headcontainer, SDL_Rect backgroundrect, int x, int y){
	Container *extra_container = *headcontainer;
	object.rectangle.x = backgroundrect.x + x * cellsize;
	object.rectangle.y = backgroundrect.y + y * cellsize;
	object.object_ID = elementCount(&extra_container);
	addLast(&extra_container, object);
}


void itemSpawn(Item item, Container **headcontainer, SDL_Rect bgrect, int x, int y){
	Container *extra_container = *headcontainer;
		item_object.weapon = item;
		item_object.rectangle.h = item_object.weapon.rectangle.h;
		item_object.rectangle.w = item_object.weapon.rectangle.w;
		item_object.rectangle.x = bgrect.x + x * cellsize;
		item_object.rectangle.y = bgrect.y + y * cellsize;
		item_object.object_ID = elementCount(&extra_container);
		item_object.LVL = -2;
		item_object.texture = item_object.weapon.texture;
		addLast(&extra_container, item_object);
	}


void randSpawn(Object object, Container **headcontainer, SDL_Rect background_rect, int extra){
	Container *extra_container = *headcontainer;
	object.rectangle.x = background_rect.x + limitedRandom(2, 18, extra * elementCount(&extra_container)) * cellsize;
	object.rectangle.y = background_rect.y + limitedRandom(2, 18, extra * extra * 257257) * cellsize;
	object.object_ID = elementCount(&extra_container);
	addLast(&extra_container, object);
}


void multiSpawn(Container **headcontainer, Object object, SDL_Rect backgroundrect, int number){
	Container *extra_container = *headcontainer;
	for(int i = 0; i < number; i++){
		randSpawn(object, &extra_container, backgroundrect, i + 1);
	}
	extra_container = *headcontainer;
}


SDL_Texture *newText(char *text, int red, int green, int blue){
	SDL_Colour text_colour;
	text_colour.b = blue;
	text_colour.g = green;
	text_colour.r = red;
	SDL_Surface *text_surface = TTF_RenderText_Solid(main_font, text, text_colour);
	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(main_render, text_surface);
	SDL_FreeSurface(text_surface);
	return text_texture;
}


//moving
int *calculateTrafficBans(Object entity, Container **headcontainer){
	Container *pointer = *headcontainer;
	unmoving[0] = 0;
	unmoving[1] = 0;
	unmoving[2] = 0;
	unmoving[3] = 0;
	for(int i = 0; i < elementCount(&pointer); i++){
		if(abs(entity.rectangle.x - getList(&pointer, i)->data.rectangle.x) <= cellsize
		&& abs(entity.rectangle.y - getList(&pointer, i)->data.rectangle.y) <= cellsize
		&& getList(&pointer, i)->data.LVL != -1 && getList(&pointer, i)->data.LVL != -2 ){
			if(entity.rectangle.x - getList(&pointer, i)->data.rectangle.x == cellsize){
				if(entity.rectangle.y == getList(&pointer, i)->data.rectangle.y){
					unmoving[3] = 4;
				}
			}
			if(entity.rectangle.x - getList(&pointer, i)->data.rectangle.x == -cellsize){
				if(entity.rectangle.y == getList(&pointer, i)->data.rectangle.y){
					unmoving[1] = 2;
				}
			}
			if(entity.rectangle.y - getList(&pointer, i)->data.rectangle.y == cellsize){
				if(entity.rectangle.x == getList(&pointer, i)->data.rectangle.x){
					unmoving[0] = 1;
				}
			}
			if(entity.rectangle.y - getList(&pointer, i)->data.rectangle.y == -cellsize){
				if(entity.rectangle.x == getList(&pointer, i)->data.rectangle.x){
					unmoving[2] = 3;
				}
			}
		}
	}
	return unmoving;
}


int calculateChasing(int *unmoving, Object entity, Container **headcontainer){
	Container *extraContainer = *headcontainer;
	char derection = -1;
	for(int i = 0; i < elementCount(&extraContainer); i++){
		if(abs(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x) <= cellsize * 4
		&& abs(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y) <= cellsize * 4
		&& entity.relation == -1 && getList(&extraContainer, i)->data.relation == 1){
			derection = 0;
			if((abs(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x) <= cellsize
			&& entity.rectangle.y == getList(&extraContainer, i)->data.rectangle.y) ||
			(abs(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y) <= cellsize
			&& entity.rectangle.x == getList(&extraContainer, i)->data.rectangle.x)) derection = 0;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y == getList(&extraContainer, i)->data.rectangle.y
			&& unmoving[3] != 4) derection = 4;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y == getList(&extraContainer, i)->data.rectangle.y
			&& unmoving[1] != 2) derection = 2;
			else if(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& entity.rectangle.x == getList(&extraContainer, i)->data.rectangle.x
			&& unmoving[0] != 1) derection = 1;
			else if(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& entity.rectangle.x == getList(&extraContainer, i)->data.rectangle.x
			&& unmoving[2] != 3) derection = 3;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[1] != 2) derection = 2;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[2] != 3) derection = 3;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[0] != 1) derection = 1;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[3] != 4) derection = 4;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[3] != 4) derection = 4;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[2] != 3) derection = 3;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[0] != 1) derection = 1;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -cellsize * 4
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= cellsize * 4
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[1] != 2) derection = 2;
		}
	}
	return derection;
}


int calculateEntityMoving(Object entity_i, Container **head_container, int randvar){
	Container *pointer = *head_container;
	int counter = 0;
	int *unmoving = calculateTrafficBans(entity_i, &pointer);
	if(entity_i.direction == -1 || entity_i.LVL == -1){
		return -1;
	}
	else if((unmoving[0] == 1 && unmoving[1] == 2 && unmoving[2] == 3 && unmoving[3] == 4)){
		return 0;
	}
	else{
		if(calculateChasing(unmoving, entity_i, &pointer) == -1){
			for(int i = 0; i < 4; i++){
				if(unmoving[i] == 0){
					unmoving[0] = 0;
					unmoving[counter + 1] = i + 1;
					counter++;
				}
			}
			return unmoving[limitedRandom(0,counter, time(NULL) * randvar * entity_i.object_ID)];
		}
		else return calculateChasing(unmoving, entity_i, &pointer);
	}
}


Object entityMoving(Object entity_i, Container **headcontainer, int randvar){
	if(entity_i.direction == 0 && entity_i.ID != -1){
		entity_i.direction = calculateEntityMoving(entity_i, headcontainer, randvar);
		if(entity_i.direction != 0){
			entity_i.restofway = cellsize;
			entity_i.pxpart = 0;
			entity_i.animation.timer[3] = current_time;
		}
	}
	else if(entity_i.direction == 1){
		if((current_time - entity_i.animation.timer[3]) > 15){
			if(entity_i.pxpart + (entity_i.movespeed * cellsize/32) / 200 - (int)entity_i.pxpart >= 1 + (int)((entity_i.movespeed * cellsize/32) / 200)){
				entity_i.pxcount = 1;
				entity_i.pxpart -= (int)entity_i.pxpart;
			}
			entity_i.pxpart += (entity_i.movespeed * cellsize/32) / 200;
			entity_i.rectangle.y -= (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			entity_i.restofway -= (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			if(entity_i.restofway <= 0){
				entity_i.rectangle.y -= entity_i.restofway;
				entity_i.restofway = 0;
			}
			entity_i.pxcount = 0;
			entity_i.animation.timer[3] = current_time;
		}
	}
	else if(entity_i.direction == 2){
		if((current_time - entity_i.animation.timer[3]) > 15){
			if(entity_i.pxpart + (entity_i.movespeed * cellsize/32) / 200 - (int)entity_i.pxpart >= 1 + (int)((entity_i.movespeed * cellsize/32) / 200)){
				entity_i.pxcount = 1;
				entity_i.pxpart -= (int)entity_i.pxpart;
			}
			entity_i.pxpart += (entity_i.movespeed * cellsize/32) / 200;
			entity_i.rectangle.x += (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			entity_i.restofway -= (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			if(entity_i.restofway <= 0){
				entity_i.rectangle.x += entity_i.restofway;
				entity_i.restofway = 0;
			}
			entity_i.pxcount = 0;
			entity_i.animation.timer[3] = current_time;
		}
	}
	else if(entity_i.direction == 3){
		if((current_time - entity_i.animation.timer[3]) > 15){
			if(entity_i.pxpart + (entity_i.movespeed * cellsize/32) / 200 - (int)entity_i.pxpart >= 1 + (int)((entity_i.movespeed * cellsize/32) / 200)){
				entity_i.pxcount = 1;
				entity_i.pxpart -= (int)entity_i.pxpart;
			}
			entity_i.pxpart += (entity_i.movespeed * cellsize/32) / 200;
			entity_i.rectangle.y += (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			entity_i.restofway -= (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			if(entity_i.restofway <= 0){
				entity_i.rectangle.y += entity_i.restofway;
				entity_i.restofway = 0;
			}
			entity_i.pxcount = 0;
			entity_i.animation.timer[3] = current_time;
		}
	}
	else if(entity_i.direction == 4){
		if((current_time - entity_i.animation.timer[3]) > 15){
			if(entity_i.pxpart + (entity_i.movespeed * cellsize/32) / 200 - (int)entity_i.pxpart >= 1 + (int)((entity_i.movespeed * cellsize/32) / 200)){
				entity_i.pxcount = 1;
				entity_i.pxpart -= (int)entity_i.pxpart;
			}
			entity_i.pxpart += (entity_i.movespeed * cellsize/32) / 200;
			entity_i.rectangle.x -= (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			entity_i.restofway -= (int)((entity_i.movespeed * cellsize/32) / 200 + entity_i.pxcount);
			if(entity_i.restofway <= 0){
				entity_i.rectangle.x -= entity_i.restofway;
				entity_i.restofway = 0;
			}
			entity_i.pxcount = 0;
			entity_i.animation.timer[3] = current_time;
		}
	}
	if(entity_i.restofway == 0 && entity_i.direction != -1){
		entity_i.direction = 0;
		if((entity_i.rectangle.x - background_rct.x) % cellsize != 0){
			entity_i.rectangle.x = background_rct.x + (entity_i.rectangle.x - background_rct.x) / cellsize * cellsize;
		}
		if((entity_i.rectangle.y - background_rct.y) % cellsize != 0){
			entity_i.rectangle.y = background_rct.y + (entity_i.rectangle.y - background_rct.y) / cellsize * cellsize;
		}
	}
	return entity_i;
}


Object playerMoving(Object player, int *trafficbans, const Uint8 *keyboardState){
	if((keyboardState[SDL_SCANCODE_UP])||(keyboardState[SDL_SCANCODE_W]))
		if(player.direction == 0 && trafficbans[0] == 0){
			player.direction = 1;
			player.restofway = cellsize;
			player.animation.timer[3] = current_time;
		}

	if((keyboardState[SDL_SCANCODE_DOWN])||(keyboardState[SDL_SCANCODE_S]))
		if(player.direction == 0 && trafficbans[2] == 0){
			player.direction = 3;
			player.restofway = cellsize;
			player.animation.timer[3] = current_time;
		}

	if((keyboardState[SDL_SCANCODE_LEFT])||(keyboardState[SDL_SCANCODE_A]))
		if(player.direction == 0 && trafficbans[3] == 0){
			player.direction = 4;
			player.restofway = cellsize;
			player.animation.timer[3] = current_time;
		}

	if((keyboardState[SDL_SCANCODE_RIGHT])||(keyboardState[SDL_SCANCODE_D]))
		if(player.direction == 0 && trafficbans[1] == 0){
			player.direction = 2;
			player.restofway = cellsize;
			player.animation.timer[3] = current_time;
		}
	return player;
}



Container *attack(int attackernumber, Container **headcontainer){
	Container *extraContainer = *headcontainer;
	Object attacker = getList(&extraContainer, attackernumber)->data;
	if(current_time - getList(&extraContainer, attackernumber)->data.attackrecharge >=
			getList(&extraContainer, attackernumber)->data.weapon.recharge * 5
	&& getList(&extraContainer, attackernumber)->data.LVL > -1){
		for(int i = 0; i < elementCount(&extraContainer); i++){
			if(abs(attacker.rectangle.x - getList(&extraContainer, i)->data.rectangle.x) <= cellsize
			&& abs(attacker.rectangle.y - getList(&extraContainer, i)->data.rectangle.y) <= cellsize
			&& (attacker.object_ID != getList(&extraContainer, i)->data.object_ID) && getList(&extraContainer, i)->data.HP > 0){
				getList(&extraContainer, i)->data.HP -= attacker.DMG + attacker.weapon.DMG;
				getList(&extraContainer, i)->data.takendamage = attacker.DMG + attacker.weapon.DMG;
				getList(&extraContainer, attackernumber)->data.weapon.animation.angle = 0;
				getList(&extraContainer, i)->data.animation.timer[0] = current_time;
				getList(&extraContainer, i)->data.animation.timer[1] = current_time;
				getList(&extraContainer, attackernumber)->data.attackrecharge = current_time;
				getList(&extraContainer, i)->data.damageEffectRect.x = getList(&extraContainer, i)->data.rectangle.x;
				getList(&extraContainer, i)->data.damageEffectRect.y = getList(&extraContainer, i)->data.rectangle.y;
				getList(&extraContainer, i)->data.animation.animationRect.x = getList(&extraContainer, i)->data.rectangle.x + cellsize/2;
				getList(&extraContainer, i)->data.animation.animationRect.y = getList(&extraContainer, i)->data.rectangle.y + cellsize/2;
				getList(&extraContainer, i)->data.animation.animationRect.w = cellsize/4 * digitCount(getList(&extraContainer, i)->data.takendamage);
				getList(&extraContainer, i)->data.animation.animationRect.h = cellsize/3;
				if(attacker.ID == -1 && getList(&extraContainer, i)->data.relation > -1) getList(&extraContainer, i)->data.relation--;
				if(getList(&extraContainer, i)->data.HP <= 0){
					if(getList(&extraContainer, i)->data.LVL == -3){
						getList(&extraContainer, i)->data.animation.timer[2] = current_time;
						getList(&extraContainer, i)->data.ID = -2;
						getList(&extraContainer, i)->data.LVL = -1;
						getList(&extraContainer, i)->data.HP = -2;
						getList(&extraContainer, i)->data.texture = getList(&extraContainer, i)->data.death;
						if(getList(&extraContainer, i)->data.weapon.ID != -1){
							itemSpawn(getList(&extraContainer, i)->data.weapon, &objects, background_rct,
							(getList(&extraContainer, i)->data.rectangle.x - background_rct.x)/cellsize,
							(getList(&extraContainer, i)->data.rectangle.y - background_rct.y)/cellsize);
						}
					}
					else{
						getList(&extraContainer, i)->data.animation.timer[2] = current_time;
						getList(&extraContainer, attackernumber)->data.XP += getList(&extraContainer, i)->data.LVL * 10;
						getList(&extraContainer, i)->data.LVL = -1;
						getList(&extraContainer, i)->data.ID = -3;
						getList(&extraContainer, i)->data.direction = -1;
						getList(&extraContainer, i)->data.HP = -2;
						getList(&extraContainer, i)->data.texture = getList(&extraContainer, i)->data.death;
					}
				}
			}
		}
		getList(&extraContainer, attackernumber)->data.weapon.animation.angle = 0;
	}
	return *headcontainer;
}


Container *loadMap(Container **head_container, SDL_Rect backgrond_rct, char *path){
	Container *pointer = *head_container;
	Object new_object;
	char map_symbol;
	FILE *input = fopen(path, "r");
	fscanf(input, "%c", &map_symbol);
	int x = 0;
	int y = 0;
	while(feof(input) == 0){
		while(map_symbol != '\\'){
			if(map_symbol == 'x'){
				new_object = stan;
				new_object.rectangle.x = backgrond_rct.x + x * cellsize;
				new_object.rectangle.y = backgrond_rct.y + y * cellsize;
				new_object.object_ID = elementCount(&pointer);
				addLast(&pointer, new_object);
			}
			if(map_symbol == 'o'){
				new_object = barrel;
				if(limitedRandom(0,1,elementCount(&pointer)))
				{
					new_object.weapon = getList(&weapons, limitedRandom(0,
					elementCount(&weapons) - 1, elementCount(&pointer) % 11))->data.weapon;
				}
				new_object.rectangle.x = backgrond_rct.x + x * cellsize;
				new_object.rectangle.y = backgrond_rct.y + y * cellsize;
				new_object.object_ID = elementCount(&pointer);
				addLast(&pointer, new_object);
			}

			x++;
			fscanf(input, "%c", &map_symbol);
		}
		y++;
		x = -1;
		fscanf(input, "%c", &map_symbol);
	}
	x++;
	fclose(input);
	return pointer;
}


void takeWeapon(int number, Container **headcontainer){
	Container *extraContainer = *headcontainer;
	Item extraItem;
	if(getList(&extraContainer, number)->data.LVL == -2){
		extraItem = getList(&extraContainer, 0)->data.weapon;
		getList(&extraContainer, 0)->data.weapon = getList(&extraContainer, number)->data.weapon;
		getList(&extraContainer, number)->data.weapon = extraItem;
		getList(&extraContainer, number)->data.rectangle = getList(&extraContainer, number)->data.weapon.rectangle;
		getList(&extraContainer, number)->data.rectangle.x = getList(&extraContainer, 0)->data.rectangle.x;
		getList(&extraContainer, number)->data.rectangle.y = getList(&extraContainer, 0)->data.rectangle.y;
		getList(&extraContainer, number)->data.texture = extraItem.texture;
	}
}

void lvlUp(int number, Container **headcontainer){
	Container *extraContainer = *headcontainer;
	if(getList(&extraContainer, number)->data.LVL > -1
	&& getList(&extraContainer, number)->data.XP >= 100
	* (getList(&extraContainer, number)->data.LVL + 1 )){
		printf("ID: %i\nLVL: %i\n", getList(&extraContainer, number)->data.object_ID, getList(&extraContainer, number)->data.LVL);
		getList(&extraContainer, number)->data.XP -= 100 * (getList(&extraContainer, number)->data.LVL + 1 );
		getList(&extraContainer, number)->data.LVL++;
		getList(&extraContainer, number)->data.DMG +=
				1 + getList(&extraContainer, number)->data.LVL
				* getList(&extraContainer, number)->data.DMG / 10;
		getList(&extraContainer, number)->data.HP +=
				1 + getList(&extraContainer, number)->data.LVL
				* getList(&extraContainer, number)->data.HP / 10;
	}
}

void attackAnimation(Object *attacker, SDL_RendererFlip flip){
	SDL_Point extraPoint = attacker->weapon.animation.center;
	SDL_Rect extraRect;
	extraRect = attacker->weapon.rectangle;
	extraRect.x = attacker->rectangle.x;
	extraRect.y = attacker->rectangle.y + 24;
	SDL_RenderCopyEx(main_render, attacker->weapon.texture, NULL,
				 	 &extraRect, attacker->weapon.animation.angle,
					 &extraPoint, flip);
}

int switchLayers(int number){
	layer = number;
	return layer;
}

int volumeChange(int vol){
	if(volume >= 0)
	{
		volume = vol;
		if(vol == 0) soundof = 1;
		else
		{
			volume = vol;
			soundof = 0;
		}
	}
	return volume;
}

int soundOf(int arg){
	if(arg >= 0){
		if(soundof == 0){
			soundof = 1;
			volume = 0;
			Mix_VolumeMusic(volume);
		}
		else
		{
			soundof = 0;
			volume = 50;
			Mix_VolumeMusic(volume);
		}
	}
	return soundof;
}

int fullScreen(int arg){
	if(arg >= 0){
		if(SettingsConf->fullscreen == 0){
			SettingsConf->fullscreen = 1;
			save(0);
			SDL_DestroyWindow(main_window);
			SDL_DestroyRenderer(main_render);
			printf("\n%ix%i\n", screen_width, screen_height);
			main_window = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
					screen_width, screen_height, SDL_WINDOW_FULLSCREEN);
			full_screen = SDL_WINDOW_FULLSCREEN;
			SDL_GetWindowSize(main_window, &screen_width, &screen_height);
			cellsize = screen_height/20;
			main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			loadItems();
			load(0);
			void loadSettings();
		}
		else
		{
			SettingsConf->fullscreen = 0;
			save(0);
			SDL_DestroyWindow(main_window);
			SDL_DestroyRenderer(main_render);
			main_window = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
					screen_width, screen_height, SDL_WINDOW_SHOWN);
			full_screen = SDL_WINDOW_SHOWN;
			SDL_GetWindowSize(main_window, &screen_width, &screen_height);
			cellsize = screen_height/20;
			main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			loadItems();
			load(0);
			void loadSettings();
		}
	}
	return SettingsConf->fullscreen;
}

int resolution(int arg){
	if(arg >= 0){
		if(SettingsConf->resolution == 0){
			SettingsConf->resolution = 1;
			save(0);
			SDL_DestroyWindow(main_window);
			SDL_DestroyRenderer(main_render);
			screen_height = SCREEN_HEIGHT_2;
			screen_width = SCREEN_WIDTH_2;
			main_window = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
					screen_width, screen_height, full_screen);
			SDL_GetWindowSize(main_window, &screen_width, &screen_height);
			cellsize = screen_height/20;
			main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			loadItems();
			load(0);
			void loadSettings();
		}
		else
		{
			SettingsConf->resolution = 0;
			save(0);
			SDL_DestroyWindow(main_window);
			SDL_DestroyRenderer(main_render);
			screen_height = SCREEN_HEIGHT_1;
			screen_width = SCREEN_WIDTH_1;
			main_window = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
					screen_width, screen_height, full_screen);
			SDL_GetWindowSize(main_window, &screen_width, &screen_height);
			cellsize = screen_height/20;
			main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			loadItems();
			load(0);
			void loadSettings();
		}
	}
	return SettingsConf->resolution;
}

int save(int path_num){
	char *path;
	if(path_num == 0) path = "saves/save.txt";
	if(path_num == 1) path = "saves/save1.txt";
	FILE *output = fopen(path, "w");
	for(int i = 0; i < elementCount(&objects); i++){
		fprintf(output, "%i ", getList(&objects,i)->data.DMG);
		fprintf(output, "%i ", getList(&objects,i)->data.HP);
		fprintf(output, "%i ", getList(&objects,i)->data.ID);
		fprintf(output, "%i ", getList(&objects,i)->data.object_ID);
		fprintf(output, "%i ", getList(&objects,i)->data.LVL);
		fprintf(output, "%i ", getList(&objects,i)->data.XP);
		fprintf(output, "%I64i ", getList(&objects,i)->data.attackrecharge);
		fprintf(output, "%i ", getList(&objects,i)->data.direction);
		fprintf(output, "%f ", getList(&objects,i)->data.movespeed);
		fprintf(output, "%i ", getList(&objects,i)->data.pxcount);
		fprintf(output, "%f ", getList(&objects,i)->data.pxpart / cellsize);
		fprintf(output, "%i ", getList(&objects,i)->data.relation);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.restofway / cellsize);
		fprintf(output, "%i ", getList(&objects,i)->data.takendamage);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.animation.animationRect.h / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.animation.animationRect.w / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.animation.animationRect.x / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.animation.animationRect.y / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.animation.center.x / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.animation.center.y / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.damageEffectRect.h / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.damageEffectRect.w / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.damageEffectRect.x / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.damageEffectRect.y / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.rectangle.h / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.rectangle.w / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.rectangle.x / cellsize);
		fprintf(output, "%f ", (float)getList(&objects,i)->data.rectangle.y / cellsize);
		fprintf(output, "%i \n", getList(&objects,i)->data.weapon.ID);
	}
	fclose(output);
	return 0;
}

int load(int path_num){
	char *path;
	if(path_num == 0) path = "saves/save.txt";
	if(path_num == 1) path = "saves/save1.txt";
	FILE *input = fopen(path, "r");
	float extra_var;
	Object extra_object;
	printf("OBJECTS BEFORE: %i\n", elementCount(&objects));
	extra_var = elementCount(&objects);
	for(int i = 0; i < extra_var; i++){
		delLast(&objects);
	}
	printf("OBJECTS DELETED: %i\n", elementCount(&objects));
	while(feof(input) == 0)
	{
		fscanf(input, "%i ", &extra_object.DMG);
		fscanf(input, "%i ", &extra_object.HP);
		fscanf(input, "%i ", &extra_object.ID);
		fscanf(input, "%i ", &extra_object.object_ID);
		fscanf(input, "%i ", &extra_object.LVL);
		fscanf(input, "%i ", &extra_object.XP);
		fscanf(input, "%I64i ", &extra_object.attackrecharge);
		fscanf(input, "%i ", &extra_object.direction);
		fscanf(input, "%f ", &extra_object.movespeed);
		fscanf(input, "%i ", &extra_object.pxcount);
		fscanf(input, "%f ", &extra_var);
		extra_object.pxpart  = extra_var * cellsize;
		fscanf(input, "%i ", &extra_object.relation);
		fscanf(input, "%f ", &extra_var);
		extra_object.restofway = extra_var * cellsize;
		fscanf(input, "%i ", &extra_object.takendamage);
		fscanf(input, "%f ", &extra_var);
		extra_object.animation.animationRect.h = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.animation.animationRect.w = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.animation.animationRect.x = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.animation.animationRect.y = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.animation.center.x = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.animation.center.y = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.damageEffectRect.h = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.damageEffectRect.w = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.damageEffectRect.x = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.damageEffectRect.y = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.rectangle.h = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.rectangle.w = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.rectangle.x = extra_var * cellsize;
		fscanf(input, "%f ", &extra_var);
		extra_object.rectangle.y = extra_var * cellsize;
		fscanf(input, "%i \n", &extra_object.weapon.ID);
		addToList(&objects, extra_object, elementCount(&objects));
	}
	printf("OBJECTS AFTER: %i\n", elementCount(&objects));
	fclose(input);
	initTextures();
	return 0;
}

_Bool createButton(char * text, int x, int y, int func(), int arg){
	button512_rct.x = background_rct.x + cellsize * x;
	button512_rct.y = background_rct.y + cellsize * y;
	SDL_Rect text_rect;
	text_rect.h = cellsize;
	text_rect.w = cellsize * strlen(text);
	text_rect.y = button512_rct.y + button512_rct.h / 2 - text_rect.h / 2 + 5;
	text_rect.x = button512_rct.x + button512_rct.w / 2 - text_rect.w / 2;
	SDL_Texture *text_txtr;
	if(mouse_x >= button512_rct.x && mouse_x <= button512_rct.x + button512_rct.w
	&& mouse_y >= button512_rct.y && mouse_y <= button512_rct.y + button512_rct.h){
		if(mouse_state == SDL_BUTTON_LMASK || mouse_state == SDL_BUTTON_RMASK){
			click_chek = 0;
			button512_state.y = 128 * 8;
			SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
			text_txtr = newText(text, 255, 255, 255);
			SDL_RenderCopy(main_render, text_txtr, NULL, &text_rect);
			SDL_DestroyTexture(text_txtr);
		}
		else
		{
			button512_state.y = 64 * 8;
			SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
			text_txtr = newText(text, 0, 0, 0);
			SDL_RenderCopy(main_render, text_txtr, NULL, &text_rect);
			SDL_DestroyTexture(text_txtr);
		}
		if(main_event->button.type == SDL_MOUSEBUTTONUP && click_chek == 0){
			click_chek = 1;
			func(arg);
			return 1;
		}
	}
	else
	{
		button512_state.y = 0;
		SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
		text_txtr = newText(text, 0, 0, 0);
		SDL_RenderCopy(main_render, text_txtr, NULL, &text_rect);
		SDL_DestroyTexture(text_txtr);
	}
	return 0;
	SDL_SetRenderDrawColor(main_render, 0, 0 ,0 ,0);
}

_Bool createButtonSwitch(char * text1, char * text2, int x, int y, int func(), int arg){
	char *text;
	button512_rct.x = background_rct.x + cellsize * x;
	button512_rct.y = background_rct.y + cellsize * y;
	SDL_Rect text_rect;
	if(func(-1) == 0){
		text = text1;
	}
	else
	{
		text = text2;
	}
	text_rect.h = cellsize;
	text_rect.w = cellsize * strlen(text);
	text_rect.y = button512_rct.y + button512_rct.h / 2 - text_rect.h / 2 + 5;
	text_rect.x = button512_rct.x + button512_rct.w / 2 - text_rect.w / 2;
	SDL_Texture *text_txtr;
	if(mouse_x >= button512_rct.x && mouse_x <= button512_rct.x + button512_rct.w
	&& mouse_y >= button512_rct.y && mouse_y <= button512_rct.y + button512_rct.h){
		if(mouse_state == SDL_BUTTON_LMASK || mouse_state == SDL_BUTTON_RMASK){
			click_chek = 0;
			button512_state.y = 128 * 8;
			SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
			text_txtr = newText(text, 255, 255, 255);
			SDL_RenderCopy(main_render, text_txtr, NULL, &text_rect);
			SDL_DestroyTexture(text_txtr);
		}
		else
		{
			button512_state.y = 64 * 8;
			SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
			text_txtr = newText(text, 0, 0, 0);
			SDL_RenderCopy(main_render, text_txtr, NULL, &text_rect);
			SDL_DestroyTexture(text_txtr);
		}
		if(main_event->button.type == SDL_MOUSEBUTTONUP && click_chek == 0){
			click_chek = 1;
			func(arg);
			return 1;
		}
	}
	else
	{
		button512_state.y = 0;
		SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
		text_txtr = newText(text, 0, 0, 0);
		SDL_RenderCopy(main_render, text_txtr, NULL, &text_rect);
		SDL_DestroyTexture(text_txtr);
	}
	return 0;
	SDL_SetRenderDrawColor(main_render, 0, 0 ,0 ,0);
}

void loadSettings(){
	FILE *input = fopen("saves/settings.txt", "r");
	fscanf(input, "%i", &SettingsConf->sound);
	fscanf(input, "%i", &SettingsConf->resolution);
	fscanf(input, "%i", &SettingsConf->fullscreen);
	soundof = SettingsConf->sound;
	printf("%i\n", SettingsConf->sound);
	printf("%i\n", SettingsConf->resolution);
	printf("%i\n", SettingsConf->fullscreen);
	if(SettingsConf->resolution == 0)
	{
		screen_height = SCREEN_HEIGHT_1;
		screen_width = SCREEN_WIDTH_1;
	}
	if(SettingsConf->resolution == 1)
	{
		screen_height = SCREEN_HEIGHT_2;
		screen_width = SCREEN_WIDTH_2;
	}
	if(SettingsConf->fullscreen == 0)
	{
		full_screen = SDL_WINDOW_SHOWN;
	}
	else
	{
		full_screen = SDL_WINDOW_FULLSCREEN;
	}
	fclose(input);
}

void pauseMenu(){
	Mix_VolumeMusic(volume);
	if(Mix_PlayingMusic() == 0) Mix_PlayMusic(main_theme, -1);
	if(createButton("RESUME", 2, 4, switchLayers, 1)) Mix_HaltMusic();
	createButton("SAVE", 2, 8, save, 1);
	createButton("SETTINGS", 2, 12, switchLayers, 2);
	if(createButton("EXIT", 2, 16, switchLayers, -1)) Mix_HaltMusic();
}

void settingsMenu(){
	createButtonSwitch("SOUND:ON", "SOUND:OFF", 2, 4, soundOf, 0);
	createButtonSwitch("1920x1080", "1280x720", 2, 8, resolution, 0);
	createButtonSwitch("FULLSCREEN:OFF", "FULLSCREEN:ON", 2, 12, fullScreen, 0);
	createButton("BACK", 2, 16, switchLayers, 0);
}

void game(){
	SDL_RenderCopy(main_render, background_txtr, NULL, &background_rct);
	Mix_VolumeMusic(volume);
	if(Mix_PlayingMusic() == 0) Mix_PlayMusic(theme1, -1);
	SDL_Rect extraRect;

	//rendering unalive
	//for(int i = 0; i < elementCount(&objects) ; i++){
	//	extraRect = getList(&objects, i)->data.rectangle;
	//	if(getList(&objects, i)->data.LVL < 0)SDL_RenderCopy(main_render, getList(&objects, i)->data.texture, NULL, &extraRect);
	//}


	//rendering alive
	//for(int i = 0; i < elementCount(&objects) ; i++){
	//	extraRect = getList(&objects, i)->data.rectangle;
		//if(getList(&objects, i)->data.LVL >= 0)
	//	SDL_RenderCopy(main_render, getList(&objects, i)->data.texture, NULL, &extraRect);
	//}


	//player attack
	if(key_state[SDL_SCANCODE_F] && getList(&objects, 0)->data.weapon.using == 0){
		getList(&objects, 0)->data.animation.timer[4] = current_time;
		getList(&objects, 0)->data.weapon.using = 1;
	}


	for(int i = 0; i < elementCount(&objects); i++){
		if(getList(&objects, i)->data.LVL < 0)
		{
			extraRect = getList(&objects, i)->data.rectangle;
			SDL_RenderCopy(main_render, getList(&objects, i)->data.texture, NULL, &extraRect);
		}
	}


	//action cycle
	for(int i = 0; i < elementCount(&objects); i++){
		int *trafficbans = calculateTrafficBans(getList(&objects, 0)->data, &objects);
		getList(&objects, 0)->data = playerMoving(getList(&objects, 0)->data, trafficbans, key_state);

		//entities moving
		getList(&objects, i)->data = entityMoving(getList(&objects, i)->data, &objects, i);


		//rendering effects
		if(getList(&objects, i)->data.takendamage > 0){

			//damage effect
			if(current_time - getList(&objects, i)->data.animation.timer[0] < 300){
				extraRect = getList(&objects, i)->data.damageEffectRect;
				SDL_RenderCopy(main_render, getList(&objects, i)->data.damageEffectTexture, NULL, &extraRect);
			}

			//damage indicator
			if(getList(&objects, i)->data.takendamage > 0){
				char *damage_indicator = malloc(12*sizeof(char));
				itoa(getList(&objects, i)->data.takendamage, damage_indicator, 10);
				if(current_time - getList(&objects, i)->data.animation.timer[1] > 10){
					getList(&objects, i)->data.animation.animationRect.y -= 2;
					getList(&objects, i)->data.animation.timer[1] = current_time;
				}
				extraRect = getList(&objects, i)->data.animation.animationRect;
				SDL_Texture *extra_texture = newText(damage_indicator, 255, 255, 255);
				free(damage_indicator);
				SDL_RenderCopy(main_render, extra_texture, NULL, &extraRect);
				SDL_DestroyTexture(extra_texture);
				if(current_time - getList(&objects, i)->data.animation.timer[0] >= 800){
					getList(&objects, i)->data.takendamage = 0;
				}
			}
		}


		//attacks of entities
		if(getList(&objects, i)->data.DMG != -1){
			if(abs(getList(&objects, 0)->data.rectangle.x - getList(&objects, i)->data.rectangle.x) <= cellsize
			&& abs(getList(&objects, 0)->data.rectangle.y - getList(&objects, i)->data.rectangle.y) <= cellsize
			&& getList(&objects, 0)->data.ID == -1 && i != 0 && getList(&objects, i)->data.relation == -1
			&& getList(&objects, i)->data.weapon.using == 0 && getList(&objects, 0)->data.XP != -1)
			{
				getList(&objects, i)->data.animation.timer[4] = current_time;
				getList(&objects, i)->data.weapon.using = 1;
			}
		}
		if(getList(&objects, i)->data.weapon.using == 1
		&& current_time - getList(&objects, i)->data.animation.timer[4] >= getList(&objects, i)->data.weapon.attackdelay * 1000){
			objects = attack(i, &objects);
			getList(&objects, i)->data.weapon.using = 0;
		}


		lvlUp(i, &objects);


		//attack animation
		if(getList(&objects, i)->data.weapon.animation.angle < 360){
			if(current_time - getList(&objects, i)->data.attackrecharge >= 10){
				getList(&objects, i)->data.attackrecharge = current_time;
				getList(&objects, i)->data.weapon.animation.angle += 1440/getList(&objects, i)->data.weapon.recharge;
			}
			Object extraObject = getList(&objects, i)->data;
			attackAnimation(&extraObject, sword_flip);
		}


		if(key_state[SDL_SCANCODE_E] && current_time - getList(&objects, 0)->data.weapon.animation.timer[0] > 1000){
			if(abs(getList(&objects, 0)->data.rectangle.x - getList(&objects, i)->data.rectangle.x) <= cellsize
			&& abs(getList(&objects, 0)->data.rectangle.y - getList(&objects, i)->data.rectangle.y) <= cellsize
			&& getList(&objects, i)->data.LVL == -2){
				takeWeapon(i, &objects);
				getList(&objects, 0)->data.weapon.animation.timer[0] = current_time;
			}
		}
		//removal of corpses
		if(current_time - getList(&objects, i)->data.animation.timer[2] >= 10000 && getList(&objects, i)->data.LVL == -1
		&& getList(&objects, i)->data.HP == -2 && getList(&objects, i)->data.ID == -3){
			delElement(&objects, i);
		}


		if(getList(&objects, i)->data.ID != -1)
		{
			extraRect = getList(&objects, i)->data.rectangle;
			if(getList(&objects, i)->data.LVL >= 0)SDL_RenderCopy(main_render, getList(&objects, i)->data.texture, NULL, &extraRect);
		}
	}
	extraRect = getList(&objects, 0)->data.rectangle;


	SDL_RenderCopy(main_render, getList(&objects, 0)->data.texture, NULL, &extraRect);

	char *stats;
	SDL_Rect stats_rct;
	SDL_Texture *stats_txtr;

	stats_rct.h = cellsize / 2;
	stats_rct.w = 1.5 * cellsize;
	stats_rct.x = background_rct.x + cellsize;
	stats_rct.y = background_rct.y + cellsize;

	stats_txtr = newText("HP:",255,255,255);
	SDL_RenderCopy(main_render, stats_txtr, NULL, &stats_rct);
	SDL_DestroyTexture(stats_txtr);
	stats_rct.x = background_rct.x + cellsize * 2.5;
	stats_rct.w = digitCount(getList(&objects, 0)->data.HP) * cellsize / 2;
	stats = malloc(12*sizeof(char));
	itoa(getList(&objects, 0)->data.HP, stats, 10);
	stats_txtr = newText(stats,255,255,255);
	SDL_RenderCopy(main_render, stats_txtr, NULL, &stats_rct);
	SDL_DestroyTexture(stats_txtr);
	free(stats);


	if(key_state[SDL_SCANCODE_ESCAPE]){
		layer = 0;
		Mix_HaltMusic();
	}

}
