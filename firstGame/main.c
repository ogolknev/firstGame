#include "includes.h"



int main(int argc, char* argv[]){
	if(initSDL() == 1){
		return 0;
	}
	main_window = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
								  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(main_window == NULL){
		printf("SDL could not create window! SDL error: %s\n", SDL_GetError());
		return 1;
	}
	main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(main_render == NULL){
		printf("SDL could not create render! SDL error: %s\n", SDL_GetError());
		return 1;
	}
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT,2,2048);
	main_event = malloc(sizeof(SDL_Event));
	unmoving = calloc(4,sizeof(int));
	main_font = TTF_OpenFont("fonts/GangSmallYuxian.ttf", 100);

	loadSounds();
	loadTextures();
	loadItems();
	loadObjects();

	objects = newContainer();
	sword_flip = SDL_FLIP_VERTICAL;

	addToList(&objects, player, 0);

	objects = loadMap(&objects, background_rct, "maps/map1.txt");
	itemSpawn(GMS, &objects, background_rct, 3, 10);
	itemSpawn(souls_slayer, &objects, background_rct, 5, 10);
	itemSpawn(hand, &objects, background_rct, 7, 10);
	multiSpawn(&objects, goblin, background_rct, 27);
	multiSpawn(&objects, alien, background_rct, 5);
	printf("%i\n", elementCount(&objects));

	key_state = SDL_GetKeyboardState(NULL);



	SDL_SetRenderDrawColor(main_render, 0, 0 ,0 ,0);


	while(run == 1 && main_event->type != SDL_QUIT ){
		SDL_PollEvent(main_event);
		SDL_PumpEvents();
		SDL_RenderClear(main_render);

		mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

		current_time = SDL_GetTicks64();

		if(key_state[SDL_SCANCODE_G]){
			layer = 1;
		}
		if(key_state[SDL_SCANCODE_ESCAPE]){
			layer = 0;
		}

		if(layer == 0) pauseMenu();
		if(layer == 1) game();
/*
		if(element_count(&objects) < 130){
			if(limitedRandom(0,2,element_count(&objects))){
				spawn(goblin, &objects, backgroundRect, 2,2);
			}
			else{
				spawn(alien, &objects, backgroundRect, 2,2);
			}
		}
*/


		SDL_RenderPresent(main_render);
	}
	SDL_DestroyRenderer(main_render);
	SDL_DestroyWindow(main_window);
	SDL_Quit();

	return 0;
}
