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
	srand(time(NULL) % 10 + extra);
	return bot_edge + (rand() % (top_edge + 1 - bot_edge));
}


void spawn(Object object, Container **headcontainer, SDL_Rect backgroundrect, int x, int y){
	Container *extra_container = *headcontainer;
	object.rectangle.x = backgroundrect.x + x * cellsize;
	object.rectangle.y = backgroundrect.y + y * cellsize;
	object.ID = elementCount(&extra_container);
	addLast(&extra_container, object);
}


void itemSpawn(Item item, Container **headcontainer, SDL_Rect bgrect, int x, int y){
	Container *extra_container = *headcontainer;
		item_object.weapon = item;
		item_object.rectangle.h = item_object.weapon.rectangle.h;
		item_object.rectangle.w = item_object.weapon.rectangle.w;
		item_object.rectangle.x = bgrect.x + x * cellsize;
		item_object.rectangle.y = bgrect.y + y * cellsize;
		item_object.ID = elementCount(&extra_container);
		item_object.LVL = -2;
		item_object.texture = item_object.weapon.texture;
		addLast(&extra_container, item_object);
	}


void randSpawn(Object object, Container **headcontainer, SDL_Rect bgrect, int extra){
	Container *extra_container = *headcontainer;
	object.rectangle.x = bgrect.x + limitedRandom(1, 19, extra*752) * cellsize;
	object.rectangle.y = bgrect.y + (limitedRandom(1, 19, extra * extra * 257257)) * cellsize;
	object.ID = elementCount(&extra_container);
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
		if(abs(entity.rectangle.x - getList(&pointer, i)->data.rectangle.x) <= 32
		&& abs(entity.rectangle.y - getList(&pointer, i)->data.rectangle.y) <= 32
		&& getList(&pointer, i)->data.LVL != -1 && getList(&pointer, i)->data.LVL != -2 ){
			if(entity.rectangle.x - getList(&pointer, i)->data.rectangle.x == 32){
				if(entity.rectangle.y == getList(&pointer, i)->data.rectangle.y){
					unmoving[3] = 4;
				}
			}
			if(entity.rectangle.x - getList(&pointer, i)->data.rectangle.x == -32){
				if(entity.rectangle.y == getList(&pointer, i)->data.rectangle.y){
					unmoving[1] = 2;
				}
			}
			if(entity.rectangle.y - getList(&pointer, i)->data.rectangle.y == 32){
				if(entity.rectangle.x == getList(&pointer, i)->data.rectangle.x){
					unmoving[0] = 1;
				}
			}
			if(entity.rectangle.y - getList(&pointer, i)->data.rectangle.y == -32){
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
		if(abs(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x) <= 128
		&& abs(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y) <= 128
		&& entity.relation == -1 && getList(&extraContainer, i)->data.relation == 1){
			derection = 0;
			if((abs(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x) <= 32
			&& entity.rectangle.y == getList(&extraContainer, i)->data.rectangle.y) ||
			(abs(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y) <= 32
			&& entity.rectangle.x == getList(&extraContainer, i)->data.rectangle.x)) derection = 0;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y == getList(&extraContainer, i)->data.rectangle.y
			&& unmoving[3] != 4) derection = 4;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y == getList(&extraContainer, i)->data.rectangle.y
			&& unmoving[1] != 2) derection = 2;
			else if(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& entity.rectangle.x == getList(&extraContainer, i)->data.rectangle.x
			&& unmoving[0] != 1) derection = 1;
			else if(entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& entity.rectangle.x == getList(&extraContainer, i)->data.rectangle.x
			&& unmoving[2] != 3) derection = 3;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[1] != 2) derection = 2;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[2] != 3) derection = 3;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[0] != 1) derection = 1;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[3] != 4) derection = 4;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[3] != 4) derection = 4;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= -128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 0
			&& unmoving[2] != 3) derection = 3;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[0] != 1) derection = 1;
			else if(entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x >= -128
			&& entity.rectangle.x - getList(&extraContainer, i)->data.rectangle.x <= 0
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y <= 128
			&& entity.rectangle.y - getList(&extraContainer, i)->data.rectangle.y >= 0
			&& unmoving[1] != 2) derection = 2;
		}
	}
	return derection;
}


