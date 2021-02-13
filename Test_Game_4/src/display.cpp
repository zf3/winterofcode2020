#include "display.hpp"

using namespace std;

void display::renew(float wC, float wCM, float wC2, float wCM2, float hp, float mHP) {
        float e,f;
        if((1-wC2/wCM2) > 0) {
            e = 1-wC2/wCM2;
        }
        else {
            e = 0;
        }
        if((1-wC/wCM) > 0) {
            f = 1-wC/wCM;
        }
        else {
            f = 0;
        }
        block1.setSize(sf::Vector2f(593*f*scale,200*scale));
        block2.setSize(sf::Vector2f(-(593*e*scale),200*scale));
        block3.setSize(sf::Vector2f(462*scale,462*(1-hp/mHP)*scale));
    }
void display::move(float x, float y) {
        display1.move(x,y);
        display2.move(x,y);
        display3.move(x,y);
        display4.move(x,y);
        block1.move(x,y);
        block2.move(x,y);
        block3.move(x,y);
    }
display::display(string a, string b, string c, string d, int re, int gr, int bl, int x, int y, float scl) {
	scale = scl;
	texture1.loadFromFile(a);
	texture1.setSmooth(true);
	texture2.loadFromFile(b);
	texture2.setSmooth(true);
	texture3.loadFromFile(c);
	texture3.setSmooth(true);
	texture4.loadFromFile(d);
	texture4.setSmooth(true);
	display1.setTexture(texture1);
	display1.setScale(sf::Vector2f(scl,scl));
	display2.setTexture(texture2);
	display2.setScale(sf::Vector2f(scl,scl));
	display3.setTexture(texture3);
	display3.setScale(sf::Vector2f(scl,scl));
	display4.setTexture(texture4);
	display4.setScale(sf::Vector2f(scl,scl));
	block1.setFillColor(sf::Color(re,gr,bl));
	block1.setSize(sf::Vector2f(593*scl,200*scl));
	block2.setFillColor(sf::Color(re,gr,bl));
	block2.setSize(sf::Vector2f(-593*scl,200*scl));
	block3.setFillColor(sf::Color(re,gr,bl));
	block3.setSize(sf::Vector2f(462*scl,462*scl));
	display1.setPosition(x-608,y+309);
	display2.setPosition(x-608,y+309);
	display3.setPosition(x-608,y+309);
	display4.setPosition(x-608,y+309);
	block1.setPosition(x-608+373/2,y+309+264/2);
	block2.setPosition(x-608+2048/2,y+309+253/2);
	block3.setPosition(x-608+983/2,y+309+84/2);
}