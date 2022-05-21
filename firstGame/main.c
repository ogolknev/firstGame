#include "includes.h"



int main(int argc, char* argv[]){
	if(initSDL() == 1){
		return 0;
	}

	SettingsConf = malloc(sizeof(Settings));
	loadSettings();


	main_window = SDL_CreateWindow("firstGame", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			screen_width, screen_height, full_screen);

	SDL_GetWindowSize(main_window, &screen_width, &screen_height);
	cellsize = screen_height/20;


	if(main_window == NULL){
		printf("SDL could not create window! SDL error: %s\n", SDL_GetError());
		return 1;
	}
	main_render = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(main_render == NULL){
		printf("SDL could not create render! SDL error: %s\n", SDL_GetError());
		return 1;
	}
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);

	main_event = malloc(sizeof(SDL_Event));
	unmoving = calloc(4,sizeof(int));
	main_font = TTF_OpenFont("fonts/GangSmallYuxian.ttf", 100);

	objects = newContainer();

	loadSounds();
	loadTextures();
	loadItems();
	loadObjects();


	sword_flip = SDL_FLIP_VERTICAL;

	addToList(&objects, player, 0);

	multiSpawn(&objects, bush0, background_rct, 10);
	multiSpawn(&objects, bush1, background_rct, 10);
	multiSpawn(&objects, bush2, background_rct, 10);
	multiSpawn(&objects, bush3, background_rct, 10);
	objects = loadMap(&objects, background_rct, "maps/map1.txt");

	itemSpawn(GMS, &objects, background_rct, 3, 10);
	itemSpawn(souls_slayer, &objects, background_rct, 5, 10);
	itemSpawn(blood_scythe, &objects, background_rct, 7, 10);
	itemSpawn(blood_sword, &objects, background_rct, 9, 10);
	multiSpawn(&objects, goblin, background_rct, 27);
	multiSpawn(&objects, alien, background_rct, 5);
	printf("%i\n", elementCount(&objects));

	key_state = SDL_GetKeyboardState(NULL);



	SDL_SetRenderDrawColor(main_render, 0, 0 ,0 ,0);
	printf("%i",Mix_AllocateChannels(-1));

	while(run == 1 && main_event->type != SDL_QUIT ){
		SDL_PollEvent(main_event);
		SDL_PumpEvents();
		SDL_RenderClear(main_render);

		mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

		current_time = SDL_GetTicks64();

		if(key_state[SDL_SCANCODE_G]){
			layer = 1;
		}

		if(layer == 0) pauseMenu();
		if(layer == 1) game();
		if(layer == 2) settingsMenu();
		if(layer == -1) run = 0;
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
	free(SettingsConf);
	SDL_DestroyRenderer(main_render);
	SDL_DestroyWindow(main_window);
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}
