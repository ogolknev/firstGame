#include "textures.h"

void load_textures(){


	//background
	backgroundTexture = IMG_LoadTexture(mainRender,"textures/backgrounds/background_0.png");
	backgroundRect.h = 640;
	backgroundRect.w = 640;
	backgroundRect.x = (SCREEN_WIDTH - backgroundRect.w) / 2;
	backgroundRect.y = (SCREEN_HEIGHT - backgroundRect.h) / 2;


	//unalive
	stan0_Txtr = IMG_LoadTexture(mainRender,"textures/stan.png");
	stan0_Rct.h = cellsize;
	stan0_Rct.w = cellsize;


	//entities
	playerTexture = IMG_LoadTexture(mainRender,"textures/helmet1.png");
	playerRect.h = cellsize;
	playerRect.w = cellsize;
	playerRect.x = backgroundRect.x + cellsize * 10;
	playerRect.y = backgroundRect.y + cellsize * 10;

	goblinTexture = IMG_LoadTexture(mainRender, "textures/minigoblin.png");
	goblinDeath = IMG_LoadTexture(mainRender, "textures/deadgoblin.png");
	goblinRect.h = cellsize;
	goblinRect.w = cellsize;


	//effects
	bloodTexture = IMG_LoadTexture(mainRender,"textures/blood.png");
	bloodRect.h = cellsize;
	bloodRect.w = cellsize;


	//weapons
	weapon0_Txtr = IMG_LoadTexture(mainRender, "textures/sword.png");
	weapon0_Rct.h = cellsize;
	weapon0_Rct.w = cellsize;

	weapon1_Txtr = IMG_LoadTexture(mainRender, "textures/goblin_stick.png");
	weapon1_Rct.h = cellsize;
	weapon1_Rct.w = cellsize;

	weapon2_Txtr = IMG_LoadTexture(mainRender, "textures/MEGGGA_GGGOOOOBLIN_STTTTIIICKKKK.png");
	weapon2_Rct.h = cellsize;
	weapon2_Rct.w = cellsize;


}
