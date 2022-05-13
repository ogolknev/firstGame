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
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT,2,2048);
	mainEvent = malloc(sizeof(SDL_Event));
	damageIndicator = malloc(20*sizeof(char));
	unmoving = calloc(4,sizeof(int));
	mainFont = TTF_OpenFont("fonts/bauhaus.ttf", 100);

	load_sounds();
	load_textures();
	load_items();
	load_objects();

	objects = newcontainer();
	swordflip = SDL_FLIP_VERTICAL;

	addtolist(&objects, player, 0);

	objects = loadmap(&objects, backgroundRect, "maps/map1.txt");
	item_spawn(GMS, &objects, backgroundRect, 3, 10);
	item_spawn(souls_slayer, &objects, backgroundRect, 5, 10);
	item_spawn(hand, &objects, backgroundRect, 7, 10);
	multiSpawn(&objects, goblin, backgroundRect, 27);
	multiSpawn(&objects, alien, backgroundRect, 5);
	printf("%i\n", element_count(&objects));

	keystate = SDL_GetKeyboardState(NULL);


	SDL_Texture *resume = newtext("resume", mainRender, 0, 0, 0);
	SDL_SetRenderDrawColor(mainRender, 0, 0 ,0 ,0);


	while(run == 1 && mainEvent->type != SDL_QUIT ){
		SDL_PollEvent(mainEvent);
		SDL_PumpEvents();
		SDL_RenderClear(mainRender);

		mousestate = SDL_GetMouseState(&x, &y);

		currenttime = SDL_GetTicks64();

		if(keystate[SDL_SCANCODE_G]){
			layer = 1;
		}
		if(keystate[SDL_SCANCODE_ESCAPE]){
			layer = 0;
		}

		if(layer == 0) mainmenu(resume);
		if(layer == 1) maingame();
/*
		if(element_count(&objects) < 130){
			if(limitedrandom(0,2,element_count(&objects))){
				spawn(goblin, &objects, backgroundRect, 2,2);
			}
			else{
				spawn(alien, &objects, backgroundRect, 2,2);
			}
		}
*/


		SDL_RenderPresent(mainRender);
	}
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}
