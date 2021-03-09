#include "basicChar.hpp"

using namespace std;
static const float PI = 3.1415;

//wall collision detection
bool basicChar::objCollisions(float xM, float yM, const int *tilemap, int xL, int *objs, int n) {
	float px = body.getPosition().x+xM, py = body.getPosition().y+yM;
	int c1x = (px+(hitbox-1))/hitbox/2, c1y = (py+(hitbox-1))/hitbox/2;
	int c2x = (px-(hitbox-1))/hitbox/2, c2y = (py+(hitbox-1))/hitbox/2;
	int c3x = (px+(hitbox-1))/hitbox/2, c3y = (py-(hitbox-1))/hitbox/2;
	int c4x = (px-(hitbox-1))/hitbox/2, c4y = (py-(hitbox-1))/hitbox/2;
	for(int i = 0; i < n; i++) {
		if(*(tilemap+c1x+c1y*xL) == *(objs+i))
			return true;
		if(*(tilemap+c2x+c2y*xL) == *(objs+i))
			return true;
		if(*(tilemap+c3x+c3y*xL) == *(objs+i))
			return true;
		if(*(tilemap+c4x+c4y*xL) == *(objs+i))
			return true;
	}
	return false;
}
bool basicChar::detectTarget(basicChar *target, vector<int> wallTypes, int n, const int *arr, int l) {
	int x0 = body.getPosition().x/hitbox/2;
	int y0 = body.getPosition().y/hitbox/2;
	int x1 = target->body.getPosition().x/hitbox/2;
	int y1 = target->body.getPosition().y/hitbox/2;
	int x2 = body.getPosition().x;
	int y2 = body.getPosition().y;
	int x3 = target->body.getPosition().x;
	int y3 = target->body.getPosition().y;
	if(sqrt((x2-x3)*(x2-x3)+(y2-y3)*y2-y3) > sightRange) {
		return false;
	}
	float xM = x1-x0;
    float yM = y1-y0;
    float slope = yM/xM;
    float err = 0.0;
    int y = y0;
    for(int i = x0; i <= x1; i++) {
        err+=slope;
        for(int j = 0; j < n; j++) {
            if(*(arr+i+y*l)==wallTypes[j]) {
                return false;
            }
        }
        while(err>=1&&y!=y1) {
            y++;
            err--;
            for(int j = 0; j < n; j++) {
                if(*(arr+i+y*l)==wallTypes[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}
//animation cycles
void basicChar::basicCollisionDetection (basicChar *target) {
	float bx = body.getPosition().x, by = body.getPosition().y;
	float br = body.getRotation()/180*PI;
	float tx = target->body.getPosition().x, ty = target->body.getPosition().y;
	for(int i = 0; i <= 3; i++) {
		float rawWX = tipPosA[atkAnimStage].x+i*(float)(tipPosB[atkAnimStage].x-tipPosA[atkAnimStage].x)/3.0;
		float rawWY = tipPosA[atkAnimStage].y+i*(float)(tipPosB[atkAnimStage].y-tipPosA[atkAnimStage].y)/3.0;
		float wx = bx+cos(br)*rawWX+cos(br-PI/2)*rawWY;
		float wy = by+sin(br)*rawWX+sin(br-PI/2)*rawWY;
		if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= target->hitbox && target->damaged == false) {
			target->hp-=dmg;
			target->damaged = true;
			target->body.setTexture(target->bTexture2);
		}
	}
}
void basicChar::loadAnim(int enemyCount, vector<basicChar> &enemies) {
	animTime = animClock.getElapsedTime();
	if(animTime.asSeconds() >= atkD/totalCycles && atkAnimStage < totalCycles) {
		animClock.restart();
		heldWeapon.setTexture(atkAnims[atkAnimStage]);
		atkAnimStage++;
		for(int i = 0; i < enemyCount; i++) {
			basicCollisionDetection(&enemies[i]);
		}
	}
	else if(animTime.asSeconds() >= atkD/totalCycles && atkAnimStage >= totalCycles) {
		heldWeapon.setTexture(wTexture);
		atkAnimStage = 0;
		atkActive = false;
		heldWeapon.setOrigin(312,312);
		for(int i = 0; i < enemyCount; i++) {
			enemies[i].damaged = false;
			enemies[i].body.setTexture(enemies[i].bTexture);
		}
	}
}
void basicChar::basicCollisionDetection2 (basicChar *target) {
	float bx = body.getPosition().x, by = body.getPosition().y;
	float br = body.getRotation()/180*PI;
	float tx = target->body.getPosition().x, ty = target->body.getPosition().y;
	for(int i = 0; i <= 3; i++) {
		float rawWX = tipPos2A[atkAnimStage].x+i*(tipPos2B[atkAnimStage].x-tipPos2A[atkAnimStage].x)/3.0;
		float rawWY = tipPos2A[atkAnimStage].y+i*(tipPos2B[atkAnimStage].y-tipPos2A[atkAnimStage].y)/3.0;
		float wx = bx+cos(br)*rawWX+cos(br-PI/2)*rawWY;
		float wy = by+sin(br)*rawWX+sin(br-PI/2)*rawWY;
		if(sqrtf((wx-tx)*(wx-tx)+(wy-ty)*(wy-ty)) <= target->hitbox && target->damaged == false) {
			target->hp-=dmg2;
			target->damaged = true;
			target->body.setTexture(target->bTexture2);
		}
	}
}
void basicChar::loadAnim2(int enemyCount, vector<basicChar> &enemies, float deltaTime, sf::View *gameView, sf::RenderWindow *window, const int *tilemap,int xL,int *objs, int n, display *playerHUD) {
	animTime2 = animClock2.getElapsedTime();
	float xM = deltaTime*atk2Spd*cos(body.getRotation()/180*PI);
	float yM = deltaTime*atk2Spd*sin(body.getRotation()/180*PI);
	if(objCollisions(xM,0,tilemap,xL,objs,n) == false) {
		body.move(xM,0);
		heldWeapon.move(xM,0);
		hpBar.move(xM,0);
		hpBarBack.move(xM,0);
		playerHUD->move(xM,0);
		gameView->move(xM,0);
		window->setView(*gameView);
	}
	if(objCollisions(0,yM,tilemap,xL,objs,n) == false) {
		body.move(0,yM);
		heldWeapon.move(0,yM);
		hpBar.move(0,yM);
		hpBarBack.move(0,yM);
		playerHUD->move(0,yM);
		gameView->move(0,yM);
		window->setView(*gameView);
	}
	body.rotate(deltaTime*atk2Rot);
	heldWeapon.rotate(deltaTime*atk2Rot);
	hpBar.rotate(deltaTime*atk2Rot);
	hpBarBack.rotate(deltaTime*atk2Rot);
	if(animTime2.asSeconds() >= atkD2/totalCycles2 && atkAnimStage2 < totalCycles2) {
		animClock2.restart();
		heldWeapon.setTexture(atkAnims2[atkAnimStage2]);
		atkAnimStage2++;
		for(int i = 0; i < enemyCount; i++) {
			basicCollisionDetection2(&enemies[i]);
		}
	}
	else if(animTime2.asSeconds() >= atkD2/totalCycles2 && atkAnimStage2 >= totalCycles2) {
		heldWeapon.setTexture(wTexture);
		atkAnimStage2 = 0;
		atkActive2 = false;
		heldWeapon.setOrigin(312,312);
		for(int i = 0; i < enemyCount; i++) {
			enemies[i].damaged = false;
			enemies[i].body.setTexture(enemies[i].bTexture);
		}
	}
}
void basicChar::move(float x, float y) {
	body.move(x,y);
	heldWeapon.move(x,y);
	hpBar.move(x,y);
	hpBarBack.move(x,y);
}
//constructor
basicChar::basicChar (int sp, int sr, int re,int gr,int bl,int x,int y) {
	body.setOrigin(sf::Vector2f(312,312));
	body.setPosition(sf::Vector2f(x,y));
	heldWeapon.setOrigin(sf::Vector2f(312,312));
	heldWeapon.setPosition(sf::Vector2f(x,y));
	atkActive = false;
	atkActive2 = false;
	atkAnimStage = 0;
	atkAnimStage2 = 0;
	atkDist = 0;
	wCooldown = 0;
	wCooldown2 = 0;
	damaged = false;
	spd = sp;
	weaponM = 1;
	armorM = 1;
	sightRange = sr;
	hpBar.setSize(sf::Vector2f(5,hp/2));
	hpBar.setFillColor(sf::Color(re,gr,bl));
	hpBar.setOrigin(sf::Vector2f(25,25));
	hpBar.setPosition(x,y);
	hpBarBack.setSize(sf::Vector2f(5,50));
	hpBarBack.setFillColor(sf::Color(255,255,255));
	hpBarBack.setOutlineThickness(5);
	hpBarBack.setOutlineColor(sf::Color(0,0,0));
	hpBarBack.setOrigin(sf::Vector2f(25,25));
	hpBarBack.setPosition(x,y);
}
