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


int digit_count(int number){
	if(number > 0){
		return 1 + digit_count(number/10);
	}
	return 0;
}


int limitedrandom(int botEdge, int topEdge, int extra){
	extravar2 = time(NULL);
	srand(extravar2 + extra);
	return botEdge + (rand() % (topEdge - botEdge));
}


void randSpawn(object object, container **headcontainer, SDL_Rect bgrect, int extra){
	extraContainer = *headcontainer;
	object.rectangle.x = bgrect.x + limitedrandom(1, 19, extra*752) * 32;
	object.rectangle.y = bgrect.y + (limitedrandom(1, 19, extra * extra * 257257)) * 32;
	object.ID = element_count(&extraContainer);
	addlast(&extraContainer, object);
	extraContainer = *headcontainer;
}


void multiSpawn(SDL_Renderer *render, container **headcontainer, object object, SDL_Rect bgrect, int number){
	extraContainer = *headcontainer;
	for(j = 0; j < number; j++){
		randSpawn(object, &extraContainer, bgrect, j + 1);
	}
	extraContainer = *headcontainer;
}


SDL_Texture *newtext(char *text, SDL_Renderer *render, int red, int green, int blue){
	extraColour.b = blue;
	extraColour.g = green;
	extraColour.r = red;
	extraSurface = TTF_RenderText_Solid(mainFont, text, extraColour);
	extraTexture2 = SDL_CreateTextureFromSurface(render, extraSurface);
	SDL_FreeSurface(extraSurface);
	return extraTexture2;
}


int *calculateTrafficBans(object entity, container **headcontainer){
	extraContainer = *headcontainer;
	unmoving[0] = 0;
	unmoving[1] = 0;
	unmoving[2] = 0;
	unmoving[3] = 0;
	for(j = 0; j < element_count(&extraContainer); j++){
		if(abs(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x) <= 32
		&& abs(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y) <= 32
		&& getlist(&extraContainer, j)->data.LVL != -1){
			if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x == 32){
				if(entity.rectangle.y == getlist(&extraContainer, j)->data.rectangle.y){
					unmoving[3] = 4;
				}
			}
			if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x == -32){
				if(entity.rectangle.y == getlist(&extraContainer, j)->data.rectangle.y){
					unmoving[1] = 2;
				}
			}
			if(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y == 32){
				if(entity.rectangle.x == getlist(&extraContainer, j)->data.rectangle.x){
					unmoving[0] = 1;
				}
			}
			if(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y == -32){
				if(entity.rectangle.x == getlist(&extraContainer, j)->data.rectangle.x){
					unmoving[2] = 3;
				}
			}
			/*if(getlist(&extraContainer, j)->data.direction != -1 && entity.ID != -1){
				if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x == -32
				&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y == -32){
					unmoving[1] = 2;
					unmoving[2] = 3;
				}
				if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x == 32
				&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y == 32){
					unmoving[0] = 1;
					unmoving[3] = 4;
				}
				if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x == 32
				&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y == -32){
					unmoving[3] = 4;
					unmoving[2] = 3;
				}
				if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x == -32
				&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y == 32){
					unmoving[2] = 1;
					unmoving[3] = 2;
				}
			}*/
		}
	}
	return unmoving;
}


int calculatechasing(int *unmoving, object entity, container **headcontainer){
	extraContainer = *headcontainer;
	extravar = -1;
	for(j = 0; j < element_count(&extraContainer); j++){
		if(abs(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x) <= 128
		&& abs(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y) <= 128
		&& entity.relation == -1 && getlist(&extraContainer, j)->data.relation == 1){
			extravar = 0;
			if((abs(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x) <= 32
			&& entity.rectangle.y == getlist(&extraContainer, j)->data.rectangle.y) ||
			(abs(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y) <= 32
			&& entity.rectangle.x == getlist(&extraContainer, j)->data.rectangle.x)) extravar = 0;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= 0
			&& entity.rectangle.y == getlist(&extraContainer, j)->data.rectangle.y
			&& unmoving[3] != 4) extravar = 4;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= -128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 0
			&& entity.rectangle.y == getlist(&extraContainer, j)->data.rectangle.y
			&& unmoving[1] != 2) extravar = 2;
			else if(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= 0
			&& entity.rectangle.x == getlist(&extraContainer, j)->data.rectangle.x
			&& unmoving[0] != 1) extravar = 1;
			else if(entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= -128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 0
			&& entity.rectangle.x == getlist(&extraContainer, j)->data.rectangle.x
			&& unmoving[2] != 3) extravar = 3;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= -128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= -128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 0
			&& unmoving[1] != 2) extravar = 2;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= -128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= -128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 0
			&& unmoving[2] != 3) extravar = 3;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= 0
			&& unmoving[0] != 1) extravar = 1;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= 0
			&& unmoving[3] != 4) extravar = 4;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= -128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 0
			&& unmoving[3] != 4) extravar = 4;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= -128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 0
			&& unmoving[2] != 3) extravar = 3;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= -128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= 0
			&& unmoving[0] != 1) extravar = 1;
			else if(entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x >= -128
			&& entity.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x <= 0
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y <= 128
			&& entity.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y >= 0
			&& unmoving[1] != 2) extravar = 2;
		}
	}
	return extravar;
}


