#include<floorItem.hpp>

#include "inventorySlot.hpp"
#include "basicChar.hpp"

void floorItem::include(basicChar *obj, float xP, float yP) {
	type = abs(rand()%2)+1;
	float quality = 1.0;

	a = obj->eqpArmor;
	quality = (rand()%11)/10.0+0.5;
	a.spdM*=quality;
	quality = (rand()%11)/10.0+0.5;
	a.maxHP*=quality;

	w = obj->eqpWeapon;
	quality = (rand()%11)/10.0+0.5;
	w.spdM*=quality;
	quality = (rand()%11)/10.0+0.5;
	w.dmg*=quality;
	quality = (rand()%11)/10.0+0.5;
	w.dmg2*=quality;
	quality = (rand()%11)/10.0+0.5;
	w.atkD*=quality;
	w.wCooldownM*=quality;
	quality = (rand()%11)/10.0+0.5;
	w.atkD2*=quality;
	w.wCooldownM2*=quality;

	w.icon = obj->eqpWeapon.icon;
	active = true;
	if(type == 1) {
		fIcon = obj->fIconW;
	}
	else {
		fIcon = obj->fIconA;
	}
	x = xP;
	y = yP;
}
void floorItem::include(inventorySlot *target) {
	type = target->type;
	active = target->active;
	if(type == 1) {
		w = target->w;
	}
	else {
		a = target->a;
	}
}
void floorItem::apply(inventorySlot *target) {
	target->a = a;
	target->w = w;
	target->active = active;
	target->type = type;
}
floorItem::floorItem() {
	active = false;
}