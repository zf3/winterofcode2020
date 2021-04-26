#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
const float pi = 3.1415;
const int h = 1500, w = 1500;
int main() {
    sf::RenderWindow window(sf::VideoMode(h, w), "My window");
    // run the main loop
    bool mouseButton = false, gameEnd = false;
    float speed = 1000, eSpeed = 100, xV = 0, yV = 0, deltaTime = 0, enemyTime = 0, enemyAmn = 0, enemyTimeM = 0.5;
    int hitbox = 100, hitboxE = 100;
    vector<float> xVs, yVs;
    vector<sf::Sprite> enemies;
    sf::Clock enemyTimeC;
    sf::Time enemyTimeT;
    sf::Clock deltaTimeC;
    sf::Time deltaTimeT;
    sf::Texture playerT;
    playerT.loadFromFile("resources/Player.png");
    sf::Texture enemyT;
    enemyT.loadFromFile("resources/Enemy.png");
    sf::Texture endScreenT;
    endScreenT.loadFromFile("resources/Restart Screen.png");
    sf::Sprite player;
    player.setTexture(playerT);
    player.setOrigin(hitbox/2,hitbox/2);
    player.setPosition(h/2,w/2);
    sf::Sprite endScreen;
    endScreen.setTexture(endScreenT);
    while (window.isOpen()) {
        if(gameEnd == false) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                if(event.type == sf::Event::MouseButtonPressed) {
                    mouseButton = true;
                }
                if(event.type == sf::Event::MouseButtonReleased) {
                    mouseButton = false;
                }
            }
            enemyTimeT = enemyTimeC.getElapsedTime();
            enemyTime = enemyTimeT.asSeconds();
            if(enemyTime >= enemyTimeM) {
                enemyTimeM*=0.995;
                eSpeed*=1.005;
                enemyTimeC.restart();
                float angle = (rand()%180);
                sf::Sprite tmp;
                tmp.setTexture(enemyT);
                tmp.setOrigin(hitboxE/2,hitboxE/2);
                tmp.setRotation(angle+90);
                tmp.setPosition(rand()%1500,0);
                xVs.push_back(cos(angle/180*pi)*eSpeed);
                yVs.push_back(sin(angle/180*pi)*eSpeed);
                enemies.push_back(tmp);
                enemyAmn++;
            }
            //deltaTime
            deltaTimeT = deltaTimeC.getElapsedTime();
            deltaTime = deltaTimeT.asSeconds();
            deltaTimeC.restart();
            //player AI
            player.move(xV*deltaTime,yV*deltaTime);
            //enemy AI
            for(int i = 0; i < enemyAmn; i++) {
                enemies[i].move(sf::Vector2f(xVs[i]*deltaTime,yVs[i]*deltaTime));
                float eX = enemies[i].getPosition().x;
                float eY = enemies[i].getPosition().y;
                if(eX > 1500 || eX < 0 || eY > 1500 || eY < 0) {
                    enemies.erase(enemies.begin()+i);
                    xVs.erase(xVs.begin()+i);
                    yVs.erase(yVs.begin()+i);
                    enemyAmn--;
                    break;
                }
                float cX1 = eX, cY1 = eY+hitboxE/2;
                float cX2 = eX+hitboxE/2, cY2 = eY-hitboxE/2;
                float cX3 = eX-hitboxE/2, cY3 = eY-hitboxE/2;
                float pX = player.getPosition().x;
                float pY = player.getPosition().y;
                if(sqrtf((pX-cX1)*(pX-cX1)+(pY-cY1)*(pY-cY1)) <= hitbox/2
                || sqrtf((pX-cX2)*(pX-cX2)+(pY-cY2)*(pY-cY2)) <= hitbox/2
                || sqrtf((pX-cX3)*(pX-cX3)+(pY-cY3)*(pY-cY3)) <= hitbox/2) {
                    enemies.erase(enemies.begin()+i);
                    xVs.erase(xVs.begin()+i);
                    yVs.erase(yVs.begin()+i);
                    enemyAmn--;
                    gameEnd = true;
                    break;
                }
            }
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            float px = player.getPosition().x;
            float py = player.getPosition().y;
            float angle = atan2(my-py,mx-px)*180/pi;
            player.setRotation(angle+90);
            if(mouseButton == true) {
                xV+=deltaTime*speed*cos(angle/180*pi);
                yV+=deltaTime*speed*sin(angle/180*pi);
            }
            xV=xV*0.999;
            yV=yV*0.999;
            if(abs(xV) <= deltaTime) {
                xV=0;
            }
            if(abs(yV) <= deltaTime) {
                yV=0;
            }
            window.clear(sf::Color(192,192,192));
            window.draw(player);
            for(int i = 0; i < enemyAmn; i++) {
                window.draw(enemies[i]);
            }
            window.display();
        }
        if(gameEnd == true) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    while(enemyAmn > 0) {
                        xVs.pop_back();
                        yVs.pop_back();
                        enemies.pop_back();
                        enemyAmn--;
                    }
                    enemyTimeC.restart();
                    deltaTimeC.restart();
                    player.setPosition(h/2,w/2);
                    mouseButton = false;
                    speed = 1000, eSpeed = 100, xV = 0, yV = 0, deltaTime = 0, enemyTime = 0, enemyAmn = 0, enemyTimeM = 2.0;
                    hitbox = 100, hitboxE = 100;
                    gameEnd = false;
                    break;
                }
            }
            window.clear(sf::Color(192,192,192));
            window.draw(endScreen);
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
