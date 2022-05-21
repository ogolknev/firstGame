#include "items.h"

void loadItems(){

	weapons = newContainer();

	//weapons
	hand.ID = -2;
	hand.DMG = 0;
	hand.recharge = 70;
	hand.attackdelay = 0.3;
	hand.texture = kick_Txtr;
	hand.rectangle = hand_Rct;
	hand.animation.center.x = cellsize / 2;
	hand.animation.center.y = 0;
	hand.animation.angle = 360;
	hand.using = 0;

	initial_sword.ID = 4;
	initial_sword.DMG = 3;
	initial_sword.recharge = 100;
	initial_sword.attackdelay = 0.1;
	initial_sword.texture = weapon0_Txtr;
	initial_sword.rectangle = weapon0_Rct;
	initial_sword.animation.center.x = cellsize / 2;
	initial_sword.animation.center.y = 0;
	initial_sword.animation.angle = 360;
	initial_sword.using = 0;
	weapon_object.weapon = initial_sword;
	addToList(&weapons, weapon_object, 0);

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
	weapon_object.weapon = goblin_stick;
	addLast(&weapons, weapon_object);

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
	weapon_object.weapon = GMS;
	addLast(&weapons, weapon_object);

	blood_scythe.ID = 3;
	blood_scythe.DMG = 66;
	blood_scythe.recharge = 99;
	blood_scythe.attackdelay = 0.3;
	blood_scythe.texture = weapon3_txtr;
	blood_scythe.rectangle = weapon3_rct;
	blood_scythe.animation.center.x = cellsize / 2;
	blood_scythe.animation.center.y = 0;
	blood_scythe.animation.angle = 360;
	blood_scythe.using = 0;
	weapon_object.weapon = blood_scythe;
	addLast(&weapons, weapon_object);

	blood_sword.ID = 4;
	blood_sword.DMG = 33;
	blood_sword.recharge = 66;
	blood_sword.attackdelay = 0.22;
	blood_sword.texture = weapon4_txtr;
	blood_sword.rectangle = weapon4_rct;
	blood_sword.animation.center.x = cellsize / 2;
	blood_sword.animation.center.y = 0;
	blood_sword.animation.angle = 360;
	blood_sword.using = 0;
	weapon_object.weapon = blood_sword;
	addLast(&weapons, weapon_object);

	souls_slayer.ID = 257;
	souls_slayer.DMG = 257;
	souls_slayer.recharge = 50;
	souls_slayer.attackdelay = 0.1;
	souls_slayer.texture = weapon257_Txtr;
	souls_slayer.rectangle = weapon257_Rct;
	souls_slayer.animation.center.x = cellsize / 2;
	souls_slayer.animation.center.y = 0;
	souls_slayer.animation.angle = 360;
	souls_slayer.using = 0;
}
