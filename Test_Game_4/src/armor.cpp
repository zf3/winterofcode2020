#include "armor.hpp"
#include "basicChar.hpp"
using namespace std;
void armor::apply(basicChar *target) {
	target->hp = maxHP;
	target->maxHP = maxHP;
	target->hitbox = hitbox;
	target->spd = target->spd*spdM;
	target->armorM = spdM;
	target->atk2Spd = target->atk2Spd*spdM;
	target->body.setTexture(bTexture);
	target->bTexture = bTexture;
	target->bTexture2 = iTexture;
	target->fIcon = fIcon;
}
armor::armor(string a, string b, string ic, string fic, float sp, float hp, float hb) {
	icon.loadFromFile(ic);
	icon.setSmooth(true);
	fIcon.loadFromFile(fic);
	fIcon.setSmooth(true);
	bTexture.loadFromFile(a);
	bTexture.setSmooth(true);
	iTexture.loadFromFile(b);
	iTexture.setSmooth(true);
	spdM = sp;
	maxHP = hp;
	hitbox = hb;
}
armor::armor() {}