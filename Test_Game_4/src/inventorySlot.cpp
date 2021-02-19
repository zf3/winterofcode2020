#include "inventorySlot.hpp"

#include "basicChar.hpp"

//type = 1 - weapon, type = 2 - armor
void inventorySlot::include(weapon obj) {
	w = obj;
	type = 1;
	active = true;
}
void inventorySlot::include(armor obj) {
	a = obj;
	type = 2;
	active = true;
}
void inventorySlot::apply(basicChar *target) {
	if(active) {
		if(type == 1) {
			target->spd/=target->weaponM;
			target->atk2Spd/=target->weaponM;
			w.apply(target);
			target->eqpWeapon = w;
		}
		if(type == 2) {
			target->spd/=target->armorM;
			target->atk2Spd/=target->armorM;
			float tHP = target->hp;
			if(tHP == 0) tHP = a.maxHP;
			a.apply(target);
			target->eqpArmor = a;
			target->hp = min(tHP, a.maxHP);
		}
	}
}
inventorySlot::inventorySlot() {
	active = false;
	used = false;
}