int calculateEntityMoving(Object entity, Container **headcontainer, int randvar){
	Container *extraContainer = *headcontainer;
	int counter = 0;
	int *unmoving = calculateTrafficBans(entity, &extraContainer);
	if(entity.direction == -1 || entity.LVL == -1){
		return -1;
	}
	else if((unmoving[0] == 1 && unmoving[1] == 2 && unmoving[2] == 3 && unmoving[3] == 4)){
		return 0;
	}
	else{
		if(calculateChasing(unmoving, entity, &extraContainer) == -1){
			for(int i = 0; i < 4; i++){
				if(unmoving[i] == 0){
					unmoving[0] = 0;
					unmoving[counter + 1] = i + 1;
					counter++;
				}
			}
			return unmoving[limitedRandom(0,counter, time(NULL) * randvar * entity.ID)];
		}
		else return calculateChasing(unmoving, entity, &extraContainer);
	}
}


Object entityMoving(Object entity, Container **headcontainer, int randvar){
	Container *extraContainer = *headcontainer;
	if(entity.direction == 0 && entity.ID != -1){
		entity.direction = calculateEntityMoving(entity, &extraContainer, randvar);
		if(entity.direction != 0){
			entity.restofway = cellsize;
			entity.pxpart = 0;
			entity.animation.timer[3] = current_time;
		}
	}
	else if(entity.direction == 1){
		if((current_time - entity.animation.timer[3]) > 15){
			if(entity.pxpart + entity.movespeed / 200 - (int)entity.pxpart >= 1 + (int)(entity.movespeed / 200)){
				entity.pxcount = 1;
				entity.pxpart -= (int)entity.pxpart;
			}
			entity.pxpart += entity.movespeed / 200;
			entity.rectangle.y -= (int)(entity.movespeed / 200 + entity.pxcount);
			entity.restofway -= (int)(entity.movespeed / 200 + entity.pxcount);
			if(entity.restofway <= 0){
				entity.rectangle.y -= entity.restofway;
				entity.restofway = 0;
			}
			entity.pxcount = 0;
			entity.animation.timer[3] = current_time;
		}
	}
	else if(entity.direction == 2){
		if((current_time - entity.animation.timer[3]) > 15){
			if(entity.pxpart + entity.movespeed / 200 - (int)entity.pxpart >= 1 + (int)(entity.movespeed / 200)){
				entity.pxcount = 1;
				entity.pxpart -= (int)entity.pxpart;
			}
			entity.pxpart += entity.movespeed / 200;
			entity.rectangle.x += (int)(entity.movespeed / 200 + entity.pxcount);
			entity.restofway -= (int)(entity.movespeed / 200 + entity.pxcount);
			if(entity.restofway <= 0){
				entity.rectangle.x += entity.restofway;
				entity.restofway = 0;
			}
			entity.pxcount = 0;
			entity.animation.timer[3] = current_time;
		}
	}
	else if(entity.direction == 3){
		if((current_time - entity.animation.timer[3]) > 15){
			if(entity.pxpart + entity.movespeed / 200 - (int)entity.pxpart >= 1 + (int)(entity.movespeed / 200)){
				entity.pxcount = 1;
				entity.pxpart -= (int)entity.pxpart;
			}
			entity.pxpart += entity.movespeed / 200;
			entity.rectangle.y += (int)(entity.movespeed / 200 + entity.pxcount);
			entity.restofway -= (int)(entity.movespeed / 200 + entity.pxcount);
			if(entity.restofway <= 0){
				entity.rectangle.y += entity.restofway;
				entity.restofway = 0;
			}
			entity.pxcount = 0;
			entity.animation.timer[3] = current_time;
		}
	}
	else if(entity.direction == 4){
		if((current_time - entity.animation.timer[3]) > 15){
			if(entity.pxpart + entity.movespeed / 200 - (int)entity.pxpart >= 1 + (int)(entity.movespeed / 200)){
				entity.pxcount = 1;
				entity.pxpart -= (int)entity.pxpart;
			}
			entity.pxpart += entity.movespeed / 200;
			entity.rectangle.x -= (int)(entity.movespeed / 200 + entity.pxcount);
			entity.restofway -= (int)(entity.movespeed / 200 + entity.pxcount);
			if(entity.restofway <= 0){
				entity.rectangle.x -= entity.restofway;
				entity.restofway = 0;
			}
			entity.pxcount = 0;
			entity.animation.timer[3] = current_time;
		}
	}
	if(entity.restofway == 0 && entity.direction != -1){
		entity.direction = 0;
	}
	return entity;
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
			if(abs(attacker.rectangle.x - getList(&extraContainer, i)->data.rectangle.x) <= 32
			&& abs(attacker.rectangle.y - getList(&extraContainer, i)->data.rectangle.y) <= 32
			&& (attacker.ID != getList(&extraContainer, i)->data.ID) && getList(&extraContainer, i)->data.HP > 0){
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
				getList(&extraContainer, i)->data.animation.animationRect.w = 8 * digitCount(getList(&extraContainer, i)->data.takendamage);
				getList(&extraContainer, i)->data.animation.animationRect.h = 12;
				if(attacker.ID == -1 && getList(&extraContainer, i)->data.relation > -1) getList(&extraContainer, i)->data.relation--;
				if(getList(&extraContainer, i)->data.HP <= 0){
					if(getList(&extraContainer, i)->data.LVL == -3){

						getList(&extraContainer, i)->data.animation.timer[2] = current_time;
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
						getList(&extraContainer, attackernumber)->data.XP += getList(&extraContainer, i)->data.LVL * 100;
						getList(&extraContainer, i)->data.LVL = -1;
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


Container *loadMap(Container **headcontainer, SDL_Rect bgrect, char *path){
	Container *extraContainer = *headcontainer;
	Object extraObject;
	char map_symbol;
	FILE *input = fopen(path, "r");
	fscanf(input, "%c", &map_symbol);
	int x = 0;
	int y = 0;
	while(feof(input) == 0){
		while(map_symbol != '\\'){
			if(map_symbol == 'x'){
				extraObject = stan;
				extraObject.rectangle.x = bgrect.x + x * cellsize;
				extraObject.rectangle.y = bgrect.y + y * cellsize;
				extraObject.ID = elementCount(&extraContainer);
				addLast(&extraContainer, extraObject);
			}
			if(map_symbol == 'o'){
				extraObject = barrel;
				extraObject.weapon = getList(&weapons, limitedRandom(0, elementCount(&weapons) - 1, elementCount(&extraContainer)))->data.weapon;
				extraObject.rectangle.x = bgrect.x + x * cellsize;
				extraObject.rectangle.y = bgrect.y + y * cellsize;
				extraObject.ID = elementCount(&extraContainer);
				printf("YAAA");
				addLast(&extraContainer, extraObject);
			}

			x++; //x
			fscanf(input, "%c", &map_symbol);
		}
		y++; //y
		x = -1;
		fscanf(input, "%c", &map_symbol);
	}
	x++;
	fclose(input);
	return extraContainer;
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
		printf("ID: %i\nLVL: %i\n", getList(&extraContainer, number)->data.ID, getList(&extraContainer, number)->data.LVL);
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
	extraRect.y = attacker->rectangle.y + 16;
	SDL_RenderCopyEx(main_render, attacker->weapon.texture, NULL,
				 	 &extraRect, attacker->weapon.animation.angle,
					 &extraPoint, flip);
}

void switchLayers(){

}

void pauseMenu(){
	if(Mix_PlayingMusic() == 0) Mix_PlayMusic(main_theme, -1);

	button512_rct.x = background_rct.x + 64;
	button512_rct.y = background_rct.y + 128;
	SDL_Rect text_rect;
	text_rect.h = 64;
	text_rect.w = 384;
	text_rect.y = 120;
	text_rect.x = 128;
	SDL_Texture *text;
	if(mouse_x >= 64 && mouse_x <= 576 && mouse_y >= 128 && mouse_y <= 192){
		if(mouse_state == SDL_BUTTON_LMASK || mouse_state == SDL_BUTTON_RMASK){
			button512_state.y = 128 * 8;
			SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
			text = newText("resume", 255, 255, 255);
			SDL_RenderCopy(main_render, text, NULL, &text_rect);
			SDL_DestroyTexture(text);
		}
		else
		{
			button512_state.y = 64 * 8;
			SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
			text = newText("resume", 0, 0, 0);
			SDL_RenderCopy(main_render, text, NULL, &text_rect);
			SDL_DestroyTexture(text);
		}
		if(main_event->button.type == SDL_MOUSEBUTTONUP){
			layer = 1;
			Mix_HaltMusic();
		}
	}
	else
	{
		button512_state.y = 0;
		SDL_RenderCopy(main_render, button512_txtr, &button512_state, &button512_rct);
		text = newText("resume", 0, 0, 0);
		SDL_RenderCopy(main_render, text, NULL, &text_rect);
		SDL_DestroyTexture(text);
	}

	SDL_SetRenderDrawColor(main_render, 0, 0 ,0 ,0);
}

void game(){
	SDL_RenderCopy(main_render, background_txtr, NULL, &background_rct);
	SDL_Rect extraRect;

	//rendering unalive
	for(int i = 0; i < elementCount(&objects) ; i++){
		extraRect = getList(&objects, i)->data.rectangle;
		if(getList(&objects, i)->data.LVL < 0)SDL_RenderCopy(main_render, getList(&objects, i)->data.texture, NULL, &extraRect);
	}


	//rendering alive
	for(int i = 0; i < elementCount(&objects) ; i++){
		extraRect = getList(&objects, i)->data.rectangle;
		if(getList(&objects, i)->data.LVL >= 0)SDL_RenderCopy(main_render, getList(&objects, i)->data.texture, NULL, &extraRect);
	}


	//player attack
	if(key_state[SDL_SCANCODE_F] && getList(&objects, 0)->data.weapon.using == 0){
		getList(&objects, 0)->data.animation.timer[4] = current_time;
		getList(&objects, 0)->data.weapon.using = 1;
	}
	int *trafficbans = calculateTrafficBans(getList(&objects, 0)->data, &objects);
	getList(&objects, 0)->data = playerMoving(getList(&objects, 0)->data, trafficbans, key_state);


	//action cycle
	for(int i = 0; i < elementCount(&objects); i++){


		//entities moving
		getList(&objects, i)->data = entityMoving(getList(&objects, i)->data, &objects, i);


		//rendering effects
		if(getList(&objects, i)->data.takendamage > 0){


			//damage effect
			if(current_time - getList(&objects, i)->data.animation.timer[0] < 250){
				extraRect = getList(&objects, i)->data.damageEffectRect;
				SDL_RenderCopy(main_render, getList(&objects, i)->data.damageEffectTexture, NULL, &extraRect);
			}


			//damage indicator
			if(getList(&objects, i)->data.takendamage > 0){
				char *damage_indicator = malloc(12*sizeof(char));
				itoa(getList(&objects, i)->data.takendamage, damage_indicator, 10);
				if(current_time - getList(&objects, i)->data.animation.timer[1] > 15){
					getList(&objects, i)->data.animation.animationRect.y -= 2;
					getList(&objects, i)->data.animation.timer[1] = current_time;
				}
				extraRect = getList(&objects, i)->data.animation.animationRect;
				SDL_Texture *extraTexture = newText(damage_indicator, 255, 255, 255);
				free(damage_indicator);
				SDL_RenderCopy(main_render, extraTexture, NULL, &extraRect);
				SDL_DestroyTexture(extraTexture);

				if(current_time - getList(&objects, i)->data.animation.timer[0] >= 800){
					getList(&objects, i)->data.takendamage = 0;
				}
			}
		}

		//attacks of entities
		if(getList(&objects, i)->data.DMG != -1){
			if(abs(getList(&objects, 0)->data.rectangle.x - getList(&objects, i)->data.rectangle.x) <= 32
			&& abs(getList(&objects, 0)->data.rectangle.y - getList(&objects, i)->data.rectangle.y) <= 32
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
			if(current_time - getList(&objects, i)->data.attackrecharge >= 15){
				getList(&objects, i)->data.attackrecharge = current_time;
				getList(&objects, i)->data.weapon.animation.angle += 1440/getList(&objects, i)->data.weapon.recharge;
			}
			Object extraObject = getList(&objects, i)->data;
			attackAnimation(&extraObject, sword_flip);
		}

		if(key_state[SDL_SCANCODE_E] && current_time - getList(&objects, 0)->data.weapon.animation.timer[0] > 1000){
			if(abs(getList(&objects, 0)->data.rectangle.x - getList(&objects, i)->data.rectangle.x) <= 32
			&& abs(getList(&objects, 0)->data.rectangle.y - getList(&objects, i)->data.rectangle.y) <= 32
			&& getList(&objects, i)->data.LVL == -2){
				takeWeapon(i, &objects);
				getList(&objects, 0)->data.weapon.animation.timer[0] = current_time;
			}
		}


		//removal of corpses
		if(current_time - getList(&objects, i)->data.animation.timer[2] >= 2000 && getList(&objects, i)->data.LVL == -1
		&& getList(&objects, i)->data.HP == -2){
			delElement(&objects, i);

		}
	}

}
