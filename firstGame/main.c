#include "includes.h"



int main(int argc, char* argv[]){
	if(initSDL() == 1){
		return 0;
	}
	mainWindow = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
								  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	unmoving = calloc(4,sizeof(int));
	mainFont = TTF_OpenFont("fonts/bauhaus.ttf", 200);

	load_textures();
	load_items();


	objects = newcontainer();
	SDL_RendererFlip swordflip = SDL_FLIP_VERTICAL;

	object player;
	player.LVL = 0;
	player.HP = 15;
	player.DMG = 2;
	player.ID = -1;
	player.direction = 0;
	player.attackrecharge = 100;
	player.restofway = 0;
	player.takendamage = 0;
	player.damageEffectTexture = bloodTexture;
	player.damageEffectRect = bloodRect;
	player.rectangle = playerRect;
	player.texture = playerTexture;
	player.weapon = initial_sword;
	player.weapon.animation.angle = 360;
	player.movespeed = 250;
	player.death = goblinDeath;
	player.relation = 1;
	player.pxpart = 0;
	player.pxcount = 0;


	addtolist(&objects, player, 0);


	object goblin;
	goblin.HP = 5;
	goblin.LVL = 0;
	goblin.DMG = 0;
	goblin.attackrecharge = 100;
	goblin.direction = 0;
	goblin.restofway = 0;
	goblin.takendamage = 0;
	goblin.rectangle = goblinRect;
	goblin.texture = goblinTexture;
	goblin.weapon = goblin_stick;
	goblin.damageEffectTexture = bloodTexture;
	goblin.damageEffectRect = bloodRect;
	goblin.death = goblinDeath;
	goblin.weapon.animation.angle = 360;
	goblin.movespeed = 200;
	goblin.relation = 0;
	goblin.pxpart = 0;
	goblin.pxcount = 0;


	object stan;
	stan.HP = -1;
	stan.LVL = 0;
	stan.DMG = -1;
	stan.direction = -1;
	stan.restofway = 0;
	stan.takendamage = 0;
	stan.texture = stan0_Txtr;
	stan.rectangle = stan0_Rct;


	objects = loadmap(&objects, backgroundRect, "maps/map1.txt");
	multiSpawn(mainRender, &objects, goblin, backgroundRect, 27);
	multiSpawn(mainRender, &objects, stan, backgroundRect, 0);
	printf("%i\n", element_count(&objects));

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	SDL_SetRenderDrawColor(mainRender, 0, 0 ,0 ,0);

	while(run == 1 && mainEvent->type != SDL_QUIT){
		SDL_PollEvent(mainEvent);
		SDL_PumpEvents();
		SDL_RenderClear(mainRender);
		SDL_RenderCopy(mainRender, backgroundTexture, NULL, &backgroundRect);

		currenttime = SDL_GetTicks();

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
		if(keystate[SDL_SCANCODE_F] && getlist(&objects, 0)->data.attackrecharge == 0){
			objects = preattack(0, &objects);
		}
		trafficbans = calculateTrafficBans(getlist(&objects, 0)->data, &objects);
		getlist(&objects, 0)->data = playerMoving(getlist(&objects, 0)->data, trafficbans, keystate);


		//action cycle
		for(i = 0; i < element_count(&objects); i++){


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
				if(SDL_GetTicks() - getlist(&objects, i)->data.animation.timer[1] > 300){
					itoa(getlist(&objects, i)->data.takendamage, damageIndicator, 10);
					getlist(&objects, i)->data.animation.animationRect.y--;
					extraRect = getlist(&objects, i)->data.animation.animationRect;
					extraTexture = newtext(damageIndicator, mainRender, 255, 255, 255);
					SDL_RenderCopy(mainRender, extraTexture, NULL, &extraRect);
					SDL_DestroyTexture(extraTexture);
					if(SDL_GetTicks() - getlist(&objects, i)->data.animation.timer[1] >= 50000){
						getlist(&objects, i)->data.takendamage = 0;
					}
				}
			}

			//attacks of entities
			if(getlist(&objects, i)->data.DMG != -1){
				if(abs(getlist(&objects, 0)->data.rectangle.x - getlist(&objects, i)->data.rectangle.x) <= 32
				&& abs(getlist(&objects, 0)->data.rectangle.y - getlist(&objects, i)->data.rectangle.y) <= 32
				&& getlist(&objects, 0)->data.ID == -1 && i != 0 && getlist(&objects, i)->data.relation == -1)
				{
					objects = preattack(i, &objects);
				}
			}

			//attack animation
			if(getlist(&objects, i)->data.weapon.animation.angle < 360 && getlist(&objects, i)->data.attackrecharge > 0){
				extraObject = getlist(&objects, i)->data;
				getlist(&objects, i)->data.weapon.animation.angle
				= attackanimation(&extraObject, swordflip, getlist(&objects, i)->data.weapon.animation.angle);
			}


			//removal of corpses
			if(getlist(&objects, i)->data.animation.timer[2] > 0) getlist(&objects, i)->data.animation.timer[2]--;
			if(getlist(&objects, i)->data.animation.timer[2] == 0 && getlist(&objects, i)->data.LVL == -1){
				delelement(&objects, i);

			}
		}

		SDL_RenderPresent(mainRender);
	}
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}
