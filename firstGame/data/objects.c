#include "objects.h"

void loadObjects(){

	//entities
	player.LVL = 0;
	player.HP = 30;
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
	player.movespeed = 400;
	player.death = goblinDeath;
	player.relation = 1;
	player.pxpart = 0;
	player.pxcount = 0;

	goblin.HP = 20;
	goblin.LVL = 1;
	goblin.DMG = 0;
	goblin.ID = 9;
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
	goblin.movespeed = 370;
	goblin.relation = 0;
	goblin.pxpart = 0;
	goblin.pxcount = 0;

	alien.HP = 50;
	alien.LVL = 3;
	alien.DMG = 5;
	alien.ID = 1;
	alien.attackrecharge = 100;
	alien.direction = 0;
	alien.restofway = 0;
	alien.takendamage = 0;
	alien.rectangle = alienRect;
	alien.texture = alienTexture;
	alien.weapon = hand;
	alien.damageEffectTexture = bloodTexture;
	alien.damageEffectRect = bloodRect;
	alien.death = goblinDeath;
	alien.weapon.animation.angle = 360;
	alien.movespeed = 380;
	alien.relation = 0;
	alien.pxpart = 0;
	alien.pxcount = 0;



	//objects
	stan.HP = -1;
	stan.LVL = 0;
	stan.DMG = -1;
	stan.ID = 2;
	stan.direction = -1;
	stan.restofway = 0;
	stan.takendamage = 0;
	stan.texture = stan0_Txtr;
	stan.rectangle = stan0_Rct;

	barrel.HP = 20;
	barrel.LVL = -3;
	barrel.DMG = -1;
	barrel.ID = 3;
	barrel.direction = -1;
	barrel.restofway = 0;
	barrel.takendamage = 0;
	barrel.texture = barrel0_Txtr;
	barrel.death = barrel0_death;
	barrel.rectangle = barrel0_Rct;
	barrel.weapon.ID = -1;


	item_object.HP = -1;
	item_object.LVL = -2;
	item_object.XP = 0;
	item_object.DMG = -1;
	item_object.ID = 4;
	item_object.direction = -1;
	item_object.restofway = 0;
	item_object.takendamage = 0;
	item_object.rectangle = item_Rct;
	item_object.movespeed = 0;

	bush0.HP = -1;
	bush0.LVL = -1;
	bush0.DMG = -1;
	bush0.ID = 5;
	bush0.direction = -1;
	bush0.restofway = 0;
	bush0.takendamage = 0;
	bush0.texture = bush0_txtr;
	bush0.rectangle = bush0_rct;

	bush1.HP = -1;
	bush1.LVL = -1;
	bush1.DMG = -1;
	bush1.ID = 6;
	bush1.direction = -1;
	bush1.restofway = 0;
	bush1.takendamage = 0;
	bush1.texture = bush1_txtr;
	bush1.rectangle = bush1_rct;

	bush2.HP = -1;
	bush2.LVL = -1;
	bush2.DMG = -1;
	bush2.ID = 7;
	bush2.direction = -1;
	bush2.restofway = 0;
	bush2.takendamage = 0;
	bush2.texture = bush2_txtr;
	bush2.rectangle = bush2_rct;

	bush3.HP = -1;
	bush3.LVL = -1;
	bush3.DMG = -1;
	bush3.ID = 8;
	bush3.direction = -1;
	bush3.restofway = 0;
	bush3.takendamage = 0;
	bush3.texture = bush3_txtr;
	bush3.rectangle = bush3_rct;

}
