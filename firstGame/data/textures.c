#include "textures.h"

void loadTextures(){

	//interface
	button512_txtr = IMG_LoadTexture(main_render,"textures/512.png");
	button512_rct.h = 64;
	button512_rct.w = 512;
	button512_state.h = button512_rct.h * 8;
	button512_state.w = button512_rct.w * 8;
	button512_state.x = 0;
	button512_state.y = 0;

	//background
	background_txtr = IMG_LoadTexture(main_render,"textures/backgrounds/background_0.png");
	background_rct.h = 640;
	background_rct.w = 640;
	background_rct.x = (SCREEN_WIDTH - background_rct.w) / 2;
	background_rct.y = (SCREEN_HEIGHT - background_rct.h) / 2;


	//unalive
	stan0_Txtr = IMG_LoadTexture(main_render,"textures/stan.png");
	stan0_Rct.h = cellsize;
	stan0_Rct.w = cellsize;

	barrel0_Txtr = IMG_LoadTexture(main_render,"textures/barrel.png");
	barrel0_Rct.h = cellsize;
	barrel0_Rct.w = cellsize;


	//entities
	playerTexture = IMG_LoadTexture(main_render,"textures/helmet1.png");
	playerRect.h = cellsize;
	playerRect.w = cellsize;
	playerRect.x = background_rct.x + cellsize * 10;
	playerRect.y = background_rct.y + cellsize * 10;

	goblinTexture = IMG_LoadTexture(main_render, "textures/minigoblin.png");
	goblinDeath = IMG_LoadTexture(main_render, "textures/deadgoblin.png");
	goblinRect.h = cellsize;
	goblinRect.w = cellsize;

	alienTexture = IMG_LoadTexture(main_render, "textures/alien.png");
	alienRect.h = cellsize;
	alienRect.w = cellsize;


	//effects
	bloodTexture = IMG_LoadTexture(main_render,"textures/blood.png");
	bloodRect.h = cellsize;
	bloodRect.w = cellsize;


	//weapons
	kick_Txtr = IMG_LoadTexture(main_render, "textures/kick.png");
	hand_Rct.h = cellsize;
	hand_Rct.w = cellsize;

	weapon0_Txtr = IMG_LoadTexture(main_render, "textures/sword.png");
	weapon0_Rct.h = cellsize;
	weapon0_Rct.w = cellsize;

	weapon1_Txtr = IMG_LoadTexture(main_render, "textures/goblin_stick.png");
	weapon1_Rct.h = cellsize;
	weapon1_Rct.w = cellsize;

	weapon2_Txtr = IMG_LoadTexture(main_render, "textures/MEGGGA_GGGOOOOBLIN_STTTTIIICKKKK.png");
	weapon2_Rct.h = cellsize;
	weapon2_Rct.w = cellsize;

	weapon257_Txtr = IMG_LoadTexture(main_render, "textures/souls_slayer.png");
	weapon257_Rct.h = cellsize;
	weapon257_Rct.w = cellsize;


}
