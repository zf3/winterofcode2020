#include<weapon.hpp>

#include "basicChar.hpp"

void weapon::apply(basicChar *target) {
	target->atkDist = atkDist;
	target->spd = target->spd*spdM;
	target->weaponM = spdM;
	target->wCooldownM = wCooldownM;
	target->wCooldownM2 = wCooldownM2;
	target->dmg = dmg;
	target->dmg2 = dmg2;
	target->atkD = atkD;
	target->atkD2 = atkD2;
	target->atk2Spd = atk2Spd;
	target->atk2Rot = atk2Rot;
	target->totalCycles = totalCycles;
	target->totalCycles2 = totalCycles2;
	target->heldWeapon.setTexture(wTexture);
	target->wTexture = wTexture;
	target->fIconW = fIcon;
	for(int i = 0; i < totalCycles; i++) {
		target->atkAnims[i] = atkAnims[i];
		target->tipPosA[i] = tipPosA[i];
	}
	for(int i = 0; i < totalCycles2; i++) {
		target->atkAnims2[i] = atkAnims2[i];
		target->tipPos2A[i] = tipPos2A[i];
	}
	for(int i = 0; i < totalCycles; i++) {
		target->atkAnims[i] = atkAnims[i];
		target->tipPosB[i] = tipPosB[i];
	}
	for(int i = 0; i < totalCycles2; i++) {
		target->atkAnims2[i] = atkAnims2[i];
		target->tipPos2B[i] = tipPos2B[i];
	}
}
weapon::weapon(string a, string ic, string fic, string desc, string *textures, string *textures2, sf::Vector2f *tPosA, sf::Vector2f *tPos2A, sf::Vector2f *tPosB, sf::Vector2f *tPos2B, int n, int n2, float sp, float cM, float cM2, float dm, float dm2, float aD, float aD2, float a2S, float a2R, float atkDi) {
	for(int i = 0; i < n; i++) {
		atkAnims[i].loadFromFile(*(textures+i));
		tipPosA[i] = *(tPosA+i);
	}
	for(int i = 0; i < n2; i++) {
		atkAnims2[i].loadFromFile(*(textures2+i));
		tipPos2A[i] = *(tPos2A+i);
	}
	for(int i = 0; i < n; i++) {
		atkAnims[i].loadFromFile(*(textures+i));
		tipPosB[i] = *(tPosB+i);
	}
	for(int i = 0; i < n2; i++) {
		atkAnims2[i].loadFromFile(*(textures2+i));
		tipPos2B[i] = *(tPos2B+i);
	}
	spdM = sp;
	wTexture.loadFromFile(a);
	wTexture.setSmooth(true);
	icon.loadFromFile(ic);
	icon.setSmooth(true);
	fIcon.loadFromFile(fic);
	fIcon.setSmooth(true);
	description.loadFromFile(desc);
	description.setSmooth(true);
	totalCycles = n;
	totalCycles2 = n2;
	wCooldownM = cM;
	wCooldownM2 = cM2;
	dmg = dm;
	dmg2 = dm2;
	atkD = aD;
	atkD2 = aD2;
	atk2Spd = a2S;
	atk2Rot = a2R;
	atkDist = atkDi;
}
weapon::weapon() {}