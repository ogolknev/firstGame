#include "objects.h"

void load_objects(){

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
	player.movespeed = 350;
	player.death = goblinDeath;
	player.relation = 1;
	player.pxpart = 0;
	player.pxcount = 0;

	goblin.HP = 20;
	goblin.LVL = 1;
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
	goblin.movespeed = 300;
	goblin.relation = 0;
	goblin.pxpart = 0;
	goblin.pxcount = 0;

	alien.HP = 50;
	alien.LVL = 3;
	alien.DMG = 5;
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
	alien.movespeed = 310;
	alien.relation = 0;
	alien.pxpart = 0;
	alien.pxcount = 0;



	//objects
	stan.HP = -1;
	stan.LVL = 0;
	stan.DMG = -1;
	stan.direction = -1;
	stan.restofway = 0;
	stan.takendamage = 0;
	stan.texture = stan0_Txtr;
	stan.rectangle = stan0_Rct;

	item_object.HP = -1;
	item_object.LVL = -2;
	item_object.XP = 0;
	item_object.DMG = -1;
	item_object.direction = -1;
	item_object.restofway = 0;
	item_object.takendamage = 0;
	item_object.rectangle = item_Rct;
	item_object.movespeed = 0;


}
