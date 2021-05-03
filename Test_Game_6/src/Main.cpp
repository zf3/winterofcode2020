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
    window.setFramerateLimit(60);
    // run the main loop
    bool mouseButton = false, large1 = false, large2 = false, large3 = false, large4 = false;
    float speed = 1000, eSpeed = 100, xV = 0, yV = 0, deltaTime = 0, enemyTime = 0, enemyAmn = 0, enemyTimeM = 0.5, replayTime = 1, frict = 0.15, movementN = 0;
    int hitbox = 100, hitboxE = 100, wordSize = 100, screen = 1, wordSize2 = 50, topScoreN = 0, totalScoreN = 0, runsN = 0;
    string scoreString = "0", scoreString2 = "0", scoreString3 = "0", scoreString4 = "0", scoreString5 = "0";
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
    sf::Texture statsT;
    statsT.loadFromFile("resources/StatsSkins.png");
    sf::Texture infoT;
    infoT.loadFromFile("resources/Instructions.png");
    sf::Texture backgroundT;
    backgroundT.loadFromFile("resources/Background.png");
    sf::Texture infoScreenT;
    infoScreenT.loadFromFile("resources/InstructionsScreen.png");
    sf::Texture backButtonT;
    backButtonT.loadFromFile("resources/BackButton.png");
    sf::Texture statsScreenT;
    statsScreenT.loadFromFile("resources/StatsScreen.png");
    sf::Sprite player;
    player.setTexture(playerT);
    player.setOrigin(hitbox/2,hitbox/2);
    player.setPosition(h/2,w/2);
    sf::Sprite button;
    button.setTexture(buttonT);
    button.setOrigin(750,750);
    button.setPosition(750,750);
    sf::Sprite stats;
    stats.setTexture(statsT);
    stats.setOrigin(750,400);
    stats.setPosition(750,400);
    sf::Sprite info;
    info.setTexture(infoT);
    info.setOrigin(750,1150);
    info.setPosition(750,1150);
    sf::Sprite backButton;
    backButton.setTexture(backButtonT);
    backButton.setOrigin(160,150);
    backButton.setPosition(160,150);
    sf::Sprite infoScreen;
    infoScreen.setTexture(infoScreenT);
    sf::Sprite endScreen;
    endScreen.setTexture(endScreenT);
    sf::Sprite background;
    background.setTexture(backgroundT);
    sf::Sprite statsScreen;
    statsScreen.setTexture(statsScreenT);
    sf::Font scoreFont;
    scoreFont.loadFromFile("resources/sansation.ttf");
    sf::Text score;
    score.setFont(scoreFont);
    score.setString(scoreString);
    score.setCharacterSize(wordSize);
    score.setFillColor(sf::Color::Black);
    score.setPosition(1500.0-2.0*(wordSize*scoreString.size())/3.0,-20);
    sf::Text topScore;
    topScore.setFont(scoreFont);
    topScore.setString(scoreString2);
    topScore.setCharacterSize(wordSize2);
    topScore.setFillColor(sf::Color::Black);
    topScore.setPosition(320,420);
    sf::Text totalScore;
    totalScore.setFont(scoreFont);
    totalScore.setString(scoreString3);
    totalScore.setCharacterSize(wordSize2);
    totalScore.setFillColor(sf::Color::Black);
    totalScore.setPosition(360,500);
    sf::Text runs;
    runs.setFont(scoreFont);
    runs.setString(scoreString4);
    runs.setCharacterSize(wordSize2);
    runs.setFillColor(sf::Color::Black);
    runs.setPosition(180,585);
    sf::Text movement;
    movement.setFont(scoreFont);
    movement.setString(scoreString5);
    movement.setCharacterSize(wordSize2);
    movement.setFillColor(sf::Color::Black);
    movement.setPosition(315,665);
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
            movementN+=sqrtf((xV*deltaTime)*(xV*deltaTime)+(yV*deltaTime)*(yV*deltaTime));
            float pX = player.getPosition().x;
            float pY = player.getPosition().y;
            if(pX > 1500 || pX < 0 || pY > 1500 || pY < 0) {
                screen = 1;
                replayTimeC.restart();
                button.setColor(sf::Color(255,255,255,255));
                endScreen.setColor(sf::Color(255,255,255,255));
                int pointScore = pointScoreT.asSeconds();
                totalScoreN += pointScore;
                topScoreN = max(topScoreN, pointScore);
                runsN++;
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
                    int pointScore = pointScoreT.asSeconds();
                    totalScoreN += pointScore;
                    topScoreN = max(topScoreN, pointScore);
                    runsN++;
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
            xV=xV*powf(frict,deltaTime);
            yV=yV*powf(frict,deltaTime);
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
                        window.draw(background);
                        window.draw(player);
                        window.draw(endScreen);
                        window.draw(button);
                        window.draw(stats);
                        window.draw(info);
                        window.draw(score);
                        window.display();
                        fadeT = fadeC.getElapsedTime();
                        endScreen.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*255));
                        button.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*255));
                        stats.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*255));
                        info.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*255));
                        window.clear(sf::Color(192,192,192));
                    }
                    enemyTimeC.restart();
                    deltaTimeC.restart();
                    pointUpdateC.restart();
                    pointScoreC.restart();
                    break;
                }
                if (replayTimeT.asSeconds() >= replayTime && event.type == sf::Event::MouseButtonPressed && mx >= 275 && mx <= 1215 && my >= 1055 && my <= 1245) {
                    screen = 2;
                    break;
                }
                if (replayTimeT.asSeconds() >= replayTime && event.type == sf::Event::MouseButtonPressed && mx >= 275 && mx <= 1215 && my >= 305 && my <= 495) {
                    screen = 3;
                    stringstream conv;
                    conv << topScoreN;
                    scoreString2 = conv.str();
                    topScore.setString(scoreString2);
                    stringstream conv2;
                    conv2 << totalScoreN;
                    scoreString3 = conv2.str();
                    totalScore.setString(scoreString3);
                    stringstream conv3;
                    conv3 << runsN;
                    scoreString4 = conv3.str();
                    runs.setString(scoreString4);
                    stringstream conv4;
                    conv4 << movementN;
                    scoreString5 = conv4.str();
                    movement.setString(scoreString5);
                    break;
                }
            }
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            if(large1 == false && mx >= 262 && mx <= 1237 && my >= 562 && my <= 937) {
                button.setScale(1.075,1.075);
                large1 = true;
            }
            if(large1 == true && (mx < 262 || mx > 1237 || my < 562 || my > 937)){
                button.setScale(1,1);
                large1 = false;
            }
            if(large2 == false && mx >= 275 && mx <= 1215 && my >= 305 && my <= 495) {
                stats.setScale(1.075,1.075);
                large2 = true;
            }
            if(large2 == true && (mx < 275 || mx > 1215 || my < 305 || my > 495)){
                stats.setScale(1,1);
                large2 = false;
            }
            if(large3 == false && mx >= 275 && mx <= 1215 && my >= 1055 && my <= 1245) {
                info.setScale(1.075,1.075);
                large3 = true;
            }
            if(large3 == true && (mx < 275 || mx > 1215 || my < 1055 || my > 1245)){
                info.setScale(1,1);
                large3 = false;
            }
            if(screen == 1) {
                window.clear(sf::Color(192,192,192));
                window.draw(endScreen);
                window.draw(button);
                window.draw(stats);
                window.draw(info);
                window.draw(score);
            }
            window.display();
        }
        if(screen == 2) {
            replayTimeT = replayTimeC.getElapsedTime();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                float mx = sf::Mouse::getPosition(window).x;
                float my = sf::Mouse::getPosition(window).y;
                if (replayTimeT.asSeconds() >= replayTime && event.type == sf::Event::MouseButtonPressed && mx >= 60 && mx <= 260 && my >= 80 && my <= 220) {
                    screen = 1;
                    break;
                }
            }
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            if(large4 == false && mx >= 60 && mx <= 260 && my >= 80 && my <= 220) {
                backButton.setScale(1.075,1.075);
                large4 = true;
            }
            if(large4 == true && (mx < 60 || mx > 260 || my < 80 || my > 220)){
                backButton.setScale(1,1);
                large4 = false;
            }
            window.clear(sf::Color(192,192,192));
            window.draw(endScreen);
            window.draw(infoScreen);
            window.draw(backButton);
            window.display();
        }
        if(screen == 3) {
            replayTimeT = replayTimeC.getElapsedTime();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    break;
                }
                float mx = sf::Mouse::getPosition(window).x;
                float my = sf::Mouse::getPosition(window).y;
                if (replayTimeT.asSeconds() >= replayTime && event.type == sf::Event::MouseButtonPressed && mx >= 60 && mx <= 260 && my >= 80 && my <= 220) {
                    screen = 1;
                    break;
                }
            }
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            if(large4 == false && mx >= 60 && mx <= 260 && my >= 80 && my <= 220) {
                backButton.setScale(1.075,1.075);
                large4 = true;
            }
            if(large4 == true && (mx < 60 || mx > 260 || my < 80 || my > 220)){
                backButton.setScale(1,1);
                large4 = false;
            }
            window.clear(sf::Color(192,192,192));
            window.draw(endScreen);
            window.draw(statsScreen);
            window.draw(topScore);
            window.draw(totalScore);
            window.draw(runs);
            window.draw(movement);
            window.draw(backButton);
            window.display();
        }
    }
    return EXIT_SUCCESS;
}