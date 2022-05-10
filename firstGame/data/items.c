#include "items.h"

void load_items(){

	//weapons
	hand.ID = 3;
	hand.DMG = 0;
	hand.recharge = 70;
	hand.attackdelay = 0.3;
	hand.texture = kick_Txtr;
	hand.rectangle = hand_Rct;
	hand.animation.center.x = cellsize / 2;
	hand.animation.center.y = 0;
	hand.animation.angle = 360;
	hand.using = 0;

	initial_sword.ID = 0;
	initial_sword.DMG = 3;
	initial_sword.recharge = 100;
	initial_sword.attackdelay = 0.1;
	initial_sword.texture = weapon0_Txtr;
	initial_sword.rectangle = weapon0_Rct;
	initial_sword.animation.center.x = cellsize / 2;
	initial_sword.animation.center.y = 0;
	initial_sword.animation.angle = 360;
	initial_sword.using = 0;

	goblin_stick.ID = 1;
	goblin_stick.DMG = 1;
	goblin_stick.recharge = 200;
	goblin_stick.attackdelay = 0.3;
	goblin_stick.texture = weapon1_Txtr;
	goblin_stick.rectangle = weapon1_Rct;
	goblin_stick.animation.center.x = cellsize / 2;
	goblin_stick.animation.center.y = 0;
	goblin_stick.animation.angle = 360;
	goblin_stick.using = 0;

	GMS.ID = 2;
	GMS.DMG = 30;
	GMS.recharge = 250;
	GMS.attackdelay = 0.5;
	GMS.texture = weapon2_Txtr;
	GMS.rectangle = weapon2_Rct;
	GMS.animation.center.x = cellsize / 2;
	GMS.animation.center.y = 0;
	GMS.animation.angle = 360;
	GMS.using = 0;

	souls_slayer.ID = 4;
	souls_slayer.DMG = 257;
	souls_slayer.recharge = 50;
	souls_slayer.attackdelay = 0.1;
	souls_slayer.texture = weapon4_Txtr;
	souls_slayer.rectangle = weapon4_Rct;
	souls_slayer.animation.center.x = cellsize / 2;
	souls_slayer.animation.center.y = 0;
	souls_slayer.animation.angle = 360;
	souls_slayer.using = 0;
}
