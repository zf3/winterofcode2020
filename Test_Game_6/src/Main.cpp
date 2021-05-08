#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Platform/Platform.hpp"

using namespace std;
const float pi = 3.1415;
const int h = 1500, w = 1500;
util::Platform platform;

int main() {
    cout << filesystem::current_path() << endl;

    sf::RenderWindow window(sf::VideoMode(h, w), "My window");
    window.setFramerateLimit(60);
    fstream savefile;
    savefile.open("resources/savefile.txt");
    bool mouseButton = false, large1 = false, large2 = false, large3 = false, large4 = false, largeArr[4][5];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            largeArr[i][j] = false;
        }
    }
    float speed = 1000, eSpeed = 100, xV = 0, yV = 0, deltaTime = 0, enemyTime = 0, enemyAmn = 0, enemyTimeM = 0.5, replayTime = 1, frict = 0.15, movementN = 0;
    int hitbox = 100, hitboxE = 100, wordSize = 100, screen = -1, wordSize2 = 50, topScoreN = 0, totalScoreN = 0, runsN = 0, chosenSkin[4];
    string scoreString = "0", scoreString2 = "0", scoreString3 = "0", scoreString4 = "0", scoreString5 = "0";
    savefile >> topScoreN >> totalScoreN >> runsN >> movementN;
    for(int i = 0; i < 4; i++) {
        savefile >> chosenSkin[i];
    }
    savefile.close();
    savefile.open("resources/savefile.txt");
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
    sf::Clock waitC;
    sf::Time waitT;
    sf::Clock fadeC;
    sf::Time fadeT;
    sf::Texture buttonT;
    buttonT.loadFromFile("resources/Button.png");
    sf::Texture statsT;
    statsT.loadFromFile("resources/StatsSkins.png");
    sf::Texture infoT;
    infoT.loadFromFile("resources/Instructions.png");
    sf::Texture infoScreenT;
    infoScreenT.loadFromFile("resources/InstructionsScreen.png");
    sf::Texture backButtonT;
    backButtonT.loadFromFile("resources/BackButton.png");
    sf::Texture statsScreenT;
    statsScreenT.loadFromFile("resources/StatsScreen.png");
    sf::Texture lockT;
    lockT.loadFromFile("resources/Lock.png");
    sf::Texture creditT;
    creditT.loadFromFile("resources/Credit.png");
    sf::Texture skins[4][5];
    skins[0][0].loadFromFile("resources/pS1.png");
    skins[0][1].loadFromFile("resources/pS2.png");
    skins[0][2].loadFromFile("resources/pS3.png");
    skins[0][3].loadFromFile("resources/pS4.png");
    skins[0][4].loadFromFile("resources/pS5.png");
    skins[1][0].loadFromFile("resources/eS1.png");
    skins[1][1].loadFromFile("resources/eS2.png");
    skins[1][2].loadFromFile("resources/eS3.png");
    skins[1][3].loadFromFile("resources/eS4.png");
    skins[1][4].loadFromFile("resources/eS5.png");
    skins[2][0].loadFromFile("resources/gS1.png");
    skins[2][1].loadFromFile("resources/gS2.png");
    skins[2][2].loadFromFile("resources/gS3.png");
    skins[2][3].loadFromFile("resources/gS4.png");
    skins[2][4].loadFromFile("resources/gS5.png");
    skins[3][0].loadFromFile("resources/bS1.png");
    skins[3][1].loadFromFile("resources/bS2.png");
    skins[3][2].loadFromFile("resources/bS3.png");
    skins[3][3].loadFromFile("resources/bS4.png");
    skins[3][4].loadFromFile("resources/bS5.png");
    sf::Sprite skinDisps[4][5];
    sf::Sprite lockDisps[4][5];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 5; j++) {
            lockDisps[i][j].setTexture(lockT);
            lockDisps[i][j].setOrigin(60,60);
            lockDisps[i][j].setPosition(368.5+j*183.5,806.5+i*180);
            skinDisps[i][j].setTexture(skins[i][j]);
            if(i == 2 || i == 3) {
                skinDisps[i][j].setOrigin(750,750);
                skinDisps[i][j].setScale(4/75.0,4/75.0);
            }
            else {
                skinDisps[i][j].setOrigin(50,50);
                skinDisps[i][j].setScale(0.8,0.8);
            }
            skinDisps[i][j].setPosition(368.5+j*183.5,806.5+i*180);
        }
    }
    sf::Sprite credit;
    credit.setTexture(creditT);
    sf::Sprite player;
    sf::Sprite tmp;
    sf::Sprite endScreen;
    sf::Sprite background;
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
    sf::Sprite statsScreen;
    statsScreen.setTexture(statsScreenT);
    for(int i = 0; i < 4; i++) {
        if(i == 0 || i == 1) {
            skinDisps[i][chosenSkin[i]].setScale(1,1);
        }
        else {
            skinDisps[i][chosenSkin[i]].setScale(1/15.0,1/15.0);
        }
        if(i == 0) {
            player.setTexture(skins[i][chosenSkin[i]]);
        }
        if(i == 1) {
            tmp.setTexture(skins[i][chosenSkin[i]]);
        }
        if(i == 2) {
            background.setTexture(skins[i][chosenSkin[i]]);
        }
        if(i == 3) {
            endScreen.setTexture(skins[i][chosenSkin[i]]);
        }
    }
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
    fadeC.restart();
    waitC.restart();
    while (window.isOpen()) {
        sf::Event event;

        if(screen == -1) {
            while(window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                    for(int i = 0; i < 4; i++) {
                        savefile << chosenSkin[i] << endl;
                    }
                    savefile.close();
                    window.close();
                    break;
                }
            }
            waitT = waitC.getElapsedTime();
            window.clear(sf::Color(192,192,192));
            window.draw(credit);
            window.display();
            if(waitT.asSeconds() >= 3.0) {
                fadeC.restart();
            }
            while(waitT.asSeconds() >= 3.0) {
                fadeT = fadeC.getElapsedTime();
                while(255-fadeT.asSeconds()*225 > 0) {
                    window.pollEvent(event);
                    if (event.type == sf::Event::Closed) {
                        savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                        for(int i = 0; i < 4; i++) {
                            savefile << chosenSkin[i] << endl;
                        }
                        savefile.close();
                        window.close();
                        break;
                    }
                    window.clear(sf::Color(192,192,192));
                    window.draw(endScreen);
                    window.draw(button);
                    window.draw(stats);
                    window.draw(info);
                    window.draw(score);
                    window.draw(credit);
                    window.display();
                    fadeT = fadeC.getElapsedTime();
                    credit.setColor(sf::Color(255,255,255,255-fadeT.asSeconds()*225));
                    window.clear(sf::Color(192,192,192));
                }
                screen = 1;
                break;
            }
        }
        if(screen == 0) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                    for(int i = 0; i < 4; i++) {
                        savefile << chosenSkin[i] << endl;
                    }
                    savefile.close();
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
                stats.setColor(sf::Color(255,255,255,255));
                info.setColor(sf::Color(255,255,255,255));
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
                    stats.setColor(sf::Color(255,255,255,255));
                    info.setColor(sf::Color(255,255,255,255));
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
            window.draw(background);
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
                    savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                    for(int i = 0; i < 4; i++) {
                        savefile << chosenSkin[i] << endl;
                    }
                    savefile.close();
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
                        window.pollEvent(event);
                        if (event.type == sf::Event::Closed) {
                            savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                            for(int i = 0; i < 4; i++) {
                                savefile << chosenSkin[i] << endl;
                            }
                            savefile.close();
                            window.close();
                            break;
                        }
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
                    for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 5; j++) {
                            bool isUnlocked = false;
                            if(i == 0 && topScoreN >= j*20) {
                                isUnlocked = true;
                            }
                            if(i == 1 && totalScoreN >= j*400) {
                                isUnlocked = true;
                            }
                            if(i == 2 && runsN >= j*10) {
                                isUnlocked = true;
                            }
                            if(i == 3 && movementN >= j*50000) {
                                isUnlocked = true;
                            }
                            if(isUnlocked == true) {
                                lockDisps[i][j].setColor(sf::Color(255,255,255,0));
                            }
                        }
                    }
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
                window.display();
            }
        }
        if(screen == 2) {
            replayTimeT = replayTimeC.getElapsedTime();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                    for(int i = 0; i < 4; i++) {
                        savefile << chosenSkin[i] << endl;
                    }
                    savefile.close();
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
            window.draw(score);
            window.display();
        }
        if(screen == 3) {
            replayTimeT = replayTimeC.getElapsedTime();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    savefile << topScoreN << endl << totalScoreN << endl << runsN << endl << movementN << endl;
                    for(int i = 0; i < 4; i++) {
                        savefile << chosenSkin[i] << endl;
                    }
                    savefile.close();
                    window.close();
                    break;
                }
                float mx = sf::Mouse::getPosition(window).x;
                float my = sf::Mouse::getPosition(window).y;
                if(event.type == sf::Event::MouseButtonPressed) {
                    for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 5; j++) {
                            bool isUnlocked = false;
                            if(i == 0 && topScoreN >= j*20) {
                                isUnlocked = true;
                            }
                            if(i == 1 && totalScoreN >= j*400) {
                                isUnlocked = true;
                            }
                            if(i == 2 && runsN >= j*10) {
                                isUnlocked = true;
                            }
                            if(i == 3 && movementN >= j*50000) {
                                isUnlocked = true;
                            }
                            if(isUnlocked == true && mx >= 318.5+j*183.5 && mx <= 418.5+j*183.5 && my >= 756.5+i*180 && my <= 856.5+i*180) {
                                if(i == 0) {
                                    player.setTexture(skins[i][j]);
                                }
                                if(i == 1) {
                                    tmp.setTexture(skins[i][j]);
                                }
                                if(i == 2) {
                                    background.setTexture(skins[i][j]);
                                }
                                if(i == 3) {
                                    endScreen.setTexture(skins[i][j]);
                                }
                                if(i == 0 || i == 1) {
                                    skinDisps[i][chosenSkin[i]].setScale(0.8,0.8);
                                    skinDisps[i][j].setScale(1,1);
                                }
                                else {
                                    skinDisps[i][chosenSkin[i]].setScale(4/75.0,4/75.0);
                                    skinDisps[i][j].setScale(1/15.0,1/15.0);
                                }
                                chosenSkin[i] = j;
                            }
                        }
                    }
                }
                if (replayTimeT.asSeconds() >= replayTime && event.type == sf::Event::MouseButtonPressed && mx >= 60 && mx <= 260 && my >= 80 && my <= 220) {
                    screen = 1;
                    break;
                }
            }
            float mx = sf::Mouse::getPosition(window).x;
            float my = sf::Mouse::getPosition(window).y;
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 5; j++) {
                    bool isUnlocked = false;
                    if(i == 0 && topScoreN >= j*20) {
                        isUnlocked = true;
                    }
                    if(i == 1 && totalScoreN >= j*400) {
                        isUnlocked = true;
                    }
                    if(i == 2 && runsN >= j*10) {
                        isUnlocked = true;
                    }
                    if(i == 3 && movementN >= j*50000) {
                        isUnlocked = true;
                    }
                    if(isUnlocked == true && chosenSkin[i] != j && largeArr[i][j] == false && mx >= 318.5+j*183.5 && mx <= 418.5+j*183.5 && my >= 756.5+i*180 && my <= 856.5+i*180) {
                        if(i == 0 || i == 1) {
                            skinDisps[i][j].setScale(0.9,0.9);
                        }
                        else {
                            skinDisps[i][j].setScale(0.06,0.06);
                        }
                        largeArr[i][j] = true;
                    }
                    if(isUnlocked == true && chosenSkin[i] != j && largeArr[i][j] == true && (mx < 318.5+j*183.5 || mx > 418.5+j*183.5 || my < 756.5+i*180 || my > 856.5+i*180)) {
                        if(i == 0 || i == 1) {
                            skinDisps[i][j].setScale(0.8,0.8);
                        }
                        else {
                            skinDisps[i][j].setScale(4/75.0,4/75.0);
                        }
                        largeArr[i][j] = false;
                    }
                }
            }
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
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 5; j++) {
                    window.draw(skinDisps[i][j]);
                    window.draw(lockDisps[i][j]);
                }
            }
            window.draw(backButton);
            window.draw(score);
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
