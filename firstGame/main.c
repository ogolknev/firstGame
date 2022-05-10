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
	damageIndicator = malloc(20*sizeof(char));
	unmoving = calloc(4,sizeof(int));
	mainFont = TTF_OpenFont("fonts/bauhaus.ttf", 500);

	load_textures();
	load_items();
	load_objects();

	objects = newcontainer();
	swordflip = SDL_FLIP_VERTICAL;

	addtolist(&objects, player, 0);

	objects = loadmap(&objects, backgroundRect, "maps/map1.txt");
	item_spawn(GMS, &objects, backgroundRect, 3, 5);
	item_spawn(souls_slayer, &objects, backgroundRect, 3, 7);
	item_spawn(hand, &objects, backgroundRect, 3, 7);
	multiSpawn(mainRender, &objects, goblin, backgroundRect, 27);
	multiSpawn(mainRender, &objects, alien, backgroundRect, 5);
	multiSpawn(mainRender, &objects, stan, backgroundRect, 0);
	printf("%i\n", element_count(&objects));

	keystate = SDL_GetKeyboardState(NULL);

	SDL_SetRenderDrawColor(mainRender, 0, 0 ,0 ,0);

	while(run == 1 && mainEvent->type != SDL_QUIT){
		SDL_PollEvent(mainEvent);
		SDL_PumpEvents();
		SDL_RenderClear(mainRender);
		SDL_RenderCopy(mainRender, backgroundTexture, NULL, &backgroundRect);

		currenttime = SDL_GetTicks64();

		maingame();

		SDL_RenderPresent(mainRender);
	}
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return 0;
}
