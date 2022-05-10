#include "items.h"

void load_items(){

	//weapons
	initial_sword.ID = 0;
	initial_sword.DMG = 1;
	initial_sword.recharge = 150;
	initial_sword.texture = weapon0_Txtr;
	initial_sword.rectangle = weapon0_Rct;
	initial_sword.animation.center.x = cellsize / 2;
	initial_sword.animation.center.y = 0;
	initial_sword.animation.angle = 0;

	goblin_stick.ID = 1;
	goblin_stick.DMG = 1;
	goblin_stick.recharge = 200;
	goblin_stick.texture = weapon1_Txtr;
	goblin_stick.rectangle = weapon1_Rct;
	goblin_stick.animation.center.x = cellsize / 2;
	goblin_stick.animation.center.y = 0;
	goblin_stick.animation.angle = 0;

	GMS.ID = 2;
	GMS.DMG = 15;
	GMS.recharge = 250;
	GMS.texture = weapon2_Txtr;
	GMS.rectangle = weapon2_Rct;
	GMS.animation.center.x = cellsize / 2;
	GMS.animation.center.y = 0;
	GMS.animation.angle = 0;

}
