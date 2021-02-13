#include<floorItem.hpp>

#include "inventorySlot.hpp"
#include "basicChar.hpp"

void floorItem::include(basicChar *obj, float xP, float yP) {
	type = abs(rand()%2)+1;
	a = obj->eqpArmor;
	w = obj->eqpWeapon;
	w.icon = obj->eqpWeapon.icon;
	active = true;
	fIcon = obj->fIcon;
	x = xP;
	y = yP;
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