int calculateEntityMoving(object entity, container **headcontainer, int randvar){
	extraContainer = *headcontainer;
	extravar = 0;
	unmoving = calculateTrafficBans(entity, &extraContainer);
	if(entity.direction == -1 || entity.LVL == -1){
		return -1;
	}
	else if((unmoving[0] == 1 && unmoving[1] == 2 && unmoving[2] == 3 && unmoving[3] == 4)){
		return 0;
	}
	else{
		if(calculatechasing(unmoving, entity, &extraContainer) == -1){
			for(j = 0; j < 4; j++){
				if(unmoving[j] == 0){
					unmoving[0] = 0;
					unmoving[extravar + 1] = j + 1;
					extravar++;
				}
			}
			return unmoving[limitedrandom(0,extravar + 1, time(NULL) * randvar+extravar)];
		}
		else return calculatechasing(unmoving, entity, &extraContainer);
	}
}


object entityMoving(object entity, container **headcontainer, int randvar){
	extraContainer = *headcontainer;
	if(entity.direction == 0 && entity.ID != -1){
		entity.direction = calculateEntityMoving(entity, &extraContainer, randvar);
		if(entity.direction != 0){
			entity.restofway = cellsize;
			entity.pxpart = 0;
			entity.animation.timer[3] = currenttime;
		}
	}
	else if(entity.direction == 1){
		if((currenttime - entity.animation.timer[3]) > 15){
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
			entity.animation.timer[3] = currenttime;
		}
	}
	else if(entity.direction == 2){
		if((currenttime - entity.animation.timer[3]) > 15){
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
			entity.animation.timer[3] = currenttime;
		}
	}
	else if(entity.direction == 3){
		if((currenttime - entity.animation.timer[3]) > 15){
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
			entity.animation.timer[3] = currenttime;
		}
	}
	else if(entity.direction == 4){
		if((currenttime - entity.animation.timer[3]) > 15){
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
			entity.animation.timer[3] = currenttime;
		}
	}
	if(entity.restofway == 0 && entity.direction != -1){
		entity.direction = 0;
	}
	return entity;
}


object playerMoving(object prect, int *trafficbans, const Uint8 *keyboardState){
	if((keyboardState[SDL_SCANCODE_UP])||(keyboardState[SDL_SCANCODE_W]))
		if(prect.direction == 0 && trafficbans[0] == 0){
			prect.direction = 1;
			prect.restofway = cellsize;
			prect.animation.timer[3] = currenttime;
		}

	if((keyboardState[SDL_SCANCODE_DOWN])||(keyboardState[SDL_SCANCODE_S]))
		if(prect.direction == 0 && trafficbans[2] == 0){
			prect.direction = 3;
			prect.restofway = cellsize;
			prect.animation.timer[3] = currenttime;
		}

	if((keyboardState[SDL_SCANCODE_LEFT])||(keyboardState[SDL_SCANCODE_A]))
		if(prect.direction == 0 && trafficbans[3] == 0){
			prect.direction = 4;
			prect.restofway = cellsize;
			prect.animation.timer[3] = currenttime;
		}

	if((keyboardState[SDL_SCANCODE_RIGHT])||(keyboardState[SDL_SCANCODE_D]))
		if(prect.direction == 0 && trafficbans[1] == 0){
			prect.direction = 2;
			prect.restofway = cellsize;
			prect.animation.timer[3] = currenttime;
		}
	return prect;
}


