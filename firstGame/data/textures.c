#include "textures.h"

Container *loadTextures(){

	for(int i = 0; i < elementCount(&objects); i++){
		SDL_DestroyTexture(getList(&objects, i)->data.damageEffectTexture);
		SDL_DestroyTexture(getList(&objects, i)->data.death);
		SDL_DestroyTexture(getList(&objects, i)->data.texture);
		SDL_DestroyTexture(getList(&objects, i)->data.weapon.texture);
	}

	Container *textures_list = newContainer();

	//interface
	button512_txtr = IMG_LoadTexture(main_render,"textures/512.png");
	button512_rct.h = cellsize * 2;
	button512_rct.w = cellsize * 16;
	button512_state.h = 64 * 8;
	button512_state.w = 512 * 8;
	button512_state.x = 0;
	button512_state.y = 0;

	//background
	background_txtr = IMG_LoadTexture(main_render,"textures/backgrounds/background_0.png");
	background_rct.h = cellsize * 20;
	background_rct.w = cellsize * 20;
	background_rct.x = (screen_width - background_rct.w) / 2;
	background_rct.y = (screen_height - background_rct.h) / 2;


	//unalive
	stan0_Txtr = IMG_LoadTexture(main_render,"textures/stan.png");
	stan0_Rct.h = cellsize;
	stan0_Rct.w = cellsize;
	txtr_object.ID = 2;
	txtr_object.texture = stan0_Txtr;
	txtr_object.rectangle = stan0_Rct;
	addToList(&textures_list, txtr_object, 0);

	barrel0_Txtr = IMG_LoadTexture(main_render,"textures/barrel.png");
	barrel0_death = IMG_LoadTexture(main_render,"textures/destroyed_barrel.png");
	barrel0_Rct.h = cellsize;
	barrel0_Rct.w = cellsize;
	txtr_object.ID = 3;
	txtr_object.texture = barrel0_Txtr;
	txtr_object.death = barrel0_death;
	txtr_object.rectangle = barrel0_Rct;
	addLast(&textures_list, txtr_object);
	txtr_object.ID = -2;
	txtr_object.texture = barrel0_death;

	addLast(&textures_list, txtr_object);

	bush0_txtr = IMG_LoadTexture(main_render,"textures/1bush.png");
	bush0_rct.h = cellsize;
	bush0_rct.w = cellsize;
	txtr_object.ID = 5;
	txtr_object.texture = bush0_txtr;
	txtr_object.rectangle = bush0_rct;
	addLast(&textures_list, txtr_object);

	bush1_txtr = IMG_LoadTexture(main_render,"textures/2bush.png");
	bush1_rct.h = cellsize;
	bush1_rct.w = cellsize;
	txtr_object.ID = 6;
	txtr_object.texture = bush1_txtr;
	txtr_object.rectangle = bush1_rct;
	addLast(&textures_list, txtr_object);

	bush2_txtr = IMG_LoadTexture(main_render,"textures/3bush.png");
	bush2_rct.h = cellsize;
	bush2_rct.w = cellsize;
	txtr_object.ID = 7;
	txtr_object.texture = bush2_txtr;
	txtr_object.rectangle = bush2_rct;
	addLast(&textures_list, txtr_object);

	bush3_txtr = IMG_LoadTexture(main_render,"textures/4bush.png");
	bush3_rct.h = cellsize;
	bush3_rct.w = cellsize;
	txtr_object.ID = 8;
	txtr_object.texture = bush3_txtr;
	txtr_object.rectangle = bush3_rct;
	addLast(&textures_list, txtr_object);

	//effects
	bloodTexture = IMG_LoadTexture(main_render,"textures/blood.png");
	bloodRect.h = cellsize;
	bloodRect.w = cellsize;
	txtr_object.ID = -666;
	txtr_object.texture = bloodTexture;
	txtr_object.rectangle = bloodRect;
	addLast(&textures_list, txtr_object);

	//entities
	playerTexture = IMG_LoadTexture(main_render,"textures/helmet1.png");
	playerRect.h = cellsize;
	playerRect.w = cellsize;
	playerRect.x = background_rct.x + cellsize * 10;
	playerRect.y = background_rct.y + cellsize * 10;
	txtr_object.ID = -1;
	txtr_object.texture = playerTexture;
	txtr_object.death = goblinDeath;
	txtr_object.damageEffectTexture = bloodTexture;
	txtr_object.rectangle = playerRect;
	addLast(&textures_list, txtr_object);

	goblinTexture = IMG_LoadTexture(main_render, "textures/minigoblin.png");
	goblinDeath = IMG_LoadTexture(main_render, "textures/deadgoblin.png");
	goblinRect.h = cellsize;
	goblinRect.w = cellsize;
	txtr_object.ID = 9;
	txtr_object.texture = goblinTexture;
	txtr_object.death = goblinDeath;
	txtr_object.damageEffectTexture = bloodTexture;
	txtr_object.rectangle = goblinRect;
	addLast(&textures_list, txtr_object);

	alienTexture = IMG_LoadTexture(main_render, "textures/alien.png");
	alienRect.h = cellsize;
	alienRect.w = cellsize;
	txtr_object.ID = 1;
	txtr_object.texture = alienTexture;
	txtr_object.death = goblinDeath;
	txtr_object.damageEffectTexture = bloodTexture;
	txtr_object.rectangle = alienRect;
	addLast(&textures_list, txtr_object);


	//weapons
	kick_Txtr = IMG_LoadTexture(main_render, "textures/kick.png");
	hand_Rct.h = cellsize;
	hand_Rct.w = cellsize;
	txtr_object.weapon = hand;
	txtr_object.weapon.ID = -2;
	txtr_object.weapon.texture = kick_Txtr;
	txtr_object.weapon.rectangle = hand_Rct;
	addLast(&textures_list, txtr_object);

	weapon0_Txtr = IMG_LoadTexture(main_render, "textures/sword.png");
	weapon0_Rct.h = cellsize;
	weapon0_Rct.w = cellsize;
	txtr_object.weapon = initial_sword;
	txtr_object.weapon.ID = 4;
	txtr_object.weapon.texture = weapon0_Txtr;
	txtr_object.weapon.rectangle = weapon0_Rct;
	addLast(&textures_list, txtr_object);

	weapon1_Txtr = IMG_LoadTexture(main_render, "textures/goblin_stick.png");
	weapon1_Rct.h = cellsize;
	weapon1_Rct.w = cellsize;
	txtr_object.weapon = goblin_stick;
	txtr_object.weapon.ID = 1;
	txtr_object.weapon.texture = weapon1_Txtr;
	txtr_object.weapon.rectangle = weapon1_Rct;
	addLast(&textures_list, txtr_object);

	weapon2_Txtr = IMG_LoadTexture(main_render, "textures/MEGGGA_GGGOOOOBLIN_STTTTIIICKKKK.png");
	weapon2_Rct.h = cellsize;
	weapon2_Rct.w = cellsize;
	txtr_object.weapon = GMS;
	txtr_object.weapon.ID = 2;
	txtr_object.weapon.texture = weapon2_Txtr;
	txtr_object.weapon.rectangle = weapon2_Rct;
	addLast(&textures_list, txtr_object);

	weapon3_txtr = IMG_LoadTexture(main_render, "textures/blood_scythe.png");
	weapon3_rct.h = cellsize;
	weapon3_rct.w = cellsize;
	txtr_object.weapon = blood_scythe;
	txtr_object.weapon.ID = 3;
	txtr_object.weapon.texture = weapon3_txtr;
	txtr_object.weapon.rectangle = weapon3_rct;
	addLast(&textures_list, txtr_object);

	weapon4_txtr = IMG_LoadTexture(main_render, "textures/blood_sword.png");
	weapon4_rct.h = cellsize;
	weapon4_rct.w = cellsize;
	txtr_object.weapon = blood_sword;
	txtr_object.weapon.ID = 4;
	txtr_object.weapon.texture = weapon4_txtr;
	txtr_object.weapon.rectangle = weapon4_rct;
	addLast(&textures_list, txtr_object);

	weapon257_Txtr = IMG_LoadTexture(main_render, "textures/souls_slayer.png");
	weapon257_Rct.h = cellsize;
	weapon257_Rct.w = cellsize;
	txtr_object.weapon = souls_slayer;
	txtr_object.weapon.ID = 257;
	txtr_object.weapon.texture = weapon257_Txtr;
	txtr_object.weapon.rectangle = weapon257_Rct;
	addLast(&textures_list, txtr_object);

	return textures_list;
}

void initTextures(){
	Container *textures = loadTextures();
	for(int i = 0; i < elementCount(&objects); i++){
		for(int j = 0; j < elementCount(&textures); j++){
			if(getList(&objects,i)->data.ID == getList(&textures,j)->data.ID){
				getList(&objects,i)->data.texture = getList(&textures,j)->data.texture;
				getList(&objects,i)->data.death = getList(&textures,j)->data.death;
				getList(&objects,i)->data.damageEffectTexture = getList(&textures,j)->data.damageEffectTexture;
			}
			//if(getList(&objects,i)->data.HP == -2 && getList(&objects,i)->data.ID == getList(&objects,j)->data.ID){
			//	getList(&objects,i)->data.texture = getList(&textures,j)->data.death;
			//}
			if(getList(&objects,i)->data.weapon.ID == getList(&textures,j)->data.weapon.ID){
				getList(&objects,i)->data.weapon = getList(&textures,j)->data.weapon;
			}
			if(getList(&objects,i)->data.LVL == -2 && getList(&textures,j)->data.weapon.ID == getList(&objects,i)->data.weapon.ID)
			{
				getList(&objects,i)->data.texture = getList(&textures,j)->data.weapon.texture;
			}
		}
	}
}
