#include<floorItem.hpp>
void floorItem::include(basicChar obj, float xP, float yP) {
	type = 1;
	active = true;
	fIcon = obj.fIcon;
	x = xP;
	y = yP;
}
void floorItem::apply(basicChar *target) {
	if(active) {
		if(type == 1) {
			target->spd/=target->weaponM;
			target->atk2Spd/=target->weaponM;
			w.apply(target);
		}
		if(type == 2) {
			target->spd/=target->armorM;
			target->atk2Spd/=target->armorM;
			float tHP = target->hp;
			if(tHP == 0) tHP = a.maxHP;
			a.apply(target);
			target->hp = min(tHP, a.maxHP);
		}
	}
}
floorItem::floorItem() {
	active = false;
}