container *attack(int attackernumber, container **headcontainer){
	extraContainer = *headcontainer;
	extraObject = getlist(&extraContainer, attackernumber)->data;
	if(currenttime - getlist(&extraContainer, attackernumber)->data.attackrecharge >=
	   getlist(&extraContainer, attackernumber)->data.weapon.recharge * 5
	&& getlist(&extraContainer, attackernumber)->data.LVL != -1){
		for(j = 0; j < element_count(&extraContainer); j++){
			if(abs(extraObject.rectangle.x - getlist(&extraContainer, j)->data.rectangle.x) <= 32
			&& abs(extraObject.rectangle.y - getlist(&extraContainer, j)->data.rectangle.y) <= 32
			&& (extraObject.ID != getlist(&extraContainer, j)->data.ID) && getlist(&extraContainer, j)->data.HP > 0){
				getlist(&extraContainer, j)->data.HP -= extraObject.DMG + extraObject.weapon.DMG;
				getlist(&extraContainer, j)->data.takendamage = extraObject.DMG + extraObject.weapon.DMG;
				getlist(&extraContainer, attackernumber)->data.weapon.animation.angle = 0;
				getlist(&extraContainer, j)->data.animation.timer[0] = currenttime;
				getlist(&extraContainer, j)->data.animation.timer[1] = currenttime;
				getlist(&extraContainer, attackernumber)->data.attackrecharge = currenttime;
				getlist(&extraContainer, j)->data.damageEffectRect.x = getlist(&extraContainer, j)->data.rectangle.x;
				getlist(&extraContainer, j)->data.damageEffectRect.y = getlist(&extraContainer, j)->data.rectangle.y;
				getlist(&extraContainer, j)->data.animation.animationRect.x = getlist(&extraContainer, j)->data.rectangle.x + cellsize/2;
				getlist(&extraContainer, j)->data.animation.animationRect.y = getlist(&extraContainer, j)->data.rectangle.y + cellsize/2;
				getlist(&extraContainer, j)->data.animation.animationRect.w = 8 * digit_count(getlist(&extraContainer, j)->data.takendamage);
				getlist(&extraContainer, j)->data.animation.animationRect.h = 12;
				if(extraObject.ID == -1 && getlist(&extraContainer, j)->data.relation > -1) getlist(&extraContainer, j)->data.relation--;
				if(getlist(&extraContainer, j)->data.HP <= 0){
					getlist(&extraContainer, j)->data.animation.timer[2] = currenttime;
					getlist(&extraContainer, j)->data.LVL = -1;
					getlist(&extraContainer, j)->data.direction = -1;
					getlist(&extraContainer, j)->data.texture = getlist(&extraContainer, j)->data.death;
				}
			}
		}
		getlist(&extraContainer, attackernumber)->data.weapon.animation.angle = 0;
	}
	return *headcontainer;
}


container *loadmap(container **headcontainer, SDL_Rect bgrect, char *path){
	extraContainer = *headcontainer;
	extraTexture = IMG_LoadTexture(mainRender,"Textures/stan.png");
	extraObject.rectangle.h = cellsize;
	extraObject.rectangle.w = cellsize;
	extraStream = fopen(path, "r");
	fscanf(extraStream, "%c", &extraSymbol);
	while(feof(extraStream) == 0){
		while(extraSymbol != '\\'){
			if(extraSymbol == 'x'){
				extraObject.rectangle.x = bgrect.x + extravar * cellsize;
				extraObject.rectangle.y = bgrect.y + extravar2 * cellsize;
				extraObject.DMG = -1;
				extraObject.HP = -1;
				extraObject.LVL = 0;
				extraObject.direction = -1;
				extraObject.ID = element_count(&extraContainer);
				extraObject.texture = extraTexture;
				addlast(&extraContainer, extraObject);
			}
			extravar++;
			fscanf(extraStream, "%c", &extraSymbol);
		}
		extravar2++;
		extravar = -1;
		fscanf(extraStream, "%c", &extraSymbol);
	}
	extravar++;
	fclose(extraStream);
	return extraContainer;
}


void attackanimation(object *attacker, SDL_RendererFlip flip){
	extraPoint = attacker->weapon.animation.center;
	extraRect = attacker->weapon.rectangle;
	extraRect.x = attacker->rectangle.x + 8;
	extraRect.y = attacker->rectangle.y + 16;
	SDL_RenderCopyEx(mainRender, attacker->weapon.texture, NULL,
				 	 &extraRect, attacker->weapon.animation.angle,
					 &extraPoint, flip);
}


