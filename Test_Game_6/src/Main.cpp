#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;
const float pi = 3.1415;
const int h = 1500, w = 1500;
int main() {
    sf::RenderWindow window(sf::VideoMode(h, w), "My window");
    // run the main loop
    bool mouseButton = false, large = false;
    float speed = 1000, eSpeed = 100, xV = 0, yV = 0, deltaTime = 0, enemyTime = 0, enemyAmn = 0, enemyTimeM = 0.5, replayTime = 1;
    int hitbox = 100, hitboxE = 100, wordSize = 100, screen = 1;
    string scoreString = "0";
    vector<float> xVs, yVs;
    vector<sf::Sprite> enemies;
    sf::Clock replayTimeC;
    sf::Time replayTimeT;
    sf::Clock pointUpdateC;
    sf::Time pointUpdateT;
    sf::Clock pointScoreC;
    sf::Time pointScoreT;
    sf::Clock enemyTimeC;
    sf::Time enemyTimeT;
    sf::Clock deltaTimeC;
    sf::Time deltaTimeT;
    sf::Texture playerT;
    playerT.loadFromFile("resources/Player.png");
    sf::Texture enemyT;
    enemyT.loadFromFile("resources/Enemy.png");
    sf::Texture endScreenT;
    endScreenT.loadFromFile("resources/StartScreen.png");
    sf::Texture buttonT;
    buttonT.loadFromFile("resources/Button.png");
    sf::Texture backgroundT;
    backgroundT.loadFromFile("resources/Background.png");
    sf::Sprite player;
    player.setTexture(playerT);
    player.setOrigin(hitbox/2,hitbox/2);
    player.setPosition(h/2,w/2);
    sf::Sprite button;
    button.setTexture(buttonT);
    button.setOrigin(750,750);
    button.setPosition(750,750);
    button.setScale(0.75,0.75);
    sf::Sprite endScreen;
    endScreen.setTexture(endScreenT);
    sf::Sprite background;
    background.setTexture(backgroundT);
    sf::Font scoreFont;
    scoreFont.loadFromFile("resources/sansation.ttf");
    sf::Text score;
    score.setFont(scoreFont);
    score.setString(scoreString);
    score.setCharacterSize(wordSize);
    score.setFillColor(sf::Color::Black);
    score.setPosition(1500.0-2.0*(wordSize*scoreString.size())/3.0,-20);
    while (window.isOpen()) {
        if(screen == 0) {
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
            pointUpdateT = pointUpdateC.getElapsedTime();
            if(pointUpdateT.asSeconds() >= 0.5) {
                pointUpdateC.restart();
                pointScoreT = pointScoreC.getElapsedTime();
                int pointScore = pointScoreT.asSeconds();
                stringstream conv;
                conv << pointScore;
                scoreString = conv.str();
                score.setString(scoreString);
                score.setPosition(1500.0-2.0*(wordSize*scoreString.size())/3.0,-20);
            }
            enemyTimeT = enemyTimeC.getElapsedTime();
            enemyTime = enemyTimeT.asSeconds();
            if(enemyTime >= enemyTimeM) {
                enemyTimeM*=0.995;
                eSpeed*=1.005;
                enemyTimeC.restart();
                int type = rand()%4;
                float angle = ((rand()%180)+type*90)%360;
                sf::Sprite tmp;
                tmp.setTexture(enemyT);
                tmp.setOrigin(hitboxE/2,hitboxE/2);
                tmp.setRotation(angle+90);
                if(type == 0) {
                    tmp.setPosition(rand()%1500,0);
                }
                if(type == 1) {
                    tmp.setPosition(1500,rand()%1500);
                }
                if(type == 2) {
                    tmp.setPosition(rand()%1500,1500);
                }
                if(type == 3) {
                    tmp.setPosition(0,rand()%1500);
                }
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
            float pX = player.getPosition().x;
            float pY = player.getPosition().y;
            if(pX > 1500 || pX < 0 || pY > 1500 || pY < 0) {
                screen = 1;
                replayTimeC.restart();
                button.setColor(sf::Color(255,255,255,255));
                endScreen.setColor(sf::Color(255,255,255,255));
            }
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
                float upX = cos((enemies[i].getRotation()-90.0)/180.0*pi)*hitboxE/2.0, upY = sin((enemies[i].getRotation()-90.0)/180.0*pi)*hitboxE/2.0;
                float downX = -upX, downY = -upY;
                float rightX = upY, rightY = -upX;
                float leftX = -upY, leftY = upX;
                float cX1 = eX+upX, cY1 = eY+upY;
                float cX2 = eX+leftX+downX, cY2 = eY+leftY+downY;
                float cX3 = eX+rightX+downX, cY3 = eY+rightY+downY;
                float pX = player.getPosition().x;
                float pY = player.getPosition().y;
                if(sqrtf((pX-cX1)*(pX-cX1)+(pY-cY1)*(pY-cY1)) <= hitbox/2
                || sqrtf((pX-cX2)*(pX-cX2)+(pY-cY2)*(pY-cY2)) <= hitbox/2
                || sqrtf((pX-cX3)*(pX-cX3)+(pY-cY3)*(pY-cY3)) <= hitbox/2) {
                    enemies.erase(enemies.begin()+i);
                    xVs.erase(xVs.begin()+i);
                    yVs.erase(yVs.begin()+i);
                    enemyAmn--;
                    screen = 1;
                    replayTimeC.restart();
                    button.setColor(sf::Color(255,255,255,255));
                    endScreen.setColor(sf::Color(255,255,255,255));
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
            window.clear(sf::Color(192,192,192));
            //window.draw(background);
            window.draw(player);
            for(int i = 0; i < enemyAmn; i++) {
                window.draw(enemies[i]);
            }
            window.draw(score);
            window.display();
        }
        if(screen == 1) {
            replayTimeT = replayTimeC.getElapsedTime();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                float mx = sf::Mouse::getPosition(window).x;
                float my = sf::Mouse::getPosition(window).y;
                if (replayTimeT.asSeconds() >= replayTime && event.type == sf::Event::MouseButtonPressed && mx >= 262 && mx <= 1237 && my >= 562 && my <= 937) {
                    while(enemyAmn > 0) {
                        xVs.pop_back();
                        yVs.pop_back();
                        enemies.pop_back();
                        enemyAmn--;
                    }
                    scoreString = "0";
                    player.setPosition(h/2,w/2);
                    mouseButton = false;
                    speed = 1000, eSpeed = 100, xV = 0, yV = 0, deltaTime = 0, enemyTime = 0, enemyAmn = 0, enemyTimeM = 0.5;
                    hitbox = 100, hitboxE = 100;
                    screen = 0;
                    sf::Clock fadeC;
                    sf::Time fadeT;
                    fadeT = fadeC.getElapsedTime();
                    while(255-fadeT.asSeconds()*255 > 0) {
                        fadeT = fadeC.getElapsedTime();
                        endScreen.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*255));
                        button.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*255));
                        window.clear(sf::Color(192,192,192));
                        window.draw(background);
                        window.draw(player);
                        window.draw(endScreen);
                        window.draw(button);
                        window.draw(score);
                        window.display();
                    }
                    enemyTimeC.restart();
                    deltaTimeC.restart();
                    pointUpdateC.restart();
                    pointScoreC.restart();
                    break;
                }
            }
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            if(large == false && mx >= 262 && mx <= 1237 && my >= 562 && my <= 937) {
                button.setScale(0.8,0.8);
                large = true;
            }
            if(large == true && (mx < 262 || mx > 1237 || my < 562 || my > 937)){
                button.setScale(0.75,0.75);
                large = false;
            }
            window.clear(sf::Color(192,192,192));
            window.draw(endScreen);
            window.draw(button);
            window.draw(score);
            window.display();
        }
    }
    return EXIT_SUCCESS;
}