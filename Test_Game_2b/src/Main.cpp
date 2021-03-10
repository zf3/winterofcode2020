#include <SFML/Window.hpp>
#include<vector>
#include<cmath>

#define PI 3.14159265

using namespace sf;
using namespace std;
struct proj {
    Sprite shot;
    double xV, yV, time, maxTime;
};
int main()
{
    double yVel = 0, xVel = 0, playerAngle = 0;
    int maxPlayerHP = 5, playerHP = maxPlayerHP, s = 0;
    Texture playerT;
    if (!playerT.loadFromFile("resources/player.png"))
    {
    }
    Texture shotT1;
    if (!shotT1.loadFromFile("resources/proj1_small.png"))
    {
    }
    Clock shotTimer;
    Sprite player;
    vector<proj> shots;
    player.setPosition(1150,750);
    player.setTexture(playerT);
    RenderWindow window(VideoMode(2400, 1800), "Test window");
    RectangleShape topBorder(Vector2f(2400.f, 60.f));
    RectangleShape bottomBorder(Vector2f(2400.f, 60.f));
    RectangleShape leftBorder(Vector2f(60.f, 1800.f));
    RectangleShape rightBorder(Vector2f(60.f, 1800.f));
    RectangleShape hpBarWhite(Vector2f(800, 230));
    RectangleShape hpBarGreen(Vector2f(180, 230));
    topBorder.setFillColor(Color(128,32,32));
    bottomBorder.setFillColor(Color(128,32,32));
    leftBorder.setFillColor(Color(128,32,32));
    rightBorder.setFillColor(Color(128,32,32));
    hpBarGreen.setFillColor(Color(16,192,16));
    bottomBorder.setPosition(0,1740);
    topBorder.setPosition(0,0);
    leftBorder.setPosition(0,0);
    rightBorder.setPosition(2340,0);
    hpBarWhite.setPosition(100,100);
    hpBarGreen.setPosition(100,100);
    hpBarWhite.setScale(0.1,0.1);
    hpBarGreen.setScale(0.1,0.1);
    hpBarWhite.setOutlineThickness(20);
    hpBarWhite.setOutlineColor(sf::Color(128, 128, 128));
    hpBarGreen.setOutlineThickness(20);
    hpBarGreen.setOutlineColor(sf::Color(128, 128, 128));
    while(window.isOpen()) {
        Vector2f position = player.getPosition();
        Vector2i mPosition = Mouse::getPosition(window);
        playerAngle = atan2((mPosition.y-position.y),(mPosition.x-position.x))*180/PI;
        if(playerAngle < 0) {
            playerAngle = 360-abs(playerAngle);
        }
        Event event;
        while (window.pollEvent(event))
        {
            Time sElapsed = shotTimer.getElapsedTime();
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                yVel-=0.05;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                xVel+=0.05;
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                xVel-=0.05;
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                xVel = 0;
                yVel = 0;
                player.setPosition(1150,750);
                playerHP = maxPlayerHP;
            }
            if (Mouse::isButtonPressed(Mouse::Left) && sElapsed.asSeconds() >= 1) {
                proj temp;
                temp.xV = cos(playerAngle/180*PI);
                temp.yV = sin(playerAngle/180*PI);
                temp.time = 0;
                temp.maxTime = 100;
                temp.shot.setTexture(shotT1);
                temp.shot.move(player.getPosition().x,player.getPosition().y);
                s++;
                shots.push_back(temp);
                shotTimer.restart();
            }
        }
        yVel+=0.0005;
        yVel*=0.999;
        xVel*=0.999;
        if(position.y >= 1550) {
            player.setPosition(position.x,1549);
            yVel = yVel/-2;
            playerHP--;
        }
        if(position.y  <= 50) {
            player.setPosition(position.x,51);
            yVel = yVel/-2;
            playerHP--;
        }
        if(position.x >= 2210) {
            player.setPosition(2209,position.y);
            xVel = xVel/-2;
            playerHP--;
        }
        if(position.x  <= 30) {
            player.setPosition(31,position.y);
            xVel = xVel/-2;
            playerHP--;
        }
        if(playerHP <= 0) {
            yVel = 0, xVel = 0;
        }
        window.clear(sf::Color::Black);
        for(int i = 0; i < s; i++) {
            shots[i].time+=0.01;
            if(shots[i].time > shots[i].maxTime) {
                shots.erase(shots.begin()+i);
                s--;
            }
            //shots[i].yV+=0.0005;
            shots[i].yV*=0.9999;
            shots[i].xV*=0.9999;
            Vector2f position = shots[i].shot.getPosition();
            if(position.y >= 1550) {
                shots[i].shot.setPosition(position.x,1549);
                shots[i].yV = shots[i].yV/-1.1;
            }
            if(position.y  <= 50) {
                shots[i].shot.setPosition(position.x,51);
                shots[i].yV = shots[i].yV/-1.1;
            }
            if(position.x >= 2210) {
                shots[i].shot.setPosition(2209,position.y);
                shots[i].xV = shots[i].xV/-1.1;
            }
            if(position.x  <= 30) {
                shots[i].shot.setPosition(31,position.y);
                shots[i].xV = shots[i].xV/-1.1;
            }
            shots[i].shot.move(shots[i].xV,shots[i].yV);
            window.draw(shots[i].shot);
        }
        hpBarGreen.setScale(playerHP/10.0,0.1);
        hpBarWhite.setPosition(player.getPosition().x+45,player.getPosition().y-50);
        hpBarGreen.setPosition(player.getPosition().x+45,player.getPosition().y-50);
        player.move(xVel,yVel);
        window.draw(player);
        window.draw(topBorder);
        window.draw(bottomBorder);
        window.draw(leftBorder);
        window.draw(rightBorder);
        window.draw(hpBarWhite);
        window.draw(hpBarGreen);
        window.display();
    }
    return 0;
}