void maingame(){
	//rendering unalive
	for(i = 0; i < element_count(&objects) ; i++){
		extraRect = getlist(&objects, i)->data.rectangle;
		if(getlist(&objects, i)->data.LVL == -1)SDL_RenderCopy(mainRender, getlist(&objects, i)->data.texture, NULL, &extraRect);
	}


	//rendering alive
	for(i = 0; i < element_count(&objects) ; i++){
		extraRect = getlist(&objects, i)->data.rectangle;
		if(getlist(&objects, i)->data.LVL != -1)SDL_RenderCopy(mainRender, getlist(&objects, i)->data.texture, NULL, &extraRect);
	}


	//player attack
	if(keystate[SDL_SCANCODE_F]){
		getlist(&objects, 0)->data.animation.timer[4] = currenttime;
		getlist(&objects, 0)->data.weapon.using = 1;
	}
	trafficbans = calculateTrafficBans(getlist(&objects, 0)->data, &objects);
	getlist(&objects, 0)->data = playerMoving(getlist(&objects, 0)->data, trafficbans, keystate);


	//action cycle
	for(i = 0; i < element_count(&objects); i++){


		//entities moving
		getlist(&objects, i)->data = entityMoving(getlist(&objects, i)->data, &objects, i);


		//rendering effects
		if(getlist(&objects, i)->data.takendamage > 0){


			//damage effect
			if(currenttime - getlist(&objects, i)->data.animation.timer[0] < 250){
				extraRect = getlist(&objects, i)->data.damageEffectRect;
				SDL_RenderCopy(mainRender, getlist(&objects, i)->data.damageEffectTexture, NULL, &extraRect);
			}


			//damage indicator
			if(getlist(&objects, i)->data.takendamage > 0){
				itoa(getlist(&objects, i)->data.takendamage, damageIndicator, 100);
				if(currenttime - getlist(&objects, i)->data.animation.timer[1] > 15){
					getlist(&objects, i)->data.animation.animationRect.y -= 2;
					getlist(&objects, i)->data.animation.timer[1] = currenttime;
				}
				extraRect = getlist(&objects, i)->data.animation.animationRect;
				extraTexture = newtext(damageIndicator, mainRender, 255, 255, 255);
				SDL_RenderCopy(mainRender, extraTexture, NULL, &extraRect);
				SDL_DestroyTexture(extraTexture);

				if(currenttime - getlist(&objects, i)->data.animation.timer[0] >= 800){
					getlist(&objects, i)->data.takendamage = 0;
				}
			}
		}

		//attacks of entities
		if(getlist(&objects, i)->data.DMG != -1){
			if(abs(getlist(&objects, 0)->data.rectangle.x - getlist(&objects, i)->data.rectangle.x) <= 32
			&& abs(getlist(&objects, 0)->data.rectangle.y - getlist(&objects, i)->data.rectangle.y) <= 32
			&& getlist(&objects, 0)->data.ID == -1 && i != 0 && getlist(&objects, i)->data.relation == -1
			&& getlist(&objects, i)->data.weapon.using == 0)
			{
				getlist(&objects, i)->data.animation.timer[4] = currenttime;
				getlist(&objects, i)->data.weapon.using = 1;
			}
		}

		if(getlist(&objects, i)->data.weapon.using == 1
		&& currenttime - getlist(&objects, i)->data.animation.timer[4] >= getlist(&objects, i)->data.weapon.attackdelay * 1000){
			objects = attack(i, &objects);
			getlist(&objects, i)->data.weapon.using = 0;
		}





		//attack animation
		if(getlist(&objects, i)->data.weapon.animation.angle < 360){
			if(currenttime - getlist(&objects, i)->data.attackrecharge >= 15){
				getlist(&objects, i)->data.attackrecharge = currenttime;
				getlist(&objects, i)->data.weapon.animation.angle += 1440/getlist(&objects, i)->data.weapon.recharge;
			}
			extraObject = getlist(&objects, i)->data;
			attackanimation(&extraObject, swordflip);
		}


		//removal of corpses
		if(currenttime - getlist(&objects, i)->data.animation.timer[2] >= 2000 && getlist(&objects, i)->data.LVL == -1){
			delelement(&objects, i);

		}
	}